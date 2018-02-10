//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Usefull/buffer.h"
#include "./Pot/List/vector.h"
#include "./Pot/Game/type.h"

namespace cpot {


class GameObject;

using ComponentName = HashString<28>;

class Component {
	CPOT_TYPE_BASE(Component);

	//初期化処理
	#pragma region Init
public:
	//コンストラクタ
	Component();

	void InitComponent(GameObject* aGameObject);

	#pragma endregion


	//終了
	#pragma region Final
public:
	//仮想コンストラクタ
	virtual ~Component();

	#pragma endregion


	//GameObjectに関する
	#pragma region GameObject

private:
	GameObject* mGameObject;

public:
	GameObject* GetGameObject() const {
		return mGameObject;
	}

	#pragma region Function

public:
	//GameObjectの関数を、Componentでも使えるように
	template <typename T>
	T* GetComponent();
	template <typename T>
	u32 GetComponentNum();
	Transform& GetTransform();

	#pragma endregion

	#pragma endregion


	//状態
	#pragma region Flags

private:
	BitFlag mFlags;
	enum CFlags {
		cDelete,
		cDeleteNow,
		cActive,
		cGameObjectActive
	};

	#pragma region Delete

public:
	BOOL GetDelete() const {
		return mFlags.IsStand(cDelete);
	}
	void SetDelete() {
		mFlags.Stand(cDelete);
	}

	BOOL GetDeleteNow() const {
		return mFlags.IsStand(cDeleteNow);
	}

	#pragma endregion


	#pragma region Active

	BOOL GetActive() const {
		return GetThisActive() && GetGameObjectActive();
	}
	BOOL GetThisActive() const {
		return mFlags.IsStand(cActive);
	}
	BOOL GetGameObjectActive() const {
		return mFlags.IsStand(cGameObjectActive);
	}
	void SetActive(BOOL aIsActive) {
		mFlags.Flag(cActive, aIsActive);
	}
	void SetGameObjectActive(BOOL aIsActive) {
		mFlags.Flag(cGameObjectActive, aIsActive);
	}

	#pragma endregion

	#pragma endregion


	//コンポーネントの名前
	#pragma region Name

	ComponentName mName;
	const ComponentName& GetName() const {
		return mName;
	}
	void SetName(const CHAR* aName) {
		mName = aName;
	}
	void SetName(const ComponentName& aName) {
		mName = aName;
	}

	#pragma endregion


	//コンポーネントごとのユニークな番号
	#pragma region Unique

	u32 mUnique;
	u32 GetUnique() const {
		return mUnique;
	}

	#pragma endregion

};


class ComponentManager : public Singleton<ComponentManager> {

	friend class Component;

	//登録&解除。Componentが呼び出す
	#pragma region Regist&Remove

private:
	void Regist(Component* aComponent) {
		mComponentNowFrame.PushBack(aComponent);
	}
	void Remove(Component* aComponent) {
		
	}

public:
	void Clear() {
		while (mComponentNowFrame.GetSize() != 0) {
			CPOT_DELETE(mComponentNowFrame.PopBack());
		}
		while (mComponent.GetSize() != 0) {
			CPOT_DELETE(mComponent.PopBack());
		}
	}

	#pragma endregion

public:
	void Update() {
		Merge();	//前のフレームに追加されたコンポーネントを統合する
		Delete();	//コンポーネントを削除する
	}

private:
	void Merge() {
		while (mComponentNowFrame.GetSize() != 0) {
			mComponent.PushBack(mComponentNowFrame.PopBack());
		}
	}

	void Delete() {
		for (u32 i = 0; i < mComponent.GetSize(); i++) {
			if (mComponent[i]->GetDelete() == true) {

			}
		}
	}


private:
	Vector<Component*> mComponentNowFrame;	//新しく追加されたコンポーネント
	Vector<Component*> mComponent;
};

}
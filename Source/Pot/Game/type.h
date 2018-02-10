//
//	content	:	コンポーネントを登録するためのクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"

namespace cpot {

class Component;

//コンポーネントを作成するクラスの基底クラス
class TypeFactoryBase {
public:
	virtual const Type& GetTypeName() = 0;
	virtual Component* Create() = 0;
};


//コンポーネントを作成するクラス
template <typename T>
class TypeFactory : public TypeFactoryBase {
public:
	const Type& GetTypeName() override {
		return T::SGetTypeName();
	}
	Component* Create() override {
		return new T;
	}
};


//コンポーネントを作成するクラスを管理するクラス
class TypeFactoryManager : public Singleton<TypeFactoryManager> {
	friend class Singleton<TypeFactoryManager>;
private:
	TypeFactoryManager() {
		mFactoryNum = 0;
	}


public:
	//コンポーネントを作成するクラスの、最大可能登録数
	static const u32 cTypeFactoryMax = 1024;


public:
	//コンポーネントを作成するクラスを登録する
	void Regist(TypeFactoryBase* aFactory) {
		CPOT_ASSERT(mFactoryNum < cTypeFactoryMax);
		mFactory[mFactoryNum++] = aFactory;
	}

	//コンポーネントの型名から、コンポーネントを作成する
	Component* Create(const Type& aTypeName) {
		for (u32 i = 0; i < mFactoryNum; i++) {
			if (aTypeName == mFactory[i]->GetTypeName()) {
				return mFactory[i]->Create();
			}
		}
		return nullptr;
	}

private:
	u32 mFactoryNum;
	TypeFactoryBase* mFactory[cTypeFactoryMax];
};


//コンポーネントを作成するクラスを登録するクラス
template <typename T>
class TypeFactoryRegister {
public:
	TypeFactoryRegister() {
		TypeFactoryManager::S().Regist(&mFactory);
	}

private:
	TypeFactory<T> mFactory;
};


//TypeFactoryRegisterクラスを実体化するクラス
template <typename T>
class TypeFactoryRegisterInstatiate {
private:
	static TypeFactoryRegister<T> mFactoryRegister;
};

template <typename T>
TypeFactoryRegister<T> TypeFactoryRegisterInstatiate<T>::mFactoryRegister;

#define CPOT_REGIST_TYPE(TYPE) template class TypeFactoryRegisterInstatiate<TYPE>;


}
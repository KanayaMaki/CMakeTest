//
//	content	:	ユニークな数を取得できるクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {

template <typename T>
class UniqueGenerator : public Singleton<UniqueGenerator<T>> {
	friend class Singleton<UniqueGenerator<T>>;

private:
	UniqueGenerator() {
		mCurrentNum = 0;
	}


	#pragma region Generate

private:
	u32 mCurrentNum;

public:
	u32 Generate() {
		return mCurrentNum++;
	}

	#pragma endregion


	#pragma region Restart

public:
	void Restart(u32 aRestartNum) {
		mCurrentNum = aRestartNum;
	}

	#pragma endregion

};

}

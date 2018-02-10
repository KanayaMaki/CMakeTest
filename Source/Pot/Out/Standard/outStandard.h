//
//	content	:	標準出力する
//	author	:	SaitoYoshiki
//


#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Out/out.h"

#include <cstdio>


namespace cpot {

namespace standard {


//	標準出力するクラス
class OutStandard : public OutBase {

	//その他
	#pragma region Other

private:
	//OutBaseの関数のオーバーライド。文字列を出力する
	void OutputStr(const CHAR* aStr) override {
		std::printf(aStr);
	}

	#pragma endregion

};


}


}
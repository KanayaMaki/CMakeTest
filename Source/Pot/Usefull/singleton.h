//
//	content	:	シングルトンのテンプレート基底クラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

template <class T>
class Singleton {
public:
	static T& S() {
		static T s;
		return s;
	}

protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(const Singleton&) {}
	const Singleton& operator =(const Singleton&) {}
};


}

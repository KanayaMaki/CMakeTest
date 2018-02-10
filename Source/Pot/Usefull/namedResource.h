//
//	content	:	Resource‚ÌƒŠƒXƒg‚ğì¬‚·‚é
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/hashTable.h"

namespace cpot {

class NamedResource {

	#pragma region Name

public:
	void SetName(const CHAR* aName) {
		mName = aName;
	}
	void SetName(const HashTableKey& aName) {
		mName = aName;
	}

public:
	const HashTableKey& GetName() const {
		return mName;
	}

	#pragma endregion

private:
	HashTableKey mName;
};


}
//
//	content	:	ResourceÇÃÉäÉXÉgÇçÏê¨Ç∑ÇÈ
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {


class ResourceUpdater {
public:
	virtual ~ResourceUpdater() {}

public:
	virtual void Update() = 0;
};


class ResourceUpdaterList : public Singleton<ResourceUpdaterList> {
	friend class Singleton<ResourceUpdaterList>;

private:
	ResourceUpdaterList() {
		mResourceUpdaterNum = 0;
	}


public:
	void Regist(ResourceUpdater* aResourceUpdater) {
		CPOT_ASSERT(mResourceUpdaterNum < cResourceUpdaterMaxNum);
		mResourceUpdater[mResourceUpdaterNum] = aResourceUpdater;
		mResourceUpdaterNum++;
	}

	void Update() {
		for (u32 i = 0; i < mResourceUpdaterNum; i++) {
			mResourceUpdater[i]->Update();
		}
	}


private:
	static const u32 cResourceUpdaterMaxNum = 64;
	u32 mResourceUpdaterNum;
	ResourceUpdater* mResourceUpdater[cResourceUpdaterMaxNum];
};

}
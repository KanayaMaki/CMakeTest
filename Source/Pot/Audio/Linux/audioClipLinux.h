//
//	content	:	AudioClipのLinuxでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"
#include "./Pot/Usefull/resourceLoadList.h"

#include "./Pot/Audio/audioClip.h"


namespace cpot {

namespace linux {


class AudioLoadData : public ResourceLoadList<AudioLoadData, String<64>> {

};

class AudioClip : public AudioClipBase {
	friend class ResourceList<AudioClip>;

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		SetName(aUnionName);
	};

	//プラットフォーム限定の読み込み
	void LoadPlatform(const CHAR* aFileName) {
		SetName(aFileName);
	};

public:
	void Release() CPOT_OR {
		
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return false;
	};


	//フィールド
	#pragma region Field

public:
	

	#pragma endregion
};

}

using AudioClip = linux::AudioClip;

}
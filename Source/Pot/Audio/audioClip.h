//
//	content	:	AudioClipのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class AudioClipBase : public NamedResource {

public:
	CPOT_VI void Load(const HashTableKey& aUnionName) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/Audio/XAudio/audioClipXAudio.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Audio/Android/audioClipAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/Audio/Linux/audioClipLinux.h"
#endif
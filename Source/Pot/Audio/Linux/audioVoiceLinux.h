//
//	content	:	AudioVoiceのXAudioでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceList.h"

#include "./Pot/Audio/audioVoice.h"

#include "./Pot/Audio/Linux/audioClipLinux.h"

namespace cpot {

namespace linux {

class AudioVoice : public AudioVoiceBase {
	friend class ResourceList<AudioVoice>;


	//ロード
	#pragma region Load

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mClip = ResourceList<AudioClip>::S().Find(aUnionName);
		Load(mClip);	//委譲
	}
	void Load(std::shared_ptr<AudioClip> aClip) CPOT_OR {
		SetName(aClip->GetName());
	}

	#pragma endregion

public:
	void Release() CPOT_OR {
	}


	//操作
	#pragma region Operate

public:
	//再生
	void Play() CPOT_OR {
	}

	//停止
	void Stop() CPOT_OR {
	}

	//ボリュームを設定
	void SetVolume(f32 aVolume) CPOT_OR {
	}
	//ボリュームを設定（現在のボリュームから相対的に）
	void SetVolumeRel(f32 aRelative) CPOT_OR {
	}

	#pragma endregion


public:
	//ボリュームを取得
	f32 GetVolume() CPOT_OR {
		return 0.0f;
	}

	BOOL IsLoad() const CPOT_OR {
		return false;
	}


	//フィールド
	#pragma region Field

public:
	std::shared_ptr<AudioClip> mClip;

	#pragma endregion

};

}

using AudioVoice = linux::AudioVoice;

}
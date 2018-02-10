//
//	content	:	ゲームのコンフィグのWindows環境
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Config/config.h"

#include "./Pot/Thread/mutex.h"

namespace cpot {

namespace linux {


#pragma region Config

class Config : public ConfigBase, public Singleton<Config> {
	
	//画面サイズ
	#pragma region ScreenSize

public:
	void SetScreenSize(const Vector2& aScreenSize) CPOT_OR {
		MutexLocker m(mScreenSizeMutex);
		mScreenSize = aScreenSize;
	}
	Vector2 GetScreenSize() CPOT_OR {
		MutexLocker m(mScreenSizeMutex);
		return mScreenSize;
	}

	#pragma endregion


	//アプリケーションが終了するかどうか
	#pragma region ApplicationEnd

public:
	void SetApplicationEnd() CPOT_OR {
		MutexLocker m(mApplicationEndMutex);
		mApplicationEnd = true;
	}
	BOOL GetApplicationEnd() CPOT_OR {
		MutexLocker m(mApplicationEndMutex);
		return mApplicationEnd;
	}

	#pragma endregion


	//ゲームが終了するかどうか
	#pragma region GameEnd

	void SetGameEnd() CPOT_OR {
		MutexLocker m(mGameEndMutex);
		mGameEnd = true;
	}
	BOOL GetGameEnd() CPOT_OR {
		MutexLocker m(mGameEndMutex);
		return mGameEnd;
	}

	#pragma endregion


	//ゲームタイトルの設定
	#pragma region Title

	void SetTitle(const CHAR* aTitle) CPOT_OR;
	const CHAR* GetTitle() CPOT_OR {
		MutexLocker m(mTitleMutex);
		return mTitle.Get();
	}

	#pragma endregion


	//ゲームがアクティブかどうか
	#pragma region Active

	void SetIsActive(BOOL aIsActive) CPOT_OR {
		MutexLocker m(mActiveMutex);
		mActive = aIsActive;
	}
	BOOL GetIsActive() CPOT_OR {
		MutexLocker m(mActiveMutex);
		return mActive;
	}

	#pragma endregion


	//ゲームのFPS
	#pragma region Fps

	void SetFps(f32 aFps) CPOT_OR {
		MutexLocker m(mFpsMutex);
		mFps = aFps;
	}
	f32 GetFps() CPOT_OR {
		MutexLocker m(mFpsMutex);
		return mFps;
	}

	#pragma endregion


private:
	Mutex mScreenSizeMutex;
	Mutex mTitleMutex;
	Mutex mApplicationEndMutex;
	Mutex mGameEndMutex;
	Mutex mActiveMutex;
	Mutex mFpsMutex;
};

#pragma endregion



}

using Config = linux::Config;

}

//
//	content	:	時間に関するクラス
//	author	:	SaitoYoshiki
//

#include "./Pot/Time/time.h"


namespace cpot {


//前のフレームからの経過時間
#pragma region DeltaTime


//経過時間を格納しておく変数
static const f32 cFps = 60.0f;
static u64 gDeltaTick = cTickUnit / cFps;
static f32 gDeltaTime = 1.0f / cFps;


f32 DeltaTime() {
	return gDeltaTime;
}

TickType DeltaTick() {
	return gDeltaTick;
}

//経過時間を設定
void SetDeltaTick(TickType aDeltaTick) {
	gDeltaTick = aDeltaTick;
	gDeltaTime = ToSecond(aDeltaTick);
}
//経過時間を設定
void SetDeltaTime(f32 aDeltaTime) {
	gDeltaTick = ToTick(aDeltaTime);
	gDeltaTime = aDeltaTime;
}


#pragma endregion


}
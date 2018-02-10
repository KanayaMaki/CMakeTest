//
//	content	:	時間に関するクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {


//ゲーム内の時間の単位、Tickの定義
#pragma region Tick


using TickType = u64;
const TickType cTickUnit = 1200000UL;	//1秒が何Tickか

//秒をチックに
inline TickType ToTick(f32 aSecond) {
	return static_cast<TickType>( aSecond * cTickUnit );
}

//チックを秒に
inline f32 ToSecond(TickType aTick) {
	return static_cast<f32>( (f64)aTick / cTickUnit );
}


#pragma endregion


//前のフレームからの経過時間
#pragma region DeltaTime

//経過時間を秒で取得
f32 DeltaTime();

//経過時間をチックで取得
TickType DeltaTick();

//経過時間を設定
void SetDeltaTick(TickType aDeltaTick);
void SetDeltaTime(f32 aDeltaTime);

#pragma endregion


using UnixTimeType = s64;


//日時
#pragma region DateTime

struct DateTimeData {
	s32 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
	enum CYoubi : u8 {
		cSunday,
		cMonday,
		cTuesday,
		cWednesday,
		cThursday,
		cFriday,
		cSaturday,
	} youbi;

};


class DateTime {

public:
	//現在の日時を取得する
	DateTimeData Get();

	//UnixTimeを現在の日時に変換する
	DateTimeData ToDateTime(UnixTimeType aUnixTime);
};



#pragma endregion


//時間を取得
#pragma region Time

class TimeBase {
public:
	//ユニックスタイムを取得
	CPOT_VI UnixTimeType GetUnix() const CPOT_ZR;

	//細密な時間を取得
	CPOT_VI f64 GetDetail() const CPOT_ZR;
};

#pragma endregion


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/Time/Windows/timeWindows.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Time/Android/timeAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/Time/Linux/timeLinux.h"
#endif
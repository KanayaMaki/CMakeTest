//
//	content	:	乱数を生成するクラスのインターフェース
//	author	:	SaitoYoshiki
//

#include "./Pot/Rand/rand.h"
#include "./Pot/Time/time.h"

namespace cpot {


//乱数の生成
#pragma region Next

//0 <= x, x <= aMaxの乱数を生成
RandType RandBase::Next(RandType aMax) {

	//全ての数が均等に出るように、中途半端な余りならもう一度生成する
	RandType lMaxMode = Mod(MaxValue(), aMax + 1); //中途半端な余りの大きさ
	RandType lMaxJust = MaxValue() - lMaxMode;	//ちょうど割り切れる最大数を求める

	while (true) {

		RandType v = Next();

		if (v >= lMaxJust) {
			continue;	//ちょうど割り切れる最大数以上なら、もう一度計算する
		}

		return Mod(v, aMax + 1);
	}
}

#pragma endregion


//操作
#pragma region Operate

//現在の時間をシードにリセット
void RandBase::Reset() {
	SetSeed(SeedType(Time().GetUnix()));
}

#pragma endregion

}
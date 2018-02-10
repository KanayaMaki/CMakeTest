#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/buffer.h"

namespace cpot {

class CharCodeBase {
public:
	static s32 Utf16ToShiftJis(const u8* pSource, u8* pDist);
	static s32 Utf8ToUtf16(const u8* pSource, u8* pDist);
	static s32 Utf8ToShiftJis(const u8* pSource, u8* pDist);

	static s32 ShiftJisToUtf16(const u8* pSource, u8* pDist);
	static s32 Utf16ToUtf8(const u8* pSource, u8* pDist);
	static s32 ShiftJisToUtf8(const u8* pSource, u8* pDist);


	static void Utf16ToShiftJis(const u8* pSource, Buffer& aRes);
	static void Utf8ToUtf16(const u8* pSource, Buffer& aRes);
	static void Utf8ToShiftJis(const u8* pSource, Buffer& aRes);

	static void ShiftJisToUtf16(const u8* pSource, Buffer& aRes);
	static void Utf16ToUtf8(const u8* pSource, Buffer& aRes);
	static void ShiftJisToUtf8(const u8* pSource, Buffer& aRes);
};

}

#ifdef CPOT_ON_WINDOWS
#include "./Pot/ModelLoader/Windows/CharCodeWindows.h"
#elif defined CPOT_ON_ANDROID

#elif defined CPOT_ON_LINUX
#include "./Pot/ModelLoader/Linux/CharCodeLinux.h"
#endif
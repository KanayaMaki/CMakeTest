#pragma once

#include "./Pot/ModelLoader/CharCode.h"

namespace cpot {

namespace linux {

class CharCode : public CharCodeBase {
public:
	static s32 Utf16ToShiftJis(const u8* pSource, u8* pDist) { return 0; }
	static s32 Utf8ToUtf16(const u8* pSource, u8* pDist) { return 0; }
	static s32 Utf8ToShiftJis(const u8* pSource, u8* pDist) { return 0; }

	static s32 ShiftJisToUtf16(const u8* pSource, u8* pDist) { return 0; }
	static s32 Utf16ToUtf8(const u8* pSource, u8* pDist) { return 0; }
	static s32 ShiftJisToUtf8(const u8* pSource, u8* pDist) { return 0; }


	static void Utf16ToShiftJis(const u8* pSource, Buffer& aRes) {}
	static void Utf8ToUtf16(const u8* pSource, Buffer& aRes) {}
	static void Utf8ToShiftJis(const u8* pSource, Buffer& aRes) {}

	static void ShiftJisToUtf16(const u8* pSource, Buffer& aRes) {}
	static void Utf16ToUtf8(const u8* pSource, Buffer& aRes) {}
	static void ShiftJisToUtf8(const u8* pSource, Buffer& aRes) {}
};

}

using CharCode = linux::CharCode;

}

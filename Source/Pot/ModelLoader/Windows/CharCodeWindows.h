#pragma once

#include "./Pot/ModelLoader/CharCode.h"

#include <Shlwapi.h>

namespace cpot {

namespace windows {

class CharCode : public CharCodeBase {
public:
	static s32 Utf16ToShiftJis(const u8* pSource, u8* pDist) {

		s32 sizeShiftJis = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pSource, -1, (LPSTR)NULL, 0, NULL, NULL);

		s32 buffSize = sizeShiftJis;

		if (pDist == nullptr) {
			return buffSize;
		}

		u8* buff = new u8[buffSize];
		::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pSource, -1, (LPSTR)buff, buffSize, NULL, NULL);

		CopyMem(pDist, buff, buffSize);

		return buffSize;
	}
	static s32 Utf8ToUtf16(const u8* pSource, u8* pDist) {

		s32 sizeUtf16 = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSource, -1, NULL, 0);

		s32 buffSize = sizeUtf16 * 2;

		if (pDist == nullptr) {
			return buffSize;
		}

		u8* buff = new u8[buffSize];
		::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pSource, -1, (LPWSTR)buff, sizeUtf16);

		CopyMem(pDist, buff, buffSize);

		return buffSize;
	}
	static s32 Utf8ToShiftJis(const u8* pSource, u8* pDist) {

		s32 utf16Size = Utf8ToUtf16(pSource, NULL);

		u8* utf16Buff = new u8[utf16Size];
		Utf8ToUtf16(pSource, utf16Buff);

		s32 shiftJisSize = Utf16ToShiftJis(utf16Buff, NULL);

		if (pDist == NULL) {
			delete[] utf16Buff;
			return shiftJisSize;
		}

		u8* shiftJisBuff = new u8[shiftJisSize];
		Utf16ToShiftJis(utf16Buff, shiftJisBuff);

		CopyMem(pDist, shiftJisBuff, shiftJisSize);

		delete[] utf16Buff;
		delete[] shiftJisBuff;

		return shiftJisSize;
	}

	static s32 ShiftJisToUtf16(const u8* pSource, u8* pDist) {

		s32 sizeUtf16 = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pSource, -1, NULL, 0);

		s32 buffSize = sizeUtf16 * 2;

		if (!pDist) {
			return buffSize;
		}

		u8* buff = new u8[buffSize];
		::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pSource, -1, (LPWSTR)buff, sizeUtf16);

		CopyMem(pDist, buff, buffSize);

		return buffSize;
	}
	static s32 Utf16ToUtf8(const u8* pSource, u8* pDist) {

		s32 sizeUtf8 = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pSource, -1, (LPSTR)NULL, 0, NULL, NULL);

		s32 buffSize = sizeUtf8;

		if (!pDist) {
			return buffSize;
		}

		u8* buff = new u8[buffSize];
		::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pSource, -1, (LPSTR)buff, buffSize, NULL, NULL);

		CopyMem(pDist, buff, buffSize);

		return buffSize;
	}
	static s32 ShiftJisToUtf8(const u8* pSource, u8* pDist) {

		s32 a = StringLen((CHAR*)pSource);

		s32 utf16Size = ShiftJisToUtf16(pSource, NULL);

		u8* utf16Buff = new u8[utf16Size];
		ShiftJisToUtf16(pSource, utf16Buff);

		s32 utf8Size = Utf16ToUtf8(utf16Buff, NULL);

		if (pDist == NULL) {
			delete[] utf16Buff;
			return utf8Size;
		}

		u8* utf8Buff = new u8[utf8Size];
		Utf16ToUtf8(utf16Buff, utf8Buff);

		CopyMemory(pDist, utf8Buff, utf8Size);

		delete[] utf16Buff;
		delete[] utf8Buff;

		return utf8Size;
	}


	static void Utf16ToShiftJis(const u8* pSource, Buffer& aRes) {
		s32 lSize = Utf16ToShiftJis(pSource, nullptr);
		
		aRes.Create(lSize);

		Utf16ToShiftJis(pSource, aRes.Get());
	}
	static void Utf8ToUtf16(const u8* pSource, Buffer& aRes) {
		s32 lSize = Utf8ToUtf16(pSource, nullptr);
		aRes.Create(lSize);

		Utf8ToUtf16(pSource, aRes.Get());
	}
	static void Utf8ToShiftJis(const u8* pSource, Buffer& aRes) {
		s32 lSize = Utf8ToShiftJis(pSource, nullptr);
		aRes.Create(lSize);

		Utf8ToShiftJis(pSource, aRes.Get());
	}

	static void ShiftJisToUtf16(const u8* pSource, Buffer& aRes) {
		s32 lSize = ShiftJisToUtf16(pSource, nullptr);
		aRes.Create(lSize);

		ShiftJisToUtf16(pSource, aRes.Get());
	}
	static void Utf16ToUtf8(const u8* pSource, Buffer& aRes) {
		s32 lSize = Utf16ToUtf8(pSource, nullptr);
		aRes.Create(lSize);

		Utf16ToUtf8(pSource, aRes.Get());
	}
	static void ShiftJisToUtf8(const u8* pSource, Buffer& aRes) {
		s32 lSize = ShiftJisToUtf8(pSource, nullptr);
		aRes.Create(lSize);

		ShiftJisToUtf8(pSource, aRes.Get());
	}
};

}

using CharCode = windows::CharCode;

}

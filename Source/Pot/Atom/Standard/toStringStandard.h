//
//	content	:	Standard‚Å‚ÌToString‚Ì’è‹`
//	author	:	SaitoYoshiki
//

#pragma once

#include "../string.h"

#include <cstdio>
#include <cstring>

namespace cpot {

namespace standard {

class ToString {

public:

	static String<15> Do(s32 aVal) {
		CHAR toStringBuffer[16];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%d", aVal);
		#else
		std::sprintf(toStringBuffer, "%d", aVal);
		#endif
		return String<15>(toStringBuffer);
	}
	static String<15> Do(u32 aVal) {
		CHAR toStringBuffer[16];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%u", aVal);
		#else
		std::sprintf(toStringBuffer, "%u", aVal);
		#endif
		return String<15>(toStringBuffer);
	}
	static String<31> Do(s64 aVal) {
		CHAR toStringBuffer[32];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%lld", aVal);
		#else
		std::sprintf(toStringBuffer, "%lld", aVal);
		#endif
		return String<31>(toStringBuffer);
	}
	static String<31> Do(u64 aVal) {
		CHAR toStringBuffer[32];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%llu", aVal);
		#else
		std::sprintf(toStringBuffer, "%llu", aVal);
		#endif
		return String<31>(toStringBuffer);
	}
	static String<15> Do(f32 aVal) {
		CHAR toStringBuffer[16];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%f", aVal);
		#else
		std::sprintf(toStringBuffer, "%f", aVal);
		#endif
		return String<15>(toStringBuffer);
	}
	static String<31> Do(f64 aVal) {
		CHAR toStringBuffer[32];
		#ifdef CPOT_ON_WINDOWS
		sprintf_s(toStringBuffer, "%f", aVal);
		#else
		std::sprintf(toStringBuffer, "%f", aVal);
		#endif
		return String<31>(toStringBuffer);
	}
	static String<7> Do(BOOL aVal) {
		return String<7>(aVal ? "true" : "false");
	}
};

}

using ToString = standard::ToString;

}

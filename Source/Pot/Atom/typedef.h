//
//	content	:	基本のtypedefを定義
//	author	:	SaitoYoshiki
//

#pragma once

//Windows環境だと、voidとBOOLがdefineされていることがある為undefしておく
#ifdef void
#undef void
#endif

#ifdef BOOL
#undef BOOL
#endif

#include "defines.h"


namespace cpot {


using s8 = signed char;	//符号付8bit整数
using u8 = unsigned char;	//符号無8bit整数
using s16 = signed short int;
using u16 = unsigned short int;

#ifdef CPOT_ON_LINUX
using s32 = signed int;
using u32 = unsigned int;
#else
using s32 = signed long int;
using u32 = unsigned long int;
#endif

using s64 = signed long long int;
using u64 = unsigned long long int;

using f32 = float;	//32bit浮動小数点
using f64 = double;	//64bit浮動小数点

using CHAR = char;	//文字列の型
using BOOL = bool;	//真偽をあらわす型

using BYTE = u8;


//ポインタの値をすべて表せる整数型の定義
#ifdef CPOT_ON_32BIT
using Pointer = u32;
#elif defined CPOT_ON_64BIT
using Pointer = u64;
#endif


}
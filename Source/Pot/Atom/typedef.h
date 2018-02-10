//
//	content	:	��{��typedef���`
//	author	:	SaitoYoshiki
//

#pragma once

//Windows�����ƁAvoid��BOOL��define����Ă��邱�Ƃ������undef���Ă���
#ifdef void
#undef void
#endif

#ifdef BOOL
#undef BOOL
#endif

#include "defines.h"


namespace cpot {


using s8 = signed char;	//�����t8bit����
using u8 = unsigned char;	//������8bit����
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

using f32 = float;	//32bit���������_
using f64 = double;	//64bit���������_

using CHAR = char;	//������̌^
using BOOL = bool;	//�^�U������킷�^

using BYTE = u8;


//�|�C���^�̒l�����ׂĕ\���鐮���^�̒�`
#ifdef CPOT_ON_32BIT
using Pointer = u32;
#elif defined CPOT_ON_64BIT
using Pointer = u64;
#endif


}
//
//	content	:	基本となるdefineを定義
//	author	:	SaitoYoshiki
//


#pragma once

#include <cassert>


namespace cpot {


#pragma region OSの種類を定義

#ifdef _WINDOWS
#define CPOT_ON_WINDOWS
#elif defined _CONSOLE
#define CPOT_ON_WINDOWS
#elif defined CPOT_ANDROID
#define CPOT_ON_ANDROID
#elif defined CPOT_LINUX
#define CPOT_ON_LINUX
#endif

#pragma endregion



#pragma region CPUのアーキテクチャを定義

#ifdef CPOT_ON_WINDOWS

#ifdef WIN32
#define CPOT_ON_32BIT
#else
#define CPOT_ON_64BIT
#endif

#elif defined CPOT_ON_ANDROID

#ifdef CPOT_32BIT
#define CPOT_ON_32BIT
#else
#define CPOT_ON_64BIT
#endif

#elif defined CPOT_ON_LINUX

#ifdef CPOT_32BIT
#define CPOT_ON_32BIT
#else
#define CPOT_ON_64BIT
#endif

#endif

#pragma endregion



#pragma region 使用するグラフィックAPIを定義

#ifdef CPOT_DIRECTX9
#define CPOT_ON_DIRECTX9
#endif
#ifdef CPOT_DIRECTX11
#define CPOT_ON_DIRECTX11
#endif
#ifdef CPOT_OPENGL
#define CPOT_ON_OPENGL
#endif

#ifdef CPOT_ON_LINUX
#define CPOT_ON_OPENGL
#endif

#pragma endregion



#pragma region ビルドの構成を定義

#ifdef NDEBUG

#ifdef CPOT_MASTER
#define CPOT_ON_MASTER
#else
#define CPOT_ON_RELEASE
#endif

#else

#define CPOT_ON_DEBUG

#endif

#pragma endregion



#pragma region ビルドの構成によって様々な設定を定義

//デバッグビルド時
#ifdef CPOT_ON_DEBUG

#define CPOT_VALID_ASSERT	//アサートを有効に
#define CPOT_VALID_ERROR	//エラーを有効に
#define CPOT_VALID_LOG	//ログを使用する
#define CPOT_VALID_VI	//バーチャルを使用する

#define CPOT_VALID_HASHSTRING_LEFT	//HashStringの文字列を残す

//リリースビルド時
#elif defined CPOT_ON_RELEASE

#define CPOT_VALID_ASSERT
#define CPOT_VALID_ERROR
#define CPOT_VALID_LOG


//マスタービルド時
#elif defined CPOT_ON_MASTER

#endif

#pragma endregion



#pragma region アサートとエラーを有効にするかの設定


//アサートの設定
#ifdef CPOT_VALID_ASSERT
#define CPOT_ASSERT(expr) assert(expr)	//有効

#else
#define CPOT_ASSERT(expr)	//無効
#endif


//エラーの設定
#ifdef CPOT_VALID_ERROR
#define CPOT_ERROR(expr) assert(0 && expr)	//有効
#else
#define CPOT_ERROR(expr)	//無効
#endif


#pragma endregion



#pragma region	マスター以外の時にだけ呼ばれる式の設定

#ifndef CPOT_ON_MASTER
#define CPOT_DEBUG_EXP(expr) (expr)	//有効

#else
#define CPOT_DEBUG_EXP(expr)	//無効
#endif

#pragma endregion



#pragma region バーチャルを有効にするかの設定

//このdefineは、インターフェースをそろえるために開発時はvirtualとoverrideで開発して、Masterでは効率化のために仮想関数にしない時に使用する

//有効にする
#ifdef CPOT_VALID_VI
#define CPOT_VI virtual
#define CPOT_ZR =0
#define CPOT_OR override

//無効
#else
#define CPOT_VI
#define CPOT_ZR
#define CPOT_OR
#endif


#pragma endregion



}
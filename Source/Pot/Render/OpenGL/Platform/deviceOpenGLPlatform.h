#pragma once

#include "./Pot/Atom/atom.h"

#ifdef CPOT_ON_WINDOWS
#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatformWindows.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatformAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatformLinux.h"
#endif
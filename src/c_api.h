/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Preprocessor defines, mainly for win32 builds.
*/
#ifndef _PLUTO_API_H_
#define _PLUTO_API_H_

#define PLUTO_PIMPL std::unique_ptr
#define PLUTO_PIMPL_CREATE std::make_unique

// Use this define if compiling as a static library
#if defined(_PLUTO_STATIC_BUILD_) || !defined(_WIN32)
#define PLUTO_API
#define PLUTO_API_EXTERN
#else
// If compiling as a shared library (DLL, Windows only)
#ifdef _WIN32
#ifdef _PLUTO_EXPORT_DLL_
#define PLUTO_API __declspec(dllexport)
#define PLUTO_API_EXTERN
#else
#define PLUTO_API __declspec(dllimport)
#define PLUTO_API_EXTERN extern
#endif
#endif
#endif

/* Host platform */

#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#define _PLUTO_PLATFORM_WINDOWS_     // Windows
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#define _PLUTO_PLATFORM_APPLE_
#if defined(TARGET_OS_OSX)
#define _PLUTO_PLATFORM_APPLE_MACOS_ // macOS
#elif defined(TARGET_OS_IOS)
#define _PLUTO_PLATFORM_APPLE_IOS_   // iOS
#endif
#elif defined(__linux__)
#define _PLUTO_PLATFORM_LINUX_       // Linux
#elif defined(__unix__)
#define _PLUTO_PLATFORM_UNIX_        // Other Unix/Unix-like operating system.
#else
#define _PLUTO_PLATFORM_UNKNOWN_     // Unknown
#endif

#endif

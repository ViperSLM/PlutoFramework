/*
  Pluto Framework
  Copyright (C) 2023-2025 ViperSLM

  3-Clause BSD License

  Redistribution and use in source and binary forms, 
  with or without modification, are permitted provided 
  that the following conditions are met:

  1. Redistributions of source code must retain the above 
     copyright notice, this list of conditions and the 
     following disclaimer.

  2. Redistributions in binary form must reproduce the 
     above copyright notice, this list of conditions 
     and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names 
     of its contributors may be used to endorse or promote 
     products derived from this software without specific 
     prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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

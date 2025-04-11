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
  Integer data types and sizes
 
  Convention: [Signed/Unsigned][Size] (i.e. s8, u8, etc.)
*/
#ifndef _PLUTO_C_INTDEF_H_
#define _PLUTO_C_INTDEF_H_

/* Floating Point */
typedef float f32;

/* Double-precision Floating Point */
typedef double f64;

#if !defined(_PLUTO_NO_CSTDINT_)
#include <cstdint>
#include <cstddef>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;
typedef size_t usize;
typedef ptrdiff_t ssize;
typedef intptr_t sptr;
typedef uintptr_t uptr;

#else
// If not using the headers from the
// C/C++ standard library, we'll just
// define them here.

/* 8-Bit Integer */
#define S8_MIN ((s8)~0x7F)
#define S8_MAX ((s8)0x7F)
#define U8_MAX ((u8)0xFF)
typedef char s8;
typedef unsigned char u8;

/* 16-Bit Integer */
#define S16_MIN ((s16)~0x7FFF)
#define S16_MAX ((s16)0x7FFF)
#define U16_MAX ((u16)0xFFFF)
typedef short s16;
typedef unsigned short u16;

/* 32-Bit Integer */
#define S32_MIN ((s32)~0x7FFFFFFF)
#define S32_MAX ((s32)0x7FFFFFFF)
#define U32_MAX ((u32)0xFFFFFFFF)
#if !defined(_PLUTO_32INT_ALT_)
typedef int s32;
typedef unsigned int u32;
#else
typedef long s32;
typedef unsigned long u32;
#endif

/* 64-Bit Integer */
#if defined(_PLUTO_64BIT_)
#define S64_MIN ((s64)~0x7FFFFFFFFFFFFFFFll)
#define S64_MAX ((s64)0x7FFFFFFFFFFFFFFFll)
#define U64_MAX ((u64)0xFFFFFFFFFFFFFFFFull)
typedef long long s64;
typedef unsigned long long u64;

#else
#define S64_MIN S32_MIN
#define S64_MAX S32_MAX
#define U64_MAX U32_MAX
typedef s32 s64;
typedef u32 u64;
#endif

/* Pointer types */
typedef u64 usize;
typedef s64 ssize;

/* Equivalent to intptr_t/uintptr_t */
typedef s64 sptr;
typedef u64 uptr;
#endif

#endif

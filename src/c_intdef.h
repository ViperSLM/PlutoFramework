/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

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

/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Dynamic string class
*/
#ifndef _PLUTO_M_STRING_H_
#define _PLUTO_M_STRING_H_
#include "c_api.h"
#include "c_intdef.h"
#include <cstdarg>

#include <memory>

namespace Pluto {
// String compare mode
typedef enum {
  PLUTO_STRCMP_EQUAL,           // [ == ]
  PLUTO_STRCMP_NOT_EQUAL,       // [ != ]
  PLUTO_STRCMP_LESS,            // [ < ]
  PLUTO_STRCMP_GREAT,           // [ > ]
  PLUTO_STRCMP_LESS_OR_EQUAL,   // [ <= ]
  PLUTO_STRCMP_GREAT_OR_EQUAL   // [ >= ]
} strcmp_t;

/* Dynamic String class */
class PLUTO_API String {
public:
  String(void);

  /* Allows the string to be initialised with a value, printf-style. */
  /* (i.e. String str("Hello World"); */
  String(const char *format, ...);

  ~String(void);

  /* Sets the string's value using a printf-style input
   (Also, I like C's printf() better than C++'s std::cout) */
  void Set(const char *format, ...) const;

  /* SetV takes a va_list data type for arguments. */
  void SetV(const char *format, va_list args, bool newLine = false) const;

  /* Returns the string's internal value as a C-style string */
  const char *Get(void) const;

  /* Returns a Unicode string [Only works under Windows] */
  const wchar_t *Get_WideString(void) const;

  /* Appends/Adds input into current string value */
  void Append(const char *format, ...) const;

  /* Clears the string's stored value */
  void Clear(void) const;

  /* Returns a boolean value for the specified comparison */
  bool Compare(const char *input, strcmp_t mode) const;
  bool Compare(String &input, strcmp_t mode) const;

  /* Returns the length of the string
  (can be useful in for loops, for example) */
  usize Length(void) const;

  /* Resize string */
  void Resize(usize newSize) const;

private:
  void preset(const char *format, va_list args, bool newLine) const;

  /* Pointer-to-Implementation, so I can avoid having to include C++'s <string>
   * header inside of this file */
  class String_Impl;
#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
  String_Impl *_impl = nullptr; // Windows' DLL interface can be annoying
                                // sometimes when it comes to C++ types
#else
  std::unique_ptr<String_Impl> _impl;
#endif
};
} // namespace Pluto

#endif

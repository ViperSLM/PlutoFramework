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
  String class implementation
*/

#include "m_string.h"

#include <cstdarg>
#include <string>
#include <cstring>
#include <vector>

#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace Pluto {

/* String class implementation [Private] */
class String::String_Impl {
public:
  String_Impl(void) {}
  ~String_Impl(void) {
#if defined(_WIN32)
    if (_wideCharBuffer.get() != nullptr) {
      wideChar_free();
    }
#endif
  }

  void set(std::string in) { _str = in; }

  void append(std::string in) { _str += in; }

  const char* get(void) const {
    return _str.c_str();
  }

  const wchar_t *getUnicode(void) {
    /*_wStr = std::wstring(_str.begin(), _str.end());
    return _wStr.c_str();*/
    // Really only important on Windows
    #if defined(_WIN32)
    _wStr.clear();
    int size = MultiByteToWideChar(CP_UTF8, 0, _str.c_str(), -1, nullptr, 0);
    _wStr.resize(size - 1);
    MultiByteToWideChar(CP_UTF8, 0, _str.c_str(), -1, &_wStr[0], size);
    return _wStr.c_str();
    #else
    return L"Conversion not supported on platforms outside of Windows";
#endif
  }

  void clear(void) { _str.clear(); }

  usize length(void) { return std::strlen(_str.c_str()); }

  void resize(usize newSize) { _str.resize(static_cast<usize>(newSize)); }

  bool compare(std::string in, strcmp_t mode) const {
    switch (mode) {
    case PLUTO_STRCMP_EQUAL:
      if (in == _str) {
        return true;
      }
      return false;
      break;

    case PLUTO_STRCMP_NOT_EQUAL:
      if (in != _str) {
        return true;
      }
      return false;
      break;

    case PLUTO_STRCMP_LESS:
      if (in < _str) {
        return true;
      }
      return false;
      break;

    case PLUTO_STRCMP_GREAT:
      if (in > _str) {
        return true;
      }
      return false;
      break;

    case PLUTO_STRCMP_LESS_OR_EQUAL:
      if (in <= _str) {
        return true;
      }
      return false;
      break;

    case PLUTO_STRCMP_GREAT_OR_EQUAL:
      if (in >= _str) {
        return true;
      }
      return false;
      break;
    }
    // If the switch/case statement somehow fails, it'll return false
    return false;
  }

private:
  std::string _str;
  std::wstring _wStr;

#if defined(_WIN32)
  std::unique_ptr<std::vector<wchar_t>> _wideCharBuffer;

  void wideChar_free(void) { _wideCharBuffer.reset(); }
  void wideChar_alloc(void) {
    _wideCharBuffer = std::make_unique<std::vector<wchar_t>>();
  }
#endif
};

/* String class implementation [Public] */

#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
String::String(void) : _impl(new String_Impl()) {}
String::String(const char *format, ...) : _impl(new String_Impl()) {
  va_list args;
  va_start(args, format);
  preset(format, args, false);
  va_end(args);
}

String::~String(void) {
  delete _impl;
  _impl = nullptr;
}
#else
String::String(void) : _impl(PLUTO_PIMPL_CREATE<String_Impl>()) {}
String::String(const char *format, ...) : _impl(PLUTO_PIMPL_CREATE<String_Impl>()) {
  va_list args;
  va_start(args, format);
  preset(format, args, false);
  va_end(args);
}
String::~String(void) = default;
#endif

void String::preset(const char *format, va_list args, bool newLine) const {
  va_list args_copy;
  va_copy(args_copy, args);
  usize size = vsnprintf(nullptr, 0, format, args_copy);
  va_end(args_copy);

  // Buffer
  std::vector<char> buffer(size + 1);
  vsnprintf(buffer.data(), buffer.size(), format, args);

  // Remove null terminator
  buffer.pop_back();
  if (newLine) {
    buffer.push_back('\n');
  }
  _impl->set(std::string{buffer.begin(), buffer.end()});
}

void String::Set(const char *format, ...) const {
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);
  usize size = vsnprintf(nullptr, 0, format, args_copy);
  va_end(args_copy);

  std::vector<char> buffer(size + 1);
  vsnprintf(buffer.data(), buffer.size(), format, args);
  va_end(args);

  buffer.pop_back();
  _impl->set(std::string{buffer.begin(), buffer.end()});
}

void String::Append(const char* format, ...) const {
  va_list args;
  va_start(args, format);
  va_list args_copy;
  va_copy(args_copy, args);
  usize size = vsnprintf(nullptr, 0, format, args_copy);
  va_end(args_copy);

  std::vector<char> buffer(size + 1);
  vsnprintf(buffer.data(), buffer.size(), format, args);
  va_end(args);

  buffer.pop_back();
  _impl->append(std::string{buffer.begin(), buffer.end()});
}

void String::SetV(const char *format, va_list args, bool newLine) const {
  preset(format, args, newLine);
}

const char* String::Get(void) const { return _impl->get(); }
const wchar_t *String::Get_WideString(void) const { return _impl->getUnicode(); }



void String::Clear(void) const { _impl->clear(); }

bool String::Compare(const char *input, strcmp_t mode) const {
  return _impl->compare(input,mode);
}

bool String::Compare(String &input, strcmp_t mode) const {
  return _impl->compare(input.Get(), mode);
}

usize String::Length(void) const { return _impl->length(); }

void String::Resize(usize newSize) const { _impl->resize(newSize); }
}

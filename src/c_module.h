/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Base module class. New modules are built by deriving
  from this class and overriding the Start and Stop
  functions.
*/
#ifndef _PLUTO_C_MODULE_H_
#define _PLUTO_C_MODULE_H_
#include "c_api.h"
#include "c_intdef.h"
#include "m_string.h"

namespace Pluto {
class PLUTO_API Module {
public:
  inline Module(const char *name) : _name(name) {}
  virtual ~Module(void) = default;

  virtual void Start(void) = 0;
  virtual void Stop(void) = 0;

  // Get the name of the module. Returns as a const char array
  inline const char *GetName(void) const { return _name; }

  // Get the memory address of the module. Returns as a 'uptr' data type
  // (uintptr_t)
  inline uptr GetMemoryAddress() { return (uptr)this; }

private:
  const char *_name;
};
} // namespace Pluto
#endif

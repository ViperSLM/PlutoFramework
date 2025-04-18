/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Memory allocator module
*/
#ifndef _PLUTO_C_MEMORY_H_
#define _PLUTO_C_MEMORY_H_
#include "c_api.h"
#include "c_coreptr.h"
#include "c_intdef.h"
#include "c_module.h"

namespace Pluto {
class Memory : public Module {
public:
  inline Memory(void) : Module("Memory") {}

  // Ensure there is only once instance of this class
  Memory(const Memory &memory) = delete;
  Memory &operator=(const Memory &memory) = delete;

  void Start(void) override { modStart(); }
  void Stop(void) override { modStop(); }

  void ThreadInit(void);
  void ThreadStop(void);

  void *Allocate(usize size);
  void *ConAllocate(usize count, usize size);
  void *ReAllocate(void *ptr, usize size);
  void Free(void *ptr);

  void SetMemory(void *ptr, int value, usize numBytes);
  void CopyMemory(void *dest, const void *src, usize size);

private:
  void modStart(void);
  void modStop(void);
};
} // namespace Pluto

#endif

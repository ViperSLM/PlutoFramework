/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Memory allocator module implementation
*/
#include "mod_memory.h"
#include "rpmalloc.h"
#include <cstring>

namespace Pluto {

void Memory::modStart(void) { rpmalloc_initialize(); }
void Memory::modStop(void) { rpmalloc_finalize(); }
void Memory::ThreadInit(void) { rpmalloc_thread_initialize(); }
void Memory::ThreadStop(void) { rpmalloc_thread_finalize(0); }

void *Memory::Allocate(usize size) { return rpmalloc(size); }
void *Memory::ConAllocate(usize count, usize size) {
  return rpcalloc(count, size);
}
void *Memory::ReAllocate(void *ptr, usize size) { return rprealloc(ptr, size); }
void Memory::Free(void *ptr) { rpfree(ptr); }

void Memory::SetMemory(void *ptr, int value, usize numBytes) {
  memset(ptr, value, numBytes);
}
void Memory::CopyMemory(void *dest, const void *src, usize size) {
  memcpy(dest, src, size);
}
} // namespace Pluto

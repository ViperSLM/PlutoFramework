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

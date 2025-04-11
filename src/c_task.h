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
  Threaded task class for running things on separate CPU threads.
  Only the Process() function gets overridden, which is then
  taken care of by both the Start() and Stop() classes.
*/
#ifndef _PLUTO_C_TASK_H_
#define _PLUTO_C_TASK_H_
#include "c_api.h"
#include <memory>

namespace Pluto {
class PLUTO_API ThreadedTask {
public:
  ThreadedTask(void);
  virtual ~ThreadedTask(void);
  
  // Start the thread and call the process function
  void Start(void);
  
  // Stop the thread
  void Stop(void);

  void Request(void);

protected:
  virtual void Process(void) = 0;

private:
  class ThreadedTask_Impl;
#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
  ThreadedTask_Impl *_impl = nullptr;
#else
  PLUTO_PIMPL<ThreadedTask_Impl> _impl;
#endif
};
} // namespace Pluto

#endif

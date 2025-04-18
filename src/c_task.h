/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

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

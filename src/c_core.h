/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Framework class. Houses the module system implementation,
  as well as handling other core tasks.
*/
#ifndef _PLUTO_C_CORE_H_
#define _PLUTO_C_CORE_H_
#include "c_api.h"
#include "c_module.h"
#include "c_msgbox.h"

#include "m_string.h"

#include <cstdarg>
#include <memory>

namespace Pluto {
// Store command-line arguments of application
typedef struct {
  int *argc;
  char **argv;
} args_t;

class PLUTO_API Framework {
public:
  // Constructor and Destructor, respectively
  Framework(void);
  ~Framework(void);
  Framework(const Framework &framework) = delete;
  Framework &operator=(const Framework &framework) = delete;

  // Show message box (Depends on platform, see i_system.h for more info)
  int MessageBox(const char *title, String &msg, mboxflags_t flags, mboxbtns_t btns);

  // Parse command-line arguments
  void Parse(args_t &args);

  // Printing-related functions
  void Print(const char *format, va_list args, bool newLine = false);
  void Print(const char *format, ...);
  void PrintLn(const char *format, ...);

  // Throw exception (which is then caught by Application class)
  void ThrowException(String &msg);

  // Functions for setting quit flag to true,
  // and checking the state of said flag
  void InvokeQuit(void);
  bool QuitInvoked(void) const;

  // Wait for specified amount of milliseconds
  // [Also sleeps current thread]
  void Wait(int ms);

  // Store and get HInstance of program
  // [Windows-specific, does nothing on other platforms]
  void StoreWinHInstance(void *hInstance);
  void *GetWinHInstance(void) const;
  
  // Register module class into registry
  void RegisterModule(Module *modulePtr);

  // Unregister module from registry
  void UnregisterModule(uptr moduleAddr);

  // Start all registered modules. Note that
  // this is already run in the Application loop,
  // so no need to use this.
  void StartModules(void);

  // Stop all registered modules. This is already
  // done after the Cleanup() function.
  void StopAllModules(void);

  /*
    Search for a registered module and return a pointer
    to the found module, or nullptr if not found.
 
    For derived classes, wrap a dynamic cast around
    the function.
 
    Example (Memory allocator module):
    Memory *memAllocator = dynamic_cast<Memory*>(GetFramework()->GetModule("Memory"));
  */
  Module *GetModule(const char *modName) const;

private:
// Pointer-to-Implementation
  class Framework_Impl;
#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
  Framework_Impl *_impl = nullptr;
#else
  std::unique_ptr<Framework_Impl> _impl;
#endif
};

} // namespace Pluto

#endif

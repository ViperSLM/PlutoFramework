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

  // Get module by name. Returns pointer to the found module if a match was found.
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

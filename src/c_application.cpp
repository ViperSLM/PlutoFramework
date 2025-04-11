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
  Application base class implementation,
  and storage for Framework class instance.
*/
#include "c_application.h"
#include "c_core.h"

#include <memory>

namespace Pluto {
std::unique_ptr<Framework> appFramework;
Framework *GetFramework(void) { return appFramework.get(); }

// Instance of running app is stored here
Application *currentApp = nullptr;

Application::Application(void) {
  currentApp = this;
}

Framework *Application::GetRunningFramework(void) { return GetFramework(); }

void Application::Quit(void) {
  appFramework->InvokeQuit();
}

int Application::Run(int *argc, char **argv, void *winHInstance) {
  int returnCode = 0;
  args_t appArgs;
  appArgs.argc = argc;
  appArgs.argv = argv;

  // Create Framework instance
  appFramework = std::make_unique<Pluto::Framework>();
  appFramework->Parse(appArgs);

  try {
    Init();
    // Start all the registered modules
    appFramework->StartModules();
    PostInit();
    while(!appFramework->QuitInvoked()) {
      Update();
      if (appFramework->QuitInvoked())
        break;
      PreRender();
      Render();
        
      // Add 1 millisecond delay
      appFramework->Wait(1);
    }
  } catch(std::exception &ex) {
    GetFramework()->PrintLn("!!! An exception has occurred during runtime.\nException Info: %s", ex.what());

    // Exception message box
    String exMsg("An exception has occurred during runtime.\nException Info:\n%s", ex.what());
    GetFramework()->MessageBox("Exception Thrown", exMsg, PLUTO_MSGBOX_ERROR, PLUTO_MSGBOXBTN_OK);

    returnCode = -1;
  }
  Cleanup();
  appFramework->StopAllModules();
  allocator.reset();
  currentApp = nullptr;
  appFramework.reset();
  return returnCode;
}
}

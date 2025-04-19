/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Application base class implementation,
  and storage for Framework class instance.
*/
#include "c_application.h"

// Needed to get around DLL linking issues
#if defined(_WIN32) && !defined(_PLUTO_STATIC_BUILD_)
#include "c_coreptr.h"
#endif

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

// Framework *Application::GetRunningFramework(void) { return GetFramework(); }

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
  currentApp = nullptr;
  appFramework.reset();
  return returnCode;
}
}

/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Application base class. Starts the core framework instance
*/
#ifndef _PLUTO_C_APPLICATION_H
#define _PLUTO_C_APPLICATION_H
#include "c_api.h"
#include "c_core.h"

namespace Pluto {

class PLUTO_API Application {
public:
  Application(void);
  virtual ~Application(void) = default;

  //  Shouldn't be needed anymore
//  Framework *GetRunningFramework(void);
  
  // Run(): Run the application and parse command-line arguments.
  // Returns exit code.
  int Run(int *argc, char **argv, void *winHInstance = nullptr);
  
  // Invoke framework's quit function
  void Quit(void);


  /*
    Virtual functions
    [Override these in your app]

    The run cycle in order:
    Init() - Initialises necessary components
    PostInit() - Run functions after modules have loaded
    Loop:
      Update()    - Used for updating things before rendering (i.e. input)
      PreRender() - Preparatory rendering work (mainly used for GUIs)
      Render()    - Run functions that draw to the screen
    Repeat

    Cleanup()     - Clean up and de-allocate anything before exiting out
                    of the app.
  */
  virtual void Init(void) = 0;
  virtual void PostInit(void) = 0;
  virtual void Update(void) = 0;
  virtual void PreRender(void) = 0;
  virtual void Render(void) = 0;
  virtual void Cleanup(void) = 0;
private:
};

}

#endif

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

  Framework *GetRunningFramework(void);
  
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

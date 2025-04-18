/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  System-specific code for core functions and classes.
*/
#ifndef _PLUTO_I_SYSTEM_H_
#define _PLUTO_I_SYSTEM_H_
#include "c_api.h"
#include "c_intdef.h"
#include "c_msgbox.h"

// Forward declarations
namespace Pluto {
class String;
}

/* ---------------------------------- */
/* Framework */
/* ---------------------------------- */

// Initialise any system-specific tasks
// If not required, you can just stub this out
void I_Init(void);

// Same thing, but when exiting
void I_Exit(void);

// Get host operating system (output written to strIn)
void I_GetHost(Pluto::String *strIn);

// Log to system (i.e. printf for most systems, NSLog for macOS, etc.)
void I_SysLog(Pluto::String &str);

// Wait for specified amount of milliseconds
void I_Wait(int ms);

/* ---------------------------------- */
/* Message Box */
/* ---------------------------------- */
int I_MessageBox(const char *title, Pluto::String &msg, Pluto::mboxflags_t flags, Pluto::mboxbtns_t buttons);

#endif

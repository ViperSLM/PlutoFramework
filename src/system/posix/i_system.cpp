/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Implementation of core 'I_' functions,
  for UNIX, BSD, Linux, and other
  POSIX-compliant systems.
*/
#include "../../i_system.h"
#include "../../m_string.h"

#include <unistd.h>
#include <sys/utsname.h>

/* ---------------------------------- */
/* Framework */
/* ---------------------------------- */

void I_GetHost(Pluto::String *strIn) {
  struct utsname uts;
  uname(&uts);
  strIn->Set("%s %s %s", uts.sysname, uts.release, uts.machine);
}

/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Implementation for 'I_Wait' for
  POSIX-compliant systems.
*/
#include "../../i_system.h"

#include <unistd.h>

// Wait for specified amount of milliseconds
void I_Wait(int ms) { usleep(ms * 1000); }

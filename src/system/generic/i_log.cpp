/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Generic implementation for misc functions
*/
#include "../../i_system.h"
#include "../../m_string.h"
#include <cstdio>

void I_SysLog(Pluto::String &str) {
  printf("%s", str.Get());
}


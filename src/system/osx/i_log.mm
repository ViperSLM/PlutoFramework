/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Implementation of I_SysLog,
  for macOS/iOS hosts.
*/
#if defined(__APPLE__)
#include "../../i_system.h"
#include "../../m_string.h"
#import <Foundation/Foundation.h>

void I_SysLog(Pluto::String &str) {
  Pluto::String strCache("\n%s", str.Get());
  NSLog(@"%s", strCache.Get());
}
#endif

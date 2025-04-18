/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Implementation of core 'I_' functions,
  for macOS/iOS hosts using the Cocoa API.
*/
#include "../../i_system.h"
#include "../../m_string.h"

#import <Cocoa/Cocoa.h>
#include <sys/utsname.h>

void I_GetHost(Pluto::String *strIn) {
  NSProcessInfo *processInfo = [NSProcessInfo processInfo];
  NSOperatingSystemVersion nsVer = [processInfo operatingSystemVersion];

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
  strIn->Set("iOS");
#elif TARGET_OS_MACCATALYST
  strIn->Set("iOS [macOS Catalyst]");
#elif TARGET_OS_TV
  strIn->Set("tvOS");
#elif TARGET_OS_WATCH
  strIn->Set("watchOS");
#elif TARGET_OS_OSX
  strIn->Set("macOS");
#else
  strIn->Set("Unknown Apple OS");
#endif
  strIn->Append(" v%d.%d.%d", nsVer.majorVersion, nsVer.minorVersion,
                nsVer.patchVersion);

  // Get Darwin version
  struct utsname uts;
  uname(&uts);
  strIn->Append(" [%s %s %s]", uts.sysname, uts.release, uts.machine);
}

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

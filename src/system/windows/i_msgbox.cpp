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
  I_MessageBox implementation, based on Windows API.
*/
#include "../../i_system.h"
#include "../../m_string.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int I_MessageBox(const char *title, Pluto::String &msg,
                 Pluto::mboxflags_t flags, Pluto::mboxbtns_t buttons) {
  UINT msgFlags = 0;
  switch (flags) {
  case Pluto::PLUTO_MSGBOX_ERROR:
    msgFlags |= MB_ICONERROR;
    break;

  case Pluto::PLUTO_MSGBOX_WARNING:
    msgFlags |= MB_ICONWARNING;
    break;

  default:
    msgFlags |= MB_ICONINFORMATION;
  }

  switch (buttons) {
  case Pluto::PLUTO_MSGBOXBTN_OK_CANCEL:
    msgFlags |= MB_OKCANCEL;
    break;

  default:
    msgFlags |= MB_OK;
  }
  Pluto::String titleStr("%s", title);
  int result = MessageBoxA(nullptr, msg.Get(),
                          titleStr.Get(), msgFlags);

  return result;
}

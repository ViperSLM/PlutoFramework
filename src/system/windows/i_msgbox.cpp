/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

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

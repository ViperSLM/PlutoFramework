/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Implementation of core 'I_' functions,
  for Windows hosts
*/
#include "../../i_system.h"
#include "../../m_string.h"

#include <windows.h>

typedef LONG NTSTATUS, *PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)
typedef NTSTATUS(WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

void I_GetHost(Pluto::String *strIn) {
  HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
  if (hMod) {
    RtlGetVersionPtr fxPtr =
        (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");

    if (fxPtr != nullptr) {
      RTL_OSVERSIONINFOW rovi = {0};
      rovi.dwOSVersionInfoSize = sizeof(rovi);
      if (STATUS_SUCCESS == fxPtr(&rovi)) {
        strIn->Set("Windows %d.%d.%d", rovi.dwMajorVersion, rovi.dwMinorVersion,
                   rovi.dwBuildNumber);
        return;
      }
    }
  }
  strIn->Set("Windows (Unknown Version)");
}

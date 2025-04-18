/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Entry-point wrappers
*/
#ifndef _PLUTO_C_MAIN_H_ // Include guard
#define _PLUTO_C_MAIN_H_

// Windows GUI subsystem (WinMain)
#if defined(_WIN32) && defined(_PLUTO_WINMAIN_)
#include <windows.h>
#define PLUTO_MAIN int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
#else

// Traditional main function
#define PLUTO_MAIN int main(int argc, char** argv)

#endif
#endif // Include guard

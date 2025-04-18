/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Generic implementation for 'I_Wait' using
  the C++ standard library.
*/
#include "../../i_system.h"

#include <chrono>
#include <thread>

// Wait for specified amount of milliseconds
void I_Wait(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

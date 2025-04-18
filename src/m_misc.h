/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Miscellaneous functions. 'Nuff said
*/
#ifndef _PLUTO_M_MISC_H_
#define _PLUTO_M_MISC_H_

namespace Pluto {
// Return 'true' if host is Little Endian, false if Big Endian.
inline bool LittleEndian(void) {
    int n = 1;
    if(*(char*)&n == 1)
        return true;
    return false;
}
}

#endif

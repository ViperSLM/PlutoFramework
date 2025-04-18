/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  GetFramework() pointer function which points
  to the Framework instance created by the
  Application class. For use outside of the Application
  class.
*/
#ifndef _PLUTO_C_COREPTR_H_
#define _PLUTO_C_COREPTR_H_
#include "c_api.h"
#include "c_core.h"

namespace Pluto {
PLUTO_API_EXTERN PLUTO_API Framework *GetFramework(void);
}

#endif

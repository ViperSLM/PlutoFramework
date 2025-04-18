/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Message box flags
  (Actual MsgBox function is in Framework class)
*/
#ifndef _PLUTO_C_MSGBOX_H_
#define _PLUTO_C_MSGBOX_H_
namespace Pluto {
typedef enum {
  PLUTO_MSGBOX_ERROR,
  PLUTO_MSGBOX_WARNING,
  PLUTO_MSGBOX_INFORMATION
} mboxflags_t;

typedef enum {
  PLUTO_MSGBOXBTN_OK,
  PLUTO_MSGBOXBTN_OK_CANCEL
} mboxbtns_t;
}
#endif

/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  I_MessageBox implementation, based on macOS's Cocoa API.
*/
#include "../../i_system.h"
#include "../../m_string.h"

#import <Cocoa/Cocoa.h>

int I_MessageBox(const char *title, Pluto::String &msg,
                 Pluto::mboxflags_t flags, Pluto::mboxbtns_t buttons) {
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:msg.Get()]];

    switch (flags) {
    case Pluto::PLUTO_MSGBOX_ERROR:
      [alert setIcon:[NSImage imageNamed:NSImageNameCaution]];
      [alert setAlertStyle:NSAlertStyleCritical];
      break;
    case Pluto::PLUTO_MSGBOX_WARNING:
      [alert setIcon:[NSImage imageNamed:NSImageNameCaution]];
      [alert setAlertStyle:NSAlertStyleWarning];
      break;
    default: // Info (Default)
      [alert setIcon:[NSImage imageNamed:NSImageNameInfo]];
      [alert setAlertStyle:NSAlertStyleInformational];
    }

    // Just an 'OK' button for now
    [alert addButtonWithTitle:@"OK"];

    [alert.window setLevel:NSStatusWindowLevel];
    [alert.window makeKeyAndOrderFront:nil];
    [alert runModal];
    [alert release];
  return 0;
}

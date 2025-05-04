/*
  Pluto Framework
  Copyright (C) 2025 ViperSLM

  This project is licensed under the terms of the 
  BSD-3-Clause license. Check the LICENSE file 
  for more info.

  DESCRIPTION:
  Framework class implementation
*/
#include "c_core.h"

#include <stdexcept>
#include <vector>

/* Forward declarations */
extern void I_SysLog(Pluto::String &str);
extern void I_GetHost(Pluto::String *strIn);
extern int I_MessageBox(const char *title, Pluto::String &msg,
                        Pluto::mboxflags_t flags, Pluto::mboxbtns_t buttons);
extern void I_Wait(int ms);

namespace Pluto {
/* ---------------------------------- */
/* Private Implementation */
/* ---------------------------------- */
class Framework::Framework_Impl {
public:
  // Module pointer is paired together with a unique ID on creation
  typedef struct {
    Module *module;
    bool registered; // Used for a neat efficiency trick
    bool started; // Has the module started? Only done with registered modules
  } module_t;

public:
  Framework_Impl(void) {
    _consoleLog.Clear();
    // String initInfo;
    I_GetHost(&_hostInfo);
    getCompilerInfo();
#if defined(_PLUTO_GIT_HASH_)
// If there's a commit hash, use that instead
    printInternal("Pluto Framework (%s)\nHost: %s\nCompiled with "
    		  "%s\nBuild Timestamp: %s, %s\n\n", _PLUTO_GIT_HASH_,
		  _hostInfo.Get(), _compilerInfo.Get(), __DATE__, __TIME__);
#else
    printInternal("Pluto Framework v%d.%d.%d\nHost: %s\nCompiled with "
                  "%s\nBuild Timestamp: %s, %s\n\n",
                  _PLUTO_VERSION_MAJOR_, _PLUTO_VERSION_MINOR_,
                  _PLUTO_VERSION_PATCH_, _hostInfo.Get(), _compilerInfo.Get(),
                  __DATE__, __TIME__);
#endif
  }
  ~Framework_Impl(void) {
    // De-initialise and unregister all modules from registry
    // Essentially garbage collection
    _modRegistry.clear();
  }

  int msgbox(const char *title, String &msg, mboxflags_t flags,
             mboxbtns_t btns) {
    return I_MessageBox(title, msg, flags, btns);
  }

  void parse(args_t &args) {
    _args.argc = args.argc;
    _args.argv = args.argv;
  }

  void print(const char *format, va_list args, bool newLine) {
    String printStr;
    printStr.SetV(format, args);
    // Append new line if related bool is true
    if (newLine)
      printStr.Append("\n");

    // TODO: System log string
    I_SysLog(printStr);
  }
  void printInternal(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print(format, args, false);
    va_end(args);
  }

  void throwEx(String &msg) {
    String msgPrefix("%s", msg.Get());
    throw std::runtime_error(msgPrefix.Get());
  }

  void invokeQuit(void) { _quit = true; }
  bool quitInvoked(void) const { return _quit; }

  void wait(int ms) { I_Wait(ms); }

  void registerModule(Module *mod) {
    // No more than 1 module can have the exact same name.
    // The check below enforces this to prevent potential
    // search complications and bugs.
    if (!_modRegistry.empty()) {
      String nameQuery("%s", mod->GetName());
      for (module_t &module : _modRegistry) {
        if (module.registered &&
            nameQuery.Compare(module.module->GetName(), PLUTO_STRCMP_EQUAL)) {
          // Got a match? Cancel registration. 'Nuff said
          printInternal("!! ERROR: Cannot register module with name: %s\n"
                        "No more than 1 module can have the exact same name.",
                        nameQuery.Get());
          return;
        }
      }
    }

   
    // Before creating a new module object, look for an unused entry in registry
    module_t *unusedModule = nullptr;
    for (module_t module : _modRegistry) {
      if (!module.registered) { // Found an unused entry!
        unusedModule = &module;
        break;
      }
    }
    

    // If an unused entry was found during the loop, use that instead of
    // creating a new entry whilst also re-using the module ID (probably a bad
    // idea)
    if (unusedModule != nullptr) {
      unusedModule->module = mod;
      unusedModule->registered = true;
      unusedModule->started = false;
      return;
    }
    
    // The new module ID, pointer, and the registered flag are defined
    module_t newModule{mod, true, false};
    _modRegistry.push_back(newModule);
  }

  void startRegisteredModules(void) {
    if (_modRegistry.empty()) {
      printInternal(
          "! Framework::StartModules: No modules registered. Ignoring.\n");
      return;
    }

    // Call the 'Start()' function in each module
    int count = 0;

    for (auto mod = _modRegistry.begin(); mod != _modRegistry.end(); mod++) {
      printInternal("Framework::StartModules: Starting %s module\n",
                    mod->module->GetName());
      startModule(mod->module->GetMemoryAddress());
      count++;
    }

    printInternal("Framework::StartModules: Started %d registered modules\n",
                  count);
  }

  void stopAllModules(void) {
    for (auto module = _modRegistry.rbegin(); module != _modRegistry.rend();
         module++) {
      printInternal("Framework::StopAllModules: Stopping %s module\n",
                    module->module->GetName());
      stopModuleIfStarted(module->module->GetMemoryAddress());
    }
  }

  void unregisterModule(uptr modAddr) {
    bool found = false;
    for (auto module = _modRegistry.begin(); module != _modRegistry.end();
         module++) {
      if (modAddr == module->module->GetMemoryAddress()) {
        found = true;

        // Stop the module first before unregistering
        // Rather than just erasing the entry from the registry,
        // The module pointer is de-initialised and the 'registered'
        // flag set to false so that the entry can be re-used.
        stopModuleIfStarted(modAddr);
        module->module = nullptr;
        module->registered = false;
        break;
      }
    }

    if (!found) {
#if defined(_PLUTO_64BIT_)
      printInternal("! Framework::UnregisterModule: Could not unregister "
                    "module with memory address 0x%16x",
                    modAddr);
#else
      printInternal("! Framework::UnregisterModule: Could not unregister "
                    "module with memory address 0x%08x",
                    modAddr);
#endif
    }
  }

  Module *getModule(const char *modName) {
    String query("%s", modName);
    Module *match = nullptr;
    for (auto mod = _modRegistry.rbegin(); mod != _modRegistry.rend(); mod++) {
      if (query.Compare(mod->module->GetName(), PLUTO_STRCMP_EQUAL)) {
        // Break out of for loop if we got a match
        match = mod->module;
      }
    }
    return match;
  }

  void startModule(uptr modAddr) {
    module_t *mod = findModuleWithAddr(modAddr);
    if (mod != nullptr) {
      if (!mod->started) {
        mod->module->Start();
        mod->started = true;
      }
    }
  }

  void storeWinHInstance(void *hInstance) { _winHInstance = hInstance; }
  void *getWinHInstance(void) { return _winHInstance; }

private:
  args_t _args;
  bool _quit = false;
  String _hostInfo;
  String _compilerInfo;
  String _consoleLog;

  std::vector<u64> _unusedModIDs;

  std::vector<module_t> _modRegistry;

  //  std::vector<module_t> _modRegistry;

  // Windows hInstance
  void *_winHInstance = nullptr;

  void getCompilerInfo(void) {
    String mingwCheck;
#if defined(__MINGW32__) || defined(__MINGW64__)
    mingwCheck.Set("[mingw-w64]");
#endif

// Clang
#if defined(__clang__)
    _compilerInfo.Set("Clang v%d.%d.%d %s", __clang_major__, __clang_minor__,
                      __clang_patchlevel__, mingwCheck.Get());
#elif defined(__GNUC__)
    _compilerInfo.Set("GCC v%d.%d.%d %s", __GNUC__, __GNUC_MINOR__,
                      __GNUC_PATCHLEVEL__, mingwCheck.Get());
#elif defined(_MSC_VER)
    const int msvc_major = _MSC_FULL_VER / 10000000;
    const int msvc_minor = (_MSC_FULL_VER / 100000) % 100;
    const int msvc_patch = _MSC_FULL_VER % 100000;
    _compilerInfo.Set("MSVC v%d.%d.%d", msvc_major, msvc_minor, msvc_patch);
#else
    _compilerInfo.Set("Unknown or unsupported compiler");
#endif
  }

  module_t *findModuleWithAddr(uptr modAddr) {
    for (module_t &mod : _modRegistry) {
      if (modAddr == mod.module->GetMemoryAddress())
        return &mod;
    }
    return nullptr;
  }

  void stopModuleIfStarted(uptr modAddr) {
    module_t *mod = findModuleWithAddr(modAddr);
    if (mod != nullptr) {
      if (mod->started) {
        mod->module->Stop();
        mod->started = false;
      }
    }
  }
};

/* ---------------------------------- */
/* Public Implementation */
/* ---------------------------------- */
#if defined(_WIN32) && !defined(PLUTO_STATIC_BUILD)
Framework::Framework(void) : _impl(new Framework_Impl()) {}
Framework::~Framework(void) {
  delete _impl;
  _impl = nullptr;
}
#else
Framework::Framework(void) : _impl(std::make_unique<Framework_Impl>()) {}
Framework::~Framework(void) = default;
#endif

int Framework::MessageBox(const char *title, String &msg, mboxflags_t flags,
                          mboxbtns_t btns) {
  return _impl->msgbox(title, msg, flags, btns);
}
void Framework::Parse(args_t &args) { _impl->parse(args); }
void Framework::Print(const char *format, va_list args, bool newLine) {
  _impl->print(format, args, newLine);
}
void Framework::Print(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _impl->print(format, args, false);
  va_end(args);
}
void Framework::PrintLn(const char *format, ...) {
  va_list args;
  va_start(args, format);
  _impl->print(format, args, true);
  va_end(args);
}
void Framework::ThrowException(String &msg) { _impl->throwEx(msg); }
void Framework::InvokeQuit(void) { _impl->invokeQuit(); }
bool Framework::QuitInvoked(void) const { return _impl->quitInvoked(); }
void Framework::Wait(int ms) { _impl->wait(ms); }

void Framework::StoreWinHInstance(void *hInstance) {
  _impl->storeWinHInstance(hInstance);
}
void *Framework::GetWinHInstance(void) const {
  return _impl->getWinHInstance();
}

void Framework::RegisterModule(Module *modulePtr) {
  _impl->registerModule(modulePtr);
}
void Framework::RegisterAndStartModule(Module *modulePtr) {
  _impl->registerModule(modulePtr);
  _impl->startModule(modulePtr->GetMemoryAddress());
}
void Framework::UnregisterModule(uptr moduleAddr) {
  _impl->unregisterModule(moduleAddr);
}
Module *Framework::GetModule(const char *modName) const {
  return _impl->getModule(modName);
}
void Framework::StartModules(void) { _impl->startRegisteredModules(); }
void Framework::StopAllModules(void) { _impl->stopAllModules(); }

/* ---------------------------------- */
/* Internal Functions */
/* ---------------------------------- */
void C_Print(Framework *frmPtr, const char *format, ...) {
  va_list args;
  va_start(args, format);
  frmPtr->Print(format, args);
  va_end(args);
}
void C_Throw(Framework *frmPtr, const char *format, ...) {
  String msg;
  va_list args;
  va_start(args, format);
  msg.SetV(format, args, true);
  va_end(args);
  frmPtr->ThrowException(msg);
}
} // namespace Pluto

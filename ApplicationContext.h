#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "controllers/MainWindowController.h"
#include "controllers/VmController.h"

class ApplicationContext {
public:
  void setMainWindowController(MainWindowController *controller);
  void setVmController(VmController *controller);

  MainWindowController *mainWindowController();
  VmController *vmController();

private:
  MainWindowController *mainWindowController_ = nullptr;
  VmController *vmController_ = nullptr;
};

#endif // APPLICATIONCONTEXT_H

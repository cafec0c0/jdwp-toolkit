#include "ApplicationContext.h"

void ApplicationContext::setMainWindowController(MainWindowController *controller) {
    this->mainWindowController_ = controller;
}

void ApplicationContext::setVmController(VmController *controller) {
    this->vmController_ = controller;
}

MainWindowController *ApplicationContext::mainWindowController() {
    return this->mainWindowController_;
}

VmController * ApplicationContext::vmController() {
    return this->vmController_;
}

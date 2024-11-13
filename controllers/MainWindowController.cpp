#include "MainWindowController.h"

#include "ui/dialog/NewConnectionDialog.h"

void MainWindowController::exit() { emit exited(); }

void MainWindowController::about() { emit showAbout(); }

#include "ToolBar.h"

#include "MainWindow.h"
#include "ui/dialog/CommandPanel.h"

ToolBar::ToolBar(ApplicationContext *ctx) : ctx(ctx) {
  newConnectionDialog = new NewConnectionDialog(ctx, topLevelWidget());

  setFloatable(false);
  setMovable(false);

  connectAction = addAction("Connect", newConnectionDialog,
                            &NewConnectionDialog::resetAndShow);
  disconnectAction = addAction("Disconnect", ctx->vmController(),
                               &VmController::removeConnection);
  disconnectAction->setEnabled(false);

  addSeparator();

  // newPanelAction = addAction("New Panel", this, &ToolBar::newPanel);

  connect(ctx->vmController(), &VmController::connectionAdded, this,
          &ToolBar::connectionAdded);
  connect(ctx->vmController(), &VmController::connectionRemoved, this,
          &ToolBar::connectionRemoved);
}
void ToolBar::connectionAdded(Connection *connection) {
  connectAction->setEnabled(false);
  disconnectAction->setEnabled(true);
}

void ToolBar::connectionRemoved() {
  connectAction->setEnabled(true);
  disconnectAction->setEnabled(false);
}
void ToolBar::newPanel() {
  CommandPanel *d = new CommandPanel(ctx, topLevelWidget());
  d->show();
}

void ToolBar::showVmCommands() {}

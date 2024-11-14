#include "MainWindow.h"

#include "TabsPlaceholder.h"
#include "model/Connection.h"

#include <QStatusBar>
#include <QVBoxLayout>

#include "ui/dialog/AboutDialog.h"

MainWindow::MainWindow(ApplicationContext *context)
    : ctx(context), toolbar(ToolBar(ctx)), menuBar(MenuBar(ctx)) {
  this->stack = new QStackedWidget();
  this->statusBar = new QStatusBar();

  this->stack->insertWidget(1, new CommandPanel(ctx));
  this->stack->setDisabled(true);

  setWindowTitle("Not Connected");
  statusBar->showMessage("Not connected");
  connectSignals();

  setMenuBar(&menuBar);
  addToolBar(&toolbar);
  setStatusBar(statusBar);
  resize(800, 500);

  setCentralWidget(this->stack);
}

void MainWindow::connectSignals() {
  connect(ctx->mainWindowController(), &MainWindowController::exited, this,
          &MainWindow::close);
  connect(ctx->mainWindowController(), &MainWindowController::showAbout, this,
          &MainWindow::showAbout);
  connect(ctx->vmController(), &VmController::connectionAdded, this,
          &MainWindow::setCurrentConnection);
  connect(ctx->vmController(), &VmController::connectionRemoved, this,
          &MainWindow::removeCurrentConnection);
}

void MainWindow::showAbout() {
  AboutDialog *aboutDialog = new AboutDialog(ctx, topLevelWidget());
  aboutDialog->show();
}
void MainWindow::setCurrentConnection(Connection *connection) {
  QString connectedText = QString("Connected (%1:%2)")
                              .arg(connection->host())
                              .arg(connection->port());
  setWindowTitle(connectedText);
  statusBar->showMessage(connectedText);
  this->stack->setDisabled(false);
}
void MainWindow::removeCurrentConnection() {
  setWindowTitle("Not Connected");
  statusBar->showMessage("Not connected");
  stack->setCurrentIndex(0);
  this->stack->setDisabled(true);
}

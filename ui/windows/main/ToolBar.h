#ifndef TOOLBAR_H
#define TOOLBAR_H
#include <QTabWidget>
#include <QToolBar>
#include <QWidget>

#include "ApplicationContext.h"
#include "ui/dialog/NewConnectionDialog.h"

class ToolBar : public QToolBar {
  Q_OBJECT
public:
  explicit ToolBar(ApplicationContext *ctx);

private slots:
  void connectionAdded(Connection *connection);
  void connectionRemoved();
  void newPanel();

private:
  void showVmCommands();

  QAction *connectAction;
  QAction *disconnectAction;
  QAction *newPanelAction;

  ApplicationContext *ctx;

  NewConnectionDialog *newConnectionDialog;
};

#endif // TOOLBAR_H

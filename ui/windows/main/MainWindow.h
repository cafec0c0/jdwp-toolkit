#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <QPushButton>

#include "ApplicationContext.h"
#include "MenuBar.h"
#include "ToolBar.h"
#include "ui/dialog/CommandPanel.h"

#include <QStackedWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(ApplicationContext *context);

private slots:
  void connectSignals();
  void showAbout();
  void setCurrentConnection(Connection *connection);
  void removeCurrentConnection();

private:
  ApplicationContext *ctx;
  MenuBar menuBar;
  ToolBar toolbar;
  QStackedWidget *stack;
  QStatusBar *statusBar;
  CommandPanel *mainPanel;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

class MainWindowController : public QObject {
  Q_OBJECT

public slots:
  void exit();
  void about();

signals:
  void exited();
  void showAbout();
};

#endif // MAINWINDOWCONTROLLER_H

#include <QApplication>

#include "ui/windows/main/MainWindow.h"

#include <QStyle>
#include <QStyleFactory>

ApplicationContext *createAppContext() {
  auto *ctx = new ApplicationContext();
  ctx->setMainWindowController(new MainWindowController());
  ctx->setVmController(new VmController());
  return ctx;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setApplicationDisplayName("JDWP Toolkit");

  ApplicationContext *ctx = createAppContext();

  MainWindow window(ctx);
  window.show();

  return QApplication::exec();
}

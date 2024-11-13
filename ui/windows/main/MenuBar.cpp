#include "MenuBar.h"

#include <QMessageBox>

MenuBar::MenuBar(ApplicationContext *ctx) : ctx(ctx) {
    auto *controller = ctx->mainWindowController();

    QMenu *fileMenu = new QMenu("File");
    QMenu *helpMenu = new QMenu("Help");

    QAction *fileExitAction = fileMenu->addAction("Exit");
    QAction *helpAboutAction = helpMenu->addAction("About");

    connect(fileExitAction, &QAction::triggered, controller, &MainWindowController::exit);
    connect(helpAboutAction, &QAction::triggered, controller, &MainWindowController::about);

    addMenu(fileMenu);
    addMenu(helpMenu);
}

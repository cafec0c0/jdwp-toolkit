#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>

#include "ApplicationContext.h"


class MenuBar : public QMenuBar {
public:
    explicit MenuBar(ApplicationContext *ctx);

private:
    ApplicationContext *ctx;
};



#endif //MENUBAR_H

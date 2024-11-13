#ifndef VMINDEXPANEL_H
#define VMINDEXPANEL_H
#include "ApplicationContext.h"

#include <QVBoxLayout>
#include <QWidget>

class VmIndexPanel : public QWidget {
  Q_OBJECT
public:
  explicit VmIndexPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

signals:
  void navigateToIndex(int index);

private:
  ApplicationContext *ctx;
  QVBoxLayout *layout;
};

#endif // VMINDEXPANEL_H

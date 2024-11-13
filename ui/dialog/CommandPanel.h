#ifndef NEWPANELDIALOG_H
#define NEWPANELDIALOG_H
#include "ApplicationContext.h"
#include "ui/panels/vm/VmIndexPanel.h"
#include "ui/panels/vm/VmVersionPanel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QTreeWidget>

class CommandPanel : public QWidget {
  Q_OBJECT

public:
  explicit CommandPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void navigateToVmCommand(int index);

private:
  void setupTree();
  void setupVmCommands();

  ApplicationContext *ctx;
  QTreeWidget *commandTree;
  QHBoxLayout *layout;
  QLabel *label;
  QStackedWidget *stack;

  // Map commands to their respective tree item and widget
  QMap<int, QPair<QTreeWidgetItem *, QWidget *>> vmItems;
};

#endif // NEWPANELDIALOG_H

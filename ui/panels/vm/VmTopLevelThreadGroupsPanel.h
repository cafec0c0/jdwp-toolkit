#ifndef VMTOPLEVELTHREADGROUPS_H
#define VMTOPLEVELTHREADGROUPS_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>

class VmTopLevelThreadGroupsPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmTopLevelThreadGroupsPanel(ApplicationContext *ctx,
                                       QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;
  QTableWidget *threadsTree;

  ApplicationContext *ctx;
};

#endif // VMTOPLEVELTHREADGROUPS_H

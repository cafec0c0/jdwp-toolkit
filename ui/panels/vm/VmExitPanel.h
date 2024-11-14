#ifndef VMEXITPANEL_H
#define VMEXITPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmExitPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmExitPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;
  QLineEdit *exitCodeEdit;
  QLabel *noErrorLabel;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMEXITPANEL_H

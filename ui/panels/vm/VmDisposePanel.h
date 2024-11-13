#ifndef VMDISPOSEPANEL_H
#define VMDISPOSEPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmDisposePanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmDisposePanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;
  QLabel *noOutputLabel;
  QLabel *noErrorLabel;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMDISPOSEPANEL_H

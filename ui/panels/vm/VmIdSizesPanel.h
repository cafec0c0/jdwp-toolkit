#ifndef VMIDSIZESPANEL_H
#define VMIDSIZESPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmIdSizesPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmIdSizesPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;

  QLineEdit *fieldIdSizeLabel;
  QLineEdit *methodIdSizeLabel;
  QLineEdit *objectIdSizeLabel;
  QLineEdit *referenceTypeIdSize;
  QLineEdit *frameIdSize;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMIDSIZESPANEL_H

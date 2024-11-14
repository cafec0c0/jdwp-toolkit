#ifndef VMCAPABILITIES_H
#define VMCAPABILITIES_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class VmCapabilitiesPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmCapabilitiesPanel(ApplicationContext *ctx,
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

  QHBoxLayout *hbox;
  QFormLayout *leftLayout;
  QFormLayout *rightLayout;

  QCheckBox *canWatchFieldModificationCheck;
  QCheckBox *canWatchFieldAccessCheck;
  QCheckBox *canGetBytecodesCheck;
  QCheckBox *canGetSyntheticAttributeCheck;
  QCheckBox *canGetOwnedMonitorInfoCheck;
  QCheckBox *canGetCurrentContendedMonitorCheck;
  QCheckBox *canGetMonitorInfoCheck;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMCAPABILITIES_H

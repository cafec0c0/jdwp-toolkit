#ifndef VMVERSIONPANEL_H
#define VMVERSIONPANEL_H
#include "ApplicationContext.h"

#include <QDialog>

#include "jdwp.h"
#include "ui/dialog/AboutDialog.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class VmVersionPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmVersionPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;

  QTextEdit *descriptionArea;
  QLineEdit *majorVersionLabel;
  QLineEdit *minorVersionLabel;
  QLineEdit *vmVersionLabel;
  QLineEdit *vmNameLabel;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMVERSIONPANEL_H

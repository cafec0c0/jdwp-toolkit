#ifndef VMCREATESTRINGPANEL_H
#define VMCREATESTRINGPANEL_H
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

class VmCreateStringPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmCreateStringPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;

  QLineEdit *utfEdit;
  QLineEdit *stringObjectEdit;

  ApplicationContext *ctx;
  JdwpVirtualMachineCreateStringData *versionData = nullptr;
};

#endif // VMCREATESTRINGPANEL_H

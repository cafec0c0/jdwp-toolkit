#ifndef VMCLASSESBYSIGNATUREL_H
#define VMCLASSESBYSIGNATUREL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class VmClassesBySignaturePanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmClassesBySignaturePanel(ApplicationContext *ctx,
                                     QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLineEdit *signatureEdit;

  QTableWidget *classesTree;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMCLASSESBYSIGNATUREL_H

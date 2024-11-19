#ifndef VMCLASSESBYSIGNATUREL_H
#define VMCLASSESBYSIGNATUREL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>

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
};

#endif // VMCLASSESBYSIGNATUREL_H

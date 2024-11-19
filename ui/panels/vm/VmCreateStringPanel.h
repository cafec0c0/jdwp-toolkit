#ifndef VMCREATESTRINGPANEL_H
#define VMCREATESTRINGPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmCreateStringPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmCreateStringPanel(ApplicationContext *ctx,
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

  QLineEdit *utfEdit;
  QLineEdit *stringObjectEdit;

  ApplicationContext *ctx;
};

#endif // VMCREATESTRINGPANEL_H

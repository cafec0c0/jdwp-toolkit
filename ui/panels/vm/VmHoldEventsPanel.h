#ifndef VMHOLDEVENTSPANEL_H
#define VMHOLDEVENTSPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmHoldEventsPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmHoldEventsPanel(ApplicationContext *ctx,
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
  QLabel *noOutputLabel;
  QLabel *noErrorLabel;

  ApplicationContext *ctx;
};

#endif // VMHOLDEVENTSPANEL_H

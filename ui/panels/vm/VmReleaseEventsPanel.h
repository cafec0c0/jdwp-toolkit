#ifndef VMRELEASEEVENTSPANEL_H
#define VMRELEASEEVENTSPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class VmReleaseEventsPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmReleaseEventsPanel(ApplicationContext *ctx,
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

#endif // VMRELEASEEVENTSPANEL_H

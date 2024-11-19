#ifndef VMVERSIONPANEL_H
#define VMVERSIONPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

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
};

#endif // VMVERSIONPANEL_H

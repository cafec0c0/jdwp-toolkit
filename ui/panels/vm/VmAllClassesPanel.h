#ifndef VMALLCLASSES_H
#define VMALLCLASSES_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>

class VmAllClassesPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmAllClassesPanel(ApplicationContext *ctx,
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
  QTableWidget *classesTree;

  ApplicationContext *ctx;
};

#endif // VMALLCLASSES_H

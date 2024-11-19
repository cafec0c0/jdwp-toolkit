#ifndef VMCAPABILITIESNEW_H
#define VMCAPABILITIESNEW_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class VmCapabilitiesNewPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmCapabilitiesNewPanel(ApplicationContext *ctx,
                                  QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();
  void setupTable();
  void insertValue(int row, bool value);

  QLabel *noArgsLabel;

  QHBoxLayout *hbox;
  QFormLayout *leftLayout;
  QFormLayout *rightLayout;

  QTableWidget *capabilitiesTable;

  ApplicationContext *ctx;
};

#endif // VMCAPABILITIESNEW_H

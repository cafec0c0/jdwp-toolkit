#ifndef VMALLTHREADS_H
#define VMALLTHREADS_H
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

class VmAllThreadsPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmAllThreadsPanel(ApplicationContext *ctx,
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
  QTableWidget *threadsTree;

  ApplicationContext *ctx;
  JdwpVirtualMachineVersionData *versionData = nullptr;
};

#endif // VMALLTHREADS_H

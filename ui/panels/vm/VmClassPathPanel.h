#ifndef VMCLASSPATH_H
#define VMCLASSPATH_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>

class VmClassPathPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmClassPathPanel(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QLabel *noArgsLabel;
  QLineEdit *baseDirEdit;
  QTableWidget *classPathsTree;
  QTableWidget *bootClassPathsTree;

  ApplicationContext *ctx;
};

#endif // VMCLASSPATH_H

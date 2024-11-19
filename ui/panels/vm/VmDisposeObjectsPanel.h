#ifndef VMDISPOSEOBJECTSPANEL_H
#define VMDISPOSEOBJECTSPANEL_H
#include "ApplicationContext.h"

#include "jdwp.h"
#include "ui/panels/BasePanel.h"

#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>

class QTableWidget;
class VmDisposeObjectsPanel : public BasePanel {
  Q_OBJECT

public:
  explicit VmDisposeObjectsPanel(ApplicationContext *ctx,
                                 QWidget *parent = nullptr);

private slots:
  void onReply(JdwpReply *reply) override;
  void sendCommand() override;
  void addRow();
  void deleteRow();

private:
  QString getPanelTitle() override;
  QString getHelpText() override;
  QString getHelpUrl() override;
  void setupConnections();

  QPushButton *newRowButton;
  QPushButton *deleteRowButton;
  QTableWidget *objectList;
  QLabel *noOutputLabel;
  QLabel *noErrorLabel;

  ApplicationContext *ctx;
};

#endif // VMDISPOSEOBJECTSPANEL_H

#ifndef NEWCONNECTIONDIALOG_H
#define NEWCONNECTIONDIALOG_H
#include "ApplicationContext.h"
#include "ui/panels/vm/VmVersionPanel.h"

#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

class NewConnectionDialog : public QDialog {
  Q_OBJECT

public:
  explicit NewConnectionDialog(ApplicationContext *ctx,
                               QWidget *parent = nullptr);

public slots:
  void resetAndShow();

private slots:
  void addConnectionSuccess(Connection *connection);
  void addConnectionError(JdwpLibError error);

private:
  void submit();

  ApplicationContext *ctx;

  QLineEdit *nameField;
  QLineEdit *hostField;
  QLineEdit *portField;
  QLabel *descriptionLabel;
  QLabel *errorLabel;

  QPushButton *submitButton;
  QPushButton *cancelButton;

  QFormLayout *formLayout;
  QHBoxLayout *buttonLayout;
};

#endif // NEWCONNECTIONDIALOG_H

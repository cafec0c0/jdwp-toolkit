#include "NewConnectionDialog.h"

#include "util/JdwpConstantsMapper.h"

NewConnectionDialog::NewConnectionDialog(ApplicationContext *ctx,
                                         QWidget *parent)
    : QDialog(parent) {
  this->ctx = ctx;

  setWindowTitle("New Connection");
  setMinimumWidth(400);

  formLayout = new QFormLayout(this);
  buttonLayout = new QHBoxLayout();
  nameField = new QLineEdit();
  hostField = new QLineEdit();
  portField = new QLineEdit();
  errorLabel = new QLabel();
  descriptionLabel = new QLabel("<h3>New Connection</h3>");

  errorLabel->setAlignment(Qt::AlignTop);
  errorLabel->setMinimumHeight(50);
  errorLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::Maximum);
  errorLabel->setWordWrap(true);
  errorLabel->setStyleSheet("text-transform: capitalize");

  formLayout->addRow(descriptionLabel);
  nameField->setSizePolicy(QSizePolicy::MinimumExpanding,
                           QSizePolicy::MinimumExpanding);
  formLayout->addRow("Name", nameField);
  formLayout->addRow("Host", hostField);
  formLayout->addRow("Port", portField);
  formLayout->addRow(errorLabel);

  submitButton = new QPushButton("Add Connection");
  cancelButton = new QPushButton("Cancel");

  buttonLayout->setAlignment(Qt::AlignRight);
  buttonLayout->addWidget(submitButton);
  buttonLayout->addWidget(cancelButton);

  formLayout->addRow(buttonLayout);

  connect(submitButton, &QPushButton::clicked, this,
          &NewConnectionDialog::submit);
  connect(cancelButton, &QPushButton::clicked, this,
          &NewConnectionDialog::close);

  // Handle add connections outcomes
  connect(ctx->vmController(), &VmController::connectionAdded, this,
          &NewConnectionDialog::addConnectionSuccess);
  connect(ctx->vmController(), &VmController::connectionAddError, this,
          &NewConnectionDialog::addConnectionError);
}
void NewConnectionDialog::resetAndShow() {
  nameField->setText("Connection 1");
  hostField->setText("127.0.0.1");
  portField->setText("8000");
  errorLabel->setText("");

  hostField->setFocus();
  show();
}

void NewConnectionDialog::addConnectionSuccess(Connection *connection) {
  submitButton->setEnabled(true);
  cancelButton->setEnabled(true);
  close();
}

void NewConnectionDialog::addConnectionError(JdwpLibError error) {
  submitButton->setEnabled(true);
  cancelButton->setEnabled(true);
  errorLabel->setText(
      QString("Unable to connect: %1 (%2)")
          .arg(JdwpConstantsMapper::getJdwpLibErrorDescription(error))
          .arg(JdwpConstantsMapper::getJdwpLibErrorEnumName(error)));
  hostField->setFocus();
  hostField->selectAll();
}

void NewConnectionDialog::submit() {
  submitButton->setEnabled(false);
  cancelButton->setEnabled(false);
  ctx->vmController()->addConnection(
      hostField->text(), portField->text().toUShort(), nameField->text());
}

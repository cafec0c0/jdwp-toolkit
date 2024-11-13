//
// Created by rogue on 13/11/24.
//

#include "BasePanel.h"

#include "util/JdwpConstantsMapper.h"

#include <QMessageBox>

BasePanel::BasePanel(const QString &title, QWidget *parent) {
  layout = new QVBoxLayout();
  titleLayout = new QHBoxLayout();
  inputLayout = new QFormLayout();
  outputLayout = new QFormLayout();
  errorLayout = new QFormLayout();
  buttonLayout = new QHBoxLayout();

  titleLabel = new QLabel(QString("<h3>%1</h3>").arg(title));
  errorLabel = new QLineEdit();
  helpButton = new QPushButton("?");
  sendButton = new QPushButton("Send");

  inputGroupBox = new QGroupBox("Out Data");
  outputGroupBox = new QGroupBox("Reply Data");
  errorGroupBox = new QGroupBox("Error Data");

  inputGroupBox->setLayout(inputLayout);
  outputGroupBox->setLayout(outputLayout);
  errorGroupBox->setLayout(errorLayout);

  layout->setContentsMargins(0, 0, 0, 0);
  buttonLayout->setAlignment(Qt::AlignRight);

  helpButton->setMaximumSize(30, 30);
  helpButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  helpButton->setToolTip("Help");

  errorLabel->setReadOnly(true);

  sendButton->setToolTip("Send Command");

  titleLayout->addWidget(titleLabel);
  titleLayout->addStretch(1);
  titleLayout->addWidget(helpButton);

  buttonLayout->addWidget(sendButton);

  errorLayout->addRow("JDWP Error", errorLabel);

  layout->addLayout(titleLayout);
  layout->addWidget(inputGroupBox);
  layout->addWidget(outputGroupBox);
  layout->addWidget(errorGroupBox);
  layout->addLayout(buttonLayout);

  setLayout(layout);
}
void BasePanel::showHelp() {
  const QString helpText =
      QString("<h3>%1</h3>"
              "%2"
              "<p>More information available at <a "
              "href=\"%3\">docs.oracle.com</a></p>")
          .arg(getPanelTitle(), getHelpText(), getHelpUrl());

  QMessageBox::information(topLevelWidget(), "About " + getPanelTitle(),
                           helpText);
}

void BasePanel::setJdwpError(const JdwpProtocolError err) const {
  this->errorLabel->setText(QString::number(err));
}
#include "TabsPlaceholder.h"
TabsPlaceholder::TabsPlaceholder(QWidget *parent) : QWidget(parent) {
  this->layout = new QVBoxLayout();

  this->label = new QLabel("Connect to a VM to start debugging");
  this->label->setAlignment(Qt::AlignCenter);
  this->label->setEnabled(false); // Make it darker so it looks cooler

  this->layout->addWidget(this->label);

  setLayout(this->layout);
}
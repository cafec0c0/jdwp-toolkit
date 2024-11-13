#include "AboutDialog.h"

#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(ApplicationContext *ctx, QWidget *parent)
    : QDialog(parent) {
  vbox = new QVBoxLayout();

  QString text =
      QString("<h1>JDWP Toolkit</h1>"
              "<h3>Version 0.0.1</h3>"
              ""
              "<p>&copy; 2024 Adam Bruce</p>"
              "<p><a href=\"https://github.com/cafec0c0/jdwp-toolkit\">View "
              "Source on GitHub</a></p>");

  QLabel *textLabel = new QLabel(text);
  textLabel->setAlignment(Qt::AlignCenter);

  QHBoxLayout *hbox = new QHBoxLayout();
  QPushButton *closeButton = new QPushButton("Close");
  hbox->setAlignment(Qt::AlignRight);
  hbox->addWidget(closeButton);

  vbox->addWidget(textLabel);
  vbox->addLayout(hbox);

  setLayout(vbox);

  resize(500, 300);

  connect(textLabel, &QLabel::linkActivated, this, &AboutDialog::openHyperlink);
  connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
}

void AboutDialog::openHyperlink(const QString &hyperlink) {
  QDesktopServices::openUrl(hyperlink);
}

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QDialog>
#include <QVBoxLayout>

#include "ApplicationContext.h"

class AboutDialog : public QDialog {
  Q_OBJECT

public:
  explicit AboutDialog(ApplicationContext *ctx, QWidget *parent = nullptr);

private slots:
  static void openHyperlink(const QString &hyperlink);

private:
  QVBoxLayout *vbox;
};

#endif // ABOUTDIALOG_H

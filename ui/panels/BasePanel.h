#ifndef BASEPANEL_H
#define BASEPANEL_H
#include "ApplicationContext.h"
#include "client/JdwpClientWrapper.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class BasePanel : public QWidget {
  Q_OBJECT

public:
  explicit BasePanel(const QString &title, QWidget *parent = nullptr);

protected slots:
  virtual void onReply(JdwpReply *reply){};
  virtual void sendCommand(){};
  void showHelp();

protected:
  virtual QString getPanelTitle() { return ""; };
  virtual QString getHelpText() { return ""; };
  virtual QString getHelpUrl() { return ""; };
  void setJdwpError(JdwpProtocolError err) const;

  QFormLayout *inputLayout;
  QFormLayout *outputLayout;
  QFormLayout *errorLayout;
  QPushButton *sendButton;
  QPushButton *helpButton;

private:
  QVBoxLayout *layout;
  QHBoxLayout *titleLayout;
  QHBoxLayout *buttonLayout;
  QLabel *titleLabel;
  QLineEdit *errorLabel;

  QGroupBox *inputGroupBox;
  QGroupBox *outputGroupBox;
  QGroupBox *errorGroupBox;

  QString helpTitle;
  QString helpText;
};

#endif // BASEPANEL_H

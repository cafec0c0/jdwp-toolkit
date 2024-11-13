#ifndef TABSPLACEHOLDER_H
#define TABSPLACEHOLDER_H
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class TabsPlaceholder : public QWidget {
  Q_OBJECT

public:
  explicit TabsPlaceholder(QWidget *parent = nullptr);

private:
  QVBoxLayout *layout;
  QLabel *label;
};

#endif // TABSPLACEHOLDER_H

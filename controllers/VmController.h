#ifndef VMCONTROLLER_H
#define VMCONTROLLER_H
#include "client/JdwpClientWrapper.h"

#include <QObject>

class Connection;
class VmController : public QObject {
  Q_OBJECT
public:
  explicit VmController();
  JdwpClientWrapper *connection();

public slots:
  void addConnection(QString host, quint16 port, QString name);
  void removeConnection();

signals:
  void connectionAdded(Connection *connection);
  void connectionAddError(JdwpLibError error);
  void connectionRemoved();

private:
  JdwpClientWrapper *connection_;
};

#endif // VMCONTROLLER_H

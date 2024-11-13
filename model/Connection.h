#ifndef CONNECTION_H
#define CONNECTION_H
#include "client/JdwpClientWrapper.h"

class Connection {
public:
  explicit Connection();
  ~Connection();
  explicit Connection(JdwpClientWrapper *client, QString host, quint16 port,
                      QString name);

  JdwpClientWrapper *client();
  QString host();
  quint16 port();
  QString name();

  void setName(QString name);

private:
  JdwpClientWrapper *client_;
  QString host_;
  quint16 port_;
  QString name_;
};

#endif // CONNECTION_H

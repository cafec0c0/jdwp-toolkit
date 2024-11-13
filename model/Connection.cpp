#include "Connection.h"

Connection::Connection() : Connection(nullptr, nullptr, 0, nullptr) {}
Connection::~Connection() {
  this->client_->disconnect();
  delete this->client_;
}

Connection::Connection(JdwpClientWrapper *client, QString host, quint16 port,
                       QString name)
    : client_(client), host_(host), port_(port), name_(name) {}

JdwpClientWrapper *Connection::client() { return this->client_; }

QString Connection::host() { return this->host_; }

quint16 Connection::port() { return this->port_; }

QString Connection::name() { return this->name_; }

void Connection::setName(QString name) { this->name_ = name; }

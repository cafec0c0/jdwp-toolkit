#include "VmController.h"

#include "client/JdwpClientWrapper.h"
#include "model/Connection.h"

VmController::VmController() {}
JdwpClientWrapper *VmController::connection() { return this->connection_; }

void VmController::addConnection(QString host, quint16 port, QString name) {
  JdwpClientWrapper *wrapper = new JdwpClientWrapper();
  JdwpLibError error = wrapper->initClient();
  if (error != JDWP_LIB_ERR_NONE) {
    emit connectionAddError(error);
    delete wrapper;
    return;
  }

  error = wrapper->connect(host, port);
  if (error != JDWP_LIB_ERR_NONE) {
    emit connectionAddError(error);
    delete wrapper;
    return;
  }

  this->connection_ = wrapper;
  Connection *connection = new Connection(wrapper, host, port, name);
  emit connectionAdded(connection);
}

void VmController::removeConnection() {
  this->connection_->disconnect();
  delete this->connection_;
  emit connectionRemoved();
}

#include "JdwpClientWrapper.h"
#include <QDebug>

JdwpLibError JdwpClientWrapper::initClient() {
  JdwpLibError err = jdwp_client_new(&this->client_);
  if (err != JDWP_LIB_ERR_NONE)
    return err;

  id = 100;

  jdwp_client_set_callback(static_cast<JdwpClient *>(this->client_),
                           handle_callback, reinterpret_cast<void **>(this));

  return err;
}

JdwpLibError JdwpClientWrapper::send(void *command, quint32 id,
                                     JdwpCommandType type) {
  return jdwp_client_send(this->client_, id, type, command);
}

JdwpLibError JdwpClientWrapper::connect(QString host, quint16 port) {
  JdwpLibError err =
      jdwp_client_connect(this->client_, host.toStdString().c_str(), port);
  connected_ = err == JDWP_LIB_ERR_NONE;
  return err;
}

JdwpLibError JdwpClientWrapper::disconnect() {
  connected_ = false;
  return jdwp_client_disconnect(this->client_);
}

JdwpClientWrapper::~JdwpClientWrapper() {
  if (connected_)
    jdwp_client_free(&this->client_);
}

uint32_t JdwpClientWrapper::nextId() { return id.fetchAndAddRelaxed(1); }

void JdwpClientWrapper::handle_callback(JdwpReply *reply, void **state) {
  auto *wrapper = reinterpret_cast<JdwpClientWrapper *>(state);
  switch (reply->type) {
  case JDWP_VIRTUAL_MACHINE_VERSION:
    emit wrapper->virtualMachineVersion(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_CLASSES_BY_SIGNATURE:
    emit wrapper->virtualMachineClassesBySignature(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_ALL_CLASSES:
    emit wrapper->virtualMachineAllClasses(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_ALL_THREADS:
    emit wrapper->virtualMachineAllThreads(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_TOP_LEVEL_THREAD_GROUPS:
    emit wrapper->virtualMachineTopLevelThreadGroups(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_ID_SIZES:
    emit wrapper->virtualMachineIdSizes(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_CREATE_STRING:
    emit wrapper->virtualMachineCreateString(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_CAPABILITIES:
    emit wrapper->virtualMachineCapabilities(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_CLASS_PATHS:
    emit wrapper->virtualMachineClassPaths(reply);
    break;
  case JDWP_VIRTUAL_MACHINE_CAPABILITIES_NEW:
    emit wrapper->virtualMachineCapabilitiesNew(reply);
    break;
  default:;
  }
}

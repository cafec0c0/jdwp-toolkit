#ifndef JDWPCLIENTWRAPPER_H
#define JDWPCLIENTWRAPPER_H

#include <QObject>
#include <jdwp.h>

class JdwpClientWrapper : public QObject {
  Q_OBJECT
public:
  JdwpLibError initClient();
  JdwpLibError send(void *command, quint32 id, JdwpCommandType type);
  JdwpLibError connect(QString host, quint16 port);
  JdwpLibError disconnect();
  ~JdwpClientWrapper() override;

  uint32_t nextId();

signals:
  void clientInitError(JdwpLibError error);
  void connectionError(JdwpLibError error);
  void sendError(JdwpLibError error);
  void disconnectError(JdwpLibError error);

  // JDWP message signals
  void virtualMachineVersion(JdwpReply *reply);
  void virtualMachineClassesBySignature(JdwpReply *reply);
  void virtualMachineAllClasses(JdwpReply *reply);
  void virtualMachineAllThreads(JdwpReply *reply);
  void virtualMachineTopLevelThreadGroups(JdwpReply *reply);
  void virtualMachineIdSizes(JdwpReply *reply);
  void virtualMachineCreateString(JdwpReply *reply);
  void virtualMachineCapabilities(JdwpReply *reply);
  void virtualMachineClassPaths(JdwpReply *reply);
  void virtualMachineCapabilitiesNew(JdwpReply *reply);

private:
  bool connected_ = false;
  static void handle_callback(JdwpReply *reply, void **state);
  JdwpClient client_ = nullptr;

  QAtomicInt id;
};

#endif // JDWPCLIENTWRAPPER_H

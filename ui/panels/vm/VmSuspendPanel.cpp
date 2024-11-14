#include "VmSuspendPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmSuspendPanel::VmSuspendPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmSuspendPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmSuspendPanel::getPanelTitle() { return "Virtual Machine :: Suspend"; }

QString VmSuspendPanel::getHelpText() {
  return "<p>Suspends the execution of the application running in the target "
         "VM. All Java threads currently running will be suspended.</p>"
         "<p>Suspends of both the virtual machine and individual threads are "
         "counted. Before a thread will run again, it must be resumed through "
         "the VM-level resume command or the thread-level resume command the "
         "same number of times it has been suspended.</p>";
}

QString VmSuspendPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Suspend");
}

void VmSuspendPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmSuspendPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmSuspendPanel::showHelp);
}

void VmSuspendPanel::onReply(JdwpReply *reply) {}

void VmSuspendPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineSuspendCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_SUSPEND);
}
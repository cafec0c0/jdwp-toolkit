#include "VmResumePanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmResumePanel::VmResumePanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmResumePanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmResumePanel::getPanelTitle() { return "Virtual Machine :: Resume"; }

QString VmResumePanel::getHelpText() {
  return "<p>Resumes execution of the application after the suspend command or "
         "an event has stopped it. Suspensions of the Virtual Machine and "
         "individual threads are counted. If a particular thread is suspended "
         "n times, it must resumed n times before it will continue.</p>";
}

QString VmResumePanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Resume");
}

void VmResumePanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this, &VmResumePanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmResumePanel::showHelp);
}

void VmResumePanel::onReply(JdwpReply *reply) {}

void VmResumePanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineResumeCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_RESUME);
}
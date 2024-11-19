#include "VmHoldEventsPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <qvalidator.h>

VmHoldEventsPanel::VmHoldEventsPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmHoldEventsPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmHoldEventsPanel::getPanelTitle() {
  return "Virtual Machine :: Hold Events";
}

QString VmHoldEventsPanel::getHelpText() {
  return "<p> Tells the target VM to stop sending events. Events are not "
         "discarded; they are held until a subsequent ReleaseEvents command is "
         "sent. This command is useful to control the number of events sent to "
         "the debugger VM in situations where very large numbers of events are "
         "generated. While events are held by the debugger back-end, "
         "application execution may be frozen by the debugger back-end to "
         "prevent buffer overflows on the back end. Responses to commands are "
         "never held and are not affected by this command. If events are "
         "already being held, this command is ignored. </p>";
}

QString VmHoldEventsPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_HoldEvents");
}

void VmHoldEventsPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmHoldEventsPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmHoldEventsPanel::showHelp);
}

void VmHoldEventsPanel::onReply(JdwpReply *reply) {}

void VmHoldEventsPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_HOLD_EVENTS);
}
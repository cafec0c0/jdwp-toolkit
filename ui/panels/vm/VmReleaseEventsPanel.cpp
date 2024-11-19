#include "VmReleaseEventsPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <qvalidator.h>

VmReleaseEventsPanel::VmReleaseEventsPanel(ApplicationContext *ctx,
                                           QWidget *parent)
    : BasePanel(VmReleaseEventsPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmReleaseEventsPanel::getPanelTitle() {
  return "Virtual Machine :: Release Events";
}

QString VmReleaseEventsPanel::getHelpText() {
  return "<p>Tells the target VM to continue sending events. This command is "
         "used to restore normal activity after a HoldEvents command. If there "
         "is no current HoldEvents command in effect, this command is ignored. "
         "</p>";
}

QString VmReleaseEventsPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_ReleaseEvents");
}

void VmReleaseEventsPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmReleaseEventsPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmReleaseEventsPanel::showHelp);
}

void VmReleaseEventsPanel::onReply(JdwpReply *reply) {}

void VmReleaseEventsPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_RELEASE_EVENTS);
}
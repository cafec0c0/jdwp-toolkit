#include "VmExitPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <qvalidator.h>

VmExitPanel::VmExitPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmExitPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  exitCodeEdit = new QLineEdit("1");
  exitCodeEdit->setValidator(new QIntValidator(0, INT32_MAX, this));
  outputLayout->addRow("Exit Code", exitCodeEdit);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmExitPanel::getPanelTitle() { return "Virtual Machine :: Exit"; }

QString VmExitPanel::getHelpText() {
  return "<p>Terminates the target VM with the given exit code. On some "
         "platforms, the exit code might be truncated, for example, to the low "
         "order 8 bits. All ids previously returned from the target VM become "
         "invalid. Threads running in the VM are abruptly terminated. A thread "
         "death exception is not thrown and finally blocks are not run.</p>";
}

QString VmExitPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Exit");
}

void VmExitPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this, &VmExitPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmExitPanel::showHelp);
}

void VmExitPanel::onReply(JdwpReply *reply) {}

void VmExitPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineExitCommand cmd{.exit_code = exitCodeEdit->text().toUInt()};
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_EXIT);

  ctx->vmController()->removeConnection();
}
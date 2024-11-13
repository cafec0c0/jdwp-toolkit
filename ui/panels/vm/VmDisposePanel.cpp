#include "VmDisposePanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmDisposePanel::VmDisposePanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmDisposePanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmDisposePanel::getPanelTitle() { return "Virtual Machine :: Dispose"; }

QString VmDisposePanel::getHelpText() {
  return "<p>Invalidates this virtual machine mirror. The communication "
         "channel to the target VM is closed, and the target VM prepares to "
         "accept another subsequent connection from this debugger or another "
         "debugger, including the following tasks:</p>"
         "<p><ul>"
         "<li>All event requests are cancelled.</li>"
         "<li>All threads suspended by the thread-level suspend command or the "
         "VM-level suspend command are resumed as many times as necessary for "
         "them to run.</li>"
         "<li>Garbage collection is re-enabled in all cases where it was "
         "disabled.</li></ul></p>"
         "<p>Any current method invocations executing in the target VM are "
         "continued after the disconnection. Upon completion of any such "
         "method invocation, the invoking thread continues from the location "
         "where it was originally stopped.</p>"
         "<p>Resources originating in this VirtualMachine (ObjectReferences, "
         "ReferenceTypes, etc.) will become invalid.</p>";
}

QString VmDisposePanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Dispose");
}

void VmDisposePanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmDisposePanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmDisposePanel::showHelp);
}

void VmDisposePanel::onReply(JdwpReply *reply) {}

void VmDisposePanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineDisposeCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_DISPOSE);

  ctx->vmController()->removeConnection();
}
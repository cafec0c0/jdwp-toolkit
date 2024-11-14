#include "VmCreateStringPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmCreateStringPanel::VmCreateStringPanel(ApplicationContext *ctx,
                                         QWidget *parent)
    : BasePanel(VmCreateStringPanel::getPanelTitle(), parent), ctx(ctx) {

  utfEdit = new QLineEdit();
  inputLayout->addRow("UTF", utfEdit);

  stringObjectEdit = new QLineEdit();
  stringObjectEdit->setReadOnly(true);

  outputLayout->addRow("String Object", stringObjectEdit);

  setupConnections();
}

QString VmCreateStringPanel::getPanelTitle() {
  return "Virtual Machine :: Create String";
}

QString VmCreateStringPanel::getHelpText() {
  return "<p>Creates a new string object in the target VM and returns its "
         "id.</p>";
}

QString VmCreateStringPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_CreateString");
}

void VmCreateStringPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmCreateStringPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmCreateStringPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineCreateString, this,
            &VmCreateStringPanel::onReply);
  });
}

void VmCreateStringPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineCreateStringData *>(reply->data);
    this->stringObjectEdit->setText(QString::number(data->string_object));
  } else {
    this->stringObjectEdit->setText("");
  }
  setJdwpError(reply->error);
}

void VmCreateStringPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  char *data = (char *)malloc(utfEdit->text().size());
  strcpy(data, utfEdit->text().toStdString().c_str());

  JdwpVirtualMachineCreateStringCommand cmd = {.utf = data};
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_CREATE_STRING);
  free(data);
}
#include "VmVersionPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmVersionPanel::VmVersionPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmVersionPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  descriptionArea = new QTextEdit();
  majorVersionLabel = new QLineEdit();
  minorVersionLabel = new QLineEdit();
  vmVersionLabel = new QLineEdit();
  vmNameLabel = new QLineEdit();

  descriptionArea->setReadOnly(true);
  descriptionArea->setMinimumHeight(0);
  majorVersionLabel->setReadOnly(true);
  minorVersionLabel->setReadOnly(true);
  vmVersionLabel->setReadOnly(true);
  vmNameLabel->setReadOnly(true);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Description", descriptionArea);
  outputLayout->addRow("JDWP Version Major", majorVersionLabel);
  outputLayout->addRow("JDWP Version Minor", minorVersionLabel);
  outputLayout->addRow("VM Version", vmVersionLabel);
  outputLayout->addRow("VM Name", vmNameLabel);

  setupConnections();
}

QString VmVersionPanel::getPanelTitle() { return "Virtual Machine :: Version"; }

QString VmVersionPanel::getHelpText() {
  return "<p>Returns the JDWP version implemented by the target VM. The "
         "version string format is implementation dependent.</p>";
}

QString VmVersionPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Version");
}

void VmVersionPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmVersionPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmVersionPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineVersion, this,
            &VmVersionPanel::onReply);
  });
}

void VmVersionPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineVersionData *>(reply->data);
    this->descriptionArea->setText(data->description);
    this->majorVersionLabel->setText(QString("%1").arg(data->jdwp_major));
    this->minorVersionLabel->setText(QString("%1").arg(data->jdwp_minor));
    this->vmVersionLabel->setText(data->vm_version);
    this->vmNameLabel->setText(data->vm_name);
  } else {
    this->descriptionArea->setText("");
    this->majorVersionLabel->setText("");
    this->minorVersionLabel->setText("");
    this->vmVersionLabel->setText("");
    this->vmNameLabel->setText("");
  }
  setJdwpError(reply->error);
}

void VmVersionPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_VERSION);
}
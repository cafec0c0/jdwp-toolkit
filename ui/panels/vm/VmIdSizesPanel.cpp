#include "VmIdSizesPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmIdSizesPanel::VmIdSizesPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmIdSizesPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  fieldIdSizeLabel = new QLineEdit();
  methodIdSizeLabel = new QLineEdit();
  objectIdSizeLabel = new QLineEdit();
  referenceTypeIdSize = new QLineEdit();
  frameIdSize = new QLineEdit();

  fieldIdSizeLabel->setReadOnly(true);
  methodIdSizeLabel->setReadOnly(true);
  objectIdSizeLabel->setReadOnly(true);
  referenceTypeIdSize->setReadOnly(true);
  frameIdSize->setReadOnly(true);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Field ID Size", fieldIdSizeLabel);
  outputLayout->addRow("Method ID Size", methodIdSizeLabel);
  outputLayout->addRow("Object ID Size", objectIdSizeLabel);
  outputLayout->addRow("Reference Type ID Size", referenceTypeIdSize);
  outputLayout->addRow("Frame ID Size", frameIdSize);

  setupConnections();
}

QString VmIdSizesPanel::getPanelTitle() {
  return "Virtual Machine :: ID Sizes";
}

QString VmIdSizesPanel::getHelpText() {
  return "<p>Returns the sizes of variably-sized data types in the target "
         "VM. The returned values indicate the number of bytes used by the "
         "identifiers in command and reply packets.</p>";
}

QString VmIdSizesPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_IDSizes");
}

void VmIdSizesPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmIdSizesPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmIdSizesPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineIdSizes, this,
            &VmIdSizesPanel::onReply);
  });
}

void VmIdSizesPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineIdSizesData *>(reply->data);
    this->fieldIdSizeLabel->setText(QString::number(data->field_id_size));
    this->methodIdSizeLabel->setText(QString::number(data->method_id_size));
    this->objectIdSizeLabel->setText(QString::number(data->object_id_size));
    this->referenceTypeIdSize->setText(
        QString::number(data->reference_type_id_size));
    this->frameIdSize->setText(QString::number(data->frame_id_size));
  } else {
    this->fieldIdSizeLabel->setText("");
    this->methodIdSizeLabel->setText("");
    this->objectIdSizeLabel->setText("");
    this->referenceTypeIdSize->setText("");
    this->frameIdSize->setText("");
  }
  setJdwpError(reply->error);
}

void VmIdSizesPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_ID_SIZES);
}
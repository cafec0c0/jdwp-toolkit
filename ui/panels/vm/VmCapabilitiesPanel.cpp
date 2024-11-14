
#include "VmCapabilitiesPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"
VmCapabilitiesPanel::VmCapabilitiesPanel(ApplicationContext *ctx,
                                         QWidget *parent)
    : BasePanel(VmCapabilitiesPanel::getPanelTitle(), parent), ctx(ctx) {

  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  hbox = new QHBoxLayout();
  leftLayout = new QFormLayout();
  rightLayout = new QFormLayout();
  hbox->addLayout(leftLayout);
  hbox->addLayout(rightLayout);

  hbox->setAlignment(Qt::AlignLeft);

  outputLayout->addRow(hbox);

  canWatchFieldModificationCheck = new QCheckBox();
  canWatchFieldModificationCheck->setEnabled(false);
  canWatchFieldAccessCheck = new QCheckBox();
  canWatchFieldAccessCheck->setEnabled(false);
  canGetBytecodesCheck = new QCheckBox();
  canGetBytecodesCheck->setEnabled(false);
  canGetSyntheticAttributeCheck = new QCheckBox();
  canGetSyntheticAttributeCheck->setEnabled(false);
  canGetOwnedMonitorInfoCheck = new QCheckBox();
  canGetOwnedMonitorInfoCheck->setEnabled(false);
  canGetCurrentContendedMonitorCheck = new QCheckBox();
  canGetCurrentContendedMonitorCheck->setEnabled(false);
  canGetMonitorInfoCheck = new QCheckBox();
  canGetMonitorInfoCheck->setEnabled(false);

  leftLayout->addRow("canWatchFieldModification",
                     canWatchFieldModificationCheck);
  leftLayout->addRow("canWatchFieldAccess", canWatchFieldAccessCheck);
  leftLayout->addRow("canGetBytecodes", canGetBytecodesCheck);
  leftLayout->addRow("canGetSyntheticAttribute", canGetSyntheticAttributeCheck);
  rightLayout->addRow("canGetOwnedMonitorInfo", canGetOwnedMonitorInfoCheck);
  rightLayout->addRow("canGetCurrentContendedMonitor",
                      canGetCurrentContendedMonitorCheck);
  rightLayout->addRow("canGetMonitorInfo", canGetMonitorInfoCheck);

  setupConnections();
}

QString VmCapabilitiesPanel::getPanelTitle() {
  return "Virtual Machine :: Capabilities";
}

QString VmCapabilitiesPanel::getHelpText() {
  return "<p>Retrieve this VM's capabilities. The capabilities are returned as "
         "booleans, each indicating the presence or absence of a capability. "
         "The commands associated with each capability will return the "
         "NOT_IMPLEMENTED error if the capability is not available.</p>";
}

QString VmCapabilitiesPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_Capabilities");
}

void VmCapabilitiesPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmCapabilitiesPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmCapabilitiesPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineCapabilities, this,
            &VmCapabilitiesPanel::onReply);
  });
}

void VmCapabilitiesPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineCapabilitiesData *>(reply->data);
    canWatchFieldModificationCheck->setChecked(
        data->can_watch_field_modification);
    canWatchFieldAccessCheck->setChecked(data->can_watch_field_access);
    canGetBytecodesCheck->setChecked(data->can_get_bytecodes);
    canGetSyntheticAttributeCheck->setChecked(
        data->can_get_synthetic_attribute);
    canGetOwnedMonitorInfoCheck->setChecked(data->can_get_owned_monitor_info);
    canGetCurrentContendedMonitorCheck->setChecked(
        data->can_get_current_contended_monitor);
    canGetMonitorInfoCheck->setChecked(data->can_get_monitor_info);
  } else {
    canWatchFieldModificationCheck->setChecked(false);
    canWatchFieldAccessCheck->setChecked(false);
    canGetBytecodesCheck->setChecked(false);
    canGetSyntheticAttributeCheck->setChecked(false);
    canGetOwnedMonitorInfoCheck->setChecked(false);
    canGetCurrentContendedMonitorCheck->setChecked(false);
    canGetMonitorInfoCheck->setChecked(false);
  }
  setJdwpError(reply->error);
}

void VmCapabilitiesPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineCapabilitiesCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_CAPABILITIES);
}
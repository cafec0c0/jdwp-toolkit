
#include "VmCapabilitiesNewPanel.h"

#include "ui/panels/BasePanel.h"
#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <QHeaderView>
#include <QStringList>

VmCapabilitiesNewPanel::VmCapabilitiesNewPanel(ApplicationContext *ctx,
                                               QWidget *parent)
    : BasePanel(VmCapabilitiesNewPanel::getPanelTitle(), parent), ctx(ctx) {

  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  capabilitiesTable = new QTableWidget();
  capabilitiesTable->setColumnCount(2);
  capabilitiesTable->setRowCount(32);
  capabilitiesTable->setHorizontalHeaderLabels(QStringList() << "Capability"
                                                             << "Present");
  capabilitiesTable->horizontalHeader()->setStretchLastSection(true);
  capabilitiesTable->verticalHeader()->setVisible(false);
  setupTable();

  outputLayout->addRow("Capabilities", capabilitiesTable);
  setupConnections();
}

QString VmCapabilitiesNewPanel::getPanelTitle() {
  return "Virtual Machine :: Capabilities New";
}

QString VmCapabilitiesNewPanel::getHelpText() {
  return "<p>Retrieve all of this VM's capabilities. The capabilities are "
         "returned as booleans, each indicating the presence or absence of a "
         "capability. The commands associated with each capability will return "
         "the NOT_IMPLEMENTED error if the capability is not available. Since "
         "JDWP version 1.4.</p>";
}

QString VmCapabilitiesNewPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_CapabilitiesNew");
}

void VmCapabilitiesNewPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmCapabilitiesNewPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmCapabilitiesNewPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineCapabilitiesNew, this,
            &VmCapabilitiesNewPanel::onReply);
  });
}
void VmCapabilitiesNewPanel::setupTable() {
  QStringList capabilities = QStringList() << "canWatchFieldModification"
                                           << "canWatchFieldAccess"
                                           << "canGetBytecodes"
                                           << "canGetSyntheticAttribute"
                                           << "canGetOwnedMonitorInfo"
                                           << "canGetCurrentContendedMonitor"
                                           << "canGetMonitorInfo"
                                           << "canRedefineClasses"
                                           << "canAddMethod"
                                           << "canUnrestrictedlyRedefineClasses"
                                           << "canPopFrames"
                                           << "canUseInstanceFilters"
                                           << "canGetSourceDebugExtension"
                                           << "canRequestVMDeathEvent"
                                           << "canSetDefaultStratum"
                                           << "canGetInstanceInfo"
                                           << "canRequestMonitorEvents"
                                           << "canGetMonitorFrameInfo"
                                           << "canUseSourceNameFilters"
                                           << "canGetConstantPool"
                                           << "canForceEarlyReturn"
                                           << "reserved22"
                                           << "reserved23"
                                           << "reserved24"
                                           << "reserved25"
                                           << "reserved26"
                                           << "reserved27"
                                           << "reserved28"
                                           << "reserved29"
                                           << "reserved30"
                                           << "reserved31"
                                           << "reserved32";

  for (int i = 0; i < capabilities.size(); i++) {
    auto t = new QTableWidgetItem(capabilities[i]);
    t->setFlags(t->flags() ^ Qt::ItemIsEditable);
    capabilitiesTable->setItem(i, 0, t);
  }

  capabilitiesTable->resizeColumnsToContents();
}
void VmCapabilitiesNewPanel::insertValue(int row, bool value) {
  auto t = new QTableWidgetItem(value ? "Yes" : "No");
  t->setFlags(t->flags() ^ Qt::ItemIsEditable);
  capabilitiesTable->setItem(row, 1, t);
}

void VmCapabilitiesNewPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data =
        static_cast<JdwpVirtualMachineCapabilitiesNewData *>(reply->data);
    insertValue(0, data->can_watch_field_modification);
    insertValue(1, data->can_watch_field_access);
    insertValue(2, data->can_get_bytecodes);
    insertValue(3, data->can_get_synthetic_attribute);
    insertValue(4, data->can_get_owned_monitor_info);
    insertValue(5, data->can_get_current_contended_monitor);
    insertValue(6, data->can_get_monitor_info);
    insertValue(7, data->can_redefine_classes);
    insertValue(8, data->can_add_method);
    insertValue(9, data->can_unrestrictedly_redefine_classes);
    insertValue(10, data->can_pop_frames);
    insertValue(11, data->can_use_instance_filters);
    insertValue(12, data->can_get_source_debug_extensions);
    insertValue(13, data->can_request_vm_death_event);
    insertValue(14, data->can_set_default_stratum);
    insertValue(15, data->can_get_instance_info);
    insertValue(16, data->can_request_monitor_events);
    insertValue(17, data->can_get_monitor_frame_info);
    insertValue(18, data->can_use_source_name_filters);
    insertValue(19, data->can_get_constant_pool);
    insertValue(20, data->can_force_early_return);
    insertValue(21, data->reserved_22);
    insertValue(22, data->reserved_23);
    insertValue(23, data->reserved_24);
    insertValue(24, data->reserved_25);
    insertValue(25, data->reserved_26);
    insertValue(26, data->reserved_27);
    insertValue(27, data->reserved_28);
    insertValue(28, data->reserved_29);
    insertValue(29, data->reserved_30);
    insertValue(30, data->reserved_31);
    insertValue(31, data->reserved_32);
  } else {
    for (int i = 0; i < 7; i++) {
      capabilitiesTable->item(i, 1)->setText("");
    }
  }
  setJdwpError(reply->error);
}

void VmCapabilitiesNewPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(),
               JDWP_VIRTUAL_MACHINE_CAPABILITIES_NEW);
}
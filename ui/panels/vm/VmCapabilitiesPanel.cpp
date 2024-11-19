
#include "VmCapabilitiesPanel.h"

#include "ui/panels/BasePanel.h"
#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <QHeaderView>
#include <QStringList>

VmCapabilitiesPanel::VmCapabilitiesPanel(ApplicationContext *ctx,
                                         QWidget *parent)
    : BasePanel(VmCapabilitiesPanel::getPanelTitle(), parent), ctx(ctx) {

  noArgsLabel = new QLabel("This command does not take any out data.");
  inputLayout->addRow(noArgsLabel);

  capabilitiesTable = new QTableWidget();
  capabilitiesTable->setColumnCount(2);
  capabilitiesTable->setRowCount(7);
  capabilitiesTable->setHorizontalHeaderLabels(QStringList() << "Capability"
                                                             << "Present");
  capabilitiesTable->horizontalHeader()->setStretchLastSection(true);
  capabilitiesTable->verticalHeader()->setVisible(false);
  setupTable();

  outputLayout->addRow("Capabilities", capabilitiesTable);
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
void VmCapabilitiesPanel::setupTable() {
  QStringList capabilities = QStringList() << "canWatchFieldModification"
                                           << "canWatchFieldAccess"
                                           << "canGetBytecodes"
                                           << "canGetSyntheticAttribute"
                                           << "canGetOwnedMonitorInfo"
                                           << "canGetCurrentContendedMonitor"
                                           << "canGetMonitorInfo";

  for (int i = 0; i < capabilities.size(); i++) {
    auto t = new QTableWidgetItem(capabilities[i]);
    t->setFlags(t->flags() ^ Qt::ItemIsEditable);
    capabilitiesTable->setItem(i, 0, t);
  }

  capabilitiesTable->resizeColumnsToContents();
}
void VmCapabilitiesPanel::insertValue(int row, bool value) {
  auto t = new QTableWidgetItem(value ? "Yes" : "No");
  t->setFlags(t->flags() ^ Qt::ItemIsEditable);
  capabilitiesTable->setItem(row, 1, t);
}

void VmCapabilitiesPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineCapabilitiesData *>(reply->data);
    insertValue(0, data->can_watch_field_modification);
    insertValue(1, data->can_watch_field_access);
    insertValue(2, data->can_get_bytecodes);
    insertValue(3, data->can_get_synthetic_attribute);
    insertValue(4, data->can_get_owned_monitor_info);
    insertValue(5, data->can_get_current_contended_monitor);
    insertValue(6, data->can_get_monitor_info);
  } else {
    for (int i = 0; i < 7; i++) {
      insertValue(0, false);
    }
  }
  setJdwpError(reply->error);
}

void VmCapabilitiesPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_CAPABILITIES);
}
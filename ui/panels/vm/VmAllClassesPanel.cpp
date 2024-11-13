#include <QTimer>

#include "VmAllClassesPanel.h"

#include <QHeaderView>
#include <QMessageBox>

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"
VmAllClassesPanel::VmAllClassesPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmAllClassesPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  classesTree = new QTableWidget();
  classesTree->setColumnCount(4);
  classesTree->setHorizontalHeaderLabels(QStringList() << "refTypeTag"
                                                       << "typeId"
                                                       << "signature"
                                                       << "status");
  classesTree->horizontalHeader()->setStretchLastSection(true);
  classesTree->verticalHeader()->setVisible(false);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Classes", classesTree);

  setupConnections();
}

void VmAllClassesPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineAllClassesCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_ALL_CLASSES);
}
QString VmAllClassesPanel::getPanelTitle() {
  return "Virtual Machine :: All Classes";
}

QString VmAllClassesPanel::getHelpText() {
  return "<p>Returns reference types for all classes currently loaded by the "
         "target VM. See JVM TI GetLoadedClasses.</p>";
}

QString VmAllClassesPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_AllClasses");
}

void VmAllClassesPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmAllClassesPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmAllClassesPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineAllClasses, this,
            &VmAllClassesPanel::onReply);
  });
}

void VmAllClassesPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineAllClassesData *>(reply->data);

    classesTree->setRowCount(data->classes);
    for (int i = 0; i < data->classes; i++) {
      JdwpVirtualMachineAllClassesClassData d = data->classes_data[i];

      auto *rtt = new QTableWidgetItem(
          JdwpConstantsMapper::getTypeTagString(d.ref_type_tag));
      rtt->setFlags(rtt->flags() ^ Qt::ItemIsEditable);
      auto *id = new QTableWidgetItem(QString::number(d.type_id));
      id->setFlags(id->flags() ^ Qt::ItemIsEditable);
      auto *sig = new QTableWidgetItem(QString(d.signature));
      sig->setFlags(sig->flags() ^ Qt::ItemIsEditable);
      auto *status =
          new QTableWidgetItem(JdwpConstantsMapper::getStatusString(d.status));
      status->setFlags(status->flags() ^ Qt::ItemIsEditable);

      classesTree->setItem(i, 0, rtt);
      classesTree->setItem(i, 1, id);
      classesTree->setItem(i, 2, sig);
      classesTree->setItem(i, 3, status);
    }

    classesTree->resizeColumnToContents(0);
    classesTree->resizeColumnToContents(1);
    classesTree->resizeColumnToContents(2);

  } else {
    this->classesTree->clear();
  }
  setJdwpError(reply->error);
}
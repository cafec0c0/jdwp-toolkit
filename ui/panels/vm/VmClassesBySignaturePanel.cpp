#include <QTimer>

#include "VmClassesBySignaturePanel.h"

#include <QHeaderView>

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"
VmClassesBySignaturePanel::VmClassesBySignaturePanel(ApplicationContext *ctx,
                                                     QWidget *parent)
    : BasePanel(VmClassesBySignaturePanel::getPanelTitle(), parent), ctx(ctx) {

  signatureEdit = new QLineEdit();

  classesTree = new QTableWidget();
  classesTree->setColumnCount(3);
  classesTree->setHorizontalHeaderLabels(QStringList() << "refTypeTag"
                                                       << "typeId"
                                                       << "status");
  classesTree->horizontalHeader()->setStretchLastSection(true);
  classesTree->verticalHeader()->setVisible(false);

  inputLayout->addRow("Signature", signatureEdit);

  outputLayout->addRow("Classes", classesTree);

  setupConnections();
}

QString VmClassesBySignaturePanel::getPanelTitle() {
  return "Virtual Machine :: Classes By Signature";
}

QString VmClassesBySignaturePanel::getHelpText() {
  return "<p>Returns reference types for all the classes loaded by the target "
         "VM which match the given signature. Multiple reference types will be "
         "returned if two or more class loaders have loaded a class of the "
         "same name. The search is confined to loaded classes only; no attempt "
         "is made to load a class of the given signature.</p>";
}

QString VmClassesBySignaturePanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand(
      "JDWP_VirtualMachine_ClassesBySignature");
}

void VmClassesBySignaturePanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmClassesBySignaturePanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmClassesBySignaturePanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineClassesBySignature, this,
            &VmClassesBySignaturePanel::onReply);
  });
}

void VmClassesBySignaturePanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data =
        static_cast<JdwpVirtualMachineClassesBySignatureData *>(reply->data);

    classesTree->setRowCount(data->classes);
    for (int i = 0; i < data->classes; i++) {
      JdwpVirtualMachineClassesBySignatureClassData d = data->classes_data[i];

      auto *rtt = new QTableWidgetItem(
          JdwpConstantsMapper::getTypeTagString(d.ref_type_tag));
      rtt->setFlags(rtt->flags() ^ Qt::ItemIsEditable);
      auto *id = new QTableWidgetItem(QString::number(d.type_id));
      id->setFlags(id->flags() ^ Qt::ItemIsEditable);
      auto *status =
          new QTableWidgetItem(JdwpConstantsMapper::getStatusString(d.status));
      status->setFlags(status->flags() ^ Qt::ItemIsEditable);

      classesTree->setItem(i, 0, rtt);
      classesTree->setItem(i, 1, id);
      classesTree->setItem(i, 2, status);
    }

    classesTree->resizeColumnToContents(0);
    classesTree->resizeColumnToContents(1);
    classesTree->resizeColumnToContents(2);

  } else {
    this->classesTree->clear();
  }
  setJdwpError(reply->error);
}

void VmClassesBySignaturePanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  char *data = (char *)malloc(signatureEdit->text().size());
  strcpy(data, signatureEdit->text().toStdString().c_str());

  JdwpVirtualMachineClassesBySignatureCommand cmd = {.signature = data};
  client->send(&cmd, client->nextId(),
               JDWP_VIRTUAL_MACHINE_CLASSES_BY_SIGNATURE);
  free(data);
  // TODO error popup
}
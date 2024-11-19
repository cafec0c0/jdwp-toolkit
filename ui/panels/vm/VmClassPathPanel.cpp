#include <QTimer>

#include "VmClassPathPanel.h"

#include <QHeaderView>
#include <QMessageBox>

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"
VmClassPathPanel::VmClassPathPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmClassPathPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  baseDirEdit = new QLineEdit();
  baseDirEdit->setReadOnly(true);

  classPathsTree = new QTableWidget();
  classPathsTree->setColumnCount(1);
  classPathsTree->horizontalHeader()->setStretchLastSection(true);
  classPathsTree->verticalHeader()->setVisible(false);
  classPathsTree->horizontalHeader()->setVisible(false);

  bootClassPathsTree = new QTableWidget();
  bootClassPathsTree->setColumnCount(1);
  bootClassPathsTree->horizontalHeader()->setStretchLastSection(true);
  bootClassPathsTree->verticalHeader()->setVisible(false);
  bootClassPathsTree->horizontalHeader()->setVisible(false);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Base Dir", baseDirEdit);
  outputLayout->addRow("Class Paths", classPathsTree);
  outputLayout->addRow("Boot Class Paths", bootClassPathsTree);

  setupConnections();
}

void VmClassPathPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpLibError e =
      client->send(nullptr, client->nextId(), JDWP_VIRTUAL_MACHINE_CLASS_PATHS);
  qDebug() << e;
}
QString VmClassPathPanel::getPanelTitle() {
  return "Virtual Machine :: Class Paths";
}

QString VmClassPathPanel::getHelpText() {
  return "<p>Retrieve the classpath and bootclasspath of the target VM. If the "
         "classpath is not defined, returns an empty list. If the "
         "bootclasspath is not defined returns an empty list. </p>";
}

QString VmClassPathPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_ClassPaths");
}

void VmClassPathPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmClassPathPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this, &VmClassPathPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineClassPaths, this,
            &VmClassPathPanel::onReply);
  });
}

void VmClassPathPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineClassPathsData *>(reply->data);

    baseDirEdit->setText(data->base_dir);

    classPathsTree->setRowCount(data->class_paths);
    for (int i = 0; i < data->class_paths; i++) {
      auto *rtt = new QTableWidgetItem(data->class_paths_data[i]);
      rtt->setFlags(rtt->flags() ^ Qt::ItemIsEditable);
      classPathsTree->setItem(i, 0, rtt);
    }

    bootClassPathsTree->setRowCount(data->boot_class_paths);
    for (int i = 0; i < data->boot_class_paths; i++) {
      auto *rtt = new QTableWidgetItem(data->boot_class_paths_data[i]);
      rtt->setFlags(rtt->flags() ^ Qt::ItemIsEditable);
      bootClassPathsTree->setItem(i, 0, rtt);
    }
  } else {
    this->classPathsTree->clear();
    this->bootClassPathsTree->clear();
  }
  setJdwpError(reply->error);
}
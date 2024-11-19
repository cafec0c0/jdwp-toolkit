#include "VmDisposeObjectsPanel.h"

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

#include <QHeaderView>
#include <QTableWidgetItem>

VmDisposeObjectsPanel::VmDisposeObjectsPanel(ApplicationContext *ctx,
                                             QWidget *parent)
    : BasePanel(VmDisposeObjectsPanel::getPanelTitle(), parent), ctx(ctx) {
  newRowButton = new QPushButton("Add");
  deleteRowButton = new QPushButton("Delete");

  QHBoxLayout *hbox = new QHBoxLayout();
  hbox->addStretch();
  hbox->addWidget(newRowButton);
  hbox->addWidget(deleteRowButton);

  inputLayout->addRow(hbox);

  objectList = new QTableWidget();
  objectList->setColumnCount(2);
  objectList->horizontalHeader()->setStretchLastSection(true);
  objectList->setHorizontalHeaderLabels(QStringList() << "object"
                                                      << "refCnt");
  objectList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  objectList->verticalHeader()->setVisible(false);
  objectList->setSelectionMode(QAbstractItemView::SingleSelection);

  inputLayout->addRow("Objects", objectList);

  noOutputLabel = new QLabel("This command does not produce any reply data.");
  outputLayout->addRow(noOutputLabel);

  errorLayout->removeRow(0);
  noErrorLabel = new QLabel("This command does not produce any error data.");
  errorLayout->addRow(noErrorLabel);

  setupConnections();
}

QString VmDisposeObjectsPanel::getPanelTitle() {
  return "Virtual Machine :: Dispose Objects";
}

QString VmDisposeObjectsPanel::getHelpText() {
  return "<p>Releases a list of object IDs. For each object in the list, the "
         "following applies. The count of references held by the back-end (the "
         "reference count) will be decremented by refCnt. If thereafter the "
         "reference count is less than or equal to zero, the ID is freed. Any "
         "back-end resources associated with the freed ID may be freed, and if "
         "garbage collection was disabled for the object, it will be "
         "re-enabled. The sender of this command promises that no further "
         "commands will be sent referencing a freed ID.</p>"
         "<p>Use of this command is not required. If it is not sent, resources "
         "associated with each ID will be freed by the back-end at some time "
         "after the corresponding object is garbage collected. It is most "
         "useful to use this command to reduce the load on the back-end if a "
         "very large number of objects has been retrieved from the back-end (a "
         "large array, for example) but may not be garbage collected any time "
         "soon. </p>"
         "<p>IDs may be re-used by the back-end after they have been freed "
         "with this command.This description assumes reference counting, a "
         "back-end may use any implementation which operates equivalently. "
         "</p>";
}

QString VmDisposeObjectsPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_DisposeObjects");
}

void VmDisposeObjectsPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmDisposeObjectsPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmDisposeObjectsPanel::showHelp);

  connect(newRowButton, &QPushButton::clicked, this,
          &VmDisposeObjectsPanel::addRow);

  connect(deleteRowButton, &QPushButton::clicked, this,
          &VmDisposeObjectsPanel::deleteRow);
}

void VmDisposeObjectsPanel::onReply(JdwpReply *reply) {}

void VmDisposeObjectsPanel::sendCommand() {
  auto client = ctx->vmController()->connection();

  auto *data = static_cast<JdwpVirtualMachineDisposeObjectsObjectData *>(
      calloc(objectList->rowCount(),
             sizeof(JdwpVirtualMachineDisposeObjectsObjectData)));
  for (int i = 0; i < objectList->rowCount(); i++) {
    qDebug() << i << objectList->item(i, 0)->text();
    qDebug() << i << objectList->item(i, 1)->text();
    data[i].object = objectList->item(i, 0)->text().toULongLong();
    data[i].ref_cnt = objectList->item(i, 1)->text().toULong();
  }
  JdwpVirtualMachineDisposeObjectsCommand cmd = {
      .requests = static_cast<uint32_t>(objectList->rowCount()),
      .requests_data = data};
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_DISPOSE_OBJECTS);
}

void VmDisposeObjectsPanel::addRow() {
  objectList->setRowCount(objectList->rowCount() + 1);
}

void VmDisposeObjectsPanel::deleteRow() {
  if (objectList->rowCount() == 0)
    return;

  auto r = objectList->selectedRanges().first();
  objectList->removeRow(r.topRow());
}
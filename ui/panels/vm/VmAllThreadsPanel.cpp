#include <QTimer>

#include "VmAllThreadsPanel.h"

#include <QHeaderView>

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmAllThreadsPanel::VmAllThreadsPanel(ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmAllThreadsPanel::getPanelTitle(), parent), ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  threadsTree = new QTableWidget();
  threadsTree->setColumnCount(1);
  threadsTree->setHorizontalHeaderLabels(QStringList() << "thread");
  threadsTree->horizontalHeader()->setStretchLastSection(true);
  threadsTree->verticalHeader()->setVisible(false);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Threads", threadsTree);

  setupConnections();
}
void VmAllThreadsPanel::onReply(JdwpReply *reply) {
  if (reply->data) {
    auto *data = static_cast<JdwpVirtualMachineAllThreadsData *>(reply->data);

    threadsTree->setRowCount(static_cast<int>(data->threads));
    for (int i = 0; i < data->threads; i++) {
      JdwpVirtualMachineAllThreadsThread d = data->threads_data[i];

      auto *t = new QTableWidgetItem(QString::number(d.thread));
      t->setFlags(t->flags() ^ Qt::ItemIsEditable);

      threadsTree->setItem(i, 0, t);
    }
  } else {
    this->threadsTree->clear();
  }
  setJdwpError(reply->error);
}

void VmAllThreadsPanel::sendCommand() {
  auto client = ctx->vmController()->connection();
  JdwpVirtualMachineAllThreadsCommand cmd;
  client->send(&cmd, client->nextId(), JDWP_VIRTUAL_MACHINE_ALL_THREADS);
}

QString VmAllThreadsPanel::getPanelTitle() {
  return "Virtual Machine :: All Threads";
}

QString VmAllThreadsPanel::getHelpText() {
  return "<p>Returns the live threads in the target VM. Threads that have not "
         "yet "
         "started or threads that have terminated are not included in the list."
         "The returned list contains a threadID for each live platform thread "
         "in the target VM. This includes platform threads created with the "
         "Thread API and all native threads attached to the target VM with JNI "
         "code.</p>"

         "<p>It is implementation dependent if the list contains threadIDs for "
         "live virtual threads in the target VM. The target VM may not return "
         "threadIDs for virtual threads, or it may be configured to return a "
         "threadID for some or all virtual threads.</p>";
}

QString VmAllThreadsPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand("JDWP_VirtualMachine_AllThreads");
}

void VmAllThreadsPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmAllThreadsPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmAllThreadsPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineAllThreads, this,
            &VmAllThreadsPanel::onReply);
  });
}

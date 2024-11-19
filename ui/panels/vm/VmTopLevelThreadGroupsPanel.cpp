#include <QTimer>

#include "VmTopLevelThreadGroupsPanel.h"

#include <QHeaderView>

#include "util/JdwpConstantsMapper.h"
#include "util/UrlMapper.h"

VmTopLevelThreadGroupsPanel::VmTopLevelThreadGroupsPanel(
    ApplicationContext *ctx, QWidget *parent)
    : BasePanel(VmTopLevelThreadGroupsPanel::getPanelTitle(), parent),
      ctx(ctx) {
  noArgsLabel = new QLabel("This command does not take any out data.");

  threadsTree = new QTableWidget();
  threadsTree->setColumnCount(1);
  threadsTree->setHorizontalHeaderLabels(QStringList() << "group");
  threadsTree->horizontalHeader()->setStretchLastSection(true);
  threadsTree->verticalHeader()->setVisible(false);

  inputLayout->addRow(noArgsLabel);

  outputLayout->addRow("Groups", threadsTree);

  setupConnections();
}
void VmTopLevelThreadGroupsPanel::onReply(JdwpReply *reply) {
  qDebug() << "recv";
  if (reply->data) {
    qDebug() << "has data";
    auto *data =
        static_cast<JdwpVirtualMachineTopLevelThreadGroupsData *>(reply->data);

    threadsTree->setRowCount(static_cast<int>(data->groups));
    for (int i = 0; i < data->groups; i++) {
      JdwpVirtualMachineTopLevelThreadGroupsGroup d = data->groups_data[i];

      auto *t = new QTableWidgetItem(QString::number(d.group));
      t->setFlags(t->flags() ^ Qt::ItemIsEditable);

      threadsTree->setItem(i, 0, t);
    }
  } else {
    this->threadsTree->clear();
  }
  setJdwpError(reply->error);
}

void VmTopLevelThreadGroupsPanel::sendCommand() {
  qDebug() << "sending";
  auto client = ctx->vmController()->connection();
  qDebug() << "client" << client;

  auto e = client->send(nullptr, client->nextId(),
                        JDWP_VIRTUAL_MACHINE_TOP_LEVEL_THREAD_GROUPS);
  qDebug() << "send err:" << e;
}

QString VmTopLevelThreadGroupsPanel::getPanelTitle() {
  return "Virtual Machine :: Top Level Thread Groups";
}

QString VmTopLevelThreadGroupsPanel::getHelpText() {
  return "<p>Returns all thread groups that do not have a parent. This command "
         "may be used as the first step in building a tree (or trees) of the "
         "existing thread groups.</p>";
}

QString VmTopLevelThreadGroupsPanel::getHelpUrl() {
  return UrlMapper::getUrlForJdwpCommand(
      "JDWP_VirtualMachine_TopLevelThreadGroups");
}

void VmTopLevelThreadGroupsPanel::setupConnections() {
  connect(sendButton, &QPushButton::clicked, this,
          &VmTopLevelThreadGroupsPanel::sendCommand);

  connect(helpButton, &QPushButton::clicked, this,
          &VmTopLevelThreadGroupsPanel::showHelp);

  connect(this->ctx->vmController(), &VmController::connectionAdded, [this] {
    connect(this->ctx->vmController()->connection(),
            &JdwpClientWrapper::virtualMachineTopLevelThreadGroups, this,
            &VmTopLevelThreadGroupsPanel::onReply);
  });
}

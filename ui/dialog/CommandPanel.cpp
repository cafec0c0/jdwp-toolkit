#include "CommandPanel.h"

#include "ui/panels/vm/VmAllClassesPanel.h"
#include "ui/panels/vm/VmAllThreadsPanel.h"
#include "ui/panels/vm/VmCapabilitiesNewPanel.h"
#include "ui/panels/vm/VmCapabilitiesPanel.h"
#include "ui/panels/vm/VmClassPathPanel.h"
#include "ui/panels/vm/VmClassesBySignaturePanel.h"
#include "ui/panels/vm/VmCreateStringPanel.h"
#include "ui/panels/vm/VmDisposeObjectsPanel.h"
#include "ui/panels/vm/VmDisposePanel.h"
#include "ui/panels/vm/VmExitPanel.h"
#include "ui/panels/vm/VmHoldEventsPanel.h"
#include "ui/panels/vm/VmIdSizesPanel.h"
#include "ui/panels/vm/VmIndexPanel.h"
#include "ui/panels/vm/VmReleaseEventsPanel.h"
#include "ui/panels/vm/VmResumePanel.h"
#include "ui/panels/vm/VmSuspendPanel.h"
#include "ui/panels/vm/VmTopLevelThreadGroupsPanel.h"

CommandPanel::CommandPanel(ApplicationContext *ctx, QWidget *parent)
    : QWidget(parent), ctx(ctx) {
  setWindowTitle("Add Panel");

  this->layout = new QHBoxLayout();
  stack = new QStackedWidget();

  setupVmCommands();
  setupTree();

  layout->addWidget(commandTree);
  layout->addWidget(stack);
  setLayout(layout);

  connect(commandTree, &QTreeWidget::itemSelectionChanged, [this] {
    auto item = commandTree->selectedItems().first();
    // Search VM command items
    for (auto it : vmItems) {
      if (item == it.first)
        stack->setCurrentWidget(it.second);
    }
  });
}

void CommandPanel::navigateToVmCommand(int index) {
  auto item = vmItems[index];
  this->commandTree->setCurrentItem(item.first);
  stack->setCurrentWidget(item.second);
}

void CommandPanel::setupTree() {
  this->commandTree = new QTreeWidget();
  this->commandTree->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  this->commandTree->setHeaderHidden(true);

  this->commandTree->addTopLevelItem(vmItems[0].first);
}

static QTreeWidgetItem *createWidgetItem(QString text,
                                         QTreeWidgetItem *parent = nullptr) {
  auto *item = new QTreeWidgetItem();
  item->setText(0, text);

  if (parent)
    parent->addChild(item);

  return item;
}

void CommandPanel::setupVmCommands() {
  QTreeWidgetItem *vmRoot = createWidgetItem("Virtual Machine");

  auto *index = new VmIndexPanel(ctx);
  connect(index, &VmIndexPanel::navigateToIndex, this,
          &CommandPanel::navigateToVmCommand);

  auto *version = new VmVersionPanel(ctx);
  vmItems = {
      {0, {vmRoot, index}},
      {1, {createWidgetItem("Version", vmRoot), version}},
      {2,
       {createWidgetItem("Classes By Signature", vmRoot),
        new VmClassesBySignaturePanel(ctx)}},
      {3,
       {createWidgetItem("All Classes", vmRoot), new VmAllClassesPanel(ctx)}},
      {4,
       {createWidgetItem("All Threads", vmRoot), new VmAllThreadsPanel(ctx)}},
      {5,
       {createWidgetItem("Top Level Thread Groups", vmRoot),
        new VmTopLevelThreadGroupsPanel(ctx)}},
      {6, {createWidgetItem("Dispose", vmRoot), new VmDisposePanel(ctx)}},
      {7, {createWidgetItem("ID Sizes", vmRoot), new VmIdSizesPanel(ctx)}},
      {8, {createWidgetItem("Suspend", vmRoot), new VmSuspendPanel(ctx)}},
      {9, {createWidgetItem("Resume", vmRoot), new VmResumePanel(ctx)}},
      {10, {createWidgetItem("Exit", vmRoot), new VmExitPanel(ctx)}},
      {11,
       {createWidgetItem("Create String", vmRoot),
        new VmCreateStringPanel(ctx)}},
      {12,
       {createWidgetItem("Capabilities", vmRoot),
        new VmCapabilitiesPanel(ctx)}},
      {13,
       {createWidgetItem("Class Paths", vmRoot), new VmClassPathPanel(ctx)}},
      {14,
       {createWidgetItem("Dispose Objects", vmRoot),
        new VmDisposeObjectsPanel(ctx)}},
      {15,
       {createWidgetItem("Hold Events", vmRoot), new VmHoldEventsPanel(ctx)}},
      {16,
       {createWidgetItem("Release Events", vmRoot),
        new VmReleaseEventsPanel(ctx)}},
      {17,
       {createWidgetItem("Capabilities New", vmRoot),
        new VmCapabilitiesNewPanel(ctx)}}};

  for (auto key : vmItems) {
    stack->addWidget(key.second);
  }
}
#include "VmIndexPanel.h"

#include <QDesktopServices>
#include <QLabel>

static QString docsLink =
    "https://docs.oracle.com/en/java/javase/23/docs/specs/jdwp/"
    "jdwp-protocol.html#JDWP_VirtualMachine";

static QString content =
    QString("<h3>Virtual Machine</h3>"
            "<p>Commands related to the Virtual Machine.</p>"
            "<p>Docs: <a href=\"%1\">docs.oracle.com</a></p>"
            "<p>Available commands:</p>"
            "<ul>"
            "<li><a href=\"index:1\">Version</a></li>"
            "<li><a href=\"index:2\">Classes By Signature</a></li>"
            "<li><a href=\"index:3\">All Classes</a></li>"
            "<li><a href=\"index:4\">All Threads</a></li>"
            "<li><a href=\"index:5\">Top Level Thread Groups</a></li>"
            "<li><a href=\"index:6\">Dispose</a></li>"
            "<li><a href=\"index:7\">Id Sizes</a></li>"
            "<li><a href=\"index:8\">Suspend</a></li>"
            "<li><a href=\"index:9\">Resume</a></li>"
            "<li><a href=\"index:10\">Exit</a></li>"
            "<li><a href=\"index:11\">Create String</a></li>"
            "<li><a href=\"index:12\">Capabilities</a></li>"
            "<li><a href=\"index:13\">Class Paths</a></li>"
            "<li><a href=\"index:14\">Dispose Objects</a></li>"
            "<li><a href=\"index:15\">Hold Events</a></li>"
            "<li><a href=\"index:16\">Release Events</a></li>"
            "<li><a href=\"index:17\">Capabilities New</a></li>"
            "</ul>")
        .arg(docsLink);

VmIndexPanel::VmIndexPanel(ApplicationContext *ctx, QWidget *parent)
    : QWidget(parent), ctx(ctx) {
  layout = new QVBoxLayout();

  QLabel *label = new QLabel(content);
  label->setWordWrap(true);
  label->setTextInteractionFlags(Qt::LinksAccessibleByMouse |
                                 Qt::LinksAccessibleByKeyboard);

  connect(label, &QLabel::linkActivated, [this](const QString &link) {
    if (link.startsWith("http")) {
      QDesktopServices::openUrl(link);
      return;
    }
    emit navigateToIndex(link.split(":").last().toInt());
  });

  layout->addWidget(label);
  layout->addStretch(1);

  setLayout(layout);
}
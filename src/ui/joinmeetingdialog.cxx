#include "ui/joinmeetingdialog.hxx"
#include "ui_joinmeetingdialog.h"

#include "controller/interactionmgr.hxx"
#include "controller/meeting.hxx"

#include <vector>

JoinMeetingDialog::JoinMeetingDialog(QWidget* parent)
    : QDialog(parent)
    , m_parent(parent)
    , m_ui(new Ui::JoinMeetingDialog)
{
    m_ui->setupUi(this);
    m_ui->meetingIdField->addItem("admin");
    m_ui->meetingIdField->addItem("meeting_1");

    connectSlots();
}

JoinMeetingDialog::~JoinMeetingDialog()
{
    delete m_ui;
}

void JoinMeetingDialog::connectSlots()
{
    connect(m_ui->joinMeetBtn, &QPushButton::clicked, this,
            &JoinMeetingDialog::onJoinMeetingClicked);
}

void JoinMeetingDialog::onJoinMeetingClicked()
{
    Controller::InteractionMgr* controller =
        Controller::InteractionMgr::GetManager();
    std::vector<QWidget*> widgets = {this, m_parent};
    Controller::Meeting* meetingCtrl =
        controller->GetController<Controller::Meeting>();
    meetingCtrl->SwitchToMeeting(widgets);
}

#include "ui/joinmeetingdialog.hxx"
#include "ui_joinmeetingdialog.h"

#include "controller/controllermgr.hxx"
#include "controller/meetingctrl.hxx"

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
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    std::vector<QWidget*> widgets = {this, m_parent};
    Controller::MeetingCtrl* meetingCtrl =
        controller->GetController<Controller::MeetingCtrl>();
    meetingCtrl->SwitchToMeetingCtrl(widgets);
}

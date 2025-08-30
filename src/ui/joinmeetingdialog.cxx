#include "ui/joinmeetingdialog.hxx"
#include "ui_joinmeetingdialog.h"
#include "controller/controllermgr.hxx"
#include "controller/meetingctrl.hxx"
#include "types/meetinginfo.hxx"

#include <vector>

JoinMeetingDialog::JoinMeetingDialog(QWidget* parent)
    : QDialog(parent)
    , m_parent(parent)
    , m_ui(new Ui::JoinMeetingDialog)
    , m_cachedMeetings()
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    fillCachedMeetingNames();
    initPasswordEye();
    connectSlots();
}

JoinMeetingDialog::~JoinMeetingDialog()
{
    delete m_ui;
}

void JoinMeetingDialog::connectSlots()
{
    connect(m_ui->showPwdIcon, &QPushButton::clicked, this,
            &JoinMeetingDialog::changePassShowState);
    connect(m_ui->joinMeetBtn, &QPushButton::clicked, this,
            &JoinMeetingDialog::onJoinMeetingClicked);
    connect(m_ui->meetingIdField, QOverload<int>::of(
                &QComboBox::currentIndexChanged),
            this, &JoinMeetingDialog::onComboBoxIndexChanged);
}

void JoinMeetingDialog::fillCachedMeetingNames()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::MeetingCtrl* meetingCtrl =
        controller->GetController<Controller::MeetingCtrl>();
    meetingCtrl->GetCachedMeetings(m_cachedMeetings);
    for ( const auto& info : m_cachedMeetings )
    {
        m_ui->meetingIdField->addItem(info.GetName().c_str());
    }
}

void JoinMeetingDialog::initPasswordEye()
{
    m_ui->showPwdIcon->setIcon(m_eyeOpened);
}

void JoinMeetingDialog::changePassShowState()
{
    if ( QLineEdit::Password == m_ui->passwordField->echoMode() )
    {
        m_ui->showPwdIcon->setIcon(m_eyeClosed);
        m_ui->passwordField->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        m_ui->showPwdIcon->setIcon(m_eyeOpened);
        m_ui->passwordField->setEchoMode(QLineEdit::Password);
    }
}

void JoinMeetingDialog::onJoinMeetingClicked()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    std::vector<QWidget*> widgets = {this, m_parent};
    Controller::MeetingCtrl* meetingCtrl =
        controller->GetController<Controller::MeetingCtrl>();
    MeetingInfo info("MeetingName", "Password");
    //meetingCtrl->AddMeetingInfoToRTDB(info);
    meetingCtrl->SwitchToMeetingCtrl(widgets);
}

void JoinMeetingDialog::onComboBoxIndexChanged(int i)
{
    m_ui->passwordField->setText(m_cachedMeetings[i].GetRealPassword().c_str());
}

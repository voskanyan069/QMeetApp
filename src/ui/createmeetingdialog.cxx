#include "ui/createmeetingdialog.hxx"
#include "ui_createmeetingdialog.h"
#include "ui/popupdialog.hxx"
#include "controller/controllermgr.hxx"
#include "controller/meetingctrl.hxx"
#include "types/meetinginfo.hxx"
#include "types/exception.hxx"
#include "net/curlclient.hxx"

CreateMeetingDialog::CreateMeetingDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::CreateMeetingDialog)
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    initPasswordEye();
    connectSlots();
}

CreateMeetingDialog::~CreateMeetingDialog()
{
    delete m_ui;
}

void CreateMeetingDialog::connectSlots()
{
    connect(m_ui->showPwdIcon, &QPushButton::clicked, this,
            &CreateMeetingDialog::changePassShowState);
    connect(m_ui->createMeetingBtn, &QPushButton::clicked, this,
            &CreateMeetingDialog::doCreateMeeting);
}

void CreateMeetingDialog::initPasswordEye()
{
    m_ui->showPwdIcon->setIcon(m_eyeOpened);
}

void CreateMeetingDialog::changePassShowState()
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

void CreateMeetingDialog::doCreateMeeting()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::MeetingCtrl* meetingCtrl =
        controller->GetController<Controller::MeetingCtrl>();
    std::string meetname(m_ui->meetingIdField->text().toStdString());
    std::string password(m_ui->passwordField->text().toStdString());
    MeetingInfo info(meetname, password);
    try
    {
        meetingCtrl->CreateMeeting(info);
        meetingCtrl->AddCachedMeetingInfo(info);
    }
    catch (const Exception& e)
    {
        PopupDialog dialog(this, PopupBoxType::BOX_WITH_CLOSE,
                (PopupMessageType)(e.type()), e.what());
        dialog.exec();
        return;
    }
    this->close();
}

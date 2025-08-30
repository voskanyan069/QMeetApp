#include "ui/createmeetingdialog.hxx"
#include "ui_createmeetingdialog.h"

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

#include "ui/signuppopup.hxx"
#include "ui/loginpopup.hxx"
#include "ui_signuppopup.h"

SignupPopup::SignupPopup(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::SignupPopup)
    , m_parent(parent)
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    initPasswordEye();
    connectSlots();
}

SignupPopup::~SignupPopup()
{
    delete m_ui;
}

void SignupPopup::connectSlots()
{
    connect(m_ui->showPwdCB, &QPushButton::clicked, this,
            &SignupPopup::changePassShowState);
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &SignupPopup::openLogInDialog);
}

void SignupPopup::initPasswordEye()
{
    m_ui->showPwdCB->setIcon(m_eyeOpened);
}

void SignupPopup::changePassShowState()
{
    if ( QLineEdit::Password == m_ui->passwordField->echoMode() )
    {
        m_ui->showPwdCB->setIcon(m_eyeClosed);
        m_ui->passwordField->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        m_ui->showPwdCB->setIcon(m_eyeOpened);
        m_ui->passwordField->setEchoMode(QLineEdit::Password);
    }
}

void SignupPopup::openLogInDialog()
{
    LoginPopup* login = new LoginPopup(m_parent);
    this->close();
    login->exec();
}

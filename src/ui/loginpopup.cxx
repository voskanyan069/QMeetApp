#include "ui/loginpopup.hxx"
#include "ui/signuppopup.hxx"
#include "ui_loginpopup.h"

LoginPopup::LoginPopup(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::LoginPopup)
    , m_parent(parent)
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    initPasswordEye();
    connectSlots();
}

LoginPopup::~LoginPopup()
{
    delete m_ui;
}

void LoginPopup::connectSlots()
{
    connect(m_ui->showPwdCB, &QPushButton::clicked, this,
            &LoginPopup::changePassShowState);
    connect(m_ui->createAccountBtn, &QPushButton::clicked, this,
            &LoginPopup::openSignUpDialog);
}

void LoginPopup::initPasswordEye()
{
    m_ui->showPwdCB->setIcon(m_eyeOpened);
}

void LoginPopup::changePassShowState()
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

void LoginPopup::openSignUpDialog()
{
    SignupPopup* signup = new SignupPopup(m_parent);
    this->close();
    signup->exec();
}

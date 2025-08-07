#include "ui/signupdialog.hxx"
#include "ui/logindialog.hxx"
#include "ui_signupdialog.h"

SignupDialog::SignupDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::SignupDialog)
    , m_parent(parent)
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    initPasswordEye();
    connectSlots();
}

SignupDialog::~SignupDialog()
{
    delete m_ui;
}

void SignupDialog::connectSlots()
{
    connect(m_ui->showPwdCB, &QPushButton::clicked, this,
            &SignupDialog::changePassShowState);
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &SignupDialog::openLogInDialog);
}

void SignupDialog::initPasswordEye()
{
    m_ui->showPwdCB->setIcon(m_eyeOpened);
}

void SignupDialog::changePassShowState()
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

void SignupDialog::openLogInDialog()
{
    LoginDialog* login = new LoginDialog(m_parent);
    this->close();
    login->exec();
}

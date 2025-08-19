#include "ui/logindialog.hxx"
#include "ui/signupdialog.hxx"
#include "controller/controllermgr.hxx"
#include "controller/accountctrl.hxx"
#include "types/user.hxx"
#include "net/curlclient.hxx"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::LoginDialog)
    , m_parent(parent)
    , m_eyeOpened(":/icons/eye_opened.png")
    , m_eyeClosed(":/icons/eye_closed.png")
{
    m_ui->setupUi(this);
    initPasswordEye();
    connectSlots();
}

LoginDialog::~LoginDialog()
{
    delete m_ui;
}

void LoginDialog::connectSlots()
{
    connect(m_ui->showPwdCB, &QPushButton::clicked, this,
            &LoginDialog::changePassShowState);
    connect(m_ui->createAccountBtn, &QPushButton::clicked, this,
            &LoginDialog::openSignUpDialog);
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &LoginDialog::doLogIn);
}

void LoginDialog::initPasswordEye()
{
    m_ui->showPwdCB->setIcon(m_eyeOpened);
}

void LoginDialog::changePassShowState()
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

void LoginDialog::openSignUpDialog()
{
    SignupDialog* signup = new SignupDialog(m_parent);
    this->close();
    signup->exec();
}

void LoginDialog::doLogIn()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::AccountCtrl* accountCtrl =
        controller->GetController<Controller::AccountCtrl>();
    std::string username(m_ui->usernameField->text().toStdString());
    std::string password(m_ui->passwordField->text().toStdString());
    User user(username, password);
    if ( accountCtrl->IsExists(user) )
    {
    }
}

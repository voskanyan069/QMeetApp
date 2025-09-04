#include "ui/signupdialog.hxx"
#include "ui_signupdialog.h"
#include "ui/logindialog.hxx"
#include "ui/popupdialog.hxx"
#include "controller/controllermgr.hxx"
#include "controller/accountctrl.hxx"
#include "types/user.hxx"
#include "types/exception.hxx"
#include "net/curlclient.hxx"

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
    connect(m_ui->createAccountBtn, &QPushButton::clicked, this,
            &SignupDialog::doCreateAccount);
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

void SignupDialog::doCreateAccount()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::AccountCtrl* accountCtrl =
        controller->GetController<Controller::AccountCtrl>();
    std::string username(m_ui->usernameField->text().toStdString());
    std::string password(m_ui->passwordField->text().toStdString());
    User user(username, password);
    try
    {
        accountCtrl->CreateAccount(user);
        accountCtrl->SetMyUsername(username);
        accountCtrl->AddCachedAccount({username, password});
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

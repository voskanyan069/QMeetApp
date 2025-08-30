#include "ui/mainwindow.hxx"
#include "ui/logindialog.hxx"
#include "ui/createmeetingdialog.hxx"
#include "ui/joinmeetingdialog.hxx"
#include "ui/popupdialog.hxx"
#include "controller/controllermgr.hxx"
#include "controller/accountctrl.hxx"
#include "io/camera.hxx"
#include "sys/macro.hxx"
#include "types/exception.hxx"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connectSlots();
    tryLocalLogin();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::connectSlots()
{
    m_ui->createMeetBtn->setEnabled(false);
    m_ui->joinMeetBtn->setText("Join Meeting As Guest");
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &MainWindow::onLoginBtnClicked);
    connect(m_ui->createMeetBtn, &QPushButton::clicked, this,
            &MainWindow::onCreateMeetingBtnClicked);
    connect(m_ui->joinMeetBtn, &QPushButton::clicked, this,
            &MainWindow::onJoinMeetingBtnClicked);
}

void MainWindow::tryLocalLogin()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::AccountCtrl* accountCtrl =
        controller->GetController<Controller::AccountCtrl>();
    PureUser user;
    try
    {
        if ( !accountCtrl->CachedLogIn(user) )
        {
            accountCtrl->LogOut();
            return;
        }
        accountCtrl->SetMyUsername(user.username);
        User hashUser(user.username, "");
        hashUser.SetPassword(user.password);
        if ( accountCtrl->IsExists(hashUser) )
        {
            onLoginSuccess();
        }
        else
        {
            accountCtrl->LogOut();
        }
    }
    catch (const Exception& e)
    {
        accountCtrl->LogOut(true);
        std::cout << " [LOG] " << e.what() << std::endl;
        return;
    }
}

void MainWindow::onLoginSuccess()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::AccountCtrl* accountCtrl =
        controller->GetController<Controller::AccountCtrl>();
    std::string username;
    try
    {
        accountCtrl->GetMyUsername(username);
    }
    catch (const Exception& e)
    {
        std::cout << " [LOG] " << e.what() << std::endl;
        return;
    }
    m_ui->createMeetBtn->setEnabled(true);
    m_ui->joinMeetBtn->setText("Join Meeting");
    m_ui->loginBtn->setText(username.c_str());
    m_ui->loginBtn->disconnect();
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &MainWindow::onUsernameClicked);
}

void MainWindow::onLogOut()
{
    Controller::ControllerMgr* controller =
        Controller::ControllerMgr::GetManager();
    Controller::AccountCtrl* accountCtrl =
        controller->GetController<Controller::AccountCtrl>();
    try
    {
        accountCtrl->LogOut();
    }
    catch (const Exception& e)
    {
        PopupDialog dialog(this, PopupBoxType::BOX_WITH_CLOSE,
                (PopupMessageType)(e.type()), e.what());
        dialog.exec();
        return;
    }
    m_ui->createMeetBtn->setEnabled(false);
    m_ui->joinMeetBtn->setText("Join Meeting As Guest");
    m_ui->loginBtn->setText("Log In");
    m_ui->loginBtn->disconnect();
    connect(m_ui->loginBtn, &QPushButton::clicked, this,
            &MainWindow::onLoginBtnClicked);
}

void MainWindow::onLoginBtnClicked()
{
    LoginDialog login(this);
    login.exec();
    onLoginSuccess();
}

void MainWindow::onUsernameClicked()
{
    bool bResult = false;
    PopupDialog dialog(this, &bResult, PopupMessageType::INFO,
            "Do you want to log out?");
    dialog.exec();
    if (bResult)
    {
        onLogOut();
    }
}

void MainWindow::onCreateMeetingBtnClicked()
{
    CreateMeetingDialog createMeet(this);
    createMeet.exec();
}

void MainWindow::onJoinMeetingBtnClicked()
{
    JoinMeetingDialog joinMeet(this);
    joinMeet.exec();
}

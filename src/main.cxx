#include "ui/mainwindow.hxx"

#include "controller/controllermgr.hxx"
#include "controller/clientctrl.hxx"
#include "net/client.hxx"
#include "net/curlclient.hxx"

#include <QApplication>
#include <QFont>

Controller::ControllerMgr* mgr = nullptr;
Controller::ClientCtrl* ctrl = nullptr;

void initializeClients()
{
    mgr = Controller::ControllerMgr::GetManager();
    ctrl = mgr->GetController<Controller::ClientCtrl>();
    ctrl->AddClient("account",
            new Net::CURLClient("http://0.0.0.0:55005", "/api/v1/account"));
    ctrl->AddClient("meeting",
            new Net::CURLClient("http://0.0.0.0:55005", "/api/v1/meeting"));
}

void finalizeClients()
{
    ctrl->DisconnectClients();
}

int main(int argc, char *argv[])
{
    initializeClients();
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Segoe UI, Ubuntu, Noto Sans, Arial");
    a.setFont(font);
    MainWindow w;
    w.show();
    int rc = a.exec();
    finalizeClients();
    return rc;
}

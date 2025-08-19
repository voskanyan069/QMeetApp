#include "ui/mainwindow.hxx"

#include "controller/controllermgr.hxx"
#include "controller/clientctrl.hxx"
#include "net/client.hxx"
#include "net/curlclient.hxx"

#include <QApplication>
#include <QFont>

void initializeClients()
{
    Controller::ControllerMgr* mgr = Controller::ControllerMgr::GetManager();
    Controller::ClientCtrl* ctrl = mgr->GetController<Controller::ClientCtrl>();
    ctrl->AddClient("account",
            new Net::CURLClient("http://0.0.0.0:55005", "/api/v1/account"));
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
    return a.exec();
}

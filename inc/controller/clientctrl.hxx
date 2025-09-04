#ifndef __CONTROLLER_CLIENT_CTRL_HXX__
#define __CONTROLLER_CLIENT_CTRL_HXX__

#include "controller/controller.hxx"

#include <string>
#include <map>

namespace Net
{
    class Client;
}

namespace Controller
{
    class ControllerMgr;
    class ClientCtrl;
}

class Controller::ClientCtrl : public Controller::Controller
{
    friend class ControllerMgr;

private:
    ClientCtrl();

public:
    ~ClientCtrl();
    ClientCtrl(const ClientCtrl&) = delete;
    ClientCtrl& operator=(const ClientCtrl&) = delete;

public:
    void AddClient(const std::string& name, Net::Client* client);
    Net::Client* GetClient(const std::string& name);
    void DisconnectClients();

private:
    std::map<std::string, Net::Client*> m_clientMap;
};

#endif // !__CONTROLLER_CLIENT_CTRL_HXX__

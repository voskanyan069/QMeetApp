#include "controller/clientctrl.hxx"
#include "net/client.hxx"

Controller::ClientCtrl::ClientCtrl()
    : m_clientMap()
{
}

Controller::ClientCtrl::~ClientCtrl()
{
    for ( auto& it : m_clientMap )
    {
        if ( nullptr != it.second )
        {
            delete it.second;
        }
    }
    m_clientMap.clear();
}

void Controller::ClientCtrl::AddClient(const std::string& name,
        Net::Client* client)
{
    m_clientMap[name] = client;
}

Net::Client* Controller::ClientCtrl::GetClient(const std::string& name)
{
    auto it = m_clientMap.find(name);
    if ( m_clientMap.end() == it )
    {
        return nullptr;
    }
    return it->second;
}

void Controller::ClientCtrl::DisconnectClients()
{
    for ( auto& cl : m_clientMap )
    {
        cl.second->Disconnect();
        delete cl.second;
    }
    m_clientMap.clear();
}

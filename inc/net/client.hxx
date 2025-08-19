#ifndef __NET_CLIENT_HXX__
#define __NET_CLIENT_HXX__

#include <string>

namespace Net
{
    class Client;
    enum class ConnState
    {
        eIdle = 0,
        eNotReachable,
        eConnected
    };
}

class Net::Client
{
public:
    Client(const std::string& sHost = "", const std::string& sApiBase = "")
        : m_sHost(sHost)
        , m_sApiBase(sApiBase)
    {
    }
    virtual ~Client() = default;

public:
    virtual void ConnectToServer(const std::string& sHost = "",
            const std::string& sApiBase = "") = 0;
    virtual Net::ConnState GetConnectionState() = 0;
    virtual void Disconnect() = 0;
    virtual void SendGetRequest(const std::string& url,
            const std::string& params="", std::string* response=nullptr) = 0;
    virtual void SendPostRequest(const std::string& url,
            const std::string& params="") = 0;

protected:
    virtual void tryPingServer() = 0;
    virtual bool doHostVerification() = 0;

protected:
    std::string m_sHost;
    std::string m_sApiBase;
};

#endif // ! __NET_CLIENT_HXX__

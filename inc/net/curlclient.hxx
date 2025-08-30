#ifndef __NET_CURL_CLIENT_HXX__
#define __NET_CURL_CLIENT_HXX__

#include "net/client.hxx"

#include <nlohmann/json.hpp>
#include <curl/curl.h>

namespace Net
{
    class CURLClient;
};

class Net::CURLClient : public Net::Client
{
public:
    CURLClient(const std::string& sHost = "", const std::string& sApiBase = "");
    virtual ~CURLClient();

public:
    virtual void ConnectToServer(const std::string& sHost = "",
            const std::string& sApiBase = "") override;
    virtual Net::ConnState GetConnectionState() override;
    virtual void Disconnect() override;
    virtual void SendGetRequest(const std::string& url,
            const std::string& params="",std::string* response=nullptr)override;
    virtual void SendGetRequest(const std::string& url,
            const std::string& params, nlohmann::json& jsonData) override;
    virtual void SendPostRequest(const std::string& url,
            const std::string& params="") override;

protected:
    virtual void tryPingServer() override;
    virtual bool doHostVerification() override;

private:
    CURL* m_curl;
};

#endif // ! __NET_CURL_CLIENT_HXX__

#include "net/curlclient.hxx"

static size_t __writeCallback(void* contents, size_t size, size_t nmemb,
        void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Net::CURLClient::CURLClient(const std::string& sHost, const std::string& sApiB)
    : Net::Client(sHost, sApiB)
    , m_curl(nullptr)
{
}

Net::CURLClient::~CURLClient()
{
    Disconnect();
}

void Net::CURLClient::ConnectToServer(const std::string& sHost,
        const std::string& sApiBase)
{
    if ( !sHost.empty() )
    {
        m_sHost = sHost;
    }
    if ( !sApiBase.empty() )
    {
        m_sApiBase = sApiBase;
    }
    m_curl = curl_easy_init();
}

Net::ConnState Net::CURLClient::GetConnectionState()
{
    return Net::ConnState::eIdle;
}

void Net::CURLClient::Disconnect()
{
}

void Net::CURLClient::SendGetRequest(const std::string& url,
        const std::string& params, std::string* response)
{
    if ( nullptr == m_curl )
    {
        fprintf(stdout, "curl is null\n");
        return;
    }
    CURLcode res;
    std::string sURL = m_sHost + m_sApiBase + url + "?" + params;
    fprintf(stdout, "Sending request to: %s\n", sURL.c_str());
    curl_easy_setopt(m_curl, CURLOPT_URL, sURL.c_str());
    if ( nullptr != response )
    {
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, __writeCallback);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, response);
    }
    res = curl_easy_perform(m_curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    curl_easy_cleanup(m_curl);
}

void Net::CURLClient::SendPostRequest(const std::string& url,
        const std::string& params)
{
}

void Net::CURLClient::tryPingServer()
{
}

bool Net::CURLClient::doHostVerification()
{
    return true;
}

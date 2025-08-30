#include "controller/accountctrl.hxx"
#include "controller/clientctrl.hxx"
#include "controller/controllermgr.hxx"
#include "types/exception.hxx"
#include "net/client.hxx"
#include "db/rtdb.hxx"

#include <nlohmann/json.hpp>

#include <iostream>

Controller::AccountCtrl::AccountCtrl()
    : m_client(nullptr)
    , m_bLoginStatus(false)
    , m_sMyUsername()
{
    ControllerMgr* mgr = ControllerMgr::GetManager();
    ClientCtrl* ctrl = mgr->GetController<ClientCtrl>();
    m_client = ctrl->GetClient("account");
    m_client->ConnectToServer();
}

void Controller::AccountCtrl::CreateAccount(const User& user)
{
    if ( nullptr == m_client )
    {
        return;
    }
    nlohmann::json jsonData;
    m_client->SendGetRequest("/create",
            "username=" + user.GetUsername() +
            "&password=" + user.GetPassword(), jsonData);
}

void Controller::AccountCtrl::DeleteAccount(const User& user)
{
}

bool Controller::AccountCtrl::IsExists(const User& user)
{
    if ( nullptr == m_client )
    {
        return false;
    }
    nlohmann::json jsonData;
    m_client->SendGetRequest("/is_exists",
            "username=" + user.GetUsername() +
            "&password=" + user.GetPassword(), jsonData);
    try
    {
        bool exists = jsonData["exists"];
        return exists;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
}

void Controller::AccountCtrl::UpdateUsername(const User& user,
        const std::string& newUsername)
{
}

void Controller::AccountCtrl::UpdatePassword(const User& user,
        const std::string& newPassword)
{
}

void Controller::AccountCtrl::SetMyUsername(const std::string& username)
{
    if ( m_bLoginStatus )
    {
        throw Exception("You are already logged in");
    }
    m_sMyUsername = username;
    m_bLoginStatus = true;
}

void Controller::AccountCtrl::LogOut(bool bNoExcept)
{
    if ( !m_bLoginStatus )
    {
        if (bNoExcept)
        {
            return;
        }
        throw Exception("You are not logged in");
    }
    m_sMyUsername = "";
    m_bLoginStatus = false;
    AddCachedAccount({"", ""});
}

bool Controller::AccountCtrl::GetLogInStatus()
{
    return m_bLoginStatus;
}

void Controller::AccountCtrl::GetMyUsername(std::string& username)
{
    if ( !m_bLoginStatus )
    {
        throw Exception("You are not logged in");
    }
    username = m_sMyUsername;
}

void Controller::AccountCtrl::AddCachedAccount(const PureUser& user)
{
    DB::RTDB* pRTDB = DB::RTDB::GetInstance();
    nlohmann::json jsonData;
    pRTDB->GetJson(jsonData);
    User hashUser("", user.password);
    try
    {
        jsonData["account"]["username"] = user.username;
        if ("" == user.password)
        {
            jsonData["account"]["password"] = "";
        }
        else
        {
            jsonData["account"]["password"] = hashUser.GetPassword();
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
    std::cout << "DumpToFile: " << jsonData << std::endl;
    pRTDB->DumpToFile(jsonData);
}

bool Controller::AccountCtrl::CachedLogIn(PureUser& user)
{
    DB::RTDB* pRTDB = DB::RTDB::GetInstance();
    nlohmann::json jsonData;
    pRTDB->GetJson(jsonData);
    try
    {
        nlohmann::json account = jsonData["account"];
        user.username = account["username"];
        user.password = account["password"];
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
    if ( user.username.empty() || user.password.empty() )
    {
        return false;
    }
    return true;
}

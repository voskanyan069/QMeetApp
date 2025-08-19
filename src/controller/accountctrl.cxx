#include "controller/accountctrl.hxx"
#include "controller/clientctrl.hxx"
#include "controller/controllermgr.hxx"
#include "net/client.hxx"

#include <iostream>

Controller::AccountCtrl::AccountCtrl()
    : m_client(nullptr)
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
    m_client->SendGetRequest("/create",
            "username=" + user.GetUsername() +
            "&password=" + user.GetPassword());
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
    std::string response;
    m_client->SendGetRequest("/is_exists",
            "username=" + user.GetUsername() +
            "&password=" + user.GetPassword(), &response);
    std::cout << "response: " << response << std::endl;
}

void Controller::AccountCtrl::UpdateUsername(const User& user,
        const std::string& newUsername)
{
}

void Controller::AccountCtrl::UpdatePassword(const User& user,
        const std::string& newPassword)
{
}

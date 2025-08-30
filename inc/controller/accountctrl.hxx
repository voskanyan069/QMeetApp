#ifndef __CONTROLLER_ACCOUNT_CTRL_HXX__
#define __CONTROLLER_ACCOUNT_CTRL_HXX__

#include "controller/controller.hxx"
#include "types/user.hxx"

namespace Net
{
    class Client;
}

namespace Controller
{
    class ControllerMgr;
    class AccountCtrl;
}

class Controller::AccountCtrl : public Controller::Controller
{
    friend class ControllerMgr;

private:
    AccountCtrl();

public:
    ~AccountCtrl();
    AccountCtrl(const AccountCtrl&) = delete;
    AccountCtrl& operator=(const AccountCtrl&) = delete;

public:
    void CreateAccount(const User& user);
    void DeleteAccount(const User& user);
    bool IsExists(const User& username);
    void UpdateUsername(const User& user, const std::string& newUsername);
    void UpdatePassword(const User& user, const std::string& newPassword);

public:
    void SetMyUsername(const std::string& username);
    void LogOut(bool bNoExcept = false);
    bool GetLogInStatus();
    void GetMyUsername(std::string& username);
    void AddCachedAccount(const PureUser& user);
    bool CachedLogIn(PureUser& user);

private:
    Net::Client* m_client;
    bool m_bLoginStatus;
    std::string m_sMyUsername;
};

#endif // !__CONTROLLER_ACCOUNT_CTRL_HXX__

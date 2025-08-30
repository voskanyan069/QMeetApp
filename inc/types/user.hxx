#ifndef __TYPES_USER_HXX__
#define __TYPES_USER_HXX__

#include "hash/sha256.hxx"
#include <string>

struct PureUser
{
    std::string username;
    std::string password;
};

class User
{
public:
    User();
    explicit User(const std::string& username, const std::string& password,
            Hash::HashBase* hasher = Hash::SHA256::GetInstance());
    ~User() = default;

public:
    std::string GetUsername() const;
    std::string GetPassword() const;
    void SetPassword(const std::string& hashPass);

private:
    void hash(Hash::HashBase*, const std::string& src, std::string& result);

private:
    std::string m_username;
    std::string m_password;
};

#endif // ! __TYPES_USER_HXX__

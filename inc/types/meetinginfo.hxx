#ifndef __TYPES_MEETING_INFO_HXX__
#define __TYPES_MEETING_INFO_HXX__

#include "hash/sha256.hxx"
#include <string>

class MeetingInfo
{
public:
    MeetingInfo();
    explicit MeetingInfo(const std::string& name, const std::string& password,
            Hash::HashBase* hasher = Hash::SHA256::GetInstance());
    ~MeetingInfo() = default;

public:
    std::string GetID() const;
    std::string GetName() const;
    std::string GetPassword() const;
    std::string GetRealPassword() const;

private:
    void hash(Hash::HashBase*, const std::string& src, std::string& result);

private:
    std::string m_meetingName;
    std::string m_meetingId;
    std::string m_meetingPassword;
    std::string m_meetingRealPassword;
};

#endif // ! __TYPES_MEETING_INFO_HXX__

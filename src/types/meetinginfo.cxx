#include "types/meetinginfo.hxx"
#include "hash/hash.hxx"

MeetingInfo::MeetingInfo()
    : m_meetingName()
    , m_meetingId()
    , m_meetingPassword()
    , m_meetingRealPassword()
{
}

MeetingInfo::MeetingInfo(const std::string& name, const std::string& password,
        Hash::HashBase* hasher)
    : m_meetingName(name)
    , m_meetingId()
    , m_meetingPassword()
    , m_meetingRealPassword(password)
{
    hash(hasher, name, m_meetingId);
    hash(hasher, password, m_meetingPassword);
}

std::string MeetingInfo::GetName() const
{
    return m_meetingName;
}

std::string MeetingInfo::GetID() const
{
    return m_meetingId;
}

std::string MeetingInfo::GetRealPassword() const
{
    return m_meetingRealPassword;
}

std::string MeetingInfo::GetPassword() const
{
    return m_meetingPassword;
}

void MeetingInfo::hash(Hash::HashBase* hasher, const std::string& src,
        std::string& result)
{
    hasher->Hash(src, result);
}

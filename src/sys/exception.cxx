#include "sys/exception.hxx"

Sys::Exception::Exception(const std::string& message)
        : m_sMsg(message)
{
}

const char* Sys::Exception::what() const noexcept
{
    return m_sMsg.c_str();
}

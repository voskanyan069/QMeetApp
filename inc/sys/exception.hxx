#ifndef __SYS_EXCEPTION_HXX__
#define __SYS_EXCEPTION_HXX__

#include <string>
#include <exception>

namespace Sys
{
    class Exception;
}

class Sys::Exception : public std::exception
{
public:
    explicit Exception(const std::string& message);
    virtual const char* what() const noexcept override;

private:
    std::string m_sMsg;
};

#endif // !__SYS_EXCEPTION_HXX__

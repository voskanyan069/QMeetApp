#ifndef __TYPES_EXCEPTION_HXX__
#define __TYPES_EXCEPTION_HXX__

#include <exception>
#include <string>

enum class ExceptionType
{
    INFO,
    WARNING,
    ERROR
};

class Exception : public std::exception
{
public:
    explicit Exception(const std::string& msg,
            const ExceptionType& type = ExceptionType::ERROR)
        : m_message(msg)
        , m_type(type)
    {
    }

    virtual const char* what() const noexcept override
    {
        return m_message.c_str();
    }

    virtual ExceptionType type() const noexcept
    {
        return m_type;
    }

private:
    std::string m_message;
    ExceptionType m_type;
};

#endif // ! __TYPES_EXCEPTION_HXX__

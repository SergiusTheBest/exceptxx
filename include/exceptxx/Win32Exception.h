#pragma once
#include <exceptxx/BaseException.h>
#include <exceptxx/ThrowHelper.h>
#include <exceptxx/Util.h>

namespace exceptxx
{
    class Win32Exception : public BaseException
    {
    public:
        using Error = winapi::DWORD;

        Win32Exception(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
            return winapi::HresultFromWin32(m_error);
        }

        virtual const char* tag() const override
        {
            return "WIN32";
        }

        virtual string error() const override
        {
            ostringstream ss;
            ss << m_error;

            return ss.str();
        }

        virtual string description() const override
        {
            return formatMessage(m_error);
        }

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const Error m_error;
    };
}

#define THROW_WIN32(error)              THROW_HELPER(Win32Exception, error)
#define CHECK_WIN32(error)              if (auto exceptxxLocalError = error) THROW_WIN32(exceptxxLocalError)
#define THROW_LAST_WIN32()              THROW_WIN32(exceptxx::winapi::GetLastError())
#define THROW_WIN32_IF(cond, error)     if (cond) THROW_WIN32(error)
#define THROW_LAST_WIN32_IF(cond)       if (cond) THROW_LAST_WIN32()
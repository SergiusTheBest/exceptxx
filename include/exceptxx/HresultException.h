#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>
#include <exceptxx/ThrowHelper.h>

namespace exceptxx
{
    class HresultException : public BaseExceptionImpl<HresultException>
    {
    public:
        using Error = HRESULT;

        HresultException(Error error, const char* func, size_t line, string&& message) : BaseExceptionImpl(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
            return m_error;
        }

        virtual const char* tag() const override
        {
            return "HRESULT";
        }

        virtual string error() const override
        {
            ostringstream ss;
            ss << "0x" << hex << uppercase << m_error;

            return ss.str();
        }

        virtual string description() const override
        {
            return formatMessage(m_error);
        }

    private:
        const Error m_error;
    };
}

#define THROW_HRESULT(error)            THROW_HELPER(HresultException, error)
#define CHECK_HRESULT(error)            if (auto exceptxxLocalError = static_cast<exceptxx::HresultException::Error>(error)) if (exceptxxLocalError < 0) THROW_HRESULT(exceptxxLocalError)
#define THROW_LAST_HRESULT()            THROW_HRESULT(exceptxx::HresultFromWin32(exceptxx::GetLastError()))
#define THROW_HRESULT_IF(cond, error)   if (cond) THROW_HRESULT(error)
#define THROW_LAST_HRESULT_IF(cond)     if (cond) THROW_LAST_HRESULT()

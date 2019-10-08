#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>
#include <exceptxx/ThrowHelper.h>

namespace exceptxx
{
    class NtstatusException : public BaseExceptionImpl<NtstatusException>
    {
    public:
        using Error = NTSTATUS;

        NtstatusException(Error error, const char* func, size_t line, string&& message) : BaseExceptionImpl(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
            return HresultFromNt(m_error);
        }

        virtual const char* tag() const override
        {
            return "NTSTATUS";
        }

        virtual string error() const override
        {
            ostringstream ss;
            ss << "0x" << hex << uppercase << m_error;

            return ss.str();
        }

        virtual string description() const override
        {
            return formatMessage(m_error, GetModuleHandleW(L"ntdll"));
        }

    private:
        const Error m_error;
    };
}

#define THROW_NTSTATUS(error)           THROW_HELPER(NtstatusException, error)
#define CHECK_NTSTATUS(error)           if (auto exceptxxLocalError = static_cast<exceptxx::NtstatusException::Error>(error)) if (exceptxxLocalError < 0) THROW_NTSTATUS(error)
#define THROW_NTSTATUS_IF(cond, error)  if (cond) THROW_NTSTATUS(error)

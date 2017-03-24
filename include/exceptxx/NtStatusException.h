#pragma once
#include <exceptxx/BaseException.h>
#include <exceptxx/ThrowHelper.h>
#include <exceptxx/Util.h>

namespace exceptxx
{
    class NtStatusException : public BaseException
    {
    public:
        using Error = winapi::NTSTATUS;

        NtStatusException(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
            return winapi::HresultFromNt(m_error);
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
            return formatMessage(m_error, winapi::GetModuleHandleW(L"ntdll"));
        }

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const Error m_error;
    };
}

#define THROW_NTSTATUS(error)           THROW_HELPER(NtStatusException, error)
#define CHECK_NTSTATUS(error)           if (auto exceptxxLocalError = error) if (exceptxxLocalError < 0) THROW_NTSTATUS(error)
#define THROW_NTSTATUS_IF(cond, error)  if (cond) THROW_NTSTATUS(error)
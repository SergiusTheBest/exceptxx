#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>
#include <exceptxx/ThrowHelper.h>

namespace exceptxx
{
    class PrecondException : public BaseExceptionImpl<PrecondException>
    {
    public:
        using Error = string;

        PrecondException(Error error, const char* func, size_t line, string&& message) : BaseExceptionImpl(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
#ifdef _WIN32
            return HR_E_INVALIDARG;
#else
            return EINVAL;
#endif
        }

        virtual const char* tag() const override
        {
            return "PRECOND";
        }

        virtual string error() const override
        {
            return m_error;
        }

        virtual string description() const override
        {
            return "Precondition failed";
        }

    private:
        const Error m_error;
    };
}

#define THROW_PRECOND()         THROW_HELPER(PrecondException, "")
#define CHECK_PRECOND(cond)     if (!(cond)) THROW_HELPER(PrecondException, #cond)

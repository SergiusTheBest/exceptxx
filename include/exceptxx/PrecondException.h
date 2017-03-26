#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseException.h>
#include <exceptxx/ThrowHelper.h>

namespace exceptxx
{
    class PrecondException : public BaseException
    {
    public:
        using Error = string;

        PrecondException(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
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

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const Error m_error;
    };
}

#define CHECK_PRECOND(cond)     if (!(cond)) THROW_HELPER(PrecondException, #cond)

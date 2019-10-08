#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>
#include <exceptxx/ThrowHelper.h>
#include <cassert>

namespace exceptxx
{
    class AssertException : public BaseExceptionImpl<AssertException>
    {
    public:
        using Error = string;

        AssertException(Error error, const char* func, size_t line, string&& message) : BaseExceptionImpl(func, line, move(message)), m_error(error)
        {
        }

        virtual const char* tag() const override
        {
            return "ASSERT";
        }

        virtual string error() const override
        {
            return m_error;
        }

        virtual string description() const override
        {
            return "Assertion failed";
        }

    private:
        const Error m_error;
    };
}

#define CHECK_ASSERT(cond)      if (!(cond)) assert(!#cond),THROW_HELPER(AssertException, #cond)

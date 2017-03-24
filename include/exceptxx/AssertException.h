#pragma once
#include <exceptxx/BaseException.h>
#include <cassert>

namespace exceptxx
{
    class AssertException : public BaseException
    {
    public:
        using Error = string;

        AssertException(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
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

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const Error m_error;
    };
}

#define CHECK_ASSERT(cond)          if (!cond) assert(!#cond),THROW_HELPER(AssertException, #cond)
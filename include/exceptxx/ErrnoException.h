#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseException.h>
#include <exceptxx/ThrowHelper.h>

namespace exceptxx
{
    class ErrnoException : public BaseException
    {
    public:
        using Error = int;

        ErrnoException(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
#ifdef _WIN32
            return kFailure;
#else
            return m_error;
#endif
        }

        virtual const char* tag() const override
        {
            return "ERRNO";
        }

        virtual string error() const override
        {
            ostringstream ss;
            ss << m_error;

            return ss.str();
        }

        virtual string description() const override
        {
            char buffer[0x200] = {};

            if (0 != ::strerror_s(buffer, sizeof(buffer), m_error))
            {
                return "Unknown error code";
            }

            return buffer;
        }

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const Error m_error;
    };
}

#define THROW_ERRNO(error)          THROW_HELPER(ErrnoException, error)
#define CHECK_ERRNO(error)          if (auto exceptxxLocalError = (error)) THROW_ERRNO(exceptxxLocalError)
#define THROW_LAST_ERRNO()          THROW_ERRNO(errno)
#define THROW_ERRNO_IF(cond, error) if (cond) THROW_ERRNO(error)
#define THROW_LAST_ERRNO_IF(cond)   if (cond) THROW_LAST_ERRNO()

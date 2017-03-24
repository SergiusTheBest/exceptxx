#pragma once
#include <exceptxx/BaseException.h>

namespace exceptxx
{
    class StdException : public BaseException
    {
    public:
        StdException(const char* func, size_t line, string&& message) : BaseException(func, line, move(message))
        {
        }

        virtual const char* tag() const override
        {
            return "C++";
        }

        virtual string error() const override
        {
            return "std::exception";
        }

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }
    };
}

#define MAKE_STD_EXCEPTION(e)   std::unique_ptr<exceptxx::BaseException>(new exceptxx::StdException(__func__, __LINE__, e.what()))
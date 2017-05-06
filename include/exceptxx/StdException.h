#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseException.h>

namespace exceptxx
{
    class StdException : public BaseException
    {
    public:
        StdException(string description, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_description(description)
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

        virtual string description() const override
        {
            return m_description;
        }

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return cloneMoveImpl(this);
        }

    private:
        const string m_description;
    };
}

#define EXCEPTXX_MAKE_STD_EXCEPTION(e)   std::unique_ptr<exceptxx::BaseException>(new exceptxx::StdException(e.what(), EXCEPTXX_GET_FUNC(), __LINE__, ""))

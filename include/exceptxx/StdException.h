#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>

namespace exceptxx
{
    class StdException : public BaseExceptionImpl<StdException>
    {
    public:
        StdException(string description, const char* func, size_t line, string&& message) : BaseExceptionImpl(func, line, move(message)), m_description(description)
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

    private:
        const string m_description;
    };
}

#define EXCEPTXX_MAKE_STD_EXCEPTION(e)   std::unique_ptr<exceptxx::BaseException>(new exceptxx::StdException(e.what(), EXCEPTXX_GET_FUNC(), __LINE__, ""))

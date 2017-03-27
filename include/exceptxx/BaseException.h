#pragma once
#include <exceptxx/Util.h>
#include <exception>
#include <string>
#include <memory>
#include <sstream>

namespace exceptxx
{
    using namespace std;

    class BaseException : public exception
    {
    public:
        ///////////////////////////////////////////////////
        // Error code definitions (platform dependent)

#ifdef _WIN32
        using Code = HRESULT;
        static const Code kSuccess = HR_S_OK;
        static const Code kFailure = HR_E_FAIL;
#else
        using Code = int;
        static const Code kSuccess = 0;
        static const Code kFailure = -1;
#endif

        BaseException(const char* func, size_t line, string&& message) : m_func(func), m_line(line), m_message(move(message))
        {
        }

        ///////////////////////////////////////////////////
        // Non-virtual getters

        const char* func() const
        {
            return m_func;
        }

        size_t line() const
        {
            return m_line;
        }

        const string& message() const
        {
            return m_message;
        }

        ///////////////////////////////////////////////////
        // Virtual getters

        virtual Code code() const
        {
            return kFailure;
        }

        virtual const char* tag() const = 0;

        virtual string error() const = 0;

        virtual string description() const
        {
            return "";
        }

        ///////////////////////////////////////////////////
        // Clone movable interface

        virtual unique_ptr<BaseException> cloneMove() = 0;

        ///////////////////////////////////////////////////
        // std::exception interface

        virtual char const* what() const EXCEPTXX_NOEXCEPT override
        {
            if (m_what.empty())
            {
                ostringstream ss;
                ss << "Text: ";

                string desc = description();

                if (!m_message.empty())
                {
                    ss << m_message;

                    if (!desc.empty())
                    {
                        ss << " (" << desc << ")";
                    }

                    ss << endl;
                }
                else if (!desc.empty())
                {
                    ss << desc << endl;
                }

                ss << "Error: " << error() << " (" << tag() << ")" << endl;
                ss << "Source: " << m_func << ":" << m_line;

                m_what = ss.str();
            }

            return m_what.c_str();
        }        

    protected:
        template<class T>
        unique_ptr<BaseException> cloneMoveImpl(T* p)
        {
            return unique_ptr<BaseException>(new T(move(*p)));
        }

    private:
        const char* const m_func;
        const size_t m_line;
        const string m_message;
        mutable string m_what;
    };
}

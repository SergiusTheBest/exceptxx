#pragma once
#include <exception>
#include <memory>
#include <sstream>
#include <exceptxx/Util.h>

namespace exceptxx
{
    using namespace std;

    class BaseException : public exception
    {
    public:
#ifdef _WIN32
        using Code = winapi::HRESULT;
        static const Code kSuccess = winapi::HR_S_OK;
        static const Code kFailure = winapi::HR_E_FAIL;
#else
        using Code = int;
        static const Code kSuccess = 0;
        static const Code kFailure = -1;
#endif

        BaseException(const char* func, size_t line, string&& message) : m_func(func), m_line(line), m_message(move(message))
        {
        }

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

        virtual unique_ptr<BaseException> cloneMove() = 0;

        virtual char const* what() const
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
                ss << "Source: " << m_func << ":" << m_line << endl;

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
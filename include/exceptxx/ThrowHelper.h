#pragma once
#include <sstream>

namespace exceptxx
{
    using namespace std;

    template<class T>
    struct ThrowHelper
    {
        using Error = typename T::Error;

        ThrowHelper(Error error, const char* func, size_t line) : m_error(error), m_func(func), m_line(line)
        {
        }

        void operator<<=(const basic_ostream<char>& ostr)
        {
            throw T(m_error, m_func, m_line, static_cast<const ostringstream&>(ostr).str());
        }

        const Error m_error;
        const char* const m_func;
        const size_t m_line;
    };
}

#define THROW_HELPER(type, code)    exceptxx::ThrowHelper<exceptxx::type>(code, __func__, __LINE__) <<= std::ostringstream()
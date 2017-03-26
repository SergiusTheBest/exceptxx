#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseException.h>

namespace exceptxx
{
    using namespace std;

    class ExceptionHolder
    {
    public:
        void operator=(unique_ptr<BaseException>&& ex)
        {
            m_ex = move(ex);
        }

        operator BaseException::Code() const
        {
            return code();
        }

        operator bool() const
        {
            return !!m_ex;
        }

        BaseException::Code code() const
        {
            if (!m_ex)
            {
                return BaseException::kSuccess;
            }

            return m_ex->code();
        }

        const BaseException* operator->() const
        {
            return m_ex.get();
        }

        void reset()
        {
            m_ex.reset();
        }

    private:
        unique_ptr<BaseException> m_ex;
    };
}

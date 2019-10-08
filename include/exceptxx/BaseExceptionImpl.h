#pragma once
#include <exceptxx/BaseException.h>
#include <memory>

namespace exceptxx
{
    using namespace std;

    template<class T>
    class BaseExceptionImpl : public BaseException
    {
    public:
        using BaseException::BaseException;

        virtual unique_ptr<BaseException> cloneMove() override
        {
            return unique_ptr<BaseException>(new T(move(*static_cast<T*>(this))));
        }

        virtual void rethrow() override
        {
            throw *static_cast<T*>(this);
        }
    };
}

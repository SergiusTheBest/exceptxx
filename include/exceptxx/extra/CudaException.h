#pragma once
#include <exceptxx/Util.h>
#include <exceptxx/BaseExceptionImpl.h>
#include <exceptxx/ThrowHelper.h>
#include <cuda_runtime_api.h>

namespace exceptxx
{
    class CudaException : public BaseExceptionImpl<CudaException>
    {
    public:
        using Error = cudaError_t;

        CudaException(Error error, const char* func, size_t line, string&& message) : BaseException(func, line, move(message)), m_error(error)
        {
        }

        virtual Code code() const override
        {
            return m_error;
        }

        virtual const char* tag() const override
        {
            return "CUDA";
        }

        virtual string error() const override
        {
            ostringstream ss;
            ss << m_error;

            return ss.str();
        }

        virtual string description() const override
        {
            return cudaGetErrorString(m_error);
        }

    private:
        const Error m_error;
    };
}

#define THROW_CUDA(error)            THROW_HELPER(CudaException, error)
#define CHECK_CUDA(error)            if (auto exceptxxLocalError = static_cast<exceptxx::CudaException::Error>(error)) THROW_CUDA(exceptxxLocalError)
#define CHECK_LAST_CUDA()            CHECK_CUDA(cudaGetLastError())

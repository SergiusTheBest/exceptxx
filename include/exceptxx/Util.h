#pragma once
#include <string>

namespace exceptxx
{
    using namespace std;

#ifdef _MSC_VER
#   define EXCEPTXX_WHAT_NOEXCEPT
#else
#   define EXCEPTXX_WHAT_NOEXCEPT   noexcept
#endif

#ifdef _MSC_VER
#   define EXCEPTXX_GET_FUNC()      __FUNCTION__
#elif defined(__BORLANDC__)
#   define EXCEPTXX_GET_FUNC()      __FUNC__
#else
#   define EXCEPTXX_GET_FUNC()      __PRETTY_FUNCTION__
#endif

#ifdef _MSC_VER
#   define EXCEPTXX_NORETURN        __declspec(noreturn)
#elif defined(__GNUC__)
#   define EXCEPTXX_NORETURN        __attribute__((__noreturn__))
#else
#   define EXCEPTXX_NORETURN
#endif

#ifdef _WIN32
    using HRESULT = long;
    using DWORD = unsigned long;
    using NTSTATUS = long;
    using HMODULE = void*;

    const HRESULT HR_S_OK = 0;
    const HRESULT HR_E_FAIL = 0x80004005L;
    const HRESULT HR_E_INVALIDARG = 0x80000003L;

    const DWORD kFormatIgnoreInserts = 0x00000200;
    const DWORD kFormatFromHmodule = 0x00000800;
    const DWORD kFormatFromSystem = 0x00001000;
    const DWORD kFormatMaxWidthMask = 0x000000FF;

    enum
    {
        kFacilityWin32 = 7,
        kFacilityNtBit = 0x10000000
    };

    inline HRESULT HresultFromWin32(DWORD x)
    {
        return static_cast<HRESULT>(x) <= 0 ? static_cast<HRESULT>(x) : static_cast<HRESULT>((x & 0x0000FFFF) | (kFacilityWin32 << 16) | 0x80000000);
    }

    inline HRESULT HresultFromNt(NTSTATUS x)
    {
        return static_cast<HRESULT>(x | kFacilityNtBit);
    }

    extern "C" __declspec(dllimport) DWORD __stdcall GetLastError();
    extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleW(const wchar_t* lpModuleName);
    extern "C" __declspec(dllimport) DWORD __stdcall FormatMessageA(DWORD dwFlags, const void* lpSource, DWORD dwMessageId, DWORD dwLanguageId, char* lpBuffer, DWORD nSize, va_list *Arguments);

    namespace internetError
    {
        const int       kBase = 12000; //INTERNET_ERROR_BASE
        const int       kLast = 12200; //INTERNET_ERROR_LAST
        const wchar_t   kModule[] = L"wininet";
    }

    inline string formatMessage(unsigned long messageId, HMODULE module = nullptr)
    {
        if (messageId >= internetError::kBase && messageId <= internetError::kLast)
        {
            module = GetModuleHandleW(internetError::kModule);
        }

        char buffer[0x200] = {};

        auto length = FormatMessageA(
            (module ? kFormatFromHmodule : kFormatFromSystem) | kFormatIgnoreInserts | kFormatMaxWidthMask,
            module,
            messageId,
            0,
            buffer,
            sizeof(buffer),
            nullptr);
        if (length < 3)
        {
            return "Unknown error code";
        }

        length -= 2;
        if (buffer[length - 1] == '.')
        {
            --length;
        }

        return string(buffer, length);
    }
#endif
}

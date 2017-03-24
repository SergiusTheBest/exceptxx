#pragma once
#include <string>

namespace exceptxx
{
    using namespace std;

#ifdef _WIN32
    namespace winapi
    {
        using HRESULT = long;
        using DWORD = unsigned long;
        using NTSTATUS = long;

        const HRESULT HR_S_OK = 0;
        const HRESULT HR_E_FAIL = 0x80004005L;
        const HRESULT HR_E_INVALIDARG = 0x80000003L;

        extern "C" __declspec(dllimport) DWORD __stdcall GetLastError();
        extern "C" __declspec(dllimport) void* __stdcall GetModuleHandleW(const wchar_t* lpModuleName);
        extern "C" __declspec(dllimport) DWORD __stdcall FormatMessageA(DWORD dwFlags, const void* lpSource, DWORD dwMessageId, DWORD dwLanguageId, char* lpBuffer, DWORD nSize, va_list *Arguments);

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
    }

    inline string formatMessage(unsigned long messageId, void* module = nullptr)
    {
        char buffer[0x200] = {};

        auto length = winapi::FormatMessageA(
            (module ? winapi::kFormatFromHmodule : winapi::kFormatFromSystem) | winapi::kFormatIgnoreInserts | winapi::kFormatMaxWidthMask,
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
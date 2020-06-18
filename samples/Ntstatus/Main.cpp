#include <exceptxx/NtStatusException.h>
#include <Windows.h>
#include <winternl.h>
#include <iostream>

using namespace std;

int main()
{
    try
    {
        auto myRtlConvertSidToUnicodeString = reinterpret_cast<decltype(::RtlConvertSidToUnicodeString)*>(::GetProcAddress(::GetModuleHandleW(L"ntdll"), "RtlConvertSidToUnicodeString"));
        
        NTSTATUS st = myRtlConvertSidToUnicodeString(nullptr, nullptr, false);
        CHECK_NTSTATUS(st) << "Failed to convert SID";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        CHECK_NTSTATUS(STATUS_INVALID_HANDLE);
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

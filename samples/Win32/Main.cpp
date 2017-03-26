#include <exceptxx/Win32Exception.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    try
    {
        HANDLE h = ::CreateFileW(L"nonexisting", 0, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        THROW_LAST_WIN32_IF(INVALID_HANDLE_VALUE == h) << "Ooops, cannot open file 'nonexisting'";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        THROW_LAST_WIN32_IF(!::ReadFile(nullptr, nullptr, 0, nullptr, nullptr));
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        CHECK_WIN32(ERROR_ACCESS_DENIED);
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

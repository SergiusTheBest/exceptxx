#include <exceptxx/HresultException.h>
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    try
    {
        HRESULT hr = ::CoInitializeEx(nullptr, MAXDWORD);
        CHECK_HRESULT(hr) << "Failed to initialize COM";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        THROW_LAST_HRESULT_IF(!::ReadFile(nullptr, nullptr, 0, nullptr, nullptr));
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        CHECK_HRESULT(E_ACCESSDENIED);
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

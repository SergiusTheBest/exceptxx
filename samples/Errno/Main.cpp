#include <exceptxx/ErrnoException.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    try
    {
        ifstream f("nonexisting");
        THROW_LAST_ERRNO_IF(f.fail()) << "Ooops, cannot open file 'nonexisting'";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    try
    {
        CHECK_ERRNO(ENODEV);
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

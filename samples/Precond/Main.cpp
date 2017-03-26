#include <exceptxx/PrecondException.h>
#include <iostream>

using namespace std;

int main(int argc, const char*[])
{
    try
    {
        CHECK_PRECOND(argc > 1) << "Expect some command line arguments";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

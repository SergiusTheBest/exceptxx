#include <exceptxx/AssertException.h>
#include <iostream>

using namespace std;

int main(int argc)
{
    try
    {
        // This is only for demo as asserts must not depend on function parameters.
        CHECK_ASSERT(argc > 1) << "Expect some command line arguments";
    }
    catch (const exception& ex)
    {
        cerr << ex.what() << endl << endl;
    }

    return 0;
}

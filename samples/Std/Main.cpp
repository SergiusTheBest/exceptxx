#include <exceptxx/TryCatch.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    XX_TRY(ex)
    {
        vector<int> v;
        v.at(10) = 0;
    }
    XX_CATCH(ex);

    if (ex)
    {
        cerr << ex->what() << endl;
    }

    return 0;
}

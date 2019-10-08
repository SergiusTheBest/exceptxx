#include <exceptxx/TryCatch.h>
#include <exceptxx/ErrnoException.h>
#include <iostream>

using namespace std;

int main()
{
    //
    // Declare exception variable (ex) and use it in the catch block.
    //

    XX_TRY(ex)
    {
        CHECK_ERRNO(EACCES);
    }
    XX_CATCH(ex);

    if (ex)
    {
        cerr << ex->what() << endl << endl;
    }

    //
    // Use previously declared exception variable in the catch block.
    //

    XX_TRY()
    {
        CHECK_ERRNO(E2BIG);
    }
    XX_CATCH(ex);

    if (ex)
    {
        cerr << ex->what() << endl << endl;
    }

    //
    // Ability to rethrow exception variable.
    //

    try
    {
        XX_TRY()
        {
            CHECK_ERRNO(EBADF);
        }
        XX_CATCH(ex);

        if (ex)
        {
            ex->rethrow();
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl << endl;
    }

    //
    // Explicitly declare exception variable and use it in the catch block.
    //

    XX_HOLDER(anotherEx);

    XX_TRY()
    {
        CHECK_ERRNO(EBADF);
    }
    XX_CATCH(anotherEx);

    if (anotherEx)
    {
        cerr << anotherEx->what() << endl << endl;
    }
    
    //
    // Another namings.
    //

    EX_TRY()
    {
        throw runtime_error("Ooops!");
    }
    EX_CATCH(ex);

    if (ex)
    {
        cerr << ex->what() << endl << endl;
    }

    return 0;
}

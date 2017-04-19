# ExceptXX: C++ exception handling library

# Intoduction
This library greatly improves and simplifies usage of C++ exceptions. It provides convinient macros for throwing/catching exceptions and checking API errors.

## Features
- header-only
- cross-platform: linux, windows, macos (msvc, gcc, clang, mingw, mingw-64)
- requires C++11
- no logic in catch blocks
- exceptions are convertible to return codes
- exceptions carry information about throwing place (function name, line number), error code and description
- a convenient way to attach an arbitrary user message to exception
- ready-made exceptions:
  - win32
  - ntstatus
  - hresult
  - errno
  - precondition
  - assert

# Quick start
```cpp
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
        cerr << ex.what() << endl;
    }
    
    return 0;
}
```

```
Text: The system cannot find the file specified (Ooops, cannot open file 'nonexisting')
Error: 2 (WIN32)
Source: main:12
```
  
# License
ExceptXX is licensed under the [MPL version 2.0](http://mozilla.org/MPL/2.0/). You can freely use it in your commercial or opensource software.

# ExceptXX: C++ exception handling library

# Intoduction
This library greatly improves and simplifies usage of C++ exceptions. It provides convinient macros for throwing/catching exceptions and checking API errors.

Here is a minimal exceptxx sample:
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
and its output:
```
Text: The system cannot find the file specified (Ooops, cannot open file 'nonexisting')
Error: 2 (WIN32)
Source: main:12
```

## Features
- header-only
- cross-platform: linux, windows, macos (msvc, gcc, clang, mingw, mingw-64)
- requires C++11
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
- macros for conditional exception throwing

# Usage
To start using exceptxx you need to make 3 simple steps.

## Step 1: Adding includes
At first your project needs to know about exceptxx. For that you have to:

1. Add `exceptxx/include` to the project include paths
2. Add `#include <exceptxx/{{{desired exception}}.h>` into your cpp/h files (if you have precompiled headers it is a good place to add this include there)

## Step 2: Throwing exceptions

## Step 3: Catching exceptions

# Samples
There are a number of samples that demonstrate various aspects of using exceptxx. They can be found in the [samples](samples) folder:

|Sample|Description|
|------|-----------|
|[Assert](samples/Assert)||
|[Errno](samples/Errno)||
|[Hresult](samples/Hresult)||
|[Ntstatus](samples/Ntstatus)||
|[Precond](samples/Precond)||
|[Std](samples/Std)||
|[TryCatch](samples/TryCatch)||
|[Win32](samples/Win32)||
  
# License
ExceptXX is licensed under the [MPL version 2.0](http://mozilla.org/MPL/2.0/). You can freely use it in your commercial or opensource software.

# Version history

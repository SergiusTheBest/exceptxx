# ExceptXX: C++ exception handling library
[![Build Status](https://travis-ci.org/SergiusTheBest/exceptxx.svg?branch=master)](https://travis-ci.org/SergiusTheBest/exceptxx) [![Build status](https://ci.appveyor.com/api/projects/status/nyo8dtyw9kfq3xhf/branch/master?svg=true)](https://ci.appveyor.com/project/SergiusTheBest/exceptxx/branch/master)

- [Intoduction](#intoduction)
  - [Features](#features)
- [Usage](#usage)
  - [Step 1: Adding includes](#step-1-adding-includes)
  - [Step 2: Throwing exceptions](#step-2-throwing-exceptions)
  - [Step 3: Catching exceptions](#step-3-catching-exceptions)
- [Samples](#samples)
- [License](#license)
- [Version history](#version-history)

# Intoduction
This library greatly improves and simplifies usage of C++ exceptions. It provides convenient macros for throwing/catching exceptions and checking API errors.

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
- Header-only
- Cross-platform: Linux, Windows, macOS (msvc, gcc, clang)
- Requires C++11
- Exceptions are convertible to return codes
- Exceptions carry information about throwing place (function name, line number), error code and description
- Convenient way to attach an arbitrary user message to exception
- Ready-made exceptions:
  - errno
  - hresult
  - ntstatus
  - win32
  - assert
  - precondition
  - cuda
  - npp
- Macros for conditional exception throwing

# Usage
To start using exceptxx you need to make 3 simple steps.

## Step 1: Adding includes
At first your project needs to know about exceptxx. For that you have to:

1. Add `exceptxx/include` to the project include paths
2. Add `#include <exceptxx/{{{desired exception}}.h>` into your cpp/h files (if you have precompiled headers it is a good place to add this include there)

## Step 2: Throwing exceptions

ExceptXX exceptions have to be thrown using special macros. There are 2 families of them:
- `THROW_...(err)`
- `CHECK_...(err)`

`THROW_...` macros throw an exception with the specified error code while `CHECK_...` macros check the error code to be a failure error code and only then throw an exception.

Also macros can have a condition: `THROW_..._IF(cond, err)`. In this case an exception is thrown only when the condition is true.

The following modification of exception throwing macros is designed to be used with API that has a notion of a last error code:
- `THROW_LAST_...()`
- `CHECK_LAST_...()`

These macros can have a condition too:
- `THROW_LAST_..._IF(cond)`
- `CHECK_LAST_..._IF(cond)`

Examples:
```cpp
THROW_HRESULT(E_ACCESS);
CHECK_ERRNO(res);
THROW_LAST_WIN32_IF(!res);
```

## Step 3: Catching exceptions
There are helper macros for try-catch blocks. They store caught exception in a variable that can be analyzed later. Also they catch and wrap `std::exception`.

```cpp
int foo()
{
    XX_TRY(ex) // declare exception variable
    {
        CHECK_ERRNO(EACCES);
    }
    XX_CATCH(ex);

    if (ex)
    {
        cerr << ex->what() << endl;
    }
    
    return ex;
}
```

# Samples
There are a number of samples that demonstrate various aspects of using exceptxx. They can be found in the [samples](samples) folder:
- [Assert](samples/Assert)
- [Errno](samples/Errno)
- [Hresult](samples/Hresult)
- [Ntstatus](samples/Ntstatus)
- [Precond](samples/Precond)
- [Std](samples/Std)
- [TryCatch](samples/TryCatch)
- [Win32](samples/Win32)
  
# License
ExceptXX is licensed under the [MIT license](https://choosealicense.com/licenses/mit). You can freely use it in your commercial or opensource software.

# Version history

## Version 1.0.0 (08 Oct 2019)
- Initial public release
# ExceptXX: C++ exception handling library

# Intoduction
This library greatly improves and simplifies usage of C++ exceptions. It provides convinient macros for throwing/catching exceptions and checking API errors.

## Features
- header-only
- requires C++11
- cross-platform: linux, windows, macos (msvc, gcc, clang, mingw, mingw-64)
- no logic in catch blocks
- convert exception to return value
- exceptions for:
  - win32
  - ntstatus
  - hresult
  - errno
  - precondition
  - assert

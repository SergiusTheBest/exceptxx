cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Samples)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif ()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wnon-virtual-dtor -Wundef -pedantic -Werror")
endif()

add_subdirectory(Assert)
add_subdirectory(Errno)
add_subdirectory(Precond)
add_subdirectory(Std)
add_subdirectory(TryCatch)

if(WIN32)
    add_subdirectory(Hresult)
    add_subdirectory(Win32)
    add_subdirectory(Ntstatus)
endif()
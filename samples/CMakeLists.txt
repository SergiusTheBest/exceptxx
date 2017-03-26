cmake_minimum_required(VERSION 2.8)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(ExceptXX)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGXX 1)
endif ()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -pedantic -Werror")
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
    checkObjCXX()
endif()

include_directories(${CMAKE_SOURCE_DIR}/../include)

file(GLOB_RECURSE EXCEPTXX_HEADERS ${CMAKE_SOURCE_DIR}/../include/*.h)
add_library(exceptxx STATIC ${EXCEPTXX_HEADERS})
set_target_properties(exceptxx PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(exceptxx PROPERTIES FOLDER Include)

add_executable(Errno Errno/Main.cpp)
set_target_properties(Errno PROPERTIES FOLDER Samples)

add_executable(Precond Precond/Main.cpp)
set_target_properties(Precond PROPERTIES FOLDER Samples)

add_executable(Assert Assert/Main.cpp)
set_target_properties(Assert PROPERTIES FOLDER Samples)

add_executable(Std Std/Main.cpp)
set_target_properties(Std PROPERTIES FOLDER Samples)

add_executable(TryCatch TryCatch/Main.cpp)
set_target_properties(TryCatch PROPERTIES FOLDER Samples)

if(WIN32)
    add_executable(Win32 Win32/Main.cpp)
    set_target_properties(Win32 PROPERTIES FOLDER Samples)

    add_executable(Hresult Hresult/Main.cpp)
    set_target_properties(Hresult PROPERTIES FOLDER Samples)

    add_executable(Ntstatus Ntstatus/Main.cpp)
    set_target_properties(Ntstatus PROPERTIES FOLDER Samples)
endif()

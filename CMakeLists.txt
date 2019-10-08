cmake_minimum_required(VERSION 3.1)

option(EXCEPTXX_BUILD_SAMPLES "Build exceptxx's samples." ON)

project(exceptxx VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# make sure install paths work on all platforms
if(NOT CMAKE_INSTALL_INCLUDEDIR)
    include(GNUInstallDirs)
endif()

add_library(exceptxx INTERFACE)
target_include_directories(exceptxx 
    INTERFACE 
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(exceptxx::exceptxx ALIAS exceptxx)

# workaround for stand-alone build detection under windows (as it's case insensitive)
get_filename_component(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
get_filename_component(SOURCE_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE)

# check if building as a stand-alone project
if(${CURRENT_SOURCE_DIR} STREQUAL ${SOURCE_DIR} AND EXCEPTXX_BUILD_SAMPLES)
    # add a pseudo-project to make project headers visible in IDE
    file(GLOB_RECURSE EXCEPTXX_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
    add_library(exceptxx-h STATIC ${EXCEPTXX_HEADERS})
    set_target_properties(exceptxx-h PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(exceptxx-h PROPERTIES FOLDER Include)

    add_subdirectory(samples)
endif()

install(TARGETS exceptxx EXPORT ExceptxxConfig)

install(
    EXPORT ExceptxxConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/exceptxx
    NAMESPACE exceptxx::
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/exceptxx
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" # headers only
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ExceptxxConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/ExceptxxConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/exceptxx
)
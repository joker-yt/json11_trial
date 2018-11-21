project(json11-test)

cmake_minimum_required(VERSION 3.2.2)

set(json11-test-VERSION_MAJOR 1)
set(json11-test-VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig)
pkg_check_modules(LIBJSON11 REQUIRED json11)
include_directories(${LIBJSON11_INCLUDE_DIRS})
link_directories(${LIBJSON11_LIBRARY_DIRS})

add_executable(mainbin ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(mainbin pthread ${LIBJSON11_LDFLAGS})

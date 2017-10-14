cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")

file(GLOB_RECURSE azure_HEADER_FILES "azure_daemon/*.h")
file(GLOB_RECURSE azure_SRC_FILES "azure_daemon/*.cc")

# find headers
set(azure_INCLUDE_DIRS "")
foreach (_headerFile ${azure_HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND azure_INCLUDE_DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES azure_INCLUDE_DIRS)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/masterlib ${CMAKE_CURRENT_BINARY_DIR}/masterlib)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/msgpack-c ${CMAKE_CURRENT_BINARY_DIR}/msgpack-c)

include_directories(${CMAKE_SOURCE_DIR}/third_party/msgpack-c/include)

add_library(azure STATIC ${azure_SRC_FILES} ${azure_INCLUDE_DIRS})

add_executable(server_test tests/test_server.cc)
add_executable(client_test tests/test_client.cc)

target_link_libraries(server_test azure)
target_link_libraries(client_test azure)

target_include_directories(azure PUBLIC
        $<TARGET_PROPERTY:masterlib_STATIC,INTERFACE_INCLUDE_DIRECTORIES>${CMAKE_SOURCE_DIR}/third_party/masterlib/src>)

cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")

file(GLOB_RECURSE libazure_HEADER_FILES "libazure/*.h")
file(GLOB_RECURSE libazure_SRC_FILES "libazure/*.cc")

file(GLOB_RECURSE azure_HEADER_FILES "azure/*.h")
file(GLOB_RECURSE azure_SRC_FILES "azure/*.cc")

# find headers
set(libazure_INCLUDE_DIRS "")
foreach (_headerFile ${libazure_HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND libazure_INCLUDE_DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES libazure_INCLUDE_DIRS)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/masterlib ${CMAKE_CURRENT_BINARY_DIR}/masterlib)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/msgpack-c ${CMAKE_CURRENT_BINARY_DIR}/msgpack-c)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gflags ${CMAKE_CURRENT_BINARY_DIR}/gflags)

include_directories(libazure)
# third party includes
include_directories(${CMAKE_SOURCE_DIR}/third_party/masterlib/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/msgpack-c/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/gflags/src)

add_library(azure_STATIC STATIC ${libazure_SRC_FILES} ${libazure_INCLUDE_DIRS})

add_executable(azure ${azure_SRC_FILES} ${azure_HEADER_FILES})

add_executable(server_test tests/test_server.cc)
add_executable(client_test tests/test_client.cc)

target_link_libraries(azure_STATIC masterlib_STATIC capstone-static keystone gflags)
target_link_libraries(azure azure_STATIC)
target_link_libraries(server_test azure_STATIC)
target_link_libraries(client_test azure_STATIC)

#target_include_directories(azure PUBLIC
#        $<TARGET_PROPERTY:masterlib_STATIC,INTERFACE_INCLUDE_DIRECTORIES>${CMAKE_SOURCE_DIR}/third_party/masterlib/src>)

cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB libazure_HEADER_FILES "libazure/*.h" "libazure/data_objects/*.h" "libazure/message_handlers/*.h" "libazure/message_unpackers/*.h")
file(GLOB libazure_SRC_FILES "libazure/*.cc" "libazure/data_objects/*.cc" "libazure/message_handlers/*.cc" "libazure/message_unpackers/*.cc")


# find headers
set(libazure_INCLUDE_DIRS "")
foreach (_headerFile ${libazure_HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND libazure_INCLUDE_DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES libazure_INCLUDE_DIRS)

add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/msgpack-c ${CMAKE_CURRENT_BINARY_DIR}/msgpack-c)

include_directories(libazure)
# third party includes
include_directories(${CMAKE_SOURCE_DIR}/third_party/msgpack-c/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/gflags/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/linenoise)
                  
add_library(azure_STATIC STATIC ${libazure_SRC_FILES} ${libazure_INCLUDE_DIRS})


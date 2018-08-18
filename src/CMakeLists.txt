# cmake .. "-GAndroid Gradle - Ninja" -DANDROID_ABI=arm64-v8a -DANDROID_NDK="D:\Programs\Android\SDK\ndk-bundle" 
# -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_TOOLCHAIN_FILE="D:\Programs\Android\SDK\ndk-bundle\build\cmake\android.toolchain.cmake" 
# -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_TOOLCHAIN=clang -DANDROID_STL=c++_static -DANDROID_CPP_FEATURES="rtti exceptions"

cmake_minimum_required(VERSION 3.0.0)
project(azure C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

option(AZURE_TARGET_ANDROID "Target android systems" ON)
option(AZURE_TARGET_LINUX "Target linux systems" OFF)
option(AZURE_TARGET_DARWIN "Target darwin systems" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(LLVM_TARGETS_TO_BUILD "AArch64;ARM;X86" CACHE STRING "keystone architecture support" FORCE)

set(CAPSTONE_MIPS_SUPPORT OFF CACHE BOOL "MIPS support" FORCE)
set(CAPSTONE_PPC_SUPPORT OFF CACHE BOOL "PowerPC support" FORCE)
set(CAPSTONE_SPARC_SUPPORT OFF CACHE BOOL "Sparc support" FORCE)
set(CAPSTONE_SYSZ_SUPPORT OFF CACHE BOOL "SystemZ support" FORCE)
set(CAPSTONE_XCORE_SUPPORT OFF CACHE BOOL "XCore support" FORCE)

file(GLOB libazure_HEADER_FILES "libazure/*.h" "libazure/data_objects/*.h" "libazure/message_handlers/*.h" "libazure/message_unpackers/*.h")
file(GLOB libazure_SRC_FILES "libazure/*.cc" "libazure/data_objects/*.cc" "libazure/message_handlers/*.cc" "libazure/message_unpackers/*.cc")

if(AZURE_TARGET_ANDROID)
    file(GLOB libazure_ANDROID_HEADER_FILES "libazure/android/*.h")
    file(GLOB libazure_ANDROID_SRC_FILES "libazure/android/*.cc")
endif()

if(AZURE_TARGET_LINUX) 
    file(GLOB libazure_LINUX_HEADER_FILES "libazure/linux/*.h")
    file(GLOB libazure_LINUX_SRC_FILES "libazure/linux/*.cc")
endif()

if(AZURE_TARGET_DARWIN) 
    file(GLOB libazure_DARWIN_HEADER_FILES "libazure/darwin/*.h")
    file(GLOB libazure_DARWIN_SRC_FILES "libazure/darwin/*.cc")
endif()

file(GLOB_RECURSE azure_HEADER_FILES "azure-cli/*.h")
file(GLOB_RECURSE azure_SRC_FILES "azure-cli/*.cc")

# find headers
set(libazure_INCLUDE_DIRS "")
foreach (_headerFile ${libazure_HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND libazure_INCLUDE_DIRS ${_dir})
endforeach ()
list(REMOVE_DUPLICATES libazure_INCLUDE_DIRS)

#add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/masterlib ${CMAKE_CURRENT_BINARY_DIR}/masterlib)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/msgpack-c ${CMAKE_CURRENT_BINARY_DIR}/msgpack-c)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/gflags ${CMAKE_CURRENT_BINARY_DIR}/gflags)

include_directories(libazure)
# third party includes
#include_directories(${CMAKE_SOURCE_DIR}/third_party/masterlib/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/msgpack-c/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/gflags/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party/linenoise)

set(linenoise_SRC_FILES "${CMAKE_SOURCE_DIR}/third_party/linenoise/linenoise.c"
                        "${CMAKE_SOURCE_DIR}/third_party/linenoise/linenoise.h")

if (AZURE_TARGET_DARWIN)                        
    add_library(azure_STATIC STATIC ${libazure_SRC_FILES} ${libazure_INCLUDE_DIRS} ${libazure_DARWIN_SRC_FILES} ${libazure_DARWIN_INCLUDE_DIRS})
elseif (AZURE_TARGET_ANDROID)
    add_library(azure_STATIC STATIC ${libazure_SRC_FILES} ${libazure_INCLUDE_DIRS} ${libazure_ANDROID_SRC_FILES} ${libazure_ANDROID_INCLUDE_DIRS})
    target_link_libraries(azure_STATIC log android)
elseif (AZURE_TARGET_LINUX)
     add_library(azure_STATIC STATIC ${libazure_SRC_FILES} ${libazure_INCLUDE_DIRS} ${libazure_LINUX_SRC_FILES} ${libazure_LINUX_INCLUDE_DIRS})
endif()

add_executable(azure ${azure_SRC_FILES} ${azure_HEADER_FILES} ${linenoise_SRC_FILES})

add_executable(server_test tests/test_server.cc tests/shared.h)
add_executable(client_test tests/test_client.cc tests/shared.h)

target_link_libraries(azure_STATIC gflags)
target_link_libraries(azure azure_STATIC)
target_link_libraries(server_test azure_STATIC)
target_link_libraries(client_test azure_STATIC)

#target_include_directories(azure PUBLIC
#        $<TARGET_PROPERTY:masterlib_STATIC,INTERFACE_INCLUDE_DIRECTORIES>${CMAKE_SOURCE_DIR}/third_party/masterlib/src>)

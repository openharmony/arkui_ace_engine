# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(AccessibilityCustomCapi)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(entry SHARED ani_init.cpp AccessibilityMaker.cpp
            AccessibilityDialog.cpp AccessibilityDialogSubWindow.cpp)

find_library(hilog-lib hilog_ndk.z)

find_library(libace-lib ace_ndk.z)

find_library(libnapi-lib ace_napi.z)

target_link_libraries(entry PUBLIC ${hilog-lib} ${libace-lib} ${libnapi-lib} libability_base_want.so)

target_link_libraries(entry PUBLIC libace_ndk.z.so)
target_link_libraries(entry PUBLIC libace_napi.z.so)

target_link_libraries(entry PRIVATE
    ace_ndk.z # 核心NDK库
    ace_napi.z # NAPI支持库
    hilog_ndk.z # 日志库
)

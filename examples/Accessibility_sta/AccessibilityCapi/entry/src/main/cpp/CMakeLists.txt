cmake_minimum_required(VERSION 3.5.0)
project(AccessibilityCapi)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

find_library(libace-lib ace_ndk.z)

add_library(entry SHARED
    ani_init.cpp
    manager/AccessibilityManager.cpp
    fakenode/fake_node.cpp)

target_link_libraries(entry PUBLIC ${libace-lib} libace_napi.z.so libhilog_ndk.z.so)

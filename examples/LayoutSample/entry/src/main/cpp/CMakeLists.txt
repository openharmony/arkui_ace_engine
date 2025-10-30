# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(CAPI0805_2)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

find_library(
    # Sets the name of the path variable.
    hilog-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    hilog_ndk.z
)

add_library(entry SHARED napi_init.cpp NativeEntry.cpp NativeEntry.h NativeModule.h nodes/ArkUINode.h nodes/ArkUINode.cpp examples/guidelineOptionExample.h examples/barrierOptionExample.h examples/listChildrenMainSizeExample.h nodes/ArkUIListNode.h examples/itemAlignmentExample.h nodes/ArkUIFlexNode.h examples/relativeLayoutChainExample.h examples/flexExample.h nodes/ArkUIStackNode.h examples/stackExample.h examples/rowExample.h examples/columnExample.h examples/layoutPositionExample.h nodes/ArkUICustomColumnNode.h examples/safeAreaExample.h  examples/layoutPolicyExample.h examples/positionEdgesExample.h nodes/ArkUIButtonNode.h)
target_link_libraries(entry PUBLIC libace_napi.z.so libace_ndk.z.so ${hilog-lib} libhilog_ndk.z.so)
# the minimum version of CMake.
cmake_minimum_required(VERSION 3.28.0)
project(native_node_sample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

file(GLOB_RECURSE ENTRY_SOURCES CONFIGURE_DEPENDS
    "${NATIVERENDER_ROOT_PATH}/*.cpp"
)

add_library(entry SHARED ${ENTRY_SOURCES} common/ArkUIColumnNode.h)

find_library(
    # Sets the name of the path variable.
    hilog-lib
    libace-lib
    libnapi-lib
    ace_napi.z
    EGL-lib
    EGL
    GLES-lib
    GLESv3
)
target_link_libraries(entry PUBLIC
    libace_ndk.z.so
    libace_napi.z.so
    libhilog_ndk.z.so
    libnative_drawing.so
    libability_base_want.so
    libpixelmap.so
)

target_link_libraries(entry PUBLIC ${libace-lib} libace_napi.z.so libnative_drawing.so libhilog_ndk.z.so)
target_link_libraries(entry PUBLIC ${EGL-lib} ${GLES-lib} libace_napi.z.so libhilog_ndk.z.so libace_ndk.z.so libnative_window.so)
target_link_libraries(entry PUBLIC ${libace-lib} libace_napi.z.so libnative_drawing.so libhilog_ndk.z.so libability_base_want.so)
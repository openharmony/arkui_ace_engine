cm_minimum_required(VERSION 3.28.0)
project(PickerCapiDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH})

file(GLOB_RECURSE ENTRY_SOURCES CONFIGURE_DEPENDS
    "${NATIVERENDER_ROOT_PATH}/*.cpp"
)

add_library(entry SHARED ${ENTRY_SOURCES})
target_link_libraries(entry PUBLIC
    ace_ndk.z
    ace_napi.z
    hilog_ndk.z
)
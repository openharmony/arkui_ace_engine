# the minimum version of CMake
cmake_minimum_required(VERSION 3.5.0)
project(capi)

set(CMAKE_CXX_STANDARD 17)
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()
add_compile_options(-Wc++17-extensions)
include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)
                    
add_library(
    entry SHARED
    napi_init.cpp
    ui_node/base_node.h
    ui_node/native_module.h
    ui_node/ui_node.h
    ui_node/image_node.h
    ui_node/column_node.h
    image/drawable_descriptor.h
    image/drawable_descriptor.cpp
    utils/log.h
    image/pixel_map.h
    ui_node/row_node.h
    ui_node/native_entry.h
    utils/self_enums.h
    utils/napi_utils.h
    utils/napi_utils.cpp
    image/resizable_params.h
    image/image_matrix.h
    image/image_matrix.cpp
    ui_node/image_node.cpp
)
target_link_libraries(entry PUBLIC libace_napi.z.so libhilog_ndk.z.so libnative_drawing.so)
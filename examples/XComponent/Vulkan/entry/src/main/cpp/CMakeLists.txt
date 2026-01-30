# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(XComponent)
ADD_DEFINITIONS(-DVK_USE_PLATFORM_OHOS=1)
set(CMAKE_CXX_STANDARD 17)
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

set (STATIC_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set (DYNAMIC_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/thirdParty)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/types/thirdParty/glm)

set (BUILD_SHARED_LIBS TRUE)
set (GLM_DLL_NAME glm)

add_subdirectory (types/thirdParty)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include) 
file (GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(entry SHARED ${SRC})
target_link_libraries(entry PUBLIC
    libace_ndk.z.so libace_napi.z.so
    libnative_window.so libvulkan.so libnative_vsync.so
    ${GLM_DLL_NAME} libhilog_ndk.z.so librawfile.z.so
    ${GLSLANG_DLL_NAME})
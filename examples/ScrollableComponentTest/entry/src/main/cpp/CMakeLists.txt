#[[
 # Copyright (c) 2025 Huawei Device Co., Ltd.
 # Licensed under the Apache License, Version 2.0 (the "License");
 # you may not use this file except in compliance with the License.
 # You may obtain a copy of the License at
 #
 #     http://www.apache.org/licenses/LICENSE-2.0
 #
 # Unless required by applicable law or agreed to in writing, software
 # distributed under the License is distributed on an "AS IS" BASIS,
 # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 # See the License for the specific language governing permissions and
 # limitations under the License.
]]

# the minimum version of CMake.
cmake_minimum_required(VERSION 3.28.0)
project(ScrollableComponentTest)

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

add_library(entry SHARED ${ENTRY_SOURCES})

find_library(
    # Sets the name of the path variable.
    libnapi-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    ace_napi.z
)
target_link_libraries(entry PUBLIC
    libace_ndk.z.so
    libace_napi.z.so
    libhilog_ndk.z.so
    libnative_drawing.so
)
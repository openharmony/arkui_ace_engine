# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(accessibilityCapi)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(nativerender SHARED
    manager/plugin_manager.cpp
    manager/xcomponent_manager.cpp
    manager/AccessibilityManager.cpp
    napi_init.cpp
    fakenode/fake_node.h
    fakenode/fake_node.cpp
    fakenode/FakeTextField.cpp
    fakenode/FakeCheckbox.cpp
    fakenode/FakeCustomWidget.cpp
    scenarios/ScenarioManager.cpp
    scenarios/Scenario1LoginPage.cpp
    scenarios/Scenario2AudioPlayer.cpp
    scenarios/Scenario3NewsList.cpp
    scenarios/Scenario7Settings.cpp)

find_library(
    # Sets the name of the path variable.
    hilog-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    hilog_ndk.z
)

find_library(
    # Sets the name of the path variable.
    libace-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    ace_ndk.z
)

find_library(
    # Sets the name of the path variable.
    libnapi-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    ace_napi.z
)
find_library(
    libnative_window

    native_window
)

target_link_libraries(nativerender PUBLIC ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libnative_window})
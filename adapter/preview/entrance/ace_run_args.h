/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_RUN_OPTIONS_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_RUN_OPTIONS_H

#include <functional>
#include <string>

#include "base/utils/device_type.h"

#ifndef ACE_PREVIEW_EXPORT
#ifdef _WIN32
#define ACE_PREVIEW_EXPORT __declspec(dllexport)
#elif defined(__APPLE__)
#define ACE_PREVIEW_EXPORT __attribute__((visibility("default")))
#endif
#endif // ACE_PREVIEW_EXPORT

namespace OHOS::Ace::Platform {

using SendRenderDataCallback = bool (*)(const void*, size_t);

// Keep the same with definition in base/utils/system_properties.h
enum class DeviceOrientation : int32_t {
    PORTRAIT,
    LANDSCAPE,
};

enum class ThemeId : int32_t {
    THEME_ID_LIGHT,
    THEME_ID_DARK,
};

// Keep the same with definition in base/utils/system_properties.h
enum class ColorMode : int32_t {
    LIGHT = 0,
    DARK,
};

struct ACE_PREVIEW_EXPORT AceRunArgs {
    // The absolute path end of "default".
    std::string assetPath;
    // The absolute path of system resources.
    std::string resourcesPath;

    // Indecate light or dark theme. 0 is theme_light, 1 is theme_dark.
    ThemeId themeId = ThemeId::THEME_ID_LIGHT;

    // Light Theme contains light mode and dark mode. The dafault is light mode of light theme.
    ColorMode colorMode = ColorMode::LIGHT;

    // Set page path to launch directly, or launch the main page in default.
    std::string url;

    std::string windowTitle;

    bool isRound = false;
    int32_t viewWidth = 0;
    int32_t viewHeight = 0;
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    double resolution = 1.0;

    // Locale
    std::string language = "zh";
    std::string region = "CN";
    std::string script = "";

    DeviceOrientation orientation = DeviceOrientation::PORTRAIT;
    DeviceType deviceType = DeviceType::PHONE;

    bool formsEnabled = false;

    SendRenderDataCallback onRender;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_RUN_OPTIONS_H

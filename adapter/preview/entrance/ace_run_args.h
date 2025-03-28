/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include <map>

#include "base/utils/device_config.h"
#include "base/utils/device_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::Platform {

using SendRenderDataCallback = bool (*)(const void*, const size_t, const int32_t, const int32_t, const uint64_t);
using SendCurrentRouterCallback = bool (*)(const std::string currentRouterPath);
using FastPreviewErrorCallback = void (*)(const std::string& jsonStr);

constexpr uint32_t OHOS_THEME_ID = 125829872;

enum class AceVersion {
    ACE_1_0,
    ACE_2_0,
};

enum class ProjectModel {
    FA,
    STAGE,
};

struct ACE_FORCE_EXPORT AceRunArgs {
    // the adopted project model
    ProjectModel projectModel = ProjectModel::FA;
    // stores routing information
    std::string pageProfile = "";
    // The absolute path end of "default".
    std::string assetPath;
    // The absolute path of system resources.
    std::string systemResourcesPath;
    // The absolute path of app resources.
    std::string appResourcesPath;

    // Indicate light or dark theme.
    uint32_t themeId = OHOS_THEME_ID;

    OHOS::Ace::DeviceConfig deviceConfig = {
        .orientation = DeviceOrientation::PORTRAIT,
        .density = 1.0,
        .deviceType = DeviceType::PHONE,
        .colorMode = ColorMode::LIGHT,
    };

    // Set page path to launch directly, or launch the main page in default.
    std::string url;

    std::string windowTitle;

    bool isRound = false;
    int32_t viewWidth = 0;
    int32_t viewHeight = 0;
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;

    // Locale
    std::string language = "zh";
    std::string region = "CN";
    std::string script = "";

    std::string configChanges;

    AceVersion aceVersion = AceVersion::ACE_1_0;

    bool formsEnabled = false;

    SendRenderDataCallback onRender = nullptr;
    SendCurrentRouterCallback onRouterChange = nullptr;
    FastPreviewErrorCallback onError = nullptr;

    // Container sdk path.
    std::string containerSdkPath = "";
    bool isComponentMode = false;

    // for strict mode
    std::map<std::string, std::string> pkgContextInfoJsonStringMap;
    std::map<std::string, std::string> packageNameList;

    // Component test
    bool isComponentTestMode = false;
    std::string componentTestConfig = "";
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_RUN_OPTIONS_H

/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "run_args_parser.h"

#include <string>
#include <map>

#include "base/utils/device_type.h"
#include "base/utils/device_config.h"
#include "frameworks/base/log/log.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace::Samples {
namespace {
const std::map<std::string, Platform::AceVersion> ACE_VERSION_MAP = {
    {"1.0", Platform::AceVersion::ACE_1_0},
    {"2.0", Platform::AceVersion::ACE_2_0},
};

const std::map<std::string, Platform::ProjectModel> PROJECT_MODEL_MAP = {
    {"FA", Platform::ProjectModel::FA},
    {"STAGE", Platform::ProjectModel::STAGE},
};

const std::map<std::string, DeviceType> DEVICE_TYPE_MAP = {
    {"default", DeviceType::PHONE},
    {"tablet", DeviceType::TABLET},
    {"unknown", DeviceType::UNKNOWN},
};

const std::map<std::string, DeviceOrientation> DEVICE_ORIENTATION_MAP = {
    {"portrait", DeviceOrientation::PORTRAIT},
    {"landscape", DeviceOrientation::LANDSCAPE},
    {"orientation_undefined", DeviceOrientation::ORIENTATION_UNDEFINED},
};

const std::map<std::string, ColorMode> COLOR_MODE_MAP = {
    {"light", ColorMode::LIGHT},
    {"dark", ColorMode::DARK},
    {"color_mode_undefined", ColorMode::COLOR_MODE_UNDEFINED},
};
}

bool RunArgsParser::Parse(const std::string& contents)
{
    auto rootJson = JsonUtil::ParseJsonString(contents);
    if (!rootJson || !rootJson->IsValid()) {
        LOGE("The run args config is illegal");
        return false;
    }
    aceRunArgs_.assetPath = rootJson->GetString("assetPath", "");
    if (aceRunArgs_.assetPath == "") {
        LOGE("The assetPath is null.");
        return false;
    }
    aceRunArgs_.systemResourcesPath = rootJson->GetString("systemResourcesPath", "");
    aceRunArgs_.appResourcesPath = rootJson->GetString("appResourcesPath", "");
    aceRunArgs_.windowTitle = rootJson->GetString("windowTitle", "ACE Demo");
    aceRunArgs_.pageProfile = rootJson->GetString("pageProfile", "main_page");
    aceRunArgs_.url = rootJson->GetString("url", "");
    aceRunArgs_.language = rootJson->GetString("language", "zh");
    aceRunArgs_.region = rootJson->GetString("region", "CN");
    aceRunArgs_.script = rootJson->GetString("script", "");
    aceRunArgs_.configChanges = rootJson->GetString("configChanges", "");
    aceRunArgs_.isRound = rootJson->GetBool("isRound", false);
    aceRunArgs_.formsEnabled = rootJson->GetBool("formsEnabled", false);
    aceRunArgs_.containerSdkPath = rootJson->GetString("containerSdkPath", "");
    aceRunArgs_.themeId = rootJson->GetUInt("themeId", Platform::THEME_ID_LIGHT);
    aceRunArgs_.viewWidth = rootJson->GetInt("viewWidth", 0);
    aceRunArgs_.viewHeight = rootJson->GetInt("viewHeight", 0);
    aceRunArgs_.deviceWidth = rootJson->GetInt("deviceWidth", 0);
    aceRunArgs_.deviceHeight = rootJson->GetInt("deviceHeight", 0);
    aceRunArgs_.aceVersion = Platform::AceVersion::ACE_1_0;
    std::string aceVersion = rootJson->GetString("aceVersion", "1.0");
    auto iterVersion = ACE_VERSION_MAP.find(aceVersion);
    if (iterVersion != ACE_VERSION_MAP.end()) {
        aceRunArgs_.aceVersion = iterVersion->second;
    }
    aceRunArgs_.projectModel = Platform::ProjectModel::FA;
    std::string projectModel = rootJson->GetString("projectModel", "FA");
    auto iterModel = PROJECT_MODEL_MAP.find(projectModel);
    if (iterModel != PROJECT_MODEL_MAP.end()) {
        aceRunArgs_.projectModel = iterModel->second;
    }
    aceRunArgs_.deviceConfig = {
        .orientation = DeviceOrientation::PORTRAIT,
        .density = 1.0,
        .deviceType = DeviceType::PHONE,
        .colorMode = ColorMode::LIGHT,
    };
    auto deviceConfig = rootJson->GetValue("deviceConfig");
    if (deviceConfig) {
        std::string orientation = deviceConfig->GetString("orientation", "portrait");
        auto iterOrientation = DEVICE_ORIENTATION_MAP.find(orientation);
        if (iterOrientation != DEVICE_ORIENTATION_MAP.end()) {
            aceRunArgs_.deviceConfig.orientation = iterOrientation->second;
        }
        std::string deviceType = deviceConfig->GetString("deviceType", "default");
        auto iterDevice = DEVICE_TYPE_MAP.find(deviceType);
        if (iterDevice != DEVICE_TYPE_MAP.end()) {
            aceRunArgs_.deviceConfig.deviceType = iterDevice->second;
        }
        std::string colorMode = deviceConfig->GetString("colorMode", "light");
        auto iterColor = COLOR_MODE_MAP.find(colorMode);
        if (iterColor != COLOR_MODE_MAP.end()) {
            aceRunArgs_.deviceConfig.colorMode = iterColor->second;
        }
        aceRunArgs_.deviceConfig.density = deviceConfig->GetDouble("density", 1.0);
    }
    return true;
}

const Platform::AceRunArgs& RunArgsParser::GetAceRunArgs() const
{
    return aceRunArgs_;
}
} // namespace OHOS::Ace::Samples
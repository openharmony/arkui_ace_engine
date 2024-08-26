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

#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"

#include <fstream>

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {

const std::string CONFIG_PATH = "/etc/";
const std::string ACE_NEW_PIPE_CONFIG_FILE_NAME = "acenewpipe.config";
const std::string ACE_NEW_PIPE_DISABLED_TAG = "DISABLED";
const std::string ACE_NEW_PIPE_ENABLED_FOR_ALL_TAG = "ENABLED_FOR_ALL";
const std::string NEW_PIPE_ENABLED_RELEASE_TYPE = "Beta4";
const std::string NEW_PIPE_ENABLED_RELEASE_TYPE_NEW = "Beta5";
const std::string NEW_PIPE_ENABLED_RELEASE_TYPE_RELEASE = "Release";
constexpr int32_t NEW_PIPE_MIN_VERSION = 9;

} // namespace

bool StartsWith(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
}

std::ifstream& AceNewPipeJudgement::SafeGetLine(std::ifstream& configFile, std::string& line)
{
    std::string myline;
    std::getline(configFile, myline);
    if (!myline.empty() && myline[myline.size() - 1] == '\r') {
        line = myline.substr(0, myline.size() - 1);
    } else {
        line = myline;
    }
    return configFile;
}

bool AceNewPipeJudgement::QueryAceNewPipeEnabledFA(const std::string& packagename, uint32_t apiCompatibleVersion,
    uint32_t apiTargetVersion, const std::string& apiReleaseType)
{
    if (((apiTargetVersion == NEW_PIPE_MIN_VERSION &&
            (apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE || apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE_NEW ||
                apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE_RELEASE ||
                SystemProperties::GetExtSurfaceEnabled())) ||
            apiTargetVersion > NEW_PIPE_MIN_VERSION) &&
        apiCompatibleVersion >= NEW_PIPE_MIN_VERSION) {
        return true;
    }
    switch (aceNewPipeEnabledType_) {
        case AceNewPipeEnabledType::ACE_NEW_PIPE_PARTIALLY_ENABLED:
            return aceNewPipeEnabledList_.find(packagename) != aceNewPipeEnabledList_.end();
        case AceNewPipeEnabledType::ACE_NEW_PIPE_ENABLED_FOR_ALL:
            return true;
        case AceNewPipeEnabledType::ACE_NEW_PIPE_DISABLED:
            return false;
        default:
            return false;
    }
}

bool AceNewPipeJudgement::QueryAceNewPipeEnabledStage(const std::string& packagename, uint32_t apiCompatibleVersion,
    uint32_t apiTargetVersion, const std::string& apiReleaseType, bool closeArkTSPartialUpdate)
{
    if (closeArkTSPartialUpdate) {
        return false;
    }
    if (((apiTargetVersion == NEW_PIPE_MIN_VERSION &&
             (apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE || apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE_NEW ||
                 apiReleaseType == NEW_PIPE_ENABLED_RELEASE_TYPE_RELEASE ||
                 SystemProperties::GetExtSurfaceEnabled())) ||
            apiTargetVersion > NEW_PIPE_MIN_VERSION) &&
        apiCompatibleVersion >= NEW_PIPE_MIN_VERSION) {
        return true;
    }
    switch (aceNewPipeEnabledType_) {
        case AceNewPipeEnabledType::ACE_NEW_PIPE_PARTIALLY_ENABLED:
            return aceNewPipeEnabledList_.find(packagename) != aceNewPipeEnabledList_.end();
        case AceNewPipeEnabledType::ACE_NEW_PIPE_ENABLED_FOR_ALL:
            return true;
        case AceNewPipeEnabledType::ACE_NEW_PIPE_DISABLED:
            return false;
        default:
            return false;
    }
}

void AceNewPipeJudgement::InitAceNewPipeConfig()
{
    if (!InitedAceNewPipeConfig_) {
        InitAceNewPipeWithConfigFile();
        LOGI("Init RenderService UniRender Type:%{public}d", aceNewPipeEnabledType_);
    }
}

void AceNewPipeJudgement::InitAceNewPipeWithConfigFile()
{
    // open config file
    std::string configFilePath = CONFIG_PATH + ACE_NEW_PIPE_CONFIG_FILE_NAME;
    std::ifstream configFile = std::ifstream(configFilePath.c_str());
    std::string line;
    // first line, init aceNewPipeEnabledType_
    if (!configFile.is_open() || !SafeGetLine(configFile, line) || line.empty()) {
        aceNewPipeEnabledType_ = AceNewPipeEnabledType::ACE_NEW_PIPE_DISABLED;
    } else if (line == ACE_NEW_PIPE_DISABLED_TAG) {
        aceNewPipeEnabledType_ = AceNewPipeEnabledType::ACE_NEW_PIPE_DISABLED;
    } else if (line == ACE_NEW_PIPE_ENABLED_FOR_ALL_TAG) {
        aceNewPipeEnabledType_ = AceNewPipeEnabledType::ACE_NEW_PIPE_ENABLED_FOR_ALL;
    } else {
        while (SafeGetLine(configFile, line)) {
            if (line.empty() || StartsWith(line, "//")) {
                continue;
            }
            aceNewPipeEnabledList_.insert(line);
        }
        if (!aceNewPipeEnabledList_.empty()) {
            aceNewPipeEnabledType_ = AceNewPipeEnabledType::ACE_NEW_PIPE_PARTIALLY_ENABLED;
        }
    }
    configFile.close();
    InitedAceNewPipeConfig_ = true;
}
} // namespace OHOS::Ace
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

#include "frameworks/bridge/common/manifest/manifest_appinfo.h"

namespace OHOS::Ace::Framework {

const std::string& ManifestAppInfo::GetAppID() const
{
    return appID_;
}

const std::string& ManifestAppInfo::GetAppName() const
{
    return appName_;
}

const std::string& ManifestAppInfo::GetIcon() const
{
    return icon_;
}

const std::string& ManifestAppInfo::GetVersionName() const
{
    return versionName_;
}

uint32_t ManifestAppInfo::GetVersionCode() const
{
    return versionCode_;
}

const std::string& ManifestAppInfo::GetLogLevel() const
{
    return logLevel_;
}

const std::string& ManifestAppInfo::GetMinPlatformVersion() const
{
    return minPlatformVersion_;
}

void ManifestAppInfo::AppInfoParse(const std::unique_ptr<JsonValue>& root)
{
    if (!root) {
        return;
    }

    appName_ = root->GetString("appName");
    versionName_ = root->GetString("versionName");
    versionCode_ = root->GetUInt("versionCode");
    logLevel_ = root->GetString("logLevel");
    icon_ = root->GetString("icon");
    appID_ = root->GetString("appID");
    minPlatformVersion_ = root->GetString("minPlatformVersion");
}

} // namespace OHOS::Ace::Framework

/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/external/ability/fa/fa_app_info.h"

namespace OHOS::Ace {
void FaAppInfo::Parse(const std::unique_ptr<JsonValue>& root)
{
    if (!root) {
        LOGW("The information of fa model application is empty.");
        return;
    }
    auto apiVersion = root->GetValue("apiVersion");
    if (apiVersion) {
        minAPIVersion_ = apiVersion->GetUInt("compatible", 0);
        apiReleaseType_ = apiVersion->GetString("releaseType");
        targetAPIVersion_ = apiVersion->GetUInt("target", 0);
    }

    bundleName_ = root->GetString("bundleName");
    vendor_ = root->GetString("vendor");

    auto versionInfo = root->GetValue("version");
    if (versionInfo) {
        versionCode_ = versionInfo->GetUInt("code", 0);
        versionName_ = versionInfo->GetString("name");
    }
}

uint32_t FaAppInfo::GetMinAPIVersion() const
{
    return minAPIVersion_;
}

const std::string& FaAppInfo::GetApiReleaseType() const
{
    return apiReleaseType_;
}

uint32_t FaAppInfo::GetTargetAPIVersion() const
{
    return targetAPIVersion_;
}

const std::string& FaAppInfo::GetBundleName() const
{
    return bundleName_;
}

const std::string& FaAppInfo::GetVendor() const
{
    return vendor_;
}

uint32_t FaAppInfo::GetVersionCode() const
{
    return versionCode_;
}

const std::string& FaAppInfo::GetVersionName() const
{
    return versionName_;
}
} // namespace OHOS::Ace

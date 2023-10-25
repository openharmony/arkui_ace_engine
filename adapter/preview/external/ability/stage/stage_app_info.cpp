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

#include "adapter/preview/external/ability/stage/stage_app_info.h"

namespace OHOS::Ace {
void StageAppInfo::Parse(const std::unique_ptr<JsonValue>& root)
{
    if (!root) {
        LOGW("The information of stage model application is empty.");
        return;
    }
    apiReleaseType_ = root->GetString("apiReleaseType");
    bundleName_ = root->GetString("bundleName");
    bundleType_ = root->GetString("bundleType");
    icon_ = root->GetString("icon");
    label_ = root->GetString("label");
    vendor_ = root->GetString("vendor");
    versionName_ = root->GetString("versionName");
    debug_ = root->GetBool("debug", false);
    distributedNotificationEnabled_ = root->GetBool("distributedNotificationEnabled", true);
    iconId_ = root->GetUInt("iconId", 0);
    labelId_ = root->GetUInt("labelId", 0);
    minAPIVersion_ = root->GetUInt("minAPIVersion", 0);
    targetAPIVersion_ = root->GetUInt("targetAPIVersion", 0);
    versionCode_ = root->GetUInt("versionCode", 0);
}

const std::string& StageAppInfo::GetApiReleaseType() const
{
    return apiReleaseType_;
}

const std::string& StageAppInfo::GetBundleName() const
{
    return bundleName_;
}

const std::string& StageAppInfo::GetIcon() const
{
    return icon_;
}

const std::string& StageAppInfo::GetLabel() const
{
    return label_;
}

const std::string& StageAppInfo::GetVendor() const
{
    return vendor_;
}

const std::string& StageAppInfo::GetVersionName() const
{
    return versionName_;
}

bool StageAppInfo::GetDebug() const
{
    return debug_;
}

bool StageAppInfo::GetDistributedNotificationEnabled() const
{
    return distributedNotificationEnabled_;
}

uint32_t StageAppInfo::GetIconId() const
{
    return iconId_;
}

uint32_t StageAppInfo::GetLabelId() const
{
    return labelId_;
}

uint32_t StageAppInfo::GetMinAPIVersion() const
{
    return minAPIVersion_;
}

uint32_t StageAppInfo::GetTargetAPIVersion() const
{
    return targetAPIVersion_;
}

uint32_t StageAppInfo::GetVersionCode() const
{
    return versionCode_;
}

bool StageAppInfo::IsInstallationFree() const
{
    if (bundleType_ == "atomicService") {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace

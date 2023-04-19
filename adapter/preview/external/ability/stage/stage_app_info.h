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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_APP_INFO_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_APP_INFO_H

#include <string>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class StageAppInfo : public AceType {
    DECLARE_ACE_TYPE(StageAppInfo, AceType);

public:
    StageAppInfo() = default;
    ~StageAppInfo() override = default;
    void Parse(const std::unique_ptr<JsonValue>& root);
    const std::string& GetApiReleaseType() const;
    const std::string& GetBundleName() const;
    const std::string& GetIcon() const;
    const std::string& GetLabel() const;
    const std::string& GetVendor() const;
    const std::string& GetVersionName() const;
    bool GetDebug() const;
    bool GetDistributedNotificationEnabled() const;
    uint32_t GetIconId() const;
    uint32_t GetLabelId() const;
    uint32_t GetMinAPIVersion() const;
    uint32_t GetTargetAPIVersion() const;
    uint32_t GetVersionCode() const;
    bool IsInstallationFree() const;

private:
    std::string apiReleaseType_;
    std::string bundleName_;
    std::string bundleType_;
    std::string icon_;
    std::string label_;
    std::string vendor_;
    std::string versionName_;
    bool debug_ = false;
    bool distributedNotificationEnabled_ = true;
    uint32_t iconId_;
    uint32_t labelId_ = 0;
    uint32_t minAPIVersion_ = 0;
    uint32_t targetAPIVersion_ = 0;
    uint32_t versionCode_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(StageAppInfo);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_APP_INFO_H

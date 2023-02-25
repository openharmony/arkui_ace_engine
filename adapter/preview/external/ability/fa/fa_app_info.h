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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_APP_INFO_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_APP_INFO_H

#include <string>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class FaAppInfo : public AceType {
    DECLARE_ACE_TYPE(FaAppInfo, AceType);

public:
    FaAppInfo() = default;
    ~FaAppInfo() override = default;
    void Parse(const std::unique_ptr<JsonValue>& root);
    uint32_t GetMinAPIVersion() const;
    const std::string& GetApiReleaseType() const;
    uint32_t GetTargetAPIVersion() const;
    const std::string& GetBundleName() const;
    const std::string& GetVendor() const;
    uint32_t GetVersionCode() const;
    const std::string& GetVersionName() const;

private:
    uint32_t minAPIVersion_ = 0;
    std::string apiReleaseType_;
    uint32_t targetAPIVersion_ = 0;
    std::string bundleName_;
    std::string vendor_;
    uint32_t versionCode_ = 0;
    std::string versionName_;
    ACE_DISALLOW_COPY_AND_MOVE(FaAppInfo);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_APP_INFO_H

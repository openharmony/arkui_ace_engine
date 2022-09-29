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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_MODULE_PARSER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_MODULE_PARSER_H

#include <string>

#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace {

class StageAppInfo : public Referenced {
public:
    StageAppInfo() = default;
    ~StageAppInfo() override = default;
    void AppInfoParse(const std::unique_ptr<JsonValue>& root);
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

private:
    std::string apiReleaseType_;
    std::string bundleName_;
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

class StageModuleInfo : public Referenced {
public:
    StageModuleInfo() = default;
    ~StageModuleInfo() override = default;
    void ModuleInfoParse(const std::unique_ptr<JsonValue>& root);
    const std::string& GetCompileMode() const;

private:
    std::string compileMode_;
    ACE_DISALLOW_COPY_AND_MOVE(StageModuleInfo);
};

class StageModuleParser : public Referenced {
public:
    StageModuleParser();
    ~StageModuleParser() override = default;
    void Parse(const std::string& contents);
    const RefPtr<StageAppInfo>& GetAppInfo() const;
    const RefPtr<StageModuleInfo>& GetModuleInfo() const;

private:
    RefPtr<StageAppInfo> stageAppInfo_;
    RefPtr<StageModuleInfo> stageModuleInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(StageModuleParser);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_OSAL_STAGE_MODULE_PARSER_H

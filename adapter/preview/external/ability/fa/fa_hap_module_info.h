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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_HAP_MODULE_INFO_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_HAP_MODULE_INFO_H

#include <string>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class FaHapModuleInfo : public AceType {
    DECLARE_ACE_TYPE(FaHapModuleInfo, AceType);

public:
    FaHapModuleInfo() = default;
    ~FaHapModuleInfo() override = default;
    void Parse(const std::unique_ptr<JsonValue>& root);
    const std::string& GetMainAbility() const;
    const std::string& GetModuleName() const;
    const std::string& GetPackage() const;

private:
    std::string mainAbility_;
    std::string moduleName_;
    std::string package_;
    ACE_DISALLOW_COPY_AND_MOVE(FaHapModuleInfo);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_FA_HAP_MODULE_INFO_H

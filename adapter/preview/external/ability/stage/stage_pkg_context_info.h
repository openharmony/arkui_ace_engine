/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_PKG_CONTEXT_INFO_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_PKG_CONTEXT_INFO_H

#include <string>
#include <map>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace {
    class StagePkgContextInfo : public AceType {
        DECLARE_ACE_TYPE(StagePkgContextInfo, AceType);
public:
    StagePkgContextInfo() = default;
    ~StagePkgContextInfo() = default;
    void SetPkgContextInfoAndAliasMap(const std::map<std::string, std::string>& map);
    void AliasMap(std::unique_ptr<JsonValue>& item,
        std::vector<std::vector<std::string>>& pkgContextInfoList, const std::string& moduleName);
    void SetPkgNameList(const std::map<std::string, std::string>& map);
    const std::map<std::string, std::string>& GetPkgNameMap() const;
    const std::map<std::string, std::string>& GetPkgAliasMap() const;
    const std::map<std::string, std::vector<std::vector<std::string>>>& GetPkgContextInfoMap();
private:
    std::map<std::string, std::string> pkgNameMap_;
    std::map<std::string, std::string> pkgAliasMap_;
    std::map<std::string, std::vector<std::vector<std::string>>> pkgContextInfoMap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_ABILITY_STAGE_PKG_CONTEXT_INFO_H

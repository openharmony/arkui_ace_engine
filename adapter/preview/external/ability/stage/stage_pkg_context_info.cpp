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

#include "adapter/preview/external/ability/stage/stage_pkg_context_info.h"

#include <memory>

#include "frameworks/base/json/json_util.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace {
void StagePkgContextInfo::SetPkgNameList(const std::map<std::string, std::string>& map)
{
    pkgNameMap_ = map;
}

void StagePkgContextInfo::SetPkgContextInfoAndAliasMap(const std::map<std::string, std::string>& map)
{
    if (map.empty()) {
        LOGW("pkgcontextinfo map is empty");
        return;
    }
    for (auto it = map.begin(); it != map.end(); it++) {
        std::string moduleName = it->first;
        std::string pkgInfoStr = it->second;
        if (pkgInfoStr.empty()) {
            return;
        }
        std::unique_ptr<JsonValue> json = JsonUtil::ParseJsonString(pkgInfoStr);
        if (!json) {
            return;
        }
        std::vector<std::vector<std::string>> pkgContextInfoList;
        std::unique_ptr<JsonValue> item = json->GetChild();
        AliasMap(item, pkgContextInfoList, moduleName);
    }
}
void StagePkgContextInfo::AliasMap(std::unique_ptr<JsonValue>& item,
    std::vector<std::vector<std::string>>& pkgContextInfoList, const std::string& moduleName)
{
    while (item && !item->GetKey().empty()) {
        std::vector<std::string> sonMap;
        std::string key = item->GetKey();
        sonMap.push_back(key);
        std::unique_ptr<JsonValue> item1 = item->GetChild();
        while (item1 && !item1->GetKey().empty()) {
            std::string key1 = item1->GetKey();
            sonMap.push_back(key1);
            if ("dependencyAlias" == key1) {
                bool value = item1->GetBool();
                std::string val1 = value ? "true" : "false";
                sonMap.push_back(val1);
                pkgAliasMap_.emplace(val1, key);
            } else {
                std::string val1 = item1->GetString();
                sonMap.push_back(val1);
            }
            item1 = item1->GetNext();
        }
        pkgContextInfoList.push_back(sonMap);
        item = item->GetNext();
    }
    pkgContextInfoMap_[moduleName] = pkgContextInfoList;
}
const std::map<std::string, std::string>& StagePkgContextInfo::GetPkgNameMap() const
{
    return pkgNameMap_;
}
const std::map<std::string, std::string>& StagePkgContextInfo::GetPkgAliasMap() const
{
    return pkgAliasMap_;
}
const std::map<std::string, std::vector<std::vector<std::string>>>& StagePkgContextInfo::GetPkgContextInfoMap()
{
    return pkgContextInfoMap_;
}
}

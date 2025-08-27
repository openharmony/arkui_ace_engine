/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "adapter/ohos/capability/feature_config/features/sync_load_parser.h"

#include "adapter/ohos/capability/feature_config/feature_param_manager.h"
#include "base/utils/string_utils.h"
#include "base/log/log.h"

namespace OHOS::Ace {
bool SyncLoadParser::IsValidDigits(const std::string& str)
{
    if (str.empty() || str.size() > FeatureParamManager::MAX_TIMER_SIZE) {
        return false;
    }
    for (char ch : str) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

ParseErrCode SyncLoadParser::ParseFeatureParam(xmlNode& node)
{
    auto& instance = FeatureParamManager::GetInstance();
    auto enabled = ExtractPropertyValue("enable", node) == "true";
    auto responseDeadlineStr = ExtractPropertyValue("value", node);
    if (!IsValidDigits(responseDeadlineStr)) {
        LOGW("SyncLoadParser::ParseFeatureParam invalid digits %{public}s", responseDeadlineStr.c_str());
        return PARSE_TYPE_ERROR;
    }
    auto deadline = StringUtils::StringToInt(responseDeadlineStr, FeatureParamManager::DEFAULT_SYNCLOAD_DEADLINE);
    instance.SetSyncLoadEnableParam(enabled, deadline * FeatureParamManager::MS_TO_NS);
    return PARSE_EXEC_SUCCESS;
}

} // namespace OHOS::Ace

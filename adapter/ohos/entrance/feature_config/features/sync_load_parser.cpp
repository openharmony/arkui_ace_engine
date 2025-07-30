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

#include "sync_load_parser.h"

#include <cctype>

#include "base/utils/system_properties.h"
#include "interfaces/inner_api/ace/arkui_log.h"

namespace OHOS::Ace {

bool SyncloadParser::enabled_ = false;
uint32_t SyncloadParser::responseDeadline_ = 50000000;  // default time 50ms

bool SyncloadParser::IsSyncloadEnable()
{
    return enabled_;
}

uint32_t SyncloadParser::GetSyncloadResponseDeadline()
{
    return responseDeadline_;
}

bool SyncloadParser::IsValidDigits(const std::string& str)
{
    if (str.empty() || str.size() > MAX_TIMER_SIZE) {
        return false;
    }
    for (char ch : str) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }
    return true;
}

ParseErrCode SyncloadParser::ParseFeatureParam(xmlNode& node)
{
    enabled_ = ExtractPropertyValue("enable", node) == "true";
    auto responseDeadline = ExtractPropertyValue("value", node);
    if (!IsValidDigits(responseDeadline)) {
        LOGW("SyncloadParser::ParseFeatureParam invalid digits %{public}s", responseDeadline.c_str());
        return PARSE_TYPE_ERROR;
    }
    responseDeadline_ = std::stoi(responseDeadline) * MS_TO_NS;
    LOGI("SyncloadParser::ParseFeatureParam %{public}d deadline %{public}u", enabled_, responseDeadline_);

    return PARSE_EXEC_SUCCESS;
}

} // namespace OHOS::Ace::NG
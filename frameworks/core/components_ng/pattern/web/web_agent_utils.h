/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_AGENT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_AGENT_UTILS_H

#include <string>
#include <vector>

#include "base/json/json_util.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {

class WebDomDocument;
class WebAgentUtils {
public:
    enum class HighlightErrorType : int32_t {
        SUCCESS = 0,
        XPATH_ERROR = 1,
        NODE_NOT_FOUND = 2,
        TEXT_NOT_MATCH = 3,
        UNKNOWN = 4,
    };

    static inline bool IsValidHighlightErrorType(int32_t value)
    {
        return value >= static_cast<int32_t>(HighlightErrorType::SUCCESS) &&
               value <= static_cast<int32_t>(HighlightErrorType::UNKNOWN);
    }

    struct HighlightErrorItem {
        HighlightErrorType type;
        int32_t index;
        std::string content;
        std::string message;

        HighlightErrorItem() : type(HighlightErrorType::UNKNOWN), index(-1), content(""), message("") {}
    };

    static bool IsNumber(const std::string& str);
    static std::unique_ptr<JsonValue> ValidateHighlightResultJson(const std::string& resultJson);
    static WebAgentUtils::HighlightErrorItem ParseHighlightErrorItem(const std::unique_ptr<JsonValue>& item);
    static std::string GetErrorNodeFromIndex(int32_t index, const std::vector<std::string>& Xpaths);
    static std::string ConvertErrorTypeToString(HighlightErrorType typeError);
    static void ReportHighlightErrorEvent(const WebAgentUtils::HighlightErrorItem& item, const std::string& errorNode);
    static bool ParseHighlightResult(const std::string& resultJson, const std::vector<std::string>& Xpaths);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_AGENT_UTILS_H

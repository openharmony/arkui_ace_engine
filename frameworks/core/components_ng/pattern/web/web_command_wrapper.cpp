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

#include "core/components_ng/pattern/web/web_command_wrapper.h"

#include "base/log/log_wrapper.h"

namespace OHOS {
namespace Ace {

// Initialize static constants
const char* const WebCommandWrapper::EVENT_TYPE_KEY = "event_type";
const char* const WebCommandWrapper::XPATH_KEY = "XPath";
const char* const WebCommandWrapper::DURATION_KEY = "duration";
const char* const WebCommandWrapper::ALIGN_KEY = "align";
const char* const WebCommandWrapper::OFFSET_KEY = "offset";

bool WebCommandWrapper::IsValidEventType(const std::string& eventTypeStr)
{
    return eventTypeStr == "click" || eventTypeStr == "scroll";
}

bool WebCommandWrapper::IsValidAlign(const std::string& alignStr)
{
    return alignStr == "top" || alignStr == "mid" || alignStr == "bottom";
}

int WebCommandWrapper::ValidateClickParameters(
    const std::unique_ptr<JsonValue>& comJson,
    std::string& outXPath)
{
    // Validate XPath (required for click)
    auto xpathValue = comJson->GetValue(XPATH_KEY);
    if (!xpathValue || !xpathValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: XPath is missing or not string type");
        return static_cast<int>(!xpathValue ? WebCommandResult::JSON_MISSING_XPATH :
                                              WebCommandResult::JSON_INVALID_XPATH);
    }
    outXPath = xpathValue->GetString();
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateScrollParameters(
    const std::unique_ptr<JsonValue>& comJson,
    int32_t& outDuration,
    std::string& outAlign,
    int32_t& outOffset,
    std::string& outXPath)
{
    // Validate XPath (required for scroll)
    auto xpathValue = comJson->GetValue(XPATH_KEY);
    if (!xpathValue || !xpathValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: XPath is missing or not string type");
        return static_cast<int>(!xpathValue ? WebCommandResult::JSON_MISSING_XPATH :
                                              WebCommandResult::JSON_INVALID_XPATH);
    }
    outXPath = xpathValue->GetString();

    auto durationValue = comJson->GetValue(DURATION_KEY);
    if (!durationValue || !durationValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: duration is missing or not integer type");
        return static_cast<int>(!durationValue ? WebCommandResult::JSON_MISSING_DURATION :
                                                 WebCommandResult::JSON_INVALID_DURATION);
    }
    outDuration = static_cast<int32_t>(comJson->GetInt(DURATION_KEY, 0));

    auto alignValue = comJson->GetValue(ALIGN_KEY);
    if (!alignValue || !alignValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: align is missing or not string type");
        return static_cast<int>(!alignValue ? WebCommandResult::JSON_MISSING_ALIGN :
                                              WebCommandResult::JSON_INVALID_ALIGN);
    }
    outAlign = alignValue->GetString();
    if (!IsValidAlign(outAlign)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: align must be 'top' 'mid' or 'bottom', but got %{public}s",
            outAlign.c_str());
        return static_cast<int>(WebCommandResult::JSON_VALUE_ERROR_ALIGN);
    }

    auto offsetValue = comJson->GetValue(OFFSET_KEY);
    if (!offsetValue || !offsetValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: offset is missing or not integer type");
        return static_cast<int>(!offsetValue ? WebCommandResult::JSON_MISSING_OFFSET :
                                               WebCommandResult::JSON_INVALID_OFFSET);
    }
    outOffset = comJson->GetInt(OFFSET_KEY, -1);

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::BuildCommandFromJson(
    const std::unique_ptr<JsonValue>& comJson,
    std::shared_ptr<NWebCommandActionImpl>& outCommandAction)
{
    // Validate event_type
    auto eventTypeValue = comJson->GetValue(EVENT_TYPE_KEY);
    if (!eventTypeValue || !eventTypeValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: event_type is missing or not string type");
        return static_cast<int>(!eventTypeValue ? WebCommandResult::JSON_MISSING_EVENT_TYPE :
                                                 WebCommandResult::JSON_INVALID_EVENT_TYPE);
    }
    std::string eventTypeStr = eventTypeValue->GetString();
    if (!IsValidEventType(eventTypeStr)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: event_type must be 'click' or 'scroll', but got %{public}s",
            eventTypeStr.c_str());
        return static_cast<int>(WebCommandResult::JSON_VALUE_ERROR_EVENT_TYPE);
    }

    // Initialize parameters with default values
    std::string xpathStr = "";
    std::string alignStr = "";
    int32_t durationInt = 0;
    int32_t offsetInt = 0;
    int validationResult = WEB_COMMAND_BUILD_SUCCESS;

    // Use switch to validate event-type-specific parameters
    if (eventTypeStr == "click") {
        validationResult = ValidateClickParameters(comJson, xpathStr);
    } else if (eventTypeStr == "scroll") {
        validationResult = ValidateScrollParameters(comJson, durationInt, alignStr, offsetInt, xpathStr);
    }

    if (validationResult != WEB_COMMAND_BUILD_SUCCESS) {
        return validationResult;
    }

    TAG_LOGD(AceLogTag::ACE_WEB,
        "Command: is ready eventTypeStr =%{public}s , xpathStr= %{public}s, durationint=%{public}d, alignStr = "
        "%{public}s,offsetInt = %{public}d",
        eventTypeStr.c_str(), xpathStr.c_str(), durationInt, alignStr.c_str(), offsetInt);

    // Create the command action object
    outCommandAction = std::make_shared<NWebCommandActionImpl>(
        eventTypeStr, xpathStr, durationInt, alignStr, offsetInt);

    return WEB_COMMAND_BUILD_SUCCESS;
}

} // namespace Ace
} // namespace OHOS

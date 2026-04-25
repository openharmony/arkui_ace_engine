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
const char* const WebCommandWrapper::VALUE_KEY = "value";
const char* const WebCommandWrapper::INDEX_KEY = "index";
const char* const WebCommandWrapper::DURATION_KEY = "duration";
const char* const WebCommandWrapper::ALIGN_KEY = "align";
const char* const WebCommandWrapper::OFFSET_KEY = "offset";

WebCommandEventType WebCommandWrapper::ParseEventType(const std::string& eventTypeStr)
{
    static const std::unordered_map<std::string, WebCommandEventType> eventTypeMap = {
        {"click", WebCommandEventType::CLICK},
        {"scroll", WebCommandEventType::SCROLL},
        {"input-date", WebCommandEventType::INPUT_DATE},
        {"input-datetime-local", WebCommandEventType::INPUT_DATETIME_LOCAL},
        {"input-month", WebCommandEventType::INPUT_MONTH},
        {"input-time", WebCommandEventType::INPUT_TIME},
        {"input-week", WebCommandEventType::INPUT_WEEK},
        {"select", WebCommandEventType::SELECT},
    };
    auto it = eventTypeMap.find(eventTypeStr);
    if (it != eventTypeMap.end()) {
        return it->second;
    }
    return WebCommandEventType::UNKNOWN;
}

bool WebCommandWrapper::IsValidAlign(const std::string& alignStr)
{
    return alignStr == "top" || alignStr == "mid" || alignStr == "bottom";
}

int WebCommandWrapper::BuildInputActionInfo(
    const std::unique_ptr<JsonValue>& comJson,
    const std::string& eventTypeStr,
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo)
{
    auto xpathValue = comJson->GetValue(XPATH_KEY);
    if (!xpathValue || !xpathValue->IsString() || xpathValue->GetString().empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "[WebCommandAction] BuildInputActionInfo: xpath is invalid");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_XPATH);
    }

    auto valueValue = comJson->GetValue(VALUE_KEY);
    if (!valueValue || !valueValue->IsString() || valueValue->GetString().empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "[WebCommandAction] BuildInputActionInfo: value is invalid");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INPUT_VALUE);
    }

    outActionInfo = NWebCommandActionInfoImpl::CreateInputInfo(
        eventTypeStr, valueValue->GetString(), xpathValue->GetString());
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::BuildSelectActionInfo(
    const std::unique_ptr<JsonValue>& comJson,
    const std::string& eventTypeStr,
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo)
{
    auto xpathValue = comJson->GetValue(XPATH_KEY);
    if (!xpathValue || !xpathValue->IsString() || xpathValue->GetString().empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "[WebCommandAction] BuildSelectActionInfo: xpath is invalid");
        return static_cast<int>(WebCommandResult::JSON_INVALID_SELECT_XPATH);
    }
    std::string xpath = xpathValue->GetString();

    std::vector<std::string> values;
    auto valueValue = comJson->GetValue(VALUE_KEY);
    if (valueValue && valueValue->IsArray()) {
        for (int32_t i = 0; i < valueValue->GetArraySize(); ++i) {
            auto item = valueValue->GetArrayItem(i);
            if (item && item->IsString()) {
                values.push_back(item->GetString());
            }
        }
    }

    std::vector<int32_t> indexes;
    auto indexValue = comJson->GetValue(INDEX_KEY);
    if (indexValue && indexValue->IsArray()) {
        for (int32_t i = 0; i < indexValue->GetArraySize(); ++i) {
            auto item = indexValue->GetArrayItem(i);
            if (item && item->IsNumber()) {
                indexes.push_back(static_cast<int32_t>(item->GetInt()));
            }
        }
    }

    if (values.empty() && indexes.empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "[WebCommandAction] BuildSelectActionInfo: values and indexes are both empty");
        return static_cast<int>(WebCommandResult::JSON_INVALID_SELECT_OPTIONS);
    }

    outActionInfo = NWebCommandActionInfoImpl::CreateSelectInfo(
        eventTypeStr, values, xpath, indexes);
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateClickParameters(
    const std::unique_ptr<JsonValue>& comJson,
    std::string& outXPath)
{
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

int WebCommandWrapper::BuildClickScrollAction(
    const std::unique_ptr<JsonValue>& comJson,
    const std::string& eventTypeStr,
    std::shared_ptr<NWebCommandActionImpl>& outCommandAction)
{
    std::string xpathStr;
    std::string alignStr;
    int32_t durationInt = 0;
    int32_t offsetInt = 0;
    int validationResult = WEB_COMMAND_BUILD_SUCCESS;

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

    outCommandAction = std::make_shared<NWebCommandActionImpl>(
        eventTypeStr, xpathStr, durationInt, alignStr, offsetInt);

    return WEB_COMMAND_BUILD_SUCCESS;
}

} // namespace Ace
} // namespace OHOS

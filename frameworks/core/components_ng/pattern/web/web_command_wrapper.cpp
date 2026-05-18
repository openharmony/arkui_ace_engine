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
const char* const WebCommandWrapper::CONTENT_KEY = "content";
const char* const WebCommandWrapper::START_INDEX_KEY = "start_index";
const char* const WebCommandWrapper::FINISH_INDEX_KEY = "finish_index";
const char* const WebCommandWrapper::NO_NEED_KEYBOARD_KEY = "no_need_keyboard";

WebCommandEventType WebCommandWrapper::ParseEventType(const std::string& eventTypeStr)
{
    static const std::unordered_map<std::string, WebCommandEventType> eventTypeMap = {
        {"click", WebCommandEventType::CLICK},
        {"scroll", WebCommandEventType::SCROLL},
        {"scrollGesture", WebCommandEventType::EVENT_TYPE_SCROLL_GESTURE},
        {"tap", WebCommandEventType::EVENT_TYPE_TAP_GESTURE},
        {"pinch", WebCommandEventType::EVENT_TYPE_PINCH_GESTURE},
        {"longPress", WebCommandEventType::EVENT_TYPE_LONG_PRESS},
        {"input-date", WebCommandEventType::INPUT_DATE},
        {"input-datetime-local", WebCommandEventType::INPUT_DATETIME_LOCAL},
        {"input-month", WebCommandEventType::INPUT_MONTH},
        {"input-time", WebCommandEventType::INPUT_TIME},
        {"input-week", WebCommandEventType::INPUT_WEEK},
        {"select", WebCommandEventType::SELECT},
        {"inputInsert", WebCommandEventType::INPUT_INSERT},
        {"inputModify", WebCommandEventType::INPUT_MODIFY},
        {"inputSelect", WebCommandEventType::INPUT_SELECT},
        {"inputCut", WebCommandEventType::INPUT_CUT},
        {"inputCopy", WebCommandEventType::INPUT_COPY},
        {"inputFocus", WebCommandEventType::INPUT_FOCUS},
        {"inputSetCursor", WebCommandEventType::INPUT_SET_CURSOR},
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
int WebCommandWrapper::ValidateInputInsertParameters(
    const std::unique_ptr<JsonValue>& comJson,
    std::string& outContent,
    int32_t& outIndex)
{
    // Validate outContent (required for InputInsert)
    auto contentValue = comJson->GetValue(CONTENT_KEY);
    if (!contentValue || !contentValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: content is missing");
        return static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT);
    }
    outContent = contentValue->GetString();
    
    // Validate outIndex (required for InputInsert)
    auto indexValue = comJson->GetValue(INDEX_KEY);
    if (!indexValue || !indexValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is missing");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    double indexDouble = comJson->GetDouble(INDEX_KEY, 0);
    if (indexDouble != static_cast<int>(indexDouble)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is not integer");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    outIndex = comJson->GetInt(INDEX_KEY, 0);
    if (outIndex < 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is invalid value");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateInputModifyParameters(
    const std::unique_ptr<JsonValue>& comJson,
    std::string& outContent)
{
    // Validate outContent (required for InputModify)
    auto contentValue = comJson->GetValue(CONTENT_KEY);
    if (!contentValue || !contentValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: content is missing or not string type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_CONTENT);
    }
    outContent = contentValue->GetString();
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateInputSelectParameters(
    const std::unique_ptr<JsonValue>& comJson,
    int32_t& outStartIndex,
    int32_t& outFinishIndex)
{
    // Validate outStartIndex (required for InputSelect)
    auto startIndexValue = comJson->GetValue(START_INDEX_KEY);
    if (!startIndexValue || !startIndexValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: start index is missing");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    outStartIndex = comJson->GetInt(START_INDEX_KEY, 0);
    // Validate outFinishIndex (required for InputSelect)
    auto finishIndexValue = comJson->GetValue(FINISH_INDEX_KEY);
    if (!finishIndexValue || !finishIndexValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: finish index is missing");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    outFinishIndex = comJson->GetInt(FINISH_INDEX_KEY, 0);

    double indexDouble = comJson->GetDouble(START_INDEX_KEY, 0);
    if (indexDouble != static_cast<int>(indexDouble)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: start index is not integer");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    indexDouble = comJson->GetDouble(FINISH_INDEX_KEY, 0);
    if (indexDouble != static_cast<int>(indexDouble)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: finish index is not integer");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    
    if (outStartIndex < 0 || outFinishIndex < 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is invalid value");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    if (outStartIndex >= outFinishIndex) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: duration not right");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX_DURATION);
    }
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateInputFocusParameters(
    const std::unique_ptr<JsonValue>& comJson,
    std::string& outXPath,
    int32_t& outNoNeedKeyboardInt)
{
    // Validate XPath (required for InputFocus)
    auto xpathValue = comJson->GetValue(XPATH_KEY);
    if (!xpathValue || !xpathValue->IsString()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: XPath is missing or not string type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_XPATH);
    }
    outXPath = xpathValue->GetString();

    double indexDouble = comJson->GetDouble(NO_NEED_KEYBOARD_KEY, 0);
    if (indexDouble != static_cast<int>(indexDouble)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: is need keyboard is invalid");
        return static_cast<int>(WebCommandResult::JSON_INVALID_NO_NEED_KEYBOARD);
    }

    auto noNeedKeyboardValue = comJson->GetValue(NO_NEED_KEYBOARD_KEY);
    if (noNeedKeyboardValue && noNeedKeyboardValue->GetInt() != 0 && noNeedKeyboardValue->GetInt() != 1) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: is need keyboard is invalid");
        return static_cast<int>(WebCommandResult::JSON_INVALID_NO_NEED_KEYBOARD);
    }
    outNoNeedKeyboardInt = comJson->GetInt(NO_NEED_KEYBOARD_KEY, 0);

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateInputSetCursorParameters(
    const std::unique_ptr<JsonValue>& comJson,
    int32_t& outIndex)
{
    // Validate outIndex (required for InputSetCursor)
    auto indexValue = comJson->GetValue(INDEX_KEY);
    if (!indexValue || !indexValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is missing");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    double indexDouble = comJson->GetDouble(INDEX_KEY, 0);
    if (indexDouble != static_cast<int>(indexDouble)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: start index is not integer");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    outIndex = comJson->GetInt(INDEX_KEY, 0);
    if (outIndex < 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: index is invalid value");
        return static_cast<int>(WebCommandResult::JSON_INVALID_INDEX);
    }
    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::BuildInputMethodAction(
    const std::unique_ptr<JsonValue>& comJson,
    const std::string& eventTypeStr,
    std::shared_ptr<NWebCommandActionImpl>& outCommandAction)
{
    std::string xpathStr;
    std::string alignStr;
    int32_t durationInt = 0;
    int32_t offsetInt = 0;
    std::string contentStr;
    int32_t indexInt = 0;
    int32_t startIndexInt = 0;
    int32_t finishIndexInt = 0;
    int32_t noNeedKeyboardInt = 0;

    int validationResult = WEB_COMMAND_BUILD_SUCCESS;

    if (eventTypeStr == "inputInsert") {
        validationResult = ValidateInputInsertParameters(comJson, contentStr, indexInt);
    } else if (eventTypeStr == "inputModify") {
        validationResult = ValidateInputModifyParameters(comJson, contentStr);
    } else if (eventTypeStr == "inputSelect") {
        validationResult = ValidateInputSelectParameters(comJson, startIndexInt, finishIndexInt);
    } else if (eventTypeStr == "inputFocus") {
        validationResult = ValidateInputFocusParameters(comJson, xpathStr, noNeedKeyboardInt);
    } else if (eventTypeStr == "inputSetCursor") {
        validationResult = ValidateInputSetCursorParameters(comJson, indexInt);
    }

    if (validationResult != WEB_COMMAND_BUILD_SUCCESS) {
        return validationResult;
    }

    TAG_LOGD(AceLogTag::ACE_WEB, "Command: is ready eventTypeStr = %{public}s ,xpathStr = %{public}s, "
        "indexInt = %{public}d, contentStr = %{public}s, startIndexInt = %{public}d, finishIndexInt = %{public}d,"
        "noNeedKeyboardInt = %{public}d", eventTypeStr.c_str(), xpathStr.c_str(), indexInt, contentStr.c_str(),
        startIndexInt, finishIndexInt, noNeedKeyboardInt);

    if (eventTypeStr == "inputInsert") {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, indexInt, contentStr, offsetInt);
    } else if (eventTypeStr == "inputModify") {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, durationInt, contentStr, offsetInt);
    } else if (eventTypeStr == "inputSelect") {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, startIndexInt, alignStr, finishIndexInt);
    } else if (eventTypeStr == "inputFocus") {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, noNeedKeyboardInt, alignStr, offsetInt);
    } else if (eventTypeStr == "inputSetCursor") {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, indexInt, alignStr, offsetInt);
    } else {
        outCommandAction = std::make_shared<NWebCommandActionImpl>(
            eventTypeStr, xpathStr, durationInt, alignStr, offsetInt);
    }

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

int WebCommandWrapper::ValidateTapParameters(
    const std::unique_ptr<JsonValue>& comJson,
    double& outX,
    double& outY,
    int32_t& outDuration,
    int32_t& outTapCount)
{
    auto xValue = comJson->GetValue("x");
    if (!xValue || !xValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: tap x is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X);
    }
    outX = xValue->GetDouble();

    auto yValue = comJson->GetValue("y");
    if (!yValue || !yValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: tap y is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y);
    }
    outY = yValue->GetDouble();

    auto durationValue = comJson->GetValue("duration");
    outDuration = (durationValue && durationValue->IsNumber()) ? durationValue->GetInt() : 0;

    auto tapCountValue = comJson->GetValue("tapCount");
    outTapCount = (tapCountValue && tapCountValue->IsNumber()) ? tapCountValue->GetInt() : 0;

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateScrollGestureParameters(
    const std::unique_ptr<JsonValue>& comJson,
    double& outX,
    double& outY,
    double& outXDistance,
    double& outYDistance,
    int32_t& outSpeed)
{
    auto xValue = comJson->GetValue("x");
    if (!xValue || !xValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: scrollGesture x is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X);
    }
    outX = xValue->GetDouble();

    auto yValue = comJson->GetValue("y");
    if (!yValue || !yValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: scrollGesture y is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y);
    }
    outY = yValue->GetDouble();

    auto xDistValue = comJson->GetValue("xDistance");
    if (!xDistValue || !xDistValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: scrollGesture xDistance is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_DISTANCE);
    }
    outXDistance = xDistValue->GetDouble();

    auto yDistValue = comJson->GetValue("yDistance");
    if (!yDistValue || !yDistValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: scrollGesture yDistance is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_DISTANCE);
    }
    outYDistance = yDistValue->GetDouble();

    auto speedValue = comJson->GetValue("speed");
    outSpeed = (speedValue && speedValue->IsNumber()) ? speedValue->GetInt() : 0;

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidatePinchParameters(
    const std::unique_ptr<JsonValue>& comJson,
    double& outX,
    double& outY,
    double& outScaleFactor,
    int32_t& outSpeed)
{
    auto xValue = comJson->GetValue("x");
    if (!xValue || !xValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: pinch x is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X);
    }
    outX = xValue->GetDouble();

    auto yValue = comJson->GetValue("y");
    if (!yValue || !yValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: pinch y is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y);
    }
    outY = yValue->GetDouble();

    auto scaleValue = comJson->GetValue("scale");
    if (!scaleValue || !scaleValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: pinch scale is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_SCALE);
    }
    outScaleFactor = scaleValue->GetDouble();
    if (outScaleFactor <= 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: pinch scale must be greater than 0");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_SCALE);
    }

    auto speedValue = comJson->GetValue("speed");
    outSpeed = (speedValue && speedValue->IsNumber()) ? speedValue->GetInt() : 0;

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::ValidateLongPressParameters(
    const std::unique_ptr<JsonValue>& comJson,
    double& outX,
    double& outY)
{
    auto xValue = comJson->GetValue("x");
    if (!xValue || !xValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: longPress x is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_X);
    }
    outX = xValue->GetDouble();

    auto yValue = comJson->GetValue("y");
    if (!yValue || !yValue->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: longPress y is missing or not number type");
        return static_cast<int>(WebCommandResult::JSON_INVALID_GESTURE_Y);
    }
    outY = yValue->GetDouble();

    return WEB_COMMAND_BUILD_SUCCESS;
}

int WebCommandWrapper::BuildGestureActionInfo(
    const std::unique_ptr<JsonValue>& comJson,
    const std::string& eventTypeStr,
    std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo)
{
    if (eventTypeStr == "tap") {
        double x;
        double y;
        int32_t duration;
        int32_t tapCount;
        int result = ValidateTapParameters(comJson, x, y, duration, tapCount);
        if (result != WEB_COMMAND_BUILD_SUCCESS) {
            return result;
        }
        outActionInfo = NWebCommandActionInfoImpl::CreateGestureInfo(
            eventTypeStr, x, y, 0, 0, 1.0f, duration, tapCount, 0);
    } else if (eventTypeStr == "scrollGesture") {
        double x;
        double y;
        double xDistance;
        double yDistance;
        int32_t speed;
        int result = ValidateScrollGestureParameters(comJson, x, y, xDistance, yDistance, speed);
        if (result != WEB_COMMAND_BUILD_SUCCESS) {
            return result;
        }
        outActionInfo = NWebCommandActionInfoImpl::CreateGestureInfo(
            eventTypeStr, x, y, xDistance, yDistance, 1.0f, 0, 1, speed);
    } else if (eventTypeStr == "pinch") {
        double x;
        double y;
        double scaleFactor;
        int32_t speed;
        int result = ValidatePinchParameters(comJson, x, y, scaleFactor, speed);
        if (result != WEB_COMMAND_BUILD_SUCCESS) {
            return result;
        }
        outActionInfo = NWebCommandActionInfoImpl::CreateGestureInfo(
            eventTypeStr, x, y, 0, 0, scaleFactor, 0, 1, speed);
    } else if (eventTypeStr == "longPress") {
        double x;
        double y;
        int result = ValidateLongPressParameters(comJson, x, y);
        if (result != WEB_COMMAND_BUILD_SUCCESS) {
            return result;
        }
        outActionInfo = NWebCommandActionInfoImpl::CreateGestureInfo(
            eventTypeStr, x, y, 0, 0, 1.0f, 0, 1, 0);
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "CommandError: unknown gesture type %{public}s", eventTypeStr.c_str());
        return static_cast<int>(WebCommandResult::JSON_INVALID_EVENT_TYPE);
    }
    return WEB_COMMAND_BUILD_SUCCESS;
}

} // namespace Ace
} // namespace OHOS

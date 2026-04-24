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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_COMMAND_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_COMMAND_WRAPPER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/components/web/resource/web_delegate.h"
#include "nweb_command_action_info.h"

namespace OHOS {
namespace Ace {

class JsonValue;

// Return code for JSON parsing/building success (distinct from WebCommandResult::SUCCESS)
const int WEB_COMMAND_BUILD_SUCCESS = 0;

/**
 * @brief Enum for parsed event types used in command routing.
 */
enum class WebCommandEventType {
    UNKNOWN = 0,
    CLICK,
    SCROLL,
    INPUT_DATE,
    INPUT_DATETIME_LOCAL,
    INPUT_MONTH,
    INPUT_TIME,
    INPUT_WEEK,
    SELECT,
    EVENT_TYPE_SCROLL_GESTURE,
    EVENT_TYPE_TAP_GESTURE,
    EVENT_TYPE_PINCH_GESTURE,
    EVENT_TYPE_LONG_PRESS,
};

/**
 * @brief Check if a WebCommandEventType is any input subtype.
 */
inline bool IsInputEventType(WebCommandEventType type)
{
    return type == WebCommandEventType::INPUT_DATE ||
           type == WebCommandEventType::INPUT_DATETIME_LOCAL ||
           type == WebCommandEventType::INPUT_MONTH ||
           type == WebCommandEventType::INPUT_TIME ||
           type == WebCommandEventType::INPUT_WEEK;
}

/**
 * @class WebCommandWrapper
 * @brief Wrapper class for building and executing web commands
 *
 * This class encapsulates the logic for creating command action objects
 * from JSON input, validating parameters, and supporting extensible command types.
 */
class WebCommandWrapper {
public:
    /**
     * @brief Parse event type string to WebCommandEventType enum
     * @param eventTypeStr The event type string (e.g., "click", "input-date", "select")
     * @return WebCommandEventType enum value
     */
    static WebCommandEventType ParseEventType(const std::string& eventTypeStr);

    /**
     * @brief Build input action info from JSON for input-* event types
     * @param comJson The JSON object containing command parameters
     * @param eventTypeStr The event type string (e.g., "input-date")
     * @param outActionInfo Output parameter for the created NWebCommandActionInfo
     * @return int Result code (0 for success, error code otherwise)
     */
    static int BuildInputActionInfo(
        const std::unique_ptr<JsonValue>& comJson,
        const std::string& eventTypeStr,
        std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo);

    /**
     * @brief Build select action info from JSON for select event type
     * @param comJson The JSON object containing command parameters
     * @param eventTypeStr The event type string ("select")
     * @param outActionInfo Output parameter for the created NWebCommandActionInfo
     * @return int Result code (0 for success, error code otherwise)
     */
    static int BuildSelectActionInfo(
        const std::unique_ptr<JsonValue>& comJson,
        const std::string& eventTypeStr,
        std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo);

    /**
     * @brief Build click/scroll command action from JSON
     * @param comJson The JSON object containing command parameters
     * @param eventTypeStr The event type string ("click" or "scroll")
     * @param outCommandAction Output parameter for the created command action
     * @return int Result code (0 for success, error code otherwise)
     */
    static int BuildClickScrollAction(
        const std::unique_ptr<JsonValue>& comJson,
        const std::string& eventTypeStr,
        std::shared_ptr<NWebCommandActionImpl>& outCommandAction);

    /**
     * @brief Validate align parameter value
     * @param alignStr The align string to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidAlign(const std::string& alignStr);

    static int BuildGestureActionInfo(
        const std::unique_ptr<JsonValue>& comJson,
        const std::string& eventTypeStr,
        std::shared_ptr<OHOS::NWeb::NWebCommandActionInfo>& outActionInfo);

    static bool IsGestureCommandType(WebCommandEventType eventType)
    {
        return eventType == WebCommandEventType::EVENT_TYPE_TAP_GESTURE ||
               eventType == WebCommandEventType::EVENT_TYPE_SCROLL_GESTURE ||
               eventType == WebCommandEventType::EVENT_TYPE_PINCH_GESTURE ||
               eventType == WebCommandEventType::EVENT_TYPE_LONG_PRESS;
    }

    static int ValidateTapParameters(
        const std::unique_ptr<JsonValue>& comJson,
        double& outX,
        double& outY,
        int32_t& outDuration,
        int32_t& outTapCount);

    static int ValidateScrollGestureParameters(
        const std::unique_ptr<JsonValue>& comJson,
        double& outX,
        double& outY,
        double& outXDistance,
        double& outYDistance,
        int32_t& outSpeed);

    static int ValidatePinchParameters(
        const std::unique_ptr<JsonValue>& comJson,
        double& outX,
        double& outY,
        double& outScaleFactor,
        int32_t& outSpeed);

    static int ValidateLongPressParameters(
        const std::unique_ptr<JsonValue>& comJson,
        double& outX,
        double& outY);
private:
    static const char* const EVENT_TYPE_KEY;
    static const char* const XPATH_KEY;
    static const char* const VALUE_KEY;
    static const char* const INDEX_KEY;
    static const char* const DURATION_KEY;
    static const char* const ALIGN_KEY;
    static const char* const OFFSET_KEY;

    static int ValidateClickParameters(
        const std::unique_ptr<JsonValue>& comJson,
        std::string& outXPath);

    static int ValidateScrollParameters(
        const std::unique_ptr<JsonValue>& comJson,
        int32_t& outDuration,
        std::string& outAlign,
        int32_t& outOffset,
        std::string& outXPath);
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_COMMAND_WRAPPER_H

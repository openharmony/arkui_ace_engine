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

#include "core/components/web/resource/web_delegate.h"

namespace OHOS {
namespace Ace {

class JsonValue;

// Return code for JSON parsing/building success (distinct from WebCommandResult::SUCCESS)
const int WEB_COMMAND_BUILD_SUCCESS = 0;

/**
 * @class WebCommandWrapper
 * @brief Wrapper class for building and executing web commands
 *
 * This class encapsulates the logic for creating NWebCommandActionImpl objects
 * from JSON input, validating parameters, and supporting extensible command types.
 */
class WebCommandWrapper {
public:
    /**
     * @brief Build a command action from JSON input
     * @param comJson The JSON object containing command parameters
     * @param outCommandAction Output parameter for the created command action
     * @return int Result code (0 for success, error code otherwise)
     */
    static int BuildCommandFromJson(
        const std::unique_ptr<JsonValue>& comJson,
        std::shared_ptr<NWebCommandActionImpl>& outCommandAction);

    /**
     * @brief Validate event type parameter
     * @param eventTypeStr The event type string to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidEventType(const std::string& eventTypeStr);

    /**
     * @brief Validate click-specific parameters
     * @param comJson The JSON object containing command parameters
     * @param outXPath Output parameter for XPath value
     * @return int Result code (0 for success, error code otherwise)
     */
    static int ValidateClickParameters(
        const std::unique_ptr<JsonValue>& comJson,
        std::string& outXPath);

    /**
     * @brief Validate scroll-specific parameters
     * @param comJson The JSON object containing command parameters
     * @param outDuration Output parameter for duration value
     * @param outAlign Output parameter for align string
     * @param outOffset Output parameter for offset value
     * @param outXPath Output parameter for XPath value
     * @return int Result code (0 for success, error code otherwise)
     */
    static int ValidateScrollParameters(
        const std::unique_ptr<JsonValue>& comJson,
        int32_t& outDuration,
        std::string& outAlign,
        int32_t& outOffset,
        std::string& outXPath);

    /**
     * @brief Validate align parameter value
     * @param alignStr The align string to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidAlign(const std::string& alignStr);

private:
    static const char* const EVENT_TYPE_KEY;
    static const char* const XPATH_KEY;
    static const char* const DURATION_KEY;
    static const char* const ALIGN_KEY;
    static const char* const OFFSET_KEY;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_COMMAND_WRAPPER_H

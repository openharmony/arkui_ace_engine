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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_RELAXED_INTERACTION_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_RELAXED_INTERACTION_TYPES_H

#include <memory>
#include <string>
#include <vector>

namespace OHOS::Ace::NG {

inline constexpr char FALLBACK_CMD_KEY[] = "fallback_cmd";
inline constexpr char CMD_KEY[] = "cmd";
inline constexpr char TYPE_KEY[] = "type";

inline constexpr char BACKPRESS[] = "backpress";
inline constexpr char CONTENT_SWITCH[] = "content_switch";
inline constexpr char FALLBACK[] = "fallback";
inline constexpr char CLICK[] = "click";
inline constexpr char SCROLL[] = "scroll";

// Return status of ExecuteNextStep.
enum class ExecutionState {
    NONE,
    RUNNING,
    SUCCESS,
    FAILED,
};

// Executor execution result
enum class ExecutorResult {
    SUCCESS,
    FAILED,
    PENDING,
};

// Execute mode
enum class ExecuteMode {
    AUTO = 0,
    SIMULATING,
    TARGET,
};

// Return result of ProcessCommand.
enum class ProcessResult {
    SUCCESS,
    PARSE_ERROR,
    VALIDATION_ERROR,
    NO_VALID_CMD,
};

struct Coordinates {
    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
};

enum class RelaxedScrollDirection { FORWARD, BACKWARD, LEFT, RIGHT, DOWN, UP };

struct ScrollActionInfo {
    RelaxedScrollDirection direction;
    float distance;
    Coordinates coordinates;
};

struct Command {
    std::string type;
    ExecuteMode mode;
    ScrollActionInfo actionInfo;
    bool isY2Set = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RELAXED_INTERACTION_RELAXED_INTERACTION_TYPES_H

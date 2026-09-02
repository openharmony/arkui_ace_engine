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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H

#include <cstdint>
#include <functional>
#include <string>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class UINode;

// Scroll containers supported by scroll placeholder frame scheduling.
enum class ScrollPlaceholderComponentType : int32_t {
    LIST = 0,
    GRID = 1,
    WATER_FLOW = 2,
};

// Prediction result decided before the real item builder runs:
// - BUILD_REAL_NOW: estimated cost fits the remaining frame budget, caller builds synchronously.
// - USE_PLACEHOLDER: budget insufficient, caller shows a placeholder and defers the real build
//   to the framed real-build queue flushed by the pipeline.
enum class ScrollPlaceholderDecision : int32_t {
    BUILD_REAL_NOW = 0,
    USE_PLACEHOLDER = 1,
};

// Flush order of pending real-build tasks: visible items first, then near-visible, then cache only.
enum class ScrollPlaceholderRealBuildPriority : int32_t {
    VISIBLE = 0,
    NEAR_VISIBLE = 1,
    CACHE_ONLY = 2,
};

// Reason codes for cancelled/dropped scheduled work, exposed through diagnostics counters.
enum class ScrollPlaceholderCancelReason : int32_t {
    HOST_RESET = 0,
    HOST_DESTROYED = 1,
    OUT_OF_RANGE = 2,
    RE_REGISTER = 3,
    DATA_CHANGE = 4,
    UNREGISTER = 5,
    PIPELINE_DESTROYED = 6,
    EXECUTION_FAILED = 7,
};

// Restricted placeholder builder handle. The real ArkTS builder bridge and the compiler
// capability check are delivered by the compiler-contract step; until then the handle stays an
// internal registration entry keyed for cost prediction.
using ScrollPlaceholderBuilder = std::function<RefPtr<UINode>()>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SCROLL_PLACEHOLDER_SCROLL_PLACEHOLDER_TYPES_H

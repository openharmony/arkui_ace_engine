/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_SCROLLABLE_PROPERTIES_H

#include <functional>
#include <optional>

#include "base/geometry/dimension.h"

namespace OHOS::Ace {
constexpr float DEFAULT_SCROLL_TO_MASS = 1.0f;
constexpr float DEFAULT_SCROLL_TO_STIFFNESS = 227.0f;
constexpr float DEFAULT_SCROLL_TO_DAMPING = 33.0f;
constexpr float DEFAULT_SCROLL_TO_VELOCITY = 7.0f;

enum class ScrollState {
    IDLE = 0,
    SCROLL,
    FLING,
};

enum class NestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST,
    PARENT_FIRST,
    PARALLEL,
};

enum class ScrollSnapAlign {
    NONE = 0,
    START,
    CENTER,
    END,
};

struct ScrollInfo {
    Dimension dx;
    Dimension dy;

    bool operator==(const ScrollInfo& scrollInfo) const
    {
        return dx == scrollInfo.dx && dy == scrollInfo.dy;
    }
};

struct ScrollFrameInfo {
    Dimension offset;
    ScrollState state;

    bool operator==(const ScrollFrameInfo& scrollInfo) const
    {
        return offset == scrollInfo.offset && state == scrollInfo.state;
    }
};

struct ScrollFrameResult {
    Dimension offset;

    bool operator==(const ScrollFrameResult& scrollRes) const
    {
        return offset == scrollRes.offset;
    }
};

struct NestedScrollOptions {
    NestedScrollMode forward;
    NestedScrollMode backward;

    bool NeedParent() const
    {
        return forward != NestedScrollMode::SELF_ONLY || backward != NestedScrollMode::SELF_ONLY;
    }
};

constexpr int32_t SCROLL_FROM_NONE = 0;
constexpr int32_t SCROLL_FROM_UPDATE = 1;
constexpr int32_t SCROLL_FROM_ANIMATION = 2;
constexpr int32_t SCROLL_FROM_JUMP = 3;
constexpr int32_t SCROLL_FROM_ANIMATION_SPRING = 4;
constexpr int32_t SCROLL_FROM_CHILD = 5;
constexpr int32_t SCROLL_FROM_BAR = 6;
constexpr int32_t SCROLL_FROM_FOCUS_JUMP = 7;
constexpr int32_t SCROLL_FROM_ROTATE = 8;
constexpr int32_t SCROLL_FROM_INDEXER = 9;
constexpr int32_t SCROLL_FROM_START = 10; // from drag start
constexpr int32_t SCROLL_FROM_AXIS = 11;
constexpr int32_t SCROLL_FROM_ANIMATION_CONTROLLER = 12;
constexpr int32_t SCROLL_FROM_BAR_FLING = 13;

using OnScrollEvent = std::function<void(Dimension, ScrollState)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollFrameBeginEvent = std::function<ScrollFrameResult(Dimension, ScrollState)>;
using OnScrollStartEvent = std::function<void()>;
using OnScrollStopEvent = std::function<void()>;
using OnReachEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t, int32_t)>;

using ScrollPositionCallback = std::function<bool(double, int32_t source)>;
using ScrollEndCallback = std::function<void()>;
using CalePredictSnapOffsetCallback = std::function<std::optional<float>(float delta)>;
using StartScrollSnapMotionCallback = std::function<void(float scrollSnapDelta, float scrollSnapVelocity)>;
} // namespace OHOS::Ace

#endif

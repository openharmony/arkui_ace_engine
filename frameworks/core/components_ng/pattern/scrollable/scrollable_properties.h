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
#include "base/geometry/dimension.h"

namespace OHOS::Ace {
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

using OnScrollEvent = std::function<void(Dimension, ScrollState)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollFrameBeginEvent = std::function<ScrollFrameResult(Dimension, ScrollState)>;
using OnScrollStartEvent = std::function<void()>;
using OnScrollStopEvent = std::function<void()>;
using OnReachEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t)>;
} // namespace OHOS::Ace

#endif

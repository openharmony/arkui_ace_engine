/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_BASE_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scrollable/scroller_observer_manager.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

constexpr uint32_t POSITION_MIDDLE = 0;
constexpr uint32_t POSITION_TOP = 1 << 0;
constexpr uint32_t POSITION_BOTTOM = 1 << 1;

enum class ScrollEvent : size_t {
    SCROLL_TOP = 0,
    SCROLL_BOTTOM,
    SCROLL_TOUCHUP,
    SCROLL_END,
    SCROLL_POSITION,
    SCROLL_EDGE,
    SCROLL_LEFT,
    SCROLL_RIGHT,
    UNKNOWN,
};

enum class ScrollEdgeType : size_t {
    SCROLL_TOP = 0,
    SCROLL_BOTTOM,
    SCROLL_LEFT,
    SCROLL_RIGHT,
    SCROLL_NONE,
};

enum class ScrollAlign {
    START = 0,
    CENTER,
    END,
    AUTO,
    NONE,
};

struct ListItemGroupIndex {
    int32_t index = -1;
    int32_t area = -1;
    int32_t indexInGroup = -1;
};

using OnFinishFunc = std::function<void()>;
class ACE_EXPORT ScrollControllerBase : public AceType {
    DECLARE_ACE_TYPE(ScrollControllerBase, AceType);

public:
    ScrollControllerBase() = default;
    ~ScrollControllerBase() override = default;

    virtual void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::NONE,
        std::optional<float> extraOffset = std::nullopt)
    {}

    virtual void JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth = false,
        ScrollAlign align = ScrollAlign::NONE, int32_t source = 3) {} // 3 is SCROLL_FROM_JUMP

    virtual Axis GetScrollDirection() const
    {
        return Axis::NONE;
    }

    virtual bool AnimateTo(
        const Dimension& position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false)
    {
        return true;
    }
    virtual void ScrollBy(double pixelX, double pixelY, bool smooth) {}
    virtual void ScrollToEdge(ScrollEdgeType scrollEdgeType, float velocity) {}
    virtual void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) {}
    virtual void Fling(double flingVelocity) {}
    virtual void ScrollPage(bool reverse, bool smooth) {}
    virtual Offset GetCurrentOffset() const
    {
        return Offset();
    }
    virtual bool IsAtEnd() const
    {
        return true;
    }
    virtual Rect GetItemRect(int32_t index) const
    {
        return Rect();
    }

    virtual int32_t GetItemIndex(double x, double y) const
    {
        return -1;
    }

    virtual Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const
    {
        return Rect();
    }

    virtual ListItemGroupIndex GetItemIndexInGroup(double x, double y) const
    {
        return ListItemGroupIndex();
    }

    virtual void CloseAllSwipeActions(OnFinishFunc&& onFinishCallback) {}

    virtual void SetObserver(const ScrollerObserver& observer) {}

    virtual void SetObserverManager(const RefPtr<ScrollerObserverManager>& mgr)
    {
        observerMgr_ = mgr;
    }

    virtual RefPtr<ScrollerObserverManager> GetObserverManager() const
    {
        return observerMgr_;
    }

    virtual void StopAnimate() {}

protected:
    RefPtr<ScrollerObserverManager> observerMgr_ = nullptr;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_SCROLL_CONTROLLER_BASE_H

/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace {
constexpr float DEFAULT_SCROLL_TO_MASS = 1.0f;
constexpr float DEFAULT_SCROLL_TO_STIFFNESS = 227.0f;
constexpr float DEFAULT_SCROLL_TO_DAMPING = 33.0f;
constexpr float DEFAULT_SCROLL_TO_VELOCITY = 7.0f;
// for add item and scrollEdge(Edge.Bottom) in one layout
constexpr int32_t LAST_ITEM = -1;

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

enum class ScrollPagingStatus {
    // no enablePaging set
    NONE = 0,
    // enablePaging is false
    INVALID,
    // enablePaging is true
    VALID,
};

// use in dumpInfo, excluding events truggered per frame,
// such as onScroll, onScrollFrameBegin, onWillScroll, onDidScroll
enum class ScrollableEventType {
    ON_SCROLL_START = 0,
    ON_SCROLL_STOP,
    ON_SCROLL_EDGE,
    ON_REACH_START,
    ON_REACH_END,
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

struct ScrollSnapOptions {
    int32_t snapAlign;
    int32_t enableSnapToStart;
    int32_t enableSnapToEnd;
    std::vector<Dimension> paginationParams;
};

struct NestedScrollOptions {
    NestedScrollMode forward;
    NestedScrollMode backward;

    bool NeedParent() const
    {
        return forward != NestedScrollMode::SELF_ONLY || backward != NestedScrollMode::SELF_ONLY;
    }

    bool NeedParent(bool forward) const
    {
        return forward ? this->forward != NestedScrollMode::SELF_ONLY : backward != NestedScrollMode::SELF_ONLY;
    }

    bool operator==(const NestedScrollOptions& other) const
    {
        return forward == other.forward && backward == other.backward;
    }

    bool operator!=(const NestedScrollOptions& other) const
    {
        return !(*this == other);
    }

    std::string ToString() const
    {
        return "NestedScrollOptions forward: " + std::to_string(static_cast<int32_t>(forward)) +
               ", backward: " + std::to_string(static_cast<int32_t>(backward));
    }

    std::string GetNestedScrollModeStr(NestedScrollMode mode) const
    {
        switch (mode) {
            case NestedScrollMode::SELF_ONLY:
                return "NestedScrollMode.SELF_ONLY";
            case NestedScrollMode::SELF_FIRST:
                return "NestedScrollMode.SELF_FIRST";
            case NestedScrollMode::PARENT_FIRST:
                return "NestedScrollMode.PARENT_FIRST";
            case NestedScrollMode::PARALLEL:
                return "NestedScrollMode.PARALLEL";
            default:
                return "";
        }
    }
};

struct NestedScrollOptionsExt {
    NestedScrollMode scrollUp;
    NestedScrollMode scrollDown;
    NestedScrollMode scrollLeft;
    NestedScrollMode scrollRight;

    std::string ToString() const
    {
        return "NestedScrollOptionsExt scrollUp: " + std::to_string(static_cast<int32_t>(scrollUp)) +
               ", scrollDown: " + std::to_string(static_cast<int32_t>(scrollDown)) +
               ", scrollLeft: " + std::to_string(static_cast<int32_t>(scrollLeft)) +
               ", scrollRight: " + std::to_string(static_cast<int32_t>(scrollRight));
    }
};

struct ListItemIndex {
    int32_t index = -1;
    int32_t area = -1;
    int32_t indexInGroup = -1;
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

inline std::string GetSourceStr(int32_t scrollSource)
{
    switch (scrollSource) {
        case SCROLL_FROM_NONE:
            return "SCROLL_FROM_NONE";
        case SCROLL_FROM_UPDATE:
            return "SCROLL_FROM_UPDATE";
        case SCROLL_FROM_ANIMATION:
            return "SCROLL_FROM_ANIMATION";
        case SCROLL_FROM_JUMP:
            return "SCROLL_FROM_JUMP";
        case SCROLL_FROM_ANIMATION_SPRING:
            return "SCROLL_FROM_ANIMATION_SPRING";
        case SCROLL_FROM_CHILD:
            return "SCROLL_FROM_CHILD";
        case SCROLL_FROM_BAR:
            return "SCROLL_FROM_BAR";
        case SCROLL_FROM_FOCUS_JUMP:
            return "SCROLL_FROM_FOCUS_JUMP";
        case SCROLL_FROM_ROTATE:
            return "SCROLL_FROM_ROTATE";
        case SCROLL_FROM_INDEXER:
            return "SCROLL_FROM_INDEXER";
        case SCROLL_FROM_START:
            return "SCROLL_FROM_START";
        case SCROLL_FROM_AXIS:
            return "SCROLL_FROM_AXIS";
        case SCROLL_FROM_ANIMATION_CONTROLLER:
            return "SCROLL_FROM_ANIMATION_CONTROLLER";
        case SCROLL_FROM_BAR_FLING:
            return "SCROLL_FROM_BAR_FLING";
        default:
            return "";
    }
}

struct ScrollableEventsFiredInfo {
    uint64_t eventFiredTime_ = 0;
    ScrollableEventType eventType_;
    int32_t scrollSource_ = 0;

    std::string ToString() const
    {
        return std::string("event type: ")
            .append(GetEventStr())
            .append(" fired in ")
            .append(std::to_string(eventFiredTime_))
            .append(", source is ")
            .append(GetSourceStr(scrollSource_));
    }

    std::string GetEventStr() const
    {
        switch (eventType_) {
            case ScrollableEventType::ON_SCROLL_START:
                return "onScrollStart";
            case ScrollableEventType::ON_SCROLL_STOP:
                return "onScrollStop";
            case ScrollableEventType::ON_SCROLL_EDGE:
                return "onScrollEdge";
            case ScrollableEventType::ON_REACH_START:
                return "onReachStart";
            case ScrollableEventType::ON_REACH_END:
                return "onReachEnd";
            default:
                return "";
        }
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("event type", GetEventStr().c_str());
        json->Put("fired in", std::to_string(eventFiredTime_).c_str());
        json->Put("source is", GetSourceStr(scrollSource_).c_str());
    }
};

struct ScrollableFrameInfo {
    uint64_t scrollStateTime_ = 0;
    int32_t scrollState_ = 0;
    bool canOverScroll_ = false;
    uint32_t canOverScrollInfo_ = 0;

    std::string ToString() const
    {
        return std::string("scroll from: ")
            .append(GetSourceStr(scrollState_))
            .append(" canOverScroll: ")
            .append(std::to_string(canOverScroll_))
            .append(" isScrollableSpringEffect: ")
            .append((canOverScrollInfo_ >> 4) & 1 ? "true" : "false")
            .append(" isScrollable: ")
            .append((canOverScrollInfo_ >> 3) & 1 ? "true" : "false")
            .append(" scrollableIdle: ")
            .append((canOverScrollInfo_ >> 2) & 1 ? "true" : "false")
            .append(" animateOverScroll: ")
            .append((canOverScrollInfo_ >> 1) & 1 ? "true" : "false")
            .append(" animateCanOverScroll: ")
            .append(canOverScrollInfo_ & 1 ? "true" : "false")
            .append(" fired in ")
            .append(std::to_string(scrollStateTime_));
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("scroll from", GetSourceStr(scrollState_).c_str());
        json->Put("canOverScroll", std::to_string(canOverScroll_).c_str());
        json->Put("isScrollableSpringEffect",
            (canOverScrollInfo_ >> 4) & 1 ? "true" : "false");                         // 4: isScrollableSpringEffect
        json->Put("isScrollable", (canOverScrollInfo_ >> 3) & 1 ? "true" : "false");   // 3: isScrollable
        json->Put("scrollableIdle", (canOverScrollInfo_ >> 2) & 1 ? "true" : "false"); // 2: scrollableIdle
        json->Put("animateOverScroll", (canOverScrollInfo_ >> 1) & 1 ? "true" : "false");
        json->Put("animateCanOverScroll", canOverScrollInfo_ & 1 ? "true" : "false");
        json->Put("scroll from", std::to_string(scrollStateTime_).c_str());
    }
};

struct ScrollLayoutInfo {
    uint64_t changedTime_ = 0;
    float scrollableDistance_ = 0;
    NG::SizeF scrollSize_;
    NG::SizeF viewPort_;
    NG::SizeF childSize_;

    std::string ToString() const
    {
        return std::string("scrollableDistance changed, scrollableDistance: ")
            .append(std::to_string(scrollableDistance_))
            .append(" scrollSize: ")
            .append(scrollSize_.ToString())
            .append(" viewPort: ")
            .append(viewPort_.ToString())
            .append(" childSize: ")
            .append(childSize_.ToString())
            .append(" fired in ")
            .append(std::to_string(changedTime_));
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("scrollableDistance changed, scrollableDistance", std::to_string(scrollableDistance_).c_str());
        json->Put("scrollSize", scrollSize_.ToString().c_str());
        json->Put("viewPort", viewPort_.ToString().c_str());
        json->Put("childSize", childSize_.ToString().c_str());
        json->Put("fired in", std::to_string(changedTime_).c_str());
    }
};

struct ScrollMeasureInfo {
    uint64_t changedTime_ = 0;
    std::optional<NG::LayoutConstraintF> parentConstraint_;
    std::optional<NG::LayoutConstraintF> childConstraint_;
    NG::SizeF selfSize_;
    NG::SizeF childSize_;

    std::string ToString() const
    {
        return std::string("Scroll Measure changed, parentConstraint: ")
            .append(parentConstraint_->ToString())
            .append(" childConstraint: ")
            .append(childConstraint_->ToString())
            .append(" selfSize: ")
            .append(selfSize_.ToString())
            .append(" childSize: ")
            .append(childSize_.ToString())
            .append(" fired in ")
            .append(std::to_string(changedTime_));
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("Scroll Measure changed, parentConstraint", parentConstraint_->ToString().c_str());
        json->Put("childConstraint", childConstraint_->ToString().c_str());
        json->Put("selfSize", selfSize_.ToString().c_str());
        json->Put("childSize", childSize_.ToString().c_str());
        json->Put("fired in", std::to_string(changedTime_).c_str());
    }
};

struct InnerScrollBarLayoutInfo {
    uint64_t layoutTime_ = 0;
    Size viewPortSize_;
    Offset lastOffset_;
    double estimatedHeight_ = 0.0;
    double outBoundary_ = 0.0;
    Rect activeRect_;

    std::string ToString() const
    {
        return std::string("inner scrollBar layout, viewPortSize:")
            .append(viewPortSize_.ToString())
            .append(" lastOffset: ")
            .append(lastOffset_.ToString())
            .append(" estimatedHeight: ")
            .append(std::to_string(estimatedHeight_))
            .append(" outBoundary: ")
            .append(std::to_string(outBoundary_))
            .append(" activeRect: ")
            .append(activeRect_.ToString())
            .append(" fired in ")
            .append(std::to_string(layoutTime_));
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("inner scrollBar layout, viewPortSize", viewPortSize_.ToString().c_str());
        json->Put("lastOffset", lastOffset_.ToString().c_str());
        json->Put("estimatedHeight", estimatedHeight_);
        json->Put("outBoundary", std::to_string(outBoundary_).c_str());
        json->Put("activeRect", activeRect_.ToString().c_str());
        json->Put("fired in", std::to_string(layoutTime_).c_str());
    }
};

struct OuterScrollBarLayoutInfo {
    uint64_t layoutTime_ = 0;
    float currentOffset_ = 0.f;
    float scrollableNodeOffset_ = 0.f;

    std::string ToString() const
    {
        return std::string("outer scrollBar layout, currentOffset:")
            .append(std::to_string(currentOffset_))
            .append(" scrollableNodeOffset: ")
            .append(std::to_string(scrollableNodeOffset_))
            .append(" fired in ")
            .append(std::to_string(layoutTime_));
    }

    void ToJson(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("outer scrollBar layout, currentOffset", std::to_string(currentOffset_).c_str());
        json->Put("scrollableNodeOffset", std::to_string(scrollableNodeOffset_).c_str());
        json->Put("fired in", std::to_string(layoutTime_).c_str());
    }
};

enum class ScrollSource {
    DRAG = 0,           // constexpr int32_t SCROLL_FROM_UPDATE = 1;
    FLING,              // constexpr int32_t SCROLL_FROM_ANIMATION = 2;
    EDGE_EFFECT,        // constexpr int32_t SCROLL_FROM_ANIMATION_SPRING = 4;
    OTHER_USER_INPUT,   // constexpr int32_t SCROLL_FROM_AXIS = 11;
    SCROLL_BAR,         // constexpr int32_t SCROLL_FROM_BAR = 6;
    SCROLL_BAR_FLING,   // constexpr int32_t SCROLL_FROM_BAR_FLING = 13;
    SCROLLER,           // constexpr int32_t SCROLL_FROM_JUMP = 3;
    SCROLLER_ANIMATION, // constexpr int32_t SCROLL_FROM_ANIMATION_CONTROLLER = 12;
};

// app tail animation
constexpr char TRAILING_ANIMATION[] = "TRAILING_ANIMATION ";

// scroller animation, such as scrollTo, scrollPage
constexpr char SCROLLER_ANIMATION[] = "CUSTOM_ANIMATOR_SCROLLER_ANIMATION ";

// scrollToEdge at a fixed speed
constexpr char SCROLLER_FIX_VELOCITY_ANIMATION[] = "SCROLLER_FIX_VELOCITY_ANIMATION ";

using OnScrollEvent = std::function<void(Dimension, ScrollState)>;
using OnDidScrollEvent = std::function<void(Dimension, ScrollState, bool, bool)>;
using OnWillScrollEvent = std::function<ScrollFrameResult(Dimension, ScrollState, ScrollSource)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollFrameBeginEvent = std::function<ScrollFrameResult(Dimension, ScrollState)>;
using OnScrollStartEvent = std::function<void()>;
using OnScrollStopEvent = std::function<void()>;
using OnReachEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t, int32_t)>;
using OnScrollVisibleContentChangeEvent = std::function<void(ListItemIndex, ListItemIndex)>;

using ScrollPositionCallback = std::function<bool(double, int32_t source)>;
using ScrollEndCallback = std::function<void()>;
using StartSnapMotionCallback = std::function<bool(float delta, float dragDistance, float velocity)>;
using ScrollBarFRCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;
using ScrollPageCallback = std::function<void(bool, bool smooth)>;

struct ScrollerObserver {
    RefPtr<NG::TouchEventImpl> onTouchEvent;
    GestureEventFunc onPanActionEndEvent;
    OnReachEvent onReachStartEvent;
    OnReachEvent onReachEndEvent;
    OnScrollStartEvent onScrollStartEvent;
    OnScrollStopEvent onScrollStopEvent;
    OnDidScrollEvent onDidScrollEvent;
};
} // namespace OHOS::Ace

#endif

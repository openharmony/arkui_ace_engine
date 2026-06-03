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
#include "base/geometry/rect.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/gestures/gesture_event.h"
#include "ui/properties/scrollable_properties.h"

namespace OHOS::Ace::NG {
enum class SceneStatus : int8_t;
class TouchEventImpl;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

class ShapeRect;
constexpr float DEFAULT_SCROLL_TO_MASS = 1.0f;
constexpr float DEFAULT_SCROLL_TO_STIFFNESS = 227.0f;
constexpr float DEFAULT_SCROLL_TO_DAMPING = 33.0f;
constexpr float DEFAULT_SCROLL_TO_VELOCITY = 7.0f;

struct SpringCurveOption {
    float velocity = DEFAULT_SCROLL_TO_VELOCITY;
    float mass = DEFAULT_SCROLL_TO_MASS;
    float stiffness = DEFAULT_SCROLL_TO_STIFFNESS;
    float damping = DEFAULT_SCROLL_TO_DAMPING;
};

// for add item and scrollEdge(Edge.Bottom) in one layout
constexpr int32_t LAST_ITEM = -1;

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

enum class ScrollBarShape {
    RECT = 0,
    ARC,
};

enum class ScrollPagingStatus {
    // no enablePaging set
    NONE = 0,
    // enablePaging is false
    INVALID,
    // enablePaging is true
    VALID,
};

namespace NG {
enum class NestedState {
    GESTURE = 0,
    CHILD_SCROLL,
    CHILD_OVER_SCROLL,
    CHILD_CHECK_OVER_SCROLL,
};

struct OverScrollOffset {
    double start;
    double end;
};

struct ScrollResult {
    double remain;
    bool reachEdge;
};

enum class ContentClipMode {
    CONTENT_ONLY, // area excluding margin & padding & SafeAreaPadding
    BOUNDARY,     // corresponding to FrameRect, area excluding margin
    SAFE_AREA,    // CONTENT_ONLY area + SafeAreaPadding (which can stack up with ancestor's SafeAreaPadding)
    CUSTOM,       // inner enum, not present in frontend. Custom shape's offset is relative to FrameOffset.
    DEFAULT,      // Different scrollable components have different default clip values.
};

struct ContentClip {
    ContentClipMode first;
    RefPtr<ShapeRect> second;

    ContentClip(ContentClipMode mode, const RefPtr<ShapeRect>& shape);
    ContentClip(const ContentClip& other);
    ContentClip(ContentClip&& other);
    ContentClip& operator=(const ContentClip& other);
    ContentClip& operator=(ContentClip&& other);
    ~ContentClip();

    bool operator==(const ContentClip& other) const;
    bool operator!=(const ContentClip& other) const;
};
} // namespace NG

using NestedState = NG::NestedState;
using OverScrollOffset = NG::OverScrollOffset;
using ScrollResult = NG::ScrollResult;

enum class SnapType {
    SCROLL_SNAP = 0,
    LIST_SNAP,
    NONE_SNAP
};

enum class SnapDirection {
    FORWARD = 0,
    BACKWARD,
    NONE
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

    bool operator==(const ScrollInfo& scrollInfo) const;
};

struct ScrollFrameInfo {
    Dimension offset;
    ScrollState state;

    bool operator==(const ScrollFrameInfo& scrollInfo) const;
};

struct ScrollSnapOptions {
    int32_t snapAlign = 0;
    int32_t enableSnapToStart = 0;
    int32_t enableSnapToEnd = 0;
    std::vector<Dimension> paginationParams;
};

struct NestedScrollOptions {
    NestedScrollMode forward;
    NestedScrollMode backward;

    bool NeedParent() const;

    bool NeedParent(bool forward) const;

    bool operator==(const NestedScrollOptions& other) const;

    bool operator!=(const NestedScrollOptions& other) const;

    std::string ToString() const;

    std::string GetNestedScrollModeStr(NestedScrollMode mode) const;
};

struct NestedScrollOptionsExt {
    NestedScrollMode scrollUp;
    NestedScrollMode scrollDown;
    NestedScrollMode scrollLeft;
    NestedScrollMode scrollRight;

    std::string ToString() const;
};

struct ScrollBarMargin {
    Dimension start_;
    Dimension end_;

    bool operator==(const ScrollBarMargin& other) const;

    bool operator!=(const ScrollBarMargin& other) const;

    std::string ToString() const;
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
constexpr int32_t SCROLL_FROM_CROWN = 14;
constexpr int32_t SCROLL_FROM_STATUSBAR = 15;
constexpr int32_t SCROLL_FROM_LAYOUT = 16;
constexpr int32_t SCROLL_FROM_BAR_OVER_DRAG = 17;

std::string GetSourceStr(int32_t scrollSource);

struct ScrollableEventsFiredInfo {
    uint64_t eventFiredTime_ = 0;
    ScrollableEventType eventType_;
    int32_t scrollSource_ = 0;

    std::string ToString() const;

    std::string GetEventStr() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct ScrollableFrameInfo {
    uint64_t scrollStateTime_ = 0;
    int32_t scrollState_ = 0;
    bool canOverScroll_ = false;
    uint32_t canOverScrollInfo_ = 0;

    std::string ToString() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct ScrollLayoutInfo {
    uint64_t changedTime_ = 0;
    float scrollableDistance_ = 0;
    NG::SizeF scrollSize_;
    NG::SizeF viewPort_;
    NG::SizeF childSize_;

    std::string ToString() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct ScrollMeasureInfo {
    uint64_t changedTime_ = 0;
    std::optional<NG::LayoutConstraintF> parentConstraint_;
    std::optional<NG::LayoutConstraintF> childConstraint_;
    NG::SizeF selfSize_;
    NG::SizeF childSize_;

    std::string ToString() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct InnerScrollBarLayoutInfo {
    uint64_t layoutTime_ = 0;
    Size viewPortSize_;
    Offset lastOffset_;
    double estimatedHeight_ = 0.0;
    double outBoundary_ = 0.0;
    Rect activeRect_;

    std::string ToString() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct OuterScrollBarLayoutInfo {
    uint64_t layoutTime_ = 0;
    float currentOffset_ = 0.f;
    float scrollableNodeOffset_ = 0.f;

    std::string ToString() const;

    void ToJson(std::unique_ptr<JsonValue>& json) const;
};

struct SnapAnimationOptions {
    float snapDelta = 0.f;
    float animationVelocity = 0.f;
    float dragDistance = 0.f;
    SnapDirection snapDirection = SnapDirection::NONE;
    int32_t source = SCROLL_FROM_NONE;
    bool fromScrollBar = false; // stop spring animation? true: stop spring animation,false: continue spring animation
};

// app tail animation
constexpr char TRAILING_ANIMATION[] = "TRAILING_ANIMATION ";

// scroller animation, such as scrollTo, scrollPage
constexpr char SCROLLER_ANIMATION[] = "CUSTOM_ANIMATOR_SCROLLER_ANIMATION ";

// scrollToEdge at a fixed speed
constexpr char SCROLLER_FIX_VELOCITY_ANIMATION[] = "SCROLLER_FIX_VELOCITY_ANIMATION ";

using OnScrollEvent = std::function<void(Dimension, ScrollState)>;
using OnDidScrollEvent = std::function<void(Dimension, ScrollSource, bool, bool)>;
using OnScrollerAreaChangeEvent = std::function<void(Dimension, ScrollSource, bool, bool)>;
using OnWillScrollEvent = std::function<ScrollFrameResult(Dimension, ScrollState, ScrollSource)>;
using OnScrollBeginEvent = std::function<ScrollInfo(Dimension, Dimension)>;
using OnScrollFrameBeginEvent = std::function<ScrollFrameResult(Dimension, ScrollState)>;
using OnScrollStartEvent = std::function<void()>;
using OnScrollStopEvent = std::function<void()>;
using OnReachEvent = std::function<void()>;
using OnScrollIndexEvent = std::function<void(int32_t, int32_t, int32_t)>;
using ScrollIndexFunc = std::function<void(int32_t, int32_t)>;
using OnScrollVisibleContentChangeEvent = std::function<void(ListItemIndex, ListItemIndex)>;
using OnWillStopDraggingEvent = std::function<void(Dimension)>;

using ScrollPositionCallback = std::function<bool(double, int32_t source)>;
using ScrollEndCallback = std::function<void()>;
using StartSnapAnimationCallback = std::function<bool(SnapAnimationOptions)>;
using ScrollBarFRCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;
using ScrollPageCallback = std::function<void(bool, bool smooth)>;
using OnWillScrollEventEx = std::function<void(ScrollFrameResult&, ScrollState, ScrollSource)>;
using TwoDimensionOnWillScrollEvent = std::function<void(ScrollFrameResult&,
    ScrollFrameResult&, ScrollState, ScrollSource)>;

using OnWillStartDraggingEvent = std::function<void()>;
using OnDidStopDraggingEvent = std::function<void(bool)>;
using OnWillStartFlingEvent = std::function<void()>;
using OnDidStopFlingEvent = std::function<void()>;

struct ScrollerObserver {
    RefPtr<NG::TouchEventImpl> onTouchEvent;
    GestureEventFunc onPanActionEndEvent;
    OnReachEvent onReachStartEvent;
    OnReachEvent onReachEndEvent;
    OnScrollStartEvent onScrollStartEvent;
    OnScrollStopEvent onScrollStopEvent;
    OnDidScrollEvent onDidScrollEvent;
    OnScrollerAreaChangeEvent onScrollerAreaChangeEvent;
    OnWillScrollEventEx onWillScrollEventEx;
    TwoDimensionOnWillScrollEvent twoDimensionOnWillScrollEvent;
};
} // namespace OHOS::Ace

#endif

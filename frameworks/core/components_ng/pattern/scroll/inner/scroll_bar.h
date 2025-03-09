/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_H

#include <cmath>

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/utils/utils.h"
#include "core/animation/friction_motion.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"

namespace OHOS::Ace::NG {

constexpr double FACTOR_HALF = 0.5;
constexpr double DEFAULT_TOPANGLE = 60.0;
constexpr double DEFAULT_BOTTOMANGLE = 120.0;
constexpr double DEFAULT_MINANGLE = 10.0;
constexpr double STRAIGHT_ANGLE = 180.0;
constexpr double BAR_FRICTION = 0.9;
constexpr Color PRESSED_BLEND_COLOR = Color(0x19000000);
using DragFRCSceneCallback = std::function<void(double velocity, NG::SceneStatus sceneStatus)>;
using ScrollBarPositionCallback = std::function<bool(double, int32_t source, bool isMouseWheelScroll)>;

enum class BarDirection {
    BAR_NONE = 0,
    PAGE_UP,
    PAGE_DOWN,
};

class ScrollBar : public AceType {
    DECLARE_ACE_TYPE(ScrollBar, AceType);

public:
    ScrollBar();
    ScrollBar(DisplayMode displayMode, ShapeMode shapeMode = ShapeMode::RECT,
        PositionMode positionMode = PositionMode::RIGHT);
    ~ScrollBar() override = default;

    ShapeMode GetShapeMode() const
    {
        return shapeMode_;
    }
    DisplayMode GetDisplayMode() const
    {
        return displayMode_;
    }
    PositionMode GetPositionMode() const
    {
        return positionMode_;
    }
    void SetPadding(const Edge& padding)
    {
        padding_ = padding;
    }
    const Edge& GetPadding() const
    {
        return padding_;
    }
    void SetBackgroundColor(const Color& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }
    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }
    void SetForegroundColor(const Color& foregroundColor)
    {
        foregroundColor_ = foregroundColor;
    }
    double GetTopAngle() const
    {
        return topAngle_;
    }
    double GetBottomAngle() const
    {
        return bottomAngle_;
    }
    double GetTrickStartAngle() const
    {
        return trickStartAngle_;
    }
    double GetTrickSweepAngle() const
    {
        return trickSweepAngle_;
    }
    void SetMinHeight(const Dimension& minHeight)
    {
        minHeight_ = minHeight;
    }
    const Dimension& GetMinHeight() const
    {
        return minHeight_;
    }
    void SetMinDynamicHeight(const Dimension& minDynamicHeight)
    {
        minDynamicHeight_ = minDynamicHeight;
    }
    const Dimension& GetMinDynamicHeight() const
    {
        return minDynamicHeight_;
    }
    void SetInactiveWidth(const Dimension& inactiveWidth)
    {
        inactiveWidth_ = inactiveWidth;
    }
    void SetActiveWidth(const Dimension& activeWidth)
    {
        activeWidth_ = activeWidth;
    }
    const Dimension& GetActiveWidth() const
    {
        return activeWidth_;
    }
    const Rect& GetActiveRect() const
    {
        return activeRect_;
    }
    void SetTouchWidth(const Dimension& touchWidth)
    {
        touchWidth_ = touchWidth;
    }
    const Dimension& GetTouchWidth() const
    {
        return touchWidth_;
    }
    const Rect& GetBarRect() const
    {
        return barRect_;
    }
    bool IsScrollable() const
    {
        return isScrollable_;
    }
    bool GetPositionModeUpdate() const
    {
        return positionModeUpdate_;
    }
    void SetShapeMode(ShapeMode shapeMode)
    {
        shapeMode_ = shapeMode;
    }
    double GetOutBoundary() const
    {
        return outBoundary_;
    }
    void SetOutBoundary(double outBoundary)
    {
        outBoundary_ = outBoundary;
    }
    void SetPosition(const Dimension& position)
    {
        position_ = position;
    }
    const Dimension& GetPosition() const
    {
        return position_;
    }
    void SetPressed(bool press)
    {
        isPressed_ = press;
    }
    bool IsPressed() const
    {
        return isPressed_;
    }
    bool IsDriving() const
    {
        return isDriving_;
    }
    void SetHover(bool hover)
    {
        isHover_ = hover;
    }
    bool IsHover() const
    {
        return isHover_;
    }
    OpacityAnimationType GetOpacityAnimationType() const
    {
        return opacityAnimationType_;
    }
    void SetOpacityAnimationType(OpacityAnimationType opacityAnimationType)
    {
        opacityAnimationType_ = opacityAnimationType;
    }
    HoverAnimationType GetHoverAnimationType() const
    {
        return hoverAnimationType_;
    }
    void SetHoverAnimationType(HoverAnimationType hoverAnimationType)
    {
        hoverAnimationType_ = hoverAnimationType;
    }
    bool GetNeedAdaptAnimation() const
    {
        return needAdaptAnimation_;
    }
    void SetMarkNeedRenderFunc(std::function<void()>&& func)
    {
        markNeedRenderFunc_ = func;
    }
    RefPtr<TouchEventImpl> GetTouchEvent()
    {
        return touchEvent_;
    }
    RefPtr<InputEvent> GetMouseEvent()
    {
        return mouseEvent_;
    }
    RefPtr<InputEvent> GetHoverEvent() const
    {
        return hoverEvent_;
    }
    void SetIsUserNormalWidth(bool isUserNormalWidth)
    {
        isUserNormalWidth_ = isUserNormalWidth;
    }
    bool GetIsUserNormalWidth() const
    {
        return isUserNormalWidth_;
    }
    void SetStartReservedHeight(const Dimension& startReservedHeight)
    {
        startReservedHeight_ = startReservedHeight;
    }
    const Dimension& GetStartReservedHeight() const
    {
        return startReservedHeight_;
    }
    void SetEndReservedHeight(const Dimension& endReservedHeight)
    {
        endReservedHeight_ = endReservedHeight;
    }
    const Dimension& GetEndReservedHeight() const
    {
        return endReservedHeight_;
    }
    void SetHostBorderRadius(const BorderRadiusProperty& hostBorderRadius)
    {
        hostBorderRadius_ = hostBorderRadius;
    }
    const BorderRadiusProperty& GetHostBorderRadius() const
    {
        return hostBorderRadius_;
    }
    void SetScrollPositionCallback(ScrollBarPositionCallback&& callback)
    {
        scrollPositionCallback_ = std::move(callback);
    }
    const ScrollBarPositionCallback& GetScrollPositionCallback() const
    {
        return scrollPositionCallback_;
    }
    void SetScrollEndCallback(ScrollEndCallback&& scrollEndCallback)
    {
        scrollEndCallback_ = std::move(scrollEndCallback);
    }
    const ScrollEndCallback& GetScrollEndCallback() const
    {
        return scrollEndCallback_;
    }
    void SetStartSnapAnimationCallback(StartSnapAnimationCallback&& startSnapAnimationCallback)
    {
        startSnapAnimationCallback_ = std::move(startSnapAnimationCallback);
    }
    void SetDragFRCSceneCallback(DragFRCSceneCallback&& dragFRCSceneCallback)
    {
        dragFRCSceneCallback_ = std::move(dragFRCSceneCallback);
    }
    void SetDragStartPosition(float position)
    {
        dragStartPosition_ = position;
    }
    void SetDragEndPosition(float position)
    {
        dragEndPosition_ = position;
    }
    float GetDragOffset()
    {
        return dragEndPosition_ - dragStartPosition_;
    }
    bool IsReverse()
    {
        return isReverse_;
    }
    Rect GetTouchRegion() const
    {
        return touchRegion_;
    }
    RefPtr<ClickEvent> GetClickEvent()
    {
        return clickevent_;
    }
    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }
    void SetScrollPageCallback(ScrollPageCallback&& scrollPageCallback)
    {
        scrollPageCallback_ = std::move(scrollPageCallback);
    }
    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
        TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
        ResponseLinkResult& responseLinkResult, bool inBarRect = false);
    void OnCollectLongPressTarget(const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
        TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
        ResponseLinkResult& responseLinkResult);
    virtual bool InBarTouchRegion(const Point& point) const;
    virtual bool InBarHoverRegion(const Point& point) const;
    virtual bool InBarRectRegion(const Point& point) const;
    bool NeedScrollBar() const;
    bool NeedPaint() const;
    void UpdateScrollBarRegion(
        const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight, int32_t scrollSource);
    double GetNormalWidthToPx() const;
    virtual float CalcPatternOffset(float scrollBarOffset) const;
    Color GetForegroundColor() const;
    void SetHoverWidth(const RefPtr<ScrollBarTheme>& theme);
    void SetNormalWidth(const Dimension& normalWidth);
    void SetScrollable(bool isScrollable);
    void SetPositionMode(PositionMode positionMode);
    void SetDisplayMode(DisplayMode displayMode);
    void PlayScrollBarDisappearAnimation();
    void PlayScrollBarAppearAnimation();
    void PlayScrollBarGrowAnimation();
    void PlayScrollBarShrinkAnimation();
    void PlayScrollBarAdaptAnimation();
    void MarkNeedRender();
    void SetGestureEvent();
    void SetMouseEvent();
    void SetHoverEvent();
    void FlushBarWidth();
    virtual void CalcReservedHeight();
    void ScheduleDisappearDelayTask();
    float GetMainOffset(const Offset& offset) const;
    void SetReverse(bool reverse);
    BarDirection CheckBarDirection(const Point& point);
    void InitLongPressEvent();
    void HandleLongPress(bool smooth);
    bool AnalysisUpOrDown(Point point, bool& reverse);
    void ScheduleCaretLongPress();
    Axis GetPanDirection() const;
    // infos for dump
    void AddScrollBarLayoutInfo();
    void GetShapeModeDumpInfo();
    void GetShapeModeDumpInfo(std::unique_ptr<JsonValue>& json);
    void GetPositionModeDumpInfo();
    void GetPositionModeDumpInfo(std::unique_ptr<JsonValue>& json);
    void GetAxisDumpInfo();
    void GetAxisDumpInfo(std::unique_ptr<JsonValue>& json);
    void GetPanDirectionDumpInfo();
    void GetPanDirectionDumpInfo(std::unique_ptr<JsonValue>& json);
    void DumpAdvanceInfo();
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json);
    void StopFlingAnimation();

#ifdef ARKUI_CIRCLE_FEATURE
    void SetActiveBackgroundWidth(const Dimension& activeBackgroundWidth)
    {
        activeBackgroundWidth_ = activeBackgroundWidth;
    }

    void SetActiveScrollBarWidth(const Dimension& activeScrollBarWidth)
    {
        activeScrollBarWidth_ = activeScrollBarWidth;
    }
#endif

protected:
    void InitTheme();
    virtual void SetBarRegion(const Offset& offset, const Size& size);
    virtual void SetRoundTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset,
        double mainScrollExtent);
    double NormalizeToPx(const Dimension& dimension) const;
    Dimension GetNormalWidth()
    {
        return normalWidth_;
    }

#ifdef ARKUI_CIRCLE_FEATURE
    void SetMouseEventMember(RefPtr<InputEvent> mouseEvent)
    {
        mouseEvent_ = mouseEvent;
    }

    bool GetIsMousePressed()
    {
        return isMousePressed_;
    }

    void SetIsMousePressed(bool isMousePressed)
    {
        isMousePressed_ = isMousePressed;
    }

    Offset GetLocationInfo()
    {
        return locationInfo_;
    }

    void SetLocationInfo(Offset locationInfo)
    {
        locationInfo_ = locationInfo;
    }

    RefPtr<LongPressRecognizer> GetLongPressRecognizer()
    {
        return longPressRecognizer_;
    }

    void SetLongPressRecognizer(RefPtr<LongPressRecognizer> longPressRecognizer)
    {
        longPressRecognizer_ = longPressRecognizer;
    }

    void SetTouchEvent(RefPtr<TouchEventImpl> touchEvent)
    {
        touchEvent_ = touchEvent;
    }

    void SetPanRecognizer(RefPtr<PanRecognizer> panRecognizer)
    {
        panRecognizer_ = panRecognizer;
    }

    RefPtr<PanRecognizer> GetPanRecognizer()
    {
        return panRecognizer_;
    }

    void CallInitPanRecognizer()
    {
        InitPanRecognizer();
    }

    double GetEstimatedHeigh() const
    {
        return estimatedHeight_;
    }

    Size GetViewPortSize() const
    {
        return viewPortSize_;
    }

    bool IsDriving_() const
    {
        return isDriving_;
    }

    Dimension GetThemeNormalWidth()
    {
        return themeNormalWidth_;
    }

    double GetBarRegionSize() const
    {
        return barRegionSize_;
    }

    void SetBarRegionSize(double barRegionSize)
    {
        barRegionSize_ = barRegionSize;
    }

    double GetOffsetScale() const
    {
        return offsetScale_;
    }

    void SetOffsetScale(double offsetScale)
    {
        offsetScale_ = offsetScale;
    }
    
    void SetNormalBackgroundWidth(const Dimension& normalBackgroundWidth)
    {
        normalBackgroundWidth_ = normalBackgroundWidth;
    }

    const Dimension& GetNormalBackgroundWidth() const
    {
        return normalBackgroundWidth_;
    }

    const Dimension& GetActiveBackgroundWidth() const
    {
        return activeBackgroundWidth_;
    }

    void SetNormaMaxOffsetAngle(double normaMaxOffsetAngle)
    {
        normaMaxOffsetAngle_ = normaMaxOffsetAngle;
    }

    double GetNormaMaxOffsetAngle() const
    {
        return normaMaxOffsetAngle_;
    }

    void SetNormalStartAngle(double normalStartAngle)
    {
        normalStartAngle_ = normalStartAngle;
    }

    double GetNormalStartAngle() const
    {
        if (positionMode_ == PositionMode::LEFT) {
            return -normalStartAngle_ - STRAIGHT_ANGLE;
        }
        return normalStartAngle_;
    }

    void SetActiveStartAngle(double activeStartAngle)
    {
        activeStartAngle_ = activeStartAngle;
    }

    double GetActiveStartAngle() const
    {
        if (positionMode_ == PositionMode::LEFT) {
            return -activeStartAngle_ - STRAIGHT_ANGLE;
        }
        return activeStartAngle_;
    }

    void SetActiveMaxOffsetAngle(double activeMaxOffsetAngle)
    {
        activeMaxOffsetAngle_ = activeMaxOffsetAngle;
    }

    double GetActiveMaxOffsetAngle() const
    {
        return activeMaxOffsetAngle_;
    }

    void SetNormalScrollBarWidth(const Dimension& normalScrollBarWidth)
    {
        normalScrollBarWidth_ = normalScrollBarWidth;
    }

    const Dimension& GetNormalScrollBarWidth() const
    {
        return normalScrollBarWidth_;
    }

    const Dimension& GetActiveScrollBarWidth() const
    {
        return activeScrollBarWidth_;
    }
#endif

    double GetMinAngle() const
    {
        return minAngle_;
    }

private:
    void SetRectTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset, double mainScrollExtent,
        int32_t scrollSource);
    void SetRectTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset, double mainScrollExtent);

    void UpdateActiveRectSize(double activeSize);
    void UpdateActiveRectOffset(double activeMainOffset);
    
    void InitPanRecognizer();
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);
    void ProcessFrictionMotion(double value);
    void ProcessFrictionMotionStop();
    void CalcScrollBarRegion(double activeMainOffset, double activeSize, const Offset& offset, const Size& size,
        double& inactiveMainOffset, double& inactiveSize);
    void GetRadiusAndPadding(float& startRadius, float& endRadius, float& padding);
    DisplayMode displayMode_ = DisplayMode::AUTO;
    ShapeMode shapeMode_ = ShapeMode::RECT;
    PositionMode positionMode_ = PositionMode::RIGHT;
    BorderRadiusProperty hostBorderRadius_;
    Edge padding_;
    Color backgroundColor_;
    Color foregroundColor_;
    Rect touchRegion_;
    Rect hoverRegion_;
    Rect barRect_;
    Rect activeRect_;
    Dimension minHeight_;           // this is min static height
    Dimension minDynamicHeight_;    // this is min dynamic height when on the top or bottom
    Dimension startReservedHeight_; // this is reservedHeight on the start
    Dimension endReservedHeight_;   // this is reservedHeight on the end
    Dimension inactiveWidth_;
    Dimension activeWidth_;
    Dimension normalWidth_; // user-set width of the scrollbar
    Dimension themeNormalWidth_;
    Dimension touchWidth_;
    Dimension hoverWidth_;
    double barWidth_ = 0.0; // actual width of the scrollbar
    Dimension position_;
    double trickStartAngle_ = 0.0;
    double trickSweepAngle_ = 0.0;
    double topAngle_ = DEFAULT_TOPANGLE;
    double bottomAngle_ = DEFAULT_BOTTOMANGLE;
    double minAngle_ = DEFAULT_MINANGLE;
    double outBoundary_ = 0.0;
    double offsetScale_ = 1.0f;
    double scrollableOffset_ = 0.0;
    double barRegionSize_ = 0.0;
    double friction_ = BAR_FRICTION;
    double frictionPosition_ = 0.0;
    float dragStartPosition_ = 0.0f;
    float dragEndPosition_ = 0.0f;
    bool isScrollable_ = false;
    bool isPressed_ = false;
    bool isDriving_ = false; // false: scroll driving; true: bar driving
    bool isHover_ = false;
    bool positionModeUpdate_ = false;
    bool normalWidthUpdate_ = false;
    bool isUserNormalWidth_ = false;
    bool needAdaptAnimation_ = false;
    bool isReverse_ = false;
    bool isReverseUpdate_ = false;
    bool isShowScrollBar_ = false;
    Offset paintOffset_;
    Size viewPortSize_;
    Offset lastOffset_;
    double estimatedHeight_ = 0.0;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> hoverEvent_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<Animator> frictionController_;
    RefPtr<FrictionMotion> frictionMotion_;
    std::function<void()> markNeedRenderFunc_;
    ScrollBarPositionCallback scrollPositionCallback_;
    ScrollEndCallback scrollEndCallback_;
    StartSnapAnimationCallback startSnapAnimationCallback_;
    ScrollPageCallback scrollPageCallback_;
    OpacityAnimationType opacityAnimationType_ = OpacityAnimationType::NONE;
    HoverAnimationType hoverAnimationType_ = HoverAnimationType::NONE;
    CancelableCallback<void()> disappearDelayTask_;
    DragFRCSceneCallback dragFRCSceneCallback_;
    Axis axis_ = Axis::VERTICAL;
    RefPtr<ClickEvent> clickevent_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    Offset locationInfo_;
    // dump info
    std::list<InnerScrollBarLayoutInfo> innerScrollBarLayoutInfos_;
    bool needAddLayoutInfo = false;
    bool isMousePressed_ = false;

#ifdef ARKUI_CIRCLE_FEATURE
    Dimension normalBackgroundWidth_;
    Dimension activeBackgroundWidth_;
    double normalStartAngle_ = 0.0;
    double activeStartAngle_ = 0.0;
    double normaMaxOffsetAngle_ = 0.0;
    double activeMaxOffsetAngle_ = 0.0;
    Dimension normalScrollBarWidth_;
    Dimension activeScrollBarWidth_;
#endif // ARKUI_CIRCLE_FEATURE
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_H

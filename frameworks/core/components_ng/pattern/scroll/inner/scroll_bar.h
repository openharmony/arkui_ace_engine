/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {

constexpr double FACTOR_HALF = 0.5;
constexpr double DEFAULT_TOPANGLE = 60.0;
constexpr double DEFAULT_BOTTOMANGLE = 120.0;
constexpr double DEFAULT_MINANGLE = 10.0;
constexpr double STRAIGHT_ANGLE = 180.0;
constexpr double BAR_FRICTION = 0.9;
constexpr Color PRESSED_BLEND_COLOR = Color(0x19000000);

enum class ShapeMode {
    /*
     * unspecified, follow theme.
     */
    DEFAULT = 0,
    /*
     * rect scrollbar.
     */
    RECT,
    /*
     * round scrollbar.
     */
    ROUND,
};

enum class DisplayMode {
    /*
     * do not display scrollbar.
     */
    OFF = 0,
    /*
     * display scrollbar on demand.
     */
    AUTO,
    /*
     * always display scrollbar.
     */
    ON,
};

enum class PositionMode {
    /*
     * display scrollbar on right.
     */
    RIGHT = 0,
    /*
     * display scrollbar on left.
     */
    LEFT,
    /*
     * display scrollbar on bottom.
     */
    BOTTOM,
};

class ScrollBar final : public AceType {
    DECLARE_ACE_TYPE(ScrollBar, AceType);

public:
    ScrollBar(RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier = nullptr);
    ScrollBar(DisplayMode displayMode, RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier = nullptr,
        ShapeMode shapeMode = ShapeMode::RECT, PositionMode positionMode = PositionMode::RIGHT);
    ~ScrollBar() override = default;

    bool InBarTouchRegion(const Point& point) const;
    bool InBarActiveRegion(const Point& point) const;
    bool NeedScrollBar() const;
    bool NeedPaint() const;
    void UpdateScrollBarRegion(
        const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight);
    double GetNormalWidthToPx() const;
    float CalcPatternOffset(float scrollBarOffset) const;

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

    Color GetForegroundColor() const
    {
        return IsPressed() ? foregroundColor_.BlendColor(PRESSED_BLEND_COLOR) : foregroundColor_;
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

    void SetNormalWidth(const Dimension& normalWidth)
    {
        if (normalWidth_ != normalWidth) {
            normalWidthUpdate_ = true;
            normalWidth_ = normalWidth;
            CalcReservedHeight();
            FlushBarWidth();
            MarkNeedRender();
        }
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

    void SetScrollable(bool isScrollable)
    {
        isScrollable_ = isScrollable;
    }

    bool IsScrollable() const
    {
        return isScrollable_;
    }

    void SetPositionMode(PositionMode positionMode)
    {
        if (positionMode_ != positionMode) {
            positionModeUpdate_ = true;
            positionMode_ = positionMode;
        }
    }

    void SetShapeMode(ShapeMode shapeMode)
    {
        shapeMode_ = shapeMode;
    }

    void SetDisplayMode(DisplayMode displayMode)
    {
        displayMode_ = displayMode;
        if (displayMode_ == DisplayMode::AUTO) {
            PlayScrollBarEndAnimation();
        } else if (displayMode_ == DisplayMode::ON) {
            PlayScrollBarStartAnimation();
        }
    }

    void SetOutBoundary(double outBoundary)
    {
        inSpring_ =  !NearEqual(outBoundary_, outBoundary, 0.000001f);
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

    void SetHover(bool hover)
    {
        isHover_ = hover;
    }

    bool IsHover() const
    {
        return isHover_;
    }

    uint8_t GetOpacity() const
    {
        return opacity_;
    }

    void PlayScrollBarEndAnimation()
    {
        if (displayMode_ == DisplayMode::AUTO && isScrollable_ && !isHover_ && !isPressed_) {
            opacity_ = 0;
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetNeedEndAnimation(true);
            }
            MarkNeedRender();
        }
    }

    void PlayScrollBarStartAnimation()
    {
        if (displayMode_ == DisplayMode::AUTO && isScrollable_) {
            opacity_ = UINT8_MAX;
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetNeedAppearAnimation(true);
            }
            MarkNeedRender();
        }
    }

    void PlayScrollBarGrowAnimation()
    {
        PlayScrollBarStartAnimation();
        normalWidth_ = activeWidth_;
        FlushBarWidth();
        if (scrollBarOverlayModifier_) {
            scrollBarOverlayModifier_->SetNeedGrowAnimation(true);
        }
        MarkNeedRender();
    }

    void PlayScrollBarShrinkAnimation()
    {
        normalWidth_ = inactiveWidth_;
        FlushBarWidth();
        if (scrollBarOverlayModifier_) {
            scrollBarOverlayModifier_->SetNeedShrinkAnimation(true);
        }
        PlayScrollBarEndAnimation();
        MarkNeedRender();
    }

    void MarkNeedRender()
    {
        if (markNeedRenderFunc_) {
            markNeedRenderFunc_();
        }
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

    void SetIsUserNormalWidth(bool isUserNormalWidth)
    {
        isUserNormalWidth_ = isUserNormalWidth;
    }

    bool GetIsUserNormalWidth() const
    {
        return isUserNormalWidth_;
    }

    void SetReservedHeightUpdate(bool reservedHeightUpdate)
    {
        reservedHeightUpdate_ = reservedHeightUpdate;
    }

    bool GetReservedHeightUpdate() const
    {
        return reservedHeightUpdate_;
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
    
    void SetScrollPositionCallback(ScrollPositionCallback&& callback)
    {
        scrollPositionCallback_ = std::move(callback);
    }

    const ScrollPositionCallback& GetScrollPositionCallback() const
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

    RefPtr<ScrollBarOverlayModifier> GetScrollBarOverlayModifier() const
    {
        return scrollBarOverlayModifier_;
    }

    void SetScrollBarOverlayModifier(RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier)
    {
        scrollBarOverlayModifier_ = scrollBarOverlayModifier;
    }

    void SetGestureEvent();
    void SetMouseEvent();
    void FlushBarWidth();
    void PlayAdaptAnimation(double activeSize, double activeMainOffset, double inactiveSize, double inactiveMainOffset);
    void PlayGrowAnimation();
    void PlayShrinkAnimation();
    void PlayBarEndAnimation();
    void CalcReservedHeight();
    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
        TouchTestResult& result);

protected:
    void InitTheme();

private:
    void SetBarRegion(const Offset& offset, const Size& size);
    void SetRectTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset, double mainScrollExtent);
    void SetRoundTrickRegion(const Offset& offset, const Size& size, const Offset& lastOffset, double mainScrollExtent);
    void UpdateActiveRectSize(double activeSize);
    void UpdateActiveRectOffset(double activeMainOffset);
    double NormalizeToPx(const Dimension& dimension) const;
    void InitPanRecognizer();
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(const GestureEvent& info);
    void ProcessFrictionMotion(double value);
    void ProcessFrictionMotionStop();

    DisplayMode displayMode_ = DisplayMode::AUTO;
    ShapeMode shapeMode_ = ShapeMode::RECT;
    PositionMode positionMode_ = PositionMode::RIGHT;
    BorderRadiusProperty hostBorderRadius_;
    Edge padding_;
    Color backgroundColor_;
    Color foregroundColor_;
    Rect touchRegion_;
    Rect barRect_;
    Rect activeRect_;
    Dimension minHeight_;           // this is min static height
    Dimension minDynamicHeight_;    // this is min dynamic height when on the top or bottom
    Dimension startReservedHeight_; // this is reservedHeight on the start
    Dimension endReservedHeight_;   // this is reservedHeight on the end
    Dimension inactiveWidth_;
    Dimension activeWidth_;
    Dimension normalWidth_;
    Dimension touchWidth_;

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

    bool isScrollable_ = false;

    bool isPressed_ = false;
    bool isDriving_ = false; // false: scroll driving; true: bar driving
    bool isHover_ = false;
    bool inSpring_ = false; // whether bar in the spring state
    bool positionModeUpdate_ = false;
    bool normalWidthUpdate_ = false;
    bool isUserNormalWidth_ = false;
    bool reservedHeightUpdate_ = false; // has reserved hight been updated

    Offset paintOffset_;
    Size viewPortSize_;
    Offset lastOffset_;
    double estimatedHeight_ = 0.0;
    uint8_t opacity_ = UINT8_MAX;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<Animator> adaptAnimator_;
    RefPtr<Animator> frictionController_;
    RefPtr<FrictionMotion> frictionMotion_;
    std::function<void()> markNeedRenderFunc_;
    ScrollPositionCallback scrollPositionCallback_;
    ScrollEndCallback scrollEndCallback_;
    RefPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_INNER_SCROLL_BAR_H

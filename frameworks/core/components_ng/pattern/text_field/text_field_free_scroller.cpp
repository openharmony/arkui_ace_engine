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

#include "core/components_ng/pattern/text_field/text_field_free_scroller.h"

#include <vector>

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PI = 3.14159265358979323846f;
constexpr float PI_DEGREES = 180.0f;
constexpr float TWO_PI_DEGREES = 360.0f;

struct AngleRange {
    float start;
    float end;
    Axis direction;
};

const std::vector<AngleRange> ANGLE_RANGES = {
    { 270.0f, 315.0f, Axis::VERTICAL },   // Top-right, upper part
    { 315.0f, 360.0f, Axis::HORIZONTAL }, // Top-right, right part
    { 180.0f, 225.0f, Axis::HORIZONTAL }, // Top-left, left part
    { 225.0f, 270.0f, Axis::VERTICAL },   // Top-left, upper part
    { 90.0f, 135.0f, Axis::VERTICAL },    // Bottom-left, lower part
    { 135.0f, 180.0f, Axis::HORIZONTAL }, // Bottom-left, left part
    { 0.0f, 45.0f, Axis::HORIZONTAL },    // Bottom-right, right part
    { 45.0f, 90.0f, Axis::VERTICAL }      // Bottom-right, lower part
};

bool GetLocalPoint(const BaseEventInfo* info, Point& point)
{
    auto gestureEvent = TypeInfoHelper::DynamicCast<GestureEvent>(info);
    if (gestureEvent) {
        point = Point(gestureEvent->GetLocalLocation().GetX(), gestureEvent->GetLocalLocation().GetY());
        return true;
    }
    auto mouseInfo = TypeInfoHelper::DynamicCast<MouseInfo>(info);
    if (mouseInfo) {
        point = Point(mouseInfo->GetLocalLocation().GetX(), mouseInfo->GetLocalLocation().GetY());
        return true;
    }
    return false;
}

float CalculateAngle(const Offset& origin, const Offset& target)
{
    auto delta = target - origin;
    float radians = std::atan2(delta.GetY(), delta.GetX());
    float degrees = radians * PI_DEGREES / PI;
    while (Negative(degrees)) {
        degrees += TWO_PI_DEGREES;
    }
    while (GreatOrEqual(degrees, TWO_PI_DEGREES)) {
        degrees -= TWO_PI_DEGREES;
    }
    return degrees;
}
}
TextFieldFreeScroller::TextFieldFreeScroller(const WeakPtr<Pattern>& pattern) : pattern_(pattern)
{
    Initialize();
}

void TextFieldFreeScroller::Initialize()
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    if (textFieldPattern) {
        freeScrollController_ = MakeRefPtr<TextFreeScrollController>(WeakPtr<TextFieldPattern>(textFieldPattern));
        freeScrollController_->SetOnScrollCallback(
            [weak = WeakClaim(this)](float offset, int32_t source, bool isVertical) {
                auto controller = weak.Upgrade();
                CHECK_NULL_VOID(controller);
                controller->HandleScrollCallback(offset, source, isVertical);
            });
        freeScrollController_->SetOnScrollEndCallback([weak = WeakClaim(this)](bool isVertical) {
            auto controller = weak.Upgrade();
            CHECK_NULL_VOID(controller);
            controller->HandleEndScrollCallback(isVertical);
        });
    }
}

void TextFieldFreeScroller::HandleScrollCallback(float offset, int32_t source, bool isVertical)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    pattern->OnScrollWithAxisCallback(offset, source, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
    SyncOffset();
    if (source == SCROLL_FROM_START) {
        scrollingAxis_ = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
        return;
    }
    if (pattern->IsReachedBoundary(offset, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL)) {
        freeScrollController_->StopScrollAnimation(isVertical);
    }
}

void TextFieldFreeScroller::UpdateScrollBarOffsetWithAxis(Axis axis)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(scrollBar_);
    auto textRect = pattern->textRect_;
    auto contentRect = pattern->contentRect_;

    if (axis == Axis::VERTICAL) {
        scrollBar_->PlayAppearAnimation(true);
        scrollBar_->ScheduleDisappearDelayTask(true);
        auto verticalPadding = pattern->GetPaddingTop() + pattern->GetPaddingBottom();
        Size size(pattern->frameRect_.Width(), contentRect.Height() + verticalPadding);
        scrollBar_->UpdateVerticalBar(
            contentRect.Top() - textRect.Top(), textRect.Height() + verticalPadding, size, Offset(0.0, 0.0));
    } else if (axis == Axis::HORIZONTAL) {
        scrollBar_->PlayAppearAnimation(false);
        scrollBar_->ScheduleDisappearDelayTask(false);
        auto horizontalPadding = pattern->GetPaddingLeft() + pattern->GetPaddingRight();
        Size size(contentRect.Width() + horizontalPadding, pattern->frameRect_.Height());
        scrollBar_->UpdateHorizontalBar(contentRect.GetX() - pattern->textRect_.GetX(),
            pattern->textRect_.Width() + horizontalPadding, size, Offset(0.0, 0.0));
    } else {
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldFreeScroller::HandleStartScroll(bool isVertical)
{
    if (scrollBar_) {
        scrollBar_->PlayAppearAnimation(isVertical);
        scrollBar_->ScheduleDisappearDelayTask(!isVertical);
    }
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    if (pattern->selectOverlay_->IsCurrentMenuVisibile()) {
        pattern->isTextSelectionMenuShow_ = true;
    } else if (pattern->CheckSelectAreaVisible()) {
        pattern->isTextSelectionMenuShow_ = false;
    }
    pattern->selectOverlay_->HideMenu(true);
}

void TextFieldFreeScroller::HandleEndScrollCallback(bool isVertical)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    pattern->OnScrollEndCallbackWithAxis(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void TextFieldFreeScroller::SyncOffset()
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(freeScrollController_);
    freeScrollController_->UpdateCurrentOffset(pattern->textRect_.GetOffset());
}

void TextFieldFreeScroller::SetScrollBar(DisplayMode displayMode)
{
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            scrollBar_.Reset();
        }
        isScrollBarModiferPropertyttached_ = false;
        return;
    }
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    DisplayMode oldMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = MakeRefPtr<TextScrollBar2D>(WeakPtr<TextFieldPattern>(pattern));
    } else {
        oldMode = scrollBar_->GetDisplayMode();
    }
    if (oldMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBar_->IsScrollable()) {
            scrollBar_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
    }
    auto layoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    scrollBar_->SetPositionMode(isRTL ? PositionMode::LEFT : PositionMode::RIGHT);
    scrollBar_->UpdateBorderRadius(true);
    scrollBar_->UpdateBorderRadius(false);
    scrollBar_->SetScrollBarScrollCallback([weak = WeakClaim(this)](float offset, int32_t source, bool isVertical) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleScrollCallback(offset, source, isVertical);
    });
    scrollBar_->SetScrollBarEndCallback([weak = WeakClaim(this)](bool isVertical) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        controller->HandleEndScrollCallback(isVertical);
    });
}

void TextFieldFreeScroller::SetMinHeight(const Dimension& height)
{
    CHECK_NULL_VOID(scrollBar_);
    auto verticalBar = scrollBar_->GetVerticalBar();
    if (verticalBar) {
        verticalBar->SetMinHeight(height);
    }
    auto horizontalBar = scrollBar_->GetHorizontalBar();
    if (horizontalBar) {
        horizontalBar->SetMinHeight(height);
    }
}

void TextFieldFreeScroller::UpdateScrollBar()
{
    CHECK_NULL_VOID(scrollBar_);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    auto verticalModifier = scrollBar_->GetVerticalModifier();
    auto verticalBar = scrollBar_->GetVerticalBar();
    if (verticalModifier && verticalBar && verticalBar->NeedPaint()) {
        verticalModifier->StartBarAnimation(verticalBar->GetHoverAnimationType(),
            verticalBar->GetOpacityAnimationType(), verticalBar->GetNeedAdaptAnimation(), verticalBar->GetActiveRect());
        verticalBar->SetHoverAnimationType(HoverAnimationType::NONE);
        auto defaultValue = verticalBar->GetForegroundColor();
        auto barColorValue = textFieldLayoutProperty->GetScrollBarColorValue(defaultValue);
        verticalModifier->SetBarColor(barColorValue);
        verticalBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    }

    auto horizontalModifier = scrollBar_->GetHorizontalModifier();
    auto horizontalBar = scrollBar_->GetHorizontalBar();
    if (horizontalModifier && horizontalBar && horizontalBar->NeedPaint()) {
        horizontalModifier->StartBarAnimation(horizontalBar->GetHoverAnimationType(),
            horizontalBar->GetOpacityAnimationType(), horizontalBar->GetNeedAdaptAnimation(),
            horizontalBar->GetActiveRect());
        horizontalBar->SetHoverAnimationType(HoverAnimationType::NONE);
        auto defaultValue = horizontalBar->GetForegroundColor();
        auto barColorValue = textFieldLayoutProperty->GetScrollBarColorValue(defaultValue);
        horizontalModifier->SetBarColor(barColorValue);
        horizontalBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    }
}

void TextFieldFreeScroller::AttachModifier(const RefPtr<TextFieldOverlayModifier>& modifier)
{
    if (isScrollBarModiferPropertyttached_) {
        return;
    }
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(scrollBar_);
    auto verticalModifier = scrollBar_->GetVerticalModifier();
    CHECK_NULL_VOID(verticalModifier);
    for (const auto& prop : verticalModifier->GetAttachedProperties()) {
        modifier->AttachProperty(prop);
    }
    auto horizontalModifier = scrollBar_->GetHorizontalModifier();
    CHECK_NULL_VOID(horizontalModifier);
    for (const auto& prop : horizontalModifier->GetAttachedProperties()) {
        modifier->AttachProperty(prop);
    }
    isScrollBarModiferPropertyttached_ = true;
}

bool TextFieldFreeScroller::HandleMouseEventByScrollBar(MouseInfo& info)
{
    CHECK_NULL_RETURN(scrollBar_, false);
    auto verticalBar = scrollBar_->GetVerticalBar();
    if (verticalBar && (verticalBar->IsPressed() || verticalBar->IsHover() || IsPointInScrollBarRect(&info, true))) {
        return true;
    }
    auto horizontalBar = scrollBar_->GetHorizontalBar();
    if (horizontalBar &&
        (horizontalBar->IsPressed() || horizontalBar->IsHover() || IsPointInScrollBarRect(&info, false))) {
        return true;
    }
    return false;
}

bool TextFieldFreeScroller::CheckMousePressedOverScrollBar(GestureEvent& info)
{
    auto handleScrollBarClick = [weak = WeakClaim(this), info](bool isVertical) -> bool {
        auto controller = weak.Upgrade();
        CHECK_NULL_RETURN(controller, false);
        CHECK_NULL_RETURN(controller->scrollBar_, false);
        auto pattern = DynamicCast<TextFieldPattern>(controller->pattern_.Upgrade());
        CHECK_NULL_RETURN(pattern, false);
        auto scrollBar =
            isVertical ? controller->scrollBar_->GetVerticalBar() : controller->scrollBar_->GetHorizontalBar();
        CHECK_NULL_RETURN(scrollBar, false);
        if (scrollBar->GetDisplayMode() == DisplayMode::OFF) {
            return false;
        }
        auto border = pattern->GetBorderWidthProperty();
        float maxFrameSize = 0.0f;
        if (isVertical) {
            maxFrameSize = pattern->frameRect_.Height() - pattern->GetPaddingTop() - pattern->GetPaddingBottom() -
                           pattern->GetBorderTop(border) - pattern->GetBorderBottom(border);
        } else {
            maxFrameSize = pattern->frameRect_.Width() - pattern->GetPaddingLeft() - pattern->GetPaddingRight() -
                           pattern->GetBorderLeft(border) - pattern->GetBorderRight(border);
        }
        auto activeRect = scrollBar->GetActiveRect();
        auto clickPos = info.GetLocalLocation();
        bool isReverse = isVertical ? (LessNotEqual(clickPos.GetY(), activeRect.Top()))
                                    : (LessNotEqual(clickPos.GetX(), activeRect.Left()));
        float distance = isReverse ? (maxFrameSize / 2.0f) : -(maxFrameSize / 2.0f);
        controller->HandleScrollCallback(distance, SCROLL_FROM_JUMP, isVertical);
        return true;
    };
    if (IsPointInScrollBarRect(&info, true)) {
        return handleScrollBarClick(true);
    }
    if (IsPointInScrollBarRect(&info, false)) {
        return handleScrollBarClick(false);
    }
    return false;
}

bool TextFieldFreeScroller::IsPointInScrollBarRect(const BaseEventInfo* info, bool isVertical)
{
    Point point;
    if (!GetLocalPoint(info, point)) {
        return false;
    }
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, false);
    CHECK_NULL_RETURN(scrollBar_, false);
    auto scrollbar = isVertical ? scrollBar_->GetVerticalBar() : scrollBar_->GetHorizontalBar();
    CHECK_NULL_RETURN(scrollbar, false);
    if (!scrollbar->NeedPaint() || scrollbar->GetShapeMode() != ShapeMode::RECT) {
        return false;
    }
    auto barRect = scrollbar->GetBarRect();
    auto regionSize = MOUSE_SCROLL_BAR_REGION_WIDTH.ConvertToPx();
    auto& frameRect = textFieldPattern->frameRect_;
    if (isVertical) {
        barRect.SetLeft(barRect.Left() + barRect.Width() - regionSize);
        barRect.SetWidth(regionSize);
        barRect.SetHeight(frameRect.Height());
        barRect.SetTop(0.0f);
    } else {
        barRect.SetTop(barRect.Top() + barRect.Height() - regionSize);
        barRect.SetHeight(regionSize);
        barRect.SetWidth(frameRect.Width());
        barRect.SetLeft(0.0f);
    }
    return barRect.IsInRegion(point);
}

bool TextFieldFreeScroller::HandleInHorizontalBand(
    const AutoScrollStepParam& param, const RectF& workRect, Axis& axis, std::optional<float>& step) const
{
    bool inHorizontalBand =
        GreatNotEqual(param.offset.GetX(), workRect.Left()) && LessNotEqual(param.offset.GetX(), workRect.Right());
    if (!inHorizontalBand) {
        return false;
    }
    // Check if outside vertical bounds (top or bottom)
    bool outsideVerticalBounds =
        GreatNotEqual(param.offset.GetY(), workRect.Bottom()) || LessNotEqual(param.offset.GetY(), workRect.Top());
    if (param.hasHotArea || outsideVerticalBounds) {
        auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
        if (pattern) {
            axis = Axis::VERTICAL;
            auto adjustedOffset =
                param.enableScrollOutside ? pattern->AdjustAutoScrollOffset(param.offset) : param.offset;
            step = pattern->CalcAutoScrollStepOffset(adjustedOffset, Axis::VERTICAL);
        }
    }
    return true;
}

bool TextFieldFreeScroller::HandleInVerticalBand(const AutoScrollStepParam& param, const RectF& workRect,
    Axis& axis, std::optional<float>& step) const
{
    bool inVerticalBand =
        GreatNotEqual(param.offset.GetY(), workRect.Top()) && LessNotEqual(param.offset.GetY(), workRect.Bottom());
    if (!inVerticalBand) {
        return false;
    }
    // Check if outside horizontal bounds (left or right)
    bool outsideHorizontalBounds =
        GreatNotEqual(param.offset.GetX(), workRect.Right()) || LessNotEqual(param.offset.GetX(), workRect.Left());
    if (param.hasHotArea || outsideHorizontalBounds) {
        auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
        if (pattern) {
            axis = Axis::HORIZONTAL;
            auto adjustedOffset =
                param.enableScrollOutside ? pattern->AdjustAutoScrollOffset(param.offset) : param.offset;
            step = pattern->CalcAutoScrollStepOffset(adjustedOffset, Axis::HORIZONTAL);
        }
    }
    return true;
}

bool TextFieldFreeScroller::HandleCornerScrolling(const AutoScrollStepParam& param, const RectF& workRect,
    Axis& axis, std::optional<float>& step) const
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    // Four corners of the work rectangle (top-right, top-left, bottom-left, bottom-right)
    std::vector<Offset> corners = {
        Offset(workRect.Right(), workRect.Top()),
        Offset(workRect.Left(), workRect.Top()),
        Offset(workRect.Left(), workRect.Bottom()),
        Offset(workRect.Right(), workRect.Bottom())
    };
    // Map each corner to its starting index in ANGLE_RANGES
    std::vector<int> rangeIndexMap = { 0, 2, 4, 6 };
    constexpr size_t RANGES_PER_CORNER = 2;
    for (size_t cornerIndex = 0; cornerIndex < corners.size(); cornerIndex++) {
        float degree = CalculateAngle(corners[cornerIndex], param.offset);
        for (size_t degreeIndex = 0; degreeIndex < RANGES_PER_CORNER; degreeIndex++) {
            const auto& range = ANGLE_RANGES[rangeIndexMap[cornerIndex] + degreeIndex];
            if (GreatOrEqual(degree, range.start) && LessNotEqual(degree, range.end)) {
                axis = range.direction;
                auto adjustedOffset =
                    param.enableScrollOutside ? pattern->AdjustAutoScrollOffset(param.offset) : param.offset;
                step = pattern->CalcAutoScrollStepOffset(adjustedOffset, range.direction);
                return true;
            }
        }
    }
    return false;
}

void TextFieldFreeScroller::UpdateAutoScrollStepOffset(
    const AutoScrollStepParam& param, Axis& axis, std::optional<float>& step)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto contentRect = pattern->contentRect_;
    RectF workRect = contentRect;
    if (param.hasHotArea) {
        auto hotAreaWidth = AUTO_SCROLL_HOT_ZONE_WIDTH.ConvertToPx();
        auto hotAreaHeight = AUTO_SCROLL_HOT_ZONE_HEIGHT.ConvertToPx();
        workRect = RectF(contentRect.Left() + hotAreaWidth, contentRect.Top() + hotAreaHeight,
            contentRect.Width() - 2.0f * hotAreaWidth, contentRect.Height() - 2.0f * hotAreaHeight);
    }
    // Try to handle in horizontal band
    if (HandleInHorizontalBand(param, workRect, axis, step)) {
        return;
    }
    // Try to handle in vertical band
    if (HandleInVerticalBand(param, workRect, axis, step)) {
        return;
    }
    // Handle corner scrolling
    HandleCornerScrolling(param, workRect, axis, step);
}

void TextFieldFreeScroller::UpdateSecondHandleInfoByMouse(MouseInfo& info)
{
    auto pattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto localLocation = info.GetLocalLocation();
    if (pattern->contentRect_.IsInRegion(PointF(localLocation.GetX(), localLocation.GetY()))) {
        pattern->StopContentScroll();
        pattern->selectController_->UpdateSecondHandleInfoByMouseOffset(localLocation);
        return;
    }
    pattern->contentScroller_.scrollingCallback = [weak = WeakPtr<TextFieldPattern>(pattern)](const Offset& offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->selectController_->UpdateSecondHandleInfoByMouseOffset(offset);
        auto tmpHost = pattern->GetHost();
        CHECK_NULL_VOID(tmpHost);
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    pattern->UpdateContentScroller(localLocation);
}

void TextFieldFreeScroller::PlayScrollBarAppearAnimation(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->PlayAppearAnimation(axis == Axis::VERTICAL);
}

void TextFieldFreeScroller::ScheduleDisappearDelayTask()
{
    ScheduleDisappearDelayTaskWitAxis(Axis::VERTICAL);
    ScheduleDisappearDelayTaskWitAxis(Axis::HORIZONTAL);
}

void TextFieldFreeScroller::ScheduleDisappearDelayTaskWitAxis(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->ScheduleDisappearDelayTask(axis == Axis::VERTICAL);
}

void TextFieldFreeScroller::ScheduleScrollingDisappearDelayTask()
{
    if (scrollingAxis_ != Axis::NONE) {
        ScheduleDisappearDelayTaskWitAxis(scrollingAxis_);
        scrollingAxis_ = Axis::NONE;
    } else {
        ScheduleDisappearDelayTask();
    }
}

void TextFieldFreeScroller::StopScrolling()
{
    CHECK_NULL_VOID(freeScrollController_);
    freeScrollController_->StopAllScrollAnimation();
}
} // namespace OHOS::Ace::NG

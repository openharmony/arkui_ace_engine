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

#include "core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.h"
#include "core/components_ng/base/observer_handler.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float PI = 3.14159265358979323846f;
constexpr float PI_DEGREES = 180.0f;
constexpr float TWO_PI_DEGREES = 360.0f;
constexpr Dimension MOUSE_SCROLL_BAR_REGION_WIDTH = 8.0_vp;
// Virtual border radius used to offset scrollbars from the edges to prevent overlap;
constexpr Dimension SCROLL_BAR_BORDER_RADIUS_SIZE = 20.0_vp;

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

const std::vector<int> RANGE_INDEX_MAP = { 0, 2, 4, 6 };
}

RichEditorScrollController::RichEditorScrollController(RichEditorPattern* pattern)
    : weakPattern_(AceType::WeakClaim(pattern)),
      isSingleLineMode_(pattern->isSingleLineMode_),
      contentRect_(pattern->contentRect_),
      textRect_(pattern->richTextRect_),
      frameRect_(pattern->frameRect_),
      selectOverlay_(pattern->selectOverlay_),
      textSelector_(pattern->textSelector_)
{}

bool RichEditorScrollController::IsReachTop()
{
    return NearEqual(textRect_.GetY(), contentRect_.GetY());
}

bool RichEditorScrollController::IsReachBottom()
{
    return NearEqual(textRect_.Bottom(), contentRect_.Bottom());
}

bool RichEditorScrollController::IsReachLeft()
{
    return NearEqual(textRect_.GetX(), contentRect_.GetX());
}

bool RichEditorScrollController::IsReachRight()
{
    return NearEqual(textRect_.Right(), contentRect_.Right());
}

bool RichEditorScrollController::IsReachLowerBoundary()
{
    return IsReachLowerBoundary(!isSingleLineMode_);
}

bool RichEditorScrollController::IsReachUpperBoundary()
{
    return IsReachUpperBoundary(!isSingleLineMode_);
}

bool RichEditorScrollController::IsReachBoundary()
{
    return IsReachLowerBoundary() || IsReachUpperBoundary();
}

bool RichEditorScrollController::IsReachAvoidBoundary(float offset)
{
    auto axis = isSingleLineMode_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    return IsReachAvoidBoundary(offset, axis);
}

float RichEditorScrollController::CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point)
{
    CHECK_NULL_RETURN(hotAreaStart != hotAreaEnd, 0.0f);
    auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
    auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
    return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * AUTO_SCROLL_INTERVAL;
}

void RichEditorScrollController::ScheduleAutoScroll(AutoScrollParam param)
{
    bool isVertical = (param.axis == Axis::NONE) ? !isSingleLineMode_ : param.axis == Axis::VERTICAL;
    bool aboutToBeyondLower = IsReachLowerBoundary(isVertical) && GreatNotEqual(param.offset, 0.0f);
    bool aboutToBeyondUpper = IsReachUpperBoundary(isVertical) && LessNotEqual(param.offset, 0.0f);
    CHECK_NULL_VOID(!aboutToBeyondLower && !aboutToBeyondUpper);

    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (param.isFirstRun_) {
        param.isFirstRun_ = false;
        currentScrollParam_ = param;
        CHECK_NULL_VOID(!isAutoScrollRunning_);
    }
    autoScrollTask_.Reset([weakPattern = weakPattern_, weakController = WeakClaim(this), isVertical]() {
        auto pattern = weakPattern.Upgrade();
        auto controller = weakController.Upgrade();
        CHECK_NULL_VOID(pattern && controller);
        if (controller->IsFreeScrollEnabled()) {
            controller->ProcessAutoScroll();
        } else {
            controller->OnAutoScroll(controller->currentScrollParam_);
        }
        if (controller->IsReachBoundary(isVertical)) {
            controller->StopAutoScroll();
        }
    });
    isAutoScrollRunning_ = true;
    taskExecutor->PostDelayedTask(autoScrollTask_, TaskExecutor::TaskType::UI, AUTO_SCROLL_INTERVAL,
        "ArkUIRichEditorScheduleAutoScroll");
}

void RichEditorScrollController::StopAutoScroll()
{
    isAutoScrollRunning_ = false;
    autoScrollTask_.Cancel();
    prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
    ScheduleDisappearDelayTask();
}

float RichEditorScrollController::GetAutoScrollOffsetDiff(const OffsetF& offset)
{
    return isSingleLineMode_
        ? prevAutoScrollOffset_.GetX() - offset.GetX()
        : prevAutoScrollOffset_.GetY() - offset.GetY();
}

bool RichEditorScrollController::GetHotAreaOverflow(bool isDragging, float edgeThreshold)
{
    auto maxHeight = isDragging ? frameRect_.Height() : contentRect_.Height();
    auto maxWidth = isDragging ? frameRect_.Width() : contentRect_.Width();
    auto doubleThreshold = edgeThreshold * 2;
    return isSingleLineMode_ ? GreatNotEqual(doubleThreshold, maxWidth) : GreatNotEqual(doubleThreshold, maxHeight);
}

RectF RichEditorScrollController::GetSafeAreaRect(bool isDragging)
{
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DIS.ConvertToPx() : AUTO_SCROLL_EDGE_DIS.ConvertToPx();
    return RectF(
        isDragging ? edgeThreshold : contentRect_.GetX() + edgeThreshold,
        isDragging ? edgeThreshold : contentRect_.GetY() + edgeThreshold,
        (isDragging ? frameRect_.Width() : contentRect_.Width()) - 2.0f * edgeThreshold,
        (isDragging ? frameRect_.Height() : contentRect_.Height()) - 2.0f * edgeThreshold
    );
}

void RichEditorScrollController::HandleAutoScrollNearBoundary(
    AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy)
{
    auto scrollOffsetDiff = GetAutoScrollOffsetDiff(offset);
    CHECK_NULL_VOID(!NearZero(scrollOffsetDiff));
    prevAutoScrollOffset_ = offset;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DIS.ConvertToPx() : AUTO_SCROLL_EDGE_DIS.ConvertToPx();
    bool hotAreaOverflow = GetHotAreaOverflow(isDragging, edgeThreshold);
    if (hotAreaOverflow) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleAutoScrollNearBoundary: hot area height is great than max height.");
        return;
    }
    auto safeAreaRect = GetSafeAreaRect(isDragging);
    RectF handleRect{ offset, param.handleRect.GetSize() };
    auto lowerThreshold = isSingleLineMode_ ? safeAreaRect.Left() : safeAreaRect.Top();
    auto upperThreshold = isSingleLineMode_ ? safeAreaRect.Right() : safeAreaRect.Bottom();
    auto handleLower = isSingleLineMode_ ? handleRect.Left() : handleRect.Top();
    auto handleUpper = isSingleLineMode_ ? handleRect.Right() : handleRect.Bottom();
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        if (GreatNotEqual(handleUpper, upperThreshold)) {
            param.offset = upperThreshold - handleUpper;
            ScheduleAutoScroll(param);
        } else if (LessNotEqual(handleLower, lowerThreshold)) {
            param.offset = lowerThreshold - handleLower;
            ScheduleAutoScroll(param);
        } else {
            StopAutoScroll();
        }
        return;
    }
    // drag and mouse
    if (GreatNotEqual(handleLower, upperThreshold)) {
        auto frameRectLen = isSingleLineMode_ ? frameRect_.Width() : frameRect_.Height();
        param.offset = isDragging ? -CalcDragSpeed(upperThreshold, frameRectLen, handleLower)
                    : upperThreshold - handleLower;
        ScheduleAutoScroll(param);
    } else if (LessNotEqual(handleLower, lowerThreshold)) {
        param.offset = isDragging ? CalcDragSpeed(lowerThreshold, 0, handleLower) : lowerThreshold - handleLower;
        ScheduleAutoScroll(param);
    } else {
        StopAutoScroll();
    }
}

OffsetF RichEditorScrollController::GetOffset2d(float offset)
{
    return GetOffset2d(offset, !isSingleLineMode_);
}

void RichEditorScrollController::MoveHandleOnScroll(float offset)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    OffsetF offset2d = GetOffset2d(offset);
    MoveFirstHandleOnScroll(offset2d);
    MoveSecondHandleOnScroll(offset2d);
}

void RichEditorScrollController::MoveHandleOnScroll(float offset, bool isFirst)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    OffsetF offset2d = GetOffset2d(offset);
    isFirst ? MoveFirstHandleOnScroll(offset2d) : MoveSecondHandleOnScroll(offset2d);
}

void RichEditorScrollController::MoveFirstHandleOnScroll(const OffsetF& offset)
{
    textSelector_.selectionBaseOffset += offset;
    auto firstHandleOffset = textSelector_.firstHandle.GetOffset();
    firstHandleOffset += offset;
    textSelector_.firstHandle.SetOffset(firstHandleOffset);
    selectOverlay_->UpdateFirstHandleOffset();
}

void RichEditorScrollController::MoveSecondHandleOnScroll(const OffsetF& offset)
{
    textSelector_.selectionDestinationOffset += offset;
    auto secondHandleOffset = textSelector_.secondHandle.GetOffset();
    secondHandleOffset += offset;
    textSelector_.secondHandle.SetOffset(secondHandleOffset);
    selectOverlay_->UpdateSecondHandleOffset();
}

float RichEditorScrollController::MoveTextRect(float offset)
{
    offset = isSingleLineMode_ ? MoveTextRectHorizontal(offset) : MoveTextRectVertical(offset);
    UpdateScrollBarOffset();
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, offset);
    pattern->UpdateChildrenOffset();
    if (auto host = pattern->GetContentHost(); host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    return offset;
}

float RichEditorScrollController::MoveTextRectHorizontal(float offset)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveTextRectHorizontal, offsetIn=%{public}f, textWidth=%{public}f, "
        "contentWidth=%{public}f", offset, textRect_.Width(), contentRect_.Width());
    if (textRect_.Width() > contentRect_.Width()) {
        if (offset > 0) { // move ->
            offset = std::min(offset, contentRect_.GetX() - textRect_.GetX());
        } else if (offset < 0) { //  <- move
            offset = std::max(offset, contentRect_.Right() - textRect_.Right());
        }
    } else {
        offset = contentRect_.GetX() - textRect_.GetX();
    }
    scrollOffset_ = textRect_.GetX() + offset;
    textRect_.SetOffset(OffsetF(scrollOffset_, textRect_.GetY()));
    return offset;
}

float RichEditorScrollController::MoveTextRectVertical(float offset)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, 0.0f);
    auto keyboardOffset = pattern->GetCrossOverHeight();
    if (NeedScroll(true, keyboardOffset)) {
        if (GreatNotEqual(textRect_.GetY() + offset, contentRect_.GetY())) {
            offset = contentRect_.GetY() - textRect_.GetY();
        } else if (LessNotEqual(textRect_.Bottom() + offset, contentRect_.Bottom() - keyboardOffset)) {
            offset = contentRect_.Bottom() - keyboardOffset - textRect_.Bottom();
        }
    } else if (!NearEqual(textRect_.GetY(), contentRect_.GetY())) {
        offset = contentRect_.GetY() - textRect_.GetY();
    } else {
        return 0.0f;
    }
    if (NearEqual(offset, 0.0f)) {
        return offset;
    }
    scrollOffset_ = textRect_.GetY() + offset;
    textRect_.SetOffset(OffsetF(textRect_.GetX(), scrollOffset_));
    return offset;
}

float RichEditorScrollController::CalCaretToContentRectDistanceVertical(
    const OffsetF& caretOffset, float caretHeight, float keyboardOffset)
{
    if (LessNotEqual(contentRect_.GetSize().Height(), caretHeight) &&
        !NearEqual(caretOffset.GetY() + caretHeight, contentRect_.Bottom() - keyboardOffset)) {
        return contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight;
    }
    if (LessNotEqual(contentRect_.GetSize().Height(), caretHeight)) {
        return 0.0f;
    }
    if (LessNotEqual(caretOffset.GetY(), contentRect_.GetY())) {
        if (LessOrEqual(caretOffset.GetX(), textRect_.GetX())) {
            return contentRect_.GetY() - caretOffset.GetY() + caretHeight;
        } else {
            return contentRect_.GetY() - caretOffset.GetY();
        }
    } else if (GreatNotEqual(caretOffset.GetY() + caretHeight, contentRect_.Bottom() - keyboardOffset)) {
        return contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight -
            CARET_BOTTOM_DISTANCE.ConvertToPx();
    }
    return 0.0f;
}

float RichEditorScrollController::CalCaretToContentRectDistanceHorizontal(const OffsetF& caretOffset, float caretWidth)
{
    float caretLeft = caretOffset.GetX();
    float caretRight = caretOffset.GetX() + caretWidth;
    float distanceLeft = std::max(contentRect_.Left() - caretLeft, 0.0f);
    float distanceRight = std::min(contentRect_.Right() - caretRight, 0.0f);
    return distanceLeft + distanceRight;
}

bool RichEditorScrollController::NeedScroll()
{
    return NeedScroll(!isSingleLineMode_);
}

bool RichEditorScrollController::NeedScroll(bool isVertical, float keyboardOffset)
{
    if (isVertical) {
        return !isSingleLineMode_ && GreatNotEqual(textRect_.Height(), contentRect_.Height() - keyboardOffset);
    }
    return GreatNotEqual(textRect_.Width(), contentRect_.Width());
}

float RichEditorScrollController::GetScrollOffset()
{
    return scrollOffset_;
}

void RichEditorScrollController::HandleScrollStart()
{
    if (selectOverlay_->SelectOverlayIsOn()) {
        selectOverlay_->HideMenu(true);
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    pattern->CloseAIMenu();
#ifndef CROSS_PLATFORM
    pattern->RecordScrollEvent(Recorder::EventType::SCROLL_START);
#endif
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        weakPattern_, ScrollEventType::SCROLL_START);
}

bool RichEditorScrollController::HandleScrollCallback(float offset, int32_t source)
{
    CHECK_NULL_RETURN(offset != 0, false);
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    auto scrollBar = pattern->GetScrollBar();
    if (source == SCROLL_FROM_START) {
        IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
        HandleScrollStart();
        return true;
    }
    if (IsReachAvoidBoundary(offset)) {
        return false;
    }
    if (scrollBar && source == SCROLL_FROM_JUMP) {
        scrollBar->PlayScrollBarAppearAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
    auto newOffset = MoveTextRect(offset);
    MoveHandleOnScroll(newOffset);
    pattern->ClearAISpanRects();
    return true;
}

void RichEditorScrollController::MoveCaretToContentRectHorizontal(const OffsetF& caretOffset)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveCaretToContentRect Horizontal");
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    if (LessOrEqual(textRect_.Width(), contentRect_.Width()) || pattern->isShowPlaceholder_) {
        return;
    }
    auto caretWidth = pattern->GetOverlayCaretWidth();
    float distance = CalCaretToContentRectDistanceHorizontal(caretOffset, caretWidth);
    HandleScrollCallback(distance, SCROLL_FROM_NONE);
}

void RichEditorScrollController::MoveCaretToContentRectVertical(const OffsetF& caretOffset, float caretHeight)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveCaretToContentRect Vertical");
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto keyboardOffset = pattern->GetCrossOverHeight();
    auto scrollBar = pattern->GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarAppearAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
    if (LessOrEqual(textRect_.Height(), contentRect_.Height() - keyboardOffset) || pattern->isShowPlaceholder_) {
        return;
    }
    float distance = CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    HandleScrollCallback(distance, SCROLL_FROM_NONE);
}

void RichEditorScrollController::MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight)
{
    if (IsFreeScrollEnabled()) {
        auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
        CHECK_NULL_VOID(pattern);
        auto caretWidth = pattern->GetOverlayCaretWidth();
        auto caretRect = RectF(caretOffset, SizeF(caretWidth, caretHeight));
        MoveCaretToContentRect(caretRect);
        return;
    }
    isSingleLineMode_ ? MoveCaretToContentRectHorizontal(caretOffset)
                      : MoveCaretToContentRectVertical(caretOffset, caretHeight);
}

void RichEditorScrollController::OnAutoScroll(AutoScrollParam param)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    if (param.showScrollbar) {
        auto scrollBar = pattern->GetScrollBar();
        IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
        param.showScrollbar = false;
    }
    CHECK_NULL_VOID(param.autoScrollEvent != AutoScrollEvent::NONE);
    auto newOffset = MoveTextRect(param.offset);
    switch (param.autoScrollEvent) {
        case AutoScrollEvent::CARET:
            break;
        case AutoScrollEvent::HANDLE: {
            MoveHandleOnScroll(newOffset, !param.isFirstHandle);
            selectOverlay_->OnHandleMove(param.handleRect, param.isFirstHandle);
            break;
        }
        case AutoScrollEvent::DRAG:
            break;
        case AutoScrollEvent::MOUSE:
            pattern->HandleMouseAutoScroll(param);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported auto scroll event type");
            return;
    }
    CHECK_NULL_VOID(!NearEqual(newOffset, 0.0f));
    ScheduleAutoScroll(param);
}

bool RichEditorScrollController::IsFreeScrollEnabled() const
{
    return freeScrollController_ != nullptr;
}

void RichEditorScrollController::ResetFreeScrollController()
{
    freeScrollController_.Reset();
    scrollBar_.Reset();
}

RefPtr<NGGestureRecognizer> RichEditorScrollController::GetScrollGestureRecognizer() const
{
    return freeScrollController_ ? freeScrollController_->GetGestureRecognizer() : nullptr;
}

bool RichEditorScrollController::IsReachBoundary(bool isVertical)
{
    return IsReachLowerBoundary(isVertical) || IsReachUpperBoundary(isVertical);
}

bool RichEditorScrollController::IsReachLowerBoundary(bool isVertical)
{
    return isVertical ? IsReachTop() : IsReachLeft();
}

bool RichEditorScrollController::IsReachUpperBoundary(bool isVertical)
{
    return isVertical ? IsReachBottom() : IsReachRight();
}

void RichEditorScrollController::PlayScrollBarAppearAnimation(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->PlayAppearAnimation(axis == Axis::VERTICAL);
}

void RichEditorScrollController::ScheduleDisappearDelayTask()
{
    if (IsFreeScrollEnabled()) {
        if (scrollingAxis_ != Axis::NONE) {
            ScheduleDisappearDelayTask(scrollingAxis_);
            return;
        }
        ScheduleDisappearDelayTask(Axis::VERTICAL);
        ScheduleDisappearDelayTask(Axis::HORIZONTAL);
        return;
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    IF_PRESENT(scrollBar, ScheduleDisappearDelayTask());
}

void RichEditorScrollController::ScheduleDisappearDelayTask(Axis axis)
{
    bool isVertical = axis == Axis::VERTICAL;
    CHECK_NULL_VOID(scrollBar_ && IsScrollDirectionValid(isVertical));
    scrollBar_->ScheduleDisappearDelayTask(isVertical);
}

void RichEditorScrollController::StopScrolling()
{
    if (IsFreeScrollEnabled()) {
        freeScrollController_->StopAllScrollAnimation();
        return;
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    pattern->StopScrollable();
}

void RichEditorScrollController::OnDrawScrollBar(DrawingContext& context)
{
    if (scrollBar_) {
        scrollBar_->OnDraw(context);
    }
}

void RichEditorScrollController::UpdateScrollBarColor(const Color& foregroundColor, const Color& backgroundColor)
{
    if (!IsFreeScrollEnabled()) {
        auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
        CHECK_NULL_VOID(pattern);
        auto scrollBar = pattern->GetScrollBar();
        CHECK_NULL_VOID(scrollBar);
        scrollBar->SetForegroundColor(foregroundColor);
        scrollBar->SetBackgroundColor(backgroundColor);
        return;
    }
    CHECK_NULL_VOID(scrollBar_);
    if (auto verticalBar = scrollBar_->GetVerticalBar(); verticalBar) {
        verticalBar->SetForegroundColor(foregroundColor);
        verticalBar->SetBackgroundColor(backgroundColor);
    }
    if (auto horizontalBar = scrollBar_->GetHorizontalBar(); horizontalBar) {
        horizontalBar->SetForegroundColor(foregroundColor);
        horizontalBar->SetBackgroundColor(backgroundColor);
    }
}

void RichEditorScrollController::UpdateScrollBarColor(std::optional<Color> color, bool isUpdateProperty)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto property = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    IF_TRUE(isUpdateProperty && property, property->UpdateScrollBarColor(color));
    auto scrollbarTheme = pattern->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollbarTheme);
    auto foregroundColor = color.value_or(scrollbarTheme->GetForegroundColor());
    auto backgroundColor = scrollbarTheme->GetBackgroundColor();
    UpdateScrollBarColor(foregroundColor, backgroundColor);
}

bool RichEditorScrollController::IsMouseOverScrollBar(const MouseInfo& info)
{
    if (IsFreeScrollEnabled()) {
        CHECK_NULL_RETURN(scrollBar_, false);
        auto point = Point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
        auto verticalBar = scrollBar_->GetVerticalBar();
        if (verticalBar &&
            (verticalBar->IsPressed() || verticalBar->IsHover() || IsPointInScrollBarRect(point, true))) {
            return true;
        }
        auto horizontalBar = scrollBar_->GetHorizontalBar();
        if (horizontalBar &&
            (horizontalBar->IsPressed() || horizontalBar->IsHover() || IsPointInScrollBarRect(point, false))) {
            return true;
        }
        return false;
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    auto scrollBar = pattern->GetScrollBar();
    CHECK_NULL_RETURN(scrollBar, false);
    return (scrollBar->IsHover() || scrollBar->IsPressed());
}

bool RichEditorScrollController::IsPointInScrollBarRect(const Point& point, bool isVertical)
{
    CHECK_NULL_RETURN(scrollBar_, false);
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    auto scrollbar = isVertical ? scrollBar_->GetVerticalBar() : scrollBar_->GetHorizontalBar();
    CHECK_NULL_RETURN(scrollbar, false);
    if (!scrollbar->NeedPaint() || scrollbar->GetShapeMode() != ShapeMode::RECT) {
        return false;
    }
    auto barRect = scrollbar->GetBarRect();
    auto regionSize = MOUSE_SCROLL_BAR_REGION_WIDTH.ConvertToPx();
    if (isVertical) {
        barRect.SetLeft(barRect.Left() + barRect.Width() - regionSize);
        barRect.SetWidth(regionSize);
        barRect.SetHeight(frameRect_.Height());
        barRect.SetTop(0.0f);
    } else {
        barRect.SetTop(barRect.Top() + barRect.Height() - regionSize);
        barRect.SetHeight(regionSize);
        barRect.SetWidth(frameRect_.Width());
        barRect.SetLeft(0.0f);
    }
    return barRect.IsInRegion(point);
}

// Intercepts vertical scrolling in single-line mode.
bool RichEditorScrollController::IsScrollDirectionValid(bool isVertical)
{
    return !(isVertical && isSingleLineMode_);
}

void RichEditorScrollController::CheckScrollEnabled()
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    bool needVerticalScroll = NeedScroll(true);
    bool needHorizontalScroll = NeedScroll(false);
    auto enabled = pattern->GetTextContentLength() > 0 && (needVerticalScroll || needHorizontalScroll);
    if (freeScrollController_) {
        freeScrollController_->SetScrollEnabled(enabled);
    }
    if (scrollBar_) {
        scrollBar_->SetScrollbarEnabled(enabled);
    }
}

void RichEditorScrollController::InitFreeScrollController(bool forceRecreate)
{
    if (freeScrollController_ && forceRecreate) {
        ResetFreeScrollController();
    }
    CHECK_NULL_VOID(!freeScrollController_);
    auto richEditorPattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    freeScrollController_ = MakeRefPtr<TextFreeScrollController>(WeakPtr<RichEditorPattern>(richEditorPattern));
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

void RichEditorScrollController::SetScrollBar(DisplayMode displayMode)
{
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            scrollBar_.Reset();
        }
        isScrollBarModifierPropertyAttached_ = false;
        return;
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    DisplayMode oldMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = MakeRefPtr<TextScrollBar2D>(WeakPtr<RichEditorPattern>(pattern));
    } else {
        scrollBar_->AddScrollableEvent();
        oldMode = scrollBar_->GetDisplayMode();
    }
    if (oldMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBar_->IsScrollable()) {
            scrollBar_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
    }
    // In single-line mode, disable vertical scrollbar to prevent it from being displayed.
    if (isSingleLineMode_) {
        scrollBar_->SetVerticalScrollable(false);
        if (auto verticalModifier = scrollBar_->GetVerticalModifier()) {
            verticalModifier->SetOpacity(0);
        }
    }
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    scrollBar_->SetPositionMode(isRTL ? PositionMode::LEFT : PositionMode::RIGHT);
    UpdateBorderRadius();
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

void RichEditorScrollController::UpdateBorderRadius()
{
    CHECK_NULL_VOID(scrollBar_);
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto ctx = host->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    auto defaultRadius = BorderRadiusProperty(SCROLL_BAR_BORDER_RADIUS_SIZE);
    auto radius = ctx->GetBorderRadius().value_or(defaultRadius);
    if (radius == BorderRadiusProperty(0.0_vp)) {
        radius = defaultRadius;
    }
    if (auto verticalBar = scrollBar_->GetVerticalBar()) {
        verticalBar->SetHostBorderRadius(radius);
        verticalBar->CalcReservedHeight();
    }
    if (auto horizontalBar = scrollBar_->GetHorizontalBar()) {
        horizontalBar->SetHostBorderRadius(radius);
        horizontalBar->CalcReservedHeight();
    }
}

void RichEditorScrollController::UpdateScrollBarAxis(bool isVertical)
{
    CHECK_NULL_VOID(scrollBar_);
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto modifier = isVertical ? scrollBar_->GetVerticalModifier() : scrollBar_->GetHorizontalModifier();
    auto bar = isVertical ? scrollBar_->GetVerticalBar() : scrollBar_->GetHorizontalBar();
    if (modifier && bar && bar->NeedPaint()) {
        modifier->StartBarAnimation(bar->GetHoverAnimationType(), bar->GetOpacityAnimationType(),
            bar->GetNeedAdaptAnimation(), bar->GetActiveRect());
        bar->SetHoverAnimationType(HoverAnimationType::NONE);
        auto barColorValue = pattern->GetScrollBarColor();
        modifier->SetBarColor(barColorValue);
        bar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    }
}

void RichEditorScrollController::UpdateScrollBar()
{
    UpdateScrollBarAxis(true);
    UpdateScrollBarAxis(false);
}

void RichEditorScrollController::UpdateScrollBarOffset()
{
    if (IsFreeScrollEnabled()) {
        UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, (scrollingAxis_ != Axis::HORIZONTAL));
        UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, (scrollingAxis_ != Axis::VERTICAL));
        return;
    }
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    if (!pattern->GetScrollBar() && !pattern->GetScrollBarProxy()) {
        return;
    }
    Size size(frameRect_.Width(), frameRect_.Height());
    auto verticalGap = frameRect_.Height() - contentRect_.Height();
    pattern->UpdateScrollBarRegion(
        contentRect_.GetY() - textRect_.GetY(), textRect_.Height() + verticalGap, size, Offset(0.0, 0.0));
    auto tmpHost = pattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorScrollController::PlayScrollBarUpdateAnimation(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    bool isVertical = (axis == Axis::VERTICAL);
    scrollBar_->PlayAppearAnimation(isVertical);
    scrollBar_->ScheduleDisappearDelayTask(isVertical);
}

void RichEditorScrollController::UpdateScrollBarOffsetWithAxis(Axis axis, bool needAnimation)
{
    CHECK_NULL_VOID(scrollBar_ && IsScrollDirectionValid(axis == Axis::VERTICAL));
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    bool hasText = (pattern->GetTextContentLength() > 0);
    IF_TRUE(needAnimation, PlayScrollBarUpdateAnimation(axis));
    CHECK_NULL_VOID(axis == Axis::VERTICAL || axis == Axis::HORIZONTAL);
    if (axis == Axis::VERTICAL) {
        auto verticalGap = frameRect_.Height() - contentRect_.Height();
        Size size(frameRect_.Width(), frameRect_.Height());
        scrollBar_->UpdateVerticalBar(
            contentRect_.GetY() - textRect_.GetY(), textRect_.Height() + verticalGap, size, Offset(0.0, 0.0));
        scrollBar_->SetVerticalScrollable(scrollBar_->IsVerticalScrollable() && hasText);
    } else if (axis == Axis::HORIZONTAL) {
        auto horizontalGap = frameRect_.Width() - contentRect_.Width();
        Size size(frameRect_.Width(), frameRect_.Height());
        scrollBar_->UpdateHorizontalBar(
            contentRect_.GetX() - textRect_.GetX(), textRect_.Width() + horizontalGap, size, Offset(0.0, 0.0));
        scrollBar_->SetHorizontalScrollable(scrollBar_->IsHorizontalScrollable() && hasText);
    }
    auto tmpHost = pattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorScrollController::SetMinHeight(const Dimension& height)
{
    CHECK_NULL_VOID(scrollBar_);
    if (auto verticalBar = scrollBar_->GetVerticalBar()) {
        verticalBar->SetMinHeight(height);
    }
    if (auto horizontalBar = scrollBar_->GetHorizontalBar()) {
        horizontalBar->SetMinHeight(height);
    }
}

bool RichEditorScrollController::IsAttachedModifier() const
{
    return isScrollBarModifierPropertyAttached_;
}

void RichEditorScrollController::AttachModifier(const RefPtr<OverlayModifier>& modifier)
{
    CHECK_NULL_VOID(!isScrollBarModifierPropertyAttached_);
    CHECK_NULL_VOID(modifier && scrollBar_);
    auto verticalModifier = scrollBar_->GetVerticalModifier();
    auto horizontalModifier = scrollBar_->GetHorizontalModifier();
    CHECK_NULL_VOID(verticalModifier && horizontalModifier);
    for (const auto& scrollModifier : {verticalModifier, horizontalModifier}) {
        for (const auto& prop : scrollModifier->GetAttachedProperties()) {
            modifier->AttachProperty(prop);
        }
    }
    isScrollBarModifierPropertyAttached_ = true;
}

void RichEditorScrollController::HandleScrollCallback(float offset, int32_t source, bool isVertical)
{
    CHECK_NULL_VOID(IsScrollDirectionValid(isVertical));
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    OnScrollWithAxisCallback(offset, source, axis);
    SyncOffset();
    bool needStopScroll = (source != SCROLL_FROM_START) && IsReachAvoidBoundary(offset, axis);
    if (needStopScroll) {
        freeScrollController_->StopScrollAnimation(isVertical);
    }
}

bool RichEditorScrollController::OnScrollWithAxisCallback(float offset, int32_t source, Axis axis)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    if (source == SCROLL_FROM_START) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Scroll start with axis:%{public}d", axis);
        scrollingAxis_ = axis;
        PlayScrollBarAppearAnimation(axis);
        HandleScrollStart();
        return true;
    }
    CHECK_NULL_RETURN(offset != 0 && !IsReachAvoidBoundary(offset, axis), false);
    if (source == SCROLL_FROM_JUMP) {
        PlayScrollBarAppearAnimation(axis);
        ScheduleDisappearDelayTask(axis);
    }
    auto newOffset = MoveTextRectWithAxis(offset, axis);
    MoveHandleOnScrollWithAxis(newOffset, axis);
    pattern->ClearAISpanRects();
    return true;
}

void RichEditorScrollController::HandleEndScrollCallback(bool isVertical)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleEndScrollCallback");
    scrollingAxis_ = Axis::NONE;
    CHECK_NULL_VOID(IsScrollDirectionValid(isVertical));
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    ScheduleDisappearDelayTask(axis);
    pattern->OnScrollEndCallback();
}

float RichEditorScrollController::MoveTextRectWithAxis(float offset, Axis axis)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern && IsScrollDirectionValid(axis == Axis::VERTICAL), 0.0f);
    offset = (axis == Axis::HORIZONTAL) ? MoveTextRectHorizontal(offset) : MoveTextRectVertical(offset);
    UpdateScrollBarOffsetWithAxis(axis);
    pattern->UpdateChildrenOffset();
    if (auto host = pattern->GetContentHost(); host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    return offset;
}

void RichEditorScrollController::SyncOffset()
{
    IF_PRESENT(freeScrollController_, UpdateCurrentOffset(textRect_.GetOffset()));
}

bool RichEditorScrollController::IsReachAvoidBoundary(float offset, Axis axis)
{
    if (axis == Axis::HORIZONTAL) {
        return (IsReachLeft() && GreatNotEqual(offset, 0.0f)) || (IsReachRight() && LessNotEqual(offset, 0.0f));
    }
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto keyboardOffset = pattern->GetCrossOverHeight();
    return (IsReachTop() && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(textRect_.Bottom(), contentRect_.Bottom() - keyboardOffset) && LessNotEqual(offset, 0.0f));
}

OffsetF RichEditorScrollController::GetOffset2d(float offset, bool isVertical)
{
    float offsetX = isVertical ? 0.0f : offset;
    float offsetY = isVertical ? offset : 0.0f;
    return { offsetX, offsetY };
}

void RichEditorScrollController::MoveHandleOnScrollWithAxis(float offset, Axis axis)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    bool isVertical = (axis == Axis::VERTICAL);
    OffsetF offset2d = GetOffset2d(offset, isVertical);
    MoveFirstHandleOnScroll(offset2d);
    MoveSecondHandleOnScroll(offset2d);
}

void RichEditorScrollController::MoveHandleOnScrollWithAxis(float offset, bool isFirst, Axis axis)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    bool isVertical = (axis == Axis::VERTICAL);
    OffsetF offset2d = GetOffset2d(offset, isVertical);
    isFirst ? MoveFirstHandleOnScroll(offset2d) : MoveSecondHandleOnScroll(offset2d);
}

void RichEditorScrollController::MoveCaretToContentRect(const RectF& caretRect)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern && !pattern->isShowPlaceholder_);
    auto caretOffset = caretRect.GetOffset();
    auto keyboardOffset = pattern->GetCrossOverHeight();
    MoveCaretToContentRectWithAxis(true, caretOffset, caretRect.Height(), keyboardOffset);
    MoveCaretToContentRectWithAxis(false, caretOffset, caretRect.Width());
}

void RichEditorScrollController::MoveCaretToContentRectWithAxis(
    bool isVertical, const OffsetF& caretOffset, float caretSize, float keyboardOffset)
{
    CHECK_NULL_VOID(NeedScroll(isVertical, keyboardOffset));
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    float distance = isVertical
        ? CalCaretToContentRectDistanceVertical(caretOffset, caretSize, keyboardOffset)
        : CalCaretToContentRectDistanceHorizontal(caretOffset, caretSize);
    PlayScrollBarAppearAnimation(axis);
    ScheduleDisappearDelayTask(axis);
    OnScrollWithAxisCallback(distance, SCROLL_FROM_NONE, axis);
}

void RichEditorScrollController::HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset)
{
    CHECK_NULL_VOID(prevAutoScrollOffset_ != offset);
    prevAutoScrollOffset_ = offset;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    auto safeAreaRect = GetSafeAreaRect(isDragging);
    auto point = PointF(offset.GetX(), offset.GetY());
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        point.SetY(offset.GetY() + param.handleRect.Height() / 2.0f);
    }
    if (safeAreaRect.IsInRegion(point)) {
        StopAutoScroll();
        return;
    }
    bool inHorizontalHotArea = Positive(safeAreaRect.Width())
        && (LessNotEqual(point.GetX(), safeAreaRect.Left()) || GreatNotEqual(point.GetX(), safeAreaRect.Right()));
    bool inVerticalHotArea = !isSingleLineMode_ && Positive(safeAreaRect.Height())
        && (LessNotEqual(point.GetY(), safeAreaRect.Top()) || GreatNotEqual(point.GetY(), safeAreaRect.Bottom()));
    if (inHorizontalHotArea && inVerticalHotArea) {
        HandleCornerScrolling(param, safeAreaRect, point);
    } else if (inHorizontalHotArea) {
        HandleInHorizontalHotArea(param, safeAreaRect, point);
    } else if (inVerticalHotArea) {
        HandleInVerticalHotArea(param, safeAreaRect, point);
    } else {
        StopAutoScroll();
        return;
    }
    ScheduleAutoScroll(param);
}

void RichEditorScrollController::HandleInHorizontalHotArea(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    param.axis = Axis::HORIZONTAL;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    if (GreatNotEqual(point.GetX(), safeAreaRect.Right())) {
        param.offset = isDragging ? -CalcDragSpeed(safeAreaRect.Right(), frameRect_.Width(), point.GetX())
            : safeAreaRect.Right() - point.GetX();
    } else if (LessNotEqual(point.GetX(), safeAreaRect.Left())) {
        param.offset = isDragging ? CalcDragSpeed(safeAreaRect.Left(), 0, point.GetX())
            : safeAreaRect.Left() - point.GetX();
    }
}

void RichEditorScrollController::HandleInVerticalHotArea(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    param.axis = Axis::VERTICAL;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    if (GreatNotEqual(point.GetY(), safeAreaRect.Bottom())) {
        param.offset = isDragging ? -CalcDragSpeed(safeAreaRect.Bottom(), frameRect_.Height(), point.GetY())
            : safeAreaRect.Bottom() - point.GetY();
    } else if (LessNotEqual(point.GetY(), safeAreaRect.Top())) {
        param.offset = isDragging ? CalcDragSpeed(safeAreaRect.Top(), 0, point.GetY())
            : safeAreaRect.Top() - point.GetY();
    }
}

void RichEditorScrollController::HandleCornerScrolling(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    // Four corners of the work rectangle (top-right, top-left, bottom-left, bottom-right)
    std::vector<PointF> corners = {
        PointF(safeAreaRect.Right(), safeAreaRect.Top()),
        PointF(safeAreaRect.Left(), safeAreaRect.Top()),
        PointF(safeAreaRect.Left(), safeAreaRect.Bottom()),
        PointF(safeAreaRect.Right(), safeAreaRect.Bottom())
    };
    // Map each corner to its starting index in ANGLE_RANGES
    constexpr size_t RANGES_PER_CORNER = 2;
    for (size_t cornerIndex = 0; cornerIndex < corners.size(); cornerIndex++) {
        float degree = CalculateAngle(corners[cornerIndex], point);
        for (size_t degreeIndex = 0; degreeIndex < RANGES_PER_CORNER; degreeIndex++) {
            const auto& range = ANGLE_RANGES[static_cast<size_t>(RANGE_INDEX_MAP[cornerIndex]) + degreeIndex];
            CHECK_NULL_CONTINUE(GreatOrEqual(degree, range.start) && LessNotEqual(degree, range.end));
            (range.direction == Axis::HORIZONTAL) ? HandleInHorizontalHotArea(param, safeAreaRect, point)
                : HandleInVerticalHotArea(param, safeAreaRect, point);
            return;
        }
    }
}

void RichEditorScrollController::ProcessAutoScroll()
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto param = currentScrollParam_;
    if (param.showScrollbar) {
        PlayScrollBarAppearAnimation(param.axis);
        param.showScrollbar = false;
    }
    CHECK_NULL_VOID(param.autoScrollEvent != AutoScrollEvent::NONE);
    auto newOffset = MoveTextRectWithAxis(param.offset, param.axis);
    switch (param.autoScrollEvent) {
        case AutoScrollEvent::CARET:
            break;
        case AutoScrollEvent::HANDLE: {
            MoveHandleOnScrollWithAxis(newOffset, !param.isFirstHandle, param.axis);
            pattern->selectOverlay_->OnHandleMove(param.handleRect, param.isFirstHandle);
            break;
        }
        case AutoScrollEvent::DRAG:
            break;
        case AutoScrollEvent::MOUSE:
            pattern->HandleMouseAutoScroll(param);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported auto scroll event type");
            return;
    }
    CHECK_NULL_VOID(!NearEqual(newOffset, 0.0f));
    ScheduleAutoScroll(param);
}

float RichEditorScrollController::CalculateAngle(const PointF& origin, const PointF& target)
{
    auto delta = target - origin;
    float radians = std::atan2(delta.GetY(), delta.GetX());
    float degrees = radians * PI_DEGREES / PI;
    degrees = std::fmod(degrees, TWO_PI_DEGREES);
    if (Negative(degrees)) {
        degrees += TWO_PI_DEGREES;
    }
    return degrees;
}

bool RichEditorScrollController::UpdateScrollState()
{
    bool hasUpdateTextOffsetY = UpdateVerticalScrollState();
    bool hasUpdateTextOffsetX = UpdateHorizontalScrollState();
    return hasUpdateTextOffsetY || hasUpdateTextOffsetX;
}

bool RichEditorScrollController::UpdateVerticalScrollState()
{
    auto hasTextOffsetChanged = false;
    bool needVerticalScroll = GreatNotEqual(textRect_.Height(), contentRect_.Height());
    if (GreatNotEqual(textRect_.GetY(), contentRect_.GetY())) {
        textRect_.SetTop(contentRect_.GetY());
        hasTextOffsetChanged = true;
    }
    if (needVerticalScroll && LessNotEqual(textRect_.Bottom(), contentRect_.Bottom())) {
        textRect_.SetTop(contentRect_.Bottom() - textRect_.Height());
        hasTextOffsetChanged = true;
    }
    if (!needVerticalScroll && LessNotEqual(textRect_.GetY(), contentRect_.GetY())) {
        textRect_.SetOffset(contentRect_.GetOffset());
        hasTextOffsetChanged = true;
    }
    return hasTextOffsetChanged;
}

bool RichEditorScrollController::UpdateHorizontalScrollState()
{
    CHECK_NULL_RETURN(IsFreeScrollEnabled(), false);
    bool needHorizontalScroll = NeedScroll(false);
    bool hasValidScroll = !needHorizontalScroll && LessNotEqual(textRect_.GetX(), contentRect_.GetX());
    CHECK_NULL_RETURN(hasValidScroll, false);
    textRect_.SetLeft(contentRect_.GetX());
    return true;
}

bool RichEditorScrollController::IsSupportHorizontalScroll()
{
    return isSingleLineMode_ || IsFreeScrollEnabled();
}

OffsetF RichEditorScrollController::CalculateDestination(int32_t start, int32_t end, bool isRTL)
{
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, OffsetF(0.0f, 0.0f));
    if (start == end) {
        float caretHeight = 0.0f;
        auto caretOffset = pattern->CalcCursorOffsetByPosition(start, caretHeight, true);
        return OffsetF(caretOffset.GetX(), caretOffset.GetY());
    }
    auto textBoxes = pattern->CalculateSelectedRect(start, end);
    CHECK_NULL_RETURN(!textBoxes.empty(), OffsetF(0.0f, 0.0f));
    float destX = isRTL ? textBoxes[0].Right() : textBoxes[0].Left();
    float destY = textBoxes[0].Top();
    for (const auto& rect : textBoxes) {
        destX = isRTL ? std::max(destX, rect.Right()) : std::min(destX, rect.Left());
        destY = std::min(destY, rect.Top());
    }
    return OffsetF(destX + textRect_.Left(), destY + textRect_.Top());
}

void RichEditorScrollController::ScrollToVisible(int32_t start, int32_t end)
{
    CHECK_NULL_VOID(end >= start);
    auto pattern = DynamicCast<RichEditorPattern>(weakPattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    StopScrolling();
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto destOffset = CalculateDestination(start, end, isRTL);
    auto contentEdgeX = isRTL ? contentRect_.Right() : contentRect_.Left();
    float distanceX = contentEdgeX - destOffset.GetX();
    float distanceY = contentRect_.Top() - destOffset.GetY();
    IF_TRUE(!isSingleLineMode_,
        OnScrollWithAxisCallback(distanceY, SCROLL_FROM_NONE, Axis::VERTICAL));
    IF_TRUE(IsSupportHorizontalScroll(), OnScrollWithAxisCallback(distanceX, SCROLL_FROM_NONE, Axis::HORIZONTAL));
    pattern->UpdateScrollBarOffset();
}
} // namespace OHOS::Ace::NG
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
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/base/observer_handler.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float MAX_DRAG_SCROLL_SPEED = 2400.0f;
constexpr int32_t AUTO_SCROLL_INTERVAL = 15;
constexpr float TIME_UNIT = 1000.0f;
constexpr Dimension AUTO_SCROLL_DRAG_EDGE_DIS = 58.0_vp;
constexpr Dimension AUTO_SCROLL_EDGE_DIS = 15.0_vp;
constexpr Dimension CARET_BOTTOM_DISTANCE = 16.0_vp;
constexpr Dimension MOUSE_SCROLL_BAR_REGION_WIDTH = 8.0_vp;

// Virtual border radius used to offset scrollbars from the edges to prevent overlap;
constexpr Dimension SCROLL_BAR_BORDER_RADIUS_SIZE = 20.0_vp;
}

// --- RichEditorScrollBar2D (dual-axis scrollbar wrapper) ---

RichEditorScrollBar2D::RichEditorScrollBar2D(const WeakPtr<ScrollablePattern>& pattern)
    : TextScrollBar2D(pattern) {}

void RichEditorScrollBar2D::SetMinHeight(const Dimension& height)
{
    ApplyToBars([&](const RefPtr<ScrollBar>& bar) { bar->SetMinHeight(height); });
}

void RichEditorScrollBar2D::SetColor(const Color& foregroundColor, const Color& backgroundColor)
{
    ApplyToBars([&](const RefPtr<ScrollBar>& bar) {
        bar->SetForegroundColor(foregroundColor);
        bar->SetBackgroundColor(backgroundColor);
    });
}

void RichEditorScrollBar2D::SetHostBorderRadius(const BorderRadiusProperty& radius)
{
    ApplyToBars([&](const RefPtr<ScrollBar>& bar) {
        bar->SetHostBorderRadius(radius);
        bar->CalcReservedHeight();
    });
}

bool RichEditorScrollBar2D::IsPointInScrollBar(const Point& point, const SizeF& frameSize) const
{
    return IsPointInScrollBar(point, frameSize, true)
        || IsPointInScrollBar(point, frameSize, false);
}

bool RichEditorScrollBar2D::IsPointInScrollBar(const Point& point, const SizeF& frameSize, bool isVertical) const
{
    auto scrollbar = isVertical ? GetVerticalBar() : GetHorizontalBar();
    CHECK_NULL_RETURN(scrollbar, false);
    if (!scrollbar->NeedPaint() || scrollbar->GetShapeMode() != ShapeMode::RECT) {
        return false;
    }
    auto barRect = scrollbar->GetBarRect();
    auto regionSize = MOUSE_SCROLL_BAR_REGION_WIDTH.ConvertToPx();
    if (isVertical) {
        barRect.SetLeft(barRect.Left() + barRect.Width() - regionSize);
        barRect.SetWidth(regionSize);
        barRect.SetHeight(frameSize.Height());
        barRect.SetTop(0.0f);
    } else {
        barRect.SetTop(barRect.Top() + barRect.Height() - regionSize);
        barRect.SetHeight(regionSize);
        barRect.SetWidth(frameSize.Width());
        barRect.SetLeft(0.0f);
    }
    return barRect.IsInRegion(point);
}

bool RichEditorScrollBar2D::IsPressedOrHovered() const
{
    auto verticalBar = GetVerticalBar();
    if (verticalBar && (verticalBar->IsPressed() || verticalBar->IsHover())) {
        return true;
    }
    auto horizontalBar = GetHorizontalBar();
    return horizontalBar && (horizontalBar->IsPressed() || horizontalBar->IsHover());
}

void RichEditorScrollBar2D::UpdateBars(const Color& barColor)
{
    UpdateBarAxis(true, barColor);
    UpdateBarAxis(false, barColor);
}

void RichEditorScrollBar2D::UpdateBarAxis(bool isVertical, const Color& barColor)
{
    auto modifier = isVertical ? GetVerticalModifier() : GetHorizontalModifier();
    auto bar = isVertical ? GetVerticalBar() : GetHorizontalBar();
    if (modifier && bar && bar->NeedPaint()) {
        modifier->StartBarAnimation(bar->GetHoverAnimationType(), bar->GetOpacityAnimationType(),
            bar->GetNeedAdaptAnimation(), bar->GetActiveRect());
        bar->SetHoverAnimationType(HoverAnimationType::NONE);
        modifier->SetBarColor(barColor);
        bar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    }
}

void RichEditorScrollBar2D::AttachPropertiesToModifier(const RefPtr<OverlayModifier>& modifier)
{
    auto verticalModifier = GetVerticalModifier();
    auto horizontalModifier = GetHorizontalModifier();
    CHECK_NULL_VOID(verticalModifier && horizontalModifier);
    for (const auto& scrollModifier : {verticalModifier, horizontalModifier}) {
        for (const auto& prop : scrollModifier->GetAttachedProperties()) {
            modifier->AttachProperty(prop);
        }
    }
}

void RichEditorScrollBar2D::DisableVerticalBar()
{
    SetVerticalScrollable(false);
    auto verticalModifier = GetVerticalModifier();
    CHECK_NULL_VOID(verticalModifier);
    verticalModifier->SetOpacity(0);
}

// --- ScrollGeometryEvaluator (pure rectangle math, no pattern/runtime deps) ---

bool ScrollGeometryEvaluator::IsReachTop() const
{
    return NearEqual(textRect_.GetY(), contentRect_.GetY());
}

bool ScrollGeometryEvaluator::IsReachBottom() const
{
    return NearEqual(textRect_.Bottom(), contentRect_.Bottom());
}

bool ScrollGeometryEvaluator::IsReachLeft() const
{
    return NearEqual(textRect_.GetX(), contentRect_.GetX());
}

bool ScrollGeometryEvaluator::IsReachRight() const
{
    return NearEqual(textRect_.Right(), contentRect_.Right());
}

bool ScrollGeometryEvaluator::IsReachLowerBoundary(bool isVertical) const
{
    return isVertical ? IsReachTop() : IsReachLeft();
}

bool ScrollGeometryEvaluator::IsReachUpperBoundary(bool isVertical) const
{
    return isVertical ? IsReachBottom() : IsReachRight();
}

bool ScrollGeometryEvaluator::IsReachBoundary(bool isVertical) const
{
    return IsReachLowerBoundary(isVertical) || IsReachUpperBoundary(isVertical);
}

bool ScrollGeometryEvaluator::IsReachAvoidBoundary(float offset, Axis axis, float keyboardOffset) const
{
    if (axis == Axis::HORIZONTAL) {
        return (IsReachLeft() && GreatNotEqual(offset, 0.0f)) || (IsReachRight() && LessNotEqual(offset, 0.0f));
    }
    return (IsReachTop() && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(textRect_.Bottom(), contentRect_.Bottom() - keyboardOffset) && LessNotEqual(offset, 0.0f));
}

bool ScrollGeometryEvaluator::NeedScroll(bool isVertical, float keyboardOffset) const
{
    if (isVertical) {
        return !isSingleLine_ && GreatNotEqual(textRect_.Height(), contentRect_.Height() - keyboardOffset);
    }
    return GreatNotEqual(textRect_.Width(), contentRect_.Width());
}

float ScrollGeometryEvaluator::ClampVerticalOffset(float offset, float keyboardOffset) const
{
    float visibleTop = contentRect_.GetY();
    float newTop = textRect_.GetY() + offset;
    if (GreatNotEqual(newTop, visibleTop)) {
        return visibleTop - textRect_.GetY();
    }
    float visibleBottom = contentRect_.Bottom() - keyboardOffset;
    float newBottom = textRect_.Bottom() + offset;
    if (LessNotEqual(newBottom, visibleBottom)) {
        return visibleBottom - textRect_.Bottom();
    }
    return offset;
}

float ScrollGeometryEvaluator::ClampHorizontalOffset(float offset) const
{
    CHECK_NULL_RETURN(offset != 0.0f, offset);
    return offset > 0
        ? std::min(offset, contentRect_.GetX() - textRect_.GetX())
        : std::max(offset, contentRect_.Right() - textRect_.Right());
}

bool ScrollGeometryEvaluator::IsScrollDirectionValid(bool isVertical) const
{
    return !(isVertical && isSingleLine_);
}

bool ScrollGeometryEvaluator::IsHotAreaOverflow(bool isDragging, float edgeThreshold) const
{
    auto maxHeight = isDragging ? frameRect_.Height() : contentRect_.Height();
    auto maxWidth = isDragging ? frameRect_.Width() : contentRect_.Width();
    auto doubleThreshold = edgeThreshold * 2;
    return isSingleLine_ ? GreatNotEqual(doubleThreshold, maxWidth) : GreatNotEqual(doubleThreshold, maxHeight);
}

OffsetF ScrollGeometryEvaluator::GetOffset2d(float offset, bool isVertical)
{
    float offsetX = isVertical ? 0.0f : offset;
    float offsetY = isVertical ? offset : 0.0f;
    return { offsetX, offsetY };
}

RectF ScrollGeometryEvaluator::GetSafeAreaRect(bool isDragging) const
{
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DIS.ConvertToPx() : AUTO_SCROLL_EDGE_DIS.ConvertToPx();
    return RectF(
        isDragging ? edgeThreshold : contentRect_.GetX() + edgeThreshold,
        isDragging ? edgeThreshold : contentRect_.GetY() + edgeThreshold,
        (isDragging ? frameRect_.Width() : contentRect_.Width()) - 2.0f * edgeThreshold,
        (isDragging ? frameRect_.Height() : contentRect_.Height()) - 2.0f * edgeThreshold
    );
}

float ScrollGeometryEvaluator::CalCaretToContentRectDistanceVertical(
    const OffsetF& caretOffset, float caretHeight, float keyboardOffset) const
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

float ScrollGeometryEvaluator::CalCaretToContentRectDistanceHorizontal(
    const OffsetF& caretOffset, float caretWidth) const
{
    float caretLeft = caretOffset.GetX();
    float caretRight = caretOffset.GetX() + caretWidth;
    float distanceLeft = std::max(contentRect_.Left() - caretLeft, 0.0f);
    float distanceRight = std::min(contentRect_.Right() - caretRight, 0.0f);
    return distanceLeft + distanceRight;
}

float ScrollGeometryEvaluator::CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point)
{
    CHECK_NULL_RETURN(hotAreaStart != hotAreaEnd, 0.0f);
    auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
    auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
    return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * AUTO_SCROLL_INTERVAL;
}

RefPtr<RichEditorScrollController> RichEditorScrollController::Create(bool isFree, RichEditorPattern* pattern)
{
    if (isFree) {
        return MakeRefPtr<RichEditorFreeScrollController>(pattern);
    }
    return MakeRefPtr<RichEditorFixedScrollController>(pattern);
}

// --- RichEditorScrollController (base class — shared implementations) ---

// --- AutoScrollScheduler (timer task + dispatch state, decoupled via callbacks) ---

void AutoScrollScheduler::Schedule(AutoScrollParam param, bool isSingleLine, const RefPtr<TaskExecutor>& taskExecutor)
{
    bool isVertical = (param.axis == Axis::NONE) ? !isSingleLine : param.axis == Axis::VERTICAL;
    bool aboutToBeyondLower = reachLower_(isVertical) && GreatNotEqual(param.offset, 0.0f);
    bool aboutToBeyondUpper = reachUpper_(isVertical) && LessNotEqual(param.offset, 0.0f);
    CHECK_NULL_VOID(!aboutToBeyondLower && !aboutToBeyondUpper);

    CHECK_NULL_VOID(taskExecutor);
    if (param.isFirstRun_) {
        param.isFirstRun_ = false;
        currentScrollParam_ = param;
        CHECK_NULL_VOID(!isAutoScrollRunning_);
    }
    // Only weakScheduler captured: scheduler lifetime ≤ controller ≤ pattern, so no separate pattern ref needed.
    autoScrollTask_.Reset([weakScheduler = WeakClaim(this), isVertical]() {
        auto scheduler = weakScheduler.Upgrade();
        CHECK_NULL_VOID(scheduler);
        scheduler->onAutoScrollStep_();
        if (scheduler->reachLower_(isVertical) || scheduler->reachUpper_(isVertical)) {
            scheduler->Stop();
        }
    });
    isAutoScrollRunning_ = true;
    taskExecutor->PostDelayedTask(autoScrollTask_, TaskExecutor::TaskType::UI, AUTO_SCROLL_INTERVAL,
        "ArkUIRichEditorScheduleAutoScroll");
}

void AutoScrollScheduler::Stop()
{
    isAutoScrollRunning_ = false;
    autoScrollTask_.Cancel();
    onAutoScrollStop_();
}

RefPtr<AutoScrollScheduler> RichEditorScrollController::CreateAutoScrollScheduler()
{
    auto weak = AceType::WeakClaim(this);
    auto* geometryEvaluator = &geometryEvaluator_;
    return MakeRefPtr<AutoScrollScheduler>(
        [weak]() {
            auto controller = weak.Upgrade();
            CHECK_NULL_VOID(controller);
            controller->DoAutoScrollStep();
        },
        [weak]() {
            auto controller = weak.Upgrade();
            CHECK_NULL_VOID(controller);
            controller->ScheduleDisappearDelayTask();
        },
        [geometryEvaluator](bool isVertical) {
            CHECK_NULL_RETURN(geometryEvaluator, false);
            return geometryEvaluator->IsReachLowerBoundary(isVertical);
        },
        [geometryEvaluator](bool isVertical) {
            CHECK_NULL_RETURN(geometryEvaluator, false);
            return geometryEvaluator->IsReachUpperBoundary(isVertical);
        });
}

RichEditorScrollController::RichEditorScrollController(RichEditorPattern* pattern)
    : weakPattern_(AceType::WeakClaim(pattern)),
      isSingleLineMode_(pattern->isSingleLineMode_),
      contentRect_(pattern->contentRect_),
      textRect_(pattern->richTextRect_),
      frameRect_(pattern->frameRect_),
      selectOverlay_(pattern->selectOverlay_),
      textSelector_(pattern->textSelector_),
      geometryEvaluator_(contentRect_, textRect_, frameRect_, isSingleLineMode_),
      autoScrollScheduler_(CreateAutoScrollScheduler())
{}

void RichEditorScrollController::ScheduleAutoScroll(AutoScrollParam param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    autoScrollScheduler_->Schedule(std::move(param), isSingleLineMode_, taskExecutor);
}

void RichEditorScrollController::StopAutoScroll()
{
    prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
    autoScrollScheduler_->Stop();
}

void RichEditorScrollController::Dispose()
{
    // Not a destructor: StopScrolling() is virtual and must dispatch on a live object.
    StopAutoScroll();
    StopScrolling();
}

void RichEditorScrollController::DoAutoScrollStep()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto param = autoScrollScheduler_->CurrentParam();
    if (param.showScrollbar) {
        PlayScrollBarAppearAnimation(param.axis);
        param.showScrollbar = false;
    }
    CHECK_NULL_VOID(param.autoScrollEvent != AutoScrollEvent::NONE);
    auto newOffset = MoveTextRectForAutoScroll(param.offset, param.axis);
    switch (param.autoScrollEvent) {
        case AutoScrollEvent::CARET:
            break;
        case AutoScrollEvent::HANDLE: {
            Axis handleAxis = IsFreeScrollEnabled() ? param.axis
                : (isSingleLineMode_ ? Axis::HORIZONTAL : Axis::VERTICAL);
            MoveHandleWithAxisOnScroll(newOffset, !param.isFirstHandle, handleAxis);
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

void RichEditorScrollController::MoveHandleOnScroll(const OffsetF& offset, bool isFirst)
{
    if (isFirst) {
        textSelector_.selectionBaseOffset += offset;
    } else {
        textSelector_.selectionDestinationOffset += offset;
    }
    auto& handle = isFirst ? textSelector_.firstHandle : textSelector_.secondHandle;
    auto handleOffset = handle.GetOffset();
    handleOffset += offset;
    handle.SetOffset(handleOffset);
    isFirst ? selectOverlay_->UpdateFirstHandleOffset()
            : selectOverlay_->UpdateSecondHandleOffset();
}

void RichEditorScrollController::MoveHandlesOnScroll(float offset, Axis axis)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    bool isVertical = (axis == Axis::VERTICAL);
    OffsetF offset2d = ScrollGeometryEvaluator::GetOffset2d(offset, isVertical);
    MoveHandleOnScroll(offset2d, true);
    MoveHandleOnScroll(offset2d, false);
}

void RichEditorScrollController::MoveHandleWithAxisOnScroll(float offset, bool isFirst, Axis axis)
{
    CHECK_NULL_VOID(!NearEqual(offset, 0.0f) && selectOverlay_->SelectOverlayIsOn());
    bool isVertical = (axis == Axis::VERTICAL);
    OffsetF offset2d = ScrollGeometryEvaluator::GetOffset2d(offset, isVertical);
    MoveHandleOnScroll(offset2d, isFirst);
}

float RichEditorScrollController::MoveTextRectHorizontal(float offset)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveTextRectHorizontal, offsetIn=%{public}f, textWidth=%{public}f, "
        "contentWidth=%{public}f", offset, textRect_.Width(), contentRect_.Width());
    offset = geometryEvaluator_.NeedScroll(false)
        ? geometryEvaluator_.ClampHorizontalOffset(offset)
        : contentRect_.GetX() - textRect_.GetX();
    scrollOffset_ = textRect_.GetX() + offset;
    textRect_.SetOffset(OffsetF(scrollOffset_, textRect_.GetY()));
    return offset;
}

float RichEditorScrollController::MoveTextRectVertical(float offset, float keyboardOffset)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveTextRectVertical, offsetIn=%{public}f, textHeight=%{public}f, "
        "contentHeight=%{public}f", offset, textRect_.Height(), contentRect_.Height());
    offset = geometryEvaluator_.NeedScroll(true, keyboardOffset)
        ? geometryEvaluator_.ClampVerticalOffset(offset, keyboardOffset)
        : contentRect_.GetY() - textRect_.GetY();
    if (NearEqual(offset, 0.0f)) {
        return offset;
    }
    scrollOffset_ = textRect_.GetY() + offset;
    textRect_.SetOffset(OffsetF(textRect_.GetX(), scrollOffset_));
    return offset;
}

float RichEditorScrollController::GetScrollOffset() const
{
    return scrollOffset_;
}

void RichEditorScrollController::HandleScrollStart()
{
    if (selectOverlay_->SelectOverlayIsOn()) {
        selectOverlay_->HideMenu(true);
    }
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->CloseAIMenu();
#ifndef CROSS_PLATFORM
    pattern->RecordScrollEvent(Recorder::EventType::SCROLL_START);
#endif
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        weakPattern_, ScrollEventType::SCROLL_START);
}

void RichEditorScrollController::UpdateScrollBarColor(std::optional<Color> color, bool isUpdateProperty)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto property = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    IF_TRUE(isUpdateProperty && property, property->UpdateScrollBarColor(color));
    auto scrollbarTheme = pattern->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollbarTheme);
    auto foregroundColor = color.value_or(scrollbarTheme->GetForegroundColor());
    auto backgroundColor = scrollbarTheme->GetBackgroundColor();
    UpdateScrollBarColor(foregroundColor, backgroundColor);
}

float RichEditorScrollController::MoveTextRectWithAxis(float offset, Axis axis, float keyboardOffset)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern && geometryEvaluator_.IsScrollDirectionValid(axis == Axis::VERTICAL), 0.0f);
    offset = (axis == Axis::HORIZONTAL) ? MoveTextRectHorizontal(offset)
                                       : MoveTextRectVertical(offset, keyboardOffset);
    UpdateScrollBarOffsetWithAxis(axis);
    pattern->UpdateChildrenOffset();
    if (auto host = pattern->GetContentHost(); host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    return offset;
}

bool RichEditorScrollController::UpdateScrollState()
{
    bool hasUpdateTextOffsetY = UpdateVerticalScrollState();
    bool hasUpdateTextOffsetX = UpdateHorizontalScrollState();
    return hasUpdateTextOffsetY || hasUpdateTextOffsetX;
}

bool RichEditorScrollController::UpdateVerticalScrollState()
{
    if (GreatNotEqual(textRect_.GetY(), contentRect_.GetY())) {
        textRect_.SetTop(contentRect_.GetY());
        return true;
    }
    bool needVerticalScroll = GreatNotEqual(textRect_.Height(), contentRect_.Height());
    if (needVerticalScroll && LessNotEqual(textRect_.Bottom(), contentRect_.Bottom())) {
        textRect_.SetTop(contentRect_.Bottom() - textRect_.Height());
        return true;
    }
    if (!needVerticalScroll && LessNotEqual(textRect_.GetY(), contentRect_.GetY())) {
        textRect_.SetOffset(contentRect_.GetOffset());
        return true;
    }
    return false;
}

bool RichEditorScrollController::UpdateHorizontalScrollState()
{
    CHECK_NULL_RETURN(IsFreeScrollEnabled(), false);
    bool needHorizontalScroll = geometryEvaluator_.NeedScroll(false);
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
    auto pattern = weakPattern_.Upgrade();
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
    auto pattern = weakPattern_.Upgrade();
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

void RichEditorScrollController::InitScrollBar(DisplayMode barMode)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    SetScrollBar(barMode);
    UpdateScrollBarColor(pattern->GetScrollBarColor());
    auto richEditorTheme = pattern->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    SetMinHeight(richEditorTheme->GetScrollbarMinHeight());
}

// --- RichEditorFixedScrollController (fixed direction scroll strategy) ---

RichEditorFixedScrollController::RichEditorFixedScrollController(RichEditorPattern* pattern)
    : RichEditorScrollController(pattern)
{}

void RichEditorFixedScrollController::ScheduleDisappearDelayTask()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    IF_PRESENT(scrollBar, ScheduleDisappearDelayTask());
}

void RichEditorFixedScrollController::StopScrolling()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StopScrollable();
}

bool RichEditorFixedScrollController::IsMouseOverScrollBar(const MouseInfo& info)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto scrollBar = pattern->GetScrollBar();
    CHECK_NULL_RETURN(scrollBar, false);
    return (scrollBar->IsHover() || scrollBar->IsPressed());
}

void RichEditorFixedScrollController::UpdateScrollBarOffset()
{
    auto pattern = weakPattern_.Upgrade();
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

void RichEditorFixedScrollController::MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight)
{
    isSingleLineMode_ ? MoveCaretToContentRectHorizontal(caretOffset)
                      : MoveCaretToContentRectVertical(caretOffset, caretHeight);
}

// FixedScroll single-axis scroll: axis is unused -- direction determined by isSingleLineMode_.
bool RichEditorFixedScrollController::OnScrollWithAxisCallback(float offset, int32_t source, Axis axis)
{
    CHECK_NULL_RETURN(offset != 0, false);
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto scrollBar = pattern->GetScrollBar();
    if (source == SCROLL_FROM_START) {
        IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
        HandleScrollStart();
        return true;
    }
    auto scrollAxis = isSingleLineMode_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    float keyboardOffset = (scrollAxis == Axis::VERTICAL) ? pattern->GetCrossOverHeight() : 0.0f;
    if (geometryEvaluator_.IsReachAvoidBoundary(offset, scrollAxis, keyboardOffset)) {
        return false;
    }
    if (scrollBar && source == SCROLL_FROM_JUMP) {
        scrollBar->PlayScrollBarAppearAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
    auto newOffset = MoveTextRect(offset, keyboardOffset);
    MoveHandlesOnScroll(newOffset, scrollAxis);
    pattern->ClearAISpanRects();
    return true;
}

void RichEditorFixedScrollController::MoveCaretToContentRectHorizontal(const OffsetF& caretOffset)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveCaretToContentRect Horizontal");
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (LessOrEqual(textRect_.Width(), contentRect_.Width()) || pattern->isShowPlaceholder_) {
        return;
    }
    auto caretWidth = pattern->GetOverlayCaretWidth();
    float distance = geometryEvaluator_.CalCaretToContentRectDistanceHorizontal(caretOffset, caretWidth);
    OnScrollWithAxisCallback(distance, SCROLL_FROM_NONE, Axis::HORIZONTAL);
}

void RichEditorFixedScrollController::MoveCaretToContentRectVertical(const OffsetF& caretOffset, float caretHeight)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "MoveCaretToContentRect Vertical");
    auto pattern = weakPattern_.Upgrade();
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
    float distance = geometryEvaluator_.CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    OnScrollWithAxisCallback(distance, SCROLL_FROM_NONE, Axis::VERTICAL);
}

void RichEditorFixedScrollController::AutoScrollForHandleEvent(
    AutoScrollParam& param, const ScrollBoundaryGeometry& geometry)
{
    if (GreatNotEqual(geometry.handleUpper, geometry.upperThreshold)) {
        param.offset = geometry.upperThreshold - geometry.handleUpper;
        ScheduleAutoScroll(param);
        return;
    }
    if (LessNotEqual(geometry.handleLower, geometry.lowerThreshold)) {
        param.offset = geometry.lowerThreshold - geometry.handleLower;
        ScheduleAutoScroll(param);
        return;
    }
    StopAutoScroll();
}

void RichEditorFixedScrollController::AutoScrollForDragEvent(
    AutoScrollParam& param, const ScrollBoundaryGeometry& geometry, bool isDragging)
{
    if (GreatNotEqual(geometry.handleLower, geometry.upperThreshold)) {
        auto frameRectLen = isSingleLineMode_ ? frameRect_.Width() : frameRect_.Height();
        param.offset = isDragging
            ? -ScrollGeometryEvaluator::CalcDragSpeed(geometry.upperThreshold, frameRectLen, geometry.handleLower)
            : geometry.upperThreshold - geometry.handleLower;
        ScheduleAutoScroll(param);
        return;
    }
    if (LessNotEqual(geometry.handleLower, geometry.lowerThreshold)) {
        param.offset = isDragging
            ? ScrollGeometryEvaluator::CalcDragSpeed(geometry.lowerThreshold, 0, geometry.handleLower)
            : geometry.lowerThreshold - geometry.handleLower;
        ScheduleAutoScroll(param);
        return;
    }
    StopAutoScroll();
}

void RichEditorFixedScrollController::HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset)
{
    auto scrollOffsetDiff = GetAutoScrollOffsetDiff(offset);
    CHECK_NULL_VOID(!NearZero(scrollOffsetDiff));
    prevAutoScrollOffset_ = offset;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DIS.ConvertToPx() : AUTO_SCROLL_EDGE_DIS.ConvertToPx();
    if (geometryEvaluator_.IsHotAreaOverflow(isDragging, edgeThreshold)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleAutoScrollNearBoundary: hot area height is great than max height.");
        return;
    }
    auto safeAreaRect = geometryEvaluator_.GetSafeAreaRect(isDragging);
    RectF handleRect{ offset, param.handleRect.GetSize() };
    ScrollBoundaryGeometry geometry(!isSingleLineMode_, safeAreaRect, handleRect);
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        AutoScrollForHandleEvent(param, geometry);
        return;
    }
    AutoScrollForDragEvent(param, geometry, isDragging);
}

void RichEditorFixedScrollController::SetScrollBar(DisplayMode displayMode)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    // In single-line mode, disable scrollbar (horizontal-only)
    pattern->SetScrollBar(isSingleLineMode_ ? DisplayMode::OFF : displayMode);
}

void RichEditorFixedScrollController::SetMinHeight(const Dimension& height)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    scrollBar->SetMinHeight(height);
}

void RichEditorFixedScrollController::CheckScrollEnabled()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gestureHub = pattern->GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    bool scrollable = pattern->GetTextContentLength() > 0 && geometryEvaluator_.NeedScroll(!isSingleLineMode_);
    pattern->SetScrollable(scrollable);
    pattern->SetScrollEnabled(scrollable);
}

void RichEditorFixedScrollController::UpdateScrollBarColor(
    const Color& foregroundColor, const Color& backgroundColor)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    scrollBar->SetForegroundColor(foregroundColor);
    scrollBar->SetBackgroundColor(backgroundColor);
}

float RichEditorFixedScrollController::GetAutoScrollOffsetDiff(const OffsetF& offset)
{
    return isSingleLineMode_
        ? prevAutoScrollOffset_.GetX() - offset.GetX()
        : prevAutoScrollOffset_.GetY() - offset.GetY();
}

float RichEditorFixedScrollController::MoveTextRect(float offset, float keyboardOffset)
{
    offset = isSingleLineMode_ ? MoveTextRectHorizontal(offset) : MoveTextRectVertical(offset, keyboardOffset);
    UpdateScrollBarOffset();
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, offset);
    pattern->UpdateChildrenOffset();
    if (auto host = pattern->GetContentHost(); host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    return offset;
}

void RichEditorFixedScrollController::PlayScrollBarAppearAnimation(Axis axis)
{
    // FixedScroll plays the single-axis bar's appear animation; axis param unused.
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
}

float RichEditorFixedScrollController::MoveTextRectForAutoScroll(float offset, Axis axis)
{
    // FixedScroll derives axis internally from isSingleLineMode_.
    auto pattern = weakPattern_.Upgrade();
    float keyboardOffset = pattern ? pattern->GetCrossOverHeight() : 0.0f;
    return MoveTextRect(offset, keyboardOffset);
}

// --- RichEditorFreeScrollController (dual-axis free scroll strategy) ---

RichEditorFreeScrollController::RichEditorFreeScrollController(RichEditorPattern* pattern)
    : RichEditorScrollController(pattern), boundaryScrollResolver_(frameRect_)
{
    InitFreeScrollController();
}

RichEditorFreeScrollController::~RichEditorFreeScrollController()
{
    IF_PRESENT(freeScrollController_, StopAllScrollAnimation());
}

void RichEditorFreeScrollController::ScheduleDisappearDelayTask()
{
    if (scrollingAxis_ != Axis::NONE) {
        ScheduleDisappearDelayTask(scrollingAxis_);
        return;
    }
    ScheduleDisappearDelayTask(Axis::VERTICAL);
    ScheduleDisappearDelayTask(Axis::HORIZONTAL);
}

void RichEditorFreeScrollController::StopScrolling()
{
    CHECK_NULL_VOID(freeScrollController_);
    freeScrollController_->StopAllScrollAnimation();
}

bool RichEditorFreeScrollController::IsMouseOverScrollBar(const MouseInfo& info)
{
    CHECK_NULL_RETURN(scrollBar_, false);
    // Check cheap pointer-state flags first; skip geometry work if any bar is engaged.
    if (scrollBar_->IsPressedOrHovered()) {
        return true;
    }
    auto point = Point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
    auto frameSize = SizeF(frameRect_.Width(), frameRect_.Height());
    return scrollBar_->IsPointInScrollBar(point, frameSize);
}

void RichEditorFreeScrollController::UpdateScrollBarOffset()
{
    UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, (scrollingAxis_ != Axis::HORIZONTAL));
    UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, (scrollingAxis_ != Axis::VERTICAL));
}

void RichEditorFreeScrollController::MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto caretWidth = pattern->GetOverlayCaretWidth();
    auto caretRect = RectF(caretOffset, SizeF(caretWidth, caretHeight));
    MoveCaretToContentRect(caretRect);
}

void RichEditorFreeScrollController::OnDrawScrollBar(DrawingContext& context, const RefPtr<OverlayModifier>& modifier)
{
    if (scrollBar_) {
        scrollBar_->OnDraw(context, modifier);
    }
}

void RichEditorFreeScrollController::CheckScrollEnabled()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto gestureHub = pattern->GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    bool needVerticalScroll = geometryEvaluator_.NeedScroll(true);
    bool needHorizontalScroll = geometryEvaluator_.NeedScroll(false);
    auto enabled = pattern->GetTextContentLength() > 0 && (needVerticalScroll || needHorizontalScroll);
    // Restore pattern flags so IsScrollable()/SetScrollEnabled() reflect actual scroll need after caret move.
    pattern->SetScrollable(enabled);
    pattern->SetScrollEnabled(enabled);
    if (freeScrollController_) {
        freeScrollController_->SetScrollEnabled(enabled);
    }
    if (scrollBar_) {
        scrollBar_->SetScrollbarEnabled(enabled);
    }
}

void RichEditorFreeScrollController::SetScrollBar(DisplayMode displayMode)
{
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            scrollBar_.Reset();
        }
        isScrollBarModifierPropertyAttached_ = false;
        return;
    }
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    DisplayMode oldMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = MakeRefPtr<RichEditorScrollBar2D>(WeakPtr<RichEditorPattern>(pattern));
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
    IF_TRUE(isSingleLineMode_, scrollBar_->DisableVerticalBar());
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    scrollBar_->SetPositionMode(isRTL ? PositionMode::LEFT : PositionMode::RIGHT);
    UpdateBorderRadius();
    RegisterScrollBarCallbacks();
}

void RichEditorFreeScrollController::RegisterScrollBarCallbacks()
{
    CHECK_NULL_VOID(scrollBar_);
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

void RichEditorFreeScrollController::UpdateScrollBar()
{
    CHECK_NULL_VOID(scrollBar_);
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    scrollBar_->UpdateBars(pattern->GetScrollBarColor());
}

void RichEditorFreeScrollController::SetMinHeight(const Dimension& height)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->SetMinHeight(height);
}

bool RichEditorFreeScrollController::IsAttachedModifier() const
{
    return isScrollBarModifierPropertyAttached_;
}

bool RichEditorFreeScrollController::OnScrollWithAxisCallback(float offset, int32_t source, Axis axis)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    if (source == SCROLL_FROM_START) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Scroll start with axis:%{public}d", axis);
        scrollingAxis_ = axis;
        PlayScrollBarAppearAnimation(axis);
        HandleScrollStart();
        return true;
    }
    float keyboardOffset = (axis == Axis::VERTICAL) ? pattern->GetCrossOverHeight() : 0.0f;
    CHECK_NULL_RETURN(offset != 0 && !geometryEvaluator_.IsReachAvoidBoundary(offset, axis, keyboardOffset), false);
    if (source == SCROLL_FROM_JUMP) {
        PlayScrollBarAppearAnimation(axis);
        ScheduleDisappearDelayTask(axis);
    }
    auto newOffset = MoveTextRectWithAxis(offset, axis, keyboardOffset);
    MoveHandlesOnScroll(newOffset, axis);
    pattern->ClearAISpanRects();
    return true;
}

void RichEditorFreeScrollController::HandleAutoScrollNearBoundary(AutoScrollParam param, OffsetF offset)
{
    CHECK_NULL_VOID(prevAutoScrollOffset_ != offset);
    prevAutoScrollOffset_ = offset;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    auto safeAreaRect = geometryEvaluator_.GetSafeAreaRect(isDragging);
    auto point = PointF(offset.GetX(), offset.GetY());
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        point.SetY(offset.GetY() + param.handleRect.Height() / 2.0f);
    }
    bool shouldStopScrolling = safeAreaRect.IsInRegion(point)
        || !boundaryScrollResolver_.ResolveBoundaryScroll(param, safeAreaRect, point, isSingleLineMode_);
    if (shouldStopScrolling) {
        StopAutoScroll();
        return;
    }
    ScheduleAutoScroll(param);
}

RefPtr<NGGestureRecognizer> RichEditorFreeScrollController::GetScrollGestureRecognizer() const
{
    return freeScrollController_ ? freeScrollController_->GetGestureRecognizer() : nullptr;
}

void RichEditorFreeScrollController::UpdateScrollBarColor(const Color& foregroundColor, const Color& backgroundColor)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->SetColor(foregroundColor, backgroundColor);
}

void RichEditorFreeScrollController::AttachModifier(const RefPtr<OverlayModifier>& modifier)
{
    CHECK_NULL_VOID(!isScrollBarModifierPropertyAttached_);
    CHECK_NULL_VOID(modifier && scrollBar_);
    scrollBar_->AttachPropertiesToModifier(modifier);
    isScrollBarModifierPropertyAttached_ = true;
}

void RichEditorFreeScrollController::ResetFreeScrollController()
{
    freeScrollController_.Reset();
    scrollBar_.Reset();
}

void RichEditorFreeScrollController::InitFreeScrollController(bool forceRecreate)
{
    if (freeScrollController_ && forceRecreate) {
        ResetFreeScrollController();
    }
    CHECK_NULL_VOID(!freeScrollController_);
    auto richEditorPattern = weakPattern_.Upgrade();
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

void RichEditorFreeScrollController::ScheduleDisappearDelayTask(Axis axis)
{
    bool isVertical = axis == Axis::VERTICAL;
    CHECK_NULL_VOID(scrollBar_ && geometryEvaluator_.IsScrollDirectionValid(isVertical));
    scrollBar_->ScheduleDisappearDelayTask(isVertical);
}

void RichEditorFreeScrollController::PlayScrollBarAppearAnimation(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    scrollBar_->PlayAppearAnimation(axis == Axis::VERTICAL);
}

void RichEditorFreeScrollController::HandleScrollCallback(float offset, int32_t source, bool isVertical)
{
    CHECK_NULL_VOID(geometryEvaluator_.IsScrollDirectionValid(isVertical));
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    OnScrollWithAxisCallback(offset, source, axis);
    SyncOffset();
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    float keyboardOffset = pattern->GetCrossOverHeight();
    bool needStopScroll = (source != SCROLL_FROM_START)
        && geometryEvaluator_.IsReachAvoidBoundary(offset, axis, keyboardOffset);
    if (needStopScroll) {
        freeScrollController_->StopScrollAnimation(isVertical);
    }
}

void RichEditorFreeScrollController::HandleEndScrollCallback(bool isVertical)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleEndScrollCallback");
    scrollingAxis_ = Axis::NONE;
    CHECK_NULL_VOID(geometryEvaluator_.IsScrollDirectionValid(isVertical));
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    ScheduleDisappearDelayTask(axis);
    pattern->OnScrollEndCallback();
}

void RichEditorFreeScrollController::SyncOffset()
{
    IF_PRESENT(freeScrollController_, UpdateCurrentOffset(textRect_.GetOffset()));
}

float RichEditorFreeScrollController::MoveTextRectForAutoScroll(float offset, Axis axis)
{
    auto pattern = weakPattern_.Upgrade();
    float keyboardOffset = pattern ? pattern->GetCrossOverHeight() : 0.0f;
    return MoveTextRectWithAxis(offset, axis, keyboardOffset);
}

bool BoundaryScrollResolver::ResolveBoundaryScroll(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point, bool isSingleLineMode)
{
    bool inHorizontalHotArea = IsInHorizontalHotArea(safeAreaRect, point);
    bool inVerticalHotArea = !isSingleLineMode && IsInVerticalHotArea(safeAreaRect, point);
    if (!inHorizontalHotArea && !inVerticalHotArea) {
        return false;
    }
    if (inHorizontalHotArea && inVerticalHotArea) {
        HandleCornerScrolling(param, safeAreaRect, point);
        return true;
    }
    if (inHorizontalHotArea) {
        HandleInHorizontalHotArea(param, safeAreaRect, point);
        return true;
    }
    HandleInVerticalHotArea(param, safeAreaRect, point);
    return true;
}

bool BoundaryScrollResolver::IsInHorizontalHotArea(const RectF& safeAreaRect, const PointF& point)
{
    return Positive(safeAreaRect.Width())
        && (LessNotEqual(point.GetX(), safeAreaRect.Left()) || GreatNotEqual(point.GetX(), safeAreaRect.Right()));
}

bool BoundaryScrollResolver::IsInVerticalHotArea(const RectF& safeAreaRect, const PointF& point)
{
    return Positive(safeAreaRect.Height())
        && (LessNotEqual(point.GetY(), safeAreaRect.Top()) || GreatNotEqual(point.GetY(), safeAreaRect.Bottom()));
}

void BoundaryScrollResolver::HandleInHorizontalHotArea(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    param.axis = Axis::HORIZONTAL;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    if (GreatNotEqual(point.GetX(), safeAreaRect.Right())) {
        param.offset = isDragging
            ? -ScrollGeometryEvaluator::CalcDragSpeed(safeAreaRect.Right(), frameRect_.Width(), point.GetX())
            : safeAreaRect.Right() - point.GetX();
    } else if (LessNotEqual(point.GetX(), safeAreaRect.Left())) {
        param.offset = isDragging ? ScrollGeometryEvaluator::CalcDragSpeed(safeAreaRect.Left(), 0, point.GetX())
            : safeAreaRect.Left() - point.GetX();
    }
}

void BoundaryScrollResolver::HandleInVerticalHotArea(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    param.axis = Axis::VERTICAL;
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    if (GreatNotEqual(point.GetY(), safeAreaRect.Bottom())) {
        param.offset = isDragging
            ? -ScrollGeometryEvaluator::CalcDragSpeed(safeAreaRect.Bottom(), frameRect_.Height(), point.GetY())
            : safeAreaRect.Bottom() - point.GetY();
    } else if (LessNotEqual(point.GetY(), safeAreaRect.Top())) {
        param.offset = isDragging ? ScrollGeometryEvaluator::CalcDragSpeed(safeAreaRect.Top(), 0, point.GetY())
            : safeAreaRect.Top() - point.GetY();
    }
}

void BoundaryScrollResolver::HandleCornerScrolling(AutoScrollParam& param, const RectF& safeAreaRect,
    const PointF& point)
{
    float horizontalBeyond = CalcHorizontalBeyond(safeAreaRect, point);
    float verticalBeyond = CalcVerticalBeyond(safeAreaRect, point);
    if (!Positive(horizontalBeyond) || !Positive(verticalBeyond)) {
        return;
    }
    if (GreatNotEqual(horizontalBeyond, verticalBeyond)) {
        HandleInHorizontalHotArea(param, safeAreaRect, point);
    } else {
        HandleInVerticalHotArea(param, safeAreaRect, point);
    }
}

float BoundaryScrollResolver::CalcHorizontalBeyond(const RectF& safeAreaRect, const PointF& point)
{
    if (GreatNotEqual(point.GetX(), safeAreaRect.Right())) {
        return point.GetX() - safeAreaRect.Right();
    }
    if (LessNotEqual(point.GetX(), safeAreaRect.Left())) {
        return safeAreaRect.Left() - point.GetX();
    }
    return 0.0f;
}

float BoundaryScrollResolver::CalcVerticalBeyond(const RectF& safeAreaRect, const PointF& point)
{
    if (GreatNotEqual(point.GetY(), safeAreaRect.Bottom())) {
        return point.GetY() - safeAreaRect.Bottom();
    }
    if (LessNotEqual(point.GetY(), safeAreaRect.Top())) {
        return safeAreaRect.Top() - point.GetY();
    }
    return 0.0f;
}

void RichEditorFreeScrollController::MoveCaretToContentRect(const RectF& caretRect)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern && !pattern->isShowPlaceholder_);
    auto caretOffset = caretRect.GetOffset();
    auto keyboardOffset = pattern->GetCrossOverHeight();
    MoveCaretToContentRectWithAxis(true, caretOffset, caretRect.Height(), keyboardOffset);
    MoveCaretToContentRectWithAxis(false, caretOffset, caretRect.Width());
}

void RichEditorFreeScrollController::UpdateBorderRadius()
{
    CHECK_NULL_VOID(scrollBar_);
    auto pattern = weakPattern_.Upgrade();
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
    scrollBar_->SetHostBorderRadius(radius);
}

void RichEditorFreeScrollController::UpdateScrollBarOffsetWithAxis(Axis axis, bool needAnimation)
{
    CHECK_NULL_VOID(scrollBar_ && geometryEvaluator_.IsScrollDirectionValid(axis == Axis::VERTICAL));
    auto pattern = weakPattern_.Upgrade();
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

void RichEditorFreeScrollController::PlayScrollBarUpdateAnimation(Axis axis)
{
    CHECK_NULL_VOID(scrollBar_);
    bool isVertical = (axis == Axis::VERTICAL);
    scrollBar_->PlayAppearAnimation(isVertical);
    scrollBar_->ScheduleDisappearDelayTask(isVertical);
}

void RichEditorFreeScrollController::MoveCaretToContentRectWithAxis(
    bool isVertical, const OffsetF& caretOffset, float caretSize, float keyboardOffset)
{
    CHECK_NULL_VOID(geometryEvaluator_.NeedScroll(isVertical, keyboardOffset));
    Axis axis = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
    float distance = isVertical
        ? geometryEvaluator_.CalCaretToContentRectDistanceVertical(caretOffset, caretSize, keyboardOffset)
        : geometryEvaluator_.CalCaretToContentRectDistanceHorizontal(caretOffset, caretSize);
    PlayScrollBarAppearAnimation(axis);
    ScheduleDisappearDelayTask(axis);
    OnScrollWithAxisCallback(distance, SCROLL_FROM_NONE, axis);
}

} // namespace OHOS::Ace::NG

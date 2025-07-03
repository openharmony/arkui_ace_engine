/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
namespace OHOS::Ace::NG {
namespace {
void ConfigureScrollBar(const std::unique_ptr<ScrollBarProperty>& property, ScrollBar& scrollBar)
{
    const auto& barWidth = property->GetScrollBarWidth();
    if (barWidth) {
        scrollBar.SetActiveWidth(*barWidth);
        scrollBar.SetTouchWidth(*barWidth);
        scrollBar.SetInactiveWidth(*barWidth);
        scrollBar.SetNormalWidth(*barWidth);
        scrollBar.SetIsUserNormalWidth(true);
    } else {
        scrollBar.SetIsUserNormalWidth(false);
    }
    const auto& barColor = property->GetScrollBarColor();
    if (barColor) {
        scrollBar.SetForegroundColor(*barColor, false);
    }
    const auto& margin = property->GetScrollBarMargin();
    if (margin && scrollBar.GetScrollBarMargin() != margin) {
        scrollBar.SetScrollBarMargin(*margin);
        scrollBar.FlushBarWidth();
    }
}
} // namespace

ScrollBar2D::ScrollBar2D(ScrollPattern& pattern) : pattern_(pattern)
{
    vertical_.SetAxis(Axis::VERTICAL);
    horizontal_.SetAxis(Axis::HORIZONTAL);
    horizontal_.SetPositionMode(PositionMode::BOTTOM);
    vertical_.SetPositionMode(PositionMode::RIGHT);

    InitGestures(vertical_, Axis::VERTICAL);
    InitGestures(horizontal_, Axis::HORIZONTAL);

    auto scrollableEvent = pattern_.GetScrollableEvent();
    CHECK_NULL_VOID(scrollableEvent);
    scrollableEvent->SetInBarRegionCallback([weak = WeakClaim(this)](const PointF& point, SourceType source) {
        auto self = weak.Upgrade();
        CHECK_NULL_RETURN(self, false);
        const Point pointDouble { point.GetX(), point.GetY() };
        if (source == SourceType::MOUSE) {
            return self->vertical_.InBarHoverRegion(pointDouble) || self->horizontal_.InBarHoverRegion(pointDouble);
        }
        return self->vertical_.InBarTouchRegion(pointDouble) || self->horizontal_.InBarTouchRegion(pointDouble);
    });
    scrollableEvent->SetInBarRectRegionCallback([weak = WeakClaim(this)](const PointF& point, SourceType source) {
        auto self = weak.Upgrade();
        CHECK_NULL_RETURN(self, false);
        const Point pointDouble { point.GetX(), point.GetY() };
        return self->vertical_.InBarRectRegion(pointDouble) || self->horizontal_.InBarRectRegion(pointDouble);
    });
    scrollableEvent->SetBarCollectTouchTargetCallback(
        [weak = WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->vertical_.OnCollectTouchTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            self->horizontal_.OnCollectTouchTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
    scrollableEvent->SetBarCollectClickAndLongPressTargetCallback(
        [weak = WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->vertical_.OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            self->horizontal_.OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
}

void ScrollBar2D::InitGestures(ScrollBar& scrollBar, Axis axis)
{
    scrollBar.SetAxis(axis);
    scrollBar.SetMarkNeedRenderFunc([weak = WeakPtr(pattern_.GetHost())]() {
        auto node = weak.Upgrade();
        if (node) {
            node->MarkNeedRenderOnly();
        }
    });
    auto scrollCallback = [weak = WeakClaim(&pattern_), axis](double offset, int32_t source, bool isMouseWheelScroll) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->FreeScrollBy(axis == Axis::VERTICAL ? OffsetF { 0.0f, offset } : OffsetF { offset, 0.0f });
        return true;
    };
    scrollBar.SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEnd = [weak = WeakClaim(&pattern_)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEndCallback();
    };
    scrollBar.SetScrollEndCallback(std::move(scrollEnd));

    auto gestureHub = pattern_.GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    auto inputHub = pattern_.GetInputHub();
    CHECK_NULL_VOID(inputHub);
    scrollBar.SetGestureEvent();
    scrollBar.SetMouseEvent();
    scrollBar.SetHoverEvent();
    gestureHub->AddTouchEvent(scrollBar.GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar.GetMouseEvent());
    inputHub->AddOnHoverEvent(scrollBar.GetHoverEvent());
}

void ScrollBar2D::SetDisplayMode(ScrollBar& scrollBar, DisplayMode mode)
{
    if (mode == DisplayMode::OFF) {
        auto gestureHub = pattern_.GetGestureHub();
        if (gestureHub) {
            gestureHub->RemoveTouchEvent(scrollBar.GetTouchEvent());
        }
        if (painter_) {
            painter_->SetOpacity(0);
        }
        return;
    }

    const auto oldDisplayMode = scrollBar.GetDisplayMode();
    if (oldDisplayMode != mode) {
        scrollBar.SetDisplayMode(mode);
        if (painter_ && scrollBar.IsScrollable()) {
            painter_->SetOpacity(UINT8_MAX);
        }
        scrollBar.ScheduleDisappearDelayTask();
    }
}

namespace {
void UpdateBorderRadius(ScrollBar& scrollBar, const RenderContext* ctx)
{
    CHECK_NULL_VOID(ctx);
    const auto radius = ctx->GetBorderRadius();
    if (radius && radius != scrollBar.GetHostBorderRadius()) {
        scrollBar.SetHostBorderRadius(*radius);
        scrollBar.CalcReservedHeight();
    }
}
} // namespace

void ScrollBar2D::Update(const std::unique_ptr<ScrollBarProperty>& props)
{
    const auto displayMode = props->GetScrollBarMode().value_or(DisplayMode::AUTO);
    SetDisplayMode(vertical_, displayMode);
    SetDisplayMode(horizontal_, displayMode);
    if (displayMode != DisplayMode::OFF) {
        ConfigureScrollBar(props, vertical_);
        ConfigureScrollBar(props, horizontal_);
    }

    const PositionMode verticalMode = pattern_.IsRTL() ? PositionMode::LEFT : PositionMode::RIGHT;
    vertical_.SetPositionMode(verticalMode);
    painter_->UpdateVerticalBarPosition(verticalMode);

    const auto* renderContext = pattern_.GetRenderContext();
    UpdateBorderRadius(vertical_, renderContext);
    UpdateBorderRadius(horizontal_, renderContext);
}

namespace {
inline float GetOverScroll(float offset, float scrollableDistance)
{
    return Positive(offset) ? offset : std::max(-(scrollableDistance + offset), 0.0f);
}
} // namespace

void ScrollBar2D::SyncLayout(const OffsetF& offset, const SizeF& viewSize, const SizeF& content)
{
    vertical_.SetOutBoundary(GetOverScroll(offset.GetY(), content.Height() - viewSize.Height()));
    horizontal_.SetOutBoundary(GetOverScroll(offset.GetX(), content.Width() - viewSize.Width()));

    const Size sizeDouble { viewSize.Width(), viewSize.Height() };
    vertical_.UpdateScrollBarRegion({}, sizeDouble, { 0.0, offset.GetY() }, content.Height(), 0);
    horizontal_.UpdateScrollBarRegion({}, sizeDouble, { offset.GetX(), 0.0 }, content.Width(), 0);
    vertical_.MarkNeedRender();
    horizontal_.MarkNeedRender();

    CHECK_NULL_VOID(painter_);
    painter_->SetRect(vertical_.GetActiveRect(), horizontal_.GetActiveRect());
}
} // namespace OHOS::Ace::NG
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
#include "core/components_ng/pattern/text/text_scroll_bar_2d.h"

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
namespace OHOS::Ace::NG {
TextScrollBar2D::TextScrollBar2D(const WeakPtr<ScrollablePattern>& hostPattern) : pattern_(hostPattern)
{
    verticalBar_ = MakeRefPtr<NG::ScrollBar>();
    verticalBar_->SetPositionMode(PositionMode::RIGHT);
    verticalModifier_ = MakeRefPtr<ScrollBarOverlayModifier>();
    verticalModifier_->SetPositionMode(PositionMode::RIGHT);

    horizontalBar_ = MakeRefPtr<NG::ScrollBar>();
    horizontalBar_->SetPositionMode(PositionMode::BOTTOM);
    horizontalModifier_ = MakeRefPtr<ScrollBarOverlayModifier>();
    horizontalModifier_->SetPositionMode(PositionMode::BOTTOM);

    InitNGScrollBar(*verticalBar_, true);
    InitNGScrollBar(*horizontalBar_, false);
    AddScrollableEvent();
}

void TextScrollBar2D::InitNGScrollBar(NG::ScrollBar& bar, bool isVertical)
{
    bar.SetMarkNeedRenderFunc([weak = pattern_]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        if (host) {
            host->MarkNeedRenderOnly();
        }
    });
    auto scrollCallback = [weak = WeakClaim(this), isVertical](double offset, int32_t source, bool isMouseWheelScroll) {
        auto self = weak.Upgrade();
        CHECK_NULL_RETURN(self, false);
        return self->HandleScrollPositionCallback(offset, source,  isMouseWheelScroll, isVertical);
    };
    bar.SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEndCallback = [weak = WeakClaim(this), isVertical]() {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->HandleScrollEndCallback(isVertical);
    };
    bar.SetScrollEndCallback(std::move(scrollEndCallback));

    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (gestureHub) {
        bar.SetGestureEvent();
        gestureHub->AddTouchEvent(bar.GetTouchEvent());
    }

    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub) {
        auto inputHub = eventHub->GetOrCreateInputEventHub();
        if (inputHub) {
            bar.SetMouseEvent();
            bar.SetHoverEvent();
            inputHub->AddOnMouseEvent(bar.GetMouseEvent());
            inputHub->AddOnHoverEvent(bar.GetHoverEvent());
        }
    }
}

void TextScrollBar2D::AddScrollableEvent()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(Axis::NONE);
    SetInBarRegionCallback(scrollableEvent_);
    SetInBarRectRegionCallback(scrollableEvent_);
    SetBarCollectTouchTargetCallback(scrollableEvent_);
    SetBarCollectClickAndLongPressTargetCallback(scrollableEvent_);
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void TextScrollBar2D::SetInBarRegionCallback(const RefPtr<ScrollableEvent>& event)
{
    CHECK_NULL_VOID(event);
    event->SetInBarRegionCallback([weak = WeakClaim(this)](const PointF& point, SourceType source) {
        auto self = weak.Upgrade();
        CHECK_NULL_RETURN(self && self->verticalBar_ && self->horizontalBar_, false);
        const Point pointDouble { point.GetX(), point.GetY() };
        if (source == SourceType::MOUSE) {
            return self->verticalBar_->InBarHoverRegion(pointDouble) ||
                   self->horizontalBar_->InBarHoverRegion(pointDouble);
        }
        return self->verticalBar_->InBarTouchRegion(pointDouble) || self->horizontalBar_->InBarTouchRegion(pointDouble);
    });
}

void TextScrollBar2D::SetInBarRectRegionCallback(const RefPtr<ScrollableEvent>& event)
{
    CHECK_NULL_VOID(event);
    event->SetInBarRectRegionCallback([weak = WeakClaim(this)](const PointF& point, SourceType source) {
        auto self = weak.Upgrade();
        CHECK_NULL_RETURN(self && self->verticalBar_ && self->horizontalBar_, false);
        const Point pointDouble { point.GetX(), point.GetY() };
        return self->verticalBar_->InBarRectRegion(pointDouble) || self->horizontalBar_->InBarRectRegion(pointDouble);
    });
}

void TextScrollBar2D::SetBarCollectTouchTargetCallback(const RefPtr<ScrollableEvent>& event)
{
    CHECK_NULL_VOID(event);
    event->SetBarCollectTouchTargetCallback(
        [weak = WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self && self->verticalBar_ && self->horizontalBar_);
            self->verticalBar_->OnCollectTouchTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            self->horizontalBar_->OnCollectTouchTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
}

void TextScrollBar2D::SetBarCollectClickAndLongPressTargetCallback(const RefPtr<ScrollableEvent>& event)
{
    CHECK_NULL_VOID(event);
    event->SetBarCollectClickAndLongPressTargetCallback(
        [weak = WeakClaim(this)](const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
            TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
            ResponseLinkResult& responseLinkResult) {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self && self->verticalBar_ && self->horizontalBar_);
            self->verticalBar_->OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            self->horizontalBar_->OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
}

void TextScrollBar2D::RemoveGestures(NG::ScrollBar& bar)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    if (gestureHub) {
        gestureHub->RemoveTouchEvent(bar.GetTouchEvent());
        if (scrollableEvent_) {
            gestureHub->RemoveScrollableEvent(scrollableEvent_);
        }
    }
    auto eventHub = host->GetEventHub<EventHub>();
    if (eventHub) {
        auto inputHub = eventHub->GetOrCreateInputEventHub();
        if (inputHub) {
            inputHub->RemoveOnMouseEvent(bar.GetMouseEvent());
            inputHub->RemoveOnHoverEvent(bar.GetHoverEvent());
        }
    }
}

TextScrollBar2D::~TextScrollBar2D()
{
    if (verticalBar_) {
        RemoveGestures(*verticalBar_);
    }
    if (horizontalBar_) {
        RemoveGestures(*horizontalBar_);
    }
}

void TextScrollBar2D::UpdateBorderRadius(bool isVertical)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto ctx = host->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    const auto radius = ctx->GetBorderRadius();
    auto scrollbar = isVertical ? verticalBar_ : horizontalBar_;
    if (radius && scrollbar && radius != scrollbar->GetHostBorderRadius()) {
        scrollbar->SetHostBorderRadius(*radius);
        scrollbar->CalcReservedHeight();
    }
}

void TextScrollBar2D::UpdateScrollBar(const UpdateScrollBarData& data, bool isVertical)
{
    auto scrollbar = isVertical ? verticalBar_ : horizontalBar_;
    CHECK_NULL_VOID(scrollbar);
    auto modifier = isVertical ? verticalModifier_ : horizontalModifier_;
    auto mainSize = isVertical ? data.viewPort.Height() : data.viewPort.Width();
    bool scrollable = GreatNotEqual(data.estimatedHeight, mainSize);
    if (scrollbar->IsScrollable() != scrollable) {
        scrollbar->SetScrollable(scrollable);
        if (modifier) {
            modifier->SetOpacity(scrollable ? UINT8_MAX : 0);
            modifier->SetScrollable(scrollable);
        }
        if (scrollable) {
            scrollbar->ScheduleDisappearDelayTask();
        }
    }
    Offset scrollOffset = { data.offset, data.offset };
    scrollbar->UpdateScrollBarRegion(data.viewOffset, data.viewPort, scrollOffset, data.estimatedHeight, 0);
}

void TextScrollBar2D::UpdateVerticalBar(float offset, float estimatedHeight, const Size& viewPort, Offset viewOffset)
{
    UpdateScrollBar({ offset, estimatedHeight, viewPort, viewOffset }, true);
}

void TextScrollBar2D::UpdateHorizontalBar(float offset, float estimatedHeight, const Size& viewPort, Offset viewOffset)
{
    UpdateScrollBar({ offset, estimatedHeight, viewPort, viewOffset }, false);
}

void TextScrollBar2D::OnDraw(DrawingContext& context) const
{
    if (verticalModifier_) {
        verticalModifier_->onDraw(context);
    }
    if (horizontalModifier_) {
        horizontalModifier_->onDraw(context);
    }
}

bool TextScrollBar2D::HandleScrollPositionCallback(
    double offset, int32_t source, bool isMouseWheelScroll, bool isVertical)
{
    if (scrollCallback_) {
        scrollCallback_(offset, source, isVertical);
    }
    return true;
}

void TextScrollBar2D::HandleScrollEndCallback(bool isVertical)
{
    if (endScrollCallback_) {
        endScrollCallback_(isVertical);
    }
}
} // namespace OHOS::Ace::NG

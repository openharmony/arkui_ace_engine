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

#include "core/components_ng/event/scrollable_event.h"

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollableEvent::ScrollableEvent(Axis axis) : axis_(axis) {};
ScrollableEvent::~ScrollableEvent() = default;

ScrollableActuator::ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

void ScrollableEvent::SetAxis(Axis axis)
{
    axis_ = axis;
    if (scrollable_) {
        scrollable_->SetAxis(axis);
    }
}

void ScrollableEvent::SetScrollable(const RefPtr<Scrollable>& scrollable)
{
    scrollable_ = scrollable;
}

const RefPtr<Scrollable>& ScrollableEvent::GetScrollable() const
{
    return scrollable_;
}

bool ScrollableEvent::Idle() const
{
    if (scrollable_) {
        return scrollable_->Idle();
    }
    return true;
}

bool ScrollableEvent::IsHitTestBlock(const PointF& localPoint, SourceType source) const
{
    if (source == SourceType::MOUSE && InBarRectRegion(localPoint, source)) {
        return false;
    }
    if (scrollable_ && !scrollable_->Idle() &&
        std::abs(scrollable_->GetCurrentVelocity()) > PipelineBase::Vp2PxWithCurrentDensity(HTMBLOCK_VELOCITY)) {
        return true;
    }
    if (getAnimateVelocityCallback_) {
        return std::abs(getAnimateVelocityCallback_()) > PipelineBase::Vp2PxWithCurrentDensity(HTMBLOCK_VELOCITY);
    }
    return false;
}

void ScrollableEvent::AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd)
{
    if (scrollable_) {
        scrollable_->AddPreviewMenuHandleDragEnd(std::move(actionEnd));
    }
}

void ScrollableActuator::AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& effect)
{
    CHECK_NULL_VOID(effect);
    auto scrollable = scrollableEvents_[axis];
    CHECK_NULL_VOID(scrollable);
    effect->SetScrollable(scrollable->GetScrollable());
    effect->InitialEdgeEffect();
    scrollEffects_[axis] = effect;
}

bool ScrollableActuator::RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& effect)
{
    CHECK_NULL_RETURN(effect, false);
    for (auto iter = scrollEffects_.begin(); iter != scrollEffects_.end(); ++iter) {
        if (effect == iter->second) {
            scrollEffects_.erase(iter);
            return true;
        }
    }
    return false;
}

void ScrollableActuator::CollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const PointF& localPoint,
    const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
    ResponseLinkResult& responseLinkResult)
{
    for (const auto& [axis, event] : scrollableEvents_) {
        if (!event) {
            continue;
        }
        if (event->GetEnabled()) {
            if (event->InBarRegion(localPoint, touchRestrict.sourceType)) {
                event->BarCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            } else if (event->InBarRectRegion(localPoint, touchRestrict.sourceType)) {
                event->BarCollectLongPressTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
                event->CollectScrollableTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
                event->BarRectCollectTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            } else {
                event->CollectScrollableTouchTarget(
                    coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            }
        }
        bool clickJudge = event->ClickJudge(localPoint);
        if (event->GetEnabled() || clickJudge) {
            InitClickRecognizer(coordinateOffset, getEventTargetImpl, frameNode, targetComponent, event, clickJudge,
                localPoint, touchRestrict.sourceType);
            result.emplace_back(clickRecognizer_);
            responseLinkResult.emplace_back(clickRecognizer_);
        }
        break;
    }
}

void ScrollableActuator::InitClickRecognizer(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent,
    const RefPtr<ScrollableEvent>& event, bool clickJudge,
    const PointF& localPoint, SourceType source)
{
    if (!clickRecognizer_) {
        clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
    }
    clickRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
    clickRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
    clickRecognizer_->SetNodeId(frameNode->GetId());
    clickRecognizer_->AttachFrameNode(frameNode);
    clickRecognizer_->SetTargetComponent(targetComponent);
    clickRecognizer_->SetIsSystemGesture(true);
    clickRecognizer_->SetRecognizerType(GestureTypeName::TAP_GESTURE);
    clickRecognizer_->SetSysGestureJudge([clickJudge](const RefPtr<GestureInfo>& gestureInfo,
                                             const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
        TAG_LOGI(
            AceLogTag::ACE_SCROLLABLE, "Scrollable GestureJudge: clickJudge %{public}d", clickJudge);
        return clickJudge ? GestureJudgeResult::CONTINUE : GestureJudgeResult::REJECT;
    });
    clickRecognizer_->SetOnClick([weak = WeakClaim(RawPtr(frameNode))](const ClickInfo&) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<ListPattern>();
        CHECK_NULL_VOID(pattern);
        auto item = pattern->GetSwiperItem().Upgrade();
        CHECK_NULL_VOID(item);
        item->ResetSwipeStatus();
    });
}

void ScrollableEvent::CollectScrollableTouchTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
    {
        if (scrollable_) {
            scrollable_->SetGetEventTargetImpl(getEventTargetImpl);
            scrollable_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
            scrollable_->OnCollectTouchTarget(result, frameNode, targetComponent, responseLinkResult);
        }
    }
} // namespace OHOS::Ace::NG

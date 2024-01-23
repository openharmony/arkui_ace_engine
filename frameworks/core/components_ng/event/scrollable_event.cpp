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

#include "base/geometry/offset.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ScrollableActuator::ScrollableActuator(const WeakPtr<GestureEventHub>& gestureEventHub)
    : gestureEventHub_(gestureEventHub)
{}

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
    const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent)
{
    for (const auto& [axis, event] : scrollableEvents_) {
        if (!event || !event->GetEnable()) {
            continue;
        }
        if (event->InBarRegion(localPoint, touchRestrict.sourceType)) {
            event->BarCollectTouchTarget(coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent);
        } else if (event->GetScrollable()) {
            const auto& scrollable = event->GetScrollable();
            scrollable->SetGetEventTargetImpl(getEventTargetImpl);
            scrollable->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
            scrollable->OnCollectTouchTarget(result, frameNode, targetComponent);
        }
        if (!clickRecognizer_) {
            clickRecognizer_ = MakeRefPtr<ClickRecognizer>();
        }
        clickRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        clickRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        clickRecognizer_->AssignNodeId(frameNode->GetId());
        clickRecognizer_->AttachFrameNode(frameNode);
        clickRecognizer_->SetTargetComponent(targetComponent);
        clickRecognizer_->SetIsSystemGesture(true);
        clickRecognizer_->SetSysGestureJudge([weak = WeakClaim(RawPtr(event))](const RefPtr<GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
            auto event = weak.Upgrade();
            CHECK_NULL_RETURN(event, GestureJudgeResult::CONTINUE);
            if (!event->IsHitTestBlock()) {
                return GestureJudgeResult::REJECT;
            }
            return GestureJudgeResult::CONTINUE;
        });
        result.emplace_front(clickRecognizer_);
        break;
    }
}
} // namespace OHOS::Ace::NG

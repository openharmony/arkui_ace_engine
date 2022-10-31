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

#include "core/components_ng/event/gesture_event_hub.h"

#include <cstdint>
#include <list>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

GestureEventHub::GestureEventHub(const WeakPtr<EventHub>& eventHub) : eventHub_(eventHub) {}

RefPtr<FrameNode> GestureEventHub::GetFrameNode() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->GetFrameNode() : nullptr;
}

bool GestureEventHub::ProcessTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& innerTargets, TouchTestResult& finalResult)
{
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    if (scrollableActuator_) {
        scrollableActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets);
    }
    if (touchEventActuator_) {
        touchEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets);
    }
    if (clickEventActuator_) {
        clickEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets);
    }
    if (panEventActuator_) {
        panEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets);
    }

    TouchTestResult dragTargets;
    if (longPressEventActuator_) {
        longPressEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, dragTargets);
    }
    if (dragEventActuator_) {
        dragEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, dragTargets);
    }

    std::list<RefPtr<GestureRecognizer>> longPressRecognizers;
    for (const auto& item : dragTargets) {
        longPressRecognizers.emplace_back(AceType::DynamicCast<GestureRecognizer>(item));
    }
    if (!longPressRecognizers.empty()) {
        // this node has long press and drag event, combine into parallelRecognizer.
        if (!nodeParallelRecognizer_) {
            nodeParallelRecognizer_ = MakeRefPtr<ParallelRecognizer>(std::move(longPressRecognizers));
        } else {
            nodeParallelRecognizer_->AddChildren(longPressRecognizers);
        }
        innerTargets.emplace_back(nodeParallelRecognizer_);
    } else {
        nodeParallelRecognizer_.Reset();
    }

    std::list<RefPtr<GestureRecognizer>> innerRecognizers;
    for (auto const& eventTarget : innerTargets) {
        auto recognizer = AceType::DynamicCast<GestureRecognizer>(eventTarget);
        if (recognizer) {
            innerRecognizers.push_back(std::move(recognizer));
        } else {
            finalResult.push_back(eventTarget);
        }
    }

    ProcessTouchTestHierarchy(coordinateOffset, touchRestrict, innerRecognizers, finalResult);

    return false;
}

void GestureEventHub::ProcessTouchTestHierarchy(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    std::list<RefPtr<GestureRecognizer>>& innerRecognizers, TouchTestResult& finalResult)
{
    auto host = GetFrameNode();
    if (!host) {
        LOGE("the host is nullptr");
        for (auto&& recognizer : innerRecognizers) {
            finalResult.emplace_back(std::move(recognizer));
        }
        return;
    }

    auto offset = Offset(coordinateOffset.GetX(), coordinateOffset.GetY());
    RefPtr<GestureRecognizer> current;

    // Pack inner recognizer include self inner recognizer and children.
    if (innerRecognizers.size() == 1) {
        current = *innerRecognizers.begin();
    } else if (innerRecognizers.size() > 1) {
        if (!innerExclusiveRecognizer_) {
            innerExclusiveRecognizer_ = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(innerRecognizers));
        } else {
            innerExclusiveRecognizer_->AddChildren(innerRecognizers);
        }
        innerExclusiveRecognizer_->SetCoordinateOffset(offset);
        current = innerExclusiveRecognizer_;
    }

    if (recreateGesture_) {
        UpdateGestureHierarchy();
        recreateGesture_ = false;
    }

    auto context = host->GetContext();
    int32_t parallelIndex = 0;
    int32_t exclusiveIndex = 0;
    for (auto const& recognizer : gestureHierarchy_) {
        if (!recognizer) {
            continue;
        }
        recognizer->SetCoordinateOffset(offset);
        auto gestureMask = recognizer->GetPriorityMask();
        if (gestureMask == GestureMask::IgnoreInternal) {
            // In ignore case, dropped the self inner recognizer and children recognizer.
            current = recognizer;
            continue;
        }
        auto priority = recognizer->GetPriority();
        std::list<RefPtr<GestureRecognizer>> recognizers { 1, recognizer };
        if (priority == GesturePriority::Parallel) {
            if (current) {
                recognizers.push_front(current);
            }
            if (recognizers.size() > 1) {
                if ((static_cast<int32_t>(externalParallelRecognizer_.size()) <= parallelIndex)) {
                    externalParallelRecognizer_.emplace_back(
                        AceType::MakeRefPtr<ParallelRecognizer>(std::move(recognizers)));
                } else {
                    externalParallelRecognizer_[parallelIndex]->AddChildren(recognizers);
                }
                externalParallelRecognizer_[parallelIndex]->SetCoordinateOffset(offset);
                current = externalParallelRecognizer_[parallelIndex];
                parallelIndex++;
            } else if (recognizers.size() == 1) {
                current = *recognizers.begin();
            }
        } else {
            if (current) {
                if (priority == GesturePriority::Low) {
                    recognizers.push_front(current);
                } else {
                    recognizers.push_back(current);
                }
            }

            if (recognizers.size() > 1) {
                if ((static_cast<int32_t>(externalExclusiveRecognizer_.size()) <= exclusiveIndex)) {
                    externalExclusiveRecognizer_.emplace_back(
                        AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(recognizers)));
                } else {
                    externalExclusiveRecognizer_[exclusiveIndex]->AddChildren(recognizers);
                }
                externalExclusiveRecognizer_[exclusiveIndex]->SetCoordinateOffset(offset);
                current = externalExclusiveRecognizer_[exclusiveIndex];
                exclusiveIndex++;
            } else if (recognizers.size() == 1) {
                current = *recognizers.begin();
            }
        }
    }

    if (exclusiveIndex != static_cast<int32_t>(externalExclusiveRecognizer_.size())) {
        LOGI("externalExclusiveRecognizer size changed, %{public}d resize to %{public}d",
            static_cast<int32_t>(externalExclusiveRecognizer_.size()), exclusiveIndex);
        externalExclusiveRecognizer_.resize(exclusiveIndex);
    }

    if (parallelIndex != static_cast<int32_t>(externalParallelRecognizer_.size())) {
        LOGI("externalParallelRecognizer size changed, %{public}d resize to %{public}d",
            static_cast<int32_t>(externalParallelRecognizer_.size()), parallelIndex);
        externalParallelRecognizer_.resize(parallelIndex);
    }

    if (current) {
        finalResult.emplace_back(std::move(current));
    }
}

void GestureEventHub::UpdateGestureHierarchy()
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    bool success = gestures_.size() == gestureHierarchy_.size();
    if (success) {
        auto iter = gestures_.begin();
        auto recognizerIter = gestureHierarchy_.begin();
        for (; iter != gestures_.end(); iter++, recognizerIter++) {
            auto newRecognizer = (*iter)->CreateRecognizer();
            success = success && (*recognizerIter)->ReconcileFrom(newRecognizer);
            if (!success) {
                break;
            }
        }
    }

    if (success) {
        gestures_.clear();
        return;
    }

    gestureHierarchy_.clear();
    for (auto const& gesture : gestures_) {
        if (!gesture) {
            continue;
        }
        auto recognizer = gesture->CreateRecognizer();
        if (!recognizer) {
            continue;
        }
        auto priority = gesture->GetPriority();
        auto gestureMask = gesture->GetGestureMask();
        recognizer->SetPriority(priority);
        recognizer->SetPriorityMask(gestureMask);
        gestureHierarchy_.emplace_back(recognizer);
    }
    gestures_.clear();
}

void GestureEventHub::CombineIntoExclusiveRecognizer(
    const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result)
{
    TouchTestResult finalResult;
    std::list<RefPtr<GestureRecognizer>> recognizers;
    const auto coordinateOffset = globalPoint - localPoint;
    auto offset = Offset(coordinateOffset.GetX(), coordinateOffset.GetY());
    for (auto const& eventTarget : result) {
        auto recognizer = AceType::DynamicCast<GestureRecognizer>(eventTarget);
        if (recognizer) {
            recognizers.push_back(std::move(recognizer));
        } else {
            finalResult.push_back(eventTarget);
        }
    }

    RefPtr<GestureRecognizer> current;
    if (recognizers.size() == 1) {
        current = *recognizers.begin();
    } else if (recognizers.size() > 1) {
        if (!nodeExclusiveRecognizer_) {
            nodeExclusiveRecognizer_ = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(recognizers));
        } else {
            nodeExclusiveRecognizer_->AddChildren(recognizers);
        }
        nodeExclusiveRecognizer_->SetCoordinateOffset(offset);
        current = nodeExclusiveRecognizer_;
    }

    if (current) {
        finalResult.emplace_back(std::move(current));
    }
    result.swap(finalResult);
}

void GestureEventHub::InitDragDropEvent()
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        if (gestureEventHub) {
            gestureEventHub->HandleOnDragStart(info);
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        if (gestureEventHub) {
            gestureEventHub->HandleOnDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        if (gestureEventHub) {
            gestureEventHub->HandleOnDragEnd(info);
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto gestureEventHub = weak.Upgrade();
        if (gestureEventHub) {
            gestureEventHub->HandleOnDragCancel();
        }
    };

    auto dragEvent = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void GestureEventHub::HandleOnDragStart(const GestureEvent& info)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);

    if (!eventHub->HasOnDragStart()) {
        LOGE("HandleOnDragStart: there is no onDragStart function.");
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    event->SetX(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    auto extraParams = JsonUtil::Create(true);
    auto dragDropInfo = (eventHub->GetOnDragStart())(event, extraParams->ToString());

    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    if (dragDropProxy_) {
        dragDropProxy_ = nullptr;
    }

    if (dragDropInfo.customNode) {
        dragDropProxy_ = dragDropManager->CreateAndShowDragWindow(dragDropInfo.customNode, info);
    } else {
        dragDropProxy_ = dragDropManager->CreateAndShowDragWindow(dragDropInfo.pixelMap, info);
    }
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragStart(info, dragDropInfo.extraInfo, GetFrameNode());
}

void GestureEventHub::HandleOnDragUpdate(const GestureEvent& info)
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragMove(info);
}

void GestureEventHub::HandleOnDragEnd(const GestureEvent& info)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    // Only the onDrop callback of dragged frame node is triggered.
    // The onDrop callback of target frame node is triggered in PipelineContext::OnDragEvent.
    if (eventHub->HasOnDrop()) {
        RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        event->SetX(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
        event->SetY(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
        eventHub->FireOnDrop(event, "");
    }

    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragEnd(info);
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
}

void GestureEventHub::HandleOnDragCancel()
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->onDragCancel();
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
}

void GestureEventHub::SetFocusClickEvent(GestureEventFunc&& clickEvent)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetFocusHub();
    if (focusHub) {
        focusHub->SetOnClickCallback(std::move(clickEvent));
    }
}

void GestureEventHub::SetClickEvent(GestureEventFunc&& clickEvent)
{
    if (!clickEventActuator_) {
        clickEventActuator_ = MakeRefPtr<ClickEventActuator>(WeakClaim(this));
        clickEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }
    clickEventActuator_->ReplaceClickEvent(std::move(clickEvent));

    SetFocusClickEvent(clickEventActuator_->GetClickEvent());
}

void GestureEventHub::AddClickEvent(const RefPtr<ClickEvent>& clickEvent)
{
    if (!clickEventActuator_) {
        clickEventActuator_ = MakeRefPtr<ClickEventActuator>(WeakClaim(this));
        clickEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }
    clickEventActuator_->AddClickEvent(clickEvent);

    SetFocusClickEvent(clickEventActuator_->GetClickEvent());
}

OnAccessibilityEventFunc GestureEventHub::GetOnAccessibilityEventFunc()
{
    auto callback = [weak = WeakClaim(this)](AccessibilityEventType eventType) {
        auto gestureHub = weak.Upgrade();
        if (!gestureHub) {
            return;
        }
        auto node = gestureHub->GetFrameNode();
        if (node) {
            node->OnAccessibilityEvent(eventType);
        }
    };
    return callback;
}

bool GestureEventHub::ActClick()
{
    if (!clickEventActuator_) {
        return false;
    }

    auto click = clickEventActuator_->GetClickEvent();
    if (click) {
        GestureEvent info;
        click(info);
    }
    return true;
}

bool GestureEventHub::ActLongClick()
{
    if (!longPressEventActuator_) {
        return false;
    }

    auto click = longPressEventActuator_->GetGestureEventFunc();
    if (click) {
        GestureEvent info;
        click(info);
    }
    return true;
}
} // namespace OHOS::Ace::NG
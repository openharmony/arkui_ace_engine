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

    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    if (scrollableActuator_) {
        // TODO: need to change scrollable to be gesture recognizer to make gesture referee works.
        scrollableActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, finalResult);
    }
    if (touchEventActuator_) {
        touchEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, finalResult);
    }
    if (longPressEventActuator_) {
        longPressEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, finalResult);
    }
    if (clickEventActuator_) {
        clickEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, finalResult);
    }
    if (panEventActuator_) {
        panEventActuator_->OnCollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, finalResult);
    }

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
            innerExclusiveRecognizer_->SetCoordinateOffset(offset);
        }
        current = innerExclusiveRecognizer_;
    }

    if (recreateGesture_) {
        UpdateGestureHierarchy();
        recreateGesture_ = false;
    }

    auto context = host->GetContext();
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
                if (!externalParallelRecognizer_ || recreateGesture_) {
                    externalParallelRecognizer_ = AceType::MakeRefPtr<ParallelRecognizer>(std::move(recognizers));
                    externalParallelRecognizer_->SetCoordinateOffset(offset);
                }
                current = externalParallelRecognizer_;
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
                if (!externalExclusiveRecognizer_ || recreateGesture_) {
                    externalExclusiveRecognizer_ = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(recognizers));
                    externalExclusiveRecognizer_->SetCoordinateOffset(offset);
                }
                current = externalExclusiveRecognizer_;
            } else if (recognizers.size() == 1) {
                current = *recognizers.begin();
            }
        }
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
            nodeExclusiveRecognizer_->SetCoordinateOffset(offset);
        }
        current = nodeExclusiveRecognizer_;
    }

    if (current) {
        finalResult.emplace_back(std::move(current));
    }
    result.swap(finalResult);
}

} // namespace OHOS::Ace::NG
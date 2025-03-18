/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "base/utils/time_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/gestures/gesture_group.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
constexpr const char* HIT_TEST_MODE[] = {
    "HitTestMode.Default",
    "HitTestMode.Block",
    "HitTestMode.Transparent",
    "HitTestMode.None",
};

GestureEventHub::GestureEventHub(const WeakPtr<EventHub>& eventHub) : eventHub_(eventHub) {}

RefPtr<FrameNode> GestureEventHub::GetFrameNode() const
{
    auto eventHub = eventHub_.Upgrade();
    return eventHub ? eventHub->GetFrameNode() : nullptr;
}

bool GestureEventHub::ProcessTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    size_t idx = innerTargets.size();
    size_t newIdx = 0;
    ProcessEventTouchTestHit(coordinateOffset, touchRestrict, innerTargets,
        finalResult, touchId, localPoint, targetComponent, responseLinkResult);
    ProcessDragEventTouchTestHit(coordinateOffset, touchRestrict, innerTargets,
        finalResult, touchId, localPoint, targetComponent, responseLinkResult);

    std::list<RefPtr<NGGestureRecognizer>> innerRecognizers;
    for (auto const& eventTarget : innerTargets) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(eventTarget);
        if (recognizer) {
            auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(recognizer);
            if (!recognizerGroup && newIdx >= idx) {
                recognizer->SetNodeId(host->GetId());
                recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
                recognizer->SetTargetComponent(targetComponent);
                recognizer->SetIsSystemGesture(true);
            }
            recognizer->BeginReferee(touchId);
            innerRecognizers.push_back(std::move(recognizer));
        } else {
            eventTarget->SetNodeId(host->GetId());
            eventTarget->AttachFrameNode(WeakPtr<FrameNode>(host));
            eventTarget->SetTargetComponent(targetComponent);
            finalResult.push_back(eventTarget);
        }
        newIdx++; // not process previous recognizers
    }

    ProcessTouchTestHierarchy(
        coordinateOffset, touchRestrict, innerRecognizers, finalResult, touchId, targetComponent, responseLinkResult);

    return false;
}

bool GestureEventHub::ProcessEventTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    if (scrollableActuator_) {
        scrollableActuator_->CollectTouchTarget(coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets,
            localPoint, host, targetComponent, responseLinkResult);
    }
    if (dragEventActuator_ && !dragEventActuator_->GetIsNewFwk()) {
        dragEventActuator_->AddTouchListener(touchRestrict);
    }
    if (touchEventActuator_) {
        touchEventActuator_->OnCollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets, responseLinkResult);
    }
    if (clickEventActuator_ && !redirectClick_) {
        clickEventActuator_->OnCollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets, responseLinkResult);
    }
    if (userParallelClickEventActuator_) {
        auto clickRecognizer = userParallelClickEventActuator_->GetClickRecognizer();
        if (clickRecognizer) {
            clickRecognizer->SetGestureInfo(
                MakeRefPtr<GestureInfo>(GestureTypeName::CLICK, GestureTypeName::CLICK, true));
            clickRecognizer->SetOnAction(userParallelClickEventActuator_->GetClickEvent());
            clickRecognizer->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
            clickRecognizer->SetGetEventTargetImpl(getEventTargetImpl);
        }
    }
    if (panEventActuator_) {
        panEventActuator_->OnCollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets, responseLinkResult);
    }
    return false;
}

bool GestureEventHub::ProcessDragEventTouchTestHit(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    TouchTestResult& innerTargets, TouchTestResult& finalResult, int32_t touchId, const PointF& localPoint,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    TouchTestResult dragTargets;
    if (longPressEventActuator_) {
        longPressEventActuator_->OnCollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, dragTargets, responseLinkResult);
    }
    if (dragEventActuator_) {
        dragEventActuator_->OnCollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, dragTargets, responseLinkResult);
    }

    std::list<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    for (const auto& item : dragTargets) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(item);
        if (recognizer) {
            recognizer->BeginReferee(touchId);
            recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
            recognizer->SetTargetComponent(targetComponent);
            auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
            if (group) {
                group->SetChildrenTargetComponent(targetComponent);
            }
        }
        longPressRecognizers.emplace_back(AceType::DynamicCast<NGGestureRecognizer>(item));
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
    return false;
}

void GestureEventHub::OnModifyDone()
{
    if (recreateGesture_) {
        UpdateGestureHierarchy();
        recreateGesture_ = false;
    }
}

RefPtr<NGGestureRecognizer> GestureEventHub::PackInnerRecognizer(
    const Offset& offset, std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent)
{
    RefPtr<NGGestureRecognizer> current;
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
        innerExclusiveRecognizer_->BeginReferee(touchId);
        auto host = GetFrameNode();
        innerExclusiveRecognizer_->AttachFrameNode(WeakPtr<FrameNode>(host));
        innerExclusiveRecognizer_->SetTargetComponent(targetComponent);
        current = innerExclusiveRecognizer_;
    }

    return current;
}

void GestureEventHub::ProcessParallelPriorityGesture(const Offset& offset, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent, const RefPtr<FrameNode>& host, RefPtr<NGGestureRecognizer>& current,
    std::list<RefPtr<NGGestureRecognizer>>& recognizers, int32_t& parallelIndex)
{
    if (current) {
        recognizers.push_front(current);
    }
    if (recognizers.size() > 1) {
        if ((static_cast<int32_t>(externalParallelRecognizer_.size()) <= parallelIndex)) {
            externalParallelRecognizer_.emplace_back(AceType::MakeRefPtr<ParallelRecognizer>(std::move(recognizers)));
        } else {
            externalParallelRecognizer_[parallelIndex]->AddChildren(recognizers);
        }
        externalParallelRecognizer_[parallelIndex]->SetCoordinateOffset(offset);
        externalParallelRecognizer_[parallelIndex]->BeginReferee(touchId);
        externalParallelRecognizer_[parallelIndex]->AttachFrameNode(WeakPtr<FrameNode>(host));
        externalParallelRecognizer_[parallelIndex]->SetTargetComponent(targetComponent);
        current = externalParallelRecognizer_[parallelIndex];
        parallelIndex++;
    } else if (static_cast<int32_t>(externalParallelRecognizer_.size()) > parallelIndex) {
        externalParallelRecognizer_[parallelIndex]->BeginReferee(touchId);
        current = externalParallelRecognizer_[parallelIndex];
        parallelIndex++;
    } else if (recognizers.size() == 1) {
        current = *recognizers.begin();
    }
}

void GestureEventHub::ProcessExternalExclusiveRecognizer(const Offset& offset, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent, const RefPtr<FrameNode>& host, GesturePriority priority,
    RefPtr<NGGestureRecognizer>& current, std::list<RefPtr<NGGestureRecognizer>>& recognizers, int32_t& exclusiveIndex)
{
    if (current) {
        if (priority == GesturePriority::Low) {
            recognizers.push_front(current);
        } else {
            recognizers.push_back(current);
        }
    }

    if (recognizers.size() > 1) {
        if ((static_cast<int32_t>(externalExclusiveRecognizer_.size()) <= exclusiveIndex)) {
            externalExclusiveRecognizer_.emplace_back(AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(recognizers)));
        } else {
            externalExclusiveRecognizer_[exclusiveIndex]->AddChildren(recognizers);
        }
        externalExclusiveRecognizer_[exclusiveIndex]->SetCoordinateOffset(offset);
        externalExclusiveRecognizer_[exclusiveIndex]->BeginReferee(touchId);
        externalExclusiveRecognizer_[exclusiveIndex]->AttachFrameNode(WeakPtr<FrameNode>(host));
        externalExclusiveRecognizer_[exclusiveIndex]->SetTargetComponent(targetComponent);
        current = externalExclusiveRecognizer_[exclusiveIndex];
        exclusiveIndex++;
    } else if (recognizers.size() == 1) {
        current = *recognizers.begin();
    }
}

void GestureEventHub::ProcessTouchTestHierarchy(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, TouchTestResult& finalResult, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    auto host = GetFrameNode();
    if (!host) {
        for (auto&& recognizer : innerRecognizers) {
            finalResult.emplace_back(std::move(recognizer));
        }
        return;
    }

    auto offset = Offset(coordinateOffset.GetX(), coordinateOffset.GetY());
    RefPtr<NGGestureRecognizer> current;
    current = PackInnerRecognizer(offset, innerRecognizers, touchId, targetComponent);
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    int32_t parallelIndex = 0;
    int32_t exclusiveIndex = 0;
    auto userRecognizers = gestureHierarchy_;
    auto userModifierRecognizers = modifierGestureHierarchy_;
    userRecognizers.splice(userRecognizers.end(), userModifierRecognizers);
    for (auto const& recognizer : userRecognizers) {
        if (!recognizer) {
            continue;
        }
        auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(recognizer);
        if (recognizerGroup) {
            recognizerGroup->SetRecognizerInfoRecursively(offset, host, targetComponent, getEventTargetImpl);
            recognizerGroup->CollectResponseLinkRecognizersRecursively(responseLinkResult);
        } else {
            responseLinkResult.emplace_back(recognizer);
        }

        recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
        recognizer->SetTargetComponent(targetComponent);
        recognizer->SetCoordinateOffset(offset);
        recognizer->BeginReferee(touchId, true);
        recognizer->SetGetEventTargetImpl(getEventTargetImpl);
        auto gestureMask = recognizer->GetPriorityMask();
        if (gestureMask == GestureMask::IgnoreInternal) {
            // In ignore case, dropped the self inner recognizer and children recognizer.
            current = recognizer;
            continue;
        }
        auto priority = recognizer->GetPriority();
        std::list<RefPtr<NGGestureRecognizer>> recognizers { 1, recognizer };
        if (priority == GesturePriority::Parallel) {
            ProcessParallelPriorityGesture(offset, touchId, targetComponent, host, current, recognizers, parallelIndex);
        } else {
            ProcessExternalExclusiveRecognizer(
                offset, touchId, targetComponent, host, priority, current, recognizers, exclusiveIndex);
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
    for (const auto& gesture : gestures_) {
        AddGestureToGestureHierarchy(gesture, false);
    }
    gestures_.clear();
}

void GestureEventHub::UpdateModifierGestureHierarchy()
{
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    bool success = modifierGestures_.size() == modifierGestureHierarchy_.size() && !needRecollect_;
    if (success) {
        auto iter = modifierGestures_.begin();
        auto recognizerIter = modifierGestureHierarchy_.begin();
        for (; iter != modifierGestures_.end(); iter++, recognizerIter++) {
            auto newRecognizer = (*iter)->CreateRecognizer();
            success = success && (*recognizerIter)->ReconcileFrom(newRecognizer);
            if (!success) {
                break;
            }
        }
    }
    if (success) {
        return;
    }

    modifierGestureHierarchy_.clear();
    for (const auto& gesture : modifierGestures_) {
        AddGestureToGestureHierarchy(gesture, true);
    }
    needRecollect_ = false;
}

void GestureEventHub::AddGestureToGestureHierarchy(const RefPtr<NG::Gesture>& gesture, bool isModifier)
{
    if (!gesture) {
        return;
    }
    auto recognizer = gesture->CreateRecognizer();

    auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(recognizer);
    if (clickRecognizer) {
        clickRecognizer->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }

    auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(recognizer);
    if (longPressRecognizer) {
        longPressRecognizer->SetOnAccessibility(GetOnAccessibilityEventFunc());
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto pattern = host->GetPattern();
        if (pattern && longPressRecognizer->HasAction()) {
            longPressRecognizer->SetOnLongPressRecorder(pattern->GetLongPressEventRecorder());
        }
    }

    if (!recognizer) {
        return;
    }
    auto priority = gesture->GetPriority();
    auto gestureMask = gesture->GetGestureMask();
    recognizer->SetPriority(priority);
    recognizer->SetPriorityMask(gestureMask);
    if (isModifier) {
        modifierGestureHierarchy_.emplace_back(recognizer);
        return;
    }
    gestureHierarchy_.emplace_back(recognizer);
}

void GestureEventHub::CombineIntoExclusiveRecognizer(
    const PointF& globalPoint, const PointF& localPoint, TouchTestResult& result, int32_t touchId)
{
    TouchTestResult finalResult;
    std::list<RefPtr<NGGestureRecognizer>> recognizers;
    const auto coordinateOffset = globalPoint - localPoint;
    auto offset = Offset(coordinateOffset.GetX(), coordinateOffset.GetY());
    for (auto const& eventTarget : result) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(eventTarget);
        if (recognizer) {
            recognizers.push_back(std::move(recognizer));
        } else {
            finalResult.push_back(eventTarget);
        }
    }

    RefPtr<NGGestureRecognizer> current;
    if (recognizers.size() == 1) {
        current = *recognizers.begin();
    } else if (recognizers.size() > 1) {
        if (!nodeExclusiveRecognizer_) {
            nodeExclusiveRecognizer_ = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(recognizers));
        } else {
            nodeExclusiveRecognizer_->AddChildren(recognizers);
        }
        nodeExclusiveRecognizer_->SetCoordinateOffset(offset);
        nodeExclusiveRecognizer_->BeginReferee(touchId);
        current = nodeExclusiveRecognizer_;
    }

    if (current) {
        finalResult.emplace_back(std::move(current));
    }
    result.swap(finalResult);
}

void GestureEventHub::SetFocusClickEvent(GestureEventFunc&& clickEvent)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnClickCallback(std::move(clickEvent));
}

// helper function to ensure clickActuator is initialized
void GestureEventHub::CheckClickActuator()
{
    if (!clickEventActuator_) {
        clickEventActuator_ = MakeRefPtr<ClickEventActuator>(WeakClaim(this));
        clickEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }

    if (parallelCombineClick && !userParallelClickEventActuator_) {
        userParallelClickEventActuator_ = MakeRefPtr<ClickEventActuator>(WeakClaim(this));
        userParallelClickEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }
}

void GestureEventHub::SetUserOnClick(GestureEventFunc&& clickEvent, double distanceThreshold)
{
    CheckClickActuator();
    if (parallelCombineClick) {
        userParallelClickEventActuator_->SetUserCallback(std::move(clickEvent));
        SetFocusClickEvent(userParallelClickEventActuator_->GetClickEvent());
        auto clickRecognizer = userParallelClickEventActuator_->GetClickRecognizer();
        clickRecognizer->SetDistanceThreshold(distanceThreshold);
        clickEventActuator_->AddDistanceThreshold(distanceThreshold);
    } else {
        clickEventActuator_->SetUserCallback(std::move(clickEvent));
        SetFocusClickEvent(clickEventActuator_->GetClickEvent());
        auto clickRecognizer = clickEventActuator_->GetClickRecognizer();
        clickRecognizer->SetDistanceThreshold(distanceThreshold);
        clickEventActuator_->AddDistanceThreshold(distanceThreshold);
    }
}

void GestureEventHub::SetNodeClickDistance(double distanceThreshold)
{
    CheckClickActuator();
    if (parallelCombineClick) {
        auto clickRecognizer = userParallelClickEventActuator_->GetClickRecognizer();
        clickRecognizer->SetDistanceThreshold(distanceThreshold);
        clickEventActuator_->AddDistanceThreshold(distanceThreshold);
    } else {
        auto clickRecognizer = clickEventActuator_->GetClickRecognizer();
        clickRecognizer->SetDistanceThreshold(distanceThreshold);
        clickEventActuator_->AddDistanceThreshold(distanceThreshold);
    }
}

void GestureEventHub::SetJSFrameNodeOnClick(GestureEventFunc&& clickEvent)
{
    CheckClickActuator();
    if (parallelCombineClick) {
        userParallelClickEventActuator_->SetJSFrameNodeCallback(std::move(clickEvent));
        SetFocusClickEvent(userParallelClickEventActuator_->GetClickEvent());
    } else {
        clickEventActuator_->SetJSFrameNodeCallback(std::move(clickEvent));
        SetFocusClickEvent(clickEventActuator_->GetClickEvent());
    }
}

void GestureEventHub::SetOnGestureJudgeBegin(GestureJudgeFunc&& gestureJudgeFunc)
{
    gestureJudgeFunc_ = std::move(gestureJudgeFunc);
}

void GestureEventHub::SetOnTouchIntercept(TouchInterceptFunc&& touchInterceptFunc)
{
    touchInterceptFunc_ = std::move(touchInterceptFunc);
}

TouchInterceptFunc GestureEventHub::GetOnTouchIntercept() const
{
    return touchInterceptFunc_;
}

void GestureEventHub::SetShouldBuildinRecognizerParallelWithFunc(
    ShouldBuiltInRecognizerParallelWithFunc&& parallelGestureToFunc)
{
    shouldBuildinRecognizerParallelWithFunc_ = std::move(parallelGestureToFunc);
}

ShouldBuiltInRecognizerParallelWithFunc GestureEventHub::GetParallelInnerGestureToFunc() const
{
    return shouldBuildinRecognizerParallelWithFunc_;
}

void GestureEventHub::SetOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc)
{
    gestureRecognizerJudgeFunc_ = std::move(gestureRecognizerJudgeFunc);
}

GestureRecognizerJudgeFunc GestureEventHub::GetOnGestureRecognizerJudgeBegin() const
{
    return gestureRecognizerJudgeFunc_;
}

void GestureEventHub::SetOnGestureJudgeNativeBegin(GestureJudgeFunc&& gestureJudgeFunc)
{
    gestureJudgeNativeFunc_ = std::move(gestureJudgeFunc);
}

void GestureEventHub::AddClickEvent(const RefPtr<ClickEvent>& clickEvent)
{
    CheckClickActuator();
    clickEventActuator_->AddClickEvent(clickEvent);

    SetFocusClickEvent(clickEventActuator_->GetClickEvent());
}

void GestureEventHub::AddClickAfterEvent(const RefPtr<ClickEvent>& clickEvent)
{
    CheckClickActuator();
    clickEventActuator_->AddClickAfterEvent(clickEvent);

    SetFocusClickEvent(clickEventActuator_->GetClickEvent());
}

// replace last showMenu callback
void GestureEventHub::BindMenu(GestureEventFunc&& showMenu)
{
    if (showMenu_) {
        RemoveClickEvent(showMenu_);
    }
    showMenu_ = MakeRefPtr<ClickEvent>(std::move(showMenu));
    AddClickEvent(showMenu_);
}

void GestureEventHub::RegisterMenuOnTouch(TouchEventFunc&& callback)
{
    if (bindMenuTouch_) {
        RemoveTouchEvent(bindMenuTouch_);
    }
    bindMenuTouch_ = MakeRefPtr<TouchEventImpl>(std::move(callback));
    AddTouchEvent(bindMenuTouch_);
}

OnAccessibilityEventFunc GestureEventHub::GetOnAccessibilityEventFunc()
{
    auto callback = [weak = WeakClaim(this)](AccessibilityEventType eventType) {
        auto gestureHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto node = gestureHub->GetFrameNode();
        CHECK_NULL_VOID(node);
        node->OnAccessibilityEvent(eventType);
    };
    return callback;
}

template<typename T>
const RefPtr<T> GestureEventHub::AccessibilityRecursionSearchRecognizer(const RefPtr<NGGestureRecognizer>& recognizer)
{
    auto CheckRecognizer = [](const RefPtr<NGGestureRecognizer>& recognizer) {
        const auto re = AceType::DynamicCast<ClickRecognizer>(recognizer);
        if (re != nullptr && re->GetFingers() == 1 && re->GetCount() == 1) {
            return true;
        } else if (AceType::DynamicCast<LongPressRecognizer>(recognizer) != nullptr &&
                   AceType::DynamicCast<LongPressRecognizer>(recognizer)->GetFingers() == 1) {
            return true;
        }
        return false;
    };

    const auto re = AceType::DynamicCast<T>(recognizer);
    if (re != nullptr && CheckRecognizer(recognizer)) {
        return re;
    } else if (AceType::DynamicCast<RecognizerGroup>(recognizer) != nullptr) {
        for (const auto& recognizerElement : AceType::DynamicCast<RecognizerGroup>(recognizer)->GetGroupRecognizer()) {
            const auto& tmpRecognizer = AccessibilityRecursionSearchRecognizer<T>(recognizerElement);
            if (tmpRecognizer != nullptr) {
                return tmpRecognizer;
            }
        }
    }
    return nullptr;
}

template<typename T>
const RefPtr<T> GestureEventHub::GetAccessibilityRecognizer()
{
    for (const auto& recognizer : gestureHierarchy_) {
        const auto& re = AccessibilityRecursionSearchRecognizer<T>(recognizer);
        if (re != nullptr) {
            return re;
        }
    }
    for (const auto& recognizer : modifierGestureHierarchy_) {
        const auto& re = AccessibilityRecursionSearchRecognizer<T>(recognizer);
        if (re != nullptr) {
            return re;
        }
    }
    return nullptr;
}

bool GestureEventHub::ActClick(std::shared_ptr<JsonValue> secComphandle)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    GestureEventFunc click;
    GestureEvent info;
    std::chrono::microseconds microseconds(GetMicroTickCount());
    TimeStamp time(microseconds);
    info.SetTimeStamp(time);
    EventTarget clickEventTarget;
    clickEventTarget.id = host->GetInspectorId().value_or("").c_str();
    clickEventTarget.type = host->GetTag();
#ifdef SECURITY_COMPONENT_ENABLE
    info.SetSecCompHandleEvent(secComphandle);
#endif
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto offset = geometryNode->GetFrameOffset();
    auto size = geometryNode->GetFrameSize();
    clickEventTarget.area.SetOffset(DimensionOffset(offset));
    clickEventTarget.area.SetHeight(Dimension(size.Height()));
    clickEventTarget.area.SetWidth(Dimension(size.Width()));
    clickEventTarget.origin = DimensionOffset(host->GetOffsetRelativeToWindow() - offset);
    info.SetTarget(clickEventTarget);
    Offset globalOffset(offset.GetX(), offset.GetY());
    info.SetGlobalLocation(globalOffset);
    if (clickEventActuator_) {
        click = clickEventActuator_->GetClickEvent();
        CHECK_NULL_RETURN(click, true);
        click(info);
        return true;
    }
    const RefPtr<ClickRecognizer> clickRecognizer = GetAccessibilityRecognizer<ClickRecognizer>();
    if (clickRecognizer) {
        click = clickRecognizer->GetTapActionFunc();
        click(info);
        host->OnAccessibilityEvent(AccessibilityEventType::CLICK);
        return true;
    }
    return false;
}

bool GestureEventHub::ActLongClick()
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    GestureEventFunc click;
    GestureEvent info;
    std::chrono::microseconds microseconds(GetMicroTickCount());
    TimeStamp time(microseconds);
    info.SetTimeStamp(time);
    EventTarget longPressTarget;
    longPressTarget.id = host->GetInspectorId().value_or("").c_str();
    longPressTarget.type = host->GetTag();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto offset = geometryNode->GetFrameOffset();
    auto size = geometryNode->GetFrameSize();
    longPressTarget.area.SetOffset(DimensionOffset(offset));
    longPressTarget.area.SetHeight(Dimension(size.Height()));
    longPressTarget.area.SetWidth(Dimension(size.Width()));
    longPressTarget.origin = DimensionOffset(host->GetOffsetRelativeToWindow() - offset);
    info.SetTarget(longPressTarget);
    Offset globalOffset(offset.GetX(), offset.GetY());
    info.SetGlobalLocation(globalOffset);
    if (longPressEventActuator_) {
        click = longPressEventActuator_->GetGestureEventFunc();
        CHECK_NULL_RETURN(click, true);
        click(info);
        return true;
    }
    RefPtr<LongPressRecognizer> longPressRecognizer;
    for (auto gestureRecognizer : gestureHierarchy_) {
        longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(gestureRecognizer);
        if (longPressRecognizer && longPressRecognizer->GetFingers() == 1) {
            click = longPressRecognizer->GetLongPressActionFunc();
            click(info);
            host->OnAccessibilityEvent(AccessibilityEventType::LONG_PRESS);
            return true;
        }
    }
    return false;
}

std::string GestureEventHub::GetHitTestModeStr(const RefPtr<GestureEventHub>& gestureEventHub)
{
    if (!gestureEventHub) {
        return HIT_TEST_MODE[0];
    }
    auto mode = static_cast<int32_t>(gestureEventHub->GetHitTestMode());
    if (mode < 0 || mode >= static_cast<int32_t>(std::size(HIT_TEST_MODE))) {
        return HIT_TEST_MODE[0];
    }
    return HIT_TEST_MODE[mode];
}

bool GestureEventHub::KeyBoardShortCutClick(const KeyEvent& event, const WeakPtr<NG::FrameNode>& node)
{
    auto host = node.Upgrade();
    CHECK_NULL_RETURN(host, false);
    CHECK_NULL_RETURN(clickEventActuator_, false);
    auto click = clickEventActuator_->GetClickEvent();
    CHECK_NULL_RETURN(click, false);
    GestureEvent info;
    info.SetSourceDevice(event.sourceType);
    info.SetTimeStamp(event.timeStamp);
    EventTarget target;
    target.id = host->GetInspectorId().value_or("").c_str();
    target.type = host->GetTag();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto offset = geometryNode->GetFrameOffset();
    auto size = geometryNode->GetFrameSize();
    target.area.SetOffset(DimensionOffset(offset));
    target.area.SetHeight(Dimension(size.Height()));
    target.area.SetWidth(Dimension(size.Width()));
    target.origin = DimensionOffset(host->GetOffsetRelativeToWindow() - offset);
    info.SetTarget(target);
    click(info);
    return true;
}

bool GestureEventHub::IsAccessibilityClickable()
{
    return IsClickable() || GetAccessibilityRecognizer<ClickRecognizer>() != nullptr;
}

bool GestureEventHub::IsAccessibilityLongClickable()
{
    return IsLongClickable() || GetAccessibilityRecognizer<LongPressRecognizer>() != nullptr;
}

bool GestureEventHub::GetMonopolizeEvents() const
{
    return monopolizeEvents_;
}

void GestureEventHub::SetMonopolizeEvents(bool monopolizeEvents)
{
    monopolizeEvents_ = monopolizeEvents;
}

void GestureEventHub::ClearUserOnClick()
{
    if (clickEventActuator_) {
        clickEventActuator_->ClearUserCallback();
    }
}

void GestureEventHub::ClearUserOnTouch()
{
    if (touchEventActuator_) {
        touchEventActuator_->ClearUserCallback();
    }
}

void GestureEventHub::ClearJSFrameNodeOnClick()
{
    if (clickEventActuator_) {
        clickEventActuator_->ClearJSFrameNodeCallback();
    }
}

void GestureEventHub::ClearJSFrameNodeOnTouch()
{
    if (touchEventActuator_) {
        touchEventActuator_->ClearJSFrameNodeCallback();
    }
}

void GestureEventHub::CopyGestures(const RefPtr<GestureEventHub>& gestureEventHub)
{
    CHECK_NULL_VOID(gestureEventHub);
    gestures_ = gestureEventHub->backupGestures_;
    modifierGestures_ = gestureEventHub->backupModifierGestures_;
    recreateGesture_ = true;
    UpdateModifierGestureHierarchy();
}

void GestureEventHub::CopyEvent(const RefPtr<GestureEventHub>& gestureEventHub)
{
    CHECK_NULL_VOID(gestureEventHub);
    auto originalTouchEventActuator = gestureEventHub->touchEventActuator_;
    if (originalTouchEventActuator) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
        touchEventActuator_->CopyTouchEvent(originalTouchEventActuator);
    }

    auto originalClickEventActuator = gestureEventHub->clickEventActuator_;
    if (originalClickEventActuator) {
        clickEventActuator_ = MakeRefPtr<ClickEventActuator>(WeakClaim(this));
        clickEventActuator_->CopyClickEvent(originalClickEventActuator);
    }

    auto originalLongPressEventActuator = gestureEventHub->longPressEventActuator_;
    if (originalLongPressEventActuator) {
        longPressEventActuator_ = MakeRefPtr<LongPressEventActuator>(WeakClaim(this));
        longPressEventActuator_->CopyLongPressEvent(originalLongPressEventActuator);
    }

    auto originalDragEventActuator = gestureEventHub->dragEventActuator_;
    if (originalDragEventActuator) {
        dragEventActuator_ = MakeRefPtr<DragEventActuator>(WeakClaim(this), originalDragEventActuator->GetDirection(),
            originalDragEventActuator->GetFingers(), originalDragEventActuator->GetDistance());
        dragEventActuator_->CopyDragEvent(originalDragEventActuator);
        InitDragDropEvent();
    }
    auto originalShowMenu = gestureEventHub->showMenu_;
    if (originalShowMenu) {
        if (showMenu_) {
            RemoveClickEvent(showMenu_);
        }
        auto originalGetGestureEventFunc = originalShowMenu->GetGestureEventFunc();
        showMenu_= MakeRefPtr<ClickEvent>(std::move(originalGetGestureEventFunc));
        AddClickEvent(showMenu_);
    }
}

bool GestureEventHub::IsTextCategoryComponent(const std::string& frameTag)
{
    return frameTag == V2::TEXTAREA_ETS_TAG || frameTag == V2::TEXT_ETS_TAG ||
           frameTag == V2::TEXTINPUT_ETS_TAG || frameTag == V2::SEARCH_Field_ETS_TAG ||
           frameTag == V2::RICH_EDITOR_ETS_TAG;
}

void GestureEventHub::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    responseRegion_ = responseRegion;
    if (!responseRegion_.empty()) {
        isResponseRegion_ = true;
    }
    if (responseRegionFunc_) {
        responseRegionFunc_(responseRegion_);
    }
}

void GestureEventHub::RemoveLastResponseRect()
{
    if (responseRegion_.empty()) {
        isResponseRegion_ = false;
        return;
    }
    responseRegion_.pop_back();
    if (responseRegion_.empty()) {
        isResponseRegion_ = false;
    }

    if (responseRegionFunc_) {
        responseRegionFunc_(responseRegion_);
    }
}

void GestureEventHub::SetOnTouchEvent(TouchEventFunc&& touchEventFunc)
{
    if (!touchEventActuator_) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
    }
    touchEventActuator_->SetOnTouchEvent(std::move(touchEventFunc));
}

void GestureEventHub::SetJSFrameNodeOnTouchEvent(TouchEventFunc&& touchEventFunc)
{
    if (!touchEventActuator_) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
    }
    touchEventActuator_->SetJSFrameNodeOnTouchEvent(std::move(touchEventFunc));
}

void GestureEventHub::RemoveGesturesByTag(const std::string& gestureTag)
{
    bool needRecollect = false;
    for (auto iter = modifierGestures_.begin(); iter != modifierGestures_.end();) {
        auto tag = (*iter)->GetTag();
        if (tag.has_value() && tag.value() == gestureTag) {
            iter = modifierGestures_.erase(iter);
            backupModifierGestures_.remove(*iter);
            needRecollect = true;
        } else {
            auto group = AceType::DynamicCast<GestureGroup>(*iter);
            if (group) {
                group->RemoveChildrenByTag(gestureTag, needRecollect);
            }
            iter++;
        }
    }
    if (needRecollect) {
        needRecollect_ = true;
        UpdateModifierGestureHierarchy();
    }
}

void GestureEventHub::ClearModifierGesture()
{
    modifierGestures_.clear();
    backupModifierGestures_.clear();
    UpdateModifierGestureHierarchy();
}

void GestureEventHub::AddGesture(const RefPtr<NG::Gesture>& gesture)
{
    if (!recreateGesture_) {
        gestures_.clear();
        backupGestures_.clear();
    }
    gestures_.emplace_back(gesture);
    backupGestures_.emplace_back(gesture);
    recreateGesture_ = true;
}

void GestureEventHub::ClearGesture()
{
    gestures_.clear();
    backupGestures_.clear();
    recreateGesture_ = true;
}

void GestureEventHub::AttachGesture(const RefPtr<NG::Gesture>& gesture)
{
    modifierGestures_.emplace_back(gesture);
    backupModifierGestures_.emplace_back(gesture);
    UpdateModifierGestureHierarchy();
}

void GestureEventHub::RemoveGesture(const RefPtr<NG::Gesture>& gesture)
{
    modifierGestures_.remove(gesture);
    backupModifierGestures_.remove(gesture);
    UpdateModifierGestureHierarchy();
}

void GestureEventHub::AddScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
{
    if (!scrollableActuator_) {
        scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
    }
    scrollableActuator_->AddScrollableEvent(scrollableEvent);
}

void GestureEventHub::RemoveScrollableEvent(const RefPtr<ScrollableEvent>& scrollableEvent)
{
    if (!scrollableActuator_) {
        return;
    }
    scrollableActuator_->RemoveScrollableEvent(scrollableEvent);
}

void GestureEventHub::AddScrollEdgeEffect(const Axis& axis, RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    if (!scrollableActuator_) {
        scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
    }
    scrollableActuator_->AddScrollEdgeEffect(axis, scrollEffect);
}

void GestureEventHub::RemoveScrollEdgeEffect(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    if (!scrollableActuator_) {
        return;
    }
    scrollableActuator_->RemoveScrollEdgeEffect(scrollEffect);
}

// Set by user define, which will replace old one.
void GestureEventHub::SetTouchEvent(TouchEventFunc&& touchEventFunc)
{
    if (!touchEventActuator_) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
    }
    touchEventActuator_->ReplaceTouchEvent(std::move(touchEventFunc));
}

void GestureEventHub::AddTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
{
    if (!touchEventActuator_) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
    }
    touchEventActuator_->AddTouchEvent(touchEvent);
}

void GestureEventHub::AddTouchAfterEvent(const RefPtr<TouchEventImpl>& touchEvent)
{
    if (!touchEventActuator_) {
        touchEventActuator_ = MakeRefPtr<TouchEventActuator>();
    }
    touchEventActuator_->AddTouchAfterEvent(touchEvent);
}

void GestureEventHub::RemoveTouchEvent(const RefPtr<TouchEventImpl>& touchEvent)
{
    if (!touchEventActuator_) {
        return;
    }
    touchEventActuator_->RemoveTouchEvent(touchEvent);
}

bool GestureEventHub::IsClickable() const
{
    return clickEventActuator_ != nullptr;
}

bool GestureEventHub::IsComponentClickable() const
{
    return clickEventActuator_ && clickEventActuator_->IsComponentClickable();
}

bool GestureEventHub::IsUserClickable() const
{
    return clickEventActuator_ != nullptr && clickEventActuator_->IsUserClickable();
}

GestureJudgeFunc GestureEventHub::GetOnGestureJudgeBeginCallback() const
{
    return gestureJudgeFunc_;
}

GestureJudgeFunc GestureEventHub::GetOnGestureJudgeNativeBeginCallback() const
{
    return gestureJudgeNativeFunc_;
}

void GestureEventHub::RemoveClickEvent(const RefPtr<ClickEvent>& clickEvent)
{
    if (!clickEventActuator_) {
        return;
    }
    clickEventActuator_->RemoveClickEvent(clickEvent);
}

bool GestureEventHub::IsClickEventsEmpty() const
{
    if (!clickEventActuator_) {
        return true;
    }
    return clickEventActuator_->IsClickEventsEmpty();
}

GestureEventFunc GestureEventHub::GetClickEvent()
{
    if (!IsClickable()) {
        return nullptr;
    }
    return clickEventActuator_->GetClickEvent();
}

bool GestureEventHub::IsLongClickable() const
{
    return longPressEventActuator_ != nullptr;
}

void GestureEventHub::SetRedirectClick(bool redirectClick)
{
    redirectClick_ = redirectClick;
}

void GestureEventHub::SetLongPressEvent(
    const RefPtr<LongPressEvent>& event, bool isForDrag, bool isDisableMouseLeft, int32_t duration)
{
    if (!longPressEventActuator_) {
        longPressEventActuator_ = MakeRefPtr<LongPressEventActuator>(WeakClaim(this));
        longPressEventActuator_->SetOnAccessibility(GetOnAccessibilityEventFunc());
    }
    longPressEventActuator_->SetLongPressEvent(event, isForDrag, isDisableMouseLeft);
    longPressEventActuator_->SetDuration(duration);
}

// Set by user define, which will replace old one.
void GestureEventHub::SetPanEvent(
    const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance)
{
    if (!panEventActuator_) {
        panEventActuator_ = MakeRefPtr<PanEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    panEventActuator_->ReplacePanEvent(panEvent);
}

void GestureEventHub::AddPanEvent(
    const RefPtr<PanEvent>& panEvent, PanDirection direction, int32_t fingers, Dimension distance)
{
    if (!panEventActuator_ || direction.type != panEventActuator_->GetDirection().type) {
        panEventActuator_ = MakeRefPtr<PanEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    panEventActuator_->AddPanEvent(panEvent);
}

void GestureEventHub::RemovePanEvent(const RefPtr<PanEvent>& panEvent)
{
    if (!panEventActuator_) {
        return;
    }
    panEventActuator_->RemovePanEvent(panEvent);
}

void GestureEventHub::SetPanEventType(GestureTypeName typeName)
{
    CHECK_NULL_VOID(panEventActuator_);
    panEventActuator_->SetPanEventType(typeName);
}

HitTestMode GestureEventHub::GetHitTestMode() const
{
    return hitTestMode_;
}

void GestureEventHub::SetHitTestMode(HitTestMode hitTestMode)
{
    hitTestMode_ = hitTestMode;
}

const std::vector<DimensionRect>& GestureEventHub::GetResponseRegion() const
{
    return responseRegion_;
}

const std::vector<DimensionRect>& GestureEventHub::GetMouseResponseRegion() const
{
    return mouseResponseRegion_;
}

void GestureEventHub::SetResponseRegionFunc(const OnReponseRegionFunc& func)
{
    responseRegionFunc_ = func;
}

void GestureEventHub::SetOnTouchTestFunc(OnChildTouchTestFunc&& callback)
{
    onChildTouchTestFunc_ = callback;
}

const OnChildTouchTestFunc& GestureEventHub::GetOnTouchTestFunc()
{
    return onChildTouchTestFunc_;
}

void GestureEventHub::SetMouseResponseRegion(const std::vector<DimensionRect>& mouseResponseRegion)
{
    mouseResponseRegion_ = mouseResponseRegion;
    if (!mouseResponseRegion_.empty()) {
        isResponseRegion_ = true;
    }
}

void GestureEventHub::AddResponseRect(const DimensionRect& responseRect)
{
    responseRegion_.emplace_back(responseRect);
    isResponseRegion_ = true;

    if (responseRegionFunc_) {
        responseRegionFunc_(responseRegion_);
    }
}

bool GestureEventHub::GetTouchable() const
{
    return touchable_;
}

void GestureEventHub::SetTouchable(bool touchable)
{
    touchable_ = touchable;
}

RefPtr<LongPressRecognizer> GestureEventHub::GetLongPressRecognizer() const
{
    CHECK_NULL_RETURN(longPressEventActuator_, nullptr);
    return longPressEventActuator_->GetLongPressRecognizer();
}

void GestureEventHub::SetIsAllowMouse(bool isAllowMouse) const
{
    CHECK_NULL_VOID(panEventActuator_);
    panEventActuator_->SetIsAllowMouse(isAllowMouse);
}

const RefPtr<ClickEventActuator>& GestureEventHub::GetUserClickEventActuator()
{
    return userParallelClickEventActuator_;
}

void GestureEventHub::CleanExternalRecognizers()
{
    externalParallelRecognizer_.clear();
    externalExclusiveRecognizer_.clear();
}

void GestureEventHub::CleanInnerRecognizer()
{
    innerExclusiveRecognizer_ = nullptr;
}

void GestureEventHub::CleanNodeRecognizer()
{
    nodeParallelRecognizer_ = nullptr;
    nodeExclusiveRecognizer_ = nullptr;
}

bool GestureEventHub::WillRecreateGesture() const
{
    return recreateGesture_;
}

bool GestureEventHub::IsGestureEmpty() const
{
    return gestures_.empty();
}

bool GestureEventHub::IsPanEventEmpty() const
{
    if (panEventActuator_) {
        return panEventActuator_->IsPanEventEmpty();
    }
    return true;
}

void GestureEventHub::SetExcludedAxisForPanEvent(bool isExcludedAxis)
{
    CHECK_NULL_VOID(panEventActuator_);
    panEventActuator_->SetExcludedAxis(isExcludedAxis);
}

void GestureEventHub::DumpVelocityInfoFroPanEvent(int32_t fingerId)
{
    CHECK_NULL_VOID(panEventActuator_);
    panEventActuator_->DumpVelocityInfo(fingerId);
}
} // namespace OHOS::Ace::NG

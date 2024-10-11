/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/time_util.h"
#include "base/image/image_source.h"
#include "core/common/container.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#if defined(PIXEL_MAP_SUPPORTED)
#include "image_source.h"
#endif

#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#ifdef WEB_SUPPORTED
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#endif
namespace OHOS::Ace::NG {
namespace {
#if defined(PIXEL_MAP_SUPPORTED)
constexpr int32_t CREATE_PIXELMAP_TIME = 30;
constexpr int32_t MAX_BUILDER_DEPTH = 5;
#endif
constexpr uint32_t EXTRA_INFO_MAX_LENGTH = 200;
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 250;
constexpr float PIXELMAP_OPACITY_RATE = 0.95f;
} // namespace
const std::string DEFAULT_MOUSE_DRAG_IMAGE { "/system/etc/device_status/drag_icon/Copy_Drag.svg" };
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
    if (dragEventActuator_) {
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

bool GestureEventHub::IsPixelMapNeedScale() const
{
    CHECK_NULL_RETURN(pixelMap_, false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto width = pixelMap_->GetWidth();
    auto maxWidth = DragDropManager::GetMaxWidthBaseOnGridSystem(frameNode->GetContextRefPtr());
    if (!frameNode->GetDragPreviewOption().isScaleEnabled || width == 0 || width < maxWidth) {
        return false;
    }
    return true;
}

void GestureEventHub::InitDragDropEvent()
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->HandleOnDragStart(info);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->HandleOnDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto gestureEventHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->HandleOnDragEnd(info);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto gestureEventHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->HandleOnDragCancel();
    };

    auto dragEvent = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    auto distance = SystemProperties::GetDragStartPanDistanceThreshold();
    SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, Dimension(distance, DimensionUnit::VP));
}

bool GestureEventHub::IsAllowedDrag(RefPtr<EventHub> eventHub)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);

    if (frameNode->IsDraggable()) {
        if (!eventHub->HasOnDragStart() && !pattern->DefaultSupportDrag()) {
            return false;
        }
    } else {
        if (frameNode->IsUserSet()) {
            return false;
        }
        if (!eventHub->HasOnDragStart() && !pattern->DefaultSupportDrag()) {
            return false;
        }
    }
    return true;
}

void GestureEventHub::StartLongPressActionForWeb()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop start long press action for web");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);

    taskScheduler->PostTask(
        [weak = WeakClaim(this)]() {
            auto gestureHub = weak.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            auto dragEventActuator = gestureHub->dragEventActuator_;
            CHECK_NULL_VOID(dragEventActuator);
            dragEventActuator->StartLongPressActionForWeb();
        },
        TaskExecutor::TaskType::UI, "ArkUIGestureWebStartLongPress");
}

void GestureEventHub::CancelDragForWeb()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop cancel drag for web");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);

    taskScheduler->PostTask(
        [weak = WeakClaim(this)]() {
            auto gestureHub = weak.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            auto dragEventActuator = gestureHub->dragEventActuator_;
            CHECK_NULL_VOID(dragEventActuator);
            dragEventActuator->CancelDragForWeb();
        },
        TaskExecutor::TaskType::UI, "ArkUIGestureWebCancelDrag");
}

void GestureEventHub::ResetDragActionForWeb()
{
    TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop reset drag action for web");
    isReceivedDragGestureInfo_ = false;
    CHECK_NULL_VOID(dragEventActuator_);
    dragEventActuator_->ResetDragActionForWeb();

    // fix drag failed when long press drag after 500ms and before 800ms
    // need to reset the state of the drag manager
    auto pipeLine = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeLine);
    auto dragDropManager = pipeLine->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ResetDragging();
}

void GestureEventHub::StartDragTaskForWeb()
{
    if (!isReceivedDragGestureInfo_) {
        TAG_LOGW(AceLogTag::ACE_WEB, "DragDrop StartDragTaskForWeb failed,"
            "because not recv gesture info");
        return;
    }

    isReceivedDragGestureInfo_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);

    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop post a task to start drag for web");
    taskScheduler->PostTask(
        [weak = WeakClaim(this)]() {
            auto gestureHub = weak.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            auto dragEventActuator = gestureHub->dragEventActuator_;
            CHECK_NULL_VOID(dragEventActuator);
            CHECK_NULL_VOID(gestureHub->gestureInfoForWeb_);
            TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop start drag task for web in async task");
            dragEventActuator->StartDragTaskForWeb(*gestureHub->gestureInfoForWeb_);
        },
        TaskExecutor::TaskType::UI, "ArkUIGestureWebStartDrag");
}

RefPtr<PixelMap> CreatePixelMapFromString(const std::string& filePath)
{
    auto imageSource = ImageSource::Create(filePath);
    CHECK_NULL_RETURN(imageSource, nullptr);
    RefPtr<PixelMap> pixelMap = imageSource->CreatePixelMap();
    return pixelMap;
}

OffsetF GestureEventHub::GetPixelMapOffset(
    const GestureEvent& info, const SizeF& size, const float scale, bool isCalculateInSubwindow) const
{
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, result);
    auto frameTag = frameNode->GetTag();
    auto coordinateX = frameNodeOffset_.GetX();
    auto coordinateY = frameNodeOffset_.GetY();
    if (NearZero(frameNodeSize_.Width()) || NearZero(size.Width()) || isCalculateInSubwindow) {
        result.SetX(scale * (coordinateX - info.GetGlobalLocation().GetX()));
        result.SetY(scale * (coordinateY - info.GetGlobalLocation().GetY()));
    } else {
        auto rateX = (info.GetGlobalLocation().GetX() - coordinateX) / frameNodeSize_.Width();
        auto rateY = (info.GetGlobalLocation().GetY() - coordinateY) / frameNodeSize_.Height();
        result.SetX(-rateX * size.Width());
        result.SetY(-rateY * size.Height());
    }
    if (result.GetX() >= 0.0f) {
        result.SetX(-1.0f);
    }
    if (result.GetX() + size.Width() <= 0.0f) {
        result.SetX(1.0f - size.Width());
    }
    if (result.GetY() >= 0.0f) {
        result.SetY(-1.0f);
    }
    if (result.GetY() + size.Height() <= 0.0f) {
        result.SetY(1.0f - size.Height());
    }
    TAG_LOGD(AceLogTag::ACE_DRAG, "Get pixelMap offset is %{public}f and %{public}f.",
        result.GetX(), result.GetY());
    return result;
}

RefPtr<PixelMap> GestureEventHub::GetPreScaledPixelMapIfExist(float targetScale, RefPtr<PixelMap> defaultPixelMap)
{
    ACE_SCOPED_TRACE("drag: get scaled pixmal, %f", targetScale);
    float preScale = 1.0f;
    CHECK_NULL_RETURN(dragEventActuator_, defaultPixelMap);
    RefPtr<PixelMap> preScaledPixelMap = dragEventActuator_->GetPreScaledPixelMapForDragThroughTouch(preScale);
    if (preScale == targetScale && preScaledPixelMap != nullptr) {
        return preScaledPixelMap;
    }
#if defined(PIXEL_MAP_SUPPORTED)
    preScaledPixelMap = PixelMap::CopyPixelMap(defaultPixelMap);
    if (!preScaledPixelMap) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "duplicate PixelMap failed!");
        preScaledPixelMap = defaultPixelMap;
    }
    if (!NearEqual(targetScale, 1.0f)) {
        preScaledPixelMap->Scale(targetScale, targetScale, AceAntiAliasingOption::HIGH);
    }
#else
    preScaledPixelMap = defaultPixelMap;
#endif
    return preScaledPixelMap;
}

float GestureEventHub::GetPixelMapScale(const int32_t height, const int32_t width) const
{
    float scale = 1.0f;
    if (height == 0 || width == 0) {
        return scale;
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, scale);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, scale);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, scale);
    auto windowScale = dragDropManager->GetWindowScale();
    if (!frameNode->GetDragPreviewOption().isScaleEnabled || !(frameNode->GetTag() == V2::WEB_ETS_TAG)) {
        return scale * windowScale;
    }
    int32_t deviceHeight = SystemProperties::GetDevicePhysicalHeight();
    int32_t deviceWidth = SystemProperties::GetDevicePhysicalWidth();
    int32_t maxDeviceLength = std::max(deviceHeight, deviceWidth);
    int32_t minDeviceLength = std::min(deviceHeight, deviceWidth);
    if (maxDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE > minDeviceLength) {
        if (height > minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE) {
            scale = static_cast<float>(minDeviceLength * PIXELMAP_DEFALUT_LIMIT_SCALE) / height;
        }
    } else {
        if (GetTextDraggable() && height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE &&
            width > minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE) {
            scale = fmin(static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / height,
                static_cast<float>(minDeviceLength * PIXELMAP_DRAG_WGR_TEXT_SCALE / PIXELMAP_DRAG_WGR_SCALE) / width);
        } else if (height > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE &&
                   width > minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) {
            scale = fmin(static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / height,
                static_cast<float>(minDeviceLength / PIXELMAP_DRAG_WGR_SCALE) / width);
        }
    }
    return scale * windowScale;
}

void GestureEventHub::GenerateMousePixelMap(const GestureEvent& info)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<RenderContext> context;
    if (GetTextDraggable()) {
        auto pattern = frameNode->GetPattern<TextDragBase>();
        CHECK_NULL_VOID(pattern);
        auto dragNode = pattern->MoveDragNode();
        CHECK_NULL_VOID(dragNode);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushPipelineImmediately();
        context = dragNode->GetRenderContext();
    } else {
        context = frameNode->GetRenderContext();
    }
    CHECK_NULL_VOID(context);
    auto thumbnailPixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(thumbnailPixelMap);
    SetPixelMap(thumbnailPixelMap);
}

void GestureEventHub::HandleNotallowDrag(const GestureEvent& info)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        gestureInfoForWeb_ = std::make_shared<GestureEvent>(info);
        isReceivedDragGestureInfo_ = true;
        TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop drag gesture info received");
    }
}

void GestureEventHub::HandleOnDragStart(const GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "Start handle onDragStart.");
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDragStart()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "FrameNode is not set onDragStart event.");
        return;
    }

    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (!IsAllowedDrag(eventHub)) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "FrameNode is not allow drag, tag is %{public}s, id is %{public}s,"
            "draggable is %{public}d, drag start event is %{public}d,"
            "default support drag is %{public}d, user set is %{public}d.",
            frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str(),
            frameNode->IsDraggable(), eventHub->HasOnDragStart(),
            pattern->DefaultSupportDrag(), frameNode->IsUserSet());
        HandleNotallowDrag(info);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && eventManager->IsLastMoveBeforeUp()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Drag stop because user release mouse button");
        return;
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        SetMouseDragMonitorState(true);
    }

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        event->SetX(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
        event->SetY(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    } else {
        event->SetX(info.GetGlobalPoint().GetX());
        event->SetY(info.GetGlobalPoint().GetY());
    }
    event->SetScreenX(info.GetScreenLocation().GetX());
    event->SetScreenY(info.GetScreenLocation().GetY());
    event->SetDisplayX(info.GetScreenLocation().GetX());
    event->SetDisplayY(info.GetScreenLocation().GetY());
    event->SetSourceTool(info.GetSourceTool());

    auto frameTag = frameNode->GetTag();
    auto hostPattern = frameNode->GetPattern<TextDragBase>();
    if (hostPattern && GetTextDraggable() && (frameTag == V2::RICH_EDITOR_ETS_TAG || frameTag == V2::TEXT_ETS_TAG ||
                        frameTag == V2::TEXTINPUT_ETS_TAG || frameTag == V2::SEARCH_Field_ETS_TAG)) {
        frameNodeOffset_ = hostPattern->GetDragUpperLeftCoordinates();
        frameNodeSize_ = SizeF(0.0f, 0.0f);
    } else {
        auto geometryNode = frameNode->GetGeometryNode();
        if (geometryNode) {
            frameNodeSize_ = geometryNode->GetFrameSize();
        } else {
            frameNodeSize_ = SizeF(0.0f, 0.0f);
        }
        auto rectCenter = frameNode->GetPaintRectCenter(false);
        frameNodeOffset_ = OffsetF(rectCenter.GetX() - frameNodeSize_.Width() / 2.0f,
            rectCenter.GetY() - frameNodeSize_.Height() / 2.0f);
#ifdef WEB_SUPPORTED
        if (frameTag == V2::WEB_ETS_TAG) {
            auto webPattern = frameNode->GetPattern<WebPattern>();
            if (webPattern) {
                frameNodeOffset_.SetX(frameNodeOffset_.GetX() + webPattern->GetDragOffset().GetX());
                frameNodeOffset_.SetY(frameNodeOffset_.GetY() + webPattern->GetDragOffset().GetY());
                frameNodeSize_ = webPattern->GetDragPixelMapSize();
            }
        }
#endif
    }
    /*
     * Users may remove frameNode in the js callback function "onDragStart "triggered below,
     * so save the offset of the framenode relative to the window in advance
     */
    DragDropInfo dragPreviewInfo;
    auto dragDropInfo = GetDragDropInfo(info, frameNode, dragPreviewInfo, event);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDraggingPointer(info.GetPointerId());
    dragDropManager->SetDraggingPressedState(true);
    if (dragPreviewInfo.inspectorId != "") {
        ACE_SCOPED_TRACE("drag: handling with inspector");
        auto dragPreviewPixelMap = GetDragPreviewPixelMap();
        TAG_LOGI(AceLogTag::ACE_DRAG, "InspectorId exist, get thumbnail.");
        if (dragPreviewPixelMap == nullptr) {
            dragPreviewPixelMap = DragEventActuator::GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
        }
        dragDropInfo.pixelMap = dragPreviewPixelMap;
        OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
        return;
    }

    if (info.GetSourceDevice() != SourceType::MOUSE) {
        if (dragPreviewInfo.pixelMap != nullptr || dragPreviewInfo.customNode != nullptr) {
            if (dragPreviewPixelMap_ != nullptr) {
                ACE_SCOPED_TRACE("drag: handling with drag preview");
                TAG_LOGI(AceLogTag::ACE_DRAG, "Non-mouse dragging, get thumbnail.");
                dragDropInfo.pixelMap = dragPreviewPixelMap_;
                OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
                return;
            }
        }
    }

    if (dragPreviewInfo.pixelMap != nullptr) {
        ACE_SCOPED_TRACE("drag: handling with pixelmap directly");
        dragDropInfo.pixelMap = dragPreviewInfo.pixelMap;
        TAG_LOGI(AceLogTag::ACE_DRAG, "PixelMap exist, get thumbnail.");
        OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
        return;
    } else if (dragPreviewInfo.customNode != nullptr) {
        dragDropInfo.customNode = dragPreviewInfo.customNode;
    }

#if defined(PIXEL_MAP_SUPPORTED)
    if (dragDropInfo.pixelMap == nullptr && dragDropInfo.customNode) {
        ACE_SCOPED_TRACE("drag: handling for custom builder");
        StartDragForCustomBuilder(info, pipeline, frameNode, dragDropInfo, event);
        return;
    }
#endif
    TAG_LOGI(AceLogTag::ACE_DRAG, "DragDropInfo is empty.");
    ACE_SCOPED_TRACE("drag: handling without preview");
    OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
}

void GestureEventHub::OnDragStart(const GestureEvent& info, const RefPtr<PipelineBase>& context,
    const RefPtr<FrameNode> frameNode, DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    ACE_SCOPED_TRACE("drag: to start");
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(pipeline);

    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (dragDropProxy_) {
        dragDropProxy_ = nullptr;
    }
    CHECK_NULL_VOID(dragEvent);
    auto eventRet = dragEvent->GetResult();
    if (eventRet == DragRet::DRAG_FAIL || eventRet == DragRet::DRAG_CANCEL) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Drag result is %{public}d, stop dragging.", eventRet);
        if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            SetMouseDragMonitorState(false);
        }
        return;
    }
    std::string udKey;
    int32_t recordsSize = 1;
    auto unifiedData = GetUnifiedData(frameNode->GetTag(), dragDropInfo, dragEvent);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->ResetDragOption();
    if (pattern->GetDragRecordSize() >= 0) {
        recordsSize = pattern->GetDragRecordSize();
    } else if (unifiedData) {
        auto recordSize = unifiedData->GetSize();
        recordsSize = recordSize > 1 ? recordSize : 1;
    }
    auto ret = SetDragData(unifiedData, udKey);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "UDMF set data failed, return value is %{public}d", ret);
    }

    std::map<std::string, int64_t> summary;
    ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "UDMF get summary failed, return value is %{public}d", ret);
    }
    dragDropManager->SetSummaryMap(summary);
    RefPtr<PixelMap> pixelMap;
    if (dragDropInfo.pixelMap != nullptr) {
        pixelMap = dragDropInfo.pixelMap;
        SetPixelMap(dragDropInfo.pixelMap);
    } else if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "no any pixmap got, get node snapshot final try");
        ACE_SCOPED_TRACE("drag: no any pixmap got, get node snapshot final try");
        if (!GetTextDraggable()) {
            GenerateMousePixelMap(info);
        }
        if (pixelMap_) {
            pixelMap = pixelMap_;
        } else {
            pixelMap = CreatePixelMapFromString(DEFAULT_MOUSE_DRAG_IMAGE);
        }
    } else {
        if (pixelMap_ == nullptr) {
            FireCustomerOnDragEnd(pipeline, eventHub);
            TAG_LOGW(AceLogTag::ACE_DRAG, "Thumbnail pixelMap is empty.");
            if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
                SetMouseDragMonitorState(false);
            }
            return;
        }
        pixelMap = pixelMap_;
    }
    SetDragGatherPixelMaps(info);
    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    auto badgeNumber = dragPreviewOptions.GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        recordsSize = badgeNumber.value();
    }
    dragDropManager->SetIsMouseDrag(info.GetInputEventType() == InputEventType::MOUSE_BUTTON);
    auto dragNodePipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(dragNodePipeline);
    auto overlayManager = dragNodePipeline->GetOverlayManager();
    bool isSwitchToSubWindow = false;
    RefPtr<FrameNode> imageNode = nullptr;
    RefPtr<FrameNode> textNode = nullptr;
    RefPtr<OverlayManager> subWindowOverlayManager = nullptr;
    RefPtr<Subwindow> subWindow = nullptr;
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    if (isMenuShow) {
        dragDropManager->SetIsDragWithContextMenu(true);
        TAG_LOGI(AceLogTag::ACE_DRAG, "Drag with contextMenu.");
    } else {
        dragDropManager->SetIsDragWithContextMenu(false);
    }
    float defaultPixelMapScale =
        info.GetInputEventType() == InputEventType::MOUSE_BUTTON ? 1.0f : DEFALUT_DRAG_PPIXELMAP_SCALE;
    // use menuPreviewScale for drag framework. this is not final solution.
    if (isMenuShow && GreatNotEqual(menuPreviewScale_, 0.0f)) {
        auto menuPreviewRect = DragDropManager::GetMenuPreviewRect();
        if (GreatNotEqual(menuPreviewRect.Width(), 0.0f)) {
            frameNodeOffset_ = menuPreviewRect.GetOffset();
        }
        int32_t originPixelMapWidth = pixelMap ? pixelMap->GetWidth() : 0;
        if (GreatNotEqual(menuPreviewRect.Width(), 0.0f) && GreatNotEqual(originPixelMapWidth, 0.0f) &&
            menuPreviewRect.Width() < originPixelMapWidth * menuPreviewScale_) {
            defaultPixelMapScale = menuPreviewRect.Width() / originPixelMapWidth;
            menuPreviewScale_ = defaultPixelMapScale;
        } else {
            defaultPixelMapScale = menuPreviewScale_;
        }
    }
    auto windowScale = dragDropManager->GetWindowScale();
    float scale = windowScale * defaultPixelMapScale;
    auto focusHub = frameNode->GetFocusHub();
    bool hasContextMenu = focusHub == nullptr
                              ? false : focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
    bool isBindMenuPreview = GetPreviewMode() != MenuPreviewMode::NONE;
    if (IsNeedSwitchToSubWindow() || isMenuShow) {
        imageNode = overlayManager->GetPixelMapContentNode();
        DragEventActuator::CreatePreviewNode(frameNode, imageNode);
        CHECK_NULL_VOID(imageNode);
        auto originPoint = imageNode->GetPositionToWindowWithTransform();
        if (hasContextMenu || isMenuShow) {
            auto previewDragMovePosition = dragDropManager->GetUpdateDragMovePosition();
            OffsetF previewOffset;
            auto ret = SubwindowManager::GetInstance()->GetMenuPreviewCenter(previewOffset);
            if (isBindMenuPreview && ret) {
                previewOffset -= OffsetF(pixelMap->GetWidth() / 2.0f, pixelMap->GetHeight() / 2.0f);
                DragEventActuator::UpdatePreviewPositionAndScale(imageNode, previewDragMovePosition + previewOffset);
            } else {
                DragEventActuator::UpdatePreviewPositionAndScale(imageNode, previewDragMovePosition + originPoint);
            }

            dragDropManager->ResetContextMenuDragPosition();
        }

        auto frameTag = frameNode->GetTag();
        if (IsPixelMapNeedScale() && GetTextDraggable() && IsTextCategoryComponent(frameTag)) {
            auto textDragPattern = frameNode->GetPattern<TextDragBase>();
            CHECK_NULL_VOID(textDragPattern);
            auto dragNode = textDragPattern->MoveDragNode();
            if (dragNode) {
                auto dragNodeOffset = dragNode->GetPaintRectOffset();
                DragEventActuator::UpdatePreviewPositionAndScale(imageNode, dragNodeOffset);
            }
        }

        if (IsPixelMapNeedScale() && frameTag == V2::WEB_ETS_TAG) {
            OffsetF webOffset;
            CHECK_NULL_VOID(pipeline);
            auto window = pipeline->GetWindow();
            CHECK_NULL_VOID(window);
            auto offset = window->GetCurrentWindowRect().GetOffset();
            webOffset.SetX(frameNodeOffset_.GetX() + offset.GetX());
            webOffset.SetY(frameNodeOffset_.GetY() + offset.GetY());
            DragEventActuator::UpdatePreviewPositionAndScale(imageNode, webOffset);
        }

        CHECK_NULL_VOID(imageNode);
        float previewScale =
            info.GetInputEventType() == InputEventType::MOUSE_BUTTON ? 1.0f : DEFALUT_DRAG_PPIXELMAP_SCALE;
        if (IsPixelMapNeedScale()) {
            previewScale = static_cast<float>(imageNode->GetPreviewScaleVal());
            scale = previewScale * windowScale;
        }
        // use menu preview scale replace default pixelMap scale.
        if (isMenuShow) {
            auto imageGestureEventHub = imageNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(imageGestureEventHub);
            if (!IsPixelMapNeedScale()) {
                imageGestureEventHub->SetMenuPreviewScale(defaultPixelMapScale);
            } else {
                imageGestureEventHub->SetMenuPreviewScale(scale);
            }
        }
        auto childSize = badgeNumber.has_value() ? badgeNumber.value() : GetSelectItemSize();
        if (childSize >= 1) {
            recordsSize = childSize;
        }
        textNode = DragEventActuator::CreateBadgeTextNode(frameNode, childSize, previewScale, true);
        {
            ACE_SCOPED_TRACE("drag: sub window show");
            auto mainPipeline = PipelineContext::GetMainPipelineContext();
            subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline != mainPipeline));
        }
        if (subWindow) {
            subWindowOverlayManager = subWindow->GetOverlayManager();
            isSwitchToSubWindow = true;
            overlayManager->RemovePixelMap();
            if (pixelMap_ != nullptr) {
                pixelMap = pixelMap_;
            }
        }
    }
    if (!overlayManager->GetIsOnAnimation()) {
        if (dragEventActuator_ != nullptr) {
            dragEventActuator_->SetIsNotInPreviewState(true);
        }
    }
    RefPtr<PixelMap> pixelMapDuplicated = GetPreScaledPixelMapIfExist(scale, pixelMap);
    CHECK_NULL_VOID(dragEventActuator_);
    dragEventActuator_->ResetPreScaledPixelMapForDragThroughTouch();
    dragPreviewPixelMap_ = nullptr;
    CHECK_NULL_VOID(pixelMapDuplicated);
    auto width = pixelMapDuplicated->GetWidth();
    auto height = pixelMapDuplicated->GetHeight();
    auto pixelMapOffset = OffsetF();
    if (isMenuShow) {
        pixelMapOffset = GetPixelMapOffset(info, SizeF(width, height), scale / defaultPixelMapScale, true);
    } else {
        pixelMapOffset = GetPixelMapOffset(info, SizeF(width, height), scale);
    }
    windowScale = NearZero(windowScale) ? 1.0f : windowScale;
    dragDropManager->SetPixelMapOffset(pixelMapOffset / windowScale);
    DragEventActuator::ResetNode(frameNode);
    auto extraInfoLimited = dragDropInfo.extraInfo.size() > EXTRA_INFO_MAX_LENGTH
                                ? dragDropInfo.extraInfo.substr(EXTRA_INFO_MAX_LENGTH + 1)
                                : dragDropInfo.extraInfo;
    auto arkExtraInfoJson = JsonUtil::Create(true);
    auto dragNodeGrayscale = pipeline->GetDragNodeGrayscale();
    auto dipScale = pipeline->GetDipScale();
    arkExtraInfoJson->Put("scale", scale);
    arkExtraInfoJson->Put("dip_scale", dipScale);
    arkExtraInfoJson->Put("drag_node_gray_scale", dragNodeGrayscale);
    UpdateExtraInfo(frameNode, arkExtraInfoJson, scale);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto windowId = container->GetWindowId();
    ShadowInfoCore shadowInfo { pixelMapDuplicated, pixelMapOffset.GetX(), pixelMapOffset.GetY() };
    DragDataCore dragData { { shadowInfo }, {}, udKey, extraInfoLimited, arkExtraInfoJson->ToString(),
        static_cast<int32_t>(info.GetSourceDevice()), recordsSize, info.GetPointerId(), info.GetScreenLocation().GetX(),
        info.GetScreenLocation().GetY(), info.GetTargetDisplayId(), windowId, true, false, summary };
    std::string summarys;
    for (const auto& [udkey, recordSize] : summary) {
        std::string str = udkey + "-" + std::to_string(recordSize) + ";";
        summarys += str;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG,
        "Start drag, frameNode is %{public}s, id is %{public}s, pixelMap width %{public}d height %{public}d, "
        "scale is %{public}f, udkey %{public}s, recordsSize %{public}d, pointerId %{public}d, "
        "displayId %{public}d, windowId %{public}d, summary %{public}s.",
        frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str(), width, height, scale, udKey.c_str(),
        recordsSize, info.GetPointerId(), info.GetTargetDisplayId(), windowId, summarys.c_str());
    dragDropManager->GetGatherPixelMap(dragData, scale, width, height);
    {
        ACE_SCOPED_TRACE("drag: call msdp start drag");
        ret = InteractionInterface::GetInstance()->StartDrag(dragData, GetDragCallback(pipeline, eventHub));
    }
    if (ret != 0) {
        if (dragDropManager->IsNeedDisplayInSubwindow() && subWindowOverlayManager) {
            SubwindowManager::GetInstance()->HidePreviewNG();
            overlayManager->RemovePixelMap();
        }
        DragNotifyMsg notifyMessage;
        notifyMessage.isInnerAndOuterTriggerBothNeeded = false;
        auto dragCallBack = GetDragCallback(pipeline, eventHub);
        CHECK_NULL_VOID(dragCallBack);
        dragCallBack(notifyMessage);
        TAG_LOGW(AceLogTag::ACE_DRAG, "Start drag failed, return value is %{public}d", ret);
        return;
    }
    if (isSwitchToSubWindow && subWindowOverlayManager) {
        std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo;
        auto gatherNode = DragEventActuator::GetOrCreateGatherNode(overlayManager,
            dragEventActuator_, gatherNodeChildrenInfo);
        DragEventActuator::MountGatherNode(subWindowOverlayManager, frameNode, gatherNode, gatherNodeChildrenInfo);
        DragEventActuator::UpdatePreviewPositionAndScale(
            imageNode, imageNode->GetOffsetInSubwindow(subWindow->GetWindowRect().GetOffset()));
        if (textNode) {
            DragEventActuator::UpdatePreviewPositionAndScale(
                textNode, textNode->GetOffsetInSubwindow(subWindow->GetWindowRect().GetOffset()));
        }
        DragEventActuator::MountPixelMap(
            subWindowOverlayManager, eventHub->GetGestureEventHub(), imageNode, textNode, true);
        pipeline->FlushSyncGeometryNodeTasks();
        DragAnimationHelper::ShowBadgeAnimation(textNode);
        dragDropManager->DoDragStartAnimation(
            subWindowOverlayManager, info, eventHub->GetGestureEventHub(), isMenuShow);
        if (hasContextMenu) {
            //response: 0.347, dampingRatio: 0.99, blendDuration: 0.0
            const RefPtr<Curve> curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.347f, 0.99f, 0.0f);
            AnimationOption option;
            option.SetCurve(curve);
            option.SetDuration(PIXELMAP_ANIMATION_DURATION);
            auto renderContext = imageNode->GetRenderContext();
            AnimationUtils::Animate(
                option,
                [renderContext]() {
                    if (renderContext) {
                        renderContext->UpdateOpacity(PIXELMAP_OPACITY_RATE);
                    }
                },
                option.GetOnFinishEvent());
        }
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && IsNeedSwitchToSubWindow()) {
        ret = RegisterCoordinationListener(pipeline);
        if (ret != 0) {
            TAG_LOGW(AceLogTag::ACE_DRAG, "Register coordination listener failed, error is %{public}d", ret);
        }
    }
    dragDropManager->SetPreviewRect(Rect(pixelMapOffset.GetX(), pixelMapOffset.GetY(), width, height));
    dragDropManager->ResetRecordSize(static_cast<uint32_t>(recordsSize));
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    eventManager->DoMouseActionRelease();
    eventManager->SetIsDragging(true);
    if (info.GetInputEventType() != InputEventType::MOUSE_BUTTON && dragEventActuator_ != nullptr &&
        dragEventActuator_->GetIsNotInPreviewState()) {
        if (!dragDropManager->IsNeedDisplayInSubwindow() && !isMenuShow) {
            overlayManager->RemovePixelMap();
            overlayManager->RemovePreviewBadgeNode();
            overlayManager->RemoveGatherNode();
            pipeline->AddAfterRenderTask([]() {
                ACE_SCOPED_TRACE("drag: set drag window visible, touch");
                InteractionInterface::GetInstance()->SetDragWindowVisible(true);
            });
        }
    } else if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        if (!dragDropManager->IsNeedDisplayInSubwindow() && !isMenuShow) {
            pipeline->AddDragWindowVisibleTask([]() {
                ACE_SCOPED_TRACE("drag: set drag window visible, mouse");
                InteractionInterface::GetInstance()->SetDragWindowVisible(true);
            });
        }
        dragDropManager->SetIsDragWindowShow(true);
    }
    dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
    dragDropProxy_ = dragDropManager->CreateFrameworkDragDropProxy();
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragStart(info, extraInfoLimited, GetFrameNode());
    if (!dragDropManager->IsDraggingPressed(info.GetPointerId())) {
        dragDropManager->OnDragEnd(
            PointerEvent(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()), extraInfoLimited);
    }
}

void GestureEventHub::UpdateExtraInfo(const RefPtr<FrameNode>& frameNode,
    std::unique_ptr<JsonValue>& arkExtraInfoJson, float scale)
{
    double opacity = frameNode->GetDragPreviewOption().options.opacity;
    auto optionInfo = frameNode->GetDragPreviewOption().options;
    arkExtraInfoJson->Put("dip_opacity", opacity);
    TAG_LOGD(AceLogTag::ACE_DRAG, "The info of opacity update to the framework is %{public}s",
        arkExtraInfoJson->ToString().c_str());

    if (optionInfo.blurbgEffect.backGroundEffect.radius.IsValid()) {
        optionInfo.blurbgEffect.ToJsonValue(arkExtraInfoJson);
    }
    DragEventActuator::PrepareShadowParametersForDragData(frameNode, arkExtraInfoJson, scale);
    DragEventActuator::PrepareRadiusParametersForDragData(frameNode, arkExtraInfoJson);
}

int32_t GestureEventHub::RegisterCoordinationListener(const RefPtr<PipelineBase>& context)
{
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, -1);
    auto callback = [id = Container::CurrentId(), weak = WeakClaim(RawPtr(pipeline))]() {
        ContainerScope scope(id);
        auto context = weak.Upgrade();
        CHECK_NULL_VOID(context);
        auto dragDropManager = context->GetDragDropManager();
        CHECK_NULL_VOID(dragDropManager);
        auto taskScheduler = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask([dragDropManager]() { dragDropManager->HideDragPreviewOverlay(); },
            TaskExecutor::TaskType::UI, "ArkUIGestureHideDragPreviewOverlay");
    };
    return InteractionInterface::GetInstance()->RegisterCoordinationListener(callback);
}

void GestureEventHub::HandleOnDragUpdate(const GestureEvent& info)
{
    gestureInfoForWeb_ = std::make_shared<GestureEvent>(info);
    CHECK_NULL_VOID(dragDropProxy_);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    if (dragDropManager->IsDragged()) {
        dragDropProxy_->OnDragMove(info);
    }
}

void GestureEventHub::HandleOnDragEnd(const GestureEvent& info)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    const static int32_t PLATFORM_VERSION_TEN = 10;
    if (pipeline && (pipeline->GetMinPlatformVersion() < PLATFORM_VERSION_TEN)) {
        auto eventHub = eventHub_.Upgrade();
        CHECK_NULL_VOID(eventHub);

        auto frameNode = GetFrameNode();
        CHECK_NULL_VOID(frameNode);

        // Only the onDrop callback of dragged frame node is triggered.
        // The onDrop callback of target frame node is triggered in PipelineContext::OnDragEvent.
        if (eventHub->HasOnDrop() || eventHub->HasCustomerOnDrop()) {
            RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
            if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
                event->SetX(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
                event->SetY(pipeline->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
            } else {
                event->SetX(info.GetGlobalPoint().GetX());
                event->SetY(info.GetGlobalPoint().GetY());
            }
            event->SetScreenX(info.GetScreenLocation().GetX());
            event->SetScreenY(info.GetScreenLocation().GetY());
            event->SetPressedKeyCodes(info.GetPressedKeyCodes());
            eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, event);
            eventHub->HandleInternalOnDrop(event, "");
        }
    }
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
}

void GestureEventHub::HandleOnDragCancel()
{
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->DestroyDragWindow();
    dragDropProxy_ = nullptr;
}

void GestureEventHub::SetFocusClickEvent(GestureEventFunc&& clickEvent)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetFocusHub();
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
    } else {
        clickEventActuator_->SetUserCallback(std::move(clickEvent));
        SetFocusClickEvent(clickEventActuator_->GetClickEvent());
        auto clickRecognizer = clickEventActuator_->GetClickRecognizer();
        clickRecognizer->SetDistanceThreshold(distanceThreshold);
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

void GestureEventHub::AddClickEvent(const RefPtr<ClickEvent>& clickEvent, double distanceThreshold)
{
    CheckClickActuator();
    clickEventActuator_->AddClickEvent(clickEvent);
    clickEventActuator_->AddDistanceThreshold(distanceThreshold);

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
    clickEventTarget.id = host->GetId();
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
    longPressTarget.id = host->GetId();
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

std::string GestureEventHub::GetHitTestModeStr() const
{
    auto mode = static_cast<int32_t>(hitTestMode_);
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
    target.id = host->GetId();
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

int32_t GestureEventHub::SetDragData(const RefPtr<UnifiedData>& unifiedData, std::string& udKey)
{
    CHECK_NULL_RETURN(unifiedData, -1);
    return UdmfClient::GetInstance()->SetData(unifiedData, udKey);
}

OnDragCallbackCore GestureEventHub::GetDragCallback(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub)
{
    auto ret = [](const DragNotifyMsgCore& notifyMessage) {};
    auto eventHub = hub.Upgrade();
    CHECK_NULL_RETURN(eventHub, ret);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, ret);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskScheduler, ret);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, ret);
    auto eventManager = pipeline->GetEventManager();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto callback = [id = Container::CurrentId(), eventHub, dragEvent, taskScheduler, dragDropManager, eventManager](
                        const DragNotifyMsgCore& notifyMessage) {
        ContainerScope scope(id);
        taskScheduler->PostTask(
            [eventHub, dragEvent, dragDropManager, eventManager, notifyMessage, id]() {
                dragDropManager->SetDragResult(notifyMessage, dragEvent);
                dragDropManager->SetDragBehavior(notifyMessage, dragEvent);
                dragDropManager->DoDragReset();
                dragDropManager->SetIsDragged(false);
                dragDropManager->SetDraggingPointer(-1);
                dragDropManager->SetDraggingPressedState(false);
                dragDropManager->ResetDragPreviewInfo();
                dragDropManager->HideDragPreviewWindow(id);
                dragEvent->SetPressedKeyCodes(dragDropManager->GetDragDropPointerEvent().pressedKeyCodes_);
                auto ret = InteractionInterface::GetInstance()->UnRegisterCoordinationListener();
                if (ret != 0) {
                    TAG_LOGW(AceLogTag::ACE_DRAG, "Unregister coordination listener failed, error is %{public}d", ret);
                }
                if (eventManager) {
                    eventManager->DoMouseActionRelease();
                }
                if (notifyMessage.isInnerAndOuterTriggerBothNeeded) {
                    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEvent);
                }
                if (eventHub->HasOnDragEnd()) {
                    (eventHub->GetOnDragEnd())(dragEvent);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIGestureDragEnd");
    };
    return callback;
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

DragDropInfo GestureEventHub::GetDragDropInfo(const GestureEvent& info, const RefPtr<FrameNode> frameNode,
    DragDropInfo& dragPreviewInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    ACE_SCOPED_TRACE("drag: execute user onDragStart");
    DragDropInfo dragDropInfo;
    CHECK_NULL_RETURN(dragEventActuator_, dragDropInfo);
    dragEventActuator_->SetIsDefaultOnDragStartExecuted(false);
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_RETURN(eventHub, dragDropInfo);
    auto extraParams = eventHub->GetDragExtraParams(std::string(), info.GetGlobalPoint(), DragEventType::START);
    auto onDragStart = eventHub->GetOnDragStart();
    if (!onDragStart && eventHub->HasDefaultOnDragStart()) {
        onDragStart = eventHub->GetDefaultOnDragStart();
        dragEventActuator_->SetIsDefaultOnDragStartExecuted(true);
    }
    dragEvent->SetPressedKeyCodes(info.GetPressedKeyCodes());
    if (GetTextDraggable() && info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        GenerateMousePixelMap(info);
    }
    dragDropInfo = onDragStart(dragEvent, extraParams);

    auto frameTag = frameNode->GetTag();
    if (GetTextDraggable() && IsTextCategoryComponent(frameTag)) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Get drag drop info, pixelmap and customNode are set to null "
            "when frameTag is %{public}s", frameTag.c_str());
        dragDropInfo.pixelMap = nullptr;
        dragDropInfo.customNode = nullptr;
    } else {
        dragPreviewInfo = frameNode->GetDragPreview();
    }
    return dragDropInfo;
}

RefPtr<UnifiedData> GestureEventHub::GetUnifiedData(const std::string& frameTag, DragDropInfo& dragDropInfo,
    const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto unifiedData = dragEvent->GetData();
    bool hasData = static_cast<bool>(unifiedData);
    if (!unifiedData && eventHub->HasDefaultOnDragStart()) {
        auto defaultDropInfo = eventHub->GetDefaultOnDragStart()(dragEvent, "");
        if (dragDropInfo.extraInfo.empty()) {
            dragDropInfo.extraInfo = defaultDropInfo.extraInfo;
        }
        CHECK_NULL_RETURN(dragEventActuator_, nullptr);
        dragEventActuator_->SetIsDefaultOnDragStartExecuted(true);
        unifiedData = dragEvent->GetData();
    }
    auto defaultOnDragStart = eventHub->GetDefaultOnDragStart();
    CHECK_NULL_RETURN(defaultOnDragStart, unifiedData);
    if (hasData && IsTextCategoryComponent(frameTag) && !dragEventActuator_->IsDefaultOnDragStartExecuted()) {
        defaultOnDragStart(dragEvent, "");
    }
    return unifiedData;
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

void GestureEventHub::SetDragForbiddenForcely(bool isDragForbidden)
{
    isDragForbidden_ = isDragForbidden;
}

bool GestureEventHub::IsDragForbidden()
{
    return isDragForbidden_;
}

bool GestureEventHub::IsNeedSwitchToSubWindow() const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (IsPixelMapNeedScale()) {
        return true;
    }
    CHECK_NULL_RETURN(dragEventActuator_, false);
    return dragEventActuator_->IsNeedGather();
}

void GestureEventHub::SetDragGatherPixelMaps(const GestureEvent& info)
{
    CHECK_NULL_VOID(dragEventActuator_);
    if (!dragEventActuator_->IsNeedGather()) {
        return;
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        SetMouseDragGatherPixelMaps();
    } else {
        SetNotMouseDragGatherPixelMaps();
    }
}

void GestureEventHub::SetMouseDragGatherPixelMaps()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ClearGatherPixelMap();
    CHECK_NULL_VOID(dragEventActuator_);
    auto fatherNode = dragEventActuator_->GetItemParentNode();
    CHECK_NULL_VOID(fatherNode);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    auto children = scrollPattern->GetVisibleSelectedItems();
    int cnt = 0;
    for (const auto& itemFrameNode : children) {
        if (itemFrameNode == frameNode) {
            continue;
        }
        CHECK_NULL_VOID(itemFrameNode);
        DragEventActuator::GetFrameNodePreviewPixelMap(itemFrameNode);
        auto gestureHub = itemFrameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        dragDropManager->PushGatherPixelMap(gestureHub->GetDragPreviewPixelMap());
        cnt++;
        if (cnt > 1) {
            break;
        }
    }
}

void GestureEventHub::SetNotMouseDragGatherPixelMaps()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ClearGatherPixelMap();
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto overlayManager = mainPipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
    int cnt = 0;
    for (auto iter = gatherNodeChildrenInfo.rbegin(); iter != gatherNodeChildrenInfo.rend(); ++iter) {
        auto imageNode = (*iter).imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo());
        dragDropManager->PushGatherPixelMap(imageSourceInfo.GetPixmap());
        cnt++;
        if (cnt > 1) {
            break;
        }
    }
}

int32_t GestureEventHub::GetSelectItemSize()
{
    CHECK_NULL_RETURN(dragEventActuator_, 0);
    if (!dragEventActuator_->IsNeedGather()) {
        return 0;
    }
    auto fatherNode = dragEventActuator_->GetItemParentNode();
    CHECK_NULL_RETURN(fatherNode, 0);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, 0);
    auto children = scrollPattern->GetVisibleSelectedItems();
    return children.size();
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

void GestureEventHub::FireCustomerOnDragEnd(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub)
{
    auto eventHub = hub.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetResult(DragRet::DRAG_FAIL);
    dragEvent->SetDragBehavior(DragBehavior::UNKNOWN);
    dragDropManager->DoDragReset();
    dragDropManager->SetIsDragged(false);
    dragDropManager->ResetDragging();
    dragDropManager->SetDraggingPointer(-1);
    dragDropManager->SetDraggingPressedState(false);
    dragDropManager->ResetDragPreviewInfo();
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEvent);
    if (eventHub->HasOnDragEnd()) {
        (eventHub->GetOnDragEnd())(dragEvent);
    }
}

#if defined(PIXEL_MAP_SUPPORTED)
void GestureEventHub::PrintBuilderNode(const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    bool hasImageNode = false;
    std::list<RefPtr<FrameNode>> imageNodes;
    int32_t depth = 1;
    PrintIfImageNode(customNode, depth, hasImageNode, imageNodes);
    CheckImageDecode(imageNodes);
    imageNodes.clear();
}

void GestureEventHub::PrintIfImageNode(
    const RefPtr<UINode>& builderNode, int32_t depth, bool& hasImageNode, std::list<RefPtr<FrameNode>>& imageNodes)
{
    if (depth > MAX_BUILDER_DEPTH) {
        return;
    }
    if (builderNode->GetTag() == V2::IMAGE_ETS_TAG) {
        auto frameNode = AceType::DynamicCast<FrameNode>(builderNode);
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        hasImageNode = true;
        imageNodes.push_back(frameNode);
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "customNode has ImageNode, nodeId: %{public}d, syncLoad: %{public}d, decode complete: %{public}d",
            frameNode->GetId(), pattern->GetSyncLoad(), pattern->GetCanvasImage() != nullptr);
    }

    auto children = builderNode->GetChildren();
    for (const auto& child : children) {
        PrintIfImageNode(child, depth + 1, hasImageNode, imageNodes);
    }
}

void GestureEventHub::CheckImageDecode(std::list<RefPtr<FrameNode>>& imageNodes)
{
    if (imageNodes.empty()) {
        return;
    }

    for (const auto& imageNode : imageNodes) {
        auto pattern = imageNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(pattern);
        if (!pattern->GetCanvasImage()) {
            TAG_LOGW(
                AceLogTag::ACE_DRAG, "ImageNode did not complete decoding, nodeId: %{public}d", imageNode->GetId());
        }
    }
}

bool GestureEventHub::StartDragForCustomBuilderSync(const GestureEvent& info, const RefPtr<PipelineBase>& pipeline,
    const RefPtr<FrameNode> frameNode, DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event)
{
    SnapshotParam param;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    {
        ACE_SCOPED_TRACE("drag: try get builder snapshot sync");
        pixelMap = ComponentSnapshot::CreateSync(dragDropInfo.customNode, param);
    }

    if (pixelMap == nullptr) {
        // try failed, need fall back to use async way
        return false;
    }

    // get snapshot successfully, go ahead
    dragDropInfo.pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
    return true;
}

void GestureEventHub::StartDragForCustomBuilder(const GestureEvent& info, const RefPtr<PipelineBase>& pipeline,
    const RefPtr<FrameNode> frameNode, DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event)
{
    if (StartDragForCustomBuilderSync(info, pipeline, frameNode, dragDropInfo,  event)) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_DRAG, "Snapshot createSync failed, get thumbnail by async.");
    auto callback = [id = Container::CurrentId(), pipeline, info, gestureEventHubPtr = AceType::Claim(this),
                        frameNode, dragDropInfo, event](
                        std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()>) mutable {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("drag: get snapshot async done, post task to UI for next handling");
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail callback executed.");
        if (pixelMap != nullptr) {
            dragDropInfo.pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
        }
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [pipeline, info, gestureEventHubPtr, frameNode, dragDropInfo, event]() {
                TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail finished, start drag.");
                CHECK_NULL_VOID(gestureEventHubPtr);
                CHECK_NULL_VOID(frameNode);
                gestureEventHubPtr->OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
            },
            TaskExecutor::TaskType::UI, "ArkUIGestureDragStart");
    };
    SnapshotParam param;
    param.delay = CREATE_PIXELMAP_TIME;
    ACE_SCOPED_TRACE("drag: try sync failed, to get snapshot async");
    NG::ComponentSnapshot::Create(dragDropInfo.customNode, std::move(callback), true, param);
    PrintBuilderNode(dragDropInfo.customNode);
}
#endif

void GestureEventHub::SetMouseDragMonitorState(bool state)
{
    auto ret = InteractionInterface::GetInstance()->SetMouseDragMonitorState(state);
    if (ret != 0) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Set mouse drag monitor state %{public}d failed, return value is %{public}d",
            state, ret);
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Set mouse drag monitor state %{public}d success", state);
}

bool GestureEventHub::IsAllowedDrag(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    CHECK_NULL_RETURN(gestureEventHub, false);
    if (gestureEventHub->IsTextCategoryComponent(frameNode->GetTag())) {
        return frameNode->IsDraggable() && eventHub->HasOnDragStart();
    }
    return gestureEventHub->IsAllowedDrag(eventHub);
}

void GestureEventHub::SetBindMenuStatus(bool setIsShow, bool isShow, MenuPreviewMode previewMode)
{
    if (setIsShow) {
        bindMenuStatus_.isBindCustomMenu = true;
        bindMenuStatus_.isShow = isShow;
        bindMenuStatus_.isShowPreviewMode = previewMode;
    } else {
        bindMenuStatus_.isBindLongPressMenu = true;
        bindMenuStatus_.longPressPreviewMode = previewMode;
    }
}
} // namespace OHOS::Ace::NG

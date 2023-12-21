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

#include <cstdint>
#include <list>

#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/time_util.h"
#include "core/common/container.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/exclusive_recognizer.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/parallel_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "image_source.h"

#include "base/msdp/device_status/interfaces/innerkits/interaction/include/interaction_manager.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#endif // ENABLE_DRAG_FRAMEWORK
namespace OHOS::Ace::NG {
#ifdef ENABLE_DRAG_FRAMEWORK
RefPtr<PixelMap> g_pixelMap;
bool g_getPixelMapSucc = false;
namespace {
constexpr int32_t CREATE_PIXELMAP_TIME = 80;
constexpr uint32_t EXTRA_INFO_MAX_LENGTH = 200;
} // namespace
using namespace Msdp::DeviceStatus;
const std::string DEFAULT_MOUSE_DRAG_IMAGE { "/system/etc/device_status/drag_icon/Copy_Drag.svg" };
#endif // ENABLE_DRAG_FRAMEWORK
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
    const RefPtr<TargetComponent>& targetComponent)
{
    size_t idx = innerTargets.size();
    size_t newIdx = 0;
    auto host = GetFrameNode();
    if (!host) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Get frame node is null");
        return false;
    }
    auto eventHub = eventHub_.Upgrade();
    auto getEventTargetImpl = eventHub ? eventHub->CreateGetEventTargetImpl() : nullptr;
    if (scrollableActuator_) {
        scrollableActuator_->CollectTouchTarget(
            coordinateOffset, touchRestrict, getEventTargetImpl, innerTargets, localPoint);
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

    std::list<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    for (const auto& item : dragTargets) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(item);
        if (recognizer) {
            recognizer->BeginReferee(touchId);
            recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
            recognizer->SetTargetComponent(targetComponent);
            if (AceType::InstanceOf<RecognizerGroup>(recognizer)) {
                auto group = AceType::DynamicCast<RecognizerGroup>(recognizer);
                if (group) {
                    group->SetChildrenTargetComponent(targetComponent);
                }
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

    std::list<RefPtr<NGGestureRecognizer>> innerRecognizers;
    for (auto const& eventTarget : innerTargets) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(eventTarget);
        if (recognizer) {
            auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(recognizer);
            if (!recognizerGroup && newIdx >= idx) {
                recognizer->AssignNodeId(host->GetId());
                recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
                recognizer->SetTargetComponent(targetComponent);
                recognizer->SetIsSystemGesture(true);
            }
            recognizer->BeginReferee(touchId);
            innerRecognizers.push_back(std::move(recognizer));
        } else {
            eventTarget->AssignNodeId(host->GetId());
            eventTarget->AttachFrameNode(WeakPtr<FrameNode>(host));
            eventTarget->SetTargetComponent(targetComponent);
            finalResult.push_back(eventTarget);
        }
        newIdx++; // not process previous recognizers
    }

    ProcessTouchTestHierarchy(coordinateOffset, touchRestrict, innerRecognizers, finalResult, touchId, targetComponent);

    return false;
}

void GestureEventHub::OnModifyDone()
{
    if (recreateGesture_) {
        UpdateGestureHierarchy();
        recreateGesture_ = false;
    }
}

void GestureEventHub::ProcessTouchTestHierarchy(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
    std::list<RefPtr<NGGestureRecognizer>>& innerRecognizers, TouchTestResult& finalResult, int32_t touchId,
    const RefPtr<TargetComponent>& targetComponent)
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
        innerExclusiveRecognizer_->AttachFrameNode(WeakPtr<FrameNode>(host));
        innerExclusiveRecognizer_->SetTargetComponent(targetComponent);
        current = innerExclusiveRecognizer_;
    }

    auto geometryNode = host->GetGeometryNode();
    auto size = geometryNode->GetFrameSize();
    auto context = host->GetContext();
    int32_t parallelIndex = 0;
    int32_t exclusiveIndex = 0;
    for (auto const& recognizer : gestureHierarchy_) {
        if (!recognizer) {
            continue;
        }
        auto recognizerGroup = AceType::DynamicCast<RecognizerGroup>(recognizer);
        if (recognizerGroup) {
            auto groupRecognizers = recognizerGroup->GetGroupRecognizer();
            for (const auto& groupRecognizer : groupRecognizers) {
                if (groupRecognizer) {
                    groupRecognizer->SetCoordinateOffset(offset);
                    groupRecognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
                    groupRecognizer->SetTargetComponent(targetComponent);
                }
            }
        }
        recognizer->AssignNodeId(host->GetId());
        recognizer->AttachFrameNode(WeakPtr<FrameNode>(host));
        recognizer->SetTargetComponent(targetComponent);
        recognizer->SetSize(size.Height(), size.Width());
        recognizer->SetCoordinateOffset(offset);
        recognizer->BeginReferee(touchId, true);
        auto gestureMask = recognizer->GetPriorityMask();
        if (gestureMask == GestureMask::IgnoreInternal) {
            // In ignore case, dropped the self inner recognizer and children recognizer.
            current = recognizer;
            continue;
        }
        auto priority = recognizer->GetPriority();
        std::list<RefPtr<NGGestureRecognizer>> recognizers { 1, recognizer };
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
                externalParallelRecognizer_[parallelIndex]->BeginReferee(touchId);
                externalParallelRecognizer_[parallelIndex]->AssignNodeId(host->GetId());
                externalParallelRecognizer_[parallelIndex]->AttachFrameNode(WeakPtr<FrameNode>(host));
                externalParallelRecognizer_[parallelIndex]->SetTargetComponent(targetComponent);
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
                externalExclusiveRecognizer_[exclusiveIndex]->BeginReferee(touchId);
                externalExclusiveRecognizer_[exclusiveIndex]->AssignNodeId(host->GetId());
                externalExclusiveRecognizer_[exclusiveIndex]->AttachFrameNode(WeakPtr<FrameNode>(host));
                externalExclusiveRecognizer_[exclusiveIndex]->SetTargetComponent(targetComponent);
                current = externalExclusiveRecognizer_[exclusiveIndex];
                exclusiveIndex++;
            } else if (recognizers.size() == 1) {
                current = *recognizers.begin();
            }
        }
    }

    if (exclusiveIndex != static_cast<int32_t>(externalExclusiveRecognizer_.size())) {
        externalExclusiveRecognizer_.resize(exclusiveIndex);
    }

    if (parallelIndex != static_cast<int32_t>(externalParallelRecognizer_.size())) {
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

        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(recognizer);
        if (clickRecognizer) {
            clickRecognizer->SetOnAccessibility(GetOnAccessibilityEventFunc());
        }

        auto longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(recognizer);
        if (longPressRecognizer) {
            longPressRecognizer->SetOnAccessibility(GetOnAccessibilityEventFunc());
            auto pattern = host->GetPattern();
            if (pattern && longPressRecognizer->HasAction()) {
                longPressRecognizer->SetOnLongPressRecorder(pattern->GetLongPressEventRecorder());
            }
        }

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

#ifdef ENABLE_DRAG_FRAMEWORK
bool GestureEventHub::IsPixelMapNeedScale() const
{
    CHECK_NULL_RETURN(pixelMap_, false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto width = pixelMap_->GetWidth();
    auto maxWidth = GridSystemManager::GetInstance().GetMaxWidthWithColumnType(GridColumnType::DRAG_PANEL);
    if (frameNode->GetTag() == V2::WEB_ETS_TAG ||
        frameNode->GetDragPreviewOption().mode == DragPreviewMode::DISABLE_SCALE || width == 0 || width < maxWidth) {
        return false;
    }
    return true;
}
#endif

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
    SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
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
        TaskExecutor::TaskType::UI);
}

void GestureEventHub::CancelDragForWeb()
{
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
        TaskExecutor::TaskType::UI);
}

void GestureEventHub::ResetDragActionForWeb()
{
    isReceivedDragGestureInfo_ = false;
    CHECK_NULL_VOID(dragEventActuator_);
    dragEventActuator_->ResetDragActionForWeb();
}

void GestureEventHub::StartDragTaskForWeb()
{
    if (!isReceivedDragGestureInfo_) {
        return;
    }

    isReceivedDragGestureInfo_ = false;
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
            dragEventActuator->StartDragTaskForWeb(gestureHub->gestureInfoForWeb_);
        },
        TaskExecutor::TaskType::UI);
}

#ifdef ENABLE_DRAG_FRAMEWORK
std::shared_ptr<Media::PixelMap> CreatePixelMapFromString(const std::string& filePath)
{
    Media::SourceOptions opts;
    opts.formatHint = "image/svg+xml";
    uint32_t errCode = 0;
    auto imageSource = Media::ImageSource::CreateImageSource(filePath, opts, errCode);
    CHECK_NULL_RETURN(imageSource, nullptr);
    Media::DecodeOptions decodeOpts;
    std::shared_ptr<Media::PixelMap> pixelMap = imageSource->CreatePixelMap(decodeOpts, errCode);
    return pixelMap;
}

OffsetF GestureEventHub::GetPixelMapOffset(
    const GestureEvent& info, const SizeF& size, const float scale, const bool needScale) const
{
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, result);
    auto frameTag = frameNode->GetTag();
    if (frameTag == V2::WEB_ETS_TAG) {
        result.SetX(size.Width() * PIXELMAP_WIDTH_RATE);
        result.SetY(size.Height() * PIXELMAP_HEIGHT_RATE);
    } else if (needScale) {
        result.SetX(size.Width() * PIXELMAP_WIDTH_RATE);
        result.SetY(PIXELMAP_DRAG_DEFAULT_HEIGHT);
    } else {
        auto coordinateX = frameNodeOffset_.GetX() > SystemProperties::GetDevicePhysicalWidth()
                               ? frameNodeOffset_.GetX() - SystemProperties::GetDevicePhysicalWidth()
                               : frameNodeOffset_.GetX();
        auto coordinateY = frameNodeOffset_.GetY();
        result.SetX(scale * (coordinateX - info.GetGlobalLocation().GetX()));
        result.SetY(scale * (coordinateY - info.GetGlobalLocation().GetY()));
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
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Get pixelMap offset is %{public}f and %{public}f.",
            result.GetX(), result.GetY());
    }
    return result;
}

float GestureEventHub::GetPixelMapScale(const int32_t height, const int32_t width) const
{
    float scale = 1.0f;
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, scale);
    if (frameNode->GetDragPreviewOption().mode == DragPreviewMode::DISABLE_SCALE ||
        !(frameNode->GetTag() == V2::WEB_ETS_TAG)) {
        return scale;
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, scale);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, scale);
    auto windowScale = dragDropManager->GetSmallWindowScale();
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
#endif

void GestureEventHub::HandleNotallowDrag(const GestureEvent& info)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        gestureInfoForWeb_ = info;
        isReceivedDragGestureInfo_ = true;
    }
}

void GestureEventHub::HandleOnDragStart(const GestureEvent& info)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "Start handle onDragStart.");
    }
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDragStart()) {
        return;
    }
    if (!IsAllowedDrag(eventHub)) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGW(AceLogTag::ACE_GESTURE, "FrameNode is not allow drag.");
        }
        HandleNotallowDrag(info);
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && eventManager->IsLastMoveBeforeUp()) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_GESTURE, "Drag stop because user release mouse button");
        }
        return;
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

    auto frameTag = frameNode->GetTag();
    auto hostPattern = frameNode->GetPattern<TextDragBase>();
    if (hostPattern && (frameTag == V2::RICH_EDITOR_ETS_TAG || frameTag == V2::TEXT_ETS_TAG ||
                        frameTag == V2::TEXTINPUT_ETS_TAG || frameTag == V2::SEARCH_Field_ETS_TAG)) {
        frameNodeOffset_ = hostPattern->GetDragUpperLeftCoordinates();
    } else {
        frameNodeOffset_ = frameNode->GetOffsetRelativeToWindow();
    }
    /*
     * Users may remove frameNode in the js callback function "onDragStart "triggered below,
     * so save the offset of the framenode relative to the window in advance
     */
    auto extraParams = eventHub->GetDragExtraParams(std::string(), info.GetGlobalPoint(), DragEventType::START);
    auto dragDropInfo = (eventHub->GetOnDragStart())(event, extraParams);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        if (dragPreviewInfo.pixelMap != nullptr || dragPreviewInfo.customNode != nullptr) {
            dragDropInfo.pixelMap = dragPreviewPixelMap_;
            OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
            return;
        }
    }
    if (info.GetSourceDevice() == SourceType::MOUSE) {
        if (dragPreviewInfo.pixelMap != nullptr) {
            dragDropInfo.pixelMap = dragPreviewInfo.pixelMap;
            OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
            return;
        } else if (dragPreviewInfo.customNode != nullptr) {
            dragDropInfo.customNode = dragPreviewInfo.customNode;
        }
    }
#if defined(ENABLE_DRAG_FRAMEWORK) && defined(ENABLE_ROSEN_BACKEND) && defined(PIXEL_MAP_SUPPORTED)
    g_getPixelMapSucc = false;
    if (dragDropInfo.customNode) {
        auto callback = [id = Container::CurrentId(), pipeline, info, gestureEventHubPtr = AceType::Claim(this),
                            frameNode, dragDropInfo,
                            event](std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()>) {
            ContainerScope scope(id);
            if (pixelMap == nullptr) {
                g_getPixelMapSucc = false;
            } else {
                g_pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
                g_getPixelMapSucc = true;
            }
            auto taskScheduler = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskScheduler);
            taskScheduler->PostTask(
                [pipeline, info, gestureEventHubPtr, frameNode, dragDropInfo, event]() {
                    CHECK_NULL_VOID(gestureEventHubPtr);
                    CHECK_NULL_VOID(frameNode);
                    gestureEventHubPtr->OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
                },
                TaskExecutor::TaskType::UI);
        };
        auto customNode = AceType::DynamicCast<FrameNode>(dragDropInfo.customNode);
        NG::ComponentSnapshot::Create(customNode, std::move(callback), false, CREATE_PIXELMAP_TIME);
        return;
    }
#endif
    OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
}

void GestureEventHub::OnDragStart(const GestureEvent& info, const RefPtr<PipelineBase>& context,
    const RefPtr<FrameNode> frameNode, const DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(pipeline);

    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (dragDropProxy_) {
        dragDropProxy_ = nullptr;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    CHECK_NULL_VOID(dragEvent);
    auto eventRet = dragEvent->GetResult();
    if (eventRet == DragRet::DRAG_FAIL || eventRet == DragRet::DRAG_CANCEL) {
        return;
    }
    std::string udKey;
    int32_t recordsSize = 1;
    auto unifiedData = dragEvent->GetData();
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
    SetDragData(unifiedData, udKey);
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "HandleOnDragStart: setDragData finish, udKey is %{public}s", udKey.c_str());
    }

    std::map<std::string, int64_t> summary;
    int32_t ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
    dragDropManager->SetSummaryMap(summary);
    std::shared_ptr<Media::PixelMap> pixelMap;
    if (dragDropInfo.pixelMap != nullptr) {
        pixelMap = dragDropInfo.pixelMap->GetPixelMapSharedPtr();
        SetPixelMap(dragDropInfo.pixelMap);
    } else if (g_getPixelMapSucc) {
        pixelMap = g_pixelMap->GetPixelMapSharedPtr();
        SetPixelMap(g_pixelMap);
    } else if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        dragDropManager->SetIsMouseDrag(true);
        pixelMap = CreatePixelMapFromString(DEFAULT_MOUSE_DRAG_IMAGE);
        CHECK_NULL_VOID(pixelMap);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        GenerateMousePixelMap(info);
        if (pixelMap_) {
            pixelMap = pixelMap_->GetPixelMapSharedPtr();
        }
    } else {
        CHECK_NULL_VOID(pixelMap_);
        if (pixelMap == nullptr) {
            pixelMap = pixelMap_->GetPixelMapSharedPtr();
        }
    }
    float defaultPixelMapScale =
        info.GetInputEventType() == InputEventType::MOUSE_BUTTON ? 1.0f : DEFALUT_DRAG_PPIXELMAP_SCALE;
    float scale = GetPixelMapScale(pixelMap->GetHeight(), pixelMap->GetWidth()) * defaultPixelMapScale;
    auto overlayManager = pipeline->GetOverlayManager();
    if (IsPixelMapNeedScale()) {
        RefPtr<FrameNode> imageNode = overlayManager->GetPixelMapContentNode();
        DragEventActuator::CreatePreviewNode(frameNode, imageNode);
        CHECK_NULL_VOID(imageNode);
        auto window = SubwindowManager::GetInstance()->ShowPreviewNG();
        CHECK_NULL_VOID(window);
        overlayManager = window->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        DragEventActuator::MountPixelMap(overlayManager, eventHub->GetGestureEventHub(), imageNode);
        dragDropManager->DoDragStartAnimation(overlayManager, info);
        scale = static_cast<float>(imageNode->GetPreviewScaleVal());
        if (pixelMap_ != nullptr) {
            pixelMap = pixelMap_->GetPixelMapSharedPtr();
        }
    }
    if (!overlayManager->GetIsOnAnimation()) {
        dragEventActuator_->SetIsNotInPreviewState(true);
    }
    pixelMap->scale(scale, scale, Media::AntiAliasingOption::HIGH);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto pixelMapOffset = GetPixelMapOffset(info, SizeF(width, height), scale, !NearEqual(scale, defaultPixelMapScale));
    auto extraInfoLimited = dragDropInfo.extraInfo.size() > EXTRA_INFO_MAX_LENGTH
                                ? dragDropInfo.extraInfo.substr(EXTRA_INFO_MAX_LENGTH + 1)
                                : dragDropInfo.extraInfo;
    auto arkExtraInfoJson = JsonUtil::Create(true);
    auto dipScale = pipeline->GetDipScale();
    arkExtraInfoJson->Put("dip_scale", dipScale);
    ShadowInfoCore shadowInfo { pixelMap, pixelMapOffset.GetX(), pixelMapOffset.GetY() };
    DragDataCore dragData { shadowInfo, {}, udKey, extraInfoLimited, arkExtraInfoJson->ToString(),
        static_cast<int32_t>(info.GetSourceDevice()), recordsSize, info.GetPointerId(), info.GetScreenLocation().GetX(),
        info.GetScreenLocation().GetY(), info.GetTargetDisplayId(), true, summary };
    ret = InteractionInterface::GetInstance()->StartDrag(dragData, GetDragCallback(pipeline, eventHub));
    if (ret != 0) {
        if (dragDropManager->IsNeedScaleDragPreview()) {
            SubwindowManager::GetInstance()->HidePreviewNG();
            overlayManager->RemovePixelMap();
        }
        return;
    }
    dragDropManager->UpdateDragStyle();
    dragDropManager->SetDraggingPointer(info.GetPointerId());
    dragDropManager->SetPreviewRect(Rect(pixelMapOffset.GetX(), pixelMapOffset.GetY(), width, height));
    dragDropManager->ResetRecordSize(static_cast<uint32_t>(recordsSize));
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    eventManager->DoMouseActionRelease();
    eventManager->SetIsDragging(true);
    if (info.GetInputEventType() != InputEventType::MOUSE_BUTTON && dragEventActuator_->GetIsNotInPreviewState()) {
        if (!dragDropManager->IsNeedScaleDragPreview()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
            overlayManager->RemovePixelMap();
            pipeline->FlushPipelineImmediately();
        }
        dragDropManager->FireOnEditableTextComponent(frameNode, DragEventType::ENTER);
    } else if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON &&
               (dragDropInfo.pixelMap || dragDropInfo.customNode)) {
        if (!dragDropManager->IsNeedScaleDragPreview()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
        dragDropManager->SetIsDragWindowShow(true);
    }
    dragDropProxy_ = dragDropManager->CreateFrameworkDragDropProxy();
    if (!dragDropProxy_) {
        return;
    }
    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragStart(info, extraInfoLimited, GetFrameNode());
#else
    if (dragDropInfo.customNode) {
        dragDropProxy_ = dragDropManager->CreateAndShowDragWindow(dragDropInfo.customNode, info);
    } else if (dragDropInfo.pixelMap) {
        dragDropProxy_ = dragDropManager->CreateAndShowDragWindow(dragDropInfo.pixelMap, info);
    } else {
        dragDropProxy_ = dragDropManager->CreateAndShowDragWindow(pixelMap_, info);
    }
    if (!dragDropProxy_) {
        return;
    }

    CHECK_NULL_VOID(dragDropProxy_);
    dragDropProxy_->OnDragStart(info, dragDropInfo.extraInfo, GetFrameNode());
#endif // ENABLE_DRAG_FRAMEWORK
}

void GestureEventHub::HandleOnDragUpdate(const GestureEvent& info)
{
    gestureInfoForWeb_ = info;
    CHECK_NULL_VOID(dragDropProxy_);
#ifndef ENABLE_DRAG_FRAMEWORK
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    if (dragDropManager->IsDragged()) {
        dragDropProxy_->OnDragMove(info);
    }
#endif // ENABLE_DRAG_FRAMEWORK
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
#ifndef ENABLE_DRAG_FRAMEWORK
    dragDropProxy_->onDragCancel();
#endif // ENABLE_DRAG_FRAMEWORK
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
}

void GestureEventHub::SetUserOnClick(GestureEventFunc&& clickEvent)
{
    CheckClickActuator();
    clickEventActuator_->SetUserCallback(std::move(clickEvent));

    SetFocusClickEvent(clickEventActuator_->GetClickEvent());
}

void GestureEventHub::SetOnGestureJudgeBegin(GestureJudgeFunc&& gestureJudgeFunc)
{
    gestureJudgeFunc_ = std::move(gestureJudgeFunc);
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
    RefPtr<ClickRecognizer> clickRecognizer;
    for (auto gestureRecognizer : gestureHierarchy_) {
        clickRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer);
        if (clickRecognizer && clickRecognizer->GetFingers() == 1 && clickRecognizer->GetCount() == 1) {
            click = clickRecognizer->GetTapActionFunc();
            click(info);
            host->OnAccessibilityEvent(AccessibilityEventType::CLICK);
            return true;
        }
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

#ifdef ENABLE_DRAG_FRAMEWORK
int32_t GestureEventHub::SetDragData(const RefPtr<UnifiedData>& unifiedData, std::string& udKey)
{
    if (unifiedData == nullptr) {
        return -1;
    }
    int32_t ret = UdmfClient::GetInstance()->SetData(unifiedData, udKey);
    if (ret != 0) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "UDMF Setdata failed:%{public}d", ret);
        }
    }
    return ret;
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
        DragRet result = DragRet::DRAG_FAIL;
        switch (notifyMessage.result) {
            case DragRet::DRAG_SUCCESS:
                result = DragRet::DRAG_SUCCESS;
                break;
            case DragRet::DRAG_FAIL:
                result = DragRet::DRAG_FAIL;
                break;
            case DragRet::DRAG_CANCEL:
                result = DragRet::DRAG_CANCEL;
                break;
            default:
                break;
        }
        dragEvent->SetResult(result);
        taskScheduler->PostTask(
            [eventHub, dragEvent, dragDropManager, eventManager]() {
                dragDropManager->SetIsDragged(false);
                dragDropManager->ResetDragging();
                dragDropManager->SetDraggingPointer(-1);
                if (eventManager) {
                    eventManager->DoMouseActionRelease();
                }
                eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEvent);
                if (eventHub->HasOnDragEnd()) {
                    (eventHub->GetOnDragEnd())(dragEvent);
                }
            },
            TaskExecutor::TaskType::UI);
    };
    return callback;
}

#endif
bool GestureEventHub::IsAccessibilityClickable()
{
    bool ret = IsClickable();
    RefPtr<ClickRecognizer> clickRecognizer;
    for (auto gestureRecognizer : gestureHierarchy_) {
        clickRecognizer = AceType::DynamicCast<ClickRecognizer>(gestureRecognizer);
        if (clickRecognizer && clickRecognizer->GetFingers() == 1 && clickRecognizer->GetCount() == 1) {
            return true;
        }
    }
    return ret;
}

bool GestureEventHub::IsAccessibilityLongClickable()
{
    bool ret = IsLongClickable();
    RefPtr<LongPressRecognizer> longPressRecognizer;
    for (auto gestureRecognizer : gestureHierarchy_) {
        longPressRecognizer = AceType::DynamicCast<LongPressRecognizer>(gestureRecognizer);
        if (longPressRecognizer && longPressRecognizer->GetFingers() == 1) {
            return true;
        }
    }
    return ret;
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
} // namespace OHOS::Ace::NG

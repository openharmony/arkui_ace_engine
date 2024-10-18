/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "base/image/image_source.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/container.h"
#include "core/common/interaction/interaction_data.h"
#include "core/common/interaction/interaction_interface.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"

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

bool GestureEventHub::IsPixelMapNeedScale() const
{
    CHECK_NULL_RETURN(pixelMap_, false);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto width = pixelMap_->GetWidth();
    auto maxWidth = DragDropManager::GetMaxWidthBaseOnGridSystem(frameNode->GetContextRefPtr());
    if (!frameNode->GetDragPreviewOption().isScaleEnabled || width == 0 || width <= maxWidth) {
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

void GestureEventHub::StartLongPressActionForWeb(bool isFloatImage)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "DragDrop start long press action for web");
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);

    taskScheduler->PostTask(
        [weak = WeakClaim(this), isFloatImage]() {
            auto gestureHub = weak.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            auto dragEventActuator = gestureHub->dragEventActuator_;
            CHECK_NULL_VOID(dragEventActuator);
            dragEventActuator->StartLongPressActionForWeb(isFloatImage);
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
    TAG_LOGD(AceLogTag::ACE_DRAG, "Get pixelMap offset is %{public}f and %{public}f.", result.GetX(), result.GetY());
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
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "FrameNode is not allow drag, tag is %{public}s, id is %{public}s,"
            "draggable is %{public}d, drag start event is %{public}d,"
            "default support drag is %{public}d, user set is %{public}d.",
            frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str(), frameNode->IsDraggable(),
            eventHub->HasOnDragStart(), pattern->DefaultSupportDrag(), frameNode->IsUserSet());
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
    if (hostPattern && GetTextDraggable() &&
        (frameTag == V2::RICH_EDITOR_ETS_TAG || frameTag == V2::TEXT_ETS_TAG || frameTag == V2::TEXTINPUT_ETS_TAG ||
            frameTag == V2::SEARCH_Field_ETS_TAG)) {
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
        frameNodeOffset_ = OffsetF(
            rectCenter.GetX() - frameNodeSize_.Width() / 2.0f, rectCenter.GetY() - frameNodeSize_.Height() / 2.0f);
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
        auto menuPreviewScale = menuPreviewScale_;
        if (GreatNotEqual(originPixelMapWidth, 0.0f)) {
            menuPreviewScale = menuPreviewRect.Width() / originPixelMapWidth;
        }
        if (GreatNotEqual(menuPreviewRect.Width(), 0.0f) && GreatNotEqual(originPixelMapWidth, 0.0f) &&
            menuPreviewRect.Width() < originPixelMapWidth * menuPreviewScale_ &&
            NearEqual(menuPreviewRect.Height(), menuPreviewScale * pixelMap->GetHeight(), 1.0)) {
            defaultPixelMapScale = menuPreviewScale;
            menuPreviewScale_ = defaultPixelMapScale;
        } else {
            defaultPixelMapScale = menuPreviewScale_;
        }
    }
    auto windowScale = dragDropManager->GetWindowScale();
    float scale = windowScale * defaultPixelMapScale;
    auto focusHub = frameNode->GetFocusHub();
    bool hasContextMenu =
        focusHub == nullptr ? false : focusHub->FindContextMenuOnKeyEvent(OnKeyEventType::CONTEXT_MENU);
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
        if (childSize > 1) {
            recordsSize = childSize;
        }
        textNode = DragEventActuator::CreateBadgeTextNode(imageNode, childSize, previewScale, true);
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
    std::string summarys = DragDropFuncWrapper::GetSummaryString(summary);
    TAG_LOGI(AceLogTag::ACE_DRAG,
        "Start drag, frameNode is %{public}s, id is %{public}s, pixelMap width %{public}d height %{public}d, "
        "scale is %{public}f, udkey %{public}s, recordsSize %{public}d, extraInfo length %{public}d, "
        "pointerId %{public}d, displayId %{public}d, windowId %{public}d, summary %{public}s.",
        frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str(), width, height, scale,
        DragDropFuncWrapper::GetAnonyString(udKey).c_str(), recordsSize,
        static_cast<int32_t>(extraInfoLimited.length()), info.GetPointerId(), info.GetTargetDisplayId(), windowId,
        summarys.c_str());
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
        auto gatherNode =
            DragEventActuator::GetOrCreateGatherNode(overlayManager, dragEventActuator_, gatherNodeChildrenInfo);
        DragEventActuator::MountGatherNode(subWindowOverlayManager, frameNode, gatherNode, gatherNodeChildrenInfo);
        DragEventActuator::UpdatePreviewPositionAndScale(
            imageNode, imageNode->GetOffsetInSubwindow(subWindow->GetWindowRect().GetOffset()));
        auto gatherNodeOffset = DragDropManager::GetTouchOffsetRelativeToSubwindow(container->GetInstanceId());
        if (pipeline->HasFloatTitle()) {
            gatherNodeOffset.SetX(
                gatherNodeOffset.GetX() + static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx()));
            gatherNodeOffset.SetY(
                gatherNodeOffset.GetY() +
                static_cast<float>((pipeline->GetCustomTitleHeight() + CONTAINER_BORDER_WIDTH).ConvertToPx()));
        }
        DragEventActuator::UpdateGatherAnimatePosition(gatherNodeChildrenInfo, gatherNodeOffset);
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
            // response: 0.347, dampingRatio: 0.99, blendDuration: 0.0
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

void GestureEventHub::UpdateExtraInfo(
    const RefPtr<FrameNode>& frameNode, std::unique_ptr<JsonValue>& arkExtraInfoJson, float scale)
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
                auto container = Container::GetContainer(id);
                if (!container) {
                    TAG_LOGE(AceLogTag::ACE_DRAG, "handle drag end callback, can not get container.");
                    return;
                }
                TAG_LOGI(
                    AceLogTag::ACE_DRAG, "handle drag end callback, windowId is %{public}d.", container->GetWindowId());
                dragDropManager->ResetDragEndOption(notifyMessage, dragEvent, id);
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
        TAG_LOGD(AceLogTag::ACE_DRAG,
            "Get drag drop info, pixelmap and customNode are set to null "
            "when frameTag is %{public}s",
            frameTag.c_str());
        dragDropInfo.pixelMap = nullptr;
        dragDropInfo.customNode = nullptr;
    } else {
        dragPreviewInfo = frameNode->GetDragPreview();
    }
    return dragDropInfo;
}

RefPtr<UnifiedData> GestureEventHub::GetUnifiedData(
    const std::string& frameTag, DragDropInfo& dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
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

void GestureEventHub::SetDragForbiddenForcely(bool isDragForbiddenForWholeSubTree)
{
    isDragForbiddenForWholeSubTree_ = isDragForbiddenForWholeSubTree;
}

bool GestureEventHub::IsDragForbidden()
{
    return isDragForbiddenForWholeSubTree_;
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
    if (StartDragForCustomBuilderSync(info, pipeline, frameNode, dragDropInfo, event)) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_DRAG, "Snapshot createSync failed, get thumbnail by async.");
    auto callback = [id = Container::CurrentId(), pipeline, info, gestureEventHubPtr = AceType::Claim(this), frameNode,
                        dragDropInfo,
                        event](std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()>) mutable {
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
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
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

void GestureEventHub::AddPreviewMenuHandleDragEnd(GestureEventFunc&& actionEnd)
{
    if (!scrollableActuator_) {
        scrollableActuator_ = MakeRefPtr<ScrollableActuator>(WeakClaim(this));
    }
    scrollableActuator_->AddPreviewMenuHandleDragEnd(std::move(actionEnd));
}

// Set by user define, which will replace old one.
void GestureEventHub::SetDragEvent(
    const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance)
{
    if (!dragEventActuator_) {
        dragEventActuator_ = MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    dragEventActuator_->ReplaceDragEvent(dragEvent);
}

void GestureEventHub::SetCustomDragEvent(
    const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance)
{
    if (!dragEventActuator_) {
        dragEventActuator_ = MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    dragEventActuator_->SetCustomDragEvent(dragEvent);
}

bool GestureEventHub::HasDragEvent() const
{
    return dragEventActuator_ && dragEventActuator_->HasDragEvent();
}

void GestureEventHub::RemoveDragEvent()
{
    if (!dragEventActuator_) {
        return;
    }
    dragEventActuator_->ClearDragEvent();
}

void GestureEventHub::SetThumbnailCallback(std::function<void(Offset)>&& callback)
{
    if (dragEventActuator_) {
        dragEventActuator_->SetThumbnailCallback(std::move(callback));
    }
}

bool GestureEventHub::GetTextDraggable() const
{
    return textDraggable_;
}

void GestureEventHub::SetTextDraggable(bool draggable)
{
    textDraggable_ = draggable;
}

void GestureEventHub::SetIsTextDraggable(bool isTextDraggable)
{
    isTextDraggable_ = isTextDraggable;
}

bool GestureEventHub::GetIsTextDraggable()
{
    return isTextDraggable_;
}

void GestureEventHub::SetPreviewMode(MenuPreviewMode mode)
{
    previewMode_ = mode;
}

MenuPreviewMode GestureEventHub::GetPreviewMode()
{
    return previewMode_;
}

void GestureEventHub::SetContextMenuShowStatus(bool contextMenuShowStatus)
{
    contextMenuShowStatus_ = contextMenuShowStatus;
}

bool GestureEventHub::GetContextMenuShowStatus()
{
    return contextMenuShowStatus_;
}

void GestureEventHub::SetMenuBindingType(MenuBindingType menuBindingType)
{
    menuBindingType_ = menuBindingType;
}

MenuBindingType GestureEventHub::GetMenuBindingType()
{
    return menuBindingType_;
}

void GestureEventHub::SetPixelMap(RefPtr<PixelMap> pixelMap)
{
    pixelMap_ = pixelMap;
}

RefPtr<PixelMap> GestureEventHub::GetPixelMap()
{
    return pixelMap_;
}

void GestureEventHub::SetDragPreviewPixelMap(RefPtr<PixelMap> pixelMap)
{
    dragPreviewPixelMap_ = pixelMap;
}

RefPtr<DragEventActuator> GestureEventHub::GetDragEventActuator()
{
    return dragEventActuator_;
}

RefPtr<PixelMap> GestureEventHub::GetDragPreviewPixelMap()
{
    return dragPreviewPixelMap_;
}

void GestureEventHub::SetMenuPreviewScale(float menuPreviewScale)
{
    menuPreviewScale_ = menuPreviewScale;
}

float GestureEventHub::GetMenuPreviewScale() const
{
    return menuPreviewScale_;
}

const BindMenuStatus& GestureEventHub::GetBindMenuStatus() const
{
    return bindMenuStatus_;
}

} // namespace OHOS::Ace::NG

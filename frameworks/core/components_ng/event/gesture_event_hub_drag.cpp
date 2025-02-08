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
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/common/vibrator/vibrator_utils.h"

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
constexpr int32_t DEFAULT_DRAG_DROP_STATUS = 0;
constexpr int32_t NEW_DRAG_DROP_STATUS = 1;
const std::unordered_set<std::string> VALID_TAG = {
    V2::WEB_ETS_TAG,
    V2::GRID_ITEM_ETS_TAG,
    V2::LIST_ITEM_ETS_TAG,
    V2::TEXTAREA_ETS_TAG,
    V2::TEXT_ETS_TAG,
    V2::TEXTINPUT_ETS_TAG,
    V2::SEARCH_Field_ETS_TAG,
    V2::RICH_EDITOR_ETS_TAG,
};
constexpr int32_t HALF_PIXELMAP = 2;
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

bool CheckNeedDragDropFrameworkStatus(const std::string& tag)
{
    auto dragDropFrameworkStatus = SystemProperties::GetDragDropFrameworkStatus();
    if (dragDropFrameworkStatus == DEFAULT_DRAG_DROP_STATUS) {
        return false;
    } else if ((dragDropFrameworkStatus == NEW_DRAG_DROP_STATUS) && (VALID_TAG.find(tag) != VALID_TAG.end())) {
        return false;
    }
    return true;
}

void GestureEventHub::InitDragDropEvent()
{
    auto frameNode = GetFrameNode();
    if (frameNode && CheckNeedDragDropFrameworkStatus(frameNode->GetTag())) {
        SetDragDropEvent();
        return;
    }
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
    CHECK_NULL_VOID(dragEventActuator_);
    dragEventActuator_->SetIsForDragDrop(false);
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
        TaskExecutor::TaskType::UI, "ArkUIGestureWebStartLongPress", PriorityType::VIP);
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

void GestureEventHub::CalcFrameNodeOffsetAndSize(const RefPtr<FrameNode> frameNode, bool isMenuShow)
{
    CHECK_NULL_VOID(frameNode);
    auto frameTag = frameNode->GetTag();
    auto hostPattern = frameNode->GetPattern<TextDragBase>();
    if (hostPattern && GetTextDraggable() &&
        (frameTag == V2::RICH_EDITOR_ETS_TAG || frameTag == V2::TEXT_ETS_TAG || frameTag == V2::TEXTINPUT_ETS_TAG ||
            frameTag == V2::SEARCH_Field_ETS_TAG)) {
        frameNodeOffset_ = hostPattern->GetDragUpperLeftCoordinates();
        frameNodeSize_ = SizeF(0.0f, 0.0f);
    } else {
        auto rect = DragDropFuncWrapper::GetPaintRectToScreen(frameNode) -
            DragDropFuncWrapper::GetCurrentWindowOffset(PipelineContext::GetCurrentContextSafelyWithCheck());
        frameNodeOffset_ = rect.GetOffset();
        frameNodeSize_ = rect.GetSize();
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

    // use menuPreview's size and offset for drag framework.
    if (!frameNode->GetDragPreview().onlyForLifting && isMenuShow && GreatNotEqual(menuPreviewScale_, 0.0f)) {
        auto menuPreviewRect = DragDropManager::GetMenuPreviewRect();
        if (GreatNotEqual(menuPreviewRect.Width(), 0.0f) && GreatNotEqual(menuPreviewRect.Height(), 0.0f)) {
            frameNodeOffset_ = menuPreviewRect.GetOffset();
            frameNodeSize_ = menuPreviewRect.GetSize();
        }
    }
}

float GestureEventHub::GetDefaultPixelMapScale(
    const RefPtr<FrameNode>& frameNode, const GestureEvent& info, bool isMenuShow, RefPtr<PixelMap> pixelMap)
{
    float defaultPixelMapScale =
        info.GetInputEventType() == InputEventType::MOUSE_BUTTON ? 1.0f : DEFALUT_DRAG_PPIXELMAP_SCALE;
    CHECK_NULL_RETURN(pixelMap, defaultPixelMapScale);
    // use menuPreviewScale for drag framework. this is not final solution.
    if (!frameNode->GetDragPreview().onlyForLifting && isMenuShow && GreatNotEqual(menuPreviewScale_, 0.0f)) {
        auto menuPreviewRect = DragDropManager::GetMenuPreviewRect();
        int32_t originPixelMapWidth = pixelMap->GetWidth();
        if (GreatNotEqual(menuPreviewRect.Width(), 0.0f) && GreatNotEqual(originPixelMapWidth, 0.0f) &&
            menuPreviewRect.Width() < originPixelMapWidth * menuPreviewScale_) {
            defaultPixelMapScale = menuPreviewRect.Width() / originPixelMapWidth;
        } else {
            defaultPixelMapScale = menuPreviewScale_;
        }
    }
    return defaultPixelMapScale;
}

bool CheckInSceneBoardWindow()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (!container->IsSubContainer()) {
        return container->IsScenceBoardWindow();
    }
    auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    container = Container::GetContainer(parentContainerId);
    CHECK_NULL_RETURN(container, false);
    return container->IsScenceBoardWindow();
}

void CheckOffsetInPixelMap(OffsetF& result, const SizeF& size)
{
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
}

RectF ParseInnerRect(const std::string& extraInfo, const SizeF& size)
{
    auto innerRect = RectF();
    if (!CheckInSceneBoardWindow() || extraInfo.empty()) {
        return innerRect;
    }
    auto extraJson = JsonUtil::ParseJsonString(extraInfo);
    CHECK_NULL_RETURN(extraJson, innerRect);
    auto extraOffsetX = extraJson->GetInt("drag_offset_x");
    auto extraOffsetY = extraJson->GetInt("drag_offset_y");
    if (extraOffsetX <= 0 || extraOffsetY <= 0) {
        return innerRect;
    }
    innerRect.SetOffset(OffsetF(Dimension(extraOffsetX, DimensionUnit::VP).ConvertToPx(),
        Dimension(extraOffsetY, DimensionUnit::VP).ConvertToPx()));
    innerRect.SetSize(size);
    return innerRect;
}

OffsetF GestureEventHub::GetPixelMapOffset(const GestureEvent& info, const SizeF& size,
    const PreparedInfoForDrag& dragInfoData, const float scale, const RectF& innerRect) const
{
    OffsetF result = OffsetF(size.Width() * PIXELMAP_WIDTH_RATE, size.Height() * PIXELMAP_HEIGHT_RATE);
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, result);
    auto frameTag = frameNode->GetTag();
    auto coordinateX = frameNodeOffset_.GetX();
    auto coordinateY = frameNodeOffset_.GetY();
    if (!innerRect.IsEmpty()) {
        auto rateX = innerRect.Width() / size.Width();
        auto rateY = innerRect.Height() / size.Height();
        result.SetX(rateX * (coordinateX + innerRect.GetOffset().GetX() - info.GetGlobalLocation().GetX()));
        result.SetY(rateY * (coordinateY + innerRect.GetOffset().GetY() - info.GetGlobalLocation().GetY()));
        CheckOffsetInPixelMap(result, size);
        return result;
    }
    if (NearZero(frameNodeSize_.Width()) || NearZero(frameNodeSize_.Height()) ||
        NearZero(size.Width()) || NearZero(size.Height())) {
        result.SetX(scale * (coordinateX - info.GetGlobalLocation().GetX()));
        result.SetY(scale * (coordinateY - info.GetGlobalLocation().GetY()));
    } else {
        if (dragInfoData.isNeedCreateTiled) {
            result.SetX(-size.Width() / HALF_PIXELMAP);
            result.SetY(-size.Height() / HALF_PIXELMAP);
        } else {
            auto rateX = (info.GetGlobalLocation().GetX() - coordinateX) / frameNodeSize_.Width();
            auto rateY = (info.GetGlobalLocation().GetY() - coordinateY) / frameNodeSize_.Height();
            result.SetX(-rateX * size.Width());
            result.SetY(-rateY * size.Height());
        }
    }
    CheckOffsetInPixelMap(result, size);
    TAG_LOGD(AceLogTag::ACE_DRAG, "Get pixelMap offset is %{public}f and %{public}f.", result.GetX(), result.GetY());
    return result;
}

void GestureEventHub::ProcessMenuPreviewScale(const RefPtr<FrameNode> imageNode, float& scale, float previewScale,
    float windowScale, float defaultMenuPreviewScale)
{
    auto imageGestureEventHub = imageNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(imageGestureEventHub);
    if (!IsPixelMapNeedScale()) {
        if (CheckInSceneBoardWindow()) {
            imageGestureEventHub->SetMenuPreviewScale(defaultMenuPreviewScale);
        } else {
            //if not in sceneboard,use default drag scale
            scale = previewScale * windowScale;
            imageGestureEventHub->SetMenuPreviewScale(previewScale);
        }
    } else {
        imageGestureEventHub->SetMenuPreviewScale(scale);
    }
}

RefPtr<PixelMap> GestureEventHub::GetPreScaledPixelMapIfExist(float targetScale, RefPtr<PixelMap> defaultPixelMap)
{
    ACE_SCOPED_TRACE("drag: get scaled pixmal, %f", targetScale);
    float preScale = 1.0f;
    CHECK_NULL_RETURN(dragEventActuator_, defaultPixelMap);
    auto frameNode = GetFrameNode();
    RefPtr<PixelMap> preScaledPixelMap;
    if (!(frameNode && frameNode->GetDragPreview().onlyForLifting)) {
        preScaledPixelMap = dragEventActuator_->GetPreScaledPixelMapForDragThroughTouch(preScale);
    }
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
    auto pipeline = frameNode->GetContextRefPtr();
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
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushPipelineImmediately();
        context = dragNode->GetRenderContext();
    } else {
        context = frameNode->GetRenderContext();
    }
    CHECK_NULL_VOID(context);
    auto thumbnailPixelMap = context->GetThumbnailPixelMap(false, GetTextDraggable());
    CHECK_NULL_VOID(thumbnailPixelMap);
    SetPixelMap(thumbnailPixelMap);
}

void GestureEventHub::HandleNotAllowDrag(const GestureEvent& info)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        gestureInfoForWeb_ = std::make_shared<GestureEvent>(info);
        isReceivedDragGestureInfo_ = true;
        TAG_LOGD(AceLogTag::ACE_WEB, "DragDrop drag gesture info received");
    }
}

void GestureEventHub::HandleDragThroughTouch(const RefPtr<FrameNode> frameNode)
{
    CHECK_NULL_VOID(frameNode);
    dragframeNodeInfo_.frameNode = frameNode;
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto grayedState = dragDropManager->GetGrayedState();
    if (grayedState) {
        return;
    }
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
    if (!gatherNodeChildrenInfo.empty()) {
        for (const auto& itemFrameNode : gatherNodeChildrenInfo) {
            auto node = itemFrameNode.preImageNode.Upgrade();
            CHECK_NULL_VOID(node);
            dragframeNodeInfo_.gatherFrameNode.push_back(node);
            DragAnimationHelper::DoDragStartGrayedAnimation(node);
        }
        dragframeNodeInfo_.gatherFrameNode.push_back(frameNode);
    }
    DragAnimationHelper::DoDragStartGrayedAnimation(frameNode);
    dragDropManager->SetGrayedState(true);
}

void GestureEventHub::HandleDragThroughMouse(const RefPtr<FrameNode> frameNode)
{
    CHECK_NULL_VOID(frameNode);
    dragframeNodeInfo_.frameNode = frameNode;
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto grayedState = dragDropManager->GetGrayedState();
    if (grayedState) {
        return;
    }
    auto size = GetSelectItemSize();
    if (size) {
        auto fatherNode = DragDropFuncWrapper::FindItemParentNode(frameNode);
        CHECK_NULL_VOID(fatherNode);
        auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(scrollPattern);
        auto children = scrollPattern->GetVisibleSelectedItems();
        dragframeNodeInfo_.gatherFrameNode = children;
        for (const auto& itemFrameNode : children) {
            DragAnimationHelper::DoDragStartGrayedAnimation(itemFrameNode);
        }
    } else {
        DragAnimationHelper::DoDragStartGrayedAnimation(frameNode);
    }
    dragDropManager->SetGrayedState(true);
}

bool GestureEventHub::IsNeedSwitchToSubWindow(const PreparedInfoForDrag& dragInfoData) const
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (dragInfoData.isMenuShow) {
        return true;
    }
    if (dragInfoData.isNeedCreateTiled) {
        return false;
    }
    if (IsPixelMapNeedScale() || DragDropGlobalController::GetInstance().GetAsyncDragCallback() != nullptr) {
        return true;
    }
    CHECK_NULL_RETURN(dragEventActuator_, false);
    return dragEventActuator_->IsNeedGather();
}

void GestureEventHub::HandleOnDragStart(const GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "Start handle onDragStart.");
    auto frameNode = GetFrameNode();
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (!frameNode || !pipeline || !CheckAllowDrag(info, pipeline, frameNode)) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "Check not allow drag");
        HandleNotAllowDrag(info);
        return;
    }

    // set drag drop status is moving
    DragDropGlobalController::GetInstance().UpdateDragDropInitiatingStatus(frameNode, DragDropInitiatingStatus::MOVING);

    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        SetMouseDragMonitorState(true);
    }

    // create drag event
    auto event = CreateDragEvent(info, pipeline, frameNode);

    /*
     * Users may remove frameNode in the js callback function "onDragStart "triggered below,
     * so save the offset of the framenode relative to the window in advance
     */
    DragDropInfo dragPreviewInfo;
    auto dragDropInfo = GetDragDropInfo(info, frameNode, dragPreviewInfo, event);
    auto continueFunc = [id = Container::CurrentId(), weak = WeakClaim(this), dragPreviewInfo, info, event,
        dragDropInfo, frameNode, pipeline]() {
        ContainerScope scope(id);
        auto gestureEventHub = weak.Upgrade();
        CHECK_NULL_VOID(gestureEventHub);
        if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            gestureEventHub->SetMouseDragMonitorState(true);
        }
        gestureEventHub->DoOnDragStartHandling(info, frameNode, dragDropInfo, event, dragPreviewInfo, pipeline);
    };
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (DragDropGlobalController::GetInstance().GetDragStartRequestStatus() == DragStartRequestStatus::READY) {
        DoOnDragStartHandling(info, frameNode, dragDropInfo, event, dragPreviewInfo, pipeline);
    } else {
        dragDropManager->SetDelayDragCallBack(continueFunc);
        TAG_LOGI(AceLogTag::ACE_DRAG, "drag start pended");
    }
}

bool GestureEventHub::ParsePixelMapAsync(DragDropInfo& dragDropInfo, const DragDropInfo& dragPreviewInfo,
    const GestureEvent& info)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    if (DragDropFuncWrapper::IsNeedCreateTiledPixelMap(frameNode, dragEventActuator_, info.GetSourceDevice())) {
        ACE_SCOPED_TRACE("drag: create titled pixelMap");
        dragDropInfo.pixelMap = DragDropFuncWrapper::CreateTiledPixelMap(frameNode);
        return true;
    }

    if (dragPreviewInfo.inspectorId != "") {
        ACE_SCOPED_TRACE("drag: handling with inspector");
        auto dragPreviewPixelMap = GetDragPreviewPixelMap();
        TAG_LOGI(AceLogTag::ACE_DRAG, "InspectorId exist, get thumbnail.");
        if (dragPreviewPixelMap == nullptr) {
            dragPreviewPixelMap = DragDropFuncWrapper::GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
        }
        dragDropInfo.pixelMap = dragPreviewPixelMap;
        return true;
    }

    if (info.GetSourceDevice() != SourceType::MOUSE) {
        if (dragPreviewInfo.pixelMap != nullptr || dragPreviewInfo.customNode != nullptr) {
            if (dragPreviewPixelMap_ != nullptr) {
                ACE_SCOPED_TRACE("drag: handling with drag preview");
                TAG_LOGI(AceLogTag::ACE_DRAG, "Non-mouse dragging, get thumbnail.");
                dragDropInfo.pixelMap = dragPreviewPixelMap_;
                return true;
            }
        }
    }

    if (dragPreviewInfo.pixelMap != nullptr) {
        ACE_SCOPED_TRACE("drag: handling with pixelmap directly");
        dragDropInfo.pixelMap = dragPreviewInfo.pixelMap;
        TAG_LOGI(AceLogTag::ACE_DRAG, "PixelMap exist, get thumbnail.");
        return true;
    } else if (dragPreviewInfo.customNode != nullptr) {
        dragDropInfo.customNode = dragPreviewInfo.customNode;
    }
    return dragDropInfo.pixelMap;
}

void GestureEventHub::DoOnDragStartHandling(const GestureEvent& info, const RefPtr<FrameNode> frameNode,
    DragDropInfo dragDropInfo, const RefPtr<OHOS::Ace::DragEvent>& event, DragDropInfo dragPreviewInfo,
    const RefPtr<PipelineContext>& pipeline)
{
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    CalcFrameNodeOffsetAndSize(frameNode, isMenuShow);

    // set drag pointer status
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetDraggingPointer(info.GetPointerId());
    dragDropManager->SetDraggingPressedState(true);

    if (ParsePixelMapAsync(dragDropInfo, dragPreviewInfo, info)) {
        OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
        return;
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
    if (!dragDropInfo.pixelMap) {
        GenerateMousePixelMap(info);
        dragDropInfo.pixelMap = pixelMap_;
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && !dragDropInfo.pixelMap) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "no any pixmap got, get node snapshot final try");
        ACE_SCOPED_TRACE("drag: no any pixmap got, get node snapshot final try");
        dragDropInfo.pixelMap = CreatePixelMapFromString(DEFAULT_MOUSE_DRAG_IMAGE);
    }
    OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
}

void GestureEventHub::HideMenu()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDrogDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDrogDropManager);
    SubwindowManager::GetInstance()->HideMenuNG(false, true);
    auto menuWrapperNode = dragDrogDropManager->GetMenuWrapperNode();
    CHECK_NULL_VOID(menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto imageNode = menuWrapperPattern->GetPreview();
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdateOpacity(0.0f);
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
        FireCustomerOnDragEnd(pipeline, eventHub);
        if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            SetMouseDragMonitorState(false);
        }
        DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::APP_REFUSE_DRAG);
        return;
    }
    std::string udKey;
    auto unifiedData = GetUnifiedData(frameNode->GetTag(), dragDropInfo, dragEvent);
    if (unifiedData) {
        DragDropBehaviorReporter::GetInstance().UpdateRecordSize(unifiedData->GetSize());
    }
    int32_t recordsSize = GetBadgeNumber(unifiedData);
    auto ret = SetDragData(unifiedData, udKey);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "UDMF set data failed, return value is %{public}d", ret);
        DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::SET_DATA_FAIL);
    }

    std::map<std::string, int64_t> summary;
    ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
    if (ret != 0) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "UDMF get summary failed, return value is %{public}d", ret);
    }
    dragDropManager->SetSummaryMap(summary);
    RefPtr<PixelMap> pixelMap = dragDropInfo.pixelMap;
    if (pixelMap_ == nullptr) {
        FireCustomerOnDragEnd(pipeline, eventHub);
        TAG_LOGW(AceLogTag::ACE_DRAG, "Thumbnail pixelMap is empty.");
        if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            SetMouseDragMonitorState(false);
        }
        return;
    }
    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    if (dragPreviewOptions.isDefaultDragItemGrayEffectEnabled) {
        (info.GetSourceDevice() == SourceType::MOUSE) ? HandleDragThroughMouse(frameNode)
                                                      : HandleDragThroughTouch(frameNode);
    }
    SetDragGatherPixelMaps(info);
    dragDropManager->SetIsMouseDrag(info.GetInputEventType() == InputEventType::MOUSE_BUTTON);
    auto dragNodePipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(dragNodePipeline);
    auto overlayManager = dragNodePipeline->GetOverlayManager();
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    if (isMenuShow) {
        dragDropManager->SetIsDragWithContextMenu(true);
        TAG_LOGI(AceLogTag::ACE_DRAG, "Drag with contextMenu.");
    } else {
        dragDropManager->SetIsDragWithContextMenu(false);
    }
    float defaultPixelMapScale = GetDefaultPixelMapScale(frameNode, info, isMenuShow, pixelMap);
    auto windowScale = dragDropManager->GetWindowScale();
    float scale = windowScale * defaultPixelMapScale;
    auto isNeedCreateTiled =
        DragDropFuncWrapper::IsNeedCreateTiledPixelMap(frameNode, dragEventActuator_, info.GetSourceDevice());
    PreparedInfoForDrag data = { isMenuShow, recordsSize, defaultPixelMapScale, isNeedCreateTiled, OffsetF(),
        dragDropManager->GetUpdateDragMovePosition(), pixelMap, nullptr };
    dragDropManager->ResetContextMenuDragPosition();
    RefPtr<Subwindow> subWindow = nullptr;
    if (IsNeedSwitchToSubWindow(data)) {
        auto imageNode = overlayManager->GetPixelMapContentNode();
        DragEventActuator::CreatePreviewNode(frameNode, imageNode, defaultPixelMapScale);
        CHECK_NULL_VOID(imageNode);
        data.imageNode = imageNode;
        data.dragPreviewOffsetToScreen = GetDragPreviewInitPositionToScreen(context, data);
        float previewScale =
            info.GetInputEventType() == InputEventType::MOUSE_BUTTON ? 1.0f : DEFALUT_DRAG_PPIXELMAP_SCALE;
        if (IsPixelMapNeedScale()) {
            previewScale = DragDropFuncWrapper::GetPixelMapScale(frameNode);
            scale = previewScale * windowScale;
        }
        data.previewScale = previewScale;
        // use menu preview scale replace default pixelMap scale.
        if (isMenuShow) {
            ProcessMenuPreviewScale(imageNode, scale, previewScale, windowScale, defaultPixelMapScale);
        }
        {
            ACE_SCOPED_TRACE("drag: sub window show");
            auto mainPipeline = PipelineContext::GetMainPipelineContext();
            subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipeline != mainPipeline));
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
    auto extraInfoLimited = dragDropInfo.extraInfo.size() > EXTRA_INFO_MAX_LENGTH
                                ? dragDropInfo.extraInfo.substr(EXTRA_INFO_MAX_LENGTH + 1)
                                : dragDropInfo.extraInfo;
    auto innerRect = ParseInnerRect(extraInfoLimited, SizeF(width, height));
    auto pixelMapOffset = GetPixelMapOffset(info, SizeF(width, height), data, scale, innerRect);
    windowScale = NearZero(windowScale) ? 1.0f : windowScale;
    dragDropManager->SetPixelMapOffset(pixelMapOffset / windowScale);
    DragDropFuncWrapper::ResetNode(frameNode);
    auto arkExtraInfoJson = JsonUtil::Create(true);
    auto dragNodeGrayscale = pipeline->GetDragNodeGrayscale();
    auto dipScale = pipeline->GetDipScale();
    arkExtraInfoJson->Put("scale", scale);
    arkExtraInfoJson->Put("dip_scale", dipScale);
    arkExtraInfoJson->Put("drag_node_gray_scale", dragNodeGrayscale);
    arkExtraInfoJson->Put("event_id", info.GetPointerEventId());
    UpdateExtraInfo(frameNode, arkExtraInfoJson, scale, data);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    DragDropBehaviorReporterTrigger trigger(DragReporterPharse::DRAG_START, container->GetInstanceId());
    auto windowId = container->GetWindowId();
    ShadowInfoCore shadowInfo { pixelMapDuplicated, pixelMapOffset.GetX(), pixelMapOffset.GetY() };
    auto dragMoveLastPoint = dragDropManager->GetDragMoveLastPoint();
    DragDataCore dragData { { shadowInfo }, {}, udKey, extraInfoLimited, arkExtraInfoJson->ToString(),
        static_cast<int32_t>(info.GetSourceDevice()), recordsSize, info.GetPointerId(),
        static_cast<int32_t>(info.GetSourceTool()), dragMoveLastPoint.GetScreenX(),
        dragMoveLastPoint.GetScreenY(), info.GetTargetDisplayId(), windowId, true, false, summary };
    std::string summarys = DragDropFuncWrapper::GetSummaryString(summary);
    DragDropBehaviorReporter::GetInstance().UpdateSummaryType(summarys);
    TAG_LOGI(AceLogTag::ACE_DRAG,
        "Start drag, frameNode is %{public}s, pixelMap width %{public}d height %{public}d, "
        "scale is %{public}f, udkey %{public}s, recordsSize %{public}d, extraInfo length %{public}d, "
        "pointerId %{public}d, toolType %{public}d, displayId %{public}d, windowId %{public}d, summary %{public}s, "
        "eventId %{public}d.",
        frameNode->GetTag().c_str(), width, height, scale, DragDropFuncWrapper::GetAnonyString(udKey).c_str(),
        recordsSize, static_cast<int32_t>(extraInfoLimited.length()), info.GetPointerId(),
        static_cast<int32_t>(info.GetSourceTool()), info.GetTargetDisplayId(), windowId, summarys.c_str(),
        info.GetPointerEventId());
    dragDropManager->GetGatherPixelMap(dragData, scale, width, height);
    {
        ACE_SCOPED_TRACE("drag: call msdp start drag");
        ret = InteractionInterface::GetInstance()->StartDrag(dragData, GetDragCallback(pipeline, eventHub));
    }
    if (ret != 0) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::DRAGFWK_START_FAIL);
        if (subWindow) {
            SubwindowManager::GetInstance()->HidePreviewNG();
            overlayManager->RemovePixelMap();
        }
        FireCustomerOnDragEnd(pipeline, eventHub);
        TAG_LOGW(AceLogTag::ACE_DRAG, "Start drag failed, return value is %{public}d", ret);
        return;
    }
    StartVibratorByDrag(frameNode);
    dragEventActuator_->NotifyDragStart();
    DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::DRAG_START_SUCCESS);
    bool isSwitchedToSubWindow = false;
    if (subWindow && TryDoDragStartAnimation(context, subWindow, info, data)) {
        isSwitchedToSubWindow = true;
    } else {
        HideMenu();
        DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
    }
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && isSwitchedToSubWindow) {
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
        if (!isSwitchedToSubWindow) {
            overlayManager->RemovePixelMap();
            overlayManager->RemovePreviewBadgeNode();
            overlayManager->RemoveGatherNode();
            dragEventActuator_->NotifyTransDragWindowToFwk();
            pipeline->AddAfterRenderTask([]() {
                ACE_SCOPED_TRACE("drag: set drag window visible, touch");
                InteractionInterface::GetInstance()->SetDragWindowVisible(true);
            });
        }
    } else if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON) {
        if (!isSwitchedToSubWindow) {
            dragEventActuator_->NotifyTransDragWindowToFwk();
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
        dragDropManager->SetIsDisableDefaultDropAnimation(true);
        dragDropManager->OnDragEnd(
            DragPointerEvent(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY()), extraInfoLimited);
    }
}

void GestureEventHub::StartVibratorByDrag(const RefPtr<FrameNode>& frameNode)
{
    bool enableHapticFeedback = frameNode->GetDragPreviewOption().enableHapticFeedback;
    auto parent = frameNode->GetAncestorNodeOfFrame(false);
    if (parent && parent->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
        enableHapticFeedback = parent->GetDragPreviewOption().enableHapticFeedback;
    }
    if (!enableHapticFeedback || !DragDropGlobalController::GetInstance().IsDragFilterShowing()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Enable haptic feedback, start vibrator by drag.");
    VibratorUtils::StartViratorDirectly("haptic.drag");
    DragDropGlobalController::GetInstance().UpdateDragFilterShowingStatus(false);
}

void GestureEventHub::UpdateExtraInfo(const RefPtr<FrameNode>& frameNode, std::unique_ptr<JsonValue>& arkExtraInfoJson,
    float scale, const PreparedInfoForDrag& dragInfoData)
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
    if (dragInfoData.isNeedCreateTiled) {
        return;
    }
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
            TaskExecutor::TaskType::UI, "ArkUIGestureHideDragPreviewOverlay", PriorityType::VIP);
    };
    return InteractionInterface::GetInstance()->RegisterCoordinationListener(callback);
}

void GestureEventHub::HandleOnDragUpdate(const GestureEvent& info)
{
    gestureInfoForWeb_ = std::make_shared<GestureEvent>(info);
}

void GestureEventHub::HandleDragEndAction(const DragframeNodeInfo& info)
{
    auto weakFrameNode = info.frameNode;
    auto frameNode = weakFrameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    if (!dragPreviewOptions.isDefaultDragItemGrayEffectEnabled) {
        return;
    }
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto state = dragDropManager->GetGrayedState();
    if (!state) {
        return;
    }
    if (!info.gatherFrameNode.empty()) {
        auto gatherFrameNode = info.gatherFrameNode;
        for (const auto& itemFrameNode : gatherFrameNode) {
            DragAnimationHelper::SetPreOpacity(itemFrameNode);
        }
    } else {
        DragAnimationHelper::SetPreOpacity(frameNode);
    }
    dragDropManager->SetGrayedState(false);
}

void GestureEventHub::HandleOnDragEnd(const GestureEvent& info)
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
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
    HandleDragEndAction(dragframeNodeInfo_);
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
    auto callback = [id = Container::CurrentId(), eventHub, dragEvent, taskScheduler, dragDropManager, eventManager,
                        dragframeNodeInfo = dragframeNodeInfo_,
                        gestureEventHubPtr = AceType::Claim(this)](const DragNotifyMsgCore& notifyMessage) {
        ContainerScope scope(id);
        taskScheduler->PostTask(
            [eventHub, dragEvent, dragDropManager, eventManager, notifyMessage, id, dragframeNodeInfo,
                gestureEventHubPtr]() {
                auto container = Container::GetContainer(id);
                if (!container) {
                    TAG_LOGE(AceLogTag::ACE_DRAG, "handle drag end callback, can not get container.");
                    return;
                }
                DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
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
                gestureEventHubPtr->HandleDragEndAction(dragframeNodeInfo);
                auto dragEventActuator = gestureEventHubPtr->GetDragEventActuator();
                CHECK_NULL_VOID(dragEventActuator);
                dragEventActuator->NotifyDragEnd();
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
        auto dragPreview = frameNode->GetDragPreview();
        if (dragPreview.onlyForLifting) {
            return dragDropInfo;
        }
        if (!dragPreview.customNode && dragPreview.delayCreating && dragPreview.buildFunc) {
            dragPreview.customNode = dragPreview.buildFunc();
        }
        frameNode->SetDragPreview(dragPreview);
        dragPreviewInfo = dragPreview;
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

bool GestureEventHub::IsDragForbidden() const
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
    if (frameNode->GetDragPreviewOption().isMultiTiled && !dragEventActuator_->GetRestartDrag()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->ClearGatherPixelMap();
    CHECK_NULL_VOID(dragEventActuator_);
    auto fatherNode = DragDropFuncWrapper::FindItemParentNode(frameNode);
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
        auto itemPreviewPixelMap = gestureHub->GetDragPreviewPixelMap();
        if (!itemPreviewPixelMap) {
            continue;
        }
        dragDropManager->PushGatherPixelMap(itemPreviewPixelMap);
        cnt++;
        if (cnt > 1) {
            break;
        }
    }
}

void GestureEventHub::SetNotMouseDragGatherPixelMaps()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
        auto itemPreviewPixelMap = imageSourceInfo.GetPixmap();
        if (!itemPreviewPixelMap) {
            continue;
        }
        dragDropManager->PushGatherPixelMap(itemPreviewPixelMap);
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
    auto fatherNode = DragDropFuncWrapper::FindItemParentNode(GetFrameNode());
    CHECK_NULL_RETURN(fatherNode, 0);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, 0);
    auto children = scrollPattern->GetVisibleSelectedItems();
    return children.size();
}

void GestureEventHub::FireCustomerOnDragEnd(const RefPtr<PipelineBase>& context, const WeakPtr<EventHub>& hub)
{
    DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
    auto eventHub = hub.Upgrade();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->RemoveDeadlineTimer();
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
            "customNode has ImageNode, syncLoad: %{public}d, decode complete: %{public}d",
            pattern->GetSyncLoad(), pattern->GetCanvasImage() != nullptr);
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
            TAG_LOGW(AceLogTag::ACE_DRAG, "ImageNode did not complete decoding");
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
        dragDropInfo, event](std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()>
        finishCallback) mutable {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("drag: get snapshot async done, post task to UI for next handling");
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail callback executed.");
        if (pixelMap != nullptr) {
            dragDropInfo.pixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
        } else {
            DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::SNAPSHOT_FAIL);
        }
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [pipeline, info, gestureEventHubPtr, frameNode, dragDropInfo, event, finishCallback]() {
                TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail finished, start drag.");
                if (finishCallback) {
                    finishCallback();
                }
                CHECK_NULL_VOID(gestureEventHubPtr);
                CHECK_NULL_VOID(frameNode);
                gestureEventHubPtr->OnDragStart(info, pipeline, frameNode, dragDropInfo, event);
            },
            TaskExecutor::TaskType::UI, "ArkUIGestureDragStart", PriorityType::VIP);
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

OffsetF GestureEventHub::GetDragPreviewInitPositionToScreen(
    const RefPtr<PipelineBase>& context, PreparedInfoForDrag& data)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, OffsetF());
    OffsetF previewOffset;
    OffsetF pixelMapHalfSize = data.pixelMap ? OffsetF(data.pixelMap->GetWidth() / 2.0f,
        data.pixelMap->GetHeight() / 2.0f) : OffsetF();
    previewOffset = DragDropFuncWrapper::GetPaintRectCenterToScreen(frameNode) - pixelMapHalfSize;
    auto frameTag = frameNode->GetTag();
    if (IsPixelMapNeedScale() && GetTextDraggable() && IsTextCategoryComponent(frameTag)) {
        auto textDragPattern = frameNode->GetPattern<TextDragBase>();
        CHECK_NULL_RETURN(textDragPattern, previewOffset);
        auto dragNode = textDragPattern->MoveDragNode();
        if (dragNode) {
            previewOffset = DragDropFuncWrapper::GetPaintRectCenterToScreen(dragNode) - pixelMapHalfSize;
            return previewOffset;
        }
    }

    if (IsPixelMapNeedScale() && frameTag == V2::WEB_ETS_TAG) {
        auto offset = DragDropFuncWrapper::GetCurrentWindowOffset(context);
        return frameNodeOffset_ + offset;
    }

    if (data.isMenuShow) {
        OffsetF menuPreviewCenter = frameNodeOffset_ + OffsetF(frameNodeSize_.Width(), frameNodeSize_.Height()) / 2.0f;
        menuPreviewCenter += DragDropFuncWrapper::GetCurrentWindowOffset(context);
        previewOffset = menuPreviewCenter - pixelMapHalfSize + data.dragMovePosition;
    }
    return previewOffset;
}

int32_t GestureEventHub::GetBadgeNumber(const RefPtr<UnifiedData>& unifiedData)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, 1);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, 1);
    int32_t badgeNumber = 1;
    pattern->ResetDragOption();
    if (pattern->GetDragRecordSize() >= 0) {
        badgeNumber = pattern->GetDragRecordSize();
    } else if (unifiedData) {
        auto recordSize = unifiedData->GetSize();
        badgeNumber = recordSize > 1 ? recordSize : 1;
    }

    auto dragPreviewOptions = frameNode->GetDragPreviewOption();
    auto customBadgeNumber = dragPreviewOptions.GetCustomerBadgeNumber();
    auto selectItemSize = GetSelectItemSize();
    if (customBadgeNumber.has_value()) {
        badgeNumber = customBadgeNumber.value();
        TAG_LOGI(AceLogTag::ACE_DRAG, "Use custom badge number, value is %{public}d", badgeNumber);
    } else if (selectItemSize > 1) {
        badgeNumber = selectItemSize;
        TAG_LOGI(AceLogTag::ACE_DRAG, "Use select item size, value is %{public}d", badgeNumber);
    }
    return badgeNumber;
}

bool GestureEventHub::TryDoDragStartAnimation(const RefPtr<PipelineBase>& context, const RefPtr<Subwindow>& subWindow,
    const GestureEvent& info, PreparedInfoForDrag& data)
{
    auto frameNode = GetFrameNode();
    auto container = Container::Current();
    auto eventHub = eventHub_.Upgrade();
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    if (!subWindow || !frameNode || !container || !pipeline || !eventHub || !data.imageNode) {
        return false;
    }

    auto dragNodePipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(dragNodePipeline, false);
    auto overlayManager = dragNodePipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto isExpandDisplay = DragDropFuncWrapper::IsExpandDisplay(context);

    // create text node
    auto subWindowOffset = isExpandDisplay ? subWindow->GetWindowRect().GetOffset() : OffsetF();
    auto textNode = DragAnimationHelper::CreateBadgeTextNode(data.badgeNumber);
    DragAnimationHelper::SetNodeVisible(textNode, false);
    // create gatherNode
    auto originGatherNode = overlayManager->GetGatherNode();
    OffsetF positionToWindow = originGatherNode ? originGatherNode->GetPositionToWindowWithTransform() : OffsetF();
    std::vector<GatherNodeChildInfo> childrenInfo;
    auto gatherNode = DragAnimationHelper::GetOrCreateGatherNode(overlayManager, dragEventActuator_, childrenInfo);
    auto gatherNodeOffset = isExpandDisplay
            ? DragDropManager::GetTouchOffsetRelativeToSubwindow(dragNodePipeline->GetInstanceId()) + positionToWindow
            : positionToWindow;
    DragEventActuator::UpdateGatherAnimatePosition(childrenInfo, gatherNodeOffset);

    // mount node
    auto subWindowOverlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_RETURN(subWindowOverlayManager, false);
    DragEventActuator::MountGatherNode(subWindowOverlayManager, frameNode, gatherNode, childrenInfo);
    DragEventActuator::MountPixelMap(
        subWindowOverlayManager, eventHub->GetOrCreateGestureEventHub(), data.imageNode, textNode, true);

    // update position
    DragAnimationHelper::UpdateBadgeTextNodePosition(frameNode, textNode, data.badgeNumber, data.previewScale,
        data.dragPreviewOffsetToScreen - subWindowOffset);
    DragDropFuncWrapper::UpdateNodePositionToScreen(data.imageNode, data.dragPreviewOffsetToScreen);
    HideMenu();
    DragAnimationHelper::PreLayout(data.imageNode);
    pipeline->FlushSyncGeometryNodeTasks();
    overlayManager->RemovePixelMap();
    DragAnimationHelper::ShowBadgeAnimation(textNode);
    DragAnimationHelper::HideDragNodeCopy(overlayManager);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);

    dragDropManager->DoDragStartAnimation(
        subWindowOverlayManager, info, eventHub->GetOrCreateGestureEventHub(), data.isMenuShow);
    return true;
}

bool GestureEventHub::CheckAllowDrag(const GestureEvent& info, const RefPtr<PipelineBase>& context,
    const RefPtr<FrameNode>& frameNode)
{
    auto eventHub = eventHub_.Upgrade();
    CHECK_NULL_RETURN(eventHub, false);
    CHECK_NULL_RETURN(frameNode, false);
    if (!eventHub->HasOnDragStart()) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "FrameNode is not set onDragStart event.");
        return false;
    }
    if (!IsAllowedDrag(eventHub)) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_RETURN(pattern, false);
        TAG_LOGE(AceLogTag::ACE_DRAG,
            "FrameNode is not allow drag, tag is %{public}s"
            "draggable is %{public}d, drag start event is %{public}d,"
            "default support drag is %{public}d, user set is %{public}d.",
            frameNode->GetTag().c_str(), frameNode->IsDraggable(), eventHub->HasOnDragStart(),
            pattern->DefaultSupportDrag(), frameNode->IsUserSet());
        return false;
    }
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, false);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    if (info.GetInputEventType() == InputEventType::MOUSE_BUTTON && eventManager->IsLastMoveBeforeUp()) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "Drag stop because user release mouse button");
        return false;
    }

    return true;
}

RefPtr<OHOS::Ace::DragEvent> GestureEventHub::CreateDragEvent(const GestureEvent& info,
    const RefPtr<PipelineBase>& context, const RefPtr<FrameNode>& frameNode)
{
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    CHECK_NULL_RETURN(frameNode, event);
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    if (frameNode->GetTag() == V2::WEB_ETS_TAG) {
        CHECK_NULL_RETURN(pipeline, event);
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
    return event;
}

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
    if (!dragEventActuator_ || dragEventActuator_->GetIsNewFwk()) {
        dragEventActuator_ = MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    dragEventActuator_->ReplaceDragEvent(dragEvent);
}

void GestureEventHub::SetDragDropEvent()
{
    if (!dragEventActuator_ || !dragEventActuator_->GetIsNewFwk()) {
        dragEventActuator_ = MakeRefPtr<DragDropEventActuator>(WeakClaim(this));
    }
}

void GestureEventHub::SetCustomDragEvent(
    const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, Dimension distance)
{
    if (!dragEventActuator_ || dragEventActuator_->GetIsNewFwk()) {
        dragEventActuator_ = MakeRefPtr<DragEventActuator>(WeakClaim(this), direction, fingers, distance.ConvertToPx());
    }
    dragEventActuator_->SetCustomDragEvent(dragEvent);
}

bool GestureEventHub::HasDragEvent() const
{
    return dragEventActuator_ && (dragEventActuator_->HasDragEvent() || dragEventActuator_->GetIsNewFwk());
}

void GestureEventHub::RemoveDragEvent()
{
    if (!dragEventActuator_) {
        return;
    }
    if (dragEventActuator_->GetIsNewFwk()) {
        dragEventActuator_ = nullptr;
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

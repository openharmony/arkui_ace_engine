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
#include "core/components_ng/manager/drag_drop/drag_drop_controller_func_wrapper.h"

#include "base/image/pixel_map.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/animation_option.h"
#include "core/common/container_consts.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SCALE_NUMBER = 0.95f;
constexpr float TOUCH_DRAG_PIXELMAP_SCALE = 1.05f;
constexpr int32_t RESERVED_DEVICEID = 0xAAAAAAFF;
constexpr Dimension BADGE_RELATIVE_OFFSET = 8.0_vp;
constexpr int32_t GATHER_COUNT = 2;
constexpr int32_t MIN_EFFECTIVE_PIXELMAP_COUNT = 2;
}

OffsetF DragControllerFuncWrapper::GetUpdateDragMovePosition(int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_RETURN(pipelineContext, OffsetF(0.0f, 0.0f));
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(manager, OffsetF(0.0f, 0.0f));
    return manager->GetUpdateDragMovePosition();
}

void DragControllerFuncWrapper::ResetContextMenuDragPosition(int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->ResetContextMenuDragPosition();
}

void DragControllerFuncWrapper::CreatePreviewNode(RefPtr<FrameNode>& imageNode, PreparedInfoForDrag& data,
    PreparedAsyncCtxForAnimate& asyncCtxData)
{
    auto frameOffset = GetOriginNodeOffset(data, asyncCtxData);
    imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() {return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);
    imageNode->SetDragPreviewOptions(asyncCtxData.dragPreviewOption);

    auto renderProps = imageNode->GetPaintProperty<ImageRenderProperty>();
    renderProps->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto props = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    props->UpdateAutoResize(false);
    props->UpdateImageSourceInfo(ImageSourceInfo(data.pixelMap));
    auto targetSize = CalcSize(NG::CalcLength(data.pixelMap->GetWidth()), NG::CalcLength(data.pixelMap->GetHeight()));
    props->UpdateUserDefinedIdealSize(targetSize);
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(imagePattern);
    imagePattern->SetSyncLoad(true);

    UpdatePreviewPositionAndScale(imageNode, frameOffset, 1.0f);
    UpdatePreviewAttr(imageNode, asyncCtxData.dragPreviewOption);
}

OffsetF DragControllerFuncWrapper::GetOriginNodeOffset(
    PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData)
{
    CHECK_NULL_RETURN(data.pixelMap, OffsetF());
    OffsetF pointPosition(static_cast<float>(asyncCtxData.dragPointerEvent.windowX),
        static_cast<float>(asyncCtxData.dragPointerEvent.windowY));
    auto container = AceEngine::Get().GetContainer(asyncCtxData.containerId);
    CHECK_NULL_RETURN(container, OffsetF());
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto windowOffset = DragDropFuncWrapper::GetCurrentWindowOffset(pipeline);
    pointPosition += windowOffset;
    auto pixelMapScaledOffset = GetPixelMapScaledOffset(pointPosition, data, asyncCtxData);
    auto offsetX = pixelMapScaledOffset.GetX() +
        (data.pixelMap->GetWidth() * data.previewScale) / 2.0f -data.pixelMap->GetWidth() / 2.0f;
    auto offsetY = pixelMapScaledOffset.GetY() +
        (data.pixelMap->GetHeight() * data.previewScale) / 2.0f - data.pixelMap->GetHeight() / 2.0f;
    auto offset = OffsetF(offsetX, offsetY);
    return offset;
}

OffsetF DragControllerFuncWrapper::GetPixelMapScaledOffset(const OffsetF& pointPosition, PreparedInfoForDrag& data,
    PreparedAsyncCtxForAnimate& asyncCtxData)
{
    CHECK_NULL_RETURN(data.pixelMap, OffsetF());
    auto globalX = pointPosition.GetX();
    auto globalY = pointPosition.GetY();
    auto touchPointOffset = GetTouchPointOffset(data, asyncCtxData);
    auto frameOffset = OffsetF(globalX - touchPointOffset.GetX(), globalY - touchPointOffset.GetY());
    return frameOffset;
}

std::shared_ptr<ScaleDataInfo> DragControllerFuncWrapper::GetScaleInfo(int32_t containerId, float width, float height)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_RETURN(container, nullptr);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, nullptr);
    auto scaleData = dragDropManager->GetScaleInfo(width, height, false);
    CHECK_NULL_RETURN(scaleData, nullptr);
    return scaleData;
}

OffsetF DragControllerFuncWrapper::GetTouchPointOffset(
    PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData)
{
    CHECK_NULL_RETURN(data.pixelMap, OffsetF());
    int32_t width = data.pixelMap->GetWidth() * data.previewScale;
    int32_t height = data.pixelMap->GetHeight() * data.previewScale;
    Dimension XTouch(asyncCtxData.touchPoint.GetX());
    Dimension yTouch(asyncCtxData.touchPoint.GetY());
    double touchPointX = XTouch.ConvertToPx();
    double touchPointY = yTouch.ConvertToPx();
    if (XTouch.Unit() == DimensionUnit::PERCENT) {
        touchPointX = XTouch.Value() * width;
    }
    if (yTouch.Unit() == DimensionUnit::PERCENT) {
        touchPointY = yTouch.Value() * height;
    }
    
    if (!asyncCtxData.hasTouchPoint) {
        touchPointX = -width * PIXELMAP_WIDTH_RATE;
        touchPointY = -height * PIXELMAP_HEIGHT_RATE;
    }
    auto touchPointOffset = OffsetF(touchPointX, touchPointY);
    return touchPointOffset;
}

void DragControllerFuncWrapper::UpdatePreviewPositionAndScale(
    const RefPtr<FrameNode>& imageNode, const OffsetF& frameOffset, float scale)
{
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(frameOffset.GetX()), Dimension(frameOffset.GetY())));
    if (GreatNotEqual(scale, 0.0f)) {
        imageContext->UpdateTransformScale({ scale, scale });
    }
    ClickEffectInfo clickEffectInfo;
    clickEffectInfo.level = ClickEffectLevel::LIGHT;
    clickEffectInfo.scaleNumber = SCALE_NUMBER;
    imageContext->UpdateClickEffectLevel(clickEffectInfo);
}

void DragControllerFuncWrapper::UpdatePreviewAttr(
    const RefPtr<FrameNode>& imageNode, DragPreviewOption& dragPreviewOption)
{
    CHECK_NULL_VOID(imageNode);
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);

    imageContext->UpdateOpacity(dragPreviewOption.options.opacity);
    if (dragPreviewOption.options.shadow.has_value()) {
        imageContext->UpdateBackShadow(dragPreviewOption.options.shadow.value());
    }
    if (dragPreviewOption.options.borderRadius.has_value()) {
        imageContext->UpdateBorderRadius(dragPreviewOption.options.borderRadius.value());
        imageContext->UpdateClipEdge(true);
    }
    auto optionsFromModifier = dragPreviewOption.options;
    if (optionsFromModifier.blurbgEffect.backGroundEffect.radius.IsValid()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundEffect, optionsFromModifier.blurbgEffect.backGroundEffect, imageNode);
    }
    imageContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
}

void DragControllerFuncWrapper::MarkDirtyNode(const RefPtr<FrameNode>& gatherNode)
{
    CHECK_NULL_VOID(gatherNode);
    gatherNode->MarkModifyDone();
    gatherNode->SetLayoutDirtyMarked(true);
    auto context = gatherNode->GetContext();
    if (context) {
        context->FlushUITaskWithSingleDirtyNode(gatherNode);
    }

    auto children = gatherNode->GetChildren();
    for (const auto& child : children) {
        CHECK_NULL_VOID(child);
        auto imageNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(imageNode);
        imageNode->MarkModifyDone();
        imageNode->SetLayoutDirtyMarked(true);
        if (context) {
            context->FlushUITaskWithSingleDirtyNode(imageNode);
        }
    }
}

RefPtr<Subwindow> DragControllerFuncWrapper::SubWindowShow(const RefPtr<PipelineBase>& context)
{
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    RefPtr<Subwindow> subWindow = nullptr;
    {
        ACE_SCOPED_TRACE("drag: sub window show");
        auto mainPipeline = PipelineContext::GetMainPipelineContext();
        subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipelineContext != mainPipeline));
    }
    return subWindow;
}

bool DragControllerFuncWrapper::TryDoDragStartAnimation(const RefPtr<Subwindow>& subWindow, PreparedInfoForDrag& data,
    PreparedAsyncCtxForAnimate& asyncCtxData)
{
    auto container = AceEngine::Get().GetContainer(asyncCtxData.containerId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(pipelineContext, false);
    CHECK_NULL_RETURN(data.imageNode, false);
    CHECK_NULL_RETURN(subWindow, false);

    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto isExpandDisplay = DragDropFuncWrapper::IsExpandDisplay(pipeline);

    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    
    auto touchPointOffset = GetTouchPointOffset(data, asyncCtxData);
    auto windowScale = container->GetWindowScale();
    windowScale = NearZero(windowScale) ? -1.0f : -windowScale;
    auto pixelMapOffset = touchPointOffset / windowScale;
    dragDropManager->SetPixelMapOffset(pixelMapOffset);

    // create text node
    auto subWindowOffset = isExpandDisplay ? subWindow->GetWindowRect().GetOffset() : OffsetF();
    auto textNode = DragAnimationHelper::CreateBadgeTextNode(data.badgeNumber);

    // create gatherNode
    auto originGatherNode = overlayManager->GetGatherNode();
    std::vector<GatherNodeChildInfo> childrenInfo;
    auto gatherNode = GetOrCreateGatherNode(overlayManager, childrenInfo, data, asyncCtxData);

    // mount node
    auto subWindowOverlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_RETURN(subWindowOverlayManager, false);
    subWindowOverlayManager->MountGatherNodeToRootNode(gatherNode, childrenInfo);
    MountPixelMap(
        subWindowOverlayManager, data, data.imageNode, textNode, true);

    // update position
    DragDropManager::UpdateGatherNodePosition(subWindowOverlayManager, data.imageNode);
    UpdateBadgeTextNodePosition(textNode, data, asyncCtxData,
        data.dragPreviewOffsetToScreen - subWindowOffset);
    DragDropFuncWrapper::UpdateNodePositionToScreen(data.imageNode, data.dragPreviewOffsetToScreen);

    auto subwindowContext = data.imageNode->GetContext();
    if (subwindowContext) {
        subwindowContext->FlushSyncGeometryNodeTasks();
        subwindowContext->PreLayout(subwindowContext->GetTimeFromExternalTimer(), 0);
    }
    pipelineContext->FlushSyncGeometryNodeTasks();
    overlayManager->RemovePixelMap();
    dragDropManager->SetIsShowBadgeAnimation(true);
    DragAnimationHelper::ShowBadgeAnimation(textNode);

    DoDragStartAnimation(subWindowOverlayManager, data, asyncCtxData);
    return true;
}

void DragControllerFuncWrapper::UpdateGatherAnimatePosition(
    std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, const OffsetF& GatherNodeOffset)
{
    for (const auto& child : gatherNodeChildrenInfo) {
        auto imageNode = child.imageNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        auto childFrameOffset = imageContext->GetPaintRectWithoutTransform();
        imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(GatherNodeOffset.GetX() + childFrameOffset.GetX()),
            Dimension(GatherNodeOffset.GetY() + childFrameOffset.GetY())));
    }
}

RefPtr<FrameNode> DragControllerFuncWrapper::GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
    std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, PreparedInfoForDrag& data,
    PreparedAsyncCtxForAnimate& asyncCtxData)
{
    if (asyncCtxData.pixelMapList.size() <= 1) {
        return nullptr;
    }
    CHECK_NULL_RETURN(overlayManager, nullptr);
    auto gatherNode = overlayManager->GetGatherNode();
    if (!gatherNode) {
        auto gatherNode = CreateGatherNode(gatherNodeChildrenInfo, data, asyncCtxData);
        if (gatherNode) {
            MarkDirtyNode(gatherNode);
        }
        return gatherNode;
    } else {
        gatherNodeChildrenInfo = overlayManager->GetGatherNodeChildrenInfo();
        overlayManager->RemoveGatherNode();
    }
    return gatherNode;
}

RefPtr<FrameNode> DragControllerFuncWrapper::CreateGatherNode(std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
    PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(manager, nullptr);

    if (manager->GetHasGatherNode()) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Not need create gather node, already have");
        return nullptr;
    }
    auto stackNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto geometryNode = stackNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    geometryNode->SetFrameOffset({0.0f, 0.0f});
    gatherNodeChildrenInfo.clear();
    int iterationCount = GATHER_COUNT;
    auto frameOffset = GetOriginNodeOffset(data, asyncCtxData);
    // ignore first pixmap
    if (asyncCtxData.pixelMapList.size() < MIN_EFFECTIVE_PIXELMAP_COUNT) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Create empty gather node success");
        return stackNode;
    }
    for (auto it = std::next(asyncCtxData.pixelMapList.begin(), 1);
         it != asyncCtxData.pixelMapList.end() && iterationCount > 0; ++it) {
        CHECK_NULL_RETURN(*it, nullptr);
        auto refPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&(*it)));
        CHECK_NULL_RETURN(refPixelMap, nullptr);
        auto imageNode = DragAnimationHelper::CreateImageNode(refPixelMap);
        CHECK_NULL_RETURN(imageNode, nullptr);
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_RETURN(imageContext, nullptr);
        imageContext->UpdatePosition(OffsetT<Dimension>(Dimension(frameOffset.GetX()), Dimension(frameOffset.GetY())));
        auto width = refPixelMap->GetWidth();
        auto height = refPixelMap->GetHeight();
        auto offset = DragDropFuncWrapper::GetPaintRectCenter(data.imageNode) - OffsetF(width / 2.0f, height / 2.0f);
        GatherNodeChildInfo gatherNodeChildInfo = { imageNode,
            offset + DragDropFuncWrapper::GetCurrentWindowOffset(pipeline), width, height, width / 2.0f, height / 2.0f,
            nullptr };
        stackNode->AddChild(imageNode);
        gatherNodeChildrenInfo.insert(gatherNodeChildrenInfo.begin(), gatherNodeChildInfo);
        --iterationCount;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "Create gather node success, count %{public}d",
        static_cast<int32_t>(gatherNodeChildrenInfo.size()));
    return stackNode;
}

void DragControllerFuncWrapper::MountPixelMap(const RefPtr<OverlayManager>& manager, PreparedInfoForDrag& data,
    const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode, bool isDragPixelMap)
{
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(imageNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    columnNode->AddChild(imageNode);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    CHECK_NULL_VOID(data.pixelMap);
    hub->SetPixelMap(data.pixelMap);
    if (textNode) {
        columnNode->AddChild(textNode);
    }
    auto container = Container::Current();
    manager->MountPixelMapToRootNode(columnNode, isDragPixelMap);
    if (imageNode->IsPreviewNeedScale()) {
        auto imageContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(imageContext);
        imageContext->UpdateTransformScale({ 1.0f, 1.0f });
        imageContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    }
    columnNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE);
    columnNode->MarkModifyDone();
    columnNode->SetActive(true);
    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        renderContext->MarkUiFirstNode(false);
        renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f)));
    }
    MarkDirtyNode(columnNode);
    if (!isDragPixelMap) {
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushSyncGeometryNodeTasks();
    }
}

void DragControllerFuncWrapper::UpdateBadgeTextNodePosition(const RefPtr<FrameNode>& textNode,
    PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData, OffsetF previewOffset)
{
    if (data.badgeNumber <= 1) {
        return;
    }
    CHECK_NULL_VOID(textNode);
    auto textRenderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    CHECK_NULL_VOID(data.pixelMap);
    auto width = data.pixelMap->GetWidth();
    auto height = data.pixelMap->GetHeight();

    auto container = AceEngine::Get().GetContainer(asyncCtxData.containerId);
    CHECK_NULL_VOID(container);
    auto windowScale = container->GetWindowScale();
    if (NearZero(windowScale)) {
        windowScale = 1.0f;
    }

    auto originNodeOffset = GetOriginNodeOffset(data, asyncCtxData);
    originNodeOffset -= DragDropFuncWrapper::GetCurrentWindowOffset(textNode->GetContextRefPtr());
    RefPtr<FrameNode> parentNode = textNode->GetAncestorNodeOfFrame(true);
    if (parentNode) {
        originNodeOffset -= parentNode->GetPositionToWindowWithTransform();
    }
    auto offset = previewOffset.NonOffset() ? originNodeOffset : previewOffset;
    
    auto badgeLength = std::to_string(data.badgeNumber).size();
    double textOffsetX = offset.GetX() + width * (data.previewScale / windowScale + 1) / 2 -
                         BADGE_RELATIVE_OFFSET.ConvertToPx() - (BADGE_RELATIVE_OFFSET.ConvertToPx() * badgeLength);
    double textOffsetY =
        offset.GetY() - height * (data.previewScale / windowScale - 1) / 2 - BADGE_RELATIVE_OFFSET.ConvertToPx();
    textRenderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    textRenderContext->UpdatePosition(OffsetT<Dimension>(Dimension(textOffsetX), Dimension(textOffsetY)));
}

void DragControllerFuncWrapper::UpdateDragPreviewScale()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto imageNode = dragDropManager->GetDragPreviewInfo().imageNode;
    CHECK_NULL_VOID(imageNode);
    if (dragDropManager->IsNeedDisplayInSubwindow()) {
        return;
    }
    auto renderContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale({ dragDropManager->GetDragPreviewInfo().scale,
        dragDropManager->GetDragPreviewInfo().scale });
}

void DragControllerFuncWrapper::TransDragWindowToDragFwk(int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (dragDropManager->IsDragFwkShow()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_DRAG, "TransDragWindowToDragFwk is %{public}d", dragDropManager->IsDragFwkShow());
    ACE_SCOPED_TRACE("drag: set drag window visible by transfer");
    InteractionInterface::GetInstance()->SetDragWindowVisible(true);
    DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
    dragDropManager->SetDragFwkShow(true);
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(containerId) : containerId);
    CHECK_NULL_VOID(subwindow);
    auto overlayManager = subwindow->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RemoveDragPixelMap();
    overlayManager->RemoveGatherNode();
    SubwindowManager::GetInstance()->HidePreviewNG();
    dragDropManager->SetDampingOverflowCount(0);
}

Offset DragControllerFuncWrapper::CalcDragMoveOffset(int32_t x, int32_t y)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, Offset());
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, Offset());
    auto info = dragDropManager->GetDragPreviewInfo();
    auto originPoint = info.originOffset;
    originPoint.SetX(originPoint.GetX() - dragDropManager->GetPixelMapOffset().GetX() +
        (info.originScale.x - info.scale) * info.width / 2.0f);
    originPoint.SetY(originPoint.GetY() - dragDropManager->GetPixelMapOffset().GetY() +
        (info.originScale.y - info.scale) * info.height / 2.0f);
    auto touchOffset = DragDropManager::GetTouchOffsetRelativeToSubwindow(Container::CurrentId(), x, y);
    Offset newOffset { touchOffset.GetX() - originPoint.GetX(), touchOffset.GetY() - originPoint.GetY() };
    return newOffset;
}

void DragControllerFuncWrapper::DoDragStartAnimation(
    const RefPtr<OverlayManager>& overlayManager, PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    CHECK_NULL_VOID(overlayManager);

    if (asyncCtxData.dragPointerEvent.deviceId == RESERVED_DEVICEID) {
        dragDropManager->SetDragFwkShow(false);
        TAG_LOGI(AceLogTag::ACE_DRAG, "Do not need animation.");
        TransDragWindowToDragFwk(asyncCtxData.containerId);
        return;
    }
    
    if (!(GetDragPreviewInfo(overlayManager, (asyncCtxData.containerId))
        || (!dragDropManager->IsNeedDisplayInSubwindow() && !data.isMenuShow &&
            !dragDropManager->IsDragWithContextMenu()))) {
        if (dragDropManager->IsDragWithContextMenu()) {
            UpdateDragPreviewScale();
            dragDropManager->SetDragFwkShow(false);
        }
        return;
    }
    CHECK_NULL_VOID(dragDropManager->GetDragPreviewInfo().imageNode);
    dragDropManager->SetDragFwkShow(false);
    dragDropManager->ResetPullMoveReceivedForCurrentDrag();

    auto dragAnimationPointerEvent =
        DragPointerEvent(asyncCtxData.dragPointerEvent.windowX, asyncCtxData.dragPointerEvent.windowY,
            asyncCtxData.dragPointerEvent.displayX, asyncCtxData.dragPointerEvent.displayY,
            asyncCtxData.dragPointerEvent.globalDisplayX, asyncCtxData.dragPointerEvent.globalDisplayY);
    dragDropManager->SetDragAnimationPointerEvent(dragAnimationPointerEvent, nullptr);
    auto gatherNodeCenter = DragDropFuncWrapper::GetPaintRectCenter(dragDropManager->GetDragPreviewInfo().imageNode);

    Point point = { asyncCtxData.dragPointerEvent.windowX, asyncCtxData.dragPointerEvent.windowY };
    Offset newOffset = CalcDragMoveOffset(asyncCtxData.dragPointerEvent.windowX,
        asyncCtxData.dragPointerEvent.windowY);
    dragDropManager->SetCurPointerOffset({ newOffset.GetX(), newOffset.GetY() });

    dragDropManager->SetCurrentAnimationCnt(0);
    dragDropManager->SetAllAnimationCnt(0);
    dragDropManager->SetStartAnimation(false);
    DragAnimationHelper::DragStartAnimation(
        newOffset, overlayManager, gatherNodeCenter, point, asyncCtxData.containerId);
}

bool DragControllerFuncWrapper::GetDragPreviewInfo(const RefPtr<OverlayManager>& overlayManager, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    CHECK_NULL_RETURN(overlayManager, false);
    if (!overlayManager->GetHasDragPixelMap()) {
        return false;
    }
    DragDropManager::DragPreviewInfo dragPreviewInfo;
    auto imageNode = overlayManager->GetDragPixelMapContentNode();
    CHECK_NULL_RETURN(imageNode, false);
    auto badgeNode = overlayManager->GetPixelMapBadgeNode();
    if (badgeNode) {
        dragPreviewInfo.textNode = badgeNode;
    }
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_RETURN(container, false);
    auto width = imageNode->GetGeometryNode()->GetFrameRect().Width();
    auto height = imageNode->GetGeometryNode()->GetFrameRect().Height();
    auto scaleData = dragDropManager->GetScaleInfo(width, height, false);
    CHECK_NULL_RETURN(scaleData, false);
    auto previewOption = imageNode->GetDragPreviewOption();
    if (imageNode->GetTag() != V2::WEB_ETS_TAG && width != 0 && scaleData->isNeedScale &&
        previewOption.isScaleEnabled) {
        dragPreviewInfo.scale = scaleData->scale;
    } else {
        dragPreviewInfo.scale = 1.0f;
    }

    if (!dragDropManager->IsMouseDrag() && dragPreviewInfo.scale == 1.0f) {
        dragPreviewInfo.scale = TOUCH_DRAG_PIXELMAP_SCALE;
    }
    // set menu preview scale only for no scale menu preview.
    if (dragDropManager->IsDragWithContextMenu() && (!previewOption.isScaleEnabled || !scaleData->isNeedScale)) {
        auto imageGestureEventHub = imageNode->GetOrCreateGestureEventHub();
        if (imageGestureEventHub) {
            auto menuPreviewScale = imageGestureEventHub->GetMenuPreviewScale();
            dragPreviewInfo.scale =
                GreatNotEqual(menuPreviewScale, 0.0f) ? menuPreviewScale : TOUCH_DRAG_PIXELMAP_SCALE;
        }
    }
    dragPreviewInfo.height = imageNode->GetGeometryNode()->GetFrameRect().Height();
    dragPreviewInfo.width = static_cast<double>(width);
    dragPreviewInfo.imageNode = imageNode;
    dragPreviewInfo.originOffset = imageNode->GetPositionToWindowWithTransform();
    dragPreviewInfo.originScale = imageNode->GetTransformScale();
    dragPreviewInfo.isDragController = true;
    dragDropManager->SetDragPreviewInfo(dragPreviewInfo);
    return true;
}

void DragControllerFuncWrapper::HideDragPreviewWindow(int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (!dragDropManager->IsDragFwkShow()) {
        dragDropManager->HideDragPreviewWindow(containerId);
    }
}
} // namespace OHOS::Ace::NG

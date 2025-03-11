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

#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"

#include "core/common/ace_engine.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/adapter/component_snapshot.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_OPACITY = 0.95f;
constexpr Dimension PREVIEW_BORDER_RADIUS = 12.0_vp;
constexpr float BLUR_SIGMA_SCALE = 0.57735f;
constexpr float SCALE_HALF = 0.5f;
constexpr float MIN_OPACITY { 0.0f };
constexpr float MAX_OPACITY { 1.0f };
using DragNotifyMsg = OHOS::Ace::DragNotifyMsg;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;
using StopDragCallback = std::function<void()>;
constexpr int32_t MOUSE_POINTER_ID = 1001;
constexpr int32_t SOURCE_TOOL_PEN = 2;
constexpr int32_t SOURCE_TYPE_TOUCH = 2;
constexpr int32_t PEN_POINTER_ID = 102;
constexpr int32_t SOURCE_TYPE_MOUSE = 1;
constexpr size_t SHORT_KEY_LENGTH = 8;
constexpr size_t PLAINTEXT_LENGTH = 4;
constexpr size_t  CONVERT_TIME_BASE = 1000;
#if defined(PIXEL_MAP_SUPPORTED)
constexpr int32_t CREATE_PIXELMAP_TIME = 80;
#endif
}

static bool CheckInternalDragging(const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext || !pipelineContext->IsDragging()) {
        return false;
    }
    return true;
}

void GetShadowInfoArray(
    std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction, std::vector<ShadowInfoCore>& shadowInfos)
{
    auto minScaleWidth = NG::DragDropFuncWrapper::GetScaleWidth(dragAction->instanceId);
    for (auto& pixelMap : dragAction->pixelMapList) {
        double scale = 1.0;
        if (Referenced::RawPtr(pixelMap)) {
            if (pixelMap->GetWidth() > minScaleWidth && dragAction->previewOption.isScaleEnabled) {
                scale = minScaleWidth / pixelMap->GetWidth();
            }
            auto pixelMapScale = dragAction->windowScale * scale;
            pixelMap->Scale(pixelMapScale, pixelMapScale, AceAntiAliasingOption::HIGH);
        }
        int32_t width = pixelMap->GetWidth();
        int32_t height = pixelMap->GetHeight();
        double x = dragAction->touchPointX;
        double y = dragAction->touchPointY;
        if (!dragAction->hasTouchPoint) {
            x = -width * PIXELMAP_WIDTH_RATE;
            y = -height * PIXELMAP_HEIGHT_RATE;
        }
        ShadowInfoCore shadowInfo { pixelMap, -x, -y };
        shadowInfos.push_back(shadowInfo);
    }
}

void PostStopDrag(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction, const RefPtr<Container>& container)
{
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowId = container->GetWindowId();
    taskExecutor->PostTask(
        [dragAction, windowId]() {
            CHECK_NULL_VOID(dragAction);
            TAG_LOGI(AceLogTag::ACE_DRAG, "drag state is reject, stop drag, windowId is %{public}d.", windowId);
            OHOS::Ace::DragDropRet dropResult { OHOS::Ace::DragRet::DRAG_CANCEL, false, windowId,
                OHOS::Ace::DragBehavior::UNKNOWN };
            InteractionInterface::GetInstance()->StopDrag(dropResult);
            InteractionInterface::GetInstance()->SetDragWindowVisible(false);
        },
        TaskExecutor::TaskType::UI, "ArkUIDragStop");
}

bool ConfirmCurPointerEventInfo(
    std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction, const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(dragAction, false);
    CHECK_NULL_RETURN(container, false);
    StopDragCallback stopDragCallback = [dragAction, container]() {
        CHECK_NULL_VOID(dragAction);
        CHECK_NULL_VOID(container);
        bool needPostStopDrag = false;
        if (dragAction->dragState == DragAdapterState::SENDING) {
            needPostStopDrag = true;
        }
        {
            std::lock_guard<std::mutex> lock(dragAction->dragStateMutex);
            dragAction->dragState = DragAdapterState::REJECT;
        }
        if (needPostStopDrag) {
            PostStopDrag(dragAction, container);
        }
    };
    bool getPointSuccess = container->GetCurPointerEventInfo(dragAction->dragPointerEvent,
        std::move(stopDragCallback));
    if (dragAction->dragPointerEvent.sourceType == SOURCE_TYPE_MOUSE) {
        dragAction->dragPointerEvent.pointerId = MOUSE_POINTER_ID;
    } else if (dragAction->dragPointerEvent.sourceType == SOURCE_TYPE_TOUCH &&
        static_cast<int32_t>(dragAction->dragPointerEvent.sourceTool) == SOURCE_TOOL_PEN) {
        dragAction->dragPointerEvent.pointerId = PEN_POINTER_ID;
    }
    return getPointSuccess;
}

void EnvelopedDragData(
    std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction, std::optional<DragDataCore>& dragData)
{
    auto container = AceEngine::Get().GetContainer(dragAction->instanceId);
    CHECK_NULL_VOID(container);

    std::vector<ShadowInfoCore> shadowInfos;
    GetShadowInfoArray(dragAction, shadowInfos);
    if (shadowInfos.empty()) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "shadowInfo array is empty");
        return;
    }
    auto pointerId = dragAction->dragPointerEvent.pointerId;
    std::string udKey;
    std::map<std::string, int64_t> summary;
    int32_t dataSize = 1;
    if (dragAction->unifiedData) {
        int32_t ret = UdmfClient::GetInstance()->SetData(dragAction->unifiedData, udKey);
        if (ret != 0) {
            TAG_LOGI(AceLogTag::ACE_DRAG, "udmf set data failed, return value is %{public}d", ret);
        } else {
            ret = UdmfClient::GetInstance()->GetSummary(udKey, summary);
            if (ret != 0) {
                TAG_LOGI(AceLogTag::ACE_DRAG, "get summary failed, return value is %{public}d", ret);
            }
        }
        dataSize = static_cast<int32_t>(dragAction->unifiedData->GetSize());
    }
    int32_t recordSize = (dataSize != 0 ? dataSize : static_cast<int32_t>(shadowInfos.size()));
    if (dragAction->previewOption.isNumber) {
        recordSize = dragAction->previewOption.badgeNumber > 1 ? dragAction->previewOption.badgeNumber : 1;
    } else if (!dragAction->previewOption.isShowBadge) {
        recordSize = 1;
    }
    auto windowId = container->GetWindowId();
    auto arkExtraInfoJson = JsonUtil::Create(true);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    dragAction->dipScale = pipeline->GetDipScale();
    arkExtraInfoJson->Put("dip_scale", dragAction->dipScale);
    arkExtraInfoJson->Put("event_id", dragAction->dragPointerEvent.pointerEventId);
    NG::DragDropFuncWrapper::UpdateExtraInfo(arkExtraInfoJson, dragAction->previewOption);
    dragData = { shadowInfos, {}, udKey, dragAction->extraParams, arkExtraInfoJson->ToString(),
        dragAction->dragPointerEvent.sourceType, recordSize, pointerId,
        static_cast<int32_t>(dragAction->dragPointerEvent.sourceTool), dragAction->dragPointerEvent.displayX,
        dragAction->dragPointerEvent.displayY, dragAction->dragPointerEvent.displayId, windowId, true, false,
        summary };
}

void HandleCallback(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction,
    const OHOS::Ace::DragNotifyMsg& dragNotifyMsg, const DragAdapterStatus& dragStatus)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "drag notify message result is %{public}d.", dragNotifyMsg.result);
    CHECK_NULL_VOID(dragAction);
    bool hasHandle = false;
    {
        std::lock_guard<std::mutex> lock(dragAction->mutex);
        hasHandle = dragAction->hasHandle;
        dragAction->hasHandle = true;
    }
    if (hasHandle) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(dragAction->instanceId);
    CHECK_NULL_VOID(container);
    if (dragStatus == DragAdapterStatus::ENDED) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ResetDragging();
    }
    int32_t dragState = static_cast<int32_t>(dragStatus);
    dragAction->callback(dragNotifyMsg, dragState);
}

int32_t CheckStartAction(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction,
    const RefPtr<Container>& container, const RefPtr<DragDropManager>& manager)
{
    if (CheckInternalDragging(container)) {
        return -1;
    }
    {
        std::lock_guard<std::mutex> lock(dragAction->dragStateMutex);
        if (manager->GetDragAction() != nullptr && (manager->GetDragAction())->dragState == DragAdapterState::SENDING) {
            return -1;
        }
        dragAction->dragState = DragAdapterState::SENDING;
    }
    DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(dragAction->previewOption);
    auto isGetPointSuccess = ConfirmCurPointerEventInfo(dragAction, container);
    if (!isGetPointSuccess) {
        return -1;
    }
    return 0;
}

int32_t DragDropFuncWrapper::StartDragAction(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction)
{
    CHECK_NULL_RETURN(dragAction, -1);
    auto pipelineContext = PipelineContext::GetContextByContainerId(dragAction->instanceId);
    CHECK_NULL_RETURN(pipelineContext, -1);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_RETURN(manager, -1);
    auto container = AceEngine::Get().GetContainer(dragAction->instanceId);
    CHECK_NULL_RETURN(container, -1);
    auto windowScale = container->GetWindowScale();
    CHECK_NULL_RETURN(windowScale, -1);
    dragAction->windowScale = windowScale;
    manager->SetDragAction(dragAction);
    if (CheckStartAction(dragAction, container, manager) == -1) {
        manager->GetDragAction()->dragState = DragAdapterState::INIT;
        return -1;
    }
    std::optional<DragDataCore> dragData;
    EnvelopedDragData(dragAction, dragData);
    if (!dragData) {
        {
            std::lock_guard<std::mutex> lock(dragAction->dragStateMutex);
            manager->GetDragAction()->dragState = DragAdapterState::INIT;
        }
        return -1;
    }
    OnDragCallback callback = [dragAction, manager](const OHOS::Ace::DragNotifyMsg& dragNotifyMsg) {
        {
            std::lock_guard<std::mutex> lock(dragAction->dragStateMutex);
            dragAction->dragState = DragAdapterState::INIT;
            manager->SetDragAction(dragAction);
        }
        HandleCallback(dragAction, dragNotifyMsg, DragAdapterStatus::ENDED);
    };
    NG::DragDropFuncWrapper::SetDraggingPointerAndPressedState(
        dragAction->dragPointerEvent.pointerId, dragAction->instanceId);
    int32_t ret = InteractionInterface::GetInstance()->StartDrag(dragData.value(), callback);
    if (ret != 0) {
        manager->GetDragAction()->dragState = DragAdapterState::INIT;
        return -1;
    }
    HandleCallback(dragAction, DragNotifyMsg {}, DragAdapterStatus::STARTED);
    pipelineContext->SetIsDragging(true);
    NG::DragDropFuncWrapper::HandleOnDragEvent(dragAction);
    return 0;
}

void DragDropFuncWrapper::HandleOnDragEvent(
    const std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction)
{
    CHECK_NULL_VOID(dragAction);
    auto pipelineContext = PipelineContext::GetContextByContainerId(dragAction->instanceId);
    CHECK_NULL_VOID(pipelineContext);
    std::lock_guard<std::mutex> lock(dragAction->dragStateMutex);
    if (dragAction->dragState == DragAdapterState::SENDING) {
        dragAction->dragState = DragAdapterState::SUCCESS;
        InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        pipelineContext->OnDragEvent(
            { dragAction->dragPointerEvent.displayX, dragAction->dragPointerEvent.displayY },
            DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER);
        NG::DragDropFuncWrapper::DecideWhetherToStopDragging(
            { dragAction->dragPointerEvent.displayX, dragAction->dragPointerEvent.displayY }, dragAction->extraParams,
            dragAction->dragPointerEvent.pointerId, dragAction->instanceId);
    }
}

void DragDropFuncWrapper::SetDraggingPointerAndPressedState(int32_t currentPointerId, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->SetDraggingPointer(currentPointerId);
    manager->SetDraggingPressedState(true);
}

int32_t DragDropFuncWrapper::RequestDragEndPending()
{
    if (!DragDropGlobalController::GetInstance().IsOnOnDropPhase()) {
        return -1;
    }
    static std::atomic<int32_t> gDragDropDelayEndRequestId;
    int32_t id = gDragDropDelayEndRequestId.fetch_add(1);
    return id;
}

int32_t DragDropFuncWrapper::NotifyDragResult(int32_t requestId, int32_t result)
{
    if (!DragDropGlobalController::GetInstance().IsOnOnDropPhase()) {
        return -1;
    }
    return DragDropGlobalController::GetInstance().NotifyDragResult(requestId, result);
}

int32_t DragDropFuncWrapper::NotifyDragEndPendingDone(int32_t requestId)
{
    if (!DragDropGlobalController::GetInstance().IsOnOnDropPhase()) {
        return -1;
    }
    return DragDropGlobalController::GetInstance().NotifyDragEndPendingDone(requestId);
}

void DragDropFuncWrapper::DecideWhetherToStopDragging(
    const DragPointerEvent& pointerEvent, const std::string& extraParams, int32_t currentPointerId, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (!manager->IsDraggingPressed(currentPointerId)) {
        manager->OnDragEnd(pointerEvent, extraParams);
    }
}

void DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(
    std::function<void(WeakPtr<FrameNode>)> applyOnNodeSync, DragPreviewOption& option)
{
    // create one temporary frame node for receiving the value from the modifier
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);

    // execute the modifier
    CHECK_NULL_VOID(applyOnNodeSync);
    applyOnNodeSync(AceType::WeakClaim(AceType::RawPtr(imageNode)));

    // get values from the temporary frame node
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto opacity = imageContext->GetOpacity();
    if (opacity.has_value() && (opacity.value()) <= MAX_OPACITY && (opacity.value()) > MIN_OPACITY) {
        option.options.opacity = opacity.value();
    } else {
        option.options.opacity = DEFAULT_OPACITY;
    }

    auto shadow = imageContext->GetBackShadow();
    if (shadow.has_value()) {
        option.options.shadow = shadow.value();
    }

    auto borderRadius = imageContext->GetBorderRadius();
    if (borderRadius.has_value()) {
        option.options.borderRadius = borderRadius;
    }

    auto bgEffect = imageContext->GetBackgroundEffect();
    if (bgEffect.has_value()) {
        option.options.blurbgEffect.backGroundEffect = bgEffect.value();
    } else {
        auto blurstyletmp = imageContext->GetBackBlurStyle();
        if (blurstyletmp.has_value()) {
            bgEffect = BlurStyleToEffection(blurstyletmp);
            if (bgEffect.has_value()) {
                option.options.blurbgEffect.backGroundEffect = bgEffect.value();
            }
        }
    }
}

void DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(DragPreviewOption& option, bool isMultiSelectionEnabled)
{
    option.options.opacity = DEFAULT_OPACITY;
    if (option.isDefaultShadowEnabled) {
        option.options.shadow = GetDefaultShadow();
    } else {
        option.options.shadow = std::nullopt;
    }
    if (option.isDefaultRadiusEnabled || isMultiSelectionEnabled) {
        option.options.borderRadius = GetDefaultBorderRadius();
    } else {
        option.options.borderRadius = std::nullopt;
    }
}

void DragDropFuncWrapper::UpdateExtraInfo(std::unique_ptr<JsonValue>& arkExtraInfoJson,
    DragPreviewOption& option)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    double opacity = option.options.opacity;
    arkExtraInfoJson->Put("dip_opacity", opacity);
    if (option.options.blurbgEffect.backGroundEffect.radius.IsValid()) {
        option.options.blurbgEffect.ToJsonValue(arkExtraInfoJson);
    }
    PrepareShadowParametersForDragData(arkExtraInfoJson, option);
    PrepareRadiusParametersForDragData(arkExtraInfoJson, option);
}

void DragDropFuncWrapper::PrepareRadiusParametersForDragData(std::unique_ptr<JsonValue>& arkExtraInfoJson,
    DragPreviewOption& option)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    auto borderRadius = option.options.borderRadius;
    if (borderRadius.has_value()) {
        if (borderRadius.value().radiusTopLeft.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius1", borderRadius.value().radiusTopLeft.value().Value());
        }
        if (borderRadius.value().radiusTopRight.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius2", borderRadius.value().radiusTopRight.value().Value());
        }
        if (borderRadius.value().radiusBottomRight.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius3", borderRadius.value().radiusBottomRight.value().Value());
        }
        if (borderRadius.value().radiusBottomLeft.has_value()) {
            arkExtraInfoJson->Put("drag_corner_radius4", borderRadius.value().radiusBottomLeft.value().Value());
        }
    }
}

void DragDropFuncWrapper::PrepareShadowParametersForDragData(std::unique_ptr<JsonValue>& arkExtraInfoJson,
    DragPreviewOption& option)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    auto shadow = option.options.shadow;
    if (!shadow.has_value() || !shadow->IsValid()) {
        arkExtraInfoJson->Put("shadow_enable", false);
        return;
    }
    arkExtraInfoJson->Put("drag_type", "non-text");
    arkExtraInfoJson->Put("shadow_enable", true);
    ParseShadowInfo(shadow.value(), arkExtraInfoJson);
}

void DragDropFuncWrapper::ParseShadowInfo(Shadow& shadow, std::unique_ptr<JsonValue>& arkExtraInfoJson)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    arkExtraInfoJson->Put("shadow_is_filled", shadow.GetIsFilled());
    arkExtraInfoJson->Put("drag_shadow_OffsetX", shadow.GetOffset().GetX());
    arkExtraInfoJson->Put("drag_shadow_OffsetY", shadow.GetOffset().GetY());
    arkExtraInfoJson->Put("shadow_mask", shadow.GetShadowType() == ShadowType::BLUR);
    int32_t argb = static_cast<int32_t>(shadow.GetColor().GetValue());
    arkExtraInfoJson->Put("drag_shadow_argb", argb);
    int32_t strategy = static_cast<int32_t>(shadow.GetShadowColorStrategy());
    arkExtraInfoJson->Put("shadow_color_strategy", strategy);
    arkExtraInfoJson->Put("shadow_corner", shadow.GetBlurRadius());
    arkExtraInfoJson->Put("shadow_elevation", shadow.GetElevation());
    arkExtraInfoJson->Put("shadow_is_hardwareacceleration", shadow.GetHardwareAcceleration());
}

std::optional<Shadow> DragDropFuncWrapper::GetDefaultShadow()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, std::nullopt);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, std::nullopt);
    auto colorMode = pipelineContext->GetColorMode();
    auto shadow = shadowTheme->GetShadow(ShadowStyle::OuterFloatingSM, colorMode);
    shadow.SetIsFilled(true);
    return shadow;
}

std::optional<BorderRadiusProperty> DragDropFuncWrapper::GetDefaultBorderRadius()
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(PREVIEW_BORDER_RADIUS);
    return borderRadius;
}

float DragDropFuncWrapper::RadiusToSigma(float radius)
{
    return GreatNotEqual(radius, 0.0f) ? BLUR_SIGMA_SCALE * radius + SCALE_HALF : 0.0f;
}

std::optional<EffectOption> DragDropFuncWrapper::BlurStyleToEffection(
    const std::optional<BlurStyleOption>& blurStyleOp)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "cannot find theme of blurStyle, create blurStyle failed");
        return std::nullopt;
    }
    CHECK_NULL_RETURN(blurStyleOp, std::nullopt);
    ThemeColorMode colorMode = blurStyleOp->colorMode;
    if (blurStyleOp->colorMode == ThemeColorMode::SYSTEM) {
        colorMode = pipeline->GetColorMode() == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
    }
    auto blurParam = blurStyleTheme->GetBlurParameter(blurStyleOp->blurStyle, colorMode);
    CHECK_NULL_RETURN(blurParam, std::nullopt);
    auto ratio = blurStyleOp->scale;
    auto maskColor = blurParam->maskColor.BlendOpacity(ratio);
    auto radiusPx = blurParam->radius * pipeline->GetDipScale();
    auto radiusBlur = RadiusToSigma(radiusPx) * ratio;
    auto saturation = (blurParam->saturation - 1) * ratio + 1.0;
    auto brightness = (blurParam->brightness - 1) * ratio + 1.0;
    Dimension dimen(radiusBlur);
    EffectOption bgEffection = {dimen, saturation, brightness, maskColor,
        blurStyleOp->adaptiveColor, blurStyleOp->blurOption};
    return std::optional<EffectOption>(bgEffection);
}

[[maybe_unused]] double DragDropFuncWrapper::GetScaleWidth(int32_t containerId)
{
    auto container = Container::GetContainer(containerId);
    CHECK_NULL_RETURN(container, -1.0f);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, -1.0f);
    return DragDropManager::GetMaxWidthBaseOnGridSystem(pipeline);
}

void DragDropFuncWrapper::SetDragStartRequestStatus(DragStartRequestStatus dragStartRequestStatus) noexcept
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->HandleSyncOnDragStart(dragStartRequestStatus);
}

void DragDropFuncWrapper::SetExtraInfo(int32_t containerId, std::string extraInfo)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->SetExtraInfo(extraInfo);
}

std::string DragDropFuncWrapper::GetSummaryString(const std::map<std::string, int64_t>& summary)
{
    std::string summarys;
    for (const auto& [udkey, recordSize] : summary) {
        std::string str = udkey + "-" + std::to_string(recordSize) + ";";
        summarys += str;
    }

    return summarys;
}

std::string DragDropFuncWrapper::GetAnonyString(const std::string &fullString)
{
    if (fullString.empty() || fullString.length() == 0) {
        return "";
    }
    std::string middleStr = "******";
    std::string anonyStr;
    size_t strLen = fullString.length();
    if (strLen <= SHORT_KEY_LENGTH) {
        anonyStr += fullString[0];
        anonyStr.append(middleStr);
        anonyStr += fullString[strLen - 1];
    } else {
        anonyStr.append(fullString, 0, PLAINTEXT_LENGTH).append(middleStr)
            .append(fullString, strLen - PLAINTEXT_LENGTH, PLAINTEXT_LENGTH);
    }
    return anonyStr;
}

// returns a node's offset relative to window plus half of self rect size(w, h)
// and accumulate every ancestor node's graphic properties such as rotate and transform
// ancestor will NOT check boundary of window scene
OffsetF DragDropFuncWrapper::GetPaintRectCenter(const RefPtr<FrameNode>& frameNode, bool checkWindowBoundary)
{
    CHECK_NULL_RETURN(frameNode, OffsetF());
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto paintRect = context->GetPaintRectWithoutTransform();
    auto offset = paintRect.GetOffset();
    PointF pointNode(offset.GetX() + paintRect.Width() / 2.0f, offset.GetY() + paintRect.Height() / 2.0f);
    context->GetPointTransformRotate(pointNode);
    auto parent = frameNode->GetAncestorNodeOfFrame(false);
    while (parent) {
        if (checkWindowBoundary && parent->IsWindowBoundary()) {
            break;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        pointNode.SetX(offset.GetX() + pointNode.GetX());
        pointNode.SetY(offset.GetY() + pointNode.GetY());
        renderContext->GetPointTransformRotate(pointNode);
        parent = parent->GetAncestorNodeOfFrame(false);
    }
    return OffsetF(pointNode.GetX(), pointNode.GetY());
}

// check if expand subwindow
bool DragDropFuncWrapper::IsExpandDisplay(const RefPtr<PipelineBase>& context)
{
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, false);
    if (theme->GetExpandDisplay()) {
        return true;
    }
    auto containerId = pipeline->GetInstanceId();
    containerId = containerId >= MIN_SUBCONTAINER_ID ?
        SubwindowManager::GetInstance()->GetParentContainerId(containerId) : containerId;
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_RETURN(container, false);
    return container->IsFreeMultiWindow();
}

OffsetF DragDropFuncWrapper::GetCurrentWindowOffset(const RefPtr<PipelineBase>& context)
{
    if (!IsExpandDisplay(context)) {
        return OffsetF();
    }
    auto pipeline = AceType::DynamicCast<PipelineContext>(context);
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto window = pipeline->GetWindow();
    CHECK_NULL_RETURN(window, OffsetF());
    auto windowOffset = window->GetCurrentWindowRect().GetOffset();
    return OffsetF(windowOffset.GetX(), windowOffset.GetY());
}

OffsetF DragDropFuncWrapper::GetPaintRectCenterToScreen(const RefPtr<FrameNode>& frameNode)
{
    auto offset = GetPaintRectCenter(frameNode);
    CHECK_NULL_RETURN(frameNode, offset);
    offset += GetCurrentWindowOffset(frameNode->GetContextRefPtr());
    return offset;
}

OffsetF DragDropFuncWrapper::GetFrameNodeOffsetToScreen(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, OffsetF());
    auto offset = frameNode->GetPositionToWindowWithTransform();
    offset += GetCurrentWindowOffset(frameNode->GetContextRefPtr());
    return offset;
}

RectF DragDropFuncWrapper::GetPaintRectToScreen(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, RectF());
    RectF rect = frameNode->GetTransformRectRelativeToWindow();
    rect += GetCurrentWindowOffset(frameNode->GetContextRefPtr());
    return rect;
}

void DragDropFuncWrapper::UpdateNodePositionToScreen(const RefPtr<FrameNode>& frameNode, OffsetF offset)
{
    CHECK_NULL_VOID(frameNode);
    offset -= GetCurrentWindowOffset(frameNode->GetContextRefPtr());
    UpdateNodePositionToWindow(frameNode, offset);
}

void DragDropFuncWrapper::UpdateNodePositionToWindow(const RefPtr<FrameNode>& frameNode, OffsetF offset)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    RefPtr<FrameNode> parentNode = frameNode->GetAncestorNodeOfFrame(true);
    if (parentNode) {
        offset -= parentNode->GetPositionToWindowWithTransform();
    }
    renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(offset.GetX()), Dimension(offset.GetY())));
}

void DragDropFuncWrapper::UpdatePositionFromFrameNode(const RefPtr<FrameNode>& targetNode,
    const RefPtr<FrameNode>& frameNode, float width, float height)
{
    CHECK_NULL_VOID(targetNode);
    CHECK_NULL_VOID(frameNode);
    auto paintRectCenter = GetPaintRectCenterToScreen(frameNode);
    auto offset = paintRectCenter - OffsetF(width / 2.0f, height / 2.0f);
    UpdateNodePositionToScreen(targetNode, offset);
}

OffsetF DragDropFuncWrapper::GetFrameNodeOffsetToWindow(const RefPtr<FrameNode>& targetNode,
    const RefPtr<FrameNode>& frameNode, float width, float height)
{
    CHECK_NULL_RETURN(targetNode, OffsetF());
    CHECK_NULL_RETURN(frameNode, OffsetF());
    auto paintRectCenter = GetPaintRectCenterToScreen(frameNode);
    auto offset = paintRectCenter - OffsetF(width / 2.0f, height / 2.0f);
    offset -= GetCurrentWindowOffset(targetNode->GetContextRefPtr());
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, OffsetF());
    RefPtr<FrameNode> parentNode = targetNode->GetAncestorNodeOfFrame(true);
    if (parentNode) {
        offset -= parentNode->GetPositionToWindowWithTransform();
    }
    return offset;
}

void DragDropFuncWrapper::ConvertPointerEvent(const TouchEvent& touchPoint, DragPointerEvent& event)
{
    event.rawPointerEvent = touchPoint.GetTouchEventPointerEvent();
    event.pointerEventId = touchPoint.touchEventId;
    event.pointerId = touchPoint.id;
    event.windowX = touchPoint.x;
    event.windowY = touchPoint.y;
    event.displayX = touchPoint.screenX;
    event.displayY = touchPoint.screenY;
    event.deviceId = touchPoint.deviceId;
    event.x = event.windowX;
    event.y = event.windowY;
    event.pressedKeyCodes.clear();
    for (const auto& curCode : touchPoint.pressedKeyCodes_) {
        event.pressedKeyCodes.emplace_back(static_cast<KeyCode>(curCode));
    }
    GetPointerEventAction(touchPoint, event);
}

void DragDropFuncWrapper::GetPointerEventAction(const TouchEvent& touchPoint, DragPointerEvent& event)
{
    auto orgAction = touchPoint.type;
    switch (orgAction) {
        case TouchType::CANCEL:
            event.action = PointerAction::CANCEL;
            break;
        case TouchType::DOWN:
            event.action = PointerAction::DOWN;
            break;
        case TouchType::MOVE:
            event.action = PointerAction::MOVE;
            break;
        case TouchType::UP:
            event.action = PointerAction::UP;
            break;
        case TouchType::PULL_MOVE:
            event.action = PointerAction::PULL_MOVE;
            break;
        case TouchType::PULL_UP:
            event.action = PointerAction::PULL_UP;
            break;
        case TouchType::PULL_IN_WINDOW:
            event.action = PointerAction::PULL_IN_WINDOW;
            break;
        case TouchType::PULL_OUT_WINDOW:
            event.action = PointerAction::PULL_OUT_WINDOW;
            break;
        default:
            event.action = PointerAction::UNKNOWN;
            break;
    }
}

RefPtr<FrameNode> DragDropFuncWrapper::GetFrameNodeByKey(const RefPtr<FrameNode>& root, const std::string& key)
{
    std::queue<RefPtr<UINode>> elements;
    elements.push(root);
    RefPtr<UINode> inspectorElement;
    while (!elements.empty()) {
        auto current = elements.front();
        elements.pop();
        if (key == current->GetInspectorId().value_or("")) {
            return AceType::DynamicCast<FrameNode>(current);
        }

        const auto& children = current->GetChildren();
        for (const auto& child : children) {
            elements.push(child);
        }
    }
    return nullptr;
}

OffsetF DragDropFuncWrapper::GetPointRelativeToMainWindow(const Point& point)
{
    OffsetF position (static_cast<float>(point.GetX()), static_cast<float>(point.GetY()));
    auto currentPipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(currentPipeline, position);
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_RETURN(mainPipeline, position);
    if (mainPipeline != currentPipeline) {
        position -= (GetCurrentWindowOffset(mainPipeline) -
                     GetCurrentWindowOffset(currentPipeline));
    }
    return position;
}

bool DragDropFuncWrapper::IsSelectedItemNode(const RefPtr<UINode>& uiNode)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto dragPreview = frameNode->GetDragPreviewOption();
    if (!dragPreview.isMultiSelectionEnabled) {
        return false;
    }
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    if (!isAllowedDrag) {
        return false;
    }
    if (frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG) {
        auto itemPattern = frameNode->GetPattern<GridItemPattern>();
        CHECK_NULL_RETURN(itemPattern, false);
        if (itemPattern->IsSelected()) {
            return true;
        }
    }
    if (frameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
        auto itemPattern = frameNode->GetPattern<ListItemPattern>();
        CHECK_NULL_RETURN(itemPattern, false);
        if (itemPattern->IsSelected()) {
            return true;
        }
    }
    return false;
}

/**
 * Do some nessessary check before returning the gesture recognizer collection result
 * to parent during the hittest process. For example, if there is one drag operation
 * already in our system, it is not allowed to start new interation for drag operation.
 */
bool DragDropFuncWrapper::IsGlobalStatusSuitableForDragging()
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (dragDropManager->IsDragging()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, is dragging status");
        return false;
    }

    if (dragDropManager->IsMSDPDragging()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, is msdp dragging status");
        return false;
    }

    return true;
}

bool DragDropFuncWrapper::IsSelfAndParentDragForbidden(const RefPtr<FrameNode>& frameNode)
{
    auto parent = frameNode;
    while (parent) {
        auto eventHub = parent->GetEventHub<EventHub>();
        parent = parent->GetAncestorNodeOfFrame(true);
        if (!eventHub) {
            continue;
        }
        auto gestureEventHub = eventHub->GetGestureEventHub();
        if (!gestureEventHub) {
            continue;
        }
        if (gestureEventHub->IsDragForbidden()) {
            return true;
        }
    }
    return false;
}

bool DragDropFuncWrapper::IsBelongToMultiItemNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_RETURN(uiNode, false);
    while (!IsSelectedItemNode(uiNode)) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, false);
    }
    return true;
}

bool DragDropFuncWrapper::CheckIsNeedGather(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto dragPreview = frameNode->GetDragPreviewOption();
    if (!dragPreview.isMultiSelectionEnabled) {
        return false;
    }
    return IsSelectedItemNode(frameNode);
}

RefPtr<FrameNode> DragDropFuncWrapper::FindItemParentNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetTag() != V2::GRID_ITEM_ETS_TAG && frameNode->GetTag() != V2::LIST_ITEM_ETS_TAG) {
        return nullptr;
    }
    auto parentType = frameNode->GetTag() == V2::GRID_ITEM_ETS_TAG ? V2::GRID_ETS_TAG : V2::LIST_ETS_TAG;
    auto uiNode = frameNode->GetParent();
    CHECK_NULL_RETURN(uiNode, nullptr);
    while (uiNode->GetTag() != parentType) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, nullptr);
    }
    return AceType::DynamicCast<FrameNode>(uiNode);
}

RefPtr<PixelMap> DragDropFuncWrapper::GetGatherNodePreviewPixelMap(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    if (dragPreviewInfo.inspectorId != "") {
        auto previewPixelMap = GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
        return previewPixelMap;
    }
    if (dragPreviewInfo.pixelMap != nullptr) {
        return dragPreviewInfo.pixelMap;
    }
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto pixelMap = context->GetThumbnailPixelMap(true);
    return pixelMap;
}

void DragDropFuncWrapper::TrySetDraggableStateAsync(
    const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (frameNode->GetTag() == V2::TEXT_ETS_TAG && !gestureHub->GetIsTextDraggable()) {
        return;
    }
    int64_t downTime = static_cast<int64_t>(touchRestrict.touchEvent.time.time_since_epoch().count());
    if (DragDropGlobalController::GetInstance().IsAppGlobalDragEnabled()) {
        InteractionInterface::GetInstance()->SetDraggableStateAsync(true, downTime / CONVERT_TIME_BASE);
    }
}

/**
 * check the current node's status to decide if it can initiate one drag operation
 */
bool DragDropFuncWrapper::IsCurrentNodeStatusSuitableForDragging(
    const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);

    if (gestureHub->IsDragForbidden() || (!frameNode->IsDraggable() && frameNode->IsCustomerSet()) ||
        touchRestrict.inputEventType == InputEventType::AXIS) {
        TAG_LOGI(AceLogTag::ACE_DRAG,
            "No need to collect drag gestures result, drag forbidden set is %{public}d,"
            "frameNode draggable is %{public}d, custom set is %{public}d",
            gestureHub->IsDragForbidden(), frameNode->IsDraggable(), frameNode->IsCustomerSet());
        return false;
    }

    if (gestureHub->GetTextDraggable()) {
        auto pattern = frameNode->GetPattern<TextBase>();
        if (pattern && !pattern->IsSelected()) {
            TrySetDraggableStateAsync(frameNode, touchRestrict);
            TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, text is not selected.");
            return false;
        }
    }

    if (IsSelfAndParentDragForbidden(frameNode)) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to collect drag gestures result, parent is drag forbidden.");
        return false;
    }

    return true;
}
void DragDropFuncWrapper::RecordMenuWrapperNodeForDrag(int32_t targetId)
{
    auto subWindow = SubwindowManager::GetInstance()->GetCurrentWindow();
    CHECK_NULL_VOID(subWindow);
    auto overlayManager = subWindow->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuWrapperNode = overlayManager->GetMenuNode(targetId);
    if (!menuWrapperNode) {
        auto rootNode = overlayManager->GetRootNode().Upgrade();
        CHECK_NULL_VOID(rootNode);
        for (const auto& child : rootNode->GetChildren()) {
            auto node = AceType::DynamicCast<FrameNode>(child);
            if (node && node->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
                menuWrapperNode = node;
                break;
            }
        }
    }
    CHECK_NULL_VOID(menuWrapperNode);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetMenuWrapperNode(menuWrapperNode);

    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto dragMainDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragMainDropManager);
    dragMainDropManager->SetMenuWrapperNode(menuWrapperNode);
}

RefPtr<FrameNode> DragDropFuncWrapper::GetFrameNodeByInspectorId(const std::string& inspectorId)
{
    if (inspectorId.empty()) {
        return nullptr;
    }

    auto frameNode = Inspector::GetFrameNodeByKey(inspectorId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto visibility = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    if (visibility == VisibleType::INVISIBLE || visibility == VisibleType::GONE) {
        return nullptr;
    }

    return frameNode;
}

void DragDropFuncWrapper::ApplyNewestOptionExecutedFromModifierToNode(
    const RefPtr<FrameNode>& optionHolderNode, const RefPtr<FrameNode>& targetNode)
{
    auto optionsFromModifier = targetNode->GetDragPreviewOption().options;
    ACE_UPDATE_NODE_RENDER_CONTEXT(Opacity, optionsFromModifier.opacity, targetNode);
    if (optionsFromModifier.blurbgEffect.backGroundEffect.radius.IsValid()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundEffect, optionsFromModifier.blurbgEffect.backGroundEffect, targetNode);
    }
    if (optionsFromModifier.shadow.has_value()) {
        // if shadow is unfilled, set shadow after animation
        if (optionsFromModifier.shadow->GetIsFilled()) {
            ACE_UPDATE_NODE_RENDER_CONTEXT(BackShadow, optionsFromModifier.shadow.value(), targetNode);
        }
    }

    const auto& target = targetNode->GetRenderContext();
    if (optionsFromModifier.borderRadius.has_value()) {
        target->UpdateBorderRadius(optionsFromModifier.borderRadius.value());
        target->UpdateClipEdge(true);
    }
}

void DragDropFuncWrapper::ResetNode(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    bool defaultAnimationBeforeLifting = frameNode->GetDragPreviewOption().defaultAnimationBeforeLifting;
    if (!defaultAnimationBeforeLifting) {
        return;
    }
    auto frameContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(frameContext);
    frameContext->UpdateTransformScale({ 1.0f, 1.0f });
    auto layoutProperty = frameNode->GetLayoutProperty();
    if (layoutProperty) {
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
}

BorderRadiusProperty DragDropFuncWrapper::GetDragFrameNodeBorderRadius(const RefPtr<FrameNode>& frameNode)
{
    Dimension defaultDimension(0);
    BorderRadiusProperty borderRadius = { defaultDimension, defaultDimension, defaultDimension, defaultDimension };
    auto dragPreviewInfo = frameNode->GetDragPreview();
    if (dragPreviewInfo.pixelMap != nullptr) {
        return borderRadius;
    }
    RefPtr<FrameNode> targetNode = frameNode;
    if (!dragPreviewInfo.inspectorId.empty()) {
        targetNode = DragDropFuncWrapper::GetFrameNodeByInspectorId(dragPreviewInfo.inspectorId);
        CHECK_NULL_RETURN(targetNode, borderRadius);
    } else if (dragPreviewInfo.customNode != nullptr) {
        targetNode = AceType::DynamicCast<FrameNode>(dragPreviewInfo.customNode);
        CHECK_NULL_RETURN(targetNode, borderRadius);
    }
    auto targetNodeContext = targetNode->GetRenderContext();
    CHECK_NULL_RETURN(targetNodeContext, borderRadius);
    if (targetNodeContext->GetBorderRadius().has_value()) {
        borderRadius.UpdateWithCheck(targetNodeContext->GetBorderRadius().value());
    }
    return borderRadius;
}

/* Retrieves a preview PixelMap for a given drag event action.
 * This function attempts to obtain a screenshot of a frameNode associated with an inspector ID.
 * If the frameNode with the given ID does not exist or hasn't been rendered,
 * it falls back to taking a screenshot of the provided frame node.
 *
 * @param inspectorId A string representing the unique identifier for the frameNode's ID.
 * @param selfFrameNode A RefPtr to the frame node associated with the drag event.
 * @return A RefPtr to a PixelMap containing the preview image, or nullptr if not found.
 */
RefPtr<PixelMap> DragDropFuncWrapper::GetPreviewPixelMap(
    const std::string& inspectorId, const RefPtr<FrameNode>& selfFrameNode)
{
    // Attempt to retrieve the PixelMap using the inspector ID.
    auto previewPixelMap = GetPreviewPixelMapByInspectorId(inspectorId, selfFrameNode);
    // If a preview PixelMap was found, return it.
    if (previewPixelMap != nullptr) {
        return previewPixelMap;
    }
    // If not found by inspector ID, attempt to get a screenshot of the frame node.
    return GetScreenShotPixelMap(selfFrameNode);
}

/* Retrieves a preview PixelMap based on an inspector ID.
 * This function attempts to find a frame node associated with the given inspector ID and then takes a screenshot of it.
 *
 * @param inspectorId The unique identifier for a frameNode.
 * @return A RefPtr to a PixelMap containing the preview image, or nullptr if not found or the ID is empty.
 */
RefPtr<PixelMap> DragDropFuncWrapper::GetPreviewPixelMapByInspectorId(
    const std::string& inspectorId, const RefPtr<FrameNode>& frameNode)
{
    // Check for an empty inspector ID and return nullptr if it is empty.
    if (inspectorId == "") {
        return nullptr;
    }

    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeLine = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeLine, nullptr);
    auto rootNode = pipeLine->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    // Retrieve the frame node using the inspector's ID.
    auto dragPreviewFrameNode = DragDropFuncWrapper::GetFrameNodeByKey(rootNode, inspectorId);
    CHECK_NULL_RETURN(dragPreviewFrameNode, nullptr);

    auto layoutProperty = dragPreviewFrameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto visibility = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    if (visibility == VisibleType::INVISIBLE || visibility == VisibleType::GONE) {
        return nullptr;
    }

    // Take a screenshot of the frame node and return it as a PixelMap.
    return GetScreenShotPixelMap(dragPreviewFrameNode);
}

/* Captures a screenshot of the specified frame node and encapsulates it in a PixelMap.
 *
 * @param frameNode A RefPtr reference to the frame node from which to capture the screenshot.
 * @return A RefPtr to a PixelMap containing the screenshot.
 */
RefPtr<PixelMap> DragDropFuncWrapper::GetScreenShotPixelMap(const RefPtr<FrameNode>& frameNode)
{
    // Ensure the frame node is not nulls before proceeding.
    CHECK_NULL_RETURN(frameNode, nullptr);

    // Obtain the rendering context from the frame node.
    auto context = frameNode->GetRenderContext();

    // If the rendering context is not available, return nullptr.
    CHECK_NULL_RETURN(context, nullptr);

    // Capture and return the thumbnail PixelMap from the rendering context.
    return context->GetThumbnailPixelMap(true);
}

bool DragDropFuncWrapper::CheckIfNeedGetThumbnailPixelMap(const RefPtr<FrameNode>& frameNode, int32_t fingerId)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, false);
    RefPtr<LongPressRecognizer> recognizer;
    auto gestureReferee = eventManager->GetGestureRefereeNG(recognizer);
    CHECK_NULL_RETURN(gestureReferee, false);
    if (gestureReferee->IsAnySucceedRecognizerExist(fingerId)) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "No need to get thumbnail pixelmap with success recognizer.");
        return true;
    }
    return false;
}

RefPtr<PixelMap> DragDropFuncWrapper::CreateTiledPixelMap(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_RETURN(manager, nullptr);
    auto fatherNode = DragDropFuncWrapper::FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(fatherNode, nullptr);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, nullptr);
    auto children = scrollPattern->GetVisibleSelectedItems();
    auto pixelMapinfo = GetTiledPixelMapInfo(children);
    RefPtr<PixelMap> tiledPixelMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    CHECK_NULL_RETURN(pixelMapinfo, nullptr);
    InitializationOptions opts;
    opts.size.SetWidth(pixelMapinfo->pixelMapRect.GetSize().Width());
    opts.size.SetHeight(pixelMapinfo->pixelMapRect.GetSize().Height());
    opts.srcPixelFormat = pixelMapinfo->srcPixelFormat;
    opts.pixelFormat = pixelMapinfo->pixelFormat;
    opts.editable = true;
    opts.alphaType = pixelMapinfo->alphaType;
    tiledPixelMap = PixelMap::Create(opts);
#endif
    DrawTiledPixelMap(tiledPixelMap, children, pixelMapinfo->pixelMapRect);
    CHECK_NULL_RETURN(tiledPixelMap, nullptr);
    return tiledPixelMap;
}

std::shared_ptr<PixelMapInfo> DragDropFuncWrapper::GetTiledPixelMapInfo(const std::vector<RefPtr<FrameNode>>& children)
{
    CHECK_NULL_RETURN(children.size(), nullptr);
    auto minX = std::numeric_limits<float>::max();
    auto minY = std::numeric_limits<float>::max();
    auto maxX = std::numeric_limits<float>::lowest();
    auto maxY = std::numeric_limits<float>::lowest();

    for (auto& node : children) {
        auto context = node->GetRenderContext();
        CHECK_NULL_RETURN(context, nullptr);
        auto pixelMap = context->GetThumbnailPixelMap();
        auto gestureHub = node->GetOrCreateGestureEventHub();
        gestureHub->SetDragPreviewPixelMap(pixelMap);
        CHECK_NULL_RETURN(pixelMap, nullptr);
        auto offset = DragDropFuncWrapper::GetPaintRectCenter(node, true);
        minX = std::min(minX, offset.GetX());
        minY = std::min(minY, offset.GetY());
        maxX = std::max(maxX, offset.GetX() + pixelMap->GetWidth());
        maxY = std::max(maxY, offset.GetY() + pixelMap->GetHeight());
    }
    auto gestureHub = children.front()->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    auto dragPreviewPixelMap = gestureHub->GetDragPreviewPixelMap();
    CHECK_NULL_RETURN(dragPreviewPixelMap, nullptr);
    std::shared_ptr<PixelMapInfo> pixelMapInfo = std::make_shared<PixelMapInfo>();
    pixelMapInfo->srcPixelFormat = dragPreviewPixelMap->GetPixelFormat();
    pixelMapInfo->pixelFormat = dragPreviewPixelMap->GetPixelFormat();
    pixelMapInfo->alphaType = dragPreviewPixelMap->GetAlphaType();
    pixelMapInfo->pixelMapRect.SetLeft(minX);
    pixelMapInfo->pixelMapRect.SetTop(minY);
    pixelMapInfo->pixelMapRect.SetHeight(maxY - minY);
    pixelMapInfo->pixelMapRect.SetWidth(maxX - minX);
    return pixelMapInfo;
}

void DragDropFuncWrapper::DrawTiledPixelMap(
    const RefPtr<PixelMap>& tiledPixelMap, const std::vector<RefPtr<FrameNode>>& children, const Rect& pixelMapRect)
{
    CHECK_NULL_VOID(tiledPixelMap);
    for (auto& node : children) {
        auto gestureHub = node->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto pixelMap = gestureHub->GetDragPreviewPixelMap();
        CHECK_NULL_VOID(pixelMap);
        auto offsetX = DragDropFuncWrapper::GetPaintRectCenter(node, true).GetX();
        auto offsetY = DragDropFuncWrapper::GetPaintRectCenter(node, true).GetY();
        auto result =
            tiledPixelMap->WritePixels({ pixelMap->GetPixels(), pixelMap->GetByteCount(), 0, pixelMap->GetRowStride(),
                { offsetX - pixelMapRect.GetOffset().GetX(), offsetY - pixelMapRect.GetOffset().GetY(),
                    pixelMap->GetWidth(), pixelMap->GetHeight() },
                pixelMap->GetPixelFormat() });
        if (result != 0) {
            TAG_LOGW(AceLogTag::ACE_DRAG, "Tiled pixelmap Write is failed, the result is %{public}d", result);
            return;
        }
    }
    return;
}

bool DragDropFuncWrapper::IsNeedCreateTiledPixelMap(
    const RefPtr<FrameNode>& frameNode, const RefPtr<DragEventActuator> dragEventActuator, SourceType type)
{
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(dragEventActuator, false);
    auto fatherNode = DragDropFuncWrapper::FindItemParentNode(frameNode);
    CHECK_NULL_RETURN(fatherNode, false);
    auto scrollPattern = fatherNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(scrollPattern, false);
    if (frameNode->GetDragPreviewOption().isMultiTiled && scrollPattern->GetVisibleSelectedItems().size() > 1 &&
        DragDropFuncWrapper::IsSelectedItemNode(frameNode) && !dragEventActuator->GetRestartDrag() &&
        type == SourceType::MOUSE) {
        return true;
    }
    return false;
}

void DragDropFuncWrapper::GetThumbnailPixelMapForCustomNodeSync(
    const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback)
{
#if defined(PIXEL_MAP_SUPPORTED)
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    SnapshotParam param;
    auto pixelMap = ComponentSnapshot::CreateSync(dragPreviewInfo.customNode, param);
    CHECK_NULL_VOID(pixelMap);
    auto previewPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    gestureHub->SetPixelMap(previewPixelMap);
    gestureHub->SetDragPreviewPixelMap(previewPixelMap);
    pixelMapCallback(previewPixelMap, false);
#endif
}

void DragDropFuncWrapper::GetThumbnailPixelMapAsync(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    auto callback = [id = Container::CurrentId(), weakGestureHub = AceType::WeakClaim(AceType::RawPtr(gestureHub))](
                        const RefPtr<PixelMap>& pixelMap) {
        ContainerScope scope(id);
        if (pixelMap != nullptr) {
            auto taskScheduler = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskScheduler);
            auto gestureHub = weakGestureHub.Upgrade();
            CHECK_NULL_VOID(gestureHub);
            taskScheduler->PostTask(
                [gestureHub, pixelMap]() {
                    CHECK_NULL_VOID(gestureHub);
                    gestureHub->SetPixelMap(pixelMap);
                    TAG_LOGI(AceLogTag::ACE_DRAG, "Set thumbnail pixelMap async success.");
                },
                TaskExecutor::TaskType::UI, "ArkUIDragSetPixelMap");
        }
    };
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (!context->CreateThumbnailPixelMapAsyncTask(true, std::move(callback))) {
        DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::SNAPSHOT_FAIL);
        TAG_LOGW(AceLogTag::ACE_DRAG, "Create thumbnail pixelMap async task failed!");
    }
}

void DragDropFuncWrapper::GetThumbnailPixelMapForCustomNode(
    const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback)
{
#if defined(PIXEL_MAP_SUPPORTED)
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [id = Container::CurrentId(), pipeline, gestureHub, pixelMapCallback](
                        std::shared_ptr<Media::PixelMap> pixelMap, int32_t arg, std::function<void()> finishCallback) {
        ContainerScope scope(id);
        CHECK_NULL_VOID(pipeline);
        auto taskScheduler = pipeline->GetTaskExecutor();
        CHECK_NULL_VOID(taskScheduler);
        taskScheduler->PostTask(
            [finishCallback]() {
                if (finishCallback) {
                    finishCallback();
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIDragRemoveCustomNode");
        if (pixelMap != nullptr) {
            auto customPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
            taskScheduler->PostTask(
                [gestureHub, customPixelMap, pixelMapCallback]() {
                    CHECK_NULL_VOID(gestureHub);
                    gestureHub->SetPixelMap(customPixelMap);
                    gestureHub->SetDragPreviewPixelMap(customPixelMap);
                    pixelMapCallback(customPixelMap, true);
                },
                TaskExecutor::TaskType::UI, "ArkUIDragSetCustomPixelMap");
        } else {
            TAG_LOGI(AceLogTag::ACE_DRAG, "PixelMap is null.");
            DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::SNAPSHOT_FAIL);
        }
    };
    SnapshotParam param;
    param.delay = CREATE_PIXELMAP_TIME;
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
    OHOS::Ace::NG::ComponentSnapshot::Create(dragPreviewInfo.customNode, std::move(callback), true, param);
    gestureHub->PrintBuilderNode(dragPreviewInfo.customNode);
#endif
}

void DragDropFuncWrapper::GetThumbnailPixelMap(
    const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback, bool isSync)
{
    CHECK_NULL_VOID(gestureHub);
    auto frameNode = gestureHub->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewInfo = frameNode->GetDragPreview();
    if (dragPreviewInfo.inspectorId != "") {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through inspectorId.");
        auto previewPixelMap = GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
        gestureHub->SetPixelMap(previewPixelMap);
        gestureHub->SetDragPreviewPixelMap(previewPixelMap);
        pixelMapCallback(previewPixelMap, false);
    } else if (dragPreviewInfo.pixelMap != nullptr) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through pixelMap.");
        gestureHub->SetPixelMap(dragPreviewInfo.pixelMap);
        gestureHub->SetDragPreviewPixelMap(dragPreviewInfo.pixelMap);
        pixelMapCallback(dragPreviewInfo.pixelMap, false);
    } else if (dragPreviewInfo.customNode || (dragPreviewInfo.delayCreating && dragPreviewInfo.buildFunc)) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Get thumbnail through customNode.");
        if (!dragPreviewInfo.customNode && dragPreviewInfo.delayCreating && dragPreviewInfo.buildFunc) {
            dragPreviewInfo.customNode = dragPreviewInfo.buildFunc();
        }
        frameNode->SetDragPreview(dragPreviewInfo);
        if (isSync) {
            GetThumbnailPixelMapForCustomNodeSync(gestureHub, pixelMapCallback);
        } else {
            GetThumbnailPixelMapForCustomNode(gestureHub, pixelMapCallback);
        }
    } else {
        GetThumbnailPixelMapAsync(gestureHub);
    }
}

float DragDropFuncWrapper::GetPixelMapScale(const RefPtr<FrameNode>& frameNode)
{
    float scale = 1.0f;
    CHECK_NULL_RETURN(frameNode, scale);
    auto pixelMap = frameNode->GetDragPixelMap();
    CHECK_NULL_RETURN(pixelMap, scale);
    auto width = pixelMap->GetWidth();
    auto height = pixelMap->GetHeight();
    auto gestureEvent = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureEvent, scale);
    if (frameNode->GetDragPreviewOption().isScaleEnabled && width > 0 && height > 0) {
        auto scaleData = DragDropManager::GetScaleInfo(width, height, gestureEvent->GetTextDraggable());
        CHECK_NULL_RETURN(scaleData, scale);
        scale = scaleData->scale;
    }
    return scale;
}

bool DragDropFuncWrapper::IsTextCategoryComponent(const std::string& frameTag)
{
    return frameTag == V2::TEXTAREA_ETS_TAG || frameTag == V2::TEXT_ETS_TAG ||
           frameTag == V2::TEXTINPUT_ETS_TAG || frameTag == V2::SEARCH_Field_ETS_TAG ||
           frameTag == V2::RICH_EDITOR_ETS_TAG;
}
} // namespace OHOS::Ace::NG

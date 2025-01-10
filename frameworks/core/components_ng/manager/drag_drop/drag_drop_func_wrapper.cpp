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
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"

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
        if (pixelMap.GetRawPtr()) {
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
        TaskExecutor::TaskType::UI, "ArkUIDragStop", PriorityType::VIP);
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

void DragDropFuncWrapper::HandleOnDragEvent(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction)
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
    if (opacity.has_value() && (opacity.value()) <= MAX_OPACITY && (opacity.value()) >= MIN_OPACITY) {
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
            bgEffect = BrulStyleToEffection(blurstyletmp);
            if (bgEffect.has_value()) {
                option.options.blurbgEffect.backGroundEffect = bgEffect.value();
            }
        }
    }
}

void DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(DragPreviewOption& option)
{
    option.options.opacity = DEFAULT_OPACITY;
    if (option.isDefaultShadowEnabled) {
        option.options.shadow = GetDefaultShadow();
    } else {
        option.options.shadow = std::nullopt;
    }
    if (option.isDefaultRadiusEnabled) {
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
    auto colorMode = SystemProperties::GetColorMode();
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

std::optional<EffectOption> DragDropFuncWrapper::BrulStyleToEffection(
    const std::optional<BlurStyleOption>& blurStyleOp)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto blurStyleTheme = pipeline->GetTheme<BlurStyleTheme>();
    if (!blurStyleTheme) {
        LOGW("cannot find theme of blurStyle, create blurStyle failed");
        return std::nullopt;
    }
    CHECK_NULL_RETURN(blurStyleOp, std::nullopt);
    ThemeColorMode colorMode = blurStyleOp->colorMode;
    if (blurStyleOp->colorMode == ThemeColorMode::SYSTEM) {
        colorMode = SystemProperties::GetColorMode() == ColorMode::DARK ? ThemeColorMode::DARK : ThemeColorMode::LIGHT;
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
    event.pressedKeyCodes_.clear();
    for (const auto& curCode : touchPoint.pressedKeyCodes_) {
        event.pressedKeyCodes_.emplace_back(static_cast<KeyCode>(curCode));
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
        auto previewPixelMap = DragEventActuator::GetPreviewPixelMap(dragPreviewInfo.inspectorId, frameNode);
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

} // namespace OHOS::Ace

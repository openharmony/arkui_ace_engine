/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "drag_controller_ani_modifier.h"

#include "interaction_manager.h"
#include "adapter/ohos/capability/interaction/start_drag_listener_impl.h"
#include "adapter/ohos/capability/udmf/udmf_impl.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/manager/drag_drop/drag_drop_controller_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "bridge/common/utils/utils.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/base/subwindow/subwindow.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
using DragAction = OHOS::Ace::Ani::DragAction;
namespace {
constexpr int32_t SOURCE_TYPE_MOUSE = 1;
constexpr int32_t MOUSE_POINTER_ID = 1001;
constexpr int32_t SOURCE_TOOL_PEN = 1;
constexpr int32_t SOURCE_TYPE_TOUCH = 2;
constexpr int32_t PEN_POINTER_ID = 102;
constexpr int32_t CREATE_PIXELMAP_DELAY_TIME = 80;

using DragNotifyMsg = Msdp::DeviceStatus::DragNotifyMsg;
using OnDragCallback = std::function<void(const DragNotifyMsg&)>;
using PreviewType = Msdp::DeviceStatus::PreviewType;
using PreviewStyle = Msdp::DeviceStatus::PreviewStyle;
using PreviewAnimation = Msdp::DeviceStatus::PreviewAnimation;

enum class DragState { PENDING, SENDING, REJECT, SUCCESS };
enum class DragStatus { STARTED, ENDED };
enum class ParameterType { DRAG_CUSTOM_BUILDER, DRAG_PIXEL, DRAG_PIXEL_ARRAY, DRAG_MIX_ARRAY, ERROR };

// the context of drag controller
struct DragControllerAsyncCtx {
    ani_env* env = nullptr;
    std::shared_ptr<Media::PixelMap> pixelMap = nullptr;
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    bool isArray = false;
    bool isSwitchedToSubWindow = false;
    ani_fn_object asyncCallback = nullptr;
    ani_resolver deferred = nullptr;
    ArkUINodeHandle customBuilderNode = nullptr;
    std::vector<ArkUINodeHandle> customBuilderNodeList;
    RefPtr<OHOS::Ace::UnifiedData> unifiedData = nullptr;
    std::string extraParams;
    int32_t instanceId = -1;
    int32_t errCode = -1;
    int32_t badgeNumber = 1;
    std::mutex mutex;
    bool hasHandle = false;
    DragPointerEvent dragPointerEvent;
    float windowScale = 1.0f;
    float dipScale = 0.0;
    int parseBuilderCount = 0;
    std::mutex dragStateMutex;
    DragState dragState = DragState::PENDING;
    std::optional<DimensionOffset> touchPoint;
    std::shared_ptr<DragAction> dragAction = nullptr;
    NG::DragPreviewOption dragPreviewOption;
    std::function<void(std::shared_ptr<ArkUIDragControllerAsync>, const ArkUIDragNotifyMessage&,
        const ArkUIDragStatus)> callBackJsFunction;
};
} // namespace
void OnMultipleComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx);
void CreatePixelMapArrayByCustom(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle customBuilder, int arrayLength);
ParameterType GetParameterType(std::shared_ptr<DragControllerAsyncCtx> asyncCtx);

static bool CheckDragging(const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext || !pipelineContext->IsDragging()) {
        return false;
    }
    return true;
}

ParameterType GetParameterType(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, ParameterType::ERROR);
    if (asyncCtx->pixelMap != nullptr) {
        return ParameterType::DRAG_PIXEL;
    }
    if (asyncCtx->customBuilderNode != nullptr) {
        return ParameterType::DRAG_CUSTOM_BUILDER;
    }
    if (!asyncCtx->pixelMapList.empty() && asyncCtx->customBuilderNodeList.empty()) {
        return ParameterType::DRAG_PIXEL_ARRAY;
    }
    if (!asyncCtx->customBuilderNodeList.empty() || !asyncCtx->pixelMapList.empty()) {
        return ParameterType::DRAG_MIX_ARRAY;
    }
    return ParameterType::ERROR;
}

double ConvertToPx(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const Dimension& dimension, double size)
{
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == DimensionUnit::PERCENT) {
        return value * size;
    }
    if (unit == DimensionUnit::NONE || unit == DimensionUnit::PX) {
        return value;
    }

    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, 0.0);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    if (unit == DimensionUnit::VP) {
        return value * pipeline->GetDipScale();
    }
    if (unit == DimensionUnit::FP) {
        return value * pipeline->GetDipScale() * pipeline->GetFontScale();
    }
    if (unit == DimensionUnit::LPX) {
        return value * pipeline->GetLogicScale();
    }
    return 0.0;
}

void SetDragResult(
    const ArkUIDragNotifyMessage& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragRet result = DragRet::DRAG_FAIL;
    switch (notifyMessage.result) {
        case ArkUIDragResult::DRAG_SUCCESS:
            result = DragRet::DRAG_SUCCESS;
            break;
        case ArkUIDragResult::DRAG_FAIL:
            result = DragRet::DRAG_FAIL;
            break;
        case ArkUIDragResult::DRAG_CANCEL:
            result = DragRet::DRAG_CANCEL;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetResult(result);
}

void SetDragBehavior(
    const ArkUIDragNotifyMessage& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent)
{
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    switch (notifyMessage.dragBehavior) {
        case ArkUIDragBehavior::COPY:
            dragBehavior = DragBehavior::COPY;
            break;
        case ArkUIDragBehavior::MOVE:
            dragBehavior = DragBehavior::MOVE;
            break;
        default:
            break;
    }
    CHECK_NULL_VOID(dragEvent);
    dragEvent->SetDragBehavior(dragBehavior);
}

void ConvertDragNotifyMsg(ArkUIDragNotifyMessage& msg, const DragNotifyMsg& dragNotifyMsg)
{
    switch (dragNotifyMsg.result) {
        case Msdp::DeviceStatus::DragResult::DRAG_SUCCESS:
            msg.result = ArkUIDragResult::DRAG_SUCCESS;
            break;
        case Msdp::DeviceStatus::DragResult::DRAG_FAIL:
            msg.result = ArkUIDragResult::DRAG_FAIL;
            break;
        case Msdp::DeviceStatus::DragResult::DRAG_CANCEL:
            msg.result = ArkUIDragResult::DRAG_CANCEL;
            break;
        default:
            break;
    }
    switch (dragNotifyMsg.dragBehavior) {
        case Msdp::DeviceStatus::DragBehavior::COPY:
            msg.dragBehavior = ArkUIDragBehavior::COPY;
            break;
        case Msdp::DeviceStatus::DragBehavior::MOVE:
            msg.dragBehavior = ArkUIDragBehavior::MOVE;
            break;
        default:
            break;
    }
}

void ConvertPreviewStyle(PreviewStyle& style, const ArkUIDragPreviewAsync& async)
{
    for (const auto& type : async.previewStyle.types) {
        style.types.push_back(static_cast<PreviewType>(type));
    }
    style.foregroundColor = async.previewStyle.foregroundColor;
    style.opacity = async.previewStyle.opacity;
    style.radius = async.previewStyle.radius;
    style.scale = async.previewStyle.scale;
}

void ConvertDragPreviewAnimation(PreviewAnimation& previewAnimation, const ArkUIDragPreviewAsync& async)
{
    previewAnimation.curve = async.previewAnimation.curve;
    previewAnimation.curveName = async.previewAnimation.curveName;
    previewAnimation.duration = async.previewAnimation.duration;
}

void prepareDataForCallback(std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    std::shared_ptr<ArkUIDragControllerAsync> arkUIAsync, const DragNotifyMsg& dragNotifyMsg,
    ArkUIDragNotifyMessage& notifyMsg)
{
    arkUIAsync->env = asyncCtx->env;
    arkUIAsync->extraParams = asyncCtx->extraParams;
    arkUIAsync->isArray = asyncCtx->isArray;
    arkUIAsync->dragAction = asyncCtx->dragAction;
    arkUIAsync->deferred = asyncCtx->deferred;
    arkUIAsync->asyncCallback = asyncCtx->asyncCallback;
    arkUIAsync->hasHandle = asyncCtx->hasHandle;
    ConvertDragNotifyMsg(notifyMsg, dragNotifyMsg);
}

void HandleSuccess(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const DragNotifyMsg& dragNotifyMsg, const DragStatus dragStatus)
{
    LOGI("AceDrag, drag notify message result is %{public}d.", dragNotifyMsg.result);
    CHECK_NULL_VOID(asyncCtx);
    bool hasHandle = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->mutex);
        hasHandle = asyncCtx->hasHandle;
        asyncCtx->hasHandle = true;
    }
    if (hasHandle) {
        return;
    }
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    if (dragStatus == DragStatus::ENDED) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ResetDragging();
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto arkUIAsync = std::make_shared<ArkUIDragControllerAsync>();
    ArkUIDragNotifyMessage arkUINotifyMsg;
    prepareDataForCallback(asyncCtx, arkUIAsync, dragNotifyMsg, arkUINotifyMsg);
    taskExecutor->PostSyncTask(
        [asyncCtx, arkUIAsync, arkUINotifyMsg, dragStatus]() {
            CHECK_NULL_VOID(asyncCtx);
            asyncCtx->callBackJsFunction(arkUIAsync, arkUINotifyMsg, static_cast<ArkUIDragStatus>(dragStatus));
            asyncCtx->deferred = nullptr;
            asyncCtx->hasHandle = false;
        },
        TaskExecutor::TaskType::JS, "ArkUIDragHandleSuccess");
}

void LogDragInfoInner(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const Msdp::DeviceStatus::DragData& dragData)
{
    auto pixelMap = dragData.shadowInfos[0].pixelMap;
    std::string summarys = DragDropFuncWrapper::GetSummaryString(dragData.summarys);
    LOGI("AceDrag, dragData: pixelMap width %{public}d height %{public}d, udkey %{public}s, recordSize %{public}d, "
        "extraParams length %{public}d, pointerId %{public}d, toolType %{public}d, summary %{public}s, "
        "eventId %{public}d",
        pixelMap->GetWidth(), pixelMap->GetHeight(),
        DragDropFuncWrapper::GetAnonyString(dragData.udKey).c_str(), dragData.dragNum,
        static_cast<int32_t>(asyncCtx->extraParams.length()), asyncCtx->dragPointerEvent.pointerId,
        static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool), summarys.c_str(),
        asyncCtx->dragPointerEvent.pointerEventId);
}

std::shared_ptr<Media::PixelMap> CopyMediaPixelMap(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    OHOS::Media::InitializationOptions opts;
    auto mediaPixelMap = pixelMap->GetPixelMapSharedPtr();
    std::unique_ptr<Media::PixelMap> uniquePixelMap = Media::PixelMap::Create(*mediaPixelMap, opts);
    CHECK_NULL_RETURN(uniquePixelMap, nullptr);
    Media::PixelMap* pixelMapRelease = uniquePixelMap.release();
    CHECK_NULL_RETURN(pixelMapRelease, nullptr);
    std::shared_ptr<Media::PixelMap> newPixelMap(pixelMapRelease);
    CHECK_NULL_RETURN(newPixelMap, nullptr);
    return newPixelMap;
}

bool GetShadowInfo(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, Msdp::DeviceStatus::ShadowInfo& shadowInfo,
    RefPtr<PixelMap> refPixelMap, float scale)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto pixelMapDuplicated = CopyMediaPixelMap(refPixelMap);
    if (!pixelMapDuplicated) {
        LOGE("AceDrag, duplicate PixelMap failed!");
        pixelMapDuplicated = asyncCtx->pixelMap;
    }
    CHECK_NULL_RETURN(pixelMapDuplicated, false);
    pixelMapDuplicated->scale(scale, scale, Media::AntiAliasingOption::HIGH);
    int32_t width = pixelMapDuplicated->GetWidth();
    int32_t height = pixelMapDuplicated->GetHeight();
    CHECK_NULL_RETURN(pixelMapDuplicated, false);
    double x = ConvertToPx(asyncCtx, asyncCtx->touchPoint->GetX(), width);
    double y = ConvertToPx(asyncCtx, asyncCtx->touchPoint->GetY(), height);
    if (!asyncCtx->touchPoint.has_value()) {
        x = -width * PIXELMAP_WIDTH_RATE;
        y = -height * PIXELMAP_HEIGHT_RATE;
    } else if (x < 0 || y < 0 || x > static_cast<double>(width) || y > static_cast<double>(height)) {
        return false;
    }
    shadowInfo = { pixelMapDuplicated, -x, -y };
    return true;
}
bool CreatePreviewNodeAndScale(std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    NG::PreparedInfoForDrag& data, NG::PreparedAsyncCtxForAnimate& asyncCtxData,
    Msdp::DeviceStatus::ShadowInfo& shadowInfo, std::shared_ptr<Media::PixelMap> pixelMap)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragNodePipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    CHECK_NULL_RETURN(dragNodePipeline, false);
    CHECK_NULL_RETURN(pixelMap, false);
    auto scaleData =
        NG::DragControllerFuncWrapper::GetScaleInfo(asyncCtx->instanceId, pixelMap->GetWidth(), pixelMap->GetHeight());
    CHECK_NULL_RETURN(scaleData, false);
    auto scale = asyncCtx->windowScale;
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(reinterpret_cast<void*>(&pixelMap));
    CHECK_NULL_RETURN(refPixelMap, false);
    auto badgeNumber = asyncCtx->dragPreviewOption.GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        asyncCtx->badgeNumber = badgeNumber.value();
    }
    data = { false, asyncCtx->badgeNumber, 1.0f, false,
        NG::OffsetF(), NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(asyncCtx->instanceId), refPixelMap };
    NG::DragControllerFuncWrapper::ResetContextMenuDragPosition(asyncCtx->instanceId);
    if (scaleData->isNeedScale && asyncCtx->dragPreviewOption.isScaleEnabled) {
        auto overlayManager = dragNodePipeline->GetOverlayManager();
        auto imageNode = overlayManager->GetPixelMapContentNode();
        scale = scaleData->scale * asyncCtx->windowScale;
        data.previewScale = scale;
        NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
        CHECK_NULL_RETURN(imageNode, false);
        data.imageNode = imageNode;
        data.dragPreviewOffsetToScreen = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    }
    if (!GetShadowInfo(asyncCtx, shadowInfo, refPixelMap, scale)) {
        return false;
    }
    asyncCtxData = { asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value_or(DimensionOffset(0.0_vp, 0.0_vp)),
        asyncCtx->pixelMapList };
    return true;
}

void HandleOnDragStart(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    ContainerScope scope(asyncCtx->instanceId);
    auto container = Ace::AceEngine::Get().GetContainer(Ace::Container::CurrentIdSafely());
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [ctx = asyncCtx, context = pipelineContext]() {
            context->OnDragEvent({ ctx->dragPointerEvent.displayX, ctx->dragPointerEvent.displayY },
                DragEventAction::DRAG_EVENT_START_FOR_CONTROLLER);
            DragDropFuncWrapper::DecideWhetherToStopDragging(
                { ctx->dragPointerEvent.displayX, ctx->dragPointerEvent.displayY }, ctx->extraParams,
                ctx->dragPointerEvent.pointerId, ctx->instanceId);
        },
        TaskExecutor::TaskType::UI, "ArkUIDragHandleDragEventStart", PriorityType::VIP);
}

void ExecuteHandleOnDragStart(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
    if (asyncCtx->dragState == DragState::SENDING) {
        asyncCtx->dragState = DragState::SUCCESS;
        if (!asyncCtx->isSwitchedToSubWindow) {
            Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(true);
        }
        HandleOnDragStart(asyncCtx);
    }
}

static void SetIsDragging(const RefPtr<Container>& container, bool isDragging)
{
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetIsDragging(isDragging);
}

void HideDragPreviewWindow(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    auto container = Ace::AceEngine::Get().GetContainer(Ace::Container::CurrentIdSafely());
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [asyncCtx]() {
            DragControllerFuncWrapper::HideDragPreviewWindow(asyncCtx->instanceId);
        },
        TaskExecutor::TaskType::UI, "ArkUIHideDragPreviewWindow", PriorityType::VIP);
}

int32_t SetUnifiedData(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, std::string& udKey,
    DragSummaryInfo& dragSummaryInfo)
{
    int32_t dataSize = 1;
    CHECK_NULL_RETURN(asyncCtx, dataSize);
    if (asyncCtx->unifiedData) {
        int32_t ret =
            UdmfClient::GetInstance()->SetData(asyncCtx->unifiedData, udKey);
        if (ret != 0) {
            LOGE("AceDrag, udmf set data failed, return value is %{public}d", ret);
        } else {
            ret = UdmfClient::GetInstance()->GetSummary(udKey, dragSummaryInfo);
            if (ret != 0) {
                LOGE("AceDrag, get summary failed, return value is %{public}d", ret);
            }
        }
        dataSize = static_cast<int32_t>(asyncCtx->unifiedData->GetSize());
    }
    auto badgeNumber = asyncCtx->dragPreviewOption.GetCustomerBadgeNumber();
    if (badgeNumber.has_value()) {
        dataSize = badgeNumber.value();
    }
    return dataSize;
    return -1;
}

bool EnvelopedDragData(std::shared_ptr<DragControllerAsyncCtx> asyncCtx,
    std::optional<Msdp::DeviceStatus::DragData>& dragData, std::vector<Msdp::DeviceStatus::ShadowInfo>& shadowInfos)
{
    if (shadowInfos.empty()) {
        LOGE("AceDrag, shadowInfo array is empty");
        return false;
    }
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (!container->GetLastMovingPointerPosition(asyncCtx->dragPointerEvent)) {
        return false;
    }
    std::string udKey;
    DragSummaryInfo dragSummaryInfo;
    int32_t dataSize = SetUnifiedData(asyncCtx, udKey, dragSummaryInfo);
    int32_t recordSize = (dataSize != 0 ? dataSize : static_cast<int32_t>(shadowInfos.size()));
    auto windowId = container->GetWindowId();
    auto arkExtraInfoJson = JsonUtil::Create(true);
    arkExtraInfoJson->Put("dip_scale", asyncCtx->dipScale);
    arkExtraInfoJson->Put("event_id", asyncCtx->dragPointerEvent.pointerEventId);
    DragDropFuncWrapper::UpdateExtraInfo(arkExtraInfoJson, asyncCtx->dragPreviewOption);
    auto materialId = DragDropFuncWrapper::ParseUiMaterial(asyncCtx->dragPreviewOption);
    dragData = { shadowInfos, {}, udKey, asyncCtx->extraParams, arkExtraInfoJson->ToString(),
        asyncCtx->dragPointerEvent.sourceType, recordSize, asyncCtx->dragPointerEvent.pointerId,
        asyncCtx->dragPointerEvent.displayX, asyncCtx->dragPointerEvent.displayY, asyncCtx->dragPointerEvent.displayId,
        windowId, true, false, dragSummaryInfo.summary, false, dragSummaryInfo.detailedSummary,
        dragSummaryInfo.summaryFormat, dragSummaryInfo.version, dragSummaryInfo.totalSize, "", materialId };
    return true;
}

bool StartDragService(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    NG::PreparedInfoForDrag data;
    NG::PreparedAsyncCtxForAnimate asyncCtxData;
    std::vector<Msdp::DeviceStatus::ShadowInfo> shadowInfos;
    Msdp::DeviceStatus::ShadowInfo shadowInfo;
    asyncCtxData = { asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value_or(DimensionOffset(0.0_vp, 0.0_vp)),
        asyncCtx->pixelMapList };
    for (auto& pixelMap : asyncCtx->pixelMapList) {
        if (!pixelMap) {
            LOGE("AceDrag, skip null pixelMap");
            continue;
        }
        if (!CreatePreviewNodeAndScale(asyncCtx, data, asyncCtxData, shadowInfo, pixelMap)) {
            return false;
        }
        shadowInfos.push_back(shadowInfo);
    }
    auto subWindow = DragControllerFuncWrapper::SubWindowShow(pipeline);
    std::optional<Msdp::DeviceStatus::DragData> dragData;
    if (!EnvelopedDragData(asyncCtx, dragData, shadowInfos)) {
        return false;
    }
    data.badgeNumber = dragData->dragNum;
    OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
        HideDragPreviewWindow(asyncCtx);
        HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
    };
    DragDropFuncWrapper::SetDraggingPointerAndPressedState(
        asyncCtx->dragPointerEvent.pointerId, asyncCtx->instanceId);
    DragDropFuncWrapper::SetExtraInfo(asyncCtx->instanceId, asyncCtx->extraParams);
    LogDragInfoInner(asyncCtx, dragData.value());
    auto result = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(
        dragData.value(), std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
    if (result != 0) {
        return false;
    }
    Msdp::DeviceStatus::InteractionManager::GetInstance()->UpdateDragStyle(
        Msdp::DeviceStatus::DragCursorStyle::MOVE, asyncCtx->dragPointerEvent.pointerEventId);
    if (DragControllerFuncWrapper::TryDoDragStartAnimation(subWindow, data, asyncCtxData)) {
        asyncCtx->isSwitchedToSubWindow = true;
    }
    return true;
}

void OnMultipleComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = container->GetWindowScale();
    asyncCtx->windowScale = windowScale;
    taskExecutor->PostTask(
        [asyncCtx]() {
            LOGI("AceDrag, try to start msdp drag.");
            CHECK_NULL_VOID(asyncCtx);
            ContainerScope scope(asyncCtx->instanceId);
            DragState dragState = DragState::PENDING;
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::PENDING) {
                    asyncCtx->dragState = DragState::SENDING;
                }
                dragState = asyncCtx->dragState;
            }
            if (dragState == DragState::REJECT) {
                return;
            }
            if (!StartDragService(asyncCtx)) {
                LOGE("AceDrag, msdp start drag failed.");
                return;
            }
            HandleSuccess(asyncCtx, DragNotifyMsg {}, DragStatus::STARTED);
            
            auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
            CHECK_NULL_VOID(container);
            SetIsDragging(container, true);
            LOGI("AceDrag, msdp start drag successfully");
            ExecuteHandleOnDragStart(asyncCtx);
        },
        TaskExecutor::TaskType::JS, "ArkUIDragMultipleComplete", PriorityType::VIP);
}

void CreatePixelMapArrayByCustom(
    std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle customBuilder, int arrayLength)
{
    CHECK_NULL_VOID(asyncCtx);
    auto callback = [asyncCtx, arrayLength](std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode,
                        std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [finishCallback]() {
                CHECK_NULL_VOID(finishCallback);
                finishCallback();
            },
            TaskExecutor::TaskType::JS, "ArkUICreatePixelMapArrayByCustom");
        asyncCtx->parseBuilderCount++;
        CHECK_NULL_VOID(pixelMap);
        asyncCtx->pixelMapList.push_back(std::move(pixelMap));
        if (asyncCtx->parseBuilderCount == arrayLength) {
            OnMultipleComplete(asyncCtx);
        }
    };
    NG::SnapshotParam param;
    param.delay = CREATE_PIXELMAP_DELAY_TIME;
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
    auto uinode = AceType::Claim(reinterpret_cast<UINode *>(customBuilder));
    CHECK_NULL_VOID(uinode);
    ComponentSnapshot::Create(uinode, std::move(callback), true, param);
}

void GetCurrentDipScale(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_VOID(asyncCtx);
    auto container = AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    asyncCtx->dipScale = pipeline->GetDipScale();
}

void HandleStopDragCallback(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const RefPtr<Container>& container)
{
    CHECK_NULL_VOID(asyncCtx);
    CHECK_NULL_VOID(container);
    bool needPostStopDrag = false;
    {
        std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
        needPostStopDrag = (asyncCtx->dragState == DragState::SENDING);
        asyncCtx->dragState = DragState::REJECT;
    }
    if (needPostStopDrag) {
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->ResetDragging();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto windowId = container->GetWindowId();
        taskExecutor->PostTask(
            [asyncCtx, windowId]() {
                CHECK_NULL_VOID(asyncCtx);
                LOGI("drag state is reject, stop drag, windowId is %{public}d.", windowId);
                Msdp::DeviceStatus::DragDropResult dropResult { Msdp::DeviceStatus::DragResult::DRAG_CANCEL, false,
                    windowId, Msdp::DeviceStatus::DragBehavior::UNKNOWN };
                Msdp::DeviceStatus::InteractionManager::GetInstance()->StopDrag(dropResult);
                Msdp::DeviceStatus::InteractionManager::GetInstance()->SetDragWindowVisible(false);
            },
            TaskExecutor::TaskType::JS, "ArkUIDragStop", PriorityType::VIP);
    }
}

bool ConfirmCurPointerEventInfo(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    CHECK_NULL_RETURN(container, false);
    StopDragCallback stopDragCallback = [asyncCtx, container]() { HandleStopDragCallback(asyncCtx, container); };
    bool getPointSuccess = container->GetCurPointerEventInfo(asyncCtx->dragPointerEvent, std::move(stopDragCallback));
    if (asyncCtx->dragPointerEvent.sourceType == SOURCE_TYPE_MOUSE) {
        asyncCtx->dragPointerEvent.pointerId = MOUSE_POINTER_ID;
    } else if (asyncCtx->dragPointerEvent.sourceType == SOURCE_TYPE_TOUCH &&
               static_cast<int32_t>(asyncCtx->dragPointerEvent.sourceTool) == SOURCE_TOOL_PEN) {
        asyncCtx->dragPointerEvent.pointerId = PEN_POINTER_ID;
    }
    return getPointSuccess;
}

bool PrepareDragData(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, Msdp::DeviceStatus::DragData& dragData,
    Msdp::DeviceStatus::ShadowInfo& shadowInfo)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    CHECK_NULL_RETURN(asyncCtx->pixelMap, false);
    std::string udKey;
    DragSummaryInfo dragSummaryInfo;
    int32_t dataSize = SetUnifiedData(asyncCtx, udKey, dragSummaryInfo);
    
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (!container->GetLastMovingPointerPosition(asyncCtx->dragPointerEvent)) {
        LOGE("AceDrag, can not find current pointerId or not in press.");
        return false;
    }
    auto arkExtraInfoJson = JsonUtil::Create(true);
    arkExtraInfoJson->Put("dip_scale", asyncCtx->dipScale);
    arkExtraInfoJson->Put("event_id", asyncCtx->dragPointerEvent.pointerEventId);
    DragDropFuncWrapper::UpdateExtraInfo(arkExtraInfoJson, asyncCtx->dragPreviewOption);
    auto windowId = container->GetWindowId();
    auto materialId = DragDropFuncWrapper::ParseUiMaterial(asyncCtx->dragPreviewOption);
    dragData = { { shadowInfo }, {}, udKey, asyncCtx->extraParams, arkExtraInfoJson->ToString(),
        asyncCtx->dragPointerEvent.sourceType, dataSize, asyncCtx->dragPointerEvent.pointerId,
        asyncCtx->dragPointerEvent.displayX, asyncCtx->dragPointerEvent.displayY, asyncCtx->dragPointerEvent.displayId,
        windowId, true, false, dragSummaryInfo.summary, false, dragSummaryInfo.detailedSummary,
        dragSummaryInfo.summaryFormat, dragSummaryInfo.version, dragSummaryInfo.totalSize, "", materialId };
    return true;
}

bool TryToStartDrag(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    CHECK_NULL_RETURN(asyncCtx, false);
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_RETURN(container, false);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipeline, false);
    NG::PreparedInfoForDrag data;
    NG::PreparedAsyncCtxForAnimate asyncCtxData;
    Msdp::DeviceStatus::ShadowInfo shadowInfo;
    asyncCtxData = { asyncCtx->instanceId, asyncCtx->touchPoint.has_value(), asyncCtx->dragPointerEvent,
        asyncCtx->dragPreviewOption, asyncCtx->touchPoint.value_or(DimensionOffset(0.0_vp, 0.0_vp)),
        asyncCtx->pixelMapList };
    if (!CreatePreviewNodeAndScale(asyncCtx, data, asyncCtxData, shadowInfo, asyncCtx->pixelMap)) {
        LOGE("AceDrag, create preview node failed.");
        return false;
    }
    auto subWindow = DragControllerFuncWrapper::SubWindowShow(pipeline);
    Msdp::DeviceStatus::DragData dragData;
    if (!PrepareDragData(asyncCtx, dragData, shadowInfo)) {
        LOGE("AceDrag, prepare drag data failed!");
        return false;
    }
    data.badgeNumber = dragData.dragNum;
    OnDragCallback callback = [asyncCtx](const DragNotifyMsg& dragNotifyMsg) {
        HideDragPreviewWindow(asyncCtx);
        HandleSuccess(asyncCtx, dragNotifyMsg, DragStatus::ENDED);
    };
    DragDropFuncWrapper::SetDraggingPointerAndPressedState(
        asyncCtx->dragPointerEvent.pointerId, asyncCtx->instanceId);
    LogDragInfoInner(asyncCtx, dragData);
    auto result = Msdp::DeviceStatus::InteractionManager::GetInstance()->StartDrag(
        dragData, std::make_shared<OHOS::Ace::StartDragListenerImpl>(callback));
    if (result != 0) {
        return false;
    }
    Msdp::DeviceStatus::InteractionManager::GetInstance()->UpdateDragStyle(
        Msdp::DeviceStatus::DragCursorStyle::MOVE, asyncCtx->dragPointerEvent.pointerEventId);
    if (DragControllerFuncWrapper::TryDoDragStartAnimation(subWindow, data, asyncCtxData)) {
        asyncCtx->isSwitchedToSubWindow = true;
    }
    return true;
}

void OnComplete(std::shared_ptr<DragControllerAsyncCtx> asyncCtx)
{
    LOGI("AceDrag, OnComplete start");
    auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto windowScale = container->GetWindowScale();
    asyncCtx->windowScale = windowScale;
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    asyncCtx->dragPointerEvent.displayId = static_cast<int32_t>(displayInfo->GetDisplayId());
    taskExecutor->PostTask(
        [asyncCtx]() {
            LOGI("AceDrag, try to start msdp drag.");
            CHECK_NULL_VOID(asyncCtx);
            ContainerScope scope(asyncCtx->instanceId);
            DragState dragState = DragState::PENDING;
            {
                std::lock_guard<std::mutex> lock(asyncCtx->dragStateMutex);
                if (asyncCtx->dragState == DragState::PENDING) {
                    asyncCtx->dragState = DragState::SENDING;
                }
                dragState = asyncCtx->dragState;
            }
            if (dragState == DragState::REJECT) {
                return;
            }
            if (!TryToStartDrag(asyncCtx)) {
                LOGE("AceDrag, msdp start drag failed.");
                return;
            }
            
            auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
            CHECK_NULL_VOID(container);
            SetIsDragging(container, true);
            LOGI("AceDrag, msdp start drag successfully");
            ExecuteHandleOnDragStart(asyncCtx);
        },
        TaskExecutor::TaskType::JS, "ArkUIDragComplete", PriorityType::VIP);
}

void CreatePixelMapByCustom(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle builderNode)
{
    CHECK_NULL_VOID(asyncCtx);
    
    auto callback = [asyncCtx](std::shared_ptr<Media::PixelMap> pixelMap, int32_t errCode,
                        std::function<void()> finishCallback) {
        CHECK_NULL_VOID(asyncCtx);
        auto container = Ace::AceEngine::Get().GetContainer(asyncCtx->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [finishCallback]() {
                CHECK_NULL_VOID(finishCallback);
                finishCallback();
            },
            TaskExecutor::TaskType::JS, "ArkUICreatePixelMapByCustom");
        CHECK_NULL_VOID(pixelMap);
        asyncCtx->pixelMap = std::move(pixelMap);
        OnComplete(asyncCtx);
    };
    NG::SnapshotParam param;
    param.delay = CREATE_PIXELMAP_DELAY_TIME;
    param.checkImageStatus = true;
    param.options.waitUntilRenderFinished = true;
    if (builderNode) {
        auto uinode = AceType::Claim(reinterpret_cast<UINode *>(builderNode));
        CHECK_NULL_VOID(uinode);
        ComponentSnapshot::Create(uinode, std::move(callback), true, param);
    }
}

void HandleExecuteDrag(std::shared_ptr<DragControllerAsyncCtx> asyncCtx, ArkUINodeHandle builderNode)
{
    ParameterType parameterType = GetParameterType(asyncCtx);
    if (parameterType == ParameterType::DRAG_PIXEL) {
        LOGI("AceDrag, drag preview is pixelMap.");
        OnComplete(asyncCtx);
    } else if (parameterType == ParameterType::DRAG_CUSTOM_BUILDER) {
        LOGI("AceDrag, drag preview is custom builder.");
        CreatePixelMapByCustom(asyncCtx, builderNode);
    } else {
        LOGE("AceDrag, parameter parsing error");
    }
}

void UpdatePreviewOptionDefaultAttr(
    std::shared_ptr<DragControllerAsyncCtx> dragAsyncContext, const ArkUIDragControllerAsync& asyncCtx)
{
    dragAsyncContext->dragPreviewOption.isScaleEnabled = asyncCtx.dragPreviewOption.isScaleEnabled;
    dragAsyncContext->dragPreviewOption.isDefaultShadowEnabled = asyncCtx.dragPreviewOption.isDefaultShadowEnabled;
    dragAsyncContext->dragPreviewOption.isDefaultRadiusEnabled = asyncCtx.dragPreviewOption.isDefaultRadiusEnabled;
    dragAsyncContext->dragPreviewOption.isNumber = asyncCtx.dragPreviewOption.isNumber;
    if (asyncCtx.dragPreviewOption.isNumber) {
        dragAsyncContext->dragPreviewOption.badgeNumber = asyncCtx.dragPreviewOption.badgeNumber;
    } else {
        dragAsyncContext->dragPreviewOption.isShowBadge = asyncCtx.dragPreviewOption.isShowBadge;
    }
    NG::DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(dragAsyncContext->dragPreviewOption);
}

void UpdateDragPreviewOptionsFromModifier(std::shared_ptr<DragControllerAsyncCtx> dragAsyncContext,
    const ArkUIDragControllerAsync& asyncCtx)
{
    CHECK_NULL_VOID(dragAsyncContext);
    if (!asyncCtx.dragPreviewOption.modifier) {
        return;
    }
    auto onApply = [executeFunc =
        std::move(asyncCtx.dragPreviewOption.modifier)](WeakPtr<FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
        auto ptr = AceType::RawPtr(node);
        CHECK_NULL_VOID(executeFunc);
        executeFunc(ptr);
    };
    NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(onApply, dragAsyncContext->dragPreviewOption);
}

void* CreateDragEventPeer(const ArkUIDragNotifyMessage& dragNotifyMsg)
{
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    SetDragResult(dragNotifyMsg, dragEvent);
    SetDragBehavior(dragNotifyMsg, dragEvent);
    auto dragEventPeer = DragEventPeer::Create(dragEvent);
    return dragEventPeer;
}

std::shared_ptr<DragControllerAsyncCtx> ConvertDragControllerAsync(const ArkUIDragControllerAsync& asyncCtx)
{
    auto dragAsyncContext = std::make_shared<DragControllerAsyncCtx>();
    CHECK_NULL_RETURN(dragAsyncContext, nullptr);
    dragAsyncContext->env = asyncCtx.env;
    dragAsyncContext->isArray = asyncCtx.isArray;
    if (!asyncCtx.extraParams.empty()) {
        dragAsyncContext->extraParams = asyncCtx.extraParams;
    }
    dragAsyncContext->hasHandle = asyncCtx.hasHandle;
    void* touchPointPtr = asyncCtx.touchPoint;
    if (touchPointPtr) {
        dragAsyncContext->touchPoint = *static_cast<DimensionOffset*>(touchPointPtr);
    } else {
        dragAsyncContext->touchPoint.reset();
    }
    dragAsyncContext->customBuilderNode = asyncCtx.customBuilderNode;
    dragAsyncContext->customBuilderNodeList = asyncCtx.customBuilderNodeList;
    dragAsyncContext->asyncCallback = asyncCtx.asyncCallback;
    dragAsyncContext->deferred = asyncCtx.deferred;
    dragAsyncContext->dragPointerEvent.pointerId = asyncCtx.dragPointerEvent.pointerId;
    dragAsyncContext->dragAction = asyncCtx.dragAction;
    dragAsyncContext->callBackJsFunction = asyncCtx.callBackJsFunction;
    UpdatePreviewOptionDefaultAttr(dragAsyncContext, asyncCtx);
    UpdateDragPreviewOptionsFromModifier(dragAsyncContext, asyncCtx);
    if (asyncCtx.unifiedData) {
        auto unifiedDataPtr = std::static_pointer_cast<UDMF::UnifiedData>(asyncCtx.unifiedData.GetSharedPtr());
        auto udData = AceType::MakeRefPtr<UnifiedDataImpl>();
        udData->SetUnifiedData(unifiedDataPtr);
        dragAsyncContext->unifiedData = udData;
    }
#if defined(PIXEL_MAP_SUPPORTED)
    if (asyncCtx.pixelMap) {
        dragAsyncContext->pixelMap = std::static_pointer_cast<Media::PixelMap>(asyncCtx.pixelMap.GetSharedPtr());
    }

    for (const auto& pixelMapValue : asyncCtx.pixelMapList) {
        dragAsyncContext->pixelMapList.emplace_back(
            std::static_pointer_cast<Media::PixelMap>(pixelMapValue.GetSharedPtr()));
    }
#endif
    return dragAsyncContext;
}

bool ANIHandleExecuteDrag(ArkUIDragControllerAsync& asyncCtx, std::string &errMsg)
{
    auto dragAsyncContext = ConvertDragControllerAsync(asyncCtx);
    CHECK_NULL_RETURN(dragAsyncContext, false);
    dragAsyncContext->instanceId = Ace::Container::CurrentIdSafely();
    GetCurrentDipScale(dragAsyncContext);
    auto container = Ace::AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (CheckDragging(container)) {
        errMsg = "only one drag is allowed at the same time.";
        LOGE("AceDrag, only one drag is allowed at the same time.");
        return false;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        errMsg = "confirm current point info failed.";
        LOGE("AceDrag, confirm current point info failed.");
        return false;
    }
    HandleExecuteDrag(dragAsyncContext, dragAsyncContext->customBuilderNode);
    return true;
}

bool ANIHandleDragAction(ArkUIDragControllerAsync& asyncCtx, std::string &errMsg)
{
    auto dragAsyncContext = ConvertDragControllerAsync(asyncCtx);
    CHECK_NULL_RETURN(dragAsyncContext, false);
    dragAsyncContext->instanceId = Ace::Container::CurrentIdSafely();
    GetCurrentDipScale(dragAsyncContext);
    auto container = Ace::AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (CheckDragging(container)) {
        errMsg = "only one drag is allowed at the same time.";
        LOGE("AceDrag, only one drag is allowed at the same time.");
        return false;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        errMsg = "confirm current point info failed.";
        LOGE("AceDrag, confirm current point info failed.");
        return false;
    }
    return true;
}

bool ANIHandleDragActionStartDrag(ArkUIDragControllerAsync& asyncCtx)
{
    auto dragAsyncContext = ConvertDragControllerAsync(asyncCtx);
    CHECK_NULL_RETURN(dragAsyncContext, false);
    dragAsyncContext->instanceId = Ace::Container::CurrentIdSafely();
    GetCurrentDipScale(dragAsyncContext);
    auto container = Ace::AceEngine::Get().GetContainer(dragAsyncContext->instanceId);
    CHECK_NULL_RETURN(container, false);
    if (CheckDragging(container)) {
        LOGE("AceDrag, only one drag is allowed at the same time.");
        return false;
    }
    auto getPointSuccess = ConfirmCurPointerEventInfo(dragAsyncContext, container);
    if (!getPointSuccess) {
        LOGE("AceDrag, confirm current point info failed.");
        return false;
    }
    ParameterType parameterType = GetParameterType(dragAsyncContext);
    if (parameterType == ParameterType::DRAG_PIXEL_ARRAY) {
        OnMultipleComplete(dragAsyncContext);
    } else if (parameterType == ParameterType::DRAG_MIX_ARRAY) {
        int32_t arrayLength = static_cast<int32_t>(dragAsyncContext->customBuilderNodeList.size());
        for (const auto& customBuilderNodeValue : dragAsyncContext->customBuilderNodeList) {
            CreatePixelMapArrayByCustom(dragAsyncContext, customBuilderNodeValue, arrayLength);
        }
    } else {
        return false;
    }
    return true;
}

void ANIDragPreviewSetForegroundColor(ani_long colorValue, ArkUIDragPreviewAsync& asyncCtx)
{
    auto iter = std::find(asyncCtx.previewStyle.types.begin(),
        asyncCtx.previewStyle.types.end(), ArkUIPreviewType::FOREGROUND_COLOR);
    if (iter == asyncCtx.previewStyle.types.end()) {
        asyncCtx.previewStyle.types.emplace_back(ArkUIPreviewType::FOREGROUND_COLOR);
    }
    const auto convColor = static_cast<int64_t>(colorValue);
    if (convColor < 0 || convColor > UINT_MAX) {
        return;
    }
    asyncCtx.previewStyle.foregroundColor = convColor;
    PreviewStyle previewStyle { {}, 0, -1, -1, -1 };
    ConvertPreviewStyle(previewStyle, asyncCtx);
    if (!asyncCtx.hasAnimation) {
        auto container = AceEngine::Get().GetContainer(Container::CurrentId());
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [previewStyle]() {
                int32_t result =
                    Msdp::DeviceStatus::InteractionManager::GetInstance()->UpdatePreviewStyle(previewStyle);
                if (result != 0) {
                    LOGE("AceDrag, update preview style failed. result = %{public}d", result);
                    return;
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewStyle");
        asyncCtx.previewStyle.types.clear();
    }
}

void ANIDragPreviewAnimate(ArkUIDragPreviewAsync& asyncCtx)
{
    auto container = AceEngine::Get().GetContainer(Container::CurrentId());
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    PreviewAnimation previewAnimation;
    ConvertDragPreviewAnimation(previewAnimation, asyncCtx);
    PreviewStyle previewStyle { {}, 0, -1, -1, -1 };
    ConvertPreviewStyle(previewStyle, asyncCtx);
    taskExecutor->PostTask(
        [previewStyle, previewAnimation]() {
            int32_t ret = Msdp::DeviceStatus::InteractionManager::
                GetInstance()->UpdatePreviewStyleWithAnimation(previewStyle, previewAnimation);
            if (ret != 0) {
                LOGE("AceDrag, update preview style with animation failed. ret = %{public}d", ret);
                return;
            };
        },
        TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewAnimationStyle");
    asyncCtx.hasAnimation = false;
    asyncCtx.previewStyle.types.clear();
}

void ANIDragActionSetDragEventStrictReportingEnabled(bool enable)
{
    ViewAbstractModel::GetInstance()->SetDragEventStrictReportingEnabled(enable);
}

void ANIDragActionCancelDataLoading(const char* key)
{
    ViewAbstractModel::GetInstance()->CancelDataLoading(key);
}

void ANIDragActionNotifyDragStartReques(int requestStatus)
{
    ViewAbstractModel::GetInstance()->NotifyDragStartRequest(static_cast<Ace::DragStartRequestStatus>(requestStatus));
}

const ArkUIAniDragControllerModifier* GetDragControllerAniModifier()
{
    static const ArkUIAniDragControllerModifier impl = {
        .aniHandleExecuteDrag = NG::ANIHandleExecuteDrag,
        .aniHandleDragAction = NG::ANIHandleDragAction,
        .aniHandleDragActionStartDrag = NG::ANIHandleDragActionStartDrag,
        .createDragEventPeer = NG::CreateDragEventPeer,
        .aniDragPreviewSetForegroundColor = NG::ANIDragPreviewSetForegroundColor,
        .aniDragPreviewAnimate = NG::ANIDragPreviewAnimate,
        .aniDragActionSetDragEventStrictReportingEnabled = NG::ANIDragActionSetDragEventStrictReportingEnabled,
        .aniDragActionCancelDataLoading = NG::ANIDragActionCancelDataLoading,
        .aniDragActionNotifyDragStartReques = NG::ANIDragActionNotifyDragStartReques,
    };
    return &impl;
}
} // namespace OHOS:Ace::NG

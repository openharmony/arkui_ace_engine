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
#include "core/interfaces/native/node/drag_adapter_impl.h"

#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"

namespace OHOS::Ace::DragAdapter {
namespace {
static void DragActionConvert(
    ArkUIDragAction* dragAction, std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> internalDragAction)
{
    CHECK_NULL_VOID(dragAction);
    CHECK_NULL_VOID(internalDragAction);
    internalDragAction->dragPointerEvent.pointerId = dragAction->pointerId;
    internalDragAction->size = dragAction->size;
    internalDragAction->previewOption.isScaleEnabled = dragAction->dragPreviewOption.isScaleEnabled;
    if (!internalDragAction->previewOption.isScaleEnabled) {
        internalDragAction->previewOption.isDefaultShadowEnabled = dragAction->dragPreviewOption.isDefaultShadowEnabled;
        internalDragAction->previewOption.isDefaultRadiusEnabled = dragAction->dragPreviewOption.isDefaultRadiusEnabled;
    }
    internalDragAction->previewOption.defaultAnimationBeforeLifting =
        dragAction->dragPreviewOption.defaultAnimationBeforeLifting;
    internalDragAction->previewOption.enableHapticFeedback = dragAction->dragPreviewOption.enableHapticFeedback;
    internalDragAction->previewOption.isMultiSelectionEnabled = dragAction->dragPreviewOption.isMultiSelectionEnabled;
    internalDragAction->previewOption.enableEdgeAutoScroll = dragAction->dragPreviewOption.enableEdgeAutoScroll;
    internalDragAction->previewOption.isNumber = dragAction->dragPreviewOption.isNumberBadgeEnabled;
    if (dragAction->dragPreviewOption.badgeNumber > 1) {
        internalDragAction->previewOption.badgeNumber = dragAction->dragPreviewOption.badgeNumber;
    } else {
        internalDragAction->previewOption.isShowBadge = dragAction->dragPreviewOption.isShowBadge;
    }
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->TransformUnifiedDataForNative(dragAction->unifiedData);
    internalDragAction->unifiedData = udData;
    internalDragAction->instanceId = dragAction->instanceId;
    internalDragAction->touchPointX = dragAction->touchPointX;
    internalDragAction->touchPointY = dragAction->touchPointY;
    internalDragAction->hasTouchPoint = dragAction->hasTouchPoint;
}

ArkUI_Int32 StartDrag(ArkUIDragAction* dragAction)
{
    CHECK_NULL_RETURN(dragAction, -1);
    auto internalDragAction = std::make_shared<OHOS::Ace::NG::ArkUIInteralDragAction>();

    CHECK_NULL_RETURN(internalDragAction, -1);
    auto callbacks = [listener = dragAction->listener, userData = dragAction->userData,
                         instanceId = dragAction->instanceId](const DragNotifyMsg& dragNotifyMsg, int32_t status) {
        auto pipelineContext = NG::PipelineContext::GetContextByContainerId(instanceId);
        CHECK_NULL_VOID(pipelineContext);
        auto manager = pipelineContext->GetDragDropManager();
        CHECK_NULL_VOID(manager);
        ArkUIDragEvent dragEvent;
        dragEvent.dragResult = static_cast<int32_t>(dragNotifyMsg.result);
        dragEvent.dragBehavior = static_cast<int32_t>(dragNotifyMsg.dragBehavior);
        DragBundleInfo dragBundleInfo;
        InteractionInterface::GetInstance()->GetDragBundleInfo(dragBundleInfo);
        dragEvent.bundleName = strdup(dragBundleInfo.bundleName.c_str());
        dragEvent.isRemoteDev = &dragBundleInfo.isRemoteDev;

        auto action = manager->GetDragAction();
        if (action != nullptr) {
            action->hasHandle = false;
        }
        ArkUIDragAndDropInfo outInfo;
        outInfo.status = status;
        outInfo.dragEvent = &dragEvent;
        CHECK_NULL_VOID(listener);
        listener(&outInfo, userData);
    };
    auto* pixelMapTemp = reinterpret_cast<std::shared_ptr<void*>*>(dragAction->pixelmapArray);
    for (int index = 0; index < dragAction->size; index++) {
        auto pixelMap = PixelMap::CreatePixelMap(&pixelMapTemp[index]);
        internalDragAction->pixelMapList.push_back(pixelMap);
    }
    internalDragAction->callback = callbacks;
    DragActionConvert(dragAction, internalDragAction);
    auto ret = OHOS::Ace::NG::DragDropFuncWrapper::StartDragAction(internalDragAction);
    if (ret == -1) {
        DragNotifyMsg dragNotifyMsg;
        dragNotifyMsg.result = DragRet::DRAG_CANCEL;
        OHOS::Ace::NG::DragDropFuncWrapper::HandleCallback(internalDragAction,
            dragNotifyMsg, NG::DragAdapterStatus::ENDED);
    }
    return 0;
}

void RegisterStatusListener(ArkUIDragAction* dragAction, void* userData, DragStatusCallback listener)
{
    CHECK_NULL_VOID(dragAction);
    dragAction->listener = listener;
    dragAction->userData = userData;
}

void UnRegisterStatusListener(ArkUIDragAction* dragAction)
{
    CHECK_NULL_VOID(dragAction);
    dragAction->listener = nullptr;
    dragAction->userData = nullptr;
}

ArkUIDragAction* CreateDragActionWithNode(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto* dragAction = new ArkUIDragAction();
    CHECK_NULL_RETURN(dragAction, nullptr);
    dragAction->instanceId = pipeline->GetInstanceId();
    return dragAction;
}

ArkUIDragAction* CreateDragActionWithContext(ArkUIContext* context)
{
    CHECK_NULL_RETURN(context, nullptr);
    auto* dragAction = new ArkUIDragAction();
    CHECK_NULL_RETURN(dragAction, nullptr);
    dragAction->instanceId = context->id;
    return dragAction;
}

void SetDragPreview(ArkUINodeHandle node, void* dragPreview)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::DragDropInfo dragPreviewInfo;
    dragPreviewInfo.pixelMap = PixelMap::CreatePixelMap(dragPreview);
    NG::ViewAbstract::SetDragPreview(frameNode, dragPreviewInfo);
}

void SetDragEventStrictReportingEnabledWithNode(bool enabled)
{
    NG::ViewAbstract::SetDragEventStrictReportingEnabled(enabled);
}

void SetDragEventStrictReportingEnabledWithContext(ArkUI_Int32 instanceId, bool enabled)
{
    NG::ViewAbstract::SetDragEventStrictReportingEnabled(instanceId, enabled);
}

void EnableDropDisallowedBadge(bool enabled)
{
    NG::ViewAbstract::EnableDropDisallowedBadge(enabled);
}

ArkUI_Int32 RequestDragEndPending()
{
    return NG::DragDropFuncWrapper::RequestDragEndPending();
}

ArkUI_Int32 NotifyDragResult(ArkUI_Int32 requestId, ArkUI_Int32 result)
{
    return NG::DragDropFuncWrapper::NotifyDragResult(requestId, result);
}

ArkUI_Int32 NotifyDragEndPendingDone(ArkUI_Int32 requestId)
{
    return NG::DragDropFuncWrapper::NotifyDragEndPendingDone(requestId);
}

} // namespace
const ArkUIDragAdapterAPI* GetDragAdapterAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDragAdapterAPI impl {
        .startDrag = StartDrag,
        .registerStatusListener = RegisterStatusListener,
        .unregisterStatusListener = UnRegisterStatusListener,
        .createDragActionWithNode = CreateDragActionWithNode,
        .createDragActionWithContext = CreateDragActionWithContext,
        .setDragPreview = SetDragPreview,
        .setDragEventStrictReportingEnabledWithNode = SetDragEventStrictReportingEnabledWithNode,
        .setDragEventStrictReportingEnabledWithContext = SetDragEventStrictReportingEnabledWithContext,
        .requestDragEndPending = RequestDragEndPending,
        .notifyDragResult = NotifyDragResult,
        .notifyDragEndPendingDone = NotifyDragEndPendingDone,
        .enableDropDisallowedBadge = EnableDropDisallowedBadge,
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}
} // namespace OHOS::Ace::DragAdapter

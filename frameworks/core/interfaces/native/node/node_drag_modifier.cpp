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
#include "core/interfaces/native/node/node_drag_modifier.h"

#include "interfaces/native/node/node_model.h"

#include "core/common/udmf/udmf_client.h"
#include "core/components_ng/pattern/text/span_model_ng.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
uint64_t CalculateModifierKeyState(const std::vector<OHOS::Ace::KeyCode>& status)
{
    uint64_t modifierKeysState = 0;
    // check ctrl
    if ((std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_CTRL_LEFT) != std::end(status)) ||
        (std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_CTRL_RIGHT) != std::end(status))) {
        modifierKeysState |= ARKUI_MODIFIER_KEY_CTRL;
    }
    // check alt
    if ((std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_ALT_LEFT) != std::end(status)) ||
        (std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_ALT_RIGHT) != std::end(status))) {
        modifierKeysState |= ARKUI_MODIFIER_KEY_ALT;
    }
    // check shift
    if ((std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_SHIFT_LEFT) != std::end(status)) ||
        (std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_SHIFT_RIGHT) != std::end(status))) {
        modifierKeysState |= ARKUI_MODIFIER_KEY_SHIFT;
    }
    // check fn
    if (std::find(status.begin(), status.end(), OHOS::Ace::KeyCode::KEY_FN) != std::end(status)) {
        modifierKeysState |= ARKUI_MODIFIER_KEY_FN;
    }

    return modifierKeysState;
}

void SetDragEventProperty(const RefPtr<OHOS::Ace::DragEvent>& info, ArkUINodeEvent& event,
    std::vector<const char*>& strList, std::vector<std::string>& keepStr)
{
    event.dragEvent.touchPointX = info->GetPreviewRect().GetOffset().GetX();
    event.dragEvent.touchPointY = info->GetPreviewRect().GetOffset().GetY();

    event.dragEvent.windowX = info->GetX();
    event.dragEvent.windowY = info->GetY();
    event.dragEvent.displayX = info->GetDisplayX();
    event.dragEvent.displayY = info->GetDisplayY();
    event.dragEvent.screenX = info->GetScreenX();
    event.dragEvent.screenY = info->GetScreenY();

    event.dragEvent.previewRectWidth = info->GetPreviewRect().Width();
    event.dragEvent.previewRectHeight = info->GetPreviewRect().Height();
    event.dragEvent.velocityX = info->GetVelocity().GetVelocityX();
    event.dragEvent.velocityY = info->GetVelocity().GetVelocityY();
    event.dragEvent.velocity = info->GetVelocity().GetVelocityValue();
    event.dragEvent.modifierKeyState = NodeModifier::CalculateModifierKeyState(info->GetPressedKeyCodes());
    event.dragEvent.displayId = info->GetDisplayId();
    auto summary = info->GetSummary();
    event.dragEvent.dataTypesCount = static_cast<int32_t>(summary.size());

    int32_t index = 0;
    int32_t maxLength = 0;
    for (auto it = summary.begin(); it != summary.end(); it++) {
        int32_t keyLength = static_cast<int32_t>(it->first.length());
        maxLength = std::max(maxLength, keyLength);
        keepStr[index] = it->first;
        strList.push_back(keepStr[index].c_str());
        ++index;
    }
    event.dragEvent.dataTypes = strList.data();
    event.dragEvent.dataTypesMaxStrLength = maxLength + 1;
    event.dragEvent.key = info->GetUdKey().c_str();
}

void SetOnDragDrop(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragDrop = [frameNode, nodeId, extraParam](
                          const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) -> void {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_DROP;
        auto summary = info->GetSummary();
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());

        SetDragEventProperty(info, event, strList, keepStr);
        event.dragEvent.isSuitGetData = true;

        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(DragBehavior::UNKNOWN);
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info->UseCustomAnimation(event.dragEvent.useCustomDropAnimation);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
        info->SetIsDragEndPending(event.dragEvent.isDragEndPending);
        info->SetRequestIdentify(event.dragEvent.requestId);
        info->SetCapi(true);
    };
    ViewAbstract::SetOnDrop(frameNode, onDragDrop);
}

void SetOnDragStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragStart = [frameNode, nodeId, extraParam](const RefPtr<OHOS::Ace::DragEvent>& info,
                           const std::string& extraParams) -> NG::DragDropBaseInfo {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_START;
        auto summary = info->GetSummary();
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());

        SetDragEventProperty(info, event, strList, keepStr);
        event.dragEvent.isSuitGetData = false;

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();
        SendArkUISyncEvent(&event);
        RefPtr<UnifiedData> udData =
            UdmfClient::GetInstance()->TransformUnifiedDataForNative(event.dragEvent.unifiedData);

        info->SetData(udData);
        NG::DragDropBaseInfo dragDropInfo;
        return dragDropInfo;
    };
    ViewAbstractModelNG::SetOnDragStart(frameNode, onDragStart);
}

void SetOnDragEnter(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragEnter = [frameNode, nodeId, extraParam](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_ENTER;

        auto summary = info->GetSummary();
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());

        SetDragEventProperty(info, event, strList, keepStr);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(DragBehavior::UNKNOWN);
        event.dragEvent.unifiedData = unifiedData;
        event.dragEvent.isSuitGetData = false;
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
        info->SetCapi(true);
    };
    ViewAbstract::SetOnDragEnter(frameNode, onDragEnter);
}

void SetOnDragMove(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragMove = [frameNode, nodeId, extraParam](
                          const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_MOVE;
        auto summary = info->GetSummary();
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());

        SetDragEventProperty(info, event, strList, keepStr);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(DragBehavior::UNKNOWN);
        event.dragEvent.unifiedData = unifiedData;
        event.dragEvent.isSuitGetData = false;
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
        info->SetCapi(true);
    };
    ViewAbstract::SetOnDragMove(frameNode, onDragMove);
}

void SetOnDragLeave(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragLeave = [frameNode, nodeId, extraParam](
                           const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams) {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_LEAVE;

        auto summary = info->GetSummary();
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());

        SetDragEventProperty(info, event, strList, keepStr);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(DragBehavior::UNKNOWN);
        event.dragEvent.unifiedData = unifiedData;
        event.dragEvent.isSuitGetData = false;
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
        info->SetCapi(true);
    };
    ViewAbstract::SetOnDragLeave(frameNode, onDragLeave);
}

void SetOnDragEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onDragEnd = [frameNode, nodeId, extraParam](const RefPtr<OHOS::Ace::DragEvent>& info) -> void {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::DRAG_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.dragEvent.subKind = ON_DRAG_END;
        auto summary = info->GetSummary();
        event.dragEvent.dataTypesCount = static_cast<int32_t>(summary.size());

        int32_t index = 0;
        int32_t maxLength = 0;
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());
        for (auto it = summary.begin(); it != summary.end(); it++) {
            int32_t keyLength = static_cast<int32_t>(it->first.length());
            maxLength = std::max(maxLength, keyLength);
            keepStr[index] = it->first;
            strList.push_back(keepStr[index].c_str());
            ++index;
        }
        event.dragEvent.dataTypes = strList.data();
        event.dragEvent.dataTypesMaxStrLength = maxLength + 1;

        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;
        event.dragEvent.isSuitGetData = false;

        // Did NOT define pressCode, so will NOT pass presscode to UI.
        event.dragEvent.dragResult = static_cast<ArkUI_Int32>(info->GetResult());
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(info->GetDragBehavior());
        event.dragEvent.displayId = static_cast<ArkUI_Int32>(info->GetDisplayId());
        event.dragEvent.bundleName = strdup(info->GetDragSource().c_str());
        event.dragEvent.isRemoteDev = info->isRemoteDev();

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnDragEnd(frameNode, onDragEnd);
}

void SetOnPreDrag(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    int32_t nodeId = frameNode->GetId();
    auto onPreDrag = [frameNode, nodeId, extraParam](const PreDragStatus preDragStatus) -> void {
        ArkUINodeEvent event;
        event.kind = ArkUIEventCategory::COMPONENT_ASYNC_EVENT;
        event.nodeId = nodeId;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_PRE_DRAG;

        // Did NOT define pressCode, so will NOT pass presscode to UI.
        event.componentAsyncEvent.data[0].i32 = static_cast<ArkUI_Int32>(preDragStatus);
        event.dragEvent.isSuitGetData = false;

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUISyncEvent(&event);
    };
    ViewAbstract::SetOnPreDrag(frameNode, onPreDrag);
}

void ResetOnDragStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDragStart(frameNode);
}

void ResetOnDragEnter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDragEnter(frameNode);
}

void ResetOnDragDrop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDrop(frameNode);
}

void ResetOnDragMove(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDragMove(frameNode);
}

void ResetOnDragLeave(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDragLeave(frameNode);
}

void ResetOnDragEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDragEnd(frameNode);
}

void ResetOnPreDrag(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnPreDrag(frameNode);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

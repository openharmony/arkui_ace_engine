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

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "interfaces/native/native_type.h"
#include "interfaces/native/node/node_model.h"
#include "securec.h"

#include "base/geometry/ng/vector.h"
#include "base/geometry/shape.h"
#include "base/image/pixel_map.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curves.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/axis_event.h"
#include "core/gestures/drag_event.h"
#include "core/image/image_source_info.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/touch_event_convertor.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
int64_t CalculateModifierKeyState(const std::vector<OHOS::Ace::KeyCode>& status)
{
    int64_t modifierKeysState = 0;
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

void SetDragEventProperty(const RefPtr<OHOS::Ace::DragEvent>& info, ArkUINodeEvent& event)
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
    auto summary = info->GetSummary();
    event.dragEvent.dataTypesCount = summary.size();

    int32_t index = 0;
    int32_t maxLength = 0;
    std::vector<const char*> strList;
    std::vector<std::string> keepStr(summary.size());
    for (auto it = summary.begin(); it != summary.end(); it++) {
        int32_t keyLength = it->first.length();
        maxLength = std::max(maxLength, keyLength);
        keepStr[index] = it->first;
        strList.push_back(keepStr[index].c_str());
        ++index;
    }
    event.dragEvent.dataTypes = strList.data();
    event.dragEvent.dataTypesMaxStrLength = maxLength;
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

        SetDragEventProperty(info, event);

        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
        info->UseCustomAnimation(event.dragEvent.useCustomDropAnimation);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
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
        SetDragEventProperty(info, event);

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
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

        SetDragEventProperty(info, event);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
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
        SetDragEventProperty(info, event);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());
        event.dragEvent.unifiedData = unifiedData;
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
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

        SetDragEventProperty(info, event);
        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
        info->SetResult(static_cast<DragRet>(event.dragEvent.dragResult));
        info->SetDragBehavior(static_cast<DragBehavior>(event.dragEvent.dragBehavior));
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
        event.dragEvent.dataTypesCount = summary.size();

        int32_t index = 0;
        int32_t maxLength = 0;
        std::vector<const char*> strList;
        std::vector<std::string> keepStr(summary.size());
        for (auto it = summary.begin(); it != summary.end(); it++) {
            int32_t keyLength = it->first.length();
            maxLength = std::max(maxLength, keyLength);
            keepStr[index] = it->first;
            strList.push_back(keepStr[index].c_str());
            ++index;
        }
        event.dragEvent.dataTypes = strList.data();
        event.dragEvent.dataTypesMaxStrLength = maxLength;

        auto unifiedData = UdmfClient::GetInstance()->TransformUnifiedDataPtr(info->GetData());

        event.dragEvent.unifiedData = unifiedData;

        // Did NOT define pressCode, so will NOT pass presscode to UI.
        event.dragEvent.dragResult = static_cast<ArkUI_Int32>(info->GetResult());
        event.dragEvent.dragBehavior = static_cast<ArkUI_Int32>(info->GetDragBehavior());

        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
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
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        SendArkUIAsyncEvent(&event);
    };
    ViewAbstract::SetOnPreDrag(frameNode, onPreDrag);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

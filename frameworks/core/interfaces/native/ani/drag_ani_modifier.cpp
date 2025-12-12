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

#include "drag_ani_modifier.h"

#include "securec.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/common/udmf/udmf_client.h"
#include "core/gestures/drag_event.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif
namespace OHOS::Ace::NG {
void SetDragData(ani_ref event, ani_ref data)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
    auto unifiedDataPtr = reinterpret_cast<void*>(data);
    CHECK_NULL_VOID(unifiedDataPtr);
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->TransformUnifiedDataFromANI(unifiedDataPtr);
    CHECK_NULL_VOID(udData);
    dragEvent->SetData(udData);
}

ani_ref GetDragData(ani_ref event)
{
    ani_ref ptr = nullptr;
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_RETURN(peer, ptr);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_RETURN(dragEvent, ptr);
    auto unifiedData = dragEvent->GetData();
    CHECK_NULL_RETURN(unifiedData, ptr);
    auto unifiedDataPtr = UdmfClient::GetInstance()->TransformUnifiedDataPtr(unifiedData);
    CHECK_NULL_RETURN(unifiedDataPtr, ptr);
    return reinterpret_cast<ani_ref>(unifiedDataPtr);
}

void GetDragSummary(ani_ref event, ani_ref summaryPtr)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
    auto summary = dragEvent->GetSummary();
    UdmfClient::GetInstance()->TransformSummaryANI(summary, reinterpret_cast<void*>(summaryPtr));
}

void SetDragDropInfoPixelMap(ani_ref event, ani_ref pixelMapPtr)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
    auto pixelMapValue = reinterpret_cast<void*>(pixelMapPtr);
    CHECK_NULL_VOID(pixelMapValue);
#if defined(PIXEL_MAP_SUPPORTED)
    auto pixelMap = PixelMap::CreatePixelMap(pixelMapValue);
    CHECK_NULL_VOID(pixelMap);
    dragEvent->SetDragDropInfoPixelMap(pixelMap);
#endif
}

void SetDragDropInfoExtraInfo(ani_ref event, const char* ptr)
{
    CHECK_NULL_VOID(ptr);
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
    std::string extraInfo = ptr;
    dragEvent->SetDragDropInfoExtraInfo(extraInfo);
}

void SetDragDropInfoCustomNode(ani_ref event, ArkUINodeHandle node)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
    auto customNode = reinterpret_cast<void*>(node);
    CHECK_NULL_VOID(customNode);
    dragEvent->SetDragDropInfoCustomNode(customNode);
}

void SetDragAllowDropNull(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDisallowDropForcedly(true);
    frameNode->SetAllowDrop({});
}

void SetDragAllowDrop(ArkUINodeHandle node, char** allowDrops, ArkUI_Int32 length)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDisallowDropForcedly(false);
    std::set<std::string> allowDropSet;
    if (!allowDrops || length <= 0) {
        frameNode->SetAllowDrop(allowDropSet);
        return;
    }
    for (int32_t i = 0; i < length; i++) {
        const char* allowDrop = *(allowDrops + i);
        if (allowDrop != nullptr) {
            allowDropSet.insert(std::string(allowDrop));
        }
    }
    frameNode->SetAllowDrop(allowDropSet);
}

void SetDragPreview(ArkUINodeHandle node, ArkUIDragInfo dragInfo)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DragDropInfo info;
    #if defined(PIXEL_MAP_SUPPORTED)
    if (dragInfo.pixelMap) {
        info.pixelMap = PixelMap::CreatePixelMap(dragInfo.pixelMap);
    }
    #endif
    info.onlyForLifting = dragInfo.onlyForLifting;
    info.delayCreating = dragInfo.delayCreating;
    frameNode->SetDragPreview(info);
}

void SetDragPreviewOptions(ArkUINodeHandle node, ArkUIDragPreviewOption options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DragPreviewOption previewOptions;
    previewOptions.isScaleEnabled = options.isScaleEnabled;
    previewOptions.defaultAnimationBeforeLifting = options.defaultAnimationBeforeLifting;
    previewOptions.isMultiSelectionEnabled = options.isMultiSelectionEnabled;
    previewOptions.isNumber = options.isNumber;
    previewOptions.isDefaultShadowEnabled = options.isDefaultShadowEnabled;
    previewOptions.isDefaultRadiusEnabled = options.isDefaultRadiusEnabled;
    previewOptions.isDragPreviewEnabled = options.isDragPreviewEnabled;
    previewOptions.isDefaultDragItemGrayEffectEnabled = options.isDefaultDragItemGrayEffectEnabled;
    previewOptions.enableEdgeAutoScroll = options.enableEdgeAutoScroll;
    previewOptions.enableHapticFeedback = options.enableHapticFeedback;
    previewOptions.isMultiTiled = options.isMultiTiled;
    previewOptions.isLiftingDisabled = options.isLiftingDisabled;
    previewOptions.isTouchPointCalculationBasedOnFinalPreviewEnable =
       options.isTouchPointCalculationBasedOnFinalPreviewEnable;
    previewOptions.sizeChangeEffect = static_cast<DraggingSizeChangeEffect>(options.sizeChangeEffect);
    if (options.modifier) {
        previewOptions.onApply = [executeFunc = std::move(options.modifier)](WeakPtr<FrameNode> frameNode) {
            auto node = frameNode.Upgrade();
            CHECK_NULL_VOID(node);
            auto ptr = AceType::RawPtr(node);
            CHECK_NULL_VOID(executeFunc);
            executeFunc(ptr);
        };
    }
    if (previewOptions.isNumber) {
        previewOptions.badgeNumber = options.badgeNumber;
    } else {
        previewOptions.isShowBadge = options.isShowBadge;
    }
    frameNode->SetDragPreviewOptions(previewOptions);
}

const char* GetUdKey(ani_ref event)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_RETURN(peer, nullptr);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_RETURN(dragEvent, nullptr);
    auto& key = dragEvent->GetUdKey();
    return key.c_str();
}

ani_long CreateUnifiedDataPeer(void* data)
{
    CHECK_NULL_RETURN(data, 0);
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->TransformUnifiedDataFromANI(data);
    CHECK_NULL_RETURN(udData, 0);
    auto peerPtr = PeerUtils::CreatePeer<unifiedDataChannel_UnifiedDataPeer>();
    CHECK_NULL_RETURN(peerPtr, 0);
    peerPtr->unifiedData = udData;
    return reinterpret_cast<ani_long>(peerPtr);
}

ani_long GetUnifiedData(ani_long peer)
{
    auto unifiedDataPeer = reinterpret_cast<unifiedDataChannel_UnifiedDataPeer*>(peer);
    CHECK_NULL_RETURN(unifiedDataPeer, 0);
    auto unifiedData = unifiedDataPeer->unifiedData;
    CHECK_NULL_RETURN(unifiedData, 0);
    auto unifiedDataPtr = UdmfClient::GetInstance()->TransformUnifiedDataPtr(unifiedData);
    CHECK_NULL_RETURN(unifiedDataPtr, 0);
    return reinterpret_cast<ani_long>(unifiedDataPtr);
}

void GetPressedModifierKey(ani_long nativePtr, char*** keys, ani_int* length)
{
    CHECK_NULL_VOID(nativePtr);
    auto accessor = reinterpret_cast<Ark_DragEvent>(nativePtr);
    CHECK_NULL_VOID(accessor && accessor->dragInfo);
    CHECK_NULL_VOID(keys && length);
    auto eventKeys = accessor->dragInfo->GetPressedKeyCodes();
    auto size = static_cast<int32_t>(eventKeys.size());
    if (size <= 0) {
        return;
    }
    *length = size;
    *keys = new char* [size];
    for (auto index = 0; index < size; index++) {
        std::string keyStr;
        switch (eventKeys[index]) {
            case KeyCode::KEY_CTRL_LEFT:
            case KeyCode::KEY_CTRL_RIGHT:
                keyStr = "ctrl";
                break;
            case KeyCode::KEY_SHIFT_LEFT:
            case KeyCode::KEY_SHIFT_RIGHT:
                keyStr = "shift";
                break;
            case KeyCode::KEY_ALT_LEFT:
            case KeyCode::KEY_ALT_RIGHT:
                keyStr = "alt";
                break;
            case KeyCode::KEY_FN:
                keyStr = "fn";
                break;
            default:
                keyStr = "";
                break;
        }
        (*keys)[index] = new char[keyStr.length() + 1];
        auto result = strcpy_s((*keys)[index], keyStr.length() + 1, keyStr.c_str());
        if (result != 0) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "Drag GetPressedModifierKey error: strcpy_s with error code: %d", result);
            for (int i = 0; i <= index; i++) {
                delete[](*keys)[i];
            }
            delete[] * keys;
            *keys = nullptr;
            *length = 0;
            return;
        }
    }
}

const ArkUIAniDragModifier* GetDragAniModifier()
{
    static const ArkUIAniDragModifier impl = {
        .setDragData = OHOS::Ace::NG::SetDragData,
        .getDragData = OHOS::Ace::NG::GetDragData,
        .getDragSummary = OHOS::Ace::NG::GetDragSummary,
        .setDragDropInfoPixelMap = OHOS::Ace::NG::SetDragDropInfoPixelMap,
        .setDragDropInfoCustomNode = OHOS::Ace::NG::SetDragDropInfoCustomNode,
        .setDragDropInfoExtraInfo = OHOS::Ace::NG::SetDragDropInfoExtraInfo,
        .setDragAllowDropNull = OHOS::Ace::NG::SetDragAllowDropNull,
        .setDragAllowDrop = OHOS::Ace::NG::SetDragAllowDrop,
        .setDragPreview = OHOS::Ace::NG::SetDragPreview,
        .setDragPreviewOptions = OHOS::Ace::NG::SetDragPreviewOptions,
        .getUdKey = OHOS::Ace::NG::GetUdKey,
        .createUnifiedDataPeer = OHOS::Ace::NG::CreateUnifiedDataPeer,
        .getUnifiedData = OHOS::Ace::NG::GetUnifiedData,
        .getPressedModifierKey = OHOS::Ace::NG::GetPressedModifierKey
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
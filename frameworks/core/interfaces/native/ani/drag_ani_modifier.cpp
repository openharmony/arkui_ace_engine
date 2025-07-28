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

#include "base/log/log.h"

#include "core/components_ng/base/frame_node.h"
#include "core/common/udmf/udmf_client.h"
#include "core/gestures/drag_event.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
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

void SetDragAllowDrop(ArkUINodeHandle node, const char** allowDrops, ArkUI_Int32 length)
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

const char* GetUdKey(ani_ref event)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_RETURN(peer, nullptr);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_RETURN(dragEvent, nullptr);
    auto& key = dragEvent->GetUdKey();
    return key.c_str();
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
        .getUdKey = OHOS::Ace::NG::GetUdKey,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
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
#include "core/gestures/drag_event.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map.h"
#include "base/image/pixel_map.h"
#endif
namespace OHOS::Ace::NG {

void SetDragDropInfoPixelMap(ani_ref event, void* pixelMap)
{
    // not implemented
}

void SetDragDropInfoExtraInfo(ani_ref event, std::string& extraInfo)
{
    auto peer = reinterpret_cast<Ark_DragEvent>(event);
    CHECK_NULL_VOID(peer);
    auto dragEvent = peer->dragInfo;
    CHECK_NULL_VOID(dragEvent);
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

const ArkUIAniDragModifier* GetDragAniModifier()
{
    static const ArkUIAniDragModifier impl = {
        .setDragDropInfoPixelMap = OHOS::Ace::NG::SetDragDropInfoPixelMap,
        .setDragDropInfoCustomNode = OHOS::Ace::NG::SetDragDropInfoCustomNode,
        .setDragDropInfoExtraInfo = OHOS::Ace::NG::SetDragDropInfoExtraInfo,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
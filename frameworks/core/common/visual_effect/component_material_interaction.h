/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_COMPONENT_MATERIAL_INTERACTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_COMPONENT_MATERIAL_INTERACTION_H

#include "ui/base/geometry/offset.h"
#include "ui/base/referenced.h"

#include "core/components_ng/base/frame_node.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace {
struct LightEffectOptions;
struct ImmersiveOptions;
}

namespace OHOS::Ace::NG {

struct ControlInteractionInfo {
    std::optional<SizeF> curFrameSize = std::nullopt;
    Dimension innerMoveOffset = Dimension();
    Dimension outerMoveOffset = Dimension();
};

class ControlInteractionBase {
public:
    static void RegisterMaterialInteractionEvent(
        RefPtr<FrameNode> targetNode, const std::shared_ptr<ImmersiveOptions>& options);
    static void UninitLightEffect(FrameNode* targetNode);
    static void HandleTouchEvent(RefPtr<FrameNode> targetNode, const TouchEventInfo& info);
    static void HandleTouchDown(
        RefPtr<FrameNode> targetNode, const Offset& clickPosition, const ControlInteractionInfo& info);
    static void HandleTouchMove(
        RefPtr<FrameNode> targetNode, const Offset& clickPosition, const ControlInteractionInfo& info);
    static void HandleTouchCancel(RefPtr<FrameNode> targetNode);
    static void InitInteractionOffset(RefPtr<FrameNode> targetNode, ControlInteractionInfo& info);

private:
    static std::optional<LightEffectOptions> GetLightEffectOptions(RefPtr<FrameNode>& targetNode);
    static bool IsInteractiveEnabled(RefPtr<FrameNode>& targetNode);
    static bool IsLightEffectEnabled(RefPtr<FrameNode>& targetNode);
    static void InitLightEffect(RefPtr<FrameNode>& targetNode);
    static void UpdateLightPositionAndColor(RefPtr<FrameNode>& targetNode, float x, float y);
    static void ResetLightPositionAndColor(RefPtr<FrameNode>& targetNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_VISUAL_EFFECT_COMPONENT_MATERIAL_INTERACTION_H
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_UTILS_DRAG_ANIMATION_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_UTILS_DRAG_ANIMATION_HELPER_H

#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {

class FrameNode;
class OverlayManager;
class DragEventActuator;
struct GatherNodeChildInfo;
struct CalcResult {
    float maxDistance = 0.0f;
    float minDistance = 0.0f;
    float maxTranslation = 0.0f;
};

class ACE_FORCE_EXPORT DragAnimationHelper {
public:
    static OffsetF CalcOffsetToTarget(OffsetF curPos, OffsetF targetrPos, CalcResult& calcResult);
    static void CalcDistanceBeforeLifting(bool isGrid, CalcResult& calcResult, OffsetF gatherNodeCenter,
        const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    static void PlayGatherNodeTranslateAnimation(const RefPtr<DragEventActuator>& actuator,
        const RefPtr<OverlayManager>& overlayManager);
    static void PlayGatherAnimationBeforeLifting(const RefPtr<DragEventActuator>& actuator);
    static void PlayNodeAnimationBeforeLifting(const RefPtr<FrameNode>& frameNode);
    static void PlayGatherNodeOpacityAnimation(const RefPtr<OverlayManager>& overlayManager);
    static void PlayNodeResetAnimation(const RefPtr<DragEventActuator>& actuator);
    static void PlayGatherAnimation(const RefPtr<FrameNode>& frameNode, const RefPtr<OverlayManager>& overlayManager);
    static void ShowBadgeAnimation(const RefPtr<FrameNode>& textNode);
    static void CalcBadgeTextPosition(const RefPtr<MenuPattern>& menuPattern,
        const RefPtr<OverlayManager>& manager, const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode);
    static OffsetF CalcBadgeTextOffset(const RefPtr<MenuPattern>& menuPattern, const RefPtr<FrameNode>& imageNode,
        const RefPtr<PipelineBase>& context, int32_t badgeLength);
    static void UpdateBadgeLayoutAndRenderContext(
        const RefPtr<FrameNode>& textNode, int32_t badgeLength, int32_t childSize);
    static void UpdateGatherNodeToTop();
    static void ShowGatherAnimationWithMenu(const RefPtr<FrameNode>& menuWrapperNode);
};
}
#endif
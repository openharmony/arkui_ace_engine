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
    static void PlayGatherNodeTranslateAnimation(const RefPtr<FrameNode>& frameNode,
        const RefPtr<OverlayManager>& overlayManager);
    static void PlayGatherAnimationBeforeLifting(const RefPtr<DragEventActuator>& actuator);
    static void PlayNodeAnimationBeforeLifting(const RefPtr<FrameNode>& frameNode);
    static void PlayGatherNodeOpacityAnimation(const RefPtr<OverlayManager>& overlayManager);
    static void PlayNodeResetAnimation(const RefPtr<DragEventActuator>& actuator);
    static void PlayGatherAnimation(const RefPtr<FrameNode>& frameNode, const RefPtr<OverlayManager>& overlayManager);
    static void ShowBadgeAnimation(const RefPtr<FrameNode>& textNode);
    static void ShowMenuHideAnimation(const RefPtr<FrameNode>& imageNode, const PreparedInfoForDrag& data);
    static void CalcBadgeTextPosition(const RefPtr<MenuPattern>& menuPattern,
        const RefPtr<OverlayManager>& manager, const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode);
    static OffsetF CalcBadgeTextOffset(const RefPtr<MenuPattern>& menuPattern, const RefPtr<FrameNode>& imageNode,
        const RefPtr<PipelineBase>& context, int32_t badgeLength);
    static void UpdateBadgeLayoutAndRenderContext(
        const RefPtr<FrameNode>& textNode, int32_t badgeLength, int32_t childSize);
    static void UpdateGatherNodeToTop();
    static void ShowGatherAnimationWithMenu(const RefPtr<FrameNode>& menuWrapperNode);
    static void DoGrayedAnimation(const RefPtr<FrameNode>& frameNode, float opacity, RefPtr<InterpolatingSpring> cure);
    static void SetPreOpacity(const RefPtr<FrameNode>& preNode);
    static void DoDragStartGrayedAnimation(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> CreateImageNode(const RefPtr<PixelMap>& pixelMap);
    static RefPtr<FrameNode> CreateGatherNode(const RefPtr<FrameNode>& frameNode,
        std::vector<GatherNodeChildInfo>& gatherNodeInfo);
    static RefPtr<FrameNode> GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
        const RefPtr<DragEventActuator>& actuator, std::vector<GatherNodeChildInfo>& info);
    static RefPtr<FrameNode> CreateGatherImageNode(const RefPtr<FrameNode>& frameNode,
        GatherNodeChildInfo& gatherNodeChildInfo);
    static void MountGatherNode(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& gatherNode, const std::vector<GatherNodeChildInfo>& gatherNodeInfo);
    static void MarkDirtyNode(const RefPtr<FrameNode>& frameNode);
    static void InitGatherNodeAttr(const RefPtr<FrameNode>& gatherNode,
        const std::vector<GatherNodeChildInfo>& gatherNodeInfo);
    static bool ShowGatherNodeAnimation(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> CreateBadgeTextNode(int32_t childSize);
    static void UpdateBadgeTextNodePosition(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& textNode,
        int32_t childSize, float previewScale, OffsetF previewOffset = { 0.0f, 0.0f });
    static void ShowPreviewBadgeAnimation(
        const RefPtr<GestureEventHub>& gestureHub, const RefPtr<OverlayManager>& manager);
    static void SetImageNodeInitAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode);
    static void SetImageNodeFinishAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode);
    static void AddDragNodeCopy(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& gatherNode);
    static void ShowDragNodeCopyAnimation(const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<FrameNode>& frameNode);
    static void HideDragNodeCopyWithAnimation(const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<FrameNode>& frameNode);
    static void HideDragNodeCopy(const RefPtr<OverlayManager>& overlayManager);
    static void PreLayout(const RefPtr<FrameNode>& imageNode);
    static void SetNodeVisible(const RefPtr<FrameNode>& frameNode, bool visible);
    static void DragStartAnimation(const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager,
        const OffsetF& gatherNodeCenter, Point point, int32_t containerId);
    static void InitImageNodeProperties(const RefPtr<FrameNode>& imageNode, const RefPtr<PixelMap>& pixelMap);
    static void CreatePreviewNode(const RefPtr<FrameNode>& frameNode, RefPtr<FrameNode>& imageNode,
        float dragPreviewScale, PreparedInfoForDrag& data);
    static void MountPixelMapWithBadge(const PreparedInfoForDrag& data, const RefPtr<FrameNode>& columnNode);
    static void MountPixelMap(const RefPtr<OverlayManager>& manager, const RefPtr<GestureEventHub>& gestureHub,
        PreparedInfoForDrag& data, bool isDragPixelMap);
    static void MountPixelMapSizeContentTransition(PreparedInfoForDrag& data, const RefPtr<FrameNode>& columnNode);
    static RefPtr<RenderContext> GetMenuRenderContextFromMenuWrapper(const RefPtr<FrameNode>& menuWrapperNode);
    static RefPtr<FrameNode> GetMenuWrapperNodeFromDrag();
    static void UpdateStartAnimation(const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<NodeAnimatablePropertyFloat>& animateProperty, Point point,
        const DragDropManager::DragPreviewInfo& info, const Offset& newOffset);
    static void UpdateStartTransitionOptionAnimation(const DragDropManager::DragPreviewInfo& info);
    static void CreateTextNode(PreparedInfoForDrag& data);

private:
    static void CreateAndMountMenuPreviewNode(PreparedInfoForDrag& data, const RefPtr<FrameNode>& stackFrameNode);
};
} // namespace OHOS::Ace::NG
#endif
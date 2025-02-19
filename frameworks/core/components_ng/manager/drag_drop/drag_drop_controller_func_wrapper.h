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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_CONTROLLER_FUNC_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_CONTROLLER_FUNC_WRAPPER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/geometry/ng/vector.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class FrameNode;
struct GatherNodeChildInfo;
class ACE_FORCE_EXPORT DragControllerFuncWrapper {
public:
    static OffsetF GetUpdateDragMovePosition(int32_t containerId);
    static void ResetContextMenuDragPosition(int32_t containerId);
    static void CreatePreviewNode(RefPtr<FrameNode>& imageNode, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData);
    static OffsetF GetOriginNodeOffset(PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData);
    static OffsetF GetPixelMapScaledOffset(const OffsetF& pointPosition, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData);
    static OffsetF GetTouchPointOffset(PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData);
    static void UpdatePreviewPositionAndScale(const RefPtr<FrameNode>& imageNode, const OffsetF& frameOffset,
        float scale);
    static void UpdatePreviewAttr(const RefPtr<FrameNode>& imageNode, DragPreviewOption& dragPreviewOption);
    static void MarkDirtyNode(const RefPtr<FrameNode>& gatherNode);
    static RefPtr<Subwindow> SubWindowShow(const RefPtr<PipelineBase>& context);
    static bool TryDoDragStartAnimation(const RefPtr<Subwindow>& subWindow, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData);
    static void UpdateGatherAnimatePosition(std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
        const OffsetF& GatherNodeOffset);
    static RefPtr<FrameNode> GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
        std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData);
    static RefPtr<FrameNode> CreateGatherNode(std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
        PreparedInfoForDrag& data, PreparedAsyncCtxForAnimate& asyncCtxData);
    static void MountPixelMap(const RefPtr<OverlayManager>& manager, PreparedInfoForDrag& data,
        const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode, bool isDragPixelMap);
    static void UpdateBadgeTextNodePosition(const RefPtr<FrameNode>& textNode, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData, OffsetF previewOffset);
    static void UpdateDragPreviewScale();
    static void TransDragWindowToDragFwk(int32_t containerId);
    static Offset CalcDragMoveOffset(int32_t x, int32_t y);
    static void DoDragStartAnimation(const RefPtr<OverlayManager>& overlayManager, PreparedInfoForDrag& data,
        PreparedAsyncCtxForAnimate& asyncCtxData);
    static bool GetDragPreviewInfo(const RefPtr<OverlayManager>& overlayManager, int32_t containerId);
    static void HideDragPreviewWindow(int32_t containerId);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_CONTROLLER_FUNC_WRAPPER_H
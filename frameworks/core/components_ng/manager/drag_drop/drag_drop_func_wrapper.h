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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_FUNC_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_FUNC_WRAPPER_H

#include "core/pipeline_ng/pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
using PixelMapFinishCallback = std::function<void(RefPtr<PixelMap>, bool)>;
/* DragDropFuncWrapper as a utility class, all function calls must use containerId. */
class FrameNode;

struct PixelMapInfo {
    Rect pixelMapRect;
    PixelFormat srcPixelFormat = PixelFormat::BGRA_8888;
    PixelFormat pixelFormat = PixelFormat::UNKNOWN;
    AlphaType alphaType = AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
};

class ACE_FORCE_EXPORT DragDropFuncWrapper {
public:
    static void HandleCallback(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction,
        const OHOS::Ace::DragNotifyMsg& dragNotifyMsg, const DragAdapterStatus& dragStatus);
    static int32_t StartDragAction(std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction);
    static void SetDraggingPointerAndPressedState(int32_t currentPointerId, int32_t containerId);
    static int32_t RequestDragEndPending();
    static int32_t NotifyDragResult(int32_t requestId, int32_t result);
    static int32_t NotifyDragEndPendingDone(int32_t requestId);
    static void DecideWhetherToStopDragging(const DragPointerEvent& pointerEvent,
        const std::string& extraParams, int32_t currentPointerId, int32_t containerId);
    static void UpdateDragPreviewOptionsFromModifier(
        std::function<void(WeakPtr<FrameNode>)> applyOnNodeSync, DragPreviewOption& options);
    static void UpdatePreviewOptionDefaultAttr(DragPreviewOption& option, bool isMultiSelectionEnabled = false);
    static void UpdateExtraInfo(std::unique_ptr<JsonValue>& arkExtraInfoJson, DragPreviewOption& option);
    static void PrepareRadiusParametersForDragData(std::unique_ptr<JsonValue>& arkExtraInfoJson,
        DragPreviewOption& option);
    static void PrepareShadowParametersForDragData(std::unique_ptr<JsonValue>& arkExtraInfoJson,
        DragPreviewOption& option);
    static void ParseShadowInfo(Shadow& shadow, std::unique_ptr<JsonValue>& arkExtraInfoJson);
    static std::optional<Shadow> GetDefaultShadow();
    static std::optional<BorderRadiusProperty> GetDefaultBorderRadius();
    static float RadiusToSigma(float radius);
    static std::optional<EffectOption> BlurStyleToEffection(const std::optional<BlurStyleOption>& blurStyleOp);
    [[maybe_unused]] static double GetScaleWidth(int32_t containerId);
    static std::string GetSummaryString(const std::map<std::string, int64_t>& summary);
    static void SetExtraInfo(int32_t containerId, std::string extraInfo);
    static std::string GetAnonyString(const std::string &fullString);
    static OffsetF GetPaintRectCenter(const RefPtr<FrameNode>& frameNode, bool checkWindowBoundary = true);
    static bool IsExpandDisplay(const RefPtr<PipelineBase>& context);
    static OffsetF GetCurrentWindowOffset(const RefPtr<PipelineBase>& context);
    static OffsetF GetPaintRectCenterToScreen(const RefPtr<FrameNode>& frameNode);
    static OffsetF GetFrameNodeOffsetToScreen(const RefPtr<FrameNode>& frameNode);
    static RectF GetPaintRectToScreen(const RefPtr<FrameNode>& frameNode);
    static void UpdateNodePositionToScreen(const RefPtr<FrameNode>& frameNode, OffsetF offset);
    static void UpdateNodePositionToWindow(const RefPtr<FrameNode>& frameNode, OffsetF offset);
    static void UpdatePositionFromFrameNode(const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& frameNode,
        float width, float height);
    static void SetDragStartRequestStatus(DragStartRequestStatus dragStartRequestStatus) noexcept;
    static void ConvertPointerEvent(const TouchEvent& touchPoint, DragPointerEvent& event);
    static RefPtr<FrameNode> GetFrameNodeByKey(const RefPtr<FrameNode>& root, const std::string& key);
    static OffsetF GetFrameNodeOffsetToWindow(
        const RefPtr<FrameNode>& targetNode, const RefPtr<FrameNode>& frameNode, float width, float height);
    static OffsetF GetPointRelativeToMainWindow(const Point& point);
    static void HandleOnDragEvent(const std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction);
    static bool IsTextCategoryComponent(const std::string& frameTag);
    static RefPtr<DragDropManager> GetDragDropManagerForDragAnimation(const RefPtr<PipelineBase>& context,
        const RefPtr<PipelineBase>& nodeContext, const RefPtr<Subwindow>& subWindow,
        bool isExpandDisplay, int32_t instanceId);
    static void SetMenuSubWindowTouchable(bool touchable);
    static void HandleBackPressHideMenu();

    // multi drag
    static bool IsSelectedItemNode(const RefPtr<UINode>& uiNode);
    static bool IsBelongToMultiItemNode(const RefPtr<FrameNode>& frameNode);
    static bool CheckIsNeedGather(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> FindItemParentNode(const RefPtr<FrameNode>& frameNode);
    static RefPtr<PixelMap> GetGatherNodePreviewPixelMap(const RefPtr<FrameNode>& frameNode);
    static RefPtr<PixelMap> CreateTiledPixelMap(const RefPtr<FrameNode>& frameNode);
    static std::shared_ptr<PixelMapInfo> GetTiledPixelMapInfo(const std::vector<RefPtr<FrameNode>>& children);
    static void DrawTiledPixelMap(const RefPtr<PixelMap>& tiledPixelMap, const std::vector<RefPtr<FrameNode>>& children,
        const Rect& pixelMapRect);
    static bool IsNeedCreateTiledPixelMap(const RefPtr<FrameNode>& frameNode,
        const RefPtr<DragEventActuator> dragEventActuator, SourceType type = SourceType::NONE);

    // check global dragging status
    static bool IsGlobalStatusSuitableForDragging();
    static bool IsSelfAndParentDragForbidden(const RefPtr<FrameNode>& frameNode);
    static bool IsCurrentNodeStatusSuitableForDragging(
        const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict);
    static void RecordMenuWrapperNodeForDrag(int32_t targetId);
    static RefPtr<FrameNode> GetFrameNodeByInspectorId(const std::string& inspectorId);
    static void TrySetDraggableStateAsync(const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict);

    // modifier
    static BorderRadiusProperty GetDragFrameNodeBorderRadius(const RefPtr<FrameNode>& frameNode);
    static void ApplyNewestOptionExecutedFromModifierToNode(
        const RefPtr<FrameNode>& optionHolderNode, const RefPtr<FrameNode>& targetNode);
    static void ResetNode(const RefPtr<FrameNode>& frameNode);

    // create snapshot from inspectorId
    static RefPtr<PixelMap> GetPreviewPixelMap(const std::string& inspectorId, const RefPtr<FrameNode>& selfFrameNode);
    static RefPtr<PixelMap> GetPreviewPixelMapByInspectorId(
        const std::string& inspectorId, const RefPtr<FrameNode>& frameNode);
    static RefPtr<PixelMap> GetScreenShotPixelMap(const RefPtr<FrameNode>& frameNode);

    // create snapshot
    static bool CheckIfNeedGetThumbnailPixelMap(const RefPtr<FrameNode>& frameNode, int32_t fingerId);
    static void GetThumbnailPixelMap(
        const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback, bool isSync);
    static void GetThumbnailPixelMapAsync(const RefPtr<GestureEventHub>& gestureHub);
    static void GetThumbnailPixelMapForCustomNode(
        const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback);
    static void GetThumbnailPixelMapForCustomNodeSync(
        const RefPtr<GestureEventHub>& gestureHub, PixelMapFinishCallback pixelMapCallback);
    static float GetPixelMapScale(const RefPtr<FrameNode>& frameNode);
    static void ProcessDragDropData(const RefPtr<OHOS::Ace::DragEvent>& dragEvent, std::string& udKey,
        std::map<std::string, int64_t>& summary, std::map<std::string, int64_t>& detailedSummary, int32_t& ret);
    static void EnvelopedDataLoadParams(
        std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction, std::string& udKey);

private:
    static void GetPointerEventAction(const TouchEvent& touchPoint, DragPointerEvent& event);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_FUNC_WRAPPER_H
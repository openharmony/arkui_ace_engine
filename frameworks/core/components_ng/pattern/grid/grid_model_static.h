/*
* Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_model.h"
 
namespace OHOS::Ace::NG {

class ACE_EXPORT GridModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static RefPtr<ScrollProxy> GetOrCreateScrollBarProxy(FrameNode* frameNode);
    static void SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& columnsTemplate);
    static void SetRowsTemplate(FrameNode* frameNode, const std::string& rowsTemplate);
    static void SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& columnsGap);
    static void SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& rowsGap);
    static void SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& scrollBarMode);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& scrollBarWidth);
    static void SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& scrollBarColor);
    static void SetCachedCount(FrameNode* frameNode, int32_t cachedCount);
    static void SetShowCached(FrameNode* frameNode, bool show);
    static void SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& layoutDirection);
    static void SetMaxCount(FrameNode* frameNode, int32_t maxCount);
    static void SetMinCount(FrameNode* frameNode, int32_t minCount);
    static void SetCellLength(FrameNode* frameNode, int32_t cellLength);
    static void SetEditable(FrameNode* frameNode, bool editMode);
    static void SetMultiSelectable(FrameNode* frameNode, bool multiSelectable);
    static void SetSupportAnimation(FrameNode* frameNode, bool supportAnimation);
    static EdgeEffect GetEdgeEffect(FrameNode* frameNode);
    static bool GetAlwaysEnabled(FrameNode* frameNode);
    static void SetEdgeEffect(
        FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect, const std::optional<bool>& alwaysEnabled,
        EffectEdge edge = EffectEdge::ALL);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& value);
    static void SetAlignItems(FrameNode* frameNode, const std::optional<GridItemAlignment>& itemAlign);

    static void SetLayoutOptions(FrameNode* frameNode, GridLayoutOptions& options);
    static void SetOnScrollBarUpdate(FrameNode* frameNode, ScrollBarUpdateFunc&& value);
    static void SetOnItemDragStart(FrameNode* frameNode, std::function<void(const ItemDragInfo&, int32_t)>&& value);
    static void SetOnItemDragEnter(FrameNode* frameNode, ItemDragEnterFunc&& value);
    static void SetOnItemDragMove(FrameNode* frameNode, ItemDragMoveFunc&& value);
    static void SetOnItemDragLeave(FrameNode* frameNode, ItemDragLeaveFunc&& value);
    static void SetOnItemDrop(FrameNode* frameNode, ItemDropFunc&& value);

    static void SetGridItemTotalCount(FrameNode* frameNode, int totalCount);
    static void SetGridItemAdapterFunc(FrameNode* frameNode, std::function<void(int start, int end)>&& requestFunc);
    static void SetGridItemAdapterCallFinish(FrameNode* frameNode, int start, int end);
    static void SetGridItemGetFunc(FrameNode* frameNode, std::function<RefPtr<FrameNode>(int32_t index)>&& getFunc);
    static RefPtr<FrameNode> CreateGrid(int32_t nodeId);

    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll);
private:
    static void AddDragFrameNodeToManager(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_STATIC_H

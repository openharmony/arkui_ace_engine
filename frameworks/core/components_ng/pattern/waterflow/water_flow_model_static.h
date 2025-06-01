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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_STATIC_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static RefPtr<ScrollProxy> GetOrCreateScrollBarProxy(FrameNode* frameNode);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetRowsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static void SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetItemMinWidth(FrameNode* frameNode, const std::optional<Dimension>& minWidth);
    static void SetItemMaxWidth(FrameNode* frameNode, const std::optional<Dimension>& maxWidth);
    static void SetItemMinHeight(FrameNode* frameNode, const std::optional<Dimension>& minHeight);
    static void SetItemMaxHeight(FrameNode* frameNode, const std::optional<Dimension>& maxHeight);
    static void SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& value);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& friction);
    static void SetCachedCount(FrameNode* frameNode, const std::optional<int32_t>& value);
    static void SetShowCached(FrameNode* frameNode, bool show);
    static RefPtr<WaterFlowSections> GetOrCreateWaterFlowSections(FrameNode* frameNode);
    static void ResetSections(FrameNode* frameNode);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin);
    static void SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetLayoutMode(FrameNode* frameNode, WaterFlowLayoutMode mode);
    static void SetFooter(FrameNode* frameNode, const RefPtr<NG::UINode>& footer);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_STATIC_H
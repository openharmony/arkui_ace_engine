/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowModelNG : public WaterFlowModel {
public:
    void Create() override;
    void SetFooter(std::function<void()>&& footer) override;
    void SetFooterWithFrameNode(const RefPtr<NG::UINode>& footer) override;
    RefPtr<ScrollControllerBase> CreateScrollController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;
    void SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy) override;
    void SetLayoutMode(WaterFlowLayoutMode mode) override;

    void SetColumnsTemplate(const std::string& value) override;
    void SetRowsTemplate(const std::string& value) override;

    void SetItemMinWidth(const Dimension& minWidth) override;
    void SetItemMinHeight(const Dimension& minHeight) override;
    void SetItemMaxWidth(const Dimension& maxWidth) override;
    void SetItemMaxHeight(const Dimension& maxHeight) override;

    void SetColumnsGap(const Dimension& value) override;
    void SetRowsGap(const Dimension& value) override;

    void SetLayoutDirection(FlexDirection value) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;

    void SetOnReachStart(OnReachEvent&& onReachStart) override;
    void SetOnReachEnd(OnReachEvent&& onReachEnd) override;
    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin) override;
    void SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll) override;
    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart) override;
    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop) override;
    void SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex) override;

    void SetFriction(double friction) override;
    void SetCachedCount(int32_t value, bool show = false) override;
    void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge = EffectEdge::ALL) override;

    void SetScrollBarMode(DisplayMode value) override;
    void SetScrollBarColor(const std::string& value) override;
    void SetScrollBarWidth(const std::string& value) override;
    void SetSyncLoad(bool syncLoad) override;

    RefPtr<WaterFlowSections> GetOrCreateWaterFlowSections() override;
    void ResetSections() override;
    void ParseResObjFriction(const RefPtr<ResourceObject>& resObj) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<ScrollControllerBase> GetOrCreateController(FrameNode* frameNode);
    static void SetColumnsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetRowsTemplate(FrameNode* frameNode, const std::string& value);
    static void SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled);
    static void SetColumnsGap(FrameNode* frameNode, const Dimension& value);
    static void SetRowsGap(FrameNode* frameNode, const Dimension& value);
    static void SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetItemMinWidth(FrameNode* frameNode, const std::optional<Dimension>& minWidth);
    static void SetItemMaxWidth(FrameNode* frameNode, const std::optional<Dimension>& maxWidth);
    static void SetItemMinHeight(FrameNode* frameNode, const std::optional<Dimension>& minHeight);
    static void SetItemMaxHeight(FrameNode* frameNode, const std::optional<Dimension>& maxHeight);
    static void SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& value);
    static void SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt);
    static void SetFriction(FrameNode* frameNode, const std::optional<double>& friction);
    static FlexDirection GetLayoutDirection(FrameNode* frameNode);
    static std::string GetColumnsTemplate(FrameNode* frameNode);
    static std::string GetRowsTemplate(FrameNode* frameNode);
    static float GetColumnsGap(FrameNode* frameNode);
    static float GetRowsGap(FrameNode* frameNode);
    static NestedScrollOptions GetNestedScroll(FrameNode* frameNode);
    static void SetCachedCount(FrameNode* frameNode, const std::optional<int32_t>& value);
    static int32_t GetCachedCount(FrameNode* frameNode);
    static void SetShowCached(FrameNode* frameNode, bool show);
    static int32_t GetShowCached(FrameNode* frameNode);
    static void SetEdgeEffect(FrameNode* frameNode, EdgeEffect edgeEffect, bool alwaysEnabled,
        EffectEdge edge = EffectEdge::ALL);
    static float GetFriction(FrameNode* frameNode);
    static void SetScrollBarMode(FrameNode* frameNode, DisplayMode value);
    static int32_t GetScrollBarMode(FrameNode* frameNode);
    static void SetScrollBarColor(FrameNode* frameNode, const std::string& value);
    static uint32_t GetScrollBarColor(FrameNode* frameNode);
    static void SetScrollBarWidth(FrameNode* frameNode, const std::string& value);
    static float GetScrollBarWidth(FrameNode* frameNode);
    static int32_t GetEdgeEffect(FrameNode* frameNode);
    static int32_t GetEdgeEffectAlways(FrameNode* frameNode);
    static Dimension GetItemMinWidth(FrameNode* frameNode);
    static Dimension GetItemMaxWidth(FrameNode* frameNode);
    static Dimension GetItemMinHeight(FrameNode* frameNode);
    static Dimension GetItemMaxHeight(FrameNode* frameNode);
    static RefPtr<WaterFlowSections> GetOrCreateWaterFlowSections(FrameNode* frameNode);
    static void ResetSections(FrameNode* frameNode);
    static bool GetScrollEnabled(FrameNode* frameNode);
    static void SetOnScroll(FrameNode* frameNode, std::function<void(Dimension, ScrollState)>&& onScroll);
    static void SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart);
    static void SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop);
    static void SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin);
    static void SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex);
    static void SetScrollToIndex(FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment);
    static void SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart);
    static void SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd);
    static void SetWaterflowFooter(FrameNode* frameNode, FrameNode* footerNode);
    static void SetWaterflowFooterWithFrameNode(FrameNode* frameNode, const RefPtr<NG::UINode>& footer);
    static bool hasFooter(FrameNode* frameNode);
    static void SetFlingSpeedLimit(FrameNode* frameNode, double maxSpeed);
    static void SetScroller(FrameNode* frameNode, RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy);
    static void SetLayoutMode(FrameNode* frameNode, WaterFlowLayoutMode mode);
    static WaterFlowLayoutMode GetLayoutMode(FrameNode* frameNode);
    static void ParseResObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void SetFooter(FrameNode* frameNode, std::function<void()>&& footer);
    static void SetSyncLoad(FrameNode* frameNode, bool syncLoad);
    static bool GetSyncLoad(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_MODEL_NG_H
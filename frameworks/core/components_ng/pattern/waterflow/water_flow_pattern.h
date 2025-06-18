/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_algorithm_base.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_accessibility_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_content_modifier.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(WaterFlowPattern, ScrollablePattern);

public:
    bool UpdateCurrentOffset(float delta, int32_t source) override;
    bool IsScrollable() const override;
    bool IsAtTop() const override;
    bool IsAtBottom(bool considerRepeat = false) const override;
    bool IsAtTopWithDelta() const override;
    bool IsAtBottomWithDelta() const override;
    bool IsReverse() const override;
    bool IsVerticalReverse() const;
    bool hasFooter()
    {
        return footer_.Upgrade() != nullptr;
    };
    OverScrollOffset GetOverScrollOffset(double delta) const override;
    void UpdateScrollBarOffset() override;

    using LayoutMode = WaterFlowLayoutMode;
    void SetLayoutMode(LayoutMode mode);
    LayoutMode GetLayoutMode() const
    {
        return layoutInfo_->Mode();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<WaterFlowLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<WaterFlowEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<WaterFlowAccessibilityProperty>();
    }

    RefPtr<ScrollableController> GetPositionController() const
    {
        return positionController_;
    }

    void TriggerModifyDone();

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    bool UpdateStartIndex(int32_t index);

    void AddFooter(const RefPtr<NG::UINode>& footer);

    void ResetLayoutInfo();

    bool GetItemStart() const
    {
        return layoutInfo_->itemStart_;
    }

    bool GetItemEnd() const
    {
        return layoutInfo_->itemEnd_;
    }

    int32_t GetBeginIndex() const
    {
        return layoutInfo_->startIndex_;
    }

    int32_t GetEndIndex() const
    {
        return layoutInfo_->endIndex_;
    }

    int32_t GetChildrenCount() const;

    float GetTotalOffset() const override
    {
        return -layoutInfo_->Offset();
    }

    int32_t GetRows() const;

    int32_t GetColumns() const;

    void OnAnimateStop() override;
    /**
     * @brief LayoutMode::SLIDING_WINDOW doesn't support scrollTo and animateTo
     */
    void ScrollTo(float position) override;
    /**
     * @brief LayoutMode::SLIDING_WINDOW doesn't support animateTo
     */
    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll,
        bool useTotalOffset = true) override;

    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override;

    void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START,
        std::optional<float> extraOffset = std::nullopt) override;

    double GetStoredOffset() const
    {
        return layoutInfo_->storedOffset_;
    }

    void SetRestoreOffset(double restoreOffset)
    {
        layoutInfo_->restoreOffset_ = restoreOffset;
    }

    void SetScrollAlign(ScrollAlign align)
    {
        layoutInfo_->align_ = align;
    }

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    Rect GetItemRect(int32_t index) const override;
    int32_t GetItemIndex(double x, double y) const override;

    RefPtr<WaterFlowSections> GetSections() const;
    RefPtr<WaterFlowSections> GetOrCreateWaterFlowSections();
    void ResetSections();

    /**
     * @brief Callback function when Sections data has changed.
     *
     * @param start the index of the first modified section.
     */
    void OnSectionChanged(int32_t start);

    void DumpAdvanceInfo() override;
    void GetEventDumpInfo() override;
    void GetEventDumpInfo(std::unique_ptr<JsonValue>& json) override;

    void SetPreloadList(std::list<int32_t>&& preload)
    {
        preloadItems_ = std::move(preload);
    }
    bool PreloadListEmpty() const
    {
        return preloadItems_.empty();
    }
    std::list<int32_t>&& MovePreloadList()
    {
        return std::move(preloadItems_);
    }
    void SetCacheLayoutAlgo(const RefPtr<WaterFlowLayoutBase>& algo)
    {
        cacheLayout_ = algo;
    }
    const RefPtr<WaterFlowLayoutBase>& GetCacheLayoutAlgo() const
    {
        return cacheLayout_;
    }

    void NotifyDataChange(int32_t index, int32_t count) override;

    // ------------------------ Focus adapter --------------------------------
    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }
    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;
    std::function<bool(int32_t)> GetScrollIndexAbility() override;
    // ------------------------ Focus ^^^ --------------------------------
    void BeforeCreateLayoutWrapper() override;

    void AddSectionChangeStartPos(int32_t start)
    {
        sectionChangeStartPos_.emplace_back(start);
        MarkDirtyNodeSelf();
    }

    float GetPrevOffset() const
    {
        return prevOffset_;
    }

    int32_t GetDefaultCachedCount() const
    {
        return layoutInfo_->defCachedCount_;
    }

    SizeF GetChildrenExpandedSize() override;

    bool OnAttachAdapter(const RefPtr<FrameNode>& node, const RefPtr<UINode>& child) override
    {
        node->AddChild(child);
        return true;
    }

private:
    DisplayMode GetDefaultScrollBarDisplayMode() const override
    {
        return DisplayMode::OFF;
    }
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta = true) override;

    void TriggerPostLayoutEvents();

    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    SizeF GetContentSize() const;
    void MarkDirtyNodeSelf();
    void OnScrollEndCallback() override;
    bool ScrollToTargetIndex(int32_t index);
    bool NeedRender();
    void FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd) override;
    void FireOnScrollIndex(bool indexChanged, const ScrollIndexFunc& onScrollIndex);
    void DumpInfoAddSections();

    /**
     * @param step FocusStep
     * @param currentFocusNode the currently focused FlowItem.
     * @return WeakPtr<FocusHub> of the next FlowItem to focus on.
     */
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);

    std::optional<int32_t> targetIndex_;
    RefPtr<WaterFlowLayoutInfoBase> layoutInfo_ = WaterFlowLayoutInfoBase::Create(LayoutMode::TOP_DOWN);
    RefPtr<WaterFlowSections> sections_;

    float prevOffset_ = 0.0f;
    SizeF lastSize_;
    std::pair<int32_t, int32_t> itemRange_ = { -1, -1 };
    WeakPtr<UINode> footer_;
    // for keepVisiableContentPosition mode temporarily.
    bool keepContentPosition_ = true;

    // clip padding of WaterFlow
    RefPtr<WaterFlowContentModifier> contentModifier_;

    std::list<int32_t> preloadItems_;
    RefPtr<WaterFlowLayoutBase> cacheLayout_;

    std::vector<int32_t> sectionChangeStartPos_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H

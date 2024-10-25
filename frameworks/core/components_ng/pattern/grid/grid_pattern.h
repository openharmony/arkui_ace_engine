/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

#include "core/components_ng/pattern/grid/grid_accessibility_property.h"
#include "core/components_ng/pattern/grid/grid_content_modifier.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_paint_method.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

struct GridItemIndexInfo {
    int32_t mainIndex = -1;
    int32_t crossIndex = -1;
    int32_t mainSpan = -1;
    int32_t crossSpan = -1;
    int32_t mainStart = -1;
    int32_t mainEnd = -1;
    int32_t crossStart = -1;
    int32_t crossEnd = -1;
};

class ACE_EXPORT GridPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(GridPattern, ScrollablePattern);

public:
    GridPattern() = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GridLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    void BeforeCreateLayoutWrapper() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<GridAccessibilityProperty>();
    }

    bool IsScrollable() const override
    {
        return isConfigScrollable_;
    }

    DisplayMode GetDefaultScrollBarDisplayMode() const override;

    void SetMultiSelectable(bool multiSelectable)
    {
        multiSelectable_ = multiSelectable;
    }

    bool MultiSelectable() const
    {
        return multiSelectable_;
    }

    void SetSupportAnimation(bool supportAnimation)
    {
        supportAnimation_ = supportAnimation;
    }

    bool SupportAnimation() const
    {
        return supportAnimation_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        auto property = GetLayoutProperty<GridLayoutProperty>();
        if (!property) {
            return ScopeFocusAlgorithm();
        }
        return ScopeFocusAlgorithm(property->IsVertical(), true, ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto grid = wp.Upgrade();
                if (grid) {
                    nextFocusNode = grid->GetNextFocusNode(step, currFocusNode);
                }
            });
    }

    int32_t GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode) override;

    void ScrollToFocusNodeIndex(int32_t index) override;

    std::pair<std::function<bool(float)>, Axis> GetScrollOffsetAbility() override;

    std::function<bool(int32_t)> GetScrollIndexAbility() override;

    bool ScrollToNode(const RefPtr<FrameNode>& focusFrameNode) override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<GridEventHub>();
    }

    bool UsResRegion() override
    {
        return false;
    }

    const GridLayoutInfo& GetGridLayoutInfo() const
    {
        return info_;
    }

    /* caution when using mutable reference */
    GridLayoutInfo& GetMutableLayoutInfo()
    {
        return info_;
    }

    void ResetGridLayoutInfo()
    {
        info_.lineHeightMap_.clear();
        info_.gridMatrix_.clear();
        info_.endIndex_ = info_.startIndex_ - 1;
        info_.endMainLineIndex_ = 0;
        info_.ResetPositionFlags();
        info_.irregularItemsPosition_.clear();
        info_.clearStretch_ = true;
    }

    void SetIrregular(bool value)
    {
        irregular_ = value;
    }

    void ResetPositionFlags()
    {
        info_.ResetPositionFlags();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    bool UpdateCurrentOffset(float offset, int32_t source) override;

    bool IsAtTop() const override
    {
        return info_.reachStart_;
    }

    bool IsAtBottom() const override
    {
        return info_.offsetEnd_;
    }

    OverScrollOffset GetOverScrollOffset(double delta) const override;
    void GetEndOverScrollIrregular(OverScrollOffset& offset, float delta) const;

    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override;

    bool UpdateStartIndex(int32_t index);

    bool UpdateStartIndex(int32_t index, ScrollAlign align);

    float GetTotalOffset() const override
    {
        return EstimateHeight();
    }

    float GetTotalHeight() const override;

    void OnAnimateStop() override;

    void AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll = false,
        bool useTotalOffset = true) override;
    void ScrollTo(float position) override;

    void ScrollBy(float offset);

    ScrollAlign GetDefaultScrollAlign() const override
    {
        return ScrollAlign::AUTO;
    }

    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) override;

    void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::AUTO,
        std::optional<float> extraOffset = std::nullopt) override;
    void AnimateToTarget(ScrollAlign align, const RefPtr<LayoutAlgorithmWrapper>& algo);
    bool AnimateToTargetImpl(ScrollAlign align, const RefPtr<LayoutAlgorithmWrapper>& algo);

    int32_t GetOriginalIndex() const;
    int32_t GetCrossCount() const;
    int32_t GetChildrenCount() const;
    void MoveItems(int32_t itemIndex, int32_t insertIndex);
    void ClearDragState();
    float EstimateHeight() const;
    float GetAverageHeight() const;

    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void BuildGridLayoutInfo(std::unique_ptr<JsonValue>& json);
    void BuildScrollAlignInfo(std::unique_ptr<JsonValue>& json);

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    Rect GetItemRect(int32_t index) const override;
    int32_t GetItemIndex(double x, double y) const override;

    bool IsNeedInitClickEventRecorder() const override
    {
        return true;
    }

    const std::list<GridPreloadItem>& GetPreloadItemList() const
    {
        return preloadItemList_;
    }

    void SetPreloadItemList(std::list<GridPreloadItem>&& list)
    {
        preloadItemList_ = std::move(list);
    }

    std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() override;

    void StopAnimate() override;

    bool IsPredictOutOfRange(int32_t index) const;

    bool IsReverse() const override;

    Axis GetAxis() const override
    {
        return info_.axis_;
    }

private:
    /**
     * @brief calculate where startMainLine_ should be after spring animation.
     * @return main axis position relative to viewport, positive when below viewport.
     */
    float GetEndOffset();
    float GetMainGap() const;
    float GetAllDelta();
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta) override;
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    SizeF GetContentSize() const;
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    std::pair<int32_t, int32_t> GetNextIndexByStep(
        int32_t curMainIndex, int32_t curCrossIndex, int32_t curMainSpan, int32_t curCrossSpan, FocusStep step);
    WeakPtr<FocusHub> SearchFocusableChildInCross(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t maxCrossCount,
        int32_t curMainIndex = -1, int32_t curCrossIndex = -1);
    WeakPtr<FocusHub> SearchIrregularFocusableChild(int32_t tarMainIndex, int32_t tarCrossIndex);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarCrossIndex, int32_t tarIndex = -1);
    std::unordered_set<int32_t> GetFocusableChildCrossIndexesAt(int32_t tarMainIndex);
    void ScrollToFocusNode(const WeakPtr<FocusHub>& focusNode);
    void FlushFocusOnScroll(const GridLayoutInfo& gridLayoutInfo);
    std::pair<bool, bool> IsFirstOrLastFocusableChild(int32_t curMainIndex, int32_t curCrossIndex);
    std::pair<FocusStep, FocusStep> GetFocusSteps(int32_t curMainIndex, int32_t curCrossIndex, FocusStep step);
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(KeyCode code);

    void ClearMultiSelect() override;
    bool IsItemSelected(const GestureEvent& info) override;
    void MultiSelectWithoutKeyboard(const RectF& selectedZone) override;
    void UpdateScrollBarOffset() override;
    void UpdateRectOfDraggedInItem(int32_t insertIndex);

    void ProcessEvent(bool indexChanged, float finalOffset);
    void MarkDirtyNodeSelf();
    void OnScrollEndCallback() override;

    /**
     * @brief preform a layout if LayoutInfo is out of sync before calculating spring positions.
     * INVARIANT: overScroll always enabled in the scope of this function. Because this function only runs in the
     * context of spring animation.
     */
    void SyncLayoutBeforeSpring();

    void FireOnScrollStart() override;
    void FireOnReachStart(const OnReachEvent& onReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd) override;
    void FireOnScrollIndex(bool indexChanged, const ScrollIndexFunc& onScrollIndex);

    inline bool UseIrregularLayout() const;

    int32_t CalcIntersectAreaInTargetDirectionShadow(GridItemIndexInfo itemIndexInfo, bool isFindInMainAxis);
    double GetNearestDistanceFromChildToCurFocusItemInMainAxis(int32_t targetIndex, GridItemIndexInfo itemIndexInfo);
    double GetNearestDistanceFromChildToCurFocusItemInCrossAxis(int32_t targetIndex, GridItemIndexInfo itemIndexInfo);
    void ResetAllDirectionsStep();

    std::string GetIrregularIndexesString() const;

    bool supportAnimation_ = false;
    bool isConfigScrollable_ = false;

    bool scrollable_ = true;
    bool forceOverScroll_ = false;

    RefPtr<GridContentModifier> gridContentModifier_;

    float endHeight_ = 0.0f;
    bool isLeftStep_ = false;
    bool isRightStep_ = false;
    bool isUpStep_ = false;
    bool isDownStep_ = false;
    bool isLeftEndStep_ = false;
    bool isRightEndStep_ = false;
    bool isSmoothScrolling_ = false;
    bool irregular_ = false; // true if LayoutOptions require running IrregularLayout

    ScrollAlign scrollAlign_ = ScrollAlign::AUTO;
    std::optional<int32_t> targetIndex_;
    std::pair<std::optional<float>, std::optional<float>> scrollbarInfo_;
    GridItemIndexInfo curFocusIndexInfo_;
    GridLayoutInfo scrollGridLayoutInfo_;
    GridLayoutInfo info_;
    std::list<GridPreloadItem> preloadItemList_; // list of GridItems to build preemptively in IdleTask
    ACE_DISALLOW_COPY_AND_MOVE(GridPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

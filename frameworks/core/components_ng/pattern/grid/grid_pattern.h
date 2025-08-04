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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

#include "core/components_ng/pattern/grid/grid_accessibility_property.h"
#include "core/components_ng/pattern/grid/grid_content_modifier.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_focus.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
class InspectorFilter;


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

    RefPtr<PaintProperty> CreatePaintProperty() override;

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

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

    int32_t GetFocusNodeIndex(const RefPtr<FocusHub>& focusNode) override;

    void ScrollToFocusNodeIndex(int32_t index) override;

    ScrollOffsetAbility GetScrollOffsetAbility() override;

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

    bool IsAtBottom(bool considerRepeat = false) const override
    {
        return considerRepeat ? (info_.offsetEnd_ && info_.repeatDifference_ == 0) : info_.offsetEnd_;
    }

    bool IsAtTopWithDelta() const override
    {
        return info_.reachStart_ || LessNotEqual(EstimateHeight(), 0);
    }

    bool IsAtBottomWithDelta() const override
    {
        return info_.offsetEnd_ || GreatNotEqual(EstimateHeight() + info_.lastMainSize_, GetTotalHeight());
    }

    bool IsFadingBottom() const override;

    OverScrollOffset GetOverScrollOffset(double delta) const override;
    void GetEndOverScrollIrregular(OverScrollOffset& offset, float delta) const;

    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override;

    bool UpdateStartIndex(int32_t index);

    bool UpdateStartIndex(int32_t index, ScrollAlign align);

    double GetTotalOffset() const override
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
    void GetEventDumpInfo() override;
    void GetEventDumpInfo(std::unique_ptr<JsonValue>& json) override;
    void BuildGridLayoutInfo(std::unique_ptr<JsonValue>& json);
    void BuildScrollAlignInfo(std::unique_ptr<JsonValue>& json);

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    Rect GetItemRect(int32_t index) const override;
    int32_t GetItemIndex(double x, double y) const override;

    bool HasPreloadItemList() const
    {
        return !preloadItemList_.empty();
    }

    std::list<GridPreloadItem> MovePreloadItemList()
    {
        return std::move(preloadItemList_);
    }

    void SetPreloadItemList(std::list<GridPreloadItem>&& list)
    {
        preloadItemList_ = std::move(list);
    }

    std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() override;

    void StopAnimate() override;

    bool IsPredictOutOfCacheRange(int32_t index) const;

    bool IsReverse() const override;

    Axis GetAxis() const override
    {
        return info_.axis_;
    }

    int32_t GetDefaultCachedCount() const
    {
        return info_.defCachedCount_;
    }

    void ResetFocusedIndex()
    {
        focusHandler_.ResetFocusIndex();
    }

    std::optional<int32_t> GetFocusedIndex() const
    {
        return focusHandler_.GetFocusIndex();
    }

    SizeF GetChildrenExpandedSize() override;

    void HandleOnItemFocus(int32_t index);

    void OnColorModeChange(uint32_t colorMode) override;
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

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);

    void ClearMultiSelect() override;
    bool IsItemSelected(float offsetX, float offsetY) override;
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

    void FireOnScrollStart(bool withPerfMonitor = true) override;
    void FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd) override;
    void FireOnScrollIndex(bool indexChanged, const ScrollIndexFunc& onScrollIndex);
    void ReportOnItemGridEvent(const std::string& event);
    int32_t OnInjectionEvent(const std::string& command) override;

    inline bool UseIrregularLayout() const;

    std::string GetIrregularIndexesString() const;

    bool supportAnimation_ = false;
    bool isConfigScrollable_ = false;
    bool scrollable_ = true;
    bool preSpring_ = false; // true if during SyncLayoutBeforeSpring task.
    bool isSmoothScrolling_ = false;
    bool irregular_ = false; // true if LayoutOptions require running IrregularLayout

    RefPtr<GridContentModifier> gridContentModifier_;

    float endHeight_ = 0.0f;
    float mainSizeChanged_ = 0.0f;
    KeyEvent keyEvent_;
    GridFocus focusHandler_ { *this, info_ };

    // index of first and last GridItem in viewport
    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;

    ScrollAlign scrollAlign_ = ScrollAlign::AUTO;
    std::optional<int32_t> targetIndex_;
    std::pair<std::optional<float>, std::optional<float>> scrollbarInfo_;
    std::unique_ptr<GridLayoutInfo> infoCopy_; // legacy impl to save independent data for animation.
    GridLayoutInfo info_;
    std::list<GridPreloadItem> preloadItemList_; // list of GridItems to build preemptively in IdleTask

    ACE_DISALLOW_COPY_AND_MOVE(GridPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_PATTERN_H

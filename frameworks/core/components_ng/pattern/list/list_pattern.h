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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

#include <tuple>
#include "base/log/log_wrapper.h"
#include "core/animation/chain_animation.h"
#include "core/components_ng/pattern/list/list_accessibility_property.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_content_modifier.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_paint_method.h"
#include "core/components_ng/pattern/list/list_position_map.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

struct ListItemGroupPara {
    int32_t lanes = -1;
    int32_t itemEndIndex = -1;
    int32_t displayStartIndex = -1;
    int32_t displayEndIndex = -1;
    bool hasHeader = false;
    bool hasFooter = false;
};

struct ListScrollTarget {
    int32_t index = -1;
    float extraOffset = 0.0f;
    ScrollAlign align = ScrollAlign::START;
    float targetOffset;
};

class ListPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(ListPattern, ScrollablePattern);

public:
    ListPattern() : ScrollablePattern(EdgeEffect::SPRING, false) {}
    ~ListPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ListLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ListEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ListAccessibilityProperty>();
    }

    bool UsResRegion() override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    bool UpdateCurrentOffset(float offset, int32_t source) override;

    DisplayMode GetDefaultScrollBarDisplayMode() const override;

    int32_t GetStartIndex() const
    {
        return startIndex_;
    }

    int32_t GetEndIndex() const
    {
        return endIndex_;
    }

    int32_t GetMaxListItemIndex() const
    {
        return maxListItemIndex_;
    }

    int32_t GetMaxIndexByRepeat() const
    {
        return maxListItemIndex_ + repeatDifference_;
    }

    int32_t GetStartIndexInItemPosition() const
    {
        return itemPosition_.empty() ? -1 : itemPosition_.begin()->first;
    }

    int32_t GetEndIndexInItemPosition() const
    {
        return itemPosition_.empty() ? -1 : itemPosition_.rbegin()->first;
    }

    bool IsScrollable() const override
    {
        return isScrollable_;
    }

    void SetMaintainVisibleContentPosition(bool enabled)
    {
        maintainVisibleContentPosition_ = enabled;
    }

    bool GetMaintainVisibleContentPosition()
    {
        return maintainVisibleContentPosition_;
    }

    void MarkNeedReEstimateOffset()
    {
        needReEstimateOffset_ = true;
    }

    void NotifyDataChange(int32_t index, int32_t count) override;

    bool IsAtTop() const override;
    bool IsAtBottom(bool considerRepeat = false) const override;
    void OnTouchDown(const TouchEventInfo& info) override;
    OverScrollOffset GetOutBoundaryOffset(float delta, bool useChainDelta = true) const;
    OverScrollOffset GetOverScrollOffset(double delta) const override;
    float GetOffsetWithLimit(float offset) const override;
    virtual void HandleScrollBarOutBoundary();

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

    bool LayoutItemInGroupForFocus(int32_t indexInList, int32_t nextIndexInGroup, int32_t curIndexInGroup,
        ListItemGroupPara listItemGroupPara, int32_t maxListItemIndex);

    ScrollOffsetAbility GetScrollOffsetAbility() override;

    std::function<bool(int32_t)> GetScrollIndexAbility() override;

    bool ScrollToNode(const RefPtr<FrameNode>& focusFrameNode) override;

    const ListLayoutAlgorithm::PositionMap& GetItemPosition() const
    {
        return itemPosition_;
    }

    float GetTotalOffset() const override
    {
        return currentOffset_;
    }

    float GetContentStartOffset() const override
    {
        return contentStartOffset_;
    }

    RefPtr<ScrollControllerBase> GetPositionController() const
    {
        return positionController_;
    }

    int32_t ProcessAreaVertical(double& x, double& y, Rect& groupRect, int32_t& index,
        RefPtr<ListItemGroupPattern> groupItemPattern) const;
    int32_t ProcessAreaHorizontal(double& x, double& y, Rect& groupRect, int32_t& index,
        RefPtr<ListItemGroupPattern> groupItemPattern) const;
    void TriggerModifyDone();

    float GetTotalHeight() const override;

    // scroller
    void ScrollTo(float position) override;
    void ScrollToIndex(int32_t index, bool smooth = false, ScrollAlign align = ScrollAlign::START,
        std::optional<float> extraOffset = std::nullopt) override;
    void ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth = false,
        ScrollAlign align = ScrollAlign::START);
    bool CheckTargetValid(int32_t index, int32_t indexInGroup);
    void ScrollPage(bool reverse, bool smooth = false,
        AccessibilityScrollType scrollType = AccessibilityScrollType::SCROLL_FULL) override;
    void ScrollBy(float offset);
    bool AnimateToTarget(int32_t index, std::optional<int32_t> indexInGroup, ScrollAlign align);
    Offset GetCurrentOffset() const;
    Rect GetItemRect(int32_t index) const override;
    int32_t GetItemIndex(double x, double y) const override;
    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const;
    ListItemIndex GetItemIndexInGroup(double x, double y) const;
    bool GetGroupItemIndex(double x, double y, RefPtr<FrameNode> itemFrameNode, int32_t& index,
        ListItemIndex& itemIndex) const;
    void OnAnimateStop() override;
    float GetMainContentSize() const override
    {
        return contentMainSize_;
    }
    int32_t GetLanes() const
    {
        return lanes_;
    }

    void CalculateCurrentOffset(float delta, const ListLayoutAlgorithm::PositionMap& recycledItemPosition);
    void UpdatePosMap(const ListLayoutAlgorithm::PositionMap& itemPos);
    void UpdateScrollBarOffset() override;
    virtual bool IsNeedAddContentOffset(bool isContentLessThanSize)
    {
        return !IsScrollSnapAlignCenter() || childrenSize_;
    }
    // chain animation
    void SetChainAnimation();
    void SetChainAnimationOptions(const ChainAnimationOptions& options);
    float FlushChainAnimation(float dragOffset);
    void ProcessDragStart(float startPosition);
    void ProcessDragUpdate(float dragOffset, int32_t source);
    float GetChainDelta(int32_t index) const;

    // multiSelectable
    void SetMultiSelectable(bool multiSelectable)
    {
        multiSelectable_ = multiSelectable;
    }

    void SetSwiperItem(WeakPtr<ListItemPattern> swiperItem);
    WeakPtr<ListItemPattern> GetSwiperItem()
    {
        if (!swiperItem_.Upgrade()) {
            return nullptr;
        }
        return swiperItem_;
    }
    void SetSwiperItemEnd(WeakPtr<ListItemPattern> swiperItem)
    {
        if (swiperItem == swiperItem_) {
            canReplaceSwiperItem_ = true;
        }
    }
    bool IsCurrentSwiperItem(WeakPtr<ListItemPattern> swiperItem)
    {
        if (!swiperItem_.Upgrade()) {
            return true;
        }
        return swiperItem == swiperItem_;
    }
    bool CanReplaceSwiperItem()
    {
        auto listItemPattern = swiperItem_.Upgrade();
        if (!listItemPattern) {
            canReplaceSwiperItem_ = true;
            return canReplaceSwiperItem_;
        }
        auto host = listItemPattern->GetHost();
        if (!host || !host->IsOnMainTree()) {
            canReplaceSwiperItem_ = true;
            return canReplaceSwiperItem_;
        }
        return canReplaceSwiperItem_;
    }

    void SetPredictSnapOffset(float predictSnapOffset)
    {
        predictSnapOffset_ = predictSnapOffset;
    }

    bool StartSnapAnimation(SnapAnimationOptions snapAnimationOptions) override;

    bool ScrollToSnapIndex(SnapDirection snapDirection, ScrollSnapAlign scrollSnapAlign);

    int32_t GetEndIndexExcludeEndOffset();

    int32_t GetStartIndexExcludeStartOffset();

    void StartListSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity);

    SnapType GetSnapType() override
    {
        auto snapAlign = GetScrollSnapAlign();
        return snapAlign != ScrollSnapAlign::NONE ? SnapType::LIST_SNAP : SnapType::NONE_SNAP;
    }

    ScrollSnapAlign GetScrollSnapAlign() const;

    void SetLastSnapTargetIndex(int32_t lastSnapTargetIndex) override
    {
        lastSnapTargetIndex_ = lastSnapTargetIndex;
    }

    std::optional<int32_t> GetLastSnapTargetIndex() override
    {
        return lastSnapTargetIndex_;
    }

    void ResetLastSnapTargetIndex() override
    {
        lastSnapTargetIndex_.reset();
    }

    int32_t GetItemIndexByPosition(float xOffset, float yOffset);

    void SetPredictLayoutParam(std::optional<ListPredictLayoutParam> param)
    {
        predictLayoutParam_ = param;
    }
    std::optional<ListPredictLayoutParam> GetPredictLayoutParam() const
    {
        return predictLayoutParam_;
    }

    void SetPredictLayoutParamV2(std::optional<ListPredictLayoutParamV2> param)
    {
        predictLayoutParamV2_ = param;
    }

    std::optional<ListPredictLayoutParamV2> GetPredictLayoutParamV2() const
    {
        return predictLayoutParamV2_;
    }

    void CloseAllSwipeActions(OnFinishFunc&&);

    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void GetEventDumpInfo() override;
    void GetEventDumpInfo(std::unique_ptr<JsonValue>& json) override;

    void SetNeedToUpdateListDirectionInCardStyle(bool isNeedToUpdateListDirection)
    {
        isNeedToUpdateListDirection_ = isNeedToUpdateListDirection;
    }

    bool IsNeedToUpdateListDirectionInCardStyle() const
    {
        return isNeedToUpdateListDirection_;
    }

    std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() override;

    void SetItemPressed(bool isPressed, int32_t id)
    {
        if (isPressed) {
            pressedItem_.emplace(id);
        } else {
            pressedItem_.erase(id);
        }
    }

    RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize();
    void SetListChildrenMainSize(float defaultSize, const std::vector<float>& mainSize);
    virtual void OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag);
    void ResetChildrenSize();
    bool ListChildrenSizeExist()
    {
        return static_cast<bool>(childrenSize_);
    }
    void UpdateChildPosInfo(int32_t index, float delta, float sizeChange);

    SizeF GetChildrenExpandedSize() override;

    inline int32_t GetItemStartIndex()
    {
        return itemStartIndex_;
    }

    void SetIsNeedDividerAnimation(bool isNeedDividerAnimation)
    {
        isNeedDividerAnimation_ = isNeedDividerAnimation;
    }

    bool IsStackFromEnd() const
    {
        return isStackFromEnd_;
    }

    void SetRepeatDifference(int32_t repeatDifference)
    {
        repeatDifference_ = repeatDifference;
    }

    bool IsOutOfBoundary(bool useCurrentDelta = true) override;

protected:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    virtual bool ScrollListForFocus(int32_t nextIndex, int32_t curIndex, int32_t nextIndexInGroup);
    virtual void AdjustScrollPosition(int32_t nextIndex, int32_t curIndex);
    void MarkDirtyNodeSelf();

    bool OnScrollCallback(float offset, int32_t source) override;
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void SetChainAnimationToPosMap();
    void SetChainAnimationLayoutAlgorithm(
        RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty);

    virtual void OnScrollVisibleContentChange(const RefPtr<ListEventHub>& listEventHub, bool indexChanged);
    virtual float GetScrollUpdateFriction(float overScroll);
    virtual ScrollAlign GetScrollToNodeAlign()
    {
        return ScrollAlign::AUTO;
    }
    virtual void OnMidIndexChanged();
    virtual float GetStartOverScrollOffset(float offset, float startMainPos) const;
    virtual float GetEndOverScrollOffset(float offset, float endMainPos, float startMainPos) const;
    void SetLayoutAlgorithmParams(
        const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty);

    bool isFadingEdge_ = false;
    int32_t maxListItemIndex_ = 0;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t centerIndex_ = -1;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float spaceWidth_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float contentStartOffset_ = 0.0f;
    float contentEndOffset_ = 0.0f;

    float currentDelta_ = 0.0f;
    bool smooth_ = false;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::optional<float> predictSnapOffset_;
    std::optional<float> predictSnapEndPos_;
    ScrollAlign scrollAlign_ = ScrollAlign::START;
    bool isNeedCheckOffset_ = false;
    bool isScrollable_ = true;

    ListLayoutAlgorithm::PositionMap itemPosition_;
    RefPtr<ListPositionMap> posMap_;
    RefPtr<ListChildrenMainSize> childrenSize_;

    RefPtr<ChainAnimation> chainAnimation_;

    RefPtr<Scrollable> scrollable_;

    int32_t itemStartIndex_ = 0;
    float scrollSnapVelocity_ = 0.0f;
    bool isStackFromEnd_ = true;
private:
    void CheckAndUpdateAnimateTo(float relativeOffset, float prevOffset);
    void OnScrollEndCallback() override;
    void FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd) override;
    void FireOnScrollIndex(bool indexChanged, const OnScrollIndexEvent& onScrollIndex);
    void ChangeAxis(RefPtr<UINode> node);
    bool HandleTargetIndex(bool isJump);
    float CalculateTargetPos(float startPos, float endPos);
    bool CheckDataChangeOutOfStart(int32_t index, int32_t count, int32_t startIndex, int32_t endIndex);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(const KeyEvent& event);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarGroupIndex);
    WeakPtr<FocusHub> ScrollAndFindFocusNode(int32_t nextIndex, int32_t curIndex, int32_t& nextIndexInGroup,
        int32_t curIndexInGroup, int32_t moveStep, FocusStep step);
    bool HandleDisplayedChildFocus(int32_t nextIndex, int32_t curIndex);
    bool ScrollListItemGroupForFocus(int32_t nextIndex, int32_t curIndex, int32_t& nextIndexInGroup,
        int32_t curIndexInGroup, int32_t moveStep, FocusStep step, bool isScrollIndex);
    ScrollAlign CalcAlignForFocusToGroupItem(int32_t moveStep, FocusStep step) const;
    int32_t CalcNextIndexInGroup(int32_t nextIndex, int32_t curIndex, int32_t curIndexInGroup, int32_t moveStep,
        ListItemGroupPara& nextListItemGroupPara) const;
    void VerifyFocusIndex(int32_t& nextIndex, int32_t& nextIndexInGroup, const ListItemGroupPara& param);
    int32_t GetNextLineFocusIndex(int32_t currIndex);

    SizeF GetContentSize() const;
    void ProcessEvent(bool indexChanged, float finalOffset, bool isJump);
    void FireOnScrollWithVersionCheck(float finalOffset, OnScrollEvent& onScroll);
    void CheckScrollable();
    void HandleScrollEffect(float offset);
    void StartDefaultOrCustomSpringMotion(float start, float end, const RefPtr<InterpolatingSpring>& curve);
    bool IsScrollSnapAlignCenter() const;
    void SetLayoutAlgorithmJumpAlign(
        const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty);
    void SetLayoutAlgorithmSnapParam(const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm);
    void SetChainAnimationCallback();
    bool NeedScrollSnapAlignEffect() const;
    ScrollAlign GetInitialScrollAlign() const;
    bool GetListItemAnimatePos(float startPos, float endPos, ScrollAlign align, float& targetPos);
    bool GetListItemGroupAnimatePosWithoutIndexInGroup(int32_t index, float startPos, float endPos,
        ScrollAlign align, float& targetPos);
    bool GetListItemGroupAnimatePosWithIndexInGroup(int32_t index, int32_t indexInGroup, float startPos,
        ScrollAlign align, float& targetPos);
    bool GetFadingEdge(RefPtr<ScrollablePaintProperty>& paintProperty);

    // multiSelectable
    void ClearMultiSelect() override;
    bool IsItemSelected(float offsetX, float offsetY) override;
    void MultiSelectWithoutKeyboard(const RectF& selectedZone) override;
    void HandleCardModeSelectedEvent(
        const RectF& selectedZone, const RefPtr<FrameNode>& itemGroupNode, const OffsetF& groupOffset);

    // focus
    bool LayoutListForFocus(int32_t nextIndex, int32_t curIndex);
    bool IsLayout(int32_t index, std::optional<int32_t> indexInGroup, ScrollAlign align);
    int32_t GetNextMoveStepForMultiLanes(int32_t curIndex, FocusStep focuseStep, bool isVertical, int32_t& nextIndex);
    WeakPtr<FocusHub> GetNextFocusNodeInList(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    bool IsListItemGroupByIndex(int32_t index);
    WeakPtr<FocusHub> FindChildFocusNodeByIndex(int32_t tarMainIndex, const FocusStep& step);
    void DetermineSingleLaneStep(
        FocusStep step, bool isVertical, int32_t curIndex, int32_t& moveStep, int32_t& nextIndex);
    void DetermineMultiLaneStep(
        FocusStep step, bool isVertical, int32_t curIndex, int32_t& moveStep, int32_t& nextIndex);
    int32_t GetCurrentFocusIndex(const RefPtr<Pattern>& curPattern);
    void AdjustFocusStepForRtl(FocusStep& step, bool isVertical);
    int32_t GetCrossAxisNextIndex(int32_t curIndex, bool isVertical, int32_t moveStep, FocusStep step);
    const ListItemInfo* GetPosition(int32_t index) const;
    bool NextPositionBlocksMove(const ListItemInfo* curPos, const ListItemInfo* nextPos, bool isVertical) const;
    int32_t AdjustNextIndexForEdgeRow(int32_t nextIndex, int32_t moveStep, int32_t curIndex);
    bool IsListItem(const WeakPtr<FocusHub>& focusNode);
    void HandleIndexToBounds(int32_t& nextIndex, bool& loopFlag);

    void DrivenRender(const RefPtr<LayoutWrapper>& layoutWrapper);
    ListItemGroupPara GetListItemGroupParameter(const RefPtr<FrameNode>& node);
    bool IsListItemGroup(int32_t listIndex, RefPtr<FrameNode>& node);
    void GetListItemGroupEdge(bool& groupAtStart, bool& groupAtEnd) const;
    void RefreshLanesItemRange();
    void UpdateListDirectionInCardStyle();
    bool UpdateStartListItemIndex();
    bool UpdateEndListItemIndex();
    bool CalculateJumpOffset();
    float UpdateTotalOffset(const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, bool isJump);
    RefPtr<ListContentModifier> listContentModifier_;
    void CreatePositionInfo(std::unique_ptr<JsonValue>& json);
    void ReportOnItemListEvent(const std::string& event);
    void ReportOnItemListScrollEvent(const std::string& event, int32_t startindex, int32_t endindex);
    int32_t OnInjectionEvent(const std::string& command) override;
    float prevStartOffset_ = 0.f;
    float prevEndOffset_ = 0.f;
    float currentOffset_ = 0.0f;
    bool maintainVisibleContentPosition_ = false;
    std::optional<int32_t> lastSnapTargetIndex_;

    bool crossMatchChild_ = false;
    bool snapTrigOnScrollStart_ = false;
    bool snapTrigByScrollBar_ = false;

    std::optional<int32_t> jumpIndexInGroup_;
    std::optional<int32_t> targetIndexInGroup_;
    std::optional<bool> isLayoutListForFocus_; // Flag for only do Layout.
    std::optional<ListScrollTarget> scrollTarget_;
    bool paintStateFlag_ = false;
    bool isFramePaintStateValid_ = false;

    ListLayoutAlgorithm::PositionMap cachedItemPosition_;
    float listTotalHeight_ = 0.0f;

    std::map<int32_t, int32_t> lanesItemRange_;
    std::set<int32_t> pressedItem_;
    int32_t lanes_ = 1;
    int32_t laneIdx4Divider_ = 0;
    float laneGutter_ = 0.0f;
    bool dragFromSpring_ = false;
    RefPtr<SpringProperty> springProperty_;
    std::optional<ChainAnimationOptions> chainAnimationOptions_;

    bool isOritationListenerRegisted_ = false;

    // ListItem swiperAction
    WeakPtr<ListItemPattern> swiperItem_;
    bool canReplaceSwiperItem_ = true;

    RefPtr<SpringMotion> scrollToIndexMotion_;
    RefPtr<SpringMotion> scrollSnapMotion_;

    bool isScrollEnd_ = false;
    bool needReEstimateOffset_ = false;
    std::optional<ListPredictLayoutParam> predictLayoutParam_;
    std::optional<ListPredictLayoutParamV2> predictLayoutParamV2_;

    bool isNeedToUpdateListDirection_ = false;
    bool startIndexChanged_ = false;
    bool endIndexChanged_ = false;

    ListItemIndex startInfo_ = {-1, -1, -1};
    ListItemIndex endInfo_ = {-1, -1, -1};
    bool isNeedDividerAnimation_ = true;
    int32_t repeatDifference_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

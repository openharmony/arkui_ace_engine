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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

#include <tuple>
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
    bool IsAtBottom() const override;
    void OnTouchDown(const TouchEventInfo& info) override;
    OverScrollOffset GetOutBoundaryOffset(bool useCurrentDelta) const;
    OverScrollOffset GetOverScrollOffset(double delta) const override;
    float GetOffsetWithLimit(float offset) const override;
    void HandleScrollBarOutBoundary();

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        auto property = GetLayoutProperty<ListLayoutProperty>();
        if (!property) {
            return {};
        }
        return ScopeFocusAlgorithm(property->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL, true,
            ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto list = wp.Upgrade();
                if (list) {
                    nextFocusNode = list->GetNextFocusNode(step, currFocusNode);
                }
            });
    }

    std::pair<std::function<bool(float)>, Axis> GetScrollOffsetAbility() override;

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
    bool OnScrollSnapCallback(double targetOffset, double velocity) override;

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
    void OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag);
    void ResetChildrenSize();
    bool ListChildrenSizeExist()
    {
        return static_cast<bool>(childrenSize_);
    }
    bool CanOverScroll(int32_t source) override
    {
        auto canOverScroll = (IsScrollableSpringEffect() && source != SCROLL_FROM_AXIS && source != SCROLL_FROM_BAR &&
            IsScrollable() && (!ScrollableIdle() || animateOverScroll_ || animateCanOverScroll_) &&
            (IsAtBottom() || IsAtTop()));
        if (canOverScroll != lastCanOverScroll_) {
            lastCanOverScroll_ = canOverScroll;
            AddScrollableFrameInfo(source);
        }
        return canOverScroll;
    }
    void UpdateChildPosInfo(int32_t index, float delta, float sizeChange);
private:

    bool IsNeedInitClickEventRecorder() const override
    {
        return true;
    }

    void OnScrollEndCallback() override;
    void FireOnReachStart(const OnReachEvent& onReachStart) override;
    void FireOnReachEnd(const OnReachEvent& onReachEnd) override;
    void FireOnScrollIndex(bool indexChanged, const OnScrollIndexEvent& onScrollIndex);
    void OnModifyDone() override;
    void ChangeAxis(RefPtr<UINode> node);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    float CalculateTargetPos(float startPos, float endPos);

    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool HandleDirectionKey(const KeyEvent& event);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    WeakPtr<FocusHub> GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarGroupIndex);
    WeakPtr<FocusHub> ScrollAndFindFocusNode(int32_t nextIndex, int32_t curIndex, int32_t& nextIndexInGroup,
        int32_t curIndexInGroup, int32_t moveStep, FocusStep step);
    bool ScrollListForFocus(int32_t nextIndex, int32_t curIndex, int32_t nextIndexInGroup);
    bool ScrollListItemGroupForFocus(int32_t nextIndex, int32_t& nextIndexInGroup, int32_t curIndexInGroup,
        int32_t moveStep, FocusStep step, bool isScrollIndex);

    void MarkDirtyNodeSelf();
    SizeF GetContentSize() const;
    void ProcessEvent(bool indexChanged, float finalOffset, bool isJump);
    void CheckScrollable();
    bool IsOutOfBoundary(bool useCurrentDelta = true) override;
    bool OnScrollCallback(float offset, int32_t source) override;
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;
    void HandleScrollEffect(float offset);
    void StartDefaultOrCustomSpringMotion(float start, float end, const RefPtr<InterpolatingSpring>& curve);
    bool IsScrollSnapAlignCenter() const;
    void SetChainAnimationCallback();
    void SetChainAnimationToPosMap();
    void SetChainAnimationLayoutAlgorithm(
        RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm, RefPtr<ListLayoutProperty> listLayoutProperty);
    bool NeedScrollSnapAlignEffect() const;
    ScrollAlign GetScrollAlignByScrollSnapAlign() const;
    bool GetListItemAnimatePos(float startPos, float endPos, ScrollAlign align, float& targetPos);
    bool GetListItemGroupAnimatePosWithoutIndexInGroup(int32_t index, float startPos, float endPos,
        ScrollAlign align, float& targetPos);
    bool GetListItemGroupAnimatePosWithIndexInGroup(int32_t index, int32_t indexInGroup, float startPos,
        ScrollAlign align, float& targetPos);

    // multiSelectable
    void ClearMultiSelect() override;
    bool IsItemSelected(const GestureEvent& info) override;
    void MultiSelectWithoutKeyboard(const RectF& selectedZone) override;
    void HandleCardModeSelectedEvent(
        const RectF& selectedZone, const RefPtr<FrameNode>& itemGroupNode, float itemGroupTop);

    void DrivenRender(const RefPtr<LayoutWrapper>& layoutWrapper);
    ListItemGroupPara GetListItemGroupParameter(const RefPtr<FrameNode>& node);
    bool IsListItemGroup(int32_t listIndex, RefPtr<FrameNode>& node);
    void GetListItemGroupEdge(bool& groupAtStart, bool& groupAtEnd) const;
    void RefreshLanesItemRange();
    void UpdateListDirectionInCardStyle();
    bool UpdateStartListItemIndex();
    bool UpdateEndListItemIndex();
    float GetStartOverScrollOffset(float offset, float startMainPos) const;
    float GetEndOverScrollOffset(float offset, float endMainPos, float startMainPos) const;
    float UpdateTotalOffset(const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, bool isJump);
    RefPtr<ListContentModifier> listContentModifier_;
    void CreatePositionInfo(std::unique_ptr<JsonValue>& json);
    int32_t maxListItemIndex_ = 0;
    int32_t startIndex_ = -1;
    int32_t endIndex_ = -1;
    int32_t centerIndex_ = -1;
    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float prevStartOffset_ = 0.f;
    float prevEndOffset_ = 0.f;
    float currentOffset_ = 0.0f;
    float spaceWidth_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float contentStartOffset_ = 0.0f;
    float contentEndOffset_ = 0.0f;
    bool maintainVisibleContentPosition_ = false;

    float currentDelta_ = 0.0f;
    bool crossMatchChild_ = false;
    bool smooth_ = false;
    float scrollSnapVelocity_ = 0.0f;
    bool snapTrigOnScrollStart_ = false;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> jumpIndexInGroup_;
    std::optional<int32_t> targetIndex_;
    std::optional<int32_t> targetIndexInGroup_;
    std::optional<ListScrollTarget> scrollTarget_;
    std::optional<float> predictSnapOffset_;
    std::optional<float> predictSnapEndPos_;
    ScrollAlign scrollAlign_ = ScrollAlign::START;
    bool isScrollable_ = true;
    bool paintStateFlag_ = false;
    bool isFramePaintStateValid_ = false;
    bool isNeedCheckOffset_ = false;

    ListLayoutAlgorithm::PositionMap itemPosition_;
    RefPtr<ListPositionMap> posMap_;
    RefPtr<ListChildrenMainSize> childrenSize_;
    float listTotalHeight_ = 0.0f;

    std::map<int32_t, int32_t> lanesItemRange_;
    std::set<int32_t> pressedItem_;
    int32_t lanes_ = 1;
    float laneGutter_ = 0.0f;
    // chain animation
    RefPtr<ChainAnimation> chainAnimation_;
    bool dragFromSpring_ = false;
    RefPtr<SpringProperty> springProperty_;
    std::optional<ChainAnimationOptions> chainAnimationOptions_;

    bool isOritationListenerRegisted_ = false;

    // ListItem swiperAction
    WeakPtr<ListItemPattern> swiperItem_;
    bool canReplaceSwiperItem_ = true;

    RefPtr<SpringMotion> scrollToIndexMotion_;
    RefPtr<SpringMotion> scrollSnapMotion_;
    RefPtr<Scrollable> scrollable_;

    bool isScrollEnd_ = false;
    bool needReEstimateOffset_ = false;
    std::optional<ListPredictLayoutParam> predictLayoutParam_;
    std::optional<ListPredictLayoutParamV2> predictLayoutParamV2_;

    bool isNeedToUpdateListDirection_ = false;

    bool endIndexChanged_ = false;

    ListItemIndex startInfo_ = {-1, -1, -1};
    ListItemIndex endInfo_ = {-1, -1, -1};
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

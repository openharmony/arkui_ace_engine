/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H

#include <functional>
#include <limits>
#include <list>

#include "core/animation/bilateral_spring_adapter.h"
#include "core/animation/simple_spring_chain.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/refresh/render_refresh_target.h"
#include "core/components/scroll/scroll_edge_effect.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/render_list_item.h"
#include "core/components_v2/list/list_item_generator.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {

using UpdateBuilderFunc = std::function<void(const Dimension&, const Dimension&)>;

enum class ListEvents {
    NONE = 0,
    SCROLL,
    SCROLL_STOP,
    REACH_START,
    REACH_END,
};

enum class ItemPositionState {
    AHEAD_OF_VIEWPORT = 0,
    IN_VIEWPORT,
    BEHIND_VIEWPORT,
};

class RenderList : public RenderNode, public RenderRefreshTarget {
    DECLARE_ACE_TYPE(V2::RenderList, RenderNode, RenderRefreshTarget);

public:
    using ScrollEventBack = std::function<void(void)>;
    static RefPtr<RenderNode> Create();

    RenderList() = default;
    ~RenderList() override;

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void PaintChild(const RefPtr<RenderNode>& child, RenderContext& context, const Offset& offset) override;

    void OnPaintFinish() override;

    bool IsUseOnly() override;

    template<class T>
    T MakeValue(double mainValue, double crossValue) const
    {
        return vertical_ ? T(crossValue, mainValue) : T(mainValue, crossValue);
    }

    double GetMainSize(const Size& size) const
    {
        return vertical_ ? size.Height() : size.Width();
    }

    double GetCrossSize(const Size& size) const
    {
        return vertical_ ? size.Width() : size.Height();
    }

    double GetMainAxis(const Offset& size) const
    {
        return vertical_ ? size.GetY() : size.GetX();
    }

    double GetCrossAxis(const Offset& size) const
    {
        return vertical_ ? size.GetX() : size.GetY();
    }

    double GetSpace() const
    {
        return spaceWidth_;
    }

    double GetStartIndex() const
    {
        return startIndex_;
    }

    double GetIndex() const
    {
        return initialIndex_;
    }

    bool IsVertical() const
    {
        return vertical_;
    }

    Axis GetAxis() const
    {
        return vertical_ ? Axis::VERTICAL : Axis::HORIZONTAL;
    }

    bool GetEditable() const
    {
        if (component_) {
            return component_->GetEditMode();
        }
        return false;
    }

    bool GetLinkage() const
    {
        if (component_) {
            return component_->GetChainAnimation();
        }
        return false;
    }

    void RegisterItemGenerator(WeakPtr<ListItemGenerator>&& listItemGenerator)
    {
        itemGenerator_ = std::move(listItemGenerator);
    }

    int32_t GetRestoreId() const
    {
        return component_ ? component_->GetRestoreId() : -1;
    }

    bool GetMultiSelectable() const
    {
        return isMultiSelectable_;
    }

    void RemoveAllItems();

    void JumpToIndex(int32_t idx);

    void AnimateTo(const Dimension& position, float duration, const RefPtr<Curve>& curve);

    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth);

    void ScrollPage(bool reverse, bool smooth);

    void ScrollBy(double pixelX, double pixelY);

    RefPtr<Component> GetComponent() override
    {
        return component_;
    }

    Offset GetCurrentOffset() const
    {
        return vertical_ ? Offset(0.0, -currentOffset_) : Offset(-currentOffset_, 0.0);
    }

    double GetRealMainSize() const
    {
        return realMainSize_;
    }

    double GetEstimatedHeight() const
    {
        return estimatedHeight_;
    }

    Offset GetLastOffset() const
    {
        return vertical_ ? Offset(0.0, lastOffset_) : Offset(lastOffset_, 0.0);
    }

    Offset CurrentOffset();

    Dimension GetListSpace() const
    {
        return listSpace_;
    }

    const UpdateBuilderFunc& GetUpdateBuilderFuncId() const
    {
        return updateBuilder_;
    }

    void SetUpdateBuilderFuncId(const UpdateBuilderFunc& updateBuilder)
    {
        updateBuilder_ = updateBuilder;
    }

    const OnItemDragEnterFunc& GetOnItemDragEnter() const
    {
        return onItemDragEnter_;
    }

    const OnItemDragMoveFunc& GetOnItemDragMove() const
    {
        return onItemDragMove_;
    }

    const OnItemDragLeaveFunc& GetOnItemDragLeave() const
    {
        return onItemDragLeave_;
    }

    const OnItemDropFunc& GetOnItemDrop() const
    {
        return onItemDrop_;
    }

    void SetPreTargetRenderList(const RefPtr<RenderList>& preTargetRenderList)
    {
        preTargetRenderList_ = preTargetRenderList;
    }

    const RefPtr<RenderList>& GetPreTargetRenderList() const
    {
        return preTargetRenderList_;
    }

    void SetBetweenItemAndBuilder(const Offset& betweenItemAndBuilder)
    {
        betweenItemAndBuilder_ = betweenItemAndBuilder;
    }

    const Offset& GetBetweenItemAndBuilder() const
    {
        return betweenItemAndBuilder_;
    }

    size_t CalculateSelectedIndex(
        const RefPtr<RenderList> targetRenderlist, const GestureEvent& info, Size& selectedItemSize);
    int32_t CalculateInsertIndex(
        const RefPtr<RenderList> targetRenderlist, const GestureEvent& info, Size selectedItemSize);

    void HandleAxisEvent(const AxisEvent& event) override;

    bool IsAxisScrollable(AxisDirection direction) override;

    int32_t RequestNextFocus(bool vertical, bool reverse);

    // distribute
    std::string ProvideRestoreInfo() override;

    void SetFocusIndex(int32_t focusIndex)
    {
        focusIndex_ = focusIndex;
    }

    int32_t GetLanes() const
    {
        return lanes_;
    }

    bool IsFramePaintStateValid() const
    {
        return isFramePaintStateValid_;
    }

    void MarkFramePaintStateValid(bool isValid)
    {
        isFramePaintStateValid_ = isValid;
    }

    bool GetPaintState() const
    {
        return paintStateFlag_;
    }

    void SetPaintState(bool flag)
    {
        paintStateFlag_ = flag;
        MarkFramePaintStateValid(true);
    }

protected:
    void UpdateAccessibilityAttr();
    void UpdateAccessibilityScrollAttr();
    void UpdateAccessibilityVisible();
    bool HandleActionScroll(bool forward);
    LayoutParam MakeInnerLayout();
    LayoutParam MakeInnerLayoutForLane();
    Size SetItemsPosition(double mainSize);
    Size SetItemsPositionForLaneList(double mainSize);
    bool HandleOverScroll();
    bool UpdateScrollPosition(double offset, int32_t source);

    bool TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
        TouchTestResult& result) override;
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    double ApplyLayoutParam();
    double LayoutOrRecycleCurrentItems(double mainSize);
    void BackwardLayoutForCache(size_t& backwardLayoutIndex, double& backwardLayoutOffset);
    double LayoutOrRecycleCurrentItemsForCache(double mainSize);
    double LayoutOrRecycleCurrentItemsForLaneList(double mainSize);
    RefPtr<RenderListItem> RequestAndLayoutNewItem(size_t index, double currMainPos, bool forward = true);

    RefPtr<RenderListItem> RequestListItem(size_t index);
    void RecycleListItem(size_t index);
    size_t FindItemStartIndex(size_t index);
    size_t GetItemRelativeIndex(size_t index);
    size_t TotalCount();
    size_t FindPreviousStickyListItem(size_t index);

    void OnItemDelete(const RefPtr<RenderListItem>& item);
    void OnItemSelect(const RefPtr<RenderListItem>& item);
    size_t GetIndexByListItem(const RefPtr<RenderListItem>& item) const;
    bool PrepareRawRecognizer();
    void OnSelectedItemMove(double position);
    void OnSelectedItemStopMoving(bool canceled);

    void UpdateStickyListItem(const RefPtr<RenderListItem>& newStickyItem, size_t newStickyItemIndex,
        const RefPtr<RenderListItem>& nextStickyItem);

    void ApplyPreviousStickyListItem(size_t index, bool forceLayout = false);

    double GetCurrentPosition() const;
    void AdjustOffset(Offset& delta, int32_t source);
    bool IsOutOfBoundary() const;
    void ResetEdgeEffect();
    void SetEdgeEffectAttribute();
    void CalculateMainScrollExtent(double curMainPos, double mainSize);
    bool GetCurMainPosAndMainSize(double &curMainPos, double &mainSize);

    // notify start position in global main axis when drag start
    void ProcessDragStart(double startPosition);
    // notify drag offset in global main axis
    void ProcessDragUpdate(double dragOffset);
    // notify scroll over
    void ProcessScrollOverCallback(double velocity);
    void InitChainAnimation(int32_t nodeCount);
    double GetChainDelta(int32_t index) const;
    size_t GetNearChildByPosition(double mainOffset) const;
    double FlushChainAnimation();
    const RefPtr<SpringProperty>& GetOverSpringProperty() const
    {
        return overSpringProperty_;
    }
    const SpringChainProperty& GetChainProperty() const
    {
        return chainProperty_;
    }
    void CalculateLanes();
    void ModifyLaneLength(const std::optional<std::pair<Dimension, Dimension>>& laneConstrain);
    ItemPositionState GetItemPositionState(double curMainPos, double lastItemMainSize);
    double GetLaneLengthInPx(const Dimension& length);
    double CalculateLaneCrossOffset(double crossSize, double childCrossSize);
    void RequestNewItemsAtEnd(double& curMainPos, double mainSize);
    void RequestNewItemsAtEndForLaneList(double& curMainPos, double mainSize);
    void RequestNewItemsAtStart();
    void RequestNewItemsAtStartForLaneList();

    RefPtr<ListComponent> component_;

    static constexpr size_t INVALID_CHILD_INDEX = std::numeric_limits<size_t>::max();
    static constexpr size_t INITIAL_CHILD_INDEX = INVALID_CHILD_INDEX - 1;

    size_t startIndex_ = INITIAL_CHILD_INDEX;
    size_t initialIndex_ = INITIAL_CHILD_INDEX;
    std::list<RefPtr<RenderListItem>> items_;

    int32_t midDisplayIndex_ = 0;
    double spaceWidth_ = 0.0;
    double lastOffset_ = 0.0;
    double startIndexOffset_ = 0.0;
    double startMainPos_ = 0.0;
    double endMainPos_ = 0.0;
    double currentOffset_ = 0.0;
    double mainSize_ = 0.0;
    double mainScrollExtent_ = 0.0;

    bool useEstimateCurrentOffset_ = false;
    bool reachStart_ = false;
    bool reachEnd_ = false;
    bool isOutOfBoundary_ = false;
    bool vertical_ = true;
    bool fixedMainSizeByLayoutParam_ = true;
    bool fixedMainSize_ = true;
    bool fixedCrossSize_ = false;
    bool chainAnimation_ = false;
    bool chainOverScroll_ = false;
    double currentDelta_ = 0.0;
    bool inLinkRefresh_ = false;

    SpringChainProperty chainProperty_;
    RefPtr<SpringProperty> overSpringProperty_;
    RefPtr<BilateralSpringAdapter> chainAdapter_;
    RefPtr<SimpleSpringChain> chain_;
    RefPtr<Animator> animator_;

    size_t firstDisplayIndex_ = INITIAL_CHILD_INDEX;
    size_t lastDisplayIndex_ = INITIAL_CHILD_INDEX;
    size_t dragStartIndexPending_ = 0;
    size_t dragStartIndex_ = 0;
    bool hasActionScroll_ = false;
    bool isActionByScroll_ = false;
    ScrollEventBack scrollFinishEventBack_;

    WeakPtr<ListItemGenerator> itemGenerator_;
    RefPtr<Scrollable> scrollable_;
    RefPtr<ScrollEdgeEffect> scrollEffect_;
    RefPtr<ScrollBarProxy> scrollBarProxy_; // user defined scroll bar
    RefPtr<ScrollBar> scrollBar_;           // system defined scroll bar

    size_t currentStickyIndex_ = INITIAL_CHILD_INDEX;
    RefPtr<RenderListItem> currentStickyItem_;

    size_t targetIndex_ = INITIAL_CHILD_INDEX;
    size_t selectedItemIndex_ = INITIAL_CHILD_INDEX;
    RefPtr<RenderListItem> selectedItem_;
    double selectedItemMainAxis_ = 0.0;
    double targetMainAxis_ = 0.0;
    RefPtr<RawRecognizer> rawRecognizer_;
    double lastPos_ = 0.0f;
    bool autoScrollingForItemMove_ = false;
    bool movingForward_ = false;
    double dipScale_ = 1.0;
    double offset_ = 0.0;

    size_t insertItemIndex_ = INITIAL_CHILD_INDEX;
    Offset betweenItemAndBuilder_;
    RefPtr<RenderListItem> selectedDragItem_;

    Offset mouseStartOffset_;
    Offset mouseEndOffset_;
    int32_t focusIndex_ = 0;
    int32_t scrollBarOpacity_ = 0;
    double prevOffset_ = 0.0;
    double prevMainPos_ = 0.0;
    double estimatedHeight_ = 0.0;
    bool isRightToLeft_ = false;
    bool drivenRender_ = false;

private:
    int32_t lanes_ = -1;
    double minLaneLength_ = -1.0; // in vertical list, [minLaneLength_] means the minimum width of a lane
    double maxLaneLength_ = -1.0; // in vertical list, [maxLaneLength_] means the maximum width of a lane
    bool isLaneList_ = false;
    bool IsReachStart();
    void HandleListEvent();
    bool ActionByScroll(bool forward, ScrollEventBack scrollEventBack);
    void ModifyActionScroll();
    void InitScrollBarProxy();
    void InitScrollBar();
    void SetScrollBarCallback();
    void LayoutChild(RefPtr<RenderNode> child, double referencePos = 0.0, bool forward = true);
    static void SetChildPosition(RefPtr<RenderNode> child, const Offset& offset);
    void AddChildItem(RefPtr<RenderNode> child);
    void AdjustForReachEnd(double mainSize, double curMainPos);
    void AdjustForReachStart(double &curMainPos);
    Dimension listSpace_;
    double realMainSize_ = 0.0; // Real size of main axis.
    size_t startCachedCount_ = 0;
    size_t endCachedCount_ = 0;
    size_t cachedCount_ = 0;
    StickyStyle sticky_ = StickyStyle::NONE;

    void CreateDragDropRecognizer();
    RefPtr<RenderListItem> FindCurrentListItem(const Point& point);

    RefPtr<GestureRecognizer> dragDropGesture_;
    RefPtr<RenderList> preTargetRenderList_;
    OnItemDragStartFunc onItemDragStart_;
    OnItemDragEnterFunc onItemDragEnter_;
    OnItemDragMoveFunc onItemDragMove_;
    OnItemDragLeaveFunc onItemDragLeave_;
    OnItemDropFunc onItemDrop_;

    UpdateBuilderFunc updateBuilder_;

    bool HandleMouseEvent(const MouseEvent& event) override;
    bool isMultiSelectable_ = false;
    bool forbidMultiSelect_ = false;
    void ClearMultiSelect();
    bool mouseIsHover_ = false;
    bool hasHeight_ = false;
    bool hasWidth_ = false;
    bool isAxisResponse_ = true;
    ScrollState scrollState_;
    bool paintStateFlag_ = false;
    bool isFramePaintStateValid_ = false;

    void MultiSelectWithoutKeyboard(const Rect& selectedZone);
    void HandleMouseEventWithoutKeyboard(const MouseEvent& event);

    void MultiSelectWhenCtrlDown(const Rect& selectedZone);
    void HandleMouseEventWhenCtrlDown(const MouseEvent& event);
    void CollectSelectedItems();
    std::set<RefPtr<RenderListItem>> selectedItemsWithCtrl_;

    void MultiSelectWhenShiftDown(const Rect& selectedZone);
    RefPtr<RenderListItem> GetPressItemWhenShiftDown(const Rect& selectedZone);
    void HandleMouseEventWhenShiftDown(const MouseEvent& event);
    void MultiSelectAllInRange(const RefPtr<RenderListItem>& firstItem, const RefPtr<RenderListItem>& secondItem);
    RefPtr<RenderListItem> firstItemWithShift_;
    RefPtr<RenderListItem> secondItemWithShift_;

    void MultiSelectAllWhenCtrlA();

    // distribute
    void ApplyRestoreInfo();

    void InitScrollable(Axis axis);

    // when window size change, add offset to keep clicked textfield in display area
    void SizeChangeOffset(double newWindowHeight);

    bool hasDragItem_ = false;
    std::map<ListEvents, bool> listEventFlags_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderList);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_RENDER_LIST_H

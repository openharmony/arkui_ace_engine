/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "list_test_ng.h"

namespace OHOS::Ace::NG {
void ListTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));

    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
    listItemTheme->itemDefaultColor_ = Color::WHITE;
    listItemTheme->hoverColor_ = Color::RED;
    listItemTheme->pressColor_ = Color::BLACK;
    int32_t hoverAnimationDuration = 250;
    int32_t hoverToPressAnimationDuration = 100;
    double disabledAlpha = 0.4;
    listItemTheme->hoverAnimationDuration_ = hoverAnimationDuration;
    listItemTheme->hoverToPressAnimationDuration_ = hoverToPressAnimationDuration;
    listItemTheme->disabledAlpha_ = disabledAlpha;
    listItemTheme->defaultColor_ = Color::WHITE;
    listItemTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listItemTheme->defaultRightMargin_ = GROUP_MARGIN;
}

void ListTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ListTestNg::SetUp() {}

void ListTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void ListTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ListPattern>();
    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ListLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<ScrollablePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

void ListTestNg::Create(const std::function<void(ListModelNG)>& callback)
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    RefPtr<ScrollControllerBase> scrollController = model.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    model.SetScroller(scrollController, proxy);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ListTestNg::CreateWithItem(const std::function<void(ListModelNG)>& callback)
{
    Create([callback](ListModelNG model) {
        if (callback) {
            callback(model);
        }
        CreateItem(TOTAL_LINE_NUMBER);
    });
}

void ListTestNg::CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber)
{
    Create([isStartNode, swipeEdgeEffect, itemNumber](ListModelNG model) {
        auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
        auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
        for (int32_t index = 0; index < itemNumber; index++) {
            if (isStartNode) {
                CreateItemWithSwipe(startFunc, nullptr, swipeEdgeEffect);
            } else {
                CreateItemWithSwipe(nullptr, endFunc, swipeEdgeEffect);
            }
        }
    });
}

void ListTestNg::CreateWithSwipeAction(
    SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect)
{
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    {
        ListItemModelNG itemModel;
        itemModel.Create();
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), effect);
        itemModel.SetDeleteArea(std::move(item.builderAction), std::move(item.onDelete),
            std::move(item.onEnterDeleteArea), std::move(item.onExitDeleteArea), std::move(item.onStateChange),
            item.actionAreaDistance, isStartArea);
        {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void ListTestNg::CreateItem(int32_t itemNumber, Axis axis, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, listItemStyle);
        if (axis == Axis::VERTICAL) {
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        } else {
            ViewAbstract::SetWidth(CalcLength(ITEM_WIDTH));
            ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        }
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateItemWithSize(int32_t itemNumber, SizeT<Dimension> itemSize, V2::ListItemStyle listItemStyle)
{
    for (int32_t index = 0; index < itemNumber; ++index) {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, listItemStyle);
        ViewAbstract::SetWidth(CalcLength(itemSize.Width()));
        ViewAbstract::SetHeight(CalcLength(itemSize.Height()));
        {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateGroupWithSetting(
    int32_t groupNumber, Axis axis, V2::ListItemGroupStyle listItemGroupStyle, int32_t itemNumber)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        auto header = GetDefaultHeaderBuilder();
        auto footer = GetDefaultHeaderBuilder();
        ListItemGroupModelNG groupModel;
        groupModel.Create(listItemGroupStyle);
        groupModel.SetSpace(Dimension(SPACE));
        groupModel.SetDivider(ITEM_DIVIDER);
        groupModel.SetHeader(std::move(header));
        groupModel.SetFooter(std::move(footer));
        CreateItem(itemNumber, axis, static_cast<V2::ListItemStyle>(listItemGroupStyle));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateGroup(int32_t groupNumber, Axis axis)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG groupModel;
        groupModel.Create(V2::ListItemGroupStyle::NONE);
        CreateItem(GROUP_LINE_NUMBER, axis, V2::ListItemStyle::NONE);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateItemWithSwipe(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG itemModel;
    itemModel.Create();
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    itemModel.SetSwiperAction(std::move(startAction), std::move(endAction), nullptr, effect);
    if (startAction) {
        itemModel.SetDeleteArea(
            std::move(startAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    }
    if (endAction) {
        itemModel.SetDeleteArea(
            std::move(endAction), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    }
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize)
{
    return [crossSize]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(crossSize));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
    };
}

std::function<void()> ListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(GROUP_HEADER_LEN));
    };
}

void ListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    FlushLayoutTask(frameNode_);
}

float ListTestNg::GetInterval()
{
    float space = layoutProperty_->GetSpace().has_value() ? layoutProperty_->GetSpace().value().ConvertToPx() : 0.f;
    float strokeWidth = layoutProperty_->GetDivider().has_value()
                            ? layoutProperty_->GetDivider().value().strokeWidth.ConvertToPx()
                            : 0.f;
    return std::max(space, strokeWidth);
}

void ListTestNg::ScrollUp(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = (itemMainLength + GetInterval()) * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollDown(float itemNumber)
{
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float offset = -(itemMainLength + GetInterval()) * itemNumber;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    pattern_->ScrollToEdge(scrollEdgeType, false);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align)
{
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        auto iter = pattern_->itemPosition_.find(index);
        float targetPos = 0.0f;
        if (iter->second.isGroup) {
            if (!pattern_->GetListItemGroupAnimatePosWithoutIndexInGroup(index, iter->second.startPos,
                iter->second.endPos, align, targetPos)) {
                return;
            }
        } else {
            pattern_->GetListItemAnimatePos(iter->second.startPos, iter->second.endPos, align, targetPos);
        }
        if (!NearZero(targetPos)) {
            float endValue = pattern_->GetFinalPosition();
            pattern_->ScrollTo(endValue);
            FlushLayoutTask(frameNode_);
        }
    }
}

void ListTestNg::ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    pattern_->ScrollToItemInGroup(index, indexInGroup, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        float endValue = pattern_->GetFinalPosition();
        pattern_->ScrollTo(endValue);
        FlushLayoutTask(frameNode_);
    }
}

void ListTestNg::DragSwiperItem(int32_t index, float mainDelta, float mainVelocity)
{
    HandleDragStart(index);
    HandleDragUpdate(index, mainDelta);
    HandleDragEnd(index, mainVelocity);
}

void ListTestNg::HandleDragStart(int32_t index)
{
    GestureEvent info;
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragStart(info);
}

void ListTestNg::HandleDragUpdate(int32_t index, float mainDelta)
{
    GestureEvent info;
    info.SetMainDelta(mainDelta);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

void ListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragEnd(info);
    // curOffset_ would be NodeSize or Zero
    EXPECT_NE(itemPattern->springMotion_, nullptr);
    double position = itemPattern->springMotion_->GetEndValue();
    itemPattern->UpdatePostion(position - itemPattern->curOffset_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
}

AssertionResult ListTestNg::VerifyPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset)
{
    bool isGroup = frameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (isGroup) {
        return VerifyGroupItemPosition(frameNode, viewItemNumber, lanes, space, startOffset);
    } else {
        Axis axis = pattern_->GetAxis();
        float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
        float itemSpaceLength = itemMainLength + space;
        int32_t initialIndex = std::floor(startOffset / itemSpaceLength) * lanes;
        return VerifyItemPosition(frameNode, viewItemNumber, lanes, space, initialIndex);
    }
}

AssertionResult ListTestNg::VerifyItemPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, int32_t initialIndex)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float itemSpaceLength = itemMainLength + space;
    auto itemPosition = frameNode->GetPattern<ListPattern>()->GetItemPosition();
    if (itemPosition.size() != static_cast<size_t>(viewItemNumber)) {
        return AssertionFailure() << "The itemPosition size is not equal to viewItemNumber"
                                  << " itemPosition: " << itemPosition.size() << " viewItemNumber: " << viewItemNumber;
    }
    for (int32_t index = 0; index < viewItemNumber; index++) {
        int32_t itemIndex = index + initialIndex;
        float startPos = itemPosition[itemIndex].startPos;
        float endPos = itemPosition[itemIndex].endPos;
        float expectStartPos = (index / lanes) * itemSpaceLength;
        float expectEndPos = expectStartPos + itemMainLength;
        if (!NearEqual(startPos, expectStartPos) || !NearEqual(endPos, expectEndPos)) {
            return AssertionFailure() << "At itemPosition Index: " << itemIndex << " ItemPosition: (" << startPos
                                      << " - " << endPos << ")"
                                      << " != expectPosition: (" << expectStartPos << " - " << expectEndPos << ")";
        }
    }
    return AssertionSuccess();
}

AssertionResult ListTestNg::VerifyGroupItemPosition(
    const RefPtr<FrameNode>& frameNode, int32_t viewItemNumber, int32_t lanes, float space, float startOffset)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    Axis axis = pattern_->GetAxis();
    float itemMainLength = (axis == Axis::VERTICAL) ? ITEM_HEIGHT : ITEM_WIDTH;
    float itemSpaceLength = itemMainLength + space;
    auto itemPosition = frameNode->GetPattern<ListItemGroupPattern>()->GetItemPosition();
    if (itemPosition.size() != static_cast<size_t>(viewItemNumber)) {
        return AssertionFailure() << "The itemPosition size is not equal to viewItemNumber"
                                  << " itemPosition: " << itemPosition.size() << " viewItemNumber: " << viewItemNumber;
    }
    for (int32_t index = 0; index < viewItemNumber; index++) {
        int32_t itemIndex = index;
        float startPos = itemPosition[itemIndex].first;
        float endPos = itemPosition[itemIndex].second;
        float expectStartPos = (index / lanes) * itemSpaceLength + startOffset;
        float expectEndPos = expectStartPos + itemMainLength;
        if (!NearEqual(startPos, expectStartPos) || !NearEqual(endPos, expectEndPos)) {
            return AssertionFailure() << "At itemPosition Index: " << itemIndex << " ItemPosition: (" << startPos
                                      << " - " << endPos << ")"
                                      << " != expectPosition: (" << expectStartPos << " - " << expectEndPos << ")";
        }
    }
    return AssertionSuccess();
}

AssertionResult ListTestNg::IsEqualTotalOffset(float expectOffset)
{
    FlushLayoutTask(frameNode_);
    return IsEqual(pattern_->GetTotalOffset(), expectOffset);
}

AssertionResult ListTestNg::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, float expectOffset)
{
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToIndex(index, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Straight to the end of the anmiation
        // can not exceed scrollableDistance if is not spring
        float endValue = pattern_->GetFinalPosition();
        float scrollableDistance = pattern_->GetScrollableDistance();
        float two = 2.f;
        if (GreatNotEqual(endValue - startOffset * two, scrollableDistance)) {
            endValue = scrollableDistance;
        }
        if (LessNotEqual(endValue, 0)) {
            endValue = 0;
        }
        pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue,
            SCROLL_FROM_ANIMATION_CONTROLLER);
        FlushLayoutTask(frameNode_);
    }
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(startOffset);
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

AssertionResult ListTestNg::ScrollToItemInGroup(
    int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align, float expectOffset)
{
    float startOffset = pattern_->GetTotalOffset();
    pattern_->ScrollToItemInGroup(index, indexInGroup, smooth, align);
    FlushLayoutTask(frameNode_);
    if (smooth) {
        // Straight to the end of the anmiation
        // can not exceed scrollableDistance if is not spring
        float endValue = pattern_->GetFinalPosition();
        float scrollableDistance = pattern_->GetScrollableDistance();
        float two = 2.f;
        if (GreatNotEqual(endValue - startOffset * two, scrollableDistance)) {
            endValue = scrollableDistance;
        }
        if (LessNotEqual(endValue, 0)) {
            endValue = 0;
        }
        pattern_->UpdateCurrentOffset(pattern_->GetTotalOffset() - endValue,
            SCROLL_FROM_ANIMATION_CONTROLLER);
        FlushLayoutTask(frameNode_);
    }
    float currentOffset = pattern_->GetTotalOffset();
    // reset offset before return
    pattern_->ScrollTo(startOffset);
    FlushLayoutTask(frameNode_);
    return IsEqual(currentOffset, expectOffset);
}

// Get all listItem that in or not in listItemGroup
std::vector<RefPtr<FrameNode>> ListTestNg::GetALLItem()
{
    std::vector<RefPtr<FrameNode>> listItems;
    auto children = frameNode_->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto group = child->GetChildren();
            for (auto item : group) {
                auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
                if (itemFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
                    listItems.emplace_back(itemFrameNode);
                }
            }
        } else if (childFrameNode->GetTag() == V2::LIST_ITEM_ETS_TAG) {
            listItems.emplace_back(childFrameNode);
        }
    }
    return listItems;
}

int32_t ListTestNg::findFocusNodeIndex(RefPtr<FocusHub>& focusNode)
{
    std::vector<RefPtr<FrameNode>> listItems = GetALLItem();
    int32_t size = static_cast<int32_t>(listItems.size());
    for (int32_t index = 0; index < size; index++) {
        if (focusNode == listItems[index]->GetOrCreateFocusHub()) {
            return index;
        }
    }
    return NULL_VALUE;
}
} // namespace OHOS::Ace::NG

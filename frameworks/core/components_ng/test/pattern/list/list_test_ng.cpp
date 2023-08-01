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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#define private public
#define protected public
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/pattern/test_ng.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "frameworks/bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float GROUP_WIDTH = 400.f;
constexpr float GROUP_HEIGHT = 600.f;
constexpr float GROUP_ITEM_WIDTH = 300.f;
constexpr int32_t TOTAL_NUMBER = 10;
constexpr int32_t VIEWPORT_NUMBER = 8;
constexpr int32_t GROUP_ITEM_NUMBER = 4;
constexpr float ITEM_HEIGHT = 100.f;
constexpr float ITEM_WIDTH = 60.f;
constexpr float HEADER_MAIN_LENGTH = 50.f;
constexpr float START_NODE_SIZE = 80.f;
constexpr float END_NODE_SIZE = 100.f;
constexpr float DELETE_AREA_DISTANCE = 50.f;
constexpr Dimension GROUP_MARGIN = 12.0_vp;
constexpr float DEFAULT_STIFFNESS = 228;
constexpr float DEFAULT_DAMPING = 30;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPER_TH = 0.25f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr int32_t DEFAULT_INTERVAL = 0;
constexpr int32_t DEFAULT_STARTINDEX = 0;
constexpr float SPACE = 10.f;
constexpr float STROKE_WIDTH = 2.f;
constexpr int32_t NULL_INDEX = -1;
} // namespace

class ListTestNg : public testing::Test, public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    void UpdateCurrentOffset(float offset, int32_t source = SCROLL_FROM_UPDATE);
    void CreateList(int32_t number = TOTAL_NUMBER, Axis axis = Axis::VERTICAL);
    void CreateSwipeList(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber = TOTAL_NUMBER);
    void CreateSelectableList();
    void CreateFocusableList(int32_t itemNumber, Axis axis);
    void CreateGroupItemFocusableList(int32_t groupItem, Axis axis);
    void CreateChainList(const ChainAnimationOptions& options);
    void CreateSnapAlignList(V2::ScrollSnapAlign scrollSnapAlign);
    void CreateListItemGroup();
    void CreateListItemGroup(int32_t groupNumber, Axis axis = Axis::VERTICAL, bool focusable = false);
    void CreateListItem(int32_t itemNumber, Axis axis = Axis::VERTICAL, bool focusable = false);
    void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    void CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
        OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
        const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect);
    std::function<void()> GetDefaultSwiperBuilder(float crossSize);
    std::function<void()> GetDefaultHeaderBuilder();
    testing::AssertionResult VerifyItemPosition(int32_t expectCount, int32_t lanes = DEFAULT_LANES,
        float interval = DEFAULT_INTERVAL, int32_t startIndex = DEFAULT_STARTINDEX);
    testing::AssertionResult VerifyGroupItemPosition(
        RefPtr<FrameNode> groupNode, int32_t expectNumber, int32_t lanes = DEFAULT_LANES,
        float interval = DEFAULT_INTERVAL, float startOffset = 0);
    testing::AssertionResult IsEqualCurrentOffset(Offset expectOffset);
    testing::AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t nextIndex);
    testing::AssertionResult IsEqualNextGroupItemFocusNode(FocusStep step, int32_t currentIndex, int32_t nextIndex);
    testing::AssertionResult ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, Offset expectOffset);
    testing::AssertionResult ScrollToIndex(int32_t index, int32_t indexInGroup, ScrollAlign align, Offset expectOffset);
    void MouseSelect(Offset start, Offset end);
    void ScrollToTop();
    void ScrollToBottom();
    void DragSwiperItem(int32_t index, float mainDelta, float mainVelocity = SWIPER_SPEED_TH);
    void HandleDragStart(int32_t index);
    void HandleDragUpdate(int32_t index, float mainDelta);
    void HandleDragEnd(int32_t index, float mainVelocity = SWIPER_SPEED_TH);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
    RefPtr<ListPaintProperty> paintProperty_;
    RefPtr<ListAccessibilityProperty> accessibilityProperty_;
};

void ListTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    auto listItemTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    EXPECT_CALL(*themeManager, GetTheme(ListItemTheme::TypeId())).WillRepeatedly(Return(listItemTheme));
}

void ListTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
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
    paintProperty_ = frameNode_->GetPaintProperty<ListPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ListAccessibilityProperty>();
}

void ListTestNg::CreateList(int32_t number, Axis axis)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(axis);
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(number, axis);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateSwipeList(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
    for (int32_t index = 0; index < itemNumber; index++) {
        if (isStartNode) {
            CreateListItemWithSwiper(startFunc, nullptr, swipeEdgeEffect);
        } else {
            CreateListItemWithSwiper(nullptr, endFunc, swipeEdgeEffect);
        }
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateSelectableList()
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateFocusableList(int32_t itemNumber, Axis axis)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(axis);
    CreateListItem(itemNumber, axis, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateGroupItemFocusableList(int32_t groupNumber, Axis axis)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(axis);
    CreateListItemGroup(groupNumber, axis, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateChainList(const ChainAnimationOptions& options)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(SPACE));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(options);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateSnapAlignList(V2::ScrollSnapAlign scrollSnapAlign)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetScrollSnapAlign(scrollSnapAlign);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::CreateListItemGroup()
{
    constexpr float startMargin = 10.f;
    constexpr float endMargin = 20.f;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(STROKE_WIDTH);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    // V2::ListItemGroupStyle::NONE
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();
    ListItemGroupModelNG listItemGroupModel_1;
    listItemGroupModel_1.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel_1.SetSpace(Dimension(SPACE));
    listItemGroupModel_1.SetDivider(itemDivider);
    listItemGroupModel_1.SetHeader(std::move(header));
    listItemGroupModel_1.SetFooter(std::move(footer));
    SetWidth(Dimension(GROUP_WIDTH));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // SetWidth
    // V2::ListItemGroupStyle::NONE
    ListItemGroupModelNG listItemGroupModel_2;
    listItemGroupModel_2.Create(V2::ListItemGroupStyle::NONE);
    listItemGroupModel_2.SetSpace(Dimension(SPACE));
    listItemGroupModel_2.SetHeader(std::move(header));
    listItemGroupModel_2.SetFooter(std::move(footer));
    SetWidth(Dimension(GROUP_WIDTH));
    for (int32_t index = 0; index < GROUP_ITEM_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(Dimension(GROUP_ITEM_WIDTH));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();

    // V2::ListItemGroupStyle::CARD
    ListItemGroupModelNG listItemGroupModel_3;
    listItemGroupModel_3.Create(V2::ListItemGroupStyle::CARD);
    listItemGroupModel_3.SetSpace(Dimension(SPACE));
    listItemGroupModel_3.SetDivider(itemDivider);
    SetWidth(Dimension(GROUP_WIDTH));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // SetWidth
    ListItemGroupModelNG listItemGroupModel_4;
    listItemGroupModel_4.Create(V2::ListItemGroupStyle::NONE);
    SetWidth(Dimension(Infinity<float>()));
    CreateListItem(GROUP_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();

    // has no listItem
    ListItemGroupModelNG listItemGroupModel_5;
    listItemGroupModel_5.Create(V2::ListItemGroupStyle::NONE);
    SetWidth(Dimension(GROUP_WIDTH));
    ViewStackProcessor::GetInstance()->Pop();
}

void ListTestNg::CreateListItemGroup(int32_t groupNumber, Axis axis, bool focusable)
{
    for (int32_t index = 0; index < groupNumber; index++) {
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create(V2::ListItemGroupStyle::NONE);
        // do not fill List
        if (axis == Axis::VERTICAL) {
            SetWidth(Dimension(GROUP_WIDTH));
        } else {
            SetHeight(Dimension(GROUP_HEIGHT));
        }
        CreateListItem(GROUP_ITEM_NUMBER, axis, focusable);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItem(int32_t itemNumber, Axis axis, bool focusable)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        if (axis == Axis::VERTICAL) {
            SetHeight(Dimension(ITEM_HEIGHT));
            SetWidth(FILL_LENGTH);
        } else {
            SetWidth(Dimension(ITEM_WIDTH));
            SetHeight(FILL_LENGTH);
        }
        if (focusable) {
            ButtonModelNG buttonModelNG;
            buttonModelNG.CreateWithLabel("label");
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItemWithSwiper(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG listItemModel;
    listItemModel.Create();
    SetWidth(FILL_LENGTH);
    SetHeight(Dimension(ITEM_HEIGHT));
    listItemModel.SetSwiperAction(std::move(startAction), std::move(endAction), effect);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

void ListTestNg::CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
    OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
    const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemModelNG listItemModel;
    listItemModel.Create();
    SetHeight(Dimension(ITEM_HEIGHT));
    SetWidth(FILL_LENGTH);
    listItemModel.SetSwiperAction(nullptr, nullptr, effect);
    listItemModel.SetDeleteArea(std::move(builderAction), useDefaultDeleteAnimation, std::move(onDelete),
        std::move(onEnterDeleteArea), std::move(onExitDeleteArea), length, isStartArea);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(FILL_LENGTH);
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize)
{
    return [crossSize]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(Dimension(crossSize));
        SetHeight(Dimension(ITEM_HEIGHT));
    };
}

std::function<void()> ListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(HEADER_MAIN_LENGTH));
    };
}

testing::AssertionResult ListTestNg::VerifyItemPosition(
    int32_t expectCount, int32_t lanes, float interval, int32_t startIndex)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = pattern_->GetItemPosition();
    for (int32_t index = 0; index < expectCount; index++) {
        auto listItem = itemPosition[index + startIndex];
        float startPos = (index / lanes) * (ITEM_HEIGHT + interval);
        float endPos = startPos + ITEM_HEIGHT;
        if (!NearEqual(listItem.startPos, startPos) || !NearEqual(listItem.endPos, endPos)) {
            return testing::AssertionFailure() <<
                "At itemPosition Index: " << index <<
                " ItemPosition: (" << listItem.startPos << " - " << listItem.endPos << ")" <<
                " != " <<
                "expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::VerifyGroupItemPosition(
    RefPtr<FrameNode> groupNode, int32_t expectNumber, int32_t lanes, float interval, float startOffset)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemPosition = groupNode->GetPattern<ListItemGroupPattern>()->GetItemPosition();
    for (int32_t index = 0; index < expectNumber; index++) {
        auto listItem = itemPosition[index];
        float startPos = (index / lanes) * (ITEM_HEIGHT + interval) + startOffset;
        float endPos = startPos + ITEM_HEIGHT;
        if (!NearEqual(listItem.first, startPos) || !NearEqual(listItem.second, endPos)) {
            return testing::AssertionFailure() <<
                "At itemPosition Index: " << index <<
                " Group ItemPosition: (" << listItem.first << " - " << listItem.second << ")" <<
                " != " <<
                "expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualCurrentOffset(Offset expectOffset)
{
    RunMeasureAndLayout(frameNode_);
    Offset currentOffset = pattern_->GetCurrentOffset();
    return IsEqualOffset(currentOffset, expectOffset);
}

testing::AssertionResult ListTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t nextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(frameNode_, currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextIndex == NULL_INDEX && nextFocusNode != nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is not null.";
    }
    if (nextIndex != NULL_INDEX && nextFocusNode == nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is null.";
    }
    if (nextIndex != NULL_INDEX && nextFocusNode != GetChildFocusHub(frameNode_, nextIndex)) {
        return testing::AssertionFailure() << "Get wrong next FocusNode.";
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualNextGroupItemFocusNode(
    FocusStep step, int32_t currentIndex, int32_t nextIndex)
{
    auto groupNode = GetChildFrameNode(frameNode_, std::floor(currentIndex / GROUP_ITEM_NUMBER));
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(groupNode, currentIndex % GROUP_ITEM_NUMBER);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextIndex == NULL_INDEX && nextFocusNode != nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is not null.";
    }
    if (nextIndex != NULL_INDEX && nextFocusNode == nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is null.";
    }
    if (nextIndex != NULL_INDEX) {
        auto groupNode = GetChildFrameNode(frameNode_, std::floor(nextIndex / GROUP_ITEM_NUMBER));
        RefPtr<FocusHub> expectNextFocusNode = GetChildFocusHub(groupNode, nextIndex % GROUP_ITEM_NUMBER);
        if (nextFocusNode != expectNextFocusNode) {
            return testing::AssertionFailure() << "Get wrong next FocusNode.";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::ScrollToIndex(
    int32_t index, bool smooth, ScrollAlign align, Offset expectOffset)
{
    float originalOffsetY = pattern_->GetCurrentOffset().GetY();
    pattern_->ScrollToIndex(index, smooth, align);
    RunMeasureAndLayout(frameNode_);
    Offset currentOffset = pattern_->GetCurrentOffset();
    // reset offset before return
    pattern_->ScrollTo(originalOffsetY);
    RunMeasureAndLayout(frameNode_);
    if (currentOffset != expectOffset) {
        return testing::AssertionFailure() <<
            "ScrollToIndex(" << index << ", " << smooth <<
            ", ScrollAlign:" << static_cast<int32_t>(align) << ")" <<
            " GetCurrentOffset(): " << currentOffset.ToString() <<
            " != " <<
            "expectOffset: " << expectOffset.ToString();
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::ScrollToIndex(
    int32_t index, int32_t indexInGroup, ScrollAlign align, Offset expectOffset)
{
    float originalOffsetY = pattern_->GetCurrentOffset().GetY();
    pattern_->ScrollToIndex(index, indexInGroup, align);
    RunMeasureAndLayout(frameNode_);
    Offset currentOffset = pattern_->GetCurrentOffset();
    // reset offset before return
    pattern_->ScrollTo(originalOffsetY);
    RunMeasureAndLayout(frameNode_);
    if (currentOffset != expectOffset) {
        return testing::AssertionFailure() <<
            "ScrollToIndex(" << index << ", " << indexInGroup <<
            ", ScrollAlign:" << static_cast<int32_t>(align) << ")" <<
            " GetCurrentOffset(): " << currentOffset.ToString() <<
            " != " <<
            "expectOffset: " << expectOffset.ToString();
    }
    return testing::AssertionSuccess();
}

void ListTestNg::MouseSelect(Offset start, Offset end)
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(start);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    if (start != end) {
        info.SetAction(MouseAction::MOVE);
        info.SetLocalLocation(end);
        pattern_->HandleMouseEventWithoutKeyboard(info);
    }
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

void ListTestNg::UpdateCurrentOffset(float offset, int32_t source)
{
    pattern_->UpdateCurrentOffset(offset, source);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::ScrollToTop()
{
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::ScrollToBottom()
{
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    RunMeasureAndLayout(frameNode_);
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
    RunMeasureAndLayout(frameNode_);
}

void ListTestNg::HandleDragEnd(int32_t index, float mainVelocity)
{
    GestureEvent info;
    info.SetMainVelocity(mainVelocity);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, index);
    itemPattern->HandleDragEnd(info);
    // curOffset_ would be NodeSize or Zero
    double position = itemPattern->springMotion_->GetEndValue();
    itemPattern->UpdatePostion(position - itemPattern->curOffset_);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout(frameNode_);
}

/**
 * @tc.name: ListLayoutProperty001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutProperty001, TestSize.Level1)
{
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10);
    itemDivider.startMargin = Dimension(5);
    itemDivider.endMargin = Dimension(5);
    itemDivider.color = Color(0x000000);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(10));
    listModelNG.SetInitialIndex(1);
    listModelNG.SetListDirection(Axis::VERTICAL);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    listModelNG.SetEditMode(true);
    listModelNG.SetChainAnimation(true);
    listModelNG.SetDivider(itemDivider);
    listModelNG.SetEdgeEffect(EdgeEffect::NONE);
    listModelNG.SetLanes(3);
    listModelNG.SetLaneMinLength(Dimension(40));
    listModelNG.SetLaneMaxLength(Dimension(60));
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    listModelNG.SetCachedCount(10);
    listModelNG.SetSticky(V2::StickyStyle::HEADER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(Dimension::FromString(json->GetString("space")), Dimension(10));
    EXPECT_EQ(json->GetString("initialIndex"), "1");
    EXPECT_EQ(static_cast<Axis>(json->GetInt("listDirection")), Axis::VERTICAL);
    EXPECT_TRUE(json->GetBool("editMode"));
    EXPECT_TRUE(json->GetBool("chainAnimation"));
    auto dividerJson = json->GetObject("divider");
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("strokeWidth")), Dimension(10));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("startMargin")), Dimension(5));
    EXPECT_EQ(Dimension::FromString(dividerJson->GetString("endMargin")), Dimension(5));
    EXPECT_EQ(Color::ColorFromString(dividerJson->GetString("color")), Color(0x000000));
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.None");
    EXPECT_EQ(json->GetString("lanes"), "3");
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMinLength")), Dimension(40));
    EXPECT_EQ(Dimension::FromString(json->GetString("laneMaxLength")), Dimension(60));
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.Center");
    EXPECT_EQ(json->GetString("cachedCount"), "10");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header");

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("edgeEffect"), "EdgeEffect.Fade");
    EXPECT_EQ(json->GetString("alignListItem"), "ListItemAlign.End");
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Footer");

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is changed
     */
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "StickyStyle.Header | StickyStyle.Footer");

    /**
     * @tc.steps: step4. The json include strokeWidth and Change it, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue().strokeWidth changed
     */
    dividerJson = json->GetObject("divider");
    dividerJson->Replace("strokeWidth", Dimension(20).ToString().c_str());
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));

    /**
     * @tc.steps: step5. The json not include strokeWidth, call FromJson()
     * @tc.expected: The layoutProperty_->GetDividerValue() not changed
     */
    dividerJson->Delete("strokeWidth");
    layoutProperty_->FromJson(json);
    EXPECT_EQ(layoutProperty_->GetDividerValue().strokeWidth, Dimension(20));
}

/**
 * @tc.name: ListItemLayoutProperty001
 * @tc.desc: Test ListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemLayoutProperty001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);
    auto layoutProperty = GetChildFrameNode(frameNode_, 0)->GetLayoutProperty<ListItemLayoutProperty>();

    /**
     * @tc.steps: step1. Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(static_cast<V2::StickyMode>(json->GetInt("sticky")), V2::StickyMode::NONE);
    EXPECT_EQ(json->GetBool("editable"), false);
    EXPECT_EQ(Dimension::FromString(json->GetString("startDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));
    EXPECT_EQ(Dimension::FromString(json->GetString("endDeleteAreaDistance")), Dimension(0, DimensionUnit::VP));

    /**
     * @tc.steps: step2. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::NORMAL);
    layoutProperty->UpdateEditMode(V2::EditMode::NONE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Normal");
    EXPECT_EQ(json->GetString("editable"), "EditMode.None");
    auto swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(static_cast<V2::SwipeEdgeEffect>(swipeAction->GetInt("edgeEffect")), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateStickyMode(V2::StickyMode::OPACITY);
    layoutProperty->UpdateEditMode(V2::EditMode::MOVABLE);
    layoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("sticky"), "Sticky.Opacity");
    EXPECT_EQ(json->GetString("editable"), "EditMode.Movable");
    swipeAction = json->GetObject("swipeAction");
    EXPECT_EQ(swipeAction->GetString("edgeEffect"), "SwipeEdgeEffect.Node");

    /**
     * @tc.steps: step4. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("editable"), "EditMode.Deletable");

    /**
     * @tc.steps: step5. Change some property, Call ToJsonValue()
     * @tc.expected: The json value is correct
     */
    layoutProperty->UpdateEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->GetBool("editable"));
}

/**
 * @tc.name: AttrSpace001
 * @tc.desc: Test property about space,
 * there is space between each ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpace001, TestSize.Level1)
{
    constexpr float space = 5.0f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, space));
}

/**
 * @tc.name: AttrSpace002
 * @tc.desc: Test property about space,
 * when space less than divider's strokeWidth, space was going to be strokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSpace002, TestSize.Level1)
{
    constexpr float space = 5.0f;
    constexpr float strokeWidth = 10.f;
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetDivider(itemDivider);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, strokeWidth));
}

/**
 * @tc.name: AttrInitIndex001
 * @tc.desc: Test property about initialIndex,
 * list layout starting from initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex001, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, 0, initIndex));
}

/**
 * @tc.name: AttrInitIndex002
 * @tc.desc: Test property about initialIndex,
 * total ListItem size less than viewport, List layout starting from first
 * ListItem.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex002, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;
    constexpr size_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(itemCount));
}

/**
 * @tc.name: AttrInitIndex003
 * @tc.desc: Test property about initialIndex,
 * The total size of ListItems after initialIndex is less than viewport, ListItem bottom to viewport.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex003, TestSize.Level1)
{
    constexpr int32_t initIndex = 5;
    constexpr int32_t expectStartIndex = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, 0, expectStartIndex));
}

/**
 * @tc.name: AttrInitIndex004
 * @tc.desc: Test property about initialIndex,
 * initialIndex out of range, ignore.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex004, TestSize.Level1)
{
    constexpr int32_t initIndex = 100;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER));
}

/**
 * @tc.name: AttrInitIndex005
 * @tc.desc: Test property about initialIndex,
 * initialIndex is not an integer multiple of the lanes,
 * List layout starting from an index integer multiple of the lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrInitIndex005, TestSize.Level1)
{
    constexpr int32_t initIndex = 3;
    constexpr int32_t lanes = 2;
    constexpr int32_t itemCount = 20;
    constexpr size_t expectItemCount = 16;
    constexpr int32_t expectStartIndex = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    listModelNG.SetLanes(lanes);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(expectItemCount, lanes, 0, expectStartIndex));
}

/**
 * @tc.name: AttrDivider001
 * @tc.desc: Test property about divider,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrDivider001, TestSize.Level1)
{
    constexpr float strokeWidth = 4;
    constexpr float startMargin = 10;
    constexpr float endMargin = 20;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetDivider(itemDivider);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_TRUE(VerifyItemPosition(VIEWPORT_NUMBER, 1, strokeWidth));
}

/**
 * @tc.name: AttrScrollBar001
 * @tc.desc: Test property about scrollBar,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollBar001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::ON);
}

/**
 * @tc.name: AttrScrollBar002
 * @tc.desc: Test property about scrollBar,
 * when api version >= 10, the default value is auto
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollBar002, TestSize.Level1)
{
    constexpr int32_t platformVersionTen = 10;

    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    MockPipelineBase::pipeline_->SetMinPlatformVersion(platformVersionTen);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrLanes001
 * @tc.desc: Test property about lanes,
 * List layout as 2 lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes001, TestSize.Level1)
{
    constexpr int32_t lanes = 2;
    constexpr int32_t itemCount = 19;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    int32_t expectItemCount = 16;
    int32_t expectLanes = 2;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    ScrollToBottom();
    int32_t expectStartIndex = 4;
    expectItemCount = 15;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, expectStartIndex));

    ScrollToTop();
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));
}

/**
 * @tc.name: AttrLanes002
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes002, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 480.f;
    constexpr int32_t itemCount = 19;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    int32_t expectLanes = 2;
    int32_t expectItemCount = 16;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    ScrollToBottom();
    int32_t expectStartIndex = 4;
    expectItemCount = 15;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, expectStartIndex));

    ScrollToTop();
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes, DEFAULT_INTERVAL, DEFAULT_STARTINDEX));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        float width = GetChildRect(frameNode_, index).Width();
        EXPECT_FLOAT_EQ(width, 240.f);
    }
}

/**
 * @tc.name: AttrLanes003
 * @tc.desc: Test LayoutProperty about minLaneLength, maxLaneLength,
 * when maxLaneLength less than minLaneLength, use minLaneLength
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes003, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 100.f;
    constexpr int32_t itemCount = 19;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    int32_t expectItemCount = 16;
    int32_t expectLanes = 2;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        float width = GetChildRect(frameNode_, index).Width();
        EXPECT_FLOAT_EQ(width, minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LayoutProperty about laneGutter,
 * LaneGutter can be set correctly
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes005, TestSize.Level1)
{
    constexpr Dimension laneGutter = 16.0_vp;
    constexpr int32_t lanes = 3;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    listModelNG.SetLaneGutter(laneGutter);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(laneGutter, layoutProperty_->GetLaneGutter().value_or(Dimension(0.0f, DimensionUnit::VP)));
}

/**
 * @tc.name: AttrAlignListItem001
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, the default is align to start
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem001, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        EXPECT_EQ(offsetX, 0);
    }
}

/**
 * @tc.name: AttrAlignListItem002
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, align by set value ListItemAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem002, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        float expectOffsetX = (DEVICE_WIDTH - itemWidth) / 2;
        EXPECT_EQ(offsetX, expectOffsetX);
    }
}

/**
 * @tc.name: AttrAlignListItem003
 * @tc.desc: Test LayoutProperty about alignListItem,
 * when ListItem width less than List, align by set value ListItemAlign::END
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrAlignListItem003, TestSize.Level1)
{
    constexpr float itemWidth = 400.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListItemAlign(V2::ListItemAlign::END);
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        float offsetX = GetChildRect(frameNode_, index).GetX();
        float expectOffsetX = DEVICE_WIDTH - itemWidth;
        EXPECT_EQ(offsetX, expectOffsetX);
    }
}

/**
 * @tc.name: AttrScrollSnapAlign001
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScrollSnapAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. scroll half of ITEM_HEIGHT
     * @tc.expected: viewport first item align top
     */
    CreateSnapAlignList(V2::ScrollSnapAlign::START);
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    Offset expectOffset = Offset(0, ITEM_HEIGHT / 2);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));

    /**
     * @tc.steps: step1. scroll to bottom
     * @tc.expected: viewport first item not align top
     */
    CreateSnapAlignList(V2::ScrollSnapAlign::START);
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    expectOffset = Offset(0, ITEM_HEIGHT * 2);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));

    CreateSnapAlignList(V2::ScrollSnapAlign::END);
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    expectOffset = Offset(0, ITEM_HEIGHT / 2);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));

    CreateSnapAlignList(V2::ScrollSnapAlign::END);
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    UpdateCurrentOffset(ITEM_HEIGHT / 2);
    expectOffset = Offset::Zero();
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));

    CreateSnapAlignList(V2::ScrollSnapAlign::CENTER);
    expectOffset = Offset(0, -ITEM_HEIGHT * 3.5);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));
    UpdateCurrentOffset(-ITEM_HEIGHT / 2);
    expectOffset = Offset(0, -ITEM_HEIGHT * 3);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));

    CreateSnapAlignList(V2::ScrollSnapAlign::CENTER);
    UpdateCurrentOffset(-ITEM_HEIGHT * TOTAL_NUMBER);
    expectOffset = Offset(0, ITEM_HEIGHT * 6.5);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));
}

/**
 * @tc.name: AttrSLECM001
 * @tc.desc: Test property about scroller/listDirection/edgeEffect/chainAnimation/multiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrSLECM001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    listModelNG.SetChainAnimation(true);
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_NE(pattern_->positionController_, nullptr);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_NE(pattern_->GetScrollEdgeEffect(), nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    EXPECT_TRUE(pattern_->multiSelectable_);
}

/**
 * @tc.name: AttrEnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrEnableScrollInteraction001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();

    /**
     * @tc.steps: step1. Test set value: true
     */
    listModelNG.SetScrollEnabled(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);

    /**
     * @tc.steps: step2. Test set value: false
     */
    layoutProperty_->UpdateScrollEnabled(false);
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
}

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, List can swipe start but cannot swipe end.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem001, TestSize.Level1)
{
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_SIZE, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = START_NODE_SIZE * SWIPER_TH;
    const float obviousSwipeDelta = START_NODE_SIZE * SWIPER_TH + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: StartNode not layout
     */
    RectF startNodeRect = GetChildRect(listItem, startNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectStartNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can not move, StartNode not layout
     */
    DragSwiperItem(listItemIndex, -START_NODE_SIZE);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe start slightly
     * @tc.expected: Can move, StartNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, startNode will not layout
    expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_SIZE, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe start obviously
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. Swipe item slightly
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem002
 * @tc.desc: Set endNode, List can swipe end but cannot swipe start.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem002, TestSize.Level1)
{
    CreateSwipeList(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeEndRect = RectF(-END_NODE_SIZE, 0, DEVICE_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = END_NODE_SIZE * SWIPER_TH;
    const float obviousSwipeDelta = END_NODE_SIZE * SWIPER_TH + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: EndNode not layout
     */
    RectF endNodeRect = GetChildRect(listItem, endNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectEndNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start
     * @tc.expected: Can not move, EndNode not layout
     */
    DragSwiperItem(listItemIndex, END_NODE_SIZE);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe end slightSwipeDelta
     * @tc.expected: Can move, EndNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, endNode will not layout
    expectEndNodeRect = RectF(DEVICE_WIDTH - slightSwipeDelta, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end obviously
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item slightSwipeDelta
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(DEVICE_WIDTH - END_NODE_SIZE + obviousSwipeDelta, 0, END_NODE_SIZE, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqualRect(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqualRect(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem003
 * @tc.desc: Set startNode and endNode. Drag to left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem003, TestSize.Level1)
{
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(frameNode_, listItemIndex);
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;

    /**
     * @tc.steps: step1. swiperIndex_ Default is ITEM_CHILD
     */
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start fast
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end fast
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    CreateSwipeList(false, V2::SwipeEdgeEffect::None);
    listItem = GetChildFrameNode(frameNode_, listItemIndex);
    listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem004
 * @tc.desc: Set startNode and endNode. if drag different ListItem, the previous item would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem004, TestSize.Level1)
{
    CreateSwipeList(true, V2::SwipeEdgeEffect::None);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;
    const int32_t firstItemIndex = 0;
    const int32_t secondItemIndex = 1;
    const RefPtr<ListItemPattern> firstItemPattern = GetChildPattern<ListItemPattern>(frameNode_, firstItemIndex);
    const RefPtr<ListItemPattern> secondItemPattern = GetChildPattern<ListItemPattern>(frameNode_, secondItemIndex);

    /**
     * @tc.steps: step1. Swipe first item fast
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(firstItemIndex, swipeDelta, fastSpeed);
    ListItemSwipeIndex firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    ListItemSwipeIndex secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::SWIPER_START);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe second item fast
     * @tc.expected: The second item swiperIndex_ changed, and first item reseted.
     */
    DragSwiperItem(secondItemIndex, swipeDelta, fastSpeed);
    firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem005
 * @tc.desc: Set startNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem005, TestSize.Level1)
{
    CreateSwipeList(true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, START_NODE_SIZE + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);
}

/**
 * @tc.name: SwiperItem006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem006, TestSize.Level1)
{
    CreateSwipeList(false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, -END_NODE_SIZE + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);
}

/**
 * @tc.name: SwiperItem007
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_SIZE
 * if great than START_NODE_SIZE + deleteAreaDistance,
 * it will adjust to START_NODE_SIZE + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem007, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_SIZE + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: cannot exceed maxDistance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: cannot move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem008
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem008, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_SIZE + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: can exceed maxDistance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: cannot move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem009
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem009, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_SIZE + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_SIZE);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem010
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem010, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_SIZE + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, -maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_SIZE);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem011
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem011, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE);
    CreateListItemWithSwipeActionItem(builder, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_SIZE);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE + 1);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem012, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(END_NODE_SIZE);
    CreateListItemWithSwipeActionItem(builder, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_SIZE);
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -(exceedArea + 1));
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem013
 * @tc.desc: Test callback with no start node
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem013, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateListItemWithSwipeActionItem(nullptr, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem014
 * @tc.desc: Test callback with no end node
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, SwiperItem014, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateListItemWithSwipeActionItem(nullptr, true, deleteEvent, enterEvent, exitEvent,
        Dimension(DELETE_AREA_DISTANCE), false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: ListItemGroup001
 * @tc.desc: check ListItem position
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(1);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. Verify second ListItemGroup itemPosition_/rect.
     */
    int32_t groupIndex = 1;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    auto groupRect = GetChildRect(frameNode_, groupIndex);
    EXPECT_TRUE(IsEqualRect(groupRect, RectF(0, 0, GROUP_WIDTH,
        HEADER_MAIN_LENGTH * 2 + GROUP_ITEM_NUMBER * ITEM_HEIGHT + (GROUP_ITEM_NUMBER - 1) * SPACE)));
    auto headRect = GetChildRect(groupNode, 0);
    auto footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    float footOffsetY = GROUP_ITEM_NUMBER * ITEM_HEIGHT + (GROUP_ITEM_NUMBER - 1) * SPACE + HEADER_MAIN_LENGTH;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH);

    /**
     * @tc.steps: step2. Verify third ListItemGroup itemPosition_/rect.
     */
    UpdateCurrentOffset(-GetChildRect(frameNode_, groupIndex).Height());
    groupIndex = 2;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, 0);

    /**
     * @tc.steps: step3. Verify fourth ListItemGroup itemPosition_/rect.
     */
    UpdateCurrentOffset(-GetChildRect(frameNode_, groupIndex).Height());
    groupIndex = 3;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), static_cast<size_t>(GROUP_ITEM_NUMBER));
    VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, 0);

    /**
     * @tc.steps: step4. Verify fifth ListItemGroup itemPosition_/rect.
     */
    groupIndex = 4;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    groupItemPosition = GetChildPattern<ListItemGroupPattern>(frameNode_, groupIndex)->GetItemPosition();
    EXPECT_EQ(groupItemPosition.size(), 0);
    EXPECT_EQ(GetChildRect(frameNode_, groupIndex).Height(), 0);
    groupRect = GetChildRect(frameNode_, groupIndex);
    EXPECT_TRUE(IsEqualRect(groupRect, RectF(0, DEVICE_HEIGHT, GROUP_WIDTH, 0)));
}

/**
 * @tc.name: ListItemGroup002
 * @tc.desc: List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    listModelNG_1.SetSticky(V2::StickyStyle::HEADER);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    int32_t groupIndex = 0;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    UpdateCurrentOffset(-ITEM_HEIGHT);
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    listModelNG_2.SetSticky(V2::StickyStyle::FOOTER);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto footRect = GetChildRect(groupNode, 1);
    float footOffsetY = DEVICE_HEIGHT - GetChildRect(frameNode_, 0).Height() - HEADER_MAIN_LENGTH;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    UpdateCurrentOffset(-ITEM_HEIGHT);
    footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY + ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    /**
     * @tc.steps: step3. V2::StickyStyle::FOOTER
     * @tc.expected: head/foot is Sticky
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    listModelNG_3.SetSticky(V2::StickyStyle::BOTH);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, 0, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    UpdateCurrentOffset(-ITEM_HEIGHT);
    headRect = GetChildRect(groupNode, 0);
    EXPECT_TRUE(IsEqualRect(headRect, RectF(0, ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));

    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    footRect = GetChildRect(groupNode, 1);
    footOffsetY = DEVICE_HEIGHT - GetChildRect(frameNode_, 0).Height() - HEADER_MAIN_LENGTH + ITEM_HEIGHT;
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
    UpdateCurrentOffset(ITEM_HEIGHT);
    footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqualRect(footRect, RectF(0, footOffsetY - ITEM_HEIGHT, GROUP_WIDTH, HEADER_MAIN_LENGTH)));
}

/**
 * @tc.name: ListItemGroup004
 * @tc.desc: test lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLanes 2
     * @tc.expected: has 2 lanes items
     */
    constexpr int32_t lanes = 2;
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    listModelNG_1.SetLanes(lanes);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    int32_t groupIndex = 0;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto groupRect = GetChildRect(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, lanes, SPACE, HEADER_MAIN_LENGTH));
    int32_t rows = std::floor(GROUP_ITEM_NUMBER / lanes);
    float groupHeight = HEADER_MAIN_LENGTH * 2 + rows * ITEM_HEIGHT + (rows - 1) * SPACE;
    EXPECT_TRUE(IsEqualRect(groupRect, RectF(0, 0, GROUP_WIDTH, groupHeight)));

    /**
     * @tc.steps: step2. maxLaneLength > GROUP_WIDTH
     */
    float minLaneLength = 220.f;
    float maxLaneLength = 480.f;
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    listModelNG_2.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG_2.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH));
    EXPECT_EQ(GetChildRect(groupNode, 2).Width(), GROUP_WIDTH);

    /**
     * @tc.steps: step3. maxLaneLength < GROUP_WIDTH
     */
    minLaneLength = 220.f;
    maxLaneLength = 300.f;
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    listModelNG_3.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG_3.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    groupIndex = 0;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    EXPECT_TRUE(VerifyGroupItemPosition(groupNode, GROUP_ITEM_NUMBER, DEFAULT_LANES, SPACE, HEADER_MAIN_LENGTH));
    EXPECT_EQ(GetChildRect(groupNode, 2).Width(), maxLaneLength);
}

/**
 * @tc.name: ListItemGroup005
 * @tc.desc: test SetListItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroup005, TestSize.Level1)
{
    /**
     * @tc.steps: step2. V2::ListItemAlign::START
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    listModelNG_1.SetListItemAlign(V2::ListItemAlign::START);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    // scroll to second group
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    int32_t groupIndex = 1;
    auto groupNode = GetChildFrameNode(frameNode_, groupIndex);
    auto listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect, RectF(0, HEADER_MAIN_LENGTH, GROUP_ITEM_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    listModelNG_2.SetListItemAlign(V2::ListItemAlign::CENTER);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect, RectF((GROUP_WIDTH - GROUP_ITEM_WIDTH) / 2, HEADER_MAIN_LENGTH,
        GROUP_ITEM_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    listModelNG_3.SetListItemAlign(V2::ListItemAlign::END);
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    UpdateCurrentOffset(-GetChildRect(frameNode_, 0).Height());
    groupIndex = 1;
    groupNode = GetChildFrameNode(frameNode_, groupIndex);
    listItemRect = GetChildRect(groupNode, 2);
    EXPECT_TRUE(IsEqualRect(listItemRect,
        RectF(GROUP_WIDTH - GROUP_ITEM_WIDTH, HEADER_MAIN_LENGTH, GROUP_ITEM_WIDTH, ITEM_HEIGHT)));
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    CreateListItemGroup(1);
    CreateListItem(TOTAL_NUMBER);
    CreateListItemGroup(1);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 2);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 2);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));

    UpdateCurrentOffset(-ITEM_HEIGHT * (GROUP_ITEM_NUMBER * 2 + TOTAL_NUMBER));
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, -400 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(0.f);
    expectOffset = { 0, -500 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -600 };
    EXPECT_TRUE(IsEqualOverScrollOffset(offset, expectOffset));
}

/**
 * @tc.name: Event001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event001, TestSize.Level1)
{
    Dimension offsetY;
    ScrollState scrollState;
    auto event = [&offsetY, &scrollState](Dimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
    };
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnScroll(event);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_EQ(offsetY.ConvertToPx(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::SCROLL);

    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_EQ(offsetY.ConvertToPx(), ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::FLING);

    UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_ANIMATION);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_ANIMATION_SPRING);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(offsetY.ConvertToPx(), 0);
    EXPECT_EQ(scrollState, ScrollState::IDLE);

    pattern_->UpdateCurrentOffset(ITEM_HEIGHT, SCROLL_FROM_NONE);
    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_EQ(offsetY.ConvertToPx(), -ITEM_HEIGHT);
    EXPECT_EQ(scrollState, ScrollState::IDLE);
}

/**
 * @tc.name: Event002
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event002, TestSize.Level1)
{
    int32_t startIndex;
    int32_t endIndex;
    int32_t centerIndex;
    auto event = [&startIndex, &endIndex, &centerIndex](int32_t start, int32_t end, int32_t center) {
        startIndex = start;
        endIndex = end;
        centerIndex = center;
    };
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnScrollIndex(event);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 0);
    EXPECT_EQ(endIndex, 8);
    EXPECT_EQ(centerIndex, 4);

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(startIndex, 1);
    EXPECT_EQ(endIndex, 9);
    EXPECT_EQ(centerIndex, 5);
}

/**
 * @tc.name: Event003
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event003, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnReachStart(event);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(isTrigger);
}

/**
 * @tc.name: Event004
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event004, TestSize.Level1)
{
    bool isTrigger = false;
    auto event = [&isTrigger]() { isTrigger = true; };
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnReachEnd(event);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    isTrigger = false;
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    EXPECT_FALSE(isTrigger);

    isTrigger = false;
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Event005
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event005, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    listModelNG.SetOnScrollStart(scrollStart);
    listModelNG.SetOnScrollStop(scrollStop);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(isScrollStopCalled);
}

/**
 * @tc.name: Event006
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Event006, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnScrollFrameBegin([](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    });
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    auto scrollable = scrollableEvent->GetScrollable();
    EXPECT_NE(scrollable->scrollFrameBeginCallback_, nullptr);
    RunMeasureAndLayout(frameNode_);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test Event hub
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Run List GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 0), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":0}");

    /**
     * @tc.steps: step2. Run ListItem GetDragExtraParams func.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetChildFrameNode(frameNode_, 0);
    auto itemEventHub = itemFrameNode->GetEventHub<ListItemEventHub>();
    jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 200.f), DragEventType::START);
    EXPECT_NE(jsonStr, "");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 200.f), DragEventType::MOVE);
    EXPECT_NE(jsonStr, "");
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse select
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect001, TestSize.Level1)
{
    CreateSelectableList();

    /**
     * @tc.steps: step1. Select zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());

    /**
     * @tc.steps: step2. Change select zone.
     * @tc.expected: Selected items changed.
     */
    MouseSelect(Offset(200.f, 200.f), Offset(200.f, 300.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 0)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 1)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step3. Click first item.
     * @tc.expected: Each item not selected.
     */
    MouseSelect(Offset(10.f, 10.f), Offset(10.f, 10.f));
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection, select from different directiong
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(120.f, 250.f);
    const Offset LEFT_BOTTOM = Offset(120.f, 350.f);
    const Offset RIGHT_TOP = Offset(360.f, 250.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 350.f);
    CreateSelectableList();

    /**
     * @tc.steps: step1. Select from LEFT_TOP to RIGHT_BOTTOM
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step2. Select from RIGHT_TOP to LEFT_BOTTOM
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step3. Select from LEFT_BOTTOM to RIGHT_TOP
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());

    /**
     * @tc.steps: step4. Select from RIGHT_BOTTOM to LEFT_TOP
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 2)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);

    /**
     * @tc.steps: step1. Create listItem and set an unselectable.
     */
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    for (int32_t index = 0; index < TOTAL_NUMBER; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(FILL_LENGTH);
        if (index == 3) {
            listItemModel.SetSelectable(false);
        }
        if (index == 4) {
            listItemModel.SetSelectCallback(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step2. Select zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(120.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, 3)->IsSelected());
    EXPECT_TRUE(GetChildPattern<ListItemPattern>(frameNode_, 4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test listItem selectable about other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect004, TestSize.Level1)
{
    CreateSelectableList();

    /**
     * @tc.steps: step1. Use RIGHT_BUTTON to select.
     * @tc.expected: Nothing selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset::Zero());
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }

    /**
     * @tc.steps: step2. Use LEFT_BUTTON, but with MouseAction::HOVER to select.
     * @tc.expected: Nothing selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::HOVER);
    info.SetLocalLocation(Offset::Zero());
    pattern_->HandleMouseEventWithoutKeyboard(info);
    for (int32_t index = 0; index < VIEWPORT_NUMBER; index++) {
        EXPECT_FALSE(GetChildPattern<ListItemPattern>(frameNode_, index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scrollable List
     */
    CreateList(TOTAL_NUMBER);
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TOTAL_NUMBER);

    /**
     * @tc.steps: step2. scroll to second item
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER);

    /**
     * @tc.steps: step3. unScrollable List
     */
    CreateList(VIEWPORT_NUMBER);
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), VIEWPORT_NUMBER - 1);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), VIEWPORT_NUMBER);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Scroll to Top.
     */
    CreateList(TOTAL_NUMBER);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_1 = 0;
    exptectActions_1 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_1);

    /**
     * @tc.steps: step2. Scroll to middle.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_2 = 0;
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions_2 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_2);

    /**
     * @tc.steps: step3. Scroll to bottom.
     */
    UpdateCurrentOffset(-ITEM_HEIGHT);
    accessibilityProperty_->ResetSupportAction();
    uint64_t exptectActions_3 = 0;
    exptectActions_3 |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions_3);

    /**
     * @tc.steps: step4. UnScrollable List.
     */
    CreateList(VIEWPORT_NUMBER);
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty003, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);
    auto listItem = GetChildFrameNode(frameNode_, 0);
    auto itemAccessibilityProperty = listItem->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    itemAccessibilityProperty->ResetSupportAction();
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibilityProperty), exptectActions);
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemGroup();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    auto groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 0)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);

    groupAccessibilityProperty =
        GetChildFrameNode(frameNode_, 4)->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), -1);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), -1);
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController001, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    CreateList(itemNumber, Axis::VERTICAL);
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT)));
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT * VIEWPORT_NUMBER)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, (itemNumber - VIEWPORT_NUMBER) * ITEM_HEIGHT)));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->JumpTo(1, false, ScrollAlign::START, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT)));
    controller->JumpTo(0, false, ScrollAlign::START, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController function with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController002, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    CreateList(itemNumber, Axis::HORIZONTAL);
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);
    EXPECT_EQ(controller->GetCurrentOffset(), Offset::Zero());

    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(ITEM_WIDTH, 0)));
    controller->ScrollBy(-ITEM_WIDTH, ITEM_HEIGHT, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(ITEM_WIDTH * VIEWPORT_NUMBER, 0)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset((itemNumber - VIEWPORT_NUMBER) * ITEM_WIDTH, 0)));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    controller->JumpTo(1, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(ITEM_WIDTH, 0)));
    controller->JumpTo(0, false, ScrollAlign::START, -1);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController003, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER, Axis::NONE);
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));
    EXPECT_EQ(controller->GetScrollDirection(), Axis::NONE);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep001, TestSize.Level1)
{
    CreateFocusableList(VIEWPORT_NUMBER, Axis::VERTICAL);

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func width HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep002, TestSize.Level1)
{
    CreateFocusableList(VIEWPORT_NUMBER, Axis::HORIZONTAL);

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep003, TestSize.Level1)
{
    const int32_t groupNumber = 2;
    CreateGroupItemFocusableList(groupNumber, Axis::VERTICAL);

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from bottom of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from top of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step4. GetNextFocusNode from bottom.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode when List has ListItemGroup with HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep004, TestSize.Level1)
{
    const int32_t groupNumber = 2;
    CreateGroupItemFocusableList(groupNumber, Axis::HORIZONTAL);

    /**
     * @tc.steps: step1. GetNextFocusNode from left.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from right of first ListItemGroup.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left of second ListItemGroup.
     */
    currentIndex = 4;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT, currentIndex, 3));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 3));

    /**
     * @tc.steps: step3. GetNextFocusNode from right.
     */
    currentIndex = 7;
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::RIGHT_END, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::SHIFT_TAB, currentIndex, 6));
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. when List has unfocuseable item
     * @tc.expected: The unfocuseable item would be skiped.
     */
    CreateFocusableList(VIEWPORT_NUMBER, Axis::VERTICAL);
    GetChildFocusHub(frameNode_, 1)->SetFocusable(false);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));

    /**
     * @tc.steps: step2. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to last item
     */
    CreateFocusableList(TOTAL_NUMBER, Axis::VERTICAL);
    UpdateCurrentOffset(-ITEM_HEIGHT - 1.f);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT + 1.f)));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step3. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    CreateFocusableList(TOTAL_NUMBER, Axis::VERTICAL);
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, NULL_INDEX));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT * 2)));

    /**
     * @tc.steps: step4. GetNextFocusNode func from bottom boundary item
     * @tc.expected: Scroll to next item
     */
    const float groupHeight = ITEM_HEIGHT * GROUP_ITEM_NUMBER;
    int32_t groupNumber = 3; // create scrollable List
    CreateGroupItemFocusableList(groupNumber, Axis::VERTICAL);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::DOWN, 7, NULL_INDEX));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, groupHeight)));

    /**
     * @tc.steps: step6. GetNextFocusNode func from top boundary item
     * @tc.expected: Scroll to next item
     */
    groupNumber = 3; // create scrollable List
    CreateGroupItemFocusableList(groupNumber, Axis::VERTICAL);
    UpdateCurrentOffset(-groupHeight);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, groupHeight)));
    EXPECT_TRUE(IsEqualNextGroupItemFocusNode(FocusStep::UP, 3, 2));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: FocusStep006
 * @tc.desc: Test List focusing ability with lanes mode and VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep006, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(4);
    CreateListItem(10, Axis::VERTICAL, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep007
 * @tc.desc: Test List focusing ability with lanes mode and HORIZONTAL.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep007, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    listModelNG.SetLanes(4);
    CreateListItem(10, Axis::HORIZONTAL, true);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. GetNextFocusNode from left_top.
     */
    int32_t currentIndex = 0;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, NULL_INDEX));

    /**
     * @tc.steps: step2. GetNextFocusNode from right_top.
     */
    currentIndex = 8;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from left_bottom.
     */
    currentIndex = 3;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 2));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 7));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 2));

    /**
     * @tc.steps: step4. GetNextFocusNode from right_bottom.
     */
    currentIndex = 9;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 8));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 8));

    /**
     * @tc.steps: step5. GetNextFocusNode from middle.
     */
    currentIndex = 5;
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, currentIndex, NULL_INDEX));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, currentIndex, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, currentIndex, 4));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, currentIndex, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, currentIndex, 9));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, currentIndex, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, currentIndex, 4));
}

/**
 * @tc.name: FocusStep008
 * @tc.desc: Test GetListItemGroupParameter function with focus.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and card style ListItemGroup.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItemGroup();
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    ASSERT_NE(frameNode_, nullptr);

    /**
     * @tc.steps: step2. Obtain nodes for items in the group.
     */
    auto group = frameNode_->GetChildAtIndex(0);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(group);
    auto groupItem = group->GetChildAtIndex(0);
    auto groupItemNode = AceType::DynamicCast<FrameNode>(groupItem);

    /**
     * @tc.steps: step3. Call IsListItemGroup and GetListItemGroupParameter func.
     * @tc.expected listItemGroupPara value is equal to expected
     */
    pattern_->IsListItemGroup(0, frameNode_);
    ListItemGroupPara listItemGroupPara;
    listItemGroupPara = pattern_->GetListItemGroupParameter(groupItemNode);
    EXPECT_EQ(listItemGroupPara.itemEndIndex, GROUP_ITEM_NUMBER);
    EXPECT_EQ(listItemGroupPara.displayStartIndex, 0);
    EXPECT_EQ(listItemGroupPara.displayEndIndex, GROUP_ITEM_NUMBER);
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, KeyEvent001, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT * 2)));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    ASSERT_NE(paint, nullptr);
    EXPECT_NE(pattern_->listContentModifier_, nullptr);
    paint = pattern_->CreateNodePaintMethod();
    EXPECT_NE(pattern_->listContentModifier_, nullptr);

    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->GetForegroundDrawFunction(&paintWrapper);
    listPaint->PaintEdgeEffect(&paintWrapper, canvas);
    listPaint->PaintScrollBar(canvas);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod002, TestSize.Level1)
{
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);

    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    listModelNG.SetDivider(itemDivider);
    CreateListItemGroup();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    auto scrollBar = pattern_->GetScrollBar();
    scrollBar->SetScrollable(true);
    scrollBar->normalWidth_ = Dimension(10);

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    listPaint->SetTotalItemCount(10);

    RSCanvas canvas;
    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100, 100));
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdateClipEdge(false);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    listPaint->PaintScrollBar(canvas);
    modifier->onDraw(ctx);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);
    listModelNG.SetDivider(itemDivider);
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    listModelNG.SetLanes(2);
    CreateListItemGroup();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100, 100));
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->PaintScrollBar(canvas);

    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test ListItemGroup paint method
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PaintMethod004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create(V2::ListItemGroupStyle::NONE);
    CreateListItem(TOTAL_NUMBER);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();

    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    RSCanvas canvas;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10.f);
    groupPaint->divider_ = itemDivider;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->lanes_ = 2;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    groupPaint->vertical_ = true;
    groupPaint->PaintDivider(&paintWrapper, canvas);

    EXPECT_TRUE(true);
}

/**
 * @tc.name: ChainAnimation001
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation001, TestSize.Level1)
{
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateChainList(options);

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be SPACE.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, SPACE);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, SPACE);

    /**
     * @tc.steps: step2. When conductivity > 1, intensity > 1.
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation002
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation002, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateChainList(options);

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0, intensity < 0
     * @tc.expected: conductivity/intensity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: ChainAnimation003
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ChainAnimation003, TestSize.Level1)
{
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;
    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
        .stiffness = DEFAULT_STIFFNESS,
        .damping = DEFAULT_DAMPING,
    };
    CreateChainList(options);

    /**
     * @tc.steps: step1. When conductivity == 0, intensity == 0
     * @tc.expected: conductivity/intensity would be itself.
     */
    auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);

    chainAnimation = pattern_->chainAnimation_;
    pattern_->SetChainAnimationOptions(options);
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: Pattern001
 * @tc.desc: Test list_pattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->isMouseEventInit_);
    EXPECT_TRUE(pattern_->isInitialized_);
    EXPECT_TRUE(pattern_->GetScrollableEvent());
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern002, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);

    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Pause();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Stop();
    pattern_->AnimateTo(0, 0, nullptr, true);
    EXPECT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern003, TestSize.Level1)
{
    CreateList(TOTAL_NUMBER);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        { Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    pattern_->OutBoundaryCallback();
    EXPECT_TRUE(pattern_->dragFromSpring_);
}

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex001, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    CreateList(itemNumber);

    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 250.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 9;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 900.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 550.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step5. scroll to middle, first item above viewport
     */
    UpdateCurrentOffset(-800.f);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 800.f)));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 6;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 250.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 800.f)));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    UpdateCurrentOffset(-ITEM_HEIGHT * itemNumber);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step8. Invalid index, index < -1
     */
    index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex with ListItem and lanes > 1
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex002, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    constexpr int32_t lanes = 2;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItem(itemNumber);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. first item in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step2. the item in viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step3. the item below viewport
     */
    index = 16;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step4. last item below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step5. scroll to bottom, first item above viewport
     */
    UpdateCurrentOffset(-ITEM_HEIGHT * itemNumber);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 200.f)));

    /**
     * @tc.steps: step6. the item above viewport
     */
    index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 200.f)));

    /**
     * @tc.steps: step7. last item in viewport
     */
    UpdateCurrentOffset(-ITEM_HEIGHT * itemNumber);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex with ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex003, TestSize.Level1)
{
    constexpr int32_t groupNumber = 5;
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemGroup(groupNumber);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    constexpr float groupHeight = GROUP_ITEM_NUMBER * ITEM_HEIGHT; // 400

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step2. the group in viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step3. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step4. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step5. scroll to middle, first group above viewport
     */
    UpdateCurrentOffset(-groupHeight * 2);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 800.f)));

    /**
     * @tc.steps: step6. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset(0, 800.f)));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset(0, 800.f)));

    /**
     * @tc.steps: step7. scroll to bottom, last item in viewport
     */
    UpdateCurrentOffset(-groupHeight * groupNumber);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, true, ScrollAlign::AUTO, Offset::Zero()));
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex with ListItemGroup and indexInGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex004, TestSize.Level1)
{
    constexpr int32_t groupNumber = 5;
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemGroup(groupNumber);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    constexpr float groupHeight = GROUP_ITEM_NUMBER * ITEM_HEIGHT;
    constexpr int32_t indexInGroup = 2;

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 2;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 400.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 300.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 400.f)));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 1000.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 1000.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 1000.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 1200.f)));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    UpdateCurrentOffset(-groupHeight * groupNumber);
    index = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 1;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 300.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 200.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 400.f)));

    /**
     * @tc.steps: step6. last item in viewport
     */
    UpdateCurrentOffset(-groupHeight * groupNumber);
    index = ListLayoutAlgorithm::LAST_ITEM;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 1000.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 1000.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 1000.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 1200.f)));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with ListItemGroup and indexInGroup and lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndex005, TestSize.Level1)
{
    constexpr int32_t groupNumber = 10;
    constexpr int32_t lanes = 2;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItemGroup(groupNumber);
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    constexpr float groupHeight = GROUP_ITEM_NUMBER * ITEM_HEIGHT / lanes;

    /**
     * @tc.steps: step1. first group in viewport
     */
    int32_t index = 0;
    int32_t indexInGroup = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step2. the group below viewport
     */
    index = 4;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 600.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 350.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 400.f)));

    /**
     * @tc.steps: step3. last group below viewport
     */
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 600.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 700.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 1200.f)));

    /**
     * @tc.steps: step4. scroll to bottom, first group above viewport
     */
    UpdateCurrentOffset(-groupHeight * groupNumber);
    index = 0;
    indexInGroup = 0;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset::Zero()));

    /**
     * @tc.steps: step5. the group above viewport
     */
    index = 2;
    indexInGroup = 1;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 400.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 100.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset::Zero()));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 400.f)));

    /**
     * @tc.steps: step6. last item in viewport
     */
    UpdateCurrentOffset(-groupHeight * groupNumber);
    index = ListLayoutAlgorithm::LAST_ITEM;
    indexInGroup = 3;
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::START, Offset(0, 600.f + 100.f / 3)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::CENTER, Offset(0, 700.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::END, Offset(0, 1200.f)));
    EXPECT_TRUE(ScrollToIndex(index, indexInGroup, ScrollAlign::AUTO, Offset(0, 1200.f)));
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern005, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(80.f);
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    listModelNG.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    listModelNG.SetChainAnimation(true);
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    // Set swiperItem_ to list pattern
    DragSwiperItem(0, 1.f);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->animator_->Resume();
    EXPECT_TRUE(pattern_->animator_->IsRunning());
    pattern_->OnScrollPosition(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    const Offset expectOffset1 = Offset::Zero();
    IsEqualCurrentOffset(expectOffset1);
    EXPECT_TRUE(pattern_->animator_->IsStopped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    const Offset expectOffset2 = Offset(0, 100.f);
    IsEqualCurrentOffset(expectOffset2);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->OnScrollCallback(0, SCROLL_FROM_UPDATE);
    const Offset expectOffset3 = Offset(0, 100.f);
    IsEqualCurrentOffset(expectOffset3);

    /**
     * @tc.steps: step4. When has animator_ and stop, call StopAnimate.
     * @tc.expected: Nothing.
     */
    pattern_->StopAnimate();
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern006, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(2);
    CreateListItem(VIEWPORT_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. When lanes > 1, call GetItemIndexByPosition
     * @tc.expected: Would return correct itemIndex
     */
    const Point point = Point(300.f, 250.f);
    constexpr int32_t expectIndex = 5;
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, expectIndex);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern007, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(VIEWPORT_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEWPORT_NUMBER);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern008, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern009
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. unscrollable List
     */
    CreateList(VIEWPORT_NUMBER);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset::Zero()));

    /**
     * @tc.steps: step1. UpdateCurrentOffset with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    CreateList(TOTAL_NUMBER);
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_START);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT)));
    pattern_->UpdateCurrentOffset(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, ITEM_HEIGHT * 2)));
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. do not set selfIdealSize, 0 listItem
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    GetInstance();
    RunMeasureAndLayout(frameNode_, -1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_NUMBER listItem
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_, -1, -1);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), DEVICE_WIDTH);

    /**
     * @tc.steps: step1. set width Infinity
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_, Infinity<float>(), DEVICE_HEIGHT);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());
}

/**
 * @tc.name: ListSelectForCardModeTest001
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List/ListItemGroup/ListItem.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItem(9);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step2. Click the (0, 0) point of firstItem.
     * @tc.expected: Can not select by click, the item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    ASSERT_NE(frameNode_, nullptr);
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    ASSERT_NE(itemGroup, nullptr);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    ASSERT_NE(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    ASSERT_NE(itemFrameNode, nullptr);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(firstItemPattern, nullptr);
    EXPECT_FALSE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());
}

/**
 * @tc.name: ListSelectForCardModeTest002
 * @tc.desc: Test the card mode for select.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);
    CreateListItem(9);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step2. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st item is selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    ASSERT_NE(frameNode_, nullptr);
    auto itemGroup = frameNode_->GetChildAtIndex(0);
    ASSERT_NE(itemGroup, nullptr);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(itemGroup);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto item = itemGroupFrameNode->GetChildAtIndex(0);
    ASSERT_NE(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    ASSERT_NE(itemFrameNode, nullptr);
    RefPtr<ListItemPattern> firstItemPattern = itemFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(firstItemPattern, nullptr);
    EXPECT_TRUE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());
}

/**
 * @tc.name: ListSelectForCardModeTest003
 * @tc.desc: Test the card mode for select when the 'selectable' of listItem  is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectForCardModeTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 9;

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem and ListItem set to unselectable.
     * @tc.expected: step1. create a card style ListItemGroup success.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create(V2::ListItemGroupStyle::CARD);

    for (int32_t i = 0; i < itemCount; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(ITEM_HEIGHT));
        SetWidth(FILL_LENGTH);
        if (i == 3) {
            listItemModel.SetSelectable(false);
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step2. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The third and fourth listItems cannot be selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(120.f, 350.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(360.f, 450.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);

    /**
     * @tc.steps: step3. Get ListItemGroup frameNode and ListItemPattern.
     * @tc.expected: Get ListItemGroup frameNode/ListItemPattern success, and judge the step2.
     */
    auto itemGroupFrameNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    auto itemFourth = itemGroupFrameNode->GetChildAtIndex(3);
    ASSERT_NE(itemFourth, nullptr);
    auto itemFourthFrameNode = AceType::DynamicCast<FrameNode>(itemFourth);
    ASSERT_NE(itemFourthFrameNode, nullptr);
    RefPtr<ListItemPattern> fourthItemPattern = itemFourthFrameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(fourthItemPattern, nullptr);
    EXPECT_FALSE(fourthItemPattern->IsSelected());

    /**
     * @tc.steps: step4. Release the mouse to deselect.
     * @tc.expected: Release the mouse to deselect.
     */
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern->MarkIsSelected(false);
}

/**
 * @tc.name: ListItemGroupCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));

    listTheme->defaultColor_ = Color::WHITE;
    listTheme->defaultLeftMargin_ = GROUP_MARGIN;
    listTheme->defaultRightMargin_ = GROUP_MARGIN;

    /**
     * @tc.steps: step2. create ListItemGroup.
     * @tc.expected: step2. create a card style ListItemGroup success.
     */
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create(V2::ListItemGroupStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(pattern->GetListItemGroupStyle(), V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(GROUP_MARGIN));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(GROUP_MARGIN));
}

/**
 * @tc.name: ListItemCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->itemDefaultColor_ = Color::WHITE;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
}

/**
 * @tc.name: ListItemCallEventsForCardModeTest001
 * @tc.desc: Test whether the event has been called when listItem is in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemCallEventsForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest001
 * @tc.desc: Test the hover event when the hover status of card mode listItem is true.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemHoverEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->hoverAnimationDuration_ = 250;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to true.
     * @tc.expected: step3. the hover status is true.
     */
    pattern->HandleHoverEvent(true, frameNode);
    EXPECT_TRUE(pattern->isHover_);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest002
 * @tc.desc: Test the hover event when the hover status of card mode listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemHoverEventForCardModeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->hoverAnimationDuration_ = 250;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to false.
     * @tc.expected: step3. the hover status is false.
     */
    pattern->HandleHoverEvent(false, frameNode);
    EXPECT_FALSE(pattern->isHover_);
}

/**
 * @tc.name: ListItemPressEventForCardModeTest001
 * @tc.desc: Test the press event when the TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemPressEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->hoverColor_ = Color::RED;
    listTheme->pressColor_ = Color::BLACK;
    listTheme->hoverToPressAnimationDuration_ = 100;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    auto renderContext = frameNode->GetRenderContext();

    /**
     * @tc.steps: step3. call function HandlePressEvent, set TouchType to DOWN and set hover status is true.
     * @tc.expected: step3. the color is different from the initial color when the listItem is pressed with the mouse.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_EQ(pattern->isPressed_, true);

    /**
     * @tc.steps: step4. call function HandlePressEvent, set TouchType to DOWN and set hover status is false.
     * @tc.expected: step4. the color is different from the initial color when the listItem is pressed with gesture.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_EQ(pattern->isPressed_, true);

    /**
     * @tc.steps: step5. call function HandlePressEvent, set TouchType to UP and set hover status is true.
     * @tc.expected: step5. the color differs from the initial color when mouse hovers over listItem after pressing.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_EQ(pattern->isPressed_, false);

    /**
     * @tc.steps: step6. call function HandlePressEvent, set TouchType to UP and set hover status is false.
     * @tc.expected: step6. the color returns to its original color after pressing on listItem through gestures.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_EQ(pattern->isPressed_, false);
}

/**
 * @tc.name: ListItemDisableEventForCardModeTest001
 * @tc.desc: Test disable event when the enable status of the listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemDisableEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem theme and set default attributes.
     * @tc.expected: step1. create ListItem theme success.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto listTheme = AceType::MakeRefPtr<ListItemTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(listTheme));
    listTheme->disabledAlpha_ = 0.4;

    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success and set enable status to false.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    eventHub->SetEnabled(false);
    pattern->selectable_ = true;

    /**
     * @tc.steps: step3. call function InitDisableEvent.
     * @tc.expected: step3. the background color has been updated and selectable has been set to false.
     */
    pattern->InitDisableEvent();
    EXPECT_FALSE(pattern->selectable_);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ListItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create listItem and initialize related properties.
     */
    ListItemModelNG listItemModel;
    listItemModel.Create();

    /**
     * @tc.steps: step2. Get listItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(listItemPattern, nullptr);
    listItemPattern->SetSelectable(false);
    listItemPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get listItem accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto listItemAccessibilityProperty = frameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    ASSERT_NE(listItemAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When listItem is not Selectable, call the callback function in listItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionClearSelection());

    /**
     * @tc.steps: step5. When listItem is Selectable, call the callback function in listItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    listItemPattern->SetSelectable(true);
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionSelect());
    EXPECT_TRUE(listItemAccessibilityProperty->ActActionClearSelection());
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: List Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();

    /**
     * @tc.steps: step2. Get list frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    listPattern->scrollable_ = false;
    listPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get list accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto listAccessibilityProperty = frameNode->GetAccessibilityProperty<ListAccessibilityProperty>();
    ASSERT_NE(listAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When list is not Scrollable, call the callback function in listAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When list is Scrollable, call the callback function in listAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    listPattern->scrollable_ = true;
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(listAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: ListPattern_ScrollToIndex001
 * @tc.desc: Test ScrollToIndex when smooth is true and index is different value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list item.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    
    /**
     * @tc.steps: step2. Test ScrollToIndex when index is -2.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(-2, true);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::START);
    EXPECT_EQ(pattern_->currentDelta_, 0.0);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step3. Test ScrollToIndex when index is 11.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(11, true);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step4. Test ScrollToIndex when index is -1.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(-1, true);
    EXPECT_EQ(pattern_->targetIndex_, -1);
}

/**
 * @tc.name: ListPattern_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when targetIndex_ have value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization and create list item.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    RunMeasureAndLayout(frameNode_);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(frameNode_->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step2. Assign a value to targetIndex_ and test OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function is called.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->targetIndex_ = VIEWPORT_NUMBER;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    pattern_->targetIndex_ = TOTAL_NUMBER + 1;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    EXPECT_FALSE(pattern_->targetIndex_.has_value());

    /**
     * @tc.steps: step3. Take different values for scrollAlign_ and test OnDirtyLayoutWrapperSwap.
     * @tc.expected: Related function is called.
     */
    pattern_->targetIndex_ = VIEWPORT_NUMBER -1;
    pattern_->scrollAlign_ = ScrollAlign::END;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
}

/**
 * @tc.name: ListLayoutAlgorithm_OffScreenLayoutDirection001
 * @tc.desc: Test OffScreenLayoutDirection when targetIndex_ is in a different state.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_OffScreenLayoutDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    constexpr float space = 5.0f;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>();

    /**
     * @tc.steps: step2. When targetIndex_ is nullptr and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    /**
     * @tc.steps: step3. When targetIndex_ is nullptr and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    /**
     * @tc.steps: step4. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step5. Assign a value to targetIndex_ and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);

    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER + 1);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_TRUE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_FALSE(listLayoutAlgorithm->backwardFeature_);
}

/**
 * @tc.name: ListLayoutAlgorithm_OffScreenLayoutDirection002
 * @tc.desc: Test OffScreenLayoutDirection When the value of targetIndex_ is greater than endIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_OffScreenLayoutDirection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    constexpr float space = 5.0f;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm = AceType::MakeRefPtr<ListLayoutAlgorithm>();

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 10; i < 20; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }

    /**
     * @tc.steps: step3. Assign a value to targetIndex_ and test OffScreenLayoutDirection.
     * @tc.expected: Related function is called.
     */
    listLayoutAlgorithm->SetTargetIndex(TOTAL_NUMBER - 2);
    listLayoutAlgorithm->OffScreenLayoutDirection();
    EXPECT_FALSE(listLayoutAlgorithm->forwardFeature_);
    EXPECT_TRUE(listLayoutAlgorithm->backwardFeature_);
}
 /**
 * @tc.name: ListPositionControllerTest001
 * @tc.desc: Test PositionController function with smooth.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func when smooth is false or true.
     * @tc.expected: Return true.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, true));

    /**
     * @tc.steps: step3. Call func when duration is positive.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, true));
}

/**
 * @tc.name: ListPositionControllerTest002
 * @tc.desc: Test PositionController function with ICurve.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Create ICurve.
     */
    RefPtr<Curve> curve;
    std::string icurveString = "spring(7.000000,1.000000,227.000000,33.000000)";
    curve = Framework::CreateCurve(icurveString);

    /**
     * @tc.steps: step3. Call func when the duration and curve are valid.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: ListPositionControllerTest003
 * @tc.desc: Test PositionController function with build-in curve.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Create build-in curve.
     */
    RefPtr<Curve> curve = Curves::EASE_IN;

    /**
     * @tc.steps: step3. Call func when the duration and curve are valid.
     * @tc.expected: Return true.
     */
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

/**
 * @tc.name: ListPositionControllerTest004
 * @tc.desc: Test IsAtEnd function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    EXPECT_FALSE(scrollController->IsAtEnd());

    const float delta = 200;
    UpdateCurrentOffset(-delta);
    EXPECT_TRUE(scrollController->IsAtEnd());
}

/**
 * @tc.name: AccessibilityEvent001
 * @tc.desc: Test AddStopListener callBack in animator
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();

    /**
     * @tc.steps: step2. Call NotifyStopListener func.
     * @tc.expected isScrollEnd_ is true
     */
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->animator_->NotifyStopListener();
    EXPECT_TRUE(pattern_->isScrollEnd_);
}

/**
 * @tc.name: ScrollToIndexAlign001
 * @tc.desc: Test ScrollToIndex with assigning align
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ScrollToIndexAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list and initialize related properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(0);
    CreateListItem(TOTAL_NUMBER);
    GetInstance();
    RunMeasureAndLayout(frameNode_);

    /**
     * @tc.steps: step2. Call ScrollToIndex func.
     * @tc.expected index and align is accurate.
     */
    pattern_->ScrollToIndex(TOTAL_NUMBER - 2, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->jumpIndex_, TOTAL_NUMBER - 2);
    EXPECT_FALSE(pattern_->targetIndex_.has_value());
    
    /**
     * @tc.steps: step3. Measure and layout.
     * @tc.expected: Related function is called and layout is accurate.
     */
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    RunMeasureAndLayout(frameNode_);
    pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config);
    EXPECT_NE(pattern_->GetStartIndex(), 0);
    EXPECT_EQ(pattern_->GetEndIndex(), TOTAL_NUMBER - 2);
    EXPECT_EQ(pattern_->itemPosition_.rbegin()->second.endPos, DEVICE_HEIGHT);
    
    /**
     * @tc.steps: step4. Take different values for index, smooth and scrollAlign_ and test.
     * @tc.expected: Related function is called.
     */
    pattern_->ScrollToIndex(TOTAL_NUMBER - 1, true, ScrollAlign::AUTO);
    EXPECT_FALSE(pattern_->jumpIndex_.has_value());
    EXPECT_EQ(pattern_->targetIndex_, TOTAL_NUMBER - 1);
    EXPECT_EQ(pattern_->scrollAlign_, ScrollAlign::AUTO);
    RunMeasureAndLayout(frameNode_);
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    pattern_->scrollAlign_ = ScrollAlign::END;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    pattern_->scrollAlign_ = ScrollAlign::CENTER;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));
    pattern_->scrollAlign_ = ScrollAlign::START;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(frameNode_, config));

    /**
     * @tc.steps: step5. Call CalculateEstimateOffset in listLayoutAlgorithm.
     * @tc.expected: Related function is called.
     */
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(listLayoutAlgorithm, nullptr);
    listLayoutAlgorithm->jumpIndex_ = 1;
    listLayoutAlgorithm->scrollAlign_ = ScrollAlign::AUTO;
    listLayoutAlgorithm->scrollAutoType_ = ScrollAutoType::START;
    listLayoutAlgorithm->CalculateEstimateOffset(ScrollAlign::AUTO);
    EXPECT_NE(listLayoutAlgorithm->estimateOffset_, 0.0f);
    listLayoutAlgorithm->itemPosition_.clear();
    listLayoutAlgorithm->CalculateEstimateOffset(ScrollAlign::AUTO);
    EXPECT_EQ(listLayoutAlgorithm->estimateOffset_, 0.0f);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset001
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is start.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::START);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset002
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is center.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::CENTER);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);
}

/**
 * @tc.name: ListLayoutAlgorithm_FixPredictSnapOffset003
 * @tc.desc: Test FixPredictSnapOffset when the scrollSnapAlign is end.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListLayoutAlgorithm_FixPredictSnapOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    auto listLayoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);

    /**
     * @tc.steps: step2. Creat itemPosition_.
     */
    float startPos = 0.0f;
    float endPos = 0.0f;
    float mainLen = 20.0f;
    bool isGroup = false;
    for (int i = 0; i < 10; i++) {
        startPos = endPos;
        listLayoutAlgorithm->itemPosition_[i] = { startPos, endPos, isGroup };
        endPos = startPos + mainLen;
    }
    /**
     * @tc.steps: step3. Set predictSnapOffset then call FixPredictSnapOffset and then get
     *            predictSnapOffset to check value.
     */
    listLayoutAlgorithm->SetSpaceWidth(5);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(20.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);

    listLayoutAlgorithm->SetTotalOffset(10.0f);
    listLayoutAlgorithm->SetPredictSnapOffset(10.0f);
    listLayoutAlgorithm->FixPredictSnapOffset(layoutProperty_);
    EXPECT_EQ(listLayoutAlgorithm->GetPredictSnapOffset().value(), 10);
}

/**
 * @tc.name: ListPattern_UpdateScrollSnap001
 * @tc.desc: Test UpdateScrollSnap.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_UpdateScrollSnap001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    pattern_->AnimateTo(0, 0, nullptr, true);
    pattern_->UpdateScrollSnap();
    EXPECT_FALSE(pattern_->predictSnapOffset_.has_value());
    pattern_->animator_->Stop();
    pattern_->UpdateScrollSnap();
    EXPECT_EQ(pattern_->predictSnapOffset_.value(), 0.0);
}

/**
 * @tc.name: ListPattern_NeedScrollSnapAlignEffect001
 * @tc.desc: Test NeedScrollSnapAlignEffect.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_NeedScrollSnapAlignEffect001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    EXPECT_FALSE(pattern_->NeedScrollSnapAlignEffect());
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::START);
    EXPECT_TRUE(pattern_->NeedScrollSnapAlignEffect());
}
/**
 * @tc.name: ListPattern_SetFriction001
 * @tc.desc: Test SetFriction:friction shouled be more than 0.0,if out of range,should be default value.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_SetFriction001, TestSize.Level1)
{
    constexpr double friction = -1;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetFriction(friction);
    GetInstance();
    /**
     * @tc.expected: friction shouled be more than 0.0,if out of range,should be default value.
     */
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 0.6);
}

/**
 * @tc.name: ListPattern_SetFriction002
 * @tc.desc: Test SetFriction.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPattern_SetFriction002, TestSize.Level1)
{
    constexpr double friction = 10;
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetFriction(friction);
    GetInstance();
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 10);
}
} // namespace OHOS::Ace::NG

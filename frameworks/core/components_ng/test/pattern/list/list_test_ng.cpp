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

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#define private public
#define protected public
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
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_LISTITEM_TOTAL_COUNT = 10;
constexpr int32_t DEFAULT_LISTITEM_VIEWPORT_COUNT = 8;
constexpr float DEFAULT_LISTITEM_VERTICAL_LENGTH = 100.f;
constexpr float DEFAULT_LISTITEM_HORIZONTAL_LENGTH = 60.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr Dimension FILL_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr float DEFAULT_HEADER_MAIN_LENGTH = 50.f;
constexpr int32_t DEFAULT_LANES = 1;
constexpr float DEFAULT_INTERVAL = 0;
constexpr int32_t DEFAULT_STARTINDEX = 0;
constexpr float LISTITEM_NODE_WIDTH = 80.f;
constexpr float START_NODE_SIZE = 80.f;
constexpr float END_NODE_SIZE = 100.f;
constexpr Dimension DELETE_AREA_DISTANCE = Dimension(50, DimensionUnit::VP);
constexpr float MOVE_DELTA = 80.f;
constexpr float MOVE_DELTA2 = 100.f;
constexpr float MOVE_DELTA3 = 20.f;
} // namespace

class ListTestNg : public testing::Test {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateList(int32_t number = DEFAULT_LISTITEM_TOTAL_COUNT);
    void CreateListItemGroup(int32_t GroupCount);
    void CreateListItem(int32_t itemCount = DEFAULT_LISTITEM_TOTAL_COUNT,
        Axis Direction = Axis::VERTICAL, bool focusable = false);
    void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    void CreateListItemWithSwipeActionItem(std::function<void()> builderAction, bool useDefaultDeleteAnimation,
        OnDeleteEvent onDelete, OnEnterDeleteAreaEvent onEnterDeleteArea, OnExitDeleteAreaEvent onExitDeleteArea,
        const Dimension& length, bool isStartArea, V2::SwipeEdgeEffect effect);
    RefPtr<LayoutWrapper> RunMeasureAndLayout();
    RefPtr<GeometryNode> GetChildGeometryNode(const RefPtr<FrameNode>& frameNode, int32_t index);
    RefPtr<FrameNode> GetChildFrameNode(int32_t index);
    RefPtr<FocusHub> GetChildFocusHub(int32_t index);
    RefPtr<ListItemPattern> GetItemPattern(int32_t index);
    RefPtr<ListItemGroupPattern> GetItemGroupPattern(int32_t index);
    void ListItemSwipeMoveAndLayout(const RefPtr<ListItemPattern>& itemPattern, float moveDelta);
    std::function<void()> GetDefaultSwiperBuilder(float crossSize, bool spring);
    std::function<void()> GetDefaultHeaderBuilder();
    testing::AssertionResult VerifyItemPosition(int32_t expectCount, int32_t lanes = DEFAULT_LANES,
        float interval = DEFAULT_INTERVAL, int32_t startIndex = DEFAULT_STARTINDEX);
    testing::AssertionResult VerifyGroupItemPosition(int32_t groupIndex, int32_t expectCount,
        int32_t lanes = DEFAULT_LANES, float interval = DEFAULT_INTERVAL);
    testing::AssertionResult IsEqualNextFocusNode(FocusStep step, int32_t currentIndex, int32_t nextIndex = -1);
    testing::AssertionResult IsEqualCurrentOffset(Offset expectOffset);
    void MouseSelect(Offset start, Offset end);
    void MouseSelectRelease();
    void UpdateCurrentOffset(float offset);
    void DragSwiperItem(int32_t index, GestureEvent info);

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
    // set buttonTheme to themeManager before using themeManager to get buttonTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
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

void ListTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ListTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void ListTestNg::CreateList(int32_t number)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(number);
    GetInstance();
    RunMeasureAndLayout();
}

void ListTestNg::CreateListItemGroup(int32_t GroupCount)
{
    for (int32_t index = 0; index < GroupCount; index++) {
        ListItemGroupModelNG listItemGroupModel;
        listItemGroupModel.Create();
        CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItem(int32_t itemCount, Axis Direction, bool focusable)
{
    for (int32_t index = 0; index < itemCount; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        if (Direction == Axis::VERTICAL) {
            SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
            SetWidth(FILL_LENGTH);
        } else {
            SetWidth(Dimension(DEFAULT_LISTITEM_HORIZONTAL_LENGTH));
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
    SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
    listItemModel.SetSwiperAction(std::move(startAction), std::move(endAction), effect);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
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
    SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
    SetWidth(FILL_LENGTH);
    listItemModel.SetSwiperAction(nullptr, nullptr, effect);
    listItemModel.SetDeleteArea(std::move(builderAction), useDefaultDeleteAnimation, std::move(onDelete),
        std::move(onEnterDeleteArea), std::move(onExitDeleteArea), length, isStartArea);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
        SetWidth(FILL_LENGTH);
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

RefPtr<LayoutWrapper> ListTestNg::RunMeasureAndLayout()
{
    RefPtr<LayoutWrapper> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

RefPtr<GeometryNode> ListTestNg::GetChildGeometryNode(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto item = frameNode->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetGeometryNode();
}

RefPtr<FrameNode> ListTestNg::GetChildFrameNode(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    return AceType::DynamicCast<FrameNode>(item);
}

RefPtr<ListItemPattern> ListTestNg::GetItemPattern(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetPattern<ListItemPattern>();
}

RefPtr<FocusHub> ListTestNg::GetChildFocusHub(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetOrCreateFocusHub();
}

RefPtr<ListItemGroupPattern> ListTestNg::GetItemGroupPattern(int32_t index)
{
    auto item = frameNode_->GetChildAtIndex(index);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetPattern<ListItemGroupPattern>();
}

void ListTestNg::ListItemSwipeMoveAndLayout(const RefPtr<ListItemPattern>& itemPattern, float moveDelta)
{
    GestureEvent info;
    info.SetMainDelta(moveDelta);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout();
}

std::function<void()> ListTestNg::GetDefaultSwiperBuilder(float crossSize, bool spring)
{
    return [crossSize, spring]() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
        if (spring) {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetWidth(Dimension(crossSize));
            SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
            ViewStackProcessor::GetInstance()->Pop();
        } else {
            SetWidth(Dimension(crossSize));
        }
    };
}

std::function<void()> ListTestNg::GetDefaultHeaderBuilder()
{
    return []() {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetWidth(FILL_LENGTH);
        SetHeight(Dimension(DEFAULT_HEADER_MAIN_LENGTH));
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
        float startPos = (index / lanes) * (DEFAULT_LISTITEM_VERTICAL_LENGTH + interval);
        float endPos = startPos + DEFAULT_LISTITEM_VERTICAL_LENGTH;
        if (!NearEqual(listItem.startPos, startPos) || !NearEqual(listItem.endPos, endPos)) {
            return testing::AssertionFailure() << "Index: " << index <<
                " ItemPosition: (" << listItem.startPos << " - " << listItem.endPos << ")"
                " != expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::VerifyGroupItemPosition(
    int32_t groupIndex, int32_t expectCount, int32_t lanes, float interval)
{
    if (lanes < 1) {
        return testing::AssertionFailure() << "lanes < 1";
    }
    auto itemGroupPattern = GetItemGroupPattern(groupIndex);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    for (int32_t index = 0; index < expectCount; index++) {
        auto listItem = itemPosition[index];
        float startPos = (index / lanes) * (DEFAULT_LISTITEM_VERTICAL_LENGTH + interval);
        float endPos = startPos + DEFAULT_LISTITEM_VERTICAL_LENGTH;
        if (!NearEqual(listItem.first, startPos) || !NearEqual(listItem.second, endPos)) {
            return testing::AssertionFailure() << "Index: " << index <<
                " Group ItemPosition: (" << listItem.first << " - " << listItem.second << ")"
                " != expectPosition: (" << startPos << " - " << endPos << ")";
        }
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualNextFocusNode(
    FocusStep step, int32_t currentIndex, int32_t nextIndex)
{
    RefPtr<FocusHub> currentFocusNode = GetChildFocusHub(currentIndex);
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextIndex == -1 && nextFocusNode != nullptr) {
        return testing::AssertionFailure() << "Next FocusNode is not null.";
    }
    if (nextIndex != -1 && nextFocusNode != GetChildFocusHub(nextIndex)) {
        return testing::AssertionFailure() << "Get wrong next FocusNode.";
    }
    return testing::AssertionSuccess();
}

testing::AssertionResult ListTestNg::IsEqualCurrentOffset(Offset expectOffset)
{
    RunMeasureAndLayout();
    Offset currentOffset = pattern_->GetCurrentOffset();
    if (expectOffset == currentOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() <<
        "GetCurrentOffset(): " << currentOffset.ToString() <<
        " But expect offset: " << expectOffset.ToString();
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
}

void ListTestNg::MouseSelectRelease()
{
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
}

void ListTestNg::UpdateCurrentOffset(float offset)
{
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
}

void ListTestNg::DragSwiperItem(int32_t index, GestureEvent info)
{
    auto itemPattern = GetItemPattern(index);
    itemPattern->HandleDragStart(info);
    itemPattern->HandleDragUpdate(info);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    RunMeasureAndLayout();
    itemPattern->HandleDragEnd(info);
}

/**
 * @tc.name: Properties001
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Properties001, TestSize.Level1)
{
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10);
    itemDivider.startMargin = Dimension(0);
    itemDivider.endMargin = Dimension(0);
    itemDivider.color = Color(0x000000);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(10));
    listModelNG.SetInitialIndex(0);
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetListDirection(Axis::VERTICAL);
    listModelNG.SetScrollBar(Ace::DisplayMode::ON);
    listModelNG.SetEdgeEffect(EdgeEffect::NONE);
    listModelNG.SetEditMode(true);
    listModelNG.SetChainAnimation(true);
    listModelNG.SetLanes(3);
    listModelNG.SetLaneMinLength(Dimension(40));
    listModelNG.SetLaneMaxLength(Dimension(60));
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    listModelNG.SetCachedCount(10);
    listModelNG.SetSticky(V2::StickyStyle::HEADER);
    listModelNG.SetMultiSelectable(true);
    listModelNG.SetDivider(itemDivider);
    GetInstance();
    RunMeasureAndLayout();

    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Properties002
 * @tc.desc: Test List layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Properties002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();

    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    layoutProperty_->UpdateEdgeEffect(EdgeEffect::FADE);
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::FOOTER);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    layoutProperty_->UpdateStickyStyle(V2::StickyStyle::BOTH);
    layoutProperty_->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: Properties003
 * @tc.desc: Test ListItem layout properties.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Properties003, TestSize.Level1)
{
    ListItemModelNG listItemModel;
    listItemModel.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(element);
    auto itemLayoutProperty = itemFrameNode->GetLayoutProperty<ListItemLayoutProperty>();

    auto json = JsonUtil::Create(true);
    itemLayoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    itemLayoutProperty->UpdateStickyMode(V2::StickyMode::NORMAL);
    itemLayoutProperty->UpdateEditMode(V2::EditMode::NONE);
    itemLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    itemLayoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    itemLayoutProperty->UpdateStickyMode(V2::StickyMode::OPACITY);
    itemLayoutProperty->UpdateEditMode(V2::EditMode::MOVABLE);
    itemLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    itemLayoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    itemLayoutProperty->UpdateEditMode(V2::EditMode::DELETABLE);
    itemLayoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    itemLayoutProperty->UpdateEditMode(V2::EditMode::DELETABLE | V2::EditMode::MOVABLE);
    itemLayoutProperty->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, space));
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

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    listModelNG.SetDivider(itemDivider);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT, 1, strokeWidth));
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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, DEFAULT_INTERVAL, initIndex));
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
    RunMeasureAndLayout();

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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, DEFAULT_INTERVAL, expectStartIndex));
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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT));
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
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(expectItemCount, lanes, DEFAULT_INTERVAL, expectStartIndex));
}

/**
 * @tc.name: AttrScroller001
 * @tc.desc: Test property about scroller,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrScroller001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->positionController_, nullptr);
}

/**
 * @tc.name: AttrListDirection001
 * @tc.desc: Test property about listDirection,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrListDirection001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, strokeWidth));
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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

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
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    RefPtr<ScrollBar> scrollBar = pattern_->GetScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::AUTO);
}

/**
 * @tc.name: AttrEdgeEffect001
 * @tc.desc: Test property about edgeEffect,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrEdgeEffect001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetEdgeEffect(EdgeEffect::FADE);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    auto scrollEffect = pattern_->GetScrollEdgeEffect();
    ASSERT_NE(scrollEffect, nullptr);
}

/**
 * @tc.name: AttrChainAnimation001
 * @tc.desc: Test property about chainAnimation,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrChainAnimation001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->chainAnimation_, nullptr);
}

/**
 * @tc.name: AttrMultiSelectable001
 * @tc.desc: Test property about multiSelectable,
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrMultiSelectable001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(pattern_->multiSelectable_);
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
    RunMeasureAndLayout();

    constexpr int32_t expectItemCount1 = 16;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount1, lanes));

    // Scroll bottom
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH * 3;
    UpdateCurrentOffset(scrollOffset);

    constexpr int32_t startIndex = 4;
    constexpr int32_t expectItemCount2 = 15;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount2, lanes, DEFAULT_INTERVAL, startIndex));
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
    constexpr int32_t expectItemCount = 16;
    constexpr int32_t expectLanes = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would self-adaption.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        auto geometryNode = GetChildGeometryNode(frameNode_, index);
        auto width = geometryNode->GetFrameSize().Width();
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
    constexpr int32_t expectItemCount = 16;
    constexpr int32_t expectLanes = 2;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_TRUE(VerifyItemPosition(expectItemCount, expectLanes));

    /**
     * @tc.steps: step1. Check ListItem width.
     * @tc.expected: ListItem width would be minLaneLength.
     */
    for (int32_t index = 0; index < expectItemCount; index++) {
        auto geometryNode = GetChildGeometryNode(frameNode_, index);
        auto width = geometryNode->GetFrameSize().Width();
        EXPECT_FLOAT_EQ(width, minLaneLength);
    }
}

/**
 * @tc.name: AttrLanes004
 * @tc.desc: Test LayoutProperty about lanes with ListItemGroup,
 * ListItemGroup is unchanged, but ListItem would be affected by lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes004, TestSize.Level1)
{
    constexpr int32_t lanes = 2;
    constexpr int32_t groupCount = 1;
    constexpr int32_t expectItemCount = 8;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItemGroup(groupCount);
    GetInstance();
    RunMeasureAndLayout();

    constexpr int32_t groupIndex = 0;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex, expectItemCount, lanes));
}

/**
 * @tc.name: AttrLanes005
 * @tc.desc: Test LayoutProperty about minLength, maxLength with ListItemGroup,
 * when ListItemGroup width less than List, the columns of ListItem in group would not equal to outside
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AttrLanes005, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 480.f;
    constexpr int32_t groupWidth = 400.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));

    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    SetWidth(Dimension(groupWidth));
    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
    ViewStackProcessor::GetInstance()->Pop();

    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT * 2);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Check ListItem in group.
     * @tc.expected: ListItem columns would be 1.
     */
    constexpr int32_t groupIndex = 0;
    constexpr int32_t expectItemCount1 = 8;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex, expectItemCount1));

    // Scroll bottom
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH * 8;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. Check ListItem out of group.
     * @tc.expected: ListItem columns would be 2.
     */
    constexpr int32_t expectItemCount2 = DEFAULT_LISTITEM_VIEWPORT_COUNT * 2;
    constexpr int32_t expectLanes2 = 2;
    constexpr int32_t expectStartIndex2 = 1;
    EXPECT_TRUE(VerifyItemPosition(expectItemCount2, expectLanes2, DEFAULT_INTERVAL, expectStartIndex2));
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
    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        auto geometryNode = GetChildGeometryNode(frameNode_, index);
        float offsetX = geometryNode->GetFrameOffset().GetX();
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
    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        auto geometryNode = GetChildGeometryNode(frameNode_, index);
        float offsetX = geometryNode->GetFrameOffset().GetX();
        float expectOffsetX = (DEFAULT_ROOT_WIDTH - itemWidth) / 2;
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
    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetWidth(Dimension(itemWidth));
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    RunMeasureAndLayout();

    for (int32_t index = 0; index < DEFAULT_LISTITEM_TOTAL_COUNT; index++) {
        auto geometryNode = GetChildGeometryNode(frameNode_, index);
        float offsetX = geometryNode->GetFrameOffset().GetX();
        float expectOffsetX = DEFAULT_ROOT_WIDTH - itemWidth;
        EXPECT_EQ(offsetX, expectOffsetX);
    }
}

/**
 * @tc.name: ListItemAttrSwiperTest001
 * @tc.desc: Set the swiperAction Attribute for ListItem, set startNode and EdgeEffect is none, List cannot swiper Left
 * but can swiper right.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest001, TestSize.Level1)
{
    constexpr float startNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(startNodeSize, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check result.
     * @tc.expected: StartNode is not measure and layout
     */
    auto itemPattern = GetItemPattern(0);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.Width(), DEFAULT_ROOT_WIDTH);
    EXPECT_FLOAT_EQ(childRect.GetX(), 0);
    auto startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), 0);

    /**
     * @tc.steps: step3. move left 45px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode is not measure and layout
     */
    constexpr float MOVE_DELTA1 = -45.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), 0);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), 0);

    /**
     * @tc.steps: step4. move right 45px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 45px - startNodeSize
     */
    constexpr float MOVE_DELTA2 = 45.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), MOVE_DELTA2);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), startNodeSize);
    EXPECT_FLOAT_EQ(startRect.GetX(), MOVE_DELTA2 - startNodeSize);

    /**
     * @tc.steps: step5. continue move right 45px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 0, child node position is startNodeSize
     */
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), startNodeSize);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), startNodeSize);
    EXPECT_FLOAT_EQ(startRect.GetX(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest002
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode and edge effect is none.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest002, TestSize.Level1)
{
    constexpr float endNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(endNodeSize, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check result.
     * @tc.expected: EndNode is not measure and layout
     */
    auto itemPattern = GetItemPattern(0);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.Width(), DEFAULT_ROOT_WIDTH);
    EXPECT_FLOAT_EQ(childRect.GetX(), 0);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), 0);

    /**
     * @tc.steps: step3. move right 45px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode is not measure and layout
     */
    constexpr float MOVE_DELTA1 = 45.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), 0);
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), 0);

    /**
     * @tc.steps: step4. move left 45px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is DEFAULT_ROOT_WIDTH - 45px
     */
    constexpr float MOVE_DELTA2 = -45.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), MOVE_DELTA2);
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), endNodeSize);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH + MOVE_DELTA2);

    /**
     * @tc.steps: step5. continue move left 45px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is -endNodeSize, child node position
     *     is DEFAULT_ROOT_WIDTH - endNodeSize
     */
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), -endNodeSize);
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), endNodeSize);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH - endNodeSize);
}

/**
 * @tc.name: ListItemAttrSwiperTest003
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and edge effect is spring,
 * move friction take effect when moving to the left.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest003, TestSize.Level1)
{
    constexpr float startNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(startNodeSize, false);
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Move left 20px twice.
     * @tc.expected: Move friction take effect
     */
    auto itemPattern = GetItemPattern(0);
    constexpr float MOVE_DELTA1 = -20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    float expOffset = (ListItemPattern::CalculateFriction(-MOVE_DELTA1 / DEFAULT_ROOT_WIDTH) + 1) * MOVE_DELTA1;
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest004
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode and edge effect is spring,
 * move friction take effect when moving to the right.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest004, TestSize.Level1)
{
    constexpr float endNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(endNodeSize, false);
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Move right 20px twice.
     * @tc.expected: Move friction take effect
     */
    auto itemPattern = GetItemPattern(0);
    constexpr float MOVE_DELTA1 = 20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    float expOffset = (ListItemPattern::CalculateFriction(MOVE_DELTA1 / DEFAULT_ROOT_WIDTH) + 1) * MOVE_DELTA1;
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest005
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and edge effect is spring.
 *  move friction take effect when moving to the left distance great than startNode size.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest005, TestSize.Level1)
{
    constexpr float startNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(startNodeSize, true);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the left distance great than endNode size, check endNode position.
     */
    auto itemPattern = GetItemPattern(0);
    constexpr float MOVE_DELTA1 = 100.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    constexpr float MOVE_DELTA2 = 20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA2 / (DEFAULT_ROOT_WIDTH - startNodeSize));
    float expOffset = factor * MOVE_DELTA2 + MOVE_DELTA1;
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), expOffset);
    EXPECT_FLOAT_EQ(endRect.GetX(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest006
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode and edge effect is spring.
 *  move friction take effect when moving to the left distance great than endNode size.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest006, TestSize.Level1)
{
    constexpr float endNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(endNodeSize, true);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the right distance great than endNode size, check endNode position.
     */
    auto itemPattern = GetItemPattern(0);
    constexpr float MOVE_DELTA1 = -100.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    constexpr float MOVE_DELTA2 = -20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(-MOVE_DELTA2 / (DEFAULT_ROOT_WIDTH - endNodeSize));
    float expOffset = factor * MOVE_DELTA2 + MOVE_DELTA1;
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), -expOffset);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH + expOffset);
}

/**
 * @tc.name: ListItemAttrSwiperTest007
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and endNode.
 * Drag the ListItem left or right to obtain the correct SwipeIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest007, TestSize.Level1)
{
    auto builder = GetDefaultSwiperBuilder(LISTITEM_NODE_WIDTH, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. move to 30px.
     * @tc.expected: swiper to startNode
     */
    GestureEvent info;
    info.SetMainDelta(30.f);
    DragSwiperItem(0, info);
    auto itemPattern = GetItemPattern(0);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. move to 50px.
     * @tc.expected: swiper to childNode
     */
    info.SetMainDelta(20.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. move to -30px.
     * @tc.expected: swiper to childNode
     */
    info.SetMainDelta(-80.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. move to -50px.
     * @tc.expected: swiper to childNode
     */
    info.SetMainDelta(-20.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step6. move to 30px.
     * @tc.expected: swiper to childNode
     */
    info.SetMainDelta(80.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step7. move to -30px.
     * @tc.expected: swiper to childNode
     */
    info.SetMainDelta(-60.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step8. move to 30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
    info.SetMainDelta(60.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ListItemAttrSwiperTest008
 * @tc.desc: Set the swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper right great than startNode size, if great than startNode size +
 * deleteAreaDistance, it will adjust to startNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. move right 80px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 80px - startNodeSize
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), MOVE_DELTA);
    auto startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), START_NODE_SIZE);
    EXPECT_FLOAT_EQ(startRect.GetX(), MOVE_DELTA - START_NODE_SIZE);

    /**
     * @tc.steps: step3. continue move right 80px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is deleteAreaDistance, child node position is startNodeSize +
     * deleteAreaDistance
     */
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), START_NODE_SIZE + static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), START_NODE_SIZE);
    EXPECT_FLOAT_EQ(startRect.GetX(), static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
}

/**
 * @tc.name: ListItemAttrSwiperTest009
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::None);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. move left 100px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is DEFAULT_ROOT_WIDTH - 100px
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA2);
    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), -MOVE_DELTA2);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), END_NODE_SIZE);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH - MOVE_DELTA2);

    /**
     * @tc.steps: step3. continue move left 100px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is DEFAULT_ROOT_WIDTH - endNodeSize - deleteAreaDistance, child node
     * position is endNodeSize + deleteAreaDistance
     */
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA2);
    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), -END_NODE_SIZE - static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), END_NODE_SIZE);
    EXPECT_FLOAT_EQ(
        endRect.GetX(), DEFAULT_ROOT_WIDTH - END_NODE_SIZE - static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
}

/**
 * @tc.name: ListItemAttrSwiperTest010
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, true);

    CreateListItemWithSwipeActionItem(
        startFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the right distance great than startNode size + deleteAreaDistance, check startNode
     * position.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    ListItemSwipeMoveAndLayout(itemPattern, static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA3);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA3 / (DEFAULT_ROOT_WIDTH - START_NODE_SIZE));
    float expOffset = factor * MOVE_DELTA3 + MOVE_DELTA2 + static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx());
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), expOffset);
    EXPECT_FLOAT_EQ(startRect.GetX(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest011
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, true);

    CreateListItemWithSwipeActionItem(
        endFunc, true, nullptr, nullptr, nullptr, DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the left distance great than endNode size + deleteAreaDistance, check startNode
     * position.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA2 - MOVE_DELTA3);
    ListItemSwipeMoveAndLayout(itemPattern, -static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA3);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA3 / (DEFAULT_ROOT_WIDTH - END_NODE_SIZE));
    float expOffset =
        factor * -MOVE_DELTA3 - MOVE_DELTA2 - MOVE_DELTA3 - static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx());
    EXPECT_FLOAT_EQ(childRect.GetX(), expOffset);
    auto endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    auto endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), -expOffset);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH + expOffset);
}

/**
 * @tc.name: ListItemAttrSwiperTest012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    bool isEnterStartDeleteAreaCalled = false;
    bool isExitStartDeleteAreaCalled = false;
    auto enterStartDeleteArea = [&isEnterStartDeleteAreaCalled]() { isEnterStartDeleteAreaCalled = true; };
    auto exitStartDeleteArea = [&isExitStartDeleteAreaCalled]() { isExitStartDeleteAreaCalled = true; };
    CreateListItemWithSwipeActionItem(builder, true, nullptr, enterStartDeleteArea, exitStartDeleteArea,
        DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the right distance great than startNode size + deleteAreaDistance, check
     * enterStartDeleteArea callback.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA);
    ListItemSwipeMoveAndLayout(itemPattern, static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA3);
    EXPECT_TRUE(isEnterStartDeleteAreaCalled);

    /**
     * @tc.steps: step3. moving to the left distance less than startNode size + deleteAreaDistance, check
     * exitStartDeleteArea callback.
     */
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA);
    EXPECT_TRUE(isExitStartDeleteAreaCalled);
}

/**
 * @tc.name: ListItemAttrSwiperTest013
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    bool isEnterEndDeleteAreaCalled = false;
    bool isExitEndDeleteAreaCalled = false;
    auto enterEndDeleteArea = [&isEnterEndDeleteAreaCalled]() { isEnterEndDeleteAreaCalled = true; };
    auto exitEndDeleteArea = [&isExitEndDeleteAreaCalled]() { isExitEndDeleteAreaCalled = true; };
    CreateListItemWithSwipeActionItem(builder, true, nullptr, enterEndDeleteArea, exitEndDeleteArea,
        DELETE_AREA_DISTANCE, false, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the left distance great than endNode size + deleteAreaDistance, check
     * enterEndDeleteArea callback.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA2);
    ListItemSwipeMoveAndLayout(itemPattern, -static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA3);
    EXPECT_TRUE(isEnterEndDeleteAreaCalled);

    /**
     * @tc.steps: step3. moving to the right distance less than endNode size + deleteAreaDistance, check
     * exitEndDeleteArea callback.
     */
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    EXPECT_TRUE(isExitEndDeleteAreaCalled);
}

/**
 * @tc.name: ListItemAttrSwiperTest014
 * @tc.desc: Test swiperAction Attribute for ListItem, set deleteArea, deleteAreaDistance and onDeleteCallBack, Drag the
 * ListItem left or right to obtain the correct SwipeIndex.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    bool isStartOnDeleteCalled = false;
    auto startOnDelete = [&isStartOnDeleteCalled]() { isStartOnDeleteCalled = true; };
    CreateListItemWithSwipeActionItem(
        builder, true, startOnDelete, nullptr, nullptr, DELETE_AREA_DISTANCE, true, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. moving to the right distance great than startNode size + deleteAreaDistance, check
     * SwipeIndex.
     */
    auto itemPattern = GetItemPattern(0);
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA);
    ListItemSwipeMoveAndLayout(itemPattern, static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA3);
    GestureEvent info;
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. moving to the left distance great than endNode size + deleteAreaDistance, check
     * SwipeIndex.
     */
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA);
    ListItemSwipeMoveAndLayout(itemPattern, -static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA3);
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA);
    ListItemSwipeMoveAndLayout(itemPattern, -static_cast<float>(DELETE_AREA_DISTANCE.ConvertToPx()));
    ListItemSwipeMoveAndLayout(itemPattern, -MOVE_DELTA3);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ListItemAttrSwiperTest015
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and endNode.
 * Drag the ListItem left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest015, TestSize.Level1)
{
    auto builder = GetDefaultSwiperBuilder(LISTITEM_NODE_WIDTH, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    GestureEvent info;
    info.SetMainDelta(10.f);
    info.SetMainVelocity(1300.f);
    DragSwiperItem(0, info);
    auto itemPattern = GetItemPattern(0);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    info.SetMainDelta(-20.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    info.SetMainDelta(-10.f);
    info.SetMainVelocity(-1300.f);
    DragSwiperItem(0, info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
}
/**
 * @tc.name: ListItemAttrSwiperTest016
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and endNode.
 * When switch ListItem to drag, the previous would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest016, TestSize.Level1)
{
    auto builder = GetDefaultSwiperBuilder(LISTITEM_NODE_WIDTH, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Drag first item to 30.
     * @tc.expected: The first item swiperIndex_ changed.
     */
    GestureEvent info;
    info.SetMainDelta(30.f);
    info.SetMainVelocity(1300.f);
    DragSwiperItem(0, info);
    auto firstItemPattern = GetItemPattern(0);
    EXPECT_EQ(firstItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_FLOAT_EQ(firstItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);

    /**
     * @tc.steps: step2. Drag second item to 30.
     * @tc.expected: The second item swiperIndex_ changed, and first item reseted.
     */
    DragSwiperItem(1, info);
    auto secondItemPattern = GetItemPattern(1);
    EXPECT_EQ(firstItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_FLOAT_EQ(firstItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);
    EXPECT_FLOAT_EQ(secondItemPattern->springMotion_->GetCurrentVelocity(), 1300.f);
}

/**
 * @tc.name: ListItemGroupSpaceTest001
 * @tc.desc: ListItemGroup set the Space attribute. There is a space between ListItems
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupSpaceTest001, TestSize.Level1)
{
    constexpr float space = 5.0f;
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetSpace(Dimension(space));
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    constexpr int32_t groupIndex = 0;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex, itemCount, DEFAULT_LANES, space));
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest001
 * @tc.desc: ListItemGroup set the header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetHeader(std::move(header));
    listItemGroupModel.SetFooter(std::move(footer));
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(itemCount));
    for (int32_t index = 0; index < itemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first,
            (index * DEFAULT_LISTITEM_VERTICAL_LENGTH) + DEFAULT_HEADER_MAIN_LENGTH);
        EXPECT_FLOAT_EQ(itemPosition[index].second,
            ((index + 1) * DEFAULT_LISTITEM_VERTICAL_LENGTH) + DEFAULT_HEADER_MAIN_LENGTH);
    }
    auto itemGroupFrameNode = GetChildFrameNode(0);
    ASSERT_NE(itemGroupFrameNode, nullptr);
    constexpr int32_t headerIndex = 0;
    constexpr int32_t footerIndex = 1;
    auto headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    auto footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 550.f);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest002
 * @tc.desc: ListItemGroup set the header and footer, List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest002, TestSize.Level1)
{
    constexpr float itemHeight = 750.f;
    constexpr int32_t headerIndex = 0;
    constexpr int32_t footerIndex = 1;
    auto header = GetDefaultHeaderBuilder();
    auto footer = GetDefaultHeaderBuilder();

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSticky(V2::StickyStyle::BOTH);
    // Create ListItem
    ListItemModelNG listItemModel1;
    listItemModel1.Create();
    SetHeight(Dimension(itemHeight));
    SetWidth(FILL_LENGTH);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItemGroup
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetHeader(std::move(header));
    listItemGroupModel.SetFooter(std::move(footer));
    CreateListItem(4);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItem
    ListItemModelNG listItemModel2;
    listItemModel2.Create();
    SetHeight(Dimension(itemHeight));
    SetWidth(FILL_LENGTH);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: footer is sticky under header
     */
    auto itemGroupFrameNode = GetChildFrameNode(1);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    auto groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), itemHeight);
    auto headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    auto footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 50.f);

    /**
     * @tc.steps: step3. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at bottom of List
     */
    constexpr float scrollOffset = -250.f;
    UpdateCurrentOffset(scrollOffset);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), 500.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 250.f);

    /**
     * @tc.steps: step4. Scroll 700px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at to of List
     */
    constexpr float scrollOffset2 = -700.f;
    UpdateCurrentOffset(scrollOffset2);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), -200.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 200.f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 450.f);

    /**
     * @tc.steps: step4. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky upper footer
     */
    constexpr float scrollOffset3 = -250.f;
    UpdateCurrentOffset(scrollOffset3);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), -450.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 400.f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 450.f);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest003
 * @tc.desc: ListItemGroup set the header and footer with null
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetHeader(nullptr);
    listItemGroupModel.SetFooter(nullptr);
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step4. Has no head and foot.
     * @tc.expected: Children count is ListItem count.
     */
    size_t expectCount = 1;
    EXPECT_EQ(frameNode_->GetChildren().size(), expectCount);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest004
 * @tc.desc: ListItemGroup set divider, space
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest004, TestSize.Level1)
{
    constexpr float space = 10.f;
    constexpr float strokeWidth = 4.f;
    constexpr float startMargin = 10.f;
    constexpr float endMargin = 20.f;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();

    ListItemGroupModelNG listItemGroupModel1;
    listItemGroupModel1.Create();
    listItemGroupModel1.SetDivider(itemDivider);
    listItemGroupModel1.SetSpace(Dimension(space));
    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
    ViewStackProcessor::GetInstance()->Pop();

    // empty listItem
    ListItemGroupModelNG listItemGroupModel2;
    listItemGroupModel2.Create();
    listItemGroupModel2.SetDivider(itemDivider);
    ViewStackProcessor::GetInstance()->Pop();

    GetInstance();
    RunMeasureAndLayout();

    constexpr int32_t groupIndex = 0;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex, DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, space));
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest005
 * @tc.desc: ListItemGroup OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest005, TestSize.Level1)
{
    constexpr float space = 10.f;
    constexpr float strokeWidth = 4.f;
    constexpr float startMargin = 10.f;
    constexpr float endMargin = 20.f;
    const Color color = Color(0x000000);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(strokeWidth);
    itemDivider.startMargin = Dimension(startMargin);
    itemDivider.endMargin = Dimension(endMargin);
    itemDivider.color = color;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetDivider(itemDivider);
    listItemGroupModel.SetSpace(Dimension(space));
    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    constexpr int32_t groupIndex = 0;
    EXPECT_TRUE(VerifyGroupItemPosition(groupIndex, DEFAULT_LISTITEM_VIEWPORT_COUNT, DEFAULT_LANES, space));

    auto group = frameNode_->GetChildAtIndex(0);
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(group);
    auto layoutWrapper = groupFrameNode->CreateLayoutWrapper(false, false);
    auto itemGroupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = false;
    config.skipLayout = false;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = true;
    config.skipLayout = false;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = false;
    config.skipLayout = true;
    EXPECT_FALSE(itemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: ListItemGroupLayoutTest001
 * @tc.desc: ListItemGroup forward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 9;

    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t index = 0; index < expectItemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first, (index * DEFAULT_LISTITEM_VERTICAL_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[index].second, ((index + 1) * DEFAULT_LISTITEM_VERTICAL_LENGTH));
    }
}

/**
 * @tc.name: ListItemGroupLayoutTest002
 * @tc.desc: ListItemGroup backward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest002, TestSize.Level1)
{
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 8;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(1);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItem(1);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    auto offset = itemGroupPattern->GetHostFrameOffset();
    constexpr float ITEM_GROUP_OFFSET = -100.f;
    EXPECT_FLOAT_EQ(offset->GetY(), ITEM_GROUP_OFFSET);
    constexpr int32_t ITEM_START = 2;
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t index = ITEM_START; index < itemCount; index++) {
        EXPECT_FLOAT_EQ(itemPosition[index].first, ((index - ITEM_START) * DEFAULT_LISTITEM_VERTICAL_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[index].second, ((index - ITEM_START + 1) * DEFAULT_LISTITEM_VERTICAL_LENGTH));
    }
}

/**
 * @tc.name: Callback001
 * @tc.desc: Test scroll callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    bool isScrollCalled = false;
    bool isScrollIndexCalled = false;
    bool isReachStartCalled = false;
    bool isReachEndCalled = false;
    auto scroll = [&isScrollCalled](Dimension, ScrollState) { isScrollCalled = true; };
    auto scrollIndex = [&isScrollIndexCalled](int32_t, int32_t) { isScrollIndexCalled = true; };
    auto reachStart = [&isReachStartCalled]() { isReachStartCalled = true; };
    auto reachEnd = [&isReachEndCalled]() { isReachEndCalled = true; };
    listModelNG.SetOnScroll(scroll);
    listModelNG.SetOnScrollIndex(scrollIndex);
    listModelNG.SetOnReachStart(reachStart);
    listModelNG.SetOnReachEnd(reachEnd);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    constexpr float scrollUpOffset = DEFAULT_LISTITEM_VERTICAL_LENGTH;
    constexpr float scrollDownOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH;

    /**
     * @tc.steps: step1. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    UpdateCurrentOffset(scrollUpOffset);
    EXPECT_TRUE(isScrollIndexCalled);

    /**
     * @tc.steps: step1. Scroll down 100px.
     * @tc.expected: Callback is called.
     */
    pattern_->UpdateCurrentOffset(scrollDownOffset, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollIndexCalled);

    /**
     * @tc.steps: step2. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollUpOffset, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);
    EXPECT_TRUE(isReachStartCalled);

    /**
     * @tc.steps: step3. Scroll down 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollDownOffset, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);

    /**
     * @tc.steps: step3. Scroll up 100px.
     * @tc.expected: Callback is called.
     */
    isScrollCalled = false;
    pattern_->UpdateCurrentOffset(scrollUpOffset, SCROLL_FROM_NONE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollCalled);

    /**
     * @tc.steps: step3. Scroll down 200px.
     * @tc.expected: Callback is called.
     */
    UpdateCurrentOffset(scrollDownOffset * 2);
    EXPECT_TRUE(isReachEndCalled);

    UpdateCurrentOffset(scrollDownOffset);
    EXPECT_TRUE(isReachEndCalled);
}

/**
 * @tc.name: Callback002
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(Dimension(0), Dimension(10), 0, 0, 0);
    bool isScrollStartCalled = false;
    bool isScrollStopCalled = false;
    auto scrollStart = [&isScrollStartCalled]() { isScrollStartCalled = true; };
    auto scrollStop = [&isScrollStopCalled]() { isScrollStopCalled = true; };
    listModelNG.SetOnScrollStart(scrollStart);
    listModelNG.SetOnScrollStop(scrollStop);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Call func.
     * @tc.expected: The callback is called.
     */
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartCalled);

    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollStopCalled);

    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
}

/**
 * @tc.name: Callback004
 * @tc.desc: Test other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Callback004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetOnScrollBegin([](Dimension, Dimension) {
        ScrollInfo info;
        return info;
    });
    listModelNG.SetOnScrollFrameBegin([](Dimension, ScrollState) {
        ScrollFrameResult result;
        return result;
    });
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get jumpIndex_.
     * @tc.expected: The jumpIndex_ is changed.
     */
    auto scrollableEvent = pattern_->GetScrollableEvent();
    ASSERT_NE(scrollableEvent, nullptr);
    EXPECT_NE(scrollableEvent->GetScrollBeginCallback(), nullptr);
    EXPECT_NE(scrollableEvent->GetScrollFrameBeginCallback(), nullptr);
    RunMeasureAndLayout();
}

/**
 * @tc.name: Drag001
 * @tc.desc: Verify onItemDragStart, onItemDragEnter, onItemDragMove, onItemDragLeave, onItemDrop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Drag001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10);
    bool isItemDragStartCalled = false;
    auto itemDragStart = [&isItemDragStartCalled](const ItemDragInfo&, int32_t) {
        isItemDragStartCalled = true;
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return dragItem;
    };
    listModelNG.SetOnItemDragStart(itemDragStart);
    listModelNG.SetOnItemDragEnter([](const ItemDragInfo&) {});
    listModelNG.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    listModelNG.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    listModelNG.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    GestureEvent info;
    Point globalPoint = Point(200.f, 150.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_TRUE(isItemDragStartCalled);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    EXPECT_NE(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step2. Trigger HandleOnItemDragUpdate and HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step3. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate and HandleOnItemDragCancel.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
}

/**
 * @tc.name: EventHub001
 * @tc.desc: Test ListItem Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub001, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Run GetDragExtraParams func.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetChildFrameNode(0);
    auto itemEventHub = itemFrameNode->GetEventHub<ListItemEventHub>();
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 200.f), DragEventType::START);
    EXPECT_NE(jsonStr, "");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 200.f), DragEventType::MOVE);
    EXPECT_NE(jsonStr, "");
}

/**
 * @tc.name: EventHub002
 * @tc.desc: Test List Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, EventHub002, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Run GetDragExtraParams func.
     * @tc.expected: Would call pattern->GetItemIndexByPosition
     */
    auto jsonStr = eventHub_->GetDragExtraParams("", Point(0, 0), DragEventType::MOVE);
    EXPECT_EQ(jsonStr, "{\"insertIndex\":0}");
}

/**
 * @tc.name: MouseSelect001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Click the (0, 0) point of firstItem.
     * @tc.expected: Can not select by click, the item is not selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(0.f, 0.f));
    EXPECT_FALSE(GetItemPattern(0)->IsSelected());
}

/**
 * @tc.name: MouseSelect002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(120.f, 250.f);
    const Offset LEFT_BOTTOM = Offset(120.f, 350.f);
    const Offset RIGHT_TOP = Offset(360.f, 250.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 350.f);

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseSelect(Offset(0.f, 0.f), Offset(200.f, 100.f));
    EXPECT_TRUE(GetItemPattern(0)->IsSelected());
    EXPECT_TRUE(GetItemPattern(1)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(0)->MarkIsSelected(false);
    GetItemPattern(1)->MarkIsSelected(false);

    /**
     * @tc.steps: step2. Select (120, 150) - (360, 250) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(LEFT_TOP, RIGHT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step3. Select (120, 150) - (360, 250) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(RIGHT_TOP, LEFT_BOTTOM);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step4. Select (120, 150) - (360, 250) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(LEFT_BOTTOM, RIGHT_TOP);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);

    /**
     * @tc.steps: step5. Select (120, 150) - (360, 250) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    MouseSelect(RIGHT_BOTTOM, LEFT_TOP);
    EXPECT_TRUE(GetItemPattern(2)->IsSelected());
    EXPECT_TRUE(GetItemPattern(3)->IsSelected());
    MouseSelectRelease();
    GetItemPattern(2)->MarkIsSelected(false);
    GetItemPattern(3)->MarkIsSelected(false);
}

/**
 * @tc.name: MouseSelect003
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect003, TestSize.Level1)
{
    constexpr int32_t itemCount = 9;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);

    /**
     * @tc.steps: step1. Create listItem and set an unselectable.
     */
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    for (int32_t index = 0; index < itemCount; index++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_LISTITEM_VERTICAL_LENGTH));
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
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseSelect(Offset(120.f, 350.f), Offset(360.f, 450.f));
    EXPECT_FALSE(GetItemPattern(3)->IsSelected());
    EXPECT_TRUE(GetItemPattern(4)->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
}

/**
 * @tc.name: MouseSelect004
 * @tc.desc: Test listItem selectable about other condition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, MouseSelect004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Use RIGHT_BUTTON to select.
     * @tc.expected: Nothing selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0, 0));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    // Nothing selected
    for (int32_t index = 0; index < DEFAULT_LISTITEM_VIEWPORT_COUNT; index++) {
        EXPECT_FALSE(GetItemPattern(index)->IsSelected()) << "Index: " << index;
    }

    /**
     * @tc.steps: step2. Use LEFT_BUTTON, but with MouseAction::HOVER to select.
     * @tc.expected: Nothing selected.
     */
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::HOVER);
    info.SetLocalLocation(Offset(0, 0));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    // Nothing selected
    for (int32_t index = 0; index < DEFAULT_LISTITEM_VIEWPORT_COUNT; index++) {
        EXPECT_FALSE(GetItemPattern(index)->IsSelected()) << "Index: " << index;
    }
}

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test List AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Run accessibilityProperty func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 7);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 10);
}

/**
 * @tc.name: AccessibilityProperty002
 * @tc.desc: Test List SetSpecificSupportAction when scroll to middle
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty002, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Scroll to middle.
     */
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty003
 * @tc.desc: Test List SetSpecificSupportAction when at top
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty003, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty004
 * @tc.desc: Test List SetSpecificSupportAction when at bottom
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty004, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Scroll to bottom.
     */
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH * 2;
    UpdateCurrentOffset(scrollOffset);
    /**
     * @tc.steps: step2. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty005
 * @tc.desc: Test List SetSpecificSupportAction when unScrollable
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty005, TestSize.Level1)
{
    CreateList(8);

    /**
     * @tc.steps: step1. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty006
 * @tc.desc: Test ListItem AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty006, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Get item accessibilityProperty.
     */
    auto itemFrameNode = GetChildFrameNode(1);
    auto itemAccessibilityProperty = itemFrameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();

    /**
     * @tc.steps: step2. Call IsSelected.
     * @tc.expected: Verify return value.
     */
    EXPECT_FALSE(itemAccessibilityProperty->IsSelected());

    /**
     * @tc.steps: step3. Call SetSpecificSupportAction.
     * @tc.expected: Verify return value.
     */
    itemAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = itemAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: AccessibilityProperty007
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty007, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(4);
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get itemGroup accessibilityProperty.
     */
    auto groupFrameNode = GetChildFrameNode(0);
    auto groupAccessibilityProperty = groupFrameNode->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();

    /**
     * @tc.steps: step3. Call func.
     * @tc.expected: Verify return value.
     */
    EXPECT_EQ(groupAccessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(groupAccessibilityProperty->GetEndIndex(), 3);
}

/**
 * @tc.name: AccessibilityProperty008
 * @tc.desc: Test ListItemGroup AccessibilityProperty func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, AccessibilityProperty008, TestSize.Level1)
{
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create();
    RefPtr<UINode> groupElement = ViewStackProcessor::GetInstance()->Finish();
    auto groupFrameNode = AceType::DynamicCast<FrameNode>(groupElement);
    auto groupAccessibilityProperty = groupFrameNode->GetAccessibilityProperty<ListItemGroupAccessibilityProperty>();

    /**
     * @tc.steps: step3. Call func.
     * @tc.expected: Verify return value.
     */
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
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 100.f)));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 200.f)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, -1);
    EXPECT_EQ(pattern_->scrollIndexAlignment_, ScrollIndexAlignment::ALIGN_BOTTOM);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->jumpIndex_, 0);
    EXPECT_EQ(pattern_->scrollIndexAlignment_, ScrollIndexAlignment::ALIGN_TOP);

    controller->JumpTo(1, false, 0);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1, nullptr));
}

/**
 * @tc.name: PositionController002
 * @tc.desc: Test PositionController function with Axis::HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL);
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10, Axis::HORIZONTAL);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::HORIZONTAL);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(50.f, 0)));

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(120.f, 0)));
    controller->ScrollPage(true, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    Offset currentOffset = controller->GetCurrentOffset();
    EXPECT_EQ(currentOffset, Offset(0, 0));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, -1);
    EXPECT_EQ(pattern_->scrollIndexAlignment_, ScrollIndexAlignment::ALIGN_BOTTOM);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern_->jumpIndex_, 0);
    EXPECT_EQ(pattern_->scrollIndexAlignment_, ScrollIndexAlignment::ALIGN_TOP);

    controller->JumpTo(1, false, 0);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1, nullptr));
}

/**
 * @tc.name: PositionController003
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, PositionController003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::NONE);
    RefPtr<ScrollControllerBase> scroller = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scroller, nullptr);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Get positionController and set scroll_.
     */
    auto controller = pattern_->positionController_;
    controller->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));

    /**
     * @tc.steps: step2. Call func.
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::NONE);

    controller->ScrollBy(50.f, 100.f, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 50.f)));

    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    EXPECT_EQ(pattern_->jumpIndex_, std::nullopt);

    controller->ScrollPage(false, true);
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 50.f)));

    controller->JumpTo(1, false, 0);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr));
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test GetNextFocusNode func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(8, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 0, 7));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 4, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 4, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 4, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 4, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 4, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 7, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, 7, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, 7, -1));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test GetNextFocusNode func in HORIZONTAL List
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep002, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::HORIZONTAL); // HORIZONTAL List.
    CreateListItem(8, Axis::HORIZONTAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from top.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 0, 1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 0, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 0, 7));

    /**
     * @tc.steps: step2. GetNextFocusNode from middle.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 4, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 4, 3));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 4, 5));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 4, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 4, 7));

    /**
     * @tc.steps: step3. GetNextFocusNode from bottom.
     * @tc.expected: Verify all condition of FocusStep.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::NONE, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, 7, 6));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, 7, -1));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, 7, 0));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, 7, -1));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test GetNextFocusNode func when List has unfocuseable item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(8, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. GetNextFocusNode from 1st item and FocusStep::DOWN.
     * @tc.expected: The 3rd item is focused.
     */
    GetChildFocusHub(1)->SetFocusable(false); // The 2nd item can not focus.
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 0, 2));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test GetNextFocusNode func from top boundary item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to 150
     */
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH - 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. UP to 1st item from 2nd item.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, 1, 0));
    EXPECT_EQ(pattern_->jumpIndex_, 0);
}

/**
 * @tc.name: FocusStep005
 * @tc.desc: Test GetNextFocusNode func from bottom boundary item
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, FocusStep005, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10, Axis::VERTICAL, true); // Create focusable ListItem.
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Scroll to 99
     */
    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH + 1.f;
    UpdateCurrentOffset(scrollOffset);

    /**
     * @tc.steps: step2. DOWN to 10th item from 9th item.
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, 8, -1));
    EXPECT_EQ(pattern_->jumpIndex_, 9);
}

/**
 * @tc.name: KeyEvent001
 * @tc.desc: Test list_pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, KeyEvent001, TestSize.Level1)
{
    CreateList();

    /**
     * @tc.steps: step1. Test other KeyEvent.
     * @tc.expected: CurrentOffset unchanged.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));

    /**
     * @tc.steps: step2. Test active KeyEvent.
     * @tc.expected: CurrentOffset changed.
     */
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_DOWN, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 200.f)));
    pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_PAGE_UP, KeyAction::DOWN));
    EXPECT_TRUE(IsEqualCurrentOffset(Offset(0, 0)));
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
    RunMeasureAndLayout();

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

    EXPECT_TRUE(true);
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
    CreateListItemGroup(3);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

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
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdateClipEdge(false);
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    listPaint->PaintScrollBar(canvas);

    modifier->onDraw(ctx);

    EXPECT_TRUE(true);
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
    CreateListItemGroup(3);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper paintWrapper(nullptr, geometryNode, paintProperty_);
    listPaint->UpdateContentModifier(&paintWrapper);
    RSCanvas canvas;
    listPaint->PaintScrollBar(canvas);

    auto modifier = pattern_->listContentModifier_;
    DrawingContext ctx = { canvas, 1, 1};
    modifier->onDraw(ctx);

    EXPECT_TRUE(true);
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
    listItemGroupModelNG.Create();
    CreateListItem();
    ViewStackProcessor::GetInstance()->Pop();
    GetInstance();
    RunMeasureAndLayout();

    auto groupFrameNode = GetChildFrameNode(0);
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
 * @tc.name: Pattern001
 * @tc.desc: Test list_pattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern001, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

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
    CreateList();

    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Pause();
    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Stop();
    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern003, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    listModelNG.SetScroller(scrollController, nullptr);
    listModelNG.SetEdgeEffect(EdgeEffect::FADE);
    GetInstance();
    RunMeasureAndLayout();

    auto paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    EXPECT_EQ(listPaint->edgeEffect_.Upgrade(), pattern_->GetScrollEdgeEffect());
}

/**
 * @tc.name: Pattern004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern004, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem();
    GetInstance();
    auto layoutWrapper = RunMeasureAndLayout();

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: Pattern005
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern005, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 10.f;
    constexpr float maxSpace = 2.f;
    constexpr float conductivity = 5.f;
    constexpr float intensity = 5.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When minSpace > maxSpace.
     * @tc.expected: minSpace and maxSpace would be space.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, space);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, space);

    /**
     * @tc.steps: step2. When conductivity > 1.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);

    /**
     * @tc.steps: step3. When intensity > 1.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern006, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = -5.f;
    constexpr float intensity = -5.f;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When minSpace < maxSpace.
     * @tc.expected: minSpace and maxSpace would be itself.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->minSpace_, minSpace);
    EXPECT_FLOAT_EQ(chainAnimation->maxSpace_, maxSpace);

    /**
     * @tc.steps: step2. When conductivity < 0.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, ChainAnimation::DEFAULT_CONDUCTIVITY);

    /**
     * @tc.steps: step3. When intensity < 0.
     * @tc.expected: conductivity would be default value.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, ChainAnimation::DEFAULT_INTENSITY);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test SetChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern007, TestSize.Level1)
{
    constexpr float space = 5.f;
    constexpr float minSpace = 2.f;
    constexpr float maxSpace = 10.f;
    constexpr float conductivity = 0;
    constexpr float intensity = 0;

    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(
        Dimension(minSpace), Dimension(maxSpace), conductivity, intensity, 0);
    CreateListItem();
    GetInstance();
    RunMeasureAndLayout();

    ChainAnimationOptions options = {
        .minSpace = Dimension(minSpace),
        .maxSpace = Dimension(maxSpace),
        .conductivity = conductivity,
        .intensity = intensity,
        .edgeEffect = 0,
    };
    pattern_->SetChainAnimationOptions(options);

    /**
     * @tc.steps: step1. When conductivity == 0.
     * @tc.expected: conductivity would be itself.
     */
    const auto chainAnimation = pattern_->chainAnimation_;
    EXPECT_FLOAT_EQ(chainAnimation->conductivity_, conductivity);

    /**
     * @tc.steps: step2. When intensity == 0.
     * @tc.expected: conductivity would be itself.
     */
    EXPECT_FLOAT_EQ(chainAnimation->intensity_, intensity);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern008, TestSize.Level1)
{
    CreateList();

    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    constexpr float scrollOffset = -DEFAULT_LISTITEM_VERTICAL_LENGTH;
    UpdateCurrentOffset(scrollOffset);
    EXPECT_FALSE(pattern_->OutBoundaryCallback());

    UpdateCurrentOffset(scrollOffset);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
}

/**
 * @tc.name: Pattern019
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern019, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetChainAnimation(true);
    listModelNG.SetChainAnimationOptions(Dimension(0), Dimension(10), 0, 0, 0);
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    pattern_->OutBoundaryCallback();
    EXPECT_TRUE(pattern_->dragFromSpring_);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern010, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. Test ScrollToIndex.
     */
    pattern_->ScrollToIndex(1, 0, ScrollIndexAlignment::ALIGN_BOTTOM);
    EXPECT_EQ(pattern_->scrollIndexAlignment_, ScrollIndexAlignment::ALIGN_BOTTOM);
    EXPECT_EQ(pattern_->currentDelta_, 0);
    EXPECT_EQ(pattern_->jumpIndex_, 1);

    pattern_->ScrollToIndex(-1, 0, ScrollIndexAlignment::ALIGN_BOTTOM);
    EXPECT_EQ(pattern_->jumpIndex_, -1);

    pattern_->ScrollToIndex(-2, 0, ScrollIndexAlignment::ALIGN_BOTTOM);
    EXPECT_EQ(pattern_->jumpIndex_, -1);

    pattern_->ScrollToIndex(-2, false, ScrollIndexAlignment::ALIGN_BOTTOM);
    EXPECT_EQ(pattern_->jumpIndex_, -1);
}

/**
 * @tc.name: Pattern011
 * @tc.desc: Test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern011, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(80.f, false);
    ListModelNG listModelNG;
    listModelNG.SetChainAnimation(true);
    listModelNG.Create();
    RefPtr<ScrollControllerBase> scrollController = listModelNG.CreateScrollController();
    RefPtr<ScrollProxy> proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    listModelNG.SetScroller(scrollController, proxy);
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    // Set swiperItem_ to list pattern
    GestureEvent info;
    DragSwiperItem(0, info);

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(0, 0, nullptr);
    pattern_->animator_->Resume();
    EXPECT_TRUE(pattern_->animator_->IsRunning());
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    const Offset expectOffset1 = Offset(0, 0);
    IsEqualCurrentOffset(expectOffset1);
    EXPECT_TRUE(pattern_->animator_->IsStopped());

    /**
     * @tc.steps: step2. When has animator_ and stop, call OnScrollCallback.
     * @tc.expected:
     */
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    pattern_->GetScrollBar()->SetDriving(true);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_UPDATE);
    const Offset expectOffset2 = Offset(0, 100.f);
    IsEqualCurrentOffset(expectOffset2);

    /**
     * @tc.steps: step3. Offset is 0, ProcessDragUpdate do nothing.
     * @tc.expected: CurrentOffset unchange.
     */
    pattern_->GetScrollBar()->SetDriving(false);
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
 * @tc.name: Pattern012
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern012, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(2);
    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
    GetInstance();
    RunMeasureAndLayout();

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
 * @tc.name: Pattern013
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern013, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(DEFAULT_LISTITEM_VIEWPORT_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, DEFAULT_LISTITEM_VIEWPORT_COUNT);
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern014, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern015
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern015, TestSize.Level1)
{
    constexpr int32_t itemCount = 5;

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(itemCount);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UpdateCurrentOffset -100
     * @tc.expected: The list is unscrollable, offset is 0
     */
    constexpr float offset = -100.f;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_UPDATE);
    const Offset expectOffset = Offset(0, 0);
    EXPECT_TRUE(IsEqualCurrentOffset(expectOffset));
}
/**
 * @tc.name: Pattern016
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, Pattern016, TestSize.Level1)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(DEFAULT_LISTITEM_TOTAL_COUNT);
    GetInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step1. UpdateCurrentOffset -100 with SCROLL_FROM_START
     * @tc.expected: The offset was not effected by friction
     */
    constexpr float offset = -100.f;
    pattern_->UpdateCurrentOffset(offset, SCROLL_FROM_START);
    constexpr float expectDelta = 100.f;
    EXPECT_EQ(pattern_->currentDelta_, expectDelta);
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
} // namespace OHOS::Ace::NG

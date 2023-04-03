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
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
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
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
constexpr float DEFAULT_ITEM_MAIN_LENGTH = 100.f;
constexpr Dimension DEFAULT_ITEM_CROSS_LENGTH = Dimension(1.0, DimensionUnit::PERCENT);
constexpr float DEFAULT_HEADER_MAIN_LENGTH = 50.f;
constexpr float LIST_ITEM_WIDTH = 10.0f;
constexpr float LIST_ITEM_HEIGHT = 30.0f;
constexpr int32_t LIST_ITEM_NUMBER = 10;
} // namespace

class ListTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetListInstance();
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void CreateListItem(int32_t number);
    void CreateListItemWithoutWidth(int32_t number);
    void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    void RunMeasureAndLayout();
    RefPtr<GeometryNode> GetChildGeometryNode(const RefPtr<FrameNode>& frameNode, int32_t index);
    RefPtr<FrameNode> GetItemFrameNode(int32_t index);
    RefPtr<ListItemPattern> GetItemPattern(int32_t index);
    RefPtr<ListItemGroupPattern> GetItemGroupPattern(int32_t index);
    void ListItemSwipeMoveAndLayout(const RefPtr<ListItemPattern>& itemPattern, float moveDelta);
    std::function<void()> GetDefaultSwiperBuilder(float crossSize, bool spring);
    std::function<void()> GetDefaultHeaderBuilder();

    RefPtr<FrameNode> frameNode_;
    RefPtr<ListPattern> pattern_;
    RefPtr<ListEventHub> eventHub_;
    RefPtr<ListLayoutProperty> layoutProperty_;
};

void ListTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
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
}

void ListTestNg::GetListInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ListPattern>();
    eventHub_ = frameNode_->GetEventHub<ListEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ListLayoutProperty>();
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

void ListTestNg::CreateListItem(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItemWithoutWidth(int32_t number)
{
    for (int32_t i = 0; i < number; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        ViewStackProcessor::GetInstance()->Pop();
    }
}

void ListTestNg::CreateListItemWithSwiper(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG listItemModel;
    listItemModel.Create();
    SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
    SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
    listItemModel.SetSwiperAction(std::move(startAction), std::move(endAction), effect);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

void ListTestNg::RunMeasureAndLayout()
{
    CHECK_NULL_VOID(frameNode_);
    RefPtr<LayoutWrapper> listLayoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    listLayoutWrapper->SetActive();
    listLayoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    listLayoutWrapper->Measure(LayoutConstraint);
    listLayoutWrapper->Layout();
    listLayoutWrapper->MountToHostOnMainThread();
}

RefPtr<GeometryNode> ListTestNg::GetChildGeometryNode(const RefPtr<FrameNode>& frameNode, int32_t index)
{
    auto item = frameNode->GetChildAtIndex(index);
    CHECK_NULL_RETURN(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetGeometryNode();
}

RefPtr<FrameNode> ListTestNg::GetItemFrameNode(int32_t index)
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    auto item = frameNode_->GetChildAtIndex(index);
    CHECK_NULL_RETURN(item, nullptr);
    return AceType::DynamicCast<FrameNode>(item);
}

RefPtr<ListItemPattern> ListTestNg::GetItemPattern(int32_t index)
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    auto item = frameNode_->GetChildAtIndex(index);
    CHECK_NULL_RETURN(item, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
    return itemFrameNode->GetPattern<ListItemPattern>();
}

RefPtr<ListItemGroupPattern> ListTestNg::GetItemGroupPattern(int32_t index)
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    auto item = frameNode_->GetChildAtIndex(index);
    CHECK_NULL_RETURN(item, nullptr);
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
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        if (spring) {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
            SetWidth(Dimension(crossSize));
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
        SetHeight(Dimension(DEFAULT_HEADER_MAIN_LENGTH));
        SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
    };
}


/**
 * @tc.name: ListPropertiesTest001
 * @tc.desc: Test all the properties of list.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPropertiesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set Properties.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(10));
    listModelNG.SetInitialIndex(0);
    listModelNG.SetListDirection(Axis::VERTICAL);
    listModelNG.SetEdgeEffect(EdgeEffect::NONE);
    listModelNG.SetLanes(3);
    listModelNG.SetLaneMinLength(Dimension(40));
    listModelNG.SetLaneMaxLength(Dimension(60));
    listModelNG.SetListItemAlign(V2::ListItemAlign::CENTER);
    listModelNG.SetCachedCount(10);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10);
    itemDivider.startMargin = Dimension(0);
    itemDivider.endMargin = Dimension(0);
    itemDivider.color = Color(0x000000);
    listModelNG.SetDivider(itemDivider);
    GetListInstance();

    /**
     * @tc.steps: step2. Compare properties and expected_value.
     * @tc.expected: Properties equals expected_value.
     */
    EXPECT_EQ(layoutProperty_->GetSpaceValue(), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetInitialIndexValue(), 0);
    EXPECT_EQ(layoutProperty_->GetListDirectionValue(), Axis::VERTICAL);
    EXPECT_EQ(layoutProperty_->GetEdgeEffectValue(), EdgeEffect::NONE);
    EXPECT_EQ(layoutProperty_->GetLanesValue(), 3);
    EXPECT_EQ(layoutProperty_->GetLaneMinLengthValue(), Dimension(40));
    EXPECT_EQ(layoutProperty_->GetLaneMaxLengthValue(),  Dimension(60));
    EXPECT_EQ(layoutProperty_->GetListItemAlignValue(), V2::ListItemAlign::CENTER);
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(), 10);
    V2::ItemDivider divider = layoutProperty_->GetDividerValue();
    EXPECT_EQ(divider.strokeWidth, Dimension(10));
    EXPECT_EQ(divider.startMargin, Dimension(0));
    EXPECT_EQ(divider.endMargin, Dimension(0));
    EXPECT_EQ(divider.color, Color(0x000000));
}

/**
 * @tc.name: ListPropertiesTest002
 * @tc.desc: Test all the properties of listItemGroup.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPropertiesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set properties.
     */
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create();
    listItemGroupModelNG.SetSpace(Dimension(10));
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = Dimension(10);
    itemDivider.startMargin = Dimension(0);
    itemDivider.endMargin = Dimension(0);
    itemDivider.color = Color(0x000000);
    listItemGroupModelNG.SetDivider(itemDivider);
    GetListInstance();

    /**
     * @tc.steps: step2. Compare properties and expected_value.
     * @tc.expected: Properties equals expected_value.
     */
    RefPtr<ListItemGroupLayoutProperty> layoutProperty =
        frameNode_->GetLayoutProperty<ListItemGroupLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSpaceValue(), Dimension(10));
    V2::ItemDivider divider = layoutProperty->GetDividerValue();
    EXPECT_EQ(divider.strokeWidth, Dimension(10));
    EXPECT_EQ(divider.startMargin, Dimension(0));
    EXPECT_EQ(divider.endMargin, Dimension(0));
    EXPECT_EQ(divider.color, Color(0x000000));
}

/**
 * @tc.name: ListAttrSpaceTest001
 * @tc.desc: Set the Space attribute. There is a space between ListItems
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrSpaceTest001, TestSize.Level1)
{
    constexpr float space = 5.0f;
    constexpr int32_t itemCount = 9;
    constexpr size_t expectItemCount = 8;

    /**
     * @tc.steps: step1. Set Space of list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(space));
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * (space + DEFAULT_ITEM_MAIN_LENGTH)));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, (i * (space + DEFAULT_ITEM_MAIN_LENGTH) + DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest001
 * @tc.desc: Set the initialIndex attribute, List layout starting from initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest001, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 8;

    /**
     * @tc.steps: step1. get frameNode and set initialIndex for List.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i + initIndex].startPos, (i * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i + initIndex].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest002
 * @tc.desc: Set the initialIndex attribute, Total ListItem size less than viewport, List layout starting from first
 * ListItem.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest002, TestSize.Level1)
{
    constexpr int32_t initIndex = 1;
    constexpr size_t itemCount = 5;

    /**
     * @tc.steps: step1. get frameNode and set initialIndex for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), itemCount);
    for (size_t i = 0; i < itemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest003
 * @tc.desc: Set the initialIndex attribute, The total size of ListItems after initialIndex is less than viewport,
 * ListItem bottom to viewport.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest003, TestSize.Level1)
{
    constexpr int32_t initIndex = 5;
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 8;
    constexpr int32_t expectItemStartIndex = 2;

    /**
     * @tc.steps: step1. get frameNode and set initialIndex for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i + expectItemStartIndex].startPos, (i * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i + expectItemStartIndex].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest004
 * @tc.desc: Set the initialIndex attribute, initialIndex out of range, ignore.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest004, TestSize.Level1)
{
    constexpr int32_t initIndex = 100;
    constexpr int32_t itemCount = 10;
    constexpr size_t expectItemCount = 8U;

    /**
     * @tc.steps: step1. get frameNode and set initialIndex for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(initIndex);
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest005
 * @tc.desc: Set the initialIndex attribute, initialIndex is not an integer multiple of the lanes,
 * List layout starting from an index integer multiple of the lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest005, TestSize.Level1)
{
    constexpr int32_t lanes = 2;
    constexpr size_t expectItemCount = 16;
    constexpr int32_t expectItemStartIndex = 2;

    /**
     * @tc.steps: step1. Set initialIndex for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(3);
    listModelNG.SetLanes(lanes);
    CreateListItem(20);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2 Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        float startPos = (i / lanes) * DEFAULT_ITEM_MAIN_LENGTH;
        EXPECT_FLOAT_EQ(itemPosition[i + expectItemStartIndex].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i + expectItemStartIndex].endPos, startPos + DEFAULT_ITEM_MAIN_LENGTH);
    }
}

/**
 * @tc.name: ListAttrLanesTest001
 * @tc.desc: Set the lanes attribute, List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrLanesTest001, TestSize.Level1)
{
    constexpr int32_t lanes = 2;

    /**
     * @tc.steps: step1. get frameNode and set lanes attribute for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(lanes);
    CreateListItem(19);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    constexpr size_t EXPECT_ITEM_COUNT1 = 16;
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT1);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT1; i++) {
        float startPos = (i / lanes) * DEFAULT_ITEM_MAIN_LENGTH;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_LENGTH);
    }

    /**
     * @tc.steps: step3. Scroll bottom, RunMeasureAndLayout and check ListItem position.
     */
    constexpr float SCROLL_OFFSET = -300.f;
    pattern_->UpdateCurrentOffset(SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();

    constexpr int32_t START_INDEX = 4;
    constexpr size_t EXPECT_ITEM_COUNT2 = 15;
    itemPosition = pattern_->GetItemPosition();
    for (size_t i = 0; i < EXPECT_ITEM_COUNT2; i++) {
        float startPos = (i / lanes) * DEFAULT_ITEM_MAIN_LENGTH;
        EXPECT_FLOAT_EQ(itemPosition[i + START_INDEX].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i + START_INDEX].endPos, startPos + DEFAULT_ITEM_MAIN_LENGTH);
    }
}

/**
 * @tc.name: ListAttrLanesTest002
 * @tc.desc: Set the minLaneLength and maxLaneLength attribute for List, List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrLanesTest002, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 480.f;
    constexpr size_t expectItemCount = 16;

    /**
     * @tc.steps: step1. get frameNode and set minLaneLength and maxLaneLength for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(19);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        float startPos = (i / 2) * DEFAULT_ITEM_MAIN_LENGTH;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_LENGTH);
        auto geometryNode = GetChildGeometryNode(frameNode_, i);
        auto width = geometryNode->GetFrameSize().Width();
        EXPECT_FLOAT_EQ(width, 240);
    }
}

/**
 * @tc.name: ListAttrLanesTest003
 * @tc.desc: Set the minLaneLength and maxLaneLength attribute for List, maxLaneLength less than minLaneLength, use
 * minLaneLength.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrLanesTest003, TestSize.Level1)
{
    constexpr float minLaneLength = 220.f;
    constexpr float maxLaneLength = 100.f;
    constexpr size_t expectItemCount = 16;

    /**
     * @tc.steps: step1. get frameNode and set maxLaneLength and minLaneLength for List, maxLaneLength less than
     * minLaneLength.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(minLaneLength));
    listModelNG.SetLaneMaxLength(Dimension(maxLaneLength));
    CreateListItem(19);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step3. Check ListItem position.
     */
    auto itemPosition = pattern_->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        float startPos = (i / 2) * DEFAULT_ITEM_MAIN_LENGTH;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_LENGTH);
        auto geometryNode = GetChildGeometryNode(frameNode_, i);
        auto width = geometryNode->GetFrameSize().Width();
        EXPECT_FLOAT_EQ(width, minLaneLength);
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
    GetListInstance();
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
    GetListInstance();
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
    GetListInstance();
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
    GetListInstance();
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
    GetListInstance();
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
    GetListInstance();
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
    constexpr float endNodeSize = 80.f;

    /**
     * @tc.steps: step1. get frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(endNodeSize, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. move to 30px.
     * @tc.expected: swiper to startNode
     */
    auto itemPattern = GetItemPattern(0);
    constexpr float MOVE_DELTA1 = 30.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA1);
    GestureEvent info;
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. move to 50px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA2 = 20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA2);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. move to -30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA3 = -80.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA3);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. move to -50px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA4 = -20.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA4);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step6. move to 30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA5 = 80.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA5);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step7. move to -30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA6 = -60.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA6);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step8. move to 30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA7 = 60.f;
    ListItemSwipeMoveAndLayout(itemPattern, MOVE_DELTA7);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
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

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetSpace(Dimension(space));
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(itemCount));
    for (size_t i = 0; i < itemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * (DEFAULT_ITEM_MAIN_LENGTH + space)));
        EXPECT_FLOAT_EQ(itemPosition[i].second, (i * (DEFAULT_ITEM_MAIN_LENGTH + space) + DEFAULT_ITEM_MAIN_LENGTH));
    }
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
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(itemCount));
    for (int32_t i = 0; i < itemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * DEFAULT_ITEM_MAIN_LENGTH) + DEFAULT_HEADER_MAIN_LENGTH);
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH) + DEFAULT_HEADER_MAIN_LENGTH);
    }
    auto itemGroupFrameNode = GetItemFrameNode(0);
    EXPECT_NE(itemGroupFrameNode, nullptr);
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
    SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
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
    SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
    ViewStackProcessor::GetInstance()->Pop();
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: footer is sticky under header
     */
    auto itemGroupFrameNode = GetItemFrameNode(1);
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
    constexpr float SCROLL_OFFSET = -250.f;
    pattern_->UpdateCurrentOffset(SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
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
    constexpr float SCROLL_OFFSET2 = -700.f;
    pattern_->UpdateCurrentOffset(SCROLL_OFFSET2, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
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
    constexpr float SCROLL_OFFSET3 = -250.f;
    pattern_->UpdateCurrentOffset(SCROLL_OFFSET3, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), -450.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, headerIndex);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 400.f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, footerIndex);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 450.f);
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
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = 0; i < expectItemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i + 1) * DEFAULT_ITEM_MAIN_LENGTH));
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
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(1);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(itemCount);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItem(1);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    auto itemGroupPattern = GetItemGroupPattern(0);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    auto offset = itemGroupPattern->GetHostFrameOffset();
    constexpr float ITEM_GROUP_OFFSET = -100.f;
    EXPECT_FLOAT_EQ(offset->GetY(), ITEM_GROUP_OFFSET);
    constexpr int32_t ITEM_START = 2;
    EXPECT_EQ(itemPosition.size(), expectItemCount);
    for (size_t i = ITEM_START; i < itemCount; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, ((i - ITEM_START) * DEFAULT_ITEM_MAIN_LENGTH));
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i - ITEM_START + 1) * DEFAULT_ITEM_MAIN_LENGTH));
    }
}

/**
 * @tc.name: ListEventTest001
 * @tc.desc: Verify onScroll, onScrollIndex, onReachStart, onReachEnd callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    bool isScrollEventCalled = false;
    bool isScrollIndexEventCalled = false;
    bool isReachStartEventCalled = false;
    bool isReachEndEventCalled = false;
    auto scrollEvent = [&isScrollEventCalled](Dimension, ScrollState) { isScrollEventCalled = true; };
    auto scrollIndexEvent = [&isScrollIndexEventCalled](int32_t, int32_t) { isScrollIndexEventCalled = true; };
    auto reachStartEvent = [&isReachStartEventCalled]() { isReachStartEventCalled = true; };
    auto reachEndEvent = [&isReachEndEventCalled]() { isReachEndEventCalled = true; };
    listModelNG.SetOnScroll(scrollEvent);
    listModelNG.SetOnScrollIndex(scrollIndexEvent);
    listModelNG.SetOnReachStart(reachStartEvent);
    listModelNG.SetOnReachEnd(reachEndEvent);
    CreateListItem(10);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Scroll 100px, RunMeasureAndLayout and check onScroll, onScrollIndex called.
     * @tc.expected: The onScroll, onScrollIndex callback is called.
     */
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollEventCalled);
    EXPECT_TRUE(isScrollIndexEventCalled);

    /**
     * @tc.steps: step3. Scroll back 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll, onReachStart callback is called.
     */
    isScrollEventCalled = false;
    pattern_->UpdateCurrentOffset(100.f, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollEventCalled);
    EXPECT_TRUE(isReachStartEventCalled);

    /**
     * @tc.steps: step4. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll callback is called.
     */
    isScrollEventCalled = false;
    pattern_->UpdateCurrentOffset(-100.f, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollEventCalled);

    /**
     * @tc.steps: step5. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll callback is called.
     */
    isScrollEventCalled = false;
    pattern_->UpdateCurrentOffset(100.f, SCROLL_FROM_NONE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollEventCalled);

    /**
     * @tc.steps: step6. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onReachEnd callback is called.
     */
    pattern_->UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    pattern_->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout();
    EXPECT_TRUE(isReachEndEventCalled);
}

/**
 * @tc.name: ListEventTest002
 * @tc.desc: Verify onScrollStart, onScrollStop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    bool isScrollStartEventCalled = false;
    bool isScrollStopEventCalled = false;
    auto scrollStartEvent = [&isScrollStartEventCalled]() { isScrollStartEventCalled = true; };
    auto scrollStopEvent = [&isScrollStopEventCalled]() { isScrollStopEventCalled = true; };
    listModelNG.SetOnScrollStart(scrollStartEvent);
    listModelNG.SetOnScrollStop(scrollStopEvent);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Call func.
     * @tc.expected: The callback is called.
     */
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartEventCalled);

    pattern_->OnScrollEndCallback();
    RunMeasureAndLayout();
    EXPECT_TRUE(isScrollStopEventCalled);
}

/**
 * @tc.name: ListEventTest003
 * @tc.desc: Verify onItemDragStart, onItemDragEnter, onItemDragMove, onItemDragLeave, onItemDrop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and listItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(10);
    bool isItemDragStartEventCalled = false;
    auto itemDragStartEvent = [&isItemDragStartEventCalled](const ItemDragInfo&, int32_t) {
        isItemDragStartEventCalled = true;
        auto dragItem = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
        return dragItem;
    };
    listModelNG.SetOnItemDragStart(itemDragStartEvent);
    listModelNG.SetOnItemDragEnter([](const ItemDragInfo&) {});
    listModelNG.SetOnItemDragLeave([](const ItemDragInfo&, int32_t) {});
    listModelNG.SetOnItemDragMove([](const ItemDragInfo&, int32_t, int32_t) {});
    listModelNG.SetOnItemDrop([](const ItemDragInfo&, int32_t, int32_t, bool) {});
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step4. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    GestureEvent info;
    Point globalPoint = Point(200.f, 150.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_TRUE(isItemDragStartEventCalled);
    EXPECT_EQ(eventHub_->draggedIndex_, 1);
    EXPECT_NE(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step5. Trigger HandleOnItemDragUpdate and HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step6. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate and HandleOnItemDragCancel.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub_->HandleOnItemDragStart(info);
    eventHub_->HandleOnItemDragUpdate(info);
    eventHub_->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(eventHub_->dragDropProxy_, nullptr);
}

/**
 * @tc.name: ListSelectTest001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Click the (0, 0) point of firstItem.
     * @tc.expected: Can not select by click, the item is not selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> firstItemPattern = GetItemPattern(0);
    EXPECT_FALSE(firstItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());
}

/**
 * @tc.name: ListSelectTest002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectTest002, TestSize.Level1)
{
    const Offset LEFT_TOP = Offset(120.f, 250.f);
    const Offset LEFT_BOTTOM = Offset(120.f, 350.f);
    const Offset RIGHT_TOP = Offset(360.f, 250.f);
    const Offset RIGHT_BOTTOM = Offset(360.f, 350.f);

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(9);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> firstItemPattern = GetItemPattern(0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    RefPtr<ListItemPattern> secondItemPattern = GetItemPattern(1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    secondItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step3. Select (120, 150) - (360, 250) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> thirdItemPattern = GetItemPattern(2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    RefPtr<ListItemPattern> fourthItemPattern = GetItemPattern(3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step4. Select (120, 150) - (360, 250) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step5. Select (120, 150) - (360, 250) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step6. Select (120, 150) - (360, 250) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_TOP);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);
}

/**
 * @tc.name: ListSelectTest003
 * @tc.desc: Test listItem selectable property and onSelect callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectTest003, TestSize.Level1)
{
    constexpr int32_t itemCount = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);

    /**
     * @tc.steps: step2. Create listItem and set an unselectable.
     */
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    for (int32_t i = 0; i < itemCount; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_LENGTH));
        SetWidth(DEFAULT_ITEM_CROSS_LENGTH);
        if (i == 3) {
            listItemModel.SetSelectable(false);
        }
        if (i == 4) {
            listItemModel.SetSelectCallback(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step3. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(120.f, 350.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(360.f, 450.f));
    pattern_->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> fourthItemPattern = GetItemPattern(3);
    EXPECT_FALSE(fourthItemPattern->IsSelected());
    RefPtr<ListItemPattern> fifthItemPattern = GetItemPattern(4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
    info.SetAction(MouseAction::RELEASE);
    pattern_->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern->MarkIsSelected(false);
    fifthItemPattern->MarkIsSelected(false);
}

/**
 * @tc.name: ListAccessibilityTest001
 * @tc.desc: Test :List Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAccessibilityTest001, TestSize.Level1)
{
    constexpr int32_t itemCount = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(itemCount);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<ListAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    RunMeasureAndLayout();
    auto pattern = frameNode->GetPattern<ListPattern>();
    pattern->startIndex_ = 1;

    /**
     * @tc.steps: step3. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibility->IsScrollable());
    EXPECT_EQ(accessibility->GetBeginIndex(), 1);
    EXPECT_EQ(accessibility->GetCurrentIndex(), 1);
    EXPECT_EQ(accessibility->GetEndIndex(), 7);
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), itemCount);
    accessibility->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibility->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: ListAccessibilityTest002
 * @tc.desc: Test :ListItem Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(9);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetItemFrameNode(1);
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemAccessibility = itemFrameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    ASSERT_NE(itemAccessibility, nullptr);
    EXPECT_FALSE(itemAccessibility->IsSelected());

    itemAccessibility->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = itemAccessibility->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: ListItemEventTest001
 * @tc.desc: Test ListItem Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(9);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Run GetDragExtraParams func.
     * @tc.expected: Verify return value.
     */
    auto itemFrameNode = GetItemFrameNode(1);
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemEventHub = itemFrameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(itemEventHub, nullptr);
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 0), DragEventType::ENTER);
    EXPECT_NE(jsonStr, "");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 0), DragEventType::START);
    EXPECT_NE(jsonStr, "");
}

/**
 * @tc.name: ListPatternTest001
 * @tc.desc: Test list pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and Get frameNode.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetListInstance();

    /**
     * @tc.steps: step2. Run OnKeyEvent with KeyAction.
     * @tc.expected: Verify return_value.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    // Call OnKeyEvent with KeyAction::DOWN
    keyEvent.code = KeyCode::KEY_PAGE_DOWN;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_PAGE_UP;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
}

/**
 * @tc.name: ListPatternTest002
 * @tc.desc: Test list pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and Get frameNode.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetListInstance();

    /**
     * @tc.steps: step2. Call AnimateTo
     */
    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_ = AceType::MakeRefPtr<Animator>();

    pattern_->animator_->Pause();
    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);

    pattern_->animator_->Resume();
    pattern_->AnimateTo(0, 0, nullptr);
    EXPECT_NE(pattern_->animator_, nullptr);
}

/**
 * @tc.name: ListPatternTest003
 * @tc.desc: Test list pattern SetChainAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and Get frameNode.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetEdgeEffect(EdgeEffect::SPRING);
    listModelNG.SetChainAnimation(true);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. chainAnimation_ is not null.
     */
    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
}

/**
 * @tc.name: ListPositionControllerTest001
 * @tc.desc: Test PositionController function with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and Get frameNode.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetListDirection(Axis::NONE);
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Test func.
     */
    RefPtr<ListPositionController> positionController = AceType::MakeRefPtr<ListPositionController>();
    // AnimateTo
    EXPECT_FALSE(positionController->AnimateTo(Dimension(0), 0, nullptr));
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));
    EXPECT_FALSE(positionController->AnimateTo(Dimension(0), 0, nullptr));
    // ScrollBy
    positionController->ScrollBy(0, 0, true);
    EXPECT_EQ(pattern_->barOffset_, 0);
    // ScrollToEdge
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    // ScrollPage
    positionController->ScrollPage(true, true);
    // JumpTo
    positionController->JumpTo(1, 0);
    EXPECT_EQ(pattern_->jumpIndex_, 1);
    // GetScrollDirection
    EXPECT_EQ(positionController->GetScrollDirection(), Axis::NONE);
    // GetCurrentOffset
    Offset offset = positionController->GetCurrentOffset();
    EXPECT_EQ(offset.GetX(), 0.f);
    EXPECT_EQ(offset.GetY(), 0.f);
}

/**
 * @tc.name: ListPositionControllerTest002
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListPositionControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and Get frameNode.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    GetListInstance();
    RunMeasureAndLayout();

    /**
     * @tc.steps: step2. Test func.
     */
    RefPtr<ListPositionController> positionController = AceType::MakeRefPtr<ListPositionController>();
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(pattern_));
    // AnimateTo
    EXPECT_FALSE(positionController->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr));
    EXPECT_TRUE(positionController->AnimateTo(Dimension(1), 0, nullptr));
    EXPECT_TRUE(positionController->AnimateTo(Dimension(1), 1, nullptr));
    // ScrollBy
    positionController->ScrollBy(0, 0, true);
    EXPECT_EQ(pattern_->barOffset_, 0);
    // GetScrollDirection
    EXPECT_EQ(positionController->GetScrollDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: ListItemGroupAccessibilityPropertyTest001
 * @tc.desc: Test the GetBeginIndex and GetEndIndex function of ListItemGroupAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupAccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listItemGroup frameNode and get listItemGroupAccessibilityProperty.
     * @tc.expected: step1. get listItemGroupAccessibilityProperty success.
     */
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);

    /**
     * @tc.steps: step2. get the beginIndex and endIndex of listItemGroupAccessibilityProperty.
     * @tc.expected: step2. the beginIndex and endIndex of listItemGroupAccessibilityProperty properties equals default
     * value.
     */
    EXPECT_EQ(accessibility->GetBeginIndex(), -1);
    EXPECT_EQ(accessibility->GetEndIndex(), -1);

    /**
     * @tc.steps: step3. get listItemGroupPattern and set the listItemGroupPattern itemPosition_ property.
     * @tc.steps: step4. get the beginIndex and endIndex of listItemGroupAccessibilityProperty.
     * @tc.expected: step4. the beginIndex and endIndex of listItemGroupAccessibilityProperty properties equals expected
     * value.
     */
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    for (int i = 0; i <= LIST_ITEM_NUMBER; i++) {
        pattern->itemPosition_[i] = { LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT * i };
    }
    EXPECT_EQ(accessibility->GetBeginIndex(), 0);
    EXPECT_EQ(accessibility->GetEndIndex(), LIST_ITEM_NUMBER);
}

/**
 * @tc.name: ListItemGroupAccessibilityPropertyTest002
 * @tc.desc: Test the GetCollectionItemCounts function of ListItemGroupAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupAccessibilityPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listItemGroup frameNode and get listItemGroupAccessibilityProperty.
     * @tc.expected: step1. get listItemGroupAccessibilityProperty success.
     */
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);

    /**
     * @tc.steps: step2. get collectionItemCounts of listItemGroupAccessibilityProperty.
     * @tc.expected: step2. the collectionItemCounts of listItemGroupAccessibilityProperty properties equals default
     * value.
     */
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), 0);

    /**
     * @tc.steps: step3. set totalItemCount_ of ListItemGroupLayoutAlgorithm
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<ListItemGroupLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 0);
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->totalItemCount_ = LIST_ITEM_NUMBER;
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig config;
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    config.skipMeasure = false;
    config.skipLayout = false;
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. get collectionItemCounts of listItemGroupAccessibilityProperty.
     * @tc.expected: step4. the collectionItemCounts of listItemGroupAccessibilityProperty properties equals expected
     * value.
     */
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), LIST_ITEM_NUMBER);
}
} // namespace OHOS::Ace::NG

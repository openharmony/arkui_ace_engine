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
#define private public
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
constexpr float DEFAULT_ITEM_MAIN_SIZE = 100.f;
constexpr float DEFAULT_HEADER_MAIN_SIZE = 50.f;
constexpr Dimension DEFAULT_ITEM_CROSS_SIZE = Dimension(1.0, DimensionUnit::PERCENT);
} // namespace
class ListTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineBase::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineBase::TearDown();
    }

    static void SetWidth(const Dimension& width)
    {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
    }

    static void SetHeight(const Dimension& height)
    {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
    }

    static void CreateListItem(int32_t number)
    {
        for (int32_t i = 0; i < number; i++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            SetWidth(DEFAULT_ITEM_CROSS_SIZE);
            ViewStackProcessor::GetInstance()->Pop();
        }
    }

    static void CreateListItemWithoutWidth(int32_t number)
    {
        for (int32_t i = 0; i < number; i++) {
            ListItemModelNG listItemModel;
            listItemModel.Create();
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            ViewStackProcessor::GetInstance()->Pop();
        }
    }

    static void CreateListItemWithSwiper(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
    {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
        SetWidth(DEFAULT_ITEM_CROSS_SIZE);
        listItemModel.SetSwiperAction(std::move(startAction), std::move(endAction), effect);
        {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            SetWidth(DEFAULT_ITEM_CROSS_SIZE);
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    static RefPtr<FrameNode> CreateListWithInitIndex(int32_t initIndex, int32_t number)
    {
        ListModelNG listModelNG;
        listModelNG.Create();
        listModelNG.SetInitialIndex(initIndex);
        CreateListItem(number);
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
        return AceType::DynamicCast<FrameNode>(element);
    }

    static void RunMeasureAndLayout(const RefPtr<FrameNode>& frameNode)
    {
        RefPtr<LayoutWrapper> listLayoutWrapper = frameNode->CreateLayoutWrapper(false, false);
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

    static RefPtr<GeometryNode> GetChildGeometryNode(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        auto item = frameNode->GetChildAtIndex(index);
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            return nullptr;
        }
        return itemFrameNode->GetGeometryNode();
    }

    static RefPtr<ListItemPattern> GetItemPattern(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        auto item = frameNode->GetChildAtIndex(index);
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            return nullptr;
        }
        return itemFrameNode->GetPattern<ListItemPattern>();
    }

    static RefPtr<ListItemGroupPattern> GetItemGroupPattern(const RefPtr<FrameNode>& frameNode, int32_t index)
    {
        auto item = frameNode->GetChildAtIndex(index);
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        if (!itemFrameNode) {
            return nullptr;
        }
        return itemFrameNode->GetPattern<ListItemGroupPattern>();
    }

    static void ListItemSwipeMoveAndLayout(
        const RefPtr<FrameNode>& frameNode, const RefPtr<ListItemPattern>& itemPattern, float moveDelta)
    {
        GestureEvent info;
        info.SetMainDelta(moveDelta);
        itemPattern->HandleDragUpdate(info);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        RunMeasureAndLayout(frameNode);
    }

    static std::function<void()> GetDefaultSwiperBuilder(float crossSize, bool spring)
    {
        return [crossSize, spring]() {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
            if (spring) {
                RowModelNG rowModel;
                rowModel.Create(std::nullopt, nullptr, "");
                SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
                SetWidth(Dimension(crossSize));
                ViewStackProcessor::GetInstance()->Pop();
            } else {
                SetWidth(Dimension(crossSize));
            }
        };
    }

    static std::function<void()> GetDefaultHeaderBuilder()
    {
        return []() {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            SetHeight(Dimension(DEFAULT_HEADER_MAIN_SIZE));
            SetWidth(DEFAULT_ITEM_CROSS_SIZE);
        };
    }
};

/**
 * @tc.name: ListAttrSpaceTest001
 * @tc.desc: Set the Space attribute. There is a space between ListItems
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrSpaceTest001, TestSize.Level1)
{
    constexpr float SPACE = 5.0f;
    constexpr int32_t ITEM_COUNT = 9;
    constexpr size_t EXPECT_ITEM_COUNT = 8;

    /**
     * @tc.steps: step1. create frameNode and set SetSpace of list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetSpace(Dimension(SPACE, DimensionUnit::PX));
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * (SPACE + DEFAULT_ITEM_MAIN_SIZE)));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, (i * (SPACE + DEFAULT_ITEM_MAIN_SIZE) + DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest001
 * @tc.desc: Set the initialIndex attribute, List layout starting from initialIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest001, TestSize.Level1)
{
    constexpr int32_t INIT_INDEX = 1;
    constexpr int32_t ITEM_COUNT = 10;
    constexpr size_t EXPECT_ITEM_COUNT = 8;

    /**
     * @tc.steps: step1. create frameNode and set initialIndex for List.
     */
    auto frameNode = CreateListWithInitIndex(INIT_INDEX, ITEM_COUNT);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i + INIT_INDEX].startPos, (i * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i + INIT_INDEX].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE));
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
    constexpr int32_t INIT_INDEX = 1;
    constexpr size_t ITEM_COUNT = 5;

    /**
     * @tc.steps: step1. create frameNode and set initialIndex for list.
     */
    auto frameNode = CreateListWithInitIndex(INIT_INDEX, ITEM_COUNT);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), ITEM_COUNT);
    for (size_t i = 0; i < ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE));
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
    constexpr int32_t INIT_INDEX = 5;
    constexpr int32_t ITEM_COUNT = 10;
    constexpr size_t EXPECT_ITEM_COUNT = 8;
    constexpr int32_t EXPECT_ITEM_START_INDEX = 2;

    /**
     * @tc.steps: step1. create frameNode and set initialIndex for list.
     */
    auto frameNode = CreateListWithInitIndex(INIT_INDEX, ITEM_COUNT);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i + EXPECT_ITEM_START_INDEX].startPos, (i * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i + EXPECT_ITEM_START_INDEX].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest004
 * @tc.desc: Set the initialIndex attribute, initialIndex out of range, ignore.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest004, TestSize.Level1)
{
    constexpr int32_t INIT_INDEX = 100;
    constexpr int32_t ITEM_COUNT = 10;
    constexpr size_t EXPECT_ITEM_COUNT = 8U;

    /**
     * @tc.steps: step1. create frameNode and set initialIndex for list.
     */
    auto frameNode = CreateListWithInitIndex(INIT_INDEX, ITEM_COUNT);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, (i * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListAttrInitIndexTest005
 * @tc.desc: Set the initialIndex attribute, initialIndex is not an integer multiple of the lanes, List layout starting
 * from an index integer multiple of the lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrInitIndexTest005, TestSize.Level1)
{
    constexpr int32_t INIT_INDEX = 3;
    constexpr int32_t ITEM_COUNT = 20;
    constexpr int32_t LANES = 2;
    constexpr size_t EXPECT_ITEM_COUNT = 16;
    constexpr int32_t EXPECT_ITEM_START_INDEX = 2;

    /**
     * @tc.steps: step1. create frameNode and set initialIndex for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(INIT_INDEX);
    listModelNG.SetLanes(LANES);
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2 RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        float startPos = (i / LANES) * DEFAULT_ITEM_MAIN_SIZE;
        EXPECT_FLOAT_EQ(itemPosition[i + EXPECT_ITEM_START_INDEX].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i + EXPECT_ITEM_START_INDEX].endPos, startPos + DEFAULT_ITEM_MAIN_SIZE);
    }
}

/**
 * @tc.name: ListAttrLanesTest001
 * @tc.desc: Set the lanes attribute, List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrLanesTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 19;
    constexpr int32_t LANES = 2;

    /**
     * @tc.steps: step1. create frameNode and set lanes attribute for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLanes(LANES);
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2 RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    constexpr size_t EXPECT_ITEM_COUNT1 = 16;
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT1);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT1; i++) {
        float startPos = (i / LANES) * DEFAULT_ITEM_MAIN_SIZE;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_SIZE);
    }

    /**
     * @tc.steps: step3. Scroll bottom, RunMeasureAndLayout and check ListItem position.
     */
    constexpr float SCROLL_OFFSET = -300.f;
    pattern->UpdateCurrentOffset(SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);

    constexpr int32_t START_INDEX = 4;
    constexpr size_t EXPECT_ITEM_COUNT2 = 15;
    itemPosition = pattern->GetItemPosition();
    for (size_t i = 0; i < EXPECT_ITEM_COUNT2; i++) {
        float startPos = (i / LANES) * DEFAULT_ITEM_MAIN_SIZE;
        EXPECT_FLOAT_EQ(itemPosition[i + START_INDEX].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i + START_INDEX].endPos, startPos + DEFAULT_ITEM_MAIN_SIZE);
    }
}

/**
 * @tc.name: ListAttrLanesTest002
 * @tc.desc: Set the minLaneLength and maxLaneLength attribute for List, List layout as 2 lanes.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAttrLanesTest002, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 19;
    constexpr float MIN_LANE_LENGTH = 220.f;
    constexpr float MAX_LANE_LENGTH = 480.f;
    constexpr size_t EXPECT_ITEM_COUNT = 16;

    /**
     * @tc.steps: step1. create frameNode and set minLaneLength and maxLaneLength for list.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(MIN_LANE_LENGTH));
    listModelNG.SetLaneMaxLength(Dimension(MAX_LANE_LENGTH));
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        float startPos = (i / 2) * DEFAULT_ITEM_MAIN_SIZE;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_SIZE);
        auto geometryNode = GetChildGeometryNode(frameNode, i);
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
    constexpr int32_t ITEM_COUNT = 19;
    constexpr float MIN_LANE_LENGTH = 220.f;
    constexpr float MAX_LANE_LENGTH = 100.f;
    constexpr size_t EXPECT_ITEM_COUNT = 16;

    /**
     * @tc.steps: step1. create frameNode and set maxLaneLength and minLaneLength for List, maxLaneLength less than
     * minLaneLength.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetLaneMinLength(Dimension(MIN_LANE_LENGTH));
    listModelNG.SetLaneMaxLength(Dimension(MAX_LANE_LENGTH));
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    auto itemPosition = pattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        float startPos = (i / 2) * DEFAULT_ITEM_MAIN_SIZE;
        EXPECT_FLOAT_EQ(itemPosition[i].startPos, startPos);
        EXPECT_FLOAT_EQ(itemPosition[i].endPos, startPos + DEFAULT_ITEM_MAIN_SIZE);
        auto geometryNode = GetChildGeometryNode(frameNode, i);
        auto width = geometryNode->GetFrameSize().Width();
        EXPECT_FLOAT_EQ(width, MIN_LANE_LENGTH);
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
    constexpr float START_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check result.
     * @tc.expected: startNode is not measure and layout
     */
    RunMeasureAndLayout(frameNode);

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
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);

    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), 0);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), 0);

    /**
     * @tc.steps: step4. move right 45px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 45px - START_NODE_SIZE
     */
    constexpr float MOVE_DELTA2 = 45.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), MOVE_DELTA2);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), START_NODE_SIZE);
    EXPECT_FLOAT_EQ(startRect.GetX(), MOVE_DELTA2 - START_NODE_SIZE);

    /**
     * @tc.steps: step5. continue move right 45px, RunMeasureAndLayout and check result.
     * @tc.expected: startNode loaded, x position is 0, child node position is START_NODE_SIZE
     */
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), START_NODE_SIZE);
    startNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    startRect = startNode->GetFrameRect();
    EXPECT_FLOAT_EQ(startRect.Width(), START_NODE_SIZE);
    EXPECT_FLOAT_EQ(startRect.GetX(), 0);
}

/**
 * @tc.name: ListItemAttrSwiperTest002
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode and edge effect is none.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest002, TestSize.Level1)
{
    constexpr float END_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check result.
     * @tc.expected: endNode is not measure and layout
     */
    RunMeasureAndLayout(frameNode);

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
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);

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
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), MOVE_DELTA2);
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), END_NODE_SIZE);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH + MOVE_DELTA2);

    /**
     * @tc.steps: step5. continue move left 45px, RunMeasureAndLayout and check result.
     * @tc.expected: endNode loaded, x position is -END_NODE_SIZE, child node position
     *     is DEFAULT_ROOT_WIDTH - END_NODE_SIZE
     */
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    childRect = childNode->GetFrameRect();
    EXPECT_FLOAT_EQ(childRect.GetX(), -END_NODE_SIZE);
    endNode = GetChildGeometryNode(itemPattern->GetHost(), 0);
    endRect = endNode->GetFrameRect();
    EXPECT_FLOAT_EQ(endRect.Width(), END_NODE_SIZE);
    EXPECT_FLOAT_EQ(endRect.GetX(), DEFAULT_ROOT_WIDTH - END_NODE_SIZE);
}

/**
 * @tc.name: ListItemAttrSwiperTest003
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode and edge effect is spring,
 * move friction take effect when moving to the left.
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemAttrSwiperTest003, TestSize.Level1)
{
    constexpr float START_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, false);
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. move left 20px twice.
     * @tc.expected: move friction take effect
     */
    RunMeasureAndLayout(frameNode);
    constexpr float MOVE_DELTA1 = -20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);

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
    constexpr float END_NODE_SIZE = 80.f;
    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, false);
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. move right 20px twice.
     * @tc.expected: move friction take effect
     */
    RunMeasureAndLayout(frameNode);
    constexpr float MOVE_DELTA1 = 20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);

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
    constexpr float START_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_SIZE, true);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. moving to the left distance great than endNode size, check endNode position.
     */
    RunMeasureAndLayout(frameNode);
    constexpr float MOVE_DELTA1 = 100.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);
    constexpr float MOVE_DELTA2 = 20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(MOVE_DELTA2 / (DEFAULT_ROOT_WIDTH - START_NODE_SIZE));
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
    constexpr float END_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_SIZE, true);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. moving to the right distance great than endNode size, check endNode position.
     */
    RunMeasureAndLayout(frameNode);
    constexpr float MOVE_DELTA1 = -100.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);
    constexpr float MOVE_DELTA2 = -20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);

    auto childNode = GetChildGeometryNode(itemPattern->GetHost(), 1);
    auto childRect = childNode->GetFrameRect();
    auto factor = ListItemPattern::CalculateFriction(-MOVE_DELTA2 / (DEFAULT_ROOT_WIDTH - END_NODE_SIZE));
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
    constexpr float END_NODE_SIZE = 80.f;

    /**
     * @tc.steps: step1. create frameNode and set SetSwiperAction for ListItem.
     */
    auto builder = GetDefaultSwiperBuilder(END_NODE_SIZE, false);

    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItemWithSwiper(builder, builder, V2::SwipeEdgeEffect::Spring);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemPattern = GetItemPattern(frameNode, 0);

    /**
     * @tc.steps: step2. move to 30px.
     * @tc.expected: swiper to startNode
     */
    RunMeasureAndLayout(frameNode);
    constexpr float MOVE_DELTA1 = 30.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA1);
    GestureEvent info;
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. move to 50px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA2 = 20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA2);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. move to -30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA3 = -80.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA3);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. move to -50px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA4 = -20.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA4);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step6. move to 30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA5 = 80.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA5);
    itemPattern->HandleDragEnd(info);
    EXPECT_EQ(itemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step7. move to -30px.
     * @tc.expected: swiper to childNode
     */
    itemPattern->HandleDragStart(info);
    constexpr float MOVE_DELTA6 = -60.f;
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA6);
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
    ListItemSwipeMoveAndLayout(frameNode, itemPattern, MOVE_DELTA7);
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
    constexpr float SPACE = 5.0f;
    constexpr int32_t ITEM_COUNT = 5;

    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetSpace(Dimension(SPACE, DimensionUnit::PX));
    CreateListItem(ITEM_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemGroupPattern = GetItemGroupPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(ITEM_COUNT));
    for (size_t i = 0; i < ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * (DEFAULT_ITEM_MAIN_SIZE + SPACE)));
        EXPECT_FLOAT_EQ(itemPosition[i].second, (i * (DEFAULT_ITEM_MAIN_SIZE + SPACE) + DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest001
 * @tc.desc: ListItemGroup set the header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 5;
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
    CreateListItem(ITEM_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> const element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemGroupPattern = GetItemGroupPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), static_cast<size_t>(ITEM_COUNT));
    for (int32_t i = 0; i < ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * DEFAULT_ITEM_MAIN_SIZE) + DEFAULT_HEADER_MAIN_SIZE);
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE) + DEFAULT_HEADER_MAIN_SIZE);
    }
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    EXPECT_NE(itemGroupFrameNode, nullptr);
    constexpr int32_t HEADER_INDEX = 0;
    constexpr int32_t FOOTER_INDEX = 1;
    auto headerNode = GetChildGeometryNode(itemGroupFrameNode, HEADER_INDEX);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    auto footerNode = GetChildGeometryNode(itemGroupFrameNode, FOOTER_INDEX);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 550.f);
}

/**
 * @tc.name: ListItemGroupHeaderFooterTest002
 * @tc.desc: ListItemGroup set the header and footer, List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupHeaderFooterTest002, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 4;
    constexpr float ITEM_HEIGHT = 750.f;
    constexpr int32_t HEADER_INDEX = 0;
    constexpr int32_t FOOTER_INDEX = 1;
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
    SetHeight(Dimension(ITEM_HEIGHT));
    SetWidth(DEFAULT_ITEM_CROSS_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItemGroup
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    listItemGroupModel.SetHeader(std::move(header));
    listItemGroupModel.SetFooter(std::move(footer));
    CreateListItem(ITEM_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    // Create ListItem
    ListItemModelNG listItemModel2;
    listItemModel2.Create();
    SetHeight(Dimension(ITEM_HEIGHT));
    SetWidth(DEFAULT_ITEM_CROSS_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> const element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemGroupPattern = GetItemGroupPattern(frameNode, 0);
    auto pattern = frameNode->GetPattern<ListPattern>();

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: footer is sticky under header
     */
    RunMeasureAndLayout(frameNode);
    auto itemGroupFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    EXPECT_NE(itemGroupFrameNode, nullptr);
    auto groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), ITEM_HEIGHT);
    auto headerNode = GetChildGeometryNode(itemGroupFrameNode, HEADER_INDEX);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    auto footerNode = GetChildGeometryNode(itemGroupFrameNode, FOOTER_INDEX);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 50.f);

    /**
     * @tc.steps: step3. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at bottom of List
     */
    constexpr float SCROLL_OFFSET = -250.f;
    pattern->UpdateCurrentOffset(SCROLL_OFFSET, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), 500.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, HEADER_INDEX);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 0.0f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, FOOTER_INDEX);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 250.f);

    /**
     * @tc.steps: step4. Scroll 700px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky at to of List
     */
    constexpr float SCROLL_OFFSET2 = -700.f;
    pattern->UpdateCurrentOffset(SCROLL_OFFSET2, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), -200.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, HEADER_INDEX);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 200.f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, FOOTER_INDEX);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 450.f);

    /**
     * @tc.steps: step4. Scroll 250px, RunMeasureAndLayout and check ListItemGroup footer position.
     * @tc.expected: header is sticky upper footer
     */
    constexpr float SCROLL_OFFSET3 = -250.f;
    pattern->UpdateCurrentOffset(SCROLL_OFFSET3, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
    EXPECT_NE(itemGroupFrameNode, nullptr);
    groupNode = itemGroupFrameNode->GetGeometryNode();
    EXPECT_FLOAT_EQ(groupNode->GetFrameOffset().GetY(), -450.f);
    headerNode = GetChildGeometryNode(itemGroupFrameNode, HEADER_INDEX);
    EXPECT_FLOAT_EQ(headerNode->GetFrameOffset().GetY(), 400.f);
    footerNode = GetChildGeometryNode(itemGroupFrameNode, FOOTER_INDEX);
    EXPECT_FLOAT_EQ(footerNode->GetFrameOffset().GetY(), 450.f);
}

/**
 * @tc.name: ListItemGroupLayoutTest001
 * @tc.desc: ListItemGroup forward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 10;
    constexpr size_t EXPECT_ITEM_COUNT = 9;
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(ITEM_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemGroupPattern = GetItemGroupPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = 0; i < EXPECT_ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, (i * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i + 1) * DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListItemGroupLayoutTest002
 * @tc.desc: ListItemGroup backward layout, stop layout when ListItem out of viewport
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemGroupLayoutTest002, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 10;
    constexpr size_t EXPECT_ITEM_COUNT = 8;
    /**
     * @tc.steps: step1. create List/ListItemGroup/ListItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetInitialIndex(1);
    ListItemGroupModelNG listItemGroupModel;
    listItemGroupModel.Create();
    CreateListItem(ITEM_COUNT);
    ViewStackProcessor::GetInstance()->Pop();
    CreateListItem(1);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemGroupPattern = GetItemGroupPattern(frameNode, 0);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto itemPosition = itemGroupPattern->GetItemPosition();
    auto offset = itemGroupPattern->GetHostFrameOffset();
    constexpr float ITEM_GROUP_OFFSET = -100.f;
    EXPECT_FLOAT_EQ(offset->GetY(), ITEM_GROUP_OFFSET);
    constexpr int32_t ITEM_START = 2;
    EXPECT_EQ(itemPosition.size(), EXPECT_ITEM_COUNT);
    for (size_t i = ITEM_START; i < ITEM_COUNT; i++) {
        EXPECT_FLOAT_EQ(itemPosition[i].first, ((i - ITEM_START) * DEFAULT_ITEM_MAIN_SIZE));
        EXPECT_FLOAT_EQ(itemPosition[i].second, ((i - ITEM_START + 1) * DEFAULT_ITEM_MAIN_SIZE));
    }
}

/**
 * @tc.name: ListEventTest001
 * @tc.desc: Verify onScroll, onScrollIndex, onReachStart, onReachEnd callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListEventTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 10;

    /**
     * @tc.steps: step1. Create List.
     */
    ListModelNG listModelNG;
    listModelNG.Create();

    /**
     * @tc.steps: step2. Set callback founction to list.
     */
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

    /**
     * @tc.steps: step3. Create listItem and get frameNode, pattern.
     */
    CreateListItem(ITEM_COUNT);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step4. Scroll 100px, RunMeasureAndLayout and check onScroll, onScrollIndex called.
     * @tc.expected: The onScroll, onScrollIndex callback is called.
     */
    pattern->UpdateCurrentOffset(-100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
    EXPECT_TRUE(isScrollEventCalled);
    EXPECT_TRUE(isScrollIndexEventCalled);

    /**
     * @tc.steps: step4. Scroll back 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll, onReachStart callback is called.
     */
    isScrollEventCalled = false;
    pattern->UpdateCurrentOffset(100.f, SCROLL_FROM_ANIMATION);
    RunMeasureAndLayout(frameNode);
    EXPECT_TRUE(isScrollEventCalled);
    EXPECT_TRUE(isReachStartEventCalled);

    /**
     * @tc.steps: step5. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll callback is called.
     */
    isScrollEventCalled = false;
    pattern->UpdateCurrentOffset(-100.f, SCROLL_FROM_ANIMATION_SPRING);
    RunMeasureAndLayout(frameNode);
    EXPECT_TRUE(isScrollEventCalled);

    /**
     * @tc.steps: step5. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onScroll callback is called.
     */
    isScrollEventCalled = false;
    pattern->UpdateCurrentOffset(100.f, SCROLL_FROM_NONE);
    RunMeasureAndLayout(frameNode);
    EXPECT_TRUE(isScrollEventCalled);

    /**
     * @tc.steps: step6. Scroll 100px, change ScrollState and RunMeasureAndLayout.
     * @tc.expected: The onReachEnd callback is called.
     */
    pattern->UpdateCurrentOffset(100.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
    pattern->UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    RunMeasureAndLayout(frameNode);
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

    /**
     * @tc.steps: step2. Set callback founction to list.
     */
    bool isScrollStartEventCalled = false;
    bool isScrollStopEventCalled = false;
    auto scrollStartEvent = [&isScrollStartEventCalled]() { isScrollStartEventCalled = true; };
    auto scrollStopEvent = [&isScrollStopEventCalled]() { isScrollStopEventCalled = true; };
    listModelNG.SetOnScrollStart(scrollStartEvent);
    listModelNG.SetOnScrollStop(scrollStopEvent);

    /**
     * @tc.steps: step3. Create listItem and get frameNode, pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Check onScrollStart called.
     * @tc.expected: The onScrollStart callback is called.
     */
    pattern->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(isScrollStartEventCalled);

    /**
     * @tc.steps: step5. Check onScrollEnd called.
     * @tc.expected: The onScrollEnd callback is called.
     */
    pattern->OnScrollEndCallback();
    RunMeasureAndLayout(frameNode);
    EXPECT_TRUE(isScrollStopEventCalled);
}

/**
 * @tc.name: ListEventTest003
 * @tc.desc: Verify onItemDragStart, onItemDragEnter, onItemDragMove, onItemDragLeave, onItemDrop callback
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListEventTest003, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 10;

    /**
     * @tc.steps: step1. Create List and listItem.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Set callback founction to list.
     */
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

    /**
     * @tc.steps: step3. Get frameNode, eventHub.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. Trigger HandleOnItemDragStart.
     * @tc.expected: Verify some values of the drag.
     */
    RunMeasureAndLayout(frameNode);
    GestureEvent info;
    Point globalPoint = Point(200.f, 150.f); // Point at the second item.
    info.SetGlobalPoint(globalPoint);
    eventHub->HandleOnItemDragStart(info);
    EXPECT_TRUE(isItemDragStartEventCalled);
    EXPECT_EQ(eventHub->draggedIndex_, 1);
    EXPECT_NE(eventHub->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step5. Trigger HandleOnItemDragUpdate and HandleOnItemDragEnd.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub->HandleOnItemDragUpdate(info);
    eventHub->HandleOnItemDragEnd(info);
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step6. Trigger HandleOnItemDragStart, HandleOnItemDragUpdate and HandleOnItemDragCancel.
     * @tc.expected: Verify some values of the drag.
     */
    eventHub->HandleOnItemDragStart(info);
    eventHub->HandleOnItemDragUpdate(info);
    eventHub->HandleOnItemDragCancel();
    EXPECT_EQ(eventHub->draggedIndex_, 0);
    EXPECT_EQ(eventHub->dragDropProxy_, nullptr);
}

/**
 * @tc.name: ListSelectTest001
 * @tc.desc: Test mouse click to select, only PRESS and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step4. Click the (0, 0) point of firstItem.
     * @tc.expected: The 1st item is selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE); // Release the mouse to deselect.
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    EXPECT_FALSE(firstItemPattern->IsSelected());

    /**
     * @tc.steps: step5. Click the middle of the 4th item.
     * @tc.expected: The 4th item is selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(240.f, 350.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step6. Click the lower boundary of the 4th item.
     * @tc.expected: The 4th and 5th items are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(240.f, 400.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    RefPtr<ListItemPattern> fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    fourthItemPattern->MarkIsSelected(false);
    fifthItemPattern->MarkIsSelected(false);
}

/**
 * @tc.name: ListSelectTest002
 * @tc.desc: Test mouse box selection, PRESS, MOVE and RELEASE the mouse
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListSelectTest002, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 9;
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
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step4. Select (0, 0) - (200, 100) zone.
     * @tc.expected: The 1st and 2nd items are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(0.f, 0.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(200.f, 100.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> firstItemPattern = GetItemPattern(frameNode, 0);
    EXPECT_TRUE(firstItemPattern->IsSelected());
    RefPtr<ListItemPattern> secondItemPattern = GetItemPattern(frameNode, 1);
    EXPECT_TRUE(secondItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    firstItemPattern->MarkIsSelected(false);
    secondItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step5. Select (120, 150) - (360, 250) zone, from the LEFT_TOP to the RIGHT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> thirdItemPattern = GetItemPattern(frameNode, 2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    RefPtr<ListItemPattern> fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step6. Select (120, 150) - (360, 250) zone, from the RIGHT_TOP to the LEFT_BOTTOM.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(frameNode, 2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step7. Select (120, 150) - (360, 250) zone, from the LEFT_BOTTOM to the RIGHT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(LEFT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(RIGHT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(frameNode, 2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern->MarkIsSelected(false);
    fourthItemPattern->MarkIsSelected(false);

    /**
     * @tc.steps: step8. Select (120, 150) - (360, 250) zone, from the RIGHT_BOTTOM to the LEFT_TOP.
     * @tc.expected: The 3rd and 4th are selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(RIGHT_BOTTOM);
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(LEFT_TOP);
    pattern->HandleMouseEventWithoutKeyboard(info);
    thirdItemPattern = GetItemPattern(frameNode, 2);
    EXPECT_TRUE(thirdItemPattern->IsSelected());
    fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_TRUE(fourthItemPattern->IsSelected());
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
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
    constexpr int32_t ITEM_COUNT = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    listModelNG.SetMultiSelectable(true);

    /**
     * @tc.steps: step2. Create listItem.
     */
    bool isFifthItemSelected = false;
    auto selectCallback = [&isFifthItemSelected](bool) { isFifthItemSelected = true; };
    for (int32_t i = 0; i < ITEM_COUNT; i++) {
        ListItemModelNG listItemModel;
        listItemModel.Create();
        SetHeight(Dimension(DEFAULT_ITEM_MAIN_SIZE));
        SetWidth(DEFAULT_ITEM_CROSS_SIZE);
        if (i == 3) {
            listItemModel.SetSelectable(false);
        }
        if (i == 4) {
            listItemModel.SetSelectCallback(std::move(selectCallback));
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    /**
     * @tc.steps: step3. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. RunMeasureAndLayout and set MouseButton::LEFT_BUTTON.
     */
    RunMeasureAndLayout(frameNode);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);

    /**
     * @tc.steps: step5. Select (120, 250) - (360, 350) zone.
     * @tc.expected: The 4th item is not selected but 5th item is selected.
     */
    info.SetAction(MouseAction::PRESS);
    info.SetLocalLocation(Offset(120.f, 350.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    info.SetAction(MouseAction::MOVE);
    info.SetLocalLocation(Offset(360.f, 450.f));
    pattern->HandleMouseEventWithoutKeyboard(info);
    RefPtr<ListItemPattern> fourthItemPattern = GetItemPattern(frameNode, 3);
    EXPECT_FALSE(fourthItemPattern->IsSelected());
    RefPtr<ListItemPattern> fifthItemPattern = GetItemPattern(frameNode, 4);
    EXPECT_TRUE(fifthItemPattern->IsSelected());
    EXPECT_TRUE(isFifthItemSelected);
    info.SetAction(MouseAction::RELEASE);
    pattern->HandleMouseEventWithoutKeyboard(info);
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
    constexpr int32_t ITEM_COUNT = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Get frameNode and pattern.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<ListAccessibilityProperty>();
    ASSERT_NE(accessibility, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_TRUE(accessibility->IsScrollable());
    EXPECT_EQ(accessibility->GetBeginIndex(), 0);
    EXPECT_EQ(accessibility->GetEndIndex(), 7);
    EXPECT_EQ(accessibility->GetCollectionItemCounts(), ITEM_COUNT);
}

/**
 * @tc.name: ListAccessibilityTest002
 * @tc.desc: Test :ListItem Accessibility func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListAccessibilityTest002, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Get frameNode.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Get itemFrameNode, itemAccessibility.
     */
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemAccessibility = itemFrameNode->GetAccessibilityProperty<ListItemAccessibilityProperty>();
    ASSERT_NE(itemAccessibility, nullptr);

    /**
     * @tc.steps: step3. Run accessibility func.
     * @tc.expected: Verify return value.
     */
    EXPECT_FALSE(itemAccessibility->IsSelected());
}

/**
 * @tc.name: ListItemEventTest001
 * @tc.desc: Test ListItem Event func
 * @tc.type: FUNC
 */
HWTEST_F(ListTestNg, ListItemEventTest001, TestSize.Level1)
{
    constexpr int32_t ITEM_COUNT = 9;

    /**
     * @tc.steps: step1. Create List and SetMultiSelectable.
     */
    ListModelNG listModelNG;
    listModelNG.Create();
    CreateListItem(ITEM_COUNT);

    /**
     * @tc.steps: step2. Get frameNode.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto itemFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    ASSERT_NE(itemFrameNode, nullptr);
    auto itemEventHub = itemFrameNode->GetEventHub<ListItemEventHub>();
    ASSERT_NE(itemEventHub, nullptr);
    RunMeasureAndLayout(frameNode);

    /**
     * @tc.steps: step3. Run GetDragExtraParams func.
     * @tc.expected: Verify return value.
     */
    auto jsonStr = itemEventHub->GetDragExtraParams("", Point(0, 0), DragEventType::ENTER);
    EXPECT_NE(jsonStr, "");
    jsonStr = itemEventHub->GetDragExtraParams("info", Point(0, 0), DragEventType::START);
    EXPECT_NE(jsonStr, "");
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2 RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2 RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    constexpr size_t EXPECT_ITEM_COUNT1 = 16;
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. RunMeasureAndLayout and check ListItem position.
     */
    RunMeasureAndLayout(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    EXPECT_NE(pattern, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
    EXPECT_NE(frameNode, nullptr);
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
} // namespace OHOS::Ace::NG
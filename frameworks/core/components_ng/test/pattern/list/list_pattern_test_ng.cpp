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
#define private public
#define protected public

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/list/list_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INITIAL_INDEX_VALUE = 0;
constexpr int32_t CACHED_COUNT_VALUE = 10;
constexpr int32_t LIST_ITEM_NUMBER = 10;
constexpr int32_t START_INDEX = 0;
constexpr int32_t END_INDEX = 10;
constexpr int32_t LANES_VALUE = 3;
constexpr int32_t LANES_CONSTRAINT_CASE1_VALUE = 1;
constexpr int32_t LANES_CONSTRAINT_CASE2_VALUE = 2;
constexpr int32_t JUMP_INDEX = 5;
constexpr int32_t JUMP_INDEX_SPECIAL_CASE1 = -2;
constexpr int32_t JUMP_INDEX_SPECIAL_CASE2 = 100;
constexpr float LIST_ITEM_WIDTH = 10.0f;
constexpr float LIST_ITEM_HEIGHT = 30.0f;
constexpr float LIST_WIDTH_CONSTRAINT_CASE1_VALUE = 70.0f;
constexpr float LIST_WIDTH_CONSTRAINT_CASE2_VALUE = 60.0f;
constexpr float LIST_HEIGHT_LIMIT = 200.0f;
constexpr float LIST_ITEM_GROUP_HEAD_VALUE = 50.0f;
constexpr float LIST_ITEM_GROUP_FOOT_VALUE = 50.0f;
constexpr float CROSS_SIZE_CASE = 100.0f;
constexpr float CHILD_CROSS_SIZE_CASE1 = 100.0f;
constexpr float CHILD_CROSS_SIZE_CASE2 = 80.0f;
constexpr float MAX_LANE_LENGTH_CASE1 = 3.0f;
constexpr float MAX_LANE_LENGTH_CASE2 = 9.9f;
constexpr float MIN_LANE_LENGTH_CASE = 0.1f;
constexpr Dimension SPACE_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension LANE_MIN_LENGTH_CASE1_VALUE = Dimension(40, DimensionUnit::PX);
constexpr Dimension LANE_MAX_LENGTH_CASE1_VALUE = Dimension(60, DimensionUnit::PX);
constexpr Dimension LANE_MIN_LENGTH_CASE2_VALUE = Dimension(30, DimensionUnit::PX);
constexpr Dimension LANE_MAX_LENGTH_CASE2_VALUE = Dimension(40, DimensionUnit::PX);
constexpr Dimension DIVIDER_STROKE_WIDTH_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension DIVIDER_START_MARGIN_VALUE = Dimension(0, DimensionUnit::PX);
constexpr Dimension DIVIDER_END_MARGIN_VALUE = Dimension(0, DimensionUnit::PX);
constexpr Color DIVIDER_COLOR_VALUE = Color(0x000000);
constexpr Axis LIST_DIRECTION_CASE1_VALUE = Axis::VERTICAL;
constexpr Axis LIST_DIRECTION_CASE2_VALUE = Axis::HORIZONTAL;
constexpr EdgeEffect EDGE_EFFECT_VALUE = EdgeEffect::NONE;
constexpr V2::ListItemAlign LIST_ITEM_ALIGN_VALUE = V2::ListItemAlign::CENTER;
} // namespace

struct TestProperty {
    std::optional<Dimension> spaceValue = std::nullopt;
    std::optional<int32_t> initialIndexValue = std::nullopt;
    std::optional<RefPtr<ScrollControllerBase>> scrollControllerBasePtr = std::nullopt;
    std::optional<RefPtr<ScrollBarProxy>> scrollBarProxyPtr = std::nullopt;
    std::optional<Axis> listDirectionValue = std::nullopt;
    std::optional<EdgeEffect> edgeEffectValue = std::nullopt;
    std::optional<V2::ItemDivider> dividerValue = std::nullopt;
    std::optional<int32_t> lanesValue = std::nullopt;
    std::optional<Dimension> laneMinLengthValue = std::nullopt;
    std::optional<Dimension> laneMaxlengthValue = std::nullopt;
    std::optional<V2::ListItemAlign> listItemAlignValue = std::nullopt;
    std::optional<int32_t> cachedCountValue = std::nullopt;
};

struct ListItemGroupTestProperty {
    std::optional<Dimension> spaceValue = std::nullopt;
    std::optional<V2::ItemDivider> itemDividerValue = std::nullopt;
};

class ListPatternTestNg : public testing::Test {
public:
    static RefPtr<FrameNode> CreateListParagraph(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateListItemGroupParagraph(
        const ListItemGroupTestProperty& listItemGroupTestProperty);
};

RefPtr<FrameNode> ListPatternTestNg::CreateListParagraph(const TestProperty& testProperty)
{
    ListModelNG listModelNG;
    listModelNG.Create();
    if (testProperty.spaceValue.has_value()) {
        listModelNG.SetSpace(testProperty.spaceValue.value());
    }
    if (testProperty.initialIndexValue.has_value()) {
        listModelNG.SetInitialIndex(testProperty.initialIndexValue.value());
    }
    if (testProperty.scrollControllerBasePtr.has_value() &&
        testProperty.scrollBarProxyPtr.has_value()) {
            listModelNG.SetScroller(testProperty.scrollControllerBasePtr.value(),
                testProperty.scrollBarProxyPtr.value());
    }
    if (testProperty.listDirectionValue.has_value()) {
        listModelNG.SetListDirection(testProperty.listDirectionValue.value());
    }
    if (testProperty.edgeEffectValue.has_value()) {
        listModelNG.SetEdgeEffect(testProperty.edgeEffectValue.value());
    }
    if (testProperty.dividerValue.has_value()) {
        listModelNG.SetDivider(testProperty.dividerValue.value());
    }
    if (testProperty.lanesValue.has_value()) {
        listModelNG.SetLanes(testProperty.lanesValue.value());
    }
    if (testProperty.laneMinLengthValue.has_value()) {
        listModelNG.SetLaneMinLength(testProperty.laneMinLengthValue.value());
    }
    if (testProperty.laneMaxlengthValue.has_value()) {
        listModelNG.SetLaneMaxLength(testProperty.laneMaxlengthValue.value());
    }
    if (testProperty.listItemAlignValue.has_value()) {
        listModelNG.SetListItemAlign(testProperty.listItemAlignValue.value());
    }
    if (testProperty.cachedCountValue.has_value()) {
        listModelNG.SetCachedCount(testProperty.cachedCountValue.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> ListPatternTestNg::CreateListItemGroupParagraph(
    const ListItemGroupTestProperty& listItemGroupTestProperty)
{
    ListItemGroupModelNG listItemGroupModelNG;
    listItemGroupModelNG.Create();

    if (listItemGroupTestProperty.spaceValue.has_value()) {
        listItemGroupModelNG.SetSpace(listItemGroupTestProperty.spaceValue.value());
    }
    if (listItemGroupTestProperty.itemDividerValue.has_value()) {
        listItemGroupModelNG.SetDivider(listItemGroupTestProperty.itemDividerValue.value());
    }
    
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: ListTest001
 * @tc.desc: Test all the properties of list.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.spaceValue = std::make_optional(SPACE_VALUE);
    testProperty.initialIndexValue = std::make_optional(INITIAL_INDEX_VALUE);
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.edgeEffectValue = std::make_optional(EDGE_EFFECT_VALUE);
    testProperty.lanesValue = std::make_optional(LANES_VALUE);
    testProperty.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE1_VALUE);
    testProperty.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE1_VALUE);
    testProperty.listItemAlignValue = std::make_optional(LIST_ITEM_ALIGN_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = DIVIDER_STROKE_WIDTH_VALUE;
    itemDivider.startMargin = DIVIDER_START_MARGIN_VALUE;
    itemDivider.endMargin = DIVIDER_END_MARGIN_VALUE;
    itemDivider.color = DIVIDER_COLOR_VALUE;
    testProperty.dividerValue = std::make_optional(itemDivider);

    /**
     * @tc.steps: step2. create list frameNode and get listLayoutProperty.
     * @tc.expected: step2. get listLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutProperty);
    EXPECT_NE(listLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. compare list properties and expected value.
     * @tc.expected: step3. list properties equals expected value.
     */
    EXPECT_EQ(listLayoutProperty->GetSpace().value(), SPACE_VALUE);
    EXPECT_EQ(listLayoutProperty->GetInitialIndex().value(), INITIAL_INDEX_VALUE);
    EXPECT_EQ(listLayoutProperty->GetListDirection().value(), LIST_DIRECTION_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetEdgeEffect().value(), EDGE_EFFECT_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLanes().value(), LANES_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLaneMinLength().value(), LANE_MIN_LENGTH_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLaneMaxLength().value(), LANE_MAX_LENGTH_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetListItemAlign().value(), LIST_ITEM_ALIGN_VALUE);
    EXPECT_EQ(listLayoutProperty->GetCachedCount().value(), CACHED_COUNT_VALUE);
    EXPECT_EQ(listLayoutProperty->GetDivider().value().strokeWidth, DIVIDER_STROKE_WIDTH_VALUE);
    EXPECT_EQ(listLayoutProperty->GetDivider().value().startMargin, DIVIDER_START_MARGIN_VALUE);
    EXPECT_EQ(listLayoutProperty->GetDivider().value().endMargin, DIVIDER_END_MARGIN_VALUE);
    EXPECT_EQ(listLayoutProperty->GetDivider().value().color, DIVIDER_COLOR_VALUE);
}

/**
 * @tc.name: ListTest002
 * @tc.desc: Test list measure and layout function, set space initialIndex direction cachedCount.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.spaceValue = std::make_optional(SPACE_VALUE);
    testProperty.initialIndexValue = std::make_optional(INITIAL_INDEX_VALUE);
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos,
            (index - INITIAL_INDEX_VALUE) * (SPACE_VALUE.Value() + LIST_ITEM_HEIGHT));
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].endPos,
            (index - INITIAL_INDEX_VALUE) * (SPACE_VALUE.Value() + LIST_ITEM_HEIGHT) + LIST_ITEM_HEIGHT);
    }
    
    listLayoutAlgorithm.Layout(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto frameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(frameOffset.GetX(), 0);
        EXPECT_EQ(frameOffset.GetY(), (index - INITIAL_INDEX_VALUE) * (SPACE_VALUE.Value() + LIST_ITEM_HEIGHT));
    }
}

/**
 * @tc.name: ListTest003
 * @tc.desc: Test list measure and layout function, set direction lanes listItemAlign.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.lanesValue = std::make_optional(LANES_VALUE);

    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    OptionalSizeF idealSize = OptionalSizeF(LIST_ITEM_WIDTH * LANES_VALUE,
        LIST_ITEM_HEIGHT * LIST_ITEM_NUMBER);
    layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(idealSize);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLanesLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    listLayoutAlgorithm.Measure(&layoutWrapper);
    listLayoutAlgorithm.Layout(&layoutWrapper);

    EXPECT_EQ(LANES_VALUE, listLayoutAlgorithm.GetLanes());
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto frameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(frameOffset.GetX(), (index % LANES_VALUE) * LIST_ITEM_WIDTH);
        EXPECT_EQ(frameOffset.GetY(), (index / LANES_VALUE) * LIST_ITEM_HEIGHT);
    }
}

/**
 * @tc.name: ListTest004
 * @tc.desc: Test list measure and layout function, set direction laneConstraint{laneMinLength, laneMaxLength} case1.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE1_VALUE);
    testProperty.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE1_VALUE);

    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    OptionalSizeF idealSize = OptionalSizeF(LIST_WIDTH_CONSTRAINT_CASE1_VALUE,
        LIST_ITEM_HEIGHT * LIST_ITEM_NUMBER);
    layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(idealSize);
    layoutConstraint.maxSize = SizeF(LIST_WIDTH_CONSTRAINT_CASE1_VALUE,
        LIST_ITEM_HEIGHT * LIST_ITEM_NUMBER);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLanesLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    listLayoutAlgorithm.Measure(&layoutWrapper);
    listLayoutAlgorithm.Layout(&layoutWrapper);

    EXPECT_EQ(LANES_CONSTRAINT_CASE1_VALUE, listLayoutAlgorithm.GetLanes());
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto frameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(frameOffset.GetX(), (index % LANES_CONSTRAINT_CASE1_VALUE) * LANE_MAX_LENGTH_CASE1_VALUE.Value());
        EXPECT_EQ(frameOffset.GetY(), (index / LANES_CONSTRAINT_CASE1_VALUE) * LIST_ITEM_HEIGHT);
    }
}

/**
 * @tc.name: ListTest005
 * @tc.desc: Test list measure and layout function, set direction laneConstraint{laneMinLength, laneMaxLength} case2.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE2_VALUE);
    testProperty.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE2_VALUE);

    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    OptionalSizeF idealSize = OptionalSizeF(LIST_WIDTH_CONSTRAINT_CASE2_VALUE,
        LIST_ITEM_HEIGHT * LIST_ITEM_NUMBER);
    layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(idealSize);
    layoutConstraint.maxSize = SizeF(LIST_WIDTH_CONSTRAINT_CASE2_VALUE,
        LIST_ITEM_HEIGHT * LIST_ITEM_NUMBER);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLanesLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    listLayoutAlgorithm.Measure(&layoutWrapper);
    listLayoutAlgorithm.Layout(&layoutWrapper);

    EXPECT_EQ(LANES_CONSTRAINT_CASE2_VALUE, listLayoutAlgorithm.GetLanes());
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto frameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(frameOffset.GetX(), (index % LANES_CONSTRAINT_CASE2_VALUE) * LANE_MIN_LENGTH_CASE2_VALUE.Value());
        EXPECT_EQ(frameOffset.GetY(), (index / LANES_CONSTRAINT_CASE2_VALUE) * LIST_ITEM_HEIGHT);
    }
}

/**
 * @tc.name: ListTest006
 * @tc.desc: Test list measure and layout function, set direction, special direction(Axis::HORIZONTAL).
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.initialIndexValue = std::make_optional(INITIAL_INDEX_VALUE);
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE2_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos, index * LIST_ITEM_WIDTH);
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].endPos, (index + 1) * LIST_ITEM_WIDTH);
    }
    
    listLayoutAlgorithm.Layout(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childWrapper = layoutWrapper.GetOrCreateChildByIndex(index);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        EXPECT_NE(childGeometryNode, nullptr);
        auto frameOffset = childGeometryNode->GetMarginFrameOffset();
        EXPECT_EQ(frameOffset.GetX(), index * LIST_ITEM_WIDTH);
        EXPECT_EQ(frameOffset.GetY(), 0);
    }
}

/**
 * @tc.name: ListTest007
 * @tc.desc: Test list measure function, set direction, jumpIndex_ set JUMP_INDEX.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. jump to JUMP_INDEX. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = JUMP_INDEX;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    for (int32_t index = JUMP_INDEX; index < END_INDEX; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos,
            (index - JUMP_INDEX) * LIST_ITEM_HEIGHT);
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].endPos,
            (index - JUMP_INDEX + 1) * LIST_ITEM_HEIGHT);
    }
}

/**
 * @tc.name: ListTest008
 * @tc.desc: Test list measure and layout function, special case: jumpIndex < 0. List jump to top.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }
    
    /**
     * @tc.steps: step4. jump to 0. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = JUMP_INDEX_SPECIAL_CASE1;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos, index * LIST_ITEM_HEIGHT);
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].endPos, (index + 1) * LIST_ITEM_HEIGHT);
    }
}

/**
 * @tc.name: ListTest009
 * @tc.desc: Test list measure and layout function, special case: jumpIndex > listItemCount.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    OptionalSizeF idealSize = OptionalSizeF(LIST_ITEM_WIDTH, LIST_HEIGHT_LIMIT);
    layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(idealSize);
    layoutConstraint.maxSize = SizeF(LIST_ITEM_WIDTH, LIST_HEIGHT_LIMIT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    /**
     * @tc.steps: step4. jump to end and layout back. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step4. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = JUMP_INDEX_SPECIAL_CASE2;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    int32_t expected = LIST_HEIGHT_LIMIT / LIST_ITEM_HEIGHT;
    for (int32_t index = START_INDEX; index < expected; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos, LIST_ITEM_HEIGHT * index);
    }
}

/**
 * @tc.name: ListTest010
 * @tc.desc: Test list measure function, special case: list has no listItem.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    OptionalSizeF idealSize = OptionalSizeF(LIST_ITEM_WIDTH, LIST_HEIGHT_LIMIT);
    layoutConstraint.UpdateIllegalSelfIdealSizeWithCheck(idealSize);
    layoutConstraint.maxSize = SizeF(LIST_ITEM_WIDTH, LIST_HEIGHT_LIMIT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. no listItem. do listLayoutAlgorithm Measure and compare values.
     * @tc.expected: step3. layout result equals expected result.
     */
    auto listLayoutAlgorithm = ListLayoutAlgorithm();
    listLayoutAlgorithm.jumpIndex_ = 0;
    
    listLayoutAlgorithm.Measure(&layoutWrapper);
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].startPos, 0);
        EXPECT_EQ(listLayoutAlgorithm.itemPosition_[index].endPos, 0);
    }
}

/**
 * @tc.name: ListTest011
 * @tc.desc: Test list UpdateListItemConstraint function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listLayoutAlgorithm and input.
     */
    ListLayoutAlgorithm listLayoutAlgorithm;
    OptionalSizeF selfIdealSize;
    LayoutConstraintF contentConstraint;
    Axis axis;
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case1: axis is VERTICAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    axis = Axis::VERTICAL;
    listLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Width(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case2: axis is VERTICAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetWidth(LIST_ITEM_WIDTH);
    listLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Width(), LIST_ITEM_WIDTH);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case3: axis is HORIZONTAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    axis = Axis::HORIZONTAL;
    listLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Height(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case4: axis is HORIZONTAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetHeight(LIST_ITEM_HEIGHT);
    listLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Height(), LIST_ITEM_HEIGHT);
}

/**
 * @tc.name: ListTest012
 * @tc.desc: Test list CalculateEstimateOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listLayoutAlgorithm and input.
     */
    ListLayoutAlgorithm listLayoutAlgorithm;
    
    /**
     * @tc.steps: step2. call function and compare.
     * @tc.steps: case1: itemPosition is empty
     * @tc.expected: step2. estimateOffset equals 0.
     */
    listLayoutAlgorithm.CalculateEstimateOffset();
    EXPECT_EQ(listLayoutAlgorithm.estimateOffset_, 0);

    /**
     * @tc.steps: step2. create itemPosition, call function and compare.
     * @tc.steps: case2: normal case.
     * @tc.expected: step2. estimateOffset equals expected.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        ListItemInfo listItemInfo;
        listItemInfo.startPos = index * LIST_ITEM_HEIGHT;
        listItemInfo.endPos = (index + 1) * LIST_ITEM_HEIGHT;
        listItemInfo.isGroup = false;
        listLayoutAlgorithm.itemPosition_[index] = listItemInfo;
    }

    listLayoutAlgorithm.CalculateEstimateOffset();
    EXPECT_EQ(listLayoutAlgorithm.estimateOffset_, START_INDEX * LIST_ITEM_HEIGHT);
}

/**
 * @tc.name: ListTest013
 * @tc.desc: Test list CalculateLaneCrossOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLayoutAlgorithm listLayoutAlgorithm;
    
    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case1: crossSize == childCrossSize
     * @tc.expected: step2. function result equals expected result.
     */
    auto result = listLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE1);
    EXPECT_EQ(result, 0);
    
    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case2: crossSize > childCrossSize, itemAlign_ is START
     * @tc.expected: step2. function result equals expected result.
     */
    listLayoutAlgorithm.listItemAlign_ = OHOS::Ace::V2::ListItemAlign::START;
    result = listLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case3: crossSize > childCrossSize, itemAlign_ is CENTER
     * @tc.expected: step2. function result equals expected result.
     */
    constexpr float half = 0.5f;
    listLayoutAlgorithm.listItemAlign_ = OHOS::Ace::V2::ListItemAlign::CENTER;
    result = listLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, half * (CROSS_SIZE_CASE - CHILD_CROSS_SIZE_CASE2));

    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case4: crossSize > childCrossSize, itemAlign_ is END
     * @tc.expected: step2. function result equals expected result.
     */
    listLayoutAlgorithm.listItemAlign_ = OHOS::Ace::V2::ListItemAlign::END;
    result = listLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, CROSS_SIZE_CASE - CHILD_CROSS_SIZE_CASE2);
}

/**
 * @tc.name: ListTest014
 * @tc.desc: Test list CreateItemGroupList function. Only have head and foot.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);
    
    /**
     * @tc.steps: step3. add head layoutWrapper to listItemGroup frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    auto headFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
        AceType::MakeRefPtr<Pattern>());
    ViewStackProcessor::GetInstance()->Push(headFrameNode);
    RefPtr<GeometryNode> headGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    headGeometryNode->SetFrameSize(SizeF(LIST_ITEM_GROUP_HEAD_VALUE, LIST_ITEM_GROUP_HEAD_VALUE));
    RefPtr<LayoutProperty> headLayoutProperty = headFrameNode->GetLayoutProperty();
    RefPtr<LayoutWrapper> headLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        headFrameNode, headGeometryNode, headLayoutProperty);
    layoutWrapper.AppendChild(std::move(headLayoutWrapper));

    /**
     * @tc.steps: step4. add foot layoutWrapper to listItemGroup frameNode layoutWrapper.
     * @tc.expected: step4. create layoutWrapper success.
     */
    auto footFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
        AceType::MakeRefPtr<Pattern>());
    ViewStackProcessor::GetInstance()->Push(footFrameNode);
    RefPtr<GeometryNode> footGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    footGeometryNode->SetFrameSize(SizeF(LIST_ITEM_GROUP_FOOT_VALUE, LIST_ITEM_GROUP_FOOT_VALUE));
    RefPtr<LayoutProperty> footLayoutProperty = footFrameNode->GetLayoutProperty();
    RefPtr<LayoutWrapper> footLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        footFrameNode, footGeometryNode, footLayoutProperty);
    layoutWrapper.AppendChild(std::move(footLayoutWrapper));

    /**
     * @tc.steps: step5. do layoutAlgorithm Measure and compare values.
     * @tc.expected: step5. layout result equals expected result.
     */
    ListLayoutAlgorithm listLayoutAlgorithm;
    listLayoutAlgorithm.Measure(&layoutWrapper);
    listLayoutAlgorithm.itemPosition_.begin()->second.isGroup = true;
    listLayoutAlgorithm.itemPosition_.rbegin()->second.isGroup = true;
    listLayoutAlgorithm.stickyStyle_ = V2::StickyStyle::HEADER;
    listLayoutAlgorithm.CreateItemGroupList(&layoutWrapper);
    auto& itemGroupList = listLayoutAlgorithm.GetItemGroupList();
    EXPECT_NE(itemGroupList.begin()->Upgrade(), nullptr);
    EXPECT_NE(itemGroupList.rbegin()->Upgrade(), nullptr);
}

/**
 * @tc.name: ListItemGroupTest001
 * @tc.desc: Test all the properties of listItemGroup.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListItemGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listItemGroupTestProperty and set properties of listItemGroup.
     */
    ListItemGroupTestProperty listItemGroupTestProperty;
    listItemGroupTestProperty.spaceValue = std::make_optional(SPACE_VALUE);
    V2::ItemDivider itemDivider = V2::ItemDivider();
    itemDivider.strokeWidth = DIVIDER_STROKE_WIDTH_VALUE;
    itemDivider.startMargin = DIVIDER_START_MARGIN_VALUE;
    itemDivider.endMargin = DIVIDER_END_MARGIN_VALUE;
    itemDivider.color = DIVIDER_COLOR_VALUE;
    listItemGroupTestProperty.itemDividerValue = std::make_optional(itemDivider);

    /**
     * @tc.steps: step2. create listItemGroup frameNode and get listItemGroupLayoutProperty.
     * @tc.expected: step2. get listItemGroupLayoutProperty success.
     */
    RefPtr<FrameNode> frameNode = CreateListItemGroupParagraph(listItemGroupTestProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ListItemGroupLayoutProperty> listItemGroupLayoutProperty =
        AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutProperty);
    EXPECT_NE(listItemGroupLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. compare listItemGroup properties and expected value.
     * @tc.expected: step3. listItemGroups properties equals expected value.
     */
    EXPECT_EQ(listItemGroupLayoutProperty->GetSpace().value(), SPACE_VALUE);
    EXPECT_EQ(listItemGroupLayoutProperty->GetDivider().value().strokeWidth, DIVIDER_STROKE_WIDTH_VALUE);
    EXPECT_EQ(listItemGroupLayoutProperty->GetDivider().value().startMargin, DIVIDER_START_MARGIN_VALUE);
    EXPECT_EQ(listItemGroupLayoutProperty->GetDivider().value().endMargin, DIVIDER_END_MARGIN_VALUE);
    EXPECT_EQ(listItemGroupLayoutProperty->GetDivider().value().color, DIVIDER_COLOR_VALUE);
}

/**
 * @tc.name: ListItemGroupTest008
 * @tc.desc: Test listItemGroup UpdateListItemConstraint function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListItemGroupTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    auto listItemGroupLayoutAlgorithm = ListItemGroupLayoutAlgorithm(-1, -1, 0);
    OptionalSizeF selfIdealSize;
    LayoutConstraintF contentConstraint;
    listItemGroupLayoutAlgorithm.axis_ = Axis::VERTICAL;
    listItemGroupLayoutAlgorithm.lanes_ = 1;
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case1: axis is VERTICAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    listItemGroupLayoutAlgorithm.UpdateListItemConstraint(selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Width(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case2: axis is VERTICAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetWidth(LIST_ITEM_WIDTH);
    listItemGroupLayoutAlgorithm.UpdateListItemConstraint(selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Width(), LIST_ITEM_WIDTH);
    EXPECT_EQ(contentConstraint.parentIdealSize.Width(), LIST_ITEM_WIDTH);
    EXPECT_EQ(contentConstraint.maxSize.Width(), LIST_ITEM_WIDTH);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case3: axis is HORIZONTAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    listItemGroupLayoutAlgorithm.axis_ = Axis::HORIZONTAL;
    listItemGroupLayoutAlgorithm.UpdateListItemConstraint(selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Height(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case4: axis is HORIZONTAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetHeight(LIST_ITEM_HEIGHT);
    listItemGroupLayoutAlgorithm.UpdateListItemConstraint(selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Height(), LIST_ITEM_HEIGHT);
    EXPECT_EQ(contentConstraint.parentIdealSize.Height(), LIST_ITEM_HEIGHT);
    EXPECT_EQ(contentConstraint.maxSize.Height(), LIST_ITEM_HEIGHT);
}

/**
 * @tc.name: ListItemGroupTest009
 * @tc.desc: Test listItemGroup CalculateLaneCrossOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListItemGroupTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    auto listItemGroupLayoutAlgorithm = ListItemGroupLayoutAlgorithm(-1, -1, 0);
    
    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case1: crossSize == childCrossSize
     * @tc.expected: step2. function result equals expected result.
     */
    auto result = listItemGroupLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE1);
    EXPECT_EQ(result, 0);
    
    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case2: crossSize > childCrossSize, itemAlign_ is START
     * @tc.expected: step2. function result equals expected result.
     */
    listItemGroupLayoutAlgorithm.itemAlign_ = OHOS::Ace::V2::ListItemAlign::START;
    result = listItemGroupLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case3: crossSize > childCrossSize, itemAlign_ is CENTER
     * @tc.expected: step2. function result equals expected result.
     */
    constexpr float half = 0.5f;
    listItemGroupLayoutAlgorithm.itemAlign_ = OHOS::Ace::V2::ListItemAlign::CENTER;
    result = listItemGroupLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, half * (CROSS_SIZE_CASE - CHILD_CROSS_SIZE_CASE2));

    /**
     * @tc.steps: step2. call CalculateLaneCrossOffset function and compare.
     * @tc.steps: case4: crossSize > childCrossSize, itemAlign_ is END
     * @tc.expected: step2. function result equals expected result.
     */
    listItemGroupLayoutAlgorithm.itemAlign_ = OHOS::Ace::V2::ListItemAlign::END;
    result = listItemGroupLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, CROSS_SIZE_CASE - CHILD_CROSS_SIZE_CASE2);
}

/**
 * @tc.name: ListLanesTest001
 * @tc.desc: Test listLanes UpdateListItemConstraint function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLanesLayoutAlgorithm listLanesLayoutAlgorithm;
    OptionalSizeF selfIdealSize;
    LayoutConstraintF contentConstraint;
    Axis axis = Axis::VERTICAL;
    listLanesLayoutAlgorithm.lanes_ = LANES_VALUE;
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case1: axis is VERTICAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Width(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case2: axis is VERTICAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetWidth(LIST_ITEM_WIDTH);
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Width(), LIST_ITEM_WIDTH / LANES_VALUE);
    EXPECT_EQ(contentConstraint.parentIdealSize.Width(), LIST_ITEM_WIDTH / LANES_VALUE);
    EXPECT_EQ(contentConstraint.maxSize.Width(), LIST_ITEM_WIDTH / LANES_VALUE);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case3: axis is VERTICAL, selfIdealSize has value, maxLaneLength has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetWidth(LIST_ITEM_WIDTH);
    listLanesLayoutAlgorithm.maxLaneLength_ = MAX_LANE_LENGTH_CASE1;
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Width(), MAX_LANE_LENGTH_CASE1);
    EXPECT_EQ(contentConstraint.parentIdealSize.Width(), MAX_LANE_LENGTH_CASE1);
    EXPECT_EQ(contentConstraint.maxSize.Width(), MAX_LANE_LENGTH_CASE1);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case4: axis is VERTICAL, selfIdealSize has value, minLaneLength has value
     * @tc.expected: step2. contentConstraint width equals expected result.
     */
    selfIdealSize.SetWidth(LIST_ITEM_WIDTH);
    listLanesLayoutAlgorithm.minLaneLength_ = MIN_LANE_LENGTH_CASE;
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.minSize.Width(), MIN_LANE_LENGTH_CASE);
}

/**
 * @tc.name: ListLanesTest002
 * @tc.desc: Test listLanes UpdateListItemConstraint function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLanesLayoutAlgorithm listLanesLayoutAlgorithm;
    OptionalSizeF selfIdealSize;
    LayoutConstraintF contentConstraint;
    Axis axis = Axis::HORIZONTAL;
    listLanesLayoutAlgorithm.lanes_ = LANES_VALUE;
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case1: axis is HORIZONTAL, selfIdealSize has no value
     * @tc.expected: step2. contentConstraint height equals expected result.
     */
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.maxSize.Height(), Infinity<float>());
    
    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case2: axis is HORIZONTAL, selfIdealSize has value
     * @tc.expected: step2. contentConstraint Height equals expected result.
     */
    selfIdealSize.SetHeight(LIST_ITEM_HEIGHT);
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Height(), LIST_ITEM_HEIGHT / LANES_VALUE);
    EXPECT_EQ(contentConstraint.parentIdealSize.Height(), LIST_ITEM_HEIGHT / LANES_VALUE);
    EXPECT_EQ(contentConstraint.maxSize.Height(), LIST_ITEM_HEIGHT / LANES_VALUE);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case3: axis is HORIZONTAL, selfIdealSize has value, maxLaneLength has value
     * @tc.expected: step2. contentConstraint height equals expected result.
     */
    selfIdealSize.SetHeight(LIST_ITEM_HEIGHT);
    listLanesLayoutAlgorithm.maxLaneLength_ = MAX_LANE_LENGTH_CASE2;
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.percentReference.Height(), MAX_LANE_LENGTH_CASE2);
    EXPECT_EQ(contentConstraint.parentIdealSize.Height(), MAX_LANE_LENGTH_CASE2);
    EXPECT_EQ(contentConstraint.maxSize.Height(), MAX_LANE_LENGTH_CASE2);

    /**
     * @tc.steps: step2. create selfIdealSize and contentConstraintSize, call function and compare.
     * @tc.steps: case4: axis is HORIZONTAL, selfIdealSize has value, minLaneLength has value
     * @tc.expected: step2. contentConstraint Height equals expected result.
     */
    selfIdealSize.SetHeight(LIST_ITEM_HEIGHT);
    listLanesLayoutAlgorithm.minLaneLength_ = MIN_LANE_LENGTH_CASE;
    listLanesLayoutAlgorithm.UpdateListItemConstraint(axis, selfIdealSize, contentConstraint);
    EXPECT_EQ(contentConstraint.minSize.Height(), MIN_LANE_LENGTH_CASE);
}

/**
 * @tc.name: ListLanesTest003
 * @tc.desc: Test listLanes ModifyLaneLength function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call modifyLanLength function and compare.
     * @tc.steps: case1: max = min = 0
     * @tc.expected: step1. result equals expected result.
     */
    std::optional<float> minLaneLength = 0;
    std::optional<float> maxLaneLength = 0;
    ListLanesLayoutAlgorithm::ModifyLaneLength(minLaneLength, maxLaneLength, LIST_ITEM_WIDTH);
    EXPECT_EQ(minLaneLength.value(), LIST_ITEM_WIDTH);
    EXPECT_EQ(maxLaneLength.value(), LIST_ITEM_WIDTH);

    /**
     * @tc.steps: step2. call modifyLanLength function and compare.
     * @tc.steps: case2: max = 1, min = 0
     * @tc.expected: step2. result equals expected result.
     */
    maxLaneLength = 1;
    minLaneLength = LIST_ITEM_WIDTH;
    ListLanesLayoutAlgorithm::ModifyLaneLength(minLaneLength, maxLaneLength, LIST_ITEM_WIDTH);
    EXPECT_EQ(maxLaneLength.value(), LIST_ITEM_WIDTH);
    EXPECT_EQ(minLaneLength.value(), LIST_ITEM_WIDTH);
}

/**
 * @tc.name: ListLanesTest004
 * @tc.desc: Test listLanes CalculateLaneCrossOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLanesLayoutAlgorithm listLanesLayoutAlgorithm;
    
    /**
     * @tc.steps: step2. call calculateLaneCrossOffset function and compare.
     * @tc.steps: case1: special case, lanes_ <= 0
     * @tc.expected: step2. result equals expected result.
     */
    listLanesLayoutAlgorithm.lanes_ = 0;
    auto result = listLanesLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE2);
    EXPECT_EQ(result, 0);

    /**
     * @tc.steps: step2. call calculateLaneCrossOffset function and compare.
     * @tc.steps: case2: normal case, lanes_ > 0
     * @tc.expected: step2. result equals expected result.
     */
    listLanesLayoutAlgorithm.lanes_ = LANES_VALUE;
    result = listLanesLayoutAlgorithm.CalculateLaneCrossOffset(
        CROSS_SIZE_CASE, CHILD_CROSS_SIZE_CASE1);
    EXPECT_EQ(result, (CROSS_SIZE_CASE - CHILD_CROSS_SIZE_CASE1) / LANES_VALUE);
}

/**
 * @tc.name: ListLanesTest005
 * @tc.desc: Test listLanes LayoutALineBackward function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLanesLayoutAlgorithm listLanesLayoutAlgorithm;

    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }
}

/**
 * @tc.name: ListLanesTest006
 * @tc.desc: Test listLanes FindLanesStartIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListLanesTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutAlgorithm.
     * @tc.expected: step1. getLayoutAlgorithm.
     */
    ListLanesLayoutAlgorithm listLanesLayoutAlgorithm;

    /**
     * @tc.steps: step1. create testProperty and set properties of list.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and layoutWrapper.
     * @tc.expected: step2. create layoutWrapper success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. add listItem layoutWrapper to list frameNode layoutWrapper.
     * @tc.expected: step3. create layoutWrapper success.
     */
    for (int32_t index = START_INDEX; index < END_INDEX; index++) {
        auto childFrameNode = FrameNode::CreateFrameNode(LIST_ITEM_TYPE, 0,
            AceType::MakeRefPtr<Pattern>());
        EXPECT_NE(childFrameNode, nullptr);
        ViewStackProcessor::GetInstance()->Push(childFrameNode);
        RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_NE(childGeometryNode, nullptr);
        childGeometryNode->SetFrameSize(SizeF(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT));
        RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
        EXPECT_NE(childLayoutProperty, nullptr);
        RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
            childFrameNode, childGeometryNode, childLayoutProperty);
        layoutWrapper.AppendChild(std::move(childLayoutWrapper));
    }

    listLanesLayoutAlgorithm.lanes_ = 1;
    auto result = listLanesLayoutAlgorithm.FindLanesStartIndex(&layoutWrapper, END_INDEX);
    EXPECT_EQ(result, 0);

    listLanesLayoutAlgorithm.lanes_ = LANES_VALUE;
    result = listLanesLayoutAlgorithm.FindLanesStartIndex(&layoutWrapper, START_INDEX);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: ListEvent001
 * @tc.desc: Test list eventHub function. ListEventHub getDirection.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.expected: step2. create eventHub success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto listEventHub = AceType::DynamicCast<ListEventHub>(eventHub);
    EXPECT_NE(listEventHub, nullptr);

    /**
     * @tc.steps: step3. compare function result and expected result.
     * @tc.expected: step3. function result equals expected result.
     */
    EXPECT_EQ(listEventHub->GetDirection(), LIST_DIRECTION_CASE1_VALUE);
}

/**
 * @tc.name: ListEvent002
 * @tc.desc: Test list eventHub function. ListEventHub::InitItemDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.expected: step2. create eventHub success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto listEventHub = AceType::DynamicCast<ListEventHub>(eventHub);
    EXPECT_NE(listEventHub, nullptr);

    /**
     * @tc.steps: step3. call ListEventHub::InitItemDragEvent function and test result.
     * @tc.expected: step3. call function success and result equals expected.
     */
    RefPtr<GestureEventHub> gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    listEventHub->InitItemDragEvent(gestureEventHub);
    EXPECT_NE(gestureEventHub->dragEventActuator_, nullptr);
}

/**
 * @tc.name: ListEvent003
 * @tc.desc: Test list eventHub function. Functions have:
 * @tc.desc: HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd, HandleOnItemDragCancel.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.expected: step2. create eventHub success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto listEventHub = AceType::DynamicCast<ListEventHub>(eventHub);
    EXPECT_NE(listEventHub, nullptr);

    /**
     * @tc.steps: step3. call HandleOnItemDragStart and Update function and test result. Get draggedIndex.
     * @tc.expected: step3. call function success and result equals expected.
     */
    GestureEvent gestureEvent = GestureEvent();
    listEventHub->HandleOnItemDragStart(gestureEvent);
    listEventHub->HandleOnItemDragUpdate(gestureEvent);
    EXPECT_EQ(listEventHub->draggedIndex_, 0);

    /**
     * @tc.steps: step4. call HandleOnItemDragEnd function and test result. Delete dragDropProxy.
     * @tc.expected: step4. call function success and result equals expected.
     */
    listEventHub->HandleOnItemDragEnd(gestureEvent);
    EXPECT_EQ(listEventHub->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step5. call HandleOnItemDragStart and Cancel function.
     * @tc.expected: step5. call function success and result equals expected.
     */
    listEventHub->HandleOnItemDragStart(gestureEvent);
    listEventHub->HandleOnItemDragCancel();
    EXPECT_EQ(listEventHub->dragDropProxy_, nullptr);
}

/**
 * @tc.name: ListEvent004
 * @tc.desc: Test list eventHub function. Functions have:
 * @tc.desc: HandleOnItemDragStart, HandleOnItemDragUpdate, HandleOnItemDragEnd, HandleOnItemDragCancel.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.expected: step2. create eventHub success.
     */
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto listEventHub = AceType::DynamicCast<ListEventHub>(eventHub);
    EXPECT_NE(listEventHub, nullptr);

    /**
     * @tc.steps: step3. call HandleOnItemDragStart and Update function and test result. Get draggedIndex.
     * @tc.expected: step3. call function success and result equals expected.
     */
    GestureEvent gestureEvent = GestureEvent();
    listEventHub->HandleOnItemDragStart(gestureEvent);
    listEventHub->HandleOnItemDragUpdate(gestureEvent);
    EXPECT_EQ(listEventHub->draggedIndex_, 0);

    /**
     * @tc.steps: step4. call HandleOnItemDragEnd function and test result. Delete dragDropProxy.
     * @tc.expected: step4. call function success and result equals expected.
     */
    listEventHub->HandleOnItemDragEnd(gestureEvent);
    EXPECT_EQ(listEventHub->dragDropProxy_, nullptr);

    /**
     * @tc.steps: step5. call HandleOnItemDragStart and Cancel function.
     * @tc.expected: step5. call function success and result equals expected.
     */
    listEventHub->HandleOnItemDragStart(gestureEvent);
    listEventHub->HandleOnItemDragCancel();
    EXPECT_EQ(listEventHub->dragDropProxy_, nullptr);
}

/**
 * @tc.name: ListPatternTest001
 * @tc.desc: Test list pattern OnModifyDone function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    auto hub = frameNode->GetEventHub<EventHub>();
    EXPECT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case1: !isInitialized_, !scrollableEvent_, !scrollEffect_
     * @tc.expected: step2. equal.
     */
    listPattern->isInitialized_ = false;
    listPattern->scrollableEvent_ = nullptr;
    listPattern->scrollEffect_ = nullptr;
    listPattern->OnModifyDone();
    EXPECT_NE(listPattern->scrollableEvent_, nullptr);

    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case2: axis not same
     * @tc.expected: step2. equal.
     */
    listPattern->scrollableEvent_->axis_ = Axis::NONE;
    listPattern->axis_ = Axis::NONE;
    listPattern->OnModifyDone();
    EXPECT_EQ(listPattern->scrollableEvent_->axis_, Axis::VERTICAL);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case3: axis same, !scrollEffect_
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = nullptr;
    listPattern->OnModifyDone();
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case3: axis same, scrollEffect_, scrollEffect = NONE
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    listPattern->OnModifyDone();
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case4: axis same, scrollEffect_, scrollEffect = SPRING
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    listPattern->OnModifyDone();
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
}

/**
 * @tc.name: ListPatternTest002
 * @tc.desc: Test list pattern OnModifyDone function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case5: edgeEffect NONE, !scrollEffect
     * @tc.expected: step2. equal.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.edgeEffectValue = std::make_optional(EDGE_EFFECT_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);

    listPattern->scrollEffect_ = nullptr;
    listPattern->OnModifyDone();
    EXPECT_EQ(listPattern->scrollEffect_, nullptr);
    
    /**
     * @tc.steps: step2. create list frameNode and eventHub.
     * @tc.steps: case6: edgeEffect NONE, scrollEffect
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE);
    listPattern->OnModifyDone();
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
}

/**
 * @tc.name: ListPatternTest003
 * @tc.desc: Test list pattern OnDirtyLayoutWrapperSwap function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<LayoutAlgorithm> layoutAlgorithm = layoutWrapper->GetLayoutAlgorithm();
    layoutWrapper->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);
    DirtySwapConfig config;
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    bool result = false;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: config.skipMeasure && config.skipLayout, return
     * @tc.expected: step2. equal.
     */
    config.skipMeasure = true;
    config.skipLayout = true;
    result = listPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: config.skipMeasure, !config.skipLayout, !jumpIndex_
     * @tc.expected: step2. equal.
     */
    config.skipMeasure = true;
    config.skipLayout = false;
    result = listPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: !config.skipMeasure, config.skipLayout, jumpIndex_, itemPosition empty
     * @tc.expected: step2. equal.
     */
    config.skipMeasure = false;
    config.skipLayout = true;
    listPattern->jumpIndex_ = JUMP_INDEX;
    listPattern->itemPosition_.clear();
    result = listPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: !config.skipMeasure, !config.skipLayout, jumpIndex_, itemPosition not empty
     * @tc.expected: step2. equal.
     */
    config.skipMeasure = false;
    config.skipLayout = false;
    listPattern->jumpIndex_ = JUMP_INDEX;
    listPattern->itemPosition_.clear();
    ListItemInfo listItemInfo;
    listPattern->itemPosition_[0] = listItemInfo;
    result = listPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ListPatternTest004
 * @tc.desc: Test list pattern ProcessEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    auto listEventHub = frameNode->GetEventHub<ListEventHub>();

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: !onScroll, finalOffset!=0; !indexChanged,
     * @tc.steps: !onReachStart, startIndex!=0; !onReachEnd, endIndex!=max; !scrollStop, !onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->ProcessEvent(false, 1, false, 0, 0);
    EXPECT_EQ(listPattern->scrollStop_, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: !onScroll, finalOffset=0; indexChanged, !onScrollIndex,
     * @tc.steps: !onReachStart, startIndex=0; !onReachEnd, endIndex=max; scrollStop, !onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->startIndex_ = 0;
    listPattern->endIndex_ = listPattern->maxListItemIndex_;
    listPattern->scrollStop_ = true;
    listPattern->ProcessEvent(true, 0, false, 0, 0);
    EXPECT_EQ(listPattern->scrollStop_, false);
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: onScroll, finalOffset!=0; indexChanged, onScrollIndex,
     * @tc.steps: onReachStart, startIndex!=0; onReachEnd, endIndex!=max; scrollStop, !onScrollStop
     * @tc.expected: step2. equal.
     */
    listEventHub->SetOnScroll([](Dimension, ScrollState) {});
    listEventHub->SetOnScrollIndex([](int32_t, int32_t) {});
    listEventHub->SetOnReachStart([]() {});
    listPattern->startIndex_ = 1;
    listEventHub->SetOnReachEnd([]() {});
    listPattern->endIndex_ = listPattern->maxListItemIndex_ - 1;
    listPattern->scrollStop_ = true;
    listPattern->ProcessEvent(true, 1, false, 0, 0);
    EXPECT_EQ(listPattern->scrollStop_, false);
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: onScroll, finalOffset=0, SCROLL_FROM_UPDATE
     * @tc.steps: onReachStart, startIndex=0; onReachEnd, endIndex=max; scrollStop, onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->scrollState_ = SCROLL_FROM_UPDATE;
    listPattern->startIndex_ = 0;
    listPattern->endIndex_ = listPattern->maxListItemIndex_;
    listEventHub->SetOnScrollStop([]() {});
    listPattern->ProcessEvent(true, 0, false, 0, 0);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case5: onScroll, finalOffset=0, SCROLL_FROM_ANIMATION
     * @tc.steps: onReachStart, startIndex=0; onReachEnd, endIndex=max; scrollStop, onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->scrollState_ = SCROLL_FROM_ANIMATION;
    listPattern->ProcessEvent(true, 0, false, 0, 0);
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case6: onScroll, finalOffset=0, SCROLL_FROM_ANIMATION_SPRING
     * @tc.steps: onReachStart, startIndex=0; onReachEnd, endIndex=max; scrollStop, onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->scrollState_ = SCROLL_FROM_ANIMATION_SPRING;
    listPattern->ProcessEvent(true, 0, false, 0, 0);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case7: onScroll, finalOffset=0, SCROLL_FROM_BAR
     * @tc.steps: onReachStart, startIndex=0; onReachEnd, endIndex=max; scrollStop, onScrollStop
     * @tc.expected: step2. equal.
     */
    listPattern->scrollState_ = SCROLL_FROM_BAR;
    listPattern->ProcessEvent(true, 0, false, 0, 0);
}

/**
 * @tc.name: ListPatternTest005
 * @tc.desc: Test list pattern CheckScrollable function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    ListItemInfo listItemInfo;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: itemPosition.empty
     * @tc.expected: step2. equal.
     */
    listPattern->CheckScrollable();
    EXPECT_EQ(listPattern->scrollable_, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: itemPosition not empty, begin!= 0, rbegin != max
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[1] = listItemInfo;
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->CheckScrollable();
    EXPECT_EQ(listPattern->scrollable_, true);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: itemPosition not empty, begin!= 0, rbegin = max
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[LIST_ITEM_NUMBER] = listItemInfo;
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->CheckScrollable();
    EXPECT_EQ(listPattern->scrollable_, true);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: itemPosition not empty, begin= 0, rbegin != max
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[0] = listItemInfo;
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->CheckScrollable();
    EXPECT_EQ(listPattern->scrollable_, true);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: itemPosition not empty, first = 0, rbegin = max
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[0] = listItemInfo;
    listPattern->itemPosition_[LIST_ITEM_NUMBER] = listItemInfo;
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->CheckScrollable();
    EXPECT_EQ(listPattern->scrollable_, false);
}

/**
 * @tc.name: ListPatternTest006
 * @tc.desc: Test list pattern CreateLayoutAlgorithm function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    RefPtr<LayoutAlgorithm> result;
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: no lanes, no LaneMin, no LaneMax, no jumpIndex_, not outOfBoundary
     * @tc.expected: step2. equal.
     */
    result = listPattern->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: no lanes, no LaneMin, no LaneMax, have jumpIndex_, is outOfBoundary
     * @tc.expected: step2. equal.
     */
    listPattern->jumpIndex_ = INITIAL_INDEX_VALUE;
    listPattern->startMainPos_ = 1;
    result = listPattern->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: have lanes, laneMinLength, laneMaxLength
     * @tc.expected: step2. equal.
     */
    TestProperty testProperty1;
    testProperty1.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty1.lanesValue = std::make_optional(LANES_VALUE);
    testProperty1.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE1_VALUE);
    testProperty1.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode1 = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<ListPattern> listPattern1 = AceType::DynamicCast<ListPattern>(frameNode1->GetPattern());
    EXPECT_NE(listPattern1, nullptr);
}

/**
 * @tc.name: ListPatternTest007
 * @tc.desc: Test list pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    bool result;
    
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case1: no scrollEffect, !isScrollContent
     * @tc.expected: step2. equal.
     */
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case2: no scrollEffect, isScrollContent
     * @tc.expected: step2. equal.
     */
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_BAR);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case3: scrollEffect not Spring, !isScrollContent
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::FADE);
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: scrollEffect Spring, !isScrollContent
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: scrollEffect Spring, isScrollContent
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_BAR);
    EXPECT_NE(result, false);
}

/**
 * @tc.name: ListPatternTest008
 * @tc.desc: Test list pattern UpdateCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    bool result;

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case4: scrollEffect Spring, isScrollContent, no header, no footer, UPDATE
     * @tc.expected: step2. equal.
     */
    listPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::SPRING);
    listPattern->scrollState_ = SCROLL_FROM_UPDATE;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case5: have header, have footer, !UPDATE
     * @tc.expected: step2. equal.
     */
    WeakPtr<FrameNode> weak = AceType::WeakClaim(AceType::RawPtr(frameNode));
    listPattern->itemGroupList_.push_back(weak);
    listPattern->scrollState_ = SCROLL_FROM_BAR;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_BAR);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case6: begin is 0, startPos > 0
     * @tc.expected: step2. equal.
     */
    ListItemInfo listItemInfo;
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[0] = listItemInfo;
    listPattern->startMainPos_ = 1;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case7: begin is not 0, startPos > 0
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[1] = listItemInfo;
    listPattern->startMainPos_ = 1;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case7: begin is 0, startPos = 0
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[0] = listItemInfo;
    listPattern->startMainPos_ = 0;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function
     * @tc.steps: case7: begin is not 0, startPos = 0
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[1] = listItemInfo;
    listPattern->startMainPos_ = 0;
    result = listPattern->UpdateCurrentOffset(0, SCROLL_FROM_UPDATE);
    EXPECT_NE(result, false);
}

/**
 * @tc.name: ListPatternTest009
 * @tc.desc: Test list pattern IsOutOfBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    bool result;

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: itemPosition is empty
     * @tc.expected: step2. equal.
     */
    result = listPattern->IsOutOfBoundary(0);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case5: have header, have footer, !UPDATE
     * @tc.expected: step2. equal.
     */
    ListItemInfo listItemInfo;
    listPattern->itemPosition_[0] = listItemInfo;
    result = listPattern->IsOutOfBoundary(0);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ListPatternTest010
 * @tc.desc: Test list pattern SetEdgeEffect function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: EdgeEffect is NONE
     * @tc.expected: step2. scrollEffect_ is nullptr.
     */
    listPattern->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_EQ(listPattern->scrollEffect_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: have scrollEffect, FADE
     * @tc.expected: step2. EdgeEffect is Fade.
     */
    listPattern->SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
    EXPECT_EQ(listPattern->scrollEffect_->IsFadeEffect(), true);

    /**
     * @tc.steps: step3. call function
     * @tc.steps: case3: have scrollEffect, SPRING
     * @tc.expected: step3. EdgeEffect is Spring.
     */
    listPattern->SetEdgeEffect(EdgeEffect::SPRING);
    EXPECT_NE(listPattern->scrollEffect_, nullptr);
    EXPECT_EQ(listPattern->scrollEffect_->IsSpringEffect(), true);

    /**
     * @tc.steps: step4. call function
     * @tc.steps: case4: have scrollEffect, FADE
     * @tc.expected: step4. IsFadeEffect is nullptr.
     */
    listPattern->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_EQ(listPattern->scrollEffect_, nullptr);
}

/**
 * @tc.name: ListPatternTest011
 * @tc.desc: Test list pattern OnKeyEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    RefPtr<ScrollEdgeEffect> scrollEffect;
    bool result = false;

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: KeyAction::DOWN
     * @tc.expected: step2. equal.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    result = listPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: KeyAction::UP
     * @tc.expected: step2. equal.
     */
    keyEvent.action = KeyAction::DOWN;
    result = listPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: KeyCode::KEY_PAGE_DOWN
     * @tc.expected: step2. equal.
     */
    keyEvent.code = KeyCode::KEY_PAGE_DOWN;
    result = listPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case4: KeyCode::KEY_DPAD_RIGHT
     * @tc.expected: step2. equal.
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    result = listPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case5: KeyCode::KEY_DPAD_CENTER
     * @tc.expected: step2. equal.
     */
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    result = listPattern->OnKeyEvent(keyEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ListPatternTest012
 * @tc.desc: Test list pattern HandleDirectionKey function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    bool result = false;

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL, KEY_DPAD_UP, next = scroll
     * @tc.expected: step2. equal.
     */
    result = listPattern->HandleDirectionKey({ KeyCode::KEY_DPAD_UP, KeyAction::DOWN });
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL, KEY_DPAD_DOWN, next = scroll
     * @tc.expected: step2. equal.
     */
    listPattern->maxListItemIndex_ = 1;
    result = listPattern->HandleDirectionKey({ KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN });
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty1;
    testProperty1.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE2_VALUE);
    
    RefPtr<FrameNode> frameNode1 = CreateListParagraph(testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<ListPattern> listPattern1 = AceType::DynamicCast<ListPattern>(frameNode1->GetPattern());
    EXPECT_NE(listPattern1, nullptr);
    listPattern1->axis_ = LIST_DIRECTION_CASE2_VALUE;
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: HORIZONTAL, KEY_DPAD_LEFT, next != scroll
     * @tc.expected: step2. equal.
     */
    result = listPattern1->HandleDirectionKey({ KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN });
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case4: HORIZONTAL, KEY_DPAD_RIGHT, next != scroll
     * @tc.expected: step2. equal.
     */
    listPattern1->maxListItemIndex_ = LIST_ITEM_NUMBER;
    result = listPattern1->HandleDirectionKey({ KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN });
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ListPatternTest013
 * @tc.desc: Test list pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: animator is nullptr
     * @tc.expected: step2. equal.
     */
    listPattern->animator_ = nullptr;
    listPattern->AnimateTo(0, 0, nullptr);
    EXPECT_NE(listPattern->animator_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: animator is STOPPED
     * @tc.expected: step2. equal.
     */
    listPattern->animator_ = AceType::MakeRefPtr<Animator>();
    listPattern->animator_->status_ = Animator::Status::STOPPED;
    listPattern->AnimateTo(0, 0, nullptr);
    EXPECT_NE(listPattern->animator_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: animator is RUNNING
     * @tc.expected: step2. equal.
     */
    listPattern->animator_ = AceType::MakeRefPtr<Animator>();
    listPattern->animator_->status_ = Animator::Status::RUNNING;
    listPattern->AnimateTo(0, 0, nullptr);
    EXPECT_NE(listPattern->animator_, nullptr);
}

/**
 * @tc.name: ListPatternTest014
 * @tc.desc: Test list pattern ScrollToIndex function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: index == -1
     * @tc.expected: step2. equal.
     */
    listPattern->ScrollToIndex(-1);
    EXPECT_EQ(listPattern->jumpIndex_, -1);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: index >= 0
     * @tc.expected: step2. equal.
     */
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->ScrollToIndex(1);
    EXPECT_EQ(listPattern->jumpIndex_, 1);
    
    /**
     * @tc.steps: step3. call function
     * @tc.steps: case3: index < -2
     * @tc.expected: step3. equal.
     */
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->ScrollToIndex(-2);
    EXPECT_NE(listPattern->jumpIndex_, -2);
}

/**
 * @tc.name: ListPatternTest015
 * @tc.desc: Test list pattern ScrollToEdge function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: ScrollEdgeType::SCROLL_TOP
     * @tc.expected: step2. equal.
     */
    listPattern->ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_EQ(listPattern->jumpIndex_, 0);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: ScrollEdgeType::SCROLL_TOP
     * @tc.expected: step2. equal.
     */
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_EQ(listPattern->jumpIndex_, -1);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: ScrollEdgeType::SCROLL_LEFT
     * @tc.expected: step2. equal.
     */
    listPattern->maxListItemIndex_ = LIST_ITEM_NUMBER;
    listPattern->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT);
    EXPECT_EQ(listPattern->jumpIndex_, -1);
}

/**
 * @tc.name: ListPatternTest016
 * @tc.desc: Test list pattern GetCurrentOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    Offset result;
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL
     * @tc.expected: step2. equal.
     */
    listPattern->estimateOffset_ = 1;
    result = listPattern->GetCurrentOffset();
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 1);

    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty1;
    testProperty1.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE2_VALUE);
    
    RefPtr<FrameNode> frameNode1 = CreateListParagraph(testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<ListPattern> listPattern1 = AceType::DynamicCast<ListPattern>(frameNode1->GetPattern());
    EXPECT_NE(listPattern1, nullptr);
    listPattern1->axis_ = LIST_DIRECTION_CASE2_VALUE;
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL
     * @tc.expected: step2. equal.
     */
    listPattern1->estimateOffset_ = 1;
    result = listPattern1->GetCurrentOffset();
    EXPECT_EQ(result.GetX(), 1);
    EXPECT_EQ(result.GetY(), 0);
}

/**
 * @tc.name: ListPatternTest017
 * @tc.desc: Test list pattern SetScrollBar function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: DisplayMode::OFF, no scrollBar, no touchEvent, !isInitialized_
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = nullptr;
    listPattern->isInitialized_ = false;
    listPattern->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(listPattern->scrollBar_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: DisplayMode::OFF, has scrollBar, has touchEvent, isInitialized_
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    listPattern->isInitialized_ = true;
    listPattern->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(listPattern->scrollBar_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: DisplayMode::ON, !scrollBar
     * @tc.expected: step2. equal.
     */
    auto listPaintProperty = frameNode->GetPaintProperty<ListPaintProperty>();
    EXPECT_NE(listPaintProperty, nullptr);
    listPaintProperty->UpdateBarDisplayMode(DisplayMode::ON);
    listPattern->scrollBar_ = nullptr;
    listPattern->SetScrollBar(DisplayMode::ON);
    EXPECT_NE(listPattern->scrollBar_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: DisplayMode::ON, scrollBar, displayMode not same
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    listPattern->scrollBar_->displayMode_ = DisplayMode::OFF;
    listPattern->SetScrollBar(DisplayMode::ON);
    EXPECT_NE(listPattern->scrollBar_, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: DisplayMode::ON, scrollBar, displayMode same
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    listPattern->scrollBar_->displayMode_ = DisplayMode::ON;
    listPattern->SetScrollBar(DisplayMode::ON);
    EXPECT_NE(listPattern->scrollBar_, nullptr);
}

/**
 * @tc.name: ListPatternTest018
 * @tc.desc: Test list pattern UpdateScrollBarOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern = AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: itemPosition is empty
     * @tc.expected: step2. equal.
     */
    listPattern->itemPosition_.clear();
    listPattern->UpdateScrollBarOffset();
    EXPECT_EQ(listPattern->itemPosition_.size(), 0);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: itemPosition not empty, !scrollBar, !scrollBarProxy
     * @tc.expected: step2. equal.
     */
    ListItemInfo listItemInfo;
    listPattern->itemPosition_.clear();
    listPattern->itemPosition_[0] = listItemInfo;
    listPattern->scrollBar_ = nullptr;
    listPattern->scrollBarProxy_ = nullptr;
    EXPECT_EQ(listPattern->itemPosition_.size(), 1);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: itemPosition not empty, scrollBar, !scrollBarProxy
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    listPattern->scrollBarProxy_ = nullptr;
    EXPECT_EQ(listPattern->itemPosition_.size(), 1);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case4: itemPosition not empty, !scrollBar, scrollBarProxy
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = nullptr;
    listPattern->scrollBarProxy_ = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_EQ(listPattern->itemPosition_.size(), 1);
    EXPECT_EQ(listPattern->barOffset_, 0);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case5: itemPosition not empty, scrollBar, scrollBarProxy
     * @tc.expected: step2. equal.
     */
    listPattern->scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
    listPattern->scrollBarProxy_ = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_EQ(listPattern->itemPosition_.size(), 1);
    EXPECT_EQ(listPattern->barOffset_, 0);
}

/**
 * @tc.name: ListPositionControllerTest001
 * @tc.desc: Test list positionController AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPositionControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(Axis::NONE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern =
        AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    listPattern->axis_ = Axis::NONE;
    RefPtr<ListPositionController> positionController =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController, nullptr);
    bool result = false;
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: !listPattern
     * @tc.expected: step2. equal.
     */
    result = positionController->AnimateTo(Dimension(0), 0, nullptr);
    EXPECT_EQ(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: listPattern, direction is NONE
     * @tc.expected: step2. equal.
     */
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern));
    result = positionController->AnimateTo(Dimension(0), 0, nullptr);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ListPositionControllerTest002
 * @tc.desc: Test list positionController AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPositionControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(Axis::VERTICAL);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern =
        AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    RefPtr<ListPositionController> positionController =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController, nullptr);
    bool result = false;
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern));
    Dimension position;
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: Unit is PERCENT, return
     * @tc.expected: step2. equal.
     */
    position = Dimension(1, DimensionUnit::PERCENT);
    result = positionController->AnimateTo(position, 0, nullptr);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    EXPECT_EQ(result, false);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case4: Unit is not PERCENT, duration = 0
     * @tc.expected: step2. equal.
     */
    position = Dimension(1, DimensionUnit::PX);
    result = positionController->AnimateTo(position, 0, nullptr);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case5: Unit is not PERCENT, duration != 0
     * @tc.expected: step2. equal.
     */
    position = Dimension(1, DimensionUnit::PX);
    result = positionController->AnimateTo(position, 1, nullptr);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ListPositionControllerTest003
 * @tc.desc: Test list positionController ScrollBy function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPositionControllerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(Axis::VERTICAL);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern =
        AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    RefPtr<ListPositionController> positionController =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController, nullptr);
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern));
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL
     * @tc.expected: step2. equal.
     */
    positionController->ScrollBy(0, 0, true);
    EXPECT_EQ(listPattern->barOffset_, 0);

    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty1;
    testProperty1.listDirectionValue = std::make_optional(Axis::HORIZONTAL);
    
    RefPtr<FrameNode> frameNode1 = CreateListParagraph(testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<ListPattern> listPattern1 =
        AceType::DynamicCast<ListPattern>(frameNode1->GetPattern());
    EXPECT_NE(listPattern1, nullptr);
    RefPtr<ListPositionController> positionController1 =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController1, nullptr);
    positionController1->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern1));
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: VERTICAL
     * @tc.expected: step2. equal.
     */
    positionController1->ScrollBy(0, 0, true);
    EXPECT_EQ(listPattern1->barOffset_, 0);
}

/**
 * @tc.name: ListPositionControllerTest004
 * @tc.desc: Test list positionController ScrollToEdge ScrollPage function
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListPositionControllerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(Axis::NONE);
    
    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<ListPattern> listPattern =
        AceType::DynamicCast<ListPattern>(frameNode->GetPattern());
    EXPECT_NE(listPattern, nullptr);
    RefPtr<ListPositionController> positionController =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController, nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case1: no listPattern
     * @tc.expected: step2. equal.
     */
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    positionController->ScrollPage(true, true);
    EXPECT_EQ(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);
    
    /**
     * @tc.steps: step2. call function
     * @tc.steps: case2: listPattern, direction is NONE
     * @tc.expected: step2. equal.
     */
    positionController->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern));
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    positionController->ScrollPage(true, true);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController->scroll_.Upgrade()), nullptr);

    /**
     * @tc.steps: step1. create listTestProperty and set properties of it.
     */
    TestProperty testProperty1;
    testProperty1.listDirectionValue = std::make_optional(Axis::VERTICAL);
    
    RefPtr<FrameNode> frameNode1 = CreateListParagraph(testProperty1);
    EXPECT_NE(frameNode1, nullptr);
    RefPtr<ListPattern> listPattern1 =
        AceType::DynamicCast<ListPattern>(frameNode1->GetPattern());
    EXPECT_NE(listPattern1, nullptr);
    RefPtr<ListPositionController> positionController1 =
        AceType::MakeRefPtr<ListPositionController>();
    EXPECT_NE(positionController1, nullptr);

    /**
     * @tc.steps: step2. call function
     * @tc.steps: case3: listPattern, direction is not NONE
     * @tc.expected: step2. equal.
     */
    positionController1->scroll_ = AceType::WeakClaim(AceType::RawPtr(listPattern1));
    positionController1->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    positionController1->ScrollPage(true, true);
    EXPECT_NE(
        AceType::DynamicCast<ListPattern>(positionController1->scroll_.Upgrade()), nullptr);
}
} // namespace OHOS::Ace::NG


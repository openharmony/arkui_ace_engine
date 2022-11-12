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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INITIAL_INDEX_VALUE = 0;
constexpr int32_t CACHED_COUNT_VALUE = 3;
constexpr int32_t LIST_ITEM_NUMBER = 10;
constexpr int32_t START_INDEX = 0;
constexpr int32_t END_INDEX = 10;
constexpr int32_t LANES_VALUE = 3;
constexpr int32_t LANES_CONSTRAINT_CASE1_VALUE = 1;
constexpr int32_t LANES_CONSTRAINT_CASE2_VALUE = 2;
constexpr int32_t JUMP_INDEX = 5;
constexpr float LIST_ITEM_WIDTH = 10.0f;
constexpr float LIST_ITEM_HEIGHT = 30.0f;
constexpr float LIST_WIDTH_CONSTRAINT_CASE1_VALUE = 70.0f;
constexpr float LIST_WIDTH_CONSTRAINT_CASE2_VALUE = 60.0f;
constexpr Dimension SPACE_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension LANE_MIN_LENGTH_CASE1_VALUE = Dimension(40, DimensionUnit::PX);
constexpr Dimension LANE_MAX_LENGTH_CASE1_VALUE = Dimension(60, DimensionUnit::PX);
constexpr Dimension LANE_MIN_LENGTH_CASE2_VALUE = Dimension(30, DimensionUnit::PX);
constexpr Dimension LANE_MAX_LENGTH_CASE2_VALUE = Dimension(40, DimensionUnit::PX);
constexpr Axis LIST_DIRECTION_CASE1_VALUE = Axis::VERTICAL;
constexpr Axis LIST_DIRECTION_CASE2_VALUE = Axis::HORIZONTAL;
constexpr EdgeEffect EDGE_EFFECT_VALUE = EdgeEffect::NONE;
constexpr V2::ListItemAlign LIST_ITEM_ALIGN_VALUE = V2::ListItemAlign::CENTER;
} // namespace

struct TestProperty {
    std::optional<Dimension> spaceValue = std::nullopt;
    std::optional<int32_t> initialIndexValue = std::nullopt;
    std::optional<Axis> listDirectionValue = std::nullopt;
    std::optional<EdgeEffect> edgeEffectValue = std::nullopt;
    std::optional<V2::ItemDivider> dividerValue = std::nullopt;
    std::optional<int32_t> lanesValue = std::nullopt;
    std::optional<Dimension> laneMinLengthValue = std::nullopt;
    std::optional<Dimension> laneMaxlengthValue = std::nullopt;
    std::optional<V2::ListItemAlign> listItemAlignValue = std::nullopt;
    std::optional<int32_t> cachedCountValue = std::nullopt;
};

class ListPatternTestNg : public testing::Test {
public:
    static RefPtr<FrameNode> CreateListParagraph(const TestProperty& testProperty);
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

/**
 * @tc.name: ListFrameNodeCreator001
 * @tc.desc: Test all the properties of list.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator001, TestSize.Level1)
{
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

    RefPtr<FrameNode> frameNode = CreateListParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::DynamicCast<ListLayoutProperty>(layoutProperty);
    EXPECT_NE(listLayoutProperty, nullptr);

    EXPECT_EQ(listLayoutProperty->GetSpace().value(), SPACE_VALUE);
    EXPECT_EQ(listLayoutProperty->GetInitialIndex().value(), INITIAL_INDEX_VALUE);
    EXPECT_EQ(listLayoutProperty->GetListDirection().value(), LIST_DIRECTION_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetEdgeEffect().value(), EDGE_EFFECT_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLanes().value(), LANES_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLaneMinLength().value(), LANE_MIN_LENGTH_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetLaneMaxLength().value(), LANE_MAX_LENGTH_CASE1_VALUE);
    EXPECT_EQ(listLayoutProperty->GetListItemAlign().value(), LIST_ITEM_ALIGN_VALUE);
    EXPECT_EQ(listLayoutProperty->GetCachedCount().value(), CACHED_COUNT_VALUE);
}

/**
 * @tc.name: ListFrameNodeCreator002
 * @tc.desc: Test list measure and layout function, set space initialIndex direction cachedCount.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.spaceValue = std::make_optional(SPACE_VALUE);
    testProperty.initialIndexValue = std::make_optional(INITIAL_INDEX_VALUE);
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.cachedCountValue = std::make_optional(CACHED_COUNT_VALUE);
    
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
 * @tc.name: ListFrameNodeCreator003
 * @tc.desc: Test list measure and layout function, set direction lanes listItemAlign.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator003, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.lanesValue = std::make_optional(LANES_VALUE);

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
 * @tc.name: ListFrameNodeCreator004
 * @tc.desc: Test list measure and layout function, set direction laneConstraint{laneMinLength, laneMaxLength} case1.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator004, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE1_VALUE);
    testProperty.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE1_VALUE);

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
 * @tc.name: ListFrameNodeCreator005
 * @tc.desc: Test list measure and layout function, set direction laneConstraint{laneMinLength, laneMaxLength} case2.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator005, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    testProperty.laneMinLengthValue = std::make_optional(LANE_MIN_LENGTH_CASE2_VALUE);
    testProperty.laneMaxlengthValue = std::make_optional(LANE_MAX_LENGTH_CASE2_VALUE);

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
 * @tc.name: ListFrameNodeCreator006
 * @tc.desc: Test list measure and layout function, set direction, special direction(Axis::HORIZONTAL).
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator006, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.initialIndexValue = std::make_optional(INITIAL_INDEX_VALUE);
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE2_VALUE);
    
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
 * @tc.name: ListFrameNodeCreator007
 * @tc.desc: Test list measure function, set direction, jumpIndex_ set JUMP_INDEX.
 * @tc.type: FUNC
 */
HWTEST_F(ListPatternTestNg, ListFrameNodeCreator007, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.listDirectionValue = std::make_optional(LIST_DIRECTION_CASE1_VALUE);
    
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
} // namespace OHOS::Ace::NG

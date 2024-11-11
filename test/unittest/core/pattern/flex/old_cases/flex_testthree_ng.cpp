/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"

#define private public
#define protectd public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/flex/flex_model_ng.h"
#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const int START_INDEX = 0;
const int THREE_ITEM_SIZE = 3;
const int DISPLAYPRIORITY_TWO = 2;
const float HALF = 0.5f;

const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const float ZERO = 0.0f;
const float LAYOUT_WEIGHT_ONE = 1.0f;

const float SMALLER_ITEM_HEIGHT = 45.0f;
const float SMALL_ITEM_WIDTH = 150.0f;
const float SMALL_ITEM_HEIGHT = 60.0f;

const float BIG_ITEM_WIDTH = 180.0f;
const float BIG_ITEM_HEIGHT = 75.0f;

const float ROW_HEIGHT = 120.0f;
const float COLUMN_HEIGHT = 150.0f;

const float TWENTY_PERCENT_WIDTH = 0.2f * RK356_WIDTH;
const float HALF_PERCENT_WIDTH = 0.5f * RK356_WIDTH;

const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);
const SizeF BIG_ITEM_SIZE(BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT);

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const OffsetF OFFSET_TOP_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, ZERO);
const OffsetF OFFSET_TOP_RIGHT = OffsetF(RK356_WIDTH, ZERO);

const OffsetF OFFSET_CENTER_LEFT = OffsetF(ZERO, RK356_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, RK356_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_RIGHT = OffsetF(RK356_WIDTH, RK356_HEIGHT / 2.0f);

const OffsetF OFFSET_BOTTOM_LEFT = OffsetF(ZERO, RK356_HEIGHT);
const OffsetF OFFSET_BOTTOM_MIDDLE = OffsetF(RK356_WIDTH / 2.0f, RK356_HEIGHT);
const OffsetF OFFSET_BOTTOM_RIGHT = OffsetF(RK356_WIDTH, RK356_HEIGHT);

const float NOPADDING = 0.0f;
const float PADDING_FIVE = 5.0f;
const float DOUBLE = 2.0f;
constexpr int32_t PLATFORM_VERSION_10 = 10;
constexpr int32_t PLATFORM_VERSION_9 = 9;
} // namespace
class FlexTestThreeNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FlexTestThreeNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void FlexTestThreeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: FlexColumnLayoutTest004
 * @tc.desc: Set 6 texts with 20% of container size in Column direction, container has no padding, the 4,5 has 1
 * layoutweight, the 6 has 2 displayPriority and 1 layoutweight.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexColumnLayoutTest004, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(columnLayoutPattern == nullptr);
    auto columnLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(columnLayoutProperty == nullptr);
    columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    auto columnLayoutAlgorithm = columnLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(columnLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(columnLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(RK356_WIDTH, ROW_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Column, alignItems: ItemAlign.Start}) {
        Text('1').width('20%').height(30).backgroundColor(0xFFFFFF)
        Text('2').width('20%').height(30).backgroundColor(0xEEEEEE)
        Text('3').width('20%').height(30).backgroundColor(0xDDDDDD)
        Text('4').width('20%').height(30).backgroundColor(0xCCCCCC).layoutWeight(1)
        Text('5').width('20%').height(30).backgroundColor(0xBBBBBB).layoutWeight(1)
        Text('6').width('20%').height(30).backgroundColor(0xAAAAAA).displayPriority(2).layoutWeight(1)
      }
      .height(100)
      .width('100%')
      .backgroundColor(0xAFEEEE)
    */
    int32_t index = 1;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        columnFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
        index++;
    }
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE - 1; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutWeight(LAYOUT_WEIGHT_ONE);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        columnFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
        index++;
    }

    auto sixthFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> sixthGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    sixthGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> sixthLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sixthFrameNode, sixthGeometryNode, sixthFrameNode->GetLayoutProperty());
    sixthLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
    sixthLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateDisplayIndex(DISPLAYPRIORITY_TWO);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateLayoutWeight(LAYOUT_WEIGHT_ONE);
    auto boxLayoutAlgorithm = sixthFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    sixthLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(sixthFrameNode);
    layoutWrapper->AppendChild(sixthLayoutWrapper);

    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    index = 0;
    auto verticalRemaning = COLUMN_HEIGHT - 3 * SMALLER_ITEM_HEIGHT;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALLER_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(0.0f, i * SMALLER_ITEM_HEIGHT));
        index++;
    }
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, verticalRemaning / 3));
        EXPECT_EQ(childOffset, OffsetF(0.0f, THREE_ITEM_SIZE * SMALLER_ITEM_HEIGHT + i * verticalRemaning / 3));
        index++;
    }
}
/**
 * @tc.name: FlexColumnLayoutTest005
 * @tc.desc: Set former 3 texts with 40% of container size in Row direction, container has no padding, the latter 3
 * texts with 20% width, and 4,5 has 1 layoutweight, the 6 has 2 displayPriority and 1 layoutweight.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexColumnLayoutTest005, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(columnLayoutPattern, nullptr);
    auto columnLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(columnLayoutProperty, nullptr);
    columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
    columnLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    auto columnLayoutAlgorithm = columnLayoutPattern->CreateLayoutAlgorithm();
    ASSERT_NE(columnLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(columnLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);

    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(RK356_WIDTH, ROW_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.ColumnReverse, alignItems: ItemAlign.Start}) {
        Text('1').width('20%').height(40).backgroundColor(0xFFFFFF)
        Text('2').width('20%').height(40).backgroundColor(0xEEEEEE)
        Text('3').width('20%').height(40).backgroundColor(0xDDDDDD)
        Text('4').width('20%').height(40).backgroundColor(0xCCCCCC).layoutWeight(1)
        Text('5').width('20%').height(40).backgroundColor(0xBBBBBB).layoutWeight(1)
        Text('6').width('20%').height(40).backgroundColor(0xAAAAAA).displayPriority(2).layoutWeight(1)
      }
      .height(100)
      .width('100%')
      .backgroundColor(0xAFEEEE)
    */
    int32_t index = 1;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        ASSERT_NE(boxLayoutAlgorithm, nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        columnFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
        index++;
    }

    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE - 1; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutWeight(LAYOUT_WEIGHT_ONE);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        ASSERT_NE(boxLayoutAlgorithm, nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        columnFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
        index++;
    }

    auto sixthFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, index, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> sixthGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    sixthGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> sixthLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sixthFrameNode, sixthGeometryNode, sixthFrameNode->GetLayoutProperty());
    sixthLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    sixthLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateDisplayIndex(DISPLAYPRIORITY_TWO);
    sixthLayoutWrapper->GetLayoutProperty()->UpdateLayoutWeight(LAYOUT_WEIGHT_ONE);
    auto boxLayoutAlgorithm = sixthFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(boxLayoutAlgorithm, nullptr);
    sixthLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(sixthFrameNode);
    layoutWrapper->AppendChild(sixthLayoutWrapper);

    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    index = 0;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(0.0f, 0.0f));
        EXPECT_EQ(childOffset, OffsetF(0.0f, 0.0f));
        index++;
    }

    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE - 1; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(0.0f, 0.0f));
        EXPECT_EQ(childOffset, OffsetF(0.0f, 0.0f));
        index++;
    }
    auto sixthChildWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto sixthChildSize = sixthChildWrapper->GetGeometryNode()->GetFrameSize();
    auto sixthChildOffset = sixthChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(sixthChildSize, SizeF(TWENTY_PERCENT_WIDTH, COLUMN_HEIGHT / 3));
    EXPECT_EQ(sixthChildOffset, OffsetF(0.0f, 2 * COLUMN_HEIGHT / 3));
}

/**
 * @tc.name: FlexColumnLayoutTest006
 * @tc.desc: Set three texts with different flexBasis, flexGrows, flexShrink.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexColumnLayoutTest006, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(columnLayoutPattern == nullptr);
    auto columnLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(columnLayoutProperty == nullptr);
    columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    columnLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto columnLayoutAlgorithm = columnLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(columnLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(columnLayoutAlgorithm));
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Column, alignItems: ItemAlign.Start}) {
            Text('1').width('20%').backgroundColor(0xDDDDDD).flexBasis(20)
            Text('2').width('20%').height('20%').backgroundColor(0xDFFFFF).flexGrow(2)
            Text('3').width('20%').height('20%').backgroundColor(0xF5DEB3).flexShrink(1)
        }
        .height(100)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength()));
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateFlexBasis(Dimension(SMALL_ITEM_HEIGHT / 2));
    firstItemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT / 2)));
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateFlexGrow(2);
    secondItemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);

    auto thirdItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> thirdItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    thirdItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> thirdItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        thirdItemFrameNode, thirdItemGeometryNode, thirdItemFrameNode->GetLayoutProperty());
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT / 2)));
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdateFlexShrink(1);
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    thirdItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(thirdItemFrameNode);
    layoutWrapper->AppendChild(thirdItemLayoutWrapper);

    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT / 4));
    EXPECT_EQ(firstChildOffset, OFFSET_TOP_LEFT);
    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT / 4 * 3));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, ROW_HEIGHT / 4));
    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT / 4));
    EXPECT_EQ(thirdChildOffset, OffsetF(0.0f, COLUMN_HEIGHT - ROW_HEIGHT / 4));
}

/**
 * @tc.name: FlexRowLayoutTest018
 * @tc.desc: Set 6 texts in Row direction, container has no padding, the former 3 has 50% width
 * the latter 3 has 2 displayPriority with 20% width.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest018, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(ROW_HEIGHT)));
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(RK356_WIDTH, ROW_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Center}) {
        Text('1').width('50%').height(40).backgroundColor(0xFFFFFF).flexGrow(2)
        Text('2').width('50%').height(40).backgroundColor(0xEEEEEE).flexGrow(0)
        Text('3').width('50%').height(40).backgroundColor(0xDDDDDD).flexShrink(1)
        Text('4').width('20%').height(40).backgroundColor(0xCCCCCC).displayPriority(2).flexGrow(2)
        Text('5').width('20%').height(40).backgroundColor(0xBBBBBB).displayPriority(2).flexGrow(0)
        Text('6').width('20%').height(40).backgroundColor(0xAAAAAA).displayPriority(2).flexShrink(1)
      }
      .height(80)
      .width('100%')
      .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < 2 * THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        if (i >= THREE_ITEM_SIZE) {
            itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
            itemLayoutWrapper->GetLayoutProperty()->UpdateDisplayIndex(DISPLAYPRIORITY_TWO);
        }
        if (i == 0 || i == 3) {
            itemLayoutWrapper->GetLayoutProperty()->UpdateFlexGrow(2);
        } else if (i == 1 || i == 4) {
            itemLayoutWrapper->GetLayoutProperty()->UpdateFlexGrow(0);
        } else {
            itemLayoutWrapper->GetLayoutProperty()->UpdateFlexShrink(1);
        }
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, ROW_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i + THREE_ITEM_SIZE);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        if (i == 0) {
            EXPECT_EQ(childSize, SizeF(THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
            EXPECT_EQ(childOffset, OffsetF(i * TWENTY_PERCENT_WIDTH, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2.0f));
        } else {
            EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
            EXPECT_EQ(childOffset, OffsetF((i + 2) * TWENTY_PERCENT_WIDTH, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2.0f));
        }
    }
}

/**
 * @tc.name: FlexRowLayoutTest019
 * @tc.desc: Set 6 texts in RowReverse direction, container has no padding, the former 3 has 50% width
 * the latter 3 has 2 displayPriority with 20% width.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest019, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(ROW_HEIGHT)));
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(RK356_WIDTH, ROW_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.RowReverse, alignItems: ItemAlign.Center}) {
        Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
        Text('2').width('50%').height(40).backgroundColor(0xEEEEEE)
        Text('3').width('50%').height(40).backgroundColor(0xDDDDDD)
        Text('4').width('20%').height(40).backgroundColor(0xCCCCCC).displayPriority(2)
        Text('5').width('20%').height(40).backgroundColor(0xBBBBBB).displayPriority(2)
        Text('6').width('20%').height(40).backgroundColor(0xAAAAAA).displayPriority(2)
      }
      .height(80)
      .width('100%')
      .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < 2 * THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        if (i >= THREE_ITEM_SIZE) {
            itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
            itemLayoutWrapper->GetLayoutProperty()->UpdateDisplayIndex(DISPLAYPRIORITY_TWO);
        }
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, ROW_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i + THREE_ITEM_SIZE);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset,
            OffsetF(RK356_WIDTH - (i + 1) * TWENTY_PERCENT_WIDTH, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2.0f));
    }
}

/**
 * @tc.name: FlexColumnLayoutTest007
 * @tc.desc: Set 6 texts in Column direction, container has no padding, the former 3 has 50 height
 * the latter 3 has 2 displayPriority with 20 height.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexColumnLayoutTest007, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(RK356_WIDTH, ROW_HEIGHT);
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Column, alignItems: ItemAlign.Start}) {
        Text('1').width('50%').height(50).backgroundColor(0xFFFFFF)
        Text('2').width('50%').height(50).backgroundColor(0xEEEEEE)
        Text('3').width('50%').height(50).backgroundColor(0xDDDDDD)
        Text('4').width('50%').height(30).backgroundColor(0xCCCCCC).displayPriority(2)
        Text('5').width('50%').height(30).backgroundColor(0xBBBBBB).displayPriority(2)
        Text('6').width('50%').height(30).backgroundColor(0xAAAAAA).displayPriority(2)
      }
      .height(100)
      .width('100%')
      .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < 2 * THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(BIG_ITEM_HEIGHT)));
        if (i >= THREE_ITEM_SIZE) {
            itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
            itemLayoutWrapper->GetLayoutProperty()->UpdateDisplayIndex(DISPLAYPRIORITY_TWO);
        }
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i + THREE_ITEM_SIZE);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(HALF_PERCENT_WIDTH, SMALLER_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(0.0f, i * SMALLER_ITEM_HEIGHT));
    }
}

/**
 * @tc.name: FlexRowLayoutTest020
 * @tc.desc: Set one child in Row direction and no constraint
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest020, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start}) {
            Text('1').width(100).height(40).backgroundColor(0xFFFFFF)
      }
      .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: FlexRowLayoutTest021
 * @tc.desc: Set one child in RowReverse direction and no constraint
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest021, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start}) {
            Text('1').width(100).height(40).backgroundColor(0xFFFFFF)
      }
      .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: FlexRowLayoutTest022
 * @tc.desc: Set no child in Row direction and no constraint
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest022, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start}) {}
      .backgroundColor(0xAFEEEE)
    */

    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetAllChildrenWithBuild().size(), 0);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(-1.0f, -1.0f));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: FlexColumnLayoutTest008
 * @tc.desc: Set one child in Column direction and no constraint
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexColumnLayoutTest008, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start}) {
            Text('1').width(100).height(40).backgroundColor(0xFFFFFF)
      }
      .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: FlexRowLayoutTest011
 * @tc.desc: Set two children and first child to be visible gone
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest011, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Center})
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
            .Visibility(VisibleType.None)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    auto firstLayoutProperty = firstFrameNode->GetLayoutProperty();
    firstLayoutProperty->UpdateVisibility(VisibleType::GONE);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstLayoutProperty);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    firstLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(
        secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2));
}

/**
 * @tc.name: FlexRowLayoutTest012
 * @tc.desc: Set flex has a flex child and a blank children and second child has layout weight 1
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest012, TestSize.Level1)
{
    std::vector<int32_t> platformVersions = { PLATFORM_VERSION_9, PLATFORM_VERSION_10 };
    for (int32_t i = 0; i < platformVersions.size(); i++) {
        PipelineBase::GetCurrentContext()->SetMinPlatformVersion(platformVersions[i]);
        // create root linear node
        auto rowFrameNode =
            FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        EXPECT_FALSE(rowFrameNode == nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        EXPECT_FALSE(geometryNode == nullptr);
        RefPtr<LayoutWrapperNode> layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

        auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
        EXPECT_FALSE(rowLayoutPattern == nullptr);
        auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
        EXPECT_FALSE(rowLayoutProperty == nullptr);
        rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
        auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
        EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
        // update layout wrapper for root node
        layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
        layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(CONTAINER_SIZE.Width()), CalcLength(CONTAINER_SIZE.Height())));
        LayoutConstraintF parentLayoutConstraint;
        parentLayoutConstraint.maxSize = CONTAINER_SIZE;
        parentLayoutConstraint.percentReference = CONTAINER_SIZE;

        layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
        layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

        auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        childLayoutConstraint.maxSize = CONTAINER_SIZE;
        childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
        /* corresponding ets code:
            Row() {
                Row() {
                    Blank()
                    .width(100)
                    .height(40)
                    .layoutWeight(1)
                }
            }.height(80)
            .width('100%')
        */
        // create node and layout wrapper for the first node
        auto firstFrameNode =
            FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(false));
        RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        firstGeometryNode->Reset();
        auto firstLayoutProperty = firstFrameNode->GetLayoutProperty();
        RefPtr<LayoutWrapperNode> firstLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstLayoutProperty);
        firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        auto boxLayoutAlgorithm = firstFrameNode->GetPattern<LinearLayoutPattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        firstLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(firstFrameNode);
        layoutWrapper->AppendChild(firstLayoutWrapper);

        // create node and layout wrapper for the second node
        auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        secondGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
        secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        auto secondBoxLayoutAlgorithm = secondFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(secondBoxLayoutAlgorithm == nullptr);
        secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        // update layout weight for the grandchild node
        secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutWeight(1);
        secondLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(secondBoxLayoutAlgorithm));
        firstFrameNode->AddChild(secondFrameNode);
        firstLayoutWrapper->AppendChild(secondLayoutWrapper);
        rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

        EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize().Width(), CONTAINER_SIZE.Width());
        EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
            OffsetF(ZERO, CONTAINER_SIZE.Height() - SMALL_ITEM_HEIGHT) * HALF);
    }
}

/**
 * @tc.name: FlexRowLayoutTest013
 * @tc.desc: Set two children parent has padding, first child has layout weight
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestThreeNg, FlexRowLayoutTest013, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(ROW_HEIGHT)));
    PaddingProperty padding;
    padding.left = CalcLength(PADDING_FIVE);
    padding.right = CalcLength(PADDING_FIVE);
    padding.top = CalcLength(PADDING_FIVE);
    padding.bottom = CalcLength(PADDING_FIVE);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(padding);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Flex({direction: FlexDirection.Row}) {
          Blank()
            .layoutWeight(1)
          Blank()
        }.height(80)
        .padding(5)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    auto firstLayoutProperty = firstFrameNode->GetLayoutProperty();
    firstLayoutProperty->UpdateLayoutWeight(1);
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstLayoutProperty);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(SMALL_ITEM_HEIGHT)));
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(),
        SizeF(CONTAINER_SIZE.Width() - PADDING_FIVE * DOUBLE - SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(PADDING_FIVE, PADDING_FIVE));
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(CONTAINER_SIZE.Width() - PADDING_FIVE - SMALL_ITEM_WIDTH, PADDING_FIVE));
}
} // namespace OHOS::Ace::NG

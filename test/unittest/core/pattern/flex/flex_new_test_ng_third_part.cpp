/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "flex_new_test_common.h"

namespace OHOS::Ace::NG {
namespace {
// Constants for flex layout tests
const int32_t START_INDEX = 0;
const int32_t THREE_ITEM_SIZE = 3;
const float SMALL_ITEM_HEIGHT = 60.0f;
const float ROW_HEIGHT = 120.0f;
const float TWENTY_PERCENT_WIDTH = 0.2f * RK356_WIDTH;
const float NOPADDING = 0.0f;
} // namespace
using namespace testing;
using namespace testing::ext;

/**
 * @tc.name: FlexLayoutAlgorithmDirection001
 * @tc.desc: Test FlexLayoutAlgorithm with different flex directions
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmDirection001, TestSize.Level0)
{
    /**
     * @tc.steps1: Create layout property with ROW direction
     */
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);

    /**
     * @tc.expected: Direction should be set to ROW
     */
    auto flexDirection = layoutProperty->GetFlexDirection();
    ASSERT_TRUE(flexDirection.has_value());
    EXPECT_EQ(flexDirection.value(), FlexDirection::ROW);

    /**
     * @tc.steps2: Change to COLUMN direction
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    flexDirection = layoutProperty->GetFlexDirection();
    ASSERT_TRUE(flexDirection.has_value());
    EXPECT_EQ(flexDirection.value(), FlexDirection::COLUMN);

    /**
     * @tc.steps3: Test ROW_REVERSE
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    flexDirection = layoutProperty->GetFlexDirection();
    ASSERT_TRUE(flexDirection.has_value());
    EXPECT_EQ(flexDirection.value(), FlexDirection::ROW_REVERSE);

    /**
     * @tc.steps4: Test COLUMN_REVERSE
     */
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
    flexDirection = layoutProperty->GetFlexDirection();
    ASSERT_TRUE(flexDirection.has_value());
    EXPECT_EQ(flexDirection.value(), FlexDirection::COLUMN_REVERSE);
}

/**
 * @tc.name: FlexLayoutAlgorithmAlign001
 * @tc.desc: Test FlexLayoutAlgorithm with different main axis alignments
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmAlign001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test FLEX_START alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_START);

    /**
     * @tc.steps2: Test CENTER alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);

    /**
     * @tc.steps3: Test FLEX_END alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_END);

    /**
     * @tc.steps4: Test SPACE_BETWEEN alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::SPACE_BETWEEN);

    /**
     * @tc.steps5: Test SPACE_AROUND alignment
     */
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    EXPECT_EQ(layoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::SPACE_AROUND);
}

/**
 * @tc.name: FlexLayoutAlgorithmCrossAlign001
 * @tc.desc: Test FlexLayoutAlgorithm with different cross axis alignments
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmCrossAlign001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test FLEX_START cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_START);

    /**
     * @tc.steps2: Test CENTER cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);

    /**
     * @tc.steps3: Test FLEX_END cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::FLEX_END);

    /**
     * @tc.steps4: Test STRETCH cross axis alignment
     */
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::STRETCH);
}

/**
 * @tc.name: FlexLayoutAlgorithmSpace001
 * @tc.desc: Test FlexLayoutAlgorithm with space property
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmSpace001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Update space with different values
     */
    layoutProperty->UpdateSpace(Dimension(10.0, DimensionUnit::PX));
    auto space = layoutProperty->GetSpaceValue({});
    EXPECT_EQ(space.ConvertToPx(), 10.0f);

    layoutProperty->UpdateSpace(Dimension(20.0, DimensionUnit::PX));
    space = layoutProperty->GetSpaceValue({});
    EXPECT_EQ(space.ConvertToPx(), 20.0f);
}

/**
 * @tc.name: FlexLayoutAlgorithmRTL001
 * @tc.desc: Test FlexLayoutAlgorithm with RTL layout direction
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmRTL001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();

    /**
     * @tc.steps1: Test LTR direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::LTR);

    /**
     * @tc.steps2: Test RTL direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::RTL);

    /**
     * @tc.steps3: Test AUTO direction
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::AUTO);
}

/**
 * @tc.name: FlexLayoutAlgorithmClone001
 * @tc.desc: Test FlexLayoutProperty clone functionality
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmClone001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);

    /**
     * @tc.steps: Clone the property
     */
    auto clonedProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty->Clone());

    /**
     * @tc.expected: Cloned property should have same values
     */
    ASSERT_NE(clonedProperty, nullptr);
    auto clonedDirection = clonedProperty->GetFlexDirection();
    ASSERT_TRUE(clonedDirection.has_value());
    EXPECT_EQ(clonedDirection.value(), FlexDirection::COLUMN);
    EXPECT_EQ(clonedProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::CENTER);
    EXPECT_EQ(clonedProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START), FlexAlign::STRETCH);
}

/**
 * @tc.name: FlexLayoutAlgorithmReset001
 * @tc.desc: Test FlexLayoutProperty reset functionality
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexLayoutAlgorithmReset001, TestSize.Level0)
{
    auto layoutProperty = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::BASELINE);

    /**
     * @tc.steps: Reset the property
     */
    layoutProperty->Reset();

    /**
     * @tc.expected: Property should be reset to default
     */
    EXPECT_FALSE(layoutProperty->GetFlexDirection().has_value());
}

/**
 * @tc.name: FlexRowLayoutTest011
 * @tc.desc: Set three texts with size in row and check the alignItems is Stretch and justifyContent is SpaceAround.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexRowLayoutTest011, TestSize.Level0)
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
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Stretch, justifyContent: FlexAlign.SpaceAround}) {
            Text('1').width('20%').height(40).backgroundColor(0xDDDDDD)
            Text('2').width('20%').height(40).backgroundColor(0xDFFFFF)
            Text('3').width('20%').height(40).backgroundColor(0xF5DEB3)
        }
        .height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
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

    auto horizontalRemaining = RK356_WIDTH - THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH;
    horizontalRemaining = horizontalRemaining / THREE_ITEM_SIZE;

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(horizontalRemaining / 2, 0.0f));
    for (int32_t i = START_INDEX + 1; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT));
        EXPECT_EQ(
            childOffset, OffsetF(horizontalRemaining / 2 + i * (TWENTY_PERCENT_WIDTH + horizontalRemaining), 0.0f));
    }
}

/**
 * @tc.name: FlexRowLayoutTest012
 * @tc.desc: Set three texts with size in row and check the alignItems is Center and justifyContent is SpaceEvenly.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexRowLayoutTest012, TestSize.Level0)
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
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_EVENLY);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceEvenly}) {
            Text('1').width('20%').height(40).backgroundColor(0xDDDDDD)
            Text('2').width('20%').height(40).backgroundColor(0xDFFFFF)
            Text('3').width('20%').height(40).backgroundColor(0xF5DEB3)
        }
        .height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
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

    auto horizontalRemaining = RK356_WIDTH - THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH;
    horizontalRemaining = horizontalRemaining / (THREE_ITEM_SIZE + 1);
    auto verticalRemaining = ROW_HEIGHT - SMALL_ITEM_HEIGHT;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(
            childOffset, OffsetF(i * TWENTY_PERCENT_WIDTH + (i + 1) * horizontalRemaining, verticalRemaining / 2));
    }
}

/**
 * @tc.name: FlexRowLayoutTest013
 * @tc.desc: Set three texts with size in row and check the alignItems is Stretch and justifyContent is Center.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexRowLayoutTest013, TestSize.Level0)
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
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::STRETCH);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Stretch, justifyContent: FlexAlign.Center}) {
            Text('1').width('20%').height(40).backgroundColor(0xDDDDDD)
            Text('2').width('20%').height(40).backgroundColor(0xDFFFFF)
            Text('3').width('20%').height(40).backgroundColor(0xF5DEB3)
        }
        .height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
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

    auto horizontalRemaining = RK356_WIDTH - THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, ROW_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(horizontalRemaining / 2 + i * TWENTY_PERCENT_WIDTH, 0.0f));
    }
}

} // namespace OHOS::Ace::NG
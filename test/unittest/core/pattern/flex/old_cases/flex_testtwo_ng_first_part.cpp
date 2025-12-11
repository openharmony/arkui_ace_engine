/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "flex_testtwo_ng.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: wrapRowLayoutTest001
 * @tc.desc: Test layout of flex wrap.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest001, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::START);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::START);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start, alignItems:
       ItemAlign.Start, alignContent: FlexAlign.Start }) { Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OFFSET_TOP_LEFT);

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(HALF_PERCENT_WIDTH, 0.0f));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(0.0f, SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: wrapRowLayoutTest002
 * @tc.desc: Test layout of different flex wrap settings.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest002, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL_REVERSE);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::CENTER);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::CENTER);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::CENTER);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.WrapReverse, justifyContent: FlexAlign.Center, alignItems:
       ItemAlign.Center, alignContent: FlexAlign.Center }) { Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    OffsetF startPosition = OffsetF(ZERO, ZERO);
    OffsetF spaceBetweenContentsOnCrossAxis = OffsetF(RK356_WIDTH / 2.0f, ZERO);
    wrapLayoutAlgorithm->UpdateStartPositionByAlign(startPosition, 2.0f, spaceBetweenContentsOnCrossAxis, 2);
    auto verticalRemaining = COLUMN_HEIGHT - 2 * SMALL_ITEM_HEIGHT;
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(HALF_PERCENT_WIDTH, verticalRemaining / 2));

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, verticalRemaining / 2));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(HALF_PERCENT_WIDTH / 2, verticalRemaining / 2 + SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: wrapRowLayoutTest003
 * @tc.desc: Test layout of different flex wrap settings.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest003, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::END);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::END);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::END);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Column, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.End, alignItems:
       ItemAlign.End, alignContent: FlexAlign.End }) { Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    OffsetF startPosition = OffsetF(ZERO, ZERO);
    OffsetF spaceBetweenContentsOnCrossAxis = OffsetF(RK356_WIDTH / 2.0f, ZERO);
    wrapLayoutAlgorithm->UpdateStartPositionByAlign(startPosition, 2.0f, spaceBetweenContentsOnCrossAxis, 2);
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(0.0f, COLUMN_HEIGHT - 2 * SMALL_ITEM_HEIGHT));

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, COLUMN_HEIGHT - SMALL_ITEM_HEIGHT));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(HALF_PERCENT_WIDTH, COLUMN_HEIGHT - SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: wrapRowLayoutTest004
 * @tc.desc: Test layout of different flex wrap settings.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest004, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::VERTICAL_REVERSE);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::SPACE_AROUND);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::SPACE_AROUND);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::STRETCH);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Column, wrap: FlexWrap.WrapReverse, justifyContent: FlexAlign.SpaceAround,
       alignItems: ItemAlign.Stretch, alignContent: FlexAlign.SpaceAround }) {
            Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    OffsetF startPosition = OffsetF(ZERO, ZERO);
    OffsetF spaceBetweenContentsOnCrossAxis = OffsetF(RK356_WIDTH / 2.0f, ZERO);
    wrapLayoutAlgorithm->UpdateStartPositionByAlign(startPosition, 2.0f, spaceBetweenContentsOnCrossAxis, 2);
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    auto verticalRemaining = COLUMN_HEIGHT - 2 * SMALL_ITEM_HEIGHT;
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(0.0f, COLUMN_HEIGHT - verticalRemaining / 4 - SMALL_ITEM_HEIGHT));

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, verticalRemaining / 4));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(HALF_PERCENT_WIDTH, (COLUMN_HEIGHT - SMALL_ITEM_HEIGHT) / 2));
}

/**
 * @tc.name: wrapRowLayoutTest005
 * @tc.desc: Test layout of different flex wrap settings.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest005, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::SPACE_BETWEEN);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::SPACE_BETWEEN);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::BASELINE);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems:
       ItemAlign.Baseline, alignContent: FlexAlign.SpaceBetween }) {
            Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    OffsetF startPosition = OffsetF(ZERO, ZERO);
    OffsetF spaceBetweenContentsOnCrossAxis = OffsetF(RK356_WIDTH / 2.0f, ZERO);
    wrapLayoutAlgorithm->UpdateStartPositionByAlign(startPosition, 2.0f, spaceBetweenContentsOnCrossAxis, 2);
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OFFSET_TOP_LEFT);

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(HALF_PERCENT_WIDTH, 0.0f));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(0.0f, COLUMN_HEIGHT - SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: wrapRowLayoutTest006
 * @tc.desc: Test layout of different flex wrap settings.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest006, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutProperty->UpdateAlignment(WrapAlignment::SPACE_EVENLY);
    wrapLayoutProperty->UpdateMainAlignment(WrapAlignment::SPACE_EVENLY);
    wrapLayoutProperty->UpdateCrossAlignment(WrapAlignment::START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceEvenly, alignItems:
       ItemAlign.Start, alignContent: FlexAlign.SpaceEvenly }) {
            Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('50%').height(40).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    OffsetF startPosition = OffsetF(ZERO, ZERO);
    OffsetF spaceBetweenContentsOnCrossAxis = OffsetF(RK356_WIDTH / 2.0f, ZERO);
    wrapLayoutAlgorithm->UpdateStartPositionByAlign(startPosition, 2.0f, spaceBetweenContentsOnCrossAxis, 2);
    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    auto verticalRemaining = COLUMN_HEIGHT - 2 * SMALL_ITEM_HEIGHT;
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(0.0f, verticalRemaining / 3));

    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(HALF_PERCENT_WIDTH, verticalRemaining / 3));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(
        thirdChildOffset, OffsetF(HALF_PERCENT_WIDTH / 2, COLUMN_HEIGHT - SMALL_ITEM_HEIGHT - verticalRemaining / 3));
}

/**
 * @tc.name: wrapRowLayoutTest007
 * @tc.desc: Test the sum of width is bigger than flex size
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest007, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap}) {
            Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('60%').height(30).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    secondChildWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SIXTY_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OFFSET_TOP_LEFT);

    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(SIXTY_PERCENT_WIDTH, SMALLER_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, SMALL_ITEM_HEIGHT));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(0.0f, SMALL_ITEM_HEIGHT + SMALLER_ITEM_HEIGHT));
}

/**
 * @tc.name: wrapRowLayoutTest008
 * @tc.desc: Test the sum of width is bigger than flex width in column
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, wrapRowLayoutTest008, TestSize.Level0)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    EXPECT_FALSE(wrapFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(wrapFrameNode, geometryNode, wrapFrameNode->GetLayoutProperty());

    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(wrapLayoutPattern == nullptr);
    auto wrapLayoutProperty = wrapLayoutPattern->GetLayoutProperty<FlexLayoutProperty>();
    EXPECT_FALSE(wrapLayoutProperty == nullptr);
    wrapLayoutProperty->UpdateWrapDirection(WrapDirection::VERTICAL);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(COLUMN_HEIGHT)));

    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    EXPECT_FALSE(wrapLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(wrapLayoutAlgorithm));
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
        Flex({direction: FlexDirection.Column, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start, alignItems:
       ItemAlign.Start, alignContent: FlexAlign.Start}) { Text('1').width('50%').height(40).backgroundColor(0xFFFFFF)
            Text('2').width('60%').height(30).backgroundColor(0xCCCCCC)
            Text('3').width('50%').height(40).backgroundColor(0x000000)
        }
        .size({ width: '100%', height: 100})
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
            CalcSize(CalcLength(HALF_PERCENT_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        wrapFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    auto secondChildWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    secondChildWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SIXTY_PERCENT_WIDTH), CalcLength(SMALLER_ITEM_HEIGHT)));
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    wrapLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetFrameSize();
    auto firstChildOffset = firstChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(firstChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OFFSET_TOP_LEFT);

    auto secondChildSize = secondChildWrapper->GetGeometryNode()->GetFrameSize();
    auto secondChildOffset = secondChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(secondChildSize, SizeF(SIXTY_PERCENT_WIDTH, SMALLER_ITEM_HEIGHT));
    EXPECT_EQ(secondChildOffset, OffsetF(0.0f, SMALL_ITEM_HEIGHT));

    auto thirdChildWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    auto thirdChildSize = thirdChildWrapper->GetGeometryNode()->GetFrameSize();
    auto thirdChildOffset = thirdChildWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(thirdChildSize, SizeF(HALF_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(thirdChildOffset, OffsetF(SIXTY_PERCENT_WIDTH, 0.0f));
}

/**
 * @tc.name: FlexRowLayoutTest015
 * @tc.desc: Set 6 texts with 20% of container size in Row direction, container has no padding, the 4,5 has 1
 * layoutweight, the 6 has 2 displayPriority and 1 layoutweight.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestTwoNg, FlexRowLayoutTest015, TestSize.Level0)
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Center}) {
        Text('1').width('20%').height(40).backgroundColor(0xFFFFFF)
        Text('2').width('20%').height(40).backgroundColor(0xEEEEEE)
        Text('3').width('20%').height(40).backgroundColor(0xDDDDDD)
        Text('4').width('20%').height(40).backgroundColor(0xCCCCCC).layoutWeight(1)
        Text('5').width('20%').height(40).backgroundColor(0xBBBBBB).layoutWeight(1)
        Text('6').width('20%').height(40).backgroundColor(0xAAAAAA).displayPriority(2).layoutWeight(1)
      }
      .height(80)
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
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(itemFrameNode);
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
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        rowFrameNode->AddChild(itemFrameNode);
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
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    sixthLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(sixthFrameNode);
    layoutWrapper->AppendChild(sixthLayoutWrapper);

    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, ROW_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    index = 0;
    auto verticalRemaning = ROW_HEIGHT - SMALL_ITEM_HEIGHT;
    auto horizontalRemaining = RK356_WIDTH - THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(i * TWENTY_PERCENT_WIDTH, verticalRemaning / 2.0f));
        index++;
    }
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(horizontalRemaining / 3, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset,
            OffsetF(THREE_ITEM_SIZE * TWENTY_PERCENT_WIDTH + i * horizontalRemaining / 3, verticalRemaning / 2.0f));
        index++;
    }
}
} // namespace OHOS::Ace::NG

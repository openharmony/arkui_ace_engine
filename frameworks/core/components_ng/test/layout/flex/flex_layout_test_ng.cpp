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

#include <cstdint>
#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

const int START_INDEX = 0;
const int THREE_ITEM_SIZE = 3;
const int FOUR_ITEM_SIZE = 4;

const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const float ZERO = 0.0f;

const float SMALL_ITEM_WIDTH = 150.0f;
const float SMALL_ITEM_HEIGHT = 60.0f;

const float BIG_ITEM_WIDTH = 180.0f;
const float BIG_ITEM_HEIGHT = 75.0f;

const float ROW_HEIGHT = 120.0f;
const float COLUMN_HEIGHT = 150.0f;

const float TWENTY_PERCENT_WIDTH = 0.2f * RK356_WIDTH;
const float TWENTY_PERCENT_COLUMN_HEIGHT = 0.2f * COLUMN_HEIGHT;

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

} // namespace

class FlexLayoutTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void FlexLayoutTestNg::SetUp() {}

void FlexLayoutTestNg::TearDown() {}
/**
 * @tc.name: FlexRowLayoutTest001
 * @tc.desc: Set two texts with size in row and check them.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest001, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

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
          Text("Text 1")
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Text("Text 2")
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
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
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
    EXPECT_EQ(
        firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2));
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(SMALL_ITEM_WIDTH, (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / 2));
}

/**
 * @tc.name: FlexRowLayoutTest002
 * @tc.desc: Set two items with different constraint size.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest002, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(RK356_WIDTH), CalcLength(ROW_HEIGHT)));
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(rowLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start}) {
            Text("Text 1")
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
            .constraintSize({minWidth : 120, minHeight: 50})
            }
            Text("Text 2")
            .width(120)
            .height(50)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
            .constraintSize({maxWidth : 100, maxHeight: 40})
        }
        .height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    auto firstLayoutConstraint = childLayoutConstraint;
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(firstLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    firstLayoutWrapper->GetLayoutProperty()->UpdateCalcMinSize(
        CalcSize(CalcLength(BIG_ITEM_WIDTH), CalcLength(BIG_ITEM_HEIGHT)));

    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    auto secondLayoutConstraint = childLayoutConstraint;
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(secondLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BIG_ITEM_WIDTH), CalcLength(BIG_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdateCalcMaxSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    rowLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    rowLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), BIG_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(BIG_ITEM_WIDTH, 0.0f));
}

/**
 * @tc.name: FlexRowLayoutTest003
 * @tc.desc: Set four texts with 20% of container size in row direction, container has no padding.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest003, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
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
        Flex({direction: FlexDirection.Reverse, alignItems: ItemAlign.Start}) {
            Text('1').width('20%').height(40).backgroundColor(0xF5DEB3)
            Text('2').width('20%').height(40).backgroundColor(0xD2B48C)
            Text('3').width('20%').height(40).backgroundColor(0xF5DEB3)
            Text('4').width('20%').height(40).backgroundColor(0xD2B48C)
        }
        .height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < FOUR_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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

    for (int32_t i = START_INDEX; i < FOUR_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(RK356_WIDTH - (i + 1) * TWENTY_PERCENT_WIDTH, 0.0f));
    }
}

/**
 * @tc.name: FlexColumnLayoutTest001
 * @tc.desc: Set two texts with size in column and check them.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexColumnLayoutTest001, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(columnLayoutPattern == nullptr);
    auto columnLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(columnLayoutProperty == nullptr);
    columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    columnLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto columnLayoutAlgorithm = columnLayoutPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(columnLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(columnLayoutAlgorithm));
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
        Flex({direction: FlexDirection.Column, alignItems: ItemAlign.Center}){
          Text("Text 1")
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Text("Text 2")
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
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    firstLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(
        firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF((RK356_WIDTH - SMALL_ITEM_WIDTH) / 2, 0.0f));
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF((RK356_WIDTH - SMALL_ITEM_WIDTH) / 2, SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: FlexColumnLayoutTest002
 * @tc.desc: Set two items in column with different constraint size.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexColumnLayoutTest002, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

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
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, COLUMN_HEIGHT));

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
            Text("Text 1")
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
            .constraintSize({minWidth : 120, minHeight: 50})
            }
            Text("Text 2")
            .width(120)
            .height(50)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
            .constraintSize({maxWidth : 100, maxHeight: 40})
        }
        .height(100)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    auto firstLayoutConstraint = childLayoutConstraint;
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(firstLayoutConstraint);
    firstLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    firstLayoutWrapper->GetLayoutProperty()->UpdateCalcMinSize(
        CalcSize(CalcLength(BIG_ITEM_WIDTH), CalcLength(BIG_ITEM_HEIGHT)));

    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(firstFrameNode);
    layoutWrapper->AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    auto secondLayoutConstraint = childLayoutConstraint;
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(secondLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BIG_ITEM_WIDTH), CalcLength(BIG_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdateCalcMaxSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    columnFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), BIG_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, BIG_ITEM_HEIGHT));
}

/**
 * @tc.name: FlexColumnLayoutTest003
 * @tc.desc: Set four texts with 20% of container size in column direction, container has no padding.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexColumnLayoutTest003, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(columnLayoutPattern == nullptr);
    auto columnLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(columnLayoutProperty == nullptr);
    columnLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
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
        Flex({direction: FlexDirection.ColumnReverse, alignItems: ItemAlign.Start}) {
            Text('1').width('20%').height('20%').backgroundColor(0xF5DEB3)
            Text('2').width('20%').height('20%').backgroundColor(0xD2B48C)
            Text('3').width('20%').height('20%').backgroundColor(0xF5DEB3)
            Text('4').width('20%').height('20%').backgroundColor(0xD2B48C)
        }
        .height(100)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    for (int32_t i = START_INDEX; i < FOUR_ITEM_SIZE; i++) {
        auto itemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, i + 1, AceType::MakeRefPtr<Pattern>());
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(TWENTY_PERCENT_WIDTH), CalcLength(TWENTY_PERCENT_COLUMN_HEIGHT)));
        itemLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
        auto boxLayoutAlgorithm = itemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        columnFrameNode->AddChild(itemFrameNode);
        layoutWrapper->AppendChild(itemLayoutWrapper);
    }
    columnLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    columnLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(RK356_WIDTH, COLUMN_HEIGHT));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);

    for (int32_t i = START_INDEX; i < FOUR_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, TWENTY_PERCENT_COLUMN_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(0.0f, COLUMN_HEIGHT - (i + 1) * TWENTY_PERCENT_COLUMN_HEIGHT));
    }
}

/**
 * @tc.name: FlexRowLayoutTest005
 * @tc.desc: Set three texts with size in row and check the alignItems is Start and justifyContent is Start.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest005, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Start, justifyContent: FlexAlign.Start}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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

    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(i * TWENTY_PERCENT_WIDTH, 0.0f));
    }
}

/**
 * @tc.name: FlexRowLayoutTest006
 * @tc.desc: Set three texts with size in row and check the alignItems is Center and justifyContent is Center.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest006, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
    auto verticalRemaining = ROW_HEIGHT - SMALL_ITEM_HEIGHT;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(horizontalRemaining / 2 + i * TWENTY_PERCENT_WIDTH, verticalRemaining / 2));
    }
}

/**
 * @tc.name: FlexRowLayoutTest007
 * @tc.desc: Set three texts with size in row and check the alignItems is End and justifyContent is End.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest007, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.End, justifyContent: FlexAlign.End}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
    auto verticalRemaining = ROW_HEIGHT - SMALL_ITEM_HEIGHT;
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(horizontalRemaining + i * TWENTY_PERCENT_WIDTH, verticalRemaining));
    }
}

/**
 * @tc.name: FlexRowLayoutTest008
 * @tc.desc: Set three texts with size in row and check the alignItems is Stretch and justifyContent is SpaceBetween.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest008, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_BETWEEN);
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
        Flex({direction: FlexDirection.Row, alignItems: ItemAlign.Stretch, justifyContent: FlexAlign.SpaceBetween}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
        EXPECT_EQ(childOffset, OffsetF(i * (TWENTY_PERCENT_WIDTH + horizontalRemaining / 2), 0.0f));
    }
}

/**
 * @tc.name: FlexRowLayoutTest009
 * @tc.desc: Set three texts with size in row and check the alignItems is Baseline and justifyContent is SpaceEvenly.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest009, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_EVENLY);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::BASELINE);
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
        Flex({direction: FlexDirection.Row, ItemAlign.Baseline, justifyContent: FlexAlign.SpaceEvenly}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
    for (int32_t i = START_INDEX; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(childOffset, OffsetF(i * TWENTY_PERCENT_WIDTH + (i + 1) * horizontalRemaining, 0.0f));
    }
}

/**
 * @tc.name: FlexRowLayoutTest010
 * @tc.desc: Set three texts with size in row and check the alignItems is Start and justifyContent is SpaceAround.
 * @tc.type: FUNC
 */
HWTEST_F(FlexLayoutTestNg, FlexRowLayoutTest010, TestSize.Level1)
{
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);
    rowLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    rowLayoutProperty->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    rowLayoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
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
        Flex({direction: FlexDirection.Row, ItemAlign.Start, justifyContent: FlexAlign.SpaceAround}) {
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
        RefPtr<LayoutWrapper> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapper>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
    EXPECT_EQ(firstChildSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildOffset, OffsetF(horizontalRemaining / 2, 0.0f));
    for (int32_t i = START_INDEX + 1; i < THREE_ITEM_SIZE; i++) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(i);
        auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
        auto childOffset = childWrapper->GetGeometryNode()->GetFrameOffset();
        EXPECT_EQ(childSize, SizeF(TWENTY_PERCENT_WIDTH, SMALL_ITEM_HEIGHT));
        EXPECT_EQ(
            childOffset, OffsetF(horizontalRemaining / 2 + i * (TWENTY_PERCENT_WIDTH + horizontalRemaining), 0.0f));
    }
}

} // namespace OHOS::Ace::NG
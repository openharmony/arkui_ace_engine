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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_styles.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float FULL_SCREEN_WIDTH = 720.0f;
const float FULL_SCREEN_HEIGHT = 1136.0f;
const float ZERO = 0.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const float ROW_HEIGHT = 120.0f;

const float SMALL_ITEM_WIDTH = 150.0f;
const float SMALL_ITEM_HEIGHT = 60.0f;
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);

const float LARGE_ITEM_WIDTH = 200.0f;
const float LARGE_ITEM_HEIGHT = 100.0f;

const float HALF = 2.0f;
const SizeF LARGE_ITEM_SIZE(LARGE_ITEM_WIDTH, LARGE_ITEM_HEIGHT);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

const std::string EMPTY_STRING;

} // namespace

class LinearLayoutTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void LinearLayoutTestNg::SetUp() {}

void LinearLayoutTestNg::TearDown() {}

PaddingProperty CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

/**
 * @tc.name: LinearRowLayoutTest001
 * @tc.desc: Layout items in row linear algorithm
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest001, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
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
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::FLEX_START);

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearColumnLayoutTest001
 * @tc.desc: Layout items in column linear algorithm
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest001, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_FALSE(rowLayoutPattern == nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(rowLayoutProperty == nullptr);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding;
    noPadding.left = CalcLength(ZERO);
    noPadding.right = CalcLength(ZERO);
    noPadding.top = CalcLength(ZERO);
    noPadding.bottom = CalcLength(ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Column() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
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
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::FLEX_START);

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: LinearRowLayoutTest001
 * @tc.desc: Layout items in row linear algorithm with FlexAlign::End main alignment
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest002, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.End)
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::FLEX_END);

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - LARGE_ITEM_WIDTH - SMALL_ITEM_WIDTH, ZERO));

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(
        secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(FULL_SCREEN_WIDTH - LARGE_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest003
 * @tc.desc: Layout items in row linear algorithm with FlexAlign::Center main alignment
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest003, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::CENTER);

    auto rowStartOffset = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / HALF;
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(rowStartOffset, ZERO));

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(
        secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(rowStartOffset + SMALL_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest004
 * @tc.desc: Layout items in row linear algorithm with FlexAlign::SpaceBetween main alignment
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest004, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_BETWEEN);

    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    auto spaceBetween = FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH;
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH + spaceBetween, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest005
 * @tc.desc: Layout items in row linear algorithm with FlexAlign::SpaceAround main alignment
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest005, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceAround)
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_AROUND);

    // for two items, space between is (totalWidth - itemWidthSum) / 2.0f, and start position is spaceBetween / 2.0f
    auto spaceBetween = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / HALF;
    auto rowStartPosition = spaceBetween / HALF;
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(rowStartPosition, ZERO));

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - rowStartPosition - LARGE_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest006
 * @tc.desc: Layout items in row linear algorithm with FlexAlign::SpaceEvenly main alignment
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest006, TestSize.Level1)
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

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xF5DEB3)
            .textAlign(TextAlign.Center)
          Blank()
            .width(100)
            .height(40)
            .backgroundColor(0xD2B48C)
            .textAlign(TextAlign.Center)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
        .backgroundColor(0xAFEEEE)
    */
    // create first child node and wrapper
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

    // create second child node and wrapper
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    secondLayoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    rowFrameNode->AddChild(secondFrameNode);
    layoutWrapper->AppendChild(secondLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(layoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(layoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_EVENLY);

    // for two items, space between is (totalWidth - itemWidthSum) / 3, and start position is spaceBetween / 2.0f
    auto itemCount = HALF + 1;
    auto spaceBetween = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / itemCount;
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(spaceBetween, ZERO));

    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - spaceBetween - LARGE_ITEM_WIDTH, ZERO));
}

} // namespace OHOS::Ace::NG
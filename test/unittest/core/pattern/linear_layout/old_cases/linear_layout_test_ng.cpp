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

#define private public
#define protected public

#include "bridge/declarative_frontend/view_stack_processor.h"
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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO = 0.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
constexpr float ROW_HEIGHT = 120.0f;
constexpr float COLUMN_HEIGHT = 200.0f;

constexpr float SMALL_ITEM_WIDTH = 100.0f;
constexpr float SMALL_ITEM_HEIGHT = 40.0f;
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);

constexpr float LARGE_ITEM_WIDTH = 200.0f;
constexpr float LARGE_ITEM_HEIGHT = 100.0f;

constexpr float HALF = 2.0f;
const SizeF LARGE_ITEM_SIZE(LARGE_ITEM_WIDTH, LARGE_ITEM_HEIGHT);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::string EMPTY_STRING;
const std::string EMPTY_TAG;
constexpr Dimension SPACE_NEGATIVE(-1);
constexpr Dimension SPACE_ONE(1);
constexpr int32_t MIRROR_FRAME_OFFSET_X = 620;
constexpr int32_t MIRROR_FRAME_OFFSET_Y_ZERO = 0;
} // namespace
class LinearLayoutTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateRow();
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateColumn();
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateSmallChild(
        const LayoutConstraintF& childLayoutConstraint);
    std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateLargeChild(
        const LayoutConstraintF& childLayoutConstraint);

    PaddingProperty CreatePadding(float left, float top, float right, float bottom);
};

void LinearLayoutTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void LinearLayoutTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> LinearLayoutTestNg::CreateRow()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowFrameNode =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(rowFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(rowLayoutPattern, nullptr);
    auto rowLayoutProperty = rowLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(ROW_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    return { rowFrameNode, layoutWrapper };
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> LinearLayoutTestNg::CreateColumn()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(columnFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

    auto columnLayoutPattern = columnFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(columnLayoutPattern, nullptr);
    auto rowLayoutProperty = columnLayoutPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(COLUMN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    return { columnFrameNode, layoutWrapper };
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> LinearLayoutTestNg::CreateSmallChild(
    const LayoutConstraintF& childLayoutConstraint)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, firstGeometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SMALL_ITEM_WIDTH), CalcLength(SMALL_ITEM_HEIGHT)));
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_NE(pattern, nullptr);

    auto boxLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(boxLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    return { frameNode, layoutWrapper };
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> LinearLayoutTestNg::CreateLargeChild(
    const LayoutConstraintF& childLayoutConstraint)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, firstGeometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LARGE_ITEM_WIDTH), CalcLength(LARGE_ITEM_HEIGHT)));
    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    auto pattern = frameNode->GetPattern<Pattern>();
    EXPECT_NE(pattern, nullptr);
    auto boxLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(boxLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    return { frameNode, layoutWrapper };
}

PaddingProperty LinearLayoutTestNg::CreatePadding(float left, float top, float right, float bottom)
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
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::Start(default)
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest001, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(100)
            .height(40)
        }.height(80)
        .width('100%')
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateSmallChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::FLEX_START);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest002
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::End
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest002, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(200)
            .height(100)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.End)
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    // update firstChild layoutWeight
    auto layoutProp = firstChildFrameNode->GetLayoutProperty();
    EXPECT_NE(layoutProp, nullptr);
    layoutProp->UpdateLayoutWeight(1);

    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::FLEX_END);

    auto leftSpaceExpectSecondChild = FULL_SCREEN_WIDTH - LARGE_ITEM_WIDTH;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(),
        SizeF(leftSpaceExpectSecondChild, SMALL_ITEM_HEIGHT));
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - LARGE_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest003
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::Center
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest003, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(200)
            .height(100)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.Center)
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::CENTER);

    auto rowStartOffset = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / HALF;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(rowStartOffset, ZERO));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(rowStartOffset + SMALL_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest004
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::SpaceBetween
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest004, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(200)
            .height(100)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceBetween)
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_BETWEEN);

    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    auto spaceBetween = FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH;
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(
        secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH + spaceBetween, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest005
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::SpaceAround
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest005, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(200)
            .height(100)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceAround)
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_AROUND);

    // for two items, space between is (totalWidth - itemWidthSum) / 2.0f, and start position is spaceBetween / 2.0f
    auto spaceBetween = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / HALF;
    auto rowStartPosition = spaceBetween / HALF;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(rowStartPosition, ZERO));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - rowStartPosition - LARGE_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest006
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::SpaceEvenly
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest006, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(200)
            .height(100)
        }.height(80)
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_START, FlexAlign::SPACE_EVENLY);

    // for two items, space between is (totalWidth - itemWidthSum) / 3, and start position is spaceBetween / 2.0f
    auto itemCount = HALF + 1;
    auto spaceBetween = (FULL_SCREEN_WIDTH - SMALL_ITEM_WIDTH - LARGE_ITEM_WIDTH) / itemCount;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(spaceBetween, ZERO));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FULL_SCREEN_WIDTH - spaceBetween - LARGE_ITEM_WIDTH, ZERO));
}

/**
 * @tc.name: LinearRowLayoutTest007
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::Start(default) and cross alignment
 * FlexAlign::End FlexAlign::End
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest007, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(100)
            .height(40)
        }.height(80)
        .width('100%')
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateSmallChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::FLEX_END, FlexAlign::FLEX_START);

    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    auto firstChildOffsetY = ROW_HEIGHT - SMALL_ITEM_HEIGHT;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, firstChildOffsetY));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(
        secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH, firstChildOffsetY));
}

/**
 * @tc.name: LinearRowLayoutTest008
 * @tc.desc: Layout items in row linear algorithm with main alignment FlexAlign::Start(default) and cross alignment
 * FlexAlign::Center FlexAlign::End
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowLayoutTest008, TestSize.Level0)
{
    auto row = CreateRow();
    auto rowFrameNode = row.first;
    auto rowLayoutWrapper = row.second;

    auto childLayoutConstraint = rowLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Row() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(100)
            .height(40)
        }.height(80)
        .width('100%')
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    rowFrameNode->AddChild(firstChildFrameNode);
    rowLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateSmallChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    rowFrameNode->AddChild(secondChildFrameNode);
    rowLayoutWrapper->AppendChild(secondChildLayoutWrapper);

    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(rowLayoutWrapper), false);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(rowLayoutWrapper), false, FlexAlign::CENTER, FlexAlign::FLEX_START);

    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    auto firstChildOffsetY = (ROW_HEIGHT - SMALL_ITEM_HEIGHT) / HALF;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, firstChildOffsetY));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(
        secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(SMALL_ITEM_WIDTH, firstChildOffsetY));
}

/**
 * @tc.name: LinearColumnLayoutTest001
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::Start(default)
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest001, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
        Column() {
          Blank()
            .width(100)
            .height(40)
          Blank()
            .width(100)
            .height(40)
        }.height(80)
        .width('100%')
    */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateSmallChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::FLEX_START);

    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: LinearColumnLayoutTest002
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::Center
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest002, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
         Blank()
           .width(200)
           .height(100)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::CENTER);

    auto columnStartOffset = (COLUMN_HEIGHT - SMALL_ITEM_HEIGHT - LARGE_ITEM_HEIGHT) / HALF;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, columnStartOffset));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(ZERO, columnStartOffset + SMALL_ITEM_HEIGHT));
}

/**
 * @tc.name: LinearColumnLayoutTest003
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::End
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest003, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
         Blank()
           .width(200)
           .height(100)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    // update firstChild layoutWeight
    auto layoutProp = firstChildFrameNode->GetLayoutProperty();
    EXPECT_NE(layoutProp, nullptr);
    layoutProp->UpdateLayoutWeight(1);
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::FLEX_END);

    auto leftSpaceExpectSecondChild = COLUMN_HEIGHT - LARGE_ITEM_HEIGHT;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(),
        SizeF(SMALL_ITEM_WIDTH, leftSpaceExpectSecondChild));
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(ZERO, COLUMN_HEIGHT - leftSpaceExpectSecondChild));
}

/**
 * @tc.name: LinearColumnLayoutTest004
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::SpaceBetween
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest004, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
         Blank()
           .width(200)
           .height(100)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::SPACE_BETWEEN);

    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    auto spaceBetween = COLUMN_HEIGHT - SMALL_ITEM_HEIGHT - LARGE_ITEM_HEIGHT;
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(
        secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, SMALL_ITEM_HEIGHT + spaceBetween));
}

/**
 * @tc.name: LinearColumnLayoutTest005
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::SpaceAround
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest005, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
         Blank()
           .width(200)
           .height(100)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::SPACE_AROUND);

    // for two items, space between is (totalWidth - itemWidthSum) / 2.0f, and start position is spaceBetween / 2.0f
    auto spaceBetween = (COLUMN_HEIGHT - SMALL_ITEM_HEIGHT - LARGE_ITEM_HEIGHT) / HALF;
    auto columnStartPosition = spaceBetween / HALF;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, columnStartPosition));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(ZERO, COLUMN_HEIGHT - columnStartPosition - LARGE_ITEM_HEIGHT));
}

/**
 * @tc.name: LinearColumnLayoutTest006
 * @tc.desc: Layout items in column linear algorithm with main alignment FlexAlign::SpaceEvenly
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest006, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
         Blank()
           .width(200)
           .height(100)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);

    // create second child node and wrapper
    auto secondChild = CreateLargeChild(childLayoutConstraint);
    auto secondChildFrameNode = secondChild.first;
    auto secondChildLayoutWrapper = secondChild.second;
    columnFrameNode->AddChild(secondChildFrameNode);
    columnLayoutWrapper->AppendChild(secondChildLayoutWrapper);
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::SPACE_EVENLY);

    // for two items, space between is (totalWidth - itemWidthSum) / 3, and start position is spaceBetween / 2.0f
    auto itemCount = HALF + 1;
    auto spaceBetween = (COLUMN_HEIGHT - SMALL_ITEM_HEIGHT - LARGE_ITEM_HEIGHT) / itemCount;
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, spaceBetween));

    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), LARGE_ITEM_SIZE);
    EXPECT_EQ(secondChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(ZERO, COLUMN_HEIGHT - spaceBetween - LARGE_ITEM_HEIGHT));
}

/**
 * @tc.name: LinearColumnLayoutTest007
 * @tc.desc: Layout items in column linear algorithm with RightToLeft
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnLayoutTest007, TestSize.Level0)
{
    auto column = CreateColumn();
    auto columnFrameNode = column.first;
    auto columnLayoutWrapper = column.second;

    auto childLayoutConstraint = columnLayoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
    /* corresponding ets code:
       Column() {
         Blank()
           .width(100)
           .height(40)
       }.height(80)
       .width('100%')
   */
    // create first child node and wrapper
    auto firstChild = CreateSmallChild(childLayoutConstraint);
    auto firstChildFrameNode = firstChild.first;
    auto firstChildLayoutWrapper = firstChild.second;
    columnFrameNode->AddChild(firstChildFrameNode);
    columnLayoutWrapper->AppendChild(firstChildLayoutWrapper);
    // isRightToLeft is false
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::SPACE_BETWEEN);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));

    // isRightToLeft is true
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    LinearLayoutUtils::Measure(AccessibilityManager::RawPtr(columnLayoutWrapper), true);
    LinearLayoutUtils::Layout(
        AccessibilityManager::RawPtr(columnLayoutWrapper), true, FlexAlign::FLEX_START, FlexAlign::SPACE_BETWEEN);
    EXPECT_EQ(firstChildLayoutWrapper->GetGeometryNode()->GetFrameSize(), SMALL_ITEM_SIZE);
    auto offsetVal = firstChildLayoutWrapper->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(offsetVal.GetX(), MIRROR_FRAME_OFFSET_X);
    EXPECT_EQ(offsetVal.GetY(), MIRROR_FRAME_OFFSET_Y_ZERO);
}

/**
 * @tc.name: LinearRowCreatorTest001
 * @tc.desc: Test create row without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowCreatorTest001, TestSize.Level0)
{
    RowModelNG instance;
    instance.Create(SPACE_NEGATIVE, nullptr, EMPTY_TAG);
    instance.SetAlignItems(FlexAlign::FLEX_START);
    instance.SetJustifyContent(FlexAlign::FLEX_END);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), false);
    EXPECT_EQ(space->ConvertToPx(), 0);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlign(), FlexAlign::FLEX_START);
    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_END);
}

/**
 * @tc.name: LinearRowCreatorTest002
 * @tc.desc: Test create row with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearRowCreatorTest002, TestSize.Level0)
{
    RowModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);
    EXPECT_EQ(rowFrameNode->GetTag(), V2::ROW_ETS_TAG);
    auto layoutProperty = rowFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::ROW);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), true);
    EXPECT_EQ(space.value(), SPACE_ONE);
}

/**
 * @tc.name: LinearColumnCreatorTest001
 * @tc.desc: Test create column without space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnCreatorTest001, TestSize.Level0)
{
    ColumnModelNG instance;
    instance.Create(SPACE_NEGATIVE, nullptr, EMPTY_TAG);
    instance.SetAlignItems(FlexAlign::FLEX_END);
    instance.SetJustifyContent(FlexAlign::FLEX_START);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(columnFrameNode, nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), false);
    EXPECT_EQ(space->ConvertToPx(), 0);
    EXPECT_EQ(layoutProperty->GetCrossAxisAlign(), FlexAlign::FLEX_END);
    EXPECT_EQ(layoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_START);
}

/**
 * @tc.name: LinearColumnCreatorTest002
 * @tc.desc: Test create column with space
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearColumnCreatorTest002, TestSize.Level0)
{
    ColumnModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto columnFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(columnFrameNode, nullptr);
    EXPECT_EQ(columnFrameNode->GetTag(), V2::COLUMN_ETS_TAG);
    auto layoutProperty = columnFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    auto direction = layoutProperty->GetFlexDirection();
    EXPECT_EQ(direction.has_value(), true);
    EXPECT_EQ(direction.value(), FlexDirection::COLUMN);
    auto space = layoutProperty->GetSpace();
    EXPECT_EQ(space.has_value(), true);
    EXPECT_EQ(space.value(), SPACE_ONE);
}

/**
 * @tc.name: LinearLayoutPatternTest001
 * @tc.desc: Verify whether the layout property, layoutAlgorithm are created.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutTestNg, LinearLayoutPatternTest001, TestSize.Level0)
{
    RowModelNG instance;
    instance.Create(SPACE_ONE, nullptr, EMPTY_TAG);
    auto rowFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(rowFrameNode, nullptr);

    auto rowPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_NE(rowPattern, nullptr);
    auto rowLayoutProperty = rowPattern->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_NE(rowLayoutProperty, nullptr);
    EXPECT_EQ(rowPattern->isVertical_, false);
}
} // namespace OHOS::Ace::NG
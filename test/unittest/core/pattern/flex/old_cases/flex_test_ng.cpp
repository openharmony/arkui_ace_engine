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
const float OFFSET_TOP = 20.0f;
const float OFFSET_LEFT = 0.0f;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
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
constexpr int32_t FLEX_NODE_ID = 12;
} // namespace
class FlexTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FlexTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void FlexTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

struct WrapProperties {
    WrapDirection wrapDirection = WrapDirection::HORIZONTAL;
    WrapAlignment wrapAlignment = WrapAlignment::START;
    WrapAlignment wrapMainAxisAlignment = WrapAlignment::START;
    WrapAlignment wrapCrossAxisAlignment = WrapAlignment::START;
    Dimension mainSpace = Dimension(20.0, DimensionUnit::VP);
    Dimension crossSpace = Dimension(20.0, DimensionUnit::VP);
};

void UpdateWrapProperties(const RefPtr<FlexLayoutProperty>& layoutProperty, const WrapProperties& wrapProperty)
{
    EXPECT_EQ(layoutProperty == nullptr, false);
    layoutProperty->UpdateWrapDirection(wrapProperty.wrapDirection);
    layoutProperty->UpdateAlignment(wrapProperty.wrapAlignment);
    layoutProperty->UpdateMainAlignment(wrapProperty.wrapMainAxisAlignment);
    layoutProperty->UpdateCrossAlignment(wrapProperty.wrapCrossAxisAlignment);
    layoutProperty->UpdateSpace(wrapProperty.mainSpace);
    layoutProperty->UpdateCrossSpace(wrapProperty.crossSpace);
}

struct FlexProperties {
    FlexDirection flexDirection = FlexDirection::ROW;
    FlexAlign flexAlign = FlexAlign::FLEX_START;
};

void UpdateFlexProperties(const RefPtr<FlexLayoutProperty>& layoutProperty, const FlexProperties& flexProperty)
{
    EXPECT_FALSE(layoutProperty == nullptr);
    layoutProperty->UpdateFlexDirection(flexProperty.flexDirection);
    layoutProperty->UpdateMainAxisAlign(flexProperty.flexAlign);
    layoutProperty->UpdateCrossAxisAlign(flexProperty.flexAlign);
}

/**
 * @tc.name: FlexWrapFrameNodeCreator001
 * @tc.desc: Test setting of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapFrameNodeCreator001, TestSize.Level1)
{
    WrapProperties wrapProperty;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, FLEX_NODE_ID, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_EQ(flexLayoutProperty == nullptr, false);
    UpdateWrapProperties(flexLayoutProperty, wrapProperty);
    EXPECT_EQ(flexLayoutProperty->GetWrapDirectionValue(WrapDirection::HORIZONTAL) == wrapProperty.wrapDirection, true);
    EXPECT_EQ(flexLayoutProperty->GetAlignmentValue(WrapAlignment::START) == wrapProperty.wrapAlignment, true);
    EXPECT_EQ(
        flexLayoutProperty->GetMainAlignmentValue(WrapAlignment::START) == wrapProperty.wrapMainAxisAlignment, true);
    EXPECT_EQ(
        flexLayoutProperty->GetCrossAlignmentValue(WrapAlignment::START) == wrapProperty.wrapCrossAxisAlignment, true);
    EXPECT_EQ(flexLayoutProperty->GetSpaceValue({}).Value() == wrapProperty.mainSpace.Value(), true);
    EXPECT_EQ(flexLayoutProperty->GetCrossSpaceValue({}).Value() == wrapProperty.crossSpace.Value(), true);

    /**
     * @tc.steps: step1. Call CreateFlexGrow.
     * @tc.expected: created successfully
     */
    FlexModelNG instance;
    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = FLEX_NODE_ID;
    instance.CreateFlexRow();
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(!pattern->GetIsWrap());
}
/**
 * @tc.name: FlexRowFrameNodeCreator001
 * @tc.desc: Test setting of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexRowFrameNodeCreator001, TestSize.Level1)
{
    FlexProperties flexProperty;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, FLEX_NODE_ID, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_EQ(flexLayoutProperty == nullptr, false);
    UpdateFlexProperties(flexLayoutProperty, flexProperty);

    /**
     * @tc.steps: step1. Call CreateFlexGrow.
     * @tc.expected: created successfully
     */
    FlexModelNG instance;
    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = FLEX_NODE_ID;
    instance.CreateFlexRow();
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(!pattern->GetIsWrap());
}
/**
 * @tc.name: FlexWrapFrameNodeCreator003
 * @tc.desc: Test flexRowNode exiting normally.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapFrameNodeCreator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare flexNode.
     */
    FlexProperties flexProperty;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, FLEX_NODE_ID, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_EQ(flexLayoutProperty == nullptr, false);
    UpdateFlexProperties(flexLayoutProperty, flexProperty);

    /**
     * @tc.steps: step2. Call CreateWrap.
     * @tc.expected: exited successfully
     */
    FlexModelNG instance;
    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = FLEX_NODE_ID;
    instance.CreateWrap();
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(pattern->GetIsWrap());
}

/**
 * @tc.name: FlexWrapFrameNodeCreator004
 * @tc.desc: Test flexWrapNode pushed successfully.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapFrameNodeCreator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare flexNode.
     */
    WrapProperties wrapProperty;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, FLEX_NODE_ID, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_EQ(flexLayoutProperty == nullptr, false);
    UpdateWrapProperties(flexLayoutProperty, wrapProperty);

    /**
     * @tc.steps: step2. Call CreateWrap.
     * @tc.expected: pushed successfully
     */
    FlexModelNG instance;
    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = FLEX_NODE_ID;
    instance.CreateWrap();
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(pattern->GetIsWrap());
}

/**
 * @tc.name: FlexWrapFrameNodeCreator002
 * @tc.desc: Test creating flex then switch to wrap.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapFrameNodeCreator002, TestSize.Level1)
{
    FlexModelNG instance;
    // create a regular flex
    instance.CreateFlexRow();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode == nullptr);
    auto pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(!pattern->GetIsWrap());
    auto flexId = frameNode->GetId();
    instance.SetDirection(FlexDirection::COLUMN);
    instance.SetMainAxisAlign(FlexAlign::FLEX_END);
    instance.SetCrossAxisAlign(FlexAlign::SPACE_AROUND);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_FALSE(flexLayoutProperty == nullptr);
    EXPECT_EQ(flexLayoutProperty->GetFlexDirectionValue(FlexDirection::ROW) == FlexDirection::COLUMN, true);
    EXPECT_EQ(flexLayoutProperty->GetMainAxisAlignValue(FlexAlign::FLEX_START) == FlexAlign::FLEX_END, true);
    EXPECT_EQ(flexLayoutProperty->GetCrossAxisAlignValue(FlexAlign::FLEX_START) == FlexAlign::SPACE_AROUND, true);
    ViewStackProcessor::GetInstance()->Finish();
    instance.CreateWrap();
    frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode == nullptr);
    // after creating wrap, id should be the same and node should use wrap layout algorithm
    EXPECT_EQ(frameNode->GetId(), flexId);
    pattern = frameNode->GetPattern<FlexLayoutPattern>();
    EXPECT_TRUE(pattern->GetIsWrap());
}

/**
 * @tc.name: FlexWrapFrameNodeLayout001
 * @tc.desc: Test layout of flex wrap.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapFrameNodeLayout001, TestSize.Level1)
{
    WrapProperties wrapProperty;
    wrapProperty.wrapDirection = WrapDirection::HORIZONTAL;
    auto flexNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, -1, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    geometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(flexNode, geometryNode, flexNode->GetLayoutProperty());
    EXPECT_FALSE(flexNode == nullptr);
    RefPtr<LayoutProperty> layoutProperty = flexNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);

    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_EQ(flexLayoutProperty == nullptr, false);
    UpdateWrapProperties(flexLayoutProperty, wrapProperty);
    auto flexLayoutPattern = flexNode->GetPattern<FlexLayoutPattern>();
    EXPECT_FALSE(flexLayoutPattern == nullptr);
    auto flexLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(flexLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    // create first item
    auto firstItem =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, -1, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    // add first item to flex
    flexNode->AddChild(firstItem);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstItem, firstGeometryNode, firstItem->GetLayoutProperty());
    EXPECT_FALSE(firstLayoutWrapper == nullptr);
    auto firstItemPattern = firstItem->GetPattern<ButtonPattern>();
    EXPECT_FALSE(firstItemPattern == nullptr);
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto firstItemLayoutAlgorithm = firstItemPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(firstItemLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(firstItemLayoutAlgorithm));
    firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(firstLayoutWrapper);

    // mock process in flex layout algorithm
    flexLayoutAlgorithm->Measure(&layoutWrapper);
    flexLayoutAlgorithm->Layout(&layoutWrapper);
    auto firstItemGeometryNode = firstLayoutWrapper->GetGeometryNode();
    EXPECT_FALSE(firstItemGeometryNode == nullptr);
    auto firstItemOffset = firstGeometryNode->GetFrameOffset();
    EXPECT_EQ(firstItemOffset.GetX(), OFFSET_LEFT);
    EXPECT_EQ(firstItemOffset.GetY(), OFFSET_TOP);
}

/**
 * @tc.name: FlexPatternTest001
 * @tc.desc: Test properties set of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexPatternTest001, TestSize.Level1)
{
    FlexProperties flexProperty;
    FlexModelNG flexModelNG;
    flexModelNG.CreateFlexRow();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_FALSE(flexLayoutProperty == nullptr);

    UpdateFlexProperties(flexLayoutProperty, flexProperty);
    EXPECT_EQ(flexLayoutProperty->GetFlexDirection(), flexProperty.flexDirection);
    EXPECT_EQ(flexLayoutProperty->GetMainAxisAlign(), flexProperty.flexAlign);
    EXPECT_EQ(flexLayoutProperty->GetCrossAxisAlign(), flexProperty.flexAlign);
}

/**
 * @tc.name: FlexPatternTest002
 * @tc.desc: Test properties set of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexPatternTest002, TestSize.Level1)
{
    FlexModelNG flexModelNG;
    flexModelNG.CreateFlexRow();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_FALSE(flexLayoutProperty == nullptr);

    flexModelNG.SetDirection(FlexDirection::ROW);
    flexModelNG.SetMainAxisAlign(FlexAlign::FLEX_START);
    flexModelNG.SetCrossAxisAlign(FlexAlign::FLEX_START);
    EXPECT_EQ(flexLayoutProperty->GetFlexDirection(), FlexDirection::ROW);
    EXPECT_EQ(flexLayoutProperty->GetMainAxisAlign(), FlexAlign::FLEX_START);
    EXPECT_EQ(flexLayoutProperty->GetCrossAxisAlign(), FlexAlign::FLEX_START);

    int32_t value = 2;
    flexModelNG.SetJustifyContent(value);
    flexModelNG.SetAlignItems(value);
    flexModelNG.SetAlignContent(value);
    EXPECT_EQ(flexLayoutProperty->GetMainAxisAlign(), static_cast<FlexAlign>(value));
    EXPECT_EQ(flexLayoutProperty->GetCrossAxisAlign(), static_cast<FlexAlign>(value));
}

/**
 * @tc.name: FlexWrapPatternTest002
 * @tc.desc: Test properties set of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexWrapPatternTest002, TestSize.Level1)
{
    FlexModelNG flexModelNG;
    flexModelNG.CreateWrap();
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_FALSE(flexLayoutProperty == nullptr);

    flexModelNG.SetWrapDirection(WrapDirection::HORIZONTAL);
    flexModelNG.SetWrapMainAlignment(WrapAlignment::START);
    flexModelNG.SetWrapCrossAlignment(WrapAlignment::START);
    flexModelNG.SetWrapAlignment(WrapAlignment::START);
    flexModelNG.SetMainSpace(Dimension(20.0, DimensionUnit::VP));
    flexModelNG.SetCrossSpace(Dimension(20.0, DimensionUnit::VP));
    EXPECT_EQ(flexLayoutProperty->GetWrapDirection(), WrapDirection::HORIZONTAL);
    EXPECT_EQ(flexLayoutProperty->GetMainAlignment(), WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetCrossAlignment(), WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetAlignment(), WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetSpaceValue({}).Value(), 20.0);
    EXPECT_EQ(flexLayoutProperty->GetCrossSpaceValue({}).Value(), 20.0);

    int32_t value = 1;
    flexModelNG.SetJustifyContent(value);
    flexModelNG.SetAlignItems(value);
    flexModelNG.SetAlignContent(value);
    EXPECT_EQ(flexLayoutProperty->GetMainAlignment(), WrapAlignment::CENTER);
    EXPECT_EQ(flexLayoutProperty->GetCrossAlignment(), WrapAlignment::CENTER);
    EXPECT_EQ(flexLayoutProperty->GetAlignment(), WrapAlignment::CENTER);
}

/**
 * @tc.name: FlexRowLayoutTest001
 * @tc.desc: Set two texts with size in row and check them.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexRowLayoutTest001, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest002, TestSize.Level1)
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
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest003, TestSize.Level1)
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
HWTEST_F(FlexTestNg, FlexColumnLayoutTest001, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
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
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
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
HWTEST_F(FlexTestNg, FlexColumnLayoutTest002, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
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
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
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
HWTEST_F(FlexTestNg, FlexColumnLayoutTest003, TestSize.Level1)
{
    auto columnFrameNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(columnFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnFrameNode, geometryNode, columnFrameNode->GetLayoutProperty());

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
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(itemFrameNode, itemGeometryNode, itemFrameNode->GetLayoutProperty());
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest005, TestSize.Level1)
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest006, TestSize.Level1)
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest007, TestSize.Level1)
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest008, TestSize.Level1)
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
        EXPECT_EQ(childOffset, OffsetF(i * (TWENTY_PERCENT_WIDTH + horizontalRemaining / 2), 0.0f));
    }
}

/**
 * @tc.name: FlexRowLayoutTest009
 * @tc.desc: Set three texts with size in row and check the alignItems is Baseline and justifyContent is SpaceEvenly.
 * @tc.type: FUNC
 */
HWTEST_F(FlexTestNg, FlexRowLayoutTest009, TestSize.Level1)
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
HWTEST_F(FlexTestNg, FlexRowLayoutTest010, TestSize.Level1)
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

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
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
} // namespace
class FlexPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

struct WrapProperties {
    WrapDirection wrapDirection = WrapDirection::HORIZONTAL;
    WrapAlignment wrapAlignment = WrapAlignment::START;
    WrapAlignment wrapMainAxisAlignment = WrapAlignment::START;
    WrapAlignment wrapCrossAxisAlignment = WrapAlignment::START;
};

void UpdateWrapProperties(const RefPtr<FlexLayoutProperty>& layoutProperty, const WrapProperties& wrapProperty)
{
    EXPECT_EQ(layoutProperty == nullptr, false);
    layoutProperty->UpdateWrapDirection(wrapProperty.wrapDirection);
    layoutProperty->UpdateAlignment(wrapProperty.wrapAlignment);
    layoutProperty->UpdateMainAlignment(wrapProperty.wrapMainAxisAlignment);
    layoutProperty->UpdateCrossAlignment(wrapProperty.wrapCrossAxisAlignment);
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
HWTEST_F(FlexPatternTestNg, FlexWrapFrameNodeCreator001, TestSize.Level1)
{
    WrapProperties wrapProperty;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, -1, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
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
}

/**
 * @tc.name: FlexWrapFrameNodeCreator002
 * @tc.desc: Test creating flex then switch to wrap.
 * @tc.type: FUNC
 */
HWTEST_F(FlexPatternTestNg, FlexWrapFrameNodeCreator002, TestSize.Level1)
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
HWTEST_F(FlexPatternTestNg, FlexWrapFrameNodeLayout001, TestSize.Level1)
{
    WrapProperties wrapProperty;
    wrapProperty.wrapDirection = WrapDirection::HORIZONTAL;
    auto flexNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, -1, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(true); });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    LayoutWrapper layoutWrapper = LayoutWrapper(flexNode, geometryNode, flexNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapper> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstItem, firstGeometryNode, firstItem->GetLayoutProperty());
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
}

/**
 * @tc.name: FlexPatternTest001
 * @tc.desc: Test properties set of flex.
 * @tc.type: FUNC
 */
HWTEST_F(FlexPatternTestNg, FlexPatternTest001, TestSize.Level1)
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
HWTEST_F(FlexPatternTestNg, FlexPatternTest002, TestSize.Level1)
{
    FlexModelNG flexModelNG;
    flexModelNG.CreateFlexRow();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
HWTEST_F(FlexPatternTestNg, FlexWrapPatternTest002, TestSize.Level1)
{
    FlexModelNG flexModelNG;
    flexModelNG.CreateWrap();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    RefPtr<FlexLayoutProperty> flexLayoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutProperty);
    EXPECT_FALSE(flexLayoutProperty == nullptr);

    flexModelNG.SetWrapDirection(WrapDirection::HORIZONTAL);
    flexModelNG.SetWrapMainAlignment(WrapAlignment::START);
    flexModelNG.SetWrapCrossAlignment(WrapAlignment::START);
    flexModelNG.SetWrapAlignment(WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetWrapDirection(), WrapDirection::HORIZONTAL);
    EXPECT_EQ(flexLayoutProperty->GetMainAlignment(), WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetCrossAlignment(), WrapAlignment::START);
    EXPECT_EQ(flexLayoutProperty->GetAlignment(), WrapAlignment::START);

    int32_t value = 1;
    flexModelNG.SetJustifyContent(value);
    flexModelNG.SetAlignItems(value);
    flexModelNG.SetAlignContent(value);
    EXPECT_EQ(flexLayoutProperty->GetMainAlignment(), WrapAlignment::CENTER);
    EXPECT_EQ(flexLayoutProperty->GetCrossAlignment(), WrapAlignment::CENTER);
    EXPECT_EQ(flexLayoutProperty->GetAlignment(), WrapAlignment::CENTER);
}

} // namespace OHOS::Ace::NG

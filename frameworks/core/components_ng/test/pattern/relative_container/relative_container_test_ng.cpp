/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_view.h"
#include "core/components_ng/test/pattern/relative_container/relative_container_common_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float ZERO = 0.0f;

const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;

const float THIRD_ITEM_WIDTH = 225.0f;
const float THIRD_ITEM_HEIGHT = 75.0f;

const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const SizeF THIRD_ITEM_SIZE(THIRD_ITEM_WIDTH, THIRD_ITEM_HEIGHT);

const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
const OffsetF OFFSET_TOP_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, ZERO);
const OffsetF OFFSET_TOP_RIGHT = OffsetF(CONTAINER_WIDTH, ZERO);

const OffsetF OFFSET_CENTER_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f);
const OffsetF OFFSET_CENTER_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT / 2.0f);

const OffsetF OFFSET_BOTTOM_LEFT = OffsetF(ZERO, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_MIDDLE = OffsetF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT);
const OffsetF OFFSET_BOTTOM_RIGHT = OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT);

const std::string FIRST_ITEM_ID = "bt1";
const std::string SECOND_ITEM_ID = "bt2";
const std::string THIRD_ITEM_ID = "bt3";
const std::string FOURTH_ITEM_ID = "bt4";
const std::string FIFTH_ITEM_ID = "bt5";
const std::string CONTAINER_ID = "__container__";
} // namespace

class RelativeContainerTestNg : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineBase::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineBase::TearDown();
    }
};

/**
 * @tc.name: RelativeContainerPropertyTest001
 * @tc.desc: Add first item--Bottom1 with alignrules value into RelativeContainer and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerPatternTest001, TestSize.Level1)
{
    RelativeContainerView::Create();
    auto relativeContainerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    auto relativeContainerLayoutProperty = relativeContainerFrameNode->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    auto relativeContainerLayoutWrapper = relativeContainerFrameNode->CreateLayoutWrapper();
    EXPECT_FALSE(relativeContainerLayoutWrapper == nullptr);

    /**
    corresponding ets code:
       RelativeContainer() {
            Button("Button 1")
              .alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Start }
              }).id("bt1").borderWidth(1).borderColor(Color.Black)
            }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItem = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::ButtonPattern>(); });
    const auto& firstItemFlexProperty = firstItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstItemAlignRules);
    firstItem->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    relativeContainerFrameNode->AddChild(firstItem);
    EXPECT_EQ(firstItemFlexProperty->GetAlignRulesValue(), firstItemAlignRules);
}

/**
 * @tc.name: RelativeContainerLayoutTest001
 * @tc.desc: Set an item with align rules with RelativeContainer and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest001, TestSize.Level1)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
        RelativeContainer() {
            Button("Button 1")
            .alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Center },
                right:{ anchor: "__container__", align: HorizontalAlign.End },
                top: { anchor: "__container__", align: VerticalAlign.Center },
                bottom: { anchor: "__container__", align: VerticalAlign.Bottom }
            }).id("bt1").borderWidth(1).borderColor(Color.Black)
        }.width(200).height(200)
    .backgroundColor(Color.Orange)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& firstFlexProperty = firstLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> firstAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::CENTER, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::TOP, VerticalAlign::CENTER, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstAlignRules);
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(firstFlexProperty->GetAlignRulesValue(), firstAlignRules);
    EXPECT_EQ(
        firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_CENTER_MIDDLE);
}

/**
 * @tc.name: RelativeContainerLayoutTest002
 * @tc.desc: Set two item with align rules with RelativeContainer and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest002, TestSize.Level1)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
        RelativeContainer() {
            Button("Button 1")
            .alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Start },
                right:{ anchor: "__container__", align: HorizontalAlign.Center },
                top: { anchor: "__container__", align: VerticalAlign.Top },
                bottom: { anchor: "__container__", align: VerticalAlign.Center }
            }).id("bt1").borderWidth(1).borderColor(Color.Black)
            Button("Button 2").width(100).height(50)
            .alignRules({
                left: { anchor: "bt1", align: HorizontalAlign.End },
                right:{ anchor: "__container__", align: HorizontalAlign.End },
                top: { anchor: "bt1", align: VerticalAlign.Bottom },
                bottom: { anchor: "__container__", align: VerticalAlign.Bottom }
            }).id("bt2").borderWidth(1).borderColor(Color.Black)
        }.width(200).height(200)
    .backgroundColor(Color.Orange)
    */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& firstFlexProperty = firstLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> firstAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::CENTER, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::CENTER, firstAlignRules);
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
                        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& secondFlexProperty = secondLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, secondAlignRules);
    secondFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondFrameNode->GetLayoutProperty()->UpdateAlignRules(secondAlignRules);
    relativeContainerFrameNode->AddChild(secondFrameNode);
    layoutWrapper.AppendChild(secondLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(firstFlexProperty->GetAlignRulesValue(), firstAlignRules);
    EXPECT_EQ(secondFlexProperty->GetAlignRulesValue(), secondAlignRules);

    EXPECT_EQ(
        firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(
        secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_WIDTH / 2.0f, CONTAINER_HEIGHT / 2.0f));
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_CENTER_MIDDLE);
}

/**
 * @tc.name: RelativeContainerLayoutTest003
 * @tc.desc: Set five items with different align rules value into RelativeContainer and check .
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest003, TestSize.Level1)
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(CONTAINER_SIZE);
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());

    layoutWrapper.GetGeometryNode()->SetFrameSize(CONTAINER_SIZE);
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = relativeContainerPattern->CreateLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);

    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);

    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
        RelativeContainer() {
            Button("Button 1").width(100).height(50)
              .alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Start }
              }).id("bt1").borderWidth(1).borderColor(Color.Black)
            Button("Button 2").fontSize(20).padding(10)
              .alignRules({
                left:{ anchor: "bt1", align: HorizontalAlign.Start },
                right:{ anchor: "bt1", align: HorizontalAlign.Center },
                bottom: { anchor: "__container__", align: VerticalAlign.Bottom },
                top: { anchor: "bt1", align: VerticalAlign.Bottom }
              }).id("bt2").borderWidth(1).borderColor(Color.Black).height(30)
            Button("Button 3").width(150).height(100)
              .alignRules({
                left: { anchor: "bt1", align: HorizontalAlign.End },
                right:{ anchor: "__container__", align: HorizontalAlign.End },
                top: { anchor: "bt2", align: VerticalAlign.Center },
                bottom: { anchor: "__container__", align: VerticalAlign.Bottom }
              }).id("bt3").borderWidth(1).borderColor(Color.Black)
            Button("Button 4").fontSize(20).padding(10)
              .alignRules({
                left: { anchor: "bt2", align: HorizontalAlign.End },
                middle: {anchor: "__container__", align: HorizontalAlign.Center},
                right:{ anchor: "__container__", align: HorizontalAlign.Center },
                top: { anchor: "bt1", align: VerticalAlign.Bottom }
              }).id("bt4").borderWidth(1).borderColor(Color.Black)
            Button("Button 5")
              .alignRules({
                left: { anchor: "bt1", align: HorizontalAlign.End },
                top: { anchor: "__container__", align: VerticalAlign.Top },
                center: {anchor: "bt1", align: VerticalAlign.Center},
                bottom: { anchor: "bt4", align: VerticalAlign.Bottom }
              }).id("bt5").borderWidth(1).borderColor(Color.Black)
        }.width(200).height(200)
    */

    // Add firstItem-Box1 with size and 1alignRules.
    int32_t firstNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto firstItem = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, firstNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>(); });
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstItem, firstItemGeometryNode, firstItem->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    LayoutConstraintF firstItemLayoutConstraint = childLayoutConstraint;
    firstItemLayoutConstraint.selfIdealSize.SetSize(FIRST_ITEM_SIZE);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(firstItemLayoutConstraint);
    auto boxLayoutAlgorithm = firstItem->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& firstItemFlexProperty = firstItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstItemAlignRules);
    firstItem->UpdateInspectorId(FIRST_ITEM_ID);
    firstItem->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    relativeContainerFrameNode->AddChild(firstItem);
    layoutWrapper.AppendChild(firstItemLayoutWrapper);

    // Add secondItem-Box2 with 4alignRules(2 HorizontalAlign and 2 VerticalAlign).
    int32_t secondNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto secondItem = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, secondNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>(); });
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(secondItem, secondItemGeometryNode, secondItem->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& secondItemFlexProperty = secondItemLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> secondItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::START, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::RIGHT, HorizontalAlign::CENTER, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondItemAlignRules);
    secondItem->UpdateInspectorId(SECOND_ITEM_ID);
    secondItem->GetLayoutProperty()->UpdateAlignRules(secondItemAlignRules);
    relativeContainerFrameNode->AddChild(secondItem);
    layoutWrapper.AppendChild(secondItemLayoutWrapper);

    // Add thirdItem-Box3 with size and 4alignRules(2 HorizontalAlign and 2 VerticalAlign).
    int32_t thirdNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto thirdItem = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, thirdNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>(); });
    RefPtr<GeometryNode> thirdItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> thirdItemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(thirdItem, thirdItemGeometryNode, thirdItem->GetLayoutProperty());
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(THIRD_ITEM_WIDTH), CalcLength(THIRD_ITEM_HEIGHT)));
    thirdItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    thirdItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& thirdItemFlexProperty = thirdItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> thirdItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, thirdItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, thirdItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        SECOND_ITEM_ID, AlignDirection::TOP, VerticalAlign::CENTER, thirdItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, thirdItemAlignRules);
    thirdItem->UpdateInspectorId(THIRD_ITEM_ID);
    thirdItem->GetLayoutProperty()->UpdateAlignRules(thirdItemAlignRules);
    relativeContainerFrameNode->AddChild(thirdItem);
    layoutWrapper.AppendChild(thirdItemLayoutWrapper);

    // Add fourthItem-Box4 with 4alignRules(3 HorizontalAlign and 1 VerticalAlign).
    int32_t fourthNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto fourthItem = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, fourthNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>(); });
    RefPtr<GeometryNode> fourthItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> fourthItemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(fourthItem, fourthItemGeometryNode, fourthItem->GetLayoutProperty());
    fourthItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    fourthItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& fourthItemFlexProperty = fourthItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> fourthItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, fourthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, fourthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::CENTER, fourthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, fourthItemAlignRules);
    fourthItem->UpdateInspectorId(FOURTH_ITEM_ID);
    fourthItem->GetLayoutProperty()->UpdateAlignRules(fourthItemAlignRules);
    relativeContainerFrameNode->AddChild(fourthItem);
    layoutWrapper.AppendChild(fourthItemLayoutWrapper);

    // Add fifthItem-Box5 with 4alignRules(1 HorizontalAlign and 3 VerticalAlign).
    int32_t fifthNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto fifthItem = FrameNode::GetOrCreateFrameNode(
        V2::BLANK_ETS_TAG, fifthNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>(); });
    RefPtr<GeometryNode> fifthItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> fifthItemLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(fifthItem, fifthItemGeometryNode, fifthItem->GetLayoutProperty());
    fifthItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    fifthItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));

    const auto& fifthItemFlexProperty = fifthItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> fifthItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, fifthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, fifthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::CENTER, VerticalAlign::CENTER, fifthItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FOURTH_ITEM_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, fifthItemAlignRules);
    fifthItem->UpdateInspectorId(FIFTH_ITEM_ID);
    fifthItem->GetLayoutProperty()->UpdateAlignRules(fifthItemAlignRules);
    relativeContainerFrameNode->AddChild(fifthItem);
    layoutWrapper.AppendChild(fifthItemLayoutWrapper);

    // check all alignRules in all items.
    EXPECT_EQ(firstItemFlexProperty->GetAlignRulesValue(), firstItemAlignRules);
    EXPECT_EQ(secondItemFlexProperty->GetAlignRulesValue(), secondItemAlignRules);
    EXPECT_EQ(thirdItemFlexProperty->GetAlignRulesValue(), thirdItemAlignRules);
    EXPECT_EQ(fourthItemFlexProperty->GetAlignRulesValue(), fourthItemAlignRules);
    EXPECT_EQ(fifthItemFlexProperty->GetAlignRulesValue(), fifthItemAlignRules);

    // check some size in some items.
    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), FIRST_ITEM_SIZE);
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize(),
        SizeF(FIRST_ITEM_WIDTH / 2.0f, CONTAINER_HEIGHT - FIRST_ITEM_HEIGHT));
    auto thirdItemWidth = CONTAINER_SIZE.Width() - FIRST_ITEM_WIDTH;
    auto thirdItemHeight = (CONTAINER_SIZE.Height() - FIRST_ITEM_HEIGHT) / 2.0f;
    EXPECT_EQ(thirdItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(thirdItemWidth, thirdItemHeight));

    // check offset in all items.
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, FIRST_ITEM_HEIGHT));
    EXPECT_EQ(thirdItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(FIRST_ITEM_WIDTH,
            FIRST_ITEM_HEIGHT + secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize().Height() / 2.0f));
    EXPECT_EQ(fourthItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(),
        OffsetF(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize().Width(), FIRST_ITEM_HEIGHT));
    EXPECT_EQ(fifthItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(FIRST_ITEM_WIDTH, 0.0f));
}

/**
 * @tc.name: RelativeContainerLayoutTest004
 * @tc.desc: Set no child in RelativeContainer.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest004, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));

    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /**
    corresponding ets code:
       RelativeContainer() {
            }.width(200).height(200).backgroundColor(Color.Orange)
    */
    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
}

/**
 * @tc.name: RelativeContainerLayoutTest005
 * @tc.desc: Set one child with no flexItemProperty another depend on itself in RelativeContainer.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest005, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
       RelativeContainer() {
        Button("Button 1").width(120).height(50).id("bt1")
        Button("Button 2").alignRules({
            left: { anchor: "bt2", align: HorizontalAlign.End },
            middle: { anchor: "bt2", align: HorizontalAlign.Center },
          }).id("bt2")
      }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> secondItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        SECOND_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        SECOND_ITEM_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, secondItemAlignRules);
    secondItemFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondItemFrameNode->GetLayoutProperty()->UpdateAlignRules(secondItemAlignRules);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
}

/**
 * @tc.name: RelativeContainerLayoutTest006
 * @tc.desc: Set two child with no flexItemProperty.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest006, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
       RelativeContainer() {
        Button("Button 1").width(120).height(50).id("bt1")
        Button("Button 2").id("bt2")
      }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondItemFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);
    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), FIRST_ITEM_SIZE);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
}

/**
 * @tc.name: RelativeContainerLayoutTest007
 * @tc.desc: Set two children with wrong alignRules which makes calc length < 0.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest007, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
       RelativeContainer() {
        Button("Button 1").width(120).height(50).id("bt1")
          .alignRules({
            middle: { anchor: "__container__", align: HorizontalAlign.End },
            right: { anchor: "__container__", align: HorizontalAlign.Center },
          }).id("bt1")
        Button("Button 2")
        .alignRules({
            center: { anchor: "__container__", align: VerticalAlign.Bottom },
            bottom: { anchor: "__container__", align: VerticalAlign.Center },
          }).id("bt2")
      }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::END, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::CENTER, firstItemAlignRules);
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstItemFrameNode->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> secondItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::BOTTOM, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::CENTER, secondItemAlignRules);
    secondItemFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondItemFrameNode->GetLayoutProperty()->UpdateAlignRules(secondItemAlignRules);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
}

/**
 * @tc.name: RelativeContainerLayoutTest008
 * @tc.desc: Set two children with remain alignRules.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest008, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
       RelativeContainer() {
        Button("Button 1").alignRules({
          middle: { anchor: "__container__", align: HorizontalAlign.Center },
          right: { anchor: "__container__", align: HorizontalAlign.End },
          center: { anchor: "__container__", align: VerticalAlign.Center },
          bottom: { anchor: "__container__", align: VerticalAlign.Bottom },
        }).id("bt1")
        Button("Button 2").alignRules({
          middle: { anchor: "__container__", align: HorizontalAlign.Start },
          right: { anchor: "__container__", align: HorizontalAlign.Start },
          center: { anchor: "__container__", align: VerticalAlign.Top },
          bottom: { anchor: "__container__", align: VerticalAlign.Top },
        }).id("bt2")
      }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::CENTER, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::CENTER, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstItemAlignRules);
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstItemFrameNode->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> secondItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::MIDDLE, HorizontalAlign::START, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::START, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::CENTER, VerticalAlign::TOP, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::TOP, secondItemAlignRules);
    secondItemFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondItemFrameNode->GetLayoutProperty()->UpdateAlignRules(secondItemAlignRules);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}

/**
 * @tc.name: RelativeContainerLayoutTest009
 * @tc.desc: Set two children with remain alignRules to check offset.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerTestNg, RelativeContainerLayoutTest009, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_FALSE(relativeContainerPattern == nullptr);
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(relativeContainerLayoutAlgorithm == nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    /**
    corresponding ets code:
       RelativeContainer() {
        Button("Button 1").alignRules({
          right: { anchor: "__container__", align: HorizontalAlign.End },
          bottom: { anchor: "__container__", align: VerticalAlign.Bottom },
        }).id("bt1")
        Button("Button 2").alignRules({
          right: { anchor: "__container__", align: HorizontalAlign.Start },
          bottom: { anchor: "__container__", align: VerticalAlign.Top },
        }).id("bt2")
      }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstItemAlignRules);
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstItemFrameNode->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    firstItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(firstItemFrameNode);
    layoutWrapper->AppendChild(firstItemLayoutWrapper);

    auto secondItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondItemFrameNode, secondItemGeometryNode, secondItemFrameNode->GetLayoutProperty());
    secondItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    std::map<AlignDirection, AlignRule> secondItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::START, secondItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::TOP, secondItemAlignRules);
    secondItemFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondItemFrameNode->GetLayoutProperty()->UpdateAlignRules(secondItemAlignRules);
    secondItemLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(secondItemFrameNode);
    layoutWrapper->AppendChild(secondItemLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
    EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    EXPECT_EQ(secondItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF());
}
} // namespace OHOS::Ace::NG

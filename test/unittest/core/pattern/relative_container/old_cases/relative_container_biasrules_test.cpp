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
#include <vector>

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/relative_container/old_cases/relative_container_common_ng.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/components/common/layout/position_param.h"

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

class RelativeContainerBiasRulesTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback = nullptr);
    void SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height);
    void SetContainerParam(std::string id, float width, float height);

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        SystemProperties::debugEnabled_ = true;
    }

    RefPtr<FrameNode> frameNode_;
    RefPtr<RelativeContainerPattern> pattern_;
    RefPtr<RelativeContainerLayoutProperty> layoutProperty_;
};

void RelativeContainerBiasRulesTest::SetUp() {}

void RelativeContainerBiasRulesTest::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

void RelativeContainerBiasRulesTest::CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RelativeContainerPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RelativeContainerLayoutProperty>();
}

void RelativeContainerBiasRulesTest::SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height)
{
    textModelNG.Create(StringUtils::Str8ToStr16(id));
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}

void RelativeContainerBiasRulesTest::SetContainerParam(std::string id, float width, float height)
{
    ViewAbstract::SetWidth(CalcLength(width));
    ViewAbstract::SetHeight(CalcLength(height));
    ViewAbstract::SetInspectorId(id);
}

/**
 * @tc.name: BiasRulesTest001
 * @tc.desc: Set an item with bias with RelativeContainer and check it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTest001, TestSize.Level0)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * set pipeline: api = 11
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(150.0f, 150.0f));
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(150.0f), CalcLength(150.0)));
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, firstItemAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstItemAlignRules);
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);

    /**
     * set bias for first node, then the container is in the middle of the parent container
     * set align rules for first node
     */
    firstItemFrameNode->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    std::vector<std::pair<float, float>> biasPairs = {
        std::make_pair(-1.0f, -1.0f),
        std::make_pair(0.0f, 0.0f),
        std::make_pair(0.3f, 0.3f),
        std::make_pair(0.5f, 0.5f),
        std::make_pair(1.0f, 1.0f),
        std::make_pair(1.5f, 1.5f)
    };
    std::vector<OffsetF> offsets = {
        OffsetF(75.0f, 75.0f),
        OffsetF(0.0f, 0.0f),
        OffsetF(45.0f, 45.0f),
        OffsetF(75.0f, 75.0f),
        OffsetF(150.0f, 150.0f),
        OffsetF(225.0f, 225.0f)
    };
    for (int i = 0; i < 6; i++) {
        firstItemFrameNode->GetLayoutProperty()->UpdateBias(biasPairs[i]);
        auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        firstItemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(firstItemFrameNode);
        layoutWrapper->AppendChild(firstItemLayoutWrapper);

        relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
        EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

        EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(150.0f, 150.0f));
        EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), offsets[i]);
    }
}

/**
 * @tc.name: BiasRulesTest002
 * @tc.desc: Set one child item to auto, at the top/left
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTest002, TestSize.Level0)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);

    /**
     * add selfIdealSize for frameNode
     */
    std::optional<CalcLength> len = CalcLength(0.0f, DimensionUnit::AUTO);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = CalcSize(len, len);
    relativeContainerFrameNode->UpdateLayoutConstraint(layoutConstraint);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    layoutWrapper.GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize = CalcSize(len, len);
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    childLayoutConstraint.percentReference = CONTAINER_SIZE;
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());

    /**
     * add first child
    */
    MeasureProperty layoutConstraint1;
    layoutConstraint1.selfIdealSize = CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT));
    firstFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
}

/**
 * @tc.name: BiasRulesTest003
 * @tc.desc: Set two child item to auto, one at top/left, the other at top/right
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTest003, TestSize.Level0)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);

    /**
     * set pipeline: api = 11
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetMinPlatformVersion(11);

    /**
     * add selfIdealSize for frameNode
     */
    std::optional<CalcLength> len = CalcLength(0.0f, DimensionUnit::AUTO);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = CalcSize(len, len);
    relativeContainerFrameNode->UpdateLayoutConstraint(layoutConstraint);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    layoutWrapper.GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize = CalcSize(len, len);
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    childLayoutConstraint.percentReference = CONTAINER_SIZE;

    /**
     * add first child
     */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    MeasureProperty layoutConstraint1;
    layoutConstraint1.selfIdealSize = CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT));
    firstFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    /**
     * add a null rule in alignRules, make first flexItemProperty is not empty
     */
    std::map<AlignDirection, AlignRule> firstAlignRules;
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * add second child, set align rules
    */
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    MeasureProperty layoutConstraint2;
    layoutConstraint2.selfIdealSize = CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT));
    secondFrameNode->UpdateLayoutConstraint(layoutConstraint2);
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    auto childLayoutConstraint1 = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint1.selfIdealSize.SetSize(SizeF(200.0f, 200.0f));
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint1);
    secondLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    const auto& secondFlexProperty = secondLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::TOP, secondAlignRules);
    secondFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondFrameNode->GetLayoutProperty()->UpdateAlignRules(secondAlignRules);
    relativeContainerFrameNode->AddChild(secondFrameNode);
    layoutWrapper.AppendChild(secondLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(450.0f, 300.0f));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondFlexProperty->GetAlignRulesValue(), secondAlignRules);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), FIRST_ITEM_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(300.0f, 0.0f));
}

/**
 * @tc.name: BiasRulesTest004
 * @tc.desc: Set two child item to auto, one at top/left, the other at bottom/left
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTest004, TestSize.Level0)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);

    /**
     * add selfIdealSize for frameNode
     */
    std::optional<CalcLength> len = CalcLength(0.0f, DimensionUnit::AUTO);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = CalcSize(len, len);
    relativeContainerFrameNode->UpdateLayoutConstraint(layoutConstraint);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    layoutWrapper.GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize = CalcSize(len, len);
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    childLayoutConstraint.percentReference = CONTAINER_SIZE;

    /**
     * add first child
     */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    MeasureProperty layoutConstraint1;
    layoutConstraint1.selfIdealSize = CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT));
    firstFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    /**
     * add a null rule in alignRules, make first flexItemProperty is not empty
     */
    std::map<AlignDirection, AlignRule> firstAlignRules;
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * add second child, set align rules
     */
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    secondFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    const auto& secondFlexProperty = secondLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::START, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondAlignRules);
    secondFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondFrameNode->GetLayoutProperty()->UpdateAlignRules(secondAlignRules);
    relativeContainerFrameNode->AddChild(secondFrameNode);
    layoutWrapper.AppendChild(secondLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 600.0f));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondFlexProperty->GetAlignRulesValue(), secondAlignRules);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 300.0f));
}

/**
 * @tc.name: BiasRulesTest005
 * @tc.desc: Set two child item to auto, one at top/left, the other at bottom/right
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTest005, TestSize.Level0)
{
    auto relativeContainerFrameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);

    /**
     * add selfIdealSize for frameNode
     */
    std::optional<CalcLength> len = CalcLength(0.0f, DimensionUnit::AUTO);
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = CalcSize(len, len);
    relativeContainerFrameNode->UpdateLayoutConstraint(layoutConstraint);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(relativeContainerFrameNode, geometryNode, relativeContainerFrameNode->GetLayoutProperty());
    auto relativeContainerPattern = relativeContainerFrameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper.GetLayoutProperty();
    relativeContainerFrameNode->UpdateInspectorId(CONTAINER_ID);
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    layoutWrapper.GetLayoutProperty()->GetCalcLayoutConstraint()->selfIdealSize = CalcSize(len, len);
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);
    childLayoutConstraint.percentReference = CONTAINER_SIZE;

    /**
     * add first child
     */
    auto firstFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    MeasureProperty layoutConstraint1;
    layoutConstraint1.selfIdealSize = CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT));
    firstFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstFrameNode, firstGeometryNode, firstFrameNode->GetLayoutProperty());
    firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm = firstFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    firstLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    firstFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    /**
     * add a null rule in alignRules, make first flexItemProperty is not empty
     */
    std::map<AlignDirection, AlignRule> firstAlignRules;
    firstFrameNode->GetLayoutProperty()->UpdateAlignRules(firstAlignRules);
    relativeContainerFrameNode->AddChild(firstFrameNode);
    layoutWrapper.AppendChild(firstLayoutWrapper);

    /**
     * add second child, set align rules
     */
    auto secondFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    secondFrameNode->UpdateLayoutConstraint(layoutConstraint1);
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    secondGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> secondLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());
    secondLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto boxLayoutAlgorithm1 = secondFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    secondLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm1));
    const auto& secondFlexProperty = secondLayoutWrapper->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> secondAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::LEFT, HorizontalAlign::END, secondAlignRules);
    RelativeContainerTestUtilsNG::AddAlignRule(
        FIRST_ITEM_ID, AlignDirection::TOP, VerticalAlign::BOTTOM, secondAlignRules);
    secondFrameNode->UpdateInspectorId(SECOND_ITEM_ID);
    secondFrameNode->GetLayoutProperty()->UpdateAlignRules(secondAlignRules);
    relativeContainerFrameNode->AddChild(secondFrameNode);
    layoutWrapper.AppendChild(secondLayoutWrapper);

    relativeContainerLayoutAlgorithm->Measure(&layoutWrapper);
    relativeContainerLayoutAlgorithm->Layout(&layoutWrapper);

    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(600.0f, 600.0f));
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(firstLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
    EXPECT_EQ(secondFlexProperty->GetAlignRulesValue(), secondAlignRules);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(secondLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(300.0f, 300.0f));
}

static void AddAlignRule(const std::string& id, const AlignDirection& direction,
    const HorizontalAlign& horizontalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    RelativeContainerTestUtilsNG::AddAlignRule(id, direction, horizontalRule, alignRules);
}

static void AddAlignRule(const std::string& id, const AlignDirection& direction,
    const VerticalAlign& verticalRule, std::map<AlignDirection, AlignRule>& alignRules)
{
    RelativeContainerTestUtilsNG::AddAlignRule(id, direction, verticalRule, alignRules);
}

std::vector<std::pair<float, float>> biasPairs = {
    std::make_pair(-1.0f, -1.0f),
    std::make_pair(0.0f, 0.0f),
    std::make_pair(0.3f, 0.3f),
    std::make_pair(0.5f, 0.5f),
    std::make_pair(1.0f, 1.0f),
    std::make_pair(1.5f, 1.5f)
};

std::vector<OffsetF> offsets = {
    OffsetF(CONTAINER_WIDTH - 150.0f - 75.0f, 75.0f),
    OffsetF(CONTAINER_WIDTH - 150.0f - 0.0f, 0.0f),
    OffsetF(CONTAINER_WIDTH - 150.0f - 45.0f, 45.0f),
    OffsetF(CONTAINER_WIDTH - 150.0f - 75.0f, 75.0f),
    OffsetF(CONTAINER_WIDTH - 150.0f - 150.0f, 150.0f),
    OffsetF(CONTAINER_WIDTH - 150.0f - 225.0f, 225.0f)
};

static void LayoutConstraint(RefPtr<LayoutWrapperNode> layoutWrapper, SizeF containerSize)
{
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = containerSize;
    parentLayoutConstraint.percentReference = containerSize;
    parentLayoutConstraint.selfIdealSize.SetSize(containerSize);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
}

/**
 * @tc.name: BiasRulesTestRtl001
 * @tc.desc: Set an item with bias with RelativeContainer and check it, direction::RTL.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerBiasRulesTest, BiasRulesTestRtl001, TestSize.Level0)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, 0,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto relativeContainerPattern = frameNode->GetPattern<RelativeContainerPattern>();
    auto relativeContainerLayoutProperty = layoutWrapper->GetLayoutProperty();
    relativeContainerLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    frameNode->UpdateInspectorId(CONTAINER_ID);
    relativeContainerLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CONTAINER_WIDTH), CalcLength(CONTAINER_HEIGHT)));
    auto relativeContainerLayoutAlgorithm = relativeContainerPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(relativeContainerLayoutAlgorithm));

    LayoutConstraint(layoutWrapper, CONTAINER_SIZE);
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(150.0f, 150.0f));
    auto firstItemFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> firstItemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstItemGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> firstItemLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        firstItemFrameNode, firstItemGeometryNode, firstItemFrameNode->GetLayoutProperty());
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    firstItemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(150.0f), CalcLength(150.0)));
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    AddAlignRule(CONTAINER_ID, AlignDirection::START, HorizontalAlign::START, firstItemAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstItemAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::END, HorizontalAlign::END, firstItemAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, firstItemAlignRules);
    firstItemFrameNode->UpdateInspectorId(FIRST_ITEM_ID);
    firstItemFrameNode->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);

    /**
     * set bias for first node, then the container is in the middle of the parent container
     * set align rules for first node
     */
    for (int i = 0; i < 6; i++) {
        firstItemFrameNode->GetLayoutProperty()->UpdateBias(biasPairs[i]);
        auto boxLayoutAlgorithm = firstItemFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
        firstItemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
        frameNode->AddChild(firstItemFrameNode);
        layoutWrapper->AppendChild(firstItemLayoutWrapper);

        relativeContainerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
        relativeContainerLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
        EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);

        EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(150.0f, 150.0f));
        EXPECT_EQ(firstItemLayoutWrapper->GetGeometryNode()->GetFrameOffset(), offsets[i]);
    }
}

} // namespace OHOS::Ace::NG

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
#include "flex_base_test_ng.h"

#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_controller.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const int32_t SECOND_CHILD = 1;
} // namespace
class FlexNewTestNG : public FlexBaseTestNG {
public:
    RefPtr<FrameNode> CreateNormalFrameNode(const std::string& content, const std::string& tag)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            tag, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        stack->Push(frameNode);

        auto castTextLayoutProperty = frameNode->GetLayoutPropertyPtr<TextLayoutProperty>();
        castTextLayoutProperty->UpdateContent(content);

        auto textPattern = frameNode->GetPattern<TextPattern>();
        textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
        textPattern->GetTextController()->SetPattern(WeakPtr(textPattern));
        textPattern->ClearSelectionMenu();

        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};

/**
 * @tc.name: Template
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);

    /**
    corresponding ets code:
       Flex({direction: FlexDirection.Row}){
          Text().width(100).height(50)
          Text().width(100).height(50)
      }.width(300).height(300)
    */
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        // step: set direction: FlexDirection.Row
        model.SetDirection(FlexDirection::ROW);

        // step: set flex common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // // step: create child nodes
        auto text1 = CreateText("text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText("text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: second text offset x = 100.0f
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 100.0f);
}

/**
 * @tc.name: CheckSizeValidity001
 * @tc.desc: test CheckSizeValidity
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, CheckSizeValidity001, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::GONE);

    auto validSizeCount = flexLayoutAlgorithm->validSizeCount_;
    flexLayoutAlgorithm->CheckSizeValidity(frameNode);
    EXPECT_EQ(flexLayoutAlgorithm->validSizeCount_, validSizeCount);

    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    auto hostNode = layoutWrapper->hostNode_;
    layoutWrapper->hostNode_ = nullptr;
    flexLayoutAlgorithm->CheckSizeValidity(frameNode);
    layoutWrapper->hostNode_ = hostNode;
    EXPECT_EQ(flexLayoutAlgorithm->validSizeCount_, validSizeCount + 1);

    flexLayoutAlgorithm->CheckSizeValidity(nullptr);
    EXPECT_EQ(flexLayoutAlgorithm->validSizeCount_, validSizeCount + 2);
}

/**
 * @tc.name: HandleBlankFirstTimeMeasure001
 * @tc.desc: test HandleBlankFirstTimeMeasure
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, HandleBlankFirstTimeMeasure001, TestSize.Level1)
{
    RefPtr<FrameNode> blankFrameNode = nullptr;
    auto frameNode = CreateFlexRow([this, &blankFrameNode](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        blankFrameNode = CreateNormalFrameNode("blank", V2::BLANK_ETS_TAG);
    });
    ASSERT_NE(frameNode, nullptr);
    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);

    flexLayoutAlgorithm->Measure(AceType::RawPtr(frameNode));

    auto iterNodes = flexLayoutAlgorithm->magicNodes_.rbegin();
    auto childList = iterNodes->second;
    auto& child = *childList.begin();
    auto layoutProperty = blankFrameNode->GetLayoutProperty();

    FlexItemProperties flexItemProperties;

    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    MeasureProperty constraint;
    layoutProperty->UpdateCalcLayoutProperty(constraint);
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    constraint.selfIdealSize = CalcSize(CalcLength(10), CalcLength(10));
    layoutProperty->UpdateCalcLayoutProperty(constraint);
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    layoutProperty->UpdateCalcLayoutProperty(constraint);
    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN;
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    flexLayoutAlgorithm->isInfiniteLayout_ = true;
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    flexLayoutAlgorithm->selfAdaptive_ = true;
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));

    flexLayoutAlgorithm->isInfiniteLayout_ = false;
    EXPECT_TRUE(flexLayoutAlgorithm->HandleBlankFirstTimeMeasure(child, flexItemProperties));
}

/**
 * @tc.name: PlaceChildren001
 * @tc.desc: test PlaceChildren
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, PlaceChildren001, TestSize.Level1)
{
    RefPtr<FrameNode> textFrameNode = nullptr;
    auto frameNode = CreateFlexRow([this, &textFrameNode](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        textFrameNode = CreateNormalFrameNode("text", V2::TEXT_ETS_TAG);
    });
    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    OffsetF paddingOffset(1, 1);

    flexLayoutAlgorithm->crossAxisAlign_ = FlexAlign::SPACE_BETWEEN;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    auto geometryNode = textFrameNode->GetGeometryNode();
    auto rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(2, 1, 0, 0));

    flexLayoutAlgorithm->crossAxisAlign_ = FlexAlign::BASELINE;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(2, 1, 0, 0));

    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(1, 2, 0, 0));

    flexLayoutAlgorithm->direction_ = FlexDirection::ROW_REVERSE;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(0, 1, 0, 0));

    flexLayoutAlgorithm->crossAxisAlign_ = FlexAlign::STRETCH;
    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN;
    flexLayoutAlgorithm->textDir_ = TextDirection::RTL;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(1, 2, 0, 0));

    auto layoutProperty = textFrameNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::GONE);

    auto hostNode = frameNode->hostNode_;
    frameNode->hostNode_ = nullptr;
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    frameNode->hostNode_ = hostNode;
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(1, 2, 0, 0));

    OffsetT<Dimension> position(Dimension(1), Dimension(1));
    textFrameNode->renderContext_->UpdatePosition(position);
    flexLayoutAlgorithm->PlaceChildren(AceType::RawPtr(frameNode), 1, 1, paddingOffset);
    rect = geometryNode->GetMarginFrameRect();
    EXPECT_EQ(rect, RectF(0, 0, 0, 0));
}

/**
 * @tc.name: SecondaryMeasureByProperty001
 * @tc.desc: test SecondaryMeasureByProperty
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, SecondaryMeasureByProperty001, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        auto textFrameNode1 = CreateNormalFrameNode("text1", V2::TEXT_ETS_TAG);
        auto textFrameNode2 = CreateNormalFrameNode("text2", V2::BLANK_ETS_TAG);
    });
    CreateLayoutTask(frameNode);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    FlexItemProperties flexItemProperties;

    flexLayoutAlgorithm->Measure(AceType::RawPtr(frameNode));

    auto iterChilds = flexLayoutAlgorithm->secondaryMeasureList_.begin();
    auto& child1 = *iterChilds++;
    auto& child2 = *iterChilds++;

    child1.layoutWrapper->SetActive(false);
    child2.needKeepMinCalcSize = true;
    flexLayoutAlgorithm->isInfiniteLayout_ = true;
    flexLayoutAlgorithm->selfAdaptive_ = false;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));
    child1.layoutWrapper->SetActive(true);
    child2.needKeepMinCalcSize = false;

    LayoutConstraintF parentConstraint { .minSize { 10, 10 } };
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    flexLayoutAlgorithm->isInfiniteLayout_ = true;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    flexLayoutAlgorithm->mainAxisSize_ = -1;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));
    flexLayoutAlgorithm->maxDisplayPriority_ = 2;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));
    flexLayoutAlgorithm->mainAxisSize_ = 300;

    child2.needKeepMinCalcSize = false;
    flexItemProperties.lastGrowChild = child1.layoutWrapper;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    child1.layoutWrapper->GetLayoutProperty()->UpdateFlexGrow(1);
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    parentConstraint.minSize = SizeT<float>(1000, 1000);
    child1.layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);
    child2.layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    flexLayoutAlgorithm->direction_ = FlexDirection::ROW_REVERSE;
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    PaddingProperty paddingProperty { .top = CalcLength(300), .bottom = CalcLength(300) };
    frameNode->GetLayoutProperty()->UpdatePadding(paddingProperty);
    flexLayoutAlgorithm->SecondaryMeasureByProperty(flexItemProperties, AceType::RawPtr(frameNode));

    EXPECT_EQ(flexLayoutAlgorithm->crossAxisSize_, 0);
}

/**
 * @tc.name: MeasureAndCleanMagicNodes001
 * @tc.desc: test MeasureAndCleanMagicNodes
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, MeasureAndCleanMagicNodes001, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        auto text1 = CreateText("text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText("text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto layoutProperty = text1->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::GONE);
    });
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    layoutProperty->contentConstraint_ = LayoutConstraintF();
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);

    layoutProperty->UpdateVisibility(VisibleType::GONE);

    MeasureProperty constraint { .selfIdealSize = CalcSize(CalcLength(10), CalcLength(10)) };
    layoutProperty->UpdateCalcLayoutProperty(constraint);

    FlexItemProperties flexItemProperties;

    flexLayoutAlgorithm->Measure(AceType::RawPtr(frameNode));

    auto iterNodes = flexLayoutAlgorithm->magicNodes_.rbegin();
    auto childList = iterNodes->second;
    auto iterChilds = childList.rbegin();
    auto& child1 = *iterChilds++;
    auto& child2 = *iterChilds++;
    child1.layoutWrapper->hostNode_ = nullptr;
    child2.layoutWrapper = nullptr;

    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    LayoutConstraintF parentConstraint { .minSize { 10, 10 } };
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    flexLayoutAlgorithm->isInfiniteLayout_ = true;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    flexLayoutAlgorithm->maxDisplayPriority_ = 2;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    std::list<MagicLayoutNode> nodes = { child1 };
    flexLayoutAlgorithm->magicNodes_[2] = nodes;
    flexLayoutAlgorithm->isInfiniteLayout_ = false;
    flexLayoutAlgorithm->mainAxisSize_ = -300;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    EXPECT_EQ(flexLayoutAlgorithm->crossAxisSize_, 50);
}

/**
 * @tc.name: MeasureAndCleanMagicNodes002
 * @tc.desc: test MeasureAndCleanMagicNodes
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, MeasureAndCleanMagicNodes002, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        auto text1 = CreateText("text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText("text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto layoutProperty = text1->GetLayoutProperty();
        layoutProperty->UpdateVisibility(VisibleType::GONE);
    });
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    layoutProperty->contentConstraint_ = LayoutConstraintF();
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);

    layoutProperty->UpdateVisibility(VisibleType::GONE);
    MeasureProperty constraint;
    constraint.selfIdealSize = CalcSize(CalcLength(10), CalcLength(10));
    layoutProperty->UpdateCalcLayoutProperty(constraint);

    FlexItemProperties flexItemProperties;

    flexLayoutAlgorithm->Measure(AceType::RawPtr(frameNode));

    flexLayoutAlgorithm->totalFlexWeight_ = 1;

    auto iterNodes = flexLayoutAlgorithm->magicNodes_.rbegin();
    auto childList = iterNodes->second;
    auto iterChilds = childList.rbegin();
    auto& child1 = *iterChilds++;
    auto& child2 = *iterChilds++;
    child1.layoutWrapper->hostNode_ = nullptr;
    child2.layoutWrapper = nullptr;

    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    flexLayoutAlgorithm->mainAxisSize_ = -300;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    std::list<MagicLayoutNode> nodes = { child1 };
    flexLayoutAlgorithm->magicNodes_[2] = nodes;
    flexLayoutAlgorithm->isInfiniteLayout_ = false;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);

    EXPECT_EQ(flexLayoutAlgorithm->crossAxisSize_, 50);
}
} // namespace OHOS::Ace::NG
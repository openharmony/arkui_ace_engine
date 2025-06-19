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

#include "core/components_ng/pattern/blank/blank_pattern.h"
#include "core/components_ng/pattern/text/text_controller.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
const int32_t SECOND_CHILD = 1;
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const float ZERO = 0.0f;
const float INFINITY_NUM = 1000000.0f;
const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);
} // namespace
class FlexNewTestNG : public FlexBaseTestNG {
public:
    RefPtr<FrameNode> CreateNormalFrameNode(const std::u16string& content, const std::string& tag)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tag.c_str(), nodeId);
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(tag, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
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
        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
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

        blankFrameNode = CreateNormalFrameNode(u"blank", V2::BLANK_ETS_TAG);
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

        textFrameNode = CreateNormalFrameNode(u"text", V2::TEXT_ETS_TAG);
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

        auto textFrameNode1 = CreateNormalFrameNode(u"text1", V2::TEXT_ETS_TAG);
        auto textFrameNode2 = CreateNormalFrameNode(u"text2", V2::BLANK_ETS_TAG);
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

        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
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

        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
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

/**
 * @tc.name: ReverseFlexDirection001
 * @tc.desc: test ReverseFlexDirection
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, ReverseFlexDirection001, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        auto text = CreateText(u"text", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);

    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(frameNode->GetLayoutProperty());
    layoutProperty->GetFlexLayoutAttribute()->UpdateIsReverse(true);

    layoutProperty->UpdateFlexDirection(FlexDirection::ROW);
    flexLayoutAlgorithm->Layout(AceType::RawPtr(frameNode));
    EXPECT_EQ(flexLayoutAlgorithm->direction_, FlexDirection::ROW_REVERSE);

    layoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    flexLayoutAlgorithm->Layout(AceType::RawPtr(frameNode));
    EXPECT_EQ(flexLayoutAlgorithm->direction_, FlexDirection::ROW);

    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    flexLayoutAlgorithm->Layout(AceType::RawPtr(frameNode));
    EXPECT_EQ(flexLayoutAlgorithm->direction_, FlexDirection::COLUMN_REVERSE);

    layoutProperty->UpdateFlexDirection(FlexDirection::COLUMN_REVERSE);
    flexLayoutAlgorithm->Layout(AceType::RawPtr(frameNode));
    EXPECT_EQ(flexLayoutAlgorithm->direction_, FlexDirection::COLUMN);

    layoutProperty->UpdateFlexDirection(static_cast<FlexDirection>(10));
    flexLayoutAlgorithm->Layout(AceType::RawPtr(frameNode));
    EXPECT_EQ(flexLayoutAlgorithm->direction_, FlexDirection::ROW);
}

/**
 * @tc.name: CheckIsGrowOrShrink001
 * @tc.desc: test CheckIsGrowOrShrink
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, CheckIsGrowOrShrink001, TestSize.Level1)
{
    RefPtr<FrameNode> textFrameNode = nullptr;
    auto frameNode = CreateFlexRow([this, &textFrameNode](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        textFrameNode = CreateText(u"text", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);
    std::function<float(const RefPtr<LayoutWrapper>&)> getFlex;
    float spacePerFlex;
    FlexItemProperties flexItemProperties;
    RefPtr<LayoutWrapper> lastChild;
    flexItemProperties.totalShrink = 1;
    flexItemProperties.lastShrinkChild = textFrameNode;
    flexLayoutAlgorithm->CheckIsGrowOrShrink(getFlex, -10, spacePerFlex, flexItemProperties, lastChild);
    auto layoutProperty = textFrameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step1. call getFlex.
     * @tc.expected: Property's FlexShrink less or equal 0, getFlex return 0.
     */
    layoutProperty->UpdateFlexShrink(0.0f);
    EXPECT_EQ(getFlex(textFrameNode), 0.0f);
    /**
     * @tc.steps: step2. call getFlex.
     * @tc.expected: getFlex return value equal Property's FlexShrink
     */
    layoutProperty->UpdateFlexShrink(1.0f);
    EXPECT_EQ(getFlex(textFrameNode), 1.0f);
}

/**
 * @tc.name: CheckBlankAndKeepMin001
 * @tc.desc: test CheckBlankAndKeepMin
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, CheckBlankAndKeepMin001, TestSize.Level1)
{
    RefPtr<FrameNode> blankFrameNode = nullptr;
    auto frameNode = CreateFlexRow([this, &blankFrameNode](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::BLANK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BlankPattern>(); });
        stack->Push(frameNode);
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->Pop();
        blankFrameNode = AceType::DynamicCast<FrameNode>(element);
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step1. call CheckBlankAndKeepMin.
     * @tc.expected: hostNode_ is nullptr, so flexSize no change
     */
    float flexSize = 300;
    auto hostNode = blankFrameNode->hostNode_;
    blankFrameNode->hostNode_ = nullptr;
    flexLayoutAlgorithm->CheckBlankAndKeepMin(blankFrameNode, flexSize);
    EXPECT_EQ(flexSize, 300);
    /**
     * @tc.steps: step2. call CheckBlankAndKeepMin.
     * @tc.expected: ndoe's property MinSize less than flexSize, so flexSize no change
     */
    blankFrameNode->hostNode_ = hostNode;
    flexLayoutAlgorithm->CheckBlankAndKeepMin(blankFrameNode, flexSize);
    EXPECT_EQ(flexSize, 300);
    /**
     * @tc.steps: step3. call CheckBlankAndKeepMin.
     * @tc.expected: ndoe's property MinSize bigger than flexSize, so flexSize equal MinSize
     */
    auto blankProperty = blankFrameNode->GetLayoutProperty<BlankLayoutProperty>();
    ASSERT_NE(blankProperty, nullptr);
    blankProperty->UpdateMinSize(Dimension(500));
    flexLayoutAlgorithm->CheckBlankAndKeepMin(blankFrameNode, flexSize);
    EXPECT_EQ(flexSize, 500);
}

/**
 * @tc.name: UpdateLayoutConstraintOnCrossAxis001
 * @tc.desc: test UpdateLayoutConstraintOnCrossAxis
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, UpdateLayoutConstraintOnCrossAxis001, TestSize.Level1)
{
    RefPtr<FrameNode> textFrameNode = nullptr;
    auto frameNode = CreateFlexRow([this, &textFrameNode](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        textFrameNode = CreateText(u"text", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
    });
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(flexLayoutAlgorithm, nullptr);

    LayoutConstraintF layoutConstraint { .selfIdealSize = OptionalSize<float>(SizeF(100, 200)) };
    /**
     * @tc.steps: step1. call UpdateLayoutConstraintOnCrossAxis.
     * @tc.expected: direction_ equal ROW, so selfIdealSize.Height() equal size
     */
    flexLayoutAlgorithm->direction_ = FlexDirection::ROW;
    float size = 300.0f;
    flexLayoutAlgorithm->UpdateLayoutConstraintOnCrossAxis(layoutConstraint, 300);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Height(), 300.0f);
    /**
     * @tc.steps: step2. call UpdateLayoutConstraintOnCrossAxis.
     * @tc.expected: direction_ equal ROW_REVERSE, so selfIdealSize.Height() equal size
     */
    flexLayoutAlgorithm->direction_ = FlexDirection::ROW_REVERSE;
    size = 500.0f;
    flexLayoutAlgorithm->UpdateLayoutConstraintOnCrossAxis(layoutConstraint, size);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Height(), 500.0f);
    /**
     * @tc.steps: step3. call UpdateLayoutConstraintOnCrossAxis.
     * @tc.expected: direction_ equal COLUMN, so selfIdealSize.Width() equal size
     */
    flexLayoutAlgorithm->direction_ = FlexDirection::COLUMN;
    size = 400.0f;
    flexLayoutAlgorithm->UpdateLayoutConstraintOnCrossAxis(layoutConstraint, size);
    EXPECT_EQ(layoutConstraint.selfIdealSize.Width(), 400.0f);
}

/**
 * @tc.name: MeasureAndCleanMagicNodes003
 * @tc.desc: test MeasureAndCleanMagicNodes
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, MeasureAndCleanMagicNodes003, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);

        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
        });
        text1->GetLayoutProperty()->GetMagicItemProperty().UpdateLayoutWeight(1.0);
        text2->GetLayoutProperty()->GetMagicItemProperty().UpdateLayoutWeight(1.0);
    });
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->layoutConstraint_ = LayoutConstraintF();
    layoutProperty->contentConstraint_ = LayoutConstraintF();
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto flexLayoutAlgorithm = AceType::DynamicCast<FlexLayoutAlgorithm>(layoutAlgorithm);
    flexLayoutAlgorithm->Measure(AceType::RawPtr(frameNode));
    auto iterChilds = flexLayoutAlgorithm->magicNodes_.begin()->second.begin();
    auto& child1 = *iterChilds++;
    auto& child2 = *iterChilds++;
    child1.layoutConstraint.minSize = SizeT<float>(500, 500);
    child2.layoutConstraint.minSize = SizeT<float>(500, 500);
    flexLayoutAlgorithm->totalFlexWeight_ = 1;
    FlexItemProperties flexItemProperties;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);
    std::list<MagicLayoutNode> nodes = { child1, child2 };
    flexLayoutAlgorithm->magicNodes_[2] = nodes;
    flexLayoutAlgorithm->MeasureAndCleanMagicNodes(AceType::RawPtr(frameNode), flexItemProperties);
    EXPECT_EQ(flexLayoutAlgorithm->crossAxisSize_, 50);
}

/**
 * @tc.name: PerformLayoutInitialize001
 * @tc.desc: test PerformLayoutInitialize
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, PerformLayoutInitialize001, TestSize.Level1)
{
    auto frameNode = CreateFlexRow([this](FlexModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<FlexLayoutPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsWrap(true);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto wrapLayoutAlgorithm = AceType::DynamicCast<WrapLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(wrapLayoutAlgorithm, nullptr);
    auto layoutProp = AceType::DynamicCast<FlexLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProp, nullptr);
    /**
     * @tc.steps: step1. call PerformLayoutInitialize.
     * @tc.expected: selfIdealSize has value and isHorizontal_ is true, so mainLengthLimit_ equal
     * selfIdealSize.Width()
     */
    layoutProp->layoutConstraint_->selfIdealSize.SetWidth(10);
    wrapLayoutAlgorithm->isHorizontal_ = true;
    wrapLayoutAlgorithm->PerformLayoutInitialize(layoutProp);
    EXPECT_EQ(wrapLayoutAlgorithm->mainLengthLimit_, 10);
    /**
     * @tc.steps: step2. call PerformLayoutInitialize.
     * @tc.expected: selfIdealSize has value and isHorizontal_ is false, so crossLengthLimit_ equal
     * selfIdealSize.Width()
     */
    wrapLayoutAlgorithm->isHorizontal_ = false;
    wrapLayoutAlgorithm->PerformLayoutInitialize(layoutProp);
    EXPECT_EQ(wrapLayoutAlgorithm->crossLengthLimit_, 10);
    /**
     * @tc.steps: step3. call PerformLayoutInitialize.
     * @tc.expected: selfIdealSize has value and isHorizontal_ is true, so crossLengthLimit_ equal
     * selfIdealSize.Height()
     */
    layoutProp->layoutConstraint_->selfIdealSize.Reset();
    layoutProp->layoutConstraint_->selfIdealSize.SetHeight(10);
    wrapLayoutAlgorithm->isHorizontal_ = true;
    wrapLayoutAlgorithm->PerformLayoutInitialize(layoutProp);
    EXPECT_EQ(wrapLayoutAlgorithm->crossLengthLimit_, 10);
    /**
     * @tc.steps: step4. call PerformLayoutInitialize.
     * @tc.expected: selfIdealSize has value and isHorizontal_ is false, so mainLengthLimit_ equal
     * selfIdealSize.Height()
     */
    wrapLayoutAlgorithm->isHorizontal_ = false;
    wrapLayoutAlgorithm->PerformLayoutInitialize(layoutProp);
    EXPECT_EQ(wrapLayoutAlgorithm->mainLengthLimit_, 10);
}

/**
 * @tc.name: CalcItemCrossAxisOffset002
 * @tc.desc: test CalcItemCrossAxisOffset
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, CalcItemCrossAxisOffset002, TestSize.Level1)
{
    auto wrapFrameNode = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    ASSERT_NE(wrapFrameNode, nullptr);
    auto wrapLayoutPattern = wrapFrameNode->GetPattern<FlexLayoutPattern>();
    ASSERT_NE(wrapLayoutPattern, nullptr);
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    ASSERT_NE(wrapLayoutAlgorithm, nullptr);
    wrapLayoutAlgorithm->isHorizontal_ = false;
    /**
     * @tc.steps: step1. call CalcItemCrossAxisOffset.
     * @tc.expected: function return value equal offset.GetX()
     */
    OffsetF offset(10.0f, 0.0f);
    std::list<RefPtr<LayoutWrapper>> list;
    ContentInfo content(362.2, 362.2, 362, list);
    wrapLayoutAlgorithm->crossAlignment_ = WrapAlignment::SPACE_AROUND;
    auto ret = wrapLayoutAlgorithm->CalcItemCrossAxisOffset(content, offset, nullptr);
    EXPECT_EQ(ret, 10.0f);
    /**
     * @tc.steps: step2. call CalcItemCrossAxisOffset.
     * @tc.expected: function return value equal offset.GetX()
     */
    wrapLayoutAlgorithm->crossAlignment_ = WrapAlignment::BASELINE;
    ret = wrapLayoutAlgorithm->CalcItemCrossAxisOffset(content, offset, nullptr);
    EXPECT_EQ(ret, 10.0f);
}

/**
 * @tc.name: FlexIgnoreLayoutSafeArea001
 * @tc.desc: test flex ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexIgnoreLayoutSafeArea001, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    RefPtr<FrameNode> row2;

    auto frameNode = CreateFlexRow([this, &row1, &row2](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        row1 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::ROW);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        row2 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::ROW);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    row1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameOffset(), OffsetF(110.0f, 10.0f));
}


/**
 * @tc.name: FlexIgnoreLayoutSafeArea002
 * @tc.desc: test flex ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexIgnoreLayoutSafeArea002, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    RefPtr<FrameNode> row2;

    auto frameNode = CreateFlexRow([this, &row1, &row2](FlexModelNG model) {
        model.SetDirection(FlexDirection::ROW);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        row1 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::ROW);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        row2 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::ROW);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    row1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsReverse(true);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameOffset(), OffsetF(200.0f, 0.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameOffset(), OffsetF(90.0f, 10.0f));
}

/**
 * @tc.name: FlexIgnoreLayoutSafeArea003
 * @tc.desc: test flex ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexIgnoreLayoutSafeArea003, TestSize.Level1)
{
    RefPtr<FrameNode> column1;
    RefPtr<FrameNode> column2;

    auto frameNode = CreateFlexRow([this, &column1, &column2](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        column1 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::COLUMN);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        column2 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::COLUMN);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    column1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameOffset(), OffsetF(10.0f, 60.0f));
}

/**
 * @tc.name: FlexIgnoreLayoutSafeArea004
 * @tc.desc: test flex ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexIgnoreLayoutSafeArea004, TestSize.Level1)
{
    RefPtr<FrameNode> column1;
    RefPtr<FrameNode> column2;

    auto frameNode = CreateFlexRow([this, &column1, &column2](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        column1 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::COLUMN);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        column2 = CreateFlexRow([this](FlexModelNG model) {
            model.SetDirection(FlexDirection::COLUMN);
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    column1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameOffset(), OffsetF(200.0f, 190.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameOffset(), OffsetF(190.0f, 240.0f));
}

/**
 * @tc.name: FlexInfinityPercentHeight001
 * @tc.desc: test flex ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexInfinityPercentHeight001, TestSize.Level1)
{
    auto frameNode = CreateColumn([this](ColumnModelNG model) {});
    auto flexColumn = CreateFlexRow([this](FlexModelNG model) { model.SetDirection(FlexDirection::COLUMN); });
    auto flexRow = CreateFlexRow([this](FlexModelNG model) { model.SetDirection(FlexDirection::ROW); });
    LayoutConstraintF parentConstraint { .percentReference { RK356_WIDTH, RK356_HEIGHT },
        .maxSize { RK356_WIDTH, INFINITY_NUM } };
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    auto res = layoutProperty->GetPercentSensitive();
    EXPECT_EQ(res.first, false);
    EXPECT_EQ(res.second, false);
    auto flexColumnLayoutProperty = flexColumn->GetLayoutProperty();
    flexColumnLayoutProperty->UpdateLayoutConstraint(parentConstraint);
    auto flexColumnSensitive = flexColumnLayoutProperty->GetPercentSensitive();
    EXPECT_EQ(flexColumnSensitive.first, false);
    EXPECT_EQ(flexColumnSensitive.second, true);
    auto flexRowLayoutProperty = flexRow->GetLayoutProperty();
    flexRowLayoutProperty->UpdateLayoutConstraint(parentConstraint);
    auto flexRowSensitive = flexRowLayoutProperty->GetPercentSensitive();
    EXPECT_EQ(flexRowSensitive.first, true);
    EXPECT_EQ(flexRowSensitive.second, false);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width(LayoutPolicy.MATCH_PARENT)
            .height(LayoutPolicy.MATCH_PARENT)
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting matchParent and parent has padding.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest002, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width(LayoutPolicy.MATCH_PARENT)
            .height(LayoutPolicy.MATCH_PARENT)
        }
        .width("500px")
        .height("300px")
        .padding("20px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(460.0f, 260.0f));
    EXPECT_EQ(offset1, OffsetF(20.0f, 20.0f));
}

/**
 * @tc.name: LayoutPolicyTest003
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest003, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.WRAP_CONTENT)
        .height(LayoutPolicy.WRAP_CONTENT)
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest004, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    RefPtr<FrameNode> flexOutter;
    RefPtr<FrameNode> flex;
    flexOutter = CreateFlexRow([this, &flex, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            flexInner = CreateFlexRow([this](FlexModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(flexOutter, nullptr);
    ASSERT_EQ(flexOutter->GetChildren().size(), 1);
    CreateLayoutTask(flexOutter);

    /* corresponding ets code:
        Flex() {
            Flex() {
                Flex().width("300px").height("400px")
            }
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect flexOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = flexOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect flex's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest005, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500.0f));
            ViewAbstract::SetHeight(CalcLength(300.0f));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.fixAtIdealSize)
        .height(LayoutPolicy.fixAtIdealSize)
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting fixAtIdealSize and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest006, TestSize.Level1)
{
    RefPtr<FrameNode> flexInner;
    RefPtr<FrameNode> flexOutter;
    RefPtr<FrameNode> flex;
    flexOutter = CreateFlexRow([this, &flex, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            flexInner = CreateFlexRow([this](FlexModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(flexOutter, nullptr);
    ASSERT_EQ(flexOutter->GetChildren().size(), 1);
    CreateLayoutTask(flexOutter);

    /* corresponding ets code:
        Flex() {
            Flex() {
                Flex().width("300px").height("400px")
            }
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect flexOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = flexOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect flex's width is 150, height is 300 and offset is [25.0, -50.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 300, height is 400 and offset is [-75.0, -50.0].
    auto geometryNodeInner = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}
} // namespace OHOS::Ace::NG
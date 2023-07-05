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

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#define private public
#define protected public
#include <cstddef>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "core/animation/animator.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float MARQUEE_WIDTH_500 = 500.0f;
constexpr float MARQUEE_HEIGHT_100 = 100.0f;
constexpr float CHILD_WIDTH_600 = 600.0f;
constexpr float CHILD_HEIGHT_50 = 50.0f;
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr double MARQUEE_SCROLL_AMOUNT = 10.0;
constexpr int32_t MARQUEE_LOOP = 3;
const std::string MARQUEE_SRC = "marquee";
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

struct TestProperty {
    std::optional<std::string> src = std::nullopt;
    std::optional<int32_t> loop = std::nullopt;
    std::optional<double> scrollAmount = std::nullopt;
    std::optional<MarqueeDirection> direction = std::nullopt;
    std::optional<bool> playerStatus = std::nullopt;
    std::optional<Dimension> fontSize = std::nullopt;
    std::optional<Color> textColor = std::nullopt;
    std::optional<Ace::FontWeight> fontWeight = std::nullopt;
    std::optional<std::vector<std::string>> fontFamily = std::nullopt;
};

class MarqueeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateMarqueeParagraph(const TestProperty& testProperty);
};

void MarqueeTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void MarqueeTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void MarqueeTestNg::SetUp() {}
void MarqueeTestNg::TearDown() {}

RefPtr<FrameNode> MarqueeTestNg::CreateMarqueeParagraph(const TestProperty& testProperty)
{
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    if (testProperty.src.has_value()) {
        marqueeModel.SetValue(testProperty.src.value());
    }
    if (testProperty.playerStatus.has_value()) {
        marqueeModel.SetPlayerStatus(testProperty.playerStatus.value());
    }
    if (testProperty.scrollAmount.has_value()) {
        marqueeModel.SetScrollAmount(testProperty.scrollAmount.value());
    }
    if (testProperty.loop.has_value()) {
        marqueeModel.SetLoop(testProperty.loop.value());
    }
    if (testProperty.direction.has_value()) {
        marqueeModel.SetDirection(testProperty.direction.value());
    }
    if (testProperty.fontSize.has_value()) {
        marqueeModel.SetFontSize(testProperty.fontSize.value());
    }
    if (testProperty.textColor.has_value()) {
        marqueeModel.SetTextColor(testProperty.textColor.value());
    }
    if (testProperty.fontWeight.has_value()) {
        marqueeModel.SetFontWeight(testProperty.fontWeight.value());
    }
    if (testProperty.fontFamily.has_value()) {
        marqueeModel.SetFontFamily(testProperty.fontFamily.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // MarqueeView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: MarqueeTest001
 * @tc.desc: Test all the properties of marquee.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of marquee.
     */
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.loop = std::make_optional(MARQUEE_LOOP);
    testProperty.playerStatus = std::make_optional(false);
    testProperty.direction = std::make_optional(MarqueeDirection::LEFT);
    testProperty.scrollAmount = std::make_optional(MARQUEE_SCROLL_AMOUNT);
    testProperty.fontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.fontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamily = std::make_optional(FONT_FAMILY_VALUE);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto marqueeLayoutProperty = AceType::DynamicCast<MarqueeLayoutProperty>(layoutProperty);
    ASSERT_NE(marqueeLayoutProperty, nullptr);
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(textChild, nullptr);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto marqueePaintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    ASSERT_NE(marqueePaintProperty, nullptr);
    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(marqueePaintProperty->GetLoop(), MARQUEE_LOOP);
    EXPECT_EQ(marqueePaintProperty->GetDirection(), MarqueeDirection::LEFT);
    EXPECT_EQ(marqueePaintProperty->GetPlayerStatus(), false);
    EXPECT_EQ(marqueePaintProperty->GetScrollAmount(), MARQUEE_SCROLL_AMOUNT);
    EXPECT_EQ(marqueeLayoutProperty->GetSrc(), MARQUEE_SRC);
    EXPECT_EQ(marqueeLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(marqueeLayoutProperty->GetFontColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(marqueeLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(marqueeLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
}

/**
 * @tc.name: MarqueeTest002
 * @tc.desc: Verify whether the layout property, event and controller functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize src and playerStatus properties of marquee.
     */
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);

    /**
     * @tc.steps: step2. create frameNode to get pattern.
     * @tc.expected: step3. related function is called.
     */
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. get pattern and create layout property, event, controller.
     * @tc.expected: step3. related function is called.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnAnimationFinish();
    pattern->OnVisibleAreaChange(needSecondPlay);
    pattern->ChangeAnimationPlayStatus();
    pattern->StopMarqueeAnimation(needSecondPlay);
    AnimationUtils::PauseAnimation(pattern->animation_);
    auto layoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto event = pattern->CreateEventHub();
    ASSERT_NE(event, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_EQ(pattern->CalculateStart(), 0.0f);
}

/**
 * @tc.name: MarqueeTest003
 * @tc.desc: Test event function of marquee.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create marquee and set event.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    bool isStart = false;
    auto onChangeStart = [&isStart]() { isStart = true; };
    marqueeModel.SetOnStart(onChangeStart);
    bool isBounce = false;
    auto onChangeBounce = [&isBounce]() { isBounce = true; };
    marqueeModel.SetOnBounce(onChangeBounce);
    bool isFinish = false;
    auto onChangeFinish = [&isFinish]() { isFinish = true; };
    marqueeModel.SetOnFinish(onChangeFinish);

    /**
     * @tc.steps: step2. get marquee frameNode and event.
     * @tc.expected: step2. function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<MarqueeEventHub> eventHub = frameNode->GetEventHub<NG::MarqueeEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    eventHub->FireStartEvent();
    EXPECT_TRUE(isStart);
    eventHub->FireBounceEvent();
    EXPECT_TRUE(isBounce);
    eventHub->FireFinishEvent();
    EXPECT_TRUE(isFinish);
}

/**
 * @tc.name: MarqueeTest004
 * @tc.desc: Test the entry function OnDirtyLayoutWrapperSwap of marquee scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create marquee model and initialize playerStatus, loop and direction property.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    marqueeModel.SetPlayerStatus(false);
    marqueeModel.SetLoop(MARQUEE_LOOP);
    marqueeModel.SetDirection(MarqueeDirection::LEFT);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto marqueePaintProperty = frameNode->GetPaintProperty<MarqueePaintProperty>();
    ASSERT_NE(marqueePaintProperty, nullptr);

    /**
     * @tc.steps: step3. get the set playerStatus, loop and direction property.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_TRUE(marqueePaintProperty->GetPlayerStatus());
    EXPECT_EQ(marqueePaintProperty->GetLoop(), MARQUEE_LOOP);
    EXPECT_EQ(marqueePaintProperty->GetDirection(), MarqueeDirection::LEFT);

    /**
     * @tc.steps: step4. get marquee pattern and call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: step4. check whether the call is correct.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    DirtySwapConfig dirtySwapConfig;
    auto dirtyLayoutWrapperSwap = pattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig);
    EXPECT_FALSE(dirtyLayoutWrapperSwap);

    /**
     * @tc.steps: step5. update the playerStatus of marquee to true and call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: step5. check whether the call is correct.
     */
    marqueePaintProperty->UpdatePlayerStatus(true);
    EXPECT_TRUE(marqueePaintProperty->GetPlayerStatus());
    pattern->ChangeAnimationPlayStatus();
    pattern->OnModifyDone();
    dirtyLayoutWrapperSwap = pattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig);
    EXPECT_FALSE(dirtyLayoutWrapperSwap);

    /**
     * @tc.steps: step6. update the loop and direction of marquee and call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: step6. check whether the call is correct.
     */
    marqueePaintProperty->UpdateLoop(-1);
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    EXPECT_EQ(marqueePaintProperty->GetLoop(), -1);
    EXPECT_EQ(marqueePaintProperty->GetDirection(), MarqueeDirection::RIGHT);
    bool needSecondPlay = true;
    pattern->OnVisibleAreaChange(needSecondPlay);
    pattern->measureChanged_ = true;
    frameNode->MarkDirtyNode();
    dirtyLayoutWrapperSwap = pattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig);
    EXPECT_FALSE(dirtyLayoutWrapperSwap);
}

/**
 * @tc.name: MarqueeTest005
 * @tc.desc: When marquee's width and height are not set, check the child's position and self framesize.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    frameNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(marqueeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(textFrameNode, nullptr);

    /**
     * @tc.steps: step4. create marquee layoutWrapper.
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textGeometryNode, nullptr);
    RefPtr<LayoutWrapper> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);

    /**
     * @tc.steps: step5. set child size and set child layoutAlgorithm.
     * @tc.expected: step5. related function is called.
     */
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH_600), CalcLength(CHILD_HEIGHT_50)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step6. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    /**
     * @tc.steps: step7. do not set the size of marquee to update layout constraint.
     *
     *    corresponding ets code:
     *         marquee({ src: 'marquee', start: false })
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step8. marquee frameNode and layoutWrapper need to add child.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step9. call the measure and layout function of marquee to calculate the size and offset.
     */
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step10. check the child's position and self framesize.
     * @tc.expected: step10. marquee's width greater than child.
     */
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(DEVICE_WIDTH, CHILD_HEIGHT_50));

    /**
     * @tc.steps: step11. get child layoutWrapper to check framesize and offset.
     * @tc.expected: step11. child offset is center.
     */
    auto childLayoutWrapper = layoutWrapper.GetOrCreateChildByIndex(0);
    ASSERT_NE(childLayoutWrapper, nullptr);
    EXPECT_EQ(childLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CHILD_WIDTH_600, CHILD_HEIGHT_50));
    EXPECT_EQ(childLayoutWrapper->GetGeometryNode()->GetFrameOffset().GetX(), 0);
}

/**
 * @tc.name: MarqueeTest006
 * @tc.desc: When marquee width less than child, check the child's position and self framesize.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    frameNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(marqueeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(textFrameNode, nullptr);

    /**
     * @tc.steps: step4. create marquee layoutWrapper.
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textGeometryNode, nullptr);
    RefPtr<LayoutWrapper> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);

    /**
     * @tc.steps: step5. set child size and set child layoutAlgorithm.
     * @tc.expected: step5. related function is called.
     */
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH_600), CalcLength(CHILD_HEIGHT_50)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step6. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    /**
     * @tc.steps: step7. set marquee layout constraint and update it.
     *
     *    corresponding ets code:
     *         marquee({ src: 'marquee', start: false }).width(500).height(100)
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(MARQUEE_WIDTH_500, MARQUEE_HEIGHT_100));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step8. marquee frameNode and layoutWrapper need to add child.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step9. call the measure and layout function of marquee to calculate the size and offset.
     */
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step10. check the child's position and self framesize.
     * @tc.expected: step10. marquee's width less than child, child position is equal to the marquee width.
     */
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(MARQUEE_WIDTH_500, MARQUEE_HEIGHT_100));
}

/**
 * @tc.name: MarqueeTest007
 * @tc.desc: Verify animation state and other related functions when scrolling is required.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(textFrameNode, nullptr);

    /**
     * @tc.steps: step4. create marquee layoutWrapper
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textGeometryNode, nullptr);
    RefPtr<LayoutWrapper> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);

    /**
     * @tc.steps: step5. set child size and set child layoutAlgorithm.
     * @tc.expected: step5. related function is called.
     */
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH_600), CalcLength(CHILD_HEIGHT_50)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step6. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    /**
     * @tc.steps: step7. set marquee layout constraint and update it.
     *
     *    corresponding ets code:
     *         marquee({ src: 'marquee', start: false }).width(500).height(100)
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(MARQUEE_WIDTH_500, MARQUEE_HEIGHT_100));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step8. test the StartMarquee function when no child is added.
     */

    pattern->StartMarqueeAnimation();
    /**
     * @tc.steps: step9. add child and calculate the size and offset.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);
    textFrameNode->SetGeometryNode(textLayoutWrapper->GetGeometryNode());
    frameNode->SetGeometryNode(layoutWrapper.GetGeometryNode());

    /**
     * @tc.steps: step10. marquee width is less than child width, check the child offset.
     * @tc.expected: step10. child offset is 0.0f.
     */

    /**
     * @tc.steps: step11. when the marquee status is inActive, verify the startMarquee function.
     * @tc.expected: step11. the startAfterLayout parameter is true.
     */
    pattern->OnInActive();

    /**
     * @tc.steps: step12. when the marquee status is active, verify the startMarquee function.
     * @tc.expected: step12. check whether the parameters and animation status are correct.
     */
    pattern->OnActive();

    /**
     * @tc.steps: step13. when playerStatus is false by default and the animation status is running, OnModifyDone is
     * called.
     * @tc.expected: step13. check whether the animation status are correct.
     */
    pattern->FireStartEvent();
    pattern->FireBounceEvent();
    pattern->OnModifyDone();

    /**
     * @tc.steps: step14. get marquee layout properties and update playerStatus.
     * @tc.expected: step14. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto marqueeLayoutProperty = AceType::DynamicCast<MarqueeLayoutProperty>(layoutProperty);
    ASSERT_NE(marqueeLayoutProperty, nullptr);
    marqueeLayoutProperty->UpdatePlayerStatus(true);
}

/**
 * @tc.name: MarqueeTest008
 * @tc.desc: When scrolling is not required, verify the child position and other related functions.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(marqueeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);

    /**
     * @tc.steps: step4. create marquee layoutWrapper
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textGeometryNode, nullptr);
    RefPtr<LayoutWrapper> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);

    /**
     * @tc.steps: step5. set child size and set child layoutAlgorithm.
     * @tc.expected: step5. related function is called.
     */
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH_600), CalcLength(CHILD_HEIGHT_50)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<TextPattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step6. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    /**
     * @tc.steps: step7. do not set the size of marquee to update layout constraint.
     *
     *    corresponding ets code:
     *         marquee({ src: 'marquee', start: false })
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step8. add child and calculate the size and offset.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);
    textFrameNode->SetGeometryNode(textLayoutWrapper->GetGeometryNode());
    frameNode->SetGeometryNode(layoutWrapper.GetGeometryNode());

    /**
     * @tc.steps: step9. get child layout properties and update textAlign.
     * @tc.expected: step9. check whether the child offset is correct.
     */
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextAlign(TextAlign::START);
}

/**
 * @tc.name: MarqueeTest009
 * @tc.desc: When the width of marquee and child is 0, and the direction of marquee is right, verify the correlation
 *           function.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(marqueeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);

    /**
     * @tc.steps: step4. create marquee layoutWrapper
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(textGeometryNode, nullptr);
    RefPtr<LayoutWrapper> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);

    /**
     * @tc.steps: step5. set child size and set child layoutAlgorithm.
     * @tc.expected: step5. related function is called.
     */
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(CalcSize(CalcLength(0.0f), CalcLength(0.0f)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<TextPattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step6. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    /**
     * @tc.steps: step7. do not set the size of marquee to update layout constraint.
     *
     *    corresponding ets code:
     *         marquee({ src: 'marquee', start: false })
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.SetSize(SizeF(0.0f, 0.0f));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step8. add child and calculate the size and offset.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);
    textFrameNode->SetGeometryNode(textLayoutWrapper->GetGeometryNode());
    frameNode->SetGeometryNode(layoutWrapper.GetGeometryNode());
}

/**
 * @tc.name: MarqueeTest010
 * @tc.desc: Test Text property of marquee.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest0010, TestSize.Level1)
{
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    marqueeModel.SetValue(MARQUEE_SRC);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto accessibility = frameNode->GetAccessibilityProperty<MarqueeAccessibilityProperty>();
    EXPECT_EQ(accessibility->GetText(), MARQUEE_SRC);
}

/**
 * @tc.name: MarqueeTest011
 * @tc.desc: Test Marquee property ChangeFlag.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest0011, TestSize.Level1)
{
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    marqueeModel.SetValue(MARQUEE_SRC);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutProperty = AceType::DynamicCast<MarqueeLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(marqueeLayoutProperty, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto paintProperty = pattern->GetHost()->GetPaintProperty<MarqueePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    bool loop = true;
    paintProperty->UpdateLoop(loop);
    pattern->loop_ = false;
    pattern->direction_ = MarqueeDirection::RIGHT;
    EXPECT_FALSE(pattern->OnlyPlayStatusChange());
    pattern->loop_ = true;
    EXPECT_FALSE(pattern->OnlyPlayStatusChange());
    pattern->direction_ = MarqueeDirection::LEFT;
    EXPECT_FALSE(pattern->OnlyPlayStatusChange());
    pattern->playStatus_ = true;
    EXPECT_TRUE(pattern->OnlyPlayStatusChange());
    pattern->StoreProperties();
    EXPECT_EQ(pattern->direction_, MarqueeDirection::LEFT);
    pattern->OnModifyDone();
    EXPECT_TRUE(CheckMeasureFlag(marqueeLayoutProperty->GetPropertyChangeFlag()));
    EXPECT_TRUE(CheckMeasureFlag(textLayoutProperty->GetPropertyChangeFlag()));
}
} // namespace OHOS::Ace::NG

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

#include <cstddef>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/json/json_util.h"
#include "core/animation/animator.h"
#include "core/components/common/layout/constants.h"
#include "core/components/marquee/marquee_theme.h"
#include "core/components/theme/theme_manager_impl.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/marquee/marquee_layout_algorithm.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"
#include "core/components_ng/pattern/marquee/marquee_paint_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float MARQUEE_WIDTH_500 = 500.0f;
constexpr float MARQUEE_HEIGHT_100 = 100.0f;
constexpr float CHILD_WIDTH_600 = 600.0f;
constexpr float CHILD_WIDTH_200 = 200.0f;
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
    std::optional<bool> allowScale = std::nullopt;
    std::optional<Ace::MarqueeUpdateStrategy> marqueeUpdateStrategy = std::nullopt;
};

class MarqueeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateMarqueeParagraph(const TestProperty& testProperty);
};

void MarqueeTestNg::SetUpTestSuite()
{
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::SetUp();
}
void MarqueeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

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
    if (testProperty.allowScale.has_value()) {
        marqueeModel.SetAllowScale(testProperty.allowScale.value());
    }
    if (testProperty.marqueeUpdateStrategy.has_value()) {
        marqueeModel.SetMarqueeUpdateStrategy(testProperty.marqueeUpdateStrategy.value());
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
    pattern->OnVisibleChange(needSecondPlay);
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
    pattern->OnVisibleChange(needSecondPlay);
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
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

/**
 * @tc.name: MarqueeTest012
 * @tc.desc: Test Marquee Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and get marquee frameNode.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    frameNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create marquee layoutWrapper and set marquee layoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    auto marqueeLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(marqueeLayoutAlgorithm));

    /**
     * @tc.steps: step3. create and get marquee children frameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(CHILD_WIDTH_600), CalcLength(CHILD_HEIGHT_50)));
    auto textLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    textLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(textLayoutAlgorithm));

    /**
     * @tc.steps: step4. create child layout constraint and update it.
     */
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step5. set MeasureType is MATCH_PARENT.
     */
    layoutWrapper.GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    /**
     * @tc.steps: step6. call the measure function of marquee to calculate the size.
     * @tc.expected: step6. return is 0.
     */
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    SizeF oTemp = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(oTemp.Width(), 0);
    EXPECT_EQ(oTemp.Height(), 0);

    /**
     * @tc.steps: step7. set layoutConstraint and call Measure.
     * @tc.expected: step7. return is equal with minSize.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize = SizeF(CHILD_WIDTH_600, CHILD_WIDTH_200);
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(SizeF(MARQUEE_WIDTH_500, MARQUEE_HEIGHT_100));
    layoutWrapper.layoutProperty_->layoutConstraint_ = layoutConstraint;
    marqueeLayoutAlgorithm->Measure(&layoutWrapper);
    oTemp = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(oTemp.Width(), MARQUEE_WIDTH_500);
    EXPECT_EQ(oTemp.Height(), CHILD_HEIGHT_50);

    /**
     * @tc.steps: step8. set positionProperty_ and call Layout.
     */
    layoutWrapper.layoutProperty_->positionProperty_ = std::make_unique<PositionProperty>();
    marqueeLayoutAlgorithm->Layout(&layoutWrapper);
    OffsetF offTemp = textLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(offTemp.GetX(), 0);
    EXPECT_EQ(offTemp.GetY(), 0);
}

/**
 * @tc.name: MarqueeTest013
 * @tc.desc: Test MarqueeModelNG.Create
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add two Children.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = static_cast<ElementIdType>(1);
    stack->reservedNodeId_ = static_cast<ElementIdType>(1);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MARQUEE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    auto frameChild2 =
        FrameNode::GetOrCreateFrameNode("Child2", nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    frameNode->AddChild(frameChild1);
    frameNode->AddChild(frameChild2);

    /**
     * @tc.steps: step2. Set up the created frameNode.
     */
    ElementRegister::GetInstance()->itemMap_[nodeId] = frameNode;

    /**
     * @tc.steps: step3. Call Create.
     * @tc.expected: step3. Create Successful and first child update successful.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
    auto& groupProperty = textLayoutProperty->GetOrCreateTextLineStyle();
    EXPECT_EQ(groupProperty->GetMaxLinesValue(), 1);
}
/**
 * @tc.name: MarqueeTest014
 * @tc.desc: Test MarqueeModelNG setFun of MarqueePaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add two Children.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = static_cast<ElementIdType>(1);
    stack->reservedNodeId_ = static_cast<ElementIdType>(1);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MARQUEE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = paintProperty;

    /**
     * @tc.steps: step2. Set up the created frameNode.
     */
    ElementRegister::GetInstance()->itemMap_[nodeId] = frameNode;

    /**
     * @tc.steps: step3. Call Create.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    auto castMarqueePaintProperty = AceType::DynamicCast<MarqueePaintProperty>(frameNode->paintProperty_);

    /**
     * @tc.steps: step4. Call Set Function.
     * @tc.expected: step4. All Set Successful.
     */
    marqueeModel.SetPlayerStatus(true);
    EXPECT_EQ(castMarqueePaintProperty->GetPlayerStatus(), true);
    marqueeModel.SetPlayerStatus(std::nullopt);
    EXPECT_FALSE(castMarqueePaintProperty->HasPlayerStatus());

    marqueeModel.SetScrollAmount(2.0);
    EXPECT_EQ(castMarqueePaintProperty->GetScrollAmount(), 2.0);
    marqueeModel.SetScrollAmount(std::nullopt);
    EXPECT_FALSE(castMarqueePaintProperty->HasScrollAmount());

    marqueeModel.SetLoop(2);
    EXPECT_EQ(castMarqueePaintProperty->GetLoop(), 2);
    marqueeModel.SetLoop(std::nullopt);
    EXPECT_FALSE(castMarqueePaintProperty->HasLoop());

    marqueeModel.SetDirection(MarqueeDirection::LEFT);
    EXPECT_EQ(castMarqueePaintProperty->GetDirection(), MarqueeDirection::LEFT);
    marqueeModel.SetDirection(std::nullopt);
    EXPECT_FALSE(castMarqueePaintProperty->HasDirection());
    ViewStackProcessor::instance = nullptr;
}

/**
 * @tc.name: MarqueeTest015
 * @tc.desc: Test MarqueeModelNG setFun of MarqueeLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNod.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = static_cast<ElementIdType>(1);
    stack->reservedNodeId_ = static_cast<ElementIdType>(1);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MARQUEE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);

    /**
     * @tc.steps: step2. Set up the created frameNode.
     */
    ElementRegister::GetInstance()->itemMap_[nodeId] = frameNode;

    /**
     * @tc.steps: step3. Call Create.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();

    /**
     * @tc.steps: step4. Call Set Function.
     * @tc.expected: step4. All Set Successful.
     */
    marqueeModel.SetFontSize(Dimension(2.0));
    EXPECT_EQ(marqueeLayoutProperty->GetFontSize(), Dimension(2.0));
    marqueeModel.SetFontSize(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontSize());

    marqueeModel.SetTextColor(Color(2));
    EXPECT_EQ(marqueeLayoutProperty->GetFontColor(), Color(2));
    marqueeModel.SetTextColor(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontColor());

    marqueeModel.SetFontWeight(Ace::FontWeight::W200);
    EXPECT_EQ(marqueeLayoutProperty->GetFontWeight(), Ace::FontWeight::W200);
    marqueeModel.SetFontWeight(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontWeight());

    std::vector<std::string> fontFamily = { "test1", "test2" };
    marqueeModel.SetFontFamily(fontFamily);
    EXPECT_EQ(marqueeLayoutProperty->GetFontFamily(), fontFamily);
    marqueeModel.SetFontFamily(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontFamily());

    marqueeModel.SetAllowScale(true);
    EXPECT_EQ(marqueeLayoutProperty->GetAllowScale(), true);
    marqueeModel.SetAllowScale(std::nullopt);
    EXPECT_EQ(marqueeLayoutProperty->GetAllowScale(), true);

    marqueeModel.SetMarqueeUpdateStrategy(Ace::MarqueeUpdateStrategy::DEFAULT);
    EXPECT_EQ(marqueeLayoutProperty->GetMarqueeUpdateStrategy(), Ace::MarqueeUpdateStrategy::DEFAULT);
    marqueeModel.SetMarqueeUpdateStrategy(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasMarqueeUpdateStrategy());

    marqueeModel.SetValue("test");
    EXPECT_EQ(marqueeLayoutProperty->GetSrcValue(), "test");
    marqueeModel.SetValue(std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasSrc());
    ViewStackProcessor::instance = nullptr;
}

/**
 * @tc.name: MarqueeTest016
 * @tc.desc: Test MarqueeModelNG setFun of MarqueeLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    FrameNode frameNode = FrameNode(V2::MARQUEE_ETS_TAG, 1, pattern);
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    frameNode.SetLayoutProperty(marqueeLayoutProperty);

    /**
     * @tc.steps: step2. Call Create.
     */
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();

    /**
     * @tc.steps: step4. Call Set Function.
     * @tc.expected: step4. All Set Successful.
     */
    marqueeModel.SetFontSize(&frameNode, Dimension(2.0));
    EXPECT_EQ(marqueeLayoutProperty->GetFontSize(), Dimension(2.0));
    marqueeModel.SetFontSize(&frameNode, std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontSize());

    marqueeModel.SetTextColor(&frameNode, Color(2));
    EXPECT_EQ(marqueeLayoutProperty->GetFontColor(), Color(2));
    marqueeModel.SetTextColor(&frameNode, std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontColor());

    marqueeModel.SetFontWeight(&frameNode, Ace::FontWeight::W200);
    EXPECT_EQ(marqueeLayoutProperty->GetFontWeight(), Ace::FontWeight::W200);
    marqueeModel.SetFontWeight(&frameNode, std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontWeight());

    std::vector<std::string> fontFamily = { "test1", "test2" };
    marqueeModel.SetFontFamily(&frameNode, fontFamily);
    EXPECT_EQ(marqueeLayoutProperty->GetFontFamily(), fontFamily);
    marqueeModel.SetFontFamily(&frameNode, std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasFontFamily());

    marqueeModel.SetAllowScale(&frameNode, true);
    EXPECT_EQ(marqueeLayoutProperty->GetAllowScale(), true);
    marqueeModel.SetAllowScale(&frameNode, false);
    EXPECT_EQ(marqueeLayoutProperty->GetAllowScale(), false);

    marqueeModel.SetMarqueeUpdateStrategy(&frameNode, Ace::MarqueeUpdateStrategy::PRESERVE_POSITION);
    EXPECT_EQ(marqueeLayoutProperty->GetMarqueeUpdateStrategy(), Ace::MarqueeUpdateStrategy::PRESERVE_POSITION);
    marqueeModel.SetMarqueeUpdateStrategy(&frameNode, std::nullopt);
    EXPECT_FALSE(marqueeLayoutProperty->HasMarqueeUpdateStrategy());
}

/**
 * @tc.name: MarqueeTest017
 * @tc.desc: Test MarqueePattern.OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add two Children.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    auto frameChild2 =
        FrameNode::GetOrCreateFrameNode("Child2", 3, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    frameNode->AddChild(frameChild1);
    frameNode->AddChild(frameChild2);

    /**
     * @tc.steps: step2. Create MarqueePattern and create MarqueeLayoutProperty with some parameters.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step3. Create themeManager.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));

    /**
     * @tc.steps: step4. Create themeManager without marqueeLayoutProperty and call OnModifyDone.
     */
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->measureChanged_);
    EXPECT_FALSE(textLayoutProperty->HasFontFamily());

    /**
     * @tc.steps: step5. UpdatePlayerStatus true and set animation and call OnModifyDone.
     */
    marqueePaintProperty->UpdatePlayerStatus(true);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnModifyDone();
    EXPECT_NE(pattern->animation_, nullptr);
    EXPECT_TRUE(marqueePaintProperty->GetPlayerStatusValue());
    EXPECT_TRUE(pattern->playStatus_);

    /**
     * @tc.steps: step6. Create themeManager with marqueeLayoutProperty values and call OnModifyDone.
     */
    marqueeLayoutProperty->UpdateSrc("test");
    marqueeLayoutProperty->UpdateFontSize(Dimension(2.0));
    marqueeLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamily = { "test1", "test2" };
    marqueeLayoutProperty->UpdateFontFamily(fontFamily);
    marqueeLayoutProperty->UpdateFontColor(Color(2));
    frameNode->SetLayoutProperty(marqueeLayoutProperty);
    pattern->OnModifyDone();
    EXPECT_EQ(textLayoutProperty->GetContentValue(), u"test");
    EXPECT_EQ(textLayoutProperty->GetFontSize().value(), Dimension(2.0));
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), Ace::FontWeight::W200);
    EXPECT_EQ(textLayoutProperty->GetFontFamily().value(), fontFamily);
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color(2));
    EXPECT_TRUE(pattern->measureChanged_);
}

/**
 * @tc.name: MarqueeTest018
 * @tc.desc: Test MarqueePattern.CalculateEnd
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add a Child.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(2, 2));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(5, 5));
    frameChild1->SetGeometryNode(geo2);
    frameNode->AddChild(frameChild1);

    /**
     * @tc.steps: step2. Create MarqueePattern and create MarqueeLayoutProperty.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    marqueeLayoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);

    /**
     * @tc.steps: step3. Create MarqueePaintProperty.
     */
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    auto padding = marqueeLayoutProperty->CreatePaddingAndBorder();

    /**
     * @tc.steps: step4. Call CalculateEnd with MarqueeDirection is right.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    float end = pattern->CalculateEnd();
    float expect = 2 - padding.left.value_or(0);
    EXPECT_EQ(end, expect);

    /**
     * @tc.steps: step5. Call CalculateEnd with positionProperty_ with MarqueeDirection is left.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::LEFT);
    Alignment align;
    align.horizontal_ = 0.0f;
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    end = pattern->CalculateEnd();
    expect = -5 - padding.left.value_or(0);
    EXPECT_EQ(end, expect);

    /**
     * @tc.steps: step6. Call CalculateEnd with positionProperty_ and direction is right.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    end = pattern->CalculateEnd();
    expect = 2 - padding.left.value_or(0);
    EXPECT_EQ(end, expect);

    /**
     * @tc.steps: step7. Call CalculateEnd with positionProperty_ and direction is left and align is 1.
     */
    align.horizontal_ = 1.0f;
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    marqueePaintProperty->UpdateDirection(MarqueeDirection::LEFT);
    end = pattern->CalculateEnd();
    expect = -5 - padding.left.value_or(0);
    EXPECT_EQ(end, expect);

    /**
     * @tc.steps: step8. Call CalculateEnd with positionProperty_ and direction is right and align is 1.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    end = pattern->CalculateEnd();
    expect = 2 - padding.left.value_or(0);
    EXPECT_EQ(end, expect);
}

/**
 * @tc.name: MarqueeTest019
 * @tc.desc: Test MarqueePattern.StartMarqueeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add a Child.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(2, 2));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(5, 5));
    frameChild1->SetGeometryNode(geo2);
    frameNode->AddChild(frameChild1);

    /**
     * @tc.steps: step2. Create MarqueePattern and create MarqueePaintProperty.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    Alignment align;
    align.horizontal_ = 0.0f;
    marqueeLayoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);

    /**
     * @tc.steps: step3. Call StartMarqueeAnimation.
     * @tc.expected: step3. Set the end successfully.
     */
    pattern->StartMarqueeAnimation();
    auto renderContext = frameChild1->GetRenderContext();
    auto temp = renderContext->GetShowingTranslateProperty().GetX();
    EXPECT_EQ(temp, 0.0f);

    /**
     * @tc.steps: step4. Call StartMarqueeAnimation again with isFormRender_ is true.
     * @tc.expected: step4. Set the end successfully.
     */
    MockPipelineContext::GetCurrent()->SetIsFormRender(true);
    pattern->StartMarqueeAnimation();
    temp = renderContext->GetShowingTranslateProperty().GetX();
    EXPECT_EQ(temp, 0.0f);
}

/**
 * @tc.name: MarqueeTest020
 * @tc.desc: Test MarqueePattern.CalculateStart
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add a Child.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(2, 2));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(5, 5));
    frameChild1->SetGeometryNode(geo2);
    frameNode->AddChild(frameChild1);

    /**
     * @tc.steps: step2. Create MarqueePattern and create MarqueeLayoutProperty.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    marqueeLayoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);

    /**
     * @tc.steps: step3. Create MarqueePaintProperty.
     */
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    auto padding = marqueeLayoutProperty->CreatePaddingAndBorder();

    /**
     * @tc.steps: step4. Call CalculateStart with MarqueeDirection is right.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    float start = pattern->CalculateStart();
    float expect = -5 - padding.left.value_or(0);
    EXPECT_EQ(start, expect);

    /**
     * @tc.steps: step5. Call CalculateStart with positionProperty_ with MarqueeDirection is left.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::LEFT);
    Alignment align;
    align.horizontal_ = 0.0f;
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    start = pattern->CalculateStart();
    expect = 2 - padding.left.value_or(0);
    EXPECT_EQ(start, expect);

    /**
     * @tc.steps: step6. Call CalculateStart with positionProperty_ and direction is right.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    start = pattern->CalculateStart();
    expect = -5 - padding.left.value_or(0);
    EXPECT_EQ(start, expect);

    /**
     * @tc.steps: step7. Call CalculateStart with positionProperty_ and direction is left and align is 1.
     */
    align.horizontal_ = 1.0f;
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    marqueePaintProperty->UpdateDirection(MarqueeDirection::LEFT);
    start = pattern->CalculateStart();
    expect = 2 - padding.left.value_or(0);
    EXPECT_EQ(start, expect);

    /**
     * @tc.steps: step8. Call CalculateStart with positionProperty_ and direction is right and align is 1.
     */
    marqueePaintProperty->UpdateDirection(MarqueeDirection::RIGHT);
    start = pattern->CalculateStart();
    expect = -5 - padding.left.value_or(0);
    EXPECT_EQ(start, expect);
}

/**
 * @tc.name: MarqueeTest022
 * @tc.desc: Test MarqueePattern.OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add a Child.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    frameChild1->paintProperty_ = AceType::MakeRefPtr<PaintProperty>();
    frameNode->AddChild(frameChild1);

    /**
     * @tc.steps: step2. Create MarqueePattern.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    /**
     * @tc.steps: step3. Create themeManager.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto marqueeTheme = AceType::MakeRefPtr<MarqueeTheme>();
    marqueeTheme->textColor_ = Color(2);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(marqueeTheme));

    /**
     * @tc.steps: step4. Create OnColorConfigurationUpdate.
     * @tc.expected: step4. Update color successfully.
     */
    pattern->OnColorConfigurationUpdate();
    EXPECT_EQ(frameChild1->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_EQ(textLayoutProperty->GetTextColorValue(Color(0)), Color(2));
}

/**
 * @tc.name: MarqueeTest023
 * @tc.desc: Test MarqueePattern.GetTextOffset
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add a Child.
     */
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::MARQUEE_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto frameChild1 =
        FrameNode::GetOrCreateFrameNode("Child1", 2, []() { return AceType::MakeRefPtr<MarqueePattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameChild1->SetLayoutProperty(textLayoutProperty);
    RefPtr<GeometryNode> geo1 = AceType::MakeRefPtr<GeometryNode>();
    geo1->SetFrameSize(SizeF(2, 2));
    frameNode->SetGeometryNode(geo1);
    RefPtr<GeometryNode> geo2 = AceType::MakeRefPtr<GeometryNode>();
    geo2->SetFrameSize(SizeF(5, 5));
    frameChild1->SetGeometryNode(geo2);
    frameNode->AddChild(frameChild1);

    /**
     * @tc.steps: step2. Create MarqueePattern and create MarqueePaintProperty.
     */
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    pattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
    RefPtr<MarqueeLayoutProperty> marqueeLayoutProperty = AceType::MakeRefPtr<MarqueeLayoutProperty>();
    frameNode->SetLayoutProperty(marqueeLayoutProperty);
    RefPtr<MarqueePaintProperty> marqueePaintProperty = AceType::MakeRefPtr<MarqueePaintProperty>();
    frameNode->paintProperty_ = marqueePaintProperty;
    marqueePaintProperty->UpdatePlayerStatus(true);
    Alignment align;
    align.horizontal_ = 0.0f;
    marqueeLayoutProperty->positionProperty_ = std::make_unique<PositionProperty>();
    marqueeLayoutProperty->positionProperty_->UpdateAlignment(align);
    marqueeLayoutProperty->UpdateSrc("Test MarqueePattern.GetTextOffset");

    /**
     * @tc.steps: step3. Call GetTextOff.
     * @tc.expected: step3. Check whether the call is correct.
     */
    marqueeLayoutProperty->UpdateMarqueeUpdateStrategy(Ace::MarqueeUpdateStrategy::DEFAULT);
    EXPECT_EQ(marqueeLayoutProperty->GetMarqueeUpdateStrategy(), Ace::MarqueeUpdateStrategy::DEFAULT);
    pattern->StartMarqueeAnimation();
    auto offset = pattern->GetTextOffset();
    EXPECT_EQ(offset, 0.0f);
    pattern->StopMarqueeAnimation(false);
    marqueeLayoutProperty->UpdateMarqueeUpdateStrategy(Ace::MarqueeUpdateStrategy::PRESERVE_POSITION);
    EXPECT_EQ(marqueeLayoutProperty->GetMarqueeUpdateStrategy(), Ace::MarqueeUpdateStrategy::PRESERVE_POSITION);
    pattern->StartMarqueeAnimation();
    offset = pattern->GetTextOffset();
    EXPECT_EQ(offset, 0.0f);
}

/**
 * @tc.name: MarqueeTest024
 * @tc.desc: Test all the properties of marquee1.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest024, TestSize.Level1)
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
    marqueeLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
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
    EXPECT_EQ(marqueeLayoutProperty->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(marqueeLayoutProperty->GetNonAutoLayoutDirection(), TextDirection::RTL);
}

/**
 * @tc.name: MarqueeTest025
 * @tc.desc: Test marquee SetFrameRate
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MarqueeTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and marquee.
     */
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<MarqueePattern>();
    FrameNode frameNode = FrameNode(V2::MARQUEE_ETS_TAG, 1, pattern);
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    /**
     * @tc.steps: step2. set frame rate range.
     * @tc.expected: step2. check if the expected rate is set correctly.
     */
    int32_t expectedRate = 60;
    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(0, 120, expectedRate);
    marqueeModel.SetMarqueeFrameRateRange(&frameNode, frameRateRange, MarqueeDynamicSyncSceneType::ANIMATE);
    auto frameRateManager = MockPipelineContext::GetCurrentContext()->GetFrameRateManager();
    int32_t nodeId = frameNode.GetId();
    frameRateManager->isRateChanged_ = false;
    frameRateManager->AddNodeRate(nodeId, "", expectedRate);
    auto iter = frameRateManager->nodeRateMap_.find(nodeId);
    EXPECT_NE(iter, frameRateManager->nodeRateMap_.end());
    if (iter != frameRateManager->nodeRateMap_.end()) {
        EXPECT_EQ(iter->second.second, expectedRate);
        EXPECT_TRUE(frameRateManager->isRateChanged_);
    }
}

/**
 * @tc.name: OnWindowHide_001
 * @tc.desc: Test marquee OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowHide_001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnModifyDone();
    ASSERT_NE(pattern->animation_, nullptr);
    pattern->playStatus_ = false;
    pattern->OnWindowHide();
    EXPECT_EQ(pattern->playStatus_, false);
}

/**
 * @tc.name: OnWindowHide_002
 * @tc.desc: Test marquee OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowHide_002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnModifyDone();
    ASSERT_NE(pattern->animation_, nullptr);
    pattern->playStatus_ = true;
    pattern->OnWindowHide();
    EXPECT_EQ(pattern->playStatus_, false);
}

/**
 * @tc.name: OnWindowShow_001
 * @tc.desc: Test marquee OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowShow_001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnModifyDone();
    ASSERT_NE(pattern->animation_, nullptr);
    pattern->playStatus_ = true;
    pattern->OnWindowShow();
    EXPECT_EQ(pattern->playStatus_, true);
}

/**
 * @tc.name: OnWindowShow_002
 * @tc.desc: Test marquee OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowShow_002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);
    auto frameNode = CreateMarqueeParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    float start = 0.0f;
    int32_t playCount = 0;
    bool needSecondPlay = false;
    pattern->PlayMarqueeAnimation(start, playCount, needSecondPlay);
    pattern->OnModifyDone();
    ASSERT_NE(pattern->animation_, nullptr);
    pattern->playStatus_ = false;
    pattern->OnWindowShow();
    EXPECT_EQ(pattern->playStatus_, true);
}

/**
 * @tc.name: OnWindowSizeChanged_001
 * @tc.desc: Test marquee OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowSizeChanged_001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    int32_t width = 10;
    int32_t height = 20;
    marqueeModel.lastWindowWidth_ = width;
    marqueeModel.lastWindowHeight_ = height;
    marqueeModel.OnWindowSizeChanged(width, height, WindowSizeChangeReason::RESIZE);
    EXPECT_EQ(marqueeModel.measureChanged_, false);
}

/**
 * @tc.name: OnWindowSizeChanged_002
 * @tc.desc: Test marquee OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowSizeChanged_002, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    int32_t width = 10;
    int32_t height = 20;
    marqueeModel.lastWindowWidth_ = 8;
    marqueeModel.lastWindowHeight_ = height;
    marqueeModel.OnWindowSizeChanged(width, height, WindowSizeChangeReason::RESIZE);
    EXPECT_EQ(marqueeModel.measureChanged_, true);
}

/**
 * @tc.name: OnWindowSizeChanged_003
 * @tc.desc: Test marquee OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowSizeChanged_003, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    int32_t width = 10;
    int32_t height = 20;
    marqueeModel.lastWindowWidth_ = width;
    marqueeModel.lastWindowHeight_ = 18;
    marqueeModel.OnWindowSizeChanged(width, height, WindowSizeChangeReason::RESIZE);
    EXPECT_EQ(marqueeModel.measureChanged_, true);
}

/**
 * @tc.name: OnWindowSizeChanged_004
 * @tc.desc: Test marquee OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnWindowSizeChanged_004, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    int32_t width = 10;
    int32_t height = 20;
    marqueeModel.lastWindowWidth_ = 8;
    marqueeModel.lastWindowHeight_ = 18;
    marqueeModel.OnWindowSizeChanged(width, height, WindowSizeChangeReason::RESIZE);
    EXPECT_EQ(marqueeModel.measureChanged_, true);
}

/**
 * @tc.name: GetTextDirection_001
 * @tc.desc: Test marquee GetTextDirection
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, GetTextDirection_001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    std::string content = "HelloWorld";
    auto res = marqueeModel.GetTextDirection(content, TextDirection::RTL);
    EXPECT_EQ(res, TextDirection::RTL);
}

/**
 * @tc.name: GetTextDirection_002
 * @tc.desc: Test marquee GetTextDirection
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, GetTextDirection_002, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    std::string content = "HelloWorld";
    auto res = marqueeModel.GetTextDirection(content, TextDirection::AUTO);
    EXPECT_EQ(res, TextDirection::LTR);
}

/**
 * @tc.name: CheckTextDirectionChange_001
 * @tc.desc: Test marquee CheckTextDirectionChange
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, CheckTextDirectionChange_001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.currentTextDirection_ = TextDirection::LTR;
    marqueeModel.CheckTextDirectionChange(TextDirection::RTL);
    EXPECT_EQ(marqueeModel.lastAnimationOffset_, std::nullopt);
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate_001
 * @tc.desc: Test marquee OnFontScaleConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, OnFontScaleConfigurationUpdate_001, TestSize.Level1)
{
    MarqueePattern marqueeModel;
    marqueeModel.OnFontScaleConfigurationUpdate();
    EXPECT_FALSE(AnimationUtils::IsImplicitAnimationOpen());
}

/**
 * @tc.name: MeasureWithLayoutPolicy
 * @tc.desc: When marquee's width and height set layout policy, check the child's position and self framesize.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, MeasureWithLayoutPolicy, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = AceType::DynamicCast<MarqueeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    textGeometryNode->SetFrameWidth(200.0f);
    textGeometryNode->SetFrameHeight(200.0f);
    /**
     * @tc.steps: step5. marquee frameNode and layoutWrapper need to add child.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step6. call the MeasureWithLayoutPolicy.
     */
    OptionalSizeF optionalSize;
    marqueeLayoutAlgorithm->MeasureWithLayoutPolicy(&layoutWrapper, textLayoutWrapper, optionalSize);
    EXPECT_FALSE(optionalSize.IsValid());
    frameNode->GetLayoutProperty()->layoutConstraint_ = LayoutConstraintF();
    frameNode->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    marqueeLayoutAlgorithm->MeasureWithLayoutPolicy(&layoutWrapper, textLayoutWrapper, optionalSize);
    ASSERT_NE(optionalSize.Width(), std::nullopt);
    EXPECT_EQ(optionalSize.Width().value(), 200.0f);
    frameNode->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    marqueeLayoutAlgorithm->MeasureWithLayoutPolicy(&layoutWrapper, textLayoutWrapper, optionalSize);
    ASSERT_NE(optionalSize.Height(), std::nullopt);
    EXPECT_EQ(optionalSize.Height().value(), 200.0f);
}

/**
 * @tc.name: HandleWidthConstraint
 * @tc.desc: HandleWidthConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, HandleWidthConstraint, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = AceType::DynamicCast<MarqueeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    /**
     * @tc.steps: step5. marquee frameNode and layoutWrapper need to add child.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step6. call the HandleWidthConstraint.
     */
    MeasureCalculationContext calcContext { .layoutProperty = frameNode->GetLayoutProperty(),
        .layoutConstraint = LayoutConstraintF(),
        .optionalSize = OptionalSizeF() };
    calcContext.layoutConstraint.selfIdealSize.SetWidth(50.0f);
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::WRAP_CONTENT, 100.0f, calcContext);
    EXPECT_FALSE(calcContext.optionalSize.Width());

    calcContext.layoutConstraint.selfIdealSize.Reset();
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::WRAP_CONTENT, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Width(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Width().value(), 100.0f);

    calcContext.optionalSize.Reset();
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Width(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Width().value(), 100.0f);
    EXPECT_EQ(calcContext.layoutConstraint.maxSize.Width(), Infinity<float>());

    calcContext.optionalSize.Reset();
    CalcSize calcSize;
    calcSize.SetWidth(CalcLength(200.0f, DimensionUnit::VP));
    calcContext.layoutProperty->UpdateCalcMaxSize(calcSize);
    calcContext.layoutConstraint.maxSize.SetWidth(500.0f);
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Width(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Width().value(), 100.0f);
    EXPECT_EQ(calcContext.layoutConstraint.maxSize.Width(), 200.0f);

    calcContext.optionalSize.Reset();
    calcContext.layoutConstraint.parentIdealSize.SetWidth(1000.0f);
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::MATCH_PARENT, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Width(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Width().value(), 1000.0f);

    calcContext.optionalSize.Reset();
    calcContext.layoutConstraint.parentIdealSize.Reset();
    calcContext.layoutConstraint.maxSize.SetWidth(1080);
    marqueeLayoutAlgorithm->HandleWidthConstraint(LayoutCalPolicy::MATCH_PARENT, 100.0f, calcContext);
    EXPECT_EQ(calcContext.optionalSize.Width(), std::nullopt);
}

/**
 * @tc.name: HandleHeightConstraint
 * @tc.desc: HandleHeightConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueeTestNg, HandleHeightConstraint, TestSize.Level1)
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    ASSERT_NE(pattern, nullptr);
    auto marqueeLayoutAlgorithm = AceType::DynamicCast<MarqueeLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
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
    RefPtr<LayoutWrapperNode> const textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    /**
     * @tc.steps: step5. marquee frameNode and layoutWrapper need to add child.
     */
    frameNode->AddChild(textFrameNode);
    layoutWrapper.AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step6. call the HandleHeightConstraint.
     */
    MeasureCalculationContext calcContext { .layoutProperty = frameNode->GetLayoutProperty(),
        .layoutConstraint = LayoutConstraintF(),
        .optionalSize = OptionalSizeF() };
    calcContext.layoutConstraint.selfIdealSize.SetHeight(50.0f);
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::WRAP_CONTENT, 100.0f, calcContext);
    EXPECT_FALSE(calcContext.optionalSize.Height());

    calcContext.layoutConstraint.selfIdealSize.Reset();
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::WRAP_CONTENT, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Height(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Height().value(), 100.0f);

    calcContext.optionalSize.Reset();
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Height(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Height().value(), 100.0f);
    EXPECT_EQ(calcContext.layoutConstraint.maxSize.Height(), Infinity<float>());

    calcContext.optionalSize.Reset();
    CalcSize calcSize;
    calcSize.SetHeight(CalcLength(200.0f, DimensionUnit::VP));
    calcContext.layoutProperty->UpdateCalcMaxSize(calcSize);
    calcContext.layoutConstraint.maxSize.SetHeight(500.0f);
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Height(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Height().value(), 100.0f);
    EXPECT_EQ(calcContext.layoutConstraint.maxSize.Height(), 200.0f);

    calcContext.optionalSize.Reset();
    calcContext.layoutConstraint.parentIdealSize.SetHeight(1000.0f);
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::MATCH_PARENT, 100.0f, calcContext);
    ASSERT_NE(calcContext.optionalSize.Height(), std::nullopt);
    EXPECT_EQ(calcContext.optionalSize.Height().value(), 1000.0f);

    calcContext.optionalSize.Reset();
    calcContext.layoutConstraint.parentIdealSize.Reset();
    calcContext.layoutConstraint.maxSize.SetHeight(1080);
    marqueeLayoutAlgorithm->HandleHeightConstraint(LayoutCalPolicy::MATCH_PARENT, 100.0f, calcContext);
    EXPECT_EQ(calcContext.optionalSize.Height(), std::nullopt);
}
} // namespace OHOS::Ace::NG

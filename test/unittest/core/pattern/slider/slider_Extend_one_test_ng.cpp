/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "ui/properties/ui_material.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float VALUE = 50.0f;
constexpr float STEP = 1.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
constexpr float MIN_RANGE = MIN + 40.0f;
constexpr float MAX_RANGE = MAX - 30.0f;
constexpr float MIDDLE_OF_RANGE = (MIN_RANGE + MAX_RANGE) / 2;
constexpr float NAN_VALUE = std::numeric_limits<float>::quiet_NaN();
constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
const Color TEST_COLOR = Color::BLUE;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr Dimension SLIDER_NONE_TRACK_THICKNRESS = Dimension(5.0);
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Dimension BLOCK_SIZE_WIDTH = Dimension(300.0);
constexpr Dimension BLOCK_SIZE_HEIGHT = Dimension(300.0);
const SizeT<Dimension> BLOCK_SIZE(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
const std::string SLIDER_MODEL_NG_BLOCK_IMAGE = "Default Image";
const std::string SLIDER_TEST_BUNDLE_NAME = "com.test.slider";
const std::string SLIDER_TEST_MODULE_NAME = "testModule";
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
const PointF POINTF_START_DIFFX { 20.0f, 10.0f };
const PointF POINTF_END_DIFFX { 10.0f, 20.0f };
const PointF POINTF_START_DIFFY { 10.0f, 20.0f };
const PointF POINTF_END_DIFFY { 20.0f, 10.0f };
const PointF SELECT_START { 10.0f, 10.0f };
const PointF SELECT_END { 20.0f, 20.0f };
const PointF POINTF_CENTER { 15.0f, 15.0f };
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT = 60.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT = 64.0_vp;
} // namespace
class SliderExOneTestNg : public testing::Test {
public:
    void TearDown() override;

    static void SetUpTestSuite();
    static void TearDownTestSuite();

private:
    void SetSliderContentModifier(SliderContentModifier& sliderContentModifier);
    void MockCanvasFunction(Testing::MockCanvas& canvas);
    void MockTipsCanvasFunction(Testing::MockCanvas& canvas);
    void MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas);
};

void SliderExOneTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderExOneTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderExOneTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderExOneTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
{
    sliderContentModifier.InitializeShapeProperty();
    sliderContentModifier.SetTrackThickness(SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    sliderContentModifier.SetTrackBorderRadius(SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    sliderContentModifier.SetSelectedBorderRadius(SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS);
    sliderContentModifier.SetTrackBackgroundColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
    sliderContentModifier.SetShowSteps(true);
    sliderContentModifier.SetStepSize(SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    sliderContentModifier.SetStepColor(TEST_COLOR);
    sliderContentModifier.SetStepRatio(SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetSelectColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderExOneTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
{
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
}

void SliderExOneTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
{
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, ClipPath(_, _, _)).WillRepeatedly(Return());
}

void SliderExOneTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
{
    EXPECT_CALL(*paragraph, Paint(An<RSCanvas&>(), _, _)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Build()).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(1.0f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(1.0f));
}

/**
 * @tc.name: SliderValidRangeTest004
 * @tc.desc: Check set Valid Slide Range depends on Slider STEP
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest004, TestSize.Level1)
{
    struct TestInputData {
        float stepValue { 1.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    struct TestOutputData {
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    constexpr float STEP_10 = 10.0f;
    constexpr float STEP_3 = 3.0f;
    constexpr float STEP_7 = 7.0f;
    constexpr float STEP_2 = 2.0f;
    std::vector<std::pair<TestInputData, TestOutputData>> testSliderValidRangeData {
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 1.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 2.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + STEP_10 / 2, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 1.0f + STEP_10 / 2, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(2 * STEP_10 - 1.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + 2.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + STEP_10 / 2) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + STEP_10 / 2 + 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_7, std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5 + 1.0f, STEP_7 * 10 - 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5, STEP_7 * 10) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_7, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_3, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_3 * 13, STEP_3 * 24) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_2, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE - 1.0f, MAX_RANGE - 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE - STEP_2, MAX_RANGE) }),
    };
    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        auto stepValue = testData.first.stepValue;
        auto setRangeValue = testData.first.range;
        auto checkRangeValue = testData.second.range;
        sliderModelNG.Create(VALUE, stepValue, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. get SliderValidRange.
         * @tc.expected: step2. check whether the properties is correct.
         */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);

        if (checkRangeValue.get()) {
            EXPECT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
            auto rangeValue = sliderPaintProperty->GetValidSlideRange().value();
            EXPECT_EQ(rangeValue->GetFromValue(), checkRangeValue.get()->GetFromValue());
            EXPECT_EQ(rangeValue->GetToValue(), checkRangeValue.get()->GetToValue());
        } else {
            //should not never call. If you are here test FAILED
            ASSERT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
        }
    }
}

/**
 * @tc.name: SliderValidRangeTest005
 * @tc.desc: Check changes by KeyPad keys and Slider Valid Range values
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest005, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN_RANGE, STEP, MIN, MAX);
    sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<SliderPattern> sliderPattern = frameNode->GetPattern<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(sliderLayoutProperty, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    sliderPattern->value_ = sliderPaintProperty->GetValue().value_or(0.0f);

    /**
     * @tc.cases: case1. event.action != KeyAction::DOWN.
     */
    KeyEvent event;
    event.action = KeyAction::UP;
    EXPECT_FALSE(sliderPattern->OnKeyEvent(event));
    /**
     * @tc.cases: case2. direction == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT, MoveStep(-1).
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    sliderPattern->value_ = MIN_RANGE;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE);

    /**
     * @tc.cases: case3. direction == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    sliderPattern->value_ = MIN_RANGE;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE + STEP);
    /**
     * @tc.cases: case4. direction == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP, MoveStep(-1).
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
    sliderPattern->value_ = MAX_RANGE;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MAX_RANGE - STEP);
    /**
     * @tc.cases: case5. direction == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    sliderPattern->value_ = MAX_RANGE;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MAX_RANGE);
}

/**
 * @tc.name: SliderValidRangeTest006
 * @tc.desc: Slide by slider block and check Slider value by Slider Valid Range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest006, TestSize.Level1)
{
    struct TestData {
        float startValue { 1.0f };
        float offsetValue { 0.0f };
        float valueAfterSlide { 0.0f };
        float valueAfteTouchUp { 0.0f };
    };
    std::vector<TestData> testSliderValidRangeData {
        { VALUE, -7.0f, VALUE - 7.0f, VALUE - 7.0f },
        { VALUE, 7.0f, VALUE + 7.0f, VALUE + 7.0f },
        { VALUE, -40.0f, VALUE - 40.0f, MIN_RANGE },
        { VALUE, 40.0f, VALUE + 40.0f, MAX_RANGE },
    };
    for (auto testData : testSliderValidRangeData) {
        auto startValue = testData.startValue;
        auto touchOffset = testData.offsetValue;
        auto valueEndSlide = testData.valueAfterSlide;
        auto endValue = testData.valueAfteTouchUp;
        SliderModelNG sliderModelNG;
        sliderModelNG.Create(startValue, STEP, MIN, MAX);
        sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);
        frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
        sliderPattern->blockHotSize_ = SizeF(startValue, MIN_LABEL);

        /**
         * @tc.cases: case1. InputEventType is not AXIS and drag by block to 20.0
         */
        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        info.localLocation_ = Offset(startValue, MIN_LABEL);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(touchOffset);
        info.localLocation_ = Offset(startValue + touchOffset, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, valueEndSlide));
        sliderPattern->HandledGestureEvent();
        sliderPattern->UpdateToValidValue();
        EXPECT_TRUE(NearEqual(sliderPattern->value_, endValue));
    }
}

/**
 * @tc.name: SliderValidRangeTest007
 * @tc.desc: Check "GetValidSlideRange" API
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest007, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto validRange = SliderModelNG::GetValidSlideRange(Referenced::RawPtr(frameNode));
    EXPECT_TRUE(validRange && validRange->HasValidValues());
    EXPECT_EQ(validRange->GetFromValue(), MIN_RANGE);
    EXPECT_EQ(validRange->GetToValue(), MAX_RANGE);
}

/**
 * @tc.name: PaintHorizontalBubbleSuitableAgingTest001
 * @tc.desc: TEST slider_tip_modifier PaintHorizontalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, PaintHorizontalBubbleSuitableAgingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintHorizontalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 1.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    /**
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 1.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: PaintHorizontalBubbleSuitableAgingTest002
 * @tc.desc: TEST slider_tip_modifier PaintHorizontalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, PaintHorizontalBubbleSuitableAgingTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintHorizontalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 2.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    /**
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 2.
     */
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SliderPaintMethodTest004
 * @tc.desc: Test slider_paint_method UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.trackThickness = static_cast<float>(SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx());
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())
        ->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    /**
     * @tc.steps: step3. call UpdateContentModifier function.
     */
    // set theme
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    Color color = Color::RED;
    sliderTheme->markerColor_ = color;
    // call UpdateContentModifier function
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->stepColor_->Get(), LinearColor(Color::RED));
}

/**
 * @tc.name: sliderTipModifierTestUpdateBubbleSize001
 * @tc.desc: Test UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, sliderTipModifierTestUpdateBubbleSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });

    /**
     * @tc.steps: step2. set theme.
     */
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->bubbleArrowHeight_ = 10.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderTipModifier.UpdateBubbleSize();
    EXPECT_EQ(sliderTipModifier.arrowHeight_, sliderTheme->GetBubbleArrowHeight().ConvertToPx());
}

/**
 * @tc.name: SliderValidRangeTest001
 * @tc.desc: check value of slider valid range by default
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderValidRange by default.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_FALSE(sliderPaintProperty->GetValidSlideRange().has_value());
}

/**
 * @tc.name: SliderValidRangeTest002
 * @tc.desc: Update Slider value by Slider valid range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest002, TestSize.Level1)
{
    struct TestData {
        float value { 0.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    std::vector<std::pair<TestData, TestData>> testSliderValidRangeData {
        std::make_pair<TestData, TestData>(
            { MIN, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN + 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX - 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX + 1.0f) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MAX, MIN) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MAX_RANGE, MIN_RANGE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN - 1.0f, MAX) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX + 1.0f) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(INFINITY_VALUE, INFINITY_VALUE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, INFINITY_VALUE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(INFINITY_VALUE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN - 1.0f, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
    };

    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        auto setValue = testData.first.value;
        auto checkValue = testData.second.value;
        auto setRangeValue = testData.first.range;
        auto checkRangeValue = testData.second.range;
        sliderModelNG.Create(setValue, STEP, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. get SliderValidRange.
         * @tc.expected: step2. check whether the properties is correct.
         */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);

        if (checkRangeValue.get()) {
            EXPECT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
            auto rangeValue = sliderPaintProperty->GetValidSlideRange().value();
            EXPECT_EQ(rangeValue->GetFromValue(), checkRangeValue.get()->GetFromValue());
            EXPECT_EQ(rangeValue->GetToValue(), checkRangeValue.get()->GetToValue());
        } else {
            EXPECT_FALSE(sliderPaintProperty->GetValidSlideRange().has_value());
        }
        EXPECT_EQ(sliderPaintProperty->GetValue(), checkValue);
    }
}

/**
 * @tc.name: SliderValidRangeTest003
 * @tc.desc: Check touch events with Slider valid range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExOneTestNg, SliderValidRangeTest003, TestSize.Level1)
{
    struct TestInputData {
        float value { 0.0f };
        float touchOffset { 0.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    struct TestOutputData {
        float value;
    };

    std::vector<std::pair<TestInputData, TestOutputData>> testSliderValidRangeData {
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE - 1.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE - 10.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE + 1.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE + 10.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIDDLE_OF_RANGE,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIDDLE_OF_RANGE + 1.0f,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MAX - MIDDLE_OF_RANGE - 1.0f,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MAX - MIDDLE_OF_RANGE,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
    };

    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        float setValue = testData.first.value;
        float touchOffset = testData.first.touchOffset;
        auto setRangeValue = testData.first.range;
        sliderModelNG.Create(setValue, STEP, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);
        frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
        auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
        EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
        sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
        sliderPattern->blockHotSize_ = SizeF(setValue, MIN_LABEL);

        /**
         * @tc.steps: step2. initialize touch information.
         * @tc.desc:  when TouchType is DOWN, SourceType is touch.
         */
        TouchLocationInfo LInfo(0);
        LInfo.touchType_ = TouchType::DOWN;
        LInfo.localLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        TouchEventInfo infoDown("");
        infoDown.SetSourceDevice(SourceType::TOUCH);
        infoDown.changedTouches_.emplace_back(LInfo);

        /**
         * @tc.steps: step2. initialize touch information.
         * @tc.desc:  when TouchType is UP, SourceType is touch.
         */
        TouchLocationInfo UpInfo(0);
        UpInfo.touchType_ = TouchType::UP;
        UpInfo.localLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        TouchEventInfo infoUp("");
        infoUp.SetSourceDevice(SourceType::TOUCH);
        infoUp.changedTouches_.emplace_back(UpInfo);

        /**
         * @tc.cases: case1. check Slider value after touch down
         */
        sliderPattern->lastTouchLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        sliderPattern->fingerId_ = LInfo.GetFingerId();
        sliderPattern->HandleTouchEvent(infoDown);

        /**
         * @tc.cases: case2. check Slider value after touch up
         */
        sliderPattern->HandleTouchEvent(infoUp);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, setValue));
    }
}
} // namespace OHOS::Ace::NG

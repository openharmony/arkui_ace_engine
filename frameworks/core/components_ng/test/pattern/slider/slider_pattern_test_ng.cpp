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

#include "gtest/gtest.h"
#include "base/utils/utils.h"
#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float VALUE = 50.0f;
constexpr float STEP = 1.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
const SliderModel::SliderMode TEST_SLIDERMODE = SliderModel::SliderMode::INSET;
const Axis TEST_AXIS = Axis::HORIZONTAL;
constexpr bool BOOL_VAULE = true;
const Color TEST_COLOR = Color::BLUE;
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float FRAME_WIDTH = 10.0f;
constexpr float FRAME_HEIGHT = 20.0f;
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
constexpr Dimension SLIDER_OUTSET_TRACK_THICKNRESS = Dimension(10.0);
constexpr Dimension SLIDER_INSET_TRACK_THICKNRESS = Dimension(20.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_SIZE = Dimension(30.0);
constexpr Dimension SLIDER_INSET_BLOCK_SIZE = Dimension(40.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_HOTSIZE = Dimension(50.0);
constexpr Dimension SLIDER_INSET_BLOCK_HOTSIZE = Dimension(60.0);
constexpr Dimension SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_TRACK_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_STEP_SIZE = Dimension(10.0);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
const std::string SLIDER_MODEL_NG_BLOCK_IMAGE = "Default Image";
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
const PointF POINTF_CENTER { 15.0f, 15.0f };
} // namespace
class SliderPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SliderPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SliderPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SliderPatternTestNg001
 * @tc.desc: Test Slider Create
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from sliderPaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
}

/**
 * @tc.name: SliderPatternTestNg002
 * @tc.desc: Test Slider Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderMode(TEST_SLIDERMODE);
    sliderModelNG.SetDirection(TEST_AXIS);
    sliderModelNG.SetReverse(BOOL_VAULE);
    sliderModelNG.SetBlockColor(TEST_COLOR);
    sliderModelNG.SetTrackBackgroundColor(TEST_COLOR);
    sliderModelNG.SetSelectColor(TEST_COLOR);
    sliderModelNG.SetShowSteps(BOOL_VAULE);
    sliderModelNG.SetThickness(WIDTH);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetReverse(), BOOL_VAULE);
    EXPECT_EQ(sliderPaintProperty->GetDirection(), TEST_AXIS);
    EXPECT_EQ(sliderPaintProperty->GetBlockColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBackgroundColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetSelectColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetShowSteps(), BOOL_VAULE);
}

/**
 * @tc.name: SliderPatternTestNg003
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get sliderPattern and sliderWrapper.
     */
    RefPtr<SliderPattern> sliderPattern = frameNode->GetPattern<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    frameNode->SetGeometryNode(geometryNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(sliderLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, sliderLayoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);
    layoutWrapper->skipMeasureContent_ = false;
    /**
     * @tc.steps: step3. call sliderPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<SliderLayoutAlgorithm> sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    /**
     * @tc.steps: step4. call sliderPattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */
    /**
     *     case 1: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool firstCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(firstCase);
    /**
     *     case 2: LayoutWrapper::SkipMeasureContent = true , skipMeasure = false;
     */
    bool secondCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(secondCase);
    /**
     *    case 3: LayoutWrapper::SkipMeasureContent = false , skipMeasure = true;
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool thirdCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(thirdCase);
    /**
     *    case 4: LayoutWrapper::SkipMeasureContent = false , skipMeasure = false, and directions is HORIZONTAL,
     *            sliderMode is OUTSET.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = 40.0f;
    bool forthCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forthCase);
    EXPECT_EQ(sliderPattern->sliderLength_, 10.f);
    EXPECT_EQ(sliderPattern->borderBlank_, 20.f);
    /**
     *    case 5: directions is VERTICAL, sliderMode is INSET.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    bool fifthCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(fifthCase);
    EXPECT_EQ(sliderPattern->sliderLength_, 1.0);
    EXPECT_EQ(sliderPattern->borderBlank_, 24.5);
}

/**
 * @tc.name: SliderPatternTestNg004
 * @tc.desc: Test Slider OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get sliderPattern.
     */
    RefPtr<SliderPattern> sliderPattern = frameNode->GetPattern<SliderPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    sliderPattern->OnModifyDone();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    sliderPattern->OnModifyDone();
    EXPECT_NE(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
}

/**
 * @tc.name: SliderPatternTestNg005
 * @tc.desc: Test Slider HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg005, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->tipTextPadding_ = Dimension(10.0);
    sliderTheme->tipColor_ = Color::BLUE;
    sliderTheme->tipFontSize_ = Dimension(16.0);
    sliderTheme->tipTextColor_ = Color::BLACK;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    EXPECT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetFrameSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    /**
     * @tc.steps: step2. get sliderPattern and initialize needed layoutProperty.
     * @tc.cases: case1. when TouchType is DOWN and direction is HORIZONTAL.
     */
    TouchLocationInfo LInfo(0);
    LInfo.touchType_ = TouchType::DOWN;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, true);
    sliderPattern->showTips_ = true;
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->bubbleFlag_, true);
    /**
     * @tc.cases: case2. when TouchType is DOWN and direction is VERTICAL.
     */
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    sliderPaintProperty->UpdateReverse(true);
    sliderPattern->UpdateCircleCenterOffset();
    /**
     * @tc.cases: case3. when TouchType is UP.
     */
    info.touches_.front().touchType_ = TouchType::UP;
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, false);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->bubbleFlag_, false);
}

/**
 * @tc.name: SliderPatternTestNg006
 * @tc.desc: Test Slider OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg006, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
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
    EXPECT_EQ(sliderPattern->OnKeyEvent(event), false);
    /**
     * @tc.cases: case2. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT, MoveStep(-1).
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_EQ(sliderPattern->OnKeyEvent(event), false);
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.49f));
    /**
     * @tc.cases: case3. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_EQ(sliderPattern->OnKeyEvent(event), false);
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.5f));
    /**
     * @tc.cases: case4. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP, MoveStep(-1).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_EQ(sliderPattern->OnKeyEvent(event), false);
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.49f));
    /**
     * @tc.cases: case5. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    EXPECT_EQ(sliderPattern->OnKeyEvent(event), false);
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.5f));
}

/**
 * @tc.name: SliderPatternTestNg007
 * @tc.desc: Test Slider HandlingGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg007, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    EXPECT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(sliderLayoutProperty, nullptr);
    /**
     * @tc.cases: case1. InputEventType is AXIS and info.GetMainDelta() <= 0.0.
     */
    sliderPattern->value_ = -2;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, .0);
    /**
     * @tc.cases: case2. InputEventType is AXIS and info.GetMainDelta() > 0.0.
     */
    info.mainDelta_ = 1.0;
    sliderPaintProperty->UpdateStep(.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, .0);
    /**
     * @tc.cases: case3. InputEventType is not AXIS, direction is HORIZONTAL and revese is false.
     */
    info.inputEventType_ = InputEventType::KEYBOARD;
    sliderPattern->sliderLength_ = 52.0f;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 19);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, true);
    /**
     * @tc.cases: case4. InputEventType is not AXIS, direction is VERTICAL and revese is true.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderPaintProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 62);
}

/**
 * @tc.name: SliderPatternTestNg008
 * @tc.desc: Test Slider min max value steps error value
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and slider min value is greater than max value.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MAX_LABEL, MIN_LABEL);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto paintProperty = sliderPattern->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(paintProperty, nullptr);
    /**
     * @tc.cases: case1. when slider min value is greater than max value, take 0 as min value,
     *                   and take 100 as max value by default.
     */
    sliderPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetMin().value(), MIN);
    EXPECT_EQ(paintProperty->GetMax().value(), MAX);
    /**
     * @tc.cases: case2. when slider value is greater than max value, take max value as current value;
     *                   when slider value is less than min value, take min value as current value.
     */
    paintProperty->UpdateMin(MIN_LABEL);
    paintProperty->UpdateMax(MAX_LABEL);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetValue().value(), MAX_LABEL);
    paintProperty->UpdateValue(0);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetValue().value(), MIN_LABEL);
    /**
     * @tc.cases: case3. when slider stepSize value is less than or equal to 0, take 1 by defualt;
     */
    paintProperty->UpdateValue(VALUE);
    paintProperty->UpdateStep(0);
    paintProperty->UpdateMin(MIN);
    paintProperty->UpdateMax(MAX);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetStep().value(), STEP);
    paintProperty->UpdateStep(-1);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(paintProperty->GetStep().value(), STEP);
}

/**
 * @tc.name: SliderLayoutAlgorithm001
 * @tc.desc: Test SliderLayoutAlgorithm MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderframeNode and LayoutProperty.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    EXPECT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(sliderLayoutProperty, nullptr);
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetTrackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS;
    sliderTheme->insetTrackThickness_ = SLIDER_INSET_TRACK_THICKNRESS;
    sliderTheme->outsetBlockSize_ = SLIDER_OUTSET_BLOCK_SIZE;
    sliderTheme->insetBlockSize_ = SLIDER_INSET_BLOCK_SIZE;
    sliderTheme->outsetBlockHotSize_ = SLIDER_OUTSET_BLOCK_HOTSIZE;
    sliderTheme->insetBlockHotSize_ = SLIDER_INSET_BLOCK_HOTSIZE;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step2. create layoutWrapper and sliderLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    EXPECT_NE(sliderLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3. start SliderLayoutAlgorithm MeasureContent func.
     * @tc.expected: step3. sliderSize is the same with expected value.
     */
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    /**
     * @tc.cases: case1. sliderMode is OUTSET and direction is Axis::HORIZONTAL.
     */
    auto size1 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH.ConvertToPx(), std::max(SLIDER_OUTSET_BLOCK_HOTSIZE.ConvertToPx(),
                                                            SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx())));
    /**
     * @tc.cases: case2. sliderMode is OUTSET and direction is Axis::VERTICAL.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto size2 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(),
        SizeF(std::max(SLIDER_OUTSET_BLOCK_HOTSIZE.ConvertToPx(), SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx()),
            WIDTH.ConvertToPx()));
    /**
     * @tc.cases: case3. sliderMode is INSET and direction is Axis::VERTICAL.
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    auto size3 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(HEIGHT.ConvertToPx(), HEIGHT.ConvertToPx()));
    /**
     * @tc.cases: case4. sliderMode is INSET and direction is Axis::HORIZONTAL.
     */
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto size4 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size4, std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(HEIGHT.ConvertToPx(), HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SliderLayoutAlgorithm002
 * @tc.desc: Test SliderLayoutAlgorithm Layout.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create layoutWrapper and sliderLayoutAlgorithm.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    LayoutWrapper layoutWrapper = LayoutWrapper(nullptr, geometryNode, sliderLayoutProperty);
    RefPtr<GeometryNode> bubbleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(bubbleGeometryNode, nullptr);
    bubbleGeometryNode->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    RefPtr<LayoutWrapper> bubbleLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, bubbleGeometryNode, nullptr);
    EXPECT_NE(bubbleLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(bubbleLayoutWrapper));
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper.Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->bubbleToCircleCenterDistance_ = 20.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step2. start SliderLayoutAlgorithm Layout func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    EXPECT_NE(sliderLayoutAlgorithm, nullptr);
    sliderLayoutAlgorithm->Measure(&layoutWrapper);
    sliderLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(bubbleGeometryNode->frame_.rect_.GetOffset(), OffsetF(-FRAME_WIDTH / 2, (MAX_HEIGHT - FRAME_HEIGHT) / 2));
    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutAlgorithm->Measure(&layoutWrapper);
    sliderLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(bubbleGeometryNode->frame_.rect_.GetOffset(), OffsetF((MAX_WIDTH - FRAME_WIDTH) / 2, -FRAME_HEIGHT / 2));
}

/**
 * @tc.name: SliderModelNgTest001
 * @tc.desc: TEST slider_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetBlockBorderColor(TEST_COLOR);
    sliderModelNG.SetBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderModelNG.SetStepColor(TEST_COLOR);
    sliderModelNG.SetTrackBorderRadius(SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    Size silderSize = Size(SLIDER_WIDTH, SLIDER_HEIGHT);
    sliderModelNG.SetBlockSize(silderSize);
    sliderModelNG.SetBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderModelNG.SetBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderModelNG.SetBlockShape(basicShape);
    sliderModelNG.SetStepSize(SLIDER_MODEL_NG_STEP_SIZE);

    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderWidth(), SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    EXPECT_EQ(sliderPaintProperty->GetStepColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBorderRadius(), SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderPaintProperty->GetBlockType(), SliderModel::BlockStyleType::IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockImage(), SLIDER_MODEL_NG_BLOCK_IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockShape(), basicShape);
}

/**
 * @tc.name: SliderPaintPropertyTest001
 * @tc.desc: Test slider_paint_property.h
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step1. create sliderPaintProperty.
     */
    RefPtr<SliderPaintProperty> sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. call ToJsonValue.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderPaintProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
    sliderPaintProperty->UpdateBlockBorderColor(TEST_COLOR);
    sliderPaintProperty->UpdateBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderPaintProperty->UpdateStepColor(TEST_COLOR);
    sliderPaintProperty->UpdateTrackBorderRadius(SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    SizeF blockSize;
    sliderPaintProperty->UpdateBlockSize(blockSize);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderPaintProperty->UpdateBlockShape(basicShape);
    sliderPaintProperty->UpdateStepSize(SLIDER_MODEL_NG_STEP_SIZE);
}

/**
 * @tc.name: SliderLayoutPropertyTest001
 * @tc.desc: Test slider_layout_property.h
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step1. create sliderPaintProperty.
     */
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. call ToJsonValue.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderLayoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: SliderPatternTest001
 * @tc.desc: Test slider_pattern
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     * @tc.steps: step2. call function
     */
    sliderPattern->CreateNodePaintMethod();
    sliderPattern->GetBlockCenter();

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    // set BlockStyleType IMAGE
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);

    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    sliderPattern->UpdateBlock();

    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);

    // set TouchType UP
    touchLocationInfo.SetTouchType(TouchType::UP);

    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
}

/**
 * @tc.name: SliderPatternTest002
 * @tc.desc: Test slider_pattern
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest002, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    // set sliderPattern
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());

    sliderPattern->CreateNodePaintMethod();
    sliderPattern->GetBlockCenter();

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    // set BlockStyleType IMAGE
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    sliderPattern->UpdateBlock();

    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);

    // set TouchType UP
    touchLocationInfo.SetTouchType(TouchType::UP);

    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
}

/**
 * @tc.name: SliderPatternTest003
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest003, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, sliderLayoutProperty);
    layoutWrapper->skipMeasureContent_ = false;
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, sliderLayoutProperty);

    RefPtr<SliderLayoutAlgorithm> sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = 40.0f;

    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    layoutWrapper->AppendChild(secondLayoutWrapper);
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest001
 * @tc.desc: Test slider_layout_algorithm
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest001, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    LayoutWrapper* pLayoutWrapper = new LayoutWrapper(nullptr, geometryNode, sliderLayoutProperty);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, geometryNode, sliderLayoutProperty);

    pLayoutWrapper->AppendChild(layoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pLayoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());

    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(pLayoutWrapper);
    sliderLayoutAlgorithm.Layout(pLayoutWrapper);
}

/**
 * @tc.name: SliderLayoutAlgorithmTest002
 * @tc.desc: Test slider_layout_algorithm.cpp  Reverse=true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest002, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    // set reverse true
    sliderLayoutProperty->UpdateReverse(true);

    LayoutWrapper* pLayoutWrapper = new LayoutWrapper(nullptr, geometryNode, sliderLayoutProperty);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, geometryNode, sliderLayoutProperty);

    pLayoutWrapper->AppendChild(layoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pLayoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());

    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(pLayoutWrapper);
    sliderLayoutAlgorithm.Layout(pLayoutWrapper);
}

/**
 * @tc.name: SliderLayoutAlgorithmTest003
 * @tc.desc: Test slider_layout_algorithm
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest003, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateReverse(true);

    LayoutWrapper* pLayoutWrapper = new LayoutWrapper(nullptr, geometryNode, sliderLayoutProperty);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, geometryNode, sliderLayoutProperty);

    pLayoutWrapper->AppendChild(layoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    pLayoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());

    // set layoutConstraintSizevalid
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    // test MeasureContent function
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, pLayoutWrapper);
}
} // namespace OHOS::Ace::NG

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

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"

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
constexpr Dimension HUGE_WIDTH = 500000000.0_vp;
constexpr Dimension HUGE_HEIGHT = 500000000.0_vp;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float FRAME_WIDTH = 10.0f;
constexpr float FRAME_HEIGHT = 20.0f;
constexpr Dimension SLIDER_OUTSET_TRACK_THICKNRESS = Dimension(10.0);
constexpr Dimension SLIDER_INSET_TRACK_THICKNRESS = Dimension(20.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_SIZE = Dimension(30.0);
constexpr Dimension SLIDER_INSET_BLOCK_SIZE = Dimension(15.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_HOTSIZE = Dimension(50.0);
constexpr Dimension SLIDER_INSET_BLOCK_HOTSIZE = Dimension(60.0);
constexpr Dimension SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_TRACK_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_STEP_SIZE = Dimension(10.0);
constexpr Dimension RADIUS = Dimension(10.0);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH = 10.0f;
constexpr float HALF = 0.5;
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Dimension BLOCK_SIZE_WIDTH = Dimension(300.0);
constexpr Dimension BLOCK_SIZE_HEIGHT = Dimension(300.0);
const SizeT<Dimension> BLOCK_SIZE(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
const std::string SLIDER_MODEL_NG_BLOCK_IMAGE = "Default Image";
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
const PointF SELECT_START { 10.0f, 10.0f };
const PointF SELECT_END { 20.0f, 20.0f };
const PointF POINTF_CENTER { 15.0f, 15.0f };
const Dimension RADIUS_X = Dimension(20.1, DimensionUnit::PX);
const Dimension RADIUS_Y = Dimension(20.1, DimensionUnit::PX);
const Dimension SHAPE_WIDTH = 10.0_vp;
const Dimension SHAPE_HEIGHT = 20.0_vp;
constexpr float CONTENT_WIDTH = 100.0f;
constexpr float CONTENT_HEIGHT = 50.0f;
constexpr float HOT_BLOCK_SHADOW_WIDTH = 3.0f;
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
constexpr Dimension TRACK_BORDER_RADIUS = 5.0_px;
} // namespace
class SliderPatternTestNg : public testing::Test {
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

void SliderPatternTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void SliderPatternTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void SliderPatternTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderPatternTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
{
    sliderContentModifier.InitializeShapeProperty();
    sliderContentModifier.SetTrackThickness(SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    sliderContentModifier.SetTrackBorderRadius(SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    sliderContentModifier.SetTrackBackgroundColor(TEST_COLOR);
    sliderContentModifier.SetShowSteps(true);
    sliderContentModifier.SetStepSize(SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    sliderContentModifier.SetStepColor(TEST_COLOR);
    sliderContentModifier.SetStepRatio(SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetSelectColor(TEST_COLOR);
    sliderContentModifier.SetBlockColor(TEST_COLOR);
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderPatternTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
}

void SliderPatternTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
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
     *     case 1: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    bool firstCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(firstCase);
    /**
     *     case 2: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = false;
     */
    bool secondCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(secondCase);
    /**
     *    case 3: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = true;
     */
    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    bool thirdCase = sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(thirdCase);
    /**
     *    case 4: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = false, and directions is HORIZONTAL,
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
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set theme.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->tipTextPadding_ = Dimension(10.0);
    sliderTheme->tipColor_ = Color::BLUE;
    sliderTheme->tipFontSize_ = Dimension(16.0);
    sliderTheme->tipTextColor_ = Color::BLACK;
    EXPECT_CALL(*theme, GetTheme(_)).WillOnce(Return(sliderTheme));
    /**
     * @tc.steps: step3. get sliderPattern and test init parameter.
     */
    RefPtr<SliderPattern> sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = sliderPattern->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(sliderPattern->value_, VALUE);
    EXPECT_EQ(sliderPattern->valueRatio_, .5f);
    EXPECT_EQ(sliderPattern->stepRatio_, .01f);
    EXPECT_EQ(sliderPattern->showTips_, false);
    EXPECT_EQ(sliderPaintProperty->GetPadding(), std::nullopt);
    EXPECT_EQ(sliderPaintProperty->GetTipColor(), std::nullopt);
    EXPECT_EQ(sliderPaintProperty->GetTextColor(), std::nullopt);
    EXPECT_EQ(sliderPaintProperty->GetFontSize(), std::nullopt);
    EXPECT_EQ(sliderPaintProperty->GetContent(), std::nullopt);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignmentValue(), Alignment::CENTER);
    /**
     * @tc.steps: step4. when showTips is true.
     */
    sliderPaintProperty->UpdateShowTips(true);
    sliderPattern->OnModifyDone();
    EXPECT_EQ(sliderPattern->showTips_, true);
    EXPECT_EQ(sliderPaintProperty->GetPaddingValue(Dimension()), Dimension(10.0));
    EXPECT_EQ(sliderPaintProperty->GetTipColorValue(Color::BLACK), Color::BLUE);
    EXPECT_EQ(sliderPaintProperty->GetTextColorValue(Color::BLUE), Color::BLACK);
    EXPECT_EQ(sliderPaintProperty->GetFontSizeValue(Dimension()), Dimension(16.0));
    EXPECT_NE(sliderPaintProperty->GetContent(), std::nullopt);
}

/**
 * @tc.name: SliderPatternTestNg005
 * @tc.desc: Test Slider HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    EXPECT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetFrameSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxIntrinsicWidth()).WillRepeatedly(Return(.0f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(.0f));
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
    sliderPattern->showTips_ = true;
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->bubbleFlag_, true);
    /**
     * @tc.cases: case2. when TouchType is DOWN and direction is VERTICAL.
     */
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    sliderPaintProperty->UpdateReverse(true);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, false);
    /**
     * @tc.cases: case3. when TouchType is UP.
     */
    info.changedTouches_.front().touchType_ = TouchType::UP;
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
    EXPECT_FALSE(sliderPattern->OnKeyEvent(event));
    /**
     * @tc.cases: case2. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT, MoveStep(-1).
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.49f));
    /**
     * @tc.cases: case3. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.5f));
    /**
     * @tc.cases: case4. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP, MoveStep(-1).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_TRUE(NearEqual(sliderPattern->valueRatio_, 0.49f));
    /**
     * @tc.cases: case5. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
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
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    /**
     * @tc.cases: case1. InputEventType is AXIS and MoveStep(-1).
     */
    sliderPattern->value_ = 1.0f;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    info.SetOffsetX(.0);
    info.SetOffsetY(1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, .02f);
    EXPECT_EQ(sliderPattern->value_, 2.0f);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0.01f);
    EXPECT_EQ(sliderPattern->value_, 1.0f);
    sliderPaintProperty->UpdateStep(.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0.01f);
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
 * @tc.name: SliderPatternTestNg009
 * @tc.desc: Test Slider ThackThickness error value
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg009, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetTrackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS;
    sliderTheme->insetTrackThickness_ = SLIDER_INSET_TRACK_THICKNRESS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create slider and get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetThickness(Dimension(-1));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    /**
     * @tc.cases: case1. slider mode = OUTSET, TrackThickness = OutsetTrackThickness.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetThickness(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetThickness().value(), SLIDER_OUTSET_TRACK_THICKNRESS);
    /**
     * @tc.cases: case2. slider mode = INSET, TrackThickness = InsetTrackThickness.
     */
    sliderModelNG.SetSliderMode(SliderModel::SliderMode::INSET);
    sliderModelNG.SetThickness(Dimension(0));
    EXPECT_NE(layoutProperty->GetThickness(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetThickness().value(), SLIDER_INSET_TRACK_THICKNRESS);
}

/**
 * @tc.name: SliderPatternTestNg010
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is mouse
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
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
    /**
     * @tc.steps: step2. initialize touch information.
     * @tc.desc:  when TouchType is DOWN, SourceType is mouse touch.
     */
    TouchLocationInfo LInfo(0);
    LInfo.touchType_ = TouchType::DOWN;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::MOUSE);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
    /**
     * @tc.cases: case1. mouse down position is outside the block side, UpdateValueByLocalLocation
     */
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    /**
     * @tc.cases: case2. mouse down position is inside the block side, not UpdateValueByLocalLocation
     */
    sliderPattern->circleCenter_.Reset();
    sliderPattern->blockSize_ = SizeF(MAX_LABEL, MAX_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderPatternTestNg011
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is touch
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
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
    /**
     * @tc.steps: step2. initialize touch information.
     * @tc.desc:  when TouchType is DOWN, SourceType is touch.
     */
    TouchLocationInfo LInfo(0);
    LInfo.touchType_ = TouchType::DOWN;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::TOUCH);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
    sliderPattern->blockHotSize_ = SizeF(MIN_LABEL, MIN_LABEL);
    /**
     * @tc.cases: case1. touch down position is outside the blockHotSize, UpdateValueByLocalLocation
     */
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MIN_LABEL, -MAX_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    sliderPattern->value_ = VALUE;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(-MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f); // Exceeding the leftmost end, take 0
    /**
     * @tc.cases: case2. touch down position is inside the blockHotSize, not UpdateValueByLocalLocation
     */
    info.changedTouches_.front().localLocation_ = Offset();
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderPatternTestNg012
 * @tc.desc: Test Slider mouse Event and wheel operation
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->showTips_ = true;
    /**
     * @tc.steps: step2. When the mouse moves into the slider area.
     */
    sliderPattern->HandleHoverEvent(true);
    EXPECT_TRUE(sliderPattern->hotFlag_);
    EXPECT_TRUE(sliderPattern->mouseHoverFlag_);
    /**
     * @tc.steps: step3. When the mouse wheel starts scrolling.
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
    EXPECT_TRUE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step4. After the mouse wheel starts scrolling, move the mouse out of the slider area
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->HandleHoverEvent(false);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step5. When moving the mouse out of the slider area, mouse wheel starts scrolling quickly.
     * @tc.desc: SliderTips will not show.
     */
    sliderPattern->HandleHoverEvent(true);
    sliderPattern->HandleHoverEvent(false);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, sliderLayoutProperty);
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
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(nullptr, geometryNode, sliderLayoutProperty);
    RefPtr<GeometryNode> bubbleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(bubbleGeometryNode, nullptr);
    bubbleGeometryNode->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    RefPtr<LayoutWrapperNode> bubbleLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, bubbleGeometryNode, nullptr);
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
 * @tc.name: SliderLayoutAlgorithm003
 * @tc.desc: Test SliderLayoutAlgorithm MeasureContent when trackThickness is greater than slider width or height.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithm003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetTrackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS;
    sliderTheme->insetTrackThickness_ = SLIDER_INSET_TRACK_THICKNRESS;
    sliderTheme->outsetBlockSize_ = SLIDER_OUTSET_BLOCK_SIZE;
    sliderTheme->insetBlockSize_ = SLIDER_INSET_BLOCK_SIZE;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create layoutWrapper and sliderLayoutAlgorithm.
     */
    auto sliderLayoutProperty = AceType::MakeRefPtr<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateThickness(Dimension(40.0));
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(nullptr, nullptr, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    ASSERT_NE(sliderLayoutAlgorithm, nullptr);
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step2. start SliderLayoutAlgorithm MeasureContent func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(sliderLayoutAlgorithm->GetTrackThickness(), SLIDER_OUTSET_TRACK_THICKNRESS.ConvertToPx());
    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    sliderLayoutProperty->UpdateThickness(Dimension(40.0));
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(sliderLayoutAlgorithm->GetTrackThickness(), SLIDER_INSET_TRACK_THICKNRESS.ConvertToPx());
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
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
    sliderModelNG.SetBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderModelNG.SetBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderModelNG.SetBlockShape(basicShape);
    sliderModelNG.SetStepSize(SLIDER_MODEL_NG_STEP_SIZE);
    sliderModelNG.SetShowTips(true, std::nullopt);
    sliderModelNG.SetShowTips(false, "content");

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

    /**
     * @tc.steps: step3. reset the properties.
     */
    sliderModelNG.ResetBlockBorderColor();
    sliderModelNG.ResetBlockBorderWidth();
    sliderModelNG.ResetTrackBorderRadius();
    sliderModelNG.ResetStepColor();
    sliderModelNG.ResetStepSize();
    sliderModelNG.ResetBlockType();
    sliderModelNG.ResetBlockImage();
    sliderModelNG.ResetBlockShape();
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step4. check whether the properties is correct.
     * @tc.expected: step4. check whether the properties is correct.
     */
    EXPECT_FALSE(sliderPaintProperty->GetBlockBorderColor().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetBlockBorderWidth().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetTrackBorderRadius().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetStepColor().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetStepSize().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetBlockType().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetBlockImage().has_value());
    EXPECT_FALSE(sliderPaintProperty->GetBlockShape().has_value());
}

/**
 * @tc.name: SliderModelNgTest002
 * @tc.desc: TEST slider_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderModelNgTest002, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create slider.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetBlockSize with invalid parameters.
     * @tc.expected: step2. check the BlockSize property not be set.
     */
    sliderModelNG.SetBlockSize(Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());

    /**
     * @tc.steps: step3. call SetBlockSize with invalid parameters while BlockSize property has been set.
     * @tc.expected: step3. check the BlockSize property has reset.
     */
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
    EXPECT_TRUE(sliderLayoutProperty->GetBlockSize().has_value());
    sliderModelNG.SetBlockSize(Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());
}

/**
 * @tc.name: SliderContentModifierTest001
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = HORIZONTAL, blockType = DEFAULT, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set direction FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set needAnimate_ false
    sliderContentModifier.SetNotAnimated();
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType DEFAULT
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::DEFAULT));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest002
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.GetBlockCenter();
    sliderContentModifier.GetTrackThickness();
    sliderContentModifier.GetBlockSize();
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest003
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    auto circle = AceType::DynamicCast<Circle>(basicShape);
    circle->SetRadius(RADIUS);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest004
 * @tc.desc: TEST slider_content_modifier onDraw and DrawSelect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.SetDirection(Axis::FREE);
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.DrawSelect(context);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest005
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest006
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = ELLIPSE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType ELLIPSE
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    basicShape->SetBasicShapeType(BasicShapeType::ELLIPSE);
    basicShape->SetRadiusX(RADIUS_X);
    basicShape->SetRadiusY(RADIUS_Y);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest007
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = PATH, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType PATH
    auto basicShape = AceType::MakeRefPtr<Path>();
    basicShape->SetBasicShapeType(BasicShapeType::PATH);
    basicShape->SetValue("PATH");
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode INSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    sliderContentModifier.SetBlockSize(SizeF(BLOCK_SIZE_WIDTH.ConvertToPx(), BLOCK_SIZE_HEIGHT.ConvertToPx()));
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest008
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = RECT, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType RECT
    auto basicShape = AceType::MakeRefPtr<ShapeRect>();
    basicShape->SetBasicShapeType(BasicShapeType::RECT);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest009
 * @tc.desc: TEST slider_content_modifier SetBlockShape with invalid circle
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid circle.
     */
    auto basicShape = AceType::MakeRefPtr<Circle>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetRadius(Dimension());
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    EXPECT_EQ(sliderContentModifier.circleRadius_->Get(), std::min(SHAPE_WIDTH, SHAPE_HEIGHT).ConvertToPx() * HALF);
}

/**
 * @tc.name: SliderContentModifierTest010
 * @tc.desc: TEST slider_content_modifier SetBlockShape with invalid ellipse
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid ellipse.
     */
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetRadiusX(Dimension());
    basicShape->SetRadiusY(Dimension());
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    EXPECT_EQ(sliderContentModifier.ellipseRadiusX_->Get(), SHAPE_WIDTH.ConvertToPx() * HALF);
    EXPECT_EQ(sliderContentModifier.ellipseRadiusY_->Get(), SHAPE_HEIGHT.ConvertToPx() * HALF);
}

/**
 * @tc.name: SliderContentModifierTest011
 * @tc.desc: TEST slider_content_modifier DrawBlockShape with invalid shape
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid shape.
     */
    auto basicShape = AceType::MakeRefPtr<BasicShape>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    // Draw nothing
    sliderContentModifier.DrawBlockShape(context);
    EXPECT_CALL(canvas, AttachBrush(_)).Times(0);
    EXPECT_CALL(canvas, AttachPen(_)).Times(0);
}

/**
 * @tc.name: SliderContentModifierTest012
 * @tc.desc: TEST slider_content_modifier DrawStep with invalid parameter
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    sliderContentModifier.isShowStep_->Set(true);
    sliderContentModifier.stepRatio_->Set(.0f);
    /**
     * @tc.steps: step2. call DrawStep function with invalid parameter.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    // Draw nothing
    sliderContentModifier.DrawStep(context);
    EXPECT_CALL(canvas, AttachBrush(_)).Times(0);
    EXPECT_CALL(canvas, AttachPen(_)).Times(0);
}

/**
 * @tc.name: SliderPaintPropertyTest001
 * @tc.desc: Test slider_paint_property.h Update function
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
     * @tc.steps: step2. create sliderPaintProperty.
     */
    RefPtr<SliderPaintProperty> sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. call ToJsonValue.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderPaintProperty->UpdateTrackBorderRadius(SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    sliderPaintProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
    sliderPaintProperty->UpdateBlockBorderColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderColorValue(Color::TRANSPARENT), TEST_COLOR);
    sliderPaintProperty->UpdateBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderWidthValue(Dimension()), SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderPaintProperty->UpdateStepColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetStepColorValue(Color::TRANSPARENT), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBorderRadiusValue(Dimension()), SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT),
        SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    std::string defaultImage = "Default";
    EXPECT_EQ(sliderPaintProperty->GetBlockImageValue(defaultImage), SLIDER_MODEL_NG_BLOCK_IMAGE);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderPaintProperty->UpdateBlockShape(basicShape);
    EXPECT_EQ(sliderPaintProperty->GetBlockShapeValue(AceType::MakeRefPtr<BasicShape>()), basicShape);
    sliderPaintProperty->UpdateStepSize(SLIDER_MODEL_NG_STEP_SIZE);
    EXPECT_EQ(sliderPaintProperty->GetStepSizeValue(Dimension()), SLIDER_MODEL_NG_STEP_SIZE);
}

/**
 * @tc.name: SliderLayoutPropertyTest001
 * @tc.desc: Test slider_layout_property.h ToJsonValue
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
     * @tc.steps: step2. create sliderPaintProperty.
     */
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SizeT<Dimension> blockSize;
    sliderLayoutProperty->UpdateBlockSize(blockSize);
    EXPECT_EQ(sliderLayoutProperty->GetBlockSizeValue(SizeF()), SizeF());

    /**
     * @tc.steps: step3. call ToJsonValue when SliderMode = OUTSET/INSET
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderLayoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutProperty->ResetBlockSize();
    sliderLayoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: SliderPatternTest001
 * @tc.desc: Test slider_pattern UpdateBlock/CreateNodePaintMethod/GetBlockCenter/HandleTouchEvent
 * imageFrameNode_ == nullptr
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
     * @tc.steps: step2. set BlockStyleType IMAGE
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);

    // set TouchType UP
    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);

    // call function
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, false);
    sliderPattern->UpdateBlock();
    sliderPattern->LayoutImageNode();
    sliderPattern->bubbleFlag_ = true;
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPattern->sliderTipModifier_->getBubbleVertexFunc_();
    sliderPattern->UpdateCircleCenterOffset();
    auto contentSize = sliderPattern->GetHostContentSize();
    EXPECT_EQ(sliderPattern->GetBlockCenter().GetY(), contentSize->Height() * HALF);
}

/**
 * @tc.name: SliderPatternTest002
 * @tc.desc: Test slider_pattern UpdateBlock/CreateNodePaintMethod/GetBlockCenter/HandleTouchEvent
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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
    /**
     * @tc.steps: step2. set attribute and call function.
     */
    // set BlockStyleType IMAGE
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    // set TouchType UP
    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    // set sliderPattern
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, false);
    sliderPattern->UpdateBlock();
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::DEFAULT);
    sliderPattern->UpdateBlock();
    sliderPattern->UpdateCircleCenterOffset();
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->UpdateCircleCenterOffset();
    auto contentSize = sliderPattern->GetHostContentSize();
    EXPECT_EQ(sliderPattern->GetBlockCenter().GetX(), contentSize->Width() * HALF);
}

/**
 * @tc.name: SliderPatternTest003
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    layoutWrapper->skipMeasureContent_ = false;
    RefPtr<LayoutWrapperNode> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);

    RefPtr<SliderLayoutAlgorithm> sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    // set theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
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
 * @tc.name: SliderPatternTest004
 * @tc.desc: Test slider pattern GetOutsetInnerFocusPaintRect function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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
    /**
     * @tc.steps: step2. call GetOutsetInnerFocusPaintRect function.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    RoundRect focusRect;
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusDistance = paintWidth * HALF + sliderTheme->GetFocusSideDistance();

    // vaild circle
    basicShape->SetRadius(RADIUS);
    sliderPaintProperty->UpdateBlockShape(basicShape);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        RADIUS.ConvertToPx() + focusDistance.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        RADIUS.ConvertToPx() + focusDistance.ConvertToPx());

    // invalid circle: radius = 0
    basicShape = AceType::MakeRefPtr<Circle>();
    sliderPaintProperty->UpdateBlockShape(basicShape);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        std::min(basicShape->GetWidth(), basicShape->GetHeight()).ConvertToPx() * HALF + focusDistance.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        std::min(basicShape->GetWidth(), basicShape->GetHeight()).ConvertToPx() * HALF + focusDistance.ConvertToPx());

    // revert to default
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.radius_.GetCorner(0).x, 1.0f);
    EXPECT_EQ(focusRect.radius_.GetCorner(0).y, 1.0f);
}

/**
 * @tc.name: SliderPatternTest005
 * @tc.desc: Test SliderPattern::OnDirtyLayoutWrapperSwap function.
 *           Calculate the value of borderBlank_ in the INSET/OUTSET scenario.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and prepare environment.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    ASSERT_NE(sliderLayoutAlgorithm, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false, false);
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH, CONTENT_HEIGHT));
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(HOT_BLOCK_SHADOW_WIDTH);

    /**
     * @tc.steps: step2. Calculate in the INSET scenario.
     * @tc.expected: borderBlank_ == block_width / 2 + shadow_width
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_INSET_TRACK_THICKNRESS.Value();
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_INSET_BLOCK_SIZE.Value(), SLIDER_INSET_BLOCK_SIZE.Value());
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_, SLIDER_INSET_TRACK_THICKNRESS.Value() * HALF + HOT_BLOCK_SHADOW_WIDTH);

    /**
     * @tc.steps: step3. Calculate in the OUTSET scenario.
     * @tc.expected: borderBlank_ == max(block_width, track_thickness) / 2 + shadow_width
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS.Value();
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_,
        std::max(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_TRACK_THICKNRESS.Value()) * HALF +
            HOT_BLOCK_SHADOW_WIDTH);
}

/**
 * @tc.name: SliderPatternTest006
 * @tc.desc: Test slider_pattern CreateNodePaintMethod/HandlingGestureEvent/OnKeyEvent
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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
    /**
     * @tc.steps: step2. set attribute and call function.
     */
    // mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));

    // set key event
    auto func = [&sliderPattern]() {
        KeyEvent keyEvent;
        sliderPattern->direction_ = Axis::HORIZONTAL;
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_LEFT;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::UP;
        sliderPattern->OnKeyEvent(keyEvent);
        sliderPattern->OnKeyEvent(keyEvent);

        sliderPattern->direction_ = Axis::VERTICAL;
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_UP;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_DOWN;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::UNKNOWN;
        sliderPattern->OnKeyEvent(keyEvent);
    };

    func();
    sliderPattern->showTips_ = true;
    func();

    // set gesture input event
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetOffsetX(-1);
    sliderPattern->HandlingGestureEvent(info);
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPattern->HandledGestureEvent();
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: SliderPatternTest007
 * @tc.desc: Test slider_pattern GetBubbleVertexPosition
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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

    /**
     * @tc.steps: step2. set attribute and call function.
     */
    auto offset = BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx();
    sliderPattern->direction_ = Axis::HORIZONTAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()), OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()), OffsetF(-offset, 0));

    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderPattern->direction_ = Axis::HORIZONTAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()), OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()), OffsetF(-offset, 0));
}

/**
 * @tc.name: SliderPatternTest008
 * @tc.desc: Test SliderPattern GetInsetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and prepare environment.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    ASSERT_NE(sliderTheme, nullptr);
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    ASSERT_NE(appTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));
    auto focusDistance =
        sliderTheme->GetFocusSideDistance().ConvertToPx() + (appTheme->GetFocusWidthVp().ConvertToPx() * HALF);
    RoundRect roundRect;
    sliderPattern->trackThickness_ = SLIDER_HEIGHT;
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH, CONTENT_HEIGHT));

    /**
     * @tc.steps: step2. call GetInsetInnerFocusPaintRect without TrackBorderRadius property.
     * @tc.expected: step2. radius == (TrackThickness / 2 + focusWidth).
     */
    sliderPattern->direction_ = Axis::HORIZONTAL;
    sliderPattern->GetInsetInnerFocusPaintRect(roundRect);
    auto radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, (SLIDER_HEIGHT * HALF) + focusDistance);
    EXPECT_EQ(radius.y, (SLIDER_HEIGHT * HALF) + focusDistance);

    /**
     * @tc.steps: step3. call GetInsetInnerFocusPaintRect with TrackBorderRadius property.
     * @tc.expected: step3. radius == (TrackBorderRadius + focusWidth).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateTrackBorderRadius(TRACK_BORDER_RADIUS);
    sliderPattern->GetInsetInnerFocusPaintRect(roundRect);
    radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
    EXPECT_EQ(radius.y, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
}

/**
 * @tc.name: SliderPatternTest009
 * @tc.desc: Test slider_pattern onBlurInternal_ HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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

    /**
     * @tc.steps: step2. call focusHub onBlurInternal callback.
     * @tc.expected: step2. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    auto focusHub = frameNode->GetOrCreateFocusHub();
    sliderPattern->OnModifyDone();
    focusHub->onBlurInternal_();
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step3. Mouse on slider block.
     * @tc.expected: step3. sliderPattern->bubbleFlag_ is true.
     */
    MouseInfo mouseInfo;
    sliderPattern->blockSize_ = SizeF(MAX_WIDTH, MAX_HEIGHT);
    sliderPattern->showTips_ = true;
    sliderPattern->HandleMouseEvent(mouseInfo);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step4. Mouse not on slider block.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->blockSize_ = SizeF(0, 0);
    sliderPattern->HandleMouseEvent(mouseInfo);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest010
 * @tc.desc: Test slider_pattern HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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

    /**
     * @tc.steps: step2. call HandleHoverEvent hover false with normal.
     * @tc.expected: step2. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->focusFlag_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step3. call HandleHoverEvent hover false with mouse pressed.
     * @tc.expected: step3. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = true;
    sliderPattern->focusFlag_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step4. call HandleHoverEvent hover false with focus.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->focusFlag_ = true;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step5. call HandleHoverEvent hover true.
     * @tc.expected: step5. sliderPattern->bubbleFlag_ is true.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->focusFlag_ = false;
    sliderPattern->HandleHoverEvent(true);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest011
 * @tc.desc: Test slider_pattern AtMousePanArea
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
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
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. modify circleCenter and blockSize.
     */
    sliderPattern->blockSize_.SetWidth(SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx());
    sliderPattern->blockSize_.SetHeight(SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx());
    sliderPattern->circleCenter_.SetX(sliderPattern->blockSize_.Width() * HALF);
    sliderPattern->circleCenter_.SetY(sliderPattern->blockSize_.Height() * HALF);

    /**
     * @tc.cases: case1. the offset(1,1) is not in circle block.
     */
    Offset offsetInFrame(1, 1);
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    ASSERT_FALSE(sliderPattern->AtMousePanArea(offsetInFrame));

    /**
     * @tc.cases: case2. the offset(1,1) is in rect block.
     */
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::SHAPE);
    ASSERT_TRUE(sliderPattern->AtMousePanArea(offsetInFrame));
}

/**
 * @tc.name: SliderPatternTest012
 * @tc.desc: Test slider_pattern InitPanEvent and event callback.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto hub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);

    /**
     * @tc.steps: step2. start SliderPattern InitPanEvent func.
     */
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    GestureEvent info = GestureEvent();
    sliderPattern->InitPanEvent(gestureHub);

    /**
     * @tc.steps: step3. call event callback func.
     */
    sliderPattern->sliderContentModifier_->needAnimate_ = false;
    sliderPattern->panEvent_->actionStart_(info);
    ASSERT_TRUE(sliderPattern->sliderContentModifier_->needAnimate_);

    sliderPattern->sliderContentModifier_->needAnimate_ = false;
    sliderPattern->panEvent_->actionUpdate_(info);
    ASSERT_TRUE(sliderPattern->sliderContentModifier_->needAnimate_);

    sliderPattern->sliderContentModifier_->needAnimate_ = true;
    sliderPattern->panEvent_->actionEnd_(info);
    ASSERT_FALSE(sliderPattern->sliderContentModifier_->needAnimate_);

    sliderPattern->sliderContentModifier_->needAnimate_ = true;
    sliderPattern->panEvent_->actionCancel_();
    ASSERT_FALSE(sliderPattern->sliderContentModifier_->needAnimate_);
}

/**
 * @tc.name: SliderPatternTest013
 * @tc.desc: Test slider_pattern InitPanEvent and event callback.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest013, TestSize.Level1)
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
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    ASSERT_NE(sliderPattern->sliderContentModifier_, nullptr);

    /**
     * @tc.steps: step2. set BlockStyleType IMAGE
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    sliderPattern->UpdateBlock();
    ASSERT_NE(sliderPattern->imageFrameNode_, nullptr);

    /**
     * @tc.steps: step3. update block center.
     */
    sliderPattern->sliderContentModifier_->updateImageCenterX_(FRAME_WIDTH);
    sliderPattern->sliderContentModifier_->updateImageCenterY_(FRAME_HEIGHT);
    auto imageGeometryNode = sliderPattern->imageFrameNode_->GetGeometryNode();
    ASSERT_NE(imageGeometryNode, nullptr);
    auto offset = imageGeometryNode->GetMarginFrameOffset();
    ASSERT_EQ(offset.GetX(), (FRAME_WIDTH - sliderPattern->blockSize_.Width() * HALF));
    ASSERT_EQ(offset.GetY(), (FRAME_HEIGHT - sliderPattern->blockSize_.Height() * HALF));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest001
 * @tc.desc: Test slider_layout_algorithm Measure and Layout(Reverse=false)
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
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

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step2. call Measure and Layout function.
     */
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // set SliderMode INSET
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));

    auto constraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto width = sliderLayoutAlgorithm.blockSize_.Width();
    auto height = sliderLayoutAlgorithm.blockSize_.Height();
    EXPECT_EQ(constraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(width, height)), true);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest002
 * @tc.desc: Test slider_layout_algorithm.cpp  Measure and Layout(Reverse=true)
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call Measure and Layout function.
     */
    // set reverse true
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateReverse(true);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // set Axis VERTICAL
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // pattern->GetAnimatableBlockCenter() != OffsetF()
    auto pattern = AceType::DynamicCast<SliderPattern>(host->GetPattern());
    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    pattern->sliderContentModifier_->blockCenterX_->Set(POINTF_CENTER.GetX());
    pattern->sliderContentModifier_->blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    auto constraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto width = sliderLayoutAlgorithm.blockSize_.Width();
    auto height = sliderLayoutAlgorithm.blockSize_.Height();
    EXPECT_EQ(constraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(width, height)), true);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest003
 * @tc.desc: Test slider_layout_algorithm MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call MeasureContent function.
     */
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateReverse(true);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());

    // set layoutConstraintSizevalid
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(HUGE_WIDTH.ConvertToPx(), HUGE_HEIGHT.ConvertToPx()));
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    // test MeasureContent function
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    auto size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));
    // set Axis VERTICAL(call MeasureContent function)
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));

    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    hSliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));
    auto maxWidth = layoutConstraintSizevalid.maxSize.Width();
    auto selfWidth = layoutConstraintSizevalid.selfIdealSize.Width().value_or(maxWidth);
    EXPECT_EQ(size->Width(), selfWidth);
}

/**
 * @tc.name: SliderLayoutAlgorithmTest004
 * @tc.desc: Test slider_layout_algorithm Layout without child node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderLayoutAlgorithmTest004, TestSize.Level1)
{
    auto sliderLayoutProperty = AceType::MakeRefPtr<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    // No child node would be layout
    sliderLayoutAlgorithm.Layout(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetContentOffset(), OffsetF());
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 0);
}

/**
 * @tc.name: SliderPaintMethodTest001
 * @tc.desc: Test slider_paint_method UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    WeakPtr<RenderContext> renderContext;
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
    MockPipelineBase::SetUp();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    // call UpdateContentModifier function
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(
        sliderPaintMethod.sliderContentModifier_->sliderMode_, static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->blockBorderColor_->Get(), LinearColor(Color::TRANSPARENT));
    EXPECT_EQ(
        sliderPaintMethod.sliderContentModifier_->blockType_, static_cast<int>(SliderModelNG::BlockStyleType::IMAGE));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->directionAxis_, static_cast<int>(Axis::HORIZONTAL));
}

/**
 * @tc.name: SliderPaintMethodTest002
 * @tc.desc: Test slider_paint_method UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    /**
     * @tc.steps: step3. call UpdateOverlayModifier function.
     */
    // set theme
    MockPipelineBase::SetUp();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    Testing::MockCanvas canvas;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    MockParagraphFunction(paragraph, canvas);

    // call UpdateOverlayModifier function
    sliderPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderTipModifier->axis_, Axis::VERTICAL);

    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->paintProperty_)->UpdateDirection(Axis::HORIZONTAL);
    sliderPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderTipModifier->axis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SliderPaintMethodTest003
 * @tc.desc: Test slider_paint_method UpdateContentDirtyRect
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPaintMethodTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create paintWrapper and sliderContentModifier.
     */
    auto sliderContentModifier =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    SliderPaintMethod sliderPaintMethod(sliderContentModifier, SliderContentModifier::Parameters(), 1.0f, 1.0f, nullptr,
        SliderPaintMethod::TipParameters());
    auto sliderPaintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    auto paintWrapper1 = PaintWrapper(nullptr, geometryNode, sliderPaintProperty);
    sliderPaintProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderPaintProperty->UpdateDirection(Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. call UpdateContentModifier function.
     */
    sliderPaintMethod.UpdateContentModifier(&paintWrapper1);
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    auto rect1 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect1->Width(), 130.0f);
    EXPECT_EQ(rect1->Height(), 60.0f);
    sliderPaintProperty->UpdateSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    auto paintWrapper2 = PaintWrapper(nullptr, geometryNode, sliderPaintProperty);
    sliderPaintMethod.UpdateContentModifier(&paintWrapper2);
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::VERTICAL));
    auto rect2 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect2->Width(), 40.0f);
    EXPECT_EQ(rect2->Height(), 100.0f);
}

/**
 * @tc.name: SliderAccessibilityPropertyTest001
 * @tc.desc: Test the HasRange and RangeInfo properties of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderAccessibilityPropertyTest001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_TRUE(sliderAccessibilityProperty->HasRange());
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().current, VALUE);
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().max, MAX);
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().min, MIN);
}

/**
 * @tc.name: SliderAccessibilityPropertyTest002
 * @tc.desc: Test the Text property of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderAccessibilityPropertyTest002, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_EQ(sliderAccessibilityProperty->GetText(), std::to_string(VALUE));
}

/**
 * @tc.name: SliderAccessibilityPropertyTest003
 * @tc.desc: Test the IsScrollable and SupportAction properties of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderAccessibilityPropertyTest003, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_TRUE(sliderAccessibilityProperty->IsScrollable());
    
    sliderAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = sliderAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: SliderContentModifierTest013
 * @tc.desc: Test DrawStep while not show step
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest013, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    auto isShowStep = AceType::MakeRefPtr<PropertyBool>(false);
    sliderContentModifier.isShowStep_ = isShowStep;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawStep(context);
    EXPECT_FALSE(sliderContentModifier.isShowStep_->Get());
}

/**
 * @tc.name: SliderContentModifierTest014
 * @tc.desc: Test JudgeNeedAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest014, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    sliderContentModifier.reverse_ = true;
    sliderContentModifier.JudgeNeedAnimate(sliderPaintProperty);
    EXPECT_FALSE(sliderContentModifier.needAnimate_);
    EXPECT_FALSE(sliderContentModifier.reverse_);
}

/**
 * @tc.name: SliderContentModifierTest015
 * @tc.desc: Test SetSelectSize while need needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest015, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.selectEnd_, nullptr);

    sliderContentModifier.needAnimate_ = true;
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    EXPECT_EQ(sliderContentModifier.selectEnd_->Get(), POINTF_END - PointF());
}

/**
 * @tc.name: SliderContentModifierTest016
 * @tc.desc: Test SetCircleCenter while needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest016, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterX_, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterY_, nullptr);

    sliderContentModifier.needAnimate_ = true;
    PointF center(FRAME_WIDTH, FRAME_HEIGHT);
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);

    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);
}

/**
 * @tc.name: SliderContentModifierTest017
 * @tc.desc: Test DrawBlock while blockType is image
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set image block property.
     */
    SliderContentModifier::Parameters parameters;
    OffsetF value;
    auto updateImageCenterX = [&value](float x) { value.SetX(x); };
    auto updateImageCenterY = [&value](float y) { value.SetY(y); };
    SliderContentModifier sliderContentModifier(parameters, updateImageCenterX, updateImageCenterY);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::IMAGE);

    /**
     * @tc.steps: step2. start SliderContentModifier SetCircleCenter func.
     * @tc.cases: case1. when the block center changes.
     */
    PointF center(FRAME_WIDTH, FRAME_HEIGHT);
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(value.GetX(), FRAME_WIDTH);
    EXPECT_EQ(value.GetY(), FRAME_HEIGHT);
}

/**
 * @tc.name: SliderContentModifierTest018
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set property callback.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    OffsetF value;
    bool set = false;
    auto animatablePropertySetCallback = [&value, &set](const OffsetF& arg) {
        value = arg;
        set = true;
    };
    auto animatablePropertyGetCallback = [&value]() { return value; };
    sliderContentModifier.selectEnd_->SetUpCallbacks(animatablePropertyGetCallback, animatablePropertySetCallback);

    /**
     * @tc.steps: step2. start SliderContentModifier StopSelectAnimation func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_START - PointF();
    sliderContentModifier.StopSelectAnimation(SELECT_END);
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation(SELECT_START);
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation(SELECT_START);
    ASSERT_FALSE(set);

    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_START - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation(SELECT_END);
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation(SELECT_START);
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation(SELECT_START);
    ASSERT_FALSE(set);
}

/**
 * @tc.name: SliderContentModifierTest019
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderContentModifierTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set property callback.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    float blockCenterX;
    float blockCenterY;
    bool set = false;
    auto animatablePropertySetCallback = [&blockCenterX, &set](const float& arg) {
        blockCenterX = arg;
        set = true;
    };
    auto animatablePropertyGetCallback = [&blockCenterX]() { return blockCenterX; };
    sliderContentModifier.blockCenterX_->SetUpCallbacks(animatablePropertyGetCallback, animatablePropertySetCallback);

    /**
     * @tc.steps: step2. start SliderContentModifier StopCircleCenterAnimation func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.blockCenterX_->Set(POINTF_CENTER.GetX());
    sliderContentModifier.targetCenter_ = POINTF_START;
    sliderContentModifier.StopCircleCenterAnimation(POINTF_END);
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_CENTER.GetX());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation(SELECT_START);
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_END.GetX());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation(SELECT_START);
    ASSERT_FALSE(set);

    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    auto animatablePropertySetCallback2 = [&blockCenterY, &set](const float& arg) {
        blockCenterY = arg;
        set = true;
    };
    auto animatablePropertyGetCallback2 = [&blockCenterY]() { return blockCenterY; };
    sliderContentModifier.blockCenterY_->SetUpCallbacks(animatablePropertyGetCallback2, animatablePropertySetCallback2);
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderContentModifier.targetCenter_ = POINTF_START;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation(POINTF_END);
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation(SELECT_START);
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_END.GetY());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation(SELECT_START);
    ASSERT_FALSE(set);
}

/**
 * @tc.name: SliderPatternChangeEventTestNg001
 * @tc.desc: Test the Text property of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternChangeEventTestNg001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    std::function<void(float)> eventOnChange = [](float floatValue) { EXPECT_EQ(floatValue, 1.0); };
    sliderModelNG.SetOnChangeEvent(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderEventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    ASSERT_NE(sliderEventHub, nullptr);
    sliderEventHub->SetOnChangeEvent(std::move(eventOnChange));
    ASSERT_NE(sliderEventHub->onChangeEvent_, nullptr);
    sliderEventHub->FireChangeEvent(1.0, 1);
    sliderEventHub->SetOnChangeEvent(nullptr);
    ASSERT_EQ(sliderEventHub->onChangeEvent_, nullptr);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Slider Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider and initialize related properties.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);

    /**
     * @tc.steps: step2. Get slider frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->showTips_ = false;
    sliderPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get slider accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When slider is not showTips, call the callback function in sliderAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When slider is showTips, call the callback function in sliderAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    sliderPattern->showTips_ = true;
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: SliderPatternDistributed001
 * @tc.desc: Test the distributed capability of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternDistributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = sliderPattern->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Get pattern and set value.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    sliderPaintProperty->UpdateValue(40);
    std::string ret = sliderPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"value":40})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"value":40})";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 40);
    restoreInfo_ = R"({"value":2})";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 2);
    restoreInfo_ = "invalid_json_string";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 2);
}
} // namespace OHOS::Ace::NG

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
constexpr Dimension SLIDER_OUTSET_TRACK_THICKNRESS = Dimension(10.0);
constexpr Dimension SLIDER_INSET_TRACK_THICKNRESS = Dimension(20.0);
constexpr Dimension SLIDER_NONE_TRACK_THICKNRESS = Dimension(5.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_SIZE = Dimension(30.0);
constexpr Dimension SLIDER_INSET_BLOCK_SIZE = Dimension(15.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_HOTSIZE = Dimension(50.0);
constexpr Dimension SLIDER_INSET_BLOCK_HOTSIZE = Dimension(60.0);
constexpr Dimension SLIDER_NONE_BLOCK_HOTSIZE = Dimension(45.0);
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float HALF = 0.5;
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
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
} // namespace
class SliderTestNg : public testing::Test {
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

void SliderTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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
    sliderContentModifier.SetBlockColor(TEST_COLOR);
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderTestNg001
 * @tc.desc: Test Slider Create
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg001, TestSize.Level1)
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
 * @tc.name: SliderTestNg002
 * @tc.desc: Test Slider Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg002, TestSize.Level1)
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
    sliderModelNG.SetTrackBackgroundColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
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
    EXPECT_EQ(true, sliderPaintProperty->GetTrackBackgroundColor().has_value());
    EXPECT_EQ(sliderPaintProperty->GetTrackBackgroundColor().value(), SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderPaintProperty->GetSelectColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetShowSteps(), BOOL_VAULE);
}

/**
 * @tc.name: SliderTestNg003
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg003, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
 * @tc.name: SliderTestNg004
 * @tc.desc: Test Slider OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg004, TestSize.Level1)
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
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
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
 * @tc.name: SliderTestNg005
 * @tc.desc: Test Slider HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg005, TestSize.Level1)
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
    EXPECT_EQ(sliderPattern->bubbleFlag_, false);
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
 * @tc.name: SliderTestNg006
 * @tc.desc: Test Slider OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg006, TestSize.Level1)
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
 * @tc.name: SliderTestNg007
 * @tc.desc: Test Slider HandlingGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg007, TestSize.Level1)
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
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0f);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
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
    sliderLayoutProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 62);
}

/**
 * @tc.name: SliderTestNg008
 * @tc.desc: Test Slider min max value steps error value
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg008, TestSize.Level1)
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
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetValue().value(), MAX_LABEL);
    paintProperty->UpdateValue(0);
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetValue().value(), MIN_LABEL);
    /**
     * @tc.cases: case3. when slider stepSize value is less than or equal to 0, take 1 by defualt;
     */
    paintProperty->UpdateValue(VALUE);
    paintProperty->UpdateStep(0);
    paintProperty->UpdateMin(MIN);
    paintProperty->UpdateMax(MAX);
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetStep().value(), STEP);
    paintProperty->UpdateStep(-1);
    sliderPattern->UpdateValue(-1);
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetStep().value(), STEP);
}

/**
 * @tc.name: SliderTestNg009
 * @tc.desc: Test Slider ThackThickness error value
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg009, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
 * @tc.name: SliderTestNg010
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is mouse
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg010, TestSize.Level1)
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
 * @tc.name: SliderTestNg011
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is touch
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg011, TestSize.Level1)
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
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = VALUE;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(-MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f); // Exceeding the leftmost end, take 0
    /**
     * @tc.cases: case2. touch down position is inside the blockHotSize, not UpdateValueByLocalLocation
     */
    info.changedTouches_.front().localLocation_ = Offset();
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderTestNg012
 * @tc.desc: Test Slider mouse Event and wheel operation
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNg012, TestSize.Level1)
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
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithm001, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetTrackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS;
    sliderTheme->insetTrackThickness_ = SLIDER_INSET_TRACK_THICKNRESS;
    sliderTheme->noneTrackThickness_ = SLIDER_NONE_TRACK_THICKNRESS;
    sliderTheme->outsetBlockSize_ = SLIDER_OUTSET_BLOCK_SIZE;
    sliderTheme->insetBlockSize_ = SLIDER_INSET_BLOCK_SIZE;
    sliderTheme->outsetBlockHotSize_ = SLIDER_OUTSET_BLOCK_HOTSIZE;
    sliderTheme->insetBlockHotSize_ = SLIDER_INSET_BLOCK_HOTSIZE;
    sliderTheme->noneBlockHotSize_ = SLIDER_NONE_BLOCK_HOTSIZE;
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
    EXPECT_EQ(size3.value(), SizeF(SLIDER_INSET_TRACK_THICKNRESS.ConvertToPx(), HEIGHT.ConvertToPx()));
    /**
     * @tc.cases: case4. sliderMode is INSET and direction is Axis::HORIZONTAL.
     */
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto size4 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size4, std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(HEIGHT.ConvertToPx(), SLIDER_INSET_TRACK_THICKNRESS.ConvertToPx()));
    /**
     * @tc.cases: case5. sliderMode is NONE and direction is Axis::HORIZONTAL.
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    auto size5 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size5, std::nullopt);
    EXPECT_EQ(size5.value(), SizeF(WIDTH.ConvertToPx(), SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx()));
}

/**
 * @tc.name: SliderLayoutAlgorithm002
 * @tc.desc: Test SliderLayoutAlgorithm Layout.
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderLayoutAlgorithm002, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithm003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
 * @tc.name: SliderLayoutAlgorithm004
 * @tc.desc: Test CalculateHoeSize.
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderLayoutAlgorithm004, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetTrackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS;
    sliderTheme->insetTrackThickness_ = SLIDER_INSET_TRACK_THICKNRESS;
    sliderTheme->noneTrackThickness_ = SLIDER_NONE_TRACK_THICKNRESS;
    sliderTheme->outsetBlockSize_ = SLIDER_OUTSET_BLOCK_SIZE;
    sliderTheme->insetBlockSize_ = SLIDER_INSET_BLOCK_SIZE;
    sliderTheme->outsetBlockHotSize_ = SLIDER_OUTSET_BLOCK_HOTSIZE;
    sliderTheme->insetBlockHotSize_ = SLIDER_INSET_BLOCK_HOTSIZE;
    sliderTheme->noneBlockHotSize_ = SLIDER_NONE_BLOCK_HOTSIZE;
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
     * @tc.cases: case1. sliderMode is NONE.
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    auto size1 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size1, std::nullopt);
    EXPECT_EQ(sliderLayoutAlgorithm->blockHotSize_,
        SizeF(SLIDER_NONE_BLOCK_HOTSIZE.ConvertToPx(), SLIDER_NONE_BLOCK_HOTSIZE.ConvertToPx()));
    /**
     * @tc.cases: case2. sliderMode is OUTSET.
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto size2 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size2, std::nullopt);
    EXPECT_EQ(sliderLayoutAlgorithm->blockHotSize_,
        SizeF(SLIDER_OUTSET_BLOCK_HOTSIZE.ConvertToPx(), SLIDER_OUTSET_BLOCK_HOTSIZE.ConvertToPx()));
    /**
     * @tc.cases: case3. sliderMode is INSET.
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    auto size3 = sliderLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper);
    EXPECT_NE(size3, std::nullopt);
    EXPECT_EQ(sliderLayoutAlgorithm->blockHotSize_,
        SizeF(SLIDER_INSET_BLOCK_HOTSIZE.ConvertToPx(), SLIDER_INSET_BLOCK_HOTSIZE.ConvertToPx()));
}

/**
 * @tc.name: SliderTestNgInteractiveMode001
 * @tc.desc: Test Slider InteractionMode by default
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode001, TestSize.Level1)
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
     * @tc.steps: step2. get SliderIntecationMode by default.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_FALSE(sliderPaintProperty->GetSliderInteractionMode().has_value());
}

/**
 * @tc.name: SliderTestNgInteractionMode002
 * @tc.desc: Test Slider InteractionMode Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderIntecationMode.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetSliderInteractionMode(), SliderModelNG::SliderInteraction::SLIDE_ONLY);
}

/**
 * @tc.name: SliderTestNgInteractionMode003
 * @tc.desc: Test Slider InteractionMode Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderIntecationMode.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetSliderInteractionMode(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
}

/**
 * @tc.name: SliderTestNgInteractionMode004
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is mouse
 *           and InteractionMode is SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
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
     *            Slider value doesn't change. SLIDE_ONLY mode
     */
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    /**
     * @tc.cases: case2. mouse down position is inside the block side, not UpdateValueByLocalLocation
     */
    sliderPattern->circleCenter_.Reset();
    sliderPattern->blockSize_ = SizeF(MAX_LABEL, MAX_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderTestNgInteractionMode005
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is mouse
 *           and InteractionMode is SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
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
 * @tc.name: SliderTestNgInteractionMode006
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is touch
 *           and InteractionMode is SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
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
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MIN_LABEL, -MAX_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = VALUE;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(-MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE); // Exceeding slider value doesn't change
    /**
     * @tc.cases: case2. touch down position is inside the blockHotSize, not UpdateValueByLocalLocation
     */
    info.changedTouches_.front().localLocation_ = Offset();
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderTestNgInteractionMode007
 * @tc.desc: Test Slider HandleTouchEvent with hot area when sourceType is touch
 *           and InteractionMode is SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
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
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = .0f;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->value_, .0f);
    sliderPattern->value_ = VALUE;
    sliderPattern->circleCenter_.Reset();
    info.changedTouches_.front().localLocation_ = Offset(-MAX_LABEL, MIN_LABEL);
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f); // Exceeding the leftmost end, take 0
    /**
     * @tc.cases: case2. touch down position is inside the blockHotSize, not UpdateValueByLocalLocation
     */
    info.changedTouches_.front().localLocation_ = Offset();
    sliderPattern->HandleTouchEvent(info);
    EXPECT_NE(sliderPattern->value_, .0f);
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: SliderTestNgInteractionMode008
 * @tc.desc: Test Slider mouse Event and wheel operation
 *           and InteractionMode is SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
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
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
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
 * @tc.name: SliderTestNgInteractionMode009
 * @tc.desc: Test Slider mouse Event and wheel operation
 *           and InteractionMode is SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
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
 * @tc.name: SliderTestNgInteractionMode010
 * @tc.desc: Test Slider HandlingGestureEvent
 *           SliderIneraction mode set to SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode010, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(
        sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);

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
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0f);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    /**
     * @tc.cases: case3. InputEventType is not AXIS, direction is HORIZONTAL and revese is false.
     */
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    sliderPattern->sliderLength_ = 52.0f;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 19);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, true);
    /**
     * @tc.cases: case4. InputEventType is not AXIS, direction is VERTICAL and revese is true.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 62);
}

/**
 * @tc.name: SliderTestNgInteractionMode011
 * @tc.desc: Test Slider HandlingGestureEvent
 *           SliderIneraction mode set to SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode011, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_ONLY);

    /**
     * @tc.cases: case1. InputEventType is AXIS and MoveStep(-1).
     */
    sliderPattern->value_ = VALUE;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    info.SetOffsetX(.0);
    info.SetOffsetY(1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    sliderPaintProperty->UpdateStep(.0);
    sliderPattern->HandlingGestureEvent(info);
    /**
     * @tc.cases: case3. InputEventType is not AXIS, direction is HORIZONTAL and revese is false.
     */
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    sliderPattern->sliderLength_ = 52.0f;
    sliderPattern->HandlingGestureStart(info);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, false);
    /**
     * @tc.cases: case4. InputEventType is not AXIS, direction is VERTICAL and revese is true.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
}

/**
 * @tc.name: SliderTestNgInteractionMode012
 * @tc.desc: Test Slider HandlingGestureEvent by Slider block
 *           SliderIneraction mode set to SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode012, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_ONLY);

    /**
     * @tc.cases: case1. InputEventType is not AXIS and drag by block to 20.0
     */
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);

    sliderPattern->value_ = VALUE;
    sliderPattern->sliderLength_ = MAX;
    sliderPattern->valueRatio_ = 0.5;
    sliderPattern->UpdateCircleCenterOffset();

    EXPECT_EQ(sliderPattern->circleCenter_.GetX(), VALUE);
    EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
    info.localLocation_ = Offset(VALUE, 0);

    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    EXPECT_FALSE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
    sliderPattern->HandlingGestureStart(info);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));

    info.SetOffsetX(20.0f);
    info.localLocation_ = Offset(VALUE + 20.0f, info.localLocation_.GetY());
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->valueChangeFlag_);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));
    EXPECT_NE(sliderPattern->value_, VALUE);
    sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);

    /**
     * @tc.cases: case2. InputEventType is not AXIS and drag by block to -20.0
     */
    sliderPattern->value_ = VALUE;
    sliderPattern->sliderLength_ = MAX;
    sliderPattern->valueRatio_ = 0.5;
    sliderPattern->UpdateCircleCenterOffset();

    EXPECT_EQ(sliderPattern->circleCenter_.GetX(), VALUE);
    EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
    info.localLocation_ = Offset(VALUE, 0);

    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
    sliderPattern->HandlingGestureStart(info);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));

    info.SetOffsetX(-20.0f);
    info.localLocation_ = Offset(VALUE - 20.0f, info.localLocation_.GetY());
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->valueChangeFlag_);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));
    EXPECT_NE(sliderPattern->value_, VALUE);
    sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
}


/**
 * @tc.name: SliderTestNgInteractionMode013
 * @tc.desc: Test Slider InteractionMode Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgInteractionMode013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderIntecationMode.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetSliderInteractionMode(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);
}

/**
 * @tc.name: SliderTestNgMinResponse001
 * @tc.desc: Test Slider MinResponse as default
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgMinResponse001, TestSize.Level1)
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
     * @tc.steps: step2. get SliderIntecationMode by default.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_FALSE(sliderPaintProperty->GetMinResponsiveDistance().has_value());
}

/**
 * @tc.name: SliderTestNgMinResponse002
 * @tc.desc: Test Slider SetMinResponse
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgMinResponse002, TestSize.Level1)
{
    //first: set value as minResponsiveDistance
    //second: expected return value of minResponsiveDistance
    std::vector<std::pair<float, float>> testMinResponseValue {
        std::make_pair<float, float>(-1.0f, 0.0f),
        std::make_pair<float, float>(0.0f, 0.0f),
        std::make_pair<float, float>(1.0f, 1.0f),
        std::make_pair<float, float>(STEP - 1.0f, STEP - 1.0f),
        std::make_pair<float, float>(static_cast<float>(STEP), static_cast<float>(STEP)),
        std::make_pair<float, float>(STEP * 10, STEP * 10),
        std::make_pair<float, float>(STEP + 1.0f, STEP + 1.0f),
        std::make_pair<float, float>(STEP * 20, STEP * 20),
        std::make_pair<float, float>(static_cast<float>(MAX), static_cast<float>(MAX)),
        std::make_pair<float, float>(MAX + 1.0f, 0.0f),
    };

    for (auto testData : testMinResponseValue) {
        /**
        * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
        */
        SliderModelNG sliderModelNG;
        sliderModelNG.Create(VALUE, STEP, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(testData.first);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
        * @tc.steps: step2. get SliderIntecationMode by default.
        * @tc.expected: step2. check whether the properties is correct.
        */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
        EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
        EXPECT_TRUE(sliderPaintProperty->GetMinResponsiveDistance().has_value());
        EXPECT_EQ(sliderPaintProperty->GetMinResponsiveDistance().value_or(-10.0f), testData.second);
    }
}

/**
 * @tc.name: SliderTestNgMinResponse003
 * @tc.desc: Test Slider MinResponse
 * Increase Slider value by dragging Slider block
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgMinResponse003, TestSize.Level1)
{
    //first: draggin value by Gesture handling
    //second: expected Slider Value after call HandlingGestureEvent
    constexpr float stepValue = 10.0f;
    constexpr float minResponseValue = 20.0f;
    constexpr float startValue = 20.0f;
    std::vector<std::pair<float, float>> testMinResponseDistanceOffset {
        std::pair<float, float>(1.0f, 0.0f),
        std::pair<float, float>(stepValue * HALF - 1, 0.0f),
        std::pair<float, float>(stepValue * HALF, 0.0f),
        std::pair<float, float>(stepValue * HALF + 1, 0.0f),
        std::pair<float, float>(stepValue, 0.0f),
        std::pair<float, float>(stepValue + 1, 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF - 1), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF + 1), 0.0f),
        std::pair<float, float>(minResponseValue - 1, 0.0f),
        std::pair<float, float>(minResponseValue, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 2, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF - 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF, std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + stepValue * HALF + 1,
            std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
    };

    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    for (auto testData : testMinResponseDistanceOffset) {
        SliderModelNG sliderModelNG;

        sliderModelNG.Create(startValue, stepValue, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(minResponseValue);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        frameNode->geometryNode_->SetContentOffset(OffsetF());
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);

        /**
         * @tc.steps: step2. get SliderIntecationMode by default.
         * @tc.expected: step2. check whether the properties is correct.
         */
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);
        EXPECT_EQ(sliderPaintProperty->GetValue(), startValue);

        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->value_ = startValue;
        sliderPattern->sliderLength_ = MAX;
        sliderPattern->valueRatio_ = startValue / MAX;
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
        info.localLocation_ = Offset(startValue, 0);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(testData.first + startValue);
        info.localLocation_ = Offset(startValue + testData.first, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_EQ(sliderPattern->value_, testData.second + startValue);
        sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
    }
}

/**
 * @tc.name: SliderTestNgMinResponse004
 * @tc.desc: Test Slider MinResponse
 * Decrease Slider value by dragging Slider block
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTestNgMinResponse004, TestSize.Level1)
{
    //first: draggin value by Gesture handling
    //second: expected Slider Value after call HandlingGestureEvent
    constexpr float stepValue = 10.0f;
    constexpr float minResponseValue = 20.0f;
    constexpr float startValue = 70.0f;
    std::vector<std::pair<float, float>> testMinResponseDistanceOffset {
        std::pair<float, float>(1.0f, 0.0f),
        std::pair<float, float>(stepValue * HALF - 1, 0.0f),
        std::pair<float, float>(stepValue * HALF, 0.0f),
        std::pair<float, float>(stepValue * HALF + 1, 0.0f),
        std::pair<float, float>(stepValue, 0.0f),
        std::pair<float, float>(stepValue + 1, 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF - 1), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF + 1), 0.0f),
        std::pair<float, float>(minResponseValue - 1, 0.0f),
        std::pair<float, float>(minResponseValue, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 2, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF - 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + stepValue * HALF + 1,
            std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
    };

    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    for (auto testData : testMinResponseDistanceOffset) {
        SliderModelNG sliderModelNG;

        sliderModelNG.Create(startValue, stepValue, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(minResponseValue);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        frameNode->geometryNode_->SetContentOffset(OffsetF());
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);

        /**
         * @tc.steps: step2. get SliderIntecationMode by default.
         * @tc.expected: step2. check whether the properties is correct.
         */
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);
        EXPECT_EQ(sliderPaintProperty->GetValue(), startValue);

        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->value_ = startValue;
        sliderPattern->sliderLength_ = MAX;
        sliderPattern->valueRatio_ = startValue / MAX;
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
        info.localLocation_ = Offset(startValue, 0);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(startValue - testData.first);
        info.localLocation_ = Offset(startValue - testData.first, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_EQ(sliderPattern->value_, startValue - testData.second);
        sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
    }
}
} // namespace OHOS::Ace::NG

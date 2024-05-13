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
constexpr float MIN_RANGE = MIN + 40.0f;
constexpr float MAX_RANGE = MAX - 30.0f;
constexpr float MIDDLE_OF_RANGE = (MIN_RANGE + MAX_RANGE) / 2;
constexpr float NAN_VALUE = std::numeric_limits<float>::quiet_NaN();
constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();
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
constexpr Dimension SLIDER_NONE_TRACK_THICKNRESS = Dimension(5.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_SIZE = Dimension(30.0);
constexpr Dimension SLIDER_INSET_BLOCK_SIZE = Dimension(15.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_HOTSIZE = Dimension(50.0);
constexpr Dimension SLIDER_INSET_BLOCK_HOTSIZE = Dimension(60.0);
constexpr Dimension SLIDER_NONE_BLOCK_HOTSIZE = Dimension(45.0);
constexpr Dimension SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_TRACK_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_STEP_SIZE = Dimension(10.0);
constexpr Dimension RADIUS = Dimension(10.0);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS_DIFF = 1.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL = 8.0f;
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
const Dimension RADIUS_X = Dimension(20.1, DimensionUnit::PX);
const Dimension RADIUS_Y = Dimension(20.1, DimensionUnit::PX);
const Dimension SHAPE_WIDTH = 10.0_vp;
const Dimension SHAPE_HEIGHT = 20.0_vp;
constexpr float CONTENT_WIDTH = 100.0f;
constexpr float CONTENT_HEIGHT = 50.0f;
constexpr float HOT_BLOCK_SHADOW_WIDTH = 3.0f;
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
constexpr Dimension TRACK_BORDER_RADIUS = 5.0_px;
constexpr Dimension BUBBLE_VERTICAL_WIDTH = 62.0_vp;
constexpr Dimension BUBBLE_VERTICAL_HEIGHT = 32.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_HEIGHT = 40.0_vp;
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 16.0_vp;
constexpr Dimension CIRCULAR_HORIZON_OFFSET = 13.86_vp;
constexpr Dimension TEXT_MAX = 36.0_vp;
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
    sliderContentModifier.SetSelectColor(TEST_COLOR);
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
    sliderPaintProperty->UpdateStep(.0);
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
    LInfo.touchType_ = TouchType::UP;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::MOUSE);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->lastTouchLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    sliderPattern->fingerId_ = LInfo.GetFingerId();
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
    LInfo.touchType_ = TouchType::UP;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::TOUCH);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->lastTouchLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    sliderPattern->fingerId_ = LInfo.GetFingerId();
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
 * @tc.name: SliderModelNgTest001
 * @tc.desc: TEST slider_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderModelNgTest001, TestSize.Level1)
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
    sliderModelNG.SetSelectedBorderRadius(SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
    sliderModelNG.SetBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderModelNG.SetBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE, SLIDER_TEST_BUNDLE_NAME, SLIDER_TEST_MODULE_NAME);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderModelNG.SetBlockShape(basicShape);
    sliderModelNG.SetStepSize(SLIDER_MODEL_NG_STEP_SIZE);
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
    EXPECT_EQ(sliderPaintProperty->GetSelectedBorderRadius(), SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
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
HWTEST_F(SliderTestNg, SliderModelNgTest002, TestSize.Level2)
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
 * @tc.name: SliderTipModifierTest001
 * @tc.desc: TEST slider_tip_modifier onDraw
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTipModifierTest001, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier attribute and call onDraw function.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), true);
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_,
        SizeF(BUBBLE_HORIZONTAL_WIDTH.ConvertToPx(), BUBBLE_HORIZONTAL_HEIGHT.ConvertToPx()));

    sliderPattern->direction_ = Axis::VERTICAL;
    sliderTipModifier.SetDirection(Axis::VERTICAL);
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), true);
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_,
        SizeF(BUBBLE_VERTICAL_WIDTH.ConvertToPx(), BUBBLE_VERTICAL_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SliderContentModifierTest001
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = HORIZONTAL, blockType = DEFAULT, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest001, TestSize.Level1)
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
    // set animatorStatus default
    sliderContentModifier.SetAnimatorStatus(SliderStatus::DEFAULT);
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
HWTEST_F(SliderTestNg, SliderContentModifierTest002, TestSize.Level1)
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
    EXPECT_EQ(sliderContentModifier.selectedBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS);
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
HWTEST_F(SliderTestNg, SliderContentModifierTest003, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest004, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest005, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest006, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest007, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest008, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest009, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest010, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest011, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest012, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPaintPropertyTest001, TestSize.Level1)
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
    sliderPaintProperty->UpdateSelectedBorderRadius(SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    sliderPaintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    sliderPaintProperty->UpdateBlockBorderColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderColorValue(Color::TRANSPARENT), TEST_COLOR);
    sliderPaintProperty->UpdateBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderWidthValue(Dimension()), SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderPaintProperty->UpdateStepColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetStepColorValue(Color::TRANSPARENT), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBorderRadiusValue(Dimension()), SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderPaintProperty->GetSelectedBorderRadiusValue(Dimension()), SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
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
HWTEST_F(SliderTestNg, SliderLayoutPropertyTest001, TestSize.Level1)
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
    sliderLayoutProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutProperty->ResetBlockSize();
    sliderLayoutProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: SliderPatternTest001
 * @tc.desc: Test slider_pattern UpdateBlock/CreateNodePaintMethod/GetBlockCenter/HandleTouchEvent
 * imageFrameNode_ == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest001, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPatternTest002, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPatternTest003, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
 * @tc.name: SliderPatternTest004
 * @tc.desc: Test slider pattern GetOutsetInnerFocusPaintRect function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest004, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
HWTEST_F(SliderTestNg, SliderPatternTest005, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
    /**
     * @tc.steps: step4. Calculate in the NONE scenario.
     * @tc.expected: borderBlank_ == 0
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_NONE_TRACK_THICKNRESS.Value();
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_, 0);
}

/**
 * @tc.name: SliderPatternTest006
 * @tc.desc: Test slider_pattern CreateNodePaintMethod/HandlingGestureEvent/OnKeyEvent
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest006, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
HWTEST_F(SliderTestNg, SliderPatternTest007, TestSize.Level1)
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
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(-offset, 0));

    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderPattern->direction_ = Axis::HORIZONTAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(-offset, 0));
}

/**
 * @tc.name: SliderPatternTest008
 * @tc.desc: Test SliderPattern GetInsetAndNoneInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest008, TestSize.Level1)
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
     * @tc.steps: step2. call GetInsetAndNoneInnerFocusPaintRect without TrackBorderRadius property.
     * @tc.expected: step2. radius == (TrackThickness / 2 + focusWidth).
     */
    sliderPattern->direction_ = Axis::HORIZONTAL;
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(roundRect);
    auto radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, (SLIDER_HEIGHT * HALF) + focusDistance);
    EXPECT_EQ(radius.y, (SLIDER_HEIGHT * HALF) + focusDistance);

    /**
     * @tc.steps: step3. call GetInsetAndNoneInnerFocusPaintRect with TrackBorderRadius property.
     * @tc.expected: step3. radius == (TrackBorderRadius + focusWidth).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateTrackBorderRadius(TRACK_BORDER_RADIUS);
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(roundRect);
    radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
    EXPECT_EQ(radius.y, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
}

/**
 * @tc.name: SliderPatternTest009
 * @tc.desc: Test slider_pattern onBlurInternal_ HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest009, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPatternTest010, TestSize.Level1)
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
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step3. call HandleHoverEvent hover false with mouse pressed.
     * @tc.expected: step3. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = true;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step4. call HandleHoverEvent hover false with focus.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = true;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step5. call HandleHoverEvent hover true.
     * @tc.expected: step5. sliderPattern->bubbleFlag_ is true.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(true);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest011
 * @tc.desc: Test slider_pattern AtMousePanArea
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest011, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPatternTest012, TestSize.Level1)
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
    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::DEFAULT;
    sliderPattern->panEvent_->actionStart_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::MOVE);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::DEFAULT;
    sliderPattern->panEvent_->actionUpdate_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::MOVE);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::MOVE;
    sliderPattern->panEvent_->actionEnd_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::DEFAULT);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::MOVE;
    sliderPattern->panEvent_->actionCancel_();
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::DEFAULT);
}

/**
 * @tc.name: SliderPatternTest013
 * @tc.desc: Test slider_pattern InitPanEvent and event callback.
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithmTest001, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithmTest002, TestSize.Level1)
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
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithmTest003, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderLayoutAlgorithmTest004, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPaintMethodTest001, TestSize.Level1)
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
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
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
    MockPipelineContext::SetUp();
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
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->selectedBorderRadius_->Get(),
        static_cast<float>(SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx()) * HALF);

    //change sliderMode
    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())
        ->UpdateSliderMode(SliderModelNG::SliderMode::NONE);
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->sliderMode_->Get(),
        static_cast<int>(SliderModelNG::SliderMode::NONE));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->selectedBorderRadius_->Get(), 0);
}

/**
 * @tc.name: SliderPaintMethodTest002
 * @tc.desc: Test slider_paint_method UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPaintMethodTest002, TestSize.Level1)
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
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
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
    MockPipelineContext::SetUp();
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
HWTEST_F(SliderTestNg, SliderPaintMethodTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
        SliderPaintMethod::TipParameters(), TextDirection::AUTO);
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
HWTEST_F(SliderTestNg, SliderAccessibilityPropertyTest001, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderAccessibilityPropertyTest002, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderAccessibilityPropertyTest003, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest013, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderContentModifierTest014, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    sliderContentModifier.reverse_ = true;
    sliderContentModifier.JudgeNeedAnimate(false);
    EXPECT_EQ(sliderContentModifier.animatorStatus_, SliderStatus::DEFAULT);
    EXPECT_FALSE(sliderContentModifier.reverse_);
}

/**
 * @tc.name: SliderContentModifierTest015
 * @tc.desc: Test SetSelectSize while need needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest015, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.selectEnd_, nullptr);

    sliderContentModifier.animatorStatus_ = SliderStatus::MOVE;
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    EXPECT_EQ(sliderContentModifier.selectEnd_->Get(), POINTF_END - PointF());
}

/**
 * @tc.name: SliderContentModifierTest016
 * @tc.desc: Test SetCircleCenter while needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest016, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterX_, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterY_, nullptr);

    sliderContentModifier.animatorStatus_ = SliderStatus::MOVE;
    PointF center(FRAME_WIDTH, FRAME_HEIGHT);
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);

    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);

    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::NONE));
    sliderContentModifier.SetCircleCenter(PointF(FRAME_WIDTH, FRAME_WIDTH));
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest017
 * @tc.desc: Test DrawBlock while blockType is image
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest017, TestSize.Level1)
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
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawBlock(context);
    EXPECT_EQ(value.GetY(), FRAME_HEIGHT);

    SliderContentModifier sliderContentModifierPro(parameters, nullptr, nullptr);
    sliderContentModifierPro.SetBlockType(SliderModelNG::BlockStyleType::IMAGE);
    sliderContentModifierPro.DrawBlock(context);
    EXPECT_EQ(sliderContentModifierPro.updateImageCenterX_, nullptr);
    EXPECT_EQ(sliderContentModifierPro.updateImageCenterX_, nullptr);
}

/**
 * @tc.name: SliderContentModifierTest018
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest018, TestSize.Level1)
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
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_START - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);
}

/**
 * @tc.name: SliderContentModifierTest019
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest019, TestSize.Level1)
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
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_CENTER.GetX());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_END.GetX());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

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
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_END.GetY());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);
}

/**
 * @tc.name: SliderContentModifierTest020
 * @tc.desc: TEST gradient track background
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest020, TestSize.Level1)
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

    Gradient gradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::WHITE));
    gradientColor1.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(0.5));
    gradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor(Color::BLUE));
    gradientColor3.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColor3);
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetTrackBackgroundColor(gradient);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);

    Gradient gradient2 = sliderContentModifier.trackBackgroundColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors2 = gradient2.GetColors();

    EXPECT_EQ(gradientColors.size(), gradientColors2.size());
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors2[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors2[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors2[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors2[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors2[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors2[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest021
 * @tc.desc: TEST default track background color
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->trackBgColor_ = Color::RED;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    ASSERT_NE(sliderPattern->sliderContentModifier_, nullptr);

    Gradient gradient = sliderPattern->sliderContentModifier_->trackBackgroundColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors = gradient.GetColors();

    Gradient defaultGradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::RED));
    gradientColor1.SetDimension(Dimension(0.0));
    defaultGradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(1.0));
    defaultGradient.AddColor(gradientColor2);
    std::vector<GradientColor> defaultGradientColors = defaultGradient.GetColors();

    EXPECT_EQ(defaultGradientColors.size(), gradientColors.size());
    EXPECT_EQ(defaultGradientColors[0].GetLinearColor(), gradientColors[0].GetLinearColor());
    EXPECT_EQ(defaultGradientColors[1].GetLinearColor(), gradientColors[1].GetLinearColor());
    EXPECT_EQ(defaultGradientColors[0].GetDimension(), gradientColors[0].GetDimension());
    EXPECT_EQ(defaultGradientColors[1].GetDimension(), gradientColors[1].GetDimension());
}

/**
 * @tc.name: SliderPatternChangeEventTestNg001
 * @tc.desc: Test the Text property of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternChangeEventTestNg001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    std::function<void(float)> eventOnChange = [](float floatValue) { EXPECT_EQ(floatValue, 1.0); };
    sliderModelNG.SetOnChangeEvent(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderEventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    ASSERT_NE(sliderEventHub, nullptr);
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
HWTEST_F(SliderTestNg, PerformActionTest001, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderPatternDistributed001, TestSize.Level1)
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

/**
 * @tc.name: SliderPatternOnIsFocusActiveUpdate001
 * @tc.desc: Test Is not Focus when slider active update
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternOnIsFocusActiveUpdate001, TestSize.Level1)
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
     * @tc.steps: step2. slider is focus,showtip is true.expect bubbleFlag_ is true.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    sliderPaintProperty->UpdateShowTips(true);
    sliderPattern->OnModifyDone();
    sliderPattern->focusFlag_ = true;
    sliderPattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderTipModifierPaintText001
 * @tc.desc: Test offset of text on slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderTipModifierPaintText001, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier's axis is HORIZONTAL and call PaintText function.
     * @tc.expected: text's offsetX is equal to half of vertex_'s width.
     */
    auto arrowSizeWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowSizeHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto circularOffset = static_cast<float>(CIRCULAR_HORIZON_OFFSET.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderTipModifier.axis_ = Axis::HORIZONTAL;
    sliderTipModifier.isMask_ = true;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    sliderTipModifier.SetParagraph(paragraph);
    sliderTipModifier.PaintTip(context);
    SizeF textSize = { 0, 0 };
    textSize =
        SizeF(std::min(sliderTipModifier.paragraph_->GetLongestLine(), static_cast<float>(TEXT_MAX.ConvertToPx())),
            sliderTipModifier.paragraph_->GetHeight());
    EXPECT_EQ(sliderTipModifier.textOffset_.GetX(), sliderTipModifier.vertex_.GetX() - textSize.Width() * HALF);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetY(),
        sliderTipModifier.vertex_.GetY() -
            (sliderTipModifier.bubbleSize_.Height() + textSize.Height() + arrowSizeHeight) * HALF);
    /**
     * @tc.steps: step2. set sliderTipModifier's axis is VERTICAL and call PaintText function.
     */
    sliderTipModifier.axis_ = Axis::VERTICAL;
    sliderTipModifier.PaintText(context);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetY(), sliderTipModifier.vertex_.GetY() - textSize.Height() * HALF);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetX(),
        sliderTipModifier.vertex_.GetX() - (sliderTipModifier.bubbleSize_.Width() + textSize.Width() + arrowSizeHeight +
                                               circularOffset - arrowSizeWidth) *
                                               HALF);
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
    LInfo.touchType_ = TouchType::UP;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::MOUSE);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->lastTouchLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    sliderPattern->fingerId_ = LInfo.GetFingerId();
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
    LInfo.touchType_ = TouchType::UP;
    LInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    TouchEventInfo info("");
    info.SetSourceDevice(SourceType::TOUCH);
    info.changedTouches_.emplace_back(LInfo);
    sliderPattern->lastTouchLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    sliderPattern->fingerId_ = LInfo.GetFingerId();
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
    sliderPaintProperty->UpdateStep(.0);
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
/**
 * @tc.name: SliderContentModifierTest022
 * @tc.desc: TEST slider_content_modifier DrawStep
 * direction = HORIZONTAL, blockType = DEFAULT, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest022, TestSize.Level1)
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
     * @tc.steps: step2. Set BackgroundSize call DrawStep function and return.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_START);
    sliderContentModifier.SetShowSteps(true);
    sliderContentModifier.SetStepRatio(1.1);
    auto backStart = sliderContentModifier.backStart_->Get();
    auto backEnd = sliderContentModifier.backEnd_->Get();
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetX(), backEnd.GetX()));
    EXPECT_TRUE(NearEqual(backStart.GetY(), backEnd.GetY()));
    /**
     * @tc.steps: step2. call DrawStep function and test stepSize.
     */
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END_DIFFX);
    sliderContentModifier.SetStepSize(SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    sliderContentModifier.SetTrackThickness(SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS_DIFF);
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetX(), backEnd.GetX()));
    /**
     * @tc.steps: step3. call DrawStep function and test reverse_.
     */
    sliderContentModifier.SetBackgroundSize(POINTF_START_DIFFY, POINTF_END);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetY(), backEnd.GetY()));
    EXPECT_TRUE(GreatOrEqual(backEnd.GetX(), backStart.GetX()));
    EXPECT_TRUE(GreatOrEqual(backEnd.GetY(), backStart.GetX()));
}

/**
 * @tc.name: SliderContentModifierTest023
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest023, TestSize.Level1)
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
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawDefaultBlock(context);
    /**
     * @tc.steps: step2. set BlockSize attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    float blockRadius = std::min(blockSize.Width(), blockSize.Height()) * HALF;
    float radius = blockRadius;
    auto borderWidth = sliderContentModifier.blockBorderWidth_->Get();
    sliderContentModifier.DrawDefaultBlock(context);
    EXPECT_FALSE(GreatOrEqual(borderWidth * HALF, radius));

    /**
     * @tc.steps: step2. set BlockBorderWidth attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL);
    borderWidth = sliderContentModifier.blockBorderWidth_->Get();
    sliderContentModifier.DrawDefaultBlock(context);
    EXPECT_TRUE(!NearEqual(borderWidth, .0f));
    EXPECT_TRUE(LessNotEqual(borderWidth * HALF, blockRadius));
}

/**
 * @tc.name: SliderContentModifierTest024
 * @tc.desc: TEST slider_content_modifier DrawBlockShape
 * direction = FREE, blockType = SHAPE, blockShape = ELLIPSE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest024, TestSize.Level1)
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
     * @tc.steps: step2. don't set anything call DrawBlockShape function return.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawBlockShape(context);
    EXPECT_EQ(sliderContentModifier.shape_, nullptr);
}

/**
 * @tc.name: SliderContentModifierTest025
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeCircle
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest025, TestSize.Level1)
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
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto circle = AccessibilityManager::DynamicCast<Circle>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(circle);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}

/**
 * @tc.name: SliderContentModifierTest026
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeEllipse
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = Ellipse, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest026, TestSize.Level1)
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
     * @tc.steps: step2. set sliderContentModifier attribute.
     */
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    basicShape->SetBasicShapeType(BasicShapeType::ELLIPSE);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto ellipse = AccessibilityManager::DynamicCast<Ellipse>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(ellipse);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}
/**
 * @tc.name: SliderContentModifierTest027
 * @tc.desc: TEST slider_content_modifier DrawBlockShapePath
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest027, TestSize.Level1)
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
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Path>();
    basicShape->SetBasicShapeType(BasicShapeType::PATH);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto path = AccessibilityManager::DynamicCast<Path>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(path);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapePath(context, path);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapePath(context, path);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));
}
/**
 * @tc.name: SliderContentModifierTest028
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeRect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderContentModifierTest028, TestSize.Level1)
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
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<ShapeRect>();
    basicShape->SetBasicShapeType(BasicShapeType::RECT);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto rect = AccessibilityManager::DynamicCast<ShapeRect>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(rect);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}

/**
 * @tc.name: SliderModelNgTest003
 * @tc.desc: TEST slider_model_ng SetShowTips
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderModelNgTest003, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create slider.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto rawPtr = AceType::RawPtr(frameNode);
    rawPtr->IncRefCount();
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetBlockSize with invalid parameters.
     * @tc.expected: step2. check the BlockSize property not be set.
     */
    sliderModelNG.SetBlockSize(rawPtr, Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());

    /**
     * @tc.steps: step3. call SetBlockSize with invalid parameters while BlockSize property has been set.
     * @tc.expected: step3. check the BlockSize property has reset.
     */
    sliderModelNG.SetBlockSize(rawPtr, BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);

    sliderModelNG.SetShowTips(rawPtr, false, "content");

    sliderModelNG.SetThickness(rawPtr, Dimension(-1));
    sliderModelNG.SetThickness(rawPtr, Dimension(1));
    EXPECT_TRUE(sliderLayoutProperty->GetBlockSize().has_value());
}

/**
 * @tc.name: SliderPatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateValue(VALUE);
    sliderPaintProperty->UpdateMin(MIN);
    sliderPaintProperty->UpdateMax(MAX);
    sliderPaintProperty->UpdateStep(STEP);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUE, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(STEP, config.step_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderValidRangeTest001
 * @tc.desc: check value of slider valid range by default
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderValidRangeTest001, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderValidRangeTest002, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderValidRangeTest003, TestSize.Level1)
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
        float checkValue = testData.second.value;
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
        sliderPattern->HandleTouchEvent(infoDown);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, setValue + touchOffset));

        /**
         * @tc.cases: case2. check Slider value after touch up
         */
        sliderPattern->HandleTouchEvent(infoUp);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, checkValue));
    }
}

/**
 * @tc.name: SliderValidRangeTest004
 * @tc.desc: Check set Valid Slide Range depends on Slider STEP
 * @tc.type: FUNC
 */
HWTEST_F(SliderTestNg, SliderValidRangeTest004, TestSize.Level1)
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
HWTEST_F(SliderTestNg, SliderValidRangeTest005, TestSize.Level1)
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
     * @tc.cases: case2. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT, MoveStep(-1).
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    sliderPattern->value_ = MIN_RANGE;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE);

    /**
     * @tc.cases: case3. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    sliderPattern->value_ = MIN_RANGE;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE + STEP);
    /**
     * @tc.cases: case4. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP, MoveStep(-1).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->value_ = MAX_RANGE;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MAX_RANGE - STEP);
    /**
     * @tc.cases: case5. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN, MoveStep(1).
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
HWTEST_F(SliderTestNg, SliderValidRangeTest006, TestSize.Level1)
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
} // namespace OHOS::Ace::NG

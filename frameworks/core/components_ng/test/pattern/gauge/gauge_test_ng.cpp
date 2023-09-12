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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"

#define private public
#define protected public
#include "base/geometry/offset.h"
#include "base/log/log_wrapper.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float METHOD_VALUE = 2.0f;
constexpr float METHOD_MAX = 3.0f;
constexpr float METHOD_MIN = 1.0f;
constexpr float VALUE_BIG = 4.0f;
constexpr float VALUE_SMALL = 0.0f;
constexpr float START = 20.0f;
constexpr float LESS_START = 5.0f;
constexpr float INTERVAL = 30.0f;
constexpr float LESS_INTERVAL = -15.0f;
constexpr float PERCENT = 10.0f;
constexpr float METHOD_START_ANGLE = 50.0f;
constexpr float METHOD_END_ANGLE = 450.0f;
constexpr float ZERO = 0.0f;
constexpr Dimension WIDTH_SMALL = 0.5_vp;

constexpr float VALUE = 50.0f;
constexpr float MAX = 100.0f;
constexpr float MIN = 0.0f;
constexpr float NEW_VALUE = 70.0f;
constexpr float START_ANGLE = 0.0f;
constexpr float END_ANGLE = 180.0f;
constexpr Dimension STOKE_WIDTH = 20.0_vp;
const std::vector<Color> COLORS = { Color::BLUE, Color::RED, Color::GREEN };
const std::vector<float> VALUES = { 1.0f, 1.5f, 2.0f };
const std::string TEST_STRING = "test";
const Color TEST_COLOR = Color::BLUE;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float NEGATIVE_NUMBER = -100;
constexpr float INFINITE = std::numeric_limits<float>::max();
constexpr float SMALL_WIDTH = 400.0f;
constexpr float SMALL_HEIGHT = 400.0f;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;

constexpr float DRAWSTARTDEGREE = 0.0f;
constexpr float SIZE_INFINITY = 2.0f;
constexpr int32_t VERSION = 11;
constexpr float WIDTH_1 = 300.0f;
constexpr float HEIGHT_1 = 300.0f;
} // namespace

class GaugeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GaugeTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void GaugeTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: GaugePatternTest001
 * @tc.desc: Test Gauge Create
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    EXPECT_NE(gaugePaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from gaugePaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(gaugePaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(gaugePaintProperty->GetMinValue(), MIN);
    EXPECT_EQ(gaugePaintProperty->GetValueValue(), VALUE);
}

/**
 * @tc.name: GaugePatternTest002
 * @tc.desc: Test Gauge SetValue SetStartAngle SetEndAngle SetStrokeWidth SetColors
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties ,and then get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetValue(NEW_VALUE);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
    gauge.SetStrokeWidth(STOKE_WIDTH);
    gauge.SetColors(COLORS, VALUES);
    gauge.SetLabelMarkedText(TEST_STRING);
    gauge.SetMarkedTextColor(TEST_COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    EXPECT_NE(gaugePaintProperty, nullptr);
    EXPECT_EQ(gaugePaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(gaugePaintProperty->GetMinValue(), MIN);
    EXPECT_EQ(gaugePaintProperty->GetValueValue(), NEW_VALUE);
    EXPECT_EQ(gaugePaintProperty->GetStartAngleValue(), START_ANGLE);
    EXPECT_EQ(gaugePaintProperty->GetEndAngleValue(), END_ANGLE);
    EXPECT_EQ(gaugePaintProperty->GetStrokeWidthValue(), STOKE_WIDTH);
    EXPECT_EQ(gaugePaintProperty->GetColorsValue(), COLORS);
    EXPECT_EQ(gaugePaintProperty->GetValuesValue(), VALUES);
}

/**
 * @tc.name: GaugeMeasureTest003
 * @tc.desc: Test Gauge MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeMeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    /**
     * @tc.steps: step2. get layoutWrapper and setLayoutAlgorithm.
     * @tc.expected: step2. check gaugeLayoutAlgorithm is not null.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    EXPECT_NE(gaugePattern, nullptr);
    auto gaugeLayoutAlgorithm = gaugePattern->CreateLayoutAlgorithm();
    EXPECT_NE(gaugeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    /**
     * @tc.steps: step3. compare gaugeSize with expected value.
     * @tc.expected: step3. gaugeSize is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *          Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(50).height(50)
     *     }
     */
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));
    auto gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).height(-10)
     *     }
     */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.maxSize = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    auto gaugeTheme = AceType::MakeRefPtr<ProgressTheme>();
    gaugeTheme->trackWidth_ = WIDTH;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(gaugeTheme));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(-10)
     *     }
     */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.maxSize = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(gaugeTheme));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintWidthUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(50)
     *     }
     */
    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutConstraintWidth.maxSize = MAX_SIZE;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).height(50)
     *     }
     */
    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    layoutConstraintHeight.maxSize = MAX_SIZE;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(HEIGHT.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(400).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }})
     *     }
     */
    LayoutConstraintF layoutConstraintSmallWidth;
    layoutConstraintSmallWidth.maxSize = SizeF(SMALL_WIDTH, MAX_HEIGHT);
    layoutConstraint.maxSize = SizeF(SMALL_WIDTH, MAX_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    gaugeTheme->trackWidth_ = 500.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(gaugeTheme));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_WIDTH, SMALL_WIDTH));

    /**
     *    corresponding ets code:
     *     Row.Width(500).Height(400) {
     *         Gauge({ { value: 50, min: 0, max: 100 }})
     *     }
     */
    LayoutConstraintF layoutConstraintSmallHeight;
    layoutConstraintSmallWidth.maxSize = SizeF(MAX_WIDTH, SMALL_HEIGHT);
    layoutConstraint.maxSize = SizeF(MAX_WIDTH, SMALL_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(gaugeTheme));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_HEIGHT, SMALL_HEIGHT));

    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.maxSize = MAX_SIZE;
    layoutConstraintInfinite.maxSize.SetWidth(INFINITE);
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.maxSize.SetWidth(INFINITE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(gaugeTheme));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

/**
 * @tc.name: GaugePatternTest004
 * @tc.desc: Test Gauge Create
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create frameNode to get layout properties and paint properties.
     * @tc.expected: step2. related function is called.
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    EXPECT_NE(gaugePaintProperty, nullptr);

    /**
     * @tc.steps: step3. get value from gaugePaintProperty.
     * @tc.expected: step3. the value is the same with setting.
     */
    EXPECT_EQ(gaugePaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(gaugePaintProperty->GetMinValue(), MIN);
    EXPECT_EQ(gaugePaintProperty->GetValueValue(), VALUE);
}

/**
 * @tc.name: GaugePatternTest005
 * @tc.desc: Test gauge pattern OnDirtyLayoutWrapperSwap function..
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create gauge frameNode, get gaugePattern and gaugeWrapper.
     * @tc.expected: step2. get gaugePattern success.
     */
    RefPtr<GaugePattern> gaugePattern = AceType::DynamicCast<GaugePattern>(frameNode->GetPattern());
    EXPECT_NE(gaugePattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call gaugePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    auto gaugeLayoutAlgorithm = gaugePattern->CreateLayoutAlgorithm();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call gaugePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *      case 1: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    bool first_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    bool second_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = true;
     */
    bool third_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = false;
     */
    bool forth_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: GaugePatternTest006
 * @tc.desc: Test Gauge OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeLayoutPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create datapnel and set effct.
     */
    GaugeModelNG dataPanel;
    dataPanel.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create dataPanel frameNode, get dataPanelPattern and dataPanelWrapper.
     * @tc.expected: step2. get dataPanelPattern success.
     */
    RefPtr<GaugePattern> dataPanelPattern = AceType::DynamicCast<GaugePattern>(frameNode->GetPattern());
    auto layoutProperty = frameNode->GetLayoutProperty();
    dataPanelPattern->OnModifyDone();
    layoutProperty->UpdateAlignment(ALIGNMENT);
    dataPanelPattern->OnModifyDone();
    EXPECT_EQ(ALIGNMENT, layoutProperty->GetPositionProperty()->GetAlignmentValue());
}

/**
 * @tc.name: GaugePaintMethodTest001
 * @tc.desc: Test Gauge PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintProperty.
     */
    GaugePaintMethod gaugePaintMethod;

    /**
     * @tc.steps: step2. test ShouldHighLight in different cases
     * @tc.expected: the result of ShouldHighLight is correct.
     */

    /**
    //     case1 : percent is LessOrEqual than start and LessOrEqual start + interval
    */
    float start = START;
    float interval = INTERVAL;
    float percent = PERCENT;
    bool result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case2 : percent is LessOrEqual than start and GreatOrEqual than start + interval
    */
    start = START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case3 : percent is GreatOrEqual than start and GreatOrEqual than start + interval
    */
    start = LESS_START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    /**
    //     case4 : percent is GreatOrEqual than start and LessOrEqual than start + interval
    */
    start = LESS_START;
    interval = INTERVAL;
    percent = PERCENT;
    result = gaugePaintMethod.ShouldHighLight(start, interval, percent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugePaintMethodTest002
 * @tc.desc: Test Gauge PaintMethod GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintProperty.
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    GaugePaintMethod gaugePaintMethod;

    /**
     * @tc.steps: step2. get paintwrapper
     * @tc.expected: paintwrapper is not null
     */
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    gaugePaintMethod.GetForegroundDrawFunction(paintwrapper);
}

/**
 * @tc.name: GaugePaintMethodTest003
 * @tc.desc: Test Gauge PaintMethod DrawGauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest003, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(1);
    gaugePaintMethod.DrawGauge(rsCanvas, data);
}

/**
 * @tc.name: GaugePaintMethodTest004
 * @tc.desc: Test Gauge PaintMethod DrawIndicator
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest004, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(2);
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(1);
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(1);
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    gaugePaintMethod.DrawIndicator(rsCanvas, data);
}

/**
 * @tc.name: GGaugePaintTest001
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest001, TestSize.Level1)
{
    /**
     * case 1: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 1 max = 3
     * startangle = 50         endangle = 450
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(METHOD_END_ANGLE);
    gauge.SetStrokeWidth(WIDTH);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GaugePaintMethodTest002
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest002, TestSize.Level1)
{
    /**
     * case 2: Paint retrun because colors.size() != weights.size()
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(METHOD_END_ANGLE);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f };
    gauge.SetColors(colors, values);
    gauge.SetStrokeWidth(WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(0);
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GaugePaintMethodTest003
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest003, TestSize.Level1)
{
    /**
     * case 3: Paint retrun because colors.size() = 0 and weights.size = 0
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(METHOD_END_ANGLE);
    std::vector<Color> colors = {};
    std::vector<float> values = {};
    gauge.SetColors(colors, values);
    gauge.SetStrokeWidth(WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(0);
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GaugePaintMethodTest004
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest004, TestSize.Level1)
{
    /**
     * case 4: Paint retrun because colors.size() = 0
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(METHOD_END_ANGLE);
    std::vector<Color> colors = {};
    std::vector<float> values = { 1.0f };
    gauge.SetColors(colors, values);
    gauge.SetStrokeWidth(WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(0);
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GaugePaintMethodTest005
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest005, TestSize.Level1)
{
    /**
     * case 5: Paint retrun because total weight is 0.0
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(METHOD_END_ANGLE);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, -1.0f };
    gauge.SetColors(colors, values);
    gauge.SetStrokeWidth(WIDTH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(0);
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GGaugePaintTest006
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest006, TestSize.Level1)
{
    /**
     * case 6: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 1 max = 3
     * startangle = 50         endangle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_BIG, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(METHOD_START_ANGLE);
    gauge.SetEndAngle(ZERO);
    gauge.SetStrokeWidth(WIDTH_SMALL);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GGaugePaintTest007
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest007, TestSize.Level1)
{
    /**
     * case 7: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startangle = 0         endangle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_SMALL, METHOD_MIN, METHOD_MAX);
    gauge.SetStartAngle(ZERO);
    gauge.SetEndAngle(ZERO);
    gauge.SetStrokeWidth(WIDTH_SMALL);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GGaugePaintTest008
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest008, TestSize.Level1)
{
    /**
     * case 8: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 1 max = 3
     * colors = {red,green} values = {1,2};
     * StrokeWidth = -50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(METHOD_VALUE, METHOD_MAX, METHOD_MIN);
    gauge.SetStrokeWidth(-WIDTH);
    std::vector<Color> colors = { Color::RED, Color::GREEN };
    std::vector<float> values = { 1.0f, 2.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GGaugePaintTest009
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest009, TestSize.Level1)
{
    /**
     * case 9: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 1 max = 3
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_BIG, METHOD_MAX, METHOD_MIN);
    gauge.SetStrokeWidth(WIDTH);
    std::vector<Color> colors = { Color::RED };
    std::vector<float> values = { 1.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GGaugePaintTest010
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintTest010, TestSize.Level1)
{
    /**
     * case 10: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startangle = NAN       endangle = NAN
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_SMALL, METHOD_MAX, METHOD_MIN);
    gauge.SetStrokeWidth(WIDTH);
    gauge.SetStartAngle(NAN);
    gauge.SetEndAngle(NAN);
    std::vector<Color> colors = { Color::RED };
    std::vector<float> values = { 1.0f };
    gauge.SetColors(colors, values);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    GaugePaintMethod gaugePaintMethod;
    RefPtr<RenderContext> rendercontext;
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugePaintMethod.Paint(rsCanvas, paintwrapper);
}

/**
 * @tc.name: GaugeAccessibilityPropertyTestNg001
 * @tc.desc: Test the HasRange and RangeInfo properties of Gauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeAccessibilityPropertyTestNg001, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto gaugeAccessibilityProperty = frameNode->GetAccessibilityProperty<GaugeAccessibilityProperty>();
    ASSERT_NE(gaugeAccessibilityProperty, nullptr);
    EXPECT_TRUE(gaugeAccessibilityProperty->HasRange());
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().current, VALUE);
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().max, MAX);
    EXPECT_EQ(gaugeAccessibilityProperty->GetAccessibilityValue().min, MIN);
}

/**
 * @tc.name: GaugeAccessibilityPropertyTestNg002
 * @tc.desc: Test the Text property of Gauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeAccessibilityPropertyTestNg002, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto gaugeAccessibilityProperty = frameNode->GetAccessibilityProperty<GaugeAccessibilityProperty>();
    ASSERT_NE(gaugeAccessibilityProperty, nullptr);
    EXPECT_EQ(gaugeAccessibilityProperty->GetText(), std::to_string(VALUE));
}

/**
 * @tc.name: NewPaint001
 * @tc.desc: Test the NewPaint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, NewPaint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto nodePaintMethod = gaugePattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);
    ASSERT_NE(gaugePaint, nullptr);
    RefPtr<RenderContext> rendercontext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.steps: step2. Update padding parameters
     * @tc.expected: Related function is called.
     */
    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));

    /**
     * @tc.steps: step3. Adding Elements to Vector
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);

    /**
     * @tc.cases: case1£ºGaugeType is TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT, function is called.
     */
    gaugePaintProperty->UpdateGradientColors(ColorStopArrayVector);
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT);
    gaugePaint->NewPaint(rsCanvas, paintwrapper);
    EXPECT_EQ(gaugePaintProperty->GetGradientColorsValue(), ColorStopArrayVector);

    /**
     * @tc.cases: case2£ºUpdateGaugeType TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT, function is called.
     */
    gaugePaintProperty->UpdateGradientColors(ColorStopArrayVector);
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    gaugePaint->NewPaint(rsCanvas, paintwrapper);
    EXPECT_EQ(gaugePaintProperty->GetGradientColorsValue(), ColorStopArrayVector);

    /**
     * @tc.cases: case3£ºUpdateGaugeType TYPE_CIRCULAR_MONOCHROME, function is called.
     */
    gaugePaintProperty->UpdateGradientColors(ColorStopArrayVector);
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MONOCHROME);
    gaugePaint->NewPaint(rsCanvas, paintwrapper);
    EXPECT_EQ(gaugePaintProperty->GetGradientColorsValue(), ColorStopArrayVector);
}

/**
 * @tc.name: DrawHighLight001
 * @tc.desc: Test the DrawHighLight
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, DrawHighLight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto nodePaintMethod = gaugePattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);
    ASSERT_NE(gaugePaint, nullptr);

    RefPtr<RenderContext> rendercontext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.steps: step2. Update padding parameters
     * @tc.expected: Related function is called.
     */
    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));

    /**
     * @tc.steps: step3. Adding Elements to Vector
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);

    RenderRingInfo data;
    EXPECT_CALL(rsCanvas, ClipPath(_, _, _)).Times(AtLeast(1));
    gaugePaint->DrawHighLight(rsCanvas, data, DRAWSTARTDEGREE);
}

/**
 * @tc.name: NewDrawIndicator001
 * @tc.desc: Test the NewDrawIndicator
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, NewDrawIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    auto nodePaintMethod = gaugePattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);
    ASSERT_NE(gaugePaint, nullptr);

    RefPtr<RenderContext> rendercontext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    auto* paintwrapper = new PaintWrapper(rendercontext, geometryNode, gaugePaintProperty);
    EXPECT_NE(paintwrapper, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));

    /**
     * @tc.steps: step2. Update padding parameters
     * @tc.expected: Related function is called.
     */
    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::APP_BAR_BACK_SVG);
    gaugePaintProperty->UpdateIsShowIndicator(true);
    gaugePaintProperty->UpdateIndicatorIconSourceInfo(imageSourceInfo);

    gaugePattern->InitIndicatorImage();
    gaugePattern->OnImageLoadSuccess();

    /**
     * @tc.steps: step3. Adding Elements to Vector
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);

    RenderRingInfo data;
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    gaugePaint->NewDrawIndicator(rsCanvas, gaugePaintProperty, data);
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test the Measure
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, Measure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    ASSERT_NE(gaugeLayoutAlgorithm, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));

    /**
     * @tc.steps: step3. Add node and wrapper.
     */
    auto titleChildNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, gaugePattern->GetTitleChildId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->AddChild(titleChildNode);
    auto titleChildWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(titleChildNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(titleChildWrapper, nullptr);
    layoutWrapper->AppendChild(titleChildWrapper);

    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, gaugePattern->GetMinValueTextId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->AddChild(textNode);
    auto textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(textLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textLayoutWrapper);

    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, gaugePattern->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    frameNode->AddChild(descriptionNode);
    auto descriptionWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(descriptionWrapper, nullptr);
    layoutWrapper->AppendChild(descriptionWrapper);

    /**
     * @tc.steps: step3. Set version restrictions.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(VERSION);

    /**
     * @tc.cases: case1£ºSet the size to infinity and compare with the expected value.
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(
        SizeF(Infinity<float>() / SIZE_INFINITY + 1.0f, Infinity<float>() / SIZE_INFINITY + 1.0f));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    gaugeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(SizeF(Infinity<float>() / SIZE_INFINITY + 1.0f, Infinity<float>() / SIZE_INFINITY + 1.0f), SizeF());

    /**
     * @tc.cases: case2£ºSet the size to 300 and compare with the expected value.
     */
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH_1, HEIGHT_1));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    gaugeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(WIDTH_1, HEIGHT_1));
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test the Layout
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, Layout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set version restrictions.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(VERSION);

    /**
     * @tc.steps: step2. Create GaugePaintMethod.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<GaugeLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    ASSERT_NE(gaugeLayoutAlgorithm, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ProgressTheme>()));

    layoutProperty->UpdateIsShowDescription(true);
    /**
     * @tc.steps: step4. Add node and wrapper.
     */
    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, gaugePattern->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    frameNode->AddChild(descriptionNode);
    auto descriptionWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, layoutProperty);
    ASSERT_NE(descriptionWrapper, nullptr);
    layoutWrapper->AppendChild(descriptionWrapper);

    auto titleChildNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, gaugePattern->GetTitleChildId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->AddChild(titleChildNode);
    auto titleChildWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(titleChildNode, geometryNode, layoutProperty);
    ASSERT_NE(titleChildWrapper, nullptr);
    layoutWrapper->AppendChild(titleChildWrapper);

    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, gaugePattern->GetMinValueTextId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode->AddChild(textNode);
    auto textLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, layoutProperty);
    ASSERT_NE(textLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(textLayoutWrapper);

    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    geometryNode->SetContentOffset(OffsetF(50, 50));

    /**
     * @tc.cases: case1£ºSet the padding size and compare it with the expected value.
     */
    gaugeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetPadding()->left, padding.left);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetPadding()->top, padding.top);
}

/**
 * @tc.name: GaugePattern::OnModifyDone
 * @tc.desc: Test the OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnModifyDone, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 11;
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    auto host = gaugePattern->GetHost();
    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    host->AddChild(titleNode);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);

    /**
     * @tc.steps: step2. Update property
     * @tc.expected: Related function is called.
     */
    gaugePaintProperty->UpdateIsShowIndicator(true);
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);
    gaugePaintProperty->UpdateGradientColors(ColorStopArrayVector);
    gaugePaintProperty->UpdateIsShowIndicator(true);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
    gaugePaintProperty->UpdateIndicatorIconSourceInfo(imageSourceInfo);
    auto gaugeLayoutProperty = frameNode->GetLayoutProperty<GaugeLayoutProperty>();
    ASSERT_NE(gaugeLayoutProperty, nullptr);
    gaugeLayoutProperty->UpdateIsShowLimitValue(true);
    gaugeLayoutProperty->UpdateIsShowDescription(true);
    auto customDescriptionNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(customDescriptionNode, nullptr);

    /**
     * @tc.steps: step3. HasDescriptionNode is true.
     * @tc.expected: Related function is called.
     */
    gaugePattern->SetDescriptionNode(customDescriptionNode);
    gaugePattern->OnModifyDone();
    EXPECT_TRUE(gaugePattern->HasDescriptionNode());
}

/**
 * @tc.name: GaugePattern::InitLimitValueText
 * @tc.desc: Test the InitLimitValueText
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, InitLimitValueText, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 11;
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    /**
     * @tc.steps: step2. Create textNode
     * @tc.expected: Related function is called.
     */
    auto valueTextId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto limitValueTextProperty = textNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step3. GetTextColorValue is Color(0xFF64BB5C).
     * @tc.expected: Related function is called.
     */
    limitValueTextProperty->UpdateTextColor(Color::RED);
    gaugePattern->InitLimitValueText(valueTextId, true);
    EXPECT_EQ(limitValueTextProperty->GetTextColorValue(Color::RED), Color(0xFF64BB5C));
}

/**
 * @tc.name: GaugePattern::GetMaxValueColor
 * @tc.desc: Test the GetMaxValueColor
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GetMaxValueColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 11;
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);

    /**
     * @tc.steps: step2. Update property
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    colorStopArray.emplace_back(std::make_pair(Color::RED, Dimension(0.0)));
    ColorStopArrayVector.emplace_back(colorStopArray);
    gaugePaintProperty->UpdateGradientColors(ColorStopArrayVector);

    /**
     * @tc.steps: step3. UpdateGaugeType
     * @tc.expected: Related function is called.
     */
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT);
    auto color = gaugePattern->GetMaxValueColor(gaugePaintProperty);

    /**
     * @tc.steps: step3. color is RED.
     */
    EXPECT_EQ(color, Color::RED);
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    color = gaugePattern->GetMaxValueColor(gaugePaintProperty);

    /**
     * @tc.steps: step3. color is RED.
     */
    EXPECT_EQ(color, Color::RED);
    gaugePaintProperty->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MONOCHROME);
    color = gaugePattern->GetMaxValueColor(gaugePaintProperty);

    /**
     * @tc.steps: step3. color is BLUE.
     */
    EXPECT_EQ(color, Color::BLUE);
}

/**
 * @tc.name: GaugePattern::OnImageLoadSuccess
 * @tc.desc: Test the OnImageLoadSuccess
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnImageLoadSuccess, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 11;
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    /**
     * @tc.steps: step2. Set indicatorIconLoadingCtx_
     * @tc.expected: Related function is called.
     */
    gaugePattern->InitIndicatorImage();
    gaugePattern->indicatorIconLoadingCtx_->dstRect_.x_ = 50;
    gaugePattern->indicatorIconLoadingCtx_->dstRect_.y_ = 100;

    /**
     * @tc.steps: step3. dstRect_ is RectF(50, 100).
     * @tc.expected: Related function is called.
     */
    gaugePattern->OnImageLoadSuccess();
    auto config = gaugePattern->indicatorIconCanvasImage_->GetPaintConfig();
    EXPECT_EQ(config.dstRect_, RectF(50, 100, 0, 0));
}

/**
 * @tc.name: GaugePattern::OnImageDataReady
 * @tc.desc: Test the OnImageDataReady
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnImageDataReady, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->minPlatformVersion_ = 11;
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. frameNode CleanDirty
     * @tc.expected: Related function is called.
     */
    frameNode->layoutProperty_->CleanDirty();
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);

    /**
     * @tc.steps: step3. propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: Related function is called.
     */
    gaugePattern->OnImageDataReady();
    EXPECT_EQ(frameNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF);
}
} // namespace OHOS::Ace::NG

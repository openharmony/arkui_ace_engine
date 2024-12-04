/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/offset.h"
#include "base/log/log_wrapper.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_modifier.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

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
constexpr float NEGATIVE_NUMBER = -100.f;
constexpr float INFINITE = std::numeric_limits<float>::max();
constexpr float SMALL_WIDTH = 400.0f;
constexpr float SMALL_HEIGHT = 400.0f;
constexpr bool SKIP_MEASURE = true;
constexpr bool NO_SKIP_MEASURE = false;
const Alignment ALIGNMENT = Alignment::BOTTOM_RIGHT;
constexpr float DRAWSTARTDEGREE = 0.0f;
constexpr float SIZE_INFINITY = 2.0f;
constexpr float WIDTH_1 = 300.0f;
constexpr float HEIGHT_1 = 300.0f;
constexpr bool SHOW_LIMIT_VALUE = true;
constexpr bool SHOW_DESCRIPTION = false;
constexpr bool SHOW_INDICATOR = true;
const std::string INDICATOR_ICON_PATH = "image1";
const std::string INDICATOR_BUNDLE_NAME = "bundleName";
const std::string INDICATOR_MODULE_NAME = "moduleName";
constexpr Dimension INDICATOR_SPACE = 8.0_vp;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
} // namespace

class GaugeTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback = nullptr);

    RefPtr<FrameNode> frameNode_;
    RefPtr<GaugePattern> pattern_;
    RefPtr<GaugeLayoutProperty> layoutProperty_;
    RefPtr<GaugePaintProperty> paintProperty_;
    RefPtr<GaugeAccessibilityProperty> accessibilityProperty_;
};

void GaugeTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    auto progressTheme = ProgressTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));

    auto gaugeTheme = GaugeTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(GaugeTheme::TypeId())).WillRepeatedly(Return(gaugeTheme));
}

void GaugeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugeTestNg::SetUp() {}

void GaugeTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void GaugeTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GaugePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GaugeLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GaugeAccessibilityProperty>();
}

void GaugeTestNg::Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback)
{
    GaugeModelNG model;
    model.Create(values, min, max);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: GaugePaintPropertyTest001
 * @tc.desc: Test Gauge Create
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge.
     */
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. get value from paintProperty_.
     * @tc.expected: step2. the value is the same with setting.
     */
    EXPECT_EQ(paintProperty_->GetMaxValue(), MAX);
    EXPECT_EQ(paintProperty_->GetMinValue(), MIN);
    EXPECT_EQ(paintProperty_->GetValueValue(), VALUE);
    EXPECT_TRUE(accessibilityProperty_->HasRange());
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().current, VALUE);
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().max, MAX);
    EXPECT_EQ(accessibilityProperty_->GetAccessibilityValue().min, MIN);
    EXPECT_EQ(accessibilityProperty_->GetText(), std::to_string(VALUE));
}

/**
 * @tc.name: GaugePaintPropertyTest002
 * @tc.desc: Test Gauge SetValue SetStartAngle SetEndAngle SetStrokeWidth SetColors
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties.
     */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        model.SetValue(NEW_VALUE);
        model.SetStartAngle(START_ANGLE);
        model.SetEndAngle(END_ANGLE);
        model.SetStrokeWidth(STOKE_WIDTH);
        model.SetColors(COLORS, VALUES);
        model.SetLabelMarkedText(TEST_STRING);
        model.SetMarkedTextColor(TEST_COLOR);
    });

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    EXPECT_EQ(paintProperty_->GetMaxValue(), MAX);
    EXPECT_EQ(paintProperty_->GetMinValue(), MIN);
    EXPECT_EQ(paintProperty_->GetValueValue(), NEW_VALUE);
    EXPECT_EQ(paintProperty_->GetStartAngleValue(), START_ANGLE);
    EXPECT_EQ(paintProperty_->GetEndAngleValue(), END_ANGLE);
    EXPECT_EQ(paintProperty_->GetStrokeWidthValue(), STOKE_WIDTH);
    EXPECT_EQ(paintProperty_->GetColorsValue(), COLORS);
    EXPECT_EQ(paintProperty_->GetValuesValue(), VALUES);
}

/**
 * @tc.name: GaugePaintPropertyTest003
 * @tc.desc: Test gauge pattern OnDirtyLayoutWrapperSwap function..
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge.
     */
    Create(VALUE, MIN, MAX);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);

    /**
     * @tc.steps: step2. call pattern_ OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step2. OnDirtyLayoutWrapperSwap success and result correct.
     */
    auto layoutAlgorithm = frameNode_->GetLayoutAlgorithm();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call gaugePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */
    /**
     *      case 1: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    EXPECT_FALSE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false));

    /**
     *     case 2: LayoutWrapperNode::SkipMeasureContent = true , skipMeasure = true;
     */
    EXPECT_FALSE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = true;
     */
    EXPECT_FALSE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false));

    /**
     *     case 4: LayoutWrapperNode::SkipMeasureContent = false , skipMeasure = false;
     */
    EXPECT_TRUE(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
}

/**
 * @tc.name: GaugeMeasureTest001
 * @tc.desc: Test Gauge MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeMeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge.
     */
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. get layoutWrapper and set layoutAlgorithm.
     * @tc.expected: step2. check layoutAlgorithm is not null.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
    auto layoutAlgorithm = frameNode_->GetLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. compare size with expected value.
     * @tc.expected: step3. size is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *          Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(50).height(50)
     *     }
     */
    LayoutConstraintF layoutConstraintSizeValid;
    layoutConstraintSizeValid.maxSize = MAX_SIZE;
    layoutConstraintSizeValid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintSizeValid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).height(-10)
     *     }
     */
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackWidth_ = WIDTH;
    EXPECT_CALL(*themeManager, GetTheme(ProgressTheme::TypeId())).WillRepeatedly(Return(progressTheme));

    LayoutConstraintF layoutConstraintHeightInvalid;
    layoutConstraintHeightInvalid.maxSize = MAX_SIZE;
    layoutConstraintHeightInvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintHeightInvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(-10)
     *     }
     */
    LayoutConstraintF layoutConstraintWidthInvalid;
    layoutConstraintWidthInvalid.maxSize = MAX_SIZE;
    layoutConstraintWidthInvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintWidthInvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(50)
     *     }
     */
    progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ProgressTheme::TypeId())).WillRepeatedly(Return(progressTheme));

    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutConstraintWidth.maxSize = MAX_SIZE;
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
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
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(HEIGHT.ConvertToPx(), HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: GaugeMeasureTest002
 * @tc.desc: Test Gauge MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeMeasureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge.
     */
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. get layoutWrapper and set layoutAlgorithm.
     * @tc.expected: step2. check layoutAlgorithm is not null.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, layoutProperty_);
    auto layoutAlgorithm = frameNode_->GetLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. compare size with expected value.
     * @tc.expected: step3. size is the same with expected value.
     */
    /**
     *     corresponding ets code:
     *     Row.Width(400).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }})
     *     }
     */
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    progressTheme->trackWidth_ = 500.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(ProgressTheme::TypeId())).WillRepeatedly(Return(progressTheme));

    LayoutConstraintF layoutConstraintSmallWidth;
    layoutConstraintSmallWidth.maxSize = SizeF(SMALL_WIDTH, MAX_HEIGHT);
    layoutConstraint.maxSize = SizeF(SMALL_WIDTH, MAX_HEIGHT);
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    auto gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_WIDTH, SMALL_WIDTH));

    /**
     *    corresponding ets code:
     *     Row.Width(500).Height(400) {
     *         Gauge({ { value: 50, min: 0, max: 100 }})
     *     }
     */
    layoutConstraintSmallWidth.maxSize = SizeF(MAX_WIDTH, SMALL_HEIGHT);
    layoutConstraint.maxSize = SizeF(MAX_WIDTH, SMALL_HEIGHT);
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_HEIGHT, SMALL_HEIGHT));

    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.maxSize = MAX_SIZE;
    layoutConstraintInfinite.maxSize.SetWidth(INFINITE);
    layoutConstraint.maxSize = MAX_SIZE;
    layoutConstraint.maxSize.SetWidth(INFINITE);
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    gaugeSize = layoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

/**
 * @tc.name: GaugeLayoutPropertyTest001
 * @tc.desc: Test Gauge OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge.
     */
    auto themeManager = AceType::DynamicCast<MockThemeManager>(MockPipelineContext::GetCurrent()->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto progressTheme = AceType::MakeRefPtr<ProgressTheme>();
    EXPECT_CALL(*themeManager, GetTheme(ProgressTheme::TypeId())).WillRepeatedly(Return(progressTheme));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. create gauge frameNode, and dataPanelWrapper.
     * @tc.expected: step2. get gaugePattern success.
     */
    pattern_->OnModifyDone();
    layoutProperty_->UpdateAlignment(ALIGNMENT);
    pattern_->OnModifyDone();
    EXPECT_EQ(layoutProperty_->GetPositionProperty()->GetAlignmentValue(), ALIGNMENT);
}

/**
 * @tc.name: GaugePaintMethodTest001
 * @tc.desc: Test Gauge PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintMethod.
     */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    /**
     * @tc.steps: step2. test ShouldHighLight in different cases
     * @tc.expected: the result of ShouldHighLight is correct.
     */
    //     case1 : percent is LessOrEqual than start and LessOrEqual start + interval
    float start = START;
    float interval = INTERVAL;
    float percent = PERCENT;
    bool result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case2 : percent is LessOrEqual than start and GreatOrEqual than start + interval
    start = START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case3 : percent is GreatOrEqual than start and GreatOrEqual than start + interval
    start = LESS_START;
    interval = LESS_INTERVAL;
    percent = PERCENT;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case4 : percent is GreatOrEqual than start and LessOrEqual than start + interval
    start = LESS_START;
    interval = INTERVAL;
    percent = PERCENT;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugePaintMethodTest003
 * @tc.desc: Test Gauge PaintMethod DrawGauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest003, TestSize.Level1)
{
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillOnce(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(1);
    gaugeModifier.DrawGauge(rsCanvas, data);
}

/**
 * @tc.name: GaugePaintMethodTest004
 * @tc.desc: Test Gauge PaintMethod DrawIndicator
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest004, TestSize.Level1)
{
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
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
    gaugeModifier.DrawIndicator(rsCanvas, data);
}

/**
 * @tc.name: GaugePaintMethodTest005
 * @tc.desc: Test Gauge PaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge without set shadowOptions.
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX);

    /**
     * @tc.steps: step2. UpdateContentModifier
     * @tc.expected: Expect the result to be false.
     */
    auto paintMethod = pattern_->CreateNodePaintMethod();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty_);
    paintMethod->UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_FALSE(paintProperty_->HasShadowOptions());

    /**
     * @tc.steps: step3. create gauge with set shadowOptions.
     */
    GaugeShadowOptions shadowOptions;
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX,
        [shadowOptions](GaugeModelNG model) { model.SetShadowOptions(shadowOptions); });

    /**
     * @tc.steps: step4. UpdateContentModifier
     * @tc.expected: Expect the result to be shadowOptions.
     */
    paintMethod = pattern_->CreateNodePaintMethod();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        frameNode_->GetRenderContext(), frameNode_->GetGeometryNode(), paintProperty_);
    paintMethod->UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(paintProperty_->GetShadowOptionsValue(), shadowOptions);
}

/**
 * @tc.name: GaugePaintMethodTest006
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest006, TestSize.Level1)
{
    /**
     * case 1: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 1 max = 3
     * startAngle = 50         endAngle = 450
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 50.0_vp
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(METHOD_END_ANGLE);
        model.SetStrokeWidth(WIDTH);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest007
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest007, TestSize.Level1)
{
    /**
     * case 2: Paint return because colors.size() != weights.size()
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(METHOD_END_ANGLE);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f };
        model.SetColors(colors, values);
        model.SetStrokeWidth(WIDTH);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest008
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest008, TestSize.Level1)
{
    /**
     * case 3: Paint return because colors.size() = 0 and weights.size = 0
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(METHOD_END_ANGLE);
        std::vector<Color> colors = {};
        std::vector<float> values = {};
        model.SetColors(colors, values);
        model.SetStrokeWidth(WIDTH);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest009
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest009, TestSize.Level1)
{
    /**
     * case 4: Paint return because colors.size() = 0
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(METHOD_END_ANGLE);
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f };
        model.SetColors(colors, values);
        model.SetStrokeWidth(WIDTH);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest010
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest010, TestSize.Level1)
{
    /**
     * case 5: Paint return because total weight is 0.0
     */
    Create(METHOD_VALUE, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(METHOD_END_ANGLE);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, -1.0f };
        model.SetColors(colors, values);
        model.SetStrokeWidth(WIDTH);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest011
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest011, TestSize.Level1)
{
    /**
     * case 6: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 1 max = 3
     * startAngle = 50         endAngle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    Create(VALUE_BIG, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(METHOD_START_ANGLE);
        model.SetEndAngle(ZERO);
        model.SetStrokeWidth(WIDTH_SMALL);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest012
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest012, TestSize.Level1)
{
    /**
     * case 7: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startAngle = 0         endAngle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    Create(VALUE_SMALL, METHOD_MIN, METHOD_MAX, [](GaugeModelNG model) {
        model.SetStartAngle(ZERO);
        model.SetEndAngle(ZERO);
        model.SetStrokeWidth(WIDTH_SMALL);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest013
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest013, TestSize.Level1)
{
    /**
     * case 8: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 3 max = 1
     * colors = {red,green} values = {1,2};
     * StrokeWidth = -50.0_vp
     */
    Create(METHOD_VALUE, METHOD_MAX, METHOD_MIN, [](GaugeModelNG model) {
        model.SetStrokeWidth(-WIDTH);
        std::vector<Color> colors = { Color::RED, Color::GREEN };
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest014
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest014, TestSize.Level1)
{
    /**
     * case 9: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 3 max = 1
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    Create(VALUE_BIG, METHOD_MAX, METHOD_MIN, [](GaugeModelNG model) {
        model.SetStrokeWidth(WIDTH);
        std::vector<Color> colors = { Color::RED };
        std::vector<float> values = { 1.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest015
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest015, TestSize.Level1)
{
    /**
     * case 10: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startAngle = NAN       endAngle = NAN
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    Create(VALUE_SMALL, METHOD_MAX, METHOD_MIN, [](GaugeModelNG model) {
        model.SetStrokeWidth(WIDTH);
        model.SetStartAngle(NAN);
        model.SetEndAngle(NAN);
        std::vector<Color> colors = { Color::RED };
        std::vector<float> values = { 1.0f };
        model.SetColors(colors, values);
    });

    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}

/**
 * @tc.name: GaugePaintMethodTest016
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest016, TestSize.Level1)
{
    /**
     * case: colors.size != VALUES.size.
     */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<ColorStopArray> colors;
        ColorStopArray colorStopArray;
        for (const auto& color : COLORS) {
            colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
        }
        colors.emplace_back(colorStopArray);
        model.SetGradientColors(colors, VALUES, GaugeType::TYPE_CIRCULAR_MONOCHROME);
    });

    GaugeModifier modifier = GaugeModifier(pattern_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    DrawingContext context = { rsCanvas, 1.f, 1.f };
    modifier.onDraw(context);

    paintProperty_->ResetValues();
    modifier.onDraw(context);

    modifier.SetUseContentModifier(true);
    modifier.onDraw(context);
}

/**
 * @tc.name: GaugePaintMethodTest017
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest017, TestSize.Level1)
{
    /**
     * case: endAngle - startAngle > DEFAULT_END_DEGREE.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<ColorStopArray> colors;
        ColorStopArray colorStopArray;
        for (const auto& color : COLORS) {
            colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
        }
        colors.emplace_back(colorStopArray);
        model.SetGradientColors(colors, VALUES, GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
        model.SetIsShowIndicator(false);
        model.SetStartAngle(START_ANGLE);
        model.SetEndAngle(END_ANGLE + DEFAULT_END_DEGREE);
        model.SetStrokeWidth(STOKE_WIDTH);
    });

    pattern_->OnSensitiveStyleChange(true);
    GaugeModifier modifier = GaugeModifier(pattern_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    DrawingContext context = { rsCanvas, 1.f, 1.f };
    modifier.onDraw(context);

    GaugeShadowOptions shadowOptions;
    shadowOptions.isShadowVisible = false;
    paintProperty_->UpdateShadowOptions(shadowOptions);
    paintProperty_->UpdateEndAngle(-DEFAULT_END_DEGREE);
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MONOCHROME);
    paintProperty_->ResetGradientColors();
    layoutProperty_->UpdateEndAngle(-DEFAULT_END_DEGREE);
    PaddingPropertyF padding;
    padding.left = 16.f;
    padding.top = 16.f;
    frameNode_->GetGeometryNode()->UpdatePaddingWithBorder(padding);
    modifier.UpdateValue();
    modifier.onDraw(context);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: GaugePaintMethodTest018
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest018, TestSize.Level1)
{
    /**
     * case: colors.size == VALUES.size.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<ColorStopArray> colors;
        ColorStopArray colorStopArray;
        for (const auto& color : COLORS) {
            colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
        }
        for (size_t i = 0; i < COLORS.size(); ++i) {
            colors.emplace_back(colorStopArray);
        }
        model.SetGradientColors(colors, VALUES, GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT);
    });

    GaugeModifier modifier = GaugeModifier(pattern_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, ClipPath(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    DrawingContext context = { rsCanvas, 1.f, 1.f };
    modifier.onDraw(context);

    paintProperty_->ResetGradientColors();
    paintProperty_->ResetValues();
    GaugeShadowOptions shadowOptions;
    shadowOptions.isShadowVisible = false;
    paintProperty_->UpdateShadowOptions(shadowOptions);
    modifier.onDraw(context);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: GaugePaintMethodTest019
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePaintMethodTest019, TestSize.Level1)
{
    /**
     * case: GaugeType == GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT.
     */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<ColorStopArray> colors;
        ColorStopArray colorStopArray;
        for (const auto& color : COLORS) {
            colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
        }
        colors.emplace_back(colorStopArray);
        model.SetGradientColors(colors, VALUES, GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    });

    GaugeModifier modifier = GaugeModifier(pattern_);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    DrawingContext context = { rsCanvas, 1.f, 1.f };
    modifier.onDraw(context);

    paintProperty_->ResetGradientColors();
    GaugeShadowOptions shadowOptions;
    shadowOptions.isShadowVisible = false;
    paintProperty_->UpdateShadowOptions(shadowOptions);
    modifier.onDraw(context);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: NewPaint001
 * @tc.desc: Test the NewPaint
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, NewPaint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);
    auto nodePaintMethod = pattern_->CreateNodePaintMethod();
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RefPtr<GaugeModifier> gaugeModifier = pattern_->GetContentModifier(AceType::RawPtr(paintWrapper));
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Update padding parameters
     * @tc.expected: Related function is called.
     */
    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    /**
     * @tc.steps: step3. Adding Elements to Vector
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);

    /**
     * @tc.cases: case1 GaugeType is TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT, function is called.
     */
    paintProperty_->UpdateGradientColors(ColorStopArrayVector);
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT);
    gaugeModifier->NewPaintCircularAndIndicator(rsCanvas);
    EXPECT_EQ(paintProperty_->GetGradientColorsValue(), ColorStopArrayVector);

    /**
     * @tc.cases: case2 GaugeType is TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT, function is called.
     */
    paintProperty_->UpdateGradientColors(ColorStopArrayVector);
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    gaugeModifier->NewPaintCircularAndIndicator(rsCanvas);
    EXPECT_EQ(paintProperty_->GetGradientColorsValue(), ColorStopArrayVector);

    /**
     * @tc.cases: case3 GaugeType is TYPE_CIRCULAR_MONOCHROME, function is called.
     */
    paintProperty_->UpdateGradientColors(ColorStopArrayVector);
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MONOCHROME);
    gaugeModifier->NewPaintCircularAndIndicator(rsCanvas);
    EXPECT_EQ(paintProperty_->GetGradientColorsValue(), ColorStopArrayVector);
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
    Create(VALUE, MIN, MAX);
    auto nodePaintMethod = pattern_->CreateNodePaintMethod();
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);

    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RefPtr<GaugeModifier> gaugeModifier = pattern_->GetContentModifier(AceType::RawPtr(paintWrapper));
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
    gaugeModifier->DrawHighLight(rsCanvas, data, DRAWSTARTDEGREE);
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
    Create(VALUE, MIN, MAX);
    auto nodePaintMethod = pattern_->CreateNodePaintMethod();
    auto gaugePaint = AceType::DynamicCast<GaugePaintMethod>(nodePaintMethod);

    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RefPtr<GaugeModifier> gaugeModifier = pattern_->GetContentModifier(AceType::RawPtr(paintWrapper));
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Update padding parameters
     * @tc.expected: Related function is called.
     */
    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::APP_BAR_BACK_SVG);
    paintProperty_->UpdateIsShowIndicator(true);
    paintProperty_->UpdateIndicatorIconSourceInfo(imageSourceInfo);

    pattern_->InitIndicatorImage();
    pattern_->OnImageLoadSuccess();

    /**
     * @tc.steps: step3. Adding Elements to Vector
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);

    RenderRingInfo data;
    gaugeModifier->NewDrawIndicator(rsCanvas, paintProperty_, data);

    data.radius = 300.0;
    float pathStartVertexX = 10.0;
    float pathStartVertexY = 12.0;
    RSPath path;
    gaugeModifier->CreateDefaultTrianglePath(pathStartVertexX, pathStartVertexY, data.radius, path);
    EXPECT_TRUE(path.BuildFromSVGString("  "));
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
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    /**
     * @tc.steps: step3. Add node and wrapper.
     */
    auto titleChildNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetTitleChildId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(titleChildNode);
    auto titleChildWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(titleChildNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(titleChildWrapper);

    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetMinValueTextId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(textNode);
    auto textLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(textLayoutWrapper);

    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(descriptionNode);
    auto descriptionWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(descriptionWrapper);

    /**
     * @tc.cases: case1 Set the size to infinity and compare with the expected value.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(Infinity<float>() / SIZE_INFINITY + 1.0f));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(Infinity<float>() / SIZE_INFINITY + 1.0f));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(),
        SizeF(Infinity<float>() / SIZE_INFINITY + 1.0f, Infinity<float>() / SIZE_INFINITY + 1.0f)));

    /**
     * @tc.cases: case2 Set the size to 300 and compare with the expected value.
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(WIDTH_1));
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(HEIGHT_1));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(WIDTH_1, HEIGHT_1)));
}

/**
 * @tc.name: SetLimitFontSize001
 * @tc.desc: Test the SetLimitFontSize
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, SetLimitFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    /**
     * @tc.steps: step3. Add node and wrapper.
     */
    auto titleChildNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetTitleChildId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(titleChildNode);
    auto titleChildWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(titleChildNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(titleChildWrapper);

    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetMinValueTextId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(textNode);
    auto textLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(textLayoutWrapper);

    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, pattern_->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    frameNode_->AddChild(descriptionNode);
    auto descriptionWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(descriptionWrapper);

    /**
     * @tc.cases: SetLimitFontSize.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    gaugeLayoutAlgorithm->SetLimitFontSize(AceType::RawPtr(layoutWrapper), true, Dimension(0.0));
    gaugeLayoutAlgorithm->SetLimitFontSize(AceType::RawPtr(layoutWrapper), false, Dimension(0.0));
    gaugeLayoutAlgorithm->Measure(nullptr);
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    gaugeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode()));
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test the Layout
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, Layout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePaintMethod.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));
    layoutProperty_->UpdateIsShowDescription(true);

    /**
     * @tc.steps: step3. Add node and wrapper.
     */
    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, pattern_->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    frameNode_->AddChild(descriptionNode);
    auto descriptionWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(descriptionWrapper);

    auto titleChildNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetTitleChildId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(titleChildNode);
    auto titleChildWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(titleChildNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(titleChildWrapper);

    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, pattern_->GetMinValueTextId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(textNode);
    auto textLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(textLayoutWrapper);

    PaddingPropertyF padding;
    padding.left = 20.0f;
    padding.top = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    geometryNode->SetContentOffset(OffsetF(50, 50));
    /**
     * @tc.cases: case1 Set the padding size and compare it with the expected value.
     */
    gaugeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetPadding()->left, padding.left);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetPadding()->top, padding.top);
}

/**
 * @tc.name: Layout002
 * @tc.desc: Test the Layout CheckDescriptionIsImageNode
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, Layout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set version restrictions and Create GaugePaintMethod.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx;
    auto gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    /**
     * @tc.steps: step3. Add node and wrapper.
     */
    auto descriptionNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, pattern_->GetDescriptionNodeId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    frameNode_->AddChild(descriptionNode, true);
    auto descriptionWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(descriptionNode, geometryNode, layoutProperty_);
    layoutWrapper->AppendChild(descriptionWrapper, false);

    /**
     * @tc.cases: case1 Layout and compare it with the expected value.
     */
    gaugeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode()));

    /**
     * @tc.cases: case1 CheckDescriptionIsImageNode and compare it with the expected value.
     */
    gaugeLayoutAlgorithm->CheckDescriptionIsImageNode(layoutWrapper);
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(layoutWrapper->GetHostNode()));
}

/**
 * @tc.name: OnModifyDone
 * @tc.desc: Test the OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnModifyDone, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    frameNode_->AddChild(titleNode);

    /**
     * @tc.steps: step2. Update property
     * @tc.expected: Related function is called.
     */
    paintProperty_->UpdateIsShowIndicator(true);
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    ColorStopArrayVector.push_back(colorStopArray);
    paintProperty_->UpdateGradientColors(ColorStopArrayVector);
    paintProperty_->UpdateIsShowIndicator(true);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
    paintProperty_->UpdateIndicatorIconSourceInfo(imageSourceInfo);
    layoutProperty_->UpdateIsShowLimitValue(true);
    layoutProperty_->UpdateIsShowDescription(true);
    auto customDescriptionNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(customDescriptionNode, nullptr);

    /**
     * @tc.steps: step3. HasDescriptionNode is true.
     * @tc.expected: Related function is called.
     */
    pattern_->SetDescriptionNode(customDescriptionNode);
    pattern_->OnModifyDone();
    pattern_->HideLimitValueText(1, true);
    pattern_->OnImageLoadFail();
    EXPECT_TRUE(pattern_->HasDescriptionNode());
}

/**
 * @tc.name: InitLimitValueText
 * @tc.desc: Test the InitLimitValueText
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, InitLimitValueText, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Create textNode
     * @tc.expected: Related function is called.
     */
    auto valueTextId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto limitValueTextProperty = textNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step3. GetTextColorValue is Color(0xFF64BB5C).
     * @tc.expected: Related function is called.
     */
    limitValueTextProperty->UpdateTextColor(Color::RED);
    pattern_->InitLimitValueText(valueTextId, true);
    EXPECT_EQ(limitValueTextProperty->GetTextColorValue(Color::RED), Color(0xFF64BB5C));
}

/**
 * @tc.name: GetMaxValueColor
 * @tc.desc: Test the GetMaxValueColor
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GetMaxValueColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Update property
     * @tc.expected: Related function is called.
     */
    std::vector<ColorStopArray> ColorStopArrayVector;
    ColorStopArray colorStopArray;
    colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    colorStopArray.emplace_back(std::make_pair(Color::RED, Dimension(0.0)));
    ColorStopArrayVector.emplace_back(colorStopArray);
    paintProperty_->UpdateGradientColors(ColorStopArrayVector);

    /**
     * @tc.cases: case1 GaugeType is TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT, expected color is RED.
     */
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT);
    auto color = pattern_->GetMaxValueColor(paintProperty_);
    EXPECT_EQ(color, Color::RED);

    /**
     * @tc.cases: case2 GaugeType is TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT, expected color is RED.
     */
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    color = pattern_->GetMaxValueColor(paintProperty_);
    EXPECT_EQ(color, Color::RED);

    /**
     * @tc.cases: case3 GaugeType is TYPE_CIRCULAR_MONOCHROME, expected color is BLUE.
     */
    paintProperty_->UpdateGaugeType(GaugeType::TYPE_CIRCULAR_MONOCHROME);
    color = pattern_->GetMaxValueColor(paintProperty_);
    EXPECT_EQ(color, Color::BLUE);
}

/**
 * @tc.name: OnImageLoadSuccess001
 * @tc.desc: Test the OnImageLoadSuccess
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnImageLoadSuccess001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Set indicatorIconLoadingCtx_
     * @tc.expected: Related function is called.
     */
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::APP_BAR_BACK_SVG);
    paintProperty_->UpdateIndicatorIconSourceInfo(imageSourceInfo);
    pattern_->InitIndicatorImage();
    pattern_->indicatorIconLoadingCtx_->dstRect_.x_ = 50;
    pattern_->indicatorIconLoadingCtx_->dstRect_.y_ = 100;

    /**
     * @tc.steps: step3. dstRect_ is RectF(50, 100).
     * @tc.expected: Related function is called.
     */
    pattern_->OnImageLoadSuccess();
    auto config = pattern_->indicatorIconCanvasImage_->GetPaintConfig();
    EXPECT_TRUE(IsEqual(config.dstRect_, RectF(50, 100, 0, 0)));
}

/**
 * @tc.name: GaugePattern::OnImageLoadSuccess002
 * @tc.desc: Test the OnImageLoadSuccess
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnImageLoadSuccess002, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. Set indicatorIconLoadingCtx_
     * @tc.expected: Related function is called.
     */
    pattern_->InitIndicatorImage();
    pattern_->indicatorIconLoadingCtx_->dstRect_.x_ = 50;
    pattern_->indicatorIconLoadingCtx_->dstRect_.y_ = 100;

    /**
     * @tc.steps: step3. HasIndicatorIconSourceInfo is false.
     * @tc.expected: Related function is called.
     */
    pattern_->OnImageLoadSuccess();
    EXPECT_FALSE(paintProperty_->HasIndicatorIconSourceInfo());
}

/**
 * @tc.name: OnImageDataReady001
 * @tc.desc: Test the OnImageDataReady
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, OnImageDataReady001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create(VALUE, MIN, MAX);

    /**
     * @tc.steps: step2. frameNode CleanDirty
     * @tc.expected: Related function is called.
     */
    layoutProperty_->CleanDirty();

    /**
     * @tc.steps: step3. propertyChangeFlag_ is PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: Related function is called.
     */
    pattern_->OnImageDataReady();
    EXPECT_EQ(layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF);
}

/**
 * @tc.name: GaugeModelNGTest001
 * @tc.desc: Test GaugeModelNG  SetIsShowIndicator SetDescription SetIsShowLimitValue SetIsShowDescription
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties ,and then get frameNode.
     */
    auto customDescriptionNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    Create(VALUE, MIN, MAX, [customDescriptionNode](GaugeModelNG model) {
        model.SetIsShowIndicator(SHOW_INDICATOR);
        model.SetDescription(customDescriptionNode);
        model.SetIsShowLimitValue(SHOW_LIMIT_VALUE);
        model.SetIsShowDescription(SHOW_DESCRIPTION);
    });

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    EXPECT_EQ(paintProperty_->GetIsShowIndicatorValue(), SHOW_INDICATOR);
    EXPECT_EQ(pattern_->descriptionNode_, customDescriptionNode);
    EXPECT_EQ(layoutProperty_->GetIsShowLimitValueValue(), SHOW_LIMIT_VALUE);
    EXPECT_EQ(layoutProperty_->GetIsShowDescriptionValue(), SHOW_DESCRIPTION);
}

/**
 * @tc.name: GaugeModelNGTest002
 * @tc.desc: Test GaugeModelNG SetShadowOptions SetGradientColors SetIndicatorIconPath SetIndicatorSpace
 * @tc.desc: Test GaugeModelNG ResetGradientColors ResetShadowOptions ResetIndicatorIconPath ResetIndicatorSpace
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties ,and then get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);

    GaugeShadowOptions shadowOptions;
    gauge.SetShadowOptions(shadowOptions);

    std::vector<ColorStopArray> colors;
    ColorStopArray colorStopArray;
    for (const auto& color : COLORS) {
        colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    }
    colors.emplace_back(colorStopArray);
    GaugeType type = GaugeType::TYPE_CIRCULAR_MONOCHROME;
    gauge.SetGradientColors(colors, VALUES, type);

    string iconPath = INDICATOR_ICON_PATH;
    string bundleName = INDICATOR_BUNDLE_NAME;
    string moduleName = INDICATOR_MODULE_NAME;
    gauge.SetIndicatorIconPath(iconPath, bundleName, moduleName);
    Dimension space = INDICATOR_SPACE;
    gauge.SetIndicatorSpace(space);
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    EXPECT_EQ(paintProperty_->GetShadowOptionsValue(), shadowOptions);
    EXPECT_EQ(paintProperty_->GetGradientColorsValue(), colors);
    EXPECT_EQ(paintProperty_->GetValuesValue(), VALUES);
    EXPECT_EQ(paintProperty_->GetGaugeTypeValue(), GaugeType::TYPE_CIRCULAR_MONOCHROME);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().src_, INDICATOR_ICON_PATH);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().bundleName_, INDICATOR_BUNDLE_NAME);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().moduleName_, INDICATOR_MODULE_NAME);
    EXPECT_EQ(paintProperty_->GetIndicatorSpaceValue(), INDICATOR_SPACE);

    /**
     * @tc.steps: step3. Reset all Settings properties.
     * @tc.expected: step3. Detects whether the property is reset.
     */

    gauge.ResetGradientColors();
    gauge.ResetShadowOptions();
    gauge.ResetIndicatorIconPath();
    gauge.ResetIndicatorSpace();

    EXPECT_FALSE(paintProperty_->HasShadowOptions());
    EXPECT_FALSE(paintProperty_->HasGradientColors());
    EXPECT_FALSE(paintProperty_->HasValues());
    EXPECT_FALSE(paintProperty_->HasGaugeType());
    EXPECT_FALSE(paintProperty_->HasIndicatorIconSourceInfo());
    EXPECT_FALSE(paintProperty_->HasShadowOptions());
}

/**
 * @tc.name: GaugeModelNGTest003
 * @tc.desc: Test GaugeModelNG SetShadowOptions SetGradientColors SetIndicatorIconPath SetIndicatorSpace
 * @tc.desc: Test GaugeModelNG ResetGradientColors ResetShadowOptions ResetIndicatorIconPath ResetIndicatorSpace
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeModelNGTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties ,and then get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);

    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    GaugeShadowOptions shadowOptions;
    gauge.SetShadowOptions(Referenced::RawPtr(frameNode_), shadowOptions);

    std::vector<ColorStopArray> colors;
    ColorStopArray colorStopArray;
    for (const auto& color : COLORS) {
        colorStopArray.emplace_back(std::make_pair(color, Dimension(0.0)));
    }
    colors.emplace_back(colorStopArray);
    GaugeType type = GaugeType::TYPE_CIRCULAR_MONOCHROME;
    gauge.SetGradientColors(Referenced::RawPtr(frameNode_), colors, VALUES, type);

    string iconPath = INDICATOR_ICON_PATH;
    string bundleName = INDICATOR_BUNDLE_NAME;
    string moduleName = INDICATOR_MODULE_NAME;
    gauge.SetIndicatorIconPath(Referenced::RawPtr(frameNode_), iconPath, bundleName, moduleName);
    Dimension space = INDICATOR_SPACE;
    gauge.SetIndicatorSpace(Referenced::RawPtr(frameNode_), space);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    EXPECT_EQ(paintProperty_->GetShadowOptionsValue(), shadowOptions);
    EXPECT_EQ(paintProperty_->GetGradientColorsValue(), colors);
    EXPECT_EQ(paintProperty_->GetValuesValue(), VALUES);
    EXPECT_EQ(paintProperty_->GetGaugeTypeValue(), GaugeType::TYPE_CIRCULAR_MONOCHROME);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().src_, INDICATOR_ICON_PATH);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().bundleName_, INDICATOR_BUNDLE_NAME);
    EXPECT_EQ(paintProperty_->GetIndicatorIconSourceInfoValue().moduleName_, INDICATOR_MODULE_NAME);
    EXPECT_EQ(paintProperty_->GetIndicatorSpaceValue(), INDICATOR_SPACE);

    /**
     * @tc.steps: step3. Reset all Settings properties.
     * @tc.expected: step3. Detects whether the property is reset.
     */

    gauge.ResetGradientColors(Referenced::RawPtr(frameNode_));
    gauge.ResetShadowOptions(Referenced::RawPtr(frameNode_));
    gauge.ResetIndicatorIconPath(Referenced::RawPtr(frameNode_));
    gauge.ResetIndicatorSpace(Referenced::RawPtr(frameNode_));

    EXPECT_FALSE(paintProperty_->HasShadowOptions());
    EXPECT_FALSE(paintProperty_->HasGradientColors());
    EXPECT_FALSE(paintProperty_->HasValues());
    EXPECT_FALSE(paintProperty_->HasGaugeType());
    EXPECT_FALSE(paintProperty_->HasIndicatorIconSourceInfo());
    EXPECT_FALSE(paintProperty_->HasShadowOptions());
}

/**
 * @tc.name: GaugeModelNGTest004
 * @tc.desc: Test GaugeModelNG  SetIsShowIndicator SetDescription SetIsShowLimitValue SetIsShowDescription
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugeModelNGTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and set the properties ,and then get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);

    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto nodePtr = Referenced::RawPtr(frameNode_);
    gauge.SetValue(nodePtr, NEW_VALUE);
    gauge.SetStartAngle(nodePtr, START_ANGLE);
    gauge.SetEndAngle(nodePtr, END_ANGLE);
    gauge.SetGaugeStrokeWidth(nodePtr, STOKE_WIDTH);
    gauge.SetColors(nodePtr, COLORS, VALUES);
    gauge.SetIsShowIndicator(nodePtr, SHOW_INDICATOR);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    EXPECT_EQ(paintProperty_->GetValueValue(), NEW_VALUE);
    EXPECT_EQ(paintProperty_->GetStartAngleValue(), START_ANGLE);
    EXPECT_EQ(paintProperty_->GetEndAngleValue(), END_ANGLE);
    EXPECT_EQ(paintProperty_->GetStrokeWidthValue(), STOKE_WIDTH);
    EXPECT_EQ(paintProperty_->GetColorsValue(), COLORS);
    EXPECT_EQ(paintProperty_->GetValuesValue(), VALUES);
    EXPECT_EQ(paintProperty_->GetIsShowIndicatorValue(), SHOW_INDICATOR);
}

/**
 * @tc.name: GaugePatternTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Gauge node.
     */
    auto gaugePattern = AceType::MakeRefPtr<GaugePattern>();
    ASSERT_NE(gaugePattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::GAUGE_ETS_TAG, -1, gaugePattern);
    gaugePattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(gaugePaintProperty, nullptr);
    gaugePaintProperty->UpdateValue(VALUE);
    gaugePaintProperty->UpdateMin(MIN);
    gaugePaintProperty->UpdateMax(MAX);
    auto node = [](GaugeConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUE, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    gaugePattern->SetBuilderFunc(node);
    gaugePattern->BuildContentModifierNode();
}

/**
 * @tc.name: GaugePrivacySensitiveTest001
 * @tc.desc: Test OnSensitiveStyleChange
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePrivacySensitiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    Create(VALUE, MIN, MAX);
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto valueTextId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    pattern_->minValueTextId_ = valueTextId;
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. change privacy sensitive and check status.
     */
    pattern_->OnSensitiveStyleChange(false);
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), false);
    pattern_->OnSensitiveStyleChange(true);
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), true);
}

/**
 * @tc.name: GaugePrivacySensitiveTest002
 * @tc.desc: Test OnSensitiveStyleChange maxValue
 * @tc.type: FUNC
 */
HWTEST_F(GaugeTestNg, GaugePrivacySensitiveTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GaugePattern.
     */
    Create(VALUE, MIN, MAX);
    frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto valueTextId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, valueTextId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    pattern_->maxValueTextId_ = valueTextId;
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. change privacy sensitive false and check status.
     */
    pattern_->OnSensitiveStyleChange(false);
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), false);
    /**
     * @tc.steps: step3. change privacy sensitive true and check status.
     */
    pattern_->OnSensitiveStyleChange(true);
    EXPECT_EQ(textPattern->IsSensitiveEnalbe(), true);
}
} // namespace OHOS::Ace::NG

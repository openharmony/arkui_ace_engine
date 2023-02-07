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
#include "base/log/log_wrapper.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
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
} // namespace

class GaugePropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void GaugePropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void GaugePropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

class ProgressTheme : public Theme {
    DECLARE_ACE_TYPE(ProgressTheme, Theme)
public:
    ProgressTheme() = default;
    ~ProgressTheme() override = default;

    Dimension GetTrackWidth() const
    {
        return dimension_;
    }

private:
    Dimension dimension_;
};

/**
 * @tc.name: GaugePatternTest001
 * @tc.desc: Test Gauge Create
 * @tc.type: FUNC
 */
HWTEST_F(GaugePropertyTestNg, GaugePaintPropertyTest001, TestSize.Level1)
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
HWTEST_F(GaugePropertyTestNg, GaugePaintPropertyTest002, TestSize.Level1)
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
HWTEST_F(GaugePropertyTestNg, GaugeMeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gauge and get frameNode.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layoutWrapper and setLayoutAlgorithm.
     * @tc.expected: step2. check gaugeLayoutAlgorithm is not null.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(-10)
     *     }
     */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.maxSize = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintWidthUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     *     corresponding ets code:
     *     Row.Width(500).Height(500) {
     *         Gauge({ { value: 50, min: 0, max: 100 }}).width(50)
     *     }
     */
    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutConstraintWidth.maxSize = MAX_SIZE;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_HEIGHT, SMALL_HEIGHT));

    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.maxSize = MAX_SIZE;
    layoutConstraintInfinite.maxSize.SetWidth(INFINITE);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<ProgressTheme>()));
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

/**
 * @tc.name: GaugePatternTest004
 * @tc.desc: Test Gauge Create
 * @tc.type: FUNC
 */
HWTEST_F(GaugePropertyTestNg, GaugePaintPropertyTest004, TestSize.Level1)
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
HWTEST_F(GaugePropertyTestNg, GaugePaintPropertyTest005, TestSize.Level1)
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
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    EXPECT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step3. call gaugePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step3. OnDirtyLayoutWrapperSwap success and result correct.
     */
    RefPtr<GaugeLayoutAlgorithm> gaugeLayoutAlgorithm = AceType::MakeRefPtr<GaugeLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm, SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     * @tc.steps: step4. call gaugePattern OnDirtyLayoutWrapperSwap function, compare result.
     * @tc.expected: step4. OnDirtyLayoutWrapperSwap success and result correct.
     */

    /**
     *      case 1: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool first_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(first_case);

    /**
     *     case 2: LayoutWrapper::SkipMeasureContent = true , skipMeasure = true;
     */
    bool second_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_FALSE(second_case);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm, NO_SKIP_MEASURE);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    /**
     *     case 3: LayoutWrapper::SkipMeasureContent = false , skipMeasure = true;
     */
    bool third_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, false);
    EXPECT_FALSE(third_case);

    /**
     *     case 4: LayoutWrapper::SkipMeasureContent = false , skipMeasure = false;
     */
    bool forth_case = gaugePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false);
    EXPECT_TRUE(forth_case);
}

/**
 * @tc.name: GaugePatternTest006
 * @tc.desc: Test Gauge OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(GaugePropertyTestNg, GaugeLayoutPropertyTest006, TestSize.Level1)
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
} // namespace OHOS::Ace::NG

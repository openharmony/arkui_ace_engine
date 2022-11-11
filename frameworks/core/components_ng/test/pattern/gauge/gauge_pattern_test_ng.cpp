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

#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const float VALUE = 50.0f;
const float MAX = 100.0f;
const float MIN = 0.0f;
const float NEW_VALUE = 70.0f;
const float START_ANGLE = 0.0f;
const float END_ANGLE = 180.0f;
const Dimension STOKE_WIDTH = 20.0_vp;
const std::vector<Color> COLORS = { Color::BLUE, Color::RED, Color::GREEN };
const std::vector<float> VALUES = { 1.0f, 1.5f, 2.0f };
const std::string TEST_STRING = "test";
const Color TEST_COLOR = Color::BLUE;
const Dimension WIDTH = 50.0_vp;
const Dimension HEIGHT = 50.0_vp;
const float MAX_WIDTH = 500.0f;
const float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const float NEGATIVE_NUMBER = -100;
const float INFINITE = Size::INFINITE_SIZE;
const float SMALL_WIDTH = 400.0f;
const float SMALL_HEIGHT = 400.0f;
} // namespace

class GaugePropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
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
    //     corresponding ets code:
    //          Row.Width(500).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }}).width(50).height(50)
    //     }
    */
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    auto gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSizevalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
    //     corresponding ets code:
    //     Row.Width(500).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }}).height(-10)
    //     }
    */
    LayoutConstraintF layoutConstraintHeightUnvalid;
    layoutConstraintHeightUnvalid.maxSize = MAX_SIZE;
    layoutConstraintHeightUnvalid.selfIdealSize.SetHeight(NEGATIVE_NUMBER);
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintHeightUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
    //     corresponding ets code:
    //     Row.Width(500).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }}).width(-10)
    //     }
    */
    LayoutConstraintF layoutConstraintWidthUnvalid;
    layoutConstraintWidthUnvalid.maxSize = MAX_SIZE;
    layoutConstraintWidthUnvalid.selfIdealSize.SetWidth(NEGATIVE_NUMBER);
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintWidthUnvalid, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
    //     corresponding ets code:
    //     Row.Width(500).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }}).width(50)
    //     }
    */
    LayoutConstraintF layoutConstraintWidth;
    layoutConstraintWidth.selfIdealSize.SetWidth(WIDTH.ConvertToPx());
    layoutConstraintWidth.maxSize = MAX_SIZE;
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(WIDTH.ConvertToPx(), WIDTH.ConvertToPx()));

    /**
    //     corresponding ets code:
    //     Row.Width(500).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }}).height(50)
    //     }
    */
    LayoutConstraintF layoutConstraintHeight;
    layoutConstraintHeight.selfIdealSize.SetHeight(HEIGHT.ConvertToPx());
    layoutConstraintHeight.maxSize = MAX_SIZE;
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintHeight, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(HEIGHT.ConvertToPx(), HEIGHT.ConvertToPx()));

    /**
    //     corresponding ets code:
    //     Row.Width(400).Height(500) {
    //         Gauge({ { value: 50, min: 0, max: 100 }})
    //     }
    */
    LayoutConstraintF layoutConstraintSmallWidth;
    layoutConstraintSmallWidth.maxSize = SizeF(SMALL_WIDTH, MAX_HEIGHT);
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_WIDTH, SMALL_WIDTH));

    /**
    //     corresponding ets code:
    //     Row.Width(500).Height(400) {
    //         Gauge({ { value: 50, min: 0, max: 100 }})
    //     }
    */
    LayoutConstraintF layoutConstraintSmallHeight;
    layoutConstraintSmallWidth.maxSize = SizeF(MAX_WIDTH, SMALL_HEIGHT);
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintSmallWidth, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(SMALL_HEIGHT, SMALL_HEIGHT));

    LayoutConstraintF layoutConstraintInfinite;
    layoutConstraintInfinite.maxSize = MAX_SIZE;
    layoutConstraintInfinite.maxSize.SetWidth(INFINITE);
    gaugeSize = gaugeLayoutAlgorithm->MeasureContent(layoutConstraintInfinite, &layoutWrapper).value();
    EXPECT_EQ(gaugeSize, SizeF(MAX_HEIGHT, MAX_HEIGHT));
}

} // namespace OHOS::Ace::NG
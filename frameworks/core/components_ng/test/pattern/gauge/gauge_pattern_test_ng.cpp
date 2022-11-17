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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

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
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto gaugePaintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    EXPECT_EQ(gaugePaintProperty->GetMaxValue(), MAX);
    EXPECT_EQ(gaugePaintProperty->GetMinValue(), MIN);
    EXPECT_EQ(gaugePaintProperty->GetValueValue(), VALUE);
}

/**
 * @tc.name: GaugePatternTest002
 * @tc.desc: Test Gauge PaintProperty
 * @tc.type: FUNC
 */
HWTEST_F(GaugePropertyTestNg, GaugePaintPropertyTest002, TestSize.Level1)
{
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
 * @tc.desc: Test Gauge Measure.
 * @tc.type: FUNC
 */
HWTEST_F(GaugePropertyTestNg, GaugeMeasureTest003, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto gaugePattern = frameNode->GetPattern<GaugePattern>();
    EXPECT_NE(gaugePattern, nullptr);
    auto gaugeLayoutAlgorithm = gaugePattern->CreateLayoutAlgorithm();
    EXPECT_NE(gaugeLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(gaugeLayoutAlgorithm));

    /**
    //     corresponding ets code:
    //         Gauge({ { value: 50, min: 0, max: 100 }}).width(50).height(50)
    */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    gaugeLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
}

} // namespace OHOS::Ace::NG
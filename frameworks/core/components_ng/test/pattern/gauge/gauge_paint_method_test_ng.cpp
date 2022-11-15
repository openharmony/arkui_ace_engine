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

#include <cmath>

#include "gtest/gtest.h"

#define private public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/render/drawing.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float VALUE = 2.0f;
constexpr float MAX = 3.0f;
constexpr float MIN = 1.0f;
constexpr float VALUE_BIG = 4.0f;
constexpr float VALUE_SMALL = 0.0f;
constexpr float START = 20.0f;
constexpr float LESS_START = 5.0f;
constexpr float INTERVAL = 30.0f;
constexpr float LESS_INTERVAL = -15.0f;
constexpr float PERCENT = 10.0f;
constexpr float START_ANGLE = 50.0f;
constexpr float END_ANGLE = 450.0f;
constexpr float ZERO = 0.0f;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension WIDTH_SMALL = 0.5_vp;
} // namespace
class GaugePaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: GaugePaintMethodTest001
 * @tc.desc: Test Gauge PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(GaugePaintMethodTestNg, GaugePaintPropertyTest001, TestSize.Level1)
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintProperty.
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
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
 * @tc.desc: Test Gauge PaintMethod Paint
 * @tc.type: FUNC
 */
HWTEST_F(GaugePaintMethodTestNg, GaugePaintMethodTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. analysis how to cover all branches.
     */
    /**
    //     branch-1 : value,min,max need to include follow
    // value = 2  min = 1 max = 3
    // value = 4  min = 1 max = 3
    // value = 0  min = 1 max = 3
    // value = 2  min = 3 max = 1
    // value = 4  min = 3 max = 1
    // value = 0  min = 3 max = 1
    */
    /**
    //     branch-2 : startangle,endangle need to include follow
    // startangle = 50         endangle = 450
    // startangle = 50         endangle = 0
    // startangle = 0         endangle = 0
    // startangle = null endangle = null
    */
    /**
    //     branch-3 : colors,values need to include follow
    // color = {red,green} values = {1,2};
    // color = {} values = {};
    // color = {} values = {1};
    // color = {red} values = {};
    // color = {red} values = {0};
    // color = {red} values = {1};
    */
    /**
    //     branch-4 : StrokeWidth need to include follow
    // StrokeWidth = 50.0_vp
    // StrokeWidth = 0.5_vp
    // StrokeWidth = -50.0_vp
    // StrokeWidth = null
    */

    /**
     * @tc.steps: step2. test in different cases
     */
    GaugeModelNG gauge_case_1;
    gauge_case_1.Create(VALUE, MIN, MAX);
    gauge_case_1.SetStartAngle(START_ANGLE);
    gauge_case_1.SetEndAngle(END_ANGLE);
    std::vector<Color> colors_case_1 = { Color::RED, Color::GREEN };
    std::vector<float> values_case_1 = { 1.0f, 2.0f };
    gauge_case_1.SetColors(colors_case_1, values_case_1);
    gauge_case_1.SetStrokeWidth(WIDTH);
    auto frameNode_case_1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode_case_1, nullptr);
    GaugePaintMethod gaugePaintMethod_case_1;
    RefPtr<RenderContext> rendercontext_case_1;
    auto gaugePaintProperty_case_1 = frameNode_case_1->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_1 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_1 = new PaintWrapper(rendercontext_case_1, geometryNode_case_1, gaugePaintProperty_case_1);
    EXPECT_NE(paintwrapper_case_1, nullptr);
    RenderRingInfo data_case_1;
    RSCanvas rsCanvas_case_1;
    gaugePaintMethod_case_1.Paint(rsCanvas_case_1, paintwrapper_case_1);
    gaugePaintMethod_case_1.DrawGauge(rsCanvas_case_1, data_case_1);
    gaugePaintMethod_case_1.DrawIndicator(rsCanvas_case_1, data_case_1);

    GaugeModelNG gauge_case_2;
    gauge_case_2.Create(VALUE_BIG, MIN, MAX);
    gauge_case_2.SetStartAngle(START_ANGLE);
    gauge_case_2.SetEndAngle(ZERO);
    gauge_case_2.SetStrokeWidth(WIDTH_SMALL);
    std::vector<Color> colors_case_2 = {};
    std::vector<float> values_case_2 = {};
    gauge_case_2.SetColors(colors_case_2, values_case_2);
    auto frameNode_case_2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode_case_2, nullptr);
    GaugePaintMethod gaugePaintMethod_case_2;
    RefPtr<RenderContext> rendercontext_case_2;
    auto gaugePaintProperty_case_2 = frameNode_case_2->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_2 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_2 = new PaintWrapper(rendercontext_case_2, geometryNode_case_2, gaugePaintProperty_case_2);
    EXPECT_NE(paintwrapper_case_2, nullptr);
    RenderRingInfo data_case_2;
    RSCanvas rsCanvas_case_2;
    gaugePaintMethod_case_2.Paint(rsCanvas_case_2, paintwrapper_case_2);
    gaugePaintMethod_case_2.DrawGauge(rsCanvas_case_2, data_case_2);
    gaugePaintMethod_case_2.DrawIndicator(rsCanvas_case_2, data_case_2);

    GaugeModelNG gauge_case_3;
    gauge_case_3.Create(VALUE_SMALL, MIN, MAX);
    gauge_case_3.SetStartAngle(ZERO);
    gauge_case_3.SetEndAngle(ZERO);
    std::vector<Color> colors_case_3 = {};
    std::vector<float> values_case_3 = { 1.0f };
    gauge_case_3.SetColors(colors_case_3, values_case_3);
    auto frameNode_case_3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode_case_3, nullptr);
    GaugePaintMethod gaugePaintMethod_case_3;
    RefPtr<RenderContext> rendercontext_case_3;
    auto gaugePaintProperty_case_3 = frameNode_case_3->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_3 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_3 = new PaintWrapper(rendercontext_case_3, geometryNode_case_3, gaugePaintProperty_case_3);
    EXPECT_NE(paintwrapper_case_3, nullptr);
    RenderRingInfo data_case_3;
    RSCanvas rsCanvas_case_3;
    gaugePaintMethod_case_3.Paint(rsCanvas_case_3, paintwrapper_case_3);
    gaugePaintMethod_case_3.DrawGauge(rsCanvas_case_3, data_case_3);
    gaugePaintMethod_case_3.DrawIndicator(rsCanvas_case_3, data_case_3);

    GaugeModelNG gauge_case_4;
    gauge_case_4.Create(VALUE, MAX, MIN);
    std::vector<Color> colors_case_4 = { Color::RED };
    std::vector<float> values_case_4 = {};
    gauge_case_4.SetColors(colors_case_4, values_case_4);
    gauge_case_4.SetStrokeWidth(0.0_vp);
    auto frameNode_case_4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode_case_4, nullptr);
    GaugePaintMethod gaugePaintMethod_case_4;
    RefPtr<RenderContext> rendercontext_case_4;
    auto gaugePaintProperty_case_4 = frameNode_case_4->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_4 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_4 = new PaintWrapper(rendercontext_case_4, geometryNode_case_4, gaugePaintProperty_case_4);
    EXPECT_NE(paintwrapper_case_4, nullptr);
    RenderRingInfo data_case_4;
    RSCanvas rsCanvas_case_4;
    gaugePaintMethod_case_4.Paint(rsCanvas_case_4, paintwrapper_case_4);
    gaugePaintMethod_case_4.DrawGauge(rsCanvas_case_4, data_case_4);
    gaugePaintMethod_case_4.DrawIndicator(rsCanvas_case_4, data_case_4);

    GaugeModelNG gauge_case_5;
    gauge_case_5.Create(VALUE_BIG, MAX, MIN);
    gauge_case_5.SetStartAngle(START_ANGLE);
    gauge_case_5.SetEndAngle(END_ANGLE);
    std::vector<Color> colors_case_5 = { Color::RED };
    std::vector<float> values_case_5 = { 0.0f };
    gauge_case_5.SetColors(colors_case_5, values_case_5);
    auto frameNode_case_5 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    gauge_case_5.SetStrokeWidth(WIDTH);
    EXPECT_NE(frameNode_case_5, nullptr);
    GaugePaintMethod gaugePaintMethod_case_5;
    RefPtr<RenderContext> rendercontext_case_5;
    auto gaugePaintProperty_case_5 = frameNode_case_5->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_5 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_5 = new PaintWrapper(rendercontext_case_5, geometryNode_case_5, gaugePaintProperty_case_5);
    EXPECT_NE(paintwrapper_case_5, nullptr);
    RenderRingInfo data_case_5;
    RSCanvas rsCanvas_case_5;
    gaugePaintMethod_case_5.Paint(rsCanvas_case_5, paintwrapper_case_5);
    gaugePaintMethod_case_5.DrawGauge(rsCanvas_case_5, data_case_5);
    gaugePaintMethod_case_5.DrawIndicator(rsCanvas_case_5, data_case_5);

    GaugeModelNG gauge_case_6;
    gauge_case_6.Create(VALUE_SMALL, MAX, MIN);
    gauge_case_6.SetStartAngle(START_ANGLE);
    gauge_case_6.SetEndAngle(END_ANGLE);
    gauge_case_6.SetStrokeWidth(WIDTH);
    std::vector<Color> colors_case_6 = { Color::RED };
    std::vector<float> values_case_6 = { 1.0f };
    gauge_case_6.SetColors(colors_case_6, values_case_6);
    auto frameNode_case_6 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode_case_6, nullptr);
    GaugePaintMethod gaugePaintMethod_case_6;
    RefPtr<RenderContext> rendercontext_case_6;
    auto gaugePaintProperty_case_6 = frameNode_case_6->GetPaintProperty<GaugePaintProperty>();
    RefPtr<GeometryNode> geometryNode_case_6 = AceType::MakeRefPtr<GeometryNode>();
    auto* paintwrapper_case_6 = new PaintWrapper(rendercontext_case_6, geometryNode_case_6, gaugePaintProperty_case_6);
    EXPECT_NE(paintwrapper_case_6, nullptr);
    RenderRingInfo data_case_6;
    RSCanvas rsCanvas_case_6;
    gaugePaintMethod_case_6.Paint(rsCanvas_case_6, paintwrapper_case_6);
    gaugePaintMethod_case_6.DrawGauge(rsCanvas_case_6, data_case_6);
    gaugePaintMethod_case_6.DrawIndicator(rsCanvas_case_6, data_case_6);
}

} // namespace OHOS::Ace::NG
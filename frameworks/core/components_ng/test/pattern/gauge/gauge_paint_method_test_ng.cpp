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
#include "base/geometry/offset.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void GaugePaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void GaugePaintMethodTestNg::TearDownTestCase()
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
 * @tc.desc: Test Gauge PaintMethod DrawGauge
 * @tc.type: FUNC
 */
HWTEST_F(GaugePaintMethodTestNg, GaugePaintMethodTest003, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintMethodTest004, TestSize.Level1)
{
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest001, TestSize.Level1)
{
    /**
     * case 1: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 1 max = 3
     * startangle = 50         endangle = 450
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest002, TestSize.Level1)
{
    /**
     * case 2: Paint retrun because colors.size() != weights.size()
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest003, TestSize.Level1)
{
    /**
     * case 3: Paint retrun because colors.size() = 0 and weights.size = 0
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest004, TestSize.Level1)
{
    /**
     * case 4: Paint retrun because colors.size() = 0
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest005, TestSize.Level1)
{
    /**
     * case 5: Paint retrun because total weight is 0.0
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
    gauge.SetEndAngle(END_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest006, TestSize.Level1)
{
    /**
     * case 6: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 1 max = 3
     * startangle = 50         endangle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_BIG, MIN, MAX);
    gauge.SetStartAngle(START_ANGLE);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest007, TestSize.Level1)
{
    /**
     * case 7: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startangle = 0         endangle = 0
     * colors = {red,green} values = {1,2};
     * StrokeWidth = 0.5_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_SMALL, MIN, MAX);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest008, TestSize.Level1)
{
    /**
     * case 8: Paint can DrawGauge and DrawIndicator
     * value = 2  min = 1 max = 3
     * colors = {red,green} values = {1,2};
     * StrokeWidth = -50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE, MAX, MIN);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest009, TestSize.Level1)
{
    /**
     * case 9: Paint can DrawGauge and DrawIndicator
     * value = 4  min = 1 max = 3
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_BIG, MAX, MIN);
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
HWTEST_F(GaugePaintMethodTestNg, GaugePaintTest010, TestSize.Level1)
{
    /**
     * case 10: Paint can DrawGauge and DrawIndicator
     * value = 0  min = 1 max = 3
     * startangle = NAN       endangle = NAN
     * colors = {red} values = {1};
     * StrokeWidth = 50.0_vp
     */
    GaugeModelNG gauge;
    gauge.Create(VALUE_SMALL, MAX, MIN);
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

} // namespace OHOS::Ace::NG

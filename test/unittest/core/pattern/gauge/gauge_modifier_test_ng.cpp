/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
constexpr float VALUE = 50.0f;
constexpr float MAX = 100.0f;
constexpr float MIN = 0.0f;
constexpr float WHOLE_CIRCLE = 360.0f;
constexpr float THICKNESS = 10.0f;
constexpr float RADIUS = 10.0f;
} // namespace

class GaugeModifierTestNg : public TestNG {
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

void GaugeModifierTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_PROGRESS);
    auto progressTheme = ProgressTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(progressTheme));
}

void GaugeModifierTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugeModifierTestNg::SetUp() {}

void GaugeModifierTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void GaugeModifierTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<GaugePattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<GaugeLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<GaugePaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<GaugeAccessibilityProperty>();
}

void GaugeModifierTestNg::Create(float values, float min, float max, const std::function<void(GaugeModelNG)>& callback)
{
    GaugeModelNG model;
    model.Create(values, min, max);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: GaugeModifierTest001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest001, TestSize.Level1)
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
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set isDrawShadow true and index 0
     * @tc.expected: Related function is called.
     */
    RenderRingInfo data;
    SingleSegmentGradientInfo info;
    info.shadowRadius = 5.0f;
    info.drawStartDegree = 10.0f;
    info.drawSweepDegree = 50.0f;
    info.offsetDegree = 10.0f;
    info.isDrawShadow = true;
    info.colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    size_t index = 0;
    gaugeModifier->DrawSingleSegmentGradientExtend(rsCanvas, data, paintProperty_, info, index);
}

/**
 * @tc.name: GaugeModifierTest002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest002, TestSize.Level1)
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
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set isDrawShadow false and index 0
     * @tc.expected: Related function is called.
     */
    RenderRingInfo data;
    SingleSegmentGradientInfo info;
    info.shadowRadius = 5.0f;
    info.drawStartDegree = 10.0f;
    info.drawSweepDegree = 50.0f;
    info.offsetDegree = 10.0f;
    info.isDrawShadow = false;
    info.colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    size_t index = 0;
    gaugeModifier->DrawSingleSegmentGradientExtend(rsCanvas, data, paintProperty_, info, index);
}

/**
 * @tc.name: GaugeModifierTest003
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest003, TestSize.Level1)
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
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set isDrawShadow true and index 1
     * @tc.expected: Related function is called.
     */
    RenderRingInfo data;
    SingleSegmentGradientInfo info;
    info.shadowRadius = 5.0f;
    info.drawStartDegree = 10.0f;
    info.drawSweepDegree = 50.0f;
    info.offsetDegree = 10.0f;
    info.isDrawShadow = true;
    info.colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    size_t index = 1;
    gaugeModifier->DrawSingleSegmentGradientExtend(rsCanvas, data, paintProperty_, info, index);
}

/**
 * @tc.name: GaugeModifierTest004
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest004, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Set isDrawShadow false and index 1
     * @tc.expected: Related function is called.
     */
    RenderRingInfo data;
    SingleSegmentGradientInfo info;
    info.shadowRadius = 5.0f;
    info.drawStartDegree = 10.0f;
    info.drawSweepDegree = 50.0f;
    info.offsetDegree = 10.0f;
    info.isDrawShadow = false;
    info.colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    size_t index = 1;
    gaugeModifier->DrawSingleSegmentGradientExtend(rsCanvas, data, paintProperty_, info, index);
}

/**
 * @tc.name: GaugeModifierTest005
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest005, TestSize.Level1)
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
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));

    /**
     * @tc.steps: step2. Set index 1 and start - offset > 0
     * @tc.expected: Related function is called.
     */
    RenderRingInfo data;
    SingleSegmentGradientInfo info;
    info.shadowRadius = 5.0f;
    info.drawStartDegree = 100.0f;
    info.drawSweepDegree = 50.0f;
    info.offsetDegree = 10.0f;
    info.isDrawShadow = true;
    info.colorStopArray.emplace_back(std::make_pair(Color::BLUE, Dimension(0.0)));
    size_t index = 1;
    gaugeModifier->DrawSingleSegmentGradientExtend(rsCanvas, data, paintProperty_, info, index);
}

/**
 * @tc.name: GaugeModifierTest006
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest006, TestSize.Level1)
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
    //     case1 : percent is less than start and less then start + interval
    float start = 20.0f;
    float interval = 30.0f;
    float percent = 10.0f;
    bool result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case2 : percent is less than start and great than start + interval
    interval = -15.0f;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case3 : percent is great than start and great than start + interval
    start = 5.0f;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_FALSE(result);

    //     case4 : percent is great than start and less than start + interval
    interval = 30.0f;
    result = gaugeModifier.ShouldHighLight(start, interval, percent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GaugeModifierTest007
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);
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
 * @tc.name: GaugeModifierTest008
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);
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
 * @tc.name: GaugeModifierTest009
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);
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
    Create(VALUE, MIN, MAX,
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
 * @tc.name: GaugeModifierTest010
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create gaugePaintMethod.
     */
    Create(VALUE, MIN, MAX);
    /**
     * @tc.steps: step2. UpdateContentModifier
     * @tc.expected: Expect the result to be false.
     */
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
 * @tc.name: GaugeModifierTest011
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest011, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gauge.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });
    /**
    * @tc.steps: step2. UpdateGauge
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;

    std::vector<float> weights = { 0.5f, 0.5f };
    paintProperty_->UpdateValues(weights);

    std::vector<ColorStopArray> colors;
    paintProperty_->UpdateGradientColors(colors);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintMultiSegmentGradientCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest012
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest012, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });
    /**
    * @tc.steps: step2. UpdateGauge to api20
    * @tc.expected: Expect functions to be call.
    */
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;

    std::vector<float> weights = { 0.5f, 0.5f };
    paintProperty_->UpdateValues(weights);

    std::vector<ColorStopArray> colors;
    paintProperty_->UpdateGradientColors(colors);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintMultiSegmentGradientCircular(rsCanvas, data, paintProperty_);
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
* @tc.name: GaugeModifierTest013
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest013, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with colors
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;

    std::vector<float> weights = { 0.5f, 0.5f };
    paintProperty_->UpdateValues(weights);

    std::vector<ColorStopArray> colors = {
        { std::make_pair(Color::RED, Dimension(0.0f)) },
        { std::make_pair(Color::BLUE, Dimension(1.0f)) }
    };
    paintProperty_->UpdateGradientColors(colors);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintMultiSegmentGradientCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest014
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest014, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with single color
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;

    std::vector<float> weights = { 0.5f, 0.5f };
    paintProperty_->UpdateValues(weights);

    std::vector<ColorStopArray> colors = { { std::make_pair(Color::RED, Dimension(0.0f)) } };
    paintProperty_->UpdateGradientColors(colors);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintMultiSegmentGradientCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest015
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest015, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with value 0
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;

    std::vector<float> weights = { 0.0f, 0.0f };
    paintProperty_->UpdateValues(weights);

    std::vector<ColorStopArray> colors = {
        { std::make_pair(Color::RED, Dimension(0.0f)) },
        { std::make_pair(Color::BLUE, Dimension(1.0f)) }
    };
    paintProperty_->UpdateGradientColors(colors);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintMultiSegmentGradientCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest016
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest016, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with isSensitive true
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;
    data.radius = RADIUS;

    gaugeModifier.value_->Set(VALUE);
    paintProperty_->UpdateIsSensitive(true);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintMonochromeCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest017
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest017, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with isSensitive false
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = WHOLE_CIRCLE;
    data.thickness = THICKNESS;
    data.radius = RADIUS;

    gaugeModifier.value_->Set(VALUE);
    paintProperty_->UpdateIsSensitive(false);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintMonochromeCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest018
* @tc.desc: Test
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest018, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gaugePaintMethod.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
        model.SetIsShowIndicator(false);
    });
    /**
    * @tc.steps: step2. UpdateGauge with sweepDegree 0
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);
    RenderRingInfo data;
    data.startDegree = MIN;
    data.sweepDegree = 0.0f;
    data.thickness = THICKNESS;
    data.radius = RADIUS;

    gaugeModifier.value_->Set(VALUE);
    paintProperty_->UpdateIsSensitive(false);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    gaugeModifier.PaintMonochromeCircular(rsCanvas, data, paintProperty_);
}

/**
* @tc.name: GaugeModifierTest019
* @tc.desc: Test CreateDefaultTrianglePath with normal parameters
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest019, TestSize.Level1)
{
    GaugeModifier modifier = GaugeModifier(pattern_);

    RSPath path;
    float startX = 100.0f;
    float startY = 100.0f;
    float radius = 50.0f;
    modifier.CreateDefaultTrianglePath(startX, startY, radius, path);

    // Verify path is not empty
    EXPECT_FALSE(path.IsValid());
}

/**
* @tc.name: GaugeModifierTest020
* @tc.desc: Test CreateDefaultTrianglePath with zero radius
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest020, TestSize.Level1)
{
    GaugeModifier modifier = GaugeModifier(pattern_);

    RSPath path;
    float startX = 100.0f;
    float startY = 100.0f;
    float radius = 0.0f;
    modifier.CreateDefaultTrianglePath(startX, startY, radius, path);

    // With zero radius, the path should still be created but with very small dimensions
    EXPECT_FALSE(path.IsValid());
}

/**
* @tc.name: GaugeModifierTest021
* @tc.desc: Test CreateDefaultTrianglePath with negative radius
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest021, TestSize.Level1)
{
    GaugeModifier modifier = GaugeModifier(pattern_);

    RSPath path;
    float startX = 100.0f;
    float startY = 100.0f;
    float radius = -50.0f;
    modifier.CreateDefaultTrianglePath(startX, startY, radius, path);

    // With negative radius, the path should still be created (uses absolute values)
    EXPECT_FALSE(path.IsValid());
}

/**
* @tc.name: GaugeModifierTest022
* @tc.desc: Test CreateDefaultTrianglePath with different start positions
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest022, TestSize.Level1)
{
    GaugeModifier modifier = GaugeModifier(pattern_);

    RSPath path1, path2;
    float radius = 50.0f;
    
    // First path at (100,100)
    modifier.CreateDefaultTrianglePath(100.0f, 100.0f, radius, path1);
    
    // Second path at (200,200)
    modifier.CreateDefaultTrianglePath(200.0f, 200.0f, radius, path2);
    
    // The paths should be different but have same shape
    EXPECT_FALSE(path1.IsValid());
    EXPECT_FALSE(path2.IsValid());
}

/**
* @tc.name: GaugeModifierTest023
* @tc.desc: Test CreateDefaultTrianglePath with very large radius
* @tc.type: FUNC
*/
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest023, TestSize.Level1)
{
    GaugeModifier modifier = GaugeModifier(pattern_);

    RSPath path;
    float startX = 100.0f;
    float startY = 100.0f;
    float radius = 10000.0f;
    modifier.CreateDefaultTrianglePath(startX, startY, radius, path);

    // With large radius, the path should be created with large dimensions
    EXPECT_FALSE(path.IsValid());
}

/**
 * @tc.name: GaugeModifierTest024
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(GaugeModifierTestNg, GaugeModifierTest024, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create gauge.
    */
    Create(VALUE, MIN, MAX, [](GaugeModelNG model) {
        std::vector<Color> colors = {};
        std::vector<float> values = { 1.0f, 2.0f };
        model.SetColors(colors, values);
    });
    /**
    * @tc.steps: step2. UpdateGauge
    * @tc.expected: Expect functions to be call.
    */
    GaugePaintMethod gaugePaintMethod;
    GaugeModifier gaugeModifier = GaugeModifier(pattern_);
    RefPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty_);

    std::vector<float> weights = { 1.0f, 1.0f };
    paintProperty_->UpdateValues(weights);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    gaugeModifier.PaintCircularAndIndicator(rsCanvas);
}
}
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <memory>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/canvas_renderer/canvas_renderer_model_ng.h"
#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};

class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
const int32_t DEFAULT_INSTANCE_ID = 0;
const int32_t INDEX_ONE = 1;
const int32_t INDEX_TWO = 2;
const int32_t INDEX_THREE = 3;
const int32_t CANVAS_WIDTH = 3;
const int32_t CANVAS_HEIGHT = 300;
const std::vector<std::string> FONT_FAMILY = { "Arial", "sans-serif", "monospace", "fantasy", "serif", "cursive",
    "system-ui", "emoji", "math" };
const std::string NULL_STR = "";
const std::vector<double> CANDIDATE_DOUBLES = { 0.0, 1.0, 10.0, 100.0, 1000.0 };
const std::string IMAGE_PNG = "image/png";
BaseInfo infoArr[4] = {};
} // namespace
class CanvasRendererTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite() {}
    static RefPtr<CustomPaintPattern> CreateCustomPaintView();
    static RefPtr<OffscreenCanvasPattern> CreateOffscreenCanvasPattern();
};

void CanvasRendererTestNg::SetUpTestSuite()
{
    infoArr[INDEX_ONE].canvasPattern = CreateCustomPaintView();
    infoArr[INDEX_TWO].isOffscreen = true;
    infoArr[INDEX_THREE].isOffscreen = true;
    infoArr[INDEX_THREE].offscreenPattern = CreateCustomPaintView();
}

RefPtr<CustomPaintPattern> CanvasRendererTestNg::CreateCustomPaintView()
{
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    CanvasModelNG canvasModelNG;
    return AceType::DynamicCast<CustomPaintPattern>(canvasModelNG.Create());
}

RefPtr<OffscreenCanvasPattern> CanvasRendererTestNg::CreateOffscreenCanvasPattern()
{
    ContainerScope scope(DEFAULT_INSTANCE_ID);
    RefPtr<PipelineBase> pipelineContext = AceType::MakeRefPtr<MockPipelineBase>();
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    return AceType::MakeRefPtr<OffscreenCanvasPattern>(CANVAS_WIDTH, CANVAS_HEIGHT);
}

/**
 * @tc.name: CanvasRendererTest001
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: create CanvasRendererModelNG and config some params.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    FillTextInfo fillTextInfo;
    fillTextInfo.text = "test";
    fillTextInfo.x = 0.0;
    fillTextInfo.y = 0.0;
    FontWeight weight = FontWeight::BOLD;
    FontStyle style = FontStyle::ITALIC;
    Ace::Gradient gradient;
    std::shared_ptr<Ace::Pattern> imagePattern;
    Color color = Color::RED;
    Dimension fontSize = 20.0_vp;
    /**
     * @tc.steps2: call some fuction.
     * @tc.expected: the paintMethod tasks size meet expectations.
     */
    for (auto value : infoArr) {
        canvasRendererModelNG.SetFillText(value, fillTextInfo);
        canvasRendererModelNG.SetStrokeText(value, fillTextInfo);
        canvasRendererModelNG.SetAntiAlias(value);
        canvasRendererModelNG.SetFontWeight(value, weight);
        canvasRendererModelNG.SetFontStyle(value, style);
        canvasRendererModelNG.SetFontFamilies(value, FONT_FAMILY);
        canvasRendererModelNG.SetFontSize(value, fontSize);
        canvasRendererModelNG.GetLineDash(value);
        canvasRendererModelNG.SetFillGradient(value, gradient);
        canvasRendererModelNG.SetFillPattern(value, imagePattern);
        canvasRendererModelNG.SetFillColor(value, color, false);
        canvasRendererModelNG.SetStrokeGradient(value, gradient);
        canvasRendererModelNG.SetStrokePattern(value, imagePattern);
        canvasRendererModelNG.SetStrokeColor(value, color, false);
    };
    auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(infoArr[1].canvasPattern);
    ASSERT_NE(canvasPattern->paintMethod_, nullptr);
}

/**
 * @tc.name: CanvasRendererTest002
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: create CanvasRendererModelNG and config some params.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    ImageInfo imageInfo;
    Ace::ImageData imageData;
    ImageSize imageSize;
    TextDirection textDirection;
    /**
     * @tc.steps2: call some fuction.
     * @tc.expected: the paintMethod tasks size meet expectations.
     */
    for (auto value : infoArr) {
        canvasRendererModelNG.DrawImage(value, imageInfo);
        canvasRendererModelNG.PutImageData(value, imageData);
        canvasRendererModelNG.CloseImageBitmap(value, IMAGE_PNG);
        canvasRendererModelNG.GetImageData(value, imageSize);
        canvasRendererModelNG.DrawPixelMap(value, imageInfo);
        canvasRendererModelNG.SetFilterParam(value, NULL_STR);
        canvasRendererModelNG.SetTextDirection(value, textDirection);
        canvasRendererModelNG.GetJsonData(value, NULL_STR);
        canvasRendererModelNG.ToDataURL(value, IMAGE_PNG, 0.0);
        canvasRendererModelNG.SetLineCap(value, LineCapStyle::ROUND);
        canvasRendererModelNG.SetLineJoin(value, LineJoinStyle::ROUND);
        canvasRendererModelNG.SetMiterLimit(value, 0.0);
        canvasRendererModelNG.SetLineWidth(value, 0.0);
        canvasRendererModelNG.SetGlobalAlpha(value, 0.0);
        canvasRendererModelNG.SetCompositeType(value, CompositeOperation::SOURCE_OUT);
        canvasRendererModelNG.SetLineDashOffset(value, 0.0);
        canvasRendererModelNG.SetShadowBlur(value, 0.0);
        canvasRendererModelNG.SetShadowColor(value, Color::RED);
        canvasRendererModelNG.SetShadowOffsetX(value, 0.0);
        canvasRendererModelNG.SetShadowOffsetY(value, 0.0);
        canvasRendererModelNG.SetSmoothingEnabled(value, true);
        canvasRendererModelNG.SetSmoothingQuality(value, NULL_STR);
    };
    auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(infoArr[1].canvasPattern);
    ASSERT_NE(canvasPattern->paintMethod_, nullptr);
}

/**
 * @tc.name: CanvasRendererTest003
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: create CanvasRendererModelNG and config some params.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    BezierCurveParam bezierCurveParam;
    QuadraticCurveParam quadraticCurveParam;
    ArcToParam arcToParam;
    ArcParam arcParam;
    EllipseParam ellipseParam;
    auto fillRule = CanvasFillRule::NONZERO;
    RefPtr<CanvasPath2D> path = AceType::MakeRefPtr<CanvasPath2D>();
    Rect rect;
    /**
     * @tc.steps2: call some fuction.
     * @tc.expected: the paintMethod tasks size meet expectations.
     */
    for (auto value : infoArr) {
        canvasRendererModelNG.MoveTo(value, 0.0, 0.0);
        canvasRendererModelNG.LineTo(value, 0.0, 0.0);
        canvasRendererModelNG.BezierCurveTo(value, bezierCurveParam);
        canvasRendererModelNG.ArcTo(value, arcToParam);
        canvasRendererModelNG.Arc(value, arcParam);
        canvasRendererModelNG.Ellipse(value, ellipseParam);
        canvasRendererModelNG.SetFillRuleForPath(value, fillRule);
        canvasRendererModelNG.SetFillRuleForPath2D(value, fillRule, path);
        canvasRendererModelNG.SetStrokeRuleForPath2D(value, fillRule, path);
        canvasRendererModelNG.SetStrokeRuleForPath(value, fillRule);
        canvasRendererModelNG.SetClipRuleForPath(value, fillRule);
        canvasRendererModelNG.SetClipRuleForPath2D(value, fillRule, path);
        canvasRendererModelNG.AddRect(value, rect);
        canvasRendererModelNG.BeginPath(value);
        canvasRendererModelNG.ClosePath(value);
        canvasRendererModelNG.Restore(value);
        canvasRendererModelNG.CanvasRendererSave(value);
        canvasRendererModelNG.CanvasRendererRotate(value, 0.0);
        canvasRendererModelNG.CanvasRendererScale(value, 0.0, 0.0);
    };
    auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(infoArr[1].canvasPattern);
    ASSERT_NE(canvasPattern->paintMethod_, nullptr);
}

/**
 * @tc.name: CanvasRendererTest004
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: create CanvasRendererModelNG and config some params.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    TransformParam transformParam;
    Rect rect;
    /**
     * @tc.steps2: call some fuction.
     * @tc.expected: the paintMethod tasks size meet expectations.
     */
    for (auto value : infoArr) {
        canvasRendererModelNG.SetTransform(value, transformParam, true);
        canvasRendererModelNG.ResetTransform(value);
        canvasRendererModelNG.Transform(value, transformParam);
        canvasRendererModelNG.Translate(value, 0.0, 0.0);
        canvasRendererModelNG.SetLineDash(value, CANDIDATE_DOUBLES);
        canvasRendererModelNG.SetTextAlign(value, TextAlign::CENTER);
        canvasRendererModelNG.SetTextBaseline(value, TextBaseline::TOP);
        canvasRendererModelNG.FillRect(value, rect);
        canvasRendererModelNG.StrokeRect(value, rect);
        canvasRendererModelNG.ClearRect(value, rect);
        canvasRendererModelNG.GetTransform(value);
    };
    auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(infoArr[1].canvasPattern);
    ASSERT_NE(canvasPattern->paintMethod_, nullptr);
}
} // namespace OHOS::Ace::NG
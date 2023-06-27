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
const double DEFAULT_DOUBLE0 = 0.0;
const double DEFAULT_DOUBLE1 = 1.0;
const std::string NULL_STR = "";
const float IDEAL_WIDTH = 300.0f;
const float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);
const std::string IMAGE_SRC = "common/images/test.png";
const std::string REPETITION_STR = "repetition";
const std::vector<double> CANDIDATE_DOUBLES = { 0.0, 1.0, 10.0, 100.0, 1000.0 };
const double DEFAULT_DOUBLE10 = 10.0;
const std::string URL_PREFIX = "data:";
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
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;
    PaintState paintState;
    baseInfo.paintState = paintState;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Test functions about text.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    FillTextInfo fillTextInfo;
    fillTextInfo.text = "";
    fillTextInfo.x = 0.0;
    fillTextInfo.y = 0.0;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFillText(baseInfo, fillTextInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetStrokeText(baseInfo, fillTextInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    TextAlign textAlign = TextAlign::CENTER;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetTextAlign(baseInfo, textAlign);
    EXPECT_TRUE(paintMethod->HasTask());

    TextBaseline textBaseline = TextBaseline::ALPHABETIC;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetTextBaseline(baseInfo, textBaseline);
    EXPECT_TRUE(paintMethod->HasTask());

    FontWeight weight = FontWeight::BOLD;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFontWeight(baseInfo, weight);
    EXPECT_TRUE(paintMethod->HasTask());

    FontStyle style = FontStyle::ITALIC;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFontStyle(baseInfo, style);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFontFamilies(baseInfo, FONT_FAMILY);
    EXPECT_TRUE(paintMethod->HasTask());

    Dimension size;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFontSize(baseInfo, size);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest002
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto offscreenPattern = CreateOffscreenCanvasPattern();

    BaseInfo baseInfo;
    baseInfo.offscreenPattern = offscreenPattern;
    baseInfo.isOffscreen = true;

    /**
     * @tc.steps2: Test functions about text.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    auto paintMethod = offscreenPattern->offscreenPaintMethod_;
    ASSERT_NE(paintMethod, nullptr);

    TextAlign textAlign = TextAlign::CENTER;
    canvasRendererModelNG.SetTextAlign(baseInfo, textAlign);
    EXPECT_EQ(paintMethod->fillState_.GetTextAlign(), textAlign);

    Color color = Color::RED;
    canvasRendererModelNG.SetFillColor(baseInfo, color, false);
    EXPECT_EQ(paintMethod->fillState_.GetColor(), color);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetTextColor(), color);

    std::shared_ptr<Ace::Pattern> imagePattern;
    canvasRendererModelNG.SetFillPattern(baseInfo, imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod->fillState_.GetPattern().GetImageWidth(), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->fillState_.GetPattern().GetImageHeight(), DEFAULT_DOUBLE0);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod->fillState_.GetPattern().GetRepetition(), NULL_STR);
}

/**
 * @tc.name: CanvasRendererTest003
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto offscreenPattern = CreateOffscreenCanvasPattern();

    BaseInfo baseInfo;
    baseInfo.offscreenPattern = offscreenPattern;
    baseInfo.isOffscreen = true;

    /**
     * @tc.steps2: Test functions about text.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    auto paintMethod = offscreenPattern->offscreenPaintMethod_;
    ASSERT_NE(paintMethod, nullptr);

    Ace::Gradient gradient;
    canvasRendererModelNG.SetFillGradient(baseInfo, gradient);
    EXPECT_FALSE(paintMethod->fillState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    canvasRendererModelNG.SetFillGradient(baseInfo, gradient);
    EXPECT_TRUE(paintMethod->fillState_.GetGradient().GetRepeat());

    TextBaseline textBaseline = TextBaseline::ALPHABETIC;
    canvasRendererModelNG.SetTextBaseline(baseInfo, textBaseline);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetTextBaseline(), textBaseline);

    Dimension fontSize = 100.0_vp;
    canvasRendererModelNG.SetFontSize(baseInfo, fontSize);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontSize(), fontSize);

    FontStyle style = FontStyle::ITALIC;
    canvasRendererModelNG.SetFontStyle(baseInfo, style);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontStyle(), style);

    FontWeight weight = FontWeight::BOLD;
    canvasRendererModelNG.SetFontWeight(baseInfo, weight);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontWeight(), weight);

    canvasRendererModelNG.SetFontFamilies(baseInfo, FONT_FAMILY);
    EXPECT_EQ(paintMethod->fillState_.GetTextStyle().GetFontFamilies(), FONT_FAMILY);

    EXPECT_TRUE(paintMethod->saveStates_.empty());
    canvasRendererModelNG.CanvasRendererSave(baseInfo);
    EXPECT_FALSE(paintMethod->saveStates_.empty());

    canvasRendererModelNG.Restore(baseInfo);
    EXPECT_TRUE(paintMethod->saveStates_.empty());
}

/**
 * @tc.name: CanvasRendererTest004
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto offscreenPattern = CreateOffscreenCanvasPattern();

    BaseInfo baseInfo;
    baseInfo.offscreenPattern = offscreenPattern;
    baseInfo.isOffscreen = true;

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable strokeState_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    auto paintMethod = offscreenPattern->offscreenPaintMethod_;
    ASSERT_NE(paintMethod, nullptr);

    Color color = Color::RED;
    canvasRendererModelNG.SetStrokeColor(baseInfo, color, false);
    EXPECT_EQ(paintMethod->strokeState_.GetColor(), color);

    std::shared_ptr<Ace::Pattern> imagePattern;
    canvasRendererModelNG.SetStrokePattern(baseInfo, imagePattern);
    EXPECT_DOUBLE_EQ(paintMethod->strokeState_.GetPattern().GetImageWidth(), DEFAULT_DOUBLE0);
    EXPECT_DOUBLE_EQ(paintMethod->strokeState_.GetPattern().GetImageHeight(), DEFAULT_DOUBLE0);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetImgSrc(), NULL_STR);
    EXPECT_EQ(paintMethod->strokeState_.GetPattern().GetRepetition(), NULL_STR);

    Ace::Gradient gradient;
    canvasRendererModelNG.SetStrokeGradient(baseInfo, gradient);
    EXPECT_FALSE(paintMethod->strokeState_.GetGradient().GetRepeat());
    gradient.SetRepeat(true);
    canvasRendererModelNG.SetStrokeGradient(baseInfo, gradient);
    EXPECT_TRUE(paintMethod->strokeState_.GetGradient().GetRepeat());

    auto capStyle = LineCapStyle::ROUND;
    canvasRendererModelNG.SetLineCap(baseInfo, capStyle);
    EXPECT_EQ(paintMethod->strokeState_.GetLineCap(), capStyle);

    auto joinStyle = LineJoinStyle::ROUND;
    canvasRendererModelNG.SetLineJoin(baseInfo, joinStyle);
    EXPECT_EQ(paintMethod->strokeState_.GetLineJoin(), joinStyle);

    double candiDate = 100.0;
    canvasRendererModelNG.SetLineWidth(baseInfo, candiDate);
    EXPECT_EQ(paintMethod->strokeState_.GetLineWidth(), candiDate);

    canvasRendererModelNG.SetMiterLimit(baseInfo, candiDate);
    EXPECT_EQ(paintMethod->strokeState_.GetMiterLimit(), candiDate);
}

/**
 * @tc.name: CanvasRendererTest005
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto offscreenPattern = CreateOffscreenCanvasPattern();

    BaseInfo baseInfo;
    baseInfo.offscreenPattern = offscreenPattern;
    baseInfo.isOffscreen = true;

    /**
     * @tc.steps2: Test all interfaces beginning with "Get" and "Set", which related to the variable strokeState_.
     * @tc.expected: The return values of interfaces beginning with "Get" are equal to the input parameters of
     *               corresponding interfaces beginning with "Set"
     */
    auto paintMethod = offscreenPattern->offscreenPaintMethod_;
    ASSERT_NE(paintMethod, nullptr);

    double candiDate = 100.0;
    canvasRendererModelNG.SetGlobalAlpha(baseInfo, candiDate);
    EXPECT_DOUBLE_EQ(paintMethod->globalState_.GetAlpha(), candiDate);

    auto compositeOperation = CompositeOperation::SOURCE_OUT;
    canvasRendererModelNG.SetCompositeType(baseInfo, compositeOperation);
    EXPECT_EQ(paintMethod->globalState_.GetType(), compositeOperation);

    Color color = Color::RED;
    canvasRendererModelNG.SetShadowColor(baseInfo, color);
    EXPECT_EQ(paintMethod->shadow_.GetColor(), color);

    canvasRendererModelNG.SetShadowOffsetX(baseInfo, CANDIDATE_DOUBLES[0]);
    canvasRendererModelNG.SetShadowOffsetY(baseInfo, CANDIDATE_DOUBLES[0]);
    canvasRendererModelNG.SetShadowBlur(baseInfo, CANDIDATE_DOUBLES[0]);
    EXPECT_FALSE(paintMethod->HasShadow());
    EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[0]);
    EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[0]);
    EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[0]);
    for (uint32_t i = 1; i < CANDIDATE_DOUBLES.size(); ++i) {
        canvasRendererModelNG.SetShadowOffsetX(baseInfo, CANDIDATE_DOUBLES[i]);
        canvasRendererModelNG.SetShadowOffsetY(baseInfo, CANDIDATE_DOUBLES[i]);
        canvasRendererModelNG.SetShadowBlur(baseInfo, CANDIDATE_DOUBLES[i]);
        EXPECT_TRUE(paintMethod->HasShadow());
        EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetOffset().GetX(), CANDIDATE_DOUBLES[i]);
        EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetOffset().GetY(), CANDIDATE_DOUBLES[i]);
        EXPECT_DOUBLE_EQ(paintMethod->shadow_.GetBlurRadius(), CANDIDATE_DOUBLES[i]);
    }
}

/**
 * @tc.name: CanvasRendererTest006
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps2: Call the function SetLineDash and SetLineDashOffset.
     * @tc.expected: The value of GetLineDash().dashOffset is equal to DEFAULT_DOUBLE10.
     */
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetLineDashOffset(baseInfo, DEFAULT_DOUBLE10);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetLineDash(baseInfo, CANDIDATE_DOUBLES);
    EXPECT_TRUE(paintMethod->HasTask());

    /**
     * @tc.steps3: Call the function ToDataURL.
     * @tc.expected: The return value is beginning with the corresponding type obtained from the input string.
     */
    // std::string imagePng = "image/png,0.0";
    std::string result = canvasRendererModelNG.ToDataURL(baseInfo, IMAGE_PNG, 0.0);
    EXPECT_EQ(result.substr(URL_PREFIX.size(), IMAGE_PNG.size()), IMAGE_PNG);

    canvasRendererModelNG.CanvasRendererSave(baseInfo);
    result = canvasRendererModelNG.ToDataURL(baseInfo, IMAGE_PNG, 0.0);
    EXPECT_EQ(result.substr(URL_PREFIX.size(), IMAGE_PNG.size()), IMAGE_PNG);

    /**
     * @tc.steps4: Call the function GetImageData.
     * @tc.expected: The dirtyWidth and dirtyHeight of the return value are equal to the input value.
     */
    ImageSize imageSize;
    imageSize.left = DEFAULT_DOUBLE1;
    imageSize.top = DEFAULT_DOUBLE1;
    imageSize.width = DEFAULT_DOUBLE1;
    imageSize.height = DEFAULT_DOUBLE1;
    auto imageData = canvasRendererModelNG.GetImageData(baseInfo, imageSize);
    EXPECT_DOUBLE_EQ(imageData->dirtyWidth, DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(imageData->dirtyHeight, DEFAULT_DOUBLE1);

    paintMethod->tasks_.clear();
    canvasRendererModelNG.CanvasRendererSave(baseInfo);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest007
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about TransformParam.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    TransformParam param;
    canvasRendererModelNG.SetTransform(baseInfo, param, false);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.ResetTransform(baseInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.Transform(baseInfo, param);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.CanvasRendererScale(baseInfo, DEFAULT_DOUBLE0, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.Translate(baseInfo, DEFAULT_DOUBLE0, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.CanvasRendererRotate(baseInfo, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    Rect rect;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.FillRect(baseInfo, rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.StrokeRect(baseInfo, rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.ClearRect(baseInfo, rect);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.AddRect(baseInfo, rect);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest008
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about TransformParam.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    Color color = Color::BLACK;
    canvasRendererModelNG.SetShadowColor(baseInfo, color);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetShadowBlur(baseInfo, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetShadowOffsetX(baseInfo, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetShadowOffsetY(baseInfo, DEFAULT_DOUBLE0);
    EXPECT_TRUE(paintMethod->HasTask());

    RefPtr<CanvasPath2D> path = AceType::MakeRefPtr<CanvasPath2D>();
    auto fillRule = CanvasFillRule::NONZERO;
    canvasRendererModelNG.SetStrokeRuleForPath2D(baseInfo, fillRule, path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetStrokeRuleForPath(baseInfo, fillRule);
    EXPECT_TRUE(paintMethod->HasTask());

    std::shared_ptr<Ace::Pattern> pattern;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetStrokePattern(baseInfo, pattern);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetStrokeColor(baseInfo, color, false);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::Gradient gradient;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetStrokeGradient(baseInfo, gradient);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest009
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about path.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    auto fillRule = CanvasFillRule::NONZERO;
    RefPtr<CanvasPath2D> path = AceType::MakeRefPtr<CanvasPath2D>();
    canvasRendererModelNG.SetFillRuleForPath(baseInfo, fillRule);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetFillRuleForPath2D(baseInfo, fillRule, path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetClipRuleForPath(baseInfo, fillRule);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.SetClipRuleForPath2D(baseInfo, fillRule, path);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.BeginPath(baseInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.ClosePath(baseInfo);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest010
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about path.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    canvasRendererModelNG.LineTo(baseInfo, DEFAULT_DOUBLE1, DEFAULT_DOUBLE10);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::CanvasImage canvasImage;
    RefPtr<PixelMap> pixelMap(nullptr);
    ImageInfo imageInfo;
    imageInfo.image = canvasImage;
    imageInfo.imgWidth = DEFAULT_DOUBLE0;
    imageInfo.imgHeight = DEFAULT_DOUBLE0;
    imageInfo.pixelMap = pixelMap;
    imageInfo.isImage = true;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.DrawImage(baseInfo, imageInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    imageInfo.isImage = false;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.DrawImage(baseInfo, imageInfo);
    EXPECT_TRUE(paintMethod->HasTask());

    Ace::ImageData imageData;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.PutImageData(baseInfo, imageData);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest011
 * @tc.desc: Test functions about text.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    CanvasRendererModelNG canvasRendererModelNG;
    auto canvasPattern = CreateCustomPaintView();

    BaseInfo baseInfo;
    baseInfo.canvasPattern = canvasPattern;
    baseInfo.isOffscreen = false;

    auto paintMethod = AceType::DynamicCast<CanvasPaintMethod>(canvasPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->tasks_.clear();
    EXPECT_FALSE(paintMethod->HasTask());

    /**
     * @tc.steps2: Test functions about path.
     * @tc.expected: The task queue of paintMethod is changed to unempty.
     */
    ArcParam arcParam;
    canvasRendererModelNG.Arc(baseInfo, arcParam);
    EXPECT_TRUE(paintMethod->HasTask());

    ArcToParam arcToParam;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.ArcTo(baseInfo, arcToParam);
    EXPECT_TRUE(paintMethod->HasTask());

    paintMethod->tasks_.clear();
    canvasRendererModelNG.MoveTo(baseInfo, DEFAULT_DOUBLE1, DEFAULT_DOUBLE1);
    EXPECT_TRUE(paintMethod->HasTask());

    EllipseParam ellipseParam;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.Ellipse(baseInfo, ellipseParam);
    EXPECT_TRUE(paintMethod->HasTask());

    BezierCurveParam bezierCurveParam;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.BezierCurveTo(baseInfo, bezierCurveParam);
    EXPECT_TRUE(paintMethod->HasTask());

    QuadraticCurveParam quadraticCurveParam;
    paintMethod->tasks_.clear();
    canvasRendererModelNG.QuadraticCurveTo(baseInfo, quadraticCurveParam);
    EXPECT_TRUE(paintMethod->HasTask());
}

/**
 * @tc.name: CanvasRendererTest012
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest012, TestSize.Level1)
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
    EXPECT_EQ(canvasPattern->paintMethod_->tasks_.size(), 13);
    canvasPattern->paintMethod_->tasks_.clear();
}

/**
 * @tc.name: CanvasRendererTest013
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest013, TestSize.Level1)
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
        canvasRendererModelNG.SetFilterParam(value, "");
        canvasRendererModelNG.SetTextDirection(value, textDirection);
        canvasRendererModelNG.GetJsonData(value, "");
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
        canvasRendererModelNG.SetSmoothingQuality(value, "");
    };
    auto canvasPattern = AceType::DynamicCast<NG::CustomPaintPattern>(infoArr[1].canvasPattern);
    ASSERT_NE(canvasPattern->paintMethod_, nullptr);
    EXPECT_EQ(canvasPattern->paintMethod_->tasks_.size(), 18);
    canvasPattern->paintMethod_->tasks_.clear();
}

/**
 * @tc.name: CanvasRendererTest014
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest014, TestSize.Level1)
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
    EXPECT_EQ(canvasPattern->paintMethod_->tasks_.size(), 25);
    canvasPattern->paintMethod_->tasks_.clear();
}

/**
 * @tc.name: CanvasRendererTest015
 * @tc.desc: Test some set function of CanvasRendererModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRendererTestNg, CanvasRendererTest015, TestSize.Level1)
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
    EXPECT_EQ(canvasPattern->paintMethod_->tasks_.size(), 10);
    canvasPattern->paintMethod_->tasks_.clear();
}
} // namespace OHOS::Ace::NG
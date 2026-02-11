/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "compatible/components/svg/svg_animate_declaration.h"
#include "compatible/components/svg/svg_circle_declaration.h"
#include "compatible/components/svg/svg_declaration.h"
#include "compatible/components/svg/svg_ellipse_declaration.h"
#include "compatible/components/svg/svg_fe_blend_declaration.h"
#include "compatible/components/svg/svg_fe_colormatrix_declaration.h"
#include "compatible/components/svg/svg_fe_composite_declaration.h"
#include "compatible/components/svg/svg_fe_declaration.h"
#include "compatible/components/svg/svg_fe_flood_declaration.h"
#include "compatible/components/svg/svg_fe_gaussianblur_declaration.h"
#include "compatible/components/svg/svg_filter_declaration.h"
#include "compatible/components/svg/svg_gradient_declaration.h"
#include "compatible/components/svg/svg_image_declaration.h"
#include "compatible/components/svg/svg_line_declaration.h"
#include "compatible/components/svg/svg_mask_declaration.h"
#include "compatible/components/svg/svg_path_declaration.h"
#include "compatible/components/svg/svg_pattern_declaration.h"
#include "compatible/components/svg/svg_polygon_declaration.h"
#include "compatible/components/svg/svg_rect_declaration.h"
#include "compatible/components/svg/svg_stop_declaration.h"
#include "include/core/SkStream.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_ellipse.h"
#include "core/components_ng/svg/parse/svg_fe_blend.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_flood.h"
#include "core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_image.h"
#include "core/components_ng/svg/parse/svg_line.h"
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_polygon.h"
#include "core/components_ng/svg/parse/svg_rect.h"
#include "core/components_ng/svg/parse/svg_stop.h"
#include "core/components_ng/svg/parse/svg_style.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/parse/svg_use.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string IMAGE_LABEL =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<image id=\"image001\" x=\"150\" y=\"20\" width=\"100\" height=\"100\" href=\"test.png\" />"
    "</svg>";
constexpr float IMAGE_COMPONENT_WIDTH = 100.0f;
constexpr float IMAGE_COMPONENT_HEIGHT = 100.0f;
const std::string URL_1 = "file://data/data/com.example.test/res/example.svg";
const std::string URL_2 = "data://data/data/com.example.test/res/exampleAlt.jpg";
const std::string URL_3 = "/common/media/aaa.png";
const std::string URL_4 = "data:base64";
const std::string URL_5 = "data:image/png;base64,test123";

const std::string CIRCLE_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<circle cx=\"50\" cy=\"50\" r=\"40\" fill=\"red\" />"
    "</svg>";

const std::string ELLIPSE_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<ellipse cx=\"100\" cy=\"50\" rx=\"50\" ry=\"25\" fill=\"green\" />"
    "</svg>";

const std::string LINE_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<line x1=\"10\" y1=\"10\" x2=\"100\" y2=\"100\" stroke=\"black\" stroke-width=\"2\" />"
    "</svg>";

const std::string POLYGON_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<polygon points=\"50,10 90,90 10,90\" fill=\"orange\" />"
    "</svg>";

const std::string POLYLINE_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<polyline points=\"10,10 20,20 30,10 40,20\" fill=\"none\" stroke=\"purple\" />"
    "</svg>";

const std::string PATH_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<path d=\"M10,10 L20,20 L30,10\" fill=\"yellow\" />"
    "</svg>";

const std::string GRADIENT_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"0%\">"
    "<stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" />"
    "<stop offset=\"100%\" style=\"stop-color:rgb(255,0,0);stop-opacity:1\" />"
    "</linearGradient>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"100\" height=\"50\" fill=\"url(#grad1)\" />"
    "</svg>";

const std::string RADIAL_GRADIENT_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<radialGradient id=\"grad2\" cx=\"50%\" cy=\"50%\" r=\"50%\">"
    "<stop offset=\"0%\" style=\"stop-color:rgb(0,0,255);stop-opacity:1\" />"
    "<stop offset=\"100%\" style=\"stop-color:rgb(0,0,0);stop-opacity:1\" />"
    "</radialGradient>"
    "</defs>"
    "<circle cx=\"100\" cy=\"100\" r=\"50\" fill=\"url(#grad2)\" />"
    "</svg>";

const std::string MASK_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<mask id=\"mask1\">"
    "<rect x=\"10\" y=\"10\" width=\"50\" height=\"50\" fill=\"white\" />"
    "</mask>"
    "</defs>"
    "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\" fill=\"blue\" mask=\"url(#mask1)\" />"
    "</svg>";

const std::string FILTER_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<filter id=\"blurFilter\">"
    "<feGaussianBlur in=\"SourceGraphic\" stdDeviation=\"5\" />"
    "</filter>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"100\" height=\"100\" fill=\"red\" filter=\"url(#blurFilter)\" />"
    "</svg>";

const std::string USE_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<circle id=\"myCircle\" cx=\"50\" cy=\"50\" r=\"40\" fill=\"red\" />"
    "</defs>"
    "<use href=\"#myCircle\" x=\"100\" y=\"100\" />"
    "</svg>";

const std::string CLIP_PATH_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<clipPath id=\"clip1\">"
    "<circle cx=\"50\" cy=\"50\" r=\"40\" />"
    "</clipPath>"
    "</defs>"
    "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\" fill=\"blue\" clip-path=\"url(#clip1)\" />"
    "</svg>";

const std::string TRANSFORM_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<rect x=\"10\" y=\"10\" width=\"50\" height=\"50\" fill=\"red\" transform=\"translate(20,20) rotate(45)\" />"
    "</svg>";

const std::string PATTERN_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<defs>"
    "<pattern id=\"pattern1\" x=\"0\" y=\"0\" width=\"20\" height=\"20\" patternUnits=\"userSpaceOnUse\">"
    "<circle cx=\"10\" cy=\"10\" r=\"5\" fill=\"red\" />"
    "</pattern>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"100\" height=\"100\" fill=\"url(#pattern1)\" />"
    "</svg>";

const std::string GROUP_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<g fill=\"red\" stroke=\"black\" stroke-width=\"2\">"
    "<circle cx=\"50\" cy=\"50\" r=\"30\" />"
    "<rect x=\"100\" y=\"10\" width=\"50\" height=\"50\" />"
    "</g>"
    "</svg>";

const std::string COMPLEX_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"500\" height=\"500\" viewBox=\"0 0 500 500\">"
    "<defs>"
    "<linearGradient id=\"lg\" x1=\"0%\" y1=\"0%\" x2=\"100%\" y2=\"100%\">"
    "<stop offset=\"0%\" stop-color=\"red\" />"
    "<stop offset=\"50%\" stop-color=\"green\" />"
    "<stop offset=\"100%\" stop-color=\"blue\" />"
    "</linearGradient>"
    "<filter id=\"f1\">"
    "<feGaussianBlur stdDeviation=\"2\" />"
    "</filter>"
    "<clipPath id=\"cp1\">"
    "<circle cx=\"250\" cy=\"250\" r=\"200\" />"
    "</clipPath>"
    "</defs>"
    "<rect x=\"50\" y=\"50\" width=\"400\" height=\"400\" fill=\"url(#lg)\" "
    "filter=\"url(#f1)\" clip-path=\"url(#cp1)\" />"
    "<circle cx=\"250\" cy=\"250\" r=\"100\" fill=\"white\" opacity=\"0.5\" />"
    "</svg>";

const std::string ANIMATION_SVG =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"200\" height=\"200\">"
    "<circle cx=\"100\" cy=\"100\" r=\"50\" fill=\"red\">"
    "<animate attributeName=\"r\" from=\"50\" to=\"80\" dur=\"2s\" repeatCount=\"indefinite\" />"
    "</circle>"
    "</svg>";

} // namespace
class SvgManagerTestNg : public testing::Test {
public:
};

/**
 * @tc.name: CalcDstRect001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, CalcDstRect001, TestSize.Level1)
{
    SvgImage svgImage;
    Size realSize(0.0f, 0.0f);
    Rect viewBox(10.0f, 10.0f, 100.0f, 100.0f);
    RSRect ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(0.0f, 1.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(1.0f, 0.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(1.0f, 1.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    EXPECT_NE(ret.left_, 0.0f);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgImageTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(IMAGE_LABEL.c_str(), IMAGE_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgImage = AceType::DynamicCast<SvgImage>(svg->children_.at(0));
    std::string test = "test.svg";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "testgif";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
}

/**
 * @tc.name: ParseHrefAttr001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, ParseHrefAttr001, TestSize.Level1)
{
    SvgImage svgImage;
    std::string uri;
    auto ret = svgImage.ParseHrefAttr("");
    EXPECT_EQ(ret, SrcType::UNSUPPORTED);
    ret = svgImage.ParseHrefAttr(URL_3);
    EXPECT_EQ(ret, SrcType::ASSET);
    ret = svgImage.ParseHrefAttr("http://gitee.com");
    EXPECT_EQ(ret, SrcType::NETWORK);
    ret = svgImage.ParseHrefAttr("https://gitee.com");
    EXPECT_EQ(ret, SrcType::NETWORK);
    ret = svgImage.ParseHrefAttr(URL_2);
    EXPECT_EQ(ret, SrcType::BASE64);
    ret = svgImage.ParseHrefAttr(URL_4);
    EXPECT_EQ(ret, SrcType::UNSUPPORTED);
    ret = svgImage.ParseHrefAttr(URL_1);
    EXPECT_EQ(ret, SrcType::ASSET);
}

/**
 * @tc.name: LoadBase64Image001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, LoadBase64Image001, TestSize.Level1)
{
    SvgImage svgImage;
    auto ret = svgImage.LoadBase64Image(URL_5);
    EXPECT_NE(ret, nullptr);
    ret = svgImage.LoadBase64Image(URL_3);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: SvgDomTest002
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDomTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(IMAGE_LABEL.c_str(), IMAGE_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value is true
     */
    auto svgImage = AceType::DynamicCast<SvgImage>(svg->children_.at(0));
    svgImage->imageAttr_.href.clear();
    RSCanvas canvas;
    Size testSize(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT);
    svgImage->imageAttr_.href = "";
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_1;
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.width = Dimension(0.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(0.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.height = Dimension(0.0);
    svgImage->imageAttr_.width = Dimension(0.0);
    EXPECT_EQ(svgImage->imageAttr_.width, Dimension(0.0f));
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_4;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_3;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_2;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    auto width = svgImage->ConvertDimensionToPx(svgImage->imageAttr_.width, testSize, SvgLengthType::HORIZONTAL);
    auto height = svgImage->ConvertDimensionToPx(svgImage->imageAttr_.height, testSize, SvgLengthType::VERTICAL);
    EXPECT_FALSE(LessOrEqual(width, 0.0f));
    EXPECT_FALSE(LessOrEqual(height, 0.0f));
}

/**
 * @tc.name: SvgDomTest003
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDomTest003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(IMAGE_LABEL.c_str(), IMAGE_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgImage = AceType::DynamicCast<SvgImage>(svg->children_.at(0));
    std::string test = "test.svg";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "test.gif";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "test/gif/test/test";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "/path/to/resource";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "./path/to/resource";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    svgImage->imagePath_ = "/images/icons/icon";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
}

// ========== SVG Ellipse Tests (001-005) ==========

/**
 * @tc.name: SvgEllipse001
 * @tc.desc: test SvgEllipse creation and basic attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgEllipse001, TestSize.Level1)
{
    auto ellipse = SvgEllipse::Create();
    EXPECT_NE(ellipse, nullptr);
}

/**
 * @tc.name: SvgEllipse002
 * @tc.desc: test SvgEllipse with valid SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgEllipse002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ELLIPSE_SVG.c_str(), ELLIPSE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgEllipse003
 * @tc.desc: test SvgEllipse AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgEllipse003, TestSize.Level1)
{
    auto ellipse = SvgEllipse::Create();
    EXPECT_NE(ellipse, nullptr);
    Size viewPort(200.0, 200.0);
    auto path = ellipse->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgEllipse004
 * @tc.desc: test SvgEllipse attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgEllipse004, TestSize.Level1)
{
    auto ellipse = SvgEllipse::Create();
    EXPECT_NE(ellipse, nullptr);
    ellipse->SetAttr("cx", "100");
    ellipse->SetAttr("cy", "50");
    ellipse->SetAttr("rx", "50");
    ellipse->SetAttr("ry", "25");
    ellipse->SetAttr("fill", "green");
    Size viewPort(200.0, 200.0);
    auto path = ellipse->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgEllipse005
 * @tc.desc: test SvgEllipse with percentage dimensions
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgEllipse005, TestSize.Level1)
{
    auto ellipse = SvgEllipse::Create();
    EXPECT_NE(ellipse, nullptr);
    ellipse->SetAttr("rx", "25%");
    ellipse->SetAttr("ry", "12.5%");
    Size viewPort(200.0, 200.0);
    auto path = ellipse->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

// ========== SVG Line Tests (001-005) ==========

/**
 * @tc.name: SvgLine001
 * @tc.desc: test SvgLine creation and basic attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgLine001, TestSize.Level1)
{
    auto line = SvgLine::Create();
    EXPECT_NE(line, nullptr);
}

/**
 * @tc.name: SvgLine002
 * @tc.desc: test SvgLine with valid SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgLine002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(LINE_SVG.c_str(), LINE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgLine003
 * @tc.desc: test SvgLine AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgLine003, TestSize.Level1)
{
    auto line = SvgLine::Create();
    EXPECT_NE(line, nullptr);
    Size viewPort(200.0, 200.0);
    auto path = line->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgLine004
 * @tc.desc: test SvgLine attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgLine004, TestSize.Level1)
{
    auto line = SvgLine::Create();
    EXPECT_NE(line, nullptr);
    line->SetAttr("x1", "10");
    line->SetAttr("y1", "10");
    line->SetAttr("x2", "100");
    line->SetAttr("y2", "100");
    line->SetAttr("stroke", "black");
    line->SetAttr("stroke-width", "2");
    Size viewPort(200.0, 200.0);
    auto path = line->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgLine005
 * @tc.desc: test SvgLine with percentage coordinates
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgLine005, TestSize.Level1)
{
    auto line = SvgLine::Create();
    EXPECT_NE(line, nullptr);
    line->SetAttr("x1", "10%");
    line->SetAttr("y1", "10%");
    line->SetAttr("x2", "50%");
    line->SetAttr("y2", "50%");
    Size viewPort(200.0, 200.0);
    auto path = line->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

// ========== SVG Polygon Tests (001-008) ==========

/**
 * @tc.name: SvgPolygon001
 * @tc.desc: test SvgPolygon creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon001, TestSize.Level1)
{
    auto polygon = SvgPolygon::CreatePolygon();
    EXPECT_NE(polygon, nullptr);
}

/**
 * @tc.name: SvgPolygon002
 * @tc.desc: test SvgPolyline creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon002, TestSize.Level1)
{
    auto polyline = SvgPolygon::CreatePolyline();
    EXPECT_NE(polyline, nullptr);
}

/**
 * @tc.name: SvgPolygon003
 * @tc.desc: test SvgPolygon with valid SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(POLYGON_SVG.c_str(), POLYGON_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgPolygon004
 * @tc.desc: test SvgPolyline with valid SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(POLYLINE_SVG.c_str(), POLYLINE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgPolygon005
 * @tc.desc: test SvgPolygon AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon005, TestSize.Level1)
{
    auto polygon = SvgPolygon::CreatePolygon();
    EXPECT_NE(polygon, nullptr);
    polygon->SetAttr("points", "50,10 90,90 10,90");
    Size viewPort(200.0, 200.0);
    auto path = polygon->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgPolygon006
 * @tc.desc: test SvgPolyline AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon006, TestSize.Level1)
{
    auto polyline = SvgPolygon::CreatePolyline();
    EXPECT_NE(polyline, nullptr);
    polyline->SetAttr("points", "10,10 20,20 30,10 40,20");
    Size viewPort(200.0, 200.0);
    auto path = polyline->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgPolygon007
 * @tc.desc: test SvgPolygon with fill attribute
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon007, TestSize.Level1)
{
    auto polygon = SvgPolygon::CreatePolygon();
    EXPECT_NE(polygon, nullptr);
    polygon->SetAttr("points", "50,10 90,90 10,90");
    polygon->SetAttr("fill", "orange");
    Size viewPort(200.0, 200.0);
    auto path = polygon->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgPolygon008
 * @tc.desc: test SvgPolyline with stroke attribute
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPolygon008, TestSize.Level1)
{
    auto polyline = SvgPolygon::CreatePolyline();
    EXPECT_NE(polyline, nullptr);
    polyline->SetAttr("points", "10,10 20,20 30,10 40,20");
    polyline->SetAttr("fill", "none");
    polyline->SetAttr("stroke", "purple");
    Size viewPort(200.0, 200.0);
    auto path = polyline->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

// ========== SVG Path Tests (001-008) ==========

/**
 * @tc.name: SvgPath001
 * @tc.desc: test SvgPath creation and basic attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath001, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
}

/**
 * @tc.name: SvgPath002
 * @tc.desc: test SvgPath with valid SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATH_SVG.c_str(), PATH_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgPath003
 * @tc.desc: test SvgPath AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath003, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 L20,20 L30,10");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

/**
 * @tc.name: SvgPath004
 * @tc.desc: test SvgPath with complex path data
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath004, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 L20,20 L30,10 Z");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

/**
 * @tc.name: SvgPath005
 * @tc.desc: test SvgPath with cubic bezier curves
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath005, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 C20,20 40,20 50,10");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

/**
 * @tc.name: SvgPath006
 * @tc.desc: test SvgPath with arc commands
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath006, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 A20,20 0 1,0 50,10");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

/**
 * @tc.name: SvgPath007
 * @tc.desc: test SvgPath with quadratic bezier curves
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath007, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 Q25,25 40,10");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

/**
 * @tc.name: SvgPath008
 * @tc.desc: test SvgPath with smooth curve commands
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPath008, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetAttr("d", "M10,10 C20,20 30,30 40,10 S60,0 70,10");
    Size viewPort(200.0, 200.0);
    auto resultPath = path->AsPath(viewPort);
    EXPECT_TRUE(resultPath.IsValid());
}

// ========== SVG Gradient Tests (001-007) ==========

/**
 * @tc.name: SvgGradient001
 * @tc.desc: test SvgGradient linear gradient creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient001, TestSize.Level1)
{
    auto linearGradient = SvgGradient::CreateLinearGradient();
    EXPECT_NE(linearGradient, nullptr);
}

/**
 * @tc.name: SvgGradient002
 * @tc.desc: test SvgGradient radial gradient creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient002, TestSize.Level1)
{
    auto radialGradient = SvgGradient::CreateRadialGradient();
    EXPECT_NE(radialGradient, nullptr);
}

/**
 * @tc.name: SvgGradient003
 * @tc.desc: test linear gradient parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(GRADIENT_SVG.c_str(), GRADIENT_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgGradient004
 * @tc.desc: test radial gradient parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(RADIAL_GRADIENT_SVG.c_str(), RADIAL_GRADIENT_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgGradient005
 * @tc.desc: test gradient spread method parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient005, TestSize.Level1)
{
    auto spreadMethod = SvgGradient::ParseSpreadMethod("pad");
    EXPECT_EQ(spreadMethod, SvgSpreadMethod::PAD);

    spreadMethod = SvgGradient::ParseSpreadMethod("reflect");
    EXPECT_EQ(spreadMethod, SvgSpreadMethod::REFLECT);

    spreadMethod = SvgGradient::ParseSpreadMethod("repeat");
    EXPECT_EQ(spreadMethod, SvgSpreadMethod::REPEAT);
}

/**
 * @tc.name: SvgGradient006
 * @tc.desc: test linear gradient with attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient006, TestSize.Level1)
{
    auto linearGradient = SvgGradient::CreateLinearGradient();
    EXPECT_NE(linearGradient, nullptr);
    linearGradient->SetAttr("x1", "0%");
    linearGradient->SetAttr("y1", "0%");
    linearGradient->SetAttr("x2", "100%");
    linearGradient->SetAttr("y2", "100%");
    linearGradient->SetAttr("gradientUnits", "userSpaceOnUse");
}

/**
 * @tc.name: SvgGradient007
 * @tc.desc: test radial gradient with attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgGradient007, TestSize.Level1)
{
    auto radialGradient = SvgGradient::CreateRadialGradient();
    EXPECT_NE(radialGradient, nullptr);
    radialGradient->SetAttr("cx", "50%");
    radialGradient->SetAttr("cy", "50%");
    radialGradient->SetAttr("r", "50%");
    radialGradient->SetAttr("fx", "50%");
    radialGradient->SetAttr("fy", "50%");
}

// ========== SVG Stop Tests (001-004) ==========

/**
 * @tc.name: SvgStop001
 * @tc.desc: test SvgStop creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgStop001, TestSize.Level1)
{
    auto stop = SvgStop::Create();
    EXPECT_NE(stop, nullptr);
}

/**
 * @tc.name: SvgStop002
 * @tc.desc: test SvgStop attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgStop002, TestSize.Level1)
{
    auto stop = SvgStop::Create();
    EXPECT_NE(stop, nullptr);
    stop->SetAttr("offset", "50%");
    stop->SetAttr("stop-color", "red");
    stop->SetAttr("stop-opacity", "0.5");
    auto stopNode = AceType::DynamicCast<SvgStop>(stop);
    ASSERT_NE(stopNode, nullptr);
    auto gradientColor = stopNode->GetGradientColor();
    EXPECT_TRUE(gradientColor.GetHasValue());
}

/**
 * @tc.name: SvgStop003
 * @tc.desc: test SvgStop with different offset values
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgStop003, TestSize.Level1)
{
    auto stop = SvgStop::Create();
    EXPECT_NE(stop, nullptr);
    stop->SetAttr("offset", "0");
    stop->SetAttr("stop-color", "rgb(255,0,0)");
    auto stopNode = AceType::DynamicCast<SvgStop>(stop);
    ASSERT_NE(stopNode, nullptr);
    auto gradientColor = stopNode->GetGradientColor();
    EXPECT_TRUE(gradientColor.GetHasValue());
}

/**
 * @tc.name: SvgStop004
 * @tc.desc: test SvgStop with hex color
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgStop004, TestSize.Level1)
{
    auto stop = SvgStop::Create();
    EXPECT_NE(stop, nullptr);
    stop->SetAttr("offset", "100%");
    stop->SetAttr("stop-color", "#FF0000");
    auto stopNode = AceType::DynamicCast<SvgStop>(stop);
    ASSERT_NE(stopNode, nullptr);
    auto gradientColor = stopNode->GetGradientColor();
    EXPECT_TRUE(gradientColor.GetHasValue());
}

// ========== SVG Mask Tests (001-003) ==========

/**
 * @tc.name: SvgMask001
 * @tc.desc: test SvgMask creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgMask001, TestSize.Level1)
{
    auto mask = SvgMask::Create();
    EXPECT_NE(mask, nullptr);
}

/**
 * @tc.name: SvgMask002
 * @tc.desc: test mask parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgMask002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(MASK_SVG.c_str(), MASK_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgMask003
 * @tc.desc: test SvgMask attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgMask003, TestSize.Level1)
{
    auto mask = SvgMask::Create();
    EXPECT_NE(mask, nullptr);
    mask->SetAttr("x", "10");
    mask->SetAttr("y", "10");
    mask->SetAttr("width", "100");
    mask->SetAttr("height", "100");
    mask->SetAttr("maskUnits", "userSpaceOnUse");
    mask->SetAttr("maskContentUnits", "userSpaceOnUse");
}

// ========== SVG Filter Tests (001-003) ==========

/**
 * @tc.name: SvgFilter001
 * @tc.desc: test SvgFilter creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFilter001, TestSize.Level1)
{
    auto filter = SvgFilter::Create();
    EXPECT_NE(filter, nullptr);
}

/**
 * @tc.name: SvgFilter002
 * @tc.desc: test filter parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFilter002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FILTER_SVG.c_str(), FILTER_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgFilter003
 * @tc.desc: test SvgFilter attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFilter003, TestSize.Level1)
{
    auto filter = SvgFilter::Create();
    EXPECT_NE(filter, nullptr);
    filter->SetAttr("x", "-10%");
    filter->SetAttr("y", "-10%");
    filter->SetAttr("width", "120%");
    filter->SetAttr("height", "120%");
    filter->SetAttr("filterUnits", "userSpaceOnUse");
    filter->SetAttr("primitiveUnits", "userSpaceOnUse");
}

// ========== SVG Use Tests (001-003) ==========

/**
 * @tc.name: SvgUse001
 * @tc.desc: test SvgUse creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgUse001, TestSize.Level1)
{
    auto use = SvgUse::Create();
    EXPECT_NE(use, nullptr);
}

/**
 * @tc.name: SvgUse002
 * @tc.desc: test use element parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgUse002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(USE_SVG.c_str(), USE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgUse003
 * @tc.desc: test SvgUse attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgUse003, TestSize.Level1)
{
    auto use = SvgUse::Create();
    EXPECT_NE(use, nullptr);
    use->SetAttr("href", "#myCircle");
    use->SetAttr("x", "100");
    use->SetAttr("y", "100");
}

// ========== SVG ClipPath Tests (001-003) ==========

/**
 * @tc.name: SvgClipPath001
 * @tc.desc: test SvgClipPath creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgClipPath001, TestSize.Level1)
{
    auto clipPath = SvgClipPath::Create();
    EXPECT_NE(clipPath, nullptr);
}

/**
 * @tc.name: SvgClipPath002
 * @tc.desc: test clip-path parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgClipPath002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CLIP_PATH_SVG.c_str(), CLIP_PATH_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgClipPath003
 * @tc.desc: test SvgClipPath attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgClipPath003, TestSize.Level1)
{
    auto clipPath = SvgClipPath::Create();
    EXPECT_NE(clipPath, nullptr);
    clipPath->SetAttr("clipPathUnits", "userSpaceOnUse");
    clipPath->SetAttr("clip-rule", "evenodd");
}

// ========== SVG Pattern Tests (001-003) ==========

/**
 * @tc.name: SvgPattern001
 * @tc.desc: test SvgPattern creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPattern001, TestSize.Level1)
{
    auto pattern = SvgPattern::Create();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SvgPattern002
 * @tc.desc: test pattern parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPattern002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATTERN_SVG.c_str(), PATTERN_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgPattern003
 * @tc.desc: test SvgPattern attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgPattern003, TestSize.Level1)
{
    auto pattern = SvgPattern::Create();
    EXPECT_NE(pattern, nullptr);
    pattern->SetAttr("x", "0");
    pattern->SetAttr("y", "0");
    pattern->SetAttr("width", "20");
    pattern->SetAttr("height", "20");
    pattern->SetAttr("patternUnits", "userSpaceOnUse");
    pattern->SetAttr("patternContentUnits", "userSpaceOnUse");
}

// ========== SVG Defs Tests (001-002) ==========

/**
 * @tc.name: SvgDefs001
 * @tc.desc: test SvgDefs creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDefs001, TestSize.Level1)
{
    auto defs = SvgDefs::Create();
    EXPECT_NE(defs, nullptr);
}

/**
 * @tc.name: SvgDefs002
 * @tc.desc: test SvgDefs AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDefs002, TestSize.Level1)
{
    auto defs = SvgDefs::Create();
    EXPECT_NE(defs, nullptr);
    SvgLengthScaleRule rule;
    auto path = defs->AsPath(rule);
    EXPECT_TRUE(path.IsValid());
}

// ========== SVG G (Group) Tests (001-004) ==========

/**
 * @tc.name: SvgG001
 * @tc.desc: test SvgG (group) creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgG001, TestSize.Level1)
{
    auto g = SvgG::Create();
    EXPECT_NE(g, nullptr);
}

/**
 * @tc.name: SvgG002
 * @tc.desc: test group parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgG002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(GROUP_SVG.c_str(), GROUP_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgG003
 * @tc.desc: test SvgG AsPath method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgG003, TestSize.Level1)
{
    auto g = SvgG::Create();
    EXPECT_NE(g, nullptr);
    Size viewPort(200.0, 200.0);
    auto path = g->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgG004
 * @tc.desc: test SvgG with transform attribute
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgG004, TestSize.Level1)
{
    auto g = SvgG::Create();
    EXPECT_NE(g, nullptr);
    g->SetAttr("transform", "translate(10,10)");
    g->SetAttr("fill", "red");
}

// ========== SVG Transform Tests (001-005) ==========

/**
 * @tc.name: SvgTransform001
 * @tc.desc: test transform parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgTransform001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_SVG.c_str(), TRANSFORM_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
}

/**
 * @tc.name: SvgTransform002
 * @tc.desc: test translate transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgTransform002, TestSize.Level1)
{
    auto rect = SvgRect::Create();
    EXPECT_NE(rect, nullptr);
    rect->SetAttr("transform", "translate(20,20)");
    Size viewPort(200.0, 200.0);
    auto path = rect->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgTransform003
 * @tc.desc: test rotate transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgTransform003, TestSize.Level1)
{
    auto rect = SvgRect::Create();
    EXPECT_NE(rect, nullptr);
    rect->SetAttr("transform", "rotate(45)");
    Size viewPort(200.0, 200.0);
    auto path = rect->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgTransform004
 * @tc.desc: test scale transform
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgTransform004, TestSize.Level1)
{
    auto circle = SvgCircle::Create();
    EXPECT_NE(circle, nullptr);
    circle->SetAttr("transform", "scale(2)");
    Size viewPort(200.0, 200.0);
    auto path = circle->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

/**
 * @tc.name: SvgTransform005
 * @tc.desc: test combined transforms
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgTransform005, TestSize.Level1)
{
    auto rect = SvgRect::Create();
    EXPECT_NE(rect, nullptr);
    rect->SetAttr("transform", "translate(10,10) rotate(45) scale(1.5)");
    Size viewPort(200.0, 200.0);
    auto path = rect->AsPath(viewPort);
    EXPECT_TRUE(path.IsValid());
}

// ========== SVG Animation Tests (001-005) ==========

/**
 * @tc.name: SvgAnimation001
 * @tc.desc: test SvgAnimation creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAnimation001, TestSize.Level1)
{
    auto animation = SvgAnimation::Create();
    EXPECT_NE(animation, nullptr);
}

/**
 * @tc.name: SvgAnimation002
 * @tc.desc: test animateTransform creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAnimation002, TestSize.Level1)
{
    auto animateTransform = SvgAnimation::CreateAnimateTransform();
    EXPECT_NE(animateTransform, nullptr);
}

/**
 * @tc.name: SvgAnimation003
 * @tc.desc: test animateMotion creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAnimation003, TestSize.Level1)
{
    auto animateMotion = SvgAnimation::CreateAnimateMotion();
    EXPECT_NE(animateMotion, nullptr);
}

/**
 * @tc.name: SvgAnimation004
 * @tc.desc: test animation parsing with SVG content
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAnimation004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ANIMATION_SVG.c_str(), ANIMATION_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
}

/**
 * @tc.name: SvgAnimation005
 * @tc.desc: test animation attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAnimation005, TestSize.Level1)
{
    auto animation = SvgAnimation::Create();
    EXPECT_NE(animation, nullptr);
    animation->SetAttr("attributeName", "r");
    animation->SetAttr("from", "50");
    animation->SetAttr("to", "80");
    animation->SetAttr("dur", "2s");
    animation->SetAttr("repeatCount", "indefinite");
}

// ========== SVG FeBlend Tests (001-003) ==========

/**
 * @tc.name: SvgFeBlend001
 * @tc.desc: test SvgFeBlend creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeBlend001, TestSize.Level1)
{
    auto feBlend = SvgFeBlend::Create();
    EXPECT_NE(feBlend, nullptr);
}

/**
 * @tc.name: SvgFeBlend002
 * @tc.desc: test SvgFeBlend attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeBlend002, TestSize.Level1)
{
    auto feBlend = SvgFeBlend::Create();
    EXPECT_NE(feBlend, nullptr);
    feBlend->SetAttr("in", "SourceGraphic");
    feBlend->SetAttr("in2", "BackgroundImage");
    feBlend->SetAttr("mode", "multiply");
    auto feBlendNode = AceType::DynamicCast<SvgFeBlend>(feBlend);
    ASSERT_NE(feBlendNode, nullptr);
    auto multiplyMode = feBlendNode->GetBlendMode(SvgFeBlendMode::MULTIPLY);
    EXPECT_NE(multiplyMode, RSBlendMode::SRC_OVER);
}

/**
 * @tc.name: SvgFeBlend003
 * @tc.desc: test blend mode conversion
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeBlend003, TestSize.Level1)
{
    auto feBlend = SvgFeBlend::Create();
    EXPECT_NE(feBlend, nullptr);
    auto feBlendNode = AceType::DynamicCast<SvgFeBlend>(feBlend);
    ASSERT_NE(feBlendNode, nullptr);
    auto normalMode = feBlendNode->GetBlendMode(SvgFeBlendMode::NORMAL);
    EXPECT_EQ(normalMode, RSBlendMode::SRC_OVER);

    auto multiplyMode = feBlendNode->GetBlendMode(SvgFeBlendMode::MULTIPLY);
    EXPECT_NE(multiplyMode, RSBlendMode::SRC_OVER);
}

// ========== SVG FeFlood Tests (001-002) ==========

/**
 * @tc.name: SvgFeFlood001
 * @tc.desc: test SvgFeFlood creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeFlood001, TestSize.Level1)
{
    auto feFlood = SvgFeFlood::Create();
    EXPECT_NE(feFlood, nullptr);
}

/**
 * @tc.name: SvgFeFlood002
 * @tc.desc: test SvgFeFlood attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeFlood002, TestSize.Level1)
{
    auto feFlood = SvgFeFlood::Create();
    EXPECT_NE(feFlood, nullptr);
    auto result1 = feFlood->ParseAndSetSpecializedAttr("flood-color", "red");
    EXPECT_TRUE(result1);
    auto result2 = feFlood->ParseAndSetSpecializedAttr("flood-opacity", "0.5");
    EXPECT_TRUE(result2);
}

// ========== SVG FeGaussianBlur Tests (001-003) ==========

/**
 * @tc.name: SvgFeGaussianBlur001
 * @tc.desc: test SvgFeGaussianBlur creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeGaussianBlur001, TestSize.Level1)
{
    auto feGaussianBlur = SvgFeGaussianBlur::Create();
    EXPECT_NE(feGaussianBlur, nullptr);
}

/**
 * @tc.name: SvgFeGaussianBlur002
 * @tc.desc: test SvgFeGaussianBlur attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeGaussianBlur002, TestSize.Level1)
{
    auto feGaussianBlur = SvgFeGaussianBlur::Create();
    EXPECT_NE(feGaussianBlur, nullptr);
    auto result1 = feGaussianBlur->ParseAndSetSpecializedAttr("stdDeviation", "5");
    EXPECT_TRUE(result1);
    auto result2 = feGaussianBlur->ParseAndSetSpecializedAttr("edgeMode", "duplicate");
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: SvgFeGaussianBlur003
 * @tc.desc: test SvgFeGaussianBlur with separate x/y deviation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeGaussianBlur003, TestSize.Level1)
{
    auto feGaussianBlur = SvgFeGaussianBlur::Create();
    EXPECT_NE(feGaussianBlur, nullptr);
    auto result = feGaussianBlur->ParseAndSetSpecializedAttr("stdDeviation", "3,5");
    EXPECT_TRUE(result);
}

// ========== SVG FeComposite Tests (001-003) ==========

/**
 * @tc.name: SvgFeComposite001
 * @tc.desc: test SvgFeComposite creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeComposite001, TestSize.Level1)
{
    auto feComposite = SvgFeComposite::Create();
    EXPECT_NE(feComposite, nullptr);
}

/**
 * @tc.name: SvgFeComposite002
 * @tc.desc: test SvgFeComposite attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeComposite002, TestSize.Level1)
{
    auto feComposite = SvgFeComposite::Create();
    EXPECT_NE(feComposite, nullptr);
    auto result1 = feComposite->ParseAndSetSpecializedAttr("in", "SourceGraphic");
    EXPECT_TRUE(result1);
    auto result2 = feComposite->ParseAndSetSpecializedAttr("in2", "BackgroundImage");
    EXPECT_TRUE(result2);
    auto result3 = feComposite->ParseAndSetSpecializedAttr("operator", "arithmetic");
    EXPECT_TRUE(result3);
    auto result4 = feComposite->ParseAndSetSpecializedAttr("k1", "0.5");
    EXPECT_TRUE(result4);
    auto result5 = feComposite->ParseAndSetSpecializedAttr("k2", "0.5");
    EXPECT_TRUE(result5);
    auto result6 = feComposite->ParseAndSetSpecializedAttr("k3", "0.5");
    EXPECT_TRUE(result6);
    auto result7 = feComposite->ParseAndSetSpecializedAttr("k4", "0");
    EXPECT_TRUE(result7);
}

/**
 * @tc.name: SvgFeComposite003
 * @tc.desc: test composite operator types
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeComposite003, TestSize.Level1)
{
    auto feComposite = SvgFeComposite::Create();
    EXPECT_NE(feComposite, nullptr);
    feComposite->SetAttr("operator", "over");
    auto feCompositeNode = AceType::DynamicCast<SvgFeComposite>(feComposite);
    ASSERT_NE(feCompositeNode, nullptr);
    auto mode = feCompositeNode->BlendModeForOperator(SvgFeOperatorType::FE_OVER);
    EXPECT_EQ(mode, RSBlendMode::SRC_OVER);
}

// ========== SVG FeColorMatrix Tests (001-004) ==========

/**
 * @tc.name: SvgFeColorMatrix001
 * @tc.desc: test SvgFeColorMatrix creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeColorMatrix001, TestSize.Level1)
{
    auto feColorMatrix = SvgFeColorMatrix::Create();
    EXPECT_NE(feColorMatrix, nullptr);
}

/**
 * @tc.name: SvgFeColorMatrix002
 * @tc.desc: test SvgFeColorMatrix attribute parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeColorMatrix002, TestSize.Level1)
{
    auto feColorMatrix = SvgFeColorMatrix::Create();
    EXPECT_NE(feColorMatrix, nullptr);
    auto result1 = feColorMatrix->ParseAndSetSpecializedAttr("type", "matrix");
    EXPECT_TRUE(result1);
    auto result2 = feColorMatrix->ParseAndSetSpecializedAttr("values",
        "1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 1 0");
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: SvgFeColorMatrix003
 * @tc.desc: test SvgFeColorMatrix saturate type
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeColorMatrix003, TestSize.Level1)
{
    auto feColorMatrix = SvgFeColorMatrix::Create();
    EXPECT_NE(feColorMatrix, nullptr);
    auto result1 = feColorMatrix->ParseAndSetSpecializedAttr("type", "saturate");
    EXPECT_TRUE(result1);
    auto result2 = feColorMatrix->ParseAndSetSpecializedAttr("values", "0.5");
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: SvgFeColorMatrix004
 * @tc.desc: test SvgFeColorMatrix hueRotate type
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgFeColorMatrix004, TestSize.Level1)
{
    auto feColorMatrix = SvgFeColorMatrix::Create();
    EXPECT_NE(feColorMatrix, nullptr);
    auto result1 = feColorMatrix->ParseAndSetSpecializedAttr("type", "hueRotate");
    EXPECT_TRUE(result1);
    auto result2 = feColorMatrix->ParseAndSetSpecializedAttr("values", "90");
    EXPECT_TRUE(result2);
}

// ========== SVG AttributesParser Tests (001-010) ==========

/**
 * @tc.name: SvgAttributesParser001
 * @tc.desc: test color parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser001, TestSize.Level1)
{
    auto color = SvgAttributesParser::GetColor("red");
    EXPECT_TRUE(color.GetValue() != Color::TRANSPARENT.GetValue());

    color = SvgAttributesParser::GetColor("#FF0000");
    EXPECT_TRUE(color.GetValue() != Color::TRANSPARENT.GetValue());

    color = SvgAttributesParser::GetColor("rgb(255,0,0)");
    EXPECT_TRUE(color.GetValue() != Color::TRANSPARENT.GetValue());
}

/**
 * @tc.name: SvgAttributesParser002
 * @tc.desc: test line cap style parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser002, TestSize.Level1)
{
    auto capStyle = SvgAttributesParser::GetLineCapStyle("butt");
    EXPECT_EQ(capStyle, LineCapStyle::BUTT);

    capStyle = SvgAttributesParser::GetLineCapStyle("round");
    EXPECT_EQ(capStyle, LineCapStyle::ROUND);

    capStyle = SvgAttributesParser::GetLineCapStyle("square");
    EXPECT_EQ(capStyle, LineCapStyle::SQUARE);
}

/**
 * @tc.name: SvgAttributesParser003
 * @tc.desc: test line join style parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser003, TestSize.Level1)
{
    auto joinStyle = SvgAttributesParser::GetLineJoinStyle("miter");
    EXPECT_EQ(joinStyle, LineJoinStyle::MITER);

    joinStyle = SvgAttributesParser::GetLineJoinStyle("round");
    EXPECT_EQ(joinStyle, LineJoinStyle::ROUND);

    joinStyle = SvgAttributesParser::GetLineJoinStyle("bevel");
    EXPECT_EQ(joinStyle, LineJoinStyle::BEVEL);
}

/**
 * @tc.name: SvgAttributesParser004
 * @tc.desc: test dimension parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser004, TestSize.Level1)
{
    auto dimension = SvgAttributesParser::ParseDimension("100");
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);

    dimension = SvgAttributesParser::ParseDimension("50%");
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PERCENT);

    dimension = SvgAttributesParser::ParseDimension("10px");
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: SvgAttributesParser005
 * @tc.desc: test transform parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser005, TestSize.Level1)
{
    auto transformInfo = SvgAttributesParser::GetTransformInfo("translate(10,20)");
    EXPECT_EQ(transformInfo.size(), 1);
    EXPECT_EQ(transformInfo[0].funcType, "translate");

    transformInfo = SvgAttributesParser::GetTransformInfo("rotate(45)");
    EXPECT_EQ(transformInfo.size(), 1);
    EXPECT_EQ(transformInfo[0].funcType, "rotate");

    transformInfo = SvgAttributesParser::GetTransformInfo("scale(2)");
    EXPECT_EQ(transformInfo.size(), 1);
    EXPECT_EQ(transformInfo[0].funcType, "scale");
}

/**
 * @tc.name: SvgAttributesParser006
 * @tc.desc: test SVG align parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser006, TestSize.Level1)
{
    auto align = SvgAttributesParser::ParseSvgAlign("xMinYMin");
    EXPECT_EQ(align, SvgAlign::ALIGN_XMIN_YMIN);

    align = SvgAttributesParser::ParseSvgAlign("xMidYMid");
    EXPECT_EQ(align, SvgAlign::ALIGN_XMID_YMID);

    align = SvgAttributesParser::ParseSvgAlign("xMaxYMax");
    EXPECT_EQ(align, SvgAlign::ALIGN_XMAX_YMAX);

    align = SvgAttributesParser::ParseSvgAlign("none");
    EXPECT_EQ(align, SvgAlign::ALIGN_NONE);
}

/**
 * @tc.name: SvgAttributesParser007
 * @tc.desc: test meet or slice parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser007, TestSize.Level1)
{
    auto meetOrSlice = SvgAttributesParser::ParseSvgMeetOrSlice("meet");
    EXPECT_EQ(meetOrSlice, SvgMeetOrSlice::MEET);

    meetOrSlice = SvgAttributesParser::ParseSvgMeetOrSlice("slice");
    EXPECT_EQ(meetOrSlice, SvgMeetOrSlice::SLICE);
}

/**
 * @tc.name: SvgAttributesParser008
 * @tc.desc: test double parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser008, TestSize.Level1)
{
    auto value = SvgAttributesParser::ParseDouble("123.45");
    EXPECT_DOUBLE_EQ(value, 123.45);

    value = SvgAttributesParser::ParseDouble("-50");
    EXPECT_DOUBLE_EQ(value, -50.0);

    value = SvgAttributesParser::ParseDouble("0.5");
    EXPECT_DOUBLE_EQ(value, 0.5);
}

/**
 * @tc.name: SvgAttributesParser009
 * @tc.desc: test transform origin parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser009, TestSize.Level1)
{
    auto origin = SvgAttributesParser::GetTransformOrigin("center center");
    EXPECT_EQ(origin.first.Unit(), DimensionUnit::PX);
    EXPECT_EQ(origin.second.Unit(), DimensionUnit::PX);

    origin = SvgAttributesParser::GetTransformOrigin("50% 50%");
    EXPECT_EQ(origin.first.Unit(), DimensionUnit::PERCENT);
    EXPECT_EQ(origin.second.Unit(), DimensionUnit::PERCENT);
}

/**
 * @tc.name: SvgAttributesParser010
 * @tc.desc: test hex color parsing
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgAttributesParser010, TestSize.Level1)
{
    auto color = SvgAttributesParser::GetColorFromHexString("#FF0000");
    EXPECT_TRUE(color.GetValue() != Color::TRANSPARENT.GetValue());

    color = SvgAttributesParser::GetColorFrom4HexString("#F00");
    EXPECT_TRUE(color.GetValue() != Color::TRANSPARENT.GetValue());
}

// ========== Complex SVG Tests (001-002) ==========

/**
 * @tc.name: ComplexSvg001
 * @tc.desc: test complex SVG with multiple features
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, ComplexSvg001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(COMPLEX_SVG.c_str(), COMPLEX_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(svg->children_.size(), 0);
}

/**
 * @tc.name: ComplexSvg002
 * @tc.desc: test SVG dump info
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, ComplexSvg002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(COMPLEX_SVG.c_str(), COMPLEX_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto dumpInfo = svgDom->GetDumpInfo();
    EXPECT_FALSE(dumpInfo.empty());
}

// ========== SvgDom Tests (001-008) ==========

/**
 * @tc.name: SvgDom001
 * @tc.desc: test SvgDom IsStatic method
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    EXPECT_TRUE(svgDom->IsStatic());
}

/**
 * @tc.name: SvgDom002
 * @tc.desc: test SvgDom animation control
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ANIMATION_SVG.c_str(), ANIMATION_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    svgDom->ControlAnimation(true);
    svgDom->ControlAnimation(false);
}

/**
 * @tc.name: SvgDom003
 * @tc.desc: test SvgDom fill color setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    svgDom->SetFillColor(Color::RED);
    svgDom->SetFillColor(std::nullopt);
}

/**
 * @tc.name: SvgDom004
 * @tc.desc: test SvgDom smooth edge setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    svgDom->SetSmoothEdge(1.0f);
}

/**
 * @tc.name: SvgDom005
 * @tc.desc: test SvgDom color filter setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom005, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    ImageColorFilter colorFilter;
    svgDom->SetColorFilter(colorFilter);
    svgDom->SetColorFilter(std::nullopt);
}

/**
 * @tc.name: SvgDom006
 * @tc.desc: test SvgDom container size
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom006, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto containerSize = svgDom->GetContainerSize();
    EXPECT_GE(containerSize.Width(), 0.0f);
    EXPECT_GE(containerSize.Height(), 0.0f);
}

/**
 * @tc.name: SvgDom007
 * @tc.desc: test SvgDom draw image with different fit modes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom007, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    RSCanvas canvas;
    Size layout(200.0, 200.0);

    svgDom->DrawImage(canvas, ImageFit::FILL, layout);
    svgDom->DrawImage(canvas, ImageFit::CONTAIN, layout);
    svgDom->DrawImage(canvas, ImageFit::COVER, layout);
    svgDom->DrawImage(canvas, ImageFit::FITWIDTH, layout);
    svgDom->DrawImage(canvas, ImageFit::FITHEIGHT, layout);
    svgDom->DrawImage(canvas, ImageFit::NONE, layout);
}

/**
 * @tc.name: SvgDom008
 * @tc.desc: test SvgDom animation callback
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDom008, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ANIMATION_SVG.c_str(), ANIMATION_SVG.length());
    ImageSourceInfo src;
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    bool callbackCalled = false;
    svgDom->SetAnimationOnFinishCallback([&callbackCalled]() { callbackCalled = true; });
}

// ========== SvgNode Tests (001-010) ==========

/**
 * @tc.name: SvgNode001
 * @tc.desc: test SvgNode id setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode001, TestSize.Level1)
{
    auto circle = SvgCircle::Create();
    EXPECT_NE(circle, nullptr);
    circle->SetNodeId("myCircle");
}

/**
 * @tc.name: SvgNode002
 * @tc.desc: test SvgNode smooth edge setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode002, TestSize.Level1)
{
    auto circle = SvgCircle::Create();
    EXPECT_NE(circle, nullptr);
    circle->SetSmoothEdge(1.5f);
    EXPECT_EQ(circle->GetSmoothEdge(), 1.5f);
}

/**
 * @tc.name: SvgNode003
 * @tc.desc: test SvgNode color filter
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode003, TestSize.Level1)
{
    auto rect = SvgRect::Create();
    EXPECT_NE(rect, nullptr);
    ImageColorFilter filter;
    rect->SetColorFilter(filter);
    auto result = rect->GetColorFilter();
    EXPECT_TRUE(result.has_value());
}

/**
 * @tc.name: SvgNode004
 * @tc.desc: test SvgNode effect filter area
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode004, TestSize.Level1)
{
    auto circle = SvgCircle::Create();
    EXPECT_NE(circle, nullptr);
    Rect filterArea(10.0, 10.0, 100.0, 100.0);
    circle->SetEffectFilterArea(filterArea);
    auto result = circle->GetEffectFilterArea();
    EXPECT_EQ(result.Left(), 10.0);
}

/**
 * @tc.name: SvgNode005
 * @tc.desc: test SvgNode image path setting
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode005, TestSize.Level1)
{
    auto path = SvgPath::Create();
    EXPECT_NE(path, nullptr);
    path->SetImagePath("/path/to/image.svg");
    auto result = path->GetImagePath();
    EXPECT_EQ(result, "/path/to/image.svg");
}

/**
 * @tc.name: SvgNode006
 * @tc.desc: test SvgNode base attributes
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode006, TestSize.Level1)
{
    auto ellipse = SvgEllipse::Create();
    EXPECT_NE(ellipse, nullptr);
    SvgBaseAttribute attr;
    attr.fillState.SetColor(Color::RED);
    ellipse->SetBaseAttributes(attr);
    auto result = ellipse->GetBaseAttributes();
    EXPECT_TRUE(result.fillState.HasColor());
}

/**
 * @tc.name: SvgNode007
 * @tc.desc: test SvgNode attributes inheritance
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode007, TestSize.Level1)
{
    auto parent = SvgG::Create();
    EXPECT_NE(parent, nullptr);
    SvgBaseAttribute parentAttr;
    parentAttr.fillState.SetColor(Color::BLUE);
    parent->SetBaseAttributes(parentAttr);

    auto child = SvgCircle::Create();
    EXPECT_NE(child, nullptr);
    child->InheritAttr(parentAttr);
}

/**
 * @tc.name: SvgNode008
 * @tc.desc: test SvgNode root node flag
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode008, TestSize.Level1)
{
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
    svg->SetIsRootNode(true);
}

/**
 * @tc.name: SvgNode009
 * @tc.desc: test SvgNode AsBounds
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode009, TestSize.Level1)
{
    auto circle = SvgCircle::Create();
    EXPECT_NE(circle, nullptr);
    circle->SetAttr("cx", "100");
    circle->SetAttr("cy", "100");
    circle->SetAttr("r", "50");
    Size viewPort(200.0, 200.0);
    auto bounds = circle->AsBounds(viewPort);
    EXPECT_GE(bounds.Width(), 0.0);
    EXPECT_GE(bounds.Height(), 0.0);
}

/**
 * @tc.name: SvgNode010
 * @tc.desc: test SvgNode AsRSPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgNode010, TestSize.Level1)
{
    auto rect = SvgRect::Create();
    EXPECT_NE(rect, nullptr);
    rect->SetAttr("x", "10");
    rect->SetAttr("y", "10");
    rect->SetAttr("width", "100");
    rect->SetAttr("height", "50");
    Size viewPort(200.0, 200.0);
    auto rsPath = rect->AsRSPath(viewPort);
    EXPECT_TRUE(rsPath.IsValid());
}

// ========== SvgSvg Tests (001-004) ==========

/**
 * @tc.name: SvgSvg001
 * @tc.desc: test SvgSvg creation
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgSvg001, TestSize.Level1)
{
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
}

/**
 * @tc.name: SvgSvg002
 * @tc.desc: test SvgSvg GetSize
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgSvg002, TestSize.Level1)
{
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
    svg->SetAttr("width", "200");
    svg->SetAttr("height", "100");
    auto svgNode = AceType::DynamicCast<SvgSvg>(svg);
    ASSERT_NE(svgNode, nullptr);
    auto size = svgNode->GetSize();
    EXPECT_GT(size.Width(), 0.0);
    EXPECT_GT(size.Height(), 0.0);
}

/**
 * @tc.name: SvgSvg003
 * @tc.desc: test SvgSvg GetViewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgSvg003, TestSize.Level1)
{
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
    svg->SetAttr("viewBox", "0 0 100 100");
    auto svgNode = AceType::DynamicCast<SvgSvg>(svg);
    ASSERT_NE(svgNode, nullptr);
    auto viewBox = svgNode->GetViewBox();
    EXPECT_EQ(viewBox.Left(), 0.0);
    EXPECT_EQ(viewBox.Top(), 0.0);
}

/**
 * @tc.name: SvgSvg004
 * @tc.desc: test SvgSvg preserve aspect ratio
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgSvg004, TestSize.Level1)
{
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
    svg->SetAttr("preserveAspectRatio", "xMidYMid meet");
    auto svgNode = AceType::DynamicCast<SvgSvg>(svg);
    ASSERT_NE(svgNode, nullptr);
    auto aspectRatio = svgNode->GetPreserveAspectRatio();
    EXPECT_EQ(aspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(aspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);
}

// ========== ImageSourceInfo Tests (001) ==========

/**
 * @tc.name: ImageSourceInfo001
 * @tc.desc: test ImageSourceInfo with SVG
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, ImageSourceInfo001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG.c_str(), CIRCLE_SVG.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLUE);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
}
} // namespace OHOS::Ace::NG

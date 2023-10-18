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

#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_animate_declaration.h"
#include "core/components/declaration/svg/svg_circle_declaration.h"
#include "core/components/declaration/svg/svg_declaration.h"
#include "core/components/declaration/svg/svg_ellipse_declaration.h"
#include "core/components/declaration/svg/svg_fe_colormatrix_declaration.h"
#include "core/components/declaration/svg/svg_fe_composite_declaration.h"
#include "core/components/declaration/svg/svg_fe_gaussianblur_declaration.h"
#include "core/components/declaration/svg/svg_filter_declaration.h"
#include "core/components/declaration/svg/svg_gradient_declaration.h"
#include "core/components/declaration/svg/svg_line_declaration.h"
#include "core/components/declaration/svg/svg_mask_declaration.h"
#include "core/components/declaration/svg/svg_path_declaration.h"
#include "core/components/declaration/svg/svg_pattern_declaration.h"
#include "core/components/declaration/svg/svg_polygon_declaration.h"
#include "core/components/declaration/svg/svg_rect_declaration.h"
#include "core/components/declaration/svg/svg_stop_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_ellipse.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
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
const std::string CIRCLE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><circle cx=\"60px\" "
    "cy=\"200px\" r = \"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" stroke-width=\"16px\" "
    "stroke-opacity=\"0.3\" id=\"circleId\"/></svg>";
constexpr float Cx = 60.0f;
constexpr float Cy = 200.0f;
constexpr float R = 50.0f;
const std::string CLIP_SVG_LABEL =
    "<svg width=\"120\" height=\"120\" viewBox=\"0 0 120 120\" version=\"1.1\"><defs><clipPath id=\"myClip\"><circle "
    "cx=\"30\" cy=\"30\" r=\"20\"/><circle cx=\"70\" cy=\"70\" r=\"30\"/></clipPath></defs><rect x=\"10\" y=\"10\" "
    "width=\"100\" height=\"100\" clip-path=\"url(#myClip)\" fill=\"red\" /></svg>";
const std::string ID = "myClip";
const std::string SVG_LABEL = "<svg width=\"400\" height=\"500\" viewBox=\"-4 -10 300 300\"></svg>";
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 500.0f;
constexpr float VIEWBOX_X = -4.0f;
constexpr float VIEWBOX_Y = -10.0f;
constexpr float VIEWBOX_WIDTH = 300.0f;
constexpr float VIEWBOX_HEIGHT = 300.0f;
const std::string USE_SVG_LABEL =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"24\" height=\"24\" "
    "version=\"1.1\" viewBox=\"0 0 24 24\"><defs><path id=\"uxs-a\" d=\"M11.5,13.5 C12.7426407,13.5 13.75,14.5073593 "
    "13.75,15.75 C13.75,16.9926407 12.7426407,18 11.5,18 C10.2573593,18 9.25,16.9926407 9.25,15.75 C9.25,14.5073593 "
    "10.2573593,13.5 11.5,13.5 Z M11.5006868,9 C13.6153489,9 15.5906493,9.84916677 16.9758057,11.3106505 "
    "C17.3557222,11.7115019 17.3387512,12.3444394 16.9378998,12.724356 C16.5370484,13.1042725 15.9041109,13.0873015 "
    "15.5241943,12.6864501 C14.5167672,11.62351 13.0663814,11 11.5006868,11 C9.93437756,11 8.48347933,11.6240033 "
    "7.47603048,12.6876625 C7.09624495,13.0886381 6.46331303,13.105816 6.06233747,12.7260305 C5.66136192,12.3462449 "
    "5.644184,11.713313 6.02396952,11.3123375 C7.40917586,9.84984392 9.38518621,9 11.5006868,9 Z M11.5002692,4.5 "
    "C14.7685386,4.5 17.818619,5.90678629 19.9943022,8.33155689 C20.3631417,8.74262367 20.3289097,9.37486259 "
    "19.9178429,9.74370206 C19.5067762,10.1125415 18.8745372,10.0783095 18.5056978,9.66724276 C16.703513,7.6587313 "
    "14.1912454,6.5 11.5002692,6.5 C8.80904291,6.5 6.29656204,7.6589485 4.49435171,9.66778779 C4.1255427,10.0788819 "
    "3.49330631,10.1131607 3.08221221,9.74435171 C2.67111811,9.3755427 2.63683928,8.74330631 3.00564829,8.33221221 "
    "C5.1813597,5.90704879 8.23169642,4.5 11.5002692,4.5 Z M11.4995363,-5.68434189e-14 C15.8001105,-5.68434189e-14 "
    "19.8214916,1.76017363 22.7244081,4.81062864 C23.1051374,5.21070819 23.0894509,5.84367883 22.6893714,6.22440812 "
    "C22.2892918,6.60513741 21.6563212,6.58945092 21.2755919,6.18937136 C18.7465254,3.53176711 15.2469734,2 "
    "11.4995363,2 C7.75253773,2 4.25335915,3.53140612 1.72434435,6.1884639 C1.34357805,6.58850824 "
    "0.71060597,6.60413618 0.310561632,6.22336988 C-0.0894827058,5.84260359 -0.105110646,5.2096315 "
    "0.27565565,4.80958716 C3.1785132,1.75975912 7.19946582,-5.68434189e-14 11.4995363,-5.68434189e-14 "
    "Z\"/></defs><use fill=\"red\" fill-rule=\"nonzero\" stroke=\"blue\" stroke-width=\"1\" "
    "transform=\"translate(.5 2.75)\" xlink:href=\"#uxs-a\"/></svg>";
const std::string HREF = "uxs-a";
const std::string FILL_RULE = "nonzero";
const std::string TRANSFORM = "translate(.5 2.75)";
constexpr float STROKE_WIDTH = 1;
constexpr int32_t INDEX_ONE = 1;
constexpr int32_t STROKE = 0xff0000ff;
const std::string STYLE_SVG_LABEL = "<svg viewBox=\"0 0 10 10\"><style>circle{fill:gold;stroke:maroon;stroke-width : "
                                    "2px;}</style><circle cx =\"5\" cy=\"5\" r=\"4\" /></svg>";
const std::string STOP_SVG_LABEL =
    "<svg height=\"150\" width=\"400\"><defs><linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" "
    "y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" /><stop offset=\"20px\" "
    "style=\"stop-color:rgb(255,0,0);stop-opacity:1\" /></linearGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
constexpr int32_t INDEX_ZEARO = 0;
constexpr int32_t CHILD_NUMBER = 2;
constexpr float STOP_OPACITY = 1.0f;
const std::string RECT_SVG_LABEL = "<svg width=\"400\" height=\"400\" version=\"1.1\" fill=\"red\" "
                                   "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                   "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"10\" ry=\"10\"></rect></svg>";
const std::string RECT_SVG_LABEL2 = "<svg version=\"1.1\" fill=\"red\" "
                                    "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                    "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"10\" ry=\"10\"></rect></svg>";
constexpr float X = 150.0f;
constexpr float Y = 20.0f;
constexpr float RX = 10.0f;
constexpr float RY = 10.0f;
constexpr float RECT_WIDTH = 100.0f;
constexpr float RECT_HEIGHT = 100.0f;
const std::string POLYGON_SVG_LABEL1 =
    "<svg fill=\"white\" stroke=\"blue\" width=\"800\" height=\"400\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><polygon points=\"10,110 60,35 60,85 110,10\" "
    "fill=\"red\"></polygon> <polyline points=\"10,200 60,125 60,175 110,100\" "
    "stroke-dasharray=\"10 5\" stroke-dashoffset=\"3\"></polyline></svg>";
const std::string POLYGON_SVG_LABEL2 =
    "<svg fill=\"white\" stroke=\"blue\" width=\"300\" height=\"400\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><polygon points=\"10,110 60,35 60,85 110,10\" "
    "fill=\"red\"></polygon> <polyline points=\"10,200 60,125 60,175 110,100\" "
    "stroke-dasharray=\"10 5\" stroke-dashoffset=\"3\"></polyline></svg>";
const std::string POLYGON_POINT = "10,110 60,35 60,85 110,10";
const std::string POLYLINE_POINT = "10,200 60,125 60,175 110,100";
const std::string PATTERN_SVG_LABEL =
    "<svg viewBox=\"0 0 230 100\"><defs><pattern id=\"star\" viewBox=\"0 0 10 10\" width=\"10\" "
    "height=\"10\"><polygon points=\"0,0 2,5 0,10 5,8 10,10 8,5 10,0 5,2\" /></pattern></defs><circle cx=\"50\" "
    "cy=\"50\" r=\"50\" fill=\"url(#star)\" /><circle cx=\"180\" cy=\"50\" r=\"40\"  fill=\"none\" stroke-width=\"20\" "
    "stroke=\"url(#star)\"/> </svg>";
constexpr float PATTERN_WIDTH = 10.0f;
constexpr float PATTERN_HEIGHT = 10.0f;
constexpr float PATTERN_VIEWBOX_X = 0.0f;
constexpr float PATTERN_VIEWBOX_Y = 0.0f;
constexpr float PATTERN_VIEWBOX_WIDTH = 10.0f;
constexpr float PATTERN_VIEWBOX_HEIGHT = 10.0f;
const std::string PATH_SVG_LABEL1 =
    "<svg width=\"400\" height=\"800\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_SVG_LABEL2 =
    "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_SVG_LABEL3 =
    "<svg width=\"-400\" height=\"-400\" viewBox=\"-4 -10 300 300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_SVG_LABEL4 =
    "<svg width=\"300\" height=\"400\" viewBox=\"-4 -10 300 300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_SVG_LABEL5 =
    "<svg width=\"400\" height=\"400\" viewBox=\"-4 -10 -300 -300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_CMD = "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z";
const std::string MASK_SVG_LABEL =
    "<svg width=\"50px\" height=\"50px\" viewBox=\"0 0 24 24\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" "
    "xmlns:xlink=\"http://www.w3.org/1999/xlink\"><defs><path d=\"M4.3,14l-2,1.8c-0.2,0.2 -0.5,0.2 -0.7,0c-0.1,-0.1 "
    "-0.1,-0.2 -0.1,-0.3V8.6c0,-0.3 0.2,-0.5 0.5,-0.5c0.1,0 0.2,0 0.3,0.1l2,1.8l0,0H10L7,3.5C6.7,2.9 6.9,2.3 "
    "7.5,2c0.6,-0.3 1.3,-0.1 1.7,0.4l6,7.6l0,0H21c1.1,0 2,0.9 2,2s-0.9,2 -2,2h-6l0,0l-5.8,7.6c-0.4,0.5 -1.1,0.7 "
    "-1.7,0.4c-0.6,-0.3 -0.8,-0.9 -0.5,-1.5l3,-6.5l0,0H4.3z\" id=\"path-1\"></path></defs><g stroke=\"none\" "
    "stroke-width=\"1\" fill=\"none\" fill-rule=\"evenodd\"><g><mask id=\"mask-2\" fill=\"#FFFFFF\"><use "
    "xlink:href=\"#path-1\"></use></mask><use id=\"myId\" fill=\"#FFFFFF\" fill-rule=\"nonzero\" "
    "xlink:href=\"#path-1\"></use></g></g></svg>";
const std::string MASK_ID = "mask-2";
const std::string LINE_SVG_LABEL =
    "<svg width=\"400\" height=\"400\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><line x1=\"10\" x2=\"300\" "
    "y1=\"50\" y2=\"50\" stroke-width=\"4\" fill=\"white\" stroke=\"blue\"></line></svg>";
constexpr float X1 = 10.0f;
constexpr float Y1 = 50.0f;
constexpr float X2 = 300.0f;
constexpr float Y2 = 50.0f;
const std::string GRADIENT_SVG_LINEAR =
    "<svg height=\"150\" width=\"400\"><defs><linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" "
    "y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" /><stop offset=\"100%\" "
    "style=\"stop-color:rgb(255,0,0);stop-opacity:1\" /></linearGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
const std::string GRADIENT_SVG_RADIAL =
    "<svg height=\"150\" width=\"500\"><defs><radialGradient id=\"grad1\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" "
    "fy=\"50%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,255);      stop-opacity:0\" /><stop offset=\"100%\" "
    "style=\"stop-color:rgb(0,0,255);stop-opacity:1\" /></radialGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
constexpr float ZERO = 0.0f;
const std::string G_SVG_LABEL = "<svg width=\"400\" height=\"500\"> <g id=\"myId\"> </g></svg>";
const std::string G_ID = "myId";
const std::string FILTER_SVG_LABEL =
    "<svg height=\"900\" width=\"900\"><filter id=\"composite\" y=\"0\" x=\"0\" width=\"900\" "
    "height=\"900\"><feTurbulence baseFrequency=\".05\" numOctaves=\"3\" result=\"B\"/><feComposite in2=\"B\" "
    "in=\"SourceGraphic\" operator=\"in\" /></filter><ellipse cx=\"100\" cy=\"87\" rx=\"75\" ry=\"87\" fill=\"red\" "
    "filter=\"url(#composite)\"/></svg>";
const std::string FILTER_ID = "composite";
constexpr float FILTER_WIDTH = 900.0f;
constexpr float FILTER_HEIGHT = 900.0f;
const std::string FEGAUSS_SVG_LABEL =
    "<svg width=\"230\" height=\"120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
const std::string FEGAUSS_SVG_LABEL2 =
    "<svg width=\"-230\" height=\"-120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
constexpr float STD_DEVIATION = 5.0f;
const std::string COMPOSITE_SVG_LABEL =
    "<svg height=\"900\" width=\"900\"><filter id=\"composite\" y=\"0\" x=\"0\" width=\"100%\" "
    "height=\"100%\"><feComposite in2=\"B\" "
    "in=\"SourceGraphic\" operator=\"in\" /></filter><ellipse cx=\"100\" cy=\"87\" rx=\"75\" ry=\"87\" fill=\"red\" "
    "filter=\"url(#composite)\"/></svg>";
const std::string COLOR_MATRIX_SVG_LABEL =
    "<svg height=\"900\" width=\"900\"><filter id=\"linear\"><feColorMatrix type=\"matrix\" "
    "values=\"R 0 0 0 0 0 G 0 0 0 0 0 B 0 0 0 0 0 A 0\"></feColorMatrix ></filter><ellipse cx=\"100\" cy=\"87\" "
    "rx=\"75\" ry=\"87\" fill=\"red\" filter=\"url(#linear)\"></ellipse></svg>";
const std::string TYPE = "matrix";
const std::string VALUE = "R 0 0 0 0 0 G 0 0 0 0 0 B 0 0 0 0 0 A 0";
const std::string ELLIPSE_SVG_LABEL1 =
    "<svg fill=\"white\" width=\"400\" height=\"400\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"60\" cy=\"200\" rx=\"50\" ry=\"100\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
const std::string ELLIPSE_SVG_LABEL2 =
    "<svg fill=\"white\" width=\"10\" height=\"10\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"60\" cy=\"200\" rx=\"50\" ry=\"100\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
constexpr float ELLIPSE_Cx = 60.0f;
constexpr float ELLIPSE_Cy = 200.0f;
constexpr float ELLIPSE_RX = 50.0f;
constexpr float ELLIPSE_RY = 100.0f;
const std::string SVG_ANIMATE_TRANSFORM(
    "<svg width=\"200px\" height=\"200px\" viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<path d =\"M50 50L20 50A30 30 0 0 0 80 50Z\">"
    "<animateTransform attributeName =\"transform\" type=\"rotate\" repeatCount=\"3\" dur=\"1s\""
    " values=\"0 50 50;45 50 50;0 50 50\" keyTimes=\"0;0.5;1\"></animateTransform></path></svg>");

constexpr float IMAGE_COMPONENT_WIDTH = 100.0f;
constexpr float IMAGE_COMPONENT_HEIGHT = 100.0f;
} // namespace
class ParseTestNg : public testing::Test {
public:
    static RefPtr<SvgDom> ParseRect(const std::string& svgLabel);
    RefPtr<SvgDom> parsePolygon(const std::string& svgLable);
    static RefPtr<SvgDom> ParsePath(const std::string& svgLabel);
    RefPtr<SvgDom> ParseFeGaussianblur(const std::string& svgLabel);
    static RefPtr<SvgDom> ParseEllipse(const std::string& svgLabel);
};

RefPtr<SvgDom> ParseTestNg::ParseRect(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(RECT_SVG_LABEL.c_str(), RECT_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    auto rectDeclaration = AceType::DynamicCast<SvgRectDeclaration>(svgRect->declaration_);
    EXPECT_NE(rectDeclaration, nullptr);
    EXPECT_FLOAT_EQ(rectDeclaration->GetX().ConvertToPx(), X);
    EXPECT_FLOAT_EQ(rectDeclaration->GetY().ConvertToPx(), Y);
    EXPECT_FLOAT_EQ(rectDeclaration->GetRx().ConvertToPx(), RX);
    EXPECT_FLOAT_EQ(rectDeclaration->GetRy().ConvertToPx(), RY);
    EXPECT_FLOAT_EQ(rectDeclaration->GetWidth().ConvertToPx(), RECT_WIDTH);
    EXPECT_FLOAT_EQ(rectDeclaration->GetHeight().ConvertToPx(), RECT_HEIGHT);
    return svgDom;
}

RefPtr<SvgDom> ParseTestNg::parsePolygon(const std::string& svgLable)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLable.c_str(), svgLable.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(svg->children_.at(0));
    EXPECT_NE(svgPolygon, nullptr);
    auto svgPolyline = AceType::DynamicCast<SvgPolygon>(svg->children_.at(1));
    EXPECT_NE(svgPolyline, nullptr);
    auto polygonDeclaration = AceType::DynamicCast<SvgPolygonDeclaration>(svgPolygon->declaration_);
    EXPECT_NE(polygonDeclaration, nullptr);
    EXPECT_STREQ(polygonDeclaration->GetPoints().c_str(), POLYGON_POINT.c_str());
    auto polylineDeclaration = AceType::DynamicCast<SvgPolygonDeclaration>(svgPolyline->declaration_);
    EXPECT_NE(polylineDeclaration, nullptr);
    EXPECT_STREQ(polylineDeclaration->GetPoints().c_str(), POLYLINE_POINT.c_str());
    return svgDom;
}

RefPtr<SvgDom> ParseTestNg::ParsePath(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgPath = AceType::DynamicCast<SvgPath>(svg->children_.at(0));
    EXPECT_NE(svgPath, nullptr);
    auto pathDeclaration = AceType::DynamicCast<SvgPathDeclaration>(svgPath->declaration_);
    EXPECT_STREQ(pathDeclaration->GetD().c_str(), PATH_CMD.c_str());
    return svgDom;
}

RefPtr<SvgDom> ParseTestNg::ParseFeGaussianblur(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    auto svgFeGaussiaBlur = AceType::DynamicCast<SvgFeGaussianBlur>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeGaussiaBlur, nullptr);
    auto feDeclaration = AceType::DynamicCast<SvgFeGaussianBlurDeclaration>(svgFeGaussiaBlur->declaration_);
    EXPECT_NE(feDeclaration, nullptr);
    EXPECT_FLOAT_EQ(feDeclaration->GetStdDeviation(), STD_DEVIATION);
    EXPECT_EQ(feDeclaration->GetEdgeMode(), FeEdgeMode::EDGE_DUPLICATE);
    return svgDom;
}

RefPtr<SvgDom> ParseTestNg::ParseEllipse(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(svg->children_.at(0));
    EXPECT_NE(svgEllipse, nullptr);
    auto ellipseDeclaration = AceType::DynamicCast<SvgEllipseDeclaration>(svgEllipse->declaration_);
    EXPECT_FLOAT_EQ(ellipseDeclaration->GetCx().ConvertToPx(), ELLIPSE_Cx);
    EXPECT_FLOAT_EQ(ellipseDeclaration->GetCy().ConvertToPx(), ELLIPSE_Cy);
    EXPECT_FLOAT_EQ(ellipseDeclaration->GetRx().ConvertToPx(), ELLIPSE_RX);
    EXPECT_FLOAT_EQ(ellipseDeclaration->GetRy().ConvertToPx(), ELLIPSE_RY);
    return svgDom;
}
/**
 * @tc.name: ParseTest001
 * @tc.desc: parse circle label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseCircleTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG_LABEL.c_str(), CIRCLE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgLine = AceType::DynamicCast<SvgCircle>(svg->children_.at(0));
    EXPECT_NE(svgLine, nullptr);
    auto circleDeclaration = AceType::DynamicCast<SvgCircleDeclaration>(svgLine->declaration_);
    EXPECT_FLOAT_EQ(circleDeclaration->GetCx().ConvertToPx(), Cx);
    EXPECT_FLOAT_EQ(circleDeclaration->GetCy().ConvertToPx(), Cy);
    EXPECT_FLOAT_EQ(circleDeclaration->GetR().ConvertToPx(), R);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseAnimation
 * @tc.desc: parse animation path label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseAnimation, TestSize.Level1)
{
    SvgAnimation* svgAnimation = new SvgAnimation(SvgAnimateType::ANIMATE);
    EXPECT_NE(svgAnimation, nullptr);
    auto svgAnimate = svgAnimation->Create();
    EXPECT_NE(svgAnimate, nullptr);
    auto svgMotion = svgAnimation->CreateAnimateMotion();
    EXPECT_NE(svgMotion, nullptr);
    auto svgTransform = svgAnimation->CreateAnimateTransform();
    EXPECT_NE(svgTransform, nullptr);
    svgAnimation->SetAttr(ID, CLIP_SVG_LABEL);
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->ConvertCalcMode(ID), CalcMode::LINEAR);
    delete svgAnimation;
}

/**
 * @tc.name: ParseClipPathTest001
 * @tc.desc: parse clip path label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseClipPathTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CLIP_SVG_LABEL.c_str(), CLIP_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgClipPath = AceType::DynamicCast<SvgClipPath>(svgDefs->children_.at(0));
    EXPECT_NE(svgClipPath, nullptr);
    EXPECT_STREQ(svgClipPath->nodeId_.c_str(), ID.c_str());
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParseSvgTest001
 * @tc.desc: parse svg label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseSvgTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    EXPECT_FLOAT_EQ(svgDom->svgSize_.Width(), WIDTH);
    EXPECT_FLOAT_EQ(svgDom->svgSize_.Height(), HEIGHT);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Left(), VIEWBOX_X);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Top(), VIEWBOX_Y);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Width(), VIEWBOX_WIDTH);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Height(), VIEWBOX_HEIGHT);
}

/**
 * @tc.name: ParseUseTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseUseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(USE_SVG_LABEL.c_str(), USE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::GREEN);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgUse = AceType::DynamicCast<SvgUse>(svg->children_.at(INDEX_ONE));
    EXPECT_NE(svgUse, nullptr);
    auto svgUseDeclaration = AceType::DynamicCast<SvgDeclaration>(svgUse->declaration_);
    EXPECT_NE(svgUseDeclaration, nullptr);
    auto fillState = svgUseDeclaration->GetFillState();
    EXPECT_STREQ(fillState.GetFillRule().c_str(), FILL_RULE.c_str());
    EXPECT_STREQ(svgUseDeclaration->GetTransform().c_str(), TRANSFORM.c_str());
    auto stroke = svgUseDeclaration->GetStrokeState();
    EXPECT_FLOAT_EQ(STROKE_WIDTH, stroke.GetLineWidth().ConvertToPx());
    EXPECT_EQ(stroke.HasStroke(), true);
    EXPECT_STREQ(stroke.GetColor().ColorToString().c_str(), Color(STROKE).ColorToString().c_str());
    EXPECT_STREQ(svgUseDeclaration->GetHref().c_str(), HREF.c_str());
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);

    // <Use> shouldn't overwrite attributes of the referenced <Path>
    auto svgPath = svgDom->svgContext_->GetSvgNodeById(HREF);
    auto pathDeclaration = svgPath->declaration_;
    EXPECT_NE(pathDeclaration->GetFillState().GetFillRule().c_str(), FILL_RULE.c_str());
    EXPECT_NE(pathDeclaration->GetFillState().GetColor(), Color::RED);
    EXPECT_NE(pathDeclaration->GetTransform().c_str(), TRANSFORM.c_str());
    EXPECT_NE(pathDeclaration->GetStrokeState().GetColor(), Color(STROKE));
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse style label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParseStyleTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(STYLE_SVG_LABEL.c_str(), STYLE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgStyle = AceType::DynamicCast<SvgStyle>(svg->children_.at(0));
    EXPECT_NE(svgStyle, nullptr);
    // todo parse style attr
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParseStopTest001
 * @tc.desc: parse stop label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParseStopTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(STOP_SVG_LABEL.c_str(), STOP_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
    auto defers = AceType::DynamicCast<SvgDefs>(svg->children_.at(INDEX_ZEARO));
    EXPECT_NE(defers, nullptr);
    auto svgGradient = AceType::DynamicCast<SvgGradient>(defers->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGradient, nullptr);
    auto svgStop = AceType::DynamicCast<SvgStop>(svgGradient->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgStop, nullptr);
    auto svgStopDeclaration = AceType::DynamicCast<SvgStopDeclaration>(svgStop->declaration_);
    EXPECT_NE(svgStopDeclaration, nullptr);
    auto gradientColor = svgStopDeclaration->GetGradientColor();
    EXPECT_FLOAT_EQ(gradientColor.GetOpacity(), STOP_OPACITY);
    EXPECT_STREQ(gradientColor.GetColor().ColorToString().c_str(), Color::FromRGB(255, 255, 0).ColorToString().c_str());
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseRectTest001
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseRectTest001, TestSize.Level1)
{
    auto svgDom = ParseRect(RECT_SVG_LABEL);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseRectTest002
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseRectTest002, TestSize.Level1)
{
    auto svgDom = ParseRect(RECT_SVG_LABEL);
    RSCanvas rSCanvas;
    svgDom->svgContext_ = nullptr;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseRectTest003
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseRectTest003, TestSize.Level1)
{
    auto svgDom = ParseRect(RECT_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParsePolygonTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParsePolygonTest001, TestSize.Level1)
{
    auto svgDom = parsePolygon(POLYGON_SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParsePolygonTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParsePolygonTest002, TestSize.Level1)
{
    auto svgDom = parsePolygon(POLYGON_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParsePatternTest001
 * @tc.desc: parse pattern label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParsePatternTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATTERN_SVG_LABEL.c_str(), PATTERN_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgPattern = AceType::DynamicCast<SvgPattern>(svgDefs->children_.at(0));
    EXPECT_NE(svgPattern, nullptr);
    auto patternDeclaration = AceType::DynamicCast<SvgPatternDeclaration>(svgPattern->declaration_);
    EXPECT_NE(patternDeclaration, nullptr);
    EXPECT_FLOAT_EQ(patternDeclaration->GetWidth().ConvertToPx(), PATTERN_WIDTH);
    EXPECT_FLOAT_EQ(patternDeclaration->GetHeight().ConvertToPx(), PATTERN_HEIGHT);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetOffset().GetX(), PATTERN_VIEWBOX_X);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetOffset().GetY(), PATTERN_VIEWBOX_Y);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetSize().Width(), PATTERN_VIEWBOX_WIDTH);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetSize().Height(), PATTERN_VIEWBOX_HEIGHT);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);

    BorderRadiusArray radius;
    for (auto&& corner : radius) {
        corner = { 0.0f, 0.0f };
    }
    svgDom->SetRadius(radius);
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(*svgDom->radius_, radius);
}

/**
 * @tc.name: ParsePathTest001
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParsePathTest001, TestSize.Level1)
{
    auto svgDom = ParsePath(PATH_SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size());
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParsePathTest002
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParsePathTest002, TestSize.Level1)
{
    auto svgDom = ParsePath(PATH_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParsePathTest003
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParsePathTest003, TestSize.Level1)
{
    auto svgDom = ParsePath(PATH_SVG_LABEL4);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParsePathTest004
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParsePathTest004, TestSize.Level1)
{
    auto svgDom = ParsePath(PATH_SVG_LABEL3);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size());
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParsePathTest005
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseTestNg, ParsePathTest005, TestSize.Level1)
{
    auto svgDom = ParsePath(PATH_SVG_LABEL5);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size());
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse Mask label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseMaskTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(MASK_SVG_LABEL.c_str(), MASK_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgG = AceType::DynamicCast<SvgG>(svg->children_.at(INDEX_ONE));
    EXPECT_NE(svgG, nullptr);
    auto svgGChild = AceType::DynamicCast<SvgG>(svgG->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGChild, nullptr);
    auto svgMask = AceType::DynamicCast<SvgMask>(svgGChild->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgMask, nullptr);
    EXPECT_STREQ(svgMask->nodeId_.c_str(), MASK_ID.c_str());
    RSCanvas rSCanvas;
    // test canvas layer save and restore
    // all saved layers need to be restored
    auto skCanvas = rSCanvas.GetImpl<RSSkCanvas>()->ExportSkCanvas();
    auto layerCount = skCanvas->getSaveCount();
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
    EXPECT_EQ(skCanvas->getSaveCount(), layerCount);
}

/**
 * @tc.name: ParseLineTest001
 * @tc.desc: parse line label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseLineTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(LINE_SVG_LABEL.c_str(), LINE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgLine = AceType::DynamicCast<SvgLine>(svg->children_.at(0));
    EXPECT_NE(svgLine, nullptr);
    auto lineDeclaration = AceType::DynamicCast<SvgLineDeclaration>(svgLine->declaration_);
    EXPECT_FLOAT_EQ(lineDeclaration->GetX1().ConvertToPx(), X1);
    EXPECT_FLOAT_EQ(lineDeclaration->GetY1().ConvertToPx(), Y1);
    EXPECT_FLOAT_EQ(lineDeclaration->GetX2().ConvertToPx(), X2);
    EXPECT_FLOAT_EQ(lineDeclaration->GetY2().ConvertToPx(), Y2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseLinearGradientTest001
 * @tc.desc: parse lineargradient label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseLinearGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(GRADIENT_SVG_LINEAR.c_str(), GRADIENT_SVG_LINEAR.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
    auto defers = AceType::DynamicCast<SvgDefs>(svg->children_.at(INDEX_ZEARO));
    EXPECT_NE(defers, nullptr);
    EXPECT_NE(defers->children_.at(INDEX_ZEARO), nullptr);
    auto svgGradient = AceType::DynamicCast<SvgGradient>(defers->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGradient, nullptr);
    auto svgGradientDeclaration = AceType::DynamicCast<SvgGradientDeclaration>(svgGradient->gradientDeclaration_);
    EXPECT_NE(svgGradientDeclaration, nullptr);
    auto gradient = svgGradientDeclaration->GetGradient();
    EXPECT_EQ(gradient.GetLinearGradient().x1.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().x1->ConvertToPx(), ZERO);
    EXPECT_EQ(gradient.GetLinearGradient().x2.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().x2->ConvertToPx(), ZERO);
    EXPECT_EQ(gradient.GetLinearGradient().y1.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().y1->ConvertToPx(), ZERO);
    EXPECT_EQ(gradient.GetLinearGradient().y2.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().y2->ConvertToPx(), ZERO);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseRadialGradientTest001
 * @tc.desc: parse radialgradient label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseRadialGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(GRADIENT_SVG_RADIAL.c_str(), GRADIENT_SVG_RADIAL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_EQ(svg->children_.size(), CHILD_NUMBER);
    auto defers = AceType::DynamicCast<SvgDefs>(svg->children_.at(INDEX_ZEARO));
    EXPECT_NE(defers, nullptr);
    EXPECT_NE(defers->children_.at(INDEX_ZEARO), nullptr);
    auto svgGradient = AceType::DynamicCast<SvgGradient>(defers->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGradient, nullptr);
    auto svgGradientDeclaration = AceType::DynamicCast<SvgGradientDeclaration>(svgGradient->gradientDeclaration_);
    EXPECT_NE(svgGradientDeclaration, nullptr);
    auto gradient = svgGradientDeclaration->GetGradient();
    auto radialGradient = gradient.GetRadialGradient();
    EXPECT_EQ(radialGradient.fRadialCenterX.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.fRadialCenterX->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.fRadialCenterY.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.fRadialCenterY->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.radialCenterX.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialCenterX->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.radialCenterY.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialCenterY->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.radialHorizontalSize.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialHorizontalSize->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.radialVerticalSize.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialVerticalSize->ConvertToPx(), ZERO);
    EXPECT_EQ(radialGradient.radialShape.has_value(), false);
    EXPECT_EQ(radialGradient.radialSizeType.has_value(), false);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseGTest001
 * @tc.desc: parse g label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseGTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(G_SVG_LABEL.c_str(), G_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto g = AceType::DynamicCast<SvgG>(svg->children_.at(0));
    ASSERT_STREQ(g->nodeId_.c_str(), G_ID.c_str());
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseFilterTest001
 * @tc.desc: parse filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFilterTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FILTER_SVG_LABEL.c_str(), FILTER_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_STREQ(svgFilter->nodeId_.c_str(), FILTER_ID.c_str());
    auto filterDeclaration = AceType::DynamicCast<SvgFilterDeclaration>(svgFilter->declaration_);
    EXPECT_NE(filterDeclaration, nullptr);
    EXPECT_FLOAT_EQ(filterDeclaration->GetHeight().ConvertToPx(), FILTER_HEIGHT);
    EXPECT_FLOAT_EQ(filterDeclaration->GetWidth().ConvertToPx(), FILTER_WIDTH);
    EXPECT_FLOAT_EQ(filterDeclaration->GetX().ConvertToPx(), ZERO);
    EXPECT_FLOAT_EQ(filterDeclaration->GetY().ConvertToPx(), ZERO);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseFeGaussianblurTest001
 * @tc.desc: parse Fegaussianblur label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeGaussianblurTest001, TestSize.Level1)
{
    auto svgDom = ParseFeGaussianblur(FEGAUSS_SVG_LABEL);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseFeGaussianblurTest002
 * @tc.desc: parse Fegaussianblur label svg size is invalid
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeGaussianblurTest002, TestSize.Level1)
{
    auto svgDom = ParseFeGaussianblur(FEGAUSS_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseFeCompositeTest001
 * @tc.desc: parse FeComposite label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeCompositeTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(COMPOSITE_SVG_LABEL.c_str(), COMPOSITE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    auto svgFeComposite = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeComposite, nullptr);
    auto feCompositsDeclaration = AceType::DynamicCast<SvgFeCompositeDeclaration>(svgFeComposite->declaration_);
    EXPECT_NE(feCompositsDeclaration, nullptr);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseFeCompositeTest002
 * @tc.desc: parse Fe label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeCompositeTest002, TestSize.Level1)
{
    SvgFe* svgFe = new SvgFe();
    EXPECT_NE(svgFe, nullptr);
    sk_sp<SkImageFilter> imageFilter = nullptr;
    ColorInterpolationType colorInterpolationType = ColorInterpolationType::LINEAR_RGB;
    ColorInterpolationType srcColor = ColorInterpolationType::SRGB;
    svgFe->GetImageFilter(imageFilter, colorInterpolationType);
    EXPECT_EQ(colorInterpolationType, ColorInterpolationType::LINEAR_RGB);
    svgFe->ConverImageFilterColor(imageFilter, srcColor, colorInterpolationType);
    EXPECT_NE(imageFilter, nullptr);
    EXPECT_EQ(colorInterpolationType, ColorInterpolationType::LINEAR_RGB);
    delete svgFe;
}

/**
 * @tc.name: ParseFeCompositeTest003
 * @tc.desc: parse FeColorMatrix label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeCompositeTest003, TestSize.Level1)
{
    SvgFeColorMatrix* colorMatrix = new SvgFeColorMatrix();
    EXPECT_NE(colorMatrix, nullptr);
    colorMatrix->OnInitStyle();
    sk_sp<SkImageFilter> imageFilter = nullptr;
    ColorInterpolationType srcColor = ColorInterpolationType::SRGB;
    ColorInterpolationType colorInterPolationType = ColorInterpolationType::LINEAR_RGB;
    colorMatrix->OnAsImageFilter(imageFilter, srcColor, colorInterPolationType);
    EXPECT_NE(imageFilter, nullptr);
    EXPECT_EQ(colorInterPolationType, ColorInterpolationType::LINEAR_RGB);
    EXPECT_EQ(srcColor, ColorInterpolationType::SRGB);
    delete colorMatrix;
}

/**
 * @tc.name: ParseFeColorMatrixTest001
 * @tc.desc: parse FeColorMatrix label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseFeColorMatrixTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(COLOR_MATRIX_SVG_LABEL.c_str(), COLOR_MATRIX_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    auto svgFeColorMatrix = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeColorMatrix, nullptr);
    auto feColorDeclaration = AceType::DynamicCast<SvgFeColorMatrixDeclaration>(svgFeColorMatrix->declaration_);
    EXPECT_NE(feColorDeclaration, nullptr);
    EXPECT_STREQ(feColorDeclaration->GetType().c_str(), TYPE.c_str());
    EXPECT_STREQ(feColorDeclaration->GetValues().c_str(), VALUE.c_str());
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseEllipseTest001
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseEllipseTest001, TestSize.Level1)
{
    auto svgDom = ParseEllipse(ELLIPSE_SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseEllipseTest002
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseEllipseTest002, TestSize.Level1)
{
    auto svgDom = ParseEllipse(ELLIPSE_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseEllipseTest003
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseEllipseTest003, TestSize.Level1)
{
    auto svgDom = ParseEllipse(ELLIPSE_SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->root_ = nullptr;
    svgDom->FitViewPort(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseEllipseTest004
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseEllipseTest004, TestSize.Level1)
{
    SvgEllipse* sEllipse = new SvgEllipse();
    const Size viewPort = Size(0.0, 0.0);
    EXPECT_EQ(viewPort.Width(), 0.0);
    EXPECT_EQ(viewPort.Height(), 0.0);
    auto svgEllipse1 = sEllipse->Create();
    svgEllipse1->AsPath(viewPort);
    delete sEllipse;
}

/**
 * @tc.name: ParseAnimateTest001
 * @tc.desc: parse circle label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestNg, ParseAnimateTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_ANIMATE_TRANSFORM.c_str(), SVG_ANIMATE_TRANSFORM.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    EXPECT_TRUE(svgDom);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_TRUE(svg);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgAnimate = AceType::DynamicCast<SvgAnimation>(svg->children_.at(0)->children_.at(0));
    EXPECT_TRUE(svgAnimate);
    // values changed to indices
    std::vector<std::string> values { "0", "1", "2" };
    EXPECT_EQ(svgAnimate->GetValues(), values);
}
} // namespace OHOS::Ace::NG
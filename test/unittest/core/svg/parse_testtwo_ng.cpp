/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "include/core/SkStream.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_animate_declaration.h"
#include "core/components/declaration/svg/svg_circle_declaration.h"
#include "core/components/declaration/svg/svg_declaration.h"
#include "core/components/declaration/svg/svg_ellipse_declaration.h"
#include "core/components/declaration/svg/svg_fe_blend_declaration.h"
#include "core/components/declaration/svg/svg_fe_colormatrix_declaration.h"
#include "core/components/declaration/svg/svg_fe_composite_declaration.h"
#include "core/components/declaration/svg/svg_fe_declaration.h"
#include "core/components/declaration/svg/svg_fe_flood_declaration.h"
#include "core/components/declaration/svg/svg_fe_gaussianblur_declaration.h"
#include "core/components/declaration/svg/svg_filter_declaration.h"
#include "core/components/declaration/svg/svg_gradient_declaration.h"
#include "core/components/declaration/svg/svg_image_declaration.h"
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
#include "core/components_ng/svg/parse/svg_fe_blend.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_flood.h"
#include "core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "core/components_ng/svg/parse/svg_fe_offset.h"
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
#include "core/components_ng/svg/parse/svg_transform.h"
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
const std::string CLIP_SVG_LABEL =
    "<svg width=\"120\" height=\"120\" viewBox=\"0 0 120 120\" version=\"1.1\"><defs><clipPath id=\"myClip\"><circle "
    "cx=\"30\" cy=\"30\" r=\"20\"/><circle cx=\"70\" cy=\"70\" r=\"30\"/></clipPath></defs><rect x=\"10\" y=\"10\" "
    "width=\"100\" height=\"100\" clip-path=\"url(#myClip)\" fill=\"red\" /></svg>";
const std::string ID = "myClip";
const std::string SVG_LABEL = "<svg width=\"400\" height=\"500\" viewBox=\"-4 -10 300 300\"></svg>";
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
constexpr int32_t INDEX_ONE = 1;
const std::string STYLE_SVG_LABEL = "<svg viewBox=\"0 0 10 10\"><style>circle{fill:gold;stroke:maroon;stroke-width : "
                                    "2px;}</style><circle cx =\"5\" cy=\"5\" r=\"4\" /></svg>";
const std::string STOP_SVG_LABEL =
    "<svg height=\"150\" width=\"400\"><defs><linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" "
    "y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" /><stop offset=\"20px\" "
    "style=\"stop-color:rgb(255,0,0);stop-opacity:1\" /></linearGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
constexpr int32_t CHILD_NUMBER = 2;
const std::string RECT_SVG_LABEL = "<svg width=\"400\" height=\"400\" version=\"1.1\" fill=\"red\" "
                                   "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                   "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"10\" ry=\"10\"></rect></svg>";
const std::string RECT_SVG_LABEL2 = "<svg version=\"1.1\" fill=\"red\" "
                                    "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                    "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"10\" ry=\"10\"></rect></svg>";
const std::string RECT_SVG_LABEL3 = "<svg version=\"1.1\" fill=\"red\" "
                                    "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                    "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"1\" ry=\"-1\"></rect></svg>";
const std::string RECT_SVG_LABEL4 = "<svg version=\"1.1\" fill=\"red\" "
                                    "xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" height=\"100\" x=\"150\" "
                                    "y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"-1\" ry=\"1\"></rect></svg>";
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
const std::string G_SVG_LABEL = "<svg width=\"400\" height=\"500\"> <g id=\"myId\"> </g></svg>";
const std::string G_ID = "myId";
const std::string FILTER_SVG_LABEL =
    "<svg height=\"900\" width=\"900\"><filter id=\"composite\" y=\"0\" x=\"0\" width=\"900\" "
    "height=\"900\"><feTurbulence baseFrequency=\".05\" numOctaves=\"3\" result=\"B\"/><feComposite in2=\"B\" "
    "in=\"SourceGraphic\" operator=\"in\" /></filter><ellipse cx=\"100\" cy=\"87\" rx=\"75\" ry=\"87\" fill=\"red\" "
    "filter=\"url(#composite)\"/></svg>";
const std::string FILTER_ID = "composite";
const std::string FEGAUSS_SVG_LABEL =
    "<svg width=\"230\" height=\"120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
const std::string FEGAUSS_SVG_LABEL2 =
    "<svg width=\"-230\" height=\"-120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
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
const std::string ELLIPSE_SVG_LABEL3 =
    "<svg fill=\"white\" width=\"10\" height=\"10\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"0.0\" cy=\"0.0\" rx=\"-1\" ry=\"-1\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
const std::string ELLIPSE_SVG_LABEL4 =
    "<svg fill=\"white\" width=\"10\" height=\"10\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"0.0\" cy=\"0.0\" rx=\"1\" ry=\"-1\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
constexpr float ELLIPSE_CX = 60.0f;
constexpr float ELLIPSE_CY = 200.0f;
constexpr float ELLIPSE_RX = 50.0f;
constexpr float ELLIPSE_RY = 100.0f;
const std::string SVG_ANIMATE_TRANSFORM(
    "<svg width=\"200px\" height=\"200px\" viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<path d =\"M50 50L20 50A30 30 0 0 0 80 50Z\">"
    "<animateTransform attributeName =\"transform\" type=\"rotate\" repeatCount=\"3\" dur=\"1s\""
    " values=\"0 50 50;45 50 50;0 50 50\" keyTimes=\"0;0.5;1\"></animateTransform></path></svg>");

const std::string NONE_STR = "";
const std::string SATURATE_VALUE = "10";
const std::string HUE_ROTATE = "80";
const std::string FE_COLOR_MATRIX =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<filter id=\"colorMatrix\">"
    "<feColorMatrix in=\"SourceGraphic\" type=\"matrix\" values=\"R 0 0 0 0 0 G 0 0 0 0 0 B 0 0 0 0 0 A 0\" />"
    "<feColorMatrix type=\"saturate\" values=\"10\"/>"
    "<feColorMatrix type=\"hueRotate\" values=\"80\"/>"
    "<feColorMatrix type=\"luminanceToAlpha\" values=\"80\"/>"
    "<feColorMatrix type=\"matrix\" values=\"1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0\" />"
    "</filter>"
    "<g>"
    "<circle cx=\"30\" cy=\"30\" r=\"20\" fill=\"red\" fill-opacity=\"0.5\" />"
    "</g>"
    "<g filter=\"url(#colorMatrix)\">"
    "<circle cx=\"80\" cy=\"30\" r=\"20\" fill=\"red\" fill-opacity=\"0.5\" />"
    "</g>"
    "</svg>";

const std::string FE_GAUSSIAN_BLUR =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<filter id=\"colorMatrix\">"
    "<feGaussianBlur stdDeviation=\"10 50\"/>"
    "<feGaussianBlur stdDeviation=\"10\"/>"
    "<feGaussianBlur stdDeviation=\"abc abc\"/>"
    "</filter>"
    "<g>"
    "<rect width=\"90\" height=\"90\" fill=\"#0099cc\" filter=\"url(#blurFilter)\" />"
    "</g>"
    "</svg>";

const std::string FE_FLOOD_AND_COMPOSITE =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" >"
    "<filter id=\"colorMatrix\">"
    "<feFlood flood-color=\"red\" flood-opacity=\"0\" result=\"flood\" /><feFlood flood-color=\"green\" "
    "flood-opacity=\"1\" result=\"flood1\" />"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"xor\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/></filter>"
    "<g><rect width=\"90\" height=\"90\" fill=\"#0099cc\" filter=\"url(#blurFilter)\" /></g></svg>";

const std::string FE_COMPOSITE =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" >"
    "<filter id=\"colorMatrix\">"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"undefine\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"arithmetic\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"atop\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"in\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"lighter\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"out\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"xor\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/>"
    "<feComposite in=\"SourceAlpha\" in2=\"SourceGraphic\" operator=\"over\" result=\"composite\" k1=\"1\" "
    "k2=\"0\"/></filter>"
    "<g><rect width=\"90\" height=\"90\" fill=\"#0099cc\" filter=\"url(#blurFilter)\" /></g></svg>";

const std::string FE_BLEND =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<filter id=\"colorMatrix\">"
    "<feBlend in=\"SourceGraphic\" in2=\"SourceAlpha\" mode=\"lighten\" />"
    "</filter>"
    "<g>"
    "<rect width=\"90\" height=\"90\" fill=\"#0099cc\" filter=\"url(#blurFilter)\" />"
    "</g>"
    "</svg>";

const std::string IMAGE_HREF = "test.png";
const std::string IMAGE_LABEL =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<image id=\"image001\" x=\"150\" y=\"20\" width=\"100\" height=\"100\" href=\"test.png\" />"
    "</svg>";

constexpr float IMAGE_COMPONENT_WIDTH = 100.0f;
constexpr float IMAGE_COMPONENT_HEIGHT = 100.0f;

std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
} // namespace
class ParseTestTwoNg : public testing::Test {
public:
    static RefPtr<SvgDom> ParseRect(const std::string& svgLabel);
    RefPtr<SvgDom> parsePolygon(const std::string& svgLable);
    static RefPtr<SvgDom> ParsePath(const std::string& svgLabel);
    RefPtr<SvgDom> ParseFeGaussianblur(const std::string& svgLabel);
    static RefPtr<SvgDom> ParseEllipse(const std::string& svgLabel);
    void CallBack(Testing::MockCanvas& rSCanvas);
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }
};

RefPtr<SvgDom> ParseTestTwoNg::ParseRect(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(RECT_SVG_LABEL.c_str(), RECT_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    auto rectDeclaration = svgRect->rectAttr_;
    EXPECT_FLOAT_EQ(rectDeclaration.x.ConvertToPx(), X);
    EXPECT_FLOAT_EQ(rectDeclaration.y.ConvertToPx(), Y);
    EXPECT_FLOAT_EQ(rectDeclaration.rx.ConvertToPx(), RX);
    EXPECT_FLOAT_EQ(rectDeclaration.ry.ConvertToPx(), RY);
    EXPECT_FLOAT_EQ(rectDeclaration.width.ConvertToPx(), RECT_WIDTH);
    EXPECT_FLOAT_EQ(rectDeclaration.height.ConvertToPx(), RECT_HEIGHT);
    return svgDom;
}

RefPtr<SvgDom> ParseTestTwoNg::parsePolygon(const std::string& svgLable)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLable.c_str(), svgLable.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(svg->children_.at(0));
    EXPECT_NE(svgPolygon, nullptr);
    auto svgPolyline = AceType::DynamicCast<SvgPolygon>(svg->children_.at(1));
    EXPECT_NE(svgPolyline, nullptr);
    auto polygonDeclaration = svgPolygon->polyAttr_;
    EXPECT_STREQ(polygonDeclaration.points.c_str(), POLYGON_POINT.c_str());
    auto polylineDeclaration = svgPolyline->polyAttr_;
    EXPECT_STREQ(polylineDeclaration.points.c_str(), POLYLINE_POINT.c_str());
    return svgDom;
}

RefPtr<SvgDom> ParseTestTwoNg::ParsePath(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgPath = AceType::DynamicCast<SvgPath>(svg->children_.at(0));
    EXPECT_NE(svgPath, nullptr);
    auto pathDeclaration = svgPath->d_;
    EXPECT_STREQ(pathDeclaration.c_str(), PATH_CMD.c_str());
    return svgDom;
}

RefPtr<SvgDom> ParseTestTwoNg::ParseFeGaussianblur(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    auto svgFeGaussiaBlur = AceType::DynamicCast<SvgFeGaussianBlur>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeGaussiaBlur, nullptr);
    auto feDeclaration = svgFeGaussiaBlur->gaussianBlurAttr_;
    EXPECT_EQ(feDeclaration.edgeMode, SvgFeEdgeMode::EDGE_DUPLICATE);
    return svgDom;
}

RefPtr<SvgDom> ParseTestTwoNg::ParseEllipse(const std::string& svgLabel)
{
    auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(svg->children_.at(0));
    EXPECT_NE(svgEllipse, nullptr);
    auto ellipseDeclaration = svgEllipse->ellipseAttr_;
    EXPECT_FLOAT_EQ(ellipseDeclaration.cx.ConvertToPx(), ELLIPSE_CX);
    EXPECT_FLOAT_EQ(ellipseDeclaration.cy.ConvertToPx(), ELLIPSE_CY);
    EXPECT_FLOAT_EQ(ellipseDeclaration.rx.ConvertToPx(), ELLIPSE_RX);
    EXPECT_FLOAT_EQ(ellipseDeclaration.ry.ConvertToPx(), ELLIPSE_RY);
    return svgDom;
}

void ParseTestTwoNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DrawPath(_)).Times(AtLeast(1));
}

/**
 * @tc.name: ParseLineTest002
 * @tc.desc: Create an SvgLine and set path
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseLineTest002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value not is nullptr
     */
    auto svgLine = AccessibilityManager::MakeRefPtr<SvgLine>();
    svgLine->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_NE(svgLine, nullptr);
}

/**
 * @tc.name: ParseEllipseTest005
 * @tc.desc: Create an SvgEllipse and set path
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseEllipseTest005, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ELLIPSE_SVG_LABEL3.c_str(), ELLIPSE_SVG_LABEL3.length());
    EXPECT_NE(svgStream, nullptr);

    /* *
     * @tc.steps: step1. call CreateSvgDom
     * @tc.expected: Execute function return value size not is 0
     */
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);

    /* *
     * @tc.steps: step2. call AsPath
     * @tc.expected: Execute function return value not is nullptr
     */
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(svg->children_.at(0));
    svgEllipse->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_NE(svgEllipse, nullptr);
}

/**
 * @tc.name: ParseEllipseTest006
 * @tc.desc: Create an SvgEllipse and set patha
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseEllipseTest006, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(ELLIPSE_SVG_LABEL4.c_str(), ELLIPSE_SVG_LABEL4.length());
    EXPECT_NE(svgStream, nullptr);

    /* *
     * @tc.steps: step1. call CreateSvgDom
     * @tc.expected: Execute function return value size not is 0
     */
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);

    /* *
     * @tc.steps: step2. call AsPath
     * @tc.expected: Execute function return value not is nullptr
     */
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(svg->children_.at(0));
    svgEllipse->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_NE(svgEllipse, nullptr);
}

/**
 * @tc.name: ParsePolygonTest003
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePolygonTest003, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. call CreateSvgDom
     * @tc.expected: Execute svgDom root node is 2
     */
    auto svgStream = SkMemoryStream::MakeCopy(POLYGON_SVG_LABEL1.c_str(), POLYGON_SVG_LABEL1.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);

    /* *
     * @tc.steps: step2. call AsPath
     * @tc.expected: Execute SvgPolygon Points is empty
     */
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(svg->children_.at(0));
    auto declaration = svgPolygon->polyAttr_;
    declaration.points = "";
    svgPolygon->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_TRUE(declaration.points.empty());

    /* *
     * @tc.steps: step3. call AsPath
     * @tc.expected: Execute SvgPolygon Points parse error
     */
    declaration.points = "ccc";
    svgPolygon->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_FALSE(declaration.points.empty());
}

/**
 * @tc.name: ParsePolygonTest003
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePolygonTest004, TestSize.Level1)
{
    auto polygon = AceType::DynamicCast<SvgPolygon>(AceType::MakeRefPtr<SvgPolygon>(true));
    EXPECT_NE(polygon, nullptr);
    std::vector<RSPoint> points;
    RSPoint point1;
    point1.SetX(1.0f);
    point1.SetX(2.0f);
    points.emplace_back(point1);

    RSPoint point2;
    point2.SetX(1.0f);
    point2.SetX(2.0f);
    points.emplace_back(point2);

    SvgLengthScaleRule lengthScaleRule;
    polygon->ConvertPoints(points, lengthScaleRule);
    EXPECT_EQ(points.size(), 2);
}

/**
 * @tc.name: ParsePolygonTest003
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePolygonTest005, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto polygon = AceType::DynamicCast<SvgPolygon>(AceType::MakeRefPtr<SvgPolygon>(true));
    EXPECT_NE(polygon, nullptr);

    Size size;
    auto result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "no";
    result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|";
    polygon->attributes_.clipState.clipRule_ = SvgRuleType::SVG_RULE_EVENODD;
    polygon->attributes_.fillState.fillRule_ = "evenodd";
    result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParsePolygonTest003
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePolygonTest006, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto polygon = AceType::DynamicCast<SvgPolygon>(AceType::MakeRefPtr<SvgPolygon>(true));
    EXPECT_NE(polygon, nullptr);

    Size size;
    auto result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "no";
    result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|";
    polygon->attributes_.clipState.clipRule_ = SvgRuleType::SVG_RULE_EVENODD;
    polygon->attributes_.fillState.fillRule_ = "evenodd";
    result = polygon->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParsePolygonTest003
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePolygonTest007, TestSize.Level1)
{
    auto polygon = AceType::DynamicCast<SvgPolygon>(AceType::MakeRefPtr<SvgPolygon>(true));
    EXPECT_NE(polygon, nullptr);
    SvgLengthScaleRule rule;
    RSRecordingPath path;
    polygon->path_ = path;

    auto result = polygon->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->path_ = std::nullopt;
    result = polygon->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "no";
    result = polygon->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    polygon->polyAttr_.points = "*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|*aaaaaaaa|";
    polygon->attributes_.fillState.fillRule_ = "evenodd";
    rule.pathTransform_ = true;
    result = polygon->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));
}

/**
 * @tc.name: SvgGTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgGTest001, TestSize.Level1)
{
    auto svgG = AceType::DynamicCast<SvgG>(AceType::MakeRefPtr<SvgG>());
    EXPECT_NE(svgG, nullptr);
    auto svgG1 = SvgG::Create();
    EXPECT_NE(svgG1, nullptr);
    SvgLengthScaleRule lengthRule;
    RSCanvas canvas;
    svgG->ApplyOpacity(canvas);
    svgG->attributes_.hasOpacity = true;
    svgG->ApplyOpacity(canvas);
    svgG->OnDraw(canvas, lengthRule);
    Size size;
    auto result = svgG->AsPath(size);
    EXPECT_TRUE(result.BuildFromSVGString(""));
    result = svgG->AsPath(lengthRule);
    EXPECT_TRUE(result.BuildFromSVGString(""));
}

/**
 * @tc.name: SvgGTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgPath001, TestSize.Level1)
{
    auto svgPath = AceType::DynamicCast<SvgPath>(AceType::MakeRefPtr<SvgPath>());
    EXPECT_NE(svgPath, nullptr);
    SvgLengthScaleRule rule;
    rule.lengthScaleUnit_ = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    auto rect = svgPath->GetobjectBoundingBox(rule);
    EXPECT_EQ(rect.Width(), 0);
    EXPECT_EQ(rect.Height(), 0);
    EXPECT_EQ(rect.Left(), 0);
    EXPECT_EQ(rect.Top(), 0);

    rule.lengthScaleUnit_ = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    rect = svgPath->GetobjectBoundingBox(rule);
    EXPECT_EQ(rect.Width(), 1);
    EXPECT_EQ(rect.Height(), 1);
    EXPECT_EQ(rect.Left(), 0);
    EXPECT_EQ(rect.Top(), 0);
}

/**
 * @tc.name: SvgGTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgPath002, TestSize.Level1)
{
    auto svgPath = AceType::DynamicCast<SvgPath>(AceType::MakeRefPtr<SvgPath>());
    EXPECT_NE(svgPath, nullptr);
    SvgLengthScaleRule rule;
    auto result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    RSRecordingPath path;
    svgPath->path_ = path;

    result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    rule.pathTransform_ = true;
    svgPath->path_ = std::nullopt;
    result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    svgPath->path_ = path;
    result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    svgPath->d_ = "123";
    result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));

    svgPath->attributes_.fillState.fillRule_ = "evenodd";
    result = svgPath->AsPath(rule);
    EXPECT_TRUE(result.BuildFromSVGString(""));
}

/**
 * @tc.name: SvgGTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgFeGaussianBlurTest001, TestSize.Level1)
{
    auto feGaussianBlur = AceType::DynamicCast<SvgFeGaussianBlur>(SvgFeGaussianBlur::Create());
    EXPECT_NE(feGaussianBlur, nullptr);
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType type = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
    feGaussianBlur->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, false);

    feGaussianBlur->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    feGaussianBlur->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, true);

    feGaussianBlur->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    feGaussianBlur->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, true);

    auto result = feGaussianBlur->ParseAndSetSpecializedAttr("edgemode", "aaaa");
    EXPECT_TRUE(result);

    result = feGaussianBlur->ParseAndSetSpecializedAttr("stddeviation", "1,2,4,6,76,43");
    EXPECT_TRUE(result);

    result = feGaussianBlur->ParseAndSetSpecializedAttr("stddeviation", "1 2 4 6 76 43");
    EXPECT_TRUE(result);

    result = feGaussianBlur->ParseAndSetSpecializedAttr("stddeviation", "1,2");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SvgGTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgPatternTest001, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    EXPECT_NE(pattern, nullptr);
    RSCanvas canvas;
    Size viewPort;
    std::optional<Color> color = Color::BLACK;
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    pattern->OnDrawTraversedBefore(canvas, viewPort, color);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);

    pattern->patternAttr_.patternContentUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    pattern->OnDrawTraversedBefore(canvas, viewPort, color);
    pattern->OnDrawTraversedAfter(canvas, viewPort, color);
    RSBrush brush;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    RefPtr<SvgNode> svgNode1 = nullptr;
    RefPtr<SvgNode> svgNode2 = SvgPattern::Create();
    pattern->children_.emplace_back(svgNode1);
    pattern->children_.emplace_back(svgNode2);
    pattern->OnPatternEffect(canvas, brush, context);
    EXPECT_TRUE(context.UseFillColor());
}

/**
 * @tc.name: ParseStyleTest002
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseStyleTest002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. call ParseCssStyle
     * @tc.expected: Execute function return value false
     */
    SvgStyle::ParseCssStyle("", nullptr);
    std::string str;
    PushAttr callback = [&str](const std::string& key, const std::pair<std::string, std::string>& value) { str = key; };
    SvgStyle::ParseCssStyle("body {font-style: oblique;}.normal {font-style: normal;}", callback);
    EXPECT_FALSE(str.empty());

    SvgStyle::ParseCssStyle("body font-style: oblique;}. {font-style: normal;}", callback);
    EXPECT_FALSE(str.empty());
}

/**
 * @tc.name: ParseRectTest004
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseRectTest004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(RECT_SVG_LABEL3.c_str(), RECT_SVG_LABEL3.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value not is 0
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    svgRect->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    auto rectDeclaration = svgRect->rectAttr_;
    EXPECT_NE(rectDeclaration.rx.Value(), 0);
}

/**
 * @tc.name: ParseUseTest002
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseUseTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(USE_SVG_LABEL.c_str(), USE_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value is true
     */
    auto svgUse = AceType::DynamicCast<SvgUse>(svg->children_.at(INDEX_ONE));
    svgUse->attributes_.href = "";
    svgUse->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_TRUE(svgUse->attributes_.href.empty());
}

/**
 * @tc.name: ParseImageTest001
 * @tc.desc: parse image label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseImageTest001, TestSize.Level1)
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
    auto imageDeclaration = svgImage->imageAttr_;
    EXPECT_FLOAT_EQ(imageDeclaration.x.ConvertToPx(), X);
    EXPECT_FLOAT_EQ(imageDeclaration.y.ConvertToPx(), Y);
    EXPECT_FLOAT_EQ(imageDeclaration.width.ConvertToPx(), RECT_WIDTH);
    EXPECT_FLOAT_EQ(imageDeclaration.height.ConvertToPx(), RECT_HEIGHT);
    EXPECT_STREQ(imageDeclaration.href.c_str(), IMAGE_HREF.c_str());
}

/**
 * @tc.name: ParseGradientTest001
 * @tc.desc: parse Gradient set
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG_LABEL.c_str(), CIRCLE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(svg->children_.at(0));
    EXPECT_NE(svgCircle, nullptr);

    OHOS::Ace::Gradient gradient;
    OHOS::Ace::LinearGradient linearGradientLocal;
    linearGradientLocal.x1 = Dimension(1.0);
    linearGradientLocal.x2 = Dimension(1.0);
    linearGradientLocal.y1 = Dimension(1.0);
    linearGradientLocal.y2 = Dimension(1.0);
    gradient.SetLinearGradient(linearGradientLocal);
    svgCircle->SetLinearGradient(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), gradient);
    auto linearGradientInfo = gradient.GetLinearGradientInfo();
    EXPECT_NE(linearGradientInfo.x1, 0.0);
    linearGradientLocal.x1 = Dimension(1.0, DimensionUnit::PERCENT);
    linearGradientLocal.x2 = Dimension(1.0, DimensionUnit::PERCENT);
    linearGradientLocal.y1 = Dimension(1.0, DimensionUnit::PERCENT);
    linearGradientLocal.y2 = Dimension(1.0, DimensionUnit::PERCENT);
    gradient.SetLinearGradient(linearGradientLocal);
    svgCircle->SetLinearGradient(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), gradient);
    linearGradientInfo = gradient.GetLinearGradientInfo();
    EXPECT_EQ(linearGradientInfo.x1, 0.0);

    OHOS::Ace::RadialGradient radialGradientLocal;
    radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
    radialGradientLocal.radialCenterX = AnimatableDimension(1);
    radialGradientLocal.radialCenterY = AnimatableDimension(1);
    radialGradientLocal.fRadialCenterX = Dimension(1);
    radialGradientLocal.fRadialCenterY = Dimension(1);
    gradient.SetRadialGradient(radialGradientLocal);
    auto radialGradientInfo = gradient.GetRadialGradientInfo();
    EXPECT_EQ(radialGradientInfo.r, 0.0);
    EXPECT_EQ(radialGradientInfo.cx, 0.0);
    EXPECT_EQ(radialGradientInfo.cy, 0.0);
    EXPECT_EQ(radialGradientInfo.fx, 0.0);
    EXPECT_EQ(radialGradientInfo.fy, 0.0);
    svgCircle->SetRadialGradient(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), gradient);
    radialGradientInfo = gradient.GetRadialGradientInfo();
    EXPECT_NE(radialGradientInfo.r, 0.0);
    EXPECT_NE(radialGradientInfo.cx, 0.0);
    EXPECT_NE(radialGradientInfo.cy, 0.0);
    EXPECT_NE(radialGradientInfo.fx, 0.0);
    EXPECT_NE(radialGradientInfo.fy, 0.0);
}

/**
 * @tc.name: ParseGradientTest002
 * @tc.desc: parse Gradient set
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseGradientTest002, TestSize.Level1)
{
    std::function func = [&](const OHOS::Ace::Gradient& gradient) {
        auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG_LABEL.c_str(), CIRCLE_SVG_LABEL.length());
        EXPECT_NE(svgStream, nullptr);
        ImageSourceInfo src;
        src.SetFillColor(Color::BLACK);
        auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
        auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
        auto svgCircle = AceType::DynamicCast<SvgCircle>(svg->children_.at(0));
        EXPECT_NE(svgCircle, nullptr);

        auto viewPort = Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT);
        auto baseAttr = svgCircle->GetBaseAttributes();
        svgCircle->fillState_.SetGradient(gradient);
        baseAttr.fillState.SetGradient(gradient);
        baseAttr.strokeState.SetGradient(gradient);
        svgCircle->SetBaseAttributes(baseAttr);
        svgCircle->SetGradientStyle(0);
        svgCircle->SetStrokeGradientStyle(0);
        svgCircle->UpdateFillGradient(viewPort);
        svgCircle->UpdateStrokeGradient(viewPort);

        OHOS::Ace::RadialGradient radialGradientLocal;
        radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
        radialGradientLocal.radialCenterX = AnimatableDimension(1);
        radialGradientLocal.radialCenterY = AnimatableDimension(1);
        radialGradientLocal.fRadialCenterX = Dimension(1);
        radialGradientLocal.fRadialCenterY = Dimension(1);
        svgCircle->fillState_.SetGradient(gradient);
        baseAttr.fillState.SetGradient(gradient);
        baseAttr.strokeState.SetGradient(gradient);
        svgCircle->SetBaseAttributes(baseAttr);
        svgCircle->SetGradientStyle(1);
        svgCircle->SetStrokeGradientStyle(1);
        svgCircle->UpdateFillGradient(viewPort);
        svgCircle->UpdateStrokeGradient(viewPort);
    };
    OHOS::Ace::Gradient gradient;
    func(gradient);
    gradient.AddColor(OHOS::Ace::GradientColor(Color::RED));
    func(gradient);
}

/**
 * @tc.name: ParseNodeTest001
 * @tc.desc: SvgNode SetAttr Parameters
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest001, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    svgNode->SetAttr("stroke-dasharray", "");

    svgNode->SetAttr("stroke-linecap", "round");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineCap(), LineCapStyle::ROUND);

    svgNode->SetAttr("strokeLinecap", "square");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineCap(), LineCapStyle::SQUARE);

    svgNode->SetAttr("stroke-linejoin", "bevel");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineJoin(), LineJoinStyle::BEVEL);

    svgNode->SetAttr("strokeLinejoin", "round");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineJoin(), LineJoinStyle::ROUND);

    svgNode->SetAttr("stroke-miterlimit", "0.1");
    EXPECT_NE(svgNode->GetBaseAttributes().strokeState.GetMiterLimit(), 0.1);

    svgNode->SetAttr("stroke-miterlimit", "1.1");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetMiterLimit(), 1.1);

    svgNode->SetAttr("strokeMiterlimit", "0.2");
    EXPECT_NE(svgNode->GetBaseAttributes().strokeState.GetMiterLimit(), 0.2);

    svgNode->SetAttr("strokeMiterlimit", "1.2");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetMiterLimit(), 1.2);

    svgNode->SetAttr("strokeOpacity", "0.321");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetOpacity().GetValue(), 0.321);

    svgNode->SetAttr("strokeWidth", "1.2");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineWidth().Value(), 1.2);

    svgNode->SetAttr("strokeWidth", "-1.2");
    EXPECT_NE(svgNode->GetBaseAttributes().strokeState.GetLineWidth().Value(), -1.2);

    svgNode->SetAttr("stroke-width", "-1.2");
    EXPECT_NE(svgNode->GetBaseAttributes().strokeState.GetLineWidth().Value(), -1.2);

    svgNode->SetAttr("strokeDasharray", "");
    svgNode->SetAttr("strokeDasharray", "1.1 1.2");
    auto tesData = std::vector { 1.1, 1.2 };
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineDash().lineDash, tesData);

    svgNode->SetAttr("strokeDashoffset", "2.0");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineDash().dashOffset, 2.0);

    svgNode->SetAttr("transform-origin", "10 10");
    EXPECT_EQ(Dimension(10), svgNode->GetBaseAttributes().transformOrigin.first);
    EXPECT_EQ(Dimension(10), svgNode->GetBaseAttributes().transformOrigin.second);

    svgNode->SetAttr("xlink:href", "test_xlink:href");
    EXPECT_NE(svgNode->GetBaseAttributes().href, "test_xlink:href");
}

/**
 * @tc.name: ParseNodeTest002
 * @tc.desc: SvgNode test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_ANIMATE_TRANSFORM.c_str(), SVG_ANIMATE_TRANSFORM.length());
    ImageSourceInfo src;
    Size size;
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);

    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    svg->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    svg->OnFilter(rSCanvas, size);
    auto containerSize = svgDom->GetContainerSize();
    EXPECT_EQ(containerSize, SizeF(200.0f, 200.0f));
    svgDom->SetFillColor(Color::RED);
    EXPECT_EQ(svgDom->fillColor_.value(), Color::RED);
    svgDom->ControlAnimation(true);
    svgDom->SetSmoothEdge(1.1f);
    EXPECT_EQ(svgDom->smoothEdge_, 1.1f);
}

/**
 * @tc.name: ParseNodeTest003
 * @tc.desc: SvgNode test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest003, TestSize.Level1)
{
    Size size;
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    auto dimension = Dimension(0.0, DimensionUnit::PERCENT);

    SvgLengthType svgLengthType = static_cast<SvgLengthType>(int(SvgLengthType::OTHER) + 1);
    EXPECT_EQ(svgNode->ConvertDimensionToPx(dimension, size, svgLengthType), 0.0);
    dimension.SetUnit(DimensionUnit::AUTO);
    EXPECT_EQ(svgNode->ConvertDimensionToPx(dimension, size, svgLengthType), 0.0);

    EXPECT_EQ(svgNode->ConvertDimensionToPx(dimension, 1.0), 0.0);

    EXPECT_EQ(svgNode->GetRootViewBox(), Rect());
}

/**
 * @tc.name: ParseNodeTest004
 * @tc.desc: SvgNode test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest004, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_ANIMATE_TRANSFORM.c_str(), SVG_ANIMATE_TRANSFORM.length());
    ImageSourceInfo src;
    Size size = { 100, 100 };
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    svgDom->SetAnimationOnFinishCallback([]() {});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, size);
}

/**
 * @tc.name: ParseNodeTest005
 * @tc.desc: SvgNode SetAttr Parameters
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest005, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create svg node
     */
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();

    /* *
     * @tc.steps: step2. set strokeLinecap
     * @tc.expected: The property is set successfully
     */
    svgNode->SetAttr("strokeLinecap", "butt");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineCap(), LineCapStyle::BUTT);

    /* *
     * @tc.steps: step3. set strokeLinejoin
     * @tc.expected: The property is set successfully
     */
    svgNode->SetAttr("strokeLinejoin", "miter");
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetLineJoin(), LineJoinStyle::MITER);

    /* *
     * @tc.steps: step4. set fill
     * @tc.expected: The property is set successfully
     */
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    svgNode->SetAttr("fill", "#003153");
    EXPECT_EQ(svgNode->GetBaseAttributes().fillState.GetColor().GetValue(), 0xFF003153);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseAnimation001
 * @tc.desc: Test SvgAnimation SetAttr Method.
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseAnimation001, TestSize.Level1)
{
    auto svgAnimation = AccessibilityManager::MakeRefPtr<SvgAnimation>(SvgAnimateType::MOTION);
    EXPECT_NE(svgAnimation, nullptr);

    svgAnimation->SetAttr("begin", "1000ms");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetBegin(), 1000);

    svgAnimation->SetAttr("dur", "indefinite");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetDur(), 0);

    svgAnimation->SetAttr("repeatcount", "indefinite");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetRepeatCount(), -1);

    svgAnimation->SetAttr("keytimes", "");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetKeyTimes().size(), 0);

    svgAnimation->SetAttr("keysplines", "");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetKeySplines().size(), 0);

    svgAnimation->SetAttr("keysplines", "0.25;0.1;0.25;1");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetKeySplines().size(), 4);

    svgAnimation->SetAttr("keypoints", "");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetKeyPoints().size(), 0);

    svgAnimation->SetAttr("keypoints", "0;0.4;1");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetKeyPoints().size(), 3);
}

/**
 * @tc.name: ParseAnimation002
 * @tc.desc: Test SvgAnimation CreatePropertyAnimation Method.
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseAnimation002, TestSize.Level1)
{
    auto svgAnimation = AccessibilityManager::MakeRefPtr<SvgAnimation>(SvgAnimateType::TRANSFORM);
    EXPECT_NE(svgAnimation, nullptr);

    svgAnimation->SetAttr("begin", "1000ms");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetBegin(), 1000);

    std::function<void(double)> callback = [](double x) -> void { x = 0; };
    const double value = 0;
    svgAnimation->values_ = { "1" };
    svgAnimation->CreatePropertyAnimation<double>(value, std::move(callback));
    EXPECT_NE(svgAnimation->animator_, nullptr);
    svgAnimation->animator_->Finish();
    EXPECT_EQ(svgAnimation->animator_->IsStopped(), true);

    svgAnimation->CreatePropertyAnimation<double>(value, std::move(callback));
    EXPECT_EQ(svgAnimation->animator_->IsStopped(), false);
}

/**
 * @tc.name: ParseAnimation003
 * @tc.desc: Create Animation SetAttr
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseAnimation003, TestSize.Level1)
{
    auto svgAnimation = AccessibilityManager::MakeRefPtr<SvgAnimation>(SvgAnimateType::MOTION);
    EXPECT_NE(svgAnimation, nullptr);

    /* *
     * @tc.steps: step1. call SetAttr
     * @tc.expected: Attribute set successfully
     */
    svgAnimation->SetAttr("attributeName", "fill");
    svgAnimation->UpdateAttr();
    auto svg = SvgSvg::Create();
    EXPECT_NE(svg, nullptr);
    svg->PrepareAnimation(svgAnimation);
    EXPECT_EQ(svgAnimation->GetAttributeName(), "fill");

    svgAnimation->SetAttr("calcmode", "paced");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetCalcMode(), CalcMode::PACED);

    svgAnimation->SetAttr("from", "blue");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetFrom(), "blue");

    svgAnimation->SetAttr("to", "red");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetTo(), "red");

    svgAnimation->SetAttr("path", "M0 0 L100 100");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetPath(), "M0 0 L100 100");

    svgAnimation->SetAttr("rotate", "45");
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->GetRotate(), "45");
}

/**
 * @tc.name: ParseStopTest001
 * @tc.desc: parse stop label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseStopTest001, TestSize.Level1)
{
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    /* *
     * @tc.steps: step1. create svgStop node
     */
    auto svgNode = SvgStop::Create();
    auto svgStop = AceType::DynamicCast<SvgStop>(svgNode);
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor(), Color::BLACK);

    /* *
     * @tc.steps: step2. parse stop-color
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stop-color", "rgba(0,49,83,255)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF003153);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "rgb(0,49,83)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF003153);

    /* *
     * @tc.steps: step3. parse stopcolor
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stopColor", "rgb(49,49,83)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF313153);

    /* *
     * @tc.steps: step4. parse stopOpacity
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stopOpacity", "0.0");
    EXPECT_EQ(svgStop->GetGradientColor().GetOpacity(), 0.0);

    /* *
     * @tc.steps: step5. parse properties that do not belong to SvgStop
     * @tc.expected: The property is parse unsuccessfully
     */
    bool parseResult = svgStop->ParseAndSetSpecializedAttr("strokeLinecap", "butt");
    EXPECT_FALSE(parseResult);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseFeTest001
 * @tc.desc: parse fe label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeTest001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create fe node
     */
    auto svgFe = AccessibilityManager::MakeRefPtr<SvgFe>();

    svgFe->ParseAndSetSpecializedAttr("color-interpolation-filters", "auto");
    EXPECT_EQ(svgFe->feAttr_.colorInterpolationType, SvgColorInterpolationType::AUTO);

    svgFe->ParseAndSetSpecializedAttr("color-interpolation-filters", "SRGB");
    EXPECT_EQ(svgFe->feAttr_.colorInterpolationType, SvgColorInterpolationType::AUTO);

    svgFe->ParseAndSetSpecializedAttr("height", "1px");
    EXPECT_EQ(svgFe->feAttr_.height, 1.0_px);

    svgFe->ParseAndSetSpecializedAttr("width", "1px");
    EXPECT_EQ(svgFe->feAttr_.width, 1.0_px);

    svgFe->ParseAndSetSpecializedAttr("x", "1px");
    EXPECT_EQ(svgFe->feAttr_.x, 1.0_px);

    svgFe->ParseAndSetSpecializedAttr("y", "1px");
    EXPECT_EQ(svgFe->feAttr_.y, 1.0_px);

    bool parseResult = svgFe->ParseAndSetSpecializedAttr("strokeLinecap", "butt");
    EXPECT_FALSE(parseResult);

    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
    svgFe->GetImageFilter(imageFilter, colorInterpolationType, resultHash);
    EXPECT_EQ(svgFe->effectFilterArea_.Top(), 0.0f);
    EXPECT_EQ(svgFe->effectFilterArea_.Left(), 0.0f);
}

/**
 * @tc.name: ParseFeBlenderTest001
 * @tc.desc: test fe blender
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeBlenderTest001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create feBlend node
     */
    auto svgFeBlend = AccessibilityManager::MakeRefPtr<SvgFeBlend>();

    svgFeBlend->ParseAndSetSpecializedAttr("in2", "undefine");
    SvgFeBlendAttribute svgFeBlendDeclaration = svgFeBlend->feBlendAttr_;
    EXPECT_EQ(svgFeBlendDeclaration.in2.id, "undefine");
    svgFeBlend->ParseAndSetSpecializedAttr("mode", "undefine");
    svgFeBlendDeclaration = svgFeBlend->feBlendAttr_;
    EXPECT_EQ(svgFeBlendDeclaration.blendMode, SvgFeBlendMode::NORMAL);

    RSBlendMode rsBlendMode = svgFeBlend->GetBlendMode(SvgFeBlendMode::NORMAL);
    EXPECT_EQ(rsBlendMode, RSBlendMode::SRC_OVER);
    rsBlendMode = svgFeBlend->GetBlendMode(SvgFeBlendMode::MULTIPLY);
    EXPECT_EQ(rsBlendMode, RSBlendMode::MULTIPLY);
    rsBlendMode = svgFeBlend->GetBlendMode(SvgFeBlendMode::SCREEN);
    EXPECT_EQ(rsBlendMode, RSBlendMode::SCREEN);
    rsBlendMode = svgFeBlend->GetBlendMode(SvgFeBlendMode::DARKEN);
    EXPECT_EQ(rsBlendMode, RSBlendMode::DARKEN);
    rsBlendMode = svgFeBlend->GetBlendMode(SvgFeBlendMode::LIGHTEN);
    EXPECT_EQ(rsBlendMode, RSBlendMode::LIGHTEN);
    rsBlendMode = svgFeBlend->GetBlendMode(static_cast<SvgFeBlendMode>(8));
    EXPECT_EQ(rsBlendMode, RSBlendMode::SRC_OVER);
}

/**
 * @tc.name: ParseFeColorMatrixTest001
 * @tc.desc: parse FeColorMatrix label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeColorMatrixTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FE_COLOR_MATRIX.c_str(), FE_COLOR_MATRIX.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    // filter is first child in svg
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    // the first child in filter
    auto svgFeColorMatrix1 = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeColorMatrix1, nullptr);
    svgFeColorMatrix1->OnInitStyle();
    auto feColorDeclaration1 = svgFeColorMatrix1->matrixAttr_;
    EXPECT_EQ(feColorDeclaration1.type, SvgFeColorMatrixType::MATRIX);
    // the second child in filter
    auto svgFeColorMatrix2 = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(1));
    EXPECT_NE(svgFeColorMatrix2, nullptr);
    svgFeColorMatrix2->OnInitStyle();
    auto feColorDeclaration2 = svgFeColorMatrix2->matrixAttr_;
    EXPECT_EQ(feColorDeclaration2.type, SvgFeColorMatrixType::SATURATE);
    // the third child in filter
    auto svgFeColorMatrix3 = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(2));
    EXPECT_NE(svgFeColorMatrix3, nullptr);
    svgFeColorMatrix3->OnInitStyle();
    auto feColorDeclaration3 = svgFeColorMatrix3->matrixAttr_;
    EXPECT_EQ(feColorDeclaration3.type, SvgFeColorMatrixType::HUE_ROTATE);
    // the fourth child in filter
    auto svgFeColorMatrix4 = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(3));
    EXPECT_NE(svgFeColorMatrix4, nullptr);
    svgFeColorMatrix4->OnInitStyle();
    auto feColorDeclaration4 = svgFeColorMatrix4->matrixAttr_;
    EXPECT_EQ(feColorDeclaration4.type, SvgFeColorMatrixType::LUMINACE_TO_ALPHA);
    // the fifth child in filter
    auto svgFeColorMatrix5 = AceType::DynamicCast<SvgFeColorMatrix>(svgFilter->children_.at(4));
    EXPECT_NE(svgFeColorMatrix5, nullptr);
    svgFeColorMatrix5->OnInitStyle();
    auto feColorDeclaration5 = svgFeColorMatrix5->matrixAttr_;
    EXPECT_EQ(feColorDeclaration5.type, SvgFeColorMatrixType::MATRIX);
}

/**
 * @tc.name: ParseFeCompositeTest001
 * @tc.desc: parse Composite label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeCompositeTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FE_COMPOSITE.c_str(), FE_COMPOSITE.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    // filter is first child in svg
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    // the first child in filter
    auto svgFeComposite1 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeComposite1, nullptr);
    svgFeComposite1->ParseAndSetSpecializedAttr("operator", "undefine");
    SvgFeCompositeAttribute svgFeCompositeDeclaration = svgFeComposite1->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_OVER);

    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType srcColor = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType currentColor = SvgColorInterpolationType::LINEAR_RGB;
    svgFeComposite1->feCompositeAttr_.operatorType = static_cast<SvgFeOperatorType>(8);
    svgFeComposite1->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    RSBlendMode rsBlendMode = svgFeComposite1->BlendModeForOperator(SvgFeOperatorType::FE_ARITHMETIC);
    EXPECT_EQ(rsBlendMode, RSBlendMode::SRC_OVER);

    auto svgFeComposite5 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(4));
    EXPECT_NE(svgFeComposite5, nullptr);
    svgFeComposite5->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite5->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_LIGHTER);

    auto svgFeComposite6 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(5));
    EXPECT_NE(svgFeComposite6, nullptr);
    svgFeComposite6->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite6->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_OUT);

    auto svgFeComposite7 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(6));
    EXPECT_NE(svgFeComposite7, nullptr);
    svgFeComposite7->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite7->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_XOR);

    auto svgFeComposite8 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(7));
    EXPECT_NE(svgFeComposite8, nullptr);
    svgFeComposite8->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite8->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_OVER);
}

/**
 * @tc.name: ParseFeCompositeTest002
 * @tc.desc: parse Composite label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeCompositeTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FE_COMPOSITE.c_str(), FE_COMPOSITE.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    // filter is first child in svg
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);

    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType srcColor = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType currentColor = SvgColorInterpolationType::LINEAR_RGB;
    auto svgFeComposite5 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(4));
    EXPECT_NE(svgFeComposite5, nullptr);
    svgFeComposite5->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    SvgFeCompositeAttribute svgFeCompositeDeclaration = svgFeComposite5->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_LIGHTER);

    auto svgFeComposite6 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(5));
    EXPECT_NE(svgFeComposite6, nullptr);
    svgFeComposite6->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite6->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_OUT);

    auto svgFeComposite7 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(6));
    EXPECT_NE(svgFeComposite7, nullptr);
    svgFeComposite7->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite7->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_XOR);

    auto svgFeComposite8 = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(7));
    EXPECT_NE(svgFeComposite8, nullptr);
    svgFeComposite8->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash);
    svgFeCompositeDeclaration = svgFeComposite8->feCompositeAttr_;
    EXPECT_EQ(svgFeCompositeDeclaration.operatorType, SvgFeOperatorType::FE_OVER);
}

HWTEST_F(ParseTestTwoNg, ParseFeGaussianBlurTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FE_GAUSSIAN_BLUR.c_str(), FE_GAUSSIAN_BLUR.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    // filter is first child in svg
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    // the first child in filter
    auto svgFeGaussianBlur1 = AceType::DynamicCast<SvgFeGaussianBlur>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeGaussianBlur1, nullptr);

    auto bResult = svgFeGaussianBlur1->ParseAndSetSpecializedAttr("stddeviation", "");
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: ParseFeOffsetTest001
 * @tc.desc: test fe offset
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeOffsetTest001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create feOffset node
     */
    auto svgFeOffset = AccessibilityManager::MakeRefPtr<SvgFeOffset>();

    svgFeOffset->ParseAndSetSpecializedAttr("dx", "5");
    auto svgFeOffsetAttribute = svgFeOffset->feOffsetAttr_;
    EXPECT_EQ(svgFeOffsetAttribute.dx, Dimension(5));

    auto bResult = svgFeOffset->ParseAndSetSpecializedAttr("undefine", "undefine");
    EXPECT_FALSE(bResult);
}

/**
 * @tc.name: ParseMaskTest001
 * @tc.desc: test Mask
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseMaskTest001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create svgMask node
     */
    auto svgMask = AceType::DynamicCast<SvgMask>(SvgMask::Create());
    EXPECT_NE(svgMask, nullptr);

    svgMask->ParseAndSetSpecializedAttr("y", "5");
    auto svgMaskAttribute = svgMask->maskAttr_;
    EXPECT_EQ(svgMaskAttribute.y, Dimension(5));
    auto attrValue = svgMask->ParseUnitsAttr(Dimension(1.0, DimensionUnit::PERCENT), 2.0);
    EXPECT_EQ(attrValue, 2.0);
    attrValue = svgMask->ParseUnitsAttr(Dimension(1.0), 2.0);
    EXPECT_EQ(attrValue, 2.0);

    svgMask->isDefaultMaskUnits_ = false;
    attrValue = svgMask->ParseUnitsAttr(Dimension(1.0), 2.0);
    EXPECT_EQ(attrValue, 1.0);
    attrValue = svgMask->ParseUnitsAttr(Dimension(1.0, DimensionUnit::PERCENT), 2.0);
    EXPECT_EQ(attrValue, 2.0);
}


/**
 * @tc.name: ParseMaskTest001
 * @tc.desc: test Mask
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseMaskTest002, TestSize.Level1)
{
    auto svgMask = AceType::DynamicCast<SvgMask>(SvgMask::Create());
    EXPECT_NE(svgMask, nullptr);
    RSCanvas canvas;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    svgMask->OnMaskEffect(canvas, context);

    SvgLengthScaleRule lengthRule;
    svgMask->smoothEdge_ = false;

    RefPtr<SvgNode> svgNode1 = nullptr;
    RefPtr<SvgNode> svgNode2 = SvgPattern::Create();
    svgNode2->drawTraversed_ = false;
    RefPtr<SvgNode> svgNode3 = SvgPattern::Create();
    svgNode3->drawTraversed_ = true;
    svgMask->children_.emplace_back(svgNode1);
    svgMask->children_.emplace_back(svgNode2);
    svgMask->children_.emplace_back(svgNode3);

    svgMask->DrawChildren(canvas, lengthRule);
    EXPECT_TRUE(lengthRule.UseFillColor());

    svgMask->smoothEdge_ = true;
    svgMask->DrawChildren(canvas, lengthRule);
    EXPECT_TRUE(lengthRule.UseFillColor());
}

/**
 * @tc.name: ParseMaskTest001
 * @tc.desc: test Mask
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseMaskTest003, TestSize.Level1)
{
    auto svgMask = AceType::DynamicCast<SvgMask>(SvgMask::Create());
    EXPECT_NE(svgMask, nullptr);
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto result = svgMask->ParseAndSetSpecializedAttr("maskunits", "objectBoundingBox");
    EXPECT_TRUE(result);
    result = svgMask->ParseAndSetSpecializedAttr("maskunits", "objectBoundingBox222");
    EXPECT_TRUE(result);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}


/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFilterTest003, TestSize.Level1)
{
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    auto svgStream = SkMemoryStream::MakeCopy(FE_COLOR_MATRIX.c_str(), FE_COLOR_MATRIX.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);

    svgFilter->children_.at(0) = nullptr;
    svgFilter->OnAsPaint();
    auto nodeFe1 = AceType::DynamicCast<SvgFe>(svgFilter->children_.at(0));
    auto nodeFe2 = AceType::DynamicCast<SvgFe>(svgFilter->children_.at(1));
    EXPECT_EQ(nodeFe1, nullptr);
    EXPECT_NE(nodeFe2, nullptr);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFilterTest004, TestSize.Level1)
{
    auto svgFilter = AceType::DynamicCast<SvgFilter>(SvgFilter::Create());
    EXPECT_NE(svgFilter, nullptr);
    RSCanvas canvas;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    float useOffsetX = 10.f;
    float useOffsetY = 10.f;

    RefPtr<SvgNode> svgNode1 = nullptr;
    RefPtr<SvgNode> svgNode2 = SvgPattern::Create();
    svgFilter->children_.emplace_back(svgNode1);
    svgFilter->children_.emplace_back(svgNode2);
    svgFilter->OnFilterEffect(canvas, context, useOffsetX, useOffsetY);
    EXPECT_TRUE(context.UseFillColor());
}

/**
 * @tc.name: ParseRectTest005
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseRectTest005, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(RECT_SVG_LABEL4.c_str(), RECT_SVG_LABEL4.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value not is 0
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgRect->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    auto rectDeclaration = svgRect->rectAttr_;
    EXPECT_NE(rectDeclaration.rx.Value(), 0);
}

/**
 * @tc.name: ParseUseTest003
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseUseTest003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(USE_SVG_LABEL.c_str(), USE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::GREEN);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    auto svgUse = AceType::DynamicCast<SvgUse>(svg->children_.at(INDEX_ONE));
    EXPECT_NE(svgUse, nullptr);

    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    svgUse->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svgUse->useAttr_.x = Dimension(1.0, DimensionUnit::PERCENT);
    svgUse->useAttr_.y = Dimension(1.0, DimensionUnit::PERCENT);
    svgUse->OnDraw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    svgUse->useAttr_.x = Dimension(0.0, DimensionUnit::PERCENT);
    svgUse->OnDraw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);
    svgUse->attributes_.href = "";
    svgUse->OnDraw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    auto bResult = svgUse->ParseAndSetSpecializedAttr("viewBox", "");
    EXPECT_TRUE(bResult);

    svgUse->ParseAndSetSpecializedAttr("viewBox", "0 0 0 10");
    EXPECT_EQ(svgUse->useAttr_.viewBox.Height(), 10.0);
    svgUse->ParseAndSetSpecializedAttr("viewBox", "0 0 10");
    EXPECT_EQ(svgUse->useAttr_.viewBox.Height(), 10.0);

    bResult = svgUse->ParseAndSetSpecializedAttr("viewbox", "");
    EXPECT_TRUE(bResult);

    svgUse->ParseAndSetSpecializedAttr("viewbox", "0 0 24");
    EXPECT_EQ(svgUse->useAttr_.viewBox.Width(), 0.0);
    svgUse->ParseAndSetSpecializedAttr("viewbox", "0 0 10 10");
    EXPECT_EQ(svgUse->useAttr_.viewBox.Width(), 10.0);

    bResult = svgUse->ParseAndSetSpecializedAttr("undefine", "");
    EXPECT_FALSE(bResult);
}

/**
 * @tc.name: ParseSvgTest001
 * @tc.desc: parse svg label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseSvgTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(USE_SVG_LABEL.c_str(), USE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::GREEN);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);

    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));

    svg->svgAttr_.width = Dimension(1.0);
    svg->svgAttr_.height = Dimension(-1.0);
    svg->AdjustContentAreaByViewBox(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svg->svgAttr_.height = Dimension(1.0);
    svg->svgAttr_.width = Dimension(-1.0);
    svg->AdjustContentAreaByViewBox(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svg->svgAttr_.height = Dimension(-1.0);
    svg->AdjustContentAreaByViewBox(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svg->svgAttr_.viewBox.height_ = 0.0;
    svg->AdjustContentAreaByViewBox(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    svg->svgAttr_.viewBox.width_ = 0.0;
    svg->AdjustContentAreaByViewBox(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));

    auto bResult = svg->ParseAndSetSpecializedAttr("viewBox", "");
    EXPECT_TRUE(bResult);
    svg->ParseAndSetSpecializedAttr("viewBox", "0 0 10");
    EXPECT_EQ(svg->GetViewBox().Height(), 0.0);
    svg->ParseAndSetSpecializedAttr("viewBox", "0 0 0 10");
    EXPECT_EQ(svg->GetViewBox().Height(), 10.0);
    svg->ParseAndSetSpecializedAttr("viewbox", "0 0 10");
    EXPECT_EQ(svg->GetViewBox().Width(), 0.0);
    svg->ParseAndSetSpecializedAttr("viewbox", "0 0 10 10");
    EXPECT_EQ(svg->GetViewBox().Width(), 10.0);
    bResult = svg->ParseAndSetSpecializedAttr("viewbox", "");
    EXPECT_TRUE(bResult);
}

/**
 * @tc.name: ParsePathTest001
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePathTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATH_SVG_LABEL1.c_str(), PATH_SVG_LABEL1.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    auto svgPath = AceType::DynamicCast<SvgPath>(svg->children_.at(0));
    EXPECT_NE(svgPath, nullptr);

    svgPath->attributes_.fillState.SetFillRule("evenodd");
    svgPath->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_TRUE(svgPath->attributes_.fillState.IsEvenodd());

    svgPath->d_ = "";
    svgPath->AsPath(Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_TRUE(svgPath->d_.empty());
}

/**
 * @tc.name: ParseFeTest002
 * @tc.desc: Test SvgFe Method
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFeTest002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. call MakeRefPtr<SvgFe>()
     * @tc.expected: Execute function return value not is nullptr
     */
    auto svgFe = AccessibilityManager::MakeRefPtr<SvgFe>();
    EXPECT_NE(svgFe, nullptr);

    /* *
     * @tc.steps: step2. call MakeImageFilter
     * @tc.expected: Execute function return value not is nullptr
     */
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgFeIn in = { .in = SvgFeInType::SOURCE_GRAPHIC, .id = "test" };

    in.in = SvgFeInType::PRIMITIVE;
    auto value = svgFe->MakeImageFilter(in, imageFilter, resultHash);
    EXPECT_EQ(value, nullptr);

    /* *
     * @tc.steps: step3. call RegisterResult
     * @tc.expected: Register Successfully
     */
    svgFe->RegisterResult("test", imageFilter, resultHash);
    EXPECT_TRUE(resultHash.find("test") != resultHash.end());

    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
    svgFe->feAttr_.in.in = SvgFeInType::SOURCE_GRAPHIC;
    svgFe->GetImageFilter(imageFilter, colorInterpolationType, resultHash);

    colorInterpolationType = SvgColorInterpolationType::LINEAR_RGB;
    SvgColorInterpolationType srcColor = SvgColorInterpolationType::LINEAR_RGB;
    svgFe->ConverImageFilterColor(imageFilter, srcColor, colorInterpolationType);

    value = svgFe->MakeImageFilter(in, imageFilter, resultHash);
    EXPECT_EQ(value, nullptr);
}

/**
 * @tc.name: ParsePatternTest001
 * @tc.desc: parse pattern label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParsePatternTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATTERN_SVG_LABEL.c_str(), PATTERN_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);

    auto svgPattern = AceType::DynamicCast<SvgPattern>(svgDefs->children_.at(0));
    EXPECT_NE(svgPattern, nullptr);
    auto patternDeclaration = svgPattern->patternAttr_;

    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));

    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    svgPattern->OnDrawTraversedBefore(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);

    svgPattern->ParseAndSetSpecializedAttr("viewbox", "");
    svgPattern->ParseAndSetSpecializedAttr("viewbox", "0 0 24");
    EXPECT_EQ(patternDeclaration.viewBox.Width(), 10.0);
    EXPECT_EQ(patternDeclaration.viewBox.Height(), 10.0);
}

/**
 * @tc.name: ParseFilterTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFilterTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(COMPOSITE_SVG_LABEL.c_str(), COMPOSITE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);

    auto svgFeComposite = AceType::DynamicCast<SvgFeComposite>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeComposite, nullptr);

    svgFilter->filterAttr_.height = Dimension(1.0, DimensionUnit::PX);
    svgFilter->filterAttr_.width = Dimension(1.0, DimensionUnit::PX);
    svgFilter->filterAttr_.x = Dimension(1.0, DimensionUnit::PX);
    svgFilter->filterAttr_.y = Dimension(1.0, DimensionUnit::PX);
    svgFilter->OnAsPaint();
    EXPECT_EQ(svgFeComposite->effectFilterArea_.x_, 1.0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.y_, 1.0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.width_, 1.0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.height_, 1.0);

    svgFilter->filterAttr_.height = Dimension(1.0, DimensionUnit::PERCENT);
    svgFilter->filterAttr_.width = Dimension(1.0, DimensionUnit::PERCENT);
    svgFilter->filterAttr_.x = Dimension(1.0, DimensionUnit::PERCENT);
    svgFilter->filterAttr_.y = Dimension(1.0, DimensionUnit::PERCENT);
    svgFilter->OnAsPaint();
    EXPECT_EQ(svgFeComposite->effectFilterArea_.x_, 0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.y_, 0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.width_, 0);
    EXPECT_EQ(svgFeComposite->effectFilterArea_.height_, 0);
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseFilterTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(FE_COLOR_MATRIX.c_str(), FE_COLOR_MATRIX.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_NE(svg, nullptr);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);

    svgFilter->children_.at(0) = nullptr;
    svgFilter->OnAsPaint();
    auto nodeFe1 = AceType::DynamicCast<SvgFe>(svgFilter->children_.at(0));
    auto nodeFe2 = AceType::DynamicCast<SvgFe>(svgFilter->children_.at(1));
    EXPECT_EQ(nodeFe1, nullptr);
    EXPECT_NE(nodeFe2, nullptr);
}

/**
 * @tc.name: ParseNodeTest006
 * @tc.desc: Test SvgNode SetAttr Parameters
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest006, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    svgNode->SetAttr("fill", "url(#test)");
    EXPECT_EQ(svgNode->GetBaseAttributes().fillState.GetHref(), "test");

    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);

    svgNode->SetAttr("stroke", "#test");

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);

    svgNode->SetAttr("stroke", "url(#test)");

    svgNode->InitStyle(SvgBaseAttribute());
    EXPECT_EQ(svgNode->GetBaseAttributes().strokeState.GetHref(), "test");
}

/**
 * @tc.name: ParseNodeTest007
 * @tc.desc: Test SvgNode SetAttr Parameters
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseNodeTest007, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(GRADIENT_SVG_LINEAR.c_str(), GRADIENT_SVG_LINEAR.length());
    EXPECT_NE(svgStream, nullptr);

    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);

    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);

    svgDom->root_->SetAttr("fill", "url(#grad1)");
    svgDom->root_->SetAttr("stroke", "url(#grad1)");
    svgDom->root_->InitStyle(SvgBaseAttribute());
    EXPECT_EQ(svgDom->root_->GetBaseAttributes().strokeState.GetHref(), "grad1");
    EXPECT_EQ(svgDom->root_->GetBaseAttributes().fillState.GetHref(), "grad1");
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, ParseStyleTest001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. call ParseCssStyle
     * @tc.expected: Execute function return value false
     */
    std::string str;
    PushAttr callback = [&str](const std::string& key, const std::pair<std::string, std::string>& value) { str = key; };
    SvgStyle::ParseCssStyle("", callback);
    EXPECT_TRUE(str.empty());

    SvgStyle::ParseCssStyle("body {font-style: oblique;}.normal {font-style: normal;}", callback);
    EXPECT_FALSE(str.empty());
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform001, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "asd";
    paramVec.emplace_back("213");
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "asd";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform002, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "matrix";
    paramVec.emplace_back("213");
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "matrix";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    paramVec1.emplace_back("215333");
    paramVec1.emplace_back("213733");
    paramVec1.emplace_back("213363");
    paramVec1.emplace_back("217333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform003, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "rotate";
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "rotate";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    paramVec1.emplace_back("215333");
    paramVec1.emplace_back("213733");
    paramVec1.emplace_back("213363");
    paramVec1.emplace_back("217333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    NG::TransformInfo info2;
    std::vector<std::string> paramVec2;
    info2.funcType = "rotate";
    paramVec2.emplace_back("213");
    paramVec2.emplace_back("21333");
    paramVec2.emplace_back("215333");
    info2.paramVec = paramVec2;
    transformVec.emplace_back(info2);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform004, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "scale";
    paramVec.emplace_back("213");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "scale";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    NG::TransformInfo info2;
    std::vector<std::string> paramVec2;
    info2.funcType = "scale";
    paramVec2.emplace_back("213");
    paramVec2.emplace_back("21333");
    paramVec2.emplace_back("215333");
    info2.paramVec = paramVec2;
    transformVec.emplace_back(info2);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform005, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "skewX";
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "skewX";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    paramVec1.emplace_back("215333");
    paramVec1.emplace_back("213733");
    paramVec1.emplace_back("213363");
    paramVec1.emplace_back("217333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform006, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "skewY";
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "skewY";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    paramVec1.emplace_back("215333");
    paramVec1.emplace_back("213733");
    paramVec1.emplace_back("213363");
    paramVec1.emplace_back("217333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform007, TestSize.Level1)
{
    // NG::NGSvgTransform::ApplyTransformPivot
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    std::vector<std::string> paramVec;
    info.funcType = "translate";
    paramVec.emplace_back("21333");
    info.paramVec = paramVec;
    transformVec.emplace_back(info);

    NG::TransformInfo info1;
    std::vector<std::string> paramVec1;
    info1.funcType = "translate";
    paramVec1.emplace_back("213");
    paramVec1.emplace_back("21333");
    paramVec1.emplace_back("215333");
    paramVec1.emplace_back("213733");
    paramVec1.emplace_back("213363");
    paramVec1.emplace_back("217333");
    info1.paramVec = paramVec1;
    transformVec.emplace_back(info1);

    NG::TransformInfo info2;
    std::vector<std::string> paramVec2;
    info2.funcType = "translate";
    paramVec2.emplace_back("213");
    paramVec2.emplace_back("21333");
    paramVec2.emplace_back("215333");
    info2.paramVec = paramVec2;
    transformVec.emplace_back(info2);

    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Offset offset;
    auto result = NGSvgTransform::CreateMatrix4(transformVec, offset, rule);
    EXPECT_EQ(result.Get(1, 0), 0);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform008, TestSize.Level1)
{
    std::vector<std::string> paramVec;
    RSMatrix matrix;

    auto result = NGSvgTransform::CreateTranslate(paramVec, matrix);
    EXPECT_FALSE(result);
    paramVec.emplace_back("2153353");
    result = NGSvgTransform::CreateTranslate(paramVec, matrix);
    EXPECT_TRUE(result);

    paramVec.emplace_back("21533333");
    result = NGSvgTransform::CreateTranslate(paramVec, matrix);
    EXPECT_TRUE(result);

    paramVec.emplace_back("21536633");
    result = NGSvgTransform::CreateTranslate(paramVec, matrix);
    EXPECT_FALSE(result);

    paramVec.emplace_back("2153600633");
    result = NGSvgTransform::CreateTranslate(paramVec, matrix);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform009, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    std::vector<std::string> paramVec;
    Matrix4 matrix;

    std::string funcType = "asd";
    auto result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "matrix";
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "matrix";
    paramVec.clear();
    paramVec.emplace_back("1");
    paramVec.emplace_back("2");
    paramVec.emplace_back("3");
    paramVec.emplace_back("4");
    paramVec.emplace_back("5");
    paramVec.emplace_back("6");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "rotate";
    paramVec.clear();
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "rotate";
    paramVec.clear();
    paramVec.emplace_back("1");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "scale";
    paramVec.clear();
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "scale";
    paramVec.clear();
    paramVec.emplace_back("1");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "scale";
    paramVec.clear();
    paramVec.emplace_back("1");
    paramVec.emplace_back("2");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform010, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    std::vector<std::string> paramVec;
    Matrix4 matrix;
    std::string funcType = "asd";

    funcType = "skewX";
    paramVec.clear();
    auto result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "skewX";
    paramVec.clear();
    paramVec.emplace_back("1");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "skewY";
    paramVec.clear();
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "skewY";
    paramVec.clear();
    paramVec.emplace_back("1");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "translate";
    paramVec.clear();
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_FALSE(result);

    funcType = "translate";
    paramVec.clear();
    paramVec.emplace_back("1");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);

    funcType = "translate";
    paramVec.clear();
    paramVec.emplace_back("1");
    paramVec.emplace_back("2");
    result = NGSvgTransform::UpdateSingleTransform(funcType, paramVec, matrix, rule);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgTransform011, TestSize.Level1)
{
    Matrix4 matrix;
    Offset offset;
    std::string funcType = "asd";
    NGSvgTransform::ApplyTransformPivot(funcType, offset, matrix);
    EXPECT_EQ(funcType, "asd");
}

/**
 * @tc.name: ParseStyleTest001
 * @tc.desc: parse use label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestTwoNg, SvgClipPath001, TestSize.Level1)
{
    auto clipPath = AceType::DynamicCast<SvgClipPath>(SvgClipPath::Create());
    EXPECT_NE(clipPath, nullptr);

    Testing::MockCanvas rSCanvas;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);

    clipPath->OnClipEffect(rSCanvas, context);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    clipPath->SetContext(svgContext);
    clipPath->OnClipEffect(rSCanvas, context);

    SvgLengthScaleRule clipPathRule = context.BuildScaleRule(clipPath->attributes_.clipState.GetClipPathUnits());
    auto result = clipPath->AsPath(clipPathRule);
    EXPECT_TRUE(result.BuildFromSVGString(""));
}
} // namespace OHOS::Ace::NG

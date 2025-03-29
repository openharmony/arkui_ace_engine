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
#include "core/components_ng/svg/parse/svg_use.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

const std::string TRANSFORM_RECT_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"1\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate(34.56)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_SCALE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"1\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"scale(0.8, 0.8)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_SKEW_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"1\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"skewX(34.56) skewY(98.76)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_TRANSLATE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"1\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"translate(34.56)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_MATRIX_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"1\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"matrix(1,0,0.577,1,0,0)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_INVALID_EMPTY_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"16px\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate()\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_INVALID_PARA_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"16px\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate(abc)\" "
    "transform-origin=\"123.45px 99.99%\"/></svg>";

const std::string TRANSFORM_ORIGIN_INVALID_PARA_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"16px\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate(34.56)\" "
    "transform-origin=\"abcd\"/></svg>";

const std::string TRANSFORM_ORIGIN_INVALID_EMPTY_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"16px\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate(34.56)\" "
    "transform-origin=\"\"/></svg>";

const std::string TRANSFORM_ORIGIN_INVALID_SPACE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"60px\" y=\"200px\" width=\"50px\" height=\"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" "
    "stroke-width=\"16px\" stroke-opacity=\"0.3\" id=\"circleId\" transform=\"rotate(34.56)\" "
    "transform-origin=\"   \"/></svg>";

constexpr float IMAGE_COMPONENT_WIDTH = 100.0f;
constexpr float IMAGE_COMPONENT_HEIGHT = 100.0f;
} // namespace

class SvgTransformTestNg : public testing::Test {
public:
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

void SvgTransformTestNg::CallBack(Testing::MockCanvas& rSCanvas)
{
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DrawPath(_)).Times(AtLeast(1));
}

/**
 * @tc.name: ParseTransformTestRect
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformTestRect, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_RECT_SVG_LABEL.c_str(), TRANSFORM_RECT_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    NG::TransformInfo element;
    element = attributes.transformVec[0];
    EXPECT_EQ(element.funcType, "rotate");
    EXPECT_EQ(element.paramVec[0], "34.56");
}

/**
 * @tc.name: ParseTransformTestScale
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformTestScale, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_SCALE_SVG_LABEL.c_str(), TRANSFORM_SCALE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    NG::TransformInfo element;
    element = attributes.transformVec[0];
    EXPECT_EQ(element.funcType, "scale");
    EXPECT_EQ(element.paramVec[0], "0.8");
    EXPECT_EQ(element.paramVec[1], "0.8");
}

/**
 * @tc.name: ParseTransformTestSkew
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformTestSkew, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_SKEW_SVG_LABEL.c_str(), TRANSFORM_SKEW_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    NG::TransformInfo element;
    element = attributes.transformVec[0];
    EXPECT_EQ(element.funcType, "skewX");
    EXPECT_EQ(element.paramVec[0], "34.56");

    NG::TransformInfo element2;
    element2 = attributes.transformVec[1];
    EXPECT_EQ(element2.funcType, "skewY");
    EXPECT_EQ(element2.paramVec[0], "98.76");
}

/**
 * @tc.name: ParseTransformTestTranslate
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformTestTranslate, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(TRANSFORM_TRANSLATE_SVG_LABEL.c_str(), TRANSFORM_TRANSLATE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    NG::TransformInfo element;
    element = attributes.transformVec[0];
    EXPECT_EQ(element.funcType, "translate");
    EXPECT_EQ(element.paramVec[0], "34.56");
}

/**
 * @tc.name: ParseTransformTestMatrix
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformTestMatrix, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_MATRIX_SVG_LABEL.c_str(), TRANSFORM_MATRIX_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    NG::TransformInfo element;
    element = attributes.transformVec[0];
    EXPECT_EQ(element.funcType, "matrix");
    EXPECT_EQ(element.paramVec[0], "1");
    EXPECT_EQ(element.paramVec[1], "0");
    EXPECT_EQ(element.paramVec[2], "0.577");
    EXPECT_EQ(element.paramVec[3], "1");
    EXPECT_EQ(element.paramVec[4], "0");
    EXPECT_EQ(element.paramVec[5], "0");
}

/**
 * @tc.name: ParseTransformInvalidTest001
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformInvalidTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(TRANSFORM_INVALID_EMPTY_SVG_LABEL.c_str(), TRANSFORM_INVALID_EMPTY_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    EXPECT_EQ(0, attributes.transformVec.size());
}

/**
 * @tc.name: ParseTransformInvalidTest002
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformInvalidTest002, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(TRANSFORM_INVALID_PARA_SVG_LABEL.c_str(), TRANSFORM_INVALID_PARA_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform function vector from the shape.
     * @tc.expected: transform function vector value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    EXPECT_EQ(0, attributes.transformVec.size());
}

/**
 * @tc.name: ParseTransformOriginTest001
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformOriginTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_RECT_SVG_LABEL.c_str(), TRANSFORM_RECT_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform-origin value from the shape.
     * @tc.expected: transform-origin value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;

    EXPECT_EQ(Dimension(123.45_px), attributes.transformOrigin.first);
    EXPECT_EQ(Dimension(0.9999_pct), attributes.transformOrigin.second);
}

/**
 * @tc.name: ParseTransformOriginInvalidTest001
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformOriginInvalidTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(
        TRANSFORM_ORIGIN_INVALID_PARA_SVG_LABEL.c_str(), TRANSFORM_ORIGIN_INVALID_PARA_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform-origin value from the shape.
     * @tc.expected: transform-origin value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    EXPECT_EQ(Dimension(0.0f), attributes.transformOrigin.first);
    EXPECT_EQ(Dimension(0.0_px), attributes.transformOrigin.second);
}

/**
 * @tc.name: ParseTransformOriginInvalidTest002
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, ParseTransformOriginInvalidTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(
        TRANSFORM_ORIGIN_INVALID_EMPTY_SVG_LABEL.c_str(), TRANSFORM_ORIGIN_INVALID_EMPTY_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    Testing::MockCanvas rSCanvas;
    CallBack(rSCanvas);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    EXPECT_NE(svgDom, nullptr);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);

    /* *
     * @tc.steps: step1. get shape from svg.
     * @tc.expected: shape is Effective.
     */
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    svgDom->root_->SetSmoothEdge(1);
    svgDom->root_->Draw(rSCanvas, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::BLACK);

    /* *
     * @tc.steps: step2. get transform-origin value from the shape.
     * @tc.expected: transform-origin value is equal to svg source.
     */
    auto attributes = svgRect->attributes_;
    std::vector<NG::TransformInfo> transformVec = attributes.transformVec;
    EXPECT_EQ(Dimension(0.0f), attributes.transformOrigin.first);
    EXPECT_EQ(Dimension(0.0_px), attributes.transformOrigin.second);
}

/**
 * @tc.name: ParseTransformOriginInvalidTest002
 * @tc.desc: parse transform-origin label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgFeOffsetTest001, TestSize.Level1)
{
    auto feOffset = AceType::DynamicCast<SvgFeOffset>(SvgFeOffset::Create());
    EXPECT_NE(feOffset, nullptr);
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType srcColor = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType currentColor = SvgColorInterpolationType::LINEAR_RGB;
    feOffset->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    feOffset->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash, true);

    feOffset->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    feOffset->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash, true);
    EXPECT_NE(imageFilter, nullptr);
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgFeBlendTest001, TestSize.Level1)
{
    auto svgFeBlend = AceType::DynamicCast<SvgFeBlend>(SvgFeBlend::Create());
    EXPECT_NE(svgFeBlend, nullptr);
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType srcColor = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType currentColor = SvgColorInterpolationType::LINEAR_RGB;
    svgFeBlend->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    svgFeBlend->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash, true);

    svgFeBlend->filterContext_.primitiveRule_.lengthScaleUnit_ = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    svgFeBlend->OnAsImageFilter(imageFilter, srcColor, currentColor, resultHash, true);
    EXPECT_NE(imageFilter, nullptr);
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgLineTest001, TestSize.Level1)
{
    auto svgLine = AceType::DynamicCast<SvgLine>(SvgLine::Create());
    EXPECT_NE(svgLine, nullptr);
    svgLine->path_ = std::nullopt;
    SvgLengthScaleRule rule;
    Rect rect(0, 10, 20, 20);
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    RSRecordingPath path;
    svgLine->path_ = path;
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);
    EXPECT_TRUE(rule.UseFillColor());
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgRectTest001, TestSize.Level1)
{
    auto svgLine = AceType::DynamicCast<SvgRect>(SvgRect::Create());
    EXPECT_NE(svgLine, nullptr);
    svgLine->path_ = std::nullopt;
    SvgLengthScaleRule rule;
    Rect rect(0, 10, 20, 20);
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    RSRecordingPath path;
    svgLine->path_ = path;
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);
    EXPECT_TRUE(rule.UseFillColor());
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgEllipseTest001, TestSize.Level1)
{
    auto svgLine = AceType::DynamicCast<SvgEllipse>(SvgEllipse::Create());
    EXPECT_NE(svgLine, nullptr);
    svgLine->path_ = std::nullopt;
    SvgLengthScaleRule rule;
    Rect rect(0, 10, 20, 20);
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    RSRecordingPath path;
    svgLine->path_ = path;
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);
    EXPECT_TRUE(rule.UseFillColor());
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgCircleTest001, TestSize.Level1)
{
    auto svgLine = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgLine, nullptr);
    svgLine->path_ = std::nullopt;
    SvgLengthScaleRule rule;
    Rect rect(0, 10, 20, 20);
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    RSRecordingPath path;
    svgLine->path_ = path;
    rule.containerRect_ = rect;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);

    rule.containerRect_ = svgLine->lengthRule_.containerRect_;
    rule.pathTransform_ = false;
    svgLine->AsPath(rule);
    rule.pathTransform_ = true;
    svgLine->AsPath(rule);
    EXPECT_TRUE(rule.UseFillColor());
}

/**
 * @tc.name: ParseFilterTest002
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgGradientTest001, TestSize.Level1)
{
    auto gradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(gradient, nullptr);
    RefPtr<SvgNode> svgNode1 = nullptr;
    RefPtr<SvgNode> svgNode2 = SvgPattern::Create();
    svgNode2->drawTraversed_ = false;
    RefPtr<SvgNode> svgNode3 = SvgPattern::Create();
    svgNode3->drawTraversed_ = true;
    gradient->children_.emplace_back(svgNode1);
    gradient->children_.emplace_back(svgNode2);
    gradient->children_.emplace_back(svgNode3);

    auto svgStop = AceType::DynamicCast<SvgStop>(SvgStop::Create());
    gradient->children_.emplace_back(svgStop);
    auto result = gradient->GetStopColors();
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgImageTest001, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    RSCanvas canvas;
    Size viewPort;

    std::optional<Color> color = Color::BLACK;
    svgImage->imageAttr_.href = "";
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.href = "href";
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.width = 0.0_px;
    svgImage->imageAttr_.height = 0.0_px;
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.width = 0.0_px;
    svgImage->imageAttr_.height = 10.0_px;
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.width = 20.0_px;
    svgImage->imageAttr_.height = 0.0_px;
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.width = 20.0_px;
    svgImage->imageAttr_.height = 20.0_px;
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.href = "data:image/jpeg;base64$";
    svgImage->OnDraw(canvas, viewPort, color);

    svgImage->imageAttr_.href = "";
    svgImage->OnDraw(canvas, viewPort, color);
    EXPECT_EQ(viewPort.Width(), 0);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgPatternTest001, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    EXPECT_NE(pattern, nullptr);
    int32_t settingApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    RSCanvas canvas;
    Size viewPort;
    std::optional<Color> color;
    pattern->OnDrawTraversedBefore(canvas, viewPort, color);
    EXPECT_EQ(viewPort.Width(), 0);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgPatternTest002, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    EXPECT_NE(pattern, nullptr);
    RSCanvas canvas;
    Size viewPort;
    std::optional<Color> color;
    pattern->patternAttr_.patternContentUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    pattern->OnDrawTraversedBefore(canvas, viewPort, color);

    EXPECT_EQ(viewPort.Width(), 0);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgPatternTest003, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    EXPECT_NE(pattern, nullptr);
    RSCanvas canvas;
    RSBrush brush;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);

    RefPtr<SvgNode> svgNode1 = nullptr;
    RefPtr<SvgNode> svgNode2 = SvgPattern::Create();
    svgNode2->drawTraversed_ = false;
    RefPtr<SvgNode> svgNode3 = SvgPattern::Create();
    svgNode3->drawTraversed_ = true;
    pattern->children_.emplace_back(svgNode1);
    pattern->children_.emplace_back(svgNode2);
    pattern->children_.emplace_back(svgNode3);

    pattern->OnPatternEffect(canvas, brush, context);
    EXPECT_TRUE(context.UseFillColor());
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgFeCompositeTest001, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgFeComposite>(SvgFeComposite::Create());
    EXPECT_NE(pattern, nullptr);

    auto result = pattern->BlendModeForOperator(SvgFeOperatorType::FE_ATOP);
    EXPECT_EQ(result, RSBlendMode::SRC_ATOP);
}

/**
 * @tc.name: SvgImageTest001
 * @tc.desc: parse Filter label
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgFeCompositeTest002, TestSize.Level1)
{
    auto pattern = AceType::DynamicCast<SvgFeComposite>(SvgFeComposite::Create());
    EXPECT_NE(pattern, nullptr);
    auto result = pattern->BlendModeForOperator(SvgFeOperatorType::FE_ATOP);
    std::shared_ptr<RSImageFilter> imageFilter = nullptr;
    SvgColorInterpolationType type = SvgColorInterpolationType::SRGB;
    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
    std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
    pattern->feCompositeAttr_.operatorType = SvgFeOperatorType::FE_ARITHMETIC;
    pattern->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, false);
    pattern->feCompositeAttr_.operatorType = SvgFeOperatorType::FE_ARITHMETIC;
    pattern->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, true);
    pattern->feCompositeAttr_.operatorType = SvgFeOperatorType::FE_ATOP;
    pattern->OnAsImageFilter(imageFilter, type, colorInterpolationType, resultHash, true);
    EXPECT_EQ(result, RSBlendMode::SRC_ATOP);
}

/**
 * @tc.name: SvgAnimateTest
 * @tc.desc: Verify the property animation process for type double
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init svg animate and animator
     */
    RefPtr<SvgAnimation> animation = AceType::DynamicCast<SvgAnimation>(SvgAnimation::Create());
    animation->SetAttributeName("opacity");
    animation->SetBegin(0);
    animation->SetDur(1600);
    animation->SetRepeatCount(1);
    animation->SetFillMode(Fill::FREEZE);
    animation->SetCalcMode(CalcMode::LINEAR);
    animation->SetFrom("0.1");
    animation->SetTo("1.0");
    std::vector<std::string> keyPoints;
    keyPoints.emplace_back("asd dfgfdg fdg000");
    keyPoints.emplace_back("asd dfgfdg fdg111");
    keyPoints.emplace_back("asd dfgfdg fdg222");
    animation->SetKeyPoints(keyPoints);
    auto callback = [](double num) { LOGE("action callback"); };
    animation->calcMode_ = static_cast<CalcMode>(100);
    animation->CreatePropertyAnimation<double>(19.0f, callback);
    EXPECT_NE(animation->animator_, nullptr);
}

/**
 * @tc.name: SvgAnimateTest
 * @tc.desc: Verify the property animation process for type double
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgAnimationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init svg animate and animator
     */
    RefPtr<SvgAnimation> animation = AceType::DynamicCast<SvgAnimation>(SvgAnimation::Create());
    animation->SetAttributeName("width");
    animation->SetBegin(0);
    animation->SetDur(1600);
    animation->SetRepeatCount(1);
    animation->SetFillMode(Fill::FREEZE);
    animation->SetCalcMode(CalcMode::PACED);
    std::vector<std::string> values = { "50", "100", "200", "300" };
    animation->SetValues(values);
    std::vector<double> keyTimes = { 0.0, 0.2, 0.7, 1.0 };
    animation->SetKeyTimes(keyTimes);
    std::vector<std::string> keyPoints;
    keyPoints.emplace_back("asd dfgfdg fdg000");
    keyPoints.emplace_back("asd dfgfdg fdg111");
    keyPoints.emplace_back("asd dfgfdg fdg222");
    animation->SetKeyPoints(keyPoints);
    auto callback = [](double num) { LOGE("action callback"); };
    animation->calcMode_ = static_cast<CalcMode>(100);
    animation->CreatePropertyAnimation<double>(19.0f, callback);
    EXPECT_NE(animation->animator_, nullptr);
}

/**
 * @tc.name: animationTest
 * @tc.desc: Verify the property animation process for type double
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgAnimationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init svg animate and animator
     */
    RefPtr<SvgAnimation> animation = AceType::DynamicCast<SvgAnimation>(SvgAnimation::Create());
    animation->SetBegin(0);
    animation->SetDur(1600);
    animation->SetFillMode(Fill::FREEZE);
    animation->SetRepeatCount(1);
    animation->SetCalcMode(CalcMode::LINEAR);
    std::vector<std::string> keyPoints = { "0", "0.5", "1" };
    animation->SetKeyPoints(keyPoints);
    std::vector<double> keyTimes = { 0.0, 0.4, 1.0 };
    animation->SetKeyTimes(keyTimes);
    auto callback = [](double num) { LOGE("action callback"); };
    animation->calcMode_ = static_cast<CalcMode>(100);
    animation->CreatePropertyAnimation<double>(19.0f, callback);
    EXPECT_NE(animation->animator_, nullptr);
}

/**
 * @tc.name: animationTest
 * @tc.desc: Verify the property animation process for type double
 * @tc.type: FUNC
 */
HWTEST_F(SvgTransformTestNg, SvgAnimationTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init svg animate and animator
     */
    RefPtr<SvgAnimation> animation = AceType::DynamicCast<SvgAnimation>(SvgAnimation::Create());
    animation->SetAttributeName("width");
    animation->SetBegin(0);
    animation->SetDur(1600);
    animation->SetRepeatCount(1);
    animation->SetFillMode(Fill::FREEZE);
    animation->SetCalcMode(CalcMode::DISCRETE);
    std::vector<std::string> values = { "100", "200", "300" };
    animation->SetValues(values);
    std::vector<double> keyTimes = { 0.0, 0.2, 0.7, 1.0 };
    animation->SetKeyTimes(keyTimes);
    auto callback = [](double num) { LOGE("action callback"); };
    animation->calcMode_ = static_cast<CalcMode>(100);
    animation->CreatePropertyAnimation<double>(19.0f, callback);
    EXPECT_NE(animation->animator_, nullptr);
}
} // namespace OHOS::Ace::NG

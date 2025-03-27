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
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_TRANSLATE_SVG_LABEL.c_str(),
        TRANSFORM_TRANSLATE_SVG_LABEL.length());
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
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_INVALID_EMPTY_SVG_LABEL.c_str(),
        TRANSFORM_INVALID_EMPTY_SVG_LABEL.length());
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
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_INVALID_PARA_SVG_LABEL.c_str(),
        TRANSFORM_INVALID_PARA_SVG_LABEL.length());
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
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_ORIGIN_INVALID_PARA_SVG_LABEL.c_str(),
        TRANSFORM_ORIGIN_INVALID_PARA_SVG_LABEL.length());
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
    auto svgStream = SkMemoryStream::MakeCopy(TRANSFORM_ORIGIN_INVALID_EMPTY_SVG_LABEL.c_str(),
        TRANSFORM_ORIGIN_INVALID_EMPTY_SVG_LABEL.length());
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
} // namespace OHOS::Ace::NG

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
#include "core/components_ng/svg/parse/svg_use.h"
#include "core/components_ng/svg/parse/svg_radial_gradient.h"
#include "core/components_ng/svg/parse/svg_linear_gradient.h"
#include "core/components_ng/svg/svg_dom.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string PATTERN_SVG_LABEL =
    "<svg width=\"210\" height=\"210\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<pattern id=\"pattern1\"  x=\"0\" y=\"0\" width=\"0.5\" height=\"0.5\" >"
    "<rect x=\"0\" y=\"0\" width=\"50\" height=\"50\" fill=\"red\" />"
    "<rect x=\"50\" y=\"50\" width=\"50\" height=\"50\" fill=\"blue\" />"
    "</pattern>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"200\" height=\"200\" fill=\"url(#pattern1)\" />"
    "</svg>";

const std::string CLIPPATH_EVENODD_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" viewBox=\"0 0 200 200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<clipPath id=\"starClip\"  clip-rule=\"evenodd\" clipPathUnits=\"objectBoundingBox\" fill-rule=\"evenodd\">"
    "<rect x=\"0.2\" y=\"0.2\" width=\"0.7\" height=\"0.6\" />  "
    "</clipPath>"
    "</defs>"
    "<rect x=\"0\" y=\"0\" width=\"200\" height=\"200\" fill=\"red\" clip-path=\"url(#starClip)\" />"
    "</svg>";

const std::string CLIPPATH_DEFAULT_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" viewBox=\"0 0 200 200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<clipPath id=\"starClip\"  clipPathUnits=\"objectBoundingBox\" fill-rule=\"evenodd\">"
    "<path d=\"M 0.5,0.05 L 0.2,0.99 L 0.95,0.39 L 0.05,0.39 L 0.8,0.99 Z\" /> "
    "</clipPath>"
    "</defs>"
    "<rect x=\"0\" y=\"0\" width=\"200\" height=\"200\" fill=\"red\" clip-path=\"url(#starClip)\" />"
    "</svg>";

const std::string MASK_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<mask id=\"mask1\" maskContentUnits=\"objectBoundingBox\">"
    "<rect x=\"0\" y=\"0\" width=\"1\" height=\"1\" fill=\"red\" />"
    "</mask>"
    "</defs>"
    "<rect x=\"50\" y=\"50\" width=\"100\" height=\"100\" fill=\"blue\" mask=\"url(#mask1)\" />"
    "</svg>";

const std::string FILTER_SVG_LABEL =
    "<svg width=\"300\" height=\"300\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<filter id=\"blurObjectBBox\" primitiveUnits=\"objectBoundingBox\">"
    "<feGaussianBlur in=\"SourceGraphic\" stdDeviation=\"0.1, 0.1\" />"
    "</filter>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"100\" height=\"100\" fill=\"green\" filter=\"url(#blurObjectBBox)\" />"
    "</svg>";

const std::string RADIAL_GRADIENT_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<radialGradient id=\"grad1\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\" "
    "gradientUnits=\"objectBoundingBox\" "
    "spreadMethod=\"pad\" gradientTransform=\"rotate(30)\" >"
    "<stop offset=\"0%\" style=\"stop-color:rgb(255,0,0); stop-opacity:1\" />"
    "<stop offset=\"100%\" style=\"stop-color:rgb(0,0,255); stop-opacity:1\" />"
    "</radialGradient>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"url(#grad1)\" />"
    "</svg>";

const std::string STROKE_RADIAL_GRADIENT_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<defs>"
    "<radialGradient id=\"grad1\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" fy=\"50%\" "
    "gradientUnits=\"objectBoundingBox\" "
    "spreadMethod=\"pad\" gradientTransform=\"rotate(30)\" >"
    "<stop offset=\"0%\" style=\"stop-color:rgb(255,0,0); stop-opacity:1\" />"
    "<stop offset=\"100%\" style=\"stop-color:rgb(0,0,255); stop-opacity:1\" />"
    "</radialGradient>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"none\" stroke=\"url(#grad1)\" />"
    "</svg>";

const std::string RECT_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"red\" />"
    "</svg>";

const std::string STROKE_RECT_SVG_LABEL =
    "<svg width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"none\" stroke=\"red\" />"
    "</svg>";

const std::string LINEAR_GRADIENT_SVG_LABEL =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
    "<defs>"
    "    <linearGradient id=\"grad1\" x1=\"10%\" y1=\"-10%\" x2=\"0\" y2=\"10%\">"
    "        <stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" />"
    "        <stop offset=\"100%\" style=\"stop-color:rgb(255,0,0);stop-opacity:1\" />"
    "    </linearGradient>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"url(#grad1)\" />"
    "</svg>";

const std::string STROKE_LINEAR_GRADIENT_SVG_LABEL =
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
    "<defs>"
    "    <linearGradient id=\"grad1\" x1=\"10%\" y1=\"-10%\" x2=\"0\" y2=\"10%\">"
    "        <stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" />"
    "        <stop offset=\"100%\" style=\"stop-color:rgb(255,0,0);stop-opacity:1\" />"
    "    </linearGradient>"
    "</defs>"
    "<rect x=\"10\" y=\"10\" width=\"180\" height=\"180\" fill=\"none\" stroke=\"url(#grad1)\" />"
    "</svg>";

std::unordered_map<std::string, std::shared_ptr<RSImageFilter>> resultHash;
} // namespace
class ParseTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: GetLengthTest001
 * @tc.desc: SvgNode GetRegionLength and GetMeasuredLength test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetRegionLengthTest001, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    EXPECT_NE(svgNode, nullptr);
    auto dimension = Dimension(1.0, DimensionUnit::PERCENT);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule rule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    SvgLengthType svgLengthType = SvgLengthType::HORIZONTAL;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::VERTICAL;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::OTHER;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
}

/**
 * @tc.name: GetRegionLengthTest002
 * @tc.desc: SvgNode GetRegionLength and GetMeasuredLength test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetRegionLengthTest002, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    auto dimension = Dimension(1.0, DimensionUnit::PERCENT);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule rule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    SvgLengthType svgLengthType = SvgLengthType::HORIZONTAL;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::VERTICAL;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::OTHER;
    EXPECT_EQ(svgNode->GetRegionLength(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredLength(dimension, rule, svgLengthType), 1.0);
}

/**
 * @tc.name: GetRegionPositionTest001
 * @tc.desc: SvgNode GetRegionPosition and GetMeasuredPosition test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetPositionTest001, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    auto dimension = Dimension(1.0, DimensionUnit::PERCENT);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule rule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    SvgLengthType svgLengthType = SvgLengthType::HORIZONTAL;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::VERTICAL;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::OTHER;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 0.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 0.0);
}

/**
 * @tc.name: GetRegionPositionTest002
 * @tc.desc: SvgNode GetRegionPosition and GetMeasuredPosition test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetRegionPositionTest002, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    auto dimension = Dimension(1.0, DimensionUnit::PERCENT);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule rule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    SvgLengthType svgLengthType = SvgLengthType::HORIZONTAL;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::VERTICAL;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 1.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 1.0);
    svgLengthType = SvgLengthType::OTHER;
    EXPECT_EQ(svgNode->GetRegionPosition(dimension, rule, svgLengthType), 0.0);
    EXPECT_EQ(svgNode->GetMeasuredPosition(dimension, rule, svgLengthType), 0.0);
}

/**
 * @tc.name: ConvertDimensionToPxTest001
 * @tc.desc: ConvertDimensionToPx test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, ConvertDimensionToPxTest001, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    auto dimension = Dimension(0.1, DimensionUnit::PERCENT);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgNode->SetContext(svgContext);
    Size viewPort(1, 1);
    SvgLengthType svgLengthType = SvgLengthType::OTHER;
    EXPECT_FLOAT_EQ(svgNode->ConvertDimensionToPx(dimension, viewPort, svgLengthType), 0.1);
}

/**
 * @tc.name: SvgImageCalcDstRectTest001
 * @tc.desc: test CalcDstRect
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SvgImageCalcDstRectTest001, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Size imageSize(1.0, 1.0);
    Rect containerRect (0, 0, 1.0, 1.0);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgImage->SetContext(svgContext);
    auto dstRect = svgImage->CalcDstRect(imageSize, containerRect);
    EXPECT_FLOAT_EQ(dstRect.GetLeft(), 0.0);
    EXPECT_FLOAT_EQ(dstRect.GetRight(), 1.0);
    EXPECT_FLOAT_EQ(dstRect.GetTop(), 0.0);
    EXPECT_FLOAT_EQ(dstRect.GetBottom(), 1.0);
}

/**
 * @tc.name: SvgPatternTest001
 * @tc.desc: SvgPattern test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SvgPatternTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATTERN_SVG_LABEL.c_str(), PATTERN_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgPattern = AceType::DynamicCast<SvgPattern>(svgDefs->children_.at(0));
    EXPECT_NE(svgPattern, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    Testing::TestingBrush rSBrush;
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    EXPECT_CALL(rSCanvas, Save());
    EXPECT_CALL(rSCanvas, Restore());
    svgPattern->OnPatternEffect(rSCanvas, rSBrush, context);
}

/**
 * @tc.name: SvgPatternTest002
 * @tc.desc: SvgPattern test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SvgPatternTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(PATTERN_SVG_LABEL.c_str(), PATTERN_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgPattern = AceType::DynamicCast<SvgPattern>(svgDefs->children_.at(0));
    EXPECT_NE(svgPattern, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: ComputeScaleTest001
 * @tc.desc: ComputeScale test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, ComputeScaleTest001, TestSize.Level1)
{
    SvgPreserveAspectRatio preserveAspectRatio;
    Size viewBox = {0.0, 0.0};
    Size viewPort = {1.0, 1.0};
    float scaleX = 1.0;
    float scaleY = 1.0;
    SvgAttributesParser::ComputeScale(viewBox, viewPort, preserveAspectRatio, scaleX, scaleY);
    EXPECT_FLOAT_EQ(scaleX, 1.0);
    EXPECT_FLOAT_EQ(scaleY, 1.0);
}

/**
 * @tc.name: ParseDimensionTest001
 * @tc.desc: ParseDimension test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, ParseDimensionTest001, TestSize.Level1)
{
    bool featureEnable = false;
    std::string val = "10";
    Dimension y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 10);
    featureEnable = true;
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 10);
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    val = "auto";
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), -0.1);
    val = " ";
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), -0.1);
    val = "20%";
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 0.2);
    val = "10px";
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 10);
    val = "10vp";
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 10);
    val = "10lpx";
    y = Dimension(-0.1, DimensionUnit::PERCENT);
    SvgAttributesParser::ParseDimension(val, y, featureEnable);
    EXPECT_FLOAT_EQ(y.Value(), 10);
}

/**
 * @tc.name: TransformForCurrentOBBTest001
 * @tc.desc: TransformForCurrentOBB test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, TransformForCurrentOBBTest001, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    Testing::MockCanvas rSCanvas;
    svgNode->TransformForCurrentOBB(rSCanvas, rule, containerRect.GetSize(), Offset(0.0, 0.0));
}

/**
 * @tc.name: TransformForCurrentOBBTest002
 * @tc.desc: TransformForCurrentOBB test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, TransformForCurrentOBBTest002, TestSize.Level1)
{
    auto svgNode = AccessibilityManager::MakeRefPtr<SvgNode>();
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rule = svgNode->BuildContentScaleRule(context, OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    EXPECT_EQ(rule.GetLengthScaleUnit(), OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, Translate(_, _));
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgNode->TransformForCurrentOBB(rSCanvas, rule, containerRect.GetSize(), Offset(0.0, 0.0));
}

/**
 * @tc.name: ClipPathEvenoddTest001
 * @tc.desc: ClipPath Evenodd label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, ClipPathEvenoddTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(CLIPPATH_EVENODD_SVG_LABEL.c_str(), CLIPPATH_EVENODD_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgClipPath = AceType::DynamicCast<SvgClipPath>(svgDefs->children_.at(0));
    EXPECT_NE(svgClipPath, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: ClipPathDefaultTest001
 * @tc.desc: ClipPath Default label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, ClipPathDefaultTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(CLIPPATH_DEFAULT_SVG_LABEL.c_str(), CLIPPATH_DEFAULT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgClipPath = AceType::DynamicCast<SvgClipPath>(svgDefs->children_.at(0));
    EXPECT_NE(svgClipPath, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: MaskTest001
 * @tc.desc: mask label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, MaskTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(MASK_SVG_LABEL.c_str(), MASK_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgMask = AceType::DynamicCast<SvgMask>(svgDefs->children_.at(0));
    EXPECT_NE(svgMask, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(4);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(3);
    EXPECT_CALL(rSCanvas, SaveLayer(_)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: MaskTest002
 * @tc.desc: mask label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, MaskTest002, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(MASK_SVG_LABEL.c_str(), MASK_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgMask = AceType::DynamicCast<SvgMask>(svgDefs->children_.at(0));
    EXPECT_NE(svgMask, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(4);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(3);
    EXPECT_CALL(rSCanvas, SaveLayer(_)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: FilterTest001
 * @tc.desc: Filter label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, FilterTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(FILTER_SVG_LABEL.c_str(), FILTER_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svgDefs->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    EXPECT_CALL(rSCanvas, SaveLayer(_)).Times(1);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: SvgRadialGradientTest001
 * @tc.desc: SvgRadialGradient label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SvgRadialGradientTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(RADIAL_GRADIENT_SVG_LABEL.c_str(), RADIAL_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(svgDefs->children_.at(0));
    EXPECT_NE(svgRadialGradient, nullptr);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}


/**
 * @tc.name: SvgLinearGradientTest001
 * @tc.desc: SvgLinearGradient
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SvgLinearGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(LINEAR_GRADIENT_SVG_LABEL.c_str(), LINEAR_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    svgDom->SetAnimationOnFinishCallback([](){});
    svgDom->SetColorFilter(std::nullopt);
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, DetachPen()).WillRepeatedly(ReturnRef(rSCanvas));
    EXPECT_CALL(rSCanvas, Save()).Times(3);
    EXPECT_CALL(rSCanvas, Restore());
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _)).Times(2);
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, size);
}

/**
 * @tc.name: InitBrushTest001
 * @tc.desc: InitBrush test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitBrushTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(RECT_SVG_LABEL.c_str(), RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    src.SetFillColor(Color::GREEN);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingBrush rSBrush;
    Testing::MockCanvas rSCanvas;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::COLOR);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::LINEAR_GRADIENT);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::RADIAL_GRADIENT);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::PATTERN);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::NONE);
}

/**
 * @tc.name: InitBrushTest002
 * @tc.desc: InitBrush test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitBrushTest002, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(RADIAL_GRADIENT_SVG_LABEL.c_str(), RADIAL_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(svgDefs->children_.at(0));
    EXPECT_NE(svgRadialGradient, nullptr);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(1));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingBrush rSBrush;
    Testing::MockCanvas rSCanvas;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::RADIAL_GRADIENT);
}

/**
 * @tc.name: InitBrushTest003
 * @tc.desc: InitBrush label
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitBrushTest003, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(LINEAR_GRADIENT_SVG_LABEL.c_str(), LINEAR_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(svgDefs->children_.at(0));
    EXPECT_NE(svgLinearGradient, nullptr);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(1));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingBrush rSBrush;
    Testing::MockCanvas rSCanvas;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::LINEAR_GRADIENT);
}

/**
 * @tc.name: InitBrushTest004
 * @tc.desc: InitBrush test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitBrushTest004, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(PATTERN_SVG_LABEL.c_str(), PATTERN_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgPattern = AceType::DynamicCast<SvgPattern>(svgDefs->children_.at(0));
    EXPECT_NE(svgPattern, nullptr);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(1));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingBrush rSBrush;
    Testing::MockCanvas rSCanvas;
    EXPECT_CALL(rSCanvas, Save());
    EXPECT_CALL(rSCanvas, Restore());
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitBrush(rSCanvas, rSBrush, context, PaintType::PATTERN);
}

/**
 * @tc.name: InitPenFillTest001
 * @tc.desc: InitPenFill test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitPenFillTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_RECT_SVG_LABEL.c_str(), STROKE_RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingPen rSPen;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitPenFill(rSPen, context, PaintType::COLOR);
    svgRect->InitPenFill(rSPen, context, PaintType::LINEAR_GRADIENT);
    svgRect->InitPenFill(rSPen, context, PaintType::RADIAL_GRADIENT);
    svgRect->InitPenFill(rSPen, context, PaintType::PATTERN);
    svgRect->InitPenFill(rSPen, context, PaintType::NONE);
}

/**
 * @tc.name: InitPenFillTest002
 * @tc.desc: InitPenFill test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitPenFillTest002, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_RADIAL_GRADIENT_SVG_LABEL.c_str(), STROKE_RADIAL_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(svgDefs->children_.at(0));
    EXPECT_NE(svgRadialGradient, nullptr);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(1));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingPen rSPen;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitPenFill(rSPen, context, PaintType::RADIAL_GRADIENT);
}

/**
 * @tc.name: InitPenFillTest003
 * @tc.desc: InitPenFill test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, InitPenFillTest003, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_LINEAR_GRADIENT_SVG_LABEL.c_str(), STROKE_LINEAR_GRADIENT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(svgDefs->children_.at(0));
    EXPECT_NE(svgLinearGradient, nullptr);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(1));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingPen rSPen;
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    svgRect->InitPenFill(rSPen, context, PaintType::LINEAR_GRADIENT);
}

/**
 * @tc.name: GetLocalMatrixTest001
 * @tc.desc: GetLocalMatrix test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetLocalMatrixTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_RECT_SVG_LABEL.c_str(), STROKE_RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    Rect containerRect(0, 0, 100, 100);
    Size viewPort(100, 100);
    SvgCoordinateSystemContext context(containerRect, viewPort);
    auto rsMatrix = svgRect->GetLocalMatrix(SvgLengthScaleUnit::OBJECT_BOUNDING_BOX, context);
    rsMatrix = svgRect->GetLocalMatrix(SvgLengthScaleUnit::USER_SPACE_ON_USE, context);
}

/**
 * @tc.name: GetFillTypeTest001
 * @tc.desc: GetFillType test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetFillTypeTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(RECT_SVG_LABEL.c_str(), RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    auto fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::COLOR);
    svgRect->attributes_.fillState.SetColor(Color::RED, false);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.fillState.SetGradient(gradient);
    fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::COLOR);
    gradient.SetHref("test");
    svgRect->attributes_.fillState.SetGradient(gradient);
    fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);
    svgRect->attributes_.fillState.SetColor(Color::RED);
    fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);
    svgRect->attributes_.fillState.SetHref("test");
    fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);
    svgRect->attributes_.fillState.SetIsFillNone(true);
    fillType = svgRect->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);
}

/**
 * @tc.name: GetStrokeTypeTest001
 * @tc.desc: GetStrokeType test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, GetStrokeTypeTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_RECT_SVG_LABEL.c_str(), STROKE_RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    auto strokeType = svgRect->GetStrokeType();
    EXPECT_EQ(strokeType, PaintType::COLOR);
    svgRect->attributes_.strokeState.SetColor(Color::TRANSPARENT);
    strokeType = svgRect->GetStrokeType();
    EXPECT_EQ(strokeType, PaintType::NONE);
    svgRect->attributes_.strokeState.SetColor(Color::RED, false);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    svgRect->attributes_.strokeState.SetGradient(gradient);
    strokeType = svgRect->GetStrokeType();
    EXPECT_EQ(strokeType, PaintType::COLOR);
    gradient.SetHref("test");
    svgRect->attributes_.strokeState.SetGradient(gradient);
    strokeType = svgRect->GetStrokeType();
    EXPECT_EQ(strokeType, PaintType::NONE);
    svgRect->attributes_.strokeState.SetHref("test");
    strokeType = svgRect->GetStrokeType();
    EXPECT_EQ(strokeType, PaintType::NONE);
}

/**
 * @tc.name: SetPenStyleTest001
 * @tc.desc: SetPenStyle test
 * @tc.type: FUNC
 */
HWTEST_F(ParseTestThreeNg, SetPenStyleTest001, TestSize.Level1)
{
    auto svgStream =
        SkMemoryStream::MakeCopy(STROKE_RECT_SVG_LABEL.c_str(), STROKE_RECT_SVG_LABEL.length());
    ImageSourceInfo src;
    src.SetSupportSvg2(true);
    Size size = { 100, 100 };
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgRect = AceType::DynamicCast<SvgRect>(svg->children_.at(0));
    EXPECT_NE(svgRect, nullptr);
    Testing::TestingPen rSPen;
    svgRect->attributes_.strokeState.SetLineCap(LineCapStyle::ROUND);
    svgRect->SetPenStyle(rSPen);
    svgRect->attributes_.strokeState.SetLineCap(LineCapStyle::SQUARE);
    svgRect->SetPenStyle(rSPen);
    svgRect->attributes_.strokeState.SetLineCap(LineCapStyle::BUTT);
    svgRect->SetPenStyle(rSPen);
    svgRect->attributes_.strokeState.SetLineJoin(LineJoinStyle::ROUND);
    svgRect->SetPenStyle(rSPen);
    svgRect->attributes_.strokeState.SetLineJoin(LineJoinStyle::BEVEL);
    svgRect->SetPenStyle(rSPen);
    svgRect->attributes_.strokeState.SetLineJoin(LineJoinStyle::MITER);
    svgRect->SetPenStyle(rSPen);
        std::vector<double> segments = {4.0, 2.0, 6.0};
    svgRect->attributes_.strokeState.SetLineDash(segments);
    svgRect->SetPenStyle(rSPen);
}
} // namespace OHOS::Ace::NG
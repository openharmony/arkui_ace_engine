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

#define private public
#define protected public

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components/declaration/svg/svg_gradient_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LINEAR =
    "<svg height=\"150\" width=\"400\"><defs><linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" "
    "y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" /><stop offset=\"100%\" "
    "style=\"stop-color:rgb(255,0,0);stop-opacity:1\" /></linearGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
const std::string SVG_RADIAL =
    "<svg height=\"150\" width=\"500\"><defs><radialGradient id=\"grad1\" cx=\"50%\" cy=\"50%\" r=\"50%\" fx=\"50%\" "
    "fy=\"50%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,255);      stop-opacity:0\" /><stop offset=\"100%\" "
    "style=\"stop-color:rgb(0,0,255);stop-opacity:1\" /></radialGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
constexpr int32_t INDEX_ZEARO = 0;
constexpr int32_t CHILD_NUMBER = 2;
constexpr float X1 = 0.0f;
constexpr float X2 = 1.0f;
constexpr float Y1 = 0.0f;
constexpr float Y2 = 0.0f;
constexpr float CX = 0.5f;
constexpr float CY = 0.5f;
constexpr float R = 0.5f;
constexpr float FX = 0.5f;
constexpr float FY = 0.5f;
} // namespace
class ParseGradientTestNg : public testing::Test {};

/**
 * @tc.name: ParseLinearGradientTest001
 * @tc.desc: parse lineargradient label
 * @tc.type: FUNC
 */

HWTEST_F(ParseGradientTestNg, ParseLinearGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LINEAR.c_str(), SVG_LINEAR.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
    auto defers = AceType::DynamicCast<SvgDefs>(svg->children_.at(INDEX_ZEARO));
    EXPECT_NE(defers, nullptr);
    auto svgGradient = AceType::DynamicCast<SvgGradient>(defers->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGradient, nullptr);
    auto svgGradientDeclaration = AceType::DynamicCast<SvgGradientDeclaration>(svgGradient->declaration_);
    EXPECT_NE(svgGradientDeclaration, nullptr);
    auto gradient = svgGradientDeclaration->GetGradient();
    EXPECT_EQ(gradient.GetLinearGradient().x1.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().x1->ConvertToPx(), X1);
    EXPECT_EQ(gradient.GetLinearGradient().x2.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().x2->ConvertToPx(), X2);
    EXPECT_EQ(gradient.GetLinearGradient().y1.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().y1->ConvertToPx(), Y1);
    EXPECT_EQ(gradient.GetLinearGradient().y2.has_value(), true);
    EXPECT_FLOAT_EQ(gradient.GetLinearGradient().y2->ConvertToPx(), Y2);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseRadialGradientTest001
 * @tc.desc: parse radialgradient label
 * @tc.type: FUNC
 */

HWTEST_F(ParseGradientTestNg, ParseRadialGradientTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_RADIAL.c_str(), SVG_RADIAL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), CHILD_NUMBER);
    auto defers = AceType::DynamicCast<SvgDefs>(svg->children_.at(INDEX_ZEARO));
    EXPECT_NE(defers, nullptr);
    auto svgGradient = AceType::DynamicCast<SvgGradient>(defers->children_.at(INDEX_ZEARO));
    EXPECT_NE(svgGradient, nullptr);
    auto svgGradientDeclaration = AceType::DynamicCast<SvgGradientDeclaration>(svgGradient->declaration_);
    EXPECT_NE(svgGradientDeclaration, nullptr);
    auto gradient = svgGradientDeclaration->GetGradient();
    auto radialGradient = gradient.GetRadialGradient();
    EXPECT_EQ(radialGradient.fRadialCenterX.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.fRadialCenterX->ConvertToPx(), FX);
    EXPECT_EQ(radialGradient.fRadialCenterY.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.fRadialCenterY->ConvertToPx(), FY);
    EXPECT_EQ(radialGradient.radialCenterX.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialCenterX->ConvertToPx(), CX);
    EXPECT_EQ(radialGradient.radialCenterY.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialCenterY->ConvertToPx(), CY);
    EXPECT_EQ(radialGradient.radialHorizontalSize.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialHorizontalSize->ConvertToPx(), R);
    EXPECT_EQ(radialGradient.radialVerticalSize.has_value(), true);
    EXPECT_FLOAT_EQ(radialGradient.radialVerticalSize->ConvertToPx(), R);
    EXPECT_EQ(radialGradient.radialShape.has_value(), false);
    EXPECT_EQ(radialGradient.radialSizeType.has_value(), false);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
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

#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_filter_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg height=\"900\" width=\"900\"><filter id=\"composite\" y=\"0\" x=\"0\" width=\"900\" "
    "height=\"900\"><feTurbulence baseFrequency=\".05\" numOctaves=\"3\" result=\"B\"/><feComposite in2=\"B\" "
    "in=\"SourceGraphic\" operator=\"in\" /></filter><ellipse cx=\"100\" cy=\"87\" rx=\"75\" ry=\"87\" fill=\"red\" "
    "filter=\"url(#composite)\"/></svg>";
const std::string ID = "composite";
constexpr float X = 0.0f;
constexpr float Y = 0.0f;
constexpr float WIDTH = 900.0f;
constexpr float HEIGHT = 900.0f;
} // namespace
class ParseFilterTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse filter label
 * @tc.type: FUNC
 */

HWTEST_F(ParseFilterTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
    EXPECT_STREQ(svgFilter->nodeId_.c_str(), ID.c_str());
    auto filterDeclaration = AceType::DynamicCast<SvgFilterDeclaration>(svgFilter->declaration_);
    EXPECT_NE(filterDeclaration, nullptr);
    EXPECT_FLOAT_EQ(filterDeclaration->GetHeight().ConvertToPx(), HEIGHT);
    EXPECT_FLOAT_EQ(filterDeclaration->GetWidth().ConvertToPx(), WIDTH);
    EXPECT_FLOAT_EQ(filterDeclaration->GetX().ConvertToPx(), X);
    EXPECT_FLOAT_EQ(filterDeclaration->GetY().ConvertToPx(), Y);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
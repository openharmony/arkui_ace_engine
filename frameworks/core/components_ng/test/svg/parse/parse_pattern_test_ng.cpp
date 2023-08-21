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
#include "core/components_ng/render/canvas_image.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_pattern_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg viewBox=\"0 0 230 100\"><defs><pattern id=\"star\" viewBox=\"0 0 10 10\" width=\"10\" "
    "height=\"10\"><polygon points=\"0,0 2,5 0,10 5,8 10,10 8,5 10,0 5,2\" /></pattern></defs><circle cx=\"50\" "
    "cy=\"50\" r=\"50\" fill=\"url(#star)\" /><circle cx=\"180\" cy=\"50\" r=\"40\"  fill=\"none\" stroke-width=\"20\" "
    "stroke=\"url(#star)\"/> </svg>";
constexpr float WIDTH = 10.0f;
constexpr float HEIGHT = 10.0f;
constexpr float VIEWBOX_X = 0.0f;
constexpr float VIEWBOX_Y = 0.0f;
constexpr float VIEWBOX_WIDTH = 10.0f;
constexpr float VIEWBOX_HEIGHT = 10.0f;
} // namespace
class ParsePatternTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse pattern label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePatternTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
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
    EXPECT_FLOAT_EQ(patternDeclaration->GetWidth().ConvertToPx(), WIDTH);
    EXPECT_FLOAT_EQ(patternDeclaration->GetHeight().ConvertToPx(), HEIGHT);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetOffset().GetX(), VIEWBOX_X);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetOffset().GetY(), VIEWBOX_Y);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetSize().Width(), VIEWBOX_WIDTH);
    EXPECT_FLOAT_EQ(patternDeclaration->GetViewBox().GetSize().Height(), VIEWBOX_HEIGHT);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);

    BorderRadiusArray radius;
    for (auto&& corner: radius) {
        corner = {0.0f, 0.0f};
    }
    svgDom->SetRadius(radius);
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(*svgDom->radius_, radius);
}
} // namespace OHOS::Ace::NG
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
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_circle_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><circle cx=\"60px\" "
    "cy=\"200px\" r = \"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" stroke-width=\"16px\" "
    "stroke-opacity=\"0.3\" id=\"circleId\"/></svg>";
constexpr float Cx = 60.0f;
constexpr float Cy = 200.0f;
constexpr float R = 50.0f;
} // namespace
class ParseCircleTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse circle label
 * @tc.type: FUNC
 */

HWTEST_F(ParseCircleTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
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
    svgDom->DrawImage(rSCanvas, ImageFit::FITWIDTH, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
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
#include "core/components/declaration/svg/svg_stop_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_stop.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg height=\"150\" width=\"400\"><defs><linearGradient id=\"grad1\" x1=\"0%\" y1=\"0%\" x2=\"100%\" "
    "y2=\"0%\"><stop offset=\"0%\" style=\"stop-color:rgb(255,255,0);stop-opacity:1\" /><stop offset=\"20px\" "
    "style=\"stop-color:rgb(255,0,0);stop-opacity:1\" /></linearGradient></defs><ellipse cx=\"200\" cy=\"70\" "
    "rx=\"85\" ry=\"55\" fill=\"url(#grad1)\" /></svg>";
constexpr int32_t INDEX_ZEARO = 0;
constexpr int32_t CHILD_NUMBER = 2;
constexpr float STOP_OPACITY = 1.0f;
} // namespace
class ParseStopTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse stop label
 * @tc.type: FUNC
 */

HWTEST_F(ParseStopTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
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
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
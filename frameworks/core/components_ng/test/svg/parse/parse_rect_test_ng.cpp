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
#include "core/components/declaration/svg/svg_rect_declaration.h"
#include "core/components_ng/svg/parse/svg_rect.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"400\" height=\"400\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><rect width=\"100\" "
    "height=\"100\" x=\"150\" y=\"20\" stroke-width=\"4\" stroke=\"#000000\" rx=\"10\" ry=\"10\"></rect></svg>";
constexpr float X = 150.0f;
constexpr float Y = 20.0f;
constexpr float RX = 10.0f;
constexpr float RY = 10.0f;
constexpr float WIDTH = 100.0f;
constexpr float HEIGHT = 100.0f;
} // namespace
class ParseRectTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse rect label
 * @tc.type: FUNC
 */

HWTEST_F(ParseRectTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
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
    EXPECT_FLOAT_EQ(rectDeclaration->GetWidth().ConvertToPx(), WIDTH);
    EXPECT_FLOAT_EQ(rectDeclaration->GetHeight().ConvertToPx(), HEIGHT);
}
} // namespace OHOS::Ace::NG
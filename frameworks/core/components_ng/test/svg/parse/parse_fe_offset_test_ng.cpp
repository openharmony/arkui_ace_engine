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
#include "core/components/declaration/svg/svg_fe_offset_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_fe_offset.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"200\" height=\"200\"><defs> <filter id =\"feOffset\" x=\"-40\" y=\"-20\" width=\"100\" "
    "height=\"200\"><feOffset in =\"SourceGraphic\" dx=\"60\" dy=\"60\" /></ filter></ defs><rect x =\"40\" y=\"40\" "
    "width=\"100\" height=\"100\" style = \"stroke : #000000; fill: green; filter: url(#feOffset);\" /></svg>";
constexpr float DX = 60.0f;
constexpr float DY = 60.0f;
} // namespace

class ParseFeOffsetTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse FeOffset label
 * @tc.type: FUNC
 */

HWTEST_F(ParseFeOffsetTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgFilter = AceType::DynamicCast<SvgFilter>(svgDefs->children_.at(0));
    EXPECT_NE(svgFilter, nullptr);
    auto svgFeOffset = AceType::DynamicCast<SvgFeOffset>(svgFilter->children_.at(0));
    EXPECT_NE(svgFeOffset, nullptr);
    auto feDeclaration = AceType::DynamicCast<SvgFeOffsetDeclaration>(svgFeOffset->declaration_);
    EXPECT_NE(feDeclaration, nullptr);
    EXPECT_FLOAT_EQ(feDeclaration->GetDx(), DX);
    EXPECT_FLOAT_EQ(feDeclaration->GetDy(), DY);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
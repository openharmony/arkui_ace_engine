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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_polygon_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_polygon.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL1 = "<svg fill=\"white\" stroke=\"blue\" width=\"800\" height=\"400\" version=\"1.1\" "
                               "xmlns=\"http://www.w3.org/2000/svg\"><polygon points=\"10,110 60,35 60,85 110,10\" "
                               "fill=\"red\"></polygon> <polyline points=\"10,200 60,125 60,175 110,100\" "
                               "stroke-dasharray=\"10 5\" stroke-dashoffset=\"3\"></polyline></svg>";
const std::string SVG_LABEL2 = "<svg fill=\"white\" stroke=\"blue\" width=\"300\" height=\"400\" version=\"1.1\" "
                               "xmlns=\"http://www.w3.org/2000/svg\"><polygon points=\"10,110 60,35 60,85 110,10\" "
                               "fill=\"red\"></polygon> <polyline points=\"10,200 60,125 60,175 110,100\" "
                               "stroke-dasharray=\"10 5\" stroke-dashoffset=\"3\"></polyline></svg>";
const std::string POLYGON_POINT = "10,110 60,35 60,85 110,10";
const std::string POLYLINE_POINT = "10,200 60,125 60,175 110,100";
constexpr int32_t CHILD_NUMBER = 2;
} // namespace
class ParsePolygonTestNg : public testing::Test {
public:
    RefPtr<SvgDom> parsePolygon(const std::string& svgLable)
    {
        auto svgStream = SkMemoryStream::MakeCopy(svgLable.c_str(), svgLable.length());
        EXPECT_NE(svgStream, nullptr);
        auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
        EXPECT_NE(svgDom, nullptr);
        auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
        EXPECT_NE(svg, nullptr);
        EXPECT_EQ(static_cast<int32_t>(svg->children_.size()), CHILD_NUMBER);
        auto svgPolygon = AceType::DynamicCast<SvgPolygon>(svg->children_.at(0));
        EXPECT_NE(svgPolygon, nullptr);
        auto svgPolyline = AceType::DynamicCast<SvgPolygon>(svg->children_.at(1));
        EXPECT_NE(svgPolyline, nullptr);
        auto polygonDeclaration = AceType::DynamicCast<SvgPolygonDeclaration>(svgPolygon->declaration_);
        EXPECT_NE(polygonDeclaration, nullptr);
        EXPECT_STREQ(polygonDeclaration->GetPoints().c_str(), POLYGON_POINT.c_str());
        auto polylineDeclaration = AceType::DynamicCast<SvgPolygonDeclaration>(svgPolyline->declaration_);
        EXPECT_NE(polylineDeclaration, nullptr);
        EXPECT_STREQ(polylineDeclaration->GetPoints().c_str(), POLYLINE_POINT.c_str());
        return svgDom;
    }
};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePolygonTestNg, ParseTest001, TestSize.Level1)
{
    auto svgDom = parsePolygon(SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest002
 * @tc.desc: parse polygon and polyline label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePolygonTestNg, ParseTest002, TestSize.Level1)
{
    auto svgDom = parsePolygon(SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::CONTAIN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
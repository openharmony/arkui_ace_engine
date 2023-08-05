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
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/declaration/svg/svg_ellipse_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_ellipse.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL1 =
    "<svg fill=\"white\" width=\"400\" height=\"400\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"60\" cy=\"200\" rx=\"50\" ry=\"100\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
const std::string SVG_LABEL2 =
    "<svg fill=\"white\" width=\"10\" height=\"10\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><ellipse "
    "cx=\"60\" cy=\"200\" rx=\"50\" ry=\"100\" stroke-width=\"4\" fill=\"red\" stroke=\"blue\"></ellipse></svg>";
constexpr float Cx = 60.0f;
constexpr float Cy = 200.0f;
constexpr float RX = 50.0f;
constexpr float RY = 100.0f;
} // namespace
class ParseEllipseTestNg : public testing::Test {
public:
    static RefPtr<SvgDom> ParseEllipse(const std::string& svgLabel)
    {
        auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
        EXPECT_NE(svgStream, nullptr);
        auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
        auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
        EXPECT_GT(svg->children_.size(), 0);
        auto svgEllipse = AceType::DynamicCast<SvgEllipse>(svg->children_.at(0));
        EXPECT_NE(svgEllipse, nullptr);
        auto ellipseDeclaration = AceType::DynamicCast<SvgEllipseDeclaration>(svgEllipse->declaration_);
        EXPECT_FLOAT_EQ(ellipseDeclaration->GetCx().ConvertToPx(), Cx);
        EXPECT_FLOAT_EQ(ellipseDeclaration->GetCy().ConvertToPx(), Cy);
        EXPECT_FLOAT_EQ(ellipseDeclaration->GetRx().ConvertToPx(), RX);
        EXPECT_FLOAT_EQ(ellipseDeclaration->GetRy().ConvertToPx(), RY);
        return svgDom;
    }
};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */

HWTEST_F(ParseEllipseTestNg, ParseTest001, TestSize.Level1)
{
    auto svgDom = ParseEllipse(SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::RED);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest002
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */

HWTEST_F(ParseEllipseTestNg, ParseTest002, TestSize.Level1)
{
    auto svgDom = ParseEllipse(SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::RED);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest003
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */

HWTEST_F(ParseEllipseTestNg, ParseTest003, TestSize.Level1)
{
    auto svgDom = ParseEllipse(SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->root_ = nullptr;
    svgDom->DrawImage(rSCanvas, ImageFit::SCALE_DOWN, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::RED);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest004
 * @tc.desc: parse ellipse label
 * @tc.type: FUNC
 */

HWTEST_F(ParseEllipseTestNg, ParseTest004, TestSize.Level1)
{
    SvgEllipse *sEllipse = new SvgEllipse();
    const Size viewPort = Size(0.0, 0.0);
    EXPECT_EQ(viewPort.Width(), 0.0);
    EXPECT_EQ(viewPort.Height(), 0.0);
    auto svgEllipse1 = sEllipse->Create();
    svgEllipse1->AsPath(viewPort);
    delete sEllipse;
}
} // namespace OHOS::Ace::NG
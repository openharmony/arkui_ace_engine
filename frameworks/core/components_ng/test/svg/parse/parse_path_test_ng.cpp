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
#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_path_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL1 =
    "<svg width=\"400\" height=\"800\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string SVG_LABEL2 =
    "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string SVG_LABEL3 =
    "<svg width=\"-400\" height=\"-400\" viewBox=\"-4 -10 300 300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string SVG_LABEL4 =
    "<svg width=\"300\" height=\"400\" viewBox=\"-4 -10 300 300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string SVG_LABEL5 =
    "<svg width=\"400\" height=\"400\" viewBox=\"-4 -10 -300 -300\" version=\"1.1\" "
    "xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_CMD = "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z";
} // namespace
class ParsePathTestNg : public testing::Test {
public:
    static RefPtr<SvgDom> ParsePath(const std::string& svgLabel)
    {
        auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
        EXPECT_NE(svgStream, nullptr);
        auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
        auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
        EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
        auto svgPath = AceType::DynamicCast<SvgPath>(svg->children_.at(0));
        EXPECT_NE(svgPath, nullptr);
        auto pathDeclaration = AceType::DynamicCast<SvgPathDeclaration>(svgPath->declaration_);
        EXPECT_STREQ(pathDeclaration->GetD().c_str(), PATH_CMD.c_str());
        return svgDom;
    }
};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest001, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL1);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size());
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest002
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest002, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest003
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest003, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL4);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParseTest004
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest004, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL3);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParseTest005
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest005, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL3);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size());
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}

/**
 * @tc.name: ParseTest006
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest006, TestSize.Level1)
{
    auto svgDom = ParsePath(SVG_LABEL5);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size());
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
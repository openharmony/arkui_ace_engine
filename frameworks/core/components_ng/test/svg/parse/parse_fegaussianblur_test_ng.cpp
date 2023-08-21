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

#include "core/components/common/layout/constants.h"
#include "core/components/declaration/svg/svg_fe_gaussianblur_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"230\" height=\"120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
const std::string SVG_LABEL2 =
    "<svg width=\"-230\" height=\"-120\"><filter id=\"blurMe\"><feGaussianBlur in=\"Graphic\" stdDeviation=\"5\" "
    "/></filter><circle cx=\"170\" cy=\"60\" r=\"50\" fill=\"green\" filter=\"url(#blurMe)\" /></svg>";
constexpr float STD_DEVIATION = 5.0f;
} // namespace

class ParseFeGaussianblurTestNg : public testing::Test {
public:
    RefPtr<SvgDom> ParseFeGaussianblur(const std::string& svgLabel)
    {
        auto svgStream = SkMemoryStream::MakeCopy(svgLabel.c_str(), svgLabel.length());
        EXPECT_NE(svgStream, nullptr);
        auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
        auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
        EXPECT_GT(svg->children_.size(), 0);
        auto svgFilter = AceType::DynamicCast<SvgFilter>(svg->children_.at(0));
        EXPECT_NE(svgFilter, nullptr);
        auto svgFeGaussiaBlur = AceType::DynamicCast<SvgFeGaussianBlur>(svgFilter->children_.at(0));
        EXPECT_NE(svgFeGaussiaBlur, nullptr);
        auto feDeclaration = AceType::DynamicCast<SvgFeGaussianBlurDeclaration>(svgFeGaussiaBlur->declaration_);
        EXPECT_NE(feDeclaration, nullptr);
        EXPECT_FLOAT_EQ(feDeclaration->GetStdDeviation(), STD_DEVIATION);
        EXPECT_EQ(feDeclaration->GetEdgeMode(), FeEdgeMode::EDGE_DUPLICATE);
        return svgDom;
    }
};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse Fegaussianblur label
 * @tc.type: FUNC
 */

HWTEST_F(ParseFeGaussianblurTestNg, ParseTest001, TestSize.Level1)
{
    auto svgDom = ParseFeGaussianblur(SVG_LABEL);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}

/**
 * @tc.name: ParseTest002
 * @tc.desc: parse Fegaussianblur label svg size is invalid
 * @tc.type: FUNC
 */

HWTEST_F(ParseFeGaussianblurTestNg, ParseTest002, TestSize.Level1)
{
    auto svgDom = ParseFeGaussianblur(SVG_LABEL2);
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), false);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
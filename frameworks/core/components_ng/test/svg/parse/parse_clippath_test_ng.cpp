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
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components/declaration/svg/svg_animate_declaration.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"120\" height=\"120\" viewBox=\"0 0 120 120\" version=\"1.1\"><defs><clipPath id=\"myClip\"><circle "
    "cx=\"30\" cy=\"30\" r=\"20\"/><circle cx=\"70\" cy=\"70\" r=\"30\"/></clipPath></defs><rect x=\"10\" y=\"10\" "
    "width=\"100\" height=\"100\" clip-path=\"url(#myClip)\" fill=\"red\" /></svg>";
const std::string ID = "myClip";
} // namespace
class ParseClipPathTestNg : public testing::Test {};

/**
 * @tc.name: ParseAnimation
 * @tc.desc: parse animation path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseClipPathTestNg, ParseAnimation, TestSize.Level1)
{
    SvgAnimation *svgAnimation = new SvgAnimation(SvgAnimateType::ANIMATE);
    EXPECT_NE(svgAnimation, nullptr);
    auto svgAnimate = svgAnimation->Create();
    EXPECT_NE(svgAnimate, nullptr);
    auto svgMotion = svgAnimation->CreateAnimateMotion();
    EXPECT_NE(svgMotion, nullptr);
    auto svgTransform = svgAnimation->CreateAnimateTransform();
    EXPECT_NE(svgTransform, nullptr);
    svgAnimation->SetAttr(ID, SVG_LABEL);
    svgAnimation->UpdateAttr();
    EXPECT_EQ(svgAnimation->ConvertCalcMode(ID), CalcMode::LINEAR);
    delete svgAnimation;
}

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse clip path label
 * @tc.type: FUNC
 */

HWTEST_F(ParseClipPathTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgDefs = AceType::DynamicCast<SvgDefs>(svg->children_.at(0));
    EXPECT_NE(svgDefs, nullptr);
    auto svgClipPath = AceType::DynamicCast<SvgClipPath>(svgDefs->children_.at(0));
    EXPECT_NE(svgClipPath, nullptr);
    EXPECT_STREQ(svgClipPath->nodeId_.c_str(), ID.c_str());
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::COVER, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT), Color::RED);
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), true);
}
} // namespace OHOS::Ace::NG
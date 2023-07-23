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

using namespace testing;
using namespace testing::ext;

#include "include/core/SkStream.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_ANIMATE_TRANSFORM(
    "<svg width=\"200px\" height=\"200px\" viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<path d =\"M50 50L20 50A30 30 0 0 0 80 50Z\">"
    "<animateTransform attributeName =\"transform\" type=\"rotate\" repeatCount=\"3\" dur=\"1s\""
    " values=\"0 50 50;45 50 50;0 50 50\" keyTimes=\"0;0.5;1\"></animateTransform></path></svg>");

} // namespace
class ParseAnimateTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse circle label
 * @tc.type: FUNC
 */

HWTEST_F(ParseAnimateTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_ANIMATE_TRANSFORM.c_str(), SVG_ANIMATE_TRANSFORM.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    EXPECT_TRUE(svgDom);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_TRUE(svg);
    EXPECT_GT(svg->children_.size(), 0);

    auto svgAnimate = AceType::DynamicCast<SvgAnimation>(svg->children_.at(0)->children_.at(0));
    EXPECT_TRUE(svgAnimate);
    // values changed to indices
    std::vector<std::string> values { "0", "1", "2" };
    EXPECT_EQ(svgAnimate->GetValues(), values);
}
} // namespace OHOS::Ace::NG
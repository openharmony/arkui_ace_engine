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
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/test/svg/parse/svg_const.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL = "<svg width=\"400\" height=\"500\"> <g id=\"myId\"> </g></svg>";
const std::string ID = "myId";
} // namespace
class ParseGTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse g label
 * @tc.type: FUNC
 */

HWTEST_F(ParseGTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto g = AceType::DynamicCast<SvgG>(svg->children_.at(0));
    ASSERT_STREQ(g->nodeId_.c_str(), ID.c_str());
    RSCanvas rSCanvas;
    svgDom->DrawImage(rSCanvas, ImageFit::FILL, Size(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT));
    EXPECT_EQ(svgDom->svgSize_.IsValid(), true);
    EXPECT_EQ(svgDom->viewBox_.IsValid(), false);
}
} // namespace OHOS::Ace::NG
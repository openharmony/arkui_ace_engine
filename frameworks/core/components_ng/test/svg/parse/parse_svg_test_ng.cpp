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

#include "core/components/common/properties/color.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL = "<svg width=\"400\" height=\"500\" viewBox=\"-4 -10 300 300\"></svg>";
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 500.0f;
constexpr float VIEWBOX_X = -4.0f;
constexpr float VIEWBOX_Y = -10.0f;
constexpr float VIEWBOX_WIDTH = 300.0f;
constexpr float VIEWBOX_HEIGHT = 300.0f;
} // namespace
class ParseSvgTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse svg label
 * @tc.type: FUNC
 */

HWTEST_F(ParseSvgTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    EXPECT_FLOAT_EQ(svgDom->svgSize_.Width(), WIDTH);
    EXPECT_FLOAT_EQ(svgDom->svgSize_.Height(), HEIGHT);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Left(), VIEWBOX_X);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Top(), VIEWBOX_Y);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Width(), VIEWBOX_WIDTH);
    EXPECT_FLOAT_EQ(svgDom->viewBox_.Height(), VIEWBOX_HEIGHT);
}
} // namespace OHOS::Ace::NG
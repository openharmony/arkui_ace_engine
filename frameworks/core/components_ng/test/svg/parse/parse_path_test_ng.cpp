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
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_path_declaration.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SVG_LABEL =
    "<svg width=\"400\" height=\"400\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"M 10,30 A 20,20 "
    "0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z\" stroke=\"blue\" stroke-width=\"3\" "
    "fill=\"red\"></path></svg>";
const std::string PATH_CMD = "M 10,30 A 20,20 0,0,1 50,30 A 20,20 0,0,1 90,30 Q 90,60 50,90 Q 10,60 10,30 z";
} // namespace
class ParsePathTestNg : public testing::Test {};

/**
 * @tc.name: ParseTest001
 * @tc.desc: parse path label
 * @tc.type: FUNC
 */

HWTEST_F(ParsePathTestNg, ParseTest001, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(SVG_LABEL.c_str(), SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, Color::BLACK);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(svg->children_.size(), 0);
    auto svgPath = AceType::DynamicCast<SvgPath>(svg->children_.at(0));
    EXPECT_NE(svgPath, nullptr);
    auto pathDeclaration = AceType::DynamicCast<SvgPathDeclaration>(svgPath->declaration_);
    EXPECT_STREQ(pathDeclaration->GetD().c_str(), PATH_CMD.c_str());
}
} // namespace OHOS::Ace::NG
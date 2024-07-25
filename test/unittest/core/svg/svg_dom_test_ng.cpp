/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_rect.h"
#include "frameworks/core/components_ng/svg/svg_ulils.h"

#define private public
#define protected public

#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/svg/svg_ulils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Size LAYOUT = { 400, 500 };
const Size SVG_SIZE = { 50, 50 };
const Rect VIEW_BOX = { -4.0, -10.0, 300.0, 300.0 };
} // namespace
class SvgDomTestNg : public testing::Test {};

/**
 * @tc.name: SvgDom001
 * @tc.desc: test fit image
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDom001, TestSize.Level1)
{
    auto svgDom = AceType::MakeRefPtr<SvgDom>();

    svgDom->svgSize_ = SVG_SIZE;
    svgDom->viewBox_ = VIEW_BOX;
    Testing::MockCanvas canvas;
    // check translate and scale parameters
    auto clipRect = Testing::TestingRect(0, 0, LAYOUT.Width(), LAYOUT.Height());
    EXPECT_CALL(canvas, ClipRect(_, _, _));
    svgDom->FitImage(canvas, ImageFit::CONTAIN, LAYOUT);
}

/**
 * @tc.name: SvgDom002
 * @tc.desc: test svg content Size
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDom002, TestSize.Level1)
{
    Size svgContentSize;
    SvgUtils::CalculateSvgConentSize(svgContentSize, LAYOUT, SVG_SIZE, VIEW_BOX);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), SVG_SIZE.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), SVG_SIZE.Height());
}
} // namespace OHOS::Ace::NG

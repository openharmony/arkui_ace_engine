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

#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_rect.h"

#define private public
#define protected public

#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Size LAYOUT = { 400, 500 };
const Size SVG_SIZE = { 50, 50 };
const Rect VIEW_BOX = { -4.0, -10.0, 300.0, 300.0 };
constexpr float EPSILON = 0.001;
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
    float layoutScale = LAYOUT.Width() / SVG_SIZE.Width();
    float viewBoxScale = SVG_SIZE.Width() / VIEW_BOX.Width();
    float tx = 4.0f * viewBoxScale * layoutScale ;
    float ty = 10.0f * viewBoxScale * layoutScale;

    ty += (LAYOUT.Height() - SVG_SIZE.Height() * layoutScale) / 2;
    // check translate and scale parameters
    EXPECT_CALL(canvas, Translate(FloatNear(tx, EPSILON), FloatNear(ty, EPSILON)));
    EXPECT_CALL(canvas, Scale(layoutScale * viewBoxScale, layoutScale * viewBoxScale));
    auto clipRect = Testing::TestingRect(0, 0, LAYOUT.Width(), LAYOUT.Height());
    EXPECT_CALL(canvas, ClipRect(_, _));
    svgDom->FitImage(canvas, ImageFit::CONTAIN, LAYOUT);
}
} // namespace OHOS::Ace::NG

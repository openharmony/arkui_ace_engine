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
#include "frameworks/core/components_ng/svg/svg_utils.h"

#define private public
#define protected public

#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/svg/svg_utils.h"

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

/**
 * @tc.name: SvgDomContentSize001
 * @tc.desc: test svg content Size
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDomContentSize001, TestSize.Level1)
{
    Size ContainerSize = { 400, 500 };
    Size SvgSize = { 50, 50 };
    Rect ViewBox = { -4.0, -10.0, -1, -1 };
    Size svgContentSize;
    SvgUtils::CalculateSvgConentSize(svgContentSize, ContainerSize, SvgSize, ViewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), SVG_SIZE.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), SVG_SIZE.Height());

    SvgSize = { -50, -50 };
    ViewBox = { -4.0, -10.0, -1, -1 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, ContainerSize, SvgSize, ViewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), ContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), ContainerSize.Height());
}

/**
 * @tc.name: SvgDomContentSize002
 * @tc.desc: test svg content Size
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDomContentSize002, TestSize.Level1)
{
    Size ContainerSize = { 400, 500 };
    Size SvgSize = { -50, -50 };
    Rect ViewBox = { -4.0, -10.0, 20, 30 };
    Size svgContentSize;
    SvgUtils::CalculateSvgConentSize(svgContentSize, ContainerSize, SvgSize, ViewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), ContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), ContainerSize.Height());

    SvgSize = { -50, 50 };
    ViewBox = { -4.0, -10.0, 20, 30 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, ContainerSize, SvgSize, ViewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), ViewBox.Width() / ViewBox.Height() * SvgSize.Height());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), SvgSize.Height());

    SvgSize = { 50, -50 };
    ViewBox = { -4.0, -10.0, 20, 30 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, ContainerSize, SvgSize, ViewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), SvgSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), ViewBox.Height() / ViewBox.Width() * SvgSize.Width());
}

/**
 * @tc.name: SvgDomDraw001
 * @tc.desc: svg draw with fit
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDomDraw001, TestSize.Level1)
{
    auto svgDom = AceType::MakeRefPtr<SvgDom>();
    svgDom->root_ = nullptr;
    Testing::MockCanvas rSCanvas;
    svgDom->layout_ = LAYOUT;
    svgDom->svgSize_ = SVG_SIZE;
    svgDom->viewBox_ = VIEW_BOX;
    ImageFit imageFit = ImageFit::FILL;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::CONTAIN;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::COVER;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::FITWIDTH;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::FITHEIGHT;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::NONE;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::SCALE_DOWN;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
}

/**
 * @tc.name: SvgDomDraw002
 * @tc.desc: svg draw with align
 * @tc.type: FUNC
 */
HWTEST_F(SvgDomTestNg, SvgDomDraw002, TestSize.Level1)
{
    auto svgDom = AceType::MakeRefPtr<SvgDom>();
    svgDom->root_ = nullptr;
    Testing::MockCanvas rSCanvas;
    svgDom->layout_ = LAYOUT;
    svgDom->svgSize_ = SVG_SIZE;
    svgDom->viewBox_ = VIEW_BOX;
    ImageFit imageFit = ImageFit::TOP_LEFT;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::TOP;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::TOP_END;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::START;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::CENTER;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::END;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::BOTTOM_START;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::BOTTOM;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::BOTTOM_END;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
    imageFit = ImageFit::COVER_TOP_LEFT;
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgDom->FitImage(rSCanvas, imageFit, LAYOUT);
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "include/core/SkStream.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/svg/svg_animate_declaration.h"
#include "core/components/declaration/svg/svg_circle_declaration.h"
#include "core/components/declaration/svg/svg_declaration.h"
#include "core/components/declaration/svg/svg_ellipse_declaration.h"
#include "core/components/declaration/svg/svg_fe_blend_declaration.h"
#include "core/components/declaration/svg/svg_fe_colormatrix_declaration.h"
#include "core/components/declaration/svg/svg_fe_composite_declaration.h"
#include "core/components/declaration/svg/svg_fe_declaration.h"
#include "core/components/declaration/svg/svg_fe_flood_declaration.h"
#include "core/components/declaration/svg/svg_fe_gaussianblur_declaration.h"
#include "core/components/declaration/svg/svg_filter_declaration.h"
#include "core/components/declaration/svg/svg_gradient_declaration.h"
#include "core/components/declaration/svg/svg_image_declaration.h"
#include "core/components/declaration/svg/svg_line_declaration.h"
#include "core/components/declaration/svg/svg_mask_declaration.h"
#include "core/components/declaration/svg/svg_path_declaration.h"
#include "core/components/declaration/svg/svg_pattern_declaration.h"
#include "core/components/declaration/svg/svg_polygon_declaration.h"
#include "core/components/declaration/svg/svg_rect_declaration.h"
#include "core/components/declaration/svg/svg_stop_declaration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_offset.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_rect.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/parse/svg_use.h"
#include "core/components_ng/svg/svg_dom.h"
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CIRCLE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"><circle cx=\"60px\" "
    "cy=\"200px\" r = \"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" stroke-width=\"16px\" "
    "stroke-opacity=\"0.3\" id=\"circleId\"/></svg>";
} // namespace

class SvgNodeTestNg : public testing::Test {};

/**
 * @tc.name: feOffsetTest
 * @tc.desc: test feOffsetTest
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, feOffsetTest001, TestSize.Level1)
{
    auto svgFeOffset = AceType::DynamicCast<SvgFeOffset>(SvgFeOffset::Create());
    CHECK_NULL_VOID(svgFeOffset);
    svgFeOffset->ParseAndSetSpecializedAttr("dx", "30");
    svgFeOffset->ParseAndSetSpecializedAttr("dy", "40");
    EXPECT_FLOAT_EQ(svgFeOffset->feOffsetAttr_.dx.Value(), 30);
    EXPECT_FLOAT_EQ(svgFeOffset->feOffsetAttr_.dy.Value(), 40);
}

/**
 * @tc.name: feOffsetTest
 * @tc.desc: test feOffsetTest
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgMaskTest001, TestSize.Level1)
{
    auto svgMask = AceType::DynamicCast<SvgMask>(SvgMask::Create());
    CHECK_NULL_VOID(svgMask);
    svgMask->ParseAndSetSpecializedAttr("width", "30");
    svgMask->ParseAndSetSpecializedAttr("height", "40");
    svgMask->ParseAndSetSpecializedAttr("maskUnits", "UseSpaceOnUse");
    svgMask->ParseAndSetSpecializedAttr("maskContentUnits", "UseSpaceOnUse");
    svgMask->ParseAndSetSpecializedAttr("x", "20");
    svgMask->ParseAndSetSpecializedAttr("y", "20");
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.x.Value(), 20);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.y.Value(), 20);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.width.Value(), 30);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.height.Value(), 40);
    EXPECT_EQ(svgMask->maskAttr_.maskUnits, "UseSpaceOnUse");
    EXPECT_EQ(svgMask->maskAttr_.maskContentUnits, "UseSpaceOnUse");
    svgMask->OnInitStyle();
    EXPECT_FLOAT_EQ(svgMask->x_.Value(), svgMask->maskAttr_.x.Value());
    EXPECT_FLOAT_EQ(svgMask->y_.Value(), svgMask->maskAttr_.y.Value());
    EXPECT_FLOAT_EQ(svgMask->height_.Value(), svgMask->maskAttr_.height.Value());
    EXPECT_FLOAT_EQ(svgMask->width_.Value(), svgMask->maskAttr_.width.Value());
    EXPECT_FLOAT_EQ(svgMask->isDefaultMaskUnits_, false);
    EXPECT_FLOAT_EQ(svgMask->isDefaultMaskContentUnits_, false);
}

/**
 * @tc.name: svgGTest001
 * @tc.desc: test g
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgGTest001, TestSize.Level1)
{
    auto svgG = AceType::DynamicCast<SvgG>(SvgG::Create());
    CHECK_NULL_VOID(svgG);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    svgG->AppendChild(svgCircle);
    Size size(300, 400);
    svgG->AsPath(size);
    EXPECT_FLOAT_EQ(svgG->children_.size(), 1);
}

/**
 * @tc.name: svgGTest002
 * @tc.desc: test g
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgGTest002, TestSize.Level1)
{
    auto svgG = AceType::DynamicCast<SvgG>(SvgG::Create());
    CHECK_NULL_VOID(svgG);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    svgG->AppendChild(svgCircle);
    Size size(300, 400);
    svgG->AsPath(size);
    EXPECT_FLOAT_EQ(svgG->children_.size(), 1);
}

/**
 * @tc.name: svgGTest003
 * @tc.desc: test g
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgGTest003, TestSize.Level1)
{
    auto svgG = AceType::DynamicCast<SvgG>(SvgG::Create());
    CHECK_NULL_VOID(svgG);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    svgG->AppendChild(svgCircle);
    Size size(300, 400);
    svgG->AsPath(size);
    EXPECT_FLOAT_EQ(svgG->children_.size(), 1);
}

/**
 * @tc.name: svgFilterTest001
 * @tc.desc: test g
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgFilterTest001, TestSize.Level1)
{
    auto svgFilter = AceType::DynamicCast<SvgFilter>(SvgFilter::Create());
    CHECK_NULL_VOID(svgFilter);
    auto svgFeOffset = AceType::DynamicCast<SvgFeOffset>(SvgFeOffset::Create());
    svgFilter->AppendChild(svgFeOffset);
    svgFilter->ParseAndSetSpecializedAttr("width", "300");
    svgFilter->ParseAndSetSpecializedAttr("height", "300");
    svgFilter->ParseAndSetSpecializedAttr("x", "30");
    svgFilter->ParseAndSetSpecializedAttr("y", "30");
    Size size(300, 400);
    svgFilter->AsPath(size);
    Testing::MockCanvas rSCanvas;
    svgFilter->Draw(rSCanvas, size, std::nullopt);
    EXPECT_FLOAT_EQ(svgFilter->filterAttr_.width.Value(), 300);
    EXPECT_FLOAT_EQ(svgFilter->filterAttr_.height.Value(), 300);
    EXPECT_FLOAT_EQ(svgFilter->filterAttr_.x.Value(), 30);
    EXPECT_FLOAT_EQ(svgFilter->filterAttr_.y.Value(), 30);
}

/**
 * @tc.name: svgUseTest001
 * @tc.desc: test use
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgUseTest001, TestSize.Level1)
{
    auto svgUse = AceType::DynamicCast<SvgUse>(SvgUse::Create());
    std::cout << "10" << std::endl;
    EXPECT_NE(svgUse, nullptr);
    std::cout << "11" << std::endl;
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    std::cout << "13" << std::endl;
    svgUse->AppendChild(svgCircle);
    std::cout << "14" << std::endl;
    svgUse->ParseAndSetSpecializedAttr("width", "300");
    svgUse->ParseAndSetSpecializedAttr("height", "300");
    svgUse->ParseAndSetSpecializedAttr("x", "30");
    svgUse->ParseAndSetSpecializedAttr("y", "30");
    svgUse->ParseAndSetSpecializedAttr("mirror", "30");
    svgUse->ParseAndSetSpecializedAttr("viewbox", "30 30 100 100");
    Size size(300, 400);
    svgUse->AsPath(size);
    Testing::MockCanvas rSCanvas;
    EXPECT_FLOAT_EQ(svgUse->useAttr_.width.Value(), 300);
    EXPECT_FLOAT_EQ(svgUse->useAttr_.height.Value(), 300);
    EXPECT_FLOAT_EQ(svgUse->useAttr_.x.Value(), 30);
    EXPECT_FLOAT_EQ(svgUse->useAttr_.y.Value(), 30);
}

/**
 * @tc.name: svgPatternTest001
 * @tc.desc: test pattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgPatternTest001, TestSize.Level1)
{
    auto svgPattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    EXPECT_NE(svgPattern, nullptr);
    svgPattern->ParseAndSetSpecializedAttr("height", "300");
    svgPattern->ParseAndSetSpecializedAttr("width", "300");
    svgPattern->ParseAndSetSpecializedAttr("x", "30");
    svgPattern->ParseAndSetSpecializedAttr("y", "30");
    svgPattern->ParseAndSetSpecializedAttr("pattenUnits", "useSpaceOnUse");
    svgPattern->ParseAndSetSpecializedAttr("pattenContentUnits", "useSpaceOnUse");
    svgPattern->ParseAndSetSpecializedAttr("viewbox", "30 30 100 100");
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->Push("myPattern", svgPattern);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    svgCircle->SetContext(svgContext);
    Size size(300, 400);
    svgCircle->AsPath(size);
    EXPECT_FLOAT_EQ(svgPattern->patternAttr_.width.Value(), 300);
    EXPECT_FLOAT_EQ(svgPattern->patternAttr_.height.Value(), 300);
    EXPECT_FLOAT_EQ(svgPattern->patternAttr_.x.Value(), 30);
    EXPECT_FLOAT_EQ(svgPattern->patternAttr_.y.Value(), 30);
}

/**
 * @tc.name: svgSvgTest001
 * @tc.desc: test pattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgTest001, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->ParseAndSetSpecializedAttr("height", "300");
    svgSvg->ParseAndSetSpecializedAttr("width", "300");
    svgSvg->ParseAndSetSpecializedAttr("x", "30");
    svgSvg->ParseAndSetSpecializedAttr("y", "30");
    svgSvg->ParseAndSetSpecializedAttr("viewbox", "30 30 100 100");
    Size size(300, 400);
    svgSvg->AsPath(size);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.width.Value(), 300);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.height.Value(), 300);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.x.Value(), 30);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.y.Value(), 30);
}

/**
 * @tc.name: svgAdjustContentArea001
 * @tc.desc: test pattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentArea001, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->svgAttr_.width = Dimension(-100);
    svgSvg->svgAttr_.height = Dimension(-100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, -100, -100);
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentArea002
 * @tc.desc: test pattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentArea002, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentArea003
 * @tc.desc: test pattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentArea003, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(-100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, Translate(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentArea004
 * @tc.desc: test AdjustContent
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentArea004, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->svgAttr_.width = Dimension(-100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, Translate(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentArea004
 * @tc.desc: test AdjustContent
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentArea005, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->svgAttr_.width = Dimension(-100);
    svgSvg->svgAttr_.height = Dimension(-100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: SvgFeCompositeTest001
 * @tc.desc: test FeComposite
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgFeCompositeTest001, TestSize.Level1)
{
    auto svgFeComposite = AceType::DynamicCast<SvgFeComposite>(SvgFeComposite::Create());
    EXPECT_NE(svgFeComposite, nullptr);
    svgFeComposite->ParseAndSetSpecializedAttr("k3", "30");
    svgFeComposite->ParseAndSetSpecializedAttr("k4", "40");
    EXPECT_FLOAT_EQ(svgFeComposite->feCompositeAttr_.k3, 30);
    EXPECT_FLOAT_EQ(svgFeComposite->feCompositeAttr_.k4, 40);
}
} // namespace OHOS::Ace::NG
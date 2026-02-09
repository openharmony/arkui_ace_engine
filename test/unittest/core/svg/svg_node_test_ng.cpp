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

#include "compatible/components/svg/svg_animate_declaration.h"
#include "compatible/components/svg/svg_circle_declaration.h"
#include "compatible/components/svg/svg_declaration.h"
#include "compatible/components/svg/svg_ellipse_declaration.h"
#include "compatible/components/svg/svg_fe_blend_declaration.h"
#include "compatible/components/svg/svg_fe_colormatrix_declaration.h"
#include "compatible/components/svg/svg_fe_composite_declaration.h"
#include "compatible/components/svg/svg_fe_declaration.h"
#include "compatible/components/svg/svg_fe_flood_declaration.h"
#include "compatible/components/svg/svg_fe_gaussianblur_declaration.h"
#include "compatible/components/svg/svg_filter_declaration.h"
#include "compatible/components/svg/svg_gradient_declaration.h"
#include "compatible/components/svg/svg_image_declaration.h"
#include "compatible/components/svg/svg_line_declaration.h"
#include "compatible/components/svg/svg_mask_declaration.h"
#include "compatible/components/svg/svg_path_declaration.h"
#include "compatible/components/svg/svg_pattern_declaration.h"
#include "compatible/components/svg/svg_polygon_declaration.h"
#include "compatible/components/svg/svg_rect_declaration.h"
#include "compatible/components/svg/svg_stop_declaration.h"
#include "include/core/SkStream.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_clip_path.h"
#include "core/components_ng/svg/parse/svg_defs.h"
#include "core/components_ng/svg/parse/svg_ellipse.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_offset.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_image.h"
#include "core/components_ng/svg/parse/svg_line.h"
#include "core/components_ng/svg/parse/svg_linear_gradient.h"
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_polygon.h"
#include "core/components_ng/svg/parse/svg_radial_gradient.h"
#include "core/components_ng/svg/parse/svg_rect.h"
#include "core/components_ng/svg/parse/svg_stop.h"
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

class SvgNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }
};

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
    svgMask->ParseAndSetSpecializedAttr("maskUnits", "userSpaceOnUse");
    svgMask->ParseAndSetSpecializedAttr("maskContentUnits", "userSpaceOnUse");
    svgMask->ParseAndSetSpecializedAttr("x", "20");
    svgMask->ParseAndSetSpecializedAttr("y", "20");
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.x.Value(), 20);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.y.Value(), 20);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.width.Value(), 30);
    EXPECT_FLOAT_EQ(svgMask->maskAttr_.height.Value(), 40);
    EXPECT_EQ(svgMask->maskAttr_.maskUnits, SvgLengthScaleUnit::USER_SPACE_ON_USE);
    EXPECT_EQ(svgMask->maskAttr_.maskContentUnits, SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgMask->OnInitStyle();
    EXPECT_FLOAT_EQ(svgMask->x_.Value(), svgMask->maskAttr_.x.Value());
    EXPECT_FLOAT_EQ(svgMask->y_.Value(), svgMask->maskAttr_.y.Value());
    EXPECT_FLOAT_EQ(svgMask->height_.Value(), svgMask->maskAttr_.height.Value());
    EXPECT_FLOAT_EQ(svgMask->width_.Value(), svgMask->maskAttr_.width.Value());
    EXPECT_FLOAT_EQ(svgMask->isDefaultMaskUnits_, false);
    EXPECT_FLOAT_EQ(svgMask->isDefaultMaskContentUnits_, true);
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
 * @tc.name: svgSvgTest002
 * @tc.desc: test svg width < 0 height < 0
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgTest002, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->ParseAndSetSpecializedAttr("height", "-100");
    svgSvg->ParseAndSetSpecializedAttr("width", "-100");
    Size size(300, 400);
    svgSvg->AsPath(size);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.width.Value(), -100);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.height.Value(), -100);
}

/**
 * @tc.name: svgSvgViewBoxTest001
 * @tc.desc: test viewBox
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgViewBoxTest001, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->ParseAndSetSpecializedAttr("height", "300");
    svgSvg->ParseAndSetSpecializedAttr("width", "300");
    svgSvg->ParseAndSetSpecializedAttr("x", "30");
    svgSvg->ParseAndSetSpecializedAttr("y", "30");
    svgSvg->ParseAndSetSpecializedAttr("viewbox", "");
    Size size(300, 400);
    svgSvg->AsPath(size);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.width.Value(), 300);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.height.Value(), 300);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.x.Value(), 30);
    EXPECT_FLOAT_EQ(svgSvg->svgAttr_.y.Value(), 30);
}

/**
 * @tc.name: svgSvgPreserveAspectRatioTest001
 * @tc.desc: test Parse preserveAspectRatio Invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgPreserveAspectRatioTest001, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "none");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_NONE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xx xx");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xx xx xx");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "   ");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);
}

/**
 * @tc.name: svgSvgPreserveAspectRatioTest002
 * @tc.desc: test Parse preserveAspectRatio MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgPreserveAspectRatioTest002, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMin meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMid meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMax meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMin meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMid meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMax meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMin meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMid meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMax meet");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::MEET);
}

/**
 * @tc.name: svgSvgPreserveAspectRatioTest003
 * @tc.desc: test Parse preserveAspectRatio SLICE
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgSvgPreserveAspectRatioTest003, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMin slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMid slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMinYMax slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMIN_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMin slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMid slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMidYMax slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMID_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMin slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMIN);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMid slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMID);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);

    svgSvg->ParseAndSetSpecializedAttr("preserveAspectRatio", "xMaxYMax slice");
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.svgAlign, SvgAlign::ALIGN_XMAX_YMAX);
    EXPECT_EQ(svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice, SvgMeetOrSlice::SLICE);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio01
 * @tc.desc: test AdjustContent
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio01, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMIN_YMIN;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio02
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMIN_YMID MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio02, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMIN_YMID;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio03
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMIN_YMAX MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio03, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMIN_YMAX;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio04
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMID_YMIN MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio04, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMID_YMIN;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio05
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMID_YMID MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio05, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMID_YMID;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio06
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMID_YMAX MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio06, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMID_YMAX;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio07
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMAX_YMIN MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio07, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMAX_YMIN;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio08
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMAX_YMID MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio08, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMAX_YMID;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio09
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMAX_YMAX MEET
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio09, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMAX_YMAX;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::MEET;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio10
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_XMIN_YMIN SLICE
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio10, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_XMIN_YMIN;
    svgSvg->svgAttr_.preserveAspectRatio.meetOrSlice = SvgMeetOrSlice::SLICE;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
}

/**
 * @tc.name: svgAdjustContentAreaPreserveAspectRatio11
 * @tc.desc: test AdjustContent preserveAspectRatio ALIGN_NONE
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgAdjustContentAreaPreserveAspectRatio11, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgSvg->SetContext(svgContext);
    svgSvg->svgAttr_.width = Dimension(100);
    svgSvg->svgAttr_.height = Dimension(100);
    svgSvg->svgAttr_.viewBox = Rect(20, 30, 100, 100);
    svgSvg->svgAttr_.preserveAspectRatio.svgAlign = SvgAlign::ALIGN_NONE;
    Testing::MockCanvas rSCanvas;
    Size viewPort(100, 200);
    EXPECT_CALL(rSCanvas, ClipRect(_, _, _));
    EXPECT_CALL(rSCanvas, Translate(_, _)).Times(2);
    EXPECT_CALL(rSCanvas, Scale(_, _));
    svgSvg->AdjustContentAreaByViewBox(rSCanvas, viewPort);
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

/**
 * @tc.name: SvgLinearGradientTest001
 * @tc.desc: test LinearGradient spread reflect
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest001, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    const std::string gradienttransform("scale(1.5)");
    svgLinearGradient->SetAttr("gradienttransform", gradienttransform);
    svgLinearGradient->SetAttr("spreadmethod", "reflect");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::REPEAT));
    EXPECT_EQ(gradient.GetGradientTransform(), gradienttransform);
}

/**
 * @tc.name: SvgLinearGradientTest002
 * @tc.desc: test LinearGradient spread pad
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest002, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    svgLinearGradient->SetAttr("spreadmethod", "pad");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::PAD));
}

/**
 * @tc.name: SvgLinearGradientTest003
 * @tc.desc: test LinearGradient spread repeat
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest003, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    svgLinearGradient->SetAttr("spreadmethod", "repeat");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::REFLECT));
}

/**
 * @tc.name: SvgLinearGradientTest004
 * @tc.desc: test LinearGradient spread reflect apiLess or equal 12
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest004, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    svgLinearGradient->SetAttr("gradienttransform", "scale(1.5)");
    svgLinearGradient->SetAttr("spreadmethod", "reflect");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::REFLECT));
}

/**
 * @tc.name: SvgLinearGradientTest005
 * @tc.desc: test LinearGradient spread pad, apiLess or equal 12
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest005, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    svgLinearGradient->SetAttr("spreadmethod", "pad");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::PAD));
}

/**
 * @tc.name: SvgLinearGradientTest006
 * @tc.desc: test LinearGradient spread repeat, apiLess or equal 12
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest006, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgGradient>(SvgGradient::CreateLinearGradient());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    svgLinearGradient->SetAttr("spreadmethod", "repeat");
    auto gradient = svgLinearGradient->GetGradient();
    auto spreadMethod = gradient.GetSpreadMethod();
    MockContainer::TearDown();
    EXPECT_EQ(static_cast<int32_t>(spreadMethod), static_cast<int32_t>(OHOS::Ace::SpreadMethod::REPEAT));
}

/**
 * @tc.name: SvgLinearGradientTest010
 * @tc.desc: test/ LinearGradient spread reflect
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest010, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    const std::string gradienttransform("scale(1.5)");
    svgLinearGradient->SetAttr("gradienttransform", gradienttransform);
    svgLinearGradient->SetAttr("spreadmethod", "reflect");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(linearGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::REFLECT));
    EXPECT_EQ(linearGradientInfo.gradientTransform, gradienttransform);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest011
 * @tc.desc: test LinearGradient spread pad
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest011, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("spreadmethod", "pad");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(linearGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::PAD));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest012
 * @tc.desc: test LinearGradient spread repeat
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest012, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("spreadmethod", "repeat");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(linearGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::REPEAT));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest013
 * @tc.desc: test LinearGradient spread error, api equal 18
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest013, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("spreadmethod", "error");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(linearGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::PAD));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest014
 * @tc.desc: test LinearGradient x1, y1, x2, y2, api equal 18
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest014, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("x1", "30");
    svgLinearGradient->SetAttr("y1", "30");
    svgLinearGradient->SetAttr("x2", "30");
    svgLinearGradient->SetAttr("y2", "30");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(linearGradientInfo.x1, 30);
    EXPECT_FLOAT_EQ(linearGradientInfo.y1, 30);
    EXPECT_FLOAT_EQ(linearGradientInfo.x2, 30);
    EXPECT_FLOAT_EQ(linearGradientInfo.y2, 30);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest015
 * @tc.desc: test LinearGradient, api equal 18
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest015, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("gradientunits", "objectBoundingBox");
    svgLinearGradient->SetAttr("x1", "0.5");
    svgLinearGradient->SetAttr("y1", "0.5");
    svgLinearGradient->SetAttr("x2", "0.5");
    svgLinearGradient->SetAttr("y2", "0.5");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(linearGradientInfo.x1, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.y1, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.x2, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.y2, 0.5);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgLinearGradientTest016
 * @tc.desc: test LinearGradient, api equal 18
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest016, TestSize.Level1)
{
    auto svgLinearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(svgLinearGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgLinearGradient->SetContext(svgContext);
    svgLinearGradient->SetAttr("gradientunits", "error");
    svgLinearGradient->SetAttr("x1", "0.5");
    svgLinearGradient->SetAttr("y1", "0.5");
    svgLinearGradient->SetAttr("x2", "0.5");
    svgLinearGradient->SetAttr("y2", "0.5");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto linearGradientInfo = svgLinearGradient->GetLinearGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(linearGradientInfo.x1, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.y1, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.x2, 0.5);
    EXPECT_FLOAT_EQ(linearGradientInfo.y2, 0.5);
    MockContainer::TearDown();
}

/**
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest001, TestSize.Level1)
{
    auto linearGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(linearGradient, nullptr);
    auto radialGradientAttr = linearGradient->radialGradientAttr_;
    radialGradientAttr.cx = 3.0_vp;
    radialGradientAttr.cy = 35.0_vp;
    radialGradientAttr.r = 31.0_vp;
    radialGradientAttr.cx = 32.0_vp;
    radialGradientAttr.cy = 32.0_vp;
    radialGradientAttr.gradientTransform = "gradientTransform11";
    linearGradient->radialGradientAttr_.gradientUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    linearGradient->SetAttr("gradienttransform", "val1");
    EXPECT_EQ(linearGradient->radialGradientAttr_.gradientTransform, "");

    linearGradient->SetAttr("gradientunits", "userSpaceOnUse");
    EXPECT_EQ(linearGradient->radialGradientAttr_.gradientUnits, SvgLengthScaleUnit::USER_SPACE_ON_USE);

    linearGradient->SetAttr("gradientunits", "userSpaceOnUse22");
    linearGradient->radialGradientAttr_.gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    EXPECT_EQ(linearGradient->radialGradientAttr_.gradientUnits, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);

    linearGradient->SetAttr("spreadmethod", "repeat");
    linearGradient->radialGradientAttr_.spreadMethod = SvgSpreadMethod::REPEAT;
    EXPECT_EQ(linearGradient->radialGradientAttr_.spreadMethod, SvgSpreadMethod::REPEAT);

    linearGradient->SetAttr("spreadmethod", "reflect");
    linearGradient->radialGradientAttr_.spreadMethod = SvgSpreadMethod::REFLECT;
    EXPECT_EQ(linearGradient->radialGradientAttr_.spreadMethod, SvgSpreadMethod::REFLECT);

    linearGradient->radialGradientAttr_.spreadMethod = SvgSpreadMethod::PAD;
    linearGradient->SetAttr("spreadmethod", "reflect222");
    EXPECT_EQ(linearGradient->radialGradientAttr_.spreadMethod, SvgSpreadMethod::PAD);

    linearGradient->radialGradientAttr_.cx = 20.0_px;
    linearGradient->SetAttr("cx", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.cx.ToString(), "20.00px");

    linearGradient->radialGradientAttr_.cy = 35.0_vp;
    linearGradient->SetAttr("cy", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.cy.ToString(), "35.00vp");

    linearGradient->radialGradientAttr_.r = 31.0_vp;
    linearGradient->SetAttr("r", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.r.ToString(), "31.00vp");

    linearGradient->radialGradientAttr_.fx = 32.0_vp;
    linearGradient->SetAttr("fx", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.fx->ToString(), "32.00vp");

    linearGradient->radialGradientAttr_.fy = 32.0_vp;
    linearGradient->SetAttr("fy", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.fy->ToString(), "32.00vp");

    linearGradient->radialGradientAttr_.fy = 32.0_vp;
    linearGradient->SetAttr("fy", "20");
    EXPECT_EQ(linearGradient->radialGradientAttr_.fy->ToString(), "32.00vp");
}

/**
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest002, TestSize.Level1)
{
    auto radialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(radialGradient, nullptr);
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);

    auto info = radialGradient->GetRadialGradientInfo(context);
    EXPECT_EQ(info.cx, 0.5);
    EXPECT_EQ(info.cy, 0.5);

    EXPECT_EQ(info.r, 0.5);
    EXPECT_EQ(info.fx, 0.5);
    EXPECT_EQ(info.fy, 0.5);
    EXPECT_EQ(info.spreadMethod, 0);
    EXPECT_EQ(info.gradientTransform, "");
    EXPECT_EQ(info.colors.size(), 0);
}

/**
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest003, TestSize.Level1)
{
    auto radialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(radialGradient, nullptr);

    radialGradient->radialGradientAttr_.gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    auto units = radialGradient->GradientUnits();
    EXPECT_EQ(units, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);

    units = radialGradient->GradientUnits();
    radialGradient->radialGradientAttr_.gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    EXPECT_EQ(units, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
}

/**
 * @tc.name: SvgRadialGradientTest004
 * @tc.desc: test/ RadialGradient spread reflect
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest004, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    const std::string gradienttransform("scale(1.5)");
    svgRadialGradient->SetAttr("gradienttransform", gradienttransform);
    svgRadialGradient->SetAttr("spreadmethod", "reflect");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(radialGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::REFLECT));
    EXPECT_EQ(radialGradientInfo.gradientTransform, gradienttransform);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest005
 * @tc.desc: test/ RadialGradient spread pad
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest005, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("spreadmethod", "pad");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(radialGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::PAD));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest006
 * @tc.desc: test/ RadialGradient spread repeat
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest006, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("spreadmethod", "repeat");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(radialGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::REPEAT));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest007
 * @tc.desc: test/ RadialGradient spread error
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest007, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("spreadmethod", "error");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_EQ(radialGradientInfo.spreadMethod, static_cast<int32_t>(OHOS::Ace::NG::SvgSpreadMethod::PAD));
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest008
 * @tc.desc: test/ RadialGradient gradientunits default cx, cy, fx, fy, r
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest008, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("cx", "30");
    svgRadialGradient->SetAttr("cy", "30");
    svgRadialGradient->SetAttr("fx", "30");
    svgRadialGradient->SetAttr("fy", "30");
    svgRadialGradient->SetAttr("r", "30");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(radialGradientInfo.cx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.cy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.r, 30);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest009
 * @tc.desc: test/ RadialGradient gradientunits=objectBoundingBox cx, cy, fx, fy, r
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest009, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("gradientunits", "objectBoundingBox");
    svgRadialGradient->SetAttr("cx", "30");
    svgRadialGradient->SetAttr("cy", "30");
    svgRadialGradient->SetAttr("fx", "30");
    svgRadialGradient->SetAttr("fy", "30");
    svgRadialGradient->SetAttr("r", "30");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(radialGradientInfo.cx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.cy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.r, 30);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgRadialGradientTest010
 * @tc.desc: test/ RadialGradient gradientunits = error cx, cy, fx, fy, r
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRadialGradientTest010, TestSize.Level1)
{
    auto svgRadialGradient = AceType::DynamicCast<SvgRadialGradient>(SvgRadialGradient::Create());
    EXPECT_NE(svgRadialGradient, nullptr);
    MockContainer::SetUp();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgRadialGradient->SetContext(svgContext);
    svgRadialGradient->SetAttr("gradientunits", "error");
    svgRadialGradient->SetAttr("cx", "30");
    svgRadialGradient->SetAttr("cy", "30");
    svgRadialGradient->SetAttr("fx", "30");
    svgRadialGradient->SetAttr("fy", "30");
    svgRadialGradient->SetAttr("r", "30");
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    auto radialGradientInfo = svgRadialGradient->GetRadialGradientInfo(svgCoordinateSystemContext);
    EXPECT_FLOAT_EQ(radialGradientInfo.cx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.cy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fx, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.fy, 30);
    EXPECT_FLOAT_EQ(radialGradientInfo.r, 30);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgPolygonPathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest001, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    Size viewPort(100, 100);
    auto rsPath = svgPolygon->AsPath(viewPort);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest002
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest002, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "abc";
    Size viewPort(100, 100);
    auto rsPath = svgPolygon->AsPath(viewPort);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest003
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest003, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "200 210";
    Size viewPort(100, 100);
    auto rsPath = svgPolygon->AsPath(viewPort);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest004
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest004, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgPolygon->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest005
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest005, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "abc";
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgPolygon->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest006
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest006, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "200 210";
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgPolygon->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest007
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest007, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "200 210";
    SvgBaseAttribute attr;
    attr.clipState.clipRule_ = SvgRuleType::SVG_RULE_EVENODD;
    svgPolygon->SetBaseAttributes(attr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgPolygon->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPolygonPathTest008
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPolygonPathTest008, TestSize.Level1)
{
    auto svgPolygon = AceType::DynamicCast<SvgPolygon>(SvgPolygon::CreatePolygon());
    EXPECT_NE(svgPolygon, nullptr);
    svgPolygon->polyAttr_.points = "200 210";
    SvgBaseAttribute attr;
    attr.clipState.clipRule_ = SvgRuleType::SVG_RULE_EVENODD;
    svgPolygon->SetBaseAttributes(attr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    auto rsPath = svgPolygon->AsPath(clipPathRule);
    svgPolygon->path_ = rsPath;
    svgPolygon->lengthRule_ = clipPathRule;
    rsPath = svgPolygon->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgCirclePathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgCirclePathTest001, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgCircle->AsPath(clipPathRule);
    svgCircle->path_ = rsPath;
    svgCircle->lengthRule_ = clipPathRule;
    rsPath = svgCircle->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgDefsPathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgDefsPathTest001, TestSize.Level1)
{
    auto svgDefs = AceType::DynamicCast<SvgDefs>(SvgDefs::Create());
    EXPECT_NE(svgDefs, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgDefs->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgEllipsePathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgEllipsePathTest001, TestSize.Level1)
{
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(SvgEllipse::Create());
    EXPECT_NE(svgEllipse, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgEllipse->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgEllipsePathTest002
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgEllipsePathTest002, TestSize.Level1)
{
    auto svgEllipse = AceType::DynamicCast<SvgEllipse>(SvgEllipse::Create());
    EXPECT_NE(svgEllipse, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgEllipse->AsPath(clipPathRule);
    svgEllipse->path_ = rsPath;
    svgEllipse->lengthRule_ = clipPathRule;
    rsPath = svgEllipse->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgGPathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGPathTest001, TestSize.Level1)
{
    auto svgG = AceType::DynamicCast<SvgG>(SvgG::Create());
    EXPECT_NE(svgG, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgG->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgLinePathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinePathTest001, TestSize.Level1)
{
    auto svgLine = AceType::DynamicCast<SvgLine>(SvgLine::Create());
    EXPECT_NE(svgLine, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgLine->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgPathPathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgPathPathTest001, TestSize.Level1)
{
    auto svgPath = AceType::DynamicCast<SvgPath>(SvgPath::Create());
    EXPECT_NE(svgPath, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    SvgBaseAttribute attr;
    attr.fillState.SetFillRule("evenodd");
    svgPath->SetBaseAttributes(attr);
    svgPath->d_ = "test";
    auto rsPath = svgPath->AsPath(clipPathRule);
    svgPath->path_ = rsPath;
    rsPath = svgPath->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgRectPathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgRectPathTest001, TestSize.Level1)
{
    auto svgRect = AceType::DynamicCast<SvgRect>(SvgRect::Create());
    EXPECT_NE(svgRect, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto rsPath = svgRect->AsPath(clipPathRule);
    svgRect->path_ = rsPath;
    svgRect->lengthRule_ = clipPathRule;
    rsPath = svgRect->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgUsePathTest001
 * @tc.desc: test asPath
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgUsePathTest001, TestSize.Level1)
{
    auto svgUse = AceType::DynamicCast<SvgUse>(SvgUse::Create());
    EXPECT_NE(svgUse, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    SvgBaseAttribute attr;
    attr.href = "testFill";
    svgUse->SetBaseAttributes(attr);
    auto rsPath = svgUse->AsPath(clipPathRule);
    EXPECT_EQ(rsPath.IsValid(), false);
}

/**
 * @tc.name: SvgImageOnDrawTest001
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgImageOnDrawTest001, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgImage->imageAttr_.x = Dimension(5.0);
    svgImage->imageAttr_.y = Dimension(5.0);
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    RSCanvas canvas;
    svgImage->OnDraw(canvas, clipPathRule);
}

/**
 * @tc.name: SvgImageOnDrawTest002
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgImageOnDrawTest002, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgImage->imageAttr_.x = Dimension(5.0);
    svgImage->imageAttr_.y = Dimension(5.0);
    svgImage->imageAttr_.width = Dimension(-5.0);
    svgImage->imageAttr_.height = Dimension(-5.0);
    svgImage->imageAttr_.href = "hrefTest";
    RSCanvas canvas;
    svgImage->OnDraw(canvas, clipPathRule);
}

/**
 * @tc.name: SvgImageOnDrawTest003
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgImageOnDrawTest003, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgImage->imageAttr_.x = Dimension(0.0);
    svgImage->imageAttr_.y = Dimension(0.0);
    svgImage->imageAttr_.width = Dimension(200.0);
    svgImage->imageAttr_.height = Dimension(200.0);
    svgImage->imageAttr_.href = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAA...";
    RSCanvas canvas;
    svgImage->OnDraw(canvas, clipPathRule);
}

/**
 * @tc.name: SvgImageOnDrawTest004
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgImageOnDrawTest004, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgImage->imageAttr_.x = Dimension(0.0);
    svgImage->imageAttr_.y = Dimension(0.0);
    svgImage->imageAttr_.width = Dimension(200.0);
    svgImage->imageAttr_.height = Dimension(200.0);
    svgImage->imageAttr_.href = "image/png;base64,iVBORw0KGgoAAAANSUhEUgAA...";
    RSCanvas canvas;
    svgImage->OnDraw(canvas, clipPathRule);
}

/**
 * @tc.name: SvgImageOnDrawTest005
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgImageOnDrawTest005, TestSize.Level1)
{
    auto svgImage = AceType::DynamicCast<SvgImage>(SvgImage::Create());
    EXPECT_NE(svgImage, nullptr);
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    svgImage->imageAttr_.x = Dimension(0.0);
    svgImage->imageAttr_.y = Dimension(0.0);
    svgImage->imageAttr_.width = Dimension(200.0);
    svgImage->imageAttr_.height = Dimension(200.0);
    svgImage->imageAttr_.href = "data:";
    RSCanvas canvas;
    svgImage->OnDraw(canvas, clipPathRule);
}

/**
 * @tc.name: SvgLengthScaleRuleTest001
 * @tc.desc: test
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLengthScaleRuleTest001, TestSize.Level1)
{
    Rect containerRect(0, 0, 1, 1);
    Size viewPort(1, 1);
    SvgCoordinateSystemContext svgCoordinateSystemContext(containerRect, viewPort);
    SvgLengthScaleRule clipPathRule =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto baseRect = clipPathRule.GetContainerRect();
    EXPECT_EQ(baseRect.Left(), 0);
    EXPECT_EQ(baseRect.Top(), 0);
    EXPECT_EQ(baseRect.Width(), 1);
    EXPECT_EQ(baseRect.Height(), 1);
    auto lengthScaleUnit = clipPathRule.GetLengthScaleUnit();
    EXPECT_EQ(lengthScaleUnit, OHOS::Ace::NG::SvgLengthScaleUnit::USER_SPACE_ON_USE);
    SvgLengthScaleRule clipPathRule2 =
        svgCoordinateSystemContext.BuildScaleRule(OHOS::Ace::NG::SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    EXPECT_EQ(clipPathRule==clipPathRule2, false);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest001, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::optional<Color> fillColorOpt = std::nullopt;
    svgCircle->fillState_.SetColor(Color::TRANSPARENT);
    auto updateFill = svgCircle->UpdateFillStyle(fillColorOpt);
    EXPECT_EQ(updateFill, false);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest002, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::optional<Color> fillColorOpt = std::nullopt;
    svgCircle->fillState_.SetColor(Color::TRANSPARENT);
    OHOS::Ace::Gradient gradient;
    svgCircle->fillState_.SetGradient(gradient);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto updateFill = svgCircle->UpdateFillStyle(fillColorOpt);
    MockContainer::TearDown();
    EXPECT_EQ(updateFill, true);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest003, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::optional<Color> fillColorOpt = std::nullopt;
    svgCircle->fillState_.SetColor(Color::TRANSPARENT);
    OHOS::Ace::Gradient gradient;
    svgCircle->fillState_.SetGradient(gradient);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto updateFill = svgCircle->UpdateFillStyle(fillColorOpt);
    MockContainer::TearDown();
    EXPECT_EQ(updateFill, false);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest004, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::optional<Color> fillColorOpt = std::nullopt;
    svgCircle->fillState_.SetColor(Color::TRANSPARENT);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradientColor1.SetDimension(Dimension(0.5, DimensionUnit::PERCENT));
    OHOS::Ace::GradientColor gradientColor2;
    gradientColor2.SetColor(Color::BLUE);
    gradientColor2.SetDimension(Dimension(1.0, DimensionUnit::PERCENT));
    gradient.AddColor(gradientColor1);
    gradient.AddColor(gradientColor2);
    svgCircle->fillState_.SetGradient(gradient);
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto updateFill = svgCircle->UpdateFillStyle(fillColorOpt);
    MockContainer::TearDown();
    EXPECT_EQ(updateFill, true);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest005, TestSize.Level1)
{
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::optional<Color> fillColorOpt = std::nullopt;
    svgCircle->fillState_.SetColor(Color::RED);
    auto updateFill = svgCircle->UpdateFillStyle(fillColorOpt);
    EXPECT_EQ(updateFill, true);
}

/**
 * @tc.name: SvgSvgOnDrawTest001
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgSvgOnDrawTest001, TestSize.Level1)
{
    auto svgSvg = AceType::DynamicCast<SvgSvg>(SvgSvg::Create());
    EXPECT_NE(svgSvg, nullptr);
    SvgLengthScaleRule lengthRule;
    Testing::MockCanvas rSCanvas;
    ImageColorFilter filter;
    filter.colorFilterMatrix_ = std::make_shared<std::vector<float>>(std::vector<float> {});
    svgSvg->SetColorFilter(filter);
    svgSvg->SetIsRootNode(true);
    svgSvg->OnDraw(rSCanvas, lengthRule);
    EXPECT_EQ(svgSvg->isRootNode_, true);
}

/**
 * @tc.name: SvgStopParseTest001
 * @tc.desc: test parse stop-color
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgStopParseTest001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    auto backupApiVersion = container->GetCurrentApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    /* *
     * @tc.steps: step1. create svgStop node
     */
    auto svgNode = SvgStop::Create();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgNode->SetContext(svgContext);
    auto svgStop = AceType::DynamicCast<SvgStop>(svgNode);
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor(), Color::BLACK);

    /* *
     * @tc.steps: step2. parse stop-color
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stop-color", "rgba(0,49,83,255)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF003153);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "rgb(0,49,83)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF003153);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#3456");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x66334455);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#33445566");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x66334455);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#3344546");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff000000);

    // invalid color-->default color black
    svgStop->ParseAndSetSpecializedAttr("stop-color", "#MF");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff000000);

    /* *
     * @tc.steps: step4. parse stopOpacity
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stopOpacity", "0.0");
    EXPECT_EQ(svgStop->GetGradientColor().GetOpacity(), 0.0);

    /* *
     * @tc.steps: step5. parse properties that do not belong to SvgStop
     * @tc.expected: The property is parse unsuccessfully
     */
    bool parseResult = svgStop->ParseAndSetSpecializedAttr("strokeLinecap", "butt");
    EXPECT_FALSE(parseResult);
    container->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgStopParseTest002
 * @tc.desc: test parse stopcolor
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgStopParseTest002, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    auto backupApiVersion = container->GetCurrentApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    /* *
     * @tc.steps: step1. create svgStop node
     */
    auto svgNode = SvgStop::Create();
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->SetUsrConfigVersion(SVG_FEATURE_SUPPORT_TWO);
    svgNode->SetContext(svgContext);
    auto svgStop = AceType::DynamicCast<SvgStop>(svgNode);
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor(), Color::BLACK);

    /* *
     * @tc.steps: step3. parse stopcolor
     * @tc.expected: The property is parse successfully
     */
    svgStop->ParseAndSetSpecializedAttr("stopColor", "rgba(0,49,83,0.5)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x80003153);

    svgStop->ParseAndSetSpecializedAttr("stopColor", "rgb(0,49,83)");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xFF003153);

    svgStop->ParseAndSetSpecializedAttr("stopColor", "#3456");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x66334455);

    svgStop->ParseAndSetSpecializedAttr("stopColor", "#33445566");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x66334455);

    svgStop->ParseAndSetSpecializedAttr("stopColor", "#3344546");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff000000);

    // invalid color-->default color black
    svgStop->ParseAndSetSpecializedAttr("stopColor", "#MF");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff000000);

    container->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: SvgStopParseTest003
 * @tc.desc: test parse stop-color
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgStopParseTest003, TestSize.Level1)
{
    MockContainer::SetUp();
    auto container = MockContainer::Current();
    auto backupApiVersion = container->GetCurrentApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    /* *
     * @tc.steps: step1. create svgStop node
     */
    auto svgNode = SvgStop::Create();
    auto svgStop = AceType::DynamicCast<SvgStop>(svgNode);
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor(), Color::BLACK);

    /* *
     * @tc.steps: step2. parse stop-color
     * @tc.expected: The property is parse successfully
     */

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#3456");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x33445566);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#33445566");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0x33445566);

    svgStop->ParseAndSetSpecializedAttr("stop-color", "#3344546");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff344546);

    // invalid color-->default color black
    svgStop->ParseAndSetSpecializedAttr("stop-color", "#MF");
    EXPECT_EQ(svgStop->stopAttr_.gradientColor.GetColor().GetValue(), 0xff000000);

    container->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: svgFilterTest002
 * @tc.desc: test g
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, svgFilterTest002, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
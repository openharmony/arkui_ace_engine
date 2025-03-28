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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    svgSvg->ParseAndSetSpecializedAttr("height", "-100");
    svgSvg->ParseAndSetSpecializedAttr("width", "-100");
    Size size(300, 400);
    svgSvg->AsPath(size);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest007, TestSize.Level1)
{
    auto linearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(linearGradient, nullptr);
    auto linearGradientAttr = linearGradient->linearGradientAttr_;
    linearGradientAttr.x1 = 3.0_vp;
    linearGradientAttr.x2 = 35.0_vp;
    linearGradientAttr.y1 = 31.0_vp;
    linearGradientAttr.y2 = 32.0_vp;
    linearGradientAttr.gradientTransform = "gradientTransform11";
    linearGradient->linearGradientAttr_.gradientUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    linearGradient->SetAttr("gradienttransform", "val1");
    EXPECT_EQ(linearGradient->linearGradientAttr_.gradientTransform, "");

    linearGradient->SetAttr("gradientunits", "userSpaceOnUse");
    EXPECT_EQ(linearGradient->linearGradientAttr_.gradientUnits, SvgLengthScaleUnit::USER_SPACE_ON_USE);

    linearGradient->SetAttr("gradientunits", "userSpaceOnUse22");
    linearGradient->linearGradientAttr_.gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    EXPECT_EQ(linearGradient->linearGradientAttr_.gradientUnits, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);

    linearGradient->SetAttr("spreadmethod", "repeat");
    linearGradient->linearGradientAttr_.spreadMethod = SvgSpreadMethod::REPEAT;
    EXPECT_EQ(linearGradient->linearGradientAttr_.spreadMethod, SvgSpreadMethod::REPEAT);

    linearGradient->SetAttr("spreadmethod", "reflect");
    linearGradient->linearGradientAttr_.spreadMethod = SvgSpreadMethod::REFLECT;
    EXPECT_EQ(linearGradient->linearGradientAttr_.spreadMethod, SvgSpreadMethod::REFLECT);

    linearGradient->linearGradientAttr_.spreadMethod = SvgSpreadMethod::PAD;
    linearGradient->SetAttr("spreadmethod", "reflect222");
    EXPECT_EQ(linearGradient->linearGradientAttr_.spreadMethod, SvgSpreadMethod::PAD);

    linearGradient->linearGradientAttr_.x1 = 20.0_px;
    linearGradient->SetAttr("x1", "20");
    EXPECT_EQ(linearGradient->linearGradientAttr_.x1.ToString(), "20.00px");

    linearGradient->linearGradientAttr_.x2 = 35.0_vp;
    linearGradient->SetAttr("x2", "20");
    EXPECT_EQ(linearGradient->linearGradientAttr_.x2.ToString(), "35.00vp");

    linearGradient->linearGradientAttr_.y1 = 31.0_vp;
    linearGradient->SetAttr("y1", "20");
    EXPECT_EQ(linearGradient->linearGradientAttr_.y1.ToString(), "31.00vp");

    linearGradient->linearGradientAttr_.y2 = 32.0_vp;
    linearGradient->SetAttr("y2", "20");
    EXPECT_EQ(linearGradient->linearGradientAttr_.y2.ToString(), "32.00vp");

    linearGradient->linearGradientAttr_.y2 = 32.0_vp;
    linearGradient->SetAttr("y22", "20");
    EXPECT_EQ(linearGradient->linearGradientAttr_.y2.ToString(), "32.00vp");
}

/**
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest008, TestSize.Level1)
{
    RefPtr<SvgLinearGradient> linearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(linearGradient, nullptr);
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);

    auto info = linearGradient->GetLinearGradientInfo(context);
    EXPECT_EQ(info.x1, 0);
    EXPECT_EQ(info.x2, 1);
    EXPECT_EQ(info.y1, 0);
    EXPECT_EQ(info.y2, 0);
    EXPECT_EQ(info.spreadMethod, 0);
    EXPECT_EQ(info.gradientTransform, "");
    EXPECT_EQ(info.colors.size(), 0);
}

/**
 * @tc.name: Svg Linear Gradient
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgLinearGradientTest009, TestSize.Level1)
{
    auto linearGradient = AceType::DynamicCast<SvgLinearGradient>(SvgLinearGradient::Create());
    EXPECT_NE(linearGradient, nullptr);

    linearGradient->linearGradientAttr_.gradientUnits = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    auto units = linearGradient->GradientUnits();
    EXPECT_EQ(units, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);

    units = linearGradient->GradientUnits();
    linearGradient->linearGradientAttr_.gradientUnits = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    EXPECT_EQ(units, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    /* *
     * @tc.steps: step1. create svgStop node
     */
    auto svgNode = SvgStop::Create();
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
 * @tc.name: Svg Graphic
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest006, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    svgGraphic->fillState_.SetHref("href");
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "href");
    svgContext->Push("href", svgGraphic);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "href");
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Testing::MockCanvas rSCanvas;
    Size size(20, 10);
    std::optional<Color> color = Color::BLACK;
    svgGraphic->OnDraw(rSCanvas, size, color);
    MockContainer::Current()->TearDown();
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "");
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest007, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    svgGraphic->fillState_.SetHref("href");
    svgContext->Push("href", svgGraphic);

    Testing::MockCanvas rSCanvas;
    Size size(50, 70);
    std::optional<Color> color = Color::TRANSPARENT;
    svgGraphic->OnDraw(rSCanvas, size, color);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "");
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test CheckHrefPattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest008, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    EXPECT_FALSE(svgGraphic->CheckHrefPattern());

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    EXPECT_FALSE(svgGraphic->CheckHrefPattern());
    svgGraphic->fillState_.SetHref("href1");
    auto svgGraphic1 = AceType::MakeRefPtr<SvgGraphic>();
    svgContext->Push("href1", svgGraphic1);
    EXPECT_FALSE(svgGraphic->CheckHrefPattern());

    auto svgPattern = AceType::MakeRefPtr<SvgPattern>();
    svgGraphic->fillState_.SetHref("href");
    svgContext->Push("href", svgPattern);
    EXPECT_TRUE(svgGraphic->CheckHrefPattern());
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest009, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    svgGraphic->fillState_.SetHref("href");
    Testing::MockCanvas rSCanvas;
    Size size(50, 70);
    std::optional<Color> color = Color::TRANSPARENT;
    svgGraphic->OnDraw(rSCanvas, size, color);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "");
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test GetHrefType
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest010, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto paintType = svgGraphic->GetHrefType("href");
    EXPECT_EQ(paintType, PaintType::NONE);

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    paintType = svgGraphic->GetHrefType("href");
    EXPECT_EQ(paintType, PaintType::NONE);

    auto svgPattern = AceType::MakeRefPtr<SvgPattern>();
    EXPECT_NE(svgPattern, nullptr);
    svgContext->Push("href", svgPattern);
    paintType = svgGraphic->GetHrefType("href");
    EXPECT_EQ(paintType, PaintType::PATTERN);

    auto linearGradient = SvgLinearGradient::Create();
    EXPECT_NE(linearGradient, nullptr);
    svgContext->Push("gradient", linearGradient);
    paintType = svgGraphic->GetHrefType("gradient");
    EXPECT_EQ(paintType, PaintType::LINEAR_GRADIENT);

    auto radialGradient = SvgRadialGradient::Create();
    EXPECT_NE(radialGradient, nullptr);
    svgContext->Push("radial", radialGradient);
    paintType = svgGraphic->GetHrefType("radial");
    EXPECT_EQ(paintType, PaintType::RADIAL_GRADIENT);

    auto graphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(graphic, nullptr);
    svgContext->Push("graphic1", graphic);
    paintType = svgGraphic->GetHrefType("graphic1");
    EXPECT_EQ(paintType, PaintType::NONE);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test OnDraw
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest011, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    SvgLengthScaleRule rule;
    Testing::MockCanvas rSCanvas;
    svgGraphic->OnDraw(rSCanvas, rule);
    Rect rect(10, 10, 50, 50);
    Size size(80, 80);
    SvgLengthScaleRule rule1(rect, size, SvgLengthScaleUnit::USER_SPACE_ON_USE);
    auto svgPattern = AceType::MakeRefPtr<SvgPattern>();
    EXPECT_NE(svgPattern, nullptr);
    svgContext->Push("svgPattern", svgPattern);
    svgGraphic->attributes_.fillState.SetHref("svgPattern");
    svgGraphic->attributes_.strokeState.SetHref("svgPattern");
    svgGraphic->attributes_.strokeState.lineWidth_ = AnimatableDimension(1.0);
    svgGraphic->OnDraw(rSCanvas, rule1);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "");
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest012, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);

    svgGraphic->attributes_.fillState.SetIsFillNone(true);
    auto fillType = svgGraphic->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);

    svgGraphic->attributes_.fillState.SetIsFillNone(false);
    svgGraphic->attributes_.fillState.SetHref("href");
    fillType = svgGraphic->GetFillType();
    EXPECT_EQ(fillType, PaintType::NONE);

    svgGraphic->attributes_.fillState.SetColor(Color::BLACK);
    svgGraphic->attributes_.fillState.SetHref("");
    fillType = svgGraphic->GetFillType();
    EXPECT_EQ(fillType, PaintType::COLOR);

    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    svgGraphic->attributes_.fillState.SetColor(Color::BLACK, false);
    EXPECT_EQ(fillType, PaintType::COLOR);

    gradient.SetHref("href");
    EXPECT_EQ(fillType, PaintType::COLOR);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest013, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Size size(50, 50);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::LinearGradient linearGradient;
    linearGradient.x1 = 10.0_vp;
    linearGradient.x2 = 15.0_vp;
    linearGradient.y1 = 10.0_vp;
    linearGradient.y2 = 16.0_vp;
    gradient.SetLinearGradient(linearGradient);
    svgGraphic->SetLinearGradient(size, gradient);
    EXPECT_TRUE(gradient.linearGradient_.x1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.x2.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y2.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearX.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearY.has_value());
    EXPECT_FALSE(gradient.linearGradient_.angle.has_value());

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Size size1(0, 0);
    svgGraphic->SetLinearGradient(size1, gradient);
    MockContainer::Current()->TearDown();
    EXPECT_TRUE(gradient.linearGradient_.x1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.x2.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y2.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearX.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearY.has_value());
    EXPECT_FALSE(gradient.linearGradient_.angle.has_value());
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest014, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Size size(50, 50);
    OHOS::Ace::Gradient gradient;

    OHOS::Ace::RadialGradient radialGradientLocal;
    radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
    radialGradientLocal.radialCenterX = AnimatableDimension(1);
    radialGradientLocal.radialCenterY = AnimatableDimension(1);
    radialGradientLocal.fRadialCenterX = Dimension(1);
    radialGradientLocal.fRadialCenterY = Dimension(1);
    gradient.SetRadialGradient(radialGradientLocal);

    svgGraphic->SetRadialGradient(size, gradient);
    EXPECT_EQ(gradient.radialGradientInfo_.r, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.cx, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.cy, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.fx, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 1);

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Size size1(0, 0);
    svgGraphic->SetRadialGradient(size1, gradient);
    MockContainer::Current()->TearDown();
    EXPECT_EQ(gradient.radialGradientInfo_.r, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.cx, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.cy, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.fx, 1);
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 1);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest015, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Size size(50, 50);
    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    OHOS::Ace::RadialGradient radialGradientLocal;
    radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
    radialGradientLocal.radialCenterX = AnimatableDimension(1);
    radialGradientLocal.radialCenterY = AnimatableDimension(1);
    radialGradientLocal.fRadialCenterX = Dimension(1);
    radialGradientLocal.fRadialCenterY = Dimension(1);
    gradient.SetRadialGradient(radialGradientLocal);

    svgGraphic->UpdateFillGradient(size);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.r, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cy, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fy, 0);

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Size size1(0, 0);
    svgGraphic->UpdateFillGradient(size1);
    MockContainer::Current()->TearDown();
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.r, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cy, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fy, 0);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest016, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Size size(50, 50);
    OHOS::Ace::Gradient gradient;
    gradient.type_ = OHOS::Ace::GradientType::RADIAL;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    OHOS::Ace::RadialGradient radialGradientLocal;
    radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
    radialGradientLocal.radialCenterX = AnimatableDimension(1);
    radialGradientLocal.radialCenterY = AnimatableDimension(1);
    radialGradientLocal.fRadialCenterX = Dimension(1);
    radialGradientLocal.fRadialCenterY = Dimension(1);
    gradient.SetRadialGradient(radialGradientLocal);

    svgGraphic->UpdateFillGradient(size);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.r, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cy, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fy, 0);

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Size size1(0, 0);
    svgGraphic->UpdateFillGradient(size1);
    MockContainer::Current()->TearDown();
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.r, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cy, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fy, 0);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest017, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    EXPECT_FALSE(svgGraphic->GradientHasColors());
    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    EXPECT_FALSE(svgGraphic->GradientHasColors());
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    EXPECT_FALSE(svgGraphic->GradientHasColors());
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    EXPECT_TRUE(svgGraphic->GradientHasColors());
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest018, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Testing::MockCanvas canvas;
    RSBrush brush;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto result = svgGraphic->InitBrush(canvas, brush, context, PaintType::NONE);
    EXPECT_TRUE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::LINEAR_GRADIENT);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::RADIAL_GRADIENT);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::PATTERN);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::NONE);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest019, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Testing::MockCanvas canvas;
    RSBrush brush;

    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto result = svgGraphic->InitBrush(canvas, brush, context, PaintType::COLOR);
    EXPECT_TRUE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::LINEAR_GRADIENT);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::RADIAL_GRADIENT);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::PATTERN);
    EXPECT_FALSE(result);
    result = svgGraphic->InitBrush(canvas, brush, context, PaintType::NONE);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest020, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSBrush brush;
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 2.0f;
    svgGraphic->SetBrushColor(brush, false);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "");
    auto svgPattern = AceType::DynamicCast<SvgPattern>(SvgPattern::Create());
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->Push("myPattern", svgPattern);
    svgGraphic->fillState_.href_ = "myPattern";
    svgGraphic->SetContext(svgContext);
    svgContext->fillColor_ = Color::BLACK;
    svgGraphic->SetBrushColor(brush, false);
    svgGraphic->attributes_.fillState.isFillNone_ = true;
    svgGraphic->SetBrushColor(brush, true);
    EXPECT_EQ(svgGraphic->fillState_.GetHref(), "myPattern");
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest021, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSBrush brush;
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 2.0f;
    SvgLinearGradientInfo info;
    info.x1 = 10.0f;
    info.x2 = 10.0f;
    info.y1 = 10.0f;
    info.y2 = 10.0f;

    info.spreadMethod = 10;
    info.gradientTransform = "gradientTransform";

    info.colors.emplace_back(GradientColor(Color::BLACK));
    info.colors.emplace_back(GradientColor(Color::BLUE));
    info.colors.emplace_back(GradientColor(Color::WHITE));
    info.colors.emplace_back(GradientColor(Color::RED));
    info.colors.emplace_back(GradientColor(Color::TRANSPARENT));

    auto linearGradient = svgGraphic->ConvertToRsLinearGradient(info);
    EXPECT_EQ(linearGradient.startPoint_.GetX(), 10.0f);
    EXPECT_EQ(linearGradient.startPoint_.GetY(), 10.0f);
    EXPECT_EQ(linearGradient.endPoint_.GetX(), 10.0f);
    EXPECT_EQ(linearGradient.endPoint_.GetY(), 10.0f);
    EXPECT_EQ(static_cast<int32_t>(linearGradient.spreadMethod_), 10);
    EXPECT_EQ(static_cast<int32_t>(linearGradient.pos_.size()), 6);
    EXPECT_EQ(static_cast<int32_t>(linearGradient.colors_.size()), 6);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest022, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    OHOS::Ace::Gradient gradient;
    OHOS::Ace::LinearGradient linearGradient;
    linearGradient.x1 = 13.0_vp;
    linearGradient.x2 = 15.0_vp;
    linearGradient.y1 = 11.0_vp;
    linearGradient.y2 = 10.0_vp;
    gradient.SetLinearGradient(linearGradient);
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    Size size(50, 60);
    svgGraphic->UpdateStrokeGradient(size);
    EXPECT_TRUE(gradient.linearGradient_.x1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.x2.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y1.has_value());
    EXPECT_TRUE(gradient.linearGradient_.y2.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearX.has_value());
    EXPECT_FALSE(gradient.linearGradient_.linearY.has_value());
    EXPECT_FALSE(gradient.linearGradient_.angle.has_value());
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest023, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    OHOS::Ace::Gradient gradient;

    gradient.type_ = OHOS::Ace::GradientType::RADIAL;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    OHOS::Ace::RadialGradient radialGradientLocal;
    radialGradientLocal.radialHorizontalSize = AnimatableDimension(1);
    radialGradientLocal.radialCenterX = AnimatableDimension(1);
    radialGradientLocal.radialCenterY = AnimatableDimension(1);
    radialGradientLocal.fRadialCenterX = Dimension(1);
    radialGradientLocal.fRadialCenterY = Dimension(1);
    gradient.SetRadialGradient(radialGradientLocal);
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    Size size(50, 60);
    svgGraphic->UpdateStrokeGradient(size);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.r, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.cy, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fx, 0);
    EXPECT_EQ(svgGraphic->attributes_.fillState.gradient_->radialGradientInfo_.fy, 0);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest024, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    OHOS::Ace::Gradient gradient;
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    svgGraphic->fillState_.href_ = "myPattern";
    svgGraphic->fillState_.SetColor(Color::BLACK);
    auto svgPattern = AceType::MakeRefPtr<SvgPattern>();
    svgGraphic->fillState_.SetHref("href");
    svgContext->Push("href", svgPattern);
    EXPECT_TRUE(svgGraphic->CheckHrefPattern());
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto result = svgGraphic->UpdateFillStyle(Color::BLACK, true);
    MockContainer::Current()->TearDown();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetGradientFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest025, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    OHOS::Ace::Gradient gradient;
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;

    OHOS::Ace::RadialGradientInfo info;
    info.cx = 10.0f;
    info.cy = 30.0f;
    info.r = 5.0f;
    info.fx = 11.0f;
    info.fy = 16.0f;
    gradient.SetRadialGradientInfo(info);
    svgGraphic->SetGradientFillStyle(gradient, pos, colors);
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 16.0f);
    info.cx = 10.0f;
    info.cy = 30.0f;
    info.fx = 10.0f;
    info.fy = 30.0f;
    gradient.SetRadialGradientInfo(info);
    svgGraphic->SetGradientFillStyle(gradient, pos, colors);
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 30.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetGradientFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest026, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    OHOS::Ace::Gradient gradient;
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;

    OHOS::Ace::RadialGradientInfo info;
    info.cx = 10.0f;
    info.cy = 30.0f;
    info.r = 5.0f;
    info.fx = 11.0f;
    info.fy = 16.0f;
    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    svgGraphic->SetGradientFillStyle(gradient, pos, colors);
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 0.0f);
    info.cx = 10.0f;
    info.cy = 30.0f;
    info.fx = 10.0f;
    info.fy = 30.0f;
    svgGraphic->SetGradientFillStyle(gradient, pos, colors);
    MockContainer::Current()->TearDown();
    EXPECT_EQ(gradient.radialGradientInfo_.fy, 0.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetGradientFillStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest027, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    SvgLengthScaleUnit unit = SvgLengthScaleUnit::USER_SPACE_ON_USE;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto matrix = svgGraphic->GetLocalMatrix(unit, context);
    auto result = matrix.Get(2);
    EXPECT_EQ(result, 1.0f);

    unit = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
    Rect rect1(10, 12, 13, 15);
    Size size1(10, 10);
    SvgCoordinateSystemContext context1(rect1, size1);
    matrix = svgGraphic->GetLocalMatrix(unit, context1);
    result = matrix.Get(2);
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetBrushLinearGradient
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest028, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    RSBrush brush;

    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto result = svgGraphic->SetBrushLinearGradient(brush, context);
    EXPECT_FALSE(result);

    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    auto linearGradient = SvgLinearGradient::Create();

    svgGraphic->attributes_.fillState.SetHref("href");
    svgContext->Push("href", linearGradient);
    result = svgGraphic->SetBrushLinearGradient(brush, context);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetBrushLinearGradient
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest029, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    SvgRadialGradientInfo info;
    info.cx = 12.0f;
    info.cy = 13.0f;
    info.r = 14.0f;
    info.fx = 15.0f;
    info.fy = 160.0f;
    info.spreadMethod = 20;
    info.gradientTransform = "gradientTransform";

    info.colors.emplace_back(GradientColor(Color::BLACK));
    info.colors.emplace_back(GradientColor(Color::BLUE));
    info.colors.emplace_back(GradientColor(Color::WHITE));
    info.colors.emplace_back(GradientColor(Color::RED));
    info.colors.emplace_back(GradientColor(Color::TRANSPARENT));
    auto gradient = svgGraphic->ConvertToRsRadialGradient(info);
    EXPECT_EQ(gradient.center_.GetX(), 12.0f);
    EXPECT_EQ(gradient.center_.GetY(), 13.0f);
    EXPECT_EQ(gradient.focal_.GetX(), 15.0f);
    EXPECT_EQ(gradient.focal_.GetY(), 160.0f);
    EXPECT_EQ(static_cast<int32_t>(gradient.spreadMethod_), 20);
    EXPECT_EQ(gradient.r_, 14.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetBrushRadialGradient
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest030, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    RSBrush brush;
    auto result = svgGraphic->SetBrushRadialGradient(brush, context);
    EXPECT_FALSE(result);

    OHOS::Ace::Gradient gradient;
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    svgGraphic->attributes_.fillState.SetGradient(gradient);

    auto radialGradient = SvgRadialGradient::Create();

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgContext->Push("href", radialGradient);
    svgGraphic->SetContext(svgContext);
    svgGraphic->attributes_.fillState.SetHref("href");
    result = svgGraphic->SetBrushRadialGradient(brush, context);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetBrushPattern
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest031, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);

    Testing::MockCanvas canvas;
    RSBrush brush;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto result = svgGraphic->SetBrushPattern(canvas, brush, context);
    EXPECT_FALSE(result);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    result = svgGraphic->SetBrushPattern(canvas, brush, context);
    EXPECT_FALSE(result);
    svgGraphic->attributes_.fillState.SetHref("href");
    svgContext->Push("href", svgGraphic);

    result = svgGraphic->SetBrushPattern(canvas, brush, context);
    EXPECT_FALSE(result);
    auto pattern = AceType::MakeRefPtr<SvgPattern>();
    svgGraphic->attributes_.fillState.SetHref("href1");
    svgContext->Push("href1", pattern);
    result = svgGraphic->SetBrushPattern(canvas, brush, context);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test GetFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest032, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 63.0f;
    svgGraphic->attributes_.fillState.SetOpacity(2.0f);
    auto result = svgGraphic->GetFillOpacity();
    EXPECT_EQ(result, 2.0f);

    svgGraphic->attributes_.hasOpacity = false;
    svgGraphic->attributes_.fillState.SetOpacity(25.0f);
    result = svgGraphic->GetFillOpacity();
    EXPECT_EQ(result, 25.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test GetStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest033, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 63.0f;
    svgGraphic->attributes_.strokeState.SetOpacity(2.0f);
    auto result = svgGraphic->GetStrokeOpacity();
    EXPECT_EQ(result, 2.0f);

    svgGraphic->attributes_.hasOpacity = false;
    svgGraphic->attributes_.strokeState.SetOpacity(25.0f);
    result = svgGraphic->GetStrokeOpacity();
    EXPECT_EQ(result, 25.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetBrushOpacity
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest034, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    RSBrush brush;
    EXPECT_NE(svgGraphic, nullptr);
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 126.0f;
    svgGraphic->attributes_.fillState.SetOpacity(2.0f);
    auto result = svgGraphic->GetFillOpacity();
    svgGraphic->SetBrushOpacity(brush); //
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetPenOpacity
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest035, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 63.0f;
    svgGraphic->attributes_.strokeState.SetOpacity(2.0f);
    auto result = svgGraphic->GetStrokeOpacity();
    svgGraphic->SetPenOpacity(pen);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetGradientStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest036, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto result = svgGraphic->SetGradientStyle(2.0f);
    EXPECT_FALSE(result);
    OHOS::Ace::Gradient gradient;
    svgGraphic->fillState_.SetGradient(gradient);
    result = svgGraphic->SetGradientStyle(2.0f);
    EXPECT_FALSE(result);
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    svgGraphic->fillState_.SetGradient(gradient);
    result = svgGraphic->SetGradientStyle(2.0f);
    EXPECT_TRUE(result);

    OHOS::Ace::Gradient gradient1;
    gradient1.type_ = OHOS::Ace::GradientType::RADIAL;
    OHOS::Ace::GradientColor gradientColor2;
    gradientColor2.SetColor(Color::RED);
    OHOS::Ace::GradientColor gradientColor3;
    gradientColor3.SetColor(Color::BLACK);
    gradient1.colors_.emplace_back(gradientColor2);
    gradient1.colors_.emplace_back(gradientColor3);
    result = svgGraphic->SetGradientStyle(2.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetStrokeGradientStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest037, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    svgGraphic->SetStrokeGradientStyle(2.0f);
    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    svgGraphic->SetStrokeGradientStyle(2.0f);

    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    svgGraphic->SetStrokeGradientStyle(2.0f);

    OHOS::Ace::Gradient gradient1;
    gradient1.type_ = OHOS::Ace::GradientType::RADIAL;
    OHOS::Ace::GradientColor gradientColor2;
    gradientColor2.SetColor(Color::RED);
    OHOS::Ace::GradientColor gradientColor3;
    gradientColor3.SetColor(Color::BLACK);
    gradient1.colors_.emplace_back(gradientColor2);
    gradient1.colors_.emplace_back(gradientColor3);
    svgGraphic->attributes_.strokeState.SetGradient(gradient1);
    svgGraphic->SetStrokeGradientStyle(2.0f);
    EXPECT_EQ(static_cast<int32_t>(gradient1.colors_.size()), 2);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test GetStrokeType
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest038, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::NONE);

    svgGraphic->attributes_.strokeState.SetColor(Color::BLACK);
    type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::COLOR);

    svgGraphic->attributes_.strokeState.SetColor(Color::RED, false);
    svgGraphic->attributes_.strokeState.SetHref("href");
    type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::NONE);

    svgGraphic->attributes_.strokeState.SetHref("");
    type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::COLOR);

    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::COLOR);

    gradient.SetHref("href");
    svgGraphic->attributes_.strokeState.SetGradient(gradient);
    type = svgGraphic->GetStrokeType();
    EXPECT_EQ(type, PaintType::NONE);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test InitPenFill
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest039, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);
    auto type = PaintType::COLOR;
    auto result = svgGraphic->InitPenFill(pen, context, type);
    EXPECT_TRUE(result);

    type = PaintType::LINEAR_GRADIENT;
    result = svgGraphic->InitPenFill(pen, context, type);
    EXPECT_FALSE(result);

    type = PaintType::RADIAL_GRADIENT;
    result = svgGraphic->InitPenFill(pen, context, type);
    EXPECT_FALSE(result);

    type = PaintType::PATTERN;
    result = svgGraphic->InitPenFill(pen, context, type);
    EXPECT_TRUE(result);

    type = PaintType::NONE;
    result = svgGraphic->InitPenFill(pen, context, type);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetPenStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest040, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::ROUND);
    svgGraphic->SetPenStyle(pen);
    EXPECT_EQ(svgGraphic->attributes_.strokeState.GetLineCap(), LineCapStyle::ROUND);

    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::SQUARE);
    svgGraphic->SetPenStyle(pen);
    EXPECT_EQ(svgGraphic->attributes_.strokeState.GetLineCap(), LineCapStyle::SQUARE);

    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::BUTT);
    svgGraphic->SetPenStyle(pen);
    EXPECT_EQ(svgGraphic->attributes_.strokeState.GetLineCap(), LineCapStyle::BUTT);

    svgGraphic->attributes_.strokeState.SetLineJoin(LineJoinStyle::ROUND);
    svgGraphic->SetPenStyle(pen);
    EXPECT_EQ(svgGraphic->attributes_.strokeState.GetLineJoin(), LineJoinStyle::ROUND);

    svgGraphic->attributes_.strokeState.SetLineJoin(LineJoinStyle::BEVEL);
    svgGraphic->SetPenStyle(pen);
    EXPECT_EQ(svgGraphic->attributes_.strokeState.GetLineJoin(), LineJoinStyle::BEVEL);

    auto lineDashState = svgGraphic->attributes_.strokeState.GetLineDash().lineDash;
    lineDashState.emplace_back(1.3f);
    EXPECT_EQ(static_cast<int32_t>(lineDashState.size()), 1);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateStrokeStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest041, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_FALSE(result);

    svgGraphic->attributes_.strokeState.SetColor(Color::BLACK);
    svgGraphic->attributes_.strokeState.SetLineWidth(0.0_vp);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_FALSE(result); // 实际为true

    svgGraphic->attributes_.strokeState.SetLineWidth(20.0_vp);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);
    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.strokeState.SetGradient(gradient);

    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::ROUND);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);

    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::SQUARE);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);

    svgGraphic->attributes_.strokeState.SetLineCap(LineCapStyle::BUTT);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);

    svgGraphic->attributes_.strokeState.SetLineJoin(LineJoinStyle::ROUND);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);

    svgGraphic->attributes_.strokeState.SetLineJoin(LineJoinStyle::BEVEL);
    result = svgGraphic->UpdateStrokeStyle(false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateStrokeStyle
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest042, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto lineDashState = svgGraphic->attributes_.strokeState.GetLineDash().lineDash;
    lineDashState.emplace_back(1.3f);
    lineDashState.emplace_back(1.5f);
    lineDashState.emplace_back(4.3f);

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    svgGraphic->UpdateLineDash();
    EXPECT_EQ(static_cast<int32_t>(lineDashState.size()), 3);
    MockContainer::Current()->TearDown();

    MockContainer::SetUp();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    svgGraphic->UpdateLineDash();
    EXPECT_EQ(static_cast<int32_t>(lineDashState.size()), 3);
    MockContainer::Current()->TearDown();
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetPenColor
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest043, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    svgGraphic->attributes_.hasOpacity = true;
    svgGraphic->attributes_.opacity = 63.0f;
    svgGraphic->attributes_.strokeState.SetOpacity(2.0f);
    svgGraphic->SetPenColor(pen);
    auto result = svgGraphic->GetStrokeOpacity();
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test AddColorFilterEffect
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest044, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    svgGraphic->AddColorFilterEffect(pen);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    ImageColorFilter filter;
    svgGraphic->colorFilter_ = filter;
    svgGraphic->AddColorFilterEffect(pen);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    filter.colorFilterMatrix_ = std::make_shared<std::vector<float>>(std::vector<float> { 0.5f, 0.3f, 0.7f });
    svgGraphic->colorFilter_ = filter;
    svgGraphic->AddColorFilterEffect(pen);
    EXPECT_NE(pen.GetWidth(), 4.0f);

    filter.colorFilterMatrix_ = nullptr;
    svgGraphic->colorFilter_ = filter;
    svgGraphic->AddColorFilterEffect(pen);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    const std::vector<float>& drawingMatrix = { 4.0, 2.0 };
    auto colorFilterDrawing = DrawingColorFilter::CreateDrawingColorFilter(drawingMatrix);
    filter.colorFilterDrawing_ = colorFilterDrawing;
    svgGraphic->colorFilter_ = filter;
    svgGraphic->AddColorFilterEffect(pen);
    EXPECT_NE(pen.GetWidth(), 3.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test UpdateColorFilter
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest045, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSFilter filter;
    RSPen pen;
    pen.SetFilter(filter);
    svgGraphic->UpdateColorFilter(filter);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    ImageColorFilter imageColorFilter;
    svgGraphic->colorFilter_ = imageColorFilter;
    svgGraphic->UpdateColorFilter(filter);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    imageColorFilter.colorFilterMatrix_ = std::make_shared<std::vector<float>>(std::vector<float> { 0.5f, 0.3f, 0.7f });
    svgGraphic->colorFilter_ = imageColorFilter;
    svgGraphic->UpdateColorFilter(filter);
    EXPECT_NE(pen.GetWidth(), 4.0f);

    imageColorFilter.colorFilterMatrix_ = nullptr;
    svgGraphic->colorFilter_ = imageColorFilter;
    svgGraphic->UpdateColorFilter(filter);
    EXPECT_EQ(pen.GetWidth(), 0.0f);

    const std::vector<float>& drawingMatrix = { 4.0, 2.0 };
    auto colorFilterDrawing = DrawingColorFilter::CreateDrawingColorFilter(drawingMatrix);
    imageColorFilter.colorFilterDrawing_ = colorFilterDrawing;
    svgGraphic->colorFilter_ = imageColorFilter;
    svgGraphic->UpdateColorFilter(filter);
    EXPECT_NE(pen.GetWidth(), 3.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test RectifyTargetSize
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest046, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    double width = 10.0f;
    double height = 12.0f;
    Rect rect(10, 12, 13, 0);
    svgGraphic->RectifyTargetSize(rect, width, height);
    EXPECT_EQ(width, 10.0f);
    EXPECT_EQ(height, 12.0f);

    Rect rect1(10, 12, 10, 10);
    svgGraphic->RectifyTargetSize(rect, width, height);
    EXPECT_EQ(width, 10.0f);
    EXPECT_EQ(height, 12.0f);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test SetPenLinearGradient
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest047, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSPen pen;
    Rect rect(10, 12, 13, 15);
    Size size(10, 10);
    SvgCoordinateSystemContext context(rect, size);

    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));
    OHOS::Ace::Gradient gradient;
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));
    OHOS::Ace::GradientColor gradientColor1;
    gradientColor1.SetColor(Color::RED);
    gradient.colors_.emplace_back(gradientColor1);
    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));
    svgGraphic->attributes_.fillState.SetGradient(gradient);
    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));

    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);
    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));

    auto svgPattern = AceType::MakeRefPtr<SvgPattern>();
    svgGraphic->attributes_.strokeState.SetHref("myPattern");
    svgContext->Push("myPattern", svgPattern);
    EXPECT_FALSE(svgGraphic->SetPenRadialGradient(pen, context));

    auto radialGradient = SvgRadialGradient::Create();
    svgContext->Push("radialGradient", radialGradient);
    svgGraphic->attributes_.strokeState.SetHref("radialGradient");
    EXPECT_TRUE(svgGraphic->SetPenRadialGradient(pen, context));
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test GetFillColor
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest048, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    auto result = svgGraphic->GetFillColor();
    EXPECT_EQ(result, std::nullopt);
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    svgGraphic->SetContext(svgContext);

    result = svgGraphic->GetFillColor();
    EXPECT_EQ(result, std::nullopt);

    std::optional<Color> color = Color::BLACK;
    svgContext->SetFillColor(color);
    result = svgGraphic->GetFillColor();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), Color::BLACK);
}

/**
 * @tc.name: Svg Graphic
 * @tc.desc: test ApplyTransform
 * @tc.type: FUNC
 */
HWTEST_F(SvgNodeTestNg, SvgGraphicTest049, TestSize.Level1)
{
    auto svgGraphic = AceType::MakeRefPtr<SvgGraphic>();
    EXPECT_NE(svgGraphic, nullptr);
    RSRecordingPath path;
    svgGraphic->ApplyTransform(path);
    EXPECT_EQ(path.GetLength(false), 0);
    std::vector<NG::TransformInfo> transformVec;
    NG::TransformInfo info;
    transformVec.emplace_back(info);
    svgGraphic->attributes_.transformVec = transformVec;
    svgGraphic->ApplyTransform(path);
    EXPECT_EQ(path.GetLength(true), 0);

    std::vector<NG::TransformInfo> transformVec1;
    NG::TransformInfo info1;
    info1.funcType = "translate";
    transformVec1.emplace_back(info);
    svgGraphic->attributes_.transformVec = transformVec1;
    svgGraphic->ApplyTransform(path);
    EXPECT_NE(path.GetLength(false), 20);
}
} // namespace OHOS::Ace::NG
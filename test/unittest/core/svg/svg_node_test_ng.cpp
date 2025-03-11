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
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_polygon.h"
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

class MockSvgGraphic : public SvgGraphic {
public:
    MockSvgGraphic() = default;
    ~MockSvgGraphic() = default;

    MOCK_METHOD2(SetLinearGradient, void(const Size& viewPort, OHOS::Ace::Gradient& gradient));
    MOCK_METHOD2(SetRadialGradient, void(const Size& viewPort, OHOS::Ace::Gradient& gradient));
    MOCK_METHOD3(RectifyTargetSize, void(const Rect& bounds, double& width, double& height));
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
} // namespace OHOS::Ace::NG
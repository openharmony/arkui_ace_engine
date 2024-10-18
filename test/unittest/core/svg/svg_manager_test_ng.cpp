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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
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
#include "core/components_ng/svg/parse/svg_ellipse.h"
#include "core/components_ng/svg/parse/svg_fe_blend.h"
#include "core/components_ng/svg/parse/svg_fe_color_matrix.h"
#include "core/components_ng/svg/parse/svg_fe_composite.h"
#include "core/components_ng/svg/parse/svg_fe_flood.h"
#include "core/components_ng/svg/parse/svg_fe_gaussian_blur.h"
#include "core/components_ng/svg/parse/svg_filter.h"
#include "core/components_ng/svg/parse/svg_g.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
#include "core/components_ng/svg/parse/svg_image.h"
#include "core/components_ng/svg/parse/svg_line.h"
#include "core/components_ng/svg/parse/svg_mask.h"
#include "core/components_ng/svg/parse/svg_path.h"
#include "core/components_ng/svg/parse/svg_pattern.h"
#include "core/components_ng/svg/parse/svg_polygon.h"
#include "core/components_ng/svg/parse/svg_rect.h"
#include "core/components_ng/svg/parse/svg_stop.h"
#include "core/components_ng/svg/parse/svg_style.h"
#include "core/components_ng/svg/parse/svg_svg.h"
#include "core/components_ng/svg/parse/svg_use.h"
#include "core/components_ng/svg/svg_dom.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string IMAGE_LABEL =
    "<svg width=\"900\" height=\"900\" viewBox=\"0 0 150 120\" xmlns=\"http://www.w3.org/2000/svg\">"
    "<image id=\"image001\" x=\"150\" y=\"20\" width=\"100\" height=\"100\" href=\"test.png\" />"
    "</svg>";
constexpr float IMAGE_COMPONENT_WIDTH = 100.0f;
constexpr float IMAGE_COMPONENT_HEIGHT = 100.0f;
const std::string URL_1 = "file://data/data/com.example.test/res/example.svg";
const std::string URL_2 = "data://data/data/com.example.test/res/exampleAlt.jpg";
const std::string URL_3 = "/common/media/aaa.png";
const std::string URL_4 = "data:base64";
const std::string URL_5 = "data:image/png;base64,test123";
} // namespace
class SvgManagerTestNg : public testing::Test {
public:
};

/**
 * @tc.name: CalcDstRect001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, CalcDstRect001, TestSize.Level1)
{
    SvgImage svgImage;
    Size realSize(0.0f, 0.0f);
    Rect viewBox(10.0f, 10.0f, 100.0f, 100.0f);
    RSRect ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(0.0f, 1.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(1.0f, 0.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    realSize.SetSize(Size(1.0f, 1.0f));
    ret = svgImage.CalcDstRect(realSize, viewBox);
    EXPECT_NE(ret.left_, 0.0f);
}

/**
 * @tc.name: ParseHrefAttr001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, ParseHrefAttr001, TestSize.Level1)
{
    SvgImage svgImage;
    std::string uri;
    auto ret = svgImage.ParseHrefAttr("");
    EXPECT_EQ(ret, SrcType::UNSUPPORTED);
    ret = svgImage.ParseHrefAttr(URL_3);
    EXPECT_EQ(ret, SrcType::ASSET);
    ret = svgImage.ParseHrefAttr("http://gitee.com");
    EXPECT_EQ(ret, SrcType::NETWORK);
    ret = svgImage.ParseHrefAttr("https://gitee.com");
    EXPECT_EQ(ret, SrcType::NETWORK);
    ret = svgImage.ParseHrefAttr(URL_2);
    EXPECT_EQ(ret, SrcType::BASE64);
    ret = svgImage.ParseHrefAttr(URL_4);
    EXPECT_EQ(ret, SrcType::UNSUPPORTED);
    ret = svgImage.ParseHrefAttr(URL_1);
    EXPECT_EQ(ret, SrcType::ASSET);
}

/**
 * @tc.name: LoadBase64Image001
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, LoadBase64Image001, TestSize.Level1)
{
    SvgImage svgImage;
    auto ret = svgImage.LoadBase64Image(URL_5);
    EXPECT_NE(ret, nullptr);
    ret = svgImage.LoadBase64Image(URL_3);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: SvgDomTest002
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDomTest002, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(IMAGE_LABEL.c_str(), IMAGE_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);

    /* *
     * @tc.steps: step1. call AsPath
     * @tc.expected: Execute function return value is true
     */
    auto svgImage = AceType::DynamicCast<SvgImage>(svg->children_.at(0));
    svgImage->imageAttr_.href.clear();
    RSCanvas canvas;
    Size testSize(IMAGE_COMPONENT_WIDTH, IMAGE_COMPONENT_HEIGHT);
    svgImage->imageAttr_.href = "";
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_1;
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.width = Dimension(0.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(0.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.height = Dimension(0.0);
    svgImage->imageAttr_.width = Dimension(0.0);
    EXPECT_EQ(svgImage->imageAttr_.width, Dimension(0.0f));
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_4;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_3;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    svgImage->imageAttr_.href = URL_2;
    svgImage->imageAttr_.width = Dimension(5.0);
    svgImage->imageAttr_.height = Dimension(5.0);
    svgImage->OnDraw(canvas, testSize, Color::BLACK);
    auto width = svgImage->ConvertDimensionToPx(svgImage->imageAttr_.width, testSize, SvgLengthType::HORIZONTAL);
    auto height = svgImage->ConvertDimensionToPx(svgImage->imageAttr_.height, testSize, SvgLengthType::VERTICAL);
    EXPECT_FALSE(LessOrEqual(width, 0.0f));
    EXPECT_FALSE(LessOrEqual(height, 0.0f));
}

/**
 * @tc.name: SvgDomTest003
 * @tc.desc: test function of SvgImage.
 * @tc.type: FUNC
 */
HWTEST_F(SvgManagerTestNg, SvgDomTest003, TestSize.Level1)
{
    auto svgStream = SkMemoryStream::MakeCopy(IMAGE_LABEL.c_str(), IMAGE_LABEL.length());
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, src);
    auto svg = AceType::DynamicCast<SvgSvg>(svgDom->root_);
    EXPECT_GT(static_cast<int32_t>(svg->children_.size()), 0);
    auto svgImage = AceType::DynamicCast<SvgImage>(svg->children_.at(0));
    std::string test = "test.svg";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "test.gif";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "test/gif/test/test";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "/path/to/resource";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    test = "./path/to/resource";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
    svgImage->imagePath_ = "/images/icons/icon";
    EXPECT_EQ(svgImage->LoadLocalImage(test), nullptr);
}
} // namespace OHOS::Ace::NG

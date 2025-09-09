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

#include "base/memory/ace_type.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_rect.h"
#include "core/components_ng/svg/parse/svg_animation.h"
#include "core/components_ng/svg/parse/svg_circle.h"
#include "core/components_ng/svg/parse/svg_node.h"
#include "core/components_ng/svg/svg_dom.h"
#include "core/components_ng/svg/svg_utils.h"
#include "include/core/SkStream.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string CIRCLE_SVG_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"> "
    "<circle id=\"myCircle\" cx=\"60px\" "
    "cy=\"200px\" r = \"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" stroke-width=\"16px\" "
    "stroke-opacity=\"0.3\" id=\"circleId\"/></svg>";
    const std::string CIRCLE_SVG_CLASS_LABEL =
    "<svg width=\"400px\" height=\"400px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\"> "
    "<circle id=\"myCircle\" cx=\"60px\" "
    "cy=\"200px\" r = \"50px\" fill=\"red\" opacity=\"0.5\" stroke=\"blue\" stroke-width=\"16px\" "
    "stroke-opacity=\"0.3\" id=\"circleId\" class=\"\"/></svg>";
    constexpr int32_t ANIMATION_BEGIN = 100;
    constexpr int32_t ANIMATION_DUR = 1000;
    constexpr int32_t ANIMATION_END = 2000;
    constexpr int32_t ANIMATION_REPEATCOUNT = 1;
    constexpr int32_t ANIMATION_FROM = 1000;
    constexpr int32_t ANIMATION_TO = 2000;
    const std::string ANIMATION_KETIMES = "20;800;2000";
    const std::string ANIMATION_VALUES = "10;20;10";
}
class SvgContextTestNg : public testing::Test {};

/**
 * @tc.name: SvgContext001
 * @tc.desc: Get svg node By ID
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTestNg, SvgContext001, TestSize.Level1)
{
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    EXPECT_NE(svgContext, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG_LABEL.c_str(), CIRCLE_SVG_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::string label("label");
    svgContext->Push(label, svgCircle);
    EXPECT_NE(svgContext->GetSvgNodeById(label), nullptr);
}

/**
 * @tc.name: SvgContext002
 * @tc.desc: parse class
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTestNg, SvgContext002, TestSize.Level1)
{
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    EXPECT_NE(svgContext, nullptr);
    ImageSourceInfo src;
    src.SetFillColor(Color::BLACK);
    auto svgStream = SkMemoryStream::MakeCopy(CIRCLE_SVG_CLASS_LABEL.c_str(), CIRCLE_SVG_CLASS_LABEL.length());
    EXPECT_NE(svgStream, nullptr);
    auto svgCircle = AceType::DynamicCast<SvgCircle>(SvgCircle::Create());
    EXPECT_NE(svgCircle, nullptr);
    std::string label("parseClass");
    svgContext->Push(label, svgCircle);
    EXPECT_NE(svgContext->GetSvgNodeById(label), nullptr);
}

/**
 * @tc.name: SvgContext004
 * @tc.desc: test Animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTestNg, SvgContext004, TestSize.Level1)
{
    auto animateMotionNode = AceType::DynamicCast<SvgAnimation>(SvgAnimation::CreateAnimateMotion());
    EXPECT_NE(animateMotionNode, nullptr);
    animateMotionNode->SetAttr("begin", std::to_string(ANIMATION_BEGIN));
    animateMotionNode->SetAttr("dur", std::to_string(ANIMATION_DUR));
    animateMotionNode->SetAttr("end", std::to_string(ANIMATION_END));
    animateMotionNode->SetAttr("repeatCount", std::to_string(ANIMATION_REPEATCOUNT));
    animateMotionNode->SetAttr("fill", "");
    animateMotionNode->SetAttr("calcumode", "");
    animateMotionNode->SetAttr("values", "");
    animateMotionNode->SetAttr("keyTimes", "");
    animateMotionNode->SetAttr("from", std::to_string(ANIMATION_FROM));
    animateMotionNode->SetAttr("to", std::to_string(ANIMATION_TO));
    animateMotionNode->UpdateAttr();
    EXPECT_FLOAT_EQ(animateMotionNode->animateAttr_.begin, ANIMATION_BEGIN);
    EXPECT_FLOAT_EQ(animateMotionNode->animateAttr_.dur, ANIMATION_DUR);
    EXPECT_FLOAT_EQ(animateMotionNode->animateAttr_.end, ANIMATION_END);
    EXPECT_FLOAT_EQ(animateMotionNode->animateAttr_.repeatCount, ANIMATION_REPEATCOUNT);
}

/**
 * @tc.name: SvgContext005
 * @tc.desc: test Animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTestNg, SvgContext005, TestSize.Level1)
{
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    EXPECT_NE(svgContext, nullptr);
    Animator animator;
    RefPtr<Animator> animator1 = AceType::MakeRefPtr<Animator>();
    svgContext->AddAnimator(1, animator1);
    RefPtr<Animator> animator2 = AceType::MakeRefPtr<Animator>();
    svgContext->AddAnimator(2, animator2);
    svgContext->RemoveAnimator(1);
    svgContext->RemoveAnimator(2);
    EXPECT_EQ(svgContext->animators_.size(), 0);
}

/**
 * @tc.name: SvgContext006
 * @tc.desc: test Animation
 * @tc.type: FUNC
 */
HWTEST_F(SvgContextTestNg, SvgContext006, TestSize.Level1)
{
    auto svgContext = AceType::MakeRefPtr<SvgContext>();
    EXPECT_NE(svgContext, nullptr);
    Animator animator;
    RefPtr<Animator> animator1 = AceType::MakeRefPtr<Animator>();
    svgContext->AddAnimator(1, animator1);
    RefPtr<Animator> animator2 = AceType::MakeRefPtr<Animator>();
    svgContext->AddAnimator(2, animator2);
    svgContext->ControlAnimators(true);
    svgContext->AnimateFlush();
    svgContext->RemoveAnimator(1);
    svgContext->RemoveAnimator(2);
    EXPECT_EQ(svgContext->animators_.size(), 0);
}
} // namespace OHOS::Ace::NG

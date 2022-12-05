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
#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewAbstractTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void ViewAbstractTestNg::SetUpTestCase()
{
    const std::string tag = "test";
    const auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, 0, AceType::MakeRefPtr<Pattern>());
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
}

void ViewAbstractTestNg::TearDownTestCase() {}

void ViewAbstractTestNg::SetUp() {}

void ViewAbstractTestNg::TearDown() {}

/**
 * @tc.name: ViewAbstractTestNg001
 * @tc.desc: Test transform common method
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg001, TestSize.Level1)
{
    // translate
    auto translateIn = Vector3F(1.0f, 1.0f, 1.0f);
    auto scaleIn = VectorF(1.0f, 1.0f);
    auto rotateIn = Vector4F(1.0f, 1.0f, 1.0f, 1.0f);
    auto centerIn = DimensionOffset(Dimension(1.0), Dimension(1.0));
    ViewAbstract::SetScale(scaleIn);
    ViewAbstract::SetTranslate(translateIn);
    ViewAbstract::SetPivot(centerIn);
    ViewAbstract::SetRotate(rotateIn);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto renderContext = frameNode->GetRenderContext();
    auto& transformProperty = renderContext->GetOrCreateTransform();
    auto translateOut = transformProperty->GetTransformTranslateValue();
    auto scaleOut = transformProperty->GetTransformScaleValue();
    auto rotateOut = transformProperty->GetTransformRotateValue();
    auto centerOut = transformProperty->GetTransformCenterValue();
    EXPECT_EQ(translateIn, translateOut);
    EXPECT_EQ(scaleIn, scaleOut);
    EXPECT_EQ(rotateIn, rotateOut);
    EXPECT_EQ(centerIn, centerOut);
}

/**
 * @tc.name: ViewAbstractTestNg002
 * @tc.desc: Test graphics common method
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg002, TestSize.Level1)
{
    // graphics
    auto brightnessIn = Dimension(1.0);
    auto grayScaleIn = Dimension(1.0);
    auto contrastIn = Dimension(1.0);
    auto saturateIn = Dimension(1.0);
    auto sepiaIn = Dimension(1.0);
    auto invertIn = Dimension(1.0);
    auto hueRotateIn = 1.0f;
    auto colorBlendIn = Color();
    ViewAbstract::SetBrightness(brightnessIn);
    ViewAbstract::SetGrayScale(grayScaleIn);
    ViewAbstract::SetContrast(contrastIn);
    ViewAbstract::SetSaturate(saturateIn);
    ViewAbstract::SetSepia(sepiaIn);
    ViewAbstract::SetInvert(invertIn);
    ViewAbstract::SetHueRotate(hueRotateIn);
    ViewAbstract::SetColorBlend(colorBlendIn);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto renderContext = frameNode->GetRenderContext();
    auto& graphicsProperty = renderContext->GetOrCreateGraphics();
    auto brightnessOut = graphicsProperty->GetFrontBrightnessValue();
    auto grayScaleOut = graphicsProperty->GetFrontGrayScaleValue();
    auto contrastOut = graphicsProperty->GetFrontContrastValue();
    auto saturateOut = graphicsProperty->GetFrontSaturateValue();
    auto sepiaOut = graphicsProperty->GetFrontSepiaValue();
    auto invertOut = graphicsProperty->GetFrontInvertValue();
    auto hueRotateOut = graphicsProperty->GetFrontHueRotateValue();
    auto colorBlendOut = graphicsProperty->GetFrontColorBlendValue();
    EXPECT_EQ(brightnessIn, brightnessOut);
    EXPECT_EQ(grayScaleIn, grayScaleOut);
    EXPECT_EQ(contrastIn, contrastOut);
    EXPECT_EQ(saturateIn, saturateOut);
    EXPECT_EQ(sepiaIn, sepiaOut);
    EXPECT_EQ(invertIn, invertOut);
    EXPECT_EQ(hueRotateIn, hueRotateOut);
    EXPECT_EQ(colorBlendIn, colorBlendOut);
}

/**
 * @tc.name: ViewAbstractTestNg003
 * @tc.desc: Test clip mask and gradient common method
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg003, TestSize.Level1)
{
    // clip mask and gradient
    auto clipShapeIn = AceType::MakeRefPtr<BasicShape>();
    auto maskShapeIn = AceType::MakeRefPtr<BasicShape>();
    auto isClipIn = true;
    auto linearGradientIn = NG::Gradient();
    auto sweepGradientIn = NG::Gradient();
    auto radialGradientIn = NG::Gradient();
    ViewAbstract::SetClipShape(clipShapeIn);
    ViewAbstract::SetClipEdge(isClipIn);
    ViewAbstract::SetMask(maskShapeIn);
    ViewAbstract::SetLinearGradient(linearGradientIn);
    ViewAbstract::SetSweepGradient(sweepGradientIn);
    ViewAbstract::SetRadialGradient(radialGradientIn);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto renderContext = frameNode->GetRenderContext();
    auto& clipProperty = renderContext->GetOrCreateClip();
    auto& gradientProperty = renderContext->GetOrCreateGradient();
    auto clipShapeOut = clipProperty->GetClipShapeValue();
    auto maskShapeOut = clipProperty->GetClipMaskValue();
    auto isClipOut = clipProperty->GetClipEdgeValue();
    auto linearGradientOut = gradientProperty->GetLinearGradientValue();
    auto sweepGradientOut = gradientProperty->GetSweepGradientValue();
    auto radialGradientOut = gradientProperty->GetRadialGradientValue();
    EXPECT_EQ(clipShapeIn, clipShapeOut);
    EXPECT_EQ(maskShapeIn, maskShapeOut);
    EXPECT_EQ(isClipIn, isClipOut);
    EXPECT_EQ(linearGradientIn, linearGradientOut);
    EXPECT_EQ(sweepGradientIn, sweepGradientOut);
    EXPECT_EQ(radialGradientIn, radialGradientOut);
}
} // namespace OHOS::Ace::NG
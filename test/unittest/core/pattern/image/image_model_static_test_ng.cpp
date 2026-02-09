/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "image_base.h"

#include "core/components_ng/pattern/image/image_model_static.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float TEST_SMOOTH_EDGE_VALUE = 0.5f;
constexpr float TEST_HDR_BRIGHTNESS_VALUE = 1.5f;
constexpr Dimension TEST_IMAGE_WIDTH = 100.0_vp;
constexpr Dimension TEST_IMAGE_HEIGHT = 100.0_vp;
constexpr DynamicRangeMode TEST_DYNAMIC_RANGE_MODE = DynamicRangeMode::HIGH;
constexpr CopyOptions TEST_COPY_OPTION = CopyOptions::InApp;
constexpr ImageRepeat TEST_IMAGE_REPEAT = ImageRepeat::REPEAT_X;
constexpr ImageRenderMode TEST_IMAGE_RENDER_MODE = ImageRenderMode::TEMPLATE;
constexpr ImageFit TEST_IMAGE_FIT = ImageFit::CONTAIN;
constexpr bool TEST_ANTIALIASED = true;
constexpr bool TEST_SUPPORT_SVG2 = true;
constexpr ImageInterpolation TEST_IMAGE_INTERPOLATION = ImageInterpolation::HIGH;
constexpr ImageRotateOrientation TEST_ORIENTATION = ImageRotateOrientation::RIGHT;
constexpr AIImageQuality TEST_IMAGE_QUALITY = AIImageQuality::HIGH;
constexpr ContentTransitionType TEST_CONTENT_TRANSITION = ContentTransitionType::IDENTITY;
const Color TEST_IMAGE_FILL_COLOR = Color::RED;
const std::string TEST_IMAGE_SRC = "file://data/test/image.png";
const std::string TEST_ALT_SRC = "file://data/test/alt.png";
const std::string TEST_NETWORK_SRC = "https://example.com/image.png";
} // namespace

class ImageModelStaticTestNg : public ImageBases {};

/**
 * @tc.name: ImageModelStaticSetSrc_WithValidInfo
 * @tc.desc: Test SetSrc with valid ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSrc_WithValidInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageSourceInfo
     */
    ImageSourceInfo testInfo(TEST_IMAGE_SRC);
    ImageModelStatic::SetSrc(AceType::RawPtr(frameNode), testInfo);

    /**
     * @tc.steps: step3. Verify ImageSourceInfo is updated
     */
    auto srcInfo = layoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(srcInfo.has_value());
    EXPECT_EQ(srcInfo.value().GetSrc(), TEST_IMAGE_SRC);
}

/**
 * @tc.name: ImageModelStaticSetSrc_WithNullInfo
 * @tc.desc: Test SetSrc with null ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSrc_WithNullInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageSourceInfo first
     */
    ImageSourceInfo testInfo(TEST_IMAGE_SRC);
    ImageModelStatic::SetSrc(AceType::RawPtr(frameNode), testInfo);
    auto srcInfoBefore = layoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(srcInfoBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageSourceInfo with null
     */
    ImageModelStatic::SetSrc(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify ImageSourceInfo is reset
     */
    auto srcInfoAfter = layoutProperty->GetImageSourceInfo();
    EXPECT_FALSE(srcInfoAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetSmoothEdge_WithValidValue
 * @tc.desc: Test SetSmoothEdge with valid float value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSmoothEdge_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid SmoothEdge value
     */
    ImageModelStatic::SetSmoothEdge(AceType::RawPtr(frameNode), TEST_SMOOTH_EDGE_VALUE);

    /**
     * @tc.steps: step3. Verify SmoothEdge is updated
     */
    auto smoothEdge = renderProperty->GetSmoothEdge();
    ASSERT_TRUE(smoothEdge.has_value());
    EXPECT_FLOAT_EQ(smoothEdge.value(), TEST_SMOOTH_EDGE_VALUE);
}

/**
 * @tc.name: ImageModelStaticSetSmoothEdge_WithNullValue
 * @tc.desc: Test SetSmoothEdge with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSmoothEdge_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid SmoothEdge value first
     */
    ImageModelStatic::SetSmoothEdge(AceType::RawPtr(frameNode), TEST_SMOOTH_EDGE_VALUE);
    auto smoothEdgeBefore = renderProperty->GetSmoothEdge();
    ASSERT_TRUE(smoothEdgeBefore.has_value());

    /**
     * @tc.steps: step3. Reset SmoothEdge with null
     */
    ImageModelStatic::SetSmoothEdge(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify SmoothEdge is reset
     */
    auto smoothEdgeAfter = renderProperty->GetSmoothEdge();
    EXPECT_FALSE(smoothEdgeAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetDynamicRangeMode_WithValidMode
 * @tc.desc: Test SetDynamicRangeMode with valid DynamicRangeMode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetDynamicRangeMode_WithValidMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid DynamicRangeMode
     */
    ImageModelStatic::SetDynamicRangeMode(AceType::RawPtr(frameNode), TEST_DYNAMIC_RANGE_MODE);

    /**
     * @tc.steps: step3. Verify DynamicRangeMode is updated in both render property and render context
     */
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    auto dynamicMode = renderProperty->GetDynamicMode();
    ASSERT_TRUE(dynamicMode.has_value());
    EXPECT_EQ(dynamicMode.value(), TEST_DYNAMIC_RANGE_MODE);
}

/**
 * @tc.name: ImageModelStaticSetDynamicRangeMode_WithNullMode
 * @tc.desc: Test SetDynamicRangeMode with null DynamicRangeMode (should use STANDARD)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetDynamicRangeMode_WithNullMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set null DynamicRangeMode (should default to STANDARD)
     */
    ImageModelStatic::SetDynamicRangeMode(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify DynamicRangeMode defaults to STANDARD
     */
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    auto dynamicMode = renderProperty->GetDynamicMode();
    ASSERT_TRUE(dynamicMode.has_value());
    EXPECT_EQ(dynamicMode.value(), DynamicRangeMode::STANDARD);
}

/**
 * @tc.name: ImageModelStaticSetCopyOption_WithValidOption
 * @tc.desc: Test SetCopyOption with valid CopyOptions
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetCopyOption_WithValidOption, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set valid CopyOption
     */
    ImageModelStatic::SetCopyOption(AceType::RawPtr(frameNode), TEST_COPY_OPTION);

    /**
     * @tc.steps: step3. Verify CopyOption is updated in pattern
     */
    auto copyOption = pattern->GetCopyOption();
    EXPECT_EQ(copyOption, TEST_COPY_OPTION);
}

/**
 * @tc.name: ImageModelStaticSetCopyOption_WithNullOption
 * @tc.desc: Test SetCopyOption with null CopyOptions (should use None)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetCopyOption_WithNullOption, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set null CopyOption (should default to None)
     */
    ImageModelStatic::SetCopyOption(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify CopyOption defaults to None
     */
    auto copyOption = pattern->GetCopyOption();
    EXPECT_EQ(copyOption, CopyOptions::None);
}

/**
 * @tc.name: ImageModelStaticSetImageRepeat_WithValidValue
 * @tc.desc: Test SetImageRepeat with valid ImageRepeat
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageRepeat_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageRepeat
     */
    ImageModelStatic::SetImageRepeat(AceType::RawPtr(frameNode), TEST_IMAGE_REPEAT);

    /**
     * @tc.steps: step3. Verify ImageRepeat is updated
     */
    auto imageRepeat = renderProperty->GetImageRepeat();
    ASSERT_TRUE(imageRepeat.has_value());
    EXPECT_EQ(imageRepeat.value(), TEST_IMAGE_REPEAT);
}

/**
 * @tc.name: ImageModelStaticSetImageRepeat_WithNullValue
 * @tc.desc: Test SetImageRepeat with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageRepeat_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageRepeat first
     */
    ImageModelStatic::SetImageRepeat(AceType::RawPtr(frameNode), TEST_IMAGE_REPEAT);
    auto imageRepeatBefore = renderProperty->GetImageRepeat();
    ASSERT_TRUE(imageRepeatBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageRepeat with null
     */
    ImageModelStatic::SetImageRepeat(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify ImageRepeat is reset
     */
    auto imageRepeatAfter = renderProperty->GetImageRepeat();
    EXPECT_FALSE(imageRepeatAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetImageRenderMode_WithValidMode
 * @tc.desc: Test SetImageRenderMode with valid ImageRenderMode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageRenderMode_WithValidMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageRenderMode
     */
    ImageModelStatic::SetImageRenderMode(AceType::RawPtr(frameNode), TEST_IMAGE_RENDER_MODE);

    /**
     * @tc.steps: step3. Verify ImageRenderMode is updated
     */
    auto renderMode = renderProperty->GetImageRenderMode();
    ASSERT_TRUE(renderMode.has_value());
    EXPECT_EQ(renderMode.value(), TEST_IMAGE_RENDER_MODE);
}

/**
 * @tc.name: ImageModelStaticSetImageRenderMode_WithNullMode
 * @tc.desc: Test SetImageRenderMode with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageRenderMode_WithNullMode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageRenderMode first
     */
    ImageModelStatic::SetImageRenderMode(AceType::RawPtr(frameNode), TEST_IMAGE_RENDER_MODE);
    auto renderModeBefore = renderProperty->GetImageRenderMode();
    ASSERT_TRUE(renderModeBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageRenderMode with null
     */
    ImageModelStatic::SetImageRenderMode(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify ImageRenderMode is reset
     */
    auto renderModeAfter = renderProperty->GetImageRenderMode();
    EXPECT_FALSE(renderModeAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetImageMatrix_WithValidMatrix
 * @tc.desc: Test SetImageMatrix with valid Matrix4
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageMatrix_WithValidMatrix, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid Matrix4
     */
    Matrix4 testMatrix = Matrix4::CreateIdentity();
    ImageModelStatic::SetImageMatrix(AceType::RawPtr(frameNode), testMatrix);

    /**
     * @tc.steps: step3. Verify ImageMatrix is updated
     */
    auto imageMatrix = renderProperty->GetImageMatrix();
    ASSERT_TRUE(imageMatrix.has_value());
    EXPECT_EQ(imageMatrix.value(), testMatrix);
}

/**
 * @tc.name: ImageModelStaticSetImageMatrix_WithNullMatrix
 * @tc.desc: Test SetImageMatrix with null Matrix4 (should use identity)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageMatrix_WithNullMatrix, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set null Matrix4 (should default to identity)
     */
    ImageModelStatic::SetImageMatrix(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify ImageMatrix defaults to identity
     */
    auto imageMatrix = renderProperty->GetImageMatrix();
    ASSERT_TRUE(imageMatrix.has_value());
    EXPECT_EQ(imageMatrix.value(), Matrix4::CreateIdentity());
}

/**
 * @tc.name: ImageModelStaticSetImageFit_WithValidValue
 * @tc.desc: Test SetImageFit with valid ImageFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageFit_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageFit
     */
    ImageModelStatic::SetImageFit(AceType::RawPtr(frameNode), TEST_IMAGE_FIT);

    /**
     * @tc.steps: step3. Verify ImageFit is updated in both layout and render properties
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    auto layoutImageFit = layoutProperty->GetImageFit();
    auto renderImageFit = renderProperty->GetImageFit();
    ASSERT_TRUE(layoutImageFit.has_value());
    ASSERT_TRUE(renderImageFit.has_value());
    EXPECT_EQ(layoutImageFit.value(), TEST_IMAGE_FIT);
    EXPECT_EQ(renderImageFit.value(), TEST_IMAGE_FIT);
}

/**
 * @tc.name: ImageModelStaticSetImageFit_WithNullValue
 * @tc.desc: Test SetImageFit with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageFit_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageFit first
     */
    ImageModelStatic::SetImageFit(AceType::RawPtr(frameNode), TEST_IMAGE_FIT);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto imageFitBefore = layoutProperty->GetImageFit();
    ASSERT_TRUE(imageFitBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageFit with null
     */
    ImageModelStatic::SetImageFit(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify ImageFit is reset in both properties
     */
    auto layoutPropertyAfter = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    auto renderPropertyAfter = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(layoutPropertyAfter, nullptr);
    ASSERT_NE(renderPropertyAfter, nullptr);

    auto layoutImageFitAfter = layoutPropertyAfter->GetImageFit();
    auto renderImageFitAfter = renderPropertyAfter->GetImageFit();
    EXPECT_FALSE(layoutImageFitAfter.has_value());
    EXPECT_FALSE(renderImageFitAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetImageSourceSize_WithValidSize
 * @tc.desc: Test SetImageSourceSize with valid size pair
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageSourceSize_WithValidSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageSourceSize
     */
    std::pair<Dimension, Dimension> testSize(TEST_IMAGE_WIDTH, TEST_IMAGE_HEIGHT);
    ImageModelStatic::SetImageSourceSize(AceType::RawPtr(frameNode), testSize);

    /**
     * @tc.steps: step3. Verify SourceSize is updated
     */
    auto sourceSize = layoutProperty->GetSourceSize();
    ASSERT_TRUE(sourceSize.has_value());
    EXPECT_FLOAT_EQ(sourceSize.value().Width(), TEST_IMAGE_WIDTH.ConvertToPx());
    EXPECT_FLOAT_EQ(sourceSize.value().Height(), TEST_IMAGE_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: ImageModelStaticSetImageSourceSize_WithNullSize
 * @tc.desc: Test SetImageSourceSize with null size
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageSourceSize_WithNullSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageSourceSize first
     */
    std::pair<Dimension, Dimension> testSize(TEST_IMAGE_WIDTH, TEST_IMAGE_HEIGHT);
    ImageModelStatic::SetImageSourceSize(AceType::RawPtr(frameNode), testSize);
    auto sourceSizeBefore = layoutProperty->GetSourceSize();
    ASSERT_TRUE(sourceSizeBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageSourceSize with null
     */
    ImageModelStatic::SetImageSourceSize(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify SourceSize is reset
     */
    auto sourceSizeAfter = layoutProperty->GetSourceSize();
    EXPECT_FALSE(sourceSizeAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetImageFill_WithValidColor
 * @tc.desc: Test SetImageFill with valid Color
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageFill_WithValidColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageFill color
     */
    ImageModelStatic::SetImageFill(AceType::RawPtr(frameNode), TEST_IMAGE_FILL_COLOR);

    /**
     * @tc.steps: step3. Verify SvgFillColor and ForegroundColor are updated
     */
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto svgFillColor = renderProperty->GetSvgFillColor();
    ASSERT_TRUE(svgFillColor.has_value());
    EXPECT_EQ(svgFillColor.value(), TEST_IMAGE_FILL_COLOR);
}

/**
 * @tc.name: ImageModelStaticSetImageFill_WithNullColor
 * @tc.desc: Test SetImageFill with null color
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageFill_WithNullColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageFill color first
     */
    ImageModelStatic::SetImageFill(AceType::RawPtr(frameNode), TEST_IMAGE_FILL_COLOR);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    auto svgFillColorBefore = renderProperty->GetSvgFillColor();
    ASSERT_TRUE(svgFillColorBefore.has_value());

    /**
     * @tc.steps: step3. Reset ImageFill with null
     */
    ImageModelStatic::SetImageFill(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify SvgFillColor is reset
     */
    auto renderPropertyAfter = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderPropertyAfter, nullptr);
    auto svgFillColorAfter = renderPropertyAfter->GetSvgFillColor();
    EXPECT_FALSE(svgFillColorAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetAlt_WithValidSrc
 * @tc.desc: Test SetAlt with valid ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAlt_WithValidSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid Alt ImageSourceInfo
     */
    ImageSourceInfo altInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAlt(AceType::RawPtr(frameNode), altInfo);

    /**
     * @tc.steps: step3. Verify Alt is updated
     */
    auto alt = layoutProperty->GetAlt();
    ASSERT_TRUE(alt.has_value());
    EXPECT_EQ(alt.value().GetSrc(), TEST_ALT_SRC);
}

/**
 * @tc.name: ImageModelStaticSetAlt_WithNullSrc
 * @tc.desc: Test SetAlt with null ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAlt_WithNullSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid Alt ImageSourceInfo first
     */
    ImageSourceInfo altInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAlt(AceType::RawPtr(frameNode), altInfo);
    auto altBefore = layoutProperty->GetAlt();
    ASSERT_TRUE(altBefore.has_value());

    /**
     * @tc.steps: step3. Reset Alt with null
     */
    ImageModelStatic::SetAlt(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify Alt is reset
     */
    auto altAfter = layoutProperty->GetAlt();
    EXPECT_FALSE(altAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetAltError_WithLocalSrc
 * @tc.desc: Test SetAltError with local image source
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAltError_WithLocalSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid AltError ImageSourceInfo (local)
     */
    ImageSourceInfo altErrorInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAltError(AceType::RawPtr(frameNode), altErrorInfo);

    /**
     * @tc.steps: step3. Verify AltError is updated
     */
    auto altError = layoutProperty->GetAltError();
    ASSERT_TRUE(altError.has_value());
    EXPECT_EQ(altError.value().GetSrc(), TEST_ALT_SRC);
}

/**
 * @tc.name: ImageModelStaticSetAltError_WithNetworkSrc
 * @tc.desc: Test SetAltError with network image source (should set empty)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAltError_WithNetworkSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid AltError ImageSourceInfo (network)
     */
    ImageSourceInfo altErrorInfo(TEST_NETWORK_SRC);
    ImageModelStatic::SetAltError(AceType::RawPtr(frameNode), altErrorInfo);

    /**
     * @tc.steps: step3. Verify AltError is updated (should be empty for network)
     */
    auto altError = layoutProperty->GetAltError();
    ASSERT_TRUE(altError.has_value());
}

/**
 * @tc.name: ImageModelStaticSetAltError_WithNullSrc
 * @tc.desc: Test SetAltError with null ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAltError_WithNullSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid AltError ImageSourceInfo first
     */
    ImageSourceInfo altErrorInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAltError(AceType::RawPtr(frameNode), altErrorInfo);
    auto altErrorBefore = layoutProperty->GetAltError();
    ASSERT_TRUE(altErrorBefore.has_value());

    /**
     * @tc.steps: step3. Reset AltError with null
     */
    ImageModelStatic::SetAltError(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify AltError is reset
     */
    auto altErrorAfter = layoutProperty->GetAltError();
    EXPECT_FALSE(altErrorAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetAltPlaceholder_WithValidSrc
 * @tc.desc: Test SetAltPlaceholder with valid ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAltPlaceholder_WithValidSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid AltPlaceholder ImageSourceInfo
     */
    ImageSourceInfo altPlaceholderInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAltPlaceholder(AceType::RawPtr(frameNode), altPlaceholderInfo);

    /**
     * @tc.steps: step3. Verify AltPlaceholder is updated
     */
    auto altPlaceholder = layoutProperty->GetAltPlaceholder();
    ASSERT_TRUE(altPlaceholder.has_value());
    EXPECT_EQ(altPlaceholder.value().GetSrc(), TEST_ALT_SRC);
}

/**
 * @tc.name: ImageModelStaticSetAltPlaceholder_WithNullSrc
 * @tc.desc: Test SetAltPlaceholder with null ImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAltPlaceholder_WithNullSrc, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and layout property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid AltPlaceholder ImageSourceInfo first
     */
    ImageSourceInfo altPlaceholderInfo(TEST_ALT_SRC);
    ImageModelStatic::SetAltPlaceholder(AceType::RawPtr(frameNode), altPlaceholderInfo);
    auto altPlaceholderBefore = layoutProperty->GetAltPlaceholder();
    ASSERT_TRUE(altPlaceholderBefore.has_value());

    /**
     * @tc.steps: step3. Reset AltPlaceholder with null
     */
    ImageModelStatic::SetAltPlaceholder(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify AltPlaceholder is reset
     */
    auto altPlaceholderAfter = layoutProperty->GetAltPlaceholder();
    EXPECT_FALSE(altPlaceholderAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetSupportSvg2_Enable
 * @tc.desc: Test SetSupportSvg2 with enable = true
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSupportSvg2_Enable, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set SupportSvg2 to true
     */
    ImageModelStatic::SetSupportSvg2(AceType::RawPtr(frameNode), TEST_SUPPORT_SVG2);

    /**
     * @tc.steps: step3. Verify SupportSvg2 is enabled (check via pattern state)
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ImageModelStaticSetSupportSvg2_Disable
 * @tc.desc: Test SetSupportSvg2 with enable = false
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetSupportSvg2_Disable, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set SupportSvg2 to false
     */
    ImageModelStatic::SetSupportSvg2(AceType::RawPtr(frameNode), false);

    /**
     * @tc.steps: step3. Verify SupportSvg2 is disabled
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ImageModelStaticSetContentTransition
 * @tc.desc: Test SetContentTransition with valid ContentTransitionType
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetContentTransition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ContentTransitionType
     */
    ImageModelStatic::SetContentTransition(AceType::RawPtr(frameNode), TEST_CONTENT_TRANSITION);

    /**
     * @tc.steps: step3. Verify ContentTransition is updated
     */
    auto contentTransition = renderProperty->GetContentTransition();
    ASSERT_TRUE(contentTransition.has_value());
    EXPECT_EQ(contentTransition.value(), TEST_CONTENT_TRANSITION);
}

/**
 * @tc.name: ImageModelStaticSetAntialiased_WithValidValue
 * @tc.desc: Test SetAntialiased with valid boolean value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAntialiased_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid Antialiased value
     */
    ImageModelStatic::SetAntialiased(AceType::RawPtr(frameNode), TEST_ANTIALIASED);

    /**
     * @tc.steps: step3. Verify AntiAlias is updated
     */
    auto antiAlias = renderProperty->GetAntiAlias();
    ASSERT_TRUE(antiAlias.has_value());
    EXPECT_EQ(antiAlias.value(), TEST_ANTIALIASED);
}

/**
 * @tc.name: ImageModelStaticSetAntialiased_WithNullValue
 * @tc.desc: Test SetAntialiased with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetAntialiased_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid Antialiased value first
     */
    ImageModelStatic::SetAntialiased(AceType::RawPtr(frameNode), TEST_ANTIALIASED);
    auto antiAliasBefore = renderProperty->GetAntiAlias();
    ASSERT_TRUE(antiAliasBefore.has_value());

    /**
     * @tc.steps: step3. Reset Antialiased with null
     */
    ImageModelStatic::SetAntialiased(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify AntiAlias is reset
     */
    auto antiAliasAfter = renderProperty->GetAntiAlias();
    EXPECT_FALSE(antiAliasAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetImageInterpolation_WithValidValue
 * @tc.desc: Test SetImageInterpolation with valid ImageInterpolation
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageInterpolation_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid ImageInterpolation
     */
    ImageModelStatic::SetImageInterpolation(AceType::RawPtr(frameNode), TEST_IMAGE_INTERPOLATION);

    /**
     * @tc.steps: step3. Verify ImageInterpolation is updated
     */
    auto imageInterpolation = renderProperty->GetImageInterpolation();
    ASSERT_TRUE(imageInterpolation.has_value());
    EXPECT_EQ(imageInterpolation.value(), TEST_IMAGE_INTERPOLATION);
}

/**
 * @tc.name: ImageModelStaticSetImageInterpolation_WithNullValue
 * @tc.desc: Test SetImageInterpolation with null value (should use NONE)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetImageInterpolation_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set null ImageInterpolation (should default to NONE)
     */
    ImageModelStatic::SetImageInterpolation(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify ImageInterpolation defaults to NONE
     */
    auto imageInterpolation = renderProperty->GetImageInterpolation();
    ASSERT_TRUE(imageInterpolation.has_value());
    EXPECT_EQ(imageInterpolation.value(), ImageInterpolation::NONE);
}

/**
 * @tc.name: ImageModelStaticSetOrientation_WithValidValue
 * @tc.desc: Test SetOrientation with valid ImageRotateOrientation
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetOrientation_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set valid Orientation
     */
    ImageModelStatic::SetOrientation(AceType::RawPtr(frameNode), TEST_ORIENTATION);

    /**
     * @tc.steps: step3. Verify Orientation is updated in both layout property and pattern
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto orientation = layoutProperty->GetImageRotateOrientation();
    ASSERT_TRUE(orientation.has_value());
    EXPECT_EQ(orientation.value(), TEST_ORIENTATION);
}

/**
 * @tc.name: ImageModelStaticSetOrientation_WithNullValue
 * @tc.desc: Test SetOrientation with null value (should use UP)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetOrientation_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set null Orientation (should default to UP)
     */
    ImageModelStatic::SetOrientation(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify Orientation defaults to UP
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto orientation = layoutProperty->GetImageRotateOrientation();
    ASSERT_TRUE(orientation.has_value());
    EXPECT_EQ(orientation.value(), ImageRotateOrientation::UP);
}

/**
 * @tc.name: ImageModelStaticSetEnhancedImageQuality_WithValidValue
 * @tc.desc: Test SetEnhancedImageQuality with valid AIImageQuality
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetEnhancedImageQuality_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set valid EnhancedImageQuality
     */
    ImageModelStatic::SetEnhancedImageQuality(AceType::RawPtr(frameNode), TEST_IMAGE_QUALITY);

    /**
     * @tc.steps: step3. Verify ImageQuality is updated in pattern
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ImageModelStaticSetEnhancedImageQuality_WithNullValue
 * @tc.desc: Test SetEnhancedImageQuality with null value (should use NONE)
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetEnhancedImageQuality_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and pattern
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set null EnhancedImageQuality (should default to NONE)
     */
    ImageModelStatic::SetEnhancedImageQuality(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step3. Verify ImageQuality defaults to NONE
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ImageModelStaticSetResizableLattice_WithValidLattice
 * @tc.desc: Test SetResizableLattice with valid DrawingLattice
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetResizableLattice_WithValidLattice, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid DrawingLattice
     */
    RefPtr<DrawingLattice> lattice = nullptr;
    ImageModelStatic::SetResizableLattice(AceType::RawPtr(frameNode), lattice);

    /**
     * @tc.steps: step3. Verify ImageResizableLattice is updated
     */
    auto resizableLattice = renderProperty->GetImageResizableLattice();
    EXPECT_EQ(resizableLattice, nullptr);
}

/**
 * @tc.name: ImageModelStaticSetHdrBrightness_WithValidValue
 * @tc.desc: Test SetHdrBrightness with valid float value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetHdrBrightness_WithValidValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid HdrBrightness value
     */
    ImageModelStatic::SetHdrBrightness(AceType::RawPtr(frameNode), TEST_HDR_BRIGHTNESS_VALUE);

    /**
     * @tc.steps: step3. Verify HdrBrightness is updated
     */
    auto hdrBrightness = renderProperty->GetHdrBrightness();
    ASSERT_TRUE(hdrBrightness.has_value());
    EXPECT_FLOAT_EQ(hdrBrightness.value(), TEST_HDR_BRIGHTNESS_VALUE);
}

/**
 * @tc.name: ImageModelStaticSetHdrBrightness_WithNullValue
 * @tc.desc: Test SetHdrBrightness with null value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetHdrBrightness_WithNullValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid HdrBrightness value first
     */
    ImageModelStatic::SetHdrBrightness(AceType::RawPtr(frameNode), TEST_HDR_BRIGHTNESS_VALUE);
    auto hdrBrightnessBefore = renderProperty->GetHdrBrightness();
    ASSERT_TRUE(hdrBrightnessBefore.has_value());

    /**
     * @tc.steps: step3. Reset HdrBrightness with null
     */
    ImageModelStatic::SetHdrBrightness(AceType::RawPtr(frameNode), std::nullopt);

    /**
     * @tc.steps: step4. Verify HdrBrightness is reset
     */
    auto hdrBrightnessAfter = renderProperty->GetHdrBrightness();
    EXPECT_FALSE(hdrBrightnessAfter.has_value());
}

/**
 * @tc.name: ImageModelStaticSetDrawingColorFilter_WithValidFilter
 * @tc.desc: Test SetDrawingColorFilter with valid DrawingColorFilter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticSetDrawingColorFilter_WithValidFilter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node and render property
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);

    /**
     * @tc.steps: step2. Set valid DrawingColorFilter
     */
    RefPtr<DrawingColorFilter> colorFilter = nullptr;
    ImageModelStatic::SetDrawingColorFilter(AceType::RawPtr(frameNode), colorFilter);

    /**
     * @tc.steps: step3. Verify DrawingColorFilter is updated
     */
    auto drawingColorFilter = renderProperty->GetDrawingColorFilter();
    EXPECT_EQ(drawingColorFilter, nullptr);
}

/**
 * @tc.name: ImageModelStaticResetDraggable
 * @tc.desc: Test ResetDraggable function
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelStaticTestNg, ImageModelStaticResetDraggable, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = ImageModelStaticTestNg::CreateImageNode(TEST_IMAGE_SRC, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Call ResetDraggable
     */
    ImageModelStatic::ResetDraggable(AceType::RawPtr(frameNode));

    /**
     * @tc.steps: step3. Verify node still exists (function completed without crash)
     */
    EXPECT_NE(frameNode, nullptr);
}

} // namespace OHOS::Ace::NG
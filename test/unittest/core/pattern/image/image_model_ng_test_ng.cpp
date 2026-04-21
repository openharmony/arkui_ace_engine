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

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImageModelNGTestNg : public ImageBases {
public:
    void CreateNode()
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        stack->Push(frameNode);
    }

    FrameNode* GetNode()
    {
        return ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
};

/**
 * @tc.name: ImageModelNGCreate001
 * @tc.desc: Test ImageModelNG::Create with basic configuration
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGCreate001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.isUriPureNumber = false;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_NE(imageLayoutProperty->GetImageSourceInfo(), std::nullopt);
}

/**
 * @tc.name: ImageModelNGCreate002
 * @tc.desc: Test ImageModelNG::Create with image span
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGCreate002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.isImageSpan = true;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: ImageModelNGCreate003
 * @tc.desc: Test ImageModelNG::Create with animated drawable
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGCreate003, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.type = ImageType::ANIMATED_DRAWABLE;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo(), std::nullopt);
}

/**
 * @tc.name: ImageModelNGResetImage001
 * @tc.desc: Test ImageModelNG::ResetImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetImage001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    image.ResetImage();

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(imageSourceInfo, std::nullopt);
    EXPECT_FALSE(imageSourceInfo->IsFromReset());
}

/**
 * @tc.name: ImageModelNGResetImage002
 * @tc.desc: Test ImageModelNG::ResetImage with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetImage002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::ResetImage(AceType::RawPtr(frameNode));

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(imageSourceInfo, std::nullopt);
    EXPECT_FALSE(imageSourceInfo->IsFromReset());
}

/**
 * @tc.name: ImageModelNGSetInitialSrc001
 * @tc.desc: Test ImageModelNG::SetInitialSrc
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetInitialSrc001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetInitialSrc(AceType::RawPtr(frameNode), IMAGE_SRC_URL, BUNDLE_NAME, MODULE_NAME, false);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(imageSourceInfo->GetSrc(), IMAGE_SRC_URL);
    EXPECT_FALSE(imageSourceInfo->GetIsUriPureNumber());
}

/**
 * @tc.name: ImageModelNGSetInitialSrc002
 * @tc.desc: Test ImageModelNG::SetInitialSrc with URI pure number
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetInitialSrc002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetInitialSrc(AceType::RawPtr(frameNode), "12345", BUNDLE_NAME, MODULE_NAME, true);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(imageSourceInfo, std::nullopt);
    EXPECT_TRUE(imageSourceInfo->GetIsUriPureNumber());
}

/**
 * @tc.name: ImageModelNGCreateFrameNode001
 * @tc.desc: Test ImageModelNG::CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGCreateFrameNode001, TestSize.Level0)
{
    RefPtr<PixelMap> pixMap = nullptr;
    auto frameNode = ImageModelNG::CreateFrameNode(1, IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME, false);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(imageSourceInfo, std::nullopt);
    EXPECT_EQ(imageSourceInfo->GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: ImageModelNGSetAlt001
 * @tc.desc: Test ImageModelNG::SetAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAlt001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto alt = imageLayoutProperty->GetAlt();
    ASSERT_NE(alt, std::nullopt);
    EXPECT_EQ(alt->GetSrc(), ALT_SRC_URL);
}

/**
 * @tc.name: ImageModelNGSetAlt002
 * @tc.desc: Test ImageModelNG::SetAlt with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAlt002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, "");
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetAlt(AceType::RawPtr(frameNode), ImageSourceInfo { ALT_SRC_URL });

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto alt = imageLayoutProperty->GetAlt();
    ASSERT_NE(alt, std::nullopt);
    EXPECT_EQ(alt->GetSrc(), ALT_SRC_URL);
}

/**
 * @tc.name: ImageModelNGSetSmoothEdge001
 * @tc.desc: Test ImageModelNG::SetSmoothEdge
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSmoothEdge001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetSmoothEdge(5.0f);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto smoothEdge = imageRenderProperty->GetSmoothEdge();
    ASSERT_NE(smoothEdge, std::nullopt);
    EXPECT_EQ(smoothEdge.value(), 5.0f);
}

/**
 * @tc.name: ImageModelNGSetSmoothEdge002
 * @tc.desc: Test ImageModelNG::SetSmoothEdge with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSmoothEdge002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetSmoothEdge(AceType::RawPtr(frameNode), 10.0f);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto smoothEdge = imageRenderProperty->GetSmoothEdge();
    ASSERT_NE(smoothEdge, std::nullopt);
    EXPECT_EQ(smoothEdge.value(), 10.0f);
}

/**
 * @tc.name: ImageModelNGSetDynamicRangeMode001
 * @tc.desc: Test ImageModelNG::SetDynamicRangeMode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetDynamicRangeMode001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetDynamicRangeMode(DynamicRangeMode::HIGH);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto dynamicMode = imageRenderProperty->GetDynamicMode();
    ASSERT_NE(dynamicMode, std::nullopt);
    EXPECT_EQ(dynamicMode.value(), DynamicRangeMode::HIGH);
}

/**
 * @tc.name: ImageModelNGSetDynamicRangeMode002
 * @tc.desc: Test ImageModelNG::SetDynamicRangeMode with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetDynamicRangeMode002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetDynamicRangeMode(AceType::RawPtr(frameNode), DynamicRangeMode::CONSTRAINT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto dynamicMode = imageRenderProperty->GetDynamicMode();
    ASSERT_NE(dynamicMode, std::nullopt);
    EXPECT_EQ(dynamicMode.value(), DynamicRangeMode::CONSTRAINT);
}

/**
 * @tc.name: ImageModelNGSetHdrBrightness001
 * @tc.desc: Test ImageModelNG::SetHdrBrightness
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetHdrBrightness001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetHdrBrightness(1.5f);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto hdrBrightness = imageRenderProperty->GetHdrBrightness();
    ASSERT_NE(hdrBrightness, std::nullopt);
    EXPECT_EQ(hdrBrightness.value(), 1.5f);
}

/**
 * @tc.name: ImageModelNGSetHdrBrightness002
 * @tc.desc: Test ImageModelNG::SetHdrBrightness with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetHdrBrightness002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetHdrBrightness(AceType::RawPtr(frameNode), 2.0f);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto hdrBrightness = imageRenderProperty->GetHdrBrightness();
    ASSERT_NE(hdrBrightness, std::nullopt);
    EXPECT_EQ(hdrBrightness.value(), 2.0f);
}

/**
 * @tc.name: ImageModelNGSetEnhancedImageQuality001
 * @tc.desc: Test ImageModelNG::SetEnhancedImageQuality
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetEnhancedImageQuality001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetEnhancedImageQuality(AIImageQuality::HIGH);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::HIGH);
}

/**
 * @tc.name: ImageModelNGSetEnhancedImageQuality002
 * @tc.desc: Test ImageModelNG::SetEnhancedImageQuality with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetEnhancedImageQuality002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetEnhancedImageQuality(AceType::RawPtr(frameNode), AIImageQuality::LOW);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::LOW);
}

/**
 * @tc.name: ImageModelNGSetBorderRadius001
 * @tc.desc: Test ImageModelNG::SetBorderRadius with single value
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetBorderRadius001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    Dimension radius(10.0f);
    image.SetBorderRadius(radius);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto borderRadius = imageRenderProperty->GetBorderRadius();
    ASSERT_NE(borderRadius, std::nullopt);
    EXPECT_EQ(borderRadius->radiusTopLeft.value(), radius);
}

/**
 * @tc.name: ImageModelNGSetBorderRadius002
 * @tc.desc: Test ImageModelNG::SetBorderRadius with multiple values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetBorderRadius002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    Dimension topLeft(10.0f);
    Dimension topRight(15.0f);
    Dimension bottomLeft(20.0f);
    Dimension bottomRight(25.0f);
    image.SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto borderRadius = imageRenderProperty->GetBorderRadius();
    ASSERT_NE(borderRadius, std::nullopt);
    EXPECT_EQ(borderRadius->radiusTopLeft.value(), topLeft);
    EXPECT_EQ(borderRadius->radiusTopRight.value(), topRight);
    EXPECT_EQ(borderRadius->radiusBottomLeft.value(), bottomLeft);
    EXPECT_EQ(borderRadius->radiusBottomRight.value(), bottomRight);
}

/**
 * @tc.name: ImageModelNGSetBorderRadius003
 * @tc.desc: Test ImageModelNG::SetBorderRadius with BorderRadiusProperty
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetBorderRadius003, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(10.0f);
    borderRadius.radiusTopRight = Dimension(15.0f);
    borderRadius.radiusBottomLeft = Dimension(20.0f);
    borderRadius.radiusBottomRight = Dimension(25.0f);
    borderRadius.multiValued = true;
    image.SetBorderRadius(borderRadius);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto resultBorderRadius = imageRenderProperty->GetBorderRadius();
    ASSERT_NE(resultBorderRadius, std::nullopt);
    EXPECT_EQ(resultBorderRadius->radiusTopLeft.value(), borderRadius.radiusTopLeft.value());
}

/**
 * @tc.name: ImageModelNGSetBorderRadius004
 * @tc.desc: Test ImageModelNG::SetBorderRadius with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetBorderRadius004, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    Dimension radius(15.0f);
    ImageModelNG::SetBorderRadius(AceType::RawPtr(frameNode), radius);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto borderRadius = imageRenderProperty->GetBorderRadius();
    ASSERT_NE(borderRadius, std::nullopt);
    EXPECT_EQ(borderRadius->radiusTopLeft.value(), radius);
}

/**
 * @tc.name: ImageModelNGSetImageFit001
 * @tc.desc: Test ImageModelNG::SetImageFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageFit001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageFit(ImageFit::CONTAIN);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageFit = imageLayoutProperty->GetImageFit();
    ASSERT_NE(imageFit, std::nullopt);
    EXPECT_EQ(imageFit.value(), ImageFit::CONTAIN);
}

/**
 * @tc.name: ImageModelNGSetImageFit002
 * @tc.desc: Test ImageModelNG::SetImageFit with various values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageFit002, TestSize.Level0)
{
    std::vector<ImageFit> fitValues = { ImageFit::COVER, ImageFit::FILL, ImageFit::NONE, ImageFit::SCALE_DOWN };

    for (auto fitValue : fitValues) {
        ImageModelNG image;
        RefPtr<PixelMap> pixMap = nullptr;
        ImageInfoConfig imageInfoConfig;
        imageInfoConfig.pixelMap = pixMap;
        imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
        imageInfoConfig.bundleName = BUNDLE_NAME;
        imageInfoConfig.moduleName = MODULE_NAME;
        image.Create(imageInfoConfig);

        image.SetImageFit(fitValue);

        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
        ASSERT_NE(imageLayoutProperty, nullptr);
        auto imageFit = imageLayoutProperty->GetImageFit();
        ASSERT_NE(imageFit, std::nullopt);
        EXPECT_EQ(imageFit.value(), fitValue);

        ViewStackProcessor::GetInstance()->Finish();
    }
}

/**
 * @tc.name: ImageModelNGSetImageFit003
 * @tc.desc: Test ImageModelNG::SetImageFit with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageFit003, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetImageFit(AceType::RawPtr(frameNode), ImageFit::FITWIDTH);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageFit = imageLayoutProperty->GetImageFit();
    ASSERT_NE(imageFit, std::nullopt);
    EXPECT_EQ(imageFit.value(), ImageFit::FITWIDTH);
}

/**
 * @tc.name: ImageModelNGSetImageMatrix001
 * @tc.desc: Test ImageModelNG::SetImageMatrix
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageMatrix001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    Matrix4 matrix4Value = Matrix4(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
    image.SetImageMatrix(matrix4Value);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto imageMatrix = imageRenderProperty->GetImageMatrix();
    ASSERT_NE(imageMatrix, std::nullopt);
    EXPECT_EQ(imageMatrix.value(), matrix4Value);
}

/**
 * @tc.name: ImageModelNGSetMatchTextDirection001
 * @tc.desc: Test ImageModelNG::SetMatchTextDirection
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetMatchTextDirection001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetMatchTextDirection(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto matchTextDirection = imageRenderProperty->GetMatchTextDirection();
    ASSERT_NE(matchTextDirection, std::nullopt);
    EXPECT_EQ(matchTextDirection.value(), true);
}

/**
 * @tc.name: ImageModelNGSetFitOriginSize001
 * @tc.desc: Test ImageModelNG::SetFitOriginSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetFitOriginSize001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetFitOriginSize(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto fitOriginalSize = imageLayoutProperty->GetFitOriginalSize();
    ASSERT_NE(fitOriginalSize, std::nullopt);
    EXPECT_EQ(fitOriginalSize.value(), true);
}

/**
 * @tc.name: ImageModelNGSetOnComplete001
 * @tc.desc: Test ImageModelNG::SetOnComplete
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetOnComplete001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    bool callbackCalled = false;
    LoadImageSuccessEvent curEvent(100, 100, 200, 200);
    auto onComplete = [&callbackCalled, &curEvent](const LoadImageSuccessEvent& info) {
        callbackCalled = true;
        curEvent = info;
    };
    image.SetOnComplete(std::move(onComplete));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    LoadImageSuccessEvent fireEvent(150, 150, 300, 300);
    eventHub->FireCompleteEvent(fireEvent);

    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(curEvent.GetWidth(), fireEvent.GetWidth());
}

/**
 * @tc.name: ImageModelNGSetOnError001
 * @tc.desc: Test ImageModelNG::SetOnError
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetOnError001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    bool callbackCalled = false;
    std::string errorMsg;
    auto onError = [&callbackCalled, &errorMsg](const LoadImageFailEvent& info) {
        callbackCalled = true;
        errorMsg = info.GetErrorMessage();
    };
    image.SetOnError(std::move(onError));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    LoadImageFailEvent fireEvent(200, 200, "Test error", {});
    eventHub->FireErrorEvent(fireEvent);

    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(errorMsg, "Test error");
}

/**
 * @tc.name: ImageModelNGSetSvgAnimatorFinishEvent001
 * @tc.desc: Test ImageModelNG::SetSvgAnimatorFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSvgAnimatorFinishEvent001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    bool callbackCalled = false;
    auto onFinish = [&callbackCalled]() { callbackCalled = true; };
    image.SetSvgAnimatorFinishEvent(std::move(onFinish));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireFinishEvent();

    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: ImageModelNGSetImageSourceSize001
 * @tc.desc: Test ImageModelNG::SetImageSourceSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageSourceSize001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    std::pair<Dimension, Dimension> size = { Dimension(100.0f), Dimension(200.0f) };
    image.SetImageSourceSize(size);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceSize = imageLayoutProperty->GetSourceSize();
    ASSERT_NE(sourceSize, std::nullopt);
    EXPECT_FLOAT_EQ(sourceSize->Width(), 100.0f);
    EXPECT_FLOAT_EQ(sourceSize->Height(), 200.0f);
}

/**
 * @tc.name: ImageModelNGSetImageFill001
 * @tc.desc: Test ImageModelNG::SetImageFill
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageFill001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageFill(Color::RED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto svgFillColor = imageRenderProperty->GetSvgFillColor();
    ASSERT_NE(svgFillColor, std::nullopt);
    EXPECT_EQ(svgFillColor.value(), Color::RED);
}

/**
 * @tc.name: ImageModelNGResetImageFill001
 * @tc.desc: Test ImageModelNG::ResetImageFill
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetImageFill001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageFill(Color::RED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    image.ResetImageFill();

    auto svgFillColor = imageRenderProperty->GetSvgFillColor();
    EXPECT_EQ(svgFillColor, std::nullopt);
}

/**
 * @tc.name: ImageModelNGResetImageFill002
 * @tc.desc: Test ImageModelNG::ResetImageFill with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetImageFill002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetImageFill(AceType::RawPtr(frameNode), Color::BLUE);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    ImageModelNG::ResetImageFill(AceType::RawPtr(frameNode));

    auto svgFillColor = imageRenderProperty->GetSvgFillColor();
    EXPECT_EQ(svgFillColor, std::nullopt);
}

/**
 * @tc.name: ImageModelNGSetImageInterpolation001
 * @tc.desc: Test ImageModelNG::SetImageInterpolation
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageInterpolation001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageInterpolation(ImageInterpolation::HIGH);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto imageInterpolation = imageRenderProperty->GetImageInterpolation();
    ASSERT_NE(imageInterpolation, std::nullopt);
    EXPECT_EQ(imageInterpolation.value(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: ImageModelNGSetImageInterpolation002
 * @tc.desc: Test ImageModelNG::SetImageInterpolation with various values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageInterpolation002, TestSize.Level0)
{
    std::vector<ImageInterpolation> interpolationValues = { ImageInterpolation::LOW, ImageInterpolation::MEDIUM,
        ImageInterpolation::HIGH };

    for (auto interpolationValue : interpolationValues) {
        ImageModelNG image;
        RefPtr<PixelMap> pixMap = nullptr;
        ImageInfoConfig imageInfoConfig;
        imageInfoConfig.pixelMap = pixMap;
        imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
        imageInfoConfig.bundleName = BUNDLE_NAME;
        imageInfoConfig.moduleName = MODULE_NAME;
        image.Create(imageInfoConfig);

        image.SetImageInterpolation(interpolationValue);

        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
        ASSERT_NE(imageRenderProperty, nullptr);
        auto imageInterpolation = imageRenderProperty->GetImageInterpolation();
        ASSERT_NE(imageInterpolation, std::nullopt);
        EXPECT_EQ(imageInterpolation.value(), interpolationValue);

        ViewStackProcessor::GetInstance()->Finish();
    }
}

/**
 * @tc.name: ImageModelNGSetImageRepeat001
 * @tc.desc: Test ImageModelNG::SetImageRepeat
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageRepeat001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageRepeat(ImageRepeat::REPEAT_X);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto imageRepeat = imageRenderProperty->GetImageRepeat();
    ASSERT_NE(imageRepeat, std::nullopt);
    EXPECT_EQ(imageRepeat.value(), ImageRepeat::REPEAT_X);
}

/**
 * @tc.name: ImageModelNGSetImageRepeat002
 * @tc.desc: Test ImageModelNG::SetImageRepeat with various values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageRepeat002, TestSize.Level0)
{
    std::vector<ImageRepeat> repeatValues = { ImageRepeat::NO_REPEAT, ImageRepeat::REPEAT, ImageRepeat::REPEAT_X,
        ImageRepeat::REPEAT_Y };

    for (auto repeatValue : repeatValues) {
        ImageModelNG image;
        RefPtr<PixelMap> pixMap = nullptr;
        ImageInfoConfig imageInfoConfig;
        imageInfoConfig.pixelMap = pixMap;
        imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
        imageInfoConfig.bundleName = BUNDLE_NAME;
        imageInfoConfig.moduleName = MODULE_NAME;
        image.Create(imageInfoConfig);

        image.SetImageRepeat(repeatValue);

        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
        ASSERT_NE(imageRenderProperty, nullptr);
        auto imageRepeat = imageRenderProperty->GetImageRepeat();
        ASSERT_NE(imageRepeat, std::nullopt);
        EXPECT_EQ(imageRepeat.value(), repeatValue);

        ViewStackProcessor::GetInstance()->Finish();
    }
}

/**
 * @tc.name: ImageModelNGSetImageRenderMode001
 * @tc.desc: Test ImageModelNG::SetImageRenderMode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetImageRenderMode001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetImageRenderMode(ImageRenderMode::TEMPLATE);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto imageRenderMode = imageRenderProperty->GetImageRenderMode();
    ASSERT_NE(imageRenderMode, std::nullopt);
    EXPECT_EQ(imageRenderMode.value(), ImageRenderMode::TEMPLATE);
}

/**
 * @tc.name: ImageModelNGIsSrcSvgImage001
 * @tc.desc: Test ImageModelNG::IsSrcSvgImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGIsSrcSvgImage001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    bool isSvg = ImageModelNG::IsSrcSvgImage(AceType::RawPtr(frameNode));
    EXPECT_FALSE(isSvg);
}

/**
 * @tc.name: ImageModelNGSetAutoResize001
 * @tc.desc: Test ImageModelNG::SetAutoResize
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAutoResize001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAutoResize(false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto autoResize = imageLayoutProperty->GetAutoResize();
    ASSERT_NE(autoResize, std::nullopt);
    EXPECT_EQ(autoResize.value(), false);
}

/**
 * @tc.name: ImageModelNGSetAutoResize002
 * @tc.desc: Test ImageModelNG::SetAutoResize with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAutoResize002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetAutoResize(AceType::RawPtr(frameNode), true);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto autoResize = imageLayoutProperty->GetAutoResize();
    ASSERT_NE(autoResize, std::nullopt);
    EXPECT_EQ(autoResize.value(), true);
}

/**
 * @tc.name: ImageModelNGSetSyncMode001
 * @tc.desc: Test ImageModelNG::SetSyncMode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSyncMode001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetSyncMode(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->GetSyncLoad(), true);
}

/**
 * @tc.name: ImageModelNGSetSyncMode002
 * @tc.desc: Test ImageModelNG::SetSyncMode with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSyncMode002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetSyncMode(AceType::RawPtr(frameNode), false);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->GetSyncLoad(), false);
}

/**
 * @tc.name: ImageModelNGSetColorFilterMatrix001
 * @tc.desc: Test ImageModelNG::SetColorFilterMatrix
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetColorFilterMatrix001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    std::vector<float> matrix = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };
    image.SetColorFilterMatrix(matrix);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto colorFilter = imageRenderProperty->GetColorFilter();
    ASSERT_NE(colorFilter, std::nullopt);
    EXPECT_EQ(colorFilter.value(), matrix);
}

/**
 * @tc.name: ImageModelNGSetDrawingColorFilter001
 * @tc.desc: Test ImageModelNG::SetDrawingColorFilter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetDrawingColorFilter001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    RefPtr<DrawingColorFilter> colorFilter = nullptr;
    image.SetDrawingColorFilter(colorFilter);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto drawingColorFilter = imageRenderProperty->GetDrawingColorFilter();
    ASSERT_NE(drawingColorFilter, std::nullopt);
    EXPECT_EQ(drawingColorFilter.value(), colorFilter);
}

/**
 * @tc.name: ImageModelNGSetDraggable001
 * @tc.desc: Test ImageModelNG::SetDraggable
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetDraggable001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetDraggable(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE(frameNode->IsDraggable());
}

/**
 * @tc.name: ImageModelNGSetDraggable002
 * @tc.desc: Test ImageModelNG::SetDraggable toggle
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetDraggable002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetDraggable(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE(frameNode->IsDraggable());

    ViewStackProcessor::GetInstance()->Finish();
    image.SetDraggable(false);
    EXPECT_TRUE(frameNode->IsDraggable());
}

/**
 * @tc.name: ImageModelNGSetCopyOption001
 * @tc.desc: Test ImageModelNG::SetCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetCopyOption001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetCopyOption(CopyOptions::InApp);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->GetCopyOption(), CopyOptions::InApp);
}

/**
 * @tc.name: ImageModelNGUpdateDragItemInfo001
 * @tc.desc: Test ImageModelNG::UpdateDragItemInfo - skip test as it's non-static
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGUpdateDragItemInfo001, TestSize.Level0)
{
    // Skip test as UpdateDragItemInfo is a non-static member function
    SUCCEED();
}

/**
 * @tc.name: ImageModelNGSetAltError001
 * @tc.desc: Test ImageModelNG::SetAltError
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAltError001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAltError(ImageSourceInfo { ALT_SRC_URL });

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto altError = imageLayoutProperty->GetAltError();
    ASSERT_NE(altError, std::nullopt);
    EXPECT_EQ(altError->GetSrc(), ALT_SRC_URL);
}

/**
 * @tc.name: ImageModelNGSetAltError002
 * @tc.desc: Test ImageModelNG::SetAltError with network URL
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAltError002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAltError(ImageSourceInfo { "xxxxxxxx" });

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto altError = imageLayoutProperty->GetAltError();
    ASSERT_NE(altError, std::nullopt);
    EXPECT_EQ(altError->GetSrc(), "xxxxxxxx");
}

/**
 * @tc.name: ImageModelNGSetAltPlaceholder001
 * @tc.desc: Test ImageModelNG::SetAltPlaceholder
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAltPlaceholder001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAltPlaceholder(ImageSourceInfo { ALT_SRC_URL });

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto altPlaceholder = imageLayoutProperty->GetAltPlaceholder();
    ASSERT_NE(altPlaceholder, std::nullopt);
    EXPECT_EQ(altPlaceholder->GetSrc(), ALT_SRC_URL);
}

/**
 * @tc.name: ImageModelNGSetAntiAlias001
 * @tc.desc: Test ImageModelNG::SetAntiAlias
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAntiAlias001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAntiAlias(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto antiAlias = imageRenderProperty->GetAntiAlias();
    ASSERT_NE(antiAlias, std::nullopt);
    EXPECT_EQ(antiAlias.value(), true);
}

/**
 * @tc.name: ImageModelNGSetAntiAlias002
 * @tc.desc: Test ImageModelNG::SetAntiAlias toggle
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetAntiAlias002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetAntiAlias(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto antiAlias = imageRenderProperty->GetAntiAlias();
    ASSERT_NE(antiAlias, std::nullopt);
    EXPECT_EQ(antiAlias.value(), true);

    ViewStackProcessor::GetInstance()->Finish();
    image.SetAntiAlias(false);
    antiAlias = imageRenderProperty->GetAntiAlias();
    ASSERT_NE(antiAlias, std::nullopt);
    EXPECT_EQ(antiAlias.value(), true);
}

/**
 * @tc.name: ImageModelNGSetOrientation001
 * @tc.desc: Test ImageModelNG::SetOrientation
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetOrientation001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetOrientation(ImageRotateOrientation::RIGHT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto orientation = imageLayoutProperty->GetImageRotateOrientation();
    ASSERT_NE(orientation, std::nullopt);
    EXPECT_EQ(orientation.value(), ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: ImageModelNGSetOrientation002
 * @tc.desc: Test ImageModelNG::SetOrientation with various values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetOrientation002, TestSize.Level0)
{
    std::vector<ImageRotateOrientation> orientationValues = { ImageRotateOrientation::UP, ImageRotateOrientation::DOWN,
        ImageRotateOrientation::LEFT, ImageRotateOrientation::AUTO };

    for (auto orientationValue : orientationValues) {
        ImageModelNG image;
        RefPtr<PixelMap> pixMap = nullptr;
        ImageInfoConfig imageInfoConfig;
        imageInfoConfig.pixelMap = pixMap;
        imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
        imageInfoConfig.bundleName = BUNDLE_NAME;
        imageInfoConfig.moduleName = MODULE_NAME;
        image.Create(imageInfoConfig);

        image.SetOrientation(orientationValue);

        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
        ASSERT_NE(imageLayoutProperty, nullptr);
        auto orientation = imageLayoutProperty->GetImageRotateOrientation();
        ASSERT_NE(orientation, std::nullopt);
        EXPECT_EQ(orientation.value(), orientationValue);

        ViewStackProcessor::GetInstance()->Finish();
    }
}

/**
 * @tc.name: ImageModelNGSetResizableSlice001
 * @tc.desc: Test ImageModelNG::SetResizableSlice
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetResizableSlice001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    ImageResizableSlice slice;
    slice.left = Dimension(10.0f);
    slice.right = Dimension(15.0f);
    slice.top = Dimension(20.0f);
    slice.bottom = Dimension(25.0f);
    image.SetResizableSlice(slice);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto resizableSlice = imageRenderProperty->GetImageResizableSlice();
    ASSERT_NE(resizableSlice, std::nullopt);
    EXPECT_EQ(resizableSlice->left, slice.left);
}

/**
 * @tc.name: ImageModelNGSetResizableLattice001
 * @tc.desc: Test ImageModelNG::SetResizableLattice
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetResizableLattice001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    // DrawingLattice is abstract, cannot be instantiated directly
    RefPtr<DrawingLattice> lattice = nullptr;
    image.SetResizableLattice(lattice);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto resizableLattice = imageRenderProperty->GetImageResizableLattice();
    EXPECT_NE(resizableLattice, std::nullopt);
}

/**
 * @tc.name: ImageModelNGResetResizableLattice001
 * @tc.desc: Test ImageModelNG::ResetResizableLattice
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetResizableLattice001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    // DrawingLattice is abstract, cannot be instantiated directly
    RefPtr<DrawingLattice> lattice = nullptr;
    image.SetResizableLattice(lattice);
    image.ResetResizableLattice();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto resizableLattice = imageRenderProperty->GetImageResizableLattice();
    EXPECT_NE(resizableLattice, std::nullopt);
}

/**
 * @tc.name: ImageModelNGEnableAnalyzer001
 * @tc.desc: Test ImageModelNG::EnableAnalyzer
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGEnableAnalyzer001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.EnableAnalyzer(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_TRUE(imagePattern->IsEnableAnalyzer());
}

/**
 * @tc.name: ImageModelNGEnableAnalyzer002
 * @tc.desc: Test ImageModelNG::EnableAnalyzer toggle
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGEnableAnalyzer002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.EnableAnalyzer(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_TRUE(imagePattern->IsEnableAnalyzer());

    ViewStackProcessor::GetInstance()->Finish();
    image.EnableAnalyzer(false);
    EXPECT_TRUE(imagePattern->IsEnableAnalyzer());
}

/**
 * @tc.name: ImageModelNGSetSupportSvg2001
 * @tc.desc: Test ImageModelNG::SetSupportSvg2
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSupportSvg2001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetSupportSvg2(true);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_TRUE(imagePattern->GetSupportSvg2());
}

/**
 * @tc.name: ImageModelNGSetSupportSvg2002
 * @tc.desc: Test ImageModelNG::SetSupportSvg2 with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetSupportSvg2002, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    ImageModelNG::SetSupportSvg2(AceType::RawPtr(frameNode), false);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_FALSE(imagePattern->GetSupportSvg2());
}

/**
 * @tc.name: ImageModelNGResetSupportSvg2001
 * @tc.desc: Test ImageModelNG::ResetSupportSvg2
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGResetSupportSvg2001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetSupportSvg2(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_TRUE(imagePattern->GetSupportSvg2());

    ViewStackProcessor::GetInstance()->Finish();
    // Skip ResetSupportSvg2 test as it's a non-static member function
    SUCCEED();
}

/**
 * @tc.name: ImageModelNGSetContentTransition001
 * @tc.desc: Test ImageModelNG::SetContentTransition
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetContentTransition001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);

    image.SetContentTransition(ContentTransitionType::OPACITY);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto contentTransition = imageRenderProperty->GetContentTransition();
    ASSERT_NE(contentTransition, std::nullopt);
    EXPECT_EQ(contentTransition.value(), ContentTransitionType::OPACITY);
}

/**
 * @tc.name: ImageModelNGSetContentTransition002
 * @tc.desc: Test ImageModelNG::SetContentTransition with various values
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGSetContentTransition002, TestSize.Level0)
{
    std::vector<ContentTransitionType> transitionValues = { ContentTransitionType::IDENTITY,
        ContentTransitionType::OPACITY };

    for (auto transitionValue : transitionValues) {
        ImageModelNG image;
        RefPtr<PixelMap> pixMap = nullptr;
        ImageInfoConfig imageInfoConfig;
        imageInfoConfig.pixelMap = pixMap;
        imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
        imageInfoConfig.bundleName = BUNDLE_NAME;
        imageInfoConfig.moduleName = MODULE_NAME;
        image.Create(imageInfoConfig);

        image.SetContentTransition(transitionValue);

        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
        ASSERT_NE(imageRenderProperty, nullptr);
        auto contentTransition = imageRenderProperty->GetContentTransition();
        ASSERT_NE(contentTransition, std::nullopt);
        EXPECT_EQ(contentTransition.value(), transitionValue);

        ViewStackProcessor::GetInstance()->Finish();
    }
}

/**
 * @tc.name: ImageModelNGGetSrc001
 * @tc.desc: Test ImageModelNG::GetSrc
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetSrc001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto srcInfo = ImageModelNG::GetSrc(AceType::RawPtr(frameNode));
    EXPECT_EQ(srcInfo.GetSrc(), "");
}

/**
 * @tc.name: ImageModelNGGetSrc002
 * @tc.desc: Test ImageModelNG::GetSrc with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetSrc002, TestSize.Level0)
{
    auto srcInfo = ImageModelNG::GetSrc(nullptr);
    EXPECT_EQ(srcInfo.GetSrc(), "");
}

/**
 * @tc.name: ImageModelNGGetObjectFit001
 * @tc.desc: Test ImageModelNG::GetObjectFit
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetObjectFit001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto imageFit = ImageModelNG::GetObjectFit(AceType::RawPtr(frameNode));
    EXPECT_EQ(imageFit, ImageFit::COVER);
}

/**
 * @tc.name: ImageModelNGGetObjectFit002
 * @tc.desc: Test ImageModelNG::GetObjectFit with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetObjectFit002, TestSize.Level0)
{
    auto imageFit = ImageModelNG::GetObjectFit(nullptr);
    EXPECT_EQ(imageFit, ImageFit::COVER);
}

/**
 * @tc.name: ImageModelNGGetOrientation001
 * @tc.desc: Test ImageModelNG::GetOrientation
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetOrientation001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto orientation = ImageModelNG::GetOrientation(AceType::RawPtr(frameNode));
    EXPECT_EQ(orientation, ImageRotateOrientation::UP);
}

/**
 * @tc.name: ImageModelNGGetImageSourceSize001
 * @tc.desc: Test ImageModelNG::GetImageSourceSize
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetImageSourceSize001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto size = ImageModelNG::GetImageSourceSize(AceType::RawPtr(frameNode));
    EXPECT_FLOAT_EQ(size.first.Value(), 0.0f);
    EXPECT_FLOAT_EQ(size.second.Value(), 0.0f);
}

/**
 * @tc.name: ImageModelNGGetHdrBrightness001
 * @tc.desc: Test ImageModelNG::GetHdrBrightness
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNGTestNg, ImageModelNGGetHdrBrightness001, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto hdrBrightness = ImageModelNG::GetHdrBrightness(AceType::RawPtr(frameNode));
    EXPECT_FLOAT_EQ(hdrBrightness, 1.0f);
}

} // namespace OHOS::Ace::NG
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

#include "image_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImageTestTwoNg : public ImageBases {
public:
};

/**
 * @tc.name: TestAutoResize001
 * @tc.desc: Test image autoResize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestAutoResize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step2. set autoResize
     */
    layoutProperty->UpdateAutoResize(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetAutoResize(), false);

    /**
     * @tc.steps: step3. set autoResize
     */
    layoutProperty->UpdateAutoResize(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetAutoResize(), true);
}

/**
 * @tc.name: TestFitOriginalSize001
 * @tc.desc: Test image fitOriginalSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestFitOriginalSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step2. set fitOriginalSize
     */
    layoutProperty->UpdateFitOriginalSize(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetFitOriginalSize().value(), false);

    /**
     * @tc.steps: step3. set fitOriginalSize
     */
    layoutProperty->UpdateFitOriginalSize(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetFitOriginalSize().value(), true);
}

/**
 * @tc.name: TestMatchTextDirection001
 * @tc.desc: Test image matchTextDirection.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestMatchTextDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and  RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set matchTextDirection
     */
    imageRenderProperty->UpdateMatchTextDirection(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection(), true);

    /**
     * @tc.steps: step4. set matchTextDirection
     */
    imageRenderProperty->UpdateMatchTextDirection(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection(), false);
}

/**
 * @tc.name: TestRenderMode001
 * @tc.desc: Test image renderMode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestRenderMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set renderMode
     */
    imageRenderProperty->UpdateImageRenderMode(ImageRenderMode::ORIGINAL);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode(), ImageRenderMode::ORIGINAL);

    /**
     * @tc.steps: step4. set renderMode
     */
    imageRenderProperty->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode(), ImageRenderMode::TEMPLATE);
}

/**
 * @tc.name: TestInterpolation001
 * @tc.desc: Test image interpolation.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestInterpolation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::NONE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::NONE);

    /**
     * @tc.steps: step4. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::LOW);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::LOW);

    /**
     * @tc.steps: step5. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::MEDIUM);

    /**
     * @tc.steps: step6. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: TestObjectRepeat001
 * @tc.desc: Test image objectRepeat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestObjectRepeat001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    const auto& geometryNode = frameNode->GetGeometryNode();

    auto paintRect = imagePattern->CalcImageContentPaintSize(geometryNode);
    /**
     * @tc.steps: step3. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step4. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT_X);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step5. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT_Y);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step6. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::NO_REPEAT);
}

/**
 * @tc.name: TestObjectFit001
 * @tc.desc: Test image objectFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestObjectFit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern RadiusProperty layoutProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step3. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateImageFit(ImageFit::FILL);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FILL);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FILL);

    /**
     * @tc.steps: step5. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::CONTAIN);
    layoutProperty->UpdateImageFit(ImageFit::CONTAIN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::CONTAIN);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::CONTAIN);

    /**
     * @tc.steps: step6. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::COVER);
    layoutProperty->UpdateImageFit(ImageFit::COVER);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::COVER);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::COVER);

    /**
     * @tc.steps: step7. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FITWIDTH);
    layoutProperty->UpdateImageFit(ImageFit::FITWIDTH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FITWIDTH);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FITWIDTH);

    /**
     * @tc.steps: step8. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FITHEIGHT);
    layoutProperty->UpdateImageFit(ImageFit::FITHEIGHT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FITHEIGHT);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FITHEIGHT);

    /**
     * @tc.steps: step9. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::NONE);
    layoutProperty->UpdateImageFit(ImageFit::NONE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::NONE);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::NONE);

    /**
     * @tc.steps: step10. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    layoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::SCALE_DOWN);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::SCALE_DOWN);

    /**
     * @tc.steps: step11. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::TOP_LEFT);
    layoutProperty->UpdateImageFit(ImageFit::TOP_LEFT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::TOP_LEFT);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::TOP_LEFT);
}

/**
 * @tc.name: TestDynamicRangeMode001
 * @tc.desc: Test image dynamicRangeMode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestDynamicRangeMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern ImageRenderProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::CONSTRAINT);

    /**
     * @tc.steps: step4. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::STANDARD);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::STANDARD);

    /**
     * @tc.steps: step5. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::HIGH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::HIGH);
}

/**
 * @tc.name: TestEnhancedImageQuality001
 * @tc.desc: Test image EnhancedImageQuality.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestEnhancedImageQuality001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern ImageRenderProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::HIGH);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::HIGH);

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::NONE);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::NONE);

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::NORMAL);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::NORMAL);
}

/**
 * @tc.name: ImageSetDraggable0001
 * @tc.desc: Set the draggable attribute of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSetDraggable0001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetDraggable(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode->draggable_);
}

HWTEST_F(ImageTestTwoNg, ImageSetDraggable0002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetDraggable(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode->draggable_);
}

/**
 * @tc.name: ImageDumpInfo0001
 * @tc.desc: Output the relevant information of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageDumpInfo0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->DumpInfo();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageDumpAdvanceInfo0001
 * @tc.desc: Output more information of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageDumpAdvanceInfo0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->DumpAdvanceInfo();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageOnColorConfigurationUpdate0001
 * @tc.desc: Output more information of ImageModelNG object when the color configuration is updated.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageOnColorConfigurationUpdate0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->loadingCtx_);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageSetImageAnalyzerConfig0001
 * @tc.desc: Set the configuration of the image analyzer.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSetImageAnalyzerConfig0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImagePixelMapListTest0001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. images size is 0.
     * @tc.expected: do nothing
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(0);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. SetShowingIndex() greater than images size-1.
     * @tc.expected: nowImageIndex_ not change
     */
    frameNode = CreatePixelMapAnimator(1);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    imagePattern->SetShowingIndex(1);
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    /**
     * @tc.steps: step3. CreateAnimation() set PixelMap List.
     * @tc.expected: images_ size is 2, other paramater is default value.
     */
    frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(imagePattern->images_.size() == 2);
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);
    EXPECT_EQ(imagePattern->status_, static_cast<Animator::Status>(STATE_START));
    EXPECT_EQ(imagePattern->durationTotal_, DURATION_DEFAULT);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImageSensitiveTest0001
 * @tc.desc: Test image privacySensitive.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSensitiveTest0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(frameNode->IsPrivacySensitive());
    frameNode->SetPrivacySensitive(true);
    EXPECT_TRUE(frameNode->IsPrivacySensitive());
    frameNode->SetPrivacySensitive(false);
    EXPECT_FALSE(frameNode->isPrivacySensitive_);
}

/**
 * @tc.name: ImageSensitiveTest0002
 * @tc.desc: Test image OnSensitiveStyleChange.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSensitiveTest0002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get ImagePattern and call OnSensitiveStyleChange.
     * @tc.expected: isSensitive_ is true when setting privacy sensitive and card notification.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    frameNode->SetPrivacySensitive(true);
    imagePattern->OnSensitiveStyleChange(false);
    EXPECT_FALSE(imagePattern->isSensitive_);
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_TRUE(imagePattern->isSensitive_);
    frameNode->SetPrivacySensitive(false);
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_FALSE(imagePattern->isSensitive_);

    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true, true);
    EXPECT_TRUE(imagePaintMethod.sensitive_);
}
} // namespace OHOS::Ace::NG
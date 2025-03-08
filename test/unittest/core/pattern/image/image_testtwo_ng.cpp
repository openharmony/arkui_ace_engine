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

#include "base/image/image_defines.h"

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
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetDraggable(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode->draggable_);
}

HWTEST_F(ImageTestTwoNg, ImageSetDraggable0002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
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
    EXPECT_EQ(imagePattern->status_, static_cast<AnimatorStatus>(STATE_START));
    EXPECT_EQ(imagePattern->durationTotal_, 0);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    /**
    * @tc.steps: step4. set SrcUndefined and call OnAnimatedModifyDone.
    * @tc.expected: isSrcUndefined_ is true.
    */
    imagePattern->imageType_ = ImageType::BASE;
    imagePattern->status_ = AnimatorStatus::PAUSED;
    imagePattern->SetSrcUndefined(true);
    imagePattern->OnModifyDone();
    imagePattern->OnAnimatedModifyDone();
    EXPECT_TRUE(imagePattern->isSrcUndefined_);
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
    ImagePaintMethod imagePaintMethod(
        imagePattern->image_, { .selected = true, .imageOverlayModifier = nullptr, .sensitive = true });
    EXPECT_TRUE(imagePaintMethod.sensitive_);
}

/**
 * @tc.name: ImagePixelMapListTest0002
 * @tc.desc: Test initial value
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);

    /**
     * @tc.steps: step2. Test imagenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);

    /**
     * @tc.steps: step3. Test FillMode
     * @tc.expected: BACKWARDS
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);

    /**
     * @tc.steps: step4. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    /**
     * @tc.steps: step5. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    /**
     * @tc.steps: step6. Test images size
     * @tc.expected: 2
     */
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step7. Test isAnimation
     * @tc.expected: true
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);

    /**
     * @tc.steps: step8. Test status
     * @tc.expected: STATE_START
     */
    EXPECT_EQ(imagePattern->status_, static_cast<AnimatorStatus>(STATE_START));

    /**
     * @tc.steps: step9. Test durationTotal
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    /**
     * @tc.steps: step10. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    /**
     * @tc.steps: step11. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);

    /**
     * @tc.steps: step12. Test ImageType
     * @tc.expected: ANIMATION
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::ANIMATED_DRAWABLE);
}

/**
 * @tc.name: ImagePixelMapListTest0003
 * @tc.desc: Test SetDuration
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    imagePattern->StopAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::STOPPED);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test Duration, default value
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    /**
     * @tc.steps: step3. Test Duration, Set Duration -10
     * @tc.expected: DURATION_DEFAULT
     */
    imagePattern->SetDuration(-10);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    /**
     * @tc.steps: step4. Test Duration, Set Duration 0
     * @tc.expected: 0
     */
    imagePattern->SetDuration(0);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), 0);

    /**
     * @tc.steps: step5. Test Duration, Set Duration 10
     * @tc.expected: 10
     */
    imagePattern->SetDuration(10);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), 10);
}

/**
 * @tc.name: ImagePixelMapListTest0004
 * @tc.desc: Test Iteration
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    imagePattern->StopAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::STOPPED);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test Iteration, default value
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test Iteration, Set Iteration -10
     * @tc.expected: ITERATION_DEFAULT
     */
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 0; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, -10);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0005
 * @tc.desc: Test GetIsAnimation()
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test isAnimation
     * @tc.expected: true
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);

    /**
     * @tc.steps: step3. Test isAnimation
     * @tc.expected: false
     */
    imagePattern->SetImageType(ImageType::BASE);
    EXPECT_EQ(imagePattern->GetIsAnimation(), false);

    /**
     * @tc.steps: step4. Test isAnimation
     * @tc.expected: false
     */
    imagePattern->SetImageType(ImageType::BASE);
    EXPECT_EQ(imagePattern->GetIsAnimation(), false);

    /**
     * @tc.steps: step5. Test isAnimation
     * @tc.expected: true
     */
    imagePattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);
}

/**
 * @tc.name: ImagePixelMapListTest0006
 * @tc.desc: Test GetImageType()
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test GetImageType
     * @tc.expected: ANIMATION
     */
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::ANIMATED_DRAWABLE);

    /**
     * @tc.steps: step3. Test GetImageType
     * @tc.expected: BASE
     */
    imagePattern->SetImageType(ImageType::BASE);
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::BASE);

    /**
     * @tc.steps: step4. Test GetImageType
     * @tc.expected: UNDEFINED
     */
    imagePattern->SetImageType(ImageType::BASE);
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::BASE);

    /**
     * @tc.steps: step5. Test GetImageType
     * @tc.expected: ANIMATION
     */
    imagePattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::ANIMATED_DRAWABLE);
}

/**
 * @tc.name: ImagePixelMapListTest0007
 * @tc.desc: Test status
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test status
     * @tc.expected: STATE_START
     */
    EXPECT_EQ(imagePattern->status_, static_cast<AnimatorStatus>(STATE_START));

    /**
     * @tc.steps: step3. Test status
     * @tc.expected: STOPPED
     */
    imagePattern->StopAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::STOPPED);

    /**
     * @tc.steps: step4. Test status
     * @tc.expected: RUNNING
     */
    imagePattern->StartAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::RUNNING);
}

/**
 * @tc.name: ImagePixelMapListTest0008
 * @tc.desc: Test durationTotal
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    imagePattern->StopAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::STOPPED);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step2. Test durationTotal, default value
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    /**
     * @tc.steps: step3. Test durationTotal, Set Duration -10
     * @tc.expected: 0
     */
    imagePattern->SetDuration(-10);
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    /**
     * @tc.steps: step4. Test durationTotal, Set Duration 0
     * @tc.expected: 0
     */
    imagePattern->SetDuration(0);
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    /**
     * @tc.steps: step5. Test durationTotal, Set Duration 10
     * @tc.expected: 0
     */
    imagePattern->SetDuration(10);
    EXPECT_EQ(imagePattern->durationTotal_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0009
 * @tc.desc: Test GetDuration
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        imageProperties.duration = 200;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    imagePattern->StopAnimation();
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::STOPPED);
    EXPECT_TRUE(imagePattern->images_.size() == 10);

    /**
     * @tc.steps: step2. Test GetDuration, default value
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    /**
     * @tc.steps: step3. Test GetDuration, Set Duration 10
     * @tc.expected: 10
     */
    imagePattern->SetDuration(10);
    EXPECT_EQ(imagePattern->durationTotal_, 0);
    EXPECT_EQ(imagePattern->animator_->GetDuration(), 10);
}

/**
 * @tc.name: ImagePixelMapListTest0010
 * @tc.desc: Test SetSrcUndefined
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test framenode tag
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto frameNode = ImageTestTwoNg::CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->animator_, nullptr);
    EXPECT_EQ(imagePattern->animator_->GetFillMode(), FillMode::BACKWARDS);
    EXPECT_TRUE(imagePattern->images_.size() == 2);

    /**
     * @tc.steps: step1. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);

    /**
     * @tc.steps: step2. Test isSrcUndefined
     * @tc.expected: false
     */
    imagePattern->SetSrcUndefined(true);
    EXPECT_EQ(imagePattern->isSrcUndefined_, true);
}

/**
 * @tc.name: ImagePixelMapListTest0011
 * @tc.desc: Test frameNode before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0011, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test imagenode
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test imagenode is empty
     * @tc.expected: true
     */
    EXPECT_EQ(frameNode->GetChildren().empty(), true);
}

/**
 * @tc.name: ImagePixelMapListTest0012
 * @tc.desc: Test Duration before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0012, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0013
 * @tc.desc: Test Iteration before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0013, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0014
 * @tc.desc: Test images size before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0014, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test images size
     * @tc.expected: 10
     */
    EXPECT_TRUE(imagePattern->images_.size() == 10);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test images size
     * @tc.expected: 0
     */
    EXPECT_TRUE(imagePattern->images_.size() == 0);
}

/**
 * @tc.name: ImagePixelMapListTest0015
 * @tc.desc: Test isAnimation before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0015, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isAnimation
     * @tc.expected: true
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isAnimation
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), false);
}

/**
 * @tc.name: ImagePixelMapListTest0016
 * @tc.desc: Test status before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0016, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test status
     * @tc.expected: STATE_START
     */
    EXPECT_EQ(imagePattern->status_, static_cast<AnimatorStatus>(STATE_START));

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test status
     * @tc.expected: IDLE
     */
    EXPECT_EQ(imagePattern->status_, AnimatorStatus::IDLE);
}

/**
 * @tc.name: ImagePixelMapListTest0017
 * @tc.desc: Test durationTotal before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0017, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0018
 * @tc.desc: Test nowImageIndex before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0018, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0019
 * @tc.desc: Test isSrcUndefined before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0019, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);
}

/**
 * @tc.name: ImagePixelMapListTest0020
 * @tc.desc: Test ImageType before and after type switching, pixelMap list to resource
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0020, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test ImageType
     * @tc.expected: ANIMATION
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::ANIMATED_DRAWABLE);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test ImageType
     * @tc.expected: BASE
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::BASE);
}

/**
 * @tc.name: ImagePixelMapListTest0021
 * @tc.desc: Test frameNode before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0021, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test imagenode
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    EXPECT_EQ(frameNode->GetChildren().empty(), true);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test imagenode
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: ImagePixelMapListTest0022
 * @tc.desc: Test Duration before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0022, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0023
 * @tc.desc: Test Iteration before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePixelMapListTest0023, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestTwoNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: TestCreate001
 * @tc.desc: Test image Create.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestCreate001, TestSize.Level1)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    ImageModelNG image;
    image.SetSyncMode(frameNode, SYNCMODE_DEFAULT);
    EXPECT_EQ(imagePattern->GetSyncLoad(), SYNCMODE_DEFAULT);
    image.EnableAnalyzer(false);
    image.EnableAnalyzer(frameNode, true);
    imagePattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    image.ResetImageSrc(frameNode);
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::BASE);
}
} // namespace OHOS::Ace::NG
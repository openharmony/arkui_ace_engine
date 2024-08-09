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

class ImagePatternTestNg : public ImageBases {};

/**
 * @tc.name: TriggerVisibleAreaChangeForChild001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerVisibleAreaChangeForChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    bool flag = false;
    auto callback = [&flag](bool visible, double opacity) { flag = true; };
    for (auto& child : frameNode->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        EXPECT_NE(childNode, nullptr);
        childNode->GetEventHub<EventHub>()->GetVisibleAreaCallback(true).callback = callback;
    }
    auto testNode = TestNode::CreateTestNode(ElementRegister::GetInstance()->MakeUniqueId());
    frameNode->AddChild(testNode);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
    EXPECT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    frameNode->AddChild(imageNode);
    flag = false;
    imagePattern->TriggerVisibleAreaChangeForChild(frameNode, true, 1.0f);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: SetObscured001
 * @tc.desc: Test ResetImage and SetObscured for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetObscured001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto childNode = frameNode->GetFirstChild();
    EXPECT_NE(childNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    imageFrameNode->renderContext_.Reset();
    imagePattern->SetObscured();
    EXPECT_FALSE(frameNode->GetRenderContext()->HasObscured());
    imagePattern->altImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePattern->ResetImage();
    ASSERT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: SetColorFilter001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetColorFilter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    RefPtr<ImageRenderProperty> layoutProperty1 = imageNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(layoutProperty1, nullptr);

    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    /**
     * @tc.steps: step2. call SetColorFilter.
     * @tc.expected: DrawingColorFilter of imageNode is changed.
     */
    imagePattern->SetColorFilter(imageNode);
    EXPECT_TRUE(layoutProperty1->HasDrawingColorFilter());
}
/**
 * @tc.name: OnSensitiveStyleChange001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnSensitiveStyleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    frameNode->isPrivacySensitive_ = true;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto renderContext = frameNode->renderContext_;
    EXPECT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetOrCreateBackground();
    groupProperty->propBlurRadius = std::make_optional<Dimension>(1.0f);
    groupProperty->propBlurStyleOption = std::make_optional<BlurStyleOption>();
    /**
     * @tc.steps: step2. call OnSensitiveStyleChange.
     * @tc.expected: renderContext changed.
     */
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_TRUE(imagePattern->isSensitive_);
}

/**
 * @tc.name: SetDuration001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call SetDuration.
     * @tc.expected: duration_ is changed.
     */
    imagePattern->durationTotal_ = 1;
    imagePattern->animator_->duration_ = imagePattern->durationTotal_ + 1;
    imagePattern->animator_->status_ = Animator::Status::RUNNING;
    imagePattern->SetDuration(1.0f);
    imagePattern->animator_->NotifyRepeatListener();
    EXPECT_EQ(imagePattern->animator_->duration_, 1);
}
/**
 * @tc.name: FindCacheImageNode001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, FindCacheImageNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call FindCacheImageNode.
     * @tc.expected:.
     */
    auto pixeMap = CreatePixelMap(IMAGE_SRC_URL);
    auto ret = imagePattern->FindCacheImageNode(pixeMap);
    EXPECT_EQ(ret, imagePattern->cacheImages_.end());
}
/**
 * @tc.name: UpdateCacheImageInfo001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateCacheImageInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateCacheImageInfo.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(imageFrameNode, nullptr);
    ImagePattern::CacheImageStruct newCacheImageStruct(imageFrameNode);
    newCacheImageStruct.isLoaded = true;
    int32_t index = 0;
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    EXPECT_NE(imagePattern->images_.size(), 0);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    auto imageLayoutProperty = newCacheImageStruct.imageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);

    void* voidPtr1 = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap1 = PixelMap::CreatePixelMap(voidPtr1);
    imageSourceInfo.pixmap_ = pixelMap1;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    if (!frameNode->layoutProperty_->calcLayoutConstraint_) {
        frameNode->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    EXPECT_NE(frameNode->layoutProperty_->calcLayoutConstraint_, nullptr);
    CalcLength width(2.0f);
    CalcLength height(3.0f);
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize = std::make_optional<CalcSize>(width, height);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    EXPECT_FALSE(newCacheImageStruct.isLoaded);
}

/**
 * @tc.name: AddImageLoadSuccessEvent001
 * @tc.desc: Test GetNextIndex and AddImageLoadSuccessEvent for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AddImageLoadSuccessEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call AddImageLoadSuccessEvent.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    imagePattern->AddImageLoadSuccessEvent(imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    ImagePattern::CacheImageStruct cacheImageStruct(imageNode);
    imagePattern->cacheImages_.emplace_back(cacheImageStruct);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = imageNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->FireCompleteEvent(info);
    auto ret = imagePattern->GetNextIndex(0);
    EXPECT_EQ(ret, 1);
    imagePattern->nowImageIndex_ = 2;
    eventHub->FireCompleteEvent(info);
    imagePattern->nowImageIndex_ = 1;
    eventHub->FireCompleteEvent(info);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = nullptr;
    }
    eventHub->FireCompleteEvent(info);
    EXPECT_TRUE(imagePattern->cacheImages_.back().isLoaded);
}

/**
 * @tc.name: AdaptSelfSize001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AdaptSelfSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call AdaptSelfSize.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    imagePattern->AdaptSelfSize();
    EXPECT_TRUE(imagePattern->hasSizeChanged);
    CalcLength width(2.0f);
    CalcLength height(3.0f);
    EXPECT_NE(frameNode->layoutProperty_->calcLayoutConstraint_, nullptr);
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize = std::make_optional<CalcSize>();
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize->SetHeight(height);
    imagePattern->AdaptSelfSize();
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize->SetWidth(width);
    imagePattern->AdaptSelfSize();
    imagePattern->images_.clear();
    imagePattern->AdaptSelfSize();
    EXPECT_TRUE(imagePattern->hasSizeChanged);
}

/**
 * @tc.name: CreatePictureAnimation001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreatePictureAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call CreatePictureAnimation.
     * @tc.expected:
     */
    int32_t index = 0;
    int32_t size = 1;
    imagePattern->durationTotal_ = 1;
    auto pictureAnimation = imagePattern->CreatePictureAnimation(size);
    pictureAnimation->NotifyListener(index);
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}
} // namespace OHOS::Ace::NG
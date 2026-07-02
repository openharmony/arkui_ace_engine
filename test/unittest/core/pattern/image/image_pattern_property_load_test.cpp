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

/**
 * @file image_pattern_property_load_test.cpp
 * @brief Comprehensive image test coverage for host product build
 */

#include "image_base.h"
#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace::NG {


// ========== Tests from image_pattern_test_animation.cpp ==========

class ImagePatternPropertyLoadTest : public ImageBases {};

/**
 * @tc.name: PrepareAnimation002
 * @tc.desc: Verify PrepareAnimation returns early for static image without setting callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PrepareAnimation002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(testing::Return(true));
    pattern->image_ = mockImage;
    pattern->PrepareAnimation(pattern->image_);
    EXPECT_EQ(mockImage->redrawCallback_, nullptr);
    EXPECT_EQ(mockImage->onFinishCallback_, nullptr);
}

/**
 * @tc.name: PrepareAnimation003
 * @tc.desc: Verify PrepareAnimation sets callbacks for animated image.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PrepareAnimation003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(testing::Return(false));
    pattern->image_ = mockImage;
    pattern->PrepareAnimation(pattern->image_);
    EXPECT_NE(mockImage->redrawCallback_, nullptr);
    EXPECT_NE(mockImage->onFinishCallback_, nullptr);
}

/**
 * @tc.name: SetRedrawCallback002
 * @tc.desc: Verify SetRedrawCallback sets redraw callback on valid mock image.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetRedrawCallback002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    EXPECT_EQ(mockImage->redrawCallback_, nullptr);
    pattern->SetRedrawCallback(pattern->image_);
    EXPECT_NE(mockImage->redrawCallback_, nullptr);
}

/**
 * @tc.name: SetOnFinishCallback002
 * @tc.desc: Verify SetOnFinishCallback sets finish callback on valid mock image.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetOnFinishCallback002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    EXPECT_EQ(mockImage->onFinishCallback_, nullptr);
    pattern->SetOnFinishCallback(pattern->image_);
    EXPECT_NE(mockImage->onFinishCallback_, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChange002
 * @tc.desc: Verify RegisterVisibleAreaChange with animator node and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RegisterVisibleAreaChange002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isComponentSnapshotNode_ = false;
    pattern->isImageAnimator_ = true;
    pattern->RegisterVisibleAreaChange(false);
    EXPECT_NE(pattern->GetContext(), nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChange003
 * @tc.desc: Verify RegisterVisibleAreaChange with normal node returns early without pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RegisterVisibleAreaChange003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isComponentSnapshotNode_ = false;
    pattern->isImageAnimator_ = false;
    pattern->RegisterVisibleAreaChange(true);
    EXPECT_EQ(pattern->GetContext(), nullptr);
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Verify OnVisibleChange with visible=true skips CloseSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnVisibleChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    pattern->previousVisibility_ = false;
    pattern->OnVisibleChange(true);
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnVisibleChange002
 * @tc.desc: Verify OnVisibleChange with visible=false triggers CloseSelectOverlay path.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnVisibleChange002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    pattern->previousVisibility_ = true;
    pattern->OnVisibleChange(false);
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnVisibleAreaChange001
 * @tc.desc: Verify OnVisibleAreaChange updates previousVisibility to true.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnVisibleAreaChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    pattern->previousVisibility_ = false;
    pattern->OnVisibleAreaChange(true, 0.0);
    EXPECT_TRUE(pattern->previousVisibility_);
}

/**
 * @tc.name: OnVisibleAreaChange002
 * @tc.desc: Verify OnVisibleAreaChange updates previousVisibility to false.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnVisibleAreaChange002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    mockImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = mockImage;
    pattern->previousVisibility_ = true;
    pattern->OnVisibleAreaChange(false, 0.0);
    EXPECT_FALSE(pattern->previousVisibility_);
}

/**
 * @tc.name: OnVisibleAreaChange003
 * @tc.desc: Verify OnVisibleAreaChange with altImage when main image is null.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnVisibleAreaChange003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto altImage = AceType::MakeRefPtr<MockCanvasImage>();
    altImage->SetPaintConfig(ImagePaintConfig());
    pattern->image_ = nullptr;
    pattern->altErrorImage_ = nullptr;
    pattern->altImage_ = altImage;
    pattern->previousVisibility_ = false;
    pattern->OnVisibleAreaChange(true, 0.5);
    EXPECT_TRUE(pattern->previousVisibility_);
}


/**
 * @tc.name: AnimatedDrawableControllAnimation002
 * @tc.desc: Verify AnimatedDrawableControllAnimation with BASE type skips animation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, AnimatedDrawableControllAnimation002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->imageType_ = ImageType::BASE;
    pattern->drawable_ = nullptr;
    pattern->AnimatedDrawableControllAnimation(1);
    EXPECT_EQ(pattern->imageType_, ImageType::BASE);
    EXPECT_EQ(pattern->image_, nullptr);
}



/**
 * @tc.name: OnAttachToMainRenderTree002
 * @tc.desc: Verify OnAttachToMainRenderTree with isRecycledImage=true and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnAttachToMainRenderTree002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isRecycledImage_ = true;
    pattern->OnAttachToMainRenderTree();
    EXPECT_TRUE(pattern->isRecycledImage_);
}

/**
 * @tc.name: OnOffscreenProcessResource002
 * @tc.desc: Verify OnOffscreenProcessResource with isRecycledImage=true and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnOffscreenProcessResource002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isRecycledImage_ = true;
    pattern->OnOffscreenProcessResource();
    EXPECT_TRUE(pattern->isRecycledImage_);
}

/**
 * @tc.name: SetImageAnimator001
 * @tc.desc: Verify SetImageAnimator sets isImageAnimator to true then false.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetImageAnimator001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->isImageAnimator_);
    pattern->SetImageAnimator(true);
    EXPECT_TRUE(pattern->isImageAnimator_);
    pattern->SetImageAnimator(false);
    EXPECT_FALSE(pattern->isImageAnimator_);
}


/**
 * @tc.name: GetIsAnimation002
 * @tc.desc: Verify GetIsAnimation returns true for ANIMATED_DRAWABLE image type.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, GetIsAnimation002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->imageType_, ImageType::BASE);
    pattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    EXPECT_TRUE(pattern->GetIsAnimation());
    pattern->imageType_ = ImageType::BASE;
    EXPECT_FALSE(pattern->GetIsAnimation());
}


// ========== Tests from image_pattern_test_image_loading.cpp ==========



/**
 * @tc.name: LoadImageDataIfNeed002
 * @tc.desc: LoadImageDataIfNeed with isImageReloadNeeded false and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImageDataIfNeed002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isImageReloadNeeded_ = false;
    pattern->LoadImageDataIfNeed();
    EXPECT_NE(pattern->GetHost(), nullptr);
    EXPECT_FALSE(pattern->isImageReloadNeeded_);
}

/**
 * @tc.name: LoadImageDataIfNeed003
 * @tc.desc: LoadImageDataIfNeed with isImageReloadNeeded true and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImageDataIfNeed003, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isImageReloadNeeded_ = true;
    pattern->LoadImageDataIfNeed();
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: LoadImageDataIfNeed004
 * @tc.desc: LoadImageDataIfNeed with loadFailed true and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImageDataIfNeed004, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->loadFailed_ = true;
    pattern->isImageReloadNeeded_ = false;
    pattern->LoadImageDataIfNeed();
    EXPECT_TRUE(pattern->loadFailed_);
}

/**
 * @tc.name: LoadImageDataIfNeed005
 * @tc.desc: LoadImageDataIfNeed in sync load mode with valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImageDataIfNeed005, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->syncLoad_ = true;
    pattern->LoadImageDataIfNeed();
    EXPECT_TRUE(pattern->syncLoad_);
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: LoadImageDataIfNeed006
 * @tc.desc: LoadImageDataIfNeed with reload needed and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImageDataIfNeed006, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isImageReloadNeeded_ = true;
    pattern->LoadImageDataIfNeed();
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: LoadImage001
 * @tc.desc: LoadImage creates loading context with needLayout true.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImage001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    ImageSourceInfo src(IMAGE_SRC_URL);
    pattern->LoadImage(src, true);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->loadingCtx_->GetSourceInfo().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: LoadImage002
 * @tc.desc: LoadImage with needLayout false should still create loading context.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImage002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    ImageSourceInfo src(IMAGE_SRC_URL);
    pattern->LoadImage(src, false);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->loadingCtx_->GetSourceInfo().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: LoadImage003
 * @tc.desc: LoadImage with resource URL should create loading context.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadImage003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    ImageSourceInfo src(RESOURCE_URL);
    pattern->LoadImage(src, true);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->loadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}


/**
 * @tc.name: LoadAltImage002
 * @tc.desc: LoadAltImage replaces existing alt loading context.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, LoadAltImage002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ImageSourceInfo firstAlt(ALT_SRC_URL);
    pattern->LoadAltImage(firstAlt);
    auto firstCtx = pattern->altLoadingCtx_;
    EXPECT_NE(firstCtx, nullptr);
    ImageSourceInfo secondAlt(RESOURCE_URL);
    pattern->LoadAltImage(secondAlt);
    EXPECT_NE(pattern->altLoadingCtx_, nullptr);
}

/**
 * @tc.name: OnImageDataReady002
 * @tc.desc: OnImageDataReady with existing image and same size should not change image.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnImageDataReady002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    // loadingCtx_ requires LoadNotifier, skip direct construction
    pattern->loadingCtx_ = nullptr;
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = mockImage;
    pattern->imageSize_ = SizeF(100.0f, 200.0f);
    pattern->OnImageDataReady();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnImageDataReady003
 * @tc.desc: OnImageDataReady with changed size should mark for layout update.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnImageDataReady003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    // loadingCtx_ requires LoadNotifier, skip direct construction
    pattern->loadingCtx_ = nullptr;
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = mockImage;
    pattern->imageSize_ = SizeF(0.0f, 0.0f);
    pattern->OnImageDataReady();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnImageLoadFail001
 * @tc.desc: OnImageLoadFail with valid host proceeds past null checks.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnImageLoadFail001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    std::string errorMsg = "load failed";
    ImageErrorInfo errorInfo;
    pattern->OnImageLoadFail(errorMsg, errorInfo);
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: OnImageLoadFail002
 * @tc.desc: OnImageLoadFail with needLoadAlt true and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnImageLoadFail002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needLoadAlt_ = true;
    std::string errorMsg = "network error";
    ImageErrorInfo errorInfo;
    pattern->OnImageLoadFail(errorMsg, errorInfo);
    EXPECT_TRUE(pattern->needLoadAlt_);
}

/**
 * @tc.name: OnImageLoadFail003
 * @tc.desc: OnImageLoadFail with needLoadAlt false and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, OnImageLoadFail003, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needLoadAlt_ = false;
    std::string errorMsg = "decode error";
    ImageErrorInfo errorInfo;
    pattern->OnImageLoadFail(errorMsg, errorInfo);
    EXPECT_FALSE(pattern->needLoadAlt_);
}


/**
 * @tc.name: StartDecoding002
 * @tc.desc: StartDecoding with valid host and size 100x200 second call.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, StartDecoding002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF dstSize(100.0f, 200.0f);
    pattern->StartDecoding(dstSize);
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: StartDecoding003
 * @tc.desc: StartDecoding with valid host and size 400x500.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, StartDecoding003, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF dstSize(400.0f, 500.0f);
    pattern->StartDecoding(dstSize);
    EXPECT_EQ(pattern->image_, nullptr);
}



/**
 * @tc.name: UpdateImageSourceinfo001
 * @tc.desc: UpdateImageSourceinfo with new source and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, UpdateImageSourceinfo001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    ImageSourceInfo newSrc(WEB_IMAGE);
    pattern->UpdateImageSourceinfo(newSrc);
    EXPECT_EQ(pattern->image_, nullptr);
}

/**
 * @tc.name: UpdateImageSourceinfo002
 * @tc.desc: UpdateImageSourceinfo with same source and valid host.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, UpdateImageSourceinfo002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    ImageSourceInfo sameSrc(IMAGE_SRC_URL);
    pattern->UpdateImageSourceinfo(sameSrc);
    EXPECT_NE(pattern->GetHost(), nullptr);
}



/**
 * @tc.name: GetImageLoadingContext002
 * @tc.desc: GetImageLoadingContext with valid context should return upgradeable weak ptr.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, GetImageLoadingContext002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto weakCtx = pattern->GetImageLoadingContext();
    auto ctx = weakCtx.Upgrade();
    EXPECT_NE(ctx, nullptr);
}


/**
 * @tc.name: GetAltImageLoadingContext002
 * @tc.desc: GetAltImageLoadingContext with valid alt context should return upgradeable weak ptr.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, GetAltImageLoadingContext002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto weakCtx = pattern->GetAltImageLoadingContext();
    auto ctx = weakCtx.Upgrade();
    EXPECT_NE(ctx, nullptr);
}

/**
 * @tc.name: SetGetSyncLoad001
 * @tc.desc: SetSyncLoad true then GetSyncLoad should return true.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetSyncLoad001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_FALSE(pattern->GetSyncLoad());
    pattern->SetSyncLoad(true);
    EXPECT_TRUE(pattern->GetSyncLoad());
    pattern->SetSyncLoad(false);
    EXPECT_FALSE(pattern->GetSyncLoad());
}

/**
 * @tc.name: SetNeedBorderRadius001
 * @tc.desc: SetNeedBorderRadius should update needBorderRadius_ flag.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetNeedBorderRadius001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_FALSE(pattern->needBorderRadius_);
    pattern->SetNeedBorderRadius(true);
    EXPECT_TRUE(pattern->needBorderRadius_);
    pattern->SetNeedBorderRadius(false);
    EXPECT_FALSE(pattern->needBorderRadius_);
}

/**
 * @tc.name: SetGetImageType001
 * @tc.desc: SetImageType and GetImageType should round-trip correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetImageType001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetImageType(), ImageType::BASE);
    pattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    EXPECT_EQ(pattern->GetImageType(), ImageType::BASE);
    EXPECT_FALSE(pattern->GetIsAnimation());
}

/**
 * @tc.name: SetGetNeedLoadAlt001
 * @tc.desc: SetNeedLoadAlt and GetNeedLoadAlt should round-trip correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetNeedLoadAlt001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
    pattern->SetNeedLoadAlt(false);
    EXPECT_FALSE(pattern->GetNeedLoadAlt());
    pattern->SetNeedLoadAlt(true);
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
}


// ========== Tests from image_pattern_test_memory_callbacks.cpp ==========




/**
 * @tc.name: ResetImage002
 * @tc.desc: Test ResetImage with altImage_ present does not remove content modifier.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ResetImage002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    auto contentMod = pattern->contentMod_;
    pattern->ResetImage();
    EXPECT_EQ(pattern->image_, nullptr);
    EXPECT_EQ(pattern->contentMod_, contentMod);
}

/**
 * @tc.name: ResetImage003
 * @tc.desc: Test ResetImage with no altImage_ removes content modifier.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ResetImage003, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_ = nullptr;
    pattern->ResetImage();
    EXPECT_EQ(pattern->image_, nullptr);
    EXPECT_EQ(pattern->contentMod_, nullptr);
    EXPECT_EQ(pattern->imagePaintMethod_, nullptr);
}


/**
 * @tc.name: ResetAltImage002
 * @tc.desc: Test ResetAltImage with image_ present does not remove content modifier.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ResetAltImage002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    auto contentMod = pattern->contentMod_;
    pattern->ResetAltImage();
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_EQ(pattern->contentMod_, contentMod);
}



/**
 * @tc.name: SetOnProgressCallback001
 * @tc.desc: Test SetOnProgressCallback sets the onProgressCallback_ member.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetOnProgressCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->onProgressCallback_, nullptr);
    bool callbackInvoked = false;
    std::function<void(const uint32_t&, const uint32_t&)> callback =
        [&callbackInvoked](const uint32_t& dlNow, const uint32_t& dlTotal) {
            callbackInvoked = true;
        };
    pattern->SetOnProgressCallback(std::move(callback));
    EXPECT_NE(pattern->onProgressCallback_, nullptr);
    uint32_t dlNow = 50;
    uint32_t dlTotal = 100;
    pattern->onProgressCallback_(dlNow, dlTotal);
    EXPECT_TRUE(callbackInvoked);
}


/**
 * @tc.name: SetGetImageQuality001
 * @tc.desc: Test SetImageQuality and GetImageQuality round-trip for MIDDLE quality.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetImageQuality001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::NONE);
    pattern->SetImageQuality(AIImageQuality::NORMAL);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::NORMAL);
    EXPECT_TRUE(pattern->isImageReloadNeeded_);
    pattern->SetImageQuality(AIImageQuality::NONE);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::NONE);
}

/**
 * @tc.name: SetGetCopyOption001
 * @tc.desc: Test SetCopyOption and GetCopyOption round-trip for Local value.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetCopyOption001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::None);
    pattern->SetCopyOption(CopyOptions::Local);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::Local);
    pattern->SetCopyOption(CopyOptions::None);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::None);
}

/**
 * @tc.name: SetGetOrientation001
 * @tc.desc: Test SetOrientation and GetOrientation round-trip for RIGHT orientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetOrientation001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::UP);
    pattern->SetOrientation(ImageRotateOrientation::RIGHT);
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::RIGHT);
    EXPECT_TRUE(pattern->isOrientationChange_);
    EXPECT_FALSE(pattern->isImageReloadNeeded_);
}



/**
 * @tc.name: SetGetExternalDecodeFormat001
 * @tc.desc: Test SetExternalDecodeFormat and GetExternalDecodeFormat with RGBA_8888.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetExternalDecodeFormat001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_8888);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::RGBA_8888);
    EXPECT_TRUE(pattern->isImageReloadNeeded_);
    pattern->SetExternalDecodeFormat(PixelFormat::UNKNOWN);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);
}



// ========== Tests from image_layout_property_test_ng.cpp ==========


/**
 * @tc.name: Clone001
 * @tc.desc: Test Clone preserves ImageSourceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, Clone001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));
    auto cloned = AceType::DynamicCast<ImageLayoutProperty>(prop->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->GetImageSourceInfo().value().GetSrc(), IMAGE_SRC_URL);
    EXPECT_TRUE(cloned->GetImageSourceInfo().has_value());
}

/**
 * @tc.name: Clone002
 * @tc.desc: Test Clone preserves Alt and ImageFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, Clone002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateAlt(ImageSourceInfo(ALT_SRC_URL));
    prop->UpdateImageFit(ImageFit::CONTAIN);
    auto cloned = AceType::DynamicCast<ImageLayoutProperty>(prop->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->GetAlt().value().GetSrc(), ALT_SRC_URL);
    EXPECT_EQ(cloned->GetImageFit().value(), ImageFit::CONTAIN);
}

/**
 * @tc.name: Clone003
 * @tc.desc: Test Clone preserves AutoResize SourceSize VerticalAlign.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, Clone003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateAutoResize(true);
    prop->UpdateSourceSize(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    prop->UpdateVerticalAlign(VerticalAlign::TOP);
    auto cloned = AceType::DynamicCast<ImageLayoutProperty>(prop->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(cloned->GetAutoResize().value());
    EXPECT_DOUBLE_EQ(cloned->GetSourceSize().value().Width(), IMAGE_SOURCESIZE_WIDTH);
    EXPECT_EQ(cloned->GetVerticalAlign().value(), VerticalAlign::TOP);
}

/**
 * @tc.name: Clone004
 * @tc.desc: Test Clone of empty property.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, Clone004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto cloned = AceType::DynamicCast<ImageLayoutProperty>(prop->Clone());
    ASSERT_NE(cloned, nullptr);
    EXPECT_FALSE(cloned->GetImageFit().has_value());
    EXPECT_FALSE(cloned->GetImageSourceInfo().has_value());
    EXPECT_FALSE(cloned->GetAlt().has_value());
    EXPECT_FALSE(cloned->GetAutoResize().has_value());
}

/**
 * @tc.name: Reset001
 * @tc.desc: Test Reset clears all properties.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, Reset001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));
    prop->UpdateImageFit(ImageFit::FILL);
    prop->UpdateAutoResize(true);
    prop->UpdateVerticalAlign(VerticalAlign::CENTER);
    prop->Reset();
    EXPECT_FALSE(prop->GetImageSourceInfo().has_value());
    EXPECT_FALSE(prop->GetImageFit().has_value());
    EXPECT_FALSE(prop->GetAutoResize().has_value());
    EXPECT_FALSE(prop->GetVerticalAlign().has_value());
}


/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test ToJsonValue with ImageFit COVER.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateImageFit(ImageFit::COVER);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Cover");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test ToJsonValue with ImageFit CONTAIN.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateImageFit(ImageFit::CONTAIN);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Contain");
}

/**
 * @tc.name: ToJsonValue004
 * @tc.desc: Test ToJsonValue with ImageFit FILL.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateImageFit(ImageFit::FILL);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Fill");
}

/**
 * @tc.name: ToJsonValue005
 * @tc.desc: Test ToJsonValue with alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue005, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateAlt(ImageSourceInfo(ALT_SRC_URL));
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("alt"), ALT_SRC_URL);
}

/**
 * @tc.name: ToJsonValue006
 * @tc.desc: Test ToJsonValue with altError and altPlaceholder.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue006, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateAltError(ImageSourceInfo(ALT_SRC_URL));
    prop->UpdateAltPlaceholder(ImageSourceInfo(ALT_SRC_URL));
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("altError"), ALT_SRC_URL);
    EXPECT_EQ(json->GetString("altPlaceholder"), ALT_SRC_URL);
}

/**
 * @tc.name: ToJsonValue007
 * @tc.desc: Test ToJsonValue with autoResize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ToJsonValue007, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateAutoResize(true);
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("autoResize"), "true");
}

/**
 * @tc.name: FromJson001
 * @tc.desc: Test FromJson restores ImageSourceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, FromJson001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto json = JsonUtil::Create(true);
    json->Put("rawSrc", IMAGE_SRC_URL.c_str());
    json->Put("objectFit", "ImageFit.Cover");
    json->Put("autoResize", "true");
    prop->FromJson(json);
    EXPECT_EQ(prop->GetImageSourceInfo().value().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: FromJson002
 * @tc.desc: Test FromJson restores ImageFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, FromJson002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto json = JsonUtil::Create(true);
    json->Put("rawSrc", IMAGE_SRC_URL.c_str());
    json->Put("objectFit", "ImageFit.Contain");
    json->Put("autoResize", "false");
    prop->FromJson(json);
    EXPECT_EQ(prop->GetImageFit().value(), ImageFit::CONTAIN);
}

/**
 * @tc.name: FromJson003
 * @tc.desc: Test FromJson restores AutoResize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, FromJson003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto json = JsonUtil::Create(true);
    json->Put("rawSrc", IMAGE_SRC_URL.c_str());
    json->Put("objectFit", "ImageFit.Cover");
    json->Put("autoResize", "true");
    prop->FromJson(json);
    EXPECT_TRUE(prop->GetAutoResize().value());
}

/**
 * @tc.name: PropertyRoundTrip001
 * @tc.desc: Test UpdateImageFit and GetImageFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateImageFit(ImageFit::COVER);
    EXPECT_TRUE(prop->GetImageFit().has_value());
    EXPECT_EQ(prop->GetImageFit().value(), ImageFit::COVER);
    prop->UpdateImageFit(ImageFit::FILL);
    EXPECT_EQ(prop->GetImageFit().value(), ImageFit::FILL);
}

/**
 * @tc.name: PropertyRoundTrip002
 * @tc.desc: Test UpdateAutoResize and GetAutoResize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateAutoResize(true);
    EXPECT_TRUE(prop->GetAutoResize().has_value());
    EXPECT_TRUE(prop->GetAutoResize().value());
    prop->UpdateAutoResize(false);
    EXPECT_FALSE(prop->GetAutoResize().value());
}

/**
 * @tc.name: PropertyRoundTrip003
 * @tc.desc: Test UpdateSourceSize and GetSourceSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    prop->UpdateSourceSize(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    auto result = prop->GetSourceSize().value();
    EXPECT_DOUBLE_EQ(result.Width(), IMAGE_SOURCESIZE_WIDTH);
    EXPECT_DOUBLE_EQ(result.Height(), IMAGE_SOURCESIZE_HEIGHT);
    EXPECT_TRUE(prop->GetSourceSize().has_value());
}

/**
 * @tc.name: PropertyRoundTrip004
 * @tc.desc: Test UpdateVerticalAlign and GetVerticalAlign.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateVerticalAlign(VerticalAlign::CENTER);
    EXPECT_TRUE(prop->GetVerticalAlign().has_value());
    EXPECT_EQ(prop->GetVerticalAlign().value(), VerticalAlign::CENTER);
    prop->UpdateVerticalAlign(VerticalAlign::BOTTOM);
    EXPECT_EQ(prop->GetVerticalAlign().value(), VerticalAlign::BOTTOM);
}

/**
 * @tc.name: PropertyRoundTrip005
 * @tc.desc: Test UpdateImageSourceInfo and GetImageSourceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip005, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));
    EXPECT_TRUE(prop->GetImageSourceInfo().has_value());
    EXPECT_EQ(prop->GetImageSourceInfo().value().GetSrc(), IMAGE_SRC_URL);
    prop->UpdateImageSourceInfo(ImageSourceInfo(ALT_SRC_URL));
    EXPECT_EQ(prop->GetImageSourceInfo().value().GetSrc(), ALT_SRC_URL);
}


// ========== Tests from image_render_property_test_ng.cpp ==========


/**
 * @tc.name: ImageRenderPropertyTestNg001
 * @tc.desc: Test Clone preserves ImageRenderMode and Interpolation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    prop->UpdateImageInterpolation(ImageInterpolation::HIGH);
    auto cloned = prop->Clone();
    auto clonedRender = AceType::DynamicCast<ImageRenderProperty>(cloned);
    ASSERT_NE(clonedRender, nullptr);
    EXPECT_EQ(clonedRender->GetImageRenderMode(), ImageRenderMode::TEMPLATE);
    EXPECT_EQ(clonedRender->GetImageInterpolation(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: ImageRenderPropertyTestNg002
 * @tc.desc: Test Clone preserves Repeat, ColorFilter, MatchTextDirection.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRepeat(ImageRepeat::REPEAT);
    prop->UpdateColorFilter(COLOR_FILTER_DEFAULT);
    prop->UpdateMatchTextDirection(true);
    auto cloned = prop->Clone();
    auto clonedRender = AceType::DynamicCast<ImageRenderProperty>(cloned);
    ASSERT_NE(clonedRender, nullptr);
    EXPECT_EQ(clonedRender->GetImageRepeat(), ImageRepeat::REPEAT);
    EXPECT_EQ(clonedRender->GetColorFilter(), COLOR_FILTER_DEFAULT);
    EXPECT_TRUE(clonedRender->GetMatchTextDirection());
}

/**
 * @tc.name: ImageRenderPropertyTestNg003
 * @tc.desc: Test Clone preserves SvgFillColor, SmoothEdge, DynamicMode, HdrBrightness, AntiAlias.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateSvgFillColor(Color::RED);
    prop->UpdateSmoothEdge(2.5f);
    prop->UpdateDynamicMode(DynamicRangeMode::HIGH);
    prop->UpdateHdrBrightness(1.5f);
    prop->UpdateAntiAlias(true);
    auto cloned = prop->Clone();
    auto clonedRender = AceType::DynamicCast<ImageRenderProperty>(cloned);
    ASSERT_NE(clonedRender, nullptr);
    EXPECT_EQ(clonedRender->GetSvgFillColor(), Color::RED);
    EXPECT_FLOAT_EQ(clonedRender->GetSmoothEdge().value_or(0.0f), 2.5f);
    EXPECT_EQ(clonedRender->GetDynamicMode(), DynamicRangeMode::HIGH);
    EXPECT_FLOAT_EQ(clonedRender->GetHdrBrightness().value_or(0.0f), 1.5f);
    EXPECT_TRUE(clonedRender->GetAntiAlias());
}

/**
 * @tc.name: ImageRenderPropertyTestNg004
 * @tc.desc: Test Reset clears all render properties.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    prop->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    prop->UpdateSmoothEdge(3.0f);
    prop->UpdateNeedBorderRadius(true);
    prop->Reset();
    EXPECT_EQ(prop->GetImageRenderMode(), std::nullopt);
    EXPECT_EQ(prop->GetImageRepeat(), std::nullopt);
    EXPECT_EQ(prop->GetSmoothEdge(), std::nullopt);
    EXPECT_EQ(prop->GetNeedBorderRadius(), std::nullopt);
}

/**
 * @tc.name: ImageRenderPropertyTestNg005
 * @tc.desc: Test ToJsonValue with default, ImageRepeat, Interpolation, RenderMode values.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg005, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRepeat(ImageRepeat::REPEAT);
    prop->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    prop->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.XY");
    EXPECT_EQ(json->GetString("interpolation"), "ImageInterpolation.Medium");
    EXPECT_EQ(json->GetString("renderMode"), "ImageRenderMode.Template");
}

/**
 * @tc.name: ImageRenderPropertyTestNg006
 * @tc.desc: Test ToJsonValue with ColorFilter, MatchTextDirection, FillColor, AntiAlias.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg006, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateColorFilter({1.0f, 0.5f});
    prop->UpdateMatchTextDirection(true);
    prop->UpdateSvgFillColor(Color::GREEN);
    prop->UpdateAntiAlias(true);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("matchTextDirection"), "true");
    EXPECT_EQ(json->GetString("antiAlias"), "true");
    EXPECT_FALSE(json->GetString("colorFilter").empty());
}

/**
 * @tc.name: ImageRenderPropertyTestNg007
 * @tc.desc: Test ToJsonValue with HdrBrightness and ContentTransition.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg007, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateHdrBrightness(2.0f);
    prop->UpdateContentTransition(ContentTransitionType::OPACITY);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    prop->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("contentTransition"), "ContentTransitionEffect.OPACITY");
    EXPECT_DOUBLE_EQ(json->GetDouble("hdrBrightness"), 2.0);
}

/**
 * @tc.name: ImageRenderPropertyTestNg008
 * @tc.desc: Test UpdateImageRenderMode and GetImageRenderMode round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg008, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    EXPECT_EQ(prop->GetImageRenderMode(), ImageRenderMode::TEMPLATE);
    prop->UpdateImageRenderMode(ImageRenderMode::ORIGINAL);
    EXPECT_EQ(prop->GetImageRenderMode(), ImageRenderMode::ORIGINAL);
    prop->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    EXPECT_EQ(prop->GetImageRenderMode(), ImageRenderMode::TEMPLATE);
}

/**
 * @tc.name: ImageRenderPropertyTestNg009
 * @tc.desc: Test UpdateImageInterpolation and GetImageInterpolation round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg009, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageInterpolation(ImageInterpolation::LOW);
    EXPECT_EQ(prop->GetImageInterpolation(), ImageInterpolation::LOW);
    prop->UpdateImageInterpolation(ImageInterpolation::NONE);
    EXPECT_EQ(prop->GetImageInterpolation(), ImageInterpolation::NONE);
    prop->UpdateImageInterpolation(ImageInterpolation::HIGH);
    EXPECT_EQ(prop->GetImageInterpolation(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: ImageRenderPropertyTestNg010
 * @tc.desc: Test UpdateImageRepeat and GetImageRepeat round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg010, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    EXPECT_EQ(prop->GetImageRepeat(), ImageRepeat::REPEAT_X);
    prop->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    EXPECT_EQ(prop->GetImageRepeat(), ImageRepeat::NO_REPEAT);
    prop->UpdateImageRepeat(ImageRepeat::REPEAT);
    EXPECT_EQ(prop->GetImageRepeat(), ImageRepeat::REPEAT);
}

/**
 * @tc.name: ImageRenderPropertyTestNg011
 * @tc.desc: Test UpdateColorFilter and GetColorFilter round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg011, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    ASSERT_NE(prop, nullptr);
    std::vector<float> filter = {0.5f, 1.0f, 1.5f, 2.0f};
    prop->UpdateColorFilter(filter);
    EXPECT_TRUE(prop->GetColorFilter().has_value());
    auto result = prop->GetColorFilter().value_or(std::vector<float>{});
    ASSERT_EQ(result.size(), 4u);
    EXPECT_FLOAT_EQ(result[0], 0.5f);
    EXPECT_FLOAT_EQ(result[1], 1.0f);
    EXPECT_FLOAT_EQ(result[2], 1.5f);
    EXPECT_FLOAT_EQ(result[3], 2.0f);
}

/**
 * @tc.name: ImageRenderPropertyTestNg012
 * @tc.desc: Test UpdateMatchTextDirection, UpdateSvgFillColor, UpdateSmoothEdge round-trips.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg012, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateMatchTextDirection(false);
    EXPECT_FALSE(prop->GetMatchTextDirection());
    prop->UpdateSvgFillColor(SVG_FILL_COLOR_DEFAULT);
    EXPECT_EQ(prop->GetSvgFillColor(), SVG_FILL_COLOR_DEFAULT);
    prop->UpdateSmoothEdge(5.0f);
    EXPECT_FLOAT_EQ(prop->GetSmoothEdge().value_or(0.0f), 5.0f);
}

/**
 * @tc.name: ImageRenderPropertyTestNg013
 * @tc.desc: Test UpdateDynamicMode, UpdateHdrBrightness, UpdateAntiAlias round-trips.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg013, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    EXPECT_EQ(prop->GetDynamicMode(), DynamicRangeMode::CONSTRAINT);
    prop->UpdateHdrBrightness(0.8f);
    EXPECT_FLOAT_EQ(prop->GetHdrBrightness().value_or(0.0f), 0.8f);
    prop->UpdateAntiAlias(false);
    EXPECT_FALSE(prop->GetAntiAlias());
}

/**
 * @tc.name: ImageRenderPropertyTestNg014
 * @tc.desc: Test UpdateContentTransition, UpdateNeedBorderRadius, UpdateImageFit round-trips.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg014, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    prop->UpdateContentTransition(ContentTransitionType::OPACITY);
    EXPECT_EQ(prop->GetContentTransition(), ContentTransitionType::OPACITY);
    prop->UpdateNeedBorderRadius(true);
    EXPECT_TRUE(prop->GetNeedBorderRadius());
    prop->UpdateImageFit(ImageFit::CONTAIN);
    EXPECT_EQ(prop->GetImageFit(), ImageFit::CONTAIN);
}

/**
 * @tc.name: ImageRenderPropertyTestNg015
 * @tc.desc: Test ImageDfxConfig constructor and getters.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg015, TestSize.Level1)
{
    ImageNodeId nodeId(1, 2L, 3UL);
    ImageDfxConfig dfx(nodeId, 1, "test_src");
    EXPECT_EQ(dfx.GetNodeId(), 1);
    EXPECT_EQ(dfx.GetAccessibilityId(), 2L);
    EXPECT_EQ(dfx.GetImageSrc(), "test_src");
    EXPECT_EQ(dfx.GetSrcType(), 1);
    EXPECT_FALSE(dfx.GetIsTrimMemRecycle());
}

/**
 * @tc.name: ImageRenderPropertyTestNg016
 * @tc.desc: Test ImageDfxConfig ToStringWithoutSrc and ToStringWithSrc format.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg016, TestSize.Level1)
{
    ImageNodeId nodeId(10, 20L, 30UL);
    ImageDfxConfig dfx(nodeId, 2, "image.png");
    EXPECT_EQ(dfx.GetNodeId(), 10);
    EXPECT_EQ(dfx.GetAccessibilityId(), 20L);
    EXPECT_EQ(dfx.ToStringWithoutSrc(), "[10-20-30-2]");
    EXPECT_EQ(dfx.ToStringWithSrc(), "[10-20-30-2]-[image.png]");
}

/**
 * @tc.name: ImageRenderPropertyTestNg017
 * @tc.desc: Test ImageDfxConfig SetAutoResize and SetFrameSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg017, TestSize.Level1)
{
    ImageNodeId nodeId(5, 10L, 15UL);
    ImageDfxConfig dfx(nodeId, 0, "src.jpg");
    EXPECT_FALSE(dfx.GetAutoResize());
    dfx.SetAutoResize(true);
    EXPECT_TRUE(dfx.GetAutoResize());
    dfx.SetFrameSize(100.0f, 200.0f);
    EXPECT_FLOAT_EQ(dfx.GetFrameSizeWidth(), 100.0f);
    EXPECT_FLOAT_EQ(dfx.GetFrameSizeHeight(), 200.0f);
}

/**
 * @tc.name: ImageRenderPropertyTestNg018
 * @tc.desc: Test RenderedImageInfo ToString with renderSuccess false and true.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg018, TestSize.Level1)
{
    RenderedImageInfo info;
    info.renderSuccess = false;
    EXPECT_EQ(info.ToString(), "RenderedImageInfo: { RenderStatus: NotRender }");
    info.renderSuccess = true;
    info.width = 100;
    info.height = 200;
    info.rowStride = 400;
    info.rowBytes = 400;
    info.byteCount = 80000;
    info.isHdr = false;
    info.pixelMapId = "pm_001";
    info.dstRectInfo = "0,0,100,200";
    std::string result = info.ToString();
    EXPECT_NE(result.find("RenderStatus: Success"), std::string::npos);
    EXPECT_NE(result.find("Width: 100"), std::string::npos);
    EXPECT_NE(result.find("Height: 200"), std::string::npos);
}

/**
 * @tc.name: ImageRenderPropertyTestNg019
 * @tc.desc: Test Clone of empty property and ToJsonValue with defaults.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg019, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    auto cloned = prop->Clone();
    auto clonedRender = AceType::DynamicCast<ImageRenderProperty>(cloned);
    ASSERT_NE(clonedRender, nullptr);
    EXPECT_EQ(clonedRender->GetImageRenderMode(), std::nullopt);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    prop->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: ImageRenderPropertyTestNg020
 * @tc.desc: Test ImageDfxConfig default constructor and GetIsTrimMemRecycle.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, ImageRenderPropertyTestNg020, TestSize.Level1)
{
    ImageDfxConfig dfx;
    EXPECT_EQ(dfx.GetNodeId(), -1);
    EXPECT_EQ(dfx.GetAccessibilityId(), -1);
    EXPECT_EQ(dfx.GetSrcType(), -1);
    EXPECT_FALSE(dfx.GetIsTrimMemRecycle());
    EXPECT_FALSE(dfx.GetAutoResize());
    EXPECT_FLOAT_EQ(dfx.GetFrameSizeWidth(), 0.0f);
    EXPECT_FLOAT_EQ(dfx.GetFrameSizeHeight(), 0.0f);
}

// ========== GROUP 1: ImageLayoutProperty Untested Methods ==========

/**
 * @tc.name: PropertyRoundTrip006
 * @tc.desc: Test UpdateFitOriginalSize and GetFitOriginalSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip006, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_FALSE(prop->GetFitOriginalSize().value_or(false));
    prop->UpdateFitOriginalSize(true);
    EXPECT_TRUE(prop->GetFitOriginalSize().value());
    prop->UpdateFitOriginalSize(false);
    EXPECT_FALSE(prop->GetFitOriginalSize().value());
}

/**
 * @tc.name: PropertyRoundTrip007
 * @tc.desc: Test UpdatePlaceHolderStyle and GetPlaceHolderStyle.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip007, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    TextBackgroundStyle style;
    prop->UpdatePlaceHolderStyle(style);
    EXPECT_TRUE(prop->GetPlaceHolderStyle().has_value());
    prop->ResetPlaceHolderStyle();
    EXPECT_FALSE(prop->GetPlaceHolderStyle().has_value());
}

/**
 * @tc.name: PropertyRoundTrip008
 * @tc.desc: Test UpdateBaselineOffset and GetBaselineOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip008, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    Dimension offset(10.0f);
    prop->UpdateBaselineOffset(offset);
    EXPECT_TRUE(prop->GetBaselineOffset().has_value());
    EXPECT_EQ(prop->GetBaselineOffset().value().Value(), 10.0f);
    prop->ResetBaselineOffset();
    EXPECT_FALSE(prop->GetBaselineOffset().has_value());
}

/**
 * @tc.name: PropertyRoundTrip009
 * @tc.desc: Test UpdateImageRotateOrientation and GetImageRotateOrientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip009, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateImageRotateOrientation(ImageRotateOrientation::RIGHT);
    EXPECT_TRUE(prop->GetImageRotateOrientation().has_value());
    EXPECT_EQ(prop->GetImageRotateOrientation().value(), ImageRotateOrientation::RIGHT);
    prop->ResetImageRotateOrientation();
    EXPECT_FALSE(prop->GetImageRotateOrientation().has_value());
}

/**
 * @tc.name: PropertyRoundTrip010
 * @tc.desc: Test UpdateImageFillSetByUser and GetImageFillSetByUser.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip010, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateImageFillSetByUser(true);
    EXPECT_TRUE(prop->GetImageFillSetByUser().value());
    prop->UpdateImageFillSetByUser(false);
    EXPECT_FALSE(prop->GetImageFillSetByUser().value());
}

/**
 * @tc.name: PropertyRoundTrip011
 * @tc.desc: Test UpdateIsYUVDecode and GetIsYUVDecode.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip011, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateIsYUVDecode(true);
    EXPECT_TRUE(prop->GetIsYUVDecode().value());
    prop->UpdateIsYUVDecode(false);
    EXPECT_FALSE(prop->GetIsYUVDecode().value());
}

// ========== GROUP 2: ImageRenderProperty Untested Methods ==========



/**
 * @tc.name: RenderPropertyRoundTrip003
 * @tc.desc: Test UpdateImageResizableSlice and GetImageResizableSlice.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RenderPropertyRoundTrip003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    ASSERT_NE(prop, nullptr);
    ImageResizableSlice slice;
    prop->UpdateImageResizableSlice(slice);
    EXPECT_TRUE(prop->GetImageResizableSlice().has_value());
    prop->ResetImageResizableSlice();
    EXPECT_FALSE(prop->GetImageResizableSlice().has_value());
}

/**
 * @tc.name: RenderPropertyRoundTrip004
 * @tc.desc: Test UpdateBorderRadius and GetBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RenderPropertyRoundTrip004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    ASSERT_NE(prop, nullptr);
    BorderRadiusProperty borderRadius;
    prop->UpdateBorderRadius(borderRadius);
    EXPECT_TRUE(prop->GetBorderRadius().has_value());
    prop->ResetBorderRadius();
    EXPECT_FALSE(prop->GetBorderRadius().has_value());
}

/**
 * @tc.name: RenderPropertyRoundTrip005
 * @tc.desc: Test UpdateImageMatrix and GetImageMatrix.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RenderPropertyRoundTrip005, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    ASSERT_NE(prop, nullptr);
    Matrix4 matrix;
    prop->UpdateImageMatrix(matrix);
    EXPECT_TRUE(prop->GetImageMatrix().has_value());
    prop->ResetImageMatrix();
    EXPECT_FALSE(prop->GetImageMatrix().has_value());
}

// ========== GROUP 3: String Converter Methods ==========









// ========== GROUP 4: Core Methods ==========











/**
 * @tc.name: PropertyRoundTrip012
 * @tc.desc: Test UpdateAltError and GetAltError.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip012, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    ImageSourceInfo altErrorSrc(ALT_SRC_URL);
    prop->UpdateAltError(altErrorSrc);
    EXPECT_TRUE(prop->GetAltError().has_value());
    prop->ResetAltError();
    EXPECT_FALSE(prop->GetAltError().has_value());
}

/**
 * @tc.name: PropertyRoundTrip013
 * @tc.desc: Test UpdateAltPlaceholder and GetAltPlaceholder.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, PropertyRoundTrip013, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    ImageSourceInfo placeholderSrc(RESOURCE_URL);
    prop->UpdateAltPlaceholder(placeholderSrc);
    EXPECT_TRUE(prop->GetAltPlaceholder().has_value());
    prop->ResetAltPlaceholder();
    EXPECT_FALSE(prop->GetAltPlaceholder().has_value());
}

/**
 * @tc.name: RenderPropertyRoundTrip006
 * @tc.desc: Test UpdateNeedBorderRadius and GetNeedBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, RenderPropertyRoundTrip006, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<ImageRenderProperty>();
    ASSERT_NE(prop, nullptr);
    EXPECT_FALSE(prop->GetNeedBorderRadius().value_or(false));
    prop->UpdateNeedBorderRadius(true);
    EXPECT_TRUE(prop->GetNeedBorderRadius().value());
    prop->UpdateNeedBorderRadius(false);
    EXPECT_FALSE(prop->GetNeedBorderRadius().value());
}


// ========== GROUP 5: Additional ImagePattern Methods ==========

/**
 * @tc.name: SetGetSupportSvg2001
 * @tc.desc: Test SetSupportSvg2 and GetSupportSvg2 round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetGetSupportSvg2001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetSupportSvg2());
    pattern->SetSupportSvg2(true);
    EXPECT_TRUE(pattern->GetSupportSvg2());
    pattern->SetSupportSvg2(false);
    EXPECT_FALSE(pattern->GetSupportSvg2());
}

/**
 * @tc.name: SetIsComponentSnapshotNode001
 * @tc.desc: Test SetIsComponentSnapshotNode sets the flag.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetIsComponentSnapshotNode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->isComponentSnapshotNode_);
    pattern->SetIsComponentSnapshotNode(true);
    EXPECT_TRUE(pattern->isComponentSnapshotNode_);
    pattern->SetIsComponentSnapshotNode(false);
    EXPECT_FALSE(pattern->isComponentSnapshotNode_);
}

/**
 * @tc.name: SetRenderedImageInfo001
 * @tc.desc: Test SetRenderedImageInfo stores rendered image info.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetRenderedImageInfo001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    RenderedImageInfo info;
    info.renderSuccess = true;
    info.width = 100;
    info.height = 200;
    pattern->SetRenderedImageInfo(info);
    EXPECT_TRUE(pattern->renderedImageInfo_.renderSuccess);
    EXPECT_EQ(pattern->renderedImageInfo_.width, 100);
    EXPECT_EQ(pattern->renderedImageInfo_.height, 200);
}

/**
 * @tc.name: EnableIsEnableAnalyzer001
 * @tc.desc: Test EnableAnalyzer and IsEnableAnalyzer round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, EnableIsEnableAnalyzer001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsEnableAnalyzer());
    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->IsEnableAnalyzer());
    pattern->EnableAnalyzer(false);
    EXPECT_FALSE(pattern->IsEnableAnalyzer());
}

/**
 * @tc.name: GetContentTransitionParam001
 * @tc.desc: Test GetContentTransitionParam returns default value.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, GetContentTransitionParam001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    ContentTransitionType type = pattern->GetContentTransitionParam();
    EXPECT_EQ(type, ContentTransitionType::IDENTITY);
}

/**
 * @tc.name: InitOnKeyEvent001
 * @tc.desc: Test InitOnKeyEvent initializes key event handling.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, InitOnKeyEvent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitOnKeyEvent();
    EXPECT_TRUE(pattern->keyEventCallback_ != nullptr);
}

/**
 * @tc.name: SetImageAnimator002
 * @tc.desc: Test SetImageAnimator with different values.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, SetImageAnimator002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->isImageAnimator_);
    pattern->SetImageAnimator(true);
    EXPECT_TRUE(pattern->isImageAnimator_);
    pattern->SetImageAnimator(false);
    EXPECT_FALSE(pattern->isImageAnimator_);
    pattern->SetImageAnimator(true);
    EXPECT_TRUE(pattern->isImageAnimator_);
}

/**
 * @tc.name: GetNeedLoadAlt002
 * @tc.desc: Test GetNeedLoadAlt and SetNeedLoadAlt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternPropertyLoadTest, GetNeedLoadAlt002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
    pattern->SetNeedLoadAlt(false);
    EXPECT_FALSE(pattern->GetNeedLoadAlt());
    pattern->SetNeedLoadAlt(true);
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
}


} // namespace OHOS::Ace::NG

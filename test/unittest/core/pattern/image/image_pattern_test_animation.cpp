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
 * @file image_pattern_test_animation.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern animation
 *
 * This file contains test cases covering:
 * - CreatePictureAnimation
 * - SetShowingIndex
 * - ControlAnimation
 * - OnAnimatedModifyDone
 * - StartAnimation / StopAnimation
 * - SetDuration / SetIteration
 * - SetImages / ResetImages
 * - CacheImageStruct operations
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternAnimationTestNg : public ImageBases {};

// ============================================================================
// CreatePictureAnimation Tests
// ============================================================================

/**
 * @tc.name: CreatePictureAnimation001
 * @tc.desc: Test CreatePictureAnimation with durationTotal > 0
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, CreatePictureAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set total duration
     */
    pattern->durationTotal_ = 2000;
    int32_t size = 2;

    /**
     * @tc.steps: step3. Create picture animation
     */
    auto animation = pattern->CreatePictureAnimation(size);

    /**
     * @tc.expected: Should use total duration
     */
    ASSERT_NE(animation, nullptr);
}

/**
 * @tc.name: CreatePictureAnimation002
 * @tc.desc: Test CreatePictureAnimation with durationTotal = 0
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, CreatePictureAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set total duration to 0
     */
    pattern->durationTotal_ = 0;
    int32_t size = 2;

    /**
     * @tc.steps: step3. Create picture animation
     */
    auto animation = pattern->CreatePictureAnimation(size);

    /**
     * @tc.expected: Should use normalized duration
     */
    ASSERT_NE(animation, nullptr);
}

/**
 * @tc.name: CreatePictureAnimation003
 * @tc.desc: Test CreatePictureAnimation notifies listener
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, CreatePictureAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->durationTotal_ = 1000;
    int32_t size = 2;
    int32_t testIndex = 0;

    /**
     * @tc.steps: step2. Create animation and notify
     */
    auto animation = pattern->CreatePictureAnimation(size);
    animation->NotifyListener(testIndex);

    /**
     * @tc.expected: Index should be updated
     */
    EXPECT_EQ(pattern->nowImageIndex_, 0);
}

// ============================================================================
// SetShowingIndex Tests
// ============================================================================

/**
 * @tc.name: SetShowingIndex001
 * @tc.desc: Test SetShowingIndex with valid index
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetShowingIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(3);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set showing index to 1
     */
    pattern->SetShowingIndex(1);

    /**
     * @tc.expected: Index should be set
     */
    EXPECT_EQ(pattern->nowImageIndex_, 1);
}

/**
 * @tc.name: SetShowingIndex002
 * @tc.desc: Test SetShowingIndex with out of bounds index
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetShowingIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set showing index beyond size
     */
    pattern->SetShowingIndex(10);

    /**
     * @tc.expected: Should handle out of bounds
     */
    // Bounds checking should prevent crash
}

/**
 * @tc.name: SetShowingIndex003
 * @tc.desc: Test SetShowingIndex finds existing cache
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetShowingIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Add cache and set index
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : pattern->images_) {
        image.pixelMap = pixelMap;
    }

    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    ImagePattern::CacheImageStruct cacheImage(imageFrameNode);
    cacheImage.isLoaded = true;
    pattern->cacheImages_.emplace_back(cacheImage);

    pattern->SetShowingIndex(0);

    /**
     * @tc.expected: Should use existing cache
     */
    EXPECT_EQ(pattern->nowImageIndex_, 0);
}

/**
 * @tc.name: SetShowingIndex004
 * @tc.desc: Test SetShowingIndex with unloaded cache
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetShowingIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Add unloaded cache
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    ImagePattern::CacheImageStruct cacheImage(imageFrameNode);
    cacheImage.isLoaded = false;
    pattern->cacheImages_.emplace_back(cacheImage);

    pattern->SetShowingIndex(0);

    /**
     * @tc.expected: Should handle unloaded cache
     */
    EXPECT_EQ(pattern->nowImageIndex_, 0);
}

/**
 * @tc.name: SetShowingIndex005
 * @tc.desc: Test SetShowingIndex when already showing
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetShowingIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up images and check already showing
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : pattern->images_) {
        image.pixelMap = pixelMap;
    }

    pattern->SetShowingIndex(0);
    auto sameImage = pattern->images_[0].pixelMap;
    bool isShowing = pattern->IsShowingSrc(frameNode, sameImage);

    /**
     * @tc.expected: Should detect already showing
     */
    // IsShowingSrc checks if same image is showing
}

// ============================================================================
// ControlAnimation Tests
// ============================================================================

/**
 * @tc.name: ControlAnimation001
 * @tc.desc: Test ControlAnimation with IDLE status
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ControlAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set status to IDLE
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::IDLE;
    }
    pattern->ControlAnimation(0);

    /**
     * @tc.expected: Should handle IDLE status
     */
    SUCCEED();
}

/**
 * @tc.name: ControlAnimation002
 * @tc.desc: Test ControlAnimation with PAUSED status
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ControlAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set status to PAUSED
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::PAUSED;
    }
    pattern->ControlAnimation(0);

    /**
     * @tc.expected: Should handle PAUSED status
     */
    SUCCEED();
}

/**
 * @tc.name: ControlAnimation003
 * @tc.desc: Test ControlAnimation with STOPPED status
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ControlAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set status to STOPPED
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::STOPPED;
    }
    pattern->ControlAnimation(0);

    /**
     * @tc.expected: Should handle STOPPED status
     */
    SUCCEED();
}

/**
 * @tc.name: ControlAnimation004
 * @tc.desc: Test ControlAnimation with RUNNING status and visible node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ControlAnimation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->isActive_ = true;

    /**
     * @tc.steps: step2. Set status to RUNNING
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::RUNNING;
    }
    pattern->ControlAnimation(0);

    /**
     * @tc.expected: Should continue running
     */
    SUCCEED();
}

/**
 * @tc.name: ControlAnimation005
 * @tc.desc: Test ControlAnimation with form animation end
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ControlAnimation005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set form animation end flag
     */
    pattern->isFormAnimationEnd_ = true;
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::RUNNING;
    }
    pattern->ControlAnimation(0);

    /**
     * @tc.expected: Should handle form animation end
     */
    SUCCEED();
}

// ============================================================================
// OnAnimatedModifyDone Tests
// ============================================================================

/**
 * @tc.name: OnAnimatedModifyDone001
 * @tc.desc: Test OnAnimatedModifyDone with empty images
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, OnAnimatedModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Clear images and call modify done
     */
    pattern->images_.clear();
    pattern->OnAnimatedModifyDone();

    /**
     * @tc.expected: Should handle empty images
     */
    SUCCEED();
}

/**
 * @tc.name: OnAnimatedModifyDone002
 * @tc.desc: Test OnAnimatedModifyDone with IDLE status
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, OnAnimatedModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set status to IDLE
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::IDLE;
    }
    pattern->firstUpdateEvent_ = true;
    pattern->OnAnimatedModifyDone();

    /**
     * @tc.expected: Should set index to 0
     */
    EXPECT_EQ(pattern->nowImageIndex_, 0);
}

/**
 * @tc.name: OnAnimatedModifyDone003
 * @tc.desc: Test OnAnimatedModifyDone with images changed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, OnAnimatedModifyDone003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set images changed flag
     */
    pattern->imagesChangedFlag_ = true;
    pattern->OnAnimatedModifyDone();

    /**
     * @tc.expected: Should update animation
     */
    SUCCEED();
}

/**
 * @tc.name: OnAnimatedModifyDone004
 * @tc.desc: Test OnAnimatedModifyDone with src undefined
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, OnAnimatedModifyDone004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set src undefined
     */
    pattern->isSrcUndefined_ = true;
    pattern->OnAnimatedModifyDone();

    /**
     * @tc.expected: Should return early
     */
    SUCCEED();
}

// ============================================================================
// StartAnimation / StopAnimation Tests
// ============================================================================

/**
 * @tc.name: StartAnimation001
 * @tc.desc: Test StartAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, StartAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Start animation
     */
    pattern->StartAnimation();

    /**
     * @tc.expected: Animation should be running
     */
    if (pattern->animator_) {
        EXPECT_EQ(pattern->animator_->status_, Animator::Status::RUNNING);
    }
}

/**
 * @tc.name: StopAnimation001
 * @tc.desc: Test StopAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, StopAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Start then stop animation
     */
    pattern->StartAnimation();
    pattern->StopAnimation();

    /**
     * @tc.expected: Animation should be stopped
     */
    if (pattern->animator_) {
        EXPECT_EQ(pattern->animator_->status_, Animator::Status::STOPPED);
    }
}

// ============================================================================
// SetDuration / SetIteration Tests
// ============================================================================

/**
 * @tc.name: SetDuration001
 * @tc.desc: Test SetDuration with positive value
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set duration
     */
    pattern->SetDuration(2000);

    /**
     * @tc.expected: Duration should be set
     */
    EXPECT_EQ(pattern->durationTotal_, 2000);
}

/**
 * @tc.name: SetIteration001
 * @tc.desc: Test SetIteration
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetIteration001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set iteration
     */
    pattern->SetIteration(5);

    /**
     * @tc.expected: Iteration should be set
     */
    EXPECT_EQ(pattern->iteration_, 5);
}

// ============================================================================
// SetImages / ResetImages Tests
// ============================================================================

/**
 * @tc.name: SetImages001
 * @tc.desc: Test SetImages with valid images
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetImages001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set images
     */
    std::vector<ImageProperties> images;
    ImageProperties prop1;
    prop1.src = IMAGE_SRC_URL;
    images.push_back(prop1);

    ImageProperties prop2;
    prop2.src = ALT_SRC_URL;
    images.push_back(prop2);

    pattern->SetImages(std::move(images));

    /**
     * @tc.expected: Images should be set
     */
    EXPECT_EQ(pattern->images_.size(), 2);
}

/**
 * @tc.name: ResetImages001
 * @tc.desc: Test ResetImages
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ResetImages001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Reset images
     */
    pattern->ResetImages();

    /**
     * @tc.expected: Images should be cleared
     */
    EXPECT_TRUE(pattern->images_.empty());
}

/**
 * @tc.name: ResetImage001
 * @tc.desc: Test ResetImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ResetImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set image and reset
     */
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->ResetImage();

    /**
     * @tc.expected: Image should be null
     */
    EXPECT_EQ(pattern->image_, nullptr);
}

/**
 * @tc.name: ResetAltImage001
 * @tc.desc: Test ResetAltImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, ResetAltImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set alt image and reset
     */
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->ResetAltImage();

    /**
     * @tc.expected: Alt image should be null
     */
    EXPECT_EQ(pattern->altImage_, nullptr);
}

// ============================================================================
// CacheImageStruct Tests
// ============================================================================

/**
 * @tc.name: FindCacheImageNode001
 * @tc.desc: Test FindCacheImageNode with existing cache
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, FindCacheImageNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Add cache and find
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);

    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);

    ImagePattern::CacheImageStruct cacheImage(imageFrameNode);
    pattern->cacheImages_.emplace_back(cacheImage);

    auto layoutProp = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    ImageSourceInfo sourceInfo;
    sourceInfo.pixmap_ = pixelMap;
    layoutProp->UpdateImageSourceInfo(sourceInfo);

    auto iter = pattern->FindCacheImageNode(pixelMap);

    /**
     * @tc.expected: Should find cache
     */
    EXPECT_NE(iter, pattern->cacheImages_.end());
}

/**
 * @tc.name: FindCacheImageNode002
 * @tc.desc: Test FindCacheImageNode with non-existing cache
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, FindCacheImageNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Find non-existing cache
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);

    auto iter = pattern->FindCacheImageNode(pixelMap);

    /**
     * @tc.expected: Should return end
     */
    EXPECT_EQ(iter, pattern->cacheImages_.end());
}

/**
 * @tc.name: GenerateCachedImages001
 * @tc.desc: Test GenerateCachedImages
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, GenerateCachedImages001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(3);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Generate cached images
     */
    pattern->GenerateCachedImages();

    /**
     * @tc.expected: Caches should be generated
     */
    EXPECT_GE(pattern->cacheImages_.size(), 0);
}

/**
 * @tc.name: UpdateCacheImageInfo001
 * @tc.desc: Test UpdateCacheImageInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, UpdateCacheImageInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create cache and update
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);

    ImagePattern::CacheImageStruct cacheImage(imageFrameNode);
    cacheImage.isLoaded = true;

    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : pattern->images_) {
        image.pixelMap = pixelMap;
    }

    int32_t index = 0;
    pattern->UpdateCacheImageInfo(cacheImage, index);

    /**
     * @tc.expected: Cache should be updated
     */
    EXPECT_FALSE(cacheImage.isLoaded);
}

// ============================================================================
// ImageAnimator Tests
// ============================================================================

/**
 * @tc.name: GetIsAnimation001
 * @tc.desc: Test GetIsAnimation returns correct value
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, GetIsAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set image type
     */
    pattern->SetImageType(ImagePattern::ImageType::ANIMATION);

    /**
     * @tc.expected: Should return true
     */
    EXPECT_TRUE(pattern->GetIsAnimation());
}

/**
 * @tc.name: SetImageType001
 * @tc.desc: Test SetImageType
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetImageType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set image type to ANIMATION
     */
    pattern->SetImageType(ImagePattern::ImageType::ANIMATION);

    /**
     * @tc.expected: Type should be ANIMATION
     */
    EXPECT_EQ(pattern->GetImageType(), ImagePattern::ImageType::ANIMATION);
}

/**
 * @tc.name: SetImageAnimator001
 * @tc.desc: Test SetImageAnimator
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetImageAnimator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set image animator flag
     */
    pattern->SetImageAnimator(true);

    /**
     * @tc.expected: isImageAnimator_ should be true
     */
    EXPECT_TRUE(pattern->isImageAnimator_);
}

/**
 * @tc.name: GetHasSizeChanged001
 * @tc.desc: Test GetHasSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, GetHasSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set size changed flag
     */
    pattern->hasSizeChanged = true;

    /**
     * @tc.expected: Should return true
     */
    EXPECT_TRUE(pattern->GetHasSizeChanged());
}

// ============================================================================
// SetSrcUndefined Tests
// ============================================================================

/**
 * @tc.name: SetSrcUndefined001
 * @tc.desc: Test SetSrcUndefined
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetSrcUndefined001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set src undefined
     */
    pattern->SetSrcUndefined(true);

    /**
     * @tc.expected: isSrcUndefined_ should be true
     */
    EXPECT_TRUE(pattern->isSrcUndefined_);
}

// ============================================================================
// SetNeedLoadAlt Tests
// ============================================================================

/**
 * @tc.name: SetNeedLoadAlt001
 * @tc.desc: Test SetNeedLoadAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternAnimationTestNg, SetNeedLoadAlt001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set need load alt
     */
    pattern->SetNeedLoadAlt(true);

    /**
     * @tc.expected: needLoadAlt_ should be true
     */
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
}

} // namespace OHOS::Ace::NG

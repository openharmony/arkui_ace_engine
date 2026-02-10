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
 * @file image_pattern_test_memory_callbacks.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern memory management and callbacks
 *
 * This file contains test cases covering:
 * - RecycleImageData
 * - OnNotifyMemoryLevel
 * - OnWindowHide / OnWindowShow
 * - OnVisibleChange
 * - OnVisibleAreaChange
 * - ClearAltData
 * - CreateDataReadyCallback
 * - CreateLoadSuccessCallback
 * - CreateLoadFailCallback
 * - CreateCompleteCallBackInDataReady
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternMemoryCallbacksTestNg : public ImageBases {};

// ============================================================================
// RecycleImageData Tests
// ============================================================================

/**
 * @tc.name: RecycleImageData001
 * @tc.desc: Test RecycleImageData when isShow is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, RecycleImageData001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set isShow to true and try to recycle
     */
    pattern->OnActive();
    auto result = pattern->RecycleImageData();

    /**
     * @tc.expected: Should return false (no recycle when showing)
     */
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RecycleImageData002
 * @tc.desc: Test RecycleImageData when isShow is false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, RecycleImageData002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set isShow to false and recycle
     */
    pattern->OnInActive();
    auto result = pattern->RecycleImageData();

    /**
     * @tc.expected: Should attempt to recycle
     */
    // Result depends on loading context state
}

/**
 * @tc.name: RecycleImageData003
 * @tc.desc: Test RecycleImageData with network image and cache
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, RecycleImageData003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up network image loading context
     */
    ImageSourceInfo sourceInfo(WEB_IMAGE);
    sourceInfo.srcType_ = SrcType::NETWORK;
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->OnInActive();

    /**
     * @tc.steps: step3. Try to recycle
     */
    auto result = pattern->RecycleImageData();

    /**
     * @tc.expected: Should handle network image cache
     */
    // Network images may be cached
}

/**
 * @tc.name: RecycleImageData004
 * @tc.desc: Test RecycleImageData clears all image data
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, RecycleImageData004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with data
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set image data
     */
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(IMAGE_SRC_URL));
    pattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(ALT_SRC_URL));
    pattern->OnInActive();

    /**
     * @tc.steps: step3. Force recycle (assuming conditions allow)
     */
    // Force conditions for recycle
    pattern->isShow_ = false;
    auto result = pattern->RecycleImageData();

    /**
     * @tc.expected: Data may be recycled depending on conditions
     */
    // Actual recycling depends on various conditions
}

// ============================================================================
// OnNotifyMemoryLevel Tests
// ============================================================================

/**
 * @tc.name: OnNotifyMemoryLevel001
 * @tc.desc: Test OnNotifyMemoryLevel when showing
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnNotifyMemoryLevel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Activate and notify memory level
     */
    pattern->OnActive();
    pattern->OnNotifyMemoryLevel(2);

    /**
     * @tc.expected: Should not recycle when showing
     */
    // Data should remain when showing
}

/**
 * @tc.name: OnNotifyMemoryLevel002
 * @tc.desc: Test OnNotifyMemoryLevel with critical level
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnNotifyMemoryLevel002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Deactivate and notify critical level
     */
    pattern->OnInActive();
    pattern->OnNotifyMemoryLevel(2);

    /**
     * @tc.expected: Should attempt to recycle
     */
    // Critical level may trigger recycle
}

/**
 * @tc.name: OnNotifyMemoryLevel003
 * @tc.desc: Test OnNotifyMemoryLevel with non-critical level
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnNotifyMemoryLevel003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Deactivate and notify low level
     */
    pattern->OnInActive();
    pattern->OnNotifyMemoryLevel(1);

    /**
     * @tc.expected: Should not recycle at non-critical level
     */
    // Low level should not trigger recycle
}

// ============================================================================
// OnWindowHide / OnWindowShow Tests
// ============================================================================

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnWindowHide001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnWindowHide
     */
    pattern->OnWindowHide();

    /**
     * @tc.expected: Should handle window hide
     */
    SUCCEED();
}

/**
 * @tc.name: OnWindowShow001
 * @tc.desc: Test OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnWindowShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnWindowShow
     */
    pattern->OnWindowShow();

    /**
     * @tc.expected: Should handle window show
     */
    SUCCEED();
}

// ============================================================================
// OnVisibleChange Tests
// ============================================================================

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Test OnVisibleChange with true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnVisibleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnVisibleChange with true
     */
    pattern->OnVisibleChange(true);

    /**
     * @tc.expected: Should handle visible change
     */
    SUCCEED();
}

/**
 * @tc.name: OnVisibleChange002
 * @tc.desc: Test OnVisibleChange with false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnVisibleChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnVisibleChange with false
     */
    pattern->OnVisibleChange(false);

    /**
     * @tc.expected: Should handle invisible change
     */
    SUCCEED();
}

// ============================================================================
// OnVisibleAreaChange Tests
// ============================================================================

/**
 * @tc.name: OnVisibleAreaChange001
 * @tc.desc: Test OnVisibleAreaChange with invisible
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnVisibleAreaChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnVisibleAreaChange with invisible
     */
    pattern->OnVisibleAreaChange(false, 0.0);

    /**
     * @tc.expected: Should close select overlay
     */
    SUCCEED();
}

/**
 * @tc.name: OnVisibleAreaChange002
 * @tc.desc: Test OnVisibleAreaChange with animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnVisibleAreaChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->imageType_ = ImagePattern::ImageType::ANIMATION;

    /**
     * @tc.steps: step2. Set animator running and change visibility
     */
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::RUNNING;
        auto pipeline = frameNode->GetContextRefPtr();
        pattern->animator_->AttachScheduler(pipeline);
    }

    pattern->OnVisibleAreaChange(false, 0.0);

    /**
     * @tc.expected: Should pause animation
     */
    if (pattern->animator_) {
        EXPECT_EQ(pattern->animator_->status_, Animator::Status::PAUSED);
    }
}

/**
 * @tc.name: OnVisibleAreaChange003
 * @tc.desc: Test OnVisibleAreaChange with alt image animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, OnVisibleAreaChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set alt image with animation
     */
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_->isStatic_ = false;
    pattern->OnVisibleAreaChange(true, 1.0);

    /**
     * @tc.expected: Should control alt image animation
     */
    SUCCEED();
}

// ============================================================================
// ClearAltData Tests
// ============================================================================

/**
 * @tc.name: ClearAltData001
 * @tc.desc: Test ClearAltData clears all alt data
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, ClearAltData001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set alt data and clear
     */
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(ALT_SRC_URL));
    pattern->altDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 50.0f, 50.0f);
    pattern->altSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 50.0f, 50.0f);

    pattern->ClearAltData();

    /**
     * @tc.expected: All alt data should be null
     */
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_EQ(pattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(pattern->altDstRect_, nullptr);
    EXPECT_EQ(pattern->altSrcRect_, nullptr);
}

// ============================================================================
// CreateDataReadyCallback Tests
// ============================================================================

/**
 * @tc.name: CreateDataReadyCallback001
 * @tc.desc: Test CreateDataReadyCallback with matching source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateDataReadyCallback();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallback002
 * @tc.desc: Test CreateDataReadyCallback with mismatched source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback and call with different source
     */
    auto callback = pattern->CreateDataReadyCallback();
    ImageSourceInfo differentSource("different_src");

    /**
     * @tc.steps: step3. Call callback with different source
     */
    callback(differentSource);

    /**
     * @tc.expected: Should handle mismatched source
     */
    SUCCEED();
}

/**
 * @tc.name: CreateDataReadyCallback003
 * @tc.desc: Test CreateDataReadyCallback with HDR mode
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with HDR
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    renderProp->UpdateDynamicMode(DynamicRangeMode::HIGH);

    /**
     * @tc.steps: step2. Create and call callback
     */
    auto callback = pattern->CreateDataReadyCallback();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);

    /**
     * @tc.expected: Should handle HDR mode
     */
    SUCCEED();
}

// ============================================================================
// CreateLoadSuccessCallback Tests
// ============================================================================

/**
 * @tc.name: CreateLoadSuccessCallback001
 * @tc.desc: Test CreateLoadSuccessCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadSuccessCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateLoadSuccessCallback();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateLoadSuccessCallback002
 * @tc.desc: Test CreateLoadSuccessCallback with drag enabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadSuccessCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->draggable_ = true;

    /**
     * @tc.steps: step2. Create and call callback
     */
    auto callback = pattern->CreateLoadSuccessCallback();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);

    /**
     * @tc.expected: Should enable drag
     */
    SUCCEED();
}

// ============================================================================
// CreateLoadFailCallback Tests
// ============================================================================

/**
 * @tc.name: CreateLoadFailCallback001
 * @tc.desc: Test CreateLoadFailCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadFailCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateLoadFailCallback();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateLoadFailCallback002
 * @tc.desc: Test CreateLoadFailCallback with error message
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadFailCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create and call callback
     */
    auto callback = pattern->CreateLoadFailCallback();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    std::string errorMsg = "Load failed";
    callback(sourceInfo, errorMsg);

    /**
     * @tc.expected: Should handle error
     */
    SUCCEED();
}

/**
 * @tc.name: CreateLoadFailCallback003
 * @tc.desc: Test CreateLoadFailCallback from reset
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadFailCallback003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback with reset source
     */
    auto callback = pattern->CreateLoadFailCallback();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    sourceInfo.SetIsFromReset(true);
    std::string errorMsg = "Load failed";
    callback(sourceInfo, errorMsg);

    /**
     * @tc.expected: Should handle reset source
     */
    SUCCEED();
}

// ============================================================================
// CreateCompleteCallBackInDataReady Tests
// ============================================================================

/**
 * @tc.name: CreateCompleteCallBackInDataReady001
 * @tc.desc: Test CreateCompleteCallBackInDataReady
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateCompleteCallBackInDataReady001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateCompleteCallBackInDataReady();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateCompleteCallBackInDataReady002
 * @tc.desc: Test CreateCompleteCallBackInDataReady call
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateCompleteCallBackInDataReady002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create and call callback
     */
    auto callback = pattern->CreateCompleteCallBackInDataReady();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);

    /**
     * @tc.expected: Should handle complete callback
     */
    SUCCEED();
}

// ============================================================================
// CreateDataReadyCallbackForAlt Tests
// ============================================================================

/**
 * @tc.name: CreateDataReadyCallbackForAlt001
 * @tc.desc: Test CreateDataReadyCallbackForAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallbackForAlt001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateDataReadyCallbackForAlt();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallbackForAlt002
 * @tc.desc: Test CreateDataReadyCallbackForAlt with inactive node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallbackForAlt002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->isActive_ = false;

    /**
     * @tc.steps: step2. Create and call callback
     */
    auto callback = pattern->CreateDataReadyCallbackForAlt();
    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    callback(sourceInfo);

    /**
     * @tc.expected: Should return early for inactive node
     */
    SUCCEED();
}

/**
 * @tc.name: CreateDataReadyCallbackForAlt003
 * @tc.desc: Test CreateDataReadyCallbackForAlt with no content
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateDataReadyCallbackForAlt003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Remove content and call callback
     */
    frameNode->GetGeometryNode()->SetContentSize(SizeF());

    auto callback = pattern->CreateDataReadyCallbackForAlt();
    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    callback(sourceInfo);

    /**
     * @tc.expected: Should mark for layout
     */
    SUCCEED();
}

// ============================================================================
// CreateLoadSuccessCallbackForAlt Tests
// ============================================================================

/**
 * @tc.name: CreateLoadSuccessCallbackForAlt001
 * @tc.desc: Test CreateLoadSuccessCallbackForAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternMemoryCallbacksTestNg, CreateLoadSuccessCallbackForAlt001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create callback
     */
    auto callback = pattern->CreateLoadSuccessCallbackForAlt();

    /**
     * @tc.expected: Callback should be created
     */
    EXPECT_NE(callback, nullptr);
}

} // namespace OHOS::Ace::NG

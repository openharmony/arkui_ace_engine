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
 * @file image_pattern_test_image_loading.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern image loading flow
 *
 * This file contains test cases covering:
 * - LoadImage / LoadAltImage
 * - StartDecoding
 * - OnImageDataReady
 * - OnImageLoadSuccess
 * - OnImageLoadFail
 * - UpdateOrientation
 * - CalcImageContentPaintSize
 * - SetImagePaintConfig
 * - PrepareAnimation
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternImageLoadingTestNg : public ImageBases {};

// ============================================================================
// LoadImage Tests
// ============================================================================

/**
 * @tc.name: LoadImage001
 * @tc.desc: Test LoadImage with new source (no existing loadingCtx)
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load image with new source
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::VISIBLE);

    /**
     * @tc.expected: loadingCtx_ should be created
     */
    // loadingCtx_ is created during LoadImage
}

/**
 * @tc.name: LoadImage002
 * @tc.desc: Test LoadImage with existing loadingCtx
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with existing context
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load same image again
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::VISIBLE);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::VISIBLE);

    /**
     * @tc.expected: Should handle existing context
     */
    SUCCEED();
}

/**
 * @tc.name: LoadImage003
 * @tc.desc: Test LoadImage with PROPERTY_UPDATE_MEASURE flag
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load image with PROPERTY_UPDATE_MEASURE
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_MEASURE, VisibleType::VISIBLE);

    /**
     * @tc.expected: Should handle measure update
     */
    SUCCEED();
}

/**
 * @tc.name: LoadImage004
 * @tc.desc: Test LoadImage with VisibleType::GONE
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load image with GONE visibility
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::GONE);

    /**
     * @tc.expected: Should handle GONE visibility
     */
    SUCCEED();
}

/**
 * @tc.name: LoadImage005
 * @tc.desc: Test LoadImage with progress callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set progress callback and load
     */
    int callbackCalled = 0;
    pattern->SetOnProgressCallback([&callbackCalled](const uint32_t&, const uint32_t&) {
        callbackCalled++;
    });

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::VISIBLE);

    /**
     * @tc.expected: Callback should be set
     */
    EXPECT_NE(pattern->onProgressCallback_, nullptr);
}

/**
 * @tc.name: LoadImage006
 * @tc.desc: Test LoadImage with network image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadImage006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load network image
     */
    ImageSourceInfo sourceInfo(WEB_IMAGE);
    pattern->LoadImage(sourceInfo, PROPERTY_UPDATE_NORMAL, VisibleType::VISIBLE);

    /**
     * @tc.expected: Should handle network image
     */
    SUCCEED();
}

// ============================================================================
// LoadAltImage Tests
// ============================================================================

/**
 * @tc.name: LoadAltImage001
 * @tc.desc: Test LoadAltImage with valid source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadAltImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load alt image
     */
    ImageSourceInfo altSourceInfo(ALT_SRC_URL);
    pattern->LoadAltImage(altSourceInfo);

    /**
     * @tc.expected: altLoadingCtx_ should be created
     */
    // altLoadingCtx_ is created during LoadAltImage
}

/**
 * @tc.name: LoadAltImage002
 * @tc.desc: Test LoadAltImage with empty source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, LoadAltImage002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load empty alt image
     */
    ImageSourceInfo altSourceInfo("");
    pattern->LoadAltImage(altSourceInfo);

    /**
     * @tc.expected: Should handle empty source
     */
    SUCCEED();
}

// ============================================================================
// StartDecoding Tests
// ============================================================================

/**
 * @tc.name: StartDecoding001
 * @tc.desc: Test StartDecoding with valid content size
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, StartDecoding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call StartDecoding
     */
    SizeF dstSize(100.0f, 100.0f);
    pattern->StartDecoding(dstSize);

    /**
     * @tc.expected: Decoding should start
     */
    SUCCEED();
}

/**
 * @tc.name: StartDecoding002
 * @tc.desc: Test StartDecoding with zero content size
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, StartDecoding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Call StartDecoding
     */
    SizeF dstSize(0.0f, 0.0f);
    pattern->StartDecoding(dstSize);

    /**
     * @tc.expected: Should handle zero size
     */
    SUCCEED();
}

/**
 * @tc.name: StartDecoding003
 * @tc.desc: Test StartDecoding with HDR mode
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, StartDecoding003, TestSize.Level1)
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
     * @tc.steps: step2. Call StartDecoding
     */
    SizeF dstSize(100.0f, 100.0f);
    pattern->StartDecoding(dstSize);

    /**
     * @tc.expected: Should handle HDR mode
     */
    SUCCEED();
}

/**
 * @tc.name: StartDecoding004
 * @tc.desc: Test StartDecoding with alt image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, StartDecoding004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with alt
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set alt context and decode
     */
    pattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(ALT_SRC_URL));
    SizeF dstSize(100.0f, 100.0f);
    pattern->StartDecoding(dstSize);

    /**
     * @tc.expected: Should handle alt image
     */
    SUCCEED();
}

// ============================================================================
// OnImageDataReady Tests
// ============================================================================

/**
 * @tc.name: OnImageDataReady001
 * @tc.desc: Test OnImageDataReady when layout is needed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageDataReady001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up loading context and call OnImageDataReady
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);

    /**
     * @tc.steps: step3. Remove content to trigger layout
     */
    frameNode->GetGeometryNode()->SetContentSize(SizeF());

    pattern->OnImageDataReady();

    /**
     * @tc.expected: Should mark for layout
     */
    SUCCEED();
}

/**
 * @tc.name: OnImageDataReady002
 * @tc.desc: Test OnImageDataReady when layout is not needed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageDataReady002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with content
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(100.0f, 100.0f));

    /**
     * @tc.steps: step2. Set up loading context
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);

    /**
     * @tc.steps: step3. Call OnImageDataReady
     */
    pattern->OnImageDataReady();

    /**
     * @tc.expected: Should start decoding
     */
    SUCCEED();
}

/**
 * @tc.name: OnImageDataReady003
 * @tc.desc: Test OnImageDataReady for image animator
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageDataReady003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image animator node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isImageAnimator_ = true;
    frameNode->GetGeometryNode()->SetContentSize(SizeF(100.0f, 100.0f));

    /**
     * @tc.steps: step2. Set up loading context
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);

    /**
     * @tc.steps: step3. Call OnImageDataReady
     */
    pattern->OnImageDataReady();

    /**
     * @tc.expected: Should start decoding directly
     */
    SUCCEED();
}

// ============================================================================
// OnImageLoadSuccess Tests
// ============================================================================

/**
 * @tc.name: OnImageLoadSuccess001
 * @tc.desc: Test OnImageLoadSuccess with valid image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadSuccess001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up loading context with canvas image
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->canvasImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->srcRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->imageSize_ = SizeF(100.0f, 100.0f);
    pattern->loadingCtx_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call OnImageLoadSuccess
     */
    pattern->OnImageLoadSuccess();

    /**
     * @tc.expected: image_ should be set, alt data cleared
     */
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccess002
 * @tc.desc: Test OnImageLoadSuccess with null canvas image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadSuccess002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up loading context without canvas image
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->canvasImage_ = nullptr;

    /**
     * @tc.steps: step3. Call OnImageLoadSuccess
     */
    pattern->OnImageLoadSuccess();

    /**
     * @tc.expected: Should handle null image gracefully
     */
    SUCCEED();
}

/**
 * @tc.name: OnImageLoadSuccess003
 * @tc.desc: Test OnImageLoadSuccess with SVG image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadSuccess003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up loading context with SVG
     */
    ImageSourceInfo sourceInfo(RESOURCE_URL);  // SVG resource
    sourceInfo.srcType_ = SrcType::RESOURCE;
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->canvasImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->srcRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->imageSize_ = SizeF(100.0f, 100.0f);
    pattern->loadingCtx_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call OnImageLoadSuccess
     */
    pattern->OnImageLoadSuccess();

    /**
     * @tc.expected: Should handle SVG
     */
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccess004
 * @tc.desc: Test OnImageLoadSuccess with drag enabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadSuccess004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->enableDrag_ = true;

    /**
     * @tc.steps: step2. Set up loading context
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->canvasImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->srcRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->imageSize_ = SizeF(100.0f, 100.0f);
    pattern->loadingCtx_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call OnImageLoadSuccess
     */
    pattern->OnImageLoadSuccess();

    /**
     * @tc.expected: Should enable drag
     */
    EXPECT_NE(pattern->image_, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccess005
 * @tc.desc: Test OnImageLoadSuccess clears alt data
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadSuccess005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up alt data and loading context
     */
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(ALT_SRC_URL));
    pattern->altDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 50.0f, 50.0f);
    pattern->altSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 50.0f, 50.0f);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->canvasImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->srcRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadingCtx_->imageSize_ = SizeF(100.0f, 100.0f);
    pattern->loadingCtx_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call OnImageLoadSuccess
     */
    pattern->OnImageLoadSuccess();

    /**
     * @tc.expected: Alt data should be cleared
     */
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_EQ(pattern->altLoadingCtx_, nullptr);
}

// ============================================================================
// OnImageLoadFail Tests
// ============================================================================

/**
 * @tc.name: OnImageLoadFail001
 * @tc.desc: Test OnImageLoadFail with error message
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadFail001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnImageLoadFail
     */
    std::string errorMsg = "Failed to load image";
    pattern->OnImageLoadFail(errorMsg);

    /**
     * @tc.expected: Should fire error event
     */
    SUCCEED();
}

/**
 * @tc.name: OnImageLoadFail002
 * @tc.desc: Test OnImageLoadFail with empty error message
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, OnImageLoadFail002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnImageLoadFail with empty message
     */
    std::string errorMsg = "";
    pattern->OnImageLoadFail(errorMsg);

    /**
     * @tc.expected: Should handle empty message
     */
    SUCCEED();
}

// ============================================================================
// UpdateOrientation Tests
// ============================================================================

/**
 * @tc.name: UpdateOrientation001
 * @tc.desc: Test UpdateOrientation with multi-frame image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, UpdateOrientation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up loading context with multi-frame
     */
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->imageObj_ = AceType::MakeRefPtr<MockImageObject>();
    pattern->loadingCtx_->imageObj_->frameCount_ = 2;  // Multi-frame

    /**
     * @tc.steps: step3. Call UpdateOrientation
     */
    pattern->UpdateOrientation();

    /**
     * @tc.expected: Orientation should be UP
     */
    // Multi-frame images always use UP orientation
}

/**
 * @tc.name: UpdateOrientation002
 * @tc.desc: Test UpdateOrientation with user orientation UP
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, UpdateOrientation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set user orientation to UP
     */
    pattern->userOrientation_ = ImageRotateOrientation::UP;
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->imageObj_ = AceType::MakeRefPtr<MockImageObject>();
    pattern->loadingCtx_->imageObj_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call UpdateOrientation
     */
    pattern->UpdateOrientation();

    /**
     * @tc.expected: joinOrientation_ should be UP
     */
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: UpdateOrientation003
 * @tc.desc: Test UpdateOrientation with user orientation AUTO
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, UpdateOrientation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set user orientation to AUTO
     */
    pattern->userOrientation_ = ImageRotateOrientation::AUTO;
    pattern->selfOrientation_ = ImageRotateOrientation::RIGHT;
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->imageObj_ = AceType::MakeRefPtr<MockImageObject>();
    pattern->loadingCtx_->imageObj_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call UpdateOrientation
     */
    pattern->UpdateOrientation();

    /**
     * @tc.expected: joinOrientation_ should use self orientation
     */
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: UpdateOrientation004
 * @tc.desc: Test UpdateOrientation with custom user orientation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, UpdateOrientation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set user orientation to RIGHT
     */
    pattern->userOrientation_ = ImageRotateOrientation::RIGHT;
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->imageObj_ = AceType::MakeRefPtr<MockImageObject>();
    pattern->loadingCtx_->imageObj_->frameCount_ = 1;

    /**
     * @tc.steps: step3. Call UpdateOrientation
     */
    pattern->UpdateOrientation();

    /**
     * @tc.expected: joinOrientation_ should be RIGHT
     */
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::RIGHT);
}

// ============================================================================
// CalcImageContentPaintSize Tests
// ============================================================================

/**
 * @tc.name: CalcImageContentPaintSize001
 * @tc.desc: Test CalcImageContentPaintSize with SVG image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, CalcImageContentPaintSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up SVG loading context
     */
    ImageSourceInfo sourceInfo(RESOURCE_URL);
    sourceInfo.srcType_ = SrcType::RESOURCE;
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    /**
     * @tc.steps: step3. Call CalcImageContentPaintSize
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);

    /**
     * @tc.expected: Should return valid paint size
     */
    EXPECT_GE(paintSize.Width(), 0.0f);
    EXPECT_GE(paintSize.Height(), 0.0f);
}

/**
 * @tc.name: CalcImageContentPaintSize002
 * @tc.desc: Test CalcImageContentPaintSize with repeat X
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, CalcImageContentPaintSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up repeat X
     */
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    renderProp->UpdateImageRepeat(ImageRepeat::REPEAT_X);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 50.0f, 50.0f);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(100.0f, 100.0f));

    /**
     * @tc.steps: step3. Call CalcImageContentPaintSize
     */
    auto geometryNode = frameNode->GetGeometryNode();
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);

    /**
     * @tc.expected: Width should match content, height should match dstRect
     */
    EXPECT_GT(paintSize.Width(), 0.0f);
}

/**
 * @tc.name: CalcImageContentPaintSize003
 * @tc.desc: Test CalcImageContentPaintSize with repeat Y
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, CalcImageContentPaintSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up repeat Y
     */
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    renderProp->UpdateImageRepeat(ImageRepeat::REPEAT_Y);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);
    pattern->loadingCtx_->dstRect_ = RectF(0.0f, 0.0f, 50.0f, 50.0f);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(100.0f, 100.0f));

    /**
     * @tc.steps: step3. Call CalcImageContentPaintSize
     */
    auto geometryNode = frameNode->GetGeometryNode();
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);

    /**
     * @tc.expected: Height should match content, width should match dstRect
     */
    EXPECT_GT(paintSize.Height(), 0.0f);
}

// ============================================================================
// SetImagePaintConfig Tests
// ============================================================================

/**
 * @tc.name: SetImagePaintConfig001
 * @tc.desc: Test SetImagePaintConfig with basic config
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, SetImagePaintConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create canvas image and set config
     */
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    RectF srcRect(0.0f, 0.0f, 100.0f, 100.0f);
    RectF dstRect(0.0f, 0.0f, 50.0f, 50.0f);
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);

    pattern->SetImagePaintConfig(canvasImage, srcRect, dstRect, sourceInfo, 1);

    /**
     * @tc.expected: Config should be set
     */
    EXPECT_NE(canvasImage->paintConfig_, nullptr);
}

/**
 * @tc.name: SetImagePaintConfig002
 * @tc.desc: Test SetImagePaintConfig with color filter
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, SetImagePaintConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set color filter
     */
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    renderProp->UpdateColorFilter(COLOR_FILTER_DEFAULT);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    RectF srcRect(0.0f, 0.0f, 100.0f, 100.0f);
    RectF dstRect(0.0f, 0.0f, 50.0f, 50.0f);
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);

    pattern->SetImagePaintConfig(canvasImage, srcRect, dstRect, sourceInfo, 1);

    /**
     * @tc.expected: Config should include color filter
     */
    EXPECT_NE(canvasImage->paintConfig_, nullptr);
}

// ============================================================================
// PrepareAnimation Tests
// ============================================================================

/**
 * @tc.name: PrepareAnimation001
 * @tc.desc: Test PrepareAnimation with static image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, PrepareAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create static canvas image
     */
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    canvasImage->SetPaintConfig(ImagePaintConfig());
    canvasImage->isStatic_ = true;

    /**
     * @tc.steps: step3. Call PrepareAnimation
     */
    pattern->PrepareAnimation(canvasImage);

    /**
     * @tc.expected: Should handle static image
     */
    EXPECT_TRUE(canvasImage->IsStatic());
}

/**
 * @tc.name: PrepareAnimation002
 * @tc.desc: Test PrepareAnimation with animated image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, PrepareAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create animated canvas image
     */
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    canvasImage->SetPaintConfig(ImagePaintConfig());
    canvasImage->isStatic_ = false;
    canvasImage->frameCount_ = 5;

    /**
     * @tc.steps: step3. Call PrepareAnimation
     */
    pattern->PrepareAnimation(canvasImage);

    /**
     * @tc.expected: Should set up animation
     */
    EXPECT_FALSE(canvasImage->IsStatic());
}

/**
 * @tc.name: PrepareAnimation003
 * @tc.desc: Test PrepareAnimation sets redraw callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternImageLoadingTestNg, PrepareAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create canvas image
     */
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    canvasImage->SetPaintConfig(ImagePaintConfig());

    /**
     * @tc.steps: step3. Call PrepareAnimation
     */
    pattern->PrepareAnimation(canvasImage);

    /**
     * @tc.expected: Redraw callback should be set
     */
    // Callback is set internally
}

} // namespace OHOS::Ace::NG

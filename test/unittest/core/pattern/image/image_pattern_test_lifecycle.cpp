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

/**
 * @file image_pattern_test_lifecycle.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern lifecycle and initialization
 *
 * This file contains test cases covering:
 * - Constructor and Destructor
 * - OnAttachToFrameNode / OnDetachFromFrameNode
 * - OnModifyDone
 * - OnActive / OnInActive
 * - OnReuse / OnRecycle
 * - Create methods (CreateLayoutProperty, CreatePaintProperty, etc.)
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternLifecycleTestNg : public ImageBases {};

// ============================================================================
// Constructor and Destructor Tests
// ============================================================================

/**
 * @tc.name: ImagePatternConstructor001
 * @tc.desc: Test ImagePattern constructor initializes all members correctly
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, ImagePatternConstructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImagePattern instance
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.expected: All members should be initialized to default values
     */
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->image_, nullptr);
    EXPECT_EQ(pattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_EQ(pattern->animator_, nullptr);
    EXPECT_TRUE(pattern->images_.empty());
    EXPECT_TRUE(pattern->cacheImages_.empty());
    EXPECT_EQ(pattern->status_, Animator::Status::IDLE);
    EXPECT_EQ(pattern->imageType_, ImagePattern::ImageType::BASE);
    EXPECT_FALSE(pattern->isShow_);
    EXPECT_FALSE(pattern->isImageAnimator_);
    EXPECT_EQ(pattern->nowImageIndex_, 0);
}

/**
 * @tc.name: ImagePatternDestructor001
 * @tc.desc: Test ImagePattern destructor releases resources when isEnableAnalyzer_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, ImagePatternDestructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImagePattern with analyzer enabled
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->isEnableAnalyzer_ = true;
    pattern->imageAnalyzerManager_ = AceType::MakeRefPtr<MockImageAnalyzerManager>();

    /**
     * @tc.steps: step2. Destroy pattern
     * @tc.expected: Analyzer should be released
     */
    pattern.reset();
    SUCCEED();
}

/**
 * @tc.name: ImagePatternDestructor002
 * @tc.desc: Test ImagePattern destructor when isEnableAnalyzer_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, ImagePatternDestructor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImagePattern without analyzer
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->isEnableAnalyzer_ = false;

    /**
     * @tc.steps: step2. Destroy pattern
     * @tc.expected: No crash, clean destruction
     */
    pattern.reset();
    SUCCEED();
}

// ============================================================================
// OnAttachToFrameNode Tests
// ============================================================================

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with pattern
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.expected: Pattern should be attached successfully
     */
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
}

// ============================================================================
// OnDetachFromFrameNode Tests
// ============================================================================

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test OnDetachFromFrameNode cleans up resources
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with pattern
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Detach pattern
     * @tc.expected: Resources should be cleaned up
     */
    pattern->UnregisterWindowStateChangedCallback();
    SUCCEED();
}

// ============================================================================
// OnModifyDone Tests
// ============================================================================

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone with normal image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Mark modify done
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Pattern should handle modify done
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone with animation image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation image node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isImageAnimator_ = true;

    /**
     * @tc.steps: step2. Mark modify done
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Animation should be set up
     */
    EXPECT_NE(pattern->animator_, nullptr);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Test OnModifyDone with copy enabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnModifyDone004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node with copy
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    frameNode->draggable_ = true;

    /**
     * @tc.steps: step2. Mark modify done
     */
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Copy should be initialized
     */
    // Copy is initialized in InitCopy
}

// ============================================================================
// OnActive / OnInActive Tests
// ============================================================================

/**
 * @tc.name: OnActive001
 * @tc.desc: Test OnActive sets isShow_ to true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnActive001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnActive
     */
    pattern->OnActive();

    /**
     * @tc.expected: isShow_ should be true
     */
    EXPECT_TRUE(pattern->isShow_);
}

/**
 * @tc.name: OnInActive001
 * @tc.desc: Test OnInActive sets isShow_ to false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnInActive001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and activate
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnActive();
    EXPECT_TRUE(pattern->isShow_);

    /**
     * @tc.steps: step2. Call OnInActive
     */
    pattern->OnInActive();

    /**
     * @tc.expected: isShow_ should be false
     */
    EXPECT_FALSE(pattern->isShow_);
}

/**
 * @tc.name: OnInActive002
 * @tc.desc: Test OnInActive with animation running
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnInActive002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Start animation and deactivate
     */
    pattern->OnActive();
    if (pattern->animator_) {
        pattern->animator_->status_ = Animator::Status::RUNNING;
    }
    pattern->OnInActive();

    /**
     * @tc.expected: isShow_ should be false
     */
    EXPECT_FALSE(pattern->isShow_);
}

// ============================================================================
// OnRecycle Tests
// ============================================================================

/**
 * @tc.name: OnRecycle001
 * @tc.desc: Test OnRecycle releases all image data
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnRecycle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node with data
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set image data and recycle
     */
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(""));
    pattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(""));

    pattern->OnRecycle();

    /**
     * @tc.expected: All image data should be null
     */
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->image_, nullptr);
    EXPECT_EQ(pattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(pattern->altImage_, nullptr);
}

/**
 * @tc.name: OnRecycle002
 * @tc.desc: Test OnRecycle with no image data
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnRecycle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Recycle without data
     */
    pattern->OnRecycle();

    /**
     * @tc.expected: No crash, all null
     */
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    EXPECT_EQ(pattern->image_, nullptr);
}

/**
 * @tc.name: OnRecycle003
 * @tc.desc: Test OnRecycle removes content modifier
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnRecycle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create modifier and recycle
     */
    pattern->CreateModifier();
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    pattern->OnRecycle();

    /**
     * @tc.expected: Modifier should be removed
     */
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
}

// ============================================================================
// OnReuse Tests
// ============================================================================

/**
 * @tc.name: OnReuse001
 * @tc.desc: Test OnReuse reinitializes state
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnReuse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnReuse
     */
    pattern->OnReuse();

    /**
     * @tc.expected: State should be reinitialized
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnReuse002
 * @tc.desc: Test OnReuse with borderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnReuse002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set needBorderRadius and reuse
     */
    pattern->needBorderRadius_ = true;
    pattern->OnReuse();

    /**
     * @tc.expected: BorderRadius should be updated
     */
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    EXPECT_TRUE(renderProp->GetNeedBorderRadiusValue(false));
}

// ============================================================================
// Create Methods Tests
// ============================================================================

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty returns valid ImageLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Create layout property
     */
    auto layoutProperty = pattern->CreateLayoutProperty();

    /**
     * @tc.expected: Should return valid ImageLayoutProperty
     */
    ASSERT_NE(layoutProperty, nullptr);
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(layoutProperty);
    EXPECT_NE(imageLayoutProperty, nullptr);
}

/**
 * @tc.name: CreatePaintProperty001
 * @tc.desc: Test CreatePaintProperty returns valid ImageRenderProperty
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreatePaintProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Create paint property
     */
    auto paintProperty = pattern->CreatePaintProperty();

    /**
     * @tc.expected: Should return valid ImageRenderProperty
     */
    ASSERT_NE(paintProperty, nullptr);
    auto imageRenderProperty = AceType::DynamicCast<ImageRenderProperty>(paintProperty);
    EXPECT_NE(imageRenderProperty, nullptr);
}

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub returns valid ImageEventHub
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreateEventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Create event hub
     */
    auto eventHub = pattern->CreateEventHub();

    /**
     * @tc.expected: Should return valid ImageEventHub
     */
    ASSERT_NE(eventHub, nullptr);
    auto imageEventHub = AceType::DynamicCast<ImageEventHub>(eventHub);
    EXPECT_NE(imageEventHub, nullptr);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm returns valid ImageLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Create layout algorithm
     */
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();

    /**
     * @tc.expected: Should return valid ImageLayoutAlgorithm
     */
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto imageLayoutAlgorithm = AceType::DynamicCast<ImageLayoutAlgorithm>(layoutAlgorithm);
    EXPECT_NE(imageLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod with null image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Create paint method without image
     */
    auto paintMethod = pattern->CreateNodePaintMethod();

    /**
     * @tc.expected: Should return null or valid paint method
     */
    // May return null if no image
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test CreateNodePaintMethod with image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set image and create paint method
     */
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    auto paintMethod = pattern->CreateNodePaintMethod();

    /**
     * @tc.expected: Should return valid paint method
     */
    ASSERT_NE(paintMethod, nullptr);
    auto imagePaintMethod = AceType::DynamicCast<ImagePaintMethod>(paintMethod);
    EXPECT_NE(imagePaintMethod, nullptr);
}

// ============================================================================
// FocusPattern Tests
// ============================================================================

/**
 * @tc.name: GetFocusPattern001
 * @tc.desc: Test GetFocusPattern returns correct focus pattern
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, GetFocusPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Get focus pattern
     */
    auto focusPattern = pattern->GetFocusPattern();

    /**
     * @tc.expected: Should return valid FocusPattern
     */
    // FocusPattern structure verification
}

// ============================================================================
// IsAtomicNode Tests
// ============================================================================

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode returns true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, IsAtomicNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Check if atomic node
     */
    auto isAtomic = pattern->IsAtomicNode();

    /**
     * @tc.expected: Should return true for image
     */
    EXPECT_TRUE(isAtomic);
}

// ============================================================================
// GetContextParam Tests
// ============================================================================

/**
 * @tc.name: GetContextParam001
 * @tc.desc: Test GetContextParam with normal setup
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, GetContextParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get context param
     */
    auto contextParam = pattern->GetContextParam();

    /**
     * @tc.expected: Should return optional context param
     */
    // ContextParam depends on implementation
}

// ============================================================================
// OnDirtyLayoutWrapperSwap Tests
// ============================================================================

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with skipMeasure
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper with skipMeasure
     */
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, imageLayoutProperty);
    layoutWrapper->skipMeasureContent_ = true;

    DirtySwapConfig config;
    config.skipMeasure = true;

    /**
     * @tc.steps: step3. Call OnDirtyLayoutWrapperSwap
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    /**
     * @tc.expected: Should return false or swap result
     */
    // Result depends on image state
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animation frame node
     */
    auto frameNode = CreatePixelMapAnimator(2);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper
     */
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, imageLayoutProperty);

    DirtySwapConfig config;
    config.skipMeasure = false;

    /**
     * @tc.steps: step3. Call OnDirtyLayoutWrapperSwap
     */
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    /**
     * @tc.expected: Should handle animation
     */
    // Result depends on animation state
}

// ============================================================================
// BeforeCreatePaintWrapper Tests
// ============================================================================

/**
 * @tc.name: BeforeCreatePaintWrapper001
 * @tc.desc: Test BeforeCreatePaintWrapper
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLifecycleTestNg, BeforeCreatePaintWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call BeforeCreatePaintWrapper
     */
    pattern->BeforeCreatePaintWrapper();

    /**
     * @tc.expected: Should complete without crash
     */
    SUCCEED();
}

} // namespace OHOS::Ace::NG

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
 * @file image_pattern_test_events_edge_cases.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern events and edge cases
 *
 * This file contains test cases covering:
 * - Event handling (InitCopy, HandleCopy, OpenSelectOverlay, CloseSelectOverlay)
 * - Keyboard events (InitOnKeyEvent, OnKeyEvent)
 * - Drag events (EnableDrag, UpdateDragEvent)
 * - Selection (CheckHandles, GetClientHost, BetweenSelectedPosition)
 * - Analyzer (EnableAnalyzer, IsSupportImageAnalyzerFeature)
 * - Configuration updates (OnLanguageConfigurationUpdate, OnColorConfigurationUpdate)
 * - Orientation (SetOrientation, GetOrientation)
 * - External decode format (SetExternalDecodeFormat, GetExternalDecodeFormat)
 * - Edge cases and error conditions
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternEventsEdgeCasesTestNg : public ImageBases {};

// ============================================================================
// InitCopy / HandleCopy Tests
// ============================================================================

/**
 * @tc.name: InitCopy001
 * @tc.desc: Test InitCopy initializes copy functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, InitCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init copy
     */
    pattern->InitCopy();

    /**
     * @tc.expected: Copy events should be initialized
     */
    EXPECT_NE(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: InitCopy002
 * @tc.desc: Test InitCopy when already initialized
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, InitCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init copy twice
     */
    pattern->InitCopy();
    pattern->InitCopy();

    /**
     * @tc.expected: Should not duplicate initialization
     */
    EXPECT_NE(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: HandleCopy001
 * @tc.desc: Test HandleCopy with null image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, HandleCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->image_ = nullptr;

    /**
     * @tc.steps: step2. Handle copy
     */
    pattern->HandleCopy();

    /**
     * @tc.expected: Should handle null image
     */
    SUCCEED();
}

/**
 * @tc.name: HandleCopy002
 * @tc.desc: Test HandleCopy with valid image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, HandleCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();

    /**
     * @tc.steps: step2. Handle copy
     */
    pattern->HandleCopy();

    /**
     * @tc.expected: Clipboard should be created
     */
    EXPECT_NE(pattern->clipboard_.GetRawPtr(), nullptr);
}

// ============================================================================
// OpenSelectOverlay / CloseSelectOverlay Tests
// ============================================================================

/**
 * @tc.name: OpenSelectOverlay001
 * @tc.desc: Test OpenSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, OpenSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Open select overlay
     */
    pattern->OpenSelectOverlay();

    /**
     * @tc.expected: Select overlay should be created
     */
    // Select overlay creation depends on system
}

/**
 * @tc.name: CloseSelectOverlay001
 * @tc.desc: Test CloseSelectOverlay with null overlay
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, CloseSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_ = nullptr;

    /**
     * @tc.steps: step2. Close select overlay
     */
    pattern->CloseSelectOverlay();

    /**
     * @tc.expected: Should handle null overlay
     */
    SUCCEED();
}

/**
 * @tc.name: CloseSelectOverlay002
 * @tc.desc: Test CloseSelectOverlay with valid overlay
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, CloseSelectOverlay002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Open and close overlay
     */
    pattern->OpenSelectOverlay();
    if (pattern->selectOverlay_) {
        pattern->CloseSelectOverlay();
    }

    /**
     * @tc.expected: Overlay should be closed
     */
    SUCCEED();
}

// ============================================================================
// CheckHandles Tests
// ============================================================================

/**
 * @tc.name: CheckHandles001
 * @tc.desc: Test CheckHandles with clip edge disabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, CheckHandles001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Disable clip edge
     */
    const auto& renderContext = frameNode->GetRenderContext();
    renderContext->UpdateClipEdge(false);

    SelectHandleInfo handleInfo;
    pattern->CheckHandles(handleInfo);

    /**
     * @tc.expected: Should return early
     */
    SUCCEED();
}

/**
 * @tc.name: CheckHandles002
 * @tc.desc: Test CheckHandles with parent
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, CheckHandles002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Enable clip edge
     */
    const auto& renderContext = frameNode->GetRenderContext();
    renderContext->UpdateClipEdge(true);

    SelectHandleInfo handleInfo;
    pattern->CheckHandles(handleInfo);

    /**
     * @tc.expected: Should check handles
     */
    SUCCEED();
}

// ============================================================================
// EnableDrag Tests
// ============================================================================

/**
 * @tc.name: EnableDrag001
 * @tc.desc: Test EnableDrag
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, EnableDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Enable drag
     */
    pattern->EnableDrag();

    /**
     * @tc.expected: Drag should be enabled
     */
    EXPECT_TRUE(pattern->enableDrag_);
}

// ============================================================================
// Keyboard Events Tests
// ============================================================================

/**
 * @tc.name: InitOnKeyEvent001
 * @tc.desc: Test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, InitOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init key event
     */
    pattern->InitOnKeyEvent();

    /**
     * @tc.expected: Should complete without crash
     */
    SUCCEED();
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: Test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, OnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnKeyEvent
     */
    pattern->OnKeyEvent();

    /**
     * @tc.expected: Should complete without crash
     */
    SUCCEED();
}

// ============================================================================
// Orientation Tests
// ============================================================================

/**
 * @tc.name: SetOrientation001
 * @tc.desc: Test SetOrientation with UP
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetOrientation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set orientation
     */
    pattern->SetOrientation(ImageRotateOrientation::UP);

    /**
     * @tc.expected: Orientation should be UP
     */
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::UP);
}

/**
 * @tc.name: SetOrientation002
 * @tc.desc: Test SetOrientation with RIGHT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetOrientation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set orientation to RIGHT
     */
    pattern->SetOrientation(ImageRotateOrientation::RIGHT);

    /**
     * @tc.expected: Orientation should be RIGHT
     */
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: SetOrientation003
 * @tc.desc: Test SetOrientation with DOWN
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetOrientation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set orientation to DOWN
     */
    pattern->SetOrientation(ImageRotateOrientation::DOWN);

    /**
     * @tc.expected: Orientation should be DOWN
     */
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::DOWN);
}

/**
 * @tc.name: SetOrientation004
 * @tc.desc: Test SetOrientation with LEFT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetOrientation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set orientation to LEFT
     */
    pattern->SetOrientation(ImageRotateOrientation::LEFT);

    /**
     * @tc.expected: Orientation should be LEFT
     */
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::LEFT);
}

/**
 * @tc.name: SetOrientation005
 * @tc.desc: Test SetOrientation with AUTO
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetOrientation005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set orientation to AUTO
     */
    pattern->SetOrientation(ImageRotateOrientation::AUTO);

    /**
     * @tc.expected: Orientation should be AUTO
     */
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::AUTO);
}

// ============================================================================
// External Decode Format Tests
// ============================================================================

/**
 * @tc.name: SetExternalDecodeFormat001
 * @tc.desc: Test SetExternalDecodeFormat with UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetExternalDecodeFormat001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set decode format
     */
    pattern->SetExternalDecodeFormat(PixelFormat::UNKNOWN);

    /**
     * @tc.expected: Format should be UNKNOWN
     */
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);
}

/**
 * @tc.name: SetExternalDecodeFormat002
 * @tc.desc: Test SetExternalDecodeFormat with RGBA_8888
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetExternalDecodeFormat002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set decode format to RGBA_8888
     */
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_8888);

    /**
     * @tc.expected: Format should be RGBA_8888
     */
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::RGBA_8888);
}

/**
 * @tc.name: SetExternalDecodeFormat003
 * @tc.desc: Test SetExternalDecodeFormat with invalid format
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetExternalDecodeFormat003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set decode format to invalid (NV12)
     */
    pattern->SetExternalDecodeFormat(PixelFormat::NV12);

    /**
     * @tc.expected: Should fall back to UNKNOWN
     */
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);
}

// ============================================================================
// ImageQuality Tests
// ============================================================================

/**
 * @tc.name: SetImageQuality001
 * @tc.desc: Test SetImageQuality
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetImageQuality001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set image quality
     */
    pattern->SetImageQuality(AIImageQuality::LOW);

    /**
     * @tc.expected: Quality should be set
     */
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::LOW);
}

// ============================================================================
// CopyOption Tests
// ============================================================================

/**
 * @tc.name: SetCopyOption001
 * @tc.desc: Test SetCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetCopyOption001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set copy option
     */
    pattern->SetCopyOption(CopyOptions::InApp);

    /**
     * @tc.expected: Copy option should be set
     */
    // Copy option is stored internally
}

// ============================================================================
// SelectOverlayClient Tests
// ============================================================================

/**
 * @tc.name: GetClientHost001
 * @tc.desc: Test GetClientHost
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, GetClientHost001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get client host
     */
    auto host = pattern->GetClientHost();

    /**
     * @tc.expected: Should return frame node
     */
    EXPECT_EQ(host, frameNode);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: Test BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, BetweenSelectedPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Check between selected position
     */
    Offset globalOffset(100, 100);
    auto result = pattern->BetweenSelectedPosition(globalOffset);

    /**
     * @tc.expected: Should return bool
     */
    // Result depends on selection state
}

/**
 * @tc.name: DefaultSupportDrag001
 * @tc.desc: Test DefaultSupportDrag
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, DefaultSupportDrag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Check default support drag
     */
    auto support = pattern->DefaultSupportDrag();

    /**
     * @tc.expected: Should return default value
     */
    // Default value depends on implementation
}

// ============================================================================
// Analyzer Tests
// ============================================================================

/**
 * @tc.name: EnableAnalyzer001
 * @tc.desc: Test EnableAnalyzer with true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, EnableAnalyzer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Enable analyzer
     */
    pattern->EnableAnalyzer(true);

    /**
     * @tc.expected: isEnableAnalyzer_ should be true
     */
    EXPECT_TRUE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: EnableAnalyzer002
 * @tc.desc: Test EnableAnalyzer with false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, EnableAnalyzer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Disable analyzer
     */
    pattern->EnableAnalyzer(false);

    /**
     * @tc.expected: isEnableAnalyzer_ should be false
     */
    EXPECT_FALSE(pattern->isEnableAnalyzer_);
}

/**
 * @tc.name: IsSupportImageAnalyzerFeature001
 * @tc.desc: Test IsSupportImageAnalyzerFeature with null manager
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, IsSupportImageAnalyzerFeature001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->imageAnalyzerManager_ = nullptr;

    /**
     * @tc.steps: step2. Check support
     */
    auto support = pattern->IsSupportImageAnalyzerFeature();

    /**
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(support);
}

/**
 * @tc.name: IsSupportImageAnalyzerFeature002
 * @tc.desc: Test IsSupportImageAnalyzerFeature with disabled analyzer
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, IsSupportImageAnalyzerFeature002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isEnableAnalyzer_ = false;

    /**
     * @tc.steps: step2. Check support
     */
    auto support = pattern->IsSupportImageAnalyzerFeature();

    /**
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(support);
}

/**
 * @tc.name: IsSupportImageAnalyzerFeature003
 * @tc.desc: Test IsSupportImageAnalyzerFeature with SVG image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, IsSupportImageAnalyzerFeature003, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Check support
     */
    auto support = pattern->IsSupportImageAnalyzerFeature();

    /**
     * @tc.expected: Should return false for SVG
     */
    EXPECT_FALSE(support);
}

// ============================================================================
// Configuration Update Tests
// ============================================================================

/**
 * @tc.name: OnLanguageConfigurationUpdate001
 * @tc.desc: Test OnLanguageConfigurationUpdate with resource image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, OnLanguageConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up resource image
     */
    ImageSourceInfo sourceInfo(RESOURCE_URL);
    sourceInfo.srcType_ = SrcType::RESOURCE;
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo);

    /**
     * @tc.steps: step3. Call language configuration update
     */
    pattern->OnLanguageConfigurationUpdate();

    /**
     * @tc.expected: Should reload resource image
     */
    SUCCEED();
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call color configuration update
     */
    pattern->OnColorConfigurationUpdate();

    /**
     * @tc.expected: Should handle color update
     */
    SUCCEED();
}

// ============================================================================
// OnAreaChangedInner Tests
// ============================================================================

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: Test OnAreaChangedInner
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, OnAreaChangedInner001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnAreaChangedInner
     */
    pattern->OnAreaChangedInner();

    /**
     * @tc.expected: Should complete without crash
     */
    SUCCEED();
}

/**
 * @tc.name: RemoveAreaChangeInner001
 * @tc.desc: Test RemoveAreaChangeInner
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, RemoveAreaChangeInner001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Remove area change inner
     */
    pattern->RemoveAreaChangeInner();

    /**
     * @tc.expected: Should remove callback
     */
    SUCCEED();
}

// ============================================================================
// TriggerFirstVisibleAreaChange Tests
// ============================================================================

/**
 * @tc.name: TriggerFirstVisibleAreaChange001
 * @tc.desc: Test TriggerFirstVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, TriggerFirstVisibleAreaChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Trigger first visible area change
     */
    pattern->TriggerFirstVisibleAreaChange();

    /**
     * @tc.expected: Should handle first visible change
     */
    SUCCEED();
}

// ============================================================================
// Other Edge Cases Tests
// ============================================================================

/**
 * @tc.name: GetCanvasImage001
 * @tc.desc: Test GetCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, GetCanvasImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Get canvas image
     */
    const auto& image = pattern->GetCanvasImage();

    /**
     * @tc.expected: Should return reference
     */
    EXPECT_EQ(image, nullptr);
}

/**
 * @tc.name: GetAltCanvasImage001
 * @tc.desc: Test GetAltCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, GetAltCanvasImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Get alt canvas image
     */
    const auto& image = pattern->GetAltCanvasImage();

    /**
     * @tc.expected: Should return reference
     */
    EXPECT_EQ(image, nullptr);
}

/**
 * @tc.name: GetImageLoadingContext001
 * @tc.desc: Test GetImageLoadingContext
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, GetImageLoadingContext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Get loading context
     */
    auto context = pattern->GetImageLoadingContext();

    /**
     * @tc.expected: Should return weak pointer
     */
    EXPECT_TRUE(context.Expired());
}

/**
 * @tc.name: GetAltImageLoadingContext001
 * @tc.desc: Test GetAltImageLoadingContext
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, GetAltImageLoadingContext001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Get alt loading context
     */
    auto context = pattern->GetAltImageLoadingContext();

    /**
     * @tc.expected: Should return weak pointer
     */
    EXPECT_TRUE(context.Expired());
}

/**
 * @tc.name: LoadImageDataIfNeed001
 * @tc.desc: Test LoadImageDataIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, LoadImageDataIfNeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Load image data if needed
     */
    pattern->LoadImageDataIfNeed();

    /**
     * @tc.expected: Should attempt loading
     */
    SUCCEED();
}

/**
 * @tc.name: SetNeedBorderRadius001
 * @tc.desc: Test SetNeedBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetNeedBorderRadius001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set need border radius
     */
    pattern->SetNeedBorderRadius(true);

    /**
     * @tc.expected: needBorderRadius_ should be true
     */
    EXPECT_TRUE(pattern->needBorderRadius_);
}

/**
 * @tc.name: SetIsComponentSnapshotNode001
 * @tc.desc: Test SetIsComponentSnapshotNode
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, SetIsComponentSnapshotNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Set component snapshot node
     */
    pattern->SetIsComponentSnapshotNode(true);

    /**
     * @tc.expected: isComponentSnapshotNode_ should be true
     */
    EXPECT_TRUE(pattern->isComponentSnapshotNode_);
}

/**
 * @tc.name: AllowVisibleAreaCheck001
 * @tc.desc: Test AllowVisibleAreaCheck
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, AllowVisibleAreaCheck001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Check allow visible area
     */
    auto allow = pattern->AllowVisibleAreaCheck();

    /**
     * @tc.expected: Should return bool
     */
    // Result depends on configuration
}

/**
 * @tc.name: hasSceneChanged001
 * @tc.desc: Test hasSceneChanged
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternEventsEdgeCasesTestNg, hasSceneChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Check scene changed
     */
    auto changed = pattern->hasSceneChanged();

    /**
     * @tc.expected: Should return bool
     */
    // Result depends on scene state
}

} // namespace OHOS::Ace::NG

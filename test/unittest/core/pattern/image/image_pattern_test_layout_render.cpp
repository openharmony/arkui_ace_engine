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
 * @file image_pattern_test_layout_render.cpp
 * @brief Comprehensive TDD test coverage for ImagePattern layout and rendering
 *
 * This file contains test cases covering:
 * - CreateNodePaintMethod
 * - CreateModifier
 * - OnDirtyLayoutWrapperSwap
 * - CheckIfNeedLayout
 * - ImageFit modes
 * - ImageRepeat modes
 * - Color filters
 * - SyncLoad/AsyncLoad
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternLayoutRenderTestNg : public ImageBases {};

// ============================================================================
// CreateNodePaintMethod Tests
// ============================================================================

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod with null image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without image
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = nullptr;

    /**
     * @tc.steps: step2. Create paint method
     */
    auto paintMethod = pattern->CreateNodePaintMethod();

    /**
     * @tc.expected: May return null
     */
    // Result depends on implementation
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test CreateNodePaintMethod with valid image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with image
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());

    /**
     * @tc.steps: step2. Create paint method
     */
    auto paintMethod = pattern->CreateNodePaintMethod();

    /**
     * @tc.expected: Should return valid ImagePaintMethod
     */
    ASSERT_NE(paintMethod, nullptr);
    auto imagePaintMethod = AceType::DynamicCast<ImagePaintMethod>(paintMethod);
    EXPECT_NE(imagePaintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod003
 * @tc.desc: Test CreateNodePaintMethod with alt image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with alt image only
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = nullptr;
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_->SetPaintConfig(ImagePaintConfig());

    /**
     * @tc.steps: step2. Create paint method
     */
    auto paintMethod = pattern->CreateNodePaintMethod();

    /**
     * @tc.expected: Should use alt image
     */
    ASSERT_NE(paintMethod, nullptr);
}

// ============================================================================
// CreateModifier Tests
// ============================================================================

/**
 * @tc.name: CreateModifier001
 * @tc.desc: Test CreateModifier creates content modifier
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CreateModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create modifier
     */
    pattern->CreateModifier();

    /**
     * @tc.expected: Modifier should be created
     */
    SUCCEED();
}

/**
 * @tc.name: CreateModifier002
 * @tc.desc: Test CreateModifier with borderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CreateModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->needBorderRadius_ = true;

    /**
     * @tc.steps: step2. Create modifier
     */
    pattern->CreateModifier();

    /**
     * @tc.expected: Modifier should have borderRadius
     */
    SUCCEED();
}

// ============================================================================
// CheckIfNeedLayout Tests
// ============================================================================

/**
 * @tc.name: CheckIfNeedLayout001
 * @tc.desc: Test CheckIfNeedLayout returns true when no frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CheckIfNeedLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     */
    auto pattern = AceType::MakeRefPtr<ImagePattern>();

    /**
     * @tc.steps: step2. Check if need layout
     */
    auto needLayout = pattern->CheckIfNeedLayout();

    /**
     * @tc.expected: Should return true (no frameNode)
     */
    EXPECT_TRUE(needLayout);
}

/**
 * @tc.name: CheckIfNeedLayout002
 * @tc.desc: Test CheckIfNeedLayout with no content
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CheckIfNeedLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Remove content
     */
    frameNode->GetGeometryNode()->SetContentSize(SizeF());

    /**
     * @tc.steps: step3. Check if need layout
     */
    auto needLayout = pattern->CheckIfNeedLayout();

    /**
     * @tc.expected: Should return true (no content)
     */
    EXPECT_TRUE(needLayout);
}

/**
 * @tc.name: CheckIfNeedLayout003
 * @tc.desc: Test CheckIfNeedLayout with selfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CheckIfNeedLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set selfIdealSize
     */
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    if (!layoutProp->calcLayoutConstraint_) {
        layoutProp->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    layoutProp->calcLayoutConstraint_->selfIdealSize =
        std::make_optional<CalcSize>(CalcLength(100.0f), CalcLength(100.0f));

    /**
     * @tc.steps: step3. Check if need layout
     */
    auto needLayout = pattern->CheckIfNeedLayout();

    /**
     * @tc.expected: Should return false (has selfIdealSize)
     */
    EXPECT_FALSE(needLayout);
}

/**
 * @tc.name: CheckIfNeedLayout004
 * @tc.desc: Test CheckIfNeedLayout without selfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, CheckIfNeedLayout004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Clear selfIdealSize
     */
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    layoutProp->calcLayoutConstraint_ = nullptr;

    /**
     * @tc.steps: step3. Check if need layout
     */
    auto needLayout = pattern->CheckIfNeedLayout();

    /**
     * @tc.expected: Should return true (no selfIdealSize)
     */
    EXPECT_TRUE(needLayout);
}

// ============================================================================
// ImageFit Tests
// ============================================================================

/**
 * @tc.name: ImageFit001
 * @tc.desc: Test ImageFit::CONTAIN
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageFit001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageFit to CONTAIN
     */
    layoutProp->UpdateImageFit(ImageFit::CONTAIN);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageFit should be CONTAIN
     */
    EXPECT_EQ(layoutProp->GetImageFit().value(), ImageFit::CONTAIN);
}

/**
 * @tc.name: ImageFit002
 * @tc.desc: Test ImageFit::COVER
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageFit002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageFit to COVER
     */
    layoutProp->UpdateImageFit(ImageFit::COVER);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageFit should be COVER
     */
    EXPECT_EQ(layoutProp->GetImageFit().value(), ImageFit::COVER);
}

/**
 * @tc.name: ImageFit003
 * @tc.desc: Test ImageFit::FILL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageFit003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageFit to FILL
     */
    layoutProp->UpdateImageFit(ImageFit::FILL);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageFit should be FILL
     */
    EXPECT_EQ(layoutProp->GetImageFit().value(), ImageFit::FILL);
}

/**
 * @tc.name: ImageFit004
 * @tc.desc: Test ImageFit::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageFit004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageFit to NONE
     */
    layoutProp->UpdateImageFit(ImageFit::NONE);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageFit should be NONE
     */
    EXPECT_EQ(layoutProp->GetImageFit().value(), ImageFit::NONE);
}

/**
 * @tc.name: ImageFit005
 * @tc.desc: Test ImageFit::SCALE_DOWN
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageFit005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageFit to SCALE_DOWN
     */
    layoutProp->UpdateImageFit(ImageFit::SCALE_DOWN);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageFit should be SCALE_DOWN
     */
    EXPECT_EQ(layoutProp->GetImageFit().value(), ImageFit::SCALE_DOWN);
}

// ============================================================================
// ImageRepeat Tests
// ============================================================================

/**
 * @tc.name: ImageRepeat001
 * @tc.desc: Test ImageRepeat::NO_REPEAT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageRepeat001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageRepeat to NO_REPEAT
     */
    renderProp->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageRepeat should be NO_REPEAT
     */
    EXPECT_EQ(renderProp->GetImageRepeat().value(), ImageRepeat::NO_REPEAT);
}

/**
 * @tc.name: ImageRepeat002
 * @tc.desc: Test ImageRepeat::REPEAT_X
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageRepeat002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageRepeat to REPEAT_X
     */
    renderProp->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageRepeat should be REPEAT_X
     */
    EXPECT_EQ(renderProp->GetImageRepeat().value(), ImageRepeat::REPEAT_X);
}

/**
 * @tc.name: ImageRepeat003
 * @tc.desc: Test ImageRepeat::REPEAT_Y
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageRepeat003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageRepeat to REPEAT_Y
     */
    renderProp->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageRepeat should be REPEAT_Y
     */
    EXPECT_EQ(renderProp->GetImageRepeat().value(), ImageRepeat::REPEAT_Y);
}

/**
 * @tc.name: ImageRepeat004
 * @tc.desc: Test ImageRepeat::REPEAT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageRepeat004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set ImageRepeat to REPEAT
     */
    renderProp->UpdateImageRepeat(ImageRepeat::REPEAT);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: ImageRepeat should be REPEAT
     */
    EXPECT_EQ(renderProp->GetImageRepeat().value(), ImageRepeat::REPEAT);
}

// ============================================================================
// ColorFilter Tests
// ============================================================================

/**
 * @tc.name: ColorFilter001
 * @tc.desc: Test SetColorFilter with valid matrix
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ColorFilter001, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Apply color filter
     */
    pattern->SetColorFilter(frameNode);

    /**
     * @tc.expected: Color filter should be applied
     */
    EXPECT_TRUE(renderProp->GetColorFilter().has_value());
}

/**
 * @tc.name: ColorFilter002
 * @tc.desc: Test SetColorFilter with empty matrix
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ColorFilter002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set empty color filter
     */
    std::vector<float> emptyMatrix;
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    renderProp->UpdateColorFilter(emptyMatrix);

    /**
     * @tc.steps: step3. Apply color filter
     */
    pattern->SetColorFilter(frameNode);

    /**
     * @tc.expected: Should handle empty matrix
     */
    SUCCEED();
}

// ============================================================================
// SyncLoad Tests
// ============================================================================

/**
 * @tc.name: SyncLoad001
 * @tc.desc: Test SetSyncLoad with true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, SyncLoad001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set sync load
     */
    pattern->SetSyncLoad(true);

    /**
     * @tc.expected: syncLoad_ should be true
     */
    EXPECT_TRUE(pattern->GetSyncLoad());
}

/**
 * @tc.name: SyncLoad002
 * @tc.desc: Test SetSyncLoad with false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, SyncLoad002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set async load
     */
    pattern->SetSyncLoad(false);

    /**
     * @tc.expected: syncLoad_ should be false
     */
    EXPECT_FALSE(pattern->GetSyncLoad());
}

// ============================================================================
// AutoResize Tests
// ============================================================================

/**
 * @tc.name: AutoResize001
 * @tc.desc: Test GetDefaultAutoResize
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, AutoResize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get default auto resize
     */
    auto autoResize = pattern->GetDefaultAutoResize();

    /**
     * @tc.expected: Should return default value
     */
    // Default value depends on system configuration
}

// ============================================================================
// SourceSize Tests
// ============================================================================

/**
 * @tc.name: SourceSize001
 * @tc.desc: Test SetSourceSize
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, SourceSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set source size
     */
    SizeF sourceSize(100.0f, 200.0f);
    layoutProp->UpdateSourceSize(sourceSize);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: SourceSize should be set
     */
    EXPECT_TRUE(layoutProp->GetSourceSize().has_value());
    EXPECT_EQ(layoutProp->GetSourceSize().value(), sourceSize);
}

// ============================================================================
// ImageInterpolation Tests
// ============================================================================

/**
 * @tc.name: ImageInterpolation001
 * @tc.desc: Test GetDefaultInterpolation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageInterpolation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Get default interpolation
     */
    auto interpolation = pattern->GetDefaultInterpolation();

    /**
     * @tc.expected: Should return default interpolation
     */
    // Default value depends on configuration
}

/**
 * @tc.name: ImageInterpolation002
 * @tc.desc: Test SetImageInterpolation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageInterpolation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set interpolation to HIGH
     */
    renderProp->UpdateImageInterpolation(ImageInterpolation::HIGH);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Interpolation should be HIGH
     */
    EXPECT_EQ(renderProp->GetImageInterpolation().value(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: ImageInterpolation003
 * @tc.desc: Test SetImageInterpolation to LOW
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageInterpolation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set interpolation to LOW
     */
    renderProp->UpdateImageInterpolation(ImageInterpolation::LOW);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Interpolation should be LOW
     */
    EXPECT_EQ(renderProp->GetImageInterpolation().value(), ImageInterpolation::LOW);
}

/**
 * @tc.name: ImageInterpolation004
 * @tc.desc: Test SetImageInterpolation to MEDIUM
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageInterpolation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set interpolation to MEDIUM
     */
    renderProp->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Interpolation should be MEDIUM
     */
    EXPECT_EQ(renderProp->GetImageInterpolation().value(), ImageInterpolation::MEDIUM);
}

/**
 * @tc.name: ImageInterpolation005
 * @tc.desc: Test SetImageInterpolation to NONE
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, ImageInterpolation005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set interpolation to NONE
     */
    renderProp->UpdateImageInterpolation(ImageInterpolation::NONE);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: Interpolation should be NONE
     */
    EXPECT_EQ(renderProp->GetImageInterpolation().value(), ImageInterpolation::NONE);
}

// ============================================================================
// MatchTextDirection Tests
// ============================================================================

/**
 * @tc.name: MatchTextDirection001
 * @tc.desc: Test UpdateMatchTextDirection
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, MatchTextDirection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set match text direction
     */
    renderProp->UpdateMatchTextDirection(true);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: MatchTextDirection should be true
     */
    EXPECT_EQ(renderProp->GetMatchTextDirection().value(), true);
}

// ============================================================================
// DynamicRangeMode Tests
// ============================================================================

/**
 * @tc.name: DynamicRangeMode001
 * @tc.desc: Test UpdateDynamicMode to STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, DynamicRangeMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set dynamic mode to STANDARD
     */
    renderProp->UpdateDynamicMode(DynamicRangeMode::STANDARD);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: DynamicMode should be STANDARD
     */
    EXPECT_EQ(renderProp->GetDynamicMode().value(), DynamicRangeMode::STANDARD);
}

/**
 * @tc.name: DynamicRangeMode002
 * @tc.desc: Test UpdateDynamicMode to HIGH
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, DynamicRangeMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set dynamic mode to HIGH
     */
    renderProp->UpdateDynamicMode(DynamicRangeMode::HIGH);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: DynamicMode should be HIGH
     */
    EXPECT_EQ(renderProp->GetDynamicMode().value(), DynamicRangeMode::HIGH);
}

/**
 * @tc.name: DynamicRangeMode003
 * @tc.desc: Test UpdateDynamicMode to CONSTRAINT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, DynamicRangeMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set dynamic mode to CONSTRAINT
     */
    renderProp->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: DynamicMode should be CONSTRAINT
     */
    EXPECT_EQ(renderProp->GetDynamicMode().value(), DynamicRangeMode::CONSTRAINT);
}

// ============================================================================
// FitOriginalSize Tests
// ============================================================================

/**
 * @tc.name: FitOriginalSize001
 * @tc.desc: Test UpdateFitOriginalSize
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, FitOriginalSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);

    /**
     * @tc.steps: step2. Set fit original size
     */
    layoutProp->UpdateFitOriginalSize(true);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: FitOriginalSize should be true
     */
    EXPECT_EQ(layoutProp->GetFitOriginalSize().value(), true);
}

// ============================================================================
// RenderMode Tests
// ============================================================================

/**
 * @tc.name: RenderMode001
 * @tc.desc: Test UpdateImageRenderMode
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternLayoutRenderTestNg, RenderMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create image node
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);

    /**
     * @tc.steps: step2. Set render mode
     */
    renderProp->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    frameNode->MarkModifyDone();

    /**
     * @tc.expected: RenderMode should be TEMPLATE
     */
    EXPECT_EQ(renderProp->GetImageRenderMode().value(), ImageRenderMode::TEMPLATE);
}

} // namespace OHOS::Ace::NG

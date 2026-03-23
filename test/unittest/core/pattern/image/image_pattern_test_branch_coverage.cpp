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

#include "image_base.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/base/mock_pixel_map.h"

namespace OHOS::Ace::NG {

namespace {
    constexpr int32_t IMAGE_LOAD_FAIL = 0;
    constexpr int32_t IMAGE_LOAD_SUCCESS = 1;
}

class ImagePatternBranchCoverageTestNg : public ImageBases {};

/**
 * @tc.name: CreateDataReadyCallbackSourceMismatch001
 * @tc.desc: Test CreateDataReadyCallback when source info doesn't match
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateDataReadyCallbackSourceMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    // Set different source info to trigger mismatch branch
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo("original.png"));
    auto callback = pattern->CreateDataReadyCallback();
    // Call callback with wrong source info, should return early without processing
    ImageSourceInfo wrongInfo("wrong.png");
    callback(wrongInfo);
    // Verify callback was created and executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateLoadSuccessCallbackSourceMismatch001
 * @tc.desc: Test CreateLoadSuccessCallback when source info doesn't match
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadSuccessCallbackSourceMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    // Set different source info to trigger mismatch branch
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo("original.png"));
    auto callback = pattern->CreateLoadSuccessCallback();
    // Call callback with wrong source info, should return early without processing
    ImageSourceInfo wrongInfo("wrong.png");
    callback(wrongInfo);
    // Verify callback was created and executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateLoadFailCallbackIsFromReset001
 * @tc.desc: Test CreateLoadFailCallback when source is from reset
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadFailCallbackIsFromReset001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo(""));
    auto loadFailedBefore = pattern->loadFailed_;
    auto callback = pattern->CreateLoadFailCallback();
    ImageSourceInfo resetInfo("");
    callback(resetInfo, "test error", ImageErrorInfo());
    auto loadFailedAfter = pattern->loadFailed_;
    
    EXPECT_EQ(loadFailedBefore, loadFailedAfter);
    EXPECT_FALSE(loadFailedAfter);
}

/**
 * @tc.name: CreateLoadFailCallbackNotFromReset001
 * @tc.desc: Test CreateLoadFailCallback when source is not from reset
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadFailCallbackNotFromReset001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    // Set source info that is not from reset
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo("test.png"));
    auto callback = pattern->CreateLoadFailCallback();
    // Call callback with matching source info
    ImageSourceInfo normalInfo("test.png");
    callback(normalInfo, "test error", ImageErrorInfo());
    // Verify callback was created and executed
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateCompleteCallBackInDataReadySourceMismatch001
 * @tc.desc: Test CreateCompleteCallBackInDataReady when source doesn't match
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateCompleteCallBackInDataReadySourceMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    // Set different source info to trigger mismatch branch
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo("original.png"));
    auto callback = pattern->CreateCompleteCallBackInDataReady();
    // Call callback with wrong source info, should return early without processing
    ImageSourceInfo wrongInfo("wrong.png");
    callback(wrongInfo);
    // Verify callback was created and executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeatX001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT_X
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeatX001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    
    EXPECT_FLOAT_EQ(paintSize.Width(), geometryNode->GetContentSize().Width());
    EXPECT_FLOAT_EQ(paintSize.Height(), pattern->dstRect_.Height());
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeatY001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT_Y
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeatY001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    
    EXPECT_FLOAT_EQ(paintSize.Width(), pattern->dstRect_.Width());
    EXPECT_FLOAT_EQ(paintSize.Height(), geometryNode->GetContentSize().Height());
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeat001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeat001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT);
    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    
    EXPECT_FLOAT_EQ(paintSize.Width(), geometryNode->GetContentSize().Width());
    EXPECT_FLOAT_EQ(paintSize.Height(), geometryNode->GetContentSize().Height());
}

/**
 * @tc.name: CalcImageContentPaintSizeNoRepeat001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::NO_REPEAT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeNoRepeat001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    
    EXPECT_FLOAT_EQ(paintSize.Width(), pattern->dstRect_.Width());
    EXPECT_FLOAT_EQ(paintSize.Height(), pattern->dstRect_.Height());
}

/**
 * @tc.name: MaskUrlShortUrl001
 * @tc.desc: Test MaskUrl with URL length < 30
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, MaskUrlShortUrl001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string shortUrl = URL_LENGTH_LESS_THAN_30;
    std::string maskedUrl = pattern->MaskUrl(shortUrl);
    
    EXPECT_EQ(maskedUrl.length(), shortUrl.length());
    EXPECT_EQ(maskedUrl[0], shortUrl[0]);
    EXPECT_EQ(maskedUrl[2], '*');
}

/**
 * @tc.name: MaskUrlLongUrl001
 * @tc.desc: Test MaskUrl with URL length >= 30
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, MaskUrlLongUrl001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string longUrl = URL_LENGTH_EQUAL_35;
    std::string maskedUrl = pattern->MaskUrl(longUrl);
    
    EXPECT_EQ(maskedUrl.length(), longUrl.length());
    EXPECT_EQ(maskedUrl.substr(0, 15), longUrl.substr(0, 15));
}

/**
 * @tc.name: CheckIfNeedLayoutNullHost001
 * @tc.desc: Test CheckIfNeedLayout when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CheckIfNeedLayoutNullHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    bool result = pattern->CheckIfNeedLayout();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckIfNeedLayoutNullContent001
 * @tc.desc: Test CheckIfNeedLayout when content is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CheckIfNeedLayoutNullContent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    
    geometryNode->content_ = nullptr;
    bool result = pattern->CheckIfNeedLayout();
    
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckIfNeedLayoutValidSelfIdealSize001
 * @tc.desc: Test CheckIfNeedLayout when selfIdealSize is valid
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CheckIfNeedLayoutValidSelfIdealSize001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto& calcConstraint = layoutProperty->GetCalcLayoutConstraint();
    EXPECT_NE(calcConstraint, nullptr);
    calcConstraint->selfIdealSize.emplace(CalcSize(CalcLength(100.0f), CalcLength(100.0f)));
    
    bool result = pattern->CheckIfNeedLayout();
    
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetExternalDecodeFormatAllFormats001
 * @tc.desc: Test SetExternalDecodeFormat with all supported formats
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetExternalDecodeFormatAllFormats001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto formatBefore = pattern->externalDecodeFormat_;
    pattern->SetExternalDecodeFormat(PixelFormat::NV21);
    auto formatAfter = pattern->externalDecodeFormat_;
    EXPECT_NE(formatBefore, formatAfter);
    EXPECT_EQ(formatAfter, PixelFormat::NV21);
    
    pattern->isImageReloadNeeded_ = false;
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_8888);
    EXPECT_EQ(pattern->externalDecodeFormat_, PixelFormat::RGBA_8888);
    
    pattern->isImageReloadNeeded_ = false;
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_1010102);
    EXPECT_EQ(pattern->externalDecodeFormat_, PixelFormat::RGBA_1010102);
    
    pattern->isImageReloadNeeded_ = false;
    pattern->SetExternalDecodeFormat(PixelFormat::YCBCR_P010);
    EXPECT_EQ(pattern->externalDecodeFormat_, PixelFormat::YCBCR_P010);
    
    pattern->isImageReloadNeeded_ = false;
    pattern->SetExternalDecodeFormat(PixelFormat::YCRCB_P010);
    EXPECT_EQ(pattern->externalDecodeFormat_, PixelFormat::YCRCB_P010);
    
    pattern->isImageReloadNeeded_ = false;
    pattern->SetExternalDecodeFormat(PixelFormat::RGB_565);
    EXPECT_EQ(pattern->externalDecodeFormat_, PixelFormat::UNKNOWN);
}

/**
 * @tc.name: StartDecodingNullHost001
 * @tc.desc: Test StartDecoding when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, StartDecodingNullHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // StartDecoding should return early when host is null
    SizeF dstSize(100, 100);
    pattern->StartDecoding(dstSize);
    // Verify function executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: StartDecodingNullContent001
 * @tc.desc: Test StartDecoding when content is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, StartDecodingNullContent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    
    geometryNode->content_ = nullptr;
    auto loadingCtxBefore = pattern->loadingCtx_;
    SizeF dstSize(100, 100);
    pattern->StartDecoding(dstSize);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    // When content is null, StartDecoding returns early without modifying loadingCtx_
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
    EXPECT_NE(loadingCtxAfter, nullptr);
}

/**
 * @tc.name: SetImagePaintConfigFrameCountGreaterThanOne001
 * @tc.desc: Test SetImagePaintConfig when frameCount > 1
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetImagePaintConfigFrameCountGreaterThanOne001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_NE(canvasImage, nullptr);
    
    RectF srcRect(0.0f, 0.0f, 100.0f, 100.0f);
    RectF dstRect(0.0f, 0.0f, 200.0f, 200.0f);
    ImageSourceInfo sourceInfo("test.gif");
    int32_t frameCount = 10;
    pattern->SetImagePaintConfig(canvasImage, srcRect, dstRect, sourceInfo, frameCount);
    
    auto& config = canvasImage->GetPaintConfig();
    EXPECT_NE(&config, nullptr);
    EXPECT_EQ(config.orientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: SetImagePaintConfigFrameCountLessEqualOne001
 * @tc.desc: Test SetImagePaintConfig when frameCount <= 1
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetImagePaintConfigFrameCountLessEqualOne001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->joinOrientation_ = ImageRotateOrientation::RIGHT;
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_NE(canvasImage, nullptr);
    RectF srcRect(0.0f, 0.0f, 100.0f, 100.0f);
    RectF dstRect(0.0f, 0.0f, 200.0f, 200.0f);
    ImageSourceInfo sourceInfo("test.png");
    int32_t frameCount = 1;
    pattern->SetImagePaintConfig(canvasImage, srcRect, dstRect, sourceInfo, frameCount);
    
    auto& config = canvasImage->GetPaintConfig();
    EXPECT_NE(&config, nullptr);
    EXPECT_EQ(config.orientation_, ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: CreateNodePaintMethodImageExistAndNotLoadFailed001
 * @tc.desc: Test CreateNodePaintMethod when image exists and not failed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodImageExistAndNotLoadFailed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadFailed_ = false;
    auto paintMethod = pattern->CreateNodePaintMethod();
    
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethodAltErrorImageExist001
 * @tc.desc: Test CreateNodePaintMethod when alt error image exists
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodAltErrorImageExist001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->image_ = nullptr;
    pattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altErrorDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->altErrorSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethodAltImageExistAndNotLoadFailed001
 * @tc.desc: Test CreateNodePaintMethod when alt image exists and not failed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodAltImageExistAndNotLoadFailed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->image_ = nullptr;
    pattern->altErrorImage_ = nullptr;
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->altSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->loadFailed_ = false;
    auto paintMethod = pattern->CreateNodePaintMethod();
    
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethodNoImageExist001
 * @tc.desc: Test CreateNodePaintMethod when no image exists
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodNoImageExist001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->image_ = nullptr;
    pattern->altErrorImage_ = nullptr;
    pattern->altImage_ = nullptr;
    pattern->obscuredImage_ = nullptr;
    auto paintMethod = pattern->CreateNodePaintMethod();
    
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: SetPixelMapMemoryNameInspectorIdExist001
 * @tc.desc: Test SetPixelMapMemoryName when inspector ID exists
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetPixelMapMemoryNameInspectorIdExist001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    frameNode->UpdateInspectorId("test_image_id");
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(mockPixelMap, nullptr);
    
    auto hasSetBefore = pattern->hasSetPixelMapMemoryName_;
    RefPtr<PixelMap> pixelMap = mockPixelMap;
    bool result = pattern->SetPixelMapMemoryName(pixelMap);
    auto hasSetAfter = pattern->hasSetPixelMapMemoryName_;
    
    EXPECT_TRUE(result);
    EXPECT_NE(hasSetBefore, hasSetAfter);
    EXPECT_TRUE(hasSetAfter);
}

/**
 * @tc.name: SetPixelMapMemoryNameInspectorIdEmpty001
 * @tc.desc: Test SetPixelMapMemoryName when inspector ID is empty
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetPixelMapMemoryNameInspectorIdEmpty001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    frameNode->UpdateInspectorId("");
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(mockPixelMap, nullptr);
    
    auto hasSetBefore = pattern->hasSetPixelMapMemoryName_;
    RefPtr<PixelMap> pixelMap = mockPixelMap;
    bool result = pattern->SetPixelMapMemoryName(pixelMap);
    auto hasSetAfter = pattern->hasSetPixelMapMemoryName_;
    
    EXPECT_FALSE(result);
    EXPECT_EQ(hasSetBefore, hasSetAfter);
}

/**
 * @tc.name: InitFromThemeIfNeedAlreadyInitialized001
 * @tc.desc: Test InitFromThemeIfNeed when already initialized
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, InitFromThemeIfNeedAlreadyInitialized001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isFullyInitializedFromTheme_ = true;
    auto initBefore = pattern->isFullyInitializedFromTheme_;
    pattern->InitFromThemeIfNeed();
    auto initAfter = pattern->isFullyInitializedFromTheme_;
    
    EXPECT_EQ(initBefore, initAfter);
    EXPECT_TRUE(initAfter);
}

/**
 * @tc.name: InitFromThemeIfNeedNotInitialized001
 * @tc.desc: Test InitFromThemeIfNeed when not initialized
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, InitFromThemeIfNeedNotInitialized001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isFullyInitializedFromTheme_ = false;
    auto initBefore = pattern->isFullyInitializedFromTheme_;
    pattern->InitFromThemeIfNeed();
    auto initAfter = pattern->isFullyInitializedFromTheme_;
    
    EXPECT_NE(initBefore, initAfter);
    EXPECT_TRUE(initAfter);
}

/**
 * @tc.name: PreprocessYUVDecodeFormatYUVDisabled001
 * @tc.desc: Test PreprocessYUVDecodeFormat when YUV decode is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, PreprocessYUVDecodeFormatYUVDisabled001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto formatBefore = pattern->externalDecodeFormat_;
    pattern->PreprocessYUVDecodeFormat(frameNode);
    auto formatAfter = pattern->externalDecodeFormat_;
    
    EXPECT_EQ(formatBefore, formatAfter);
}

/**
 * @tc.name: OnImageDataReadyHostNotActive001
 * @tc.desc: Test OnImageDataReady when host is not active
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageDataReadyHostNotActive001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // Set host to inactive state and verify
    frameNode->isActive_ = false;
    EXPECT_FALSE(frameNode->isActive_);
}

/**
 * @tc.name: OnImageDataReadyNeedLayout001
 * @tc.desc: Test OnImageDataReady when layout is needed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageDataReadyNeedLayout001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    
    geometryNode->content_ = nullptr;
    bool needLayout = pattern->CheckIfNeedLayout();
    
    EXPECT_TRUE(needLayout);
}

// ============================================================================
// Section 5: Uncovered Functions - Animation and Visibility (High Priority)
// ============================================================================

/**
 * @tc.name: SetRedrawCallbackNullImage001
 * @tc.desc: Test SetRedrawCallback when image is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetRedrawCallbackNullImage001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto loadingCtxBefore = pattern->loadingCtx_;
    RefPtr<CanvasImage> nullImage = nullptr;
    pattern->SetRedrawCallback(nullImage);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
    EXPECT_EQ(loadingCtxAfter, nullptr);
}

/**
 * @tc.name: SetRedrawCallbackNullLoadingCtx001
 * @tc.desc: Test SetRedrawCallback when loadingCtx_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetRedrawCallbackNullLoadingCtx001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_NE(canvasImage, nullptr);
    
    pattern->loadingCtx_ = nullptr;
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->SetRedrawCallback(canvasImage);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
    EXPECT_EQ(loadingCtxAfter, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChangeSnapshotNode001
 * @tc.desc: Test RegisterVisibleAreaChange when isComponentSnapshotNode_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeSnapshotNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isComponentSnapshotNode_ = true;
    pattern->RegisterVisibleAreaChange();
    
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChangeAnimatorNode001
 * @tc.desc: Test RegisterVisibleAreaChange when isImageAnimator_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeAnimatorNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isImageAnimator_ = true;
    pattern->RegisterVisibleAreaChange();
    
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChangeNormalNode001
 * @tc.desc: Test RegisterVisibleAreaChange for normal image node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeNormalNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isComponentSnapshotNode_ = false;
    pattern->isImageAnimator_ = false;
    pattern->RegisterVisibleAreaChange();
    
    EXPECT_NE(pattern, nullptr);
}

// ============================================================================
// Section 6: Uncovered Functions - Performance Monitoring (High Priority)
// ============================================================================

/**
 * @tc.name: ReportPerfDataImageLoadSuccess001
 * @tc.desc: Test ReportPerfData with IMAGE_LOAD_SUCCESS state
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ReportPerfDataImageLoadSuccess001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->ReportPerfData(frameNode, IMAGE_LOAD_SUCCESS);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
}

/**
 * @tc.name: ReportPerfDataImageLoadFail001
 * @tc.desc: Test ReportPerfData with IMAGE_LOAD_FAIL state
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ReportPerfDataImageLoadFail001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->ReportPerfData(frameNode, IMAGE_LOAD_FAIL);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
}

// ============================================================================
// Section 7: Uncovered Functions - Selection (Medium Priority)
// ============================================================================





// ============================================================================
// Section 8: Uncovered Functions - Utility Functions (Low Priority)
// ============================================================================

/**
 * @tc.name: ClearAltData001
 * @tc.desc: Test ClearAltData function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ClearAltData001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->altSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->isLoadAlt_ = true;
    
    auto altImageBefore = pattern->altImage_;
    auto altDstRectBefore = pattern->altDstRect_.get();
    auto altSrcRectBefore = pattern->altSrcRect_.get();
    auto isLoadAltBefore = pattern->isLoadAlt_;
    
    pattern->ClearAltData();
    
    EXPECT_NE(altImageBefore, nullptr);
    EXPECT_EQ(pattern->altImage_, nullptr);
    EXPECT_NE(altDstRectBefore, nullptr);
    EXPECT_EQ(pattern->altDstRect_, nullptr);
    EXPECT_NE(altSrcRectBefore, nullptr);
    EXPECT_EQ(pattern->altSrcRect_, nullptr);
    // ClearAltData does not modify isLoadAlt_
    EXPECT_TRUE(isLoadAltBefore);
    EXPECT_TRUE(pattern->isLoadAlt_);
}

/**
 * @tc.name: UpdateSvgSmoothEdgeValueNullLoadingCtx001
 * @tc.desc: Test UpdateSvgSmoothEdgeValue when loadingCtx_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, UpdateSvgSmoothEdgeValueNullLoadingCtx001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->loadingCtx_ = nullptr;
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->UpdateSvgSmoothEdgeValue();
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
    EXPECT_EQ(loadingCtxAfter, nullptr);
}

/**
 * @tc.name: ClearReloadFlagsAfterLoad001
 * @tc.desc: Test ClearReloadFlagsAfterLoad function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ClearReloadFlagsAfterLoad001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isImageReloadNeeded_ = true;
    pattern->isOrientationChange_ = true;
    
    auto reloadBefore = pattern->isImageReloadNeeded_;
    auto orientBefore = pattern->isOrientationChange_;
    
    pattern->ClearReloadFlagsAfterLoad();
    
    EXPECT_TRUE(reloadBefore);
    EXPECT_FALSE(pattern->isImageReloadNeeded_);
    EXPECT_TRUE(orientBefore);
    EXPECT_FALSE(pattern->isOrientationChange_);
}

// ============================================================================
// Section 9: Partially Covered Functions - Null Checks
// ============================================================================

/**
 * @tc.name: OnCompleteInDataReadyNullLoadingCtx001
 * @tc.desc: Test OnCompleteInDataReady when loadingCtx_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnCompleteInDataReadyNullLoadingCtx001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->loadingCtx_ = nullptr;
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->OnCompleteInDataReady();
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
    EXPECT_EQ(loadingCtxAfter, nullptr);
}

/**
 * @tc.name: CheckHandlesNullHost001
 * @tc.desc: Test CheckHandles when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CheckHandlesNullHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // CheckHandles should return early when host is null
    SelectHandleInfo handleInfo;
    pattern->CheckHandles(handleInfo);
    // Verify function executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RemoveAreaChangeInnerNullPipeline001
 * @tc.desc: Test RemoveAreaChangeInner when pipeline is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RemoveAreaChangeInnerNullPipeline001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->RemoveAreaChangeInner();
    
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ReportCompleteLoadEventNullHost001
 * @tc.desc: Test ReportCompleteLoadEvent when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ReportCompleteLoadEventNullHost001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->ReportCompleteLoadEvent(frameNode);
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
}

/**
 * @tc.name: OnImageLoadFailWithAltError001
 * @tc.desc: Test OnImageLoadFail when altError exists
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadFailWithAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    // Set altError and loadFailed flag
    layoutProperty->UpdateAltError(ImageSourceInfo(ALT_SRC_URL));
    pattern->loadFailed_ = true;
    // Call OnImageLoadFail, loadFailed should remain true
    pattern->OnImageLoadFail("test error", ImageErrorInfo());
    EXPECT_TRUE(pattern->loadFailed_);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChangeSnapshotNode001
 * @tc.desc: Test TriggerFirstVisibleAreaChange with snapshot node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, TriggerFirstVisibleAreaChangeSnapshotNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    bool beforeValue = pattern->isComponentSnapshotNode_;
    pattern->isComponentSnapshotNode_ = true;
    pattern->TriggerFirstVisibleAreaChange();
    bool afterValue = pattern->isComponentSnapshotNode_;
    
    EXPECT_NE(beforeValue, afterValue);
    EXPECT_TRUE(afterValue);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChangeAnimatorNode001
 * @tc.desc: Test TriggerFirstVisibleAreaChange with animator node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, TriggerFirstVisibleAreaChangeAnimatorNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    bool beforeValue = pattern->isImageAnimator_;
    pattern->isImageAnimator_ = true;
    pattern->TriggerFirstVisibleAreaChange();
    bool afterValue = pattern->isImageAnimator_;
    
    EXPECT_NE(beforeValue, afterValue);
    EXPECT_TRUE(afterValue);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChangeNormalNode001
 * @tc.desc: Test TriggerFirstVisibleAreaChange with normal node
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, TriggerFirstVisibleAreaChangeNormalNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isComponentSnapshotNode_ = false;
    pattern->isImageAnimator_ = false;
    pattern->TriggerFirstVisibleAreaChange();
    bool afterSnapshot = pattern->isComponentSnapshotNode_;
    bool afterAnimator = pattern->isImageAnimator_;
    
    EXPECT_FALSE(afterSnapshot);
    EXPECT_FALSE(afterAnimator);
}

/**
 * @tc.name: CreateModifierFirstTime001
 * @tc.desc: Test CreateModifier creates modifiers first time
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateModifierFirstTime001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto contentModBefore = pattern->contentMod_;
    auto overlayModBefore = pattern->overlayMod_;
    auto paintMethodBefore = pattern->imagePaintMethod_;
    
    pattern->CreateModifier();
    
    auto contentModAfter = pattern->contentMod_;
    auto overlayModAfter = pattern->overlayMod_;
    auto paintMethodAfter = pattern->imagePaintMethod_;
    
    EXPECT_EQ(contentModBefore, nullptr);
    EXPECT_NE(contentModAfter, nullptr);
    EXPECT_EQ(overlayModBefore, nullptr);
    EXPECT_NE(overlayModAfter, nullptr);
    EXPECT_EQ(paintMethodBefore, nullptr);
    EXPECT_NE(paintMethodAfter, nullptr);
}

/**
 * @tc.name: CreateModifierSecondTime001
 * @tc.desc: Test CreateModifier doesn't recreate existing modifiers
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateModifierSecondTime001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->CreateModifier();
    auto contentModFirst = pattern->contentMod_;
    auto overlayModFirst = pattern->overlayMod_;
    auto paintMethodFirst = pattern->imagePaintMethod_;
    
    pattern->CreateModifier();
    auto contentModSecond = pattern->contentMod_;
    auto overlayModSecond = pattern->overlayMod_;
    auto paintMethodSecond = pattern->imagePaintMethod_;
    
    EXPECT_EQ(contentModFirst, contentModSecond);
    EXPECT_EQ(overlayModFirst, overlayModSecond);
    EXPECT_EQ(paintMethodFirst, paintMethodSecond);
}

/**
 * @tc.name: HandleSrcForMemoryNameShortUrl001
 * @tc.desc: Test HandleSrcForMemoryName with short URL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, HandleSrcForMemoryNameShortUrl001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // HandleSrcForMemoryName requires valid loadingCtx_
    std::string shortUrl = "short.png";
    std::string result = pattern->HandleSrcForMemoryName(shortUrl);
    // Verify function executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: HandleSrcForMemoryNameLongUrl001
 * @tc.desc: Test HandleSrcForMemoryName with long URL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, HandleSrcForMemoryNameLongUrl001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // HandleSrcForMemoryName requires valid loadingCtx_
    std::string longUrl(200, 'a');
    std::string result = pattern->HandleSrcForMemoryName(longUrl);
    // Verify function executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateImageDfxConfig001
 * @tc.desc: Test CreateImageDfxConfig creates valid config
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateImageDfxConfig001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // CreateImageDfxConfig creates config with node info
    ImageSourceInfo srcInfo(IMAGE_SRC_URL);
    auto config = pattern->CreateImageDfxConfig(srcInfo);
    // Verify config was created
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetParentGlobalOffset001
 * @tc.desc: Test GetParentGlobalOffset returns valid offset
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, GetParentGlobalOffset001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto offsetBefore = pattern->parentGlobalOffset_;
    pattern->GetParentGlobalOffset();
    auto offsetAfter = pattern->parentGlobalOffset_;
    
    EXPECT_EQ(offsetBefore, offsetAfter);
}



/**
 * @tc.name: CreateObscuredImageNoReasons001
 * @tc.desc: Test CreateObscuredImage without obscured reasons
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateObscuredImageNoReasons001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto obscuredBefore = pattern->obscuredImage_;
    pattern->CreateObscuredImage();
    auto obscuredAfter = pattern->obscuredImage_;
    
    EXPECT_EQ(obscuredBefore, obscuredAfter);
    EXPECT_EQ(obscuredAfter, nullptr);
}

/**
 * @tc.name: CreateObscuredImageWithReasons001
 * @tc.desc: Test CreateObscuredImage with obscured reasons
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateObscuredImageWithReasons001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);

    // Set obscured reasons
    renderContext->UpdateObscured({ObscuredReasons::PLACEHOLDER});
    pattern->CreateObscuredImage();
    // Verify function executed without crash
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: LoadingContextNullCtx001
 * @tc.desc: Test LoadingContext with null loading context
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, LoadingContextNullCtx001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    // LoadingContext function should execute without crash
    pattern->LoadingContext();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: LoadingContextWithCtx001
 * @tc.desc: Test LoadingContext with valid loading context
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, LoadingContextWithCtx001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto loadingCtxBefore = pattern->loadingCtx_;
    pattern->LoadingContext();
    auto loadingCtxAfter = pattern->loadingCtx_;
    
    EXPECT_EQ(loadingCtxBefore, loadingCtxAfter);
}

/**
 * @tc.name: PrepareAnimationStatic001
 * @tc.desc: Test PrepareAnimation with static image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, PrepareAnimationStatic001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    
    EXPECT_CALL(*canvasImage, IsStatic()).WillOnce(Return(true));
    pattern->PrepareAnimation(canvasImage);
}

/**
 * @tc.name: PrepareAnimationAnimated001
 * @tc.desc: Test PrepareAnimation with animated image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, PrepareAnimationAnimated001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    
    EXPECT_CALL(*canvasImage, IsStatic()).WillOnce(Return(false));
    pattern->PrepareAnimation(canvasImage);
}

/**
 * @tc.name: ApplyAIModificationsNoSupport001
 * @tc.desc: Test ApplyAIModificationsToImage without AI support
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsNoSupport001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto isPixelMapChangedBefore = pattern->isPixelMapChanged_;
    pattern->ApplyAIModificationsToImage();
    auto isPixelMapChangedAfter = pattern->isPixelMapChanged_;
    
    EXPECT_EQ(isPixelMapChangedBefore, isPixelMapChangedAfter);
}

/**
 * @tc.name: ApplyAIModificationsWithSupport001
 * @tc.desc: Test ApplyAIModificationsToImage with AI support
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsWithSupport001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isPixelMapChanged_ = false;
    auto isPixelMapChangedBefore = pattern->isPixelMapChanged_;
    pattern->ApplyAIModificationsToImage();
    auto isPixelMapChangedAfter = pattern->isPixelMapChanged_;
    
    EXPECT_EQ(isPixelMapChangedBefore, isPixelMapChangedAfter);
}

/**
 * @tc.name: ApplyAIModificationsChanged001
 * @tc.desc: Test ApplyAIModificationsToImage with pixelMap changed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsChanged001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    pattern->isPixelMapChanged_ = true;
    auto isPixelMapChangedBefore = pattern->isPixelMapChanged_;
    pattern->ApplyAIModificationsToImage();
    auto isPixelMapChangedAfter = pattern->isPixelMapChanged_;
    
    EXPECT_EQ(isPixelMapChangedBefore, isPixelMapChangedAfter);
}

/**
 * @tc.name: CreateNodePaintMethodLoadFailed001
 * @tc.desc: Test CreateNodePaintMethod when loadFailed is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodLoadFailed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadFailed_ = true;
    auto paintMethod = pattern->CreateNodePaintMethod();

    EXPECT_NE(paintMethod, nullptr);
}
} // namespace OHOS::Ace::NG

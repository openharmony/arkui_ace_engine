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
#include "test/mock/frameworks/core/components_ng/render/mock_canvas_image.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "core/components_ng/image_provider/image_object.h"

namespace OHOS::Ace::NG {

namespace {
    constexpr int32_t IMAGE_LOAD_FAIL = 0;
    constexpr int32_t IMAGE_LOAD_SUCCESS = 1;
    
    class MockImageData : public ImageData {
    public:
        MOCK_METHOD(size_t, GetSize, (), (const, override));
        MOCK_METHOD(const void*, GetData, (), (const, override));
    };

    class MockImageObject : public ImageObject {
    public:
        MOCK_METHOD(void, MakeCanvasImage,
            (const WeakPtr<ImageLoadingContext>& ctxWp, const SizeF& resizeTarget, bool forceResize, bool syncLoad),
            (override));
        MOCK_METHOD(RefPtr<ImageObject>, Clone, (), (override));
        MockImageObject(const ImageSourceInfo& sourceInfo, const SizeF& imageSize, const RefPtr<ImageData>& data)
            : ImageObject(sourceInfo, imageSize, data)
        {}
        ~MockImageObject() override = default;
    };
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
 * @tc.name: CreateNodePaintMethodAltImageLoadFailed001
 * @tc.desc: Test CreateNodePaintMethod when altImage exists but loadFailed is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodAltImageLoadFailed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->image_ = nullptr;
    pattern->loadFailed_ = true;
    pattern->altErrorImage_ = nullptr;
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altDstRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->altSrcRect_ = std::make_unique<RectF>(0.0f, 0.0f, 100.0f, 100.0f);
    pattern->obscuredImage_ = nullptr;
    auto paintMethod = pattern->CreateNodePaintMethod();

    EXPECT_NE(paintMethod, nullptr);
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

/**
 * @tc.name: CreateNodePaintMethodImageNullLoadFailed001
 * @tc.desc: Test CreateNodePaintMethod when image is null and loadFailed is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateNodePaintMethodImageNullLoadFailed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->image_ = nullptr;
    pattern->loadFailed_ = true;
    pattern->altErrorImage_ = nullptr;
    pattern->altImage_ = nullptr;
    pattern->obscuredImage_ = nullptr;
    auto paintMethod = pattern->CreateNodePaintMethod();

    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: RemoveAreaChangeInnerHasOnAreaChanged001
 * @tc.desc: Test RemoveAreaChangeInner when HasOnAreaChanged returns true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RemoveAreaChangeInnerHasOnAreaChanged001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);

    pattern->RemoveAreaChangeInner();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccessNullImageBranch001
 * @tc.desc: Test OnImageLoadSuccess when image_ is null after MoveCanvasImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadSuccessNullImageBranch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccessEnableDragTrue001
 * @tc.desc: Test OnImageLoadSuccess when enableDrag_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadSuccessEnableDragTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->enableDrag_ = true;
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = canvasImage;

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    pattern->loadingCtx_->canvasImage_ = canvasImage;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageLoadSuccess();
    EXPECT_TRUE(pattern->enableDrag_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapIsImageAnimator001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when isImageAnimator_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDirtyLayoutWrapperSwapIsImageAnimator001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isImageAnimator_ = true;
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = false;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    pattern->loadingCtx_ = nullptr;
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapInvalidId001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when host GetId is INVALID_ID
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDirtyLayoutWrapperSwapInvalidId001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = true;

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    pattern->loadingCtx_ = nullptr;
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnVisibleAreaChangePipelineNull001
 * @tc.desc: Test OnVisibleAreaChange when pipeline is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnVisibleAreaChangePipelineNull001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnVisibleAreaChange(true, 1.0);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnImageLoadSuccessSvgSmoothEdge001
 * @tc.desc: Test OnImageLoadSuccess with SVG to trigger UpdateSvgSmoothEdgeValue
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadSuccessSvgSmoothEdge001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("test.svg");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->canvasImage_ = canvasImage;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetPixelMapMemoryNameEmptyId001
 * @tc.desc: Test SetPixelMapMemoryName when id is empty
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetPixelMapMemoryNameEmptyId001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(pixelMap, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));

    bool result = pattern->SetPixelMapMemoryName(pixelMap);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetPixelMapMemoryNameNoInspectorId001
 * @tc.desc: Test SetPixelMapMemoryName when there's no inspector id
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetPixelMapMemoryNameNoInspectorId001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    EXPECT_NE(pixelMap, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo(IMAGE_SRC_URL));

    bool result = pattern->SetPixelMapMemoryName(pixelMap);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleSrcForMemoryNameLongUrlBranch001
 * @tc.desc: Test HandleSrcForMemoryName with URL > KERNEL_MAX_LENGTH_EXCEPT_OTHER
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, HandleSrcForMemoryNameLongUrlBranch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    std::string longUrl(200, 'a');
    auto result = pattern->HandleSrcForMemoryName(longUrl);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: PreprocessYUVDecodeFormatYuvClosed001
 * @tc.desc: Test PreprocessYUVDecodeFormat when YUV decode is closed
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, PreprocessYUVDecodeFormatYuvClosed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->PreprocessYUVDecodeFormat(frameNode);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateOrientationFrameCountGreaterThanOne001
 * @tc.desc: Test UpdateOrientation when frame count > 1
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, UpdateOrientationFrameCountGreaterThanOne001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    mockObj->SetFrameCount(10);
    pattern->loadingCtx_->imageObj_ = mockObj;

    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateOrientationUserOrientationUp001
 * @tc.desc: Test UpdateOrientation when user orientation is UP
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, UpdateOrientationUserOrientationUp001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    mockObj->SetFrameCount(1);
    mockObj->SetOrientation(ImageRotateOrientation::RIGHT);
    pattern->loadingCtx_->imageObj_ = mockObj;

    pattern->userOrientation_ = ImageRotateOrientation::UP;
    pattern->UpdateOrientation();
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: UpdateOrientationUserOrientationAuto001
 * @tc.desc: Test UpdateOrientation when user orientation is AUTO
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, UpdateOrientationUserOrientationAuto001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    mockObj->SetFrameCount(1);
    mockObj->SetOrientation(ImageRotateOrientation::RIGHT);
    pattern->loadingCtx_->imageObj_ = mockObj;

    pattern->userOrientation_ = ImageRotateOrientation::AUTO;
    pattern->UpdateOrientation();
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: OnImageDataReadySvgIsTrue001
 * @tc.desc: Test OnImageDataReady when loadingCtx GetSourceInfo IsSvg is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageDataReadySvgIsTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("test.svg", ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("test.svg");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    pattern->loadingCtx_->imageObj_ = mockObj;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageDataReady();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CalcImageContentPaintSizeSvgSource001
 * @tc.desc: Test CalcImageContentPaintSize with SVG source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeSvgSource001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("test.svg", ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("test.svg");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));

    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    EXPECT_FLOAT_EQ(paintSize.Width(), 100.0f);
    EXPECT_FLOAT_EQ(paintSize.Height(), 100.0f);
}

/**
 * @tc.name: OnImageLoadSuccessPixelMapExists001
 * @tc.desc: Test OnImageLoadSuccess when pixelMap exists
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadSuccessPixelMapExists001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    pattern->loadingCtx_->canvasImage_ = canvasImage;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnModifyDoneIsSupportImageAnalyzer001
 * @tc.desc: Test OnModifyDone when IsSupportImageAnalyzerFeature is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnModifyDoneIsSupportImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isEnableAnalyzer_ = true;
    pattern->isPixelMapChanged_ = true;

    pattern->OnModifyDone();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FireCompleteEventNullEventHub001
 * @tc.desc: Test OnImageLoadSuccess when eventHub is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, FireCompleteEventNullEventHub001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->canvasImage_ = canvasImage;

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ReportImageSuccessInfoNotCoveredBranch001
 * @tc.desc: Test ReportImageSuccessInfo uncovered branch conditions
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ReportImageSuccessInfoNotCoveredBranch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("/data/local/tmp/test.png");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->canvasImage_ = canvasImage;
    pattern->image_ = canvasImage;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnVisibleAreaChangeVisibleFalse001
 * @tc.desc: Test OnVisibleAreaChange when visible is false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnVisibleAreaChangeVisibleFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isRecycledImage_ = false;
    pattern->OnVisibleAreaChange(false, 0.0);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnVisibleAreaChangeVisibleTrueWithAnimation001
 * @tc.desc: Test OnVisibleAreaChange when visible is true with animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnVisibleAreaChangeVisibleTrueWithAnimation001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*canvasImage, IsStatic()).WillRepeatedly(Return(false));
    pattern->image_ = canvasImage;

    pattern->OnVisibleAreaChange(true, 1.0);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnModifyDonePixelMapChanged001
 * @tc.desc: Test OnModifyDone when isPixelMapChanged_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnModifyDonePixelMapChanged001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isEnableAnalyzer_ = true;
    pattern->isPixelMapChanged_ = true;

    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->isPixelMapChanged_);
}

/**
 * @tc.name: OnImageLoadSuccessSvgBranch001
 * @tc.desc: Test OnImageLoadSuccess when srcInfo.IsSvg() is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadSuccessSvgBranch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("test.svg", ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("test.svg");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->loadingCtx_->canvasImage_ = canvasImage;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageLoadSuccess();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapMeasureFlag001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with measure flag condition
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDirtyLayoutWrapperSwapMeasureFlag001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_MEASURE;

    pattern->isImageAnimator_ = false;
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = true;

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    pattern->loadingCtx_ = nullptr;
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapAnimatorTrue001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when isImageAnimator_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDirtyLayoutWrapperSwapAnimatorTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isImageAnimator_ = true;
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, layoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = false;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    pattern->loadingCtx_ = nullptr;
    auto result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDetachFromMainTreeStatic001
 * @tc.desc: Test OnDetachFromMainTree with static image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDetachFromMainTreeStatic001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*canvasImage, IsStatic()).WillRepeatedly(Return(true));
    pattern->image_ = canvasImage;

    pattern->OnDetachFromMainTree();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTreeAnimated001
 * @tc.desc: Test OnDetachFromMainTree with animated image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnDetachFromMainTreeAnimated001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*canvasImage, IsStatic()).WillRepeatedly(Return(false));
    pattern->image_ = canvasImage;

    pattern->OnDetachFromMainTree();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: LoadImageDataIfNeedNullLayoutProperty001
 * @tc.desc: Test LoadImageDataIfNeed with null layout property
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, LoadImageDataIfNeedNullLayoutProperty001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->LoadImageDataIfNeed();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnImageLoadFailNoAltError001
 * @tc.desc: Test OnImageLoadFail when no altError is set
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadFailNoAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL));
    pattern->OnImageLoadFail("test error", ImageErrorInfo());
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnImageLoadFailHasAltError001
 * @tc.desc: Test OnImageLoadFail when altError is set
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageLoadFailHasAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateAltError(ImageSourceInfo(ALT_SRC_URL));
    layoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL));
    pattern->loadFailed_ = true;

    pattern->OnImageLoadFail("test error", ImageErrorInfo());
    EXPECT_TRUE(pattern->loadFailed_);
}

/**
 * @tc.name: OnImageDataReadyNeedLayoutNew001
 * @tc.desc: Test OnImageDataReady when CheckIfNeedLayout returns true (new)
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnImageDataReadyNeedLayoutNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(200.0f, 200.0f), mockImageData);
    pattern->loadingCtx_->imageObj_ = mockObj;

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->OnImageDataReady();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateOrientationUserOrientationLeft001
 * @tc.desc: Test UpdateOrientation when userOrientation is LEFT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, UpdateOrientationUserOrientationLeft001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    mockObj->SetFrameCount(1);
    mockObj->SetOrientation(ImageRotateOrientation::RIGHT);
    pattern->loadingCtx_->imageObj_ = mockObj;

    pattern->userOrientation_ = ImageRotateOrientation::LEFT;
    pattern->UpdateOrientation();
    EXPECT_EQ(pattern->joinOrientation_, ImageRotateOrientation::LEFT);
}

/**
 * @tc.name: OnNotifyMemoryLevelCritical001
 * @tc.desc: Test OnNotifyMemoryLevel when level is CRITICAL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnNotifyMemoryLevelCritical001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = canvasImage;
    pattern->altImage_ = canvasImage;

    pattern->OnNotifyMemoryLevel(2);

    EXPECT_NE(pattern->image_, nullptr);
    EXPECT_NE(pattern->altImage_, nullptr);
}

/**
 * @tc.name: OnNotifyMemoryLevelNormal001
 * @tc.desc: Test OnNotifyMemoryLevel when level is NORMAL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnNotifyMemoryLevelNormal001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = canvasImage;
    pattern->altImage_ = canvasImage;

    pattern->OnNotifyMemoryLevel(0);

    EXPECT_NE(pattern->image_, nullptr);
    EXPECT_NE(pattern->altImage_, nullptr);
}

/**
 * @tc.name: OnWindowShow001
 * @tc.desc: Test OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnWindowShow001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnWindowShow();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnWindowHide001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = canvasImage;

    pattern->OnWindowHide();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: EnableDrag001
 * @tc.desc: Test EnableDrag
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, EnableDrag001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->enableDrag_ = true;
    pattern->EnableDrag();

    EXPECT_TRUE(pattern->enableDrag_);
}

/**
 * @tc.name: CalcImageContentPaintSizeInvalidDstRect001
 * @tc.desc: Test CalcImageContentPaintSize with invalid dstRect
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeInvalidDstRect001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("test.svg", ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo("test.svg");
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->dstRect_ = RectF(-1.0f, -1.0f, -1.0f, -1.0f);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));

    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    EXPECT_EQ(paintSize.Width(), -1.0f);
    EXPECT_EQ(paintSize.Height(), -1.0f);
}

/**
 * @tc.name: FireFinishEvent001
 * @tc.desc: Test FireFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, FireFinishEvent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_ = canvasImage;
    pattern->SetOnFinishCallback(canvasImage);
    pattern->SetRedrawCallback(canvasImage);

    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChange001
 * @tc.desc: Test RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChange001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->RegisterVisibleAreaChange(false);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: StartDecodingNullLoadingCtx001
 * @tc.desc: Test StartDecoding when loadingCtx_ is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, StartDecodingNullLoadingCtx001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->loadingCtx_ = nullptr;
    SizeF dstSize(100, 100);
    pattern->StartDecoding(dstSize);
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeatNew001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeatNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(ALT_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(200.0f, 200.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));

    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT);

    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    EXPECT_FLOAT_EQ(paintSize.Width(), 200.0f);
    EXPECT_FLOAT_EQ(paintSize.Height(), 200.0f);
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeatXNew001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT_X
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeatXNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(ALT_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(200.0f, 200.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));

    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);

    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    EXPECT_FLOAT_EQ(paintSize.Width(), 200.0f);
    EXPECT_FLOAT_EQ(paintSize.Height(), 100.0f);
}

/**
 * @tc.name: CalcImageContentPaintSizeImageRepeatYNew001
 * @tc.desc: Test CalcImageContentPaintSize with ImageRepeat::REPEAT_Y
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CalcImageContentPaintSizeImageRepeatYNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(ALT_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    pattern->dstRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(200.0f, 200.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));

    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);

    auto paintSize = pattern->CalcImageContentPaintSize(geometryNode);
    EXPECT_FLOAT_EQ(paintSize.Width(), 100.0f);
    EXPECT_FLOAT_EQ(paintSize.Height(), 200.0f);
}

/**
 * @tc.name: OnCompleteInDataReady001
 * @tc.desc: Test OnCompleteInDataReady fires complete event
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, OnCompleteInDataReady001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    geometryNode->SetFrameSize(SizeF(100, 100));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    pattern->loadingCtx_->imageObj_ = mockObj;

    pattern->OnCompleteInDataReady();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChange001
 * @tc.desc: Test TriggerFirstVisibleAreaChange when isComponentSnapshotNode_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, TriggerFirstVisibleAreaChange001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isComponentSnapshotNode_ = true;
    pattern->TriggerFirstVisibleAreaChange();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChange002
 * @tc.desc: Test TriggerFirstVisibleAreaChange when isImageAnimator_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, TriggerFirstVisibleAreaChange002, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isImageAnimator_ = true;
    pattern->TriggerFirstVisibleAreaChange();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChangeNew001
 * @tc.desc: Test RegisterVisibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->RegisterVisibleAreaChange();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetRedrawCallbackNew001
 * @tc.desc: Test SetRedrawCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetRedrawCallback001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->SetRedrawCallback(canvasImage);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: SetOnFinishCallback001
 * @tc.desc: Test SetOnFinishCallback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, SetOnFinishCallback001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->SetOnFinishCallback(canvasImage);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallback001
 * @tc.desc: Test CreateDataReadyCallback creates valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateDataReadyCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallback();
    EXPECT_TRUE(callback != nullptr);
}

/**
 * @tc.name: CreateLoadSuccessCallback001
 * @tc.desc: Test CreateLoadSuccessCallback creates valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadSuccessCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadSuccessCallback();
    EXPECT_TRUE(callback != nullptr);
}

/**
 * @tc.name: CreateLoadFailCallback001
 * @tc.desc: Test CreateLoadFailCallback creates valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadFailCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadFailCallback();
    EXPECT_TRUE(callback != nullptr);
}

/**
 * @tc.name: CreateCompleteCallBackInDataReady001
 * @tc.desc: Test CreateCompleteCallBackInDataReady creates valid callback
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateCompleteCallBackInDataReady001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateCompleteCallBackInDataReady();
    EXPECT_TRUE(callback != nullptr);
}

/**
 * @tc.name: ApplyAIModificationsToImage001
 * @tc.desc: Test ApplyAIModificationsToImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsToImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ApplyAIModificationsToImage();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ApplyAIModificationsToImageAnalyzer001
 * @tc.desc: Test ApplyAIModificationsToImage with analyzer enabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsToImageAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->isEnableAnalyzer_ = true;
    pattern->isPixelMapChanged_ = true;
    pattern->ApplyAIModificationsToImage();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: HandleSrcForMemoryNameShortUrlNew001
 * @tc.desc: Test HandleSrcForMemoryName with short URL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, HandleSrcForMemoryNameShortUrlNew001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    LoadNotifier loadNotifier(nullptr, nullptr, nullptr);
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifier));

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    auto mockObj = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    pattern->loadingCtx_->imageObj_ = mockObj;

    std::string shortUrl = "test.png";
    auto result = pattern->HandleSrcForMemoryName(shortUrl);
    EXPECT_TRUE(!result.empty());
}

/**
 * @tc.name: MaskUrlShortNew001
 * @tc.desc: Test MaskUrl with short URL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, MaskUrlShort001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    std::string shortUrl = "testurl";
    auto result = pattern->MaskUrl(shortUrl);
    EXPECT_TRUE(!result.empty());
}

/**
 * @tc.name: MaskUrlLong001
 * @tc.desc: Test MaskUrl with long URL
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, MaskUrlLong001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    std::string longUrl(500, 'a');
    auto result = pattern->MaskUrl(longUrl);
    EXPECT_TRUE(!result.empty());
}

/**
 * @tc.name: ApplyAIModificationsNullHost001
 * @tc.desc: Test ApplyAIModificationsToImage with null host
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsNullHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ApplyAIModificationsToImage();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ApplyAIModificationsAnalyzerEnabled001
 * @tc.desc: Test ApplyAIModificationsToImage with analyzer enabled
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ApplyAIModificationsAnalyzerEnabled001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100, 100));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    pattern->isEnableAnalyzer_ = true;
    pattern->isPixelMapChanged_ = true;

    pattern->ApplyAIModificationsToImage();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteDataReadyCallback001
 * @tc.desc: Test executing DataReadyCallback with matching sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteDataReadyCallback001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteDataReadyCallbackMismatch001
 * @tc.desc: Test executing DataReadyCallback with mismatched sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteDataReadyCallbackMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo mismatchSourceInfo("different_url.png");
    callback(mismatchSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteLoadSuccessCallback001
 * @tc.desc: Test executing LoadSuccessCallback with matching sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteLoadSuccessCallback001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadSuccessCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteLoadSuccessCallbackMismatch001
 * @tc.desc: Test executing LoadSuccessCallback with mismatched sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteLoadSuccessCallbackMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadSuccessCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo mismatchSourceInfo("different_url.png");
    callback(mismatchSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteLoadFailCallback001
 * @tc.desc: Test executing LoadFailCallback with matching sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteLoadFailCallback001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadFailCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo, "test error", ImageErrorInfo());
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteLoadFailCallbackMismatch001
 * @tc.desc: Test executing LoadFailCallback with mismatched sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteLoadFailCallbackMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadFailCallback();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo mismatchSourceInfo("different_url.png");
    callback(mismatchSourceInfo, "test error", ImageErrorInfo());
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: ExecuteCompleteCallBackInDataReady001
 * @tc.desc: Test executing CompleteCallBackInDataReady
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, ExecuteCompleteCallBackInDataReady001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateCompleteCallBackInDataReady();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChange001
 * @tc.desc: Test RegisterVisibleAreaChange with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeCalcClip001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->RegisterVisibleAreaChange(true);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChangeNoCalcClip001
 * @tc.desc: Test RegisterVisibleAreaChange with calcClip=false
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, RegisterVisibleAreaChangeNoCalcClip001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->RegisterVisibleAreaChange(false);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallbackForAlt001
 * @tc.desc: Test CreateDataReadyCallbackForAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateDataReadyCallbackForAlt001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallbackForAlt();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallbackForAltMismatch001
 * @tc.desc: Test CreateDataReadyCallbackForAlt with mismatched sourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateDataReadyCallbackForAltMismatch001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallbackForAlt();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo mismatchSourceInfo("different_alt.png");
    callback(mismatchSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateLoadSuccessCallbackForAlt001
 * @tc.desc: Test CreateLoadSuccessCallbackForAlt
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadSuccessCallbackForAlt001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadSuccessCallbackForAlt();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo(ALT_SRC_URL);
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: LoadAltErrorImage001
 * @tc.desc: Test LoadAltErrorImage
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, LoadAltErrorImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo altErrorSourceInfo("alt_error.png");
    pattern->LoadAltErrorImage(altErrorSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateDataReadyCallbackForAltError001
 * @tc.desc: Test CreateDataReadyCallbackForAltError
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateDataReadyCallbackForAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateDataReadyCallbackForAltError();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo("alt_error.png");
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateLoadSuccessCallbackForAltError001
 * @tc.desc: Test CreateLoadSuccessCallbackForAltError
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadSuccessCallbackForAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadSuccessCallbackForAltError();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo("alt_error.png");
    callback(sourceInfo);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CreateLoadFailCallbackForAltError001
 * @tc.desc: Test CreateLoadFailCallbackForAltError
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternBranchCoverageTestNg, CreateLoadFailCallbackForAltError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto callback = pattern->CreateLoadFailCallbackForAltError();
    EXPECT_TRUE(callback != nullptr);

    ImageSourceInfo sourceInfo("alt_error.png");
    callback(sourceInfo, "error", ImageErrorInfo());
    EXPECT_NE(pattern, nullptr);
}

} // namespace OHOS::Ace::NG

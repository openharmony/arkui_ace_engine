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

#include "base/image/image_defines.h"

namespace OHOS::Ace::NG {
class ImageTestTwoNg : public ImageBases {};

/**
 * @tc.name: ImagePatternCreateCompleteCallBackInDataReady
 * @tc.desc: call CreateCompleteCallBackInDataReady.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternCreateCompleteCallBackInDataReady, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ImageSourceInfo info;
    imagePattern->CreateCompleteCallBackInDataReady()(info);
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternSetOnFinishCallback
 * @tc.desc: call SetOnFinishCallback.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternSetOnFinishCallback, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->SetOnFinishCallback(canvasImage);
    imagePattern->SetRedrawCallback(canvasImage);
    EXPECT_EQ(imagePattern->image_, nullptr);
    EXPECT_NE(canvasImage->redrawCallback_, nullptr);
    canvasImage->redrawCallback_();
    EXPECT_NE(canvasImage->onFinishCallback_, nullptr);
    canvasImage->onFinishCallback_();
}

/**
 * @tc.name: ImagePatternCheckHandles
 * @tc.desc: call CheckHandles.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternCheckHandles, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    SelectHandleInfo info;
    imagePattern->CheckHandles(info);
    EXPECT_FALSE(info.isShow);
}

/**
 * @tc.name: ImagePatternCalAndUpdateSelectOverlay
 * @tc.desc: call CalAndUpdateSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternCalAndUpdateSelectOverlay, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OpenSelectOverlay();
    imagePattern->CalAndUpdateSelectOverlay();
    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
    auto info = imagePattern->selectOverlay_->GetSelectOverlayMangerInfo();
    info.onHandleMoveDone(RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH), true);
    info.menuCallback.onCopy();
}

/**
 * @tc.name: ImagePatternGetParentGlobalOffset
 * @tc.desc: call GetParentGlobalOffset.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternGetParentGlobalOffset, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    OffsetF offset = imagePattern->GetParentGlobalOffset();
    EXPECT_EQ(offset, OffsetF());
}

/**
 * @tc.name: ImagePatternOnAreaChangedInner
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnAreaChangedInner, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OpenSelectOverlay();
    imagePattern->OnAreaChangedInner();
    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: ImagePatternStartDecoding
 * @tc.desc: call StartDecoding.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternStartDecoding, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF());
    imagePattern->StartDecoding(SizeF());
    EXPECT_NE(frameNode->GetGeometryNode()->GetContent().get(), nullptr);
}

/**
 * @tc.name: ImagePatternOnRecycle
 * @tc.desc: call OnRecycle.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnRecycle, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OnRecycle();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternOnReuse
 * @tc.desc: call OnReuse.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnReuse, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OnReuse();
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternHandleCopy
 * @tc.desc: call HandleCopy.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternHandleCopy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    frameNode->SetActive(true);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imageLayoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. AltImage loads successfully, and trigger alt callback.
     */
    imagePattern->altLoadingCtx_->DataReadyCallback(nullptr);

    imagePattern->altLoadingCtx_->srcRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT };
    imagePattern->altLoadingCtx_->dstRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH };
    imagePattern->altLoadingCtx_->SuccessCallback(nullptr);

    // check onAltLoadSuccess result
    ASSERT_NE(imagePattern->altImage_, nullptr);
    EXPECT_EQ(*imagePattern->altSrcRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_EQ(*imagePattern->altDstRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH));
    ASSERT_NE(imagePattern->altImage_->paintConfig_, nullptr);
    auto altImagePaintConfig = imagePattern->altImage_->GetPaintConfig();
    EXPECT_EQ(altImagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    /**
     * @tc.steps: step4. Image loads successfully, and trigger Pattern->OnImageLoadSuccess.
     */

    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    ASSERT_NE(imagePattern->image_, nullptr);

    imagePattern->HandleCopy();
    EXPECT_NE(imagePattern->clipboard_, nullptr);
}

/**
 * @tc.name: ImagePatternToJsonValue
 * @tc.desc: call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternToJsonValue, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    InspectorFilter filter;
    imagePattern->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
}

/**
 * @tc.name: ImagePatternUpdateFillColorIfForegroundColor
 * @tc.desc: call UpdateFillColorIfForegroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternUpdateFillColorIfForegroundColor, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateForegroundColor(Color::BLACK);
    EXPECT_TRUE(renderContext->HasForegroundColor());
}

/**
 * @tc.name: ImagePatternBetweenSelectedPosition
 * @tc.desc: call BetweenSelectedPosition.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternBetweenSelectedPosition, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    bool b = imagePattern->BetweenSelectedPosition(Offset());
    imagePattern->BeforeCreatePaintWrapper();
    imagePattern->OnDirectionConfigurationUpdate();
    imagePattern->OnIconConfigurationUpdate();
    EXPECT_FALSE(b);
}

/**
 * @tc.name: ImagePatternGetImageColorFilterStr
 * @tc.desc: call GetImageColorFilterStr.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternGetImageColorFilterStr, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    std::vector<float> colorFilter = { .0f, .0f };

    std::string str1 = imagePattern->GetImageColorFilterStr(colorFilter);
    std::string str2 = std::string("[") + std::to_string(colorFilter[0]) + ", " + std::to_string(colorFilter[1]) + "]";
    EXPECT_STREQ(str1.c_str(), str2.c_str());
}

/**
 * @tc.name: ImagePatternGetSrcTypeToString001
 * @tc.desc: call GetSrcTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternGetSrcTypeToString001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode and imagePattern.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. SrcType value should be we set.
     */
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::UNSUPPORTED).c_str(), "unsupported");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::FILE).c_str(), "file");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::ASSET).c_str(), "asset");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::NETWORK).c_str(), "network");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::MEMORY).c_str(), "memory");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::BASE64).c_str(), "base64");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::INTERNAL).c_str(), "internal");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::RESOURCE).c_str(), "resource");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::DATA_ABILITY).c_str(), "dataAbility");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::DATA_ABILITY_DECODED).c_str(), "dataAbilityDecoded");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::RESOURCE_ID).c_str(), "resourceId");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::PIXMAP).c_str(), "pixmap");
    EXPECT_STREQ(imagePattern->GetSrcTypeToString(SrcType::ASTC).c_str(), "astc");
}

/**
 * @tc.name: ImagePatternGetSrcTypeToString002
 * @tc.desc: call GetSrcTypeToString with error type.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternGetSrcTypeToString002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode and imagePattern.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    std::string retStr;

    /**
     * @tc.steps: step2. call GetSrcTypeToString with error value.
     */
    auto errType = static_cast<SrcType>(99);
    retStr = imagePattern->GetSrcTypeToString(errType);

    /**
     * @tc.steps: step3. SrcType value should be null string.
     */
    EXPECT_STREQ(retStr.c_str(), "");
}

/**
 * @tc.name: ImagePatternSetImageAnalyzerConfig
 * @tc.desc: call SetImageAnalyzerConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternSetImageAnalyzerConfig, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ImageAnalyzerConfig config;
    imagePattern->SetImageAnalyzerConfig(config);
    imagePattern->SetImageAnalyzerConfig(nullptr);
    EXPECT_FALSE(imagePattern->isEnableAnalyzer_);
}

/**
 * @tc.name: ImagePatternCreateAnalyzerOverlay
 * @tc.desc: call CreateAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternCreateAnalyzerOverlay, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    frameNode->SetActive(true);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->EnableAnalyzer(true);
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imageLayoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. AltImage loads successfully, and trigger alt callback.
     */
    imagePattern->altLoadingCtx_->DataReadyCallback(nullptr);

    imagePattern->altLoadingCtx_->srcRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT };
    imagePattern->altLoadingCtx_->dstRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH };
    imagePattern->altLoadingCtx_->SuccessCallback(nullptr);

    // check onAltLoadSuccess result
    ASSERT_NE(imagePattern->altImage_, nullptr);
    EXPECT_EQ(*imagePattern->altSrcRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_EQ(*imagePattern->altDstRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH));
    ASSERT_NE(imagePattern->altImage_->paintConfig_, nullptr);
    auto altImagePaintConfig = imagePattern->altImage_->GetPaintConfig();
    EXPECT_EQ(altImagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    /**
     * @tc.steps: step4. Image loads successfully, and trigger Pattern->OnImageLoadSuccess.
     */

    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    ASSERT_NE(imagePattern->image_, nullptr);

    imagePattern->CreateAnalyzerOverlay();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name:  ImagePatternUpdateAnalyzerOverlayLayout
 * @tc.desc: call UpdateAnalyzerOverlayLayout.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternUpdateAnalyzerOverlayLayout, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    imagePattern->UpdateAnalyzerOverlayLayout();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name:  ImagePatternDestroyAnalyzerOverlay
 * @tc.desc: call DestroyAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternDestroyAnalyzerOverlay, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->DestroyAnalyzerOverlay();
    imagePattern->EnableAnalyzer(true);
    imagePattern->DestroyAnalyzerOverlay();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name:  ImagePatternReleaseImageAnalyzer
 * @tc.desc: call ReleaseImageAnalyzer.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternReleaseImageAnalyzer, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->ReleaseImageAnalyzer();
    imagePattern->EnableAnalyzer(true);
    imagePattern->ReleaseImageAnalyzer();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name:  ImagePatternUpdateAnalyzerUIConfig
 * @tc.desc: call UpdateAnalyzerUIConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternUpdateAnalyzerUIConfig, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->UpdateAnalyzerUIConfig(nullptr);
    bool b = imagePattern->IsSupportImageAnalyzerFeature();
    EXPECT_FALSE(b);
}

/**
 * @tc.name:  ImagePatternhasSceneChanged
 * @tc.desc: call hasSceneChanged.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternhasSceneChanged, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    bool b = imagePattern->hasSceneChanged();
    EXPECT_TRUE(b);
}

/**
 * @tc.name:  ImagePatternResetImage
 * @tc.desc: call ResetImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternResetImage, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->ResetImage();
    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ImagePatternResetAltImage001
 * @tc.desc: call ResetAltImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternResetAltImage001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    frameNode->SetActive(true);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->EnableAnalyzer(true);
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imageLayoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. AltImage loads successfully, and trigger alt callback.
     */
    imagePattern->altLoadingCtx_->DataReadyCallback(nullptr);

    imagePattern->altLoadingCtx_->srcRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT };
    imagePattern->altLoadingCtx_->dstRect_ = { 0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH };
    imagePattern->altLoadingCtx_->SuccessCallback(nullptr);

    // check onAltLoadSuccess result
    ASSERT_NE(imagePattern->altImage_, nullptr);
    EXPECT_EQ(*imagePattern->altSrcRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_EQ(*imagePattern->altDstRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_WIDTH));
    ASSERT_NE(imagePattern->altImage_->paintConfig_, nullptr);
    auto altImagePaintConfig = imagePattern->altImage_->GetPaintConfig();
    EXPECT_EQ(altImagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    /**
     * @tc.steps: step4. Image loads successfully, and trigger Pattern->OnImageLoadSuccess.
     */

    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    ASSERT_NE(imagePattern->image_, nullptr);

    imagePattern->ResetAltImage();
    EXPECT_EQ(imagePattern->altImage_, nullptr);
}

/**
 * @tc.name: ImagePatternResetAltImage002
 * @tc.desc: call ResetAltImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternResetAltImage002, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->ResetAltImage();
    EXPECT_EQ(imagePattern->altImage_, nullptr);
}

/**
 * @tc.name:  ImagePatternMethods
 * @tc.desc: call void methods.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternMethods, TestSize.Level0)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    imagePattern->TriggerFirstVisibleAreaChange();
    imagePattern->imageAnalyzerManager_ = nullptr;
    EXPECT_EQ(imagePattern->IsSupportImageAnalyzerFeature(), false);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub->completeEvent_, nullptr);
    LoadImageSuccessEvent loadImageSuccessEvent(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT);
    eventHub->FireCompleteEvent(loadImageSuccessEvent);
    loadImageSuccessEvent.loadingStatus_ = -1;
    eventHub->FireCompleteEvent(loadImageSuccessEvent);
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    int testData = 0;
    std::function onProgress = [&testData](const uint32_t&, const uint32_t&) { testData = 1; };
    imagePattern->SetOnProgressCallback(std::move(onProgress));
    imagePattern->onProgressCallback_(uint32_t(0), uint32_t(1));
    EXPECT_EQ(testData, 1);
    imagePattern->EnableDrag();
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->defaultOnDragStart_(dragEvent, string(""));
    EXPECT_EQ(dragEvent->GetData(), nullptr);
    std::vector<float> matrix = { 1.1f };
    ImageModelNG::SetColorFilterMatrix(AceType::RawPtr(frameNode), matrix);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), matrix);
    ImageModelNG::SetImageFit(AceType::RawPtr(frameNode), ImageFit::COVER);
    EXPECT_EQ(imageRenderProperty->GetImageFitValue(), ImageFit::COVER);
}

/**
 * @tc.name: ImagePatternIsSupportImageAnalyzerFeature0045
 * @tc.desc: call IsSupportImageAnalyzerFeature.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternIsSupportImageAnalyzerFeature0045, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    imagePattern->UpdateAnalyzerOverlay();
    EXPECT_TRUE(!imagePattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name:  ImagePatternhasSceneChanged0048
 * @tc.desc: call hasSceneChanged.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternhasSceneChanged0048, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_ = nullptr;
    bool b = imagePattern->hasSceneChanged();
    EXPECT_TRUE(b);
}

/**
 * @tc.name: ImagePatternOnAreaChangedInner0049
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnAreaChangedInner111, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OpenSelectOverlay();
    imagePattern->OnAreaChangedInner();
    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: ImagePatternCreateNodePaintMethod0050
 * @tc.desc: Test Image related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternCreateNodePaintMethod0050, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->isSensitive_ = true;
    EXPECT_NE(imagePattern->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: ImagePatternOnDirtyLayoutWrapperSwap0051
 * @tc.desc: Test Image related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnDirtyLayoutWrapperSwap0051, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, imageLayoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig config;
    config.skipMeasure = false;
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    imagePattern->imageType_ = ImageType::BASE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
}

/**
 * @tc.name: ImagePatternOnAreaChangedInner0054
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnAreaChangedInner0054, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->parentGlobalOffset_ = OffsetF(1, 1);
    imagePattern->OpenSelectOverlay();
    imagePattern->OnAreaChangedInner();
    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: ImagePatternIsSupportImageAnalyzerFeature0055
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternIsSupportImageAnalyzerFeature0055, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isEnableAnalyzer_ = true;

    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    ASSERT_NE(imagePattern->image_, nullptr);
    EXPECT_FALSE(imagePattern->loadingCtx_->GetSourceInfo().IsSvg());
    EXPECT_TRUE(imagePattern->loadingCtx_->GetFrameCount() <= 1);

    imagePattern->DestroyAnalyzerOverlay();
    imagePattern->EnableAnalyzer(true);
    imagePattern->DestroyAnalyzerOverlay();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
    EXPECT_FALSE(imagePattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name: ImagePatternSetImageAIOptions0056
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternSetImageAIOptions0056, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->imageAnalyzerManager_ = nullptr;
    imagePattern->SetImageAIOptions(nullptr);
    ASSERT_NE(imagePattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: ImagePatternEnableAnalyzer0057
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternEnableAnalyzer0057, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->CreateAnalyzerOverlay();
    imagePattern->isEnableAnalyzer_ = true;
    imagePattern->EnableAnalyzer(false);
    EXPECT_FALSE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name: ImagePatternGetImageColorFilterStr0058
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternGetImageColorFilterStr0058, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    std::vector<float> testColorFilter;
    testColorFilter.push_back(1.0f);
    testColorFilter.clear();
    std::string str = imagePattern->GetImageColorFilterStr(testColorFilter);
    EXPECT_EQ(str, "");
}

/**
 * @tc.name: ImagePatternOnLanguageConfigurationUpdate0059
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnLanguageConfigurationUpdate0059, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    RectF testRectF = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->srcRect_ = testRectF;
    imagePattern->loadingCtx_->dstRect_ = testRectF;
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    imagePattern->loadingCtx_->src_.srcType_ = SrcType::RESOURCE;
    imagePattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternOnAttachToFrameNode0060
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternOnAttachToFrameNode0060, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnAttachToFrameNode();
    EXPECT_TRUE(imagePattern->GetIsAnimation());
}

/**
 * @tc.name: ImagePatternUpdateDragEvent0061
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternUpdateDragEvent0061, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    ASSERT_NE(imagePattern->image_, nullptr);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    imagePattern->loadingCtx_->src_.srcType_ = SrcType::DATA_ABILITY_DECODED;
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(dragEvent->unifiedData_, nullptr);
    imagePattern->OnRecycle();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternUpdateDragEvent0062
 * @tc.desc: call UpdateDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImagePatternUpdateDragEvent0062, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    imagePattern->loadingCtx_->src_.srcType_ = SrcType::DATA_ABILITY_DECODED;
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(dragEvent->unifiedData_, nullptr);
    imagePattern->OnRecycle();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
    /**
     * @tc.steps: step2. call UpdateDragEvent.
     * @tc.expected: Returned color value is BLUE.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImageCreator0063
 * @tc.desc: call Creat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageCreator0063, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    ImageModelNG image;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
    /**
     * @tc.steps: step2. call Create.
     * @tc.expected: GetImageType value is not BASE.
     */
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    auto imageType = ImageType::BASE;
    auto res = imagePattern->GetImageType();
    EXPECT_EQ(res, imageType);
    imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    image.Create(imageInfoConfig);
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: ImageCreator0064
 * @tc.desc: call Creat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageCreator0064, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    ImageModelNG image;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
    /**
     * @tc.steps: step2. call Create.
     * @tc.expected: GetImageType value is not BASE and pattern has changed.
     */
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    auto res = imagePattern->GetImageType();
    auto imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    image.Create(imageInfoConfig);
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: ResetImage0065
 * @tc.desc: call ResetImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ResetImage0065, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    ImageModelNG image;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
    /**
     * @tc.steps: step2. call ResetImage.
     * @tc.expected: GetImageType value is UNDEFINED.
     */
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    auto imageType = ImageType::BASE;
    auto res = imagePattern->GetImageType();
    imagePattern->SetImageType(imageType);
    image.ResetImage();
    /**
     * @tc.steps: step3. call ResetImage.
     * @tc.expected: GetImageType value is ANIMATION.
     */
    imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    image.ResetImage();
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: ResetImage0066
 * @tc.desc: call ResetImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ResetImage0066, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    ImageModelNG image;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_->srcRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->dstRect_ = { 0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT };
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
    /**
     * @tc.steps: step2. call ResetImage.
     * @tc.expected: GetImageType value is ANIMATION and pattern has changed.
     */
    RefPtr<PixelMap> pixMap = nullptr;
    auto res = imagePattern->GetImageType();
    auto imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    image.ResetImage();
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: TestAutoResize001
 * @tc.desc: Test image autoResize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestAutoResize001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step2. set autoResize
     */
    layoutProperty->UpdateAutoResize(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetAutoResize(), false);

    /**
     * @tc.steps: step3. set autoResize
     */
    layoutProperty->UpdateAutoResize(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetAutoResize(), true);
}

/**
 * @tc.name: TestFitOriginalSize001
 * @tc.desc: Test image fitOriginalSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestFitOriginalSize001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step2. set fitOriginalSize
     */
    layoutProperty->UpdateFitOriginalSize(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetFitOriginalSize().value(), false);

    /**
     * @tc.steps: step3. set fitOriginalSize
     */
    layoutProperty->UpdateFitOriginalSize(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetFitOriginalSize().value(), true);
}

/**
 * @tc.name: TestMatchTextDirection001
 * @tc.desc: Test image matchTextDirection.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestMatchTextDirection001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and  RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set matchTextDirection
     */
    imageRenderProperty->UpdateMatchTextDirection(true);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection(), true);

    /**
     * @tc.steps: step4. set matchTextDirection
     */
    imageRenderProperty->UpdateMatchTextDirection(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection(), false);
}

/**
 * @tc.name: TestRenderMode001
 * @tc.desc: Test image renderMode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestRenderMode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set renderMode
     */
    imageRenderProperty->UpdateImageRenderMode(ImageRenderMode::ORIGINAL);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode(), ImageRenderMode::ORIGINAL);

    /**
     * @tc.steps: step4. set renderMode
     */
    imageRenderProperty->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode(), ImageRenderMode::TEMPLATE);
}

/**
 * @tc.name: TestInterpolation001
 * @tc.desc: Test image interpolation.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestInterpolation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::NONE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::NONE);

    /**
     * @tc.steps: step4. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::LOW);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::LOW);

    /**
     * @tc.steps: step5. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::MEDIUM);

    /**
     * @tc.steps: step6. set interpolation
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: ImageModelSetDraggable001
 * @tc.desc: Set the draggable attribute of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageModelSetDraggable001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    image.SetDraggable(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode->draggable_);
}

/**
 * @tc.name: TestObjectRepeat001
 * @tc.desc: Test image objectRepeat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestObjectRepeat001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern and RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    const auto& geometryNode = frameNode->GetGeometryNode();

    auto paintRect = imagePattern->CalcImageContentPaintSize(geometryNode);
    /**
     * @tc.steps: step3. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step4. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT_X);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step5. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::REPEAT_Y);
    EXPECT_EQ(paintRect.Left(), 0);
    EXPECT_EQ(paintRect.Top(), 0);

    /**
     * @tc.steps: step6. set objectRepeat
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageRepeat(), ImageRepeat::NO_REPEAT);
}

/**
 * @tc.name: TestObjectFit001
 * @tc.desc: Test image objectFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestObjectFit001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern RadiusProperty layoutProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();

    /**
     * @tc.steps: step3. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FILL);
    layoutProperty->UpdateImageFit(ImageFit::FILL);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FILL);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FILL);

    /**
     * @tc.steps: step5. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::CONTAIN);
    layoutProperty->UpdateImageFit(ImageFit::CONTAIN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::CONTAIN);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::CONTAIN);

    /**
     * @tc.steps: step6. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::COVER);
    layoutProperty->UpdateImageFit(ImageFit::COVER);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::COVER);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::COVER);

    /**
     * @tc.steps: step7. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FITWIDTH);
    layoutProperty->UpdateImageFit(ImageFit::FITWIDTH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FITWIDTH);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FITWIDTH);

    /**
     * @tc.steps: step8. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::FITHEIGHT);
    layoutProperty->UpdateImageFit(ImageFit::FITHEIGHT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::FITHEIGHT);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::FITHEIGHT);

    /**
     * @tc.steps: step9. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::NONE);
    layoutProperty->UpdateImageFit(ImageFit::NONE);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::NONE);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::NONE);

    /**
     * @tc.steps: step10. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    layoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::SCALE_DOWN);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::SCALE_DOWN);

    /**
     * @tc.steps: step11. set objectFit
     */
    imageRenderProperty->UpdateImageFit(ImageFit::TOP_LEFT);
    layoutProperty->UpdateImageFit(ImageFit::TOP_LEFT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetImageFit(), ImageFit::TOP_LEFT);
    EXPECT_EQ(layoutProperty->GetImageFit(), ImageFit::TOP_LEFT);
}

/**
 * @tc.name: TestDynamicRangeMode001
 * @tc.desc: Test image dynamicRangeMode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestDynamicRangeMode001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern ImageRenderProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::CONSTRAINT);

    /**
     * @tc.steps: step4. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::STANDARD);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::STANDARD);

    /**
     * @tc.steps: step5. set dynamicRangeMode
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::HIGH);
    frameNode->MarkModifyDone();
    EXPECT_EQ(imageRenderProperty->GetDynamicMode(), DynamicRangeMode::HIGH);
}

/**
 * @tc.name: TestEnhancedImageQuality001
 * @tc.desc: Test image EnhancedImageQuality.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestEnhancedImageQuality001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);

    /**
     * @tc.steps: step2. get ImagePattern ImageRenderProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::HIGH);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::HIGH);

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::NONE);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::NONE);

    /**
     * @tc.steps: step3. set EnhancedImageQuality
     */
    imagePattern->SetImageQuality(AIImageQuality::NORMAL);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::NORMAL);
}

/**
 * @tc.name: ImageSetDraggable0001
 * @tc.desc: Set the draggable attribute of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSetDraggable0001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    image.SetDraggable(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode->draggable_);
}

HWTEST_F(ImageTestTwoNg, ImageSetDraggable0002, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    image.SetDraggable(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_FALSE(frameNode->draggable_);
}

/**
 * @tc.name: ImageDumpInfo0001
 * @tc.desc: Output the relevant information of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageDumpInfo0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->DumpInfo();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageDumpAdvanceInfo0001
 * @tc.desc: Output more information of ImageModelNG object.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageDumpAdvanceInfo0001, TestSize.Level1)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->DumpAdvanceInfo();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageOnColorConfigurationUpdate0001
 * @tc.desc: Output more information of ImageModelNG object when the color configuration is updated.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageOnColorConfigurationUpdate0001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->loadingCtx_);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageSetImageAnalyzerConfig0001
 * @tc.desc: Set the configuration of the image analyzer.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSetImageAnalyzerConfig0001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: ImageSensitiveTest0001
 * @tc.desc: Test image privacySensitive.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSensitiveTest0001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(frameNode->IsPrivacySensitive());
    frameNode->SetPrivacySensitive(true);
    EXPECT_TRUE(frameNode->IsPrivacySensitive());
    frameNode->SetPrivacySensitive(false);
    EXPECT_FALSE(frameNode->isPrivacySensitive_);
}

/**
 * @tc.name: ImageSensitiveTest0002
 * @tc.desc: Test image OnSensitiveStyleChange.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, ImageSensitiveTest0002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get ImagePattern and call OnSensitiveStyleChange.
     * @tc.expected: isSensitive_ is true when setting privacy sensitive and card notification.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    frameNode->SetPrivacySensitive(true);
    imagePattern->OnSensitiveStyleChange(false);
    EXPECT_FALSE(imagePattern->isSensitive_);
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_TRUE(imagePattern->isSensitive_);
    frameNode->SetPrivacySensitive(false);
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_FALSE(imagePattern->isSensitive_);

    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(
        imagePattern->image_, { .selected = true, .imageOverlayModifier = nullptr, .sensitive = true });
    EXPECT_TRUE(imagePaintMethod.sensitive_);
}

/**
 * @tc.name: TestCreate001
 * @tc.desc: Test image Create.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestCreate001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ImageModelNG image;
    image.SetSyncMode(AceType::RawPtr(frameNode), SYNCMODE_DEFAULT);
    EXPECT_EQ(imagePattern->GetSyncLoad(), SYNCMODE_DEFAULT);
    image.EnableAnalyzer(false);
    image.EnableAnalyzer(AceType::RawPtr(frameNode), true);
    imagePattern->SetImageType(ImageType::ANIMATED_DRAWABLE);
    image.ResetImageSrc(AceType::RawPtr(frameNode));
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    EXPECT_EQ(imagePattern->GetImageType(), ImageType::ANIMATED_DRAWABLE);
}

/**
 * @tc.name: TestSetResizableSlice001
 * @tc.desc: test ImageModelNG::SetResizableSlice
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestSetResizableSlice001, TestSize.Level0)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    ImageResizableSlice imageResizableSlice {
        .left = Dimension(1),
    };
    image.SetResizableSlice(imageResizableSlice);
    EXPECT_EQ(renderProperty->GetImageResizableSlice().value(), imageResizableSlice);
}

/**
 * @tc.name: TestUpdateImageSourceinfo001
 * @tc.desc: Test ImagePattern::UpdateImageSourceinfo function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestUpdateImageSourceinfo001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageSourceInfo sourceInfo("test_source");
    auto host = imagePattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);

    pipelineContext->isSystemColorChange_ = true;
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    imagePattern->UpdateImageSourceinfo(sourceInfo);
    sourceInfo.src_ = "test_source2";
    EXPECT_NE(imageLayoutProperty->GetImageSourceInfo(), sourceInfo);
}

/**
 * @tc.name: TestUpdateImageFill001
 * @tc.desc: Test ImagePattern::UpdateImageFill function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestUpdateImageFill001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    Color testColor(Color::RED);
    imagePattern->UpdateImageFill(testColor);

    auto renderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetSvgFillColor(), testColor);

    auto host = imagePattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetForegroundColor(), testColor);
}

/**
 * @tc.name: TestUpdateImageAlt001
 * @tc.desc: Test ImagePattern::UpdateImageAlt function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestUpdateImageAlt001, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageSourceInfo sourceInfo("test_alt_source");
    auto host = imagePattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);

    pipelineContext->isSystemColorChange_ = true;
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    imagePattern->UpdateImageAlt(sourceInfo);
    sourceInfo.src_ = "test_alt_source2";
    EXPECT_NE(imageLayoutProperty->GetAlt(), sourceInfo);
}

/**
 * @tc.name: TestUpdateImageFill002
 * @tc.desc: Test ImagePattern::UpdateImageFill function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TestUpdateImageFill002, TestSize.Level0)
{
    auto frameNode = ImageTestTwoNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    Color testColor(Color::BLUE);
    imagePattern->UpdateImageFill(testColor);

    auto renderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProperty, nullptr);
    EXPECT_EQ(renderProperty->GetSvgFillColor(), testColor);
}

/**
 * @tc.name: TesSetBorderRadius001
 * @tc.desc: Test SetBorderRadius function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, TesSetBorderRadius001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    g_isConfigChangePerform = false;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(RADIUS_DEFAULT);
    image.SetBorderRadius(borderRadius);
    g_isConfigChangePerform = true;
    image.SetBorderRadius(borderRadius);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    EXPECT_TRUE(pattern->needBorderRadius_);
}

/**
 * @tc.name: HandleBorderRadiusResource001
 * @tc.desc: Test HandleBorderRadiusResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestTwoNg, HandleBorderRadiusResource001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = pixMap;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObjWithDimensionId =
        AceType::MakeRefPtr<ResourceObject>(100000, 10007, resObjParamsList, "com.example.test", "entry", 100000);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    image.CreateWithResourceObj(ImageResourceType::BORDER_RADIUS, resObjWithDimensionId);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::BORDER_RADIUS, resObj);
    pattern->OnColorModeChange(colorMode);
    EXPECT_TRUE(pattern->needBorderRadius_);
}
} // namespace OHOS::Ace::NG

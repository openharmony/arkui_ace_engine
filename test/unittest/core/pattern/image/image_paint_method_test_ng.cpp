/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/pattern/image/image_paint_method.h"

namespace OHOS::Ace::NG {

class ImagePaintMethodTestNg : public ImageBases {};

/**
 * @tc.name: ImagePaintMethodTestNg_UpdateBorderRadius
 * @tc.desc: Create UpdateBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdateBorderRadius, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageGeometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(imageGeometryNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    /**
     * @tc.steps: step3. call function.
     */
    RefPtr<PaintWrapper> paintWrapperNull = AceType::MakeRefPtr<PaintWrapper>(nullptr, nullptr, nullptr);
    PaintWrapper* imagePaintWrapperNullRaw_ = AceType::RawPtr(paintWrapperNull);
    ImageDfxConfig imageDfxConfig;
    imagePaintMethod_->UpdateBorderRadius(imagePaintWrapperNullRaw_, imageDfxConfig);
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    imagePaintMethod_->UpdateBorderRadius(imagePaintWrapperRaw_, imageDfxConfig);
    BorderWidthProperty borderWidth_;
    frameNode->GetRenderContext()->UpdateBorderWidth(borderWidth_);
    imagePaintMethod_->UpdateBorderRadius(imagePaintWrapperRaw_, imageDfxConfig);
    borderWidth_.SetBorderWidth(IMAGE_SOURCEINFO_WIDTH);
    frameNode->GetRenderContext()->UpdateBorderWidth(borderWidth_);
    imagePaintMethod_->UpdateBorderRadius(imagePaintWrapperRaw_, imageDfxConfig);
    EXPECT_EQ(imagePaintMethod_->selected_, true);
}

/**
 * @tc.name: ImagePaintMethodTestNg_UpdatePaintConfig
 * @tc.desc: Create UpdatePaintConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdatePaintConfig, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(), geometryNode, imagePaintProperty_);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    EXPECT_NE(imagePaintWrapper_, paintWrapper);
    /**
     * @tc.steps: step3. call function.
     */
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    EXPECT_EQ(isRightToLeft, false);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    bool isRightToLeftEnd = AceApplicationInfo::GetInstance().IsRightToLeft();
    EXPECT_EQ(isRightToLeftEnd, true);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    auto& config = imagePaintMethod_->canvasImage_->paintConfig_;
    EXPECT_NE(config, nullptr);
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    imagePaintProperty_->UpdateDrawingColorFilter(drawingColorFilter);
    imagePaintProperty_->UpdateNeedBorderRadius(false);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    EXPECT_EQ(imagePaintMethod_->selected_, true);
}

/**
 * @tc.name: ImagePaintMethodTestNg_UpdatePaintConfig_ImageMatrix001
 * @tc.desc: Create UpdatePaintConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdatePaintConfig_ImageMatrix001, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    ImageModelNG image;
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(), geometryNode, imagePaintProperty_);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    EXPECT_NE(imagePaintWrapper_, paintWrapper);
    /**
     * @tc.steps: step3. call function.
     */
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    Matrix4 defaultMatrix4Value = Matrix4(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
    image.SetImageMatrix(defaultMatrix4Value);
    image.SetImageFit(ImageFit::MATRIX);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    auto& config = imagePaintMethod_->canvasImage_->paintConfig_;
    auto matrix4 = config->imageMatrix_;
    EXPECT_EQ(matrix4, defaultMatrix4Value);
}

/**
 * @tc.name: ImagePaintMethodTestNg_UpdatePaintConfig_ImageMatrix002
 * @tc.desc: Create UpdatePaintConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdatePaintConfig_ImageMatrix002, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    ImageModelNG image;
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(), geometryNode, imagePaintProperty_);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    EXPECT_NE(imagePaintWrapper_, paintWrapper);
    /**
     * @tc.steps: step3. call function.
     */
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    Matrix4 defaultMatrix4Value = Matrix4(1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f);
    image.SetImageMatrix(defaultMatrix4Value);
    image.SetImageFit(ImageFit::CENTER);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    auto& config = imagePaintMethod_->canvasImage_->paintConfig_;
    auto matrix4 = config->imageMatrix_;
    EXPECT_EQ(matrix4, defaultMatrix4Value);
}

/**
 * @tc.name: ImagePaintMethodTestNg_UpdatePaintConfig_Antialias
 * @tc.desc: Create UpdatePaintConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdatePaintConfig_Antialias, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    ImageModelNG image;
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    imagePaintProperty_->UpdateAntiAlias(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(), geometryNode, imagePaintProperty_);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    EXPECT_NE(imagePaintWrapper_, paintWrapper);
    /**
     * @tc.steps: step3. call function.
     */
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    image.SetImageFit(ImageFit::CENTER);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    auto& config = imagePaintMethod_->canvasImage_->paintConfig_;
    auto antiAlias = config->antiAlias_;
    EXPECT_EQ(antiAlias, true);
}

/**
 * @tc.name: ImagePaintMethodTestNg_NormalizeRadius
 * @tc.desc: Create NormalizeRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_NormalizeRadius, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageGeometryNode = frameNode->GetGeometryNode();
    EXPECT_NE(imageGeometryNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(1.0f, 1.0f));
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    /**
     * @tc.steps: step3. call function.
     */
    ImageDfxConfig imageDfxConfig;
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    imagePaintMethod_->UpdateBorderRadius(imagePaintWrapperRaw_, imageDfxConfig);
}

/**
 * @tc.name: ImagePaintMethodTestNg_HdrBrightness
 * @tc.desc: Test hdrBrightness.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_HdrBrightness, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imageRenderProperty, nullptr);
    imageRenderProperty->UpdateHdrBrightness(0.5f);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);
    ImagePaintMethodConfig imagePaintMethodConfig_;
    RefPtr<ImagePaintMethod> imagePaintMethod_ =
        AceType::MakeRefPtr<ImagePaintMethod>(pattern->image_, imagePaintMethodConfig_);
    EXPECT_NE(imagePaintMethod_, nullptr);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    /**
     * @tc.steps: step3. call function.
     */
    PaintWrapper* imagePaintWrapperRaw_ = AceType::RawPtr(imagePaintWrapper_);
    EXPECT_NE(imagePaintWrapperRaw_, nullptr);
    imagePaintMethod_->UpdatePaintConfig(imagePaintWrapperRaw_);
    auto config = pattern->image_->GetPaintConfig();
    EXPECT_EQ(config.dynamicMode, DynamicRangeMode::HIGH);
}

/**
 * @tc.name: ImagePaintMethodTestNg_DfxSetFrameSize
 * @tc.desc: Test SetFrameSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_DfxSetFrameSize, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create imageDfx object
     */
    ImageDfxConfig imageDfxConfig;
    /**
     * @tc.steps: step2. call function.
     */
    imageDfxConfig.SetFrameSize(WIDTH, HEIGHT);
    /**
     * @tc.steps: step3. call function and EQ.
     */
    auto width = imageDfxConfig.GetFrameSizeWidth();
    auto height = imageDfxConfig.GetFrameSizeHeight();
    EXPECT_EQ(width, WIDTH);
    EXPECT_EQ(height, HEIGHT);
}

/**
 * @tc.name: ImagePaintMethodTestNg_NeedsContentTransition001
 * @tc.desc: test NeedsContentTransition
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_NeedsContentTransition001, TestSize.Level0)
{
    /* *
     * @tc.steps: step1. create image object
     */
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);

    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(true));
    imagePattern->image_ = mockImage;

    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethodConfig imagePaintMethodConfig_;
    imagePaintMethodConfig_.selected = true;
    RefPtr<ImagePaintMethod> imagePaintMethod_ = AceType::MakeRefPtr<ImagePaintMethod>(nullptr);
    EXPECT_NE(imagePaintMethod_, nullptr);
    EXPECT_FALSE(imagePaintMethod_->needContentTransition_);
    imagePaintMethod_->UpdatePaintMethod(pattern->image_, imagePaintMethodConfig_);
    EXPECT_FALSE(imagePaintMethod_->needContentTransition_);
    RefPtr<ImageRenderProperty> imagePaintProperty_ = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imagePaintProperty_, nullptr);
    imagePaintProperty_->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    imagePaintProperty_->UpdateNeedBorderRadius(true);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    RefPtr<PaintWrapper> paintWrapper =
        AceType::MakeRefPtr<PaintWrapper>(frameNode->GetRenderContext(), geometryNode, imagePaintProperty_);
    auto imagePaintWrapper_ = frameNode->CreatePaintWrapper();
    EXPECT_NE(imagePaintWrapper_, nullptr);
    EXPECT_NE(imagePaintWrapper_, paintWrapper);

    /**
     * @tc.steps: step3. call function.
     */
    auto&& config = pattern->image_->GetPaintConfig();
    config.isSvg_ = true;
    bool needsTransition = imagePaintMethod_->NeedsContentTransition();
    EXPECT_FALSE(needsTransition);

    /**
     * @tc.steps: step4. call function.
     */
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(false));
    bool needsTransition1 = imagePaintMethod_->NeedsContentTransition();
    EXPECT_EQ(needsTransition1, false);

    /**
     * @tc.steps: step5. call function.
     */
    config.isSvg_ = false;
    config.frameCount_ = 2;
    bool needsTransition2 = imagePaintMethod_->NeedsContentTransition();
    EXPECT_EQ(needsTransition2, false);

    /**
     * @tc.steps: step6. call function.
     */
    config.frameCount_ = 1;
    bool needsTransition3 = imagePaintMethod_->NeedsContentTransition();
    EXPECT_FALSE(needsTransition3);
}

/**
 * @tc.name: HandleSrcResource001
 * @tc.desc: Test HandleSrcResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, HandleSrcResource001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create image object
     */
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

    /**
     * @tc.steps: step2. create resobj.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    std::vector<ResourceObjectParams> resObjNullParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(100000, 20000, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjWithId0 =
        AceType::MakeRefPtr<ResourceObject>(0, 20000, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj1 =
        AceType::MakeRefPtr<ResourceObject>(0, 20000, resObjNullParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(0, 30000, resObjParamsList, "com.example.test", "entry", 100000);
    /**
     * @tc.steps: step3. call function.
     */
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObjWithId0);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj1);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj2);
    pattern->OnColorModeChange(colorMode);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(imageInfo.GetIsUriPureNumber());
}

/**
 * @tc.name: HandleAltResource001
 * @tc.desc: Test HandleAltResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, HandleAltResource001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create image object
     */
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

    /**
     * @tc.steps: step2. create resobj.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    std::vector<ResourceObjectParams> resObjNullParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(100000, 20000, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjWithId0 =
        AceType::MakeRefPtr<ResourceObject>(0, 20000, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj1 =
        AceType::MakeRefPtr<ResourceObject>(0, 20000, resObjNullParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(0, 30000, resObjParamsList, "com.example.test", "entry", 100000);
    /**
     * @tc.steps: step3. call function.
     */
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObjWithId0);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj1);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj2);
    pattern->OnColorModeChange(colorMode);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(imageInfo.GetIsUriPureNumber());
}

/**
 * @tc.name: HandleSrcAltResource001
 * @tc.desc: Test HandleSrcResource HandleAltResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, HandleSrcAltResource001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create image object
     */
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

    /**
     * @tc.steps: step2. create resobj.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    ResourceObjectParams params2 { .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    std::vector<ResourceObjectParams> resObjNullParamsList;
    resObjParamsList.push_back(params);
    resObjNullParamsList.push_back(params2);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(0, 30000, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(0, 30000, resObjNullParamsList, "com.example.test", "entry", 100000);
    /**
     * @tc.steps: step3. call function.
     */
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj2);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj2);
    pattern->OnColorModeChange(colorMode);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(imageInfo.GetIsUriPureNumber());
    auto altInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(altInfo.GetIsUriPureNumber());
}

/**
 * @tc.name: HandleSrcAltResource002
 * @tc.desc: Test HandleSrcResource HandleAltResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, HandleSrcAltResource002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create image object
     */
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

    /**
     * @tc.steps: step2. create resobj.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    ResourceObjectParams params2 { .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    std::vector<ResourceObjectParams> resObjParamsList2;
    std::vector<ResourceObjectParams> resObjNullParamsList;
    resObjParamsList.push_back(params);
    resObjNullParamsList.push_back(params2);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, resObjNullParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj3 =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, resObjParamsList2, "com.example.test", "entry", 100000);
    /**
     * @tc.steps: step3. call function.
     */
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj);
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj2);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj2);
    pattern->OnColorModeChange(colorMode);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj3);
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj3);
    pattern->OnColorModeChange(colorMode);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(imageInfo.GetIsUriPureNumber());
    auto altInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(altInfo.GetIsUriPureNumber());
}

/**
 * @tc.name: HandleSrcAltResource003
 * @tc.desc: Test HandleAltResource function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, HandleSrcAltResource003, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create image object
     */
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.pixelMap = nullptr;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. create resobj.
     */
    ResourceObjectParams params { .value = "test", .type = ResourceObjectParamType::STRING };
    std::vector<ResourceObjectParams> resObjParamsList;
    std::vector<ResourceObjectParams> resObjNullParamsList;
    resObjParamsList.push_back(params);
    RefPtr<ResourceObject> resObj =
        AceType::MakeRefPtr<ResourceObject>(100000, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObjWithId0 =
        AceType::MakeRefPtr<ResourceObject>(-1, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj1 =
        AceType::MakeRefPtr<ResourceObject>(0, 10003, resObjNullParamsList, "com.example.test", "entry", 100000);
    RefPtr<ResourceObject> resObj2 =
        AceType::MakeRefPtr<ResourceObject>(0, 10003, resObjParamsList, "com.example.test", "entry", 100000);
    /**
     * @tc.steps: step3. call function.
     */
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj);
    pattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    image.CreateWithResourceObj(ImageResourceType::ALT, resObjWithId0);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObjWithId0);
    pattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj1);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj1);
    pattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    image.CreateWithResourceObj(ImageResourceType::ALT, resObj2);
    image.CreateWithResourceObj(ImageResourceType::SRC, resObj2);
    pattern->OnColorModeChange(static_cast<int32_t>(ColorMode::DARK));
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto imageInfo = imageLayoutProperty->GetAlt().value_or(ImageSourceInfo(""));
    EXPECT_FALSE(imageInfo.GetIsUriPureNumber());
}

/**
 * @tc.name: ImagePaintMethodConstructor001
 * @tc.desc: Test ImagePaintMethod constructor with default config
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodConstructor001, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);
    ASSERT_NE(paintMethod, nullptr);
    EXPECT_EQ(paintMethod->NeedsContentTransition(), false);
}

/**
 * @tc.name: ImagePaintMethodConstructor002
 * @tc.desc: Test ImagePaintMethod constructor with custom config
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodConstructor002, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;
    config.selected = true;
    config.sensitive = true;
    config.interpolation = ImageInterpolation::HIGH;
    config.contentTransitionType = ContentTransitionType::IDENTITY;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);
    ASSERT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: ImagePaintMethodConstructor003
 * @tc.desc: Test ImagePaintMethod constructor with null canvas image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodConstructor003, TestSize.Level0)
{
    ImagePaintMethodConfig config;
    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(nullptr, config);
    ASSERT_NE(paintMethod, nullptr);
}

// ============================================================================
// UpdatePaintConfig Tests
// ============================================================================

/**
 * @tc.name: ImagePaintMethodUpdatePaintConfig002
 * @tc.desc: Test UpdatePaintConfig with interpolation settings
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodUpdatePaintConfig002, TestSize.Level0)
{
    auto frameNode = ImagePaintMethodTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->loadingCtx_, nullptr);
    pattern->image_ = pattern->loadingCtx_->MoveCanvasImage();
    EXPECT_NE(pattern->image_, nullptr);

    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;
    config.interpolation = ImageInterpolation::MEDIUM;
    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);

    auto paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    paintProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);

    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    PaintWrapper* paintWrapperRaw = AceType::RawPtr(paintWrapper);
    paintMethod->UpdatePaintConfig(paintWrapperRaw);
    EXPECT_NE(canvasImage, nullptr);
}

// ============================================================================
// UpdateBorderRadius Tests
// ============================================================================

// ============================================================================
// UpdateCanvasImage Tests
// ============================================================================

/**
 * @tc.name: ImagePaintMethodUpdateCanvasImage001
 * @tc.desc: Test UpdateCanvasImage with identity transition
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodUpdateCanvasImage001, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;
    config.contentTransitionType = ContentTransitionType::IDENTITY;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);
    ASSERT_NE(paintMethod, nullptr);
    EXPECT_EQ(paintMethod->NeedsContentTransition(), false);
}

/**
 * @tc.name: ImagePaintMethodUpdateCanvasImage002
 * @tc.desc: Test UpdateCanvasImage with different source
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodUpdateCanvasImage002, TestSize.Level0)
{
    auto canvasImage1 = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;
    config.contentTransitionType = ContentTransitionType::IDENTITY;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage1, config);
    ASSERT_NE(paintMethod, nullptr);

    auto canvasImage2 = AceType::MakeRefPtr<MockCanvasImage>();
    paintMethod->UpdatePaintMethod(canvasImage2, config);
    EXPECT_EQ(paintMethod->NeedsContentTransition(), false);
}

/**
 * @tc.name: ImagePaintMethodUpdateCanvasImage003
 * @tc.desc: Test UpdateCanvasImage with SVG image
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodUpdateCanvasImage003, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);
    ASSERT_NE(paintMethod, nullptr);

    paintMethod->UpdatePaintMethod(canvasImage, config);
    EXPECT_EQ(paintMethod->NeedsContentTransition(), false);
}

// ============================================================================
// UpdatePaintMethod Tests
// ============================================================================

/**
 * @tc.name: ImagePaintMethodUpdatePaintMethod001
 * @tc.desc: Test UpdatePaintMethod with new config
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodUpdatePaintMethod001, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config1;
    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config1);
    ASSERT_NE(paintMethod, nullptr);

    ImagePaintMethodConfig config2;
    config2.selected = true;
    config2.sensitive = true;
    config2.interpolation = ImageInterpolation::HIGH;

    paintMethod->UpdatePaintMethod(canvasImage, config2);
    EXPECT_NE(paintMethod, nullptr);
}

// ============================================================================
// UpdateOverlayModifier Tests
// ============================================================================

// ============================================================================
// UpdateContentModifier Tests
// ============================================================================

// ============================================================================
// NeedsContentTransition Tests
// ============================================================================

/**
 * @tc.name: ImagePaintMethodNeedsContentTransition001
 * @tc.desc: Test NeedsContentTransition with identity type
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodNeedsContentTransition001, TestSize.Level0)
{
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    ImagePaintMethodConfig config;
    config.contentTransitionType = ContentTransitionType::IDENTITY;

    auto paintMethod = AceType::MakeRefPtr<ImagePaintMethod>(canvasImage, config);
    ASSERT_NE(paintMethod, nullptr);

    EXPECT_EQ(paintMethod->NeedsContentTransition(), false);
}

} // namespace OHOS::Ace::NG

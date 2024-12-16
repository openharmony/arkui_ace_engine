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
#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace::NG {

class ImagePaintMethodTestNg : public ImageBases {};

/**
 * @tc.name: ImagePaintMethodTestNg_UpdateBorderRadius
 * @tc.desc: Create UpdateBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdateBorderRadius, TestSize.Level1)
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
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_UpdatePaintConfig, TestSize.Level1)
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
 * @tc.name: ImagePaintMethodTestNg_NormalizeRadius
 * @tc.desc: Create NormalizeRadius.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePaintMethodTestNg, ImagePaintMethodTestNg_NormalizeRadius, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
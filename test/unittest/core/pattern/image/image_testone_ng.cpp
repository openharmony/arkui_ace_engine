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

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImageTestOneNg : public ImageBases {
public:
};

/**
 * @tc.name: ImageColorFilterTest002
 * @tc.desc: Test image ColorFilter for jpg is set correctly.
 * @tc.type: FUNC
*/
HWTEST_F(ImageTestOneNg, ImageColorFilterTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    /**
     * set jpg picture
     */
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest003
 * @tc.desc: Test image ColorFilter for png is set correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    /**
     * set png picture
     */
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest004
 * @tc.desc: Test image ColorFilter for web picture is set correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    /**
     * set web picture
     */
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest005
 * @tc.desc: Test image ColorFilter for jpg is set correctly by empty array.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_NULL);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto matriCcolorFilter = imageRenderProperty->GetColorFilter();
    EXPECT_EQ(matriCcolorFilter.value(), COLOR_FILTER_NULL);
    frameNode->MarkModifyDone();

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest006
 * @tc.desc: Test image ColorFilter for png is set correctly by empty array.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_NULL);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_NULL);
    frameNode->MarkModifyDone();

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest007
 * desc: Test image ColorFilter for svg is set correctly by empty array.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_NULL);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_NULL);
    frameNode->MarkModifyDone();

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest008
 * @tc.desc: Test image ColorFilter for web picture is set correctly by empty array.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    /**
     * set web picture
    */
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest009
 * @tc.desc: Test whether image ColorFilter and FillColor affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set blue fillcolor
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageFill(Color::BLUE);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the color is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetForegroundColor().value(), Color::BLUE);
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set blue fillcolor
    */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageFill(Color::BLUE);

    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the color is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest010
 * @tc.desc: Test whether image ColorFilter and smoothedge affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set smoothedge
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetSmoothEdge(true);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the smoothedge is set
    */
    EXPECT_EQ(imageRenderProperty->GetSmoothEdge().value_or(0.0f), true);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set smoothedge
    */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetSmoothEdge(true);

    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the smoothedge is set
    */
    EXPECT_EQ(imageRenderProperty->GetSmoothEdge().value_or(0.0f), true);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest011
 * @tc.desc: Test image ColorFilter is set correctly for alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode without picture.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->loadingCtx_->GetSourceInfo().GetSrc(), "");
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest012
 * @tc.desc: Test image ColorFilter is set correctly for picture with web image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode with web image and sync mode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetSyncMode(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest013
 * @tc.desc: Test whether image ColorFilter and rendermode affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set rendermode
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageRenderMode(IMAGE_RENDERMODE_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the rendermode is set
    */
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode().value(), IMAGE_NO_RENDERMODE);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set rendermode
    */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageRenderMode(IMAGE_RENDERMODE_DEFAULT);

    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the rendermode is set
    */
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode().value(), IMAGE_NO_RENDERMODE);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest014
 * @tc.desc: Test whether image ColorFilter and ImageFit affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set imagefit
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageFit(IMAGE_FIT_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the imagefit is set
    */
    EXPECT_EQ(config->imageFit_, IMAGE_FIT_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
   /**
    * Creating a colorfilter through a graphical interface
    * Set imagefit
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageFit(IMAGE_FIT_DEFAULT);
    ASSERT_NE(imageRenderProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the imagefit is set
    */
    EXPECT_EQ(config->imageFit_, IMAGE_FIT_DEFAULT);;
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest015
 * @tc.desc: Test whether image ColorFilter and FillColor affect each other for svg image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode with svg image and sync mode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    image.SetSyncMode(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set blue fillcolor
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageFill(Color::BLUE);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
   /**
    * Creating a colorfilter through a graphical interface
    * Set red fillcolor
    */
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageFill(Color::RED);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::RED);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest016
 * @tc.desc: Test image ColorFilter is set correctly for picture with png image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode with web image and sync mode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    image.SetSyncMode(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest017
 * @tc.desc: Test image ColorFilter is set correctly by the methode of GetContentDrawFunction .
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    /**
     * @tc.steps: step3. create ImagePaintMethod.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    /**
     * @tc.steps: step4. ImagePaintMethod GetContentDrawFunction.
     */
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    PaintWrapper paintWrapper(nullptr, geometryNode, imageRenderProperty);
    auto pipeLine = PipelineBase::GetCurrentContext();
    pipeLine->SetIsRightToLeft(true);
    auto paintMethod = imagePaintMethod.GetContentDrawFunction(&paintWrapper);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);
    ASSERT_NE(paintMethod, nullptr);
    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(*config->colorFilter_.colorFilterMatrix_, COLOR_FILTER_DEFAULT);
    /**
     * Creating a colorfilter through a graphical interface
     * @tc.steps: step3. set drawingcolorFilter.
     */
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& paintConfig = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = paintConfig->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(config->colorFilter_.colorFilterDrawing_, drawingColorFilter);
}

/**
 * @tc.name: ImageColorFilterTest018
 * @tc.desc: Test whether image ColorFilter and ImageSourceSize affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set ImageSourceSize
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageSourceSize({ Dimension(IMAGE_SOURCESIZE_WIDTH), Dimension(IMAGE_SOURCESIZE_HEIGHT) });

    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the ImageSourceSize is set
    */
    EXPECT_EQ(imageLayoutProperty->GetSourceSize().value(),
        SizeF(static_cast<float>(Dimension(IMAGE_SOURCESIZE_WIDTH).ConvertToPx()),
            static_cast<float>(Dimension(IMAGE_SOURCESIZE_HEIGHT).ConvertToPx())));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set ImageSourceSize
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageSourceSize({ Dimension(IMAGE_SOURCESIZE_WIDTH), Dimension(IMAGE_SOURCESIZE_HEIGHT) });
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the ImageSourceSize is set
    */
    EXPECT_EQ(imageLayoutProperty->GetSourceSize().value(),
        SizeF(static_cast<float>(Dimension(IMAGE_SOURCESIZE_WIDTH).ConvertToPx()),
            static_cast<float>(Dimension(IMAGE_SOURCESIZE_HEIGHT).ConvertToPx())));
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest019
 * @tc.desc: Test whether image ColorFilter is set correctly when language changeing
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest019, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);
    /**
     * The default form of colorfilter
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(imagePattern->loadingCtx_);

    imagePattern->OnLanguageConfigurationUpdate();
    frameNode->MarkModifyDone();

    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
}

/**
 * @tc.name: ImageColorFilterTest020
 * @tc.desc: Test whether image ColorFilter and ImageInterpolation affect each other for svg image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode with svg image and sync mode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    image.SetSyncMode(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set ImageInterpolation
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageInterpolation(IMAGE_NO_INTERPOLATION);

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), IMAGE_NO_INTERPOLATION);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set ImageInterpolation
    */
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;

    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageInterpolation(IMAGE_NO_INTERPOLATION);

    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), IMAGE_NO_INTERPOLATION);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest021
 * @tc.desc: Test whether image ColorFilter and ImageRepeat affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set ImageRepeat
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetImageRepeat(IMAGE_NO_REPEAT);

    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the ImageRepeat is set
    */
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), IMAGE_NO_REPEAT);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set ImageRepeat
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetImageRepeat(IMAGE_NO_REPEAT);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the ImageRepeat is set
    */
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), IMAGE_NO_REPEAT);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest022
 * @tc.desc: Test whether image ColorFilter and MatchTextDirection affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set MatchTextDirection
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetMatchTextDirection(MATCHTEXTDIRECTION_DEFAULT);

    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the MatchTextDirection is set
    */
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection().value(), MATCHTEXTDIRECTION_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set MatchTextDirection
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetMatchTextDirection(MATCHTEXTDIRECTION_DEFAULT);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the MatchTextDirection is set
    */
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection().value(), MATCHTEXTDIRECTION_DEFAULT);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest023
 * @tc.desc: Test whether image ColorFilter and CopyOption affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set CopyOption
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetCopyOption(COPYOPTIONS_DEFAULT);

    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the CopyOption is set
    */
    EXPECT_EQ(frameNode->GetPattern<ImagePattern>()->copyOption_, COPYOPTIONS_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set CopyOption
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetCopyOption(COPYOPTIONS_DEFAULT);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the CopyOption is set
    */
    EXPECT_EQ(frameNode->GetPattern<ImagePattern>()->copyOption_, COPYOPTIONS_DEFAULT);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageColorFilterTest024
 * @tc.desc: Test whether image ColorFilter and AutoResize affect each other
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageColorFilterTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    /**
     * @tc.steps: step2. set maxtrixcolorFilter.
     */
    /**
     * Colorfilter in default array form
     * Set AutoResize
    */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    image.SetAutoResize(AUTORESIZE_DEFAULT);

    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    /**
     * Check if the AutoResize is set
    */
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), AUTORESIZE_DEFAULT);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. set drawingcolorFilter.
     */
    /**
    * Creating a colorfilter through a graphical interface
    * Set AutoResize
    */
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    image.SetAutoResize(AUTORESIZE_DEFAULT);
    /**
     * Check if the colorfilter is set correctly
    */
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);
    /**
     * Check if the AutoResize is set
    */
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), AUTORESIZE_DEFAULT);
    frameNode->MarkModifyDone();

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

void ImageModelNGTest001_SetLayoutProperty01(ImageModelNG &image)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    auto imageTestData = string("imageTestData");
    ImageModelNG::InitImage(frameNode, imageTestData);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_EQ(imageSourceInfo->GetSrc(), imageTestData);

    image.SetInitialSrc(frameNode, IMAGE_SRC_URL, BUNDLE_NAME, MODULE_NAME, false);
    imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_EQ(imageSourceInfo->GetModuleName(), MODULE_NAME);
    ASSERT_EQ(imageSourceInfo->GetSrc(), IMAGE_SRC_URL);

    auto imageSourceInfo_ = imageSourceInfo.value();
    ImageModelNG::SetAlt(frameNode, imageSourceInfo_);
    auto &&imageSourceInfoAlt = ImageModelNG::GetAlt(frameNode);
    ASSERT_EQ(imageSourceInfoAlt.GetModuleName(), MODULE_NAME);
    ASSERT_EQ(imageSourceInfoAlt.GetSrc(), IMAGE_SRC_URL);

    ImageModelNG::SetFitOriginSize(frameNode, false);
    EXPECT_EQ(imageLayoutProperty->GetFitOriginalSize().value(), false);

    auto autoResize = false;
    ImageModelNG::SetAutoResize(frameNode, autoResize);
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), autoResize);

    auto autoResize_ = ImageModelNG::GetAutoResize(frameNode);
    EXPECT_EQ(autoResize_, autoResize);

    ImageModelNG::SetImageSourceSize(
        frameNode, { Dimension(IMAGE_SOURCESIZE_WIDTH), Dimension(IMAGE_SOURCESIZE_HEIGHT) });
    EXPECT_EQ(imageLayoutProperty->GetSourceSize().value(),
        SizeF(static_cast<float>(Dimension(IMAGE_SOURCESIZE_WIDTH).ConvertToPx()),
            static_cast<float>(Dimension(IMAGE_SOURCESIZE_HEIGHT).ConvertToPx())));
}

void ImageModelNGTest001_SetRenderProperty01(ImageModelNG &image)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    ImageModelNG::SetAlt(frameNode, ImageSourceInfo { RESOURCE_URL });
    ImageModelNG::SetColorFilterMatrix(frameNode, COLOR_FILTER_DEFAULT);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), COLOR_FILTER_DEFAULT);
    ImageResizableSlice imageResizableSlice {
        .left = Dimension(1),
    };
    image.SetResizableSlice(imageResizableSlice);
    EXPECT_EQ(imageRenderProperty->GetImageResizableSlice().value(), imageResizableSlice);

    auto imageResizableSlice_ = ImageModelNG::GetResizableSlice(frameNode);
    EXPECT_EQ(imageResizableSlice_, imageResizableSlice);

    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);
    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetDrawingColorFilter(frameNode, drawingColorFilter);
    EXPECT_EQ(imageRenderProperty->GetDrawingColorFilter().value(), drawingColorFilter);

    auto drawingColorFilter_ = ImageModelNG::GetDrawingColorFilter(frameNode);
    EXPECT_EQ(drawingColorFilter_, drawingColorFilter);

    ImageModelNG::SetImageRepeat(frameNode, ImageRepeat::REPEAT_X);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), ImageRepeat::REPEAT_X);

    auto imageRepeat = ImageModelNG::GetObjectRepeat(frameNode);
    EXPECT_EQ(imageRepeat, ImageRepeat::REPEAT_X);

    ImageModelNG::SetImageRenderMode(frameNode, ImageRenderMode::ORIGINAL);
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode().value(), ImageRenderMode::ORIGINAL);

    ImageModelNG::SetMatchTextDirection(frameNode, true);
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection().value(), true);

    float smoothEdge = 3;
    ImageModelNG::SetSmoothEdge(frameNode, smoothEdge);
    EXPECT_EQ(imageRenderProperty->GetSmoothEdge().value(), smoothEdge);
}

void ImageModelNGTest001_MixedProperties01(ImageModelNG &image)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    ImageModelNG::SetImageFill(frameNode, Color::BLUE);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetForegroundColor().value(), Color::BLUE);

    auto fillColor = ImageModelNG::GetFillColor(frameNode);
    EXPECT_EQ(fillColor, Color::BLUE.GetValue());

    ImageModelNG::SetImageInterpolation(frameNode, ImageInterpolation::HIGH);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), ImageInterpolation::HIGH);
    EXPECT_EQ(imagePattern->GetImageInterpolation(), string("HIGH"));

    auto imageInterpolation = ImageModelNG::GetInterpolation(frameNode);
    EXPECT_EQ(imageInterpolation, ImageInterpolation::HIGH);

    image.ResetImageInterpolation(frameNode);
    EXPECT_EQ(imagePattern->GetDefaultInterpolation(), imageRenderProperty->GetImageInterpolation().value());

    ImageModelNG::SetImageFit(frameNode, ImageFit::FITWIDTH);
    EXPECT_EQ(imageRenderProperty->GetImageFit().value(), ImageFit::FITWIDTH);
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::FITWIDTH);

    auto imageFit = ImageModelNG::GetObjectFit(frameNode);
    EXPECT_EQ(imageFit, ImageFit::FITWIDTH);

    LoadImageSuccessEvent successEvent(
        IMAGE_WIDTH_DEFAULT, IMAGE_HEIGHT_DEFAULT, IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, -1);
    auto onComplete = [&successEvent](const LoadImageSuccessEvent& info) { successEvent = info; };
    ImageModelNG::SetOnComplete(frameNode, std::move(onComplete));
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);
    LoadImageSuccessEvent loadImageSuccessEvent(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT, 1);
    eventHub->FireCompleteEvent(loadImageSuccessEvent);
    EXPECT_EQ(successEvent.GetWidth(), loadImageSuccessEvent.GetWidth());
    EXPECT_EQ(successEvent.GetHeight(), loadImageSuccessEvent.GetHeight());
    EXPECT_EQ(successEvent.GetComponentWidth(), loadImageSuccessEvent.GetComponentWidth());
    EXPECT_EQ(successEvent.GetComponentHeight(), loadImageSuccessEvent.GetComponentHeight());
    EXPECT_EQ(successEvent.GetLoadingStatus(), loadImageSuccessEvent.GetLoadingStatus());

    LoadImageFailEvent failEvent(IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, "");
    auto onError = [&failEvent](const LoadImageFailEvent& info) { failEvent = info; };
    ImageModelNG::SetOnError(frameNode, std::move(onError));
    LoadImageFailEvent loadImageFailEvent(WIDTH, HEIGHT, "image load error!");
    eventHub->FireErrorEvent(loadImageFailEvent);
    EXPECT_EQ(failEvent.GetErrorMessage(), loadImageFailEvent.GetErrorMessage());
    EXPECT_EQ(failEvent.GetComponentWidth(), loadImageFailEvent.GetComponentWidth());
    EXPECT_EQ(failEvent.GetComponentHeight(), loadImageFailEvent.GetComponentHeight());
}

void ImageModelNGTest001_MixedProperties02(ImageModelNG &image)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto finishEventData = RADIUS_DEFAULT;
    auto finishEventCls = [&finishEventData]() { finishEventData = RADIUS_EXTREME;};
    ImageModelNG::SetOnSvgPlayFinish(frameNode, std::move(finishEventCls));
    eventHub->FireFinishEvent();
    EXPECT_EQ(finishEventData, RADIUS_EXTREME);

    auto finishEventIns = [&finishEventData]() { finishEventData = RADIUS_DEFAULT;};
    image.SetSvgAnimatorFinishEvent(std::move(finishEventIns));
    eventHub->FireFinishEvent();
    EXPECT_EQ(finishEventData, RADIUS_DEFAULT);

    auto getSrc = ImageModelNG::GetSrc(frameNode);
    ASSERT_EQ(getSrc.GetModuleName(), MODULE_NAME);
    ASSERT_EQ(getSrc.GetSrc(), IMAGE_SRC_URL);

    bool isAnimation = image.GetIsAnimation();
    ASSERT_EQ(isAnimation, false);

    auto imageRenderMode = ImageModelNG::GetImageRenderMode(frameNode);
    ASSERT_EQ(imageRenderMode, ImageRenderMode::ORIGINAL);

    image.SetCopyOption(frameNode, CopyOptions::InApp);
    EXPECT_EQ(imagePattern->copyOption_, CopyOptions::InApp);

    image.ResetAutoResize(frameNode);
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), imagePattern->GetDefaultAutoResize());

    ImageModelNG::SetDraggable(frameNode, true);
    EXPECT_EQ(frameNode->IsDraggable(), true);

    auto draggable = ImageModelNG::GetDraggable(frameNode);
    EXPECT_EQ(draggable, true);

    auto fitOriginalSize = ImageModelNG::GetFitOriginalSize(frameNode);
    EXPECT_EQ(fitOriginalSize, false);

    ImageModelNG::SetBackBorder(frameNode);
}

void ImageModelNGTest001_MixedProperties03(ImageModelNG &image)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    ImageModelNG::SetSyncMode(frameNode, SYNCMODE_DEFAULT);
    EXPECT_EQ(imagePattern->GetSyncLoad(), SYNCMODE_DEFAULT);

    image.EnableAnalyzer(false);
    ImageModelNG::EnableAnalyzer(frameNode, true);
    imagePattern->SetImageType(ImagePattern::ImageType::ANIMATION);
    ImageModelNG::ResetImageSrc(frameNode);
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_EQ(imageSourceInfo->GetSrc(), "");
    ASSERT_EQ(imageSourceInfo->GetModuleName(), "");

    ImageModelNG::ResetImageAlt(frameNode);
    EXPECT_EQ(imageLayoutProperty->GetAltValue(), ImageSourceInfo());

    image.SetDynamicRangeMode(DynamicRangeMode::HIGH);
    EXPECT_EQ(imageRenderProperty->GetDynamicMode().value(), DynamicRangeMode::HIGH);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetDynamicRangeMode().value(), DynamicRangeMode::HIGH);

    ImageModelNG::SetDynamicRangeMode(frameNode, DynamicRangeMode::STANDARD);
    EXPECT_EQ(imageRenderProperty->GetDynamicMode().value(), DynamicRangeMode::STANDARD);
    EXPECT_EQ(renderContext->GetDynamicRangeMode().value(), DynamicRangeMode::STANDARD);

    image.SetEnhancedImageQuality(AIImageQuality::HIGH);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::HIGH);

    ImageModelNG::SetEnhancedImageQuality(frameNode, AIImageQuality::NORMAL);
    EXPECT_EQ(imagePattern->GetImageQuality(), AIImageQuality::NORMAL);
}

/**
 * @tc.name: ImageModelNGTest001
 * @tc.desc: Test Image related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImageModelNGTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);

    auto [frameNode, v1, v2, v3] = GetCompoment();
    ImageModelNGTest001_SetLayoutProperty01(image);
    ImageModelNGTest001_SetRenderProperty01(image);
    ImageModelNGTest001_MixedProperties01(image);
    ImageModelNGTest001_MixedProperties02(image);
    ImageModelNGTest001_MixedProperties03(image);
    frameNode->MarkModifyDone();
}

/**
 * @tc.name: ImagePatternTest001
 * @tc.desc: Test ImagePattern related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestOneNg, ImagePatternTest001, TestSize.Level1)
{
    CreatePixelMapAnimator(1);
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();
    auto contain = "CONTAIN";
    auto cover = "COVER";
    auto fill = "FILL";
    auto fitWidth = "FITWIDTH";
    auto fitHeight = "FITHEIGHT";
    auto none = "NONE";
    auto scaleDown = "SCALE_DOWN";
    auto topLeft = "TOP_LEFT";
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::CONTAIN), contain);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::COVER), cover);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::FILL), fill);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::FITWIDTH), fitWidth);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::FITHEIGHT), fitHeight);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::NONE), none);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::SCALE_DOWN), scaleDown);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::TOP_LEFT), topLeft);
    EXPECT_EQ(imagePattern->GetImageFitStr(ImageFit::START), cover);

    auto noRepeat = "NO_REPEAT";
    auto repeat = "REPEAT_XY";
    auto repeatX = "REPEAT_X";
    auto repeatY = "REPEAT_Y";
    EXPECT_EQ(imagePattern->GetImageRepeatStr(ImageRepeat::NO_REPEAT), noRepeat);
    EXPECT_EQ(imagePattern->GetImageRepeatStr(ImageRepeat::REPEAT), repeat);
    EXPECT_EQ(imagePattern->GetImageRepeatStr(ImageRepeat::REPEAT_X), repeatX);
    EXPECT_EQ(imagePattern->GetImageRepeatStr(ImageRepeat::REPEAT_Y), repeatY);
}
} // namespace OHOS::Ace::NG
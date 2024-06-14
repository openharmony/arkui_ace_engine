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
} // namespace OHOS::Ace::NG
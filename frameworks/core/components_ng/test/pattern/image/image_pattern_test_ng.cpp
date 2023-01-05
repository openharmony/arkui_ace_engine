/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/test/mock/render/mock_canvas_image.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double RADIUS_DEFAULT = 300.0;
constexpr double IMAGE_WIDTH_DEFAULT = -1.0;
constexpr double IMAGE_HEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTWIDTH_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTHEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTSIZE_WIDTH = 400.0;
constexpr double IMAGE_COMPONENTSIZE_HEIGHT = 500.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_WIDTH = 600.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_HEIGHT = 700.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 200.0;
constexpr double ALT_SOURCESIZE_WIDTH = 100.0;
constexpr double ALT_SOURCESIZE_HEIGHT = 200.0;
constexpr Dimension IMAGE_SOURCEINFO_WIDTH = Dimension(IMAGE_SOURCESIZE_WIDTH);
constexpr Dimension IMAGE_SOURCEINFO_HEIGHT = Dimension(IMAGE_SOURCESIZE_HEIGHT);
constexpr Dimension ALT_SOURCEINFO_WIDTH = Dimension(ALT_SOURCESIZE_WIDTH);
constexpr Dimension ALT_SOURCEINFO_HEIGHT = Dimension(ALT_SOURCESIZE_HEIGHT);
constexpr ImageFit IMAGE_FIT_DEFAULT = ImageFit::COVER;
constexpr ImageRepeat IMAGE_REPEAT_DEFAULT = ImageRepeat::REPEAT;
constexpr ImageInterpolation IMAGE_INTERPOLATION_DEFAULT = ImageInterpolation::HIGH;
constexpr ImageRenderMode IMAGE_RENDERMODE_DEFAULT = ImageRenderMode::ORIGINAL;
constexpr bool MATCHTEXTDIRECTION_DEFAULT = true;
const Color SVG_FILL_COLOR_DEFAULT = Color::BLUE;
const std::vector<float> COLOR_FILTER_DEFAULT = { 1.0, 2.0, 3.0 };
constexpr bool SYNCMODE_DEFAULT = false;
constexpr CopyOptions COPYOPTIONS_DEFAULT = CopyOptions::None;
constexpr bool AUTORESIZE_DEFAULT = true;
constexpr bool FIT_ORIGINAL_SIZE_DEFAULT = true;
constexpr ImageRepeat IMAGE_NO_REPEAT = ImageRepeat::NO_REPEAT;
constexpr ImageInterpolation IMAGE_NO_INTERPOLATION = ImageInterpolation::NONE;
constexpr ImageRenderMode IMAGE_NO_RENDERMODE = ImageRenderMode::ORIGINAL;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
const std::string ALT_SRC_URL = "file://data/data/com.example.test/res/exampleAlt.jpg";
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string PNG_IMAGE = "/common/media/aaa.png";
const std::string WEB_IMAGE =
    "https://img2.baidu.com/it/u=3999091694,1705560228&fm=253&fmt=auto&app=120&f=JPEG?w=1280&h=800";
} // namespace

class ImagePatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateImageNode(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateImageNodeWithDefaultProp(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateSyncImageNode();
    static RefPtr<FrameNode> CreateSyncWebImageNode();
};

void ImagePatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ImagePatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> ImagePatternTestNg::CreateImageNode(
    const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    image.Create(src, pixMap, pixMap);
    image.SetAlt(alt);
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImagePatternTestNg::CreateImageNodeWithDefaultProp(
    const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    image.Create(src, pixMap, pixMap);
    image.SetAlt(alt);
    image.SetImageFill(SVG_FILL_COLOR_DEFAULT);
    image.SetImageFit(static_cast<int32_t>(IMAGE_FIT_DEFAULT));
    image.SetImageRenderMode(IMAGE_RENDERMODE_DEFAULT);
    image.SetImageInterpolation(IMAGE_INTERPOLATION_DEFAULT);
    image.SetMatchTextDirection(MATCHTEXTDIRECTION_DEFAULT);
    image.SetImageRepeat(IMAGE_REPEAT_DEFAULT);
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImagePatternTestNg::CreateSyncImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(PNG_IMAGE, true, pixMap);
    image.SetAlt(ALT_SRC_URL);
    image.SetSyncMode(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImagePatternTestNg::CreateSyncWebImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(WEB_IMAGE, true, pixMap);
    image.SetAlt(ALT_SRC_URL);
    image.SetSyncMode(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: ImagePatternCreator001
 * @tc.desc: Create ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCreator001, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
}

/**
 * @tc.name: ImagePatternCreator002
 * @tc.desc: Create ImagePattern with sync load.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCreator002, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateSyncImageNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
}

/**
 * @tc.name: ImagePatternCreator003
 * @tc.desc: Create ImagePattern with web image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCreator003, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateSyncWebImageNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
}

/**
 * @tc.name: ImagePatternModifyDone001
 * @tc.desc: When ImageComponent update its all properties, it will enter pattern's onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternModifyDone001, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(imagePattern->loadingCtx_ != nullptr);
    EXPECT_TRUE(imagePattern->altLoadingCtx_ != nullptr);
}

/**
 * @tc.name: UpdateInternalResource001
 * @tc.desc: Verify that ImagePattern can load correct resource Icon.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateInternalResource001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<IconTheme>()));
    auto frameNode = ImagePatternTestNg::CreateImageNode("", ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    /**
    //     case1 : imageSource is not internal resource, and it can not load correct resource Icon.
    */
    ImageSourceInfo sourceInfo;
    imagePattern->UpdateInternalResource(sourceInfo);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->IsInternalResource(), false);
    /**
    //     case2 : imageSource is an invalid internal resource, and it will not set IconPath.
    */
    sourceInfo.SetResourceId(InternalResource::ResourceId::NO_ID);
    imagePattern->UpdateInternalResource(sourceInfo);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc(), "");
    /**
    //     case3 : imageSource is internal resource, and it can successfully load correct resource Icon.
    */
    sourceInfo.SetResourceId(InternalResource::ResourceId::PLAY_SVG);
    imagePattern->UpdateInternalResource(sourceInfo);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: SetImagePaintConfig001
 * @tc.desc: When Image upload successfully, Imagepattern will set ImagePaintConfig to CanvaImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetImagePaintConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTestNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    frameNode->SetActive(true);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imageLayoutProperty->UpdateAlt(ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. AltImage loads successfully, and trigger alt callback.
     */
    imagePattern->altLoadingCtx_->DataReadyCallback(nullptr);
    imagePattern->altLoadingCtx_->SuccessCallback(nullptr);
    EXPECT_TRUE(imagePattern->altImage_ != nullptr);
    EXPECT_EQ(*imagePattern->altSrcRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_EQ(*imagePattern->altDstRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_TRUE(imagePattern->altImage_->paintConfig_ != nullptr);
    auto altImagePaintConfig = imagePattern->altImage_->GetPaintConfig();
    EXPECT_EQ(altImagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    /**
     * @tc.steps: step4. Image loads successfully, and trigger Pattern->OnImageLoadSuccess.
     */
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    EXPECT_TRUE(imagePattern->image_ != nullptr);
    EXPECT_EQ(imagePattern->srcRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    EXPECT_EQ(imagePattern->dstRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    EXPECT_TRUE(imagePattern->image_->paintConfig_ != nullptr);
    auto imagePaintConfig = imagePattern->image_->GetPaintConfig();
    EXPECT_EQ(imagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    /**
     * @tc.steps: step5. Image loads successfully, and clear alt data.
     */
    EXPECT_EQ(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    EXPECT_EQ(imagePattern->altSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->altDstRect_, nullptr);
}

/**
 * @tc.name: SetImagePaintConfig002
 * @tc.desc: Verify that Imagepattern will set correct ImagePaintConfig to CanvaImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetImagePaintConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode and CanvasImage.
     */
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(RADIUS_DEFAULT));
    frameNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    /**
     * @tc.steps: step2. get ImagePattern and set RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    EXPECT_TRUE(imageRenderProperty != nullptr);
    imageRenderProperty->UpdateNeedBorderRadius(true);
    /**
     * @tc.steps: step3. start set ImagePaintConfig and Verify it will be set correctly.
     */
    imagePattern->SetImagePaintConfig(canvasImage, RectF(), RectF(), true);
    EXPECT_TRUE(canvasImage->paintConfig_ != nullptr);
    auto paintConfig = canvasImage->GetPaintConfig();
    EXPECT_EQ(paintConfig.srcRect_, RectF());
    EXPECT_EQ(paintConfig.dstRect_, RectF());
    EXPECT_EQ(paintConfig.imageFit_, ImageFit::COVER);
    EXPECT_EQ(paintConfig.isSvg_, true);
    EXPECT_TRUE(paintConfig.borderRadiusXY_ != nullptr);
    for (auto point : *paintConfig.borderRadiusXY_) {
        EXPECT_EQ(point, PointF(RADIUS_DEFAULT, RADIUS_DEFAULT));
    }
}

/**
 * @tc.name: ImagePatternCallback001
 * @tc.desc: Verify that when ImageSourceInfo is not same, ImagePattern's callback will fail.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. ImageLoadingContext trigger callback, but ImageSourceInfo is not match.
     */
    imagePattern->altLoadingCtx_->SuccessCallback(nullptr);
    imagePattern->altLoadingCtx_->FailCallback("");
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    EXPECT_EQ(imagePattern->altSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->altDstRect_, nullptr);
    imagePattern->loadingCtx_->SuccessCallback(nullptr);
    imagePattern->loadingCtx_->FailCallback("");
    EXPECT_TRUE(imagePattern->image_ == nullptr);
}

/**
 * @tc.name: ImagePatternCallback002
 * @tc.desc: Verify that ImagePattern's Failcallback is common.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. Image loads failed, and trigger Pattern->OnImageLoadFail.
     */
    imagePattern->loadingCtx_->FailCallback("");
    EXPECT_TRUE(imagePattern->image_ == nullptr);
}

/**
 * @tc.name: ImagePatternOnNotifyMemoryLevelFunction001
 * @tc.desc: Verify that ImagePattern can do different data cleaning operation according to level.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternOnNotifyMemoryLevelFunction001, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    imagePattern->loadingCtx_ = nullptr;
    imagePattern->altLoadingCtx_ = nullptr;
    /**
     * @tc.cases: case1. Before Image load and ImagePattern windowHide, Image doesn't need resetLoading.
     */
    imagePattern->OnWindowHide();
    imagePattern->OnNotifyMemoryLevel(0);
    EXPECT_TRUE(imagePattern->isShow_ == false);
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->image_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    /**
     * @tc.cases: case2. ImagePattern windowShow and OnNotifyMemoryLevel function will return.
     */
    imagePattern->OnWindowShow();
    imagePattern->OnNotifyMemoryLevel(0);
    EXPECT_TRUE(imagePattern->isShow_ == true);
    /**
     * @tc.cases: case3. After Image load and ImagePattern windowHide, pattern will clean data and reset params.
     */
    imagePattern->OnWindowHide();
    imagePattern->OnNotifyMemoryLevel(0);
    EXPECT_TRUE(imagePattern->isShow_ == false);
    EXPECT_EQ(imagePattern->image_, nullptr);
    EXPECT_EQ(imagePattern->srcRect_, RectF());
    EXPECT_EQ(imagePattern->dstRect_, RectF());
    EXPECT_EQ(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    EXPECT_EQ(imagePattern->altSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->altDstRect_, nullptr);
}

/**
 * @tc.name: ImagePatternCreateNodePaintMethod001
 * @tc.desc: When ImageComponent load successfully, it will Create NodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternCreateNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(imagePattern->loadingCtx_ != nullptr);
    EXPECT_TRUE(imagePattern->altLoadingCtx_ != nullptr);
    /**
     * @tc.cases: case1. When SrcImage and AltImage load failed, it will not Create Image NodePaintMethod.
     */
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() == nullptr);
    /**
     * @tc.cases: case2. When SrcImage load successfully, it will Create SrcImage's NodePaintMethod.
     */
    imagePattern->image_ = imagePattern->loadingCtx_->MoveCanvasImage();
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() != nullptr);
    /**
     * @tc.cases: case3. When AltImage load successfully and altImage Rect is valid, it will Create AltImage's
     *                   NodePaintMethod.
     */
    imagePattern->image_ = nullptr;
    imagePattern->altImage_ = imagePattern->altLoadingCtx_->MoveCanvasImage();
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() == nullptr);
    imagePattern->altDstRect_ = std::make_unique<RectF>(RectF());
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() == nullptr);
    imagePattern->altSrcRect_ = std::make_unique<RectF>(RectF());
    imagePattern->altDstRect_.reset();
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() == nullptr);
    imagePattern->altDstRect_ = std::make_unique<RectF>(RectF());
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() != nullptr);
}

/**
 * @tc.name: ImagePaintMethod001
 * @tc.desc: ImagePaintMethod can get ContentDrawFunction and UpdatePaintConfig correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTestNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_);
    /**
     * @tc.steps: step3. ImagePaintMethod GetContentDrawFunction.
     */
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    EXPECT_TRUE(imageRenderProperty != nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    PaintWrapper paintWrapper(nullptr, geometryNode, imageRenderProperty);
    auto pipeLine = PipelineBase::GetCurrentContext();
    pipeLine->SetIsRightToLeft(true);
    auto paintMethod = imagePaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(imagePaintMethod.canvasImage_ != nullptr);
    EXPECT_TRUE(paintMethod != nullptr);
    EXPECT_EQ(imagePaintMethod.canvasImage_->paintConfig_->imageFit_, IMAGE_FIT_DEFAULT);
    EXPECT_EQ(imagePaintMethod.canvasImage_->paintConfig_->renderMode_, IMAGE_RENDERMODE_DEFAULT);
    EXPECT_EQ(imagePaintMethod.canvasImage_->paintConfig_->imageInterpolation_, IMAGE_INTERPOLATION_DEFAULT);
    EXPECT_EQ(imagePaintMethod.canvasImage_->paintConfig_->imageRepeat_, IMAGE_REPEAT_DEFAULT);
    EXPECT_EQ(imagePaintMethod.canvasImage_->paintConfig_->needFlipCanvasHorizontally_, MATCHTEXTDIRECTION_DEFAULT);
    EXPECT_EQ(*imagePaintMethod.canvasImage_->paintConfig_->colorFilter_, COLOR_FILTER_DEFAULT);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = ImagePatternTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = true;
    DirtySwapConfig config;
    config.skipMeasure = false;
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    layoutWrapper->skipMeasureContent_ = false;
    config.skipMeasure = true;
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = false;
    EXPECT_EQ(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), imagePattern->image_);
}

/**
 * @tc.name: ImageCreator001
 * @tc.desc: Create Image.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageCreator001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create("", false, pixMap);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: ImageCreator002
 * @tc.desc: Verify that ImageCreator can parse json with no attributes set.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageCreator002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create("", false, pixMap);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo().value(), ImageSourceInfo(""));
    EXPECT_EQ(imageLayoutProperty->GetImageFit(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetAlt(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetSyncMode(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetCopyOptions(), std::nullopt);
    EXPECT_TRUE(imageLayoutProperty->GetImageSizeStyle() == nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_TRUE(imageRenderProperty != nullptr);
    EXPECT_TRUE(imageRenderProperty->GetImagePaintStyle() == nullptr);
    EXPECT_TRUE(imageRenderProperty->GetNeedBorderRadius() == std::nullopt);
}

/**
 * @tc.name: ImageCreator003
 * @tc.desc: Verify that ImageCreator can parse json with all attributes set.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageCreator003, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, false, pixMap);
    image.SetImageFit(static_cast<int32_t>(IMAGE_FIT_DEFAULT));
    image.SetAlt(ALT_SRC_URL);
    image.SetSyncMode(SYNCMODE_DEFAULT);
    image.SetCopyOption(COPYOPTIONS_DEFAULT);
    image.SetAutoResize(AUTORESIZE_DEFAULT);
    image.SetFitOriginSize(FIT_ORIGINAL_SIZE_DEFAULT);
    image.SetImageSourceSize({ Dimension(IMAGE_SOURCESIZE_WIDTH), Dimension(IMAGE_SOURCESIZE_HEIGHT) });
    image.SetImageRenderMode(IMAGE_NO_RENDERMODE);
    image.SetImageInterpolation(IMAGE_NO_INTERPOLATION);
    image.SetImageRepeat(IMAGE_NO_REPEAT);
    image.SetMatchTextDirection(MATCHTEXTDIRECTION_DEFAULT);
    image.SetBackBorder();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfoValue(), ImageSourceInfo(IMAGE_SRC_URL));
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), IMAGE_FIT_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetAltValue(), ImageSourceInfo(ALT_SRC_URL));
    EXPECT_EQ(imageLayoutProperty->GetSyncModeValue(), false);
    EXPECT_EQ(imageLayoutProperty->GetCopyOptionsValue(), COPYOPTIONS_DEFAULT);
    EXPECT_TRUE(imageLayoutProperty->GetImageSizeStyle() != nullptr);
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), AUTORESIZE_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetFitOriginalSize().value(), FIT_ORIGINAL_SIZE_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetSourceSize().value(),
        SizeF(static_cast<float>(Dimension(IMAGE_SOURCESIZE_WIDTH).ConvertToPx()),
            static_cast<float>(Dimension(IMAGE_SOURCESIZE_HEIGHT).ConvertToPx())));

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_TRUE(imageRenderProperty != nullptr);
    EXPECT_TRUE(imageRenderProperty->GetImagePaintStyle() != nullptr);
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode().value(), IMAGE_NO_RENDERMODE);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), IMAGE_NO_INTERPOLATION);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), IMAGE_NO_REPEAT);
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection().value(), MATCHTEXTDIRECTION_DEFAULT);
    EXPECT_EQ(imageRenderProperty->GetNeedBorderRadiusValue(), true);
}

/**
 * @tc.name: ImageEventTest001
 * @tc.desc: Test Image onComplete event.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageEventTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, false, pixMap);
    LoadImageSuccessEvent curEvent(
        IMAGE_WIDTH_DEFAULT, IMAGE_HEIGHT_DEFAULT, IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, -1);
    auto onComplete = [&curEvent](const LoadImageSuccessEvent& info) { curEvent = info; };
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    EXPECT_TRUE(eventHub != nullptr);
    LoadImageSuccessEvent loadImageSuccessEvent(
        IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT, 1);
    eventHub->FireCompleteEvent(loadImageSuccessEvent);
    EXPECT_EQ(curEvent.GetWidth(), loadImageSuccessEvent.GetWidth());
    EXPECT_EQ(curEvent.GetHeight(), loadImageSuccessEvent.GetHeight());
    EXPECT_EQ(curEvent.GetComponentWidth(), loadImageSuccessEvent.GetComponentWidth());
    EXPECT_EQ(curEvent.GetComponentHeight(), loadImageSuccessEvent.GetComponentHeight());
    EXPECT_EQ(curEvent.GetLoadingStatus(), loadImageSuccessEvent.GetLoadingStatus());
}

/**
 * @tc.name: ImageEventTest002
 * @tc.desc: Test Image onError event.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageEventTest002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, false, pixMap);
    LoadImageFailEvent curEvent(IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, "");
    auto onError = [&curEvent](const LoadImageFailEvent& info) { curEvent = info; };
    image.SetOnError(std::move(onError));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    EXPECT_TRUE(eventHub != nullptr);
    LoadImageFailEvent loadImageFailEvent(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT, "image load error!");
    eventHub->FireErrorEvent(loadImageFailEvent);
    EXPECT_EQ(curEvent.GetErrorMessage(), loadImageFailEvent.GetErrorMessage());
    EXPECT_EQ(curEvent.GetComponentWidth(), loadImageFailEvent.GetComponentWidth());
    EXPECT_EQ(curEvent.GetComponentHeight(), loadImageFailEvent.GetComponentHeight());
}

/**
 * @tc.name: ImageSvgTest001
 * @tc.desc: Test svg FillColor is set correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageSvgTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, false, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    image.SetAlt(RESOURCE_URL);
    image.SetImageFill(Color::BLUE);
    EXPECT_NE(imageLayoutProperty->GetImageSourceInfo(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->fillColor_.value(), Color::BLUE);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->loadingCtx_->GetSourceInfo().GetSrc(), IMAGE_SRC_URL);
    EXPECT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageLayout001
 * @tc.desc: Verify that ImageComponent can resize with selfSize, whether has src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout002
 * @tc.desc: Verify that Image which has no SelfSize can resize with ContainerSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout002, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout003
 * @tc.desc: Verify that, when there is no srcImage, ImageComponent which has no SelfSize can resize with AltImageSize .
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout003, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    LayoutWrapper layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm != nullptr);
    /**
    //     corresponding ets code:
    //         Image().Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    LayoutConstraintF layoutConstraintSize;
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size != std::nullopt);
    EXPECT_EQ(size.value(), SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout004
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout004, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm4 != nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size4 != std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout005
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with AltImageSize and its aspectRatio.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout005, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout006
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent can resize with selfSize,
 *           whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout006, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout007
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent which has no size can resize with max
 *           LayoutConstraint, whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout007, TestSize.Level1)
{
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image().Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout008
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not, although fitOriginSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout008, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm4 != nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size4 != std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout009
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with ImageSize and its aspectRatio, although fitOriginalSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout009, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Widrh(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout010
 * @tc.desc: Verify that ImageComponent which has no SelfSize can resize with ImageSize, whether fitOriginalSize is set
 *           default. FitOriginalSize is false by default.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout010, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    LayoutWrapper layoutWrapper1(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper1);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));

    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper2(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper2);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout011
 * @tc.desc: Verify that ImageComponent which has no SelfSize, and there has no srcImage or altImage, ImageComponent can
 *           not resize its size.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayout011, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image()
    */
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm != nullptr);
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
}

/**
 * @tc.name: ImageLayoutFunction001
 * @tc.desc: Verify that ImageLayoutAlgorithm's Layout can carry out successfully.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageLayoutFunction001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    LayoutWrapper layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    /**
     * @tc.cases: case1. layoutWrapper->GetGeometryNode()->GetContent() == nullptr, func will return.
     */
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr));
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, loadingCtx);
    imageLayoutAlgorithm->Layout(&layoutWrapper);
    /**
     * @tc.cases: case2. layoutWrapper->GetGeometryNode()->GetContent() is true, func success.
     */
    geometryNode->SetContentSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    imageLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(loadingCtx->imageFit_, ImageFit::COVER);
    EXPECT_EQ(loadingCtx->autoResize_, true);
    EXPECT_EQ(loadingCtx->dstSize_, SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}
} // namespace OHOS::Ace::NG

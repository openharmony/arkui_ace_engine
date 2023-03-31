/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <optional>
#include "gtest/gtest.h"
#include "base/geometry/ng/rect_t.h"

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
constexpr double IMAGE_FRAMESIZE_WIDTH = 400.0;
constexpr double IMAGE_FRAMESIZE_HEIGHT = 500.0;
constexpr ImageFit IMAGE_FIT_DEFAULT = ImageFit::COVER;
constexpr ImageRepeat IMAGE_REPEAT_DEFAULT = ImageRepeat::REPEAT;
constexpr ImageInterpolation IMAGE_INTERPOLATION_DEFAULT = ImageInterpolation::HIGH;
constexpr ImageRenderMode IMAGE_RENDERMODE_DEFAULT = ImageRenderMode::ORIGINAL;
constexpr bool MATCHTEXTDIRECTION_DEFAULT = true;
const Color SVG_FILL_COLOR_DEFAULT = Color::BLUE;
const std::vector<float> COLOR_FILTER_DEFAULT = { 1.0, 2.0, 3.0 };
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
const std::string ALT_SRC_URL = "file://data/data/com.example.test/res/exampleAlt.jpg";
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
} // namespace

class ImagePatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<FrameNode> CreateImageNode(const std::string& src, const std::string& alt,
        RefPtr<PixelMap> pixMap = nullptr, const Color& svgFillColor = SVG_FILL_COLOR_DEFAULT,
        const ImageFit& imageFit = ImageFit::NONE, const ImageRenderMode& renderMode = ImageRenderMode::TEMPLATE,
        const ImageInterpolation& interpolation = ImageInterpolation::NONE,
        const ImageRepeat& imageRepeat = ImageRepeat::NO_REPEAT, const std::vector<float>& colorFilter = {},
        bool matchTextDirection = false);
};

void ImagePatternTest::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ImagePatternTest::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> ImagePatternTest::CreateImageNode(const std::string& src, const std::string& alt,
    RefPtr<PixelMap> pixMap, const Color& svgFillColor, const ImageFit& imageFit, const ImageRenderMode& renderMode,
    const ImageInterpolation& interpolation, const ImageRepeat& imageRepeat, const std::vector<float>& colorFilter,
    bool matchTextDirection)
{
    ImageModelNG image;
    image.Create(src, pixMap, pixMap);
    image.SetAlt(alt);
    image.SetImageFill(svgFillColor);
    if (imageFit != ImageFit::NONE) {
        image.SetImageFit(imageFit);
    }
    if (renderMode != ImageRenderMode::TEMPLATE) {
        image.SetImageRenderMode(renderMode);
    }
    if (interpolation != ImageInterpolation::NONE) {
        image.SetImageInterpolation(interpolation);
    }
    if (imageRepeat != ImageRepeat::NO_REPEAT) {
        image.SetImageRepeat(imageRepeat);
    }
    if (matchTextDirection) {
        image.SetMatchTextDirection(matchTextDirection);
    }
    if (!colorFilter.empty()) {
        image.SetColorFilterMatrix(colorFilter);
    }
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: ImagePatternCreator001
 * @tc.desc: Create ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternCreator001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
}

/**
 * @tc.name: ImagePatternModifyDone001
 * @tc.desc: When ImageComponent update its all properties, it will enter pattern's onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternModifyDone001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImagePatternTest, UpdateInternalResource001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<IconTheme>()));
    auto frameNode = ImagePatternTest::CreateImageNode("", ALT_SRC_URL);
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
 * @tc.name: SetImagePaintConfig002
 * @tc.desc: Verify that Imagepattern will set correct ImagePaintConfig to CanvaImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, SetImagePaintConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode and CanvasImage.
     */
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
 * @tc.name: ImagePatternOnNotifyMemoryLevelFunction001
 * @tc.desc: Verify that ImagePattern can do different data cleaning operation according to level.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternOnNotifyMemoryLevelFunction001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImagePatternTest, ImagePatternCreateNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImagePatternTest, ImagePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr, SVG_FILL_COLOR_DEFAULT,
        IMAGE_FIT_DEFAULT, IMAGE_RENDERMODE_DEFAULT, IMAGE_INTERPOLATION_DEFAULT, IMAGE_REPEAT_DEFAULT,
        COLOR_FILTER_DEFAULT, MATCHTEXTDIRECTION_DEFAULT);
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
    geometryNode->SetFrameSize(SizeF(IMAGE_FRAMESIZE_WIDTH, IMAGE_FRAMESIZE_HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(IMAGE_FRAMESIZE_WIDTH, IMAGE_FRAMESIZE_HEIGHT));
    PaintWrapper paintWrapper(nullptr, geometryNode, imageRenderProperty);
    auto pipeLine = PipelineBase::GetCurrentContext();
    pipeLine->SetIsRightToLeft(true);
    auto paintMethod = imagePaintMethod.GetContentDrawFunction(&paintWrapper);
    EXPECT_TRUE(imagePaintMethod.canvasImage_ != nullptr);
    EXPECT_TRUE(paintMethod != nullptr);
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
HWTEST_F(ImagePatternTest, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
} // namespace OHOS::Ace::NG

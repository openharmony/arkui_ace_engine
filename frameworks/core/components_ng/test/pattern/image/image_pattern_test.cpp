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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double IMAGE_FRAMESIZE_WIDTH = 400.0;
constexpr double IMAGE_FRAMESIZE_HEIGHT = 500.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 300.0;
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
        image.SetImageFit(static_cast<int32_t>(imageFit));
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
    if (!matchTextDirection) {
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
    //     case2 : imageSource is internal resource, and it can successfully load correct resource Icon.
    */
    sourceInfo.SetResourceId(InternalResource::ResourceId::PLAY_SVG);
    imagePattern->UpdateInternalResource(sourceInfo);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: SetImagePaintConfig001
 * @tc.desc: When Image upload successfully, Imagepattern will set ImagePaintConfit to CanvaImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, SetImagePaintConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr, SVG_FILL_COLOR_DEFAULT,
        IMAGE_FIT_DEFAULT, IMAGE_RENDERMODE_DEFAULT, IMAGE_INTERPOLATION_DEFAULT, IMAGE_REPEAT_DEFAULT,
        COLOR_FILTER_DEFAULT, MATCHTEXTDIRECTION_DEFAULT);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_FRAMESIZE_WIDTH, IMAGE_FRAMESIZE_HEIGHT));
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
    imagePattern->altLoadingCtx_->OnDataReady(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT), nullptr);
    imagePattern->altLoadingCtx_->OnLoadSuccess(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT));
    EXPECT_TRUE(imagePattern->lastAltCanvasImage_ != nullptr);
    EXPECT_EQ(*imagePattern->lastAltSrcRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_EQ(*imagePattern->lastAltDstRect_, RectF(0, 0, ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
    EXPECT_TRUE(imagePattern->lastAltCanvasImage_->paintConfig_ != nullptr);
    auto altImagePaintConfig = imagePattern->lastAltCanvasImage_->GetPaintConfig();
    EXPECT_EQ(altImagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    EXPECT_EQ(altImagePaintConfig.renderMode_, IMAGE_RENDERMODE_DEFAULT);
    EXPECT_EQ(altImagePaintConfig.imageInterpolation_, IMAGE_INTERPOLATION_DEFAULT);
    EXPECT_EQ(altImagePaintConfig.imageRepeat_, IMAGE_REPEAT_DEFAULT);
    EXPECT_EQ(*altImagePaintConfig.colorFilter_, COLOR_FILTER_DEFAULT);
    EXPECT_EQ(altImagePaintConfig.needFlipCanvasHorizontally_, false);
    /**
     * @tc.steps: step4. Image loads successfully, and trigger Pattern->OnImageLoadSuccess.
     */
    imagePattern->loadingCtx_->OnLoadSuccess(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    EXPECT_TRUE(imagePattern->lastCanvasImage_ != nullptr);
    EXPECT_EQ(imagePattern->lastSrcRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    EXPECT_EQ(imagePattern->lastDstRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    EXPECT_TRUE(imagePattern->lastCanvasImage_->paintConfig_ != nullptr);
    auto imagePaintConfig = imagePattern->lastCanvasImage_->GetPaintConfig();
    EXPECT_EQ(imagePaintConfig.imageFit_, IMAGE_FIT_DEFAULT);
    EXPECT_EQ(imagePaintConfig.renderMode_, IMAGE_RENDERMODE_DEFAULT);
    EXPECT_EQ(imagePaintConfig.imageInterpolation_, IMAGE_INTERPOLATION_DEFAULT);
    EXPECT_EQ(imagePaintConfig.imageRepeat_, IMAGE_REPEAT_DEFAULT);
    EXPECT_EQ(*imagePaintConfig.colorFilter_, COLOR_FILTER_DEFAULT);
    EXPECT_EQ(imagePaintConfig.needFlipCanvasHorizontally_, false);
    /**
     * @tc.steps: step5. Image loads successfully, and clear alt data.
     */
    EXPECT_EQ(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->lastAltCanvasImage_, nullptr);
    EXPECT_EQ(imagePattern->lastAltSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->lastAltDstRect_, nullptr);
}

/**
 * @tc.name: ImagePatternCallback001
 * @tc.desc: Verify that when ImageSourceInfo is not same, ImagePattern's callback will fail.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_FRAMESIZE_WIDTH, IMAGE_FRAMESIZE_HEIGHT));
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
    imagePattern->altLoadingCtx_->OnLoadSuccess(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imagePattern->altLoadingCtx_->OnLoadFail(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT), "",
        ImageLoadingCommand::LOAD_DATA_FAIL);
    EXPECT_EQ(imagePattern->lastAltCanvasImage_, nullptr);
    EXPECT_EQ(imagePattern->lastAltSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->lastAltDstRect_, nullptr);
    imagePattern->loadingCtx_->OnLoadSuccess(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    imagePattern->loadingCtx_->OnLoadFail(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT), "",
        ImageLoadingCommand::LOAD_DATA_FAIL);
    EXPECT_TRUE(imagePattern->lastCanvasImage_ == nullptr);
}

/**
 * @tc.name: ImagePatternCallback002
 * @tc.desc: Verify that ImagePattern's Failcallback is common.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImagePatternTest::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(IMAGE_FRAMESIZE_WIDTH, IMAGE_FRAMESIZE_HEIGHT));
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
    imagePattern->loadingCtx_->OnLoadFail(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT), "",
        ImageLoadingCommand::LOAD_DATA_FAIL);
    EXPECT_TRUE(imagePattern->lastCanvasImage_ == nullptr);
}
} // namespace OHOS::Ace::NG

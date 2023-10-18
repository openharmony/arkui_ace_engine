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

#include <optional>
#include <utility>
#include <vector>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "core/common/container.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_paint_method.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/test/mock/render/mock_canvas_image.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double RADIUS_DEFAULT = 50.0;
constexpr double RADIUS_EXTREME = 300.0;
constexpr double IMAGE_WIDTH_DEFAULT = -1.0;
constexpr double IMAGE_HEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTWIDTH_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTHEIGHT_DEFAULT = -1.0;
constexpr double WIDTH = 400.0;
constexpr double HEIGHT = 500.0;
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
const SizeF CONTENT_SIZE = SizeF(400.0f, 500.0f);
const OffsetF CONTENT_OFFSET = OffsetF(50.0f, 60.0f);
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
const std::string BUNDLE_NAME;
const std::string MODULE_NAME;
const std::string WEB_IMAGE =
    "https://img2.baidu.com/it/u=3999091694,1705560228&fm=253&fmt=auto&app=120&f=JPEG?w=1280&h=800";
} // namespace

class ImageTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateImageNode(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateImageNodeWithDefaultProp(
        const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap = nullptr);
    static RefPtr<FrameNode> CreateSyncImageNode();
    static RefPtr<FrameNode> CreateSyncWebImageNode();
};

void ImageTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ImageTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> ImageTestNg::CreateImageNode(const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    image.Create(src, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetAlt(alt);
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageTestNg::CreateImageNodeWithDefaultProp(
    const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    image.Create(src, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetAlt(alt);
    image.SetImageFill(SVG_FILL_COLOR_DEFAULT);
    image.SetImageFit(IMAGE_FIT_DEFAULT);
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

RefPtr<FrameNode> ImageTestNg::CreateSyncImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(PNG_IMAGE, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetAlt(ALT_SRC_URL);
    image.SetSyncMode(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageTestNg::CreateSyncWebImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(WEB_IMAGE, pixMap, BUNDLE_NAME, MODULE_NAME);
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
HWTEST_F(ImageTestNg, ImagePatternCreator001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
}

/**
 * @tc.name: ImagePatternCreator002
 * @tc.desc: Create ImagePattern with sync load.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCreator002, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateSyncImageNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
}

/**
 * @tc.name: ImagePatternCreator003
 * @tc.desc: Create ImagePattern with web image and sync mode.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCreator003, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateSyncWebImageNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
}

/**
 * @tc.name: ImagePatternModifyDone001
 * @tc.desc: When ImageComponent update its all properties, it will enter pattern's onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternModifyDone001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    frameNode->MarkModifyDone();
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_NE(imagePattern->altLoadingCtx_, nullptr);
}

/**
 * @tc.name: ImagePatternModifyDone002
 * @tc.desc: When enter pattern's onModifyDone, check obscured and events.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetCopyOption(CopyOptions::InApp);
    /**
     * @tc.steps: step2. call MarkModifyDone and check obscured and events
     * @tc.expected: step2. has_value return false and events are not nullptr
     */
    frameNode->MarkModifyDone();
    EXPECT_FALSE(frameNode->GetRenderContext()->GetObscured().has_value());
    EXPECT_NE(imagePattern->longPressEvent_, nullptr);
    EXPECT_NE(imagePattern->clickEvent_, nullptr);
    EXPECT_NE(imagePattern->mouseEvent_, nullptr);
    /**
     * @tc.steps: step3. set obscured
     */
    std::vector<ObscuredReasons> reasons;
    reasons.emplace_back(static_cast<ObscuredReasons>(0));
    frameNode->GetRenderContext()->UpdateObscured(reasons);
    /**
     * @tc.steps: step4. call MarkModifyDone and check obscured
     * @tc.expected: step4. has_value return true and and events are nullptr
     */
    frameNode->MarkModifyDone();
    EXPECT_TRUE(frameNode->GetRenderContext()->GetObscured().has_value());
    EXPECT_EQ(imagePattern->longPressEvent_, nullptr);
    EXPECT_EQ(imagePattern->clickEvent_, nullptr);
    EXPECT_EQ(imagePattern->mouseEvent_, nullptr);
}

/**
 * @tc.name: UpdateInternalResource001
 * @tc.desc: Verify that ImagePattern can load correct resource Icon.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, UpdateInternalResource001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode("", ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IconTheme>()));
    /**
    //     case1 : imageSource is not internal resource, and it can not load correct resource Icon.
    */
    ImageSourceInfo sourceInfo;
    imagePattern->UpdateInternalResource(sourceInfo);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
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

/** CalcImageContentPaintSize
 * @tc.name: SetImagePaintConfig001
 * @tc.desc: When Image upload successfully, ImagePattern will set ImagePaintConfig to CanvasImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, SetImagePaintConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
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
    EXPECT_EQ(imagePattern->srcRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    EXPECT_EQ(imagePattern->dstRect_, RectF(0, 0, IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    ASSERT_NE(imagePattern->image_->paintConfig_, nullptr);
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
 * @tc.desc: Verify that ImagePattern will set correct ImagePaintConfig to CanvasImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, SetImagePaintConfig002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode and CanvasImage.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(RADIUS_DEFAULT));
    frameNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    /**
     * @tc.steps: step2. get ImagePattern and set RadiusProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    imageRenderProperty->UpdateNeedBorderRadius(true);
    /**
     * @tc.steps: step3. start set ImagePaintConfig and Verify it will be set correctly.
     */
    imagePattern->SetImagePaintConfig(canvasImage, RectF(), RectF(), true);
    ASSERT_NE(canvasImage->paintConfig_, nullptr);
    auto paintConfig = canvasImage->GetPaintConfig();
    EXPECT_EQ(paintConfig.srcRect_, RectF());
    EXPECT_EQ(paintConfig.dstRect_, RectF());
    EXPECT_EQ(paintConfig.imageFit_, ImageFit::COVER);
    EXPECT_TRUE(paintConfig.isSvg_);
}

/**
 * @tc.name: ImagePatternCallback001
 * @tc.desc: trigger image load fail.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. ImageLoadingContext trigger callback, but ImageSourceInfo is not match.
     */
    imagePattern->altLoadingCtx_->FailCallback("");
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    EXPECT_EQ(imagePattern->altSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->altDstRect_, nullptr);

    imagePattern->loadingCtx_->FailCallback("");
    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ImagePatternCallback002
 * @tc.desc: Verify that ImagePattern's Failcallback is common.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. get ImagePattern and enter markModifyDone, load ImageLoadingContext.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT));
    frameNode->MarkModifyDone();
    /**
     * @tc.steps: step3. Image loads failed, and trigger Pattern->OnImageLoadFail.
     */
    imagePattern->loadingCtx_->FailCallback("");
    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ImagePatternOnNotifyMemoryLevelFunction001
 * @tc.desc: Verify that ImagePattern can do different data cleaning operation according to level.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternOnNotifyMemoryLevelFunction001, TestSize.Level1)
{
    EXPECT_CALL(*(MockPipelineBase::GetCurrent()), FlushMessages()).Times(2);
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
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
    EXPECT_TRUE(imagePattern->isShow_);
    /**
     * @tc.cases: case3. After Image load and ImagePattern windowHide, pattern will clean data and reset params.
     */
    imagePattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->OnWindowHide();
    imagePattern->OnNotifyMemoryLevel(0);
    EXPECT_FALSE(imagePattern->isShow_);
    EXPECT_EQ(imagePattern->image_, nullptr);
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
HWTEST_F(ImageTestNg, ImagePatternCreateNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    frameNode->MarkModifyDone();
    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
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
    EXPECT_EQ(imagePattern->CreateNodePaintMethod(), nullptr);
    imagePattern->altDstRect_ = std::make_unique<RectF>(RectF());
    EXPECT_EQ(imagePattern->CreateNodePaintMethod(), nullptr);
    imagePattern->altSrcRect_ = std::make_unique<RectF>(RectF());
    imagePattern->altDstRect_.reset();
    EXPECT_EQ(imagePattern->CreateNodePaintMethod(), nullptr);
    imagePattern->altDstRect_ = std::make_unique<RectF>(RectF());
    EXPECT_NE(imagePattern->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: ImagePatternCreateNodePaintMethod002
 * @tc.desc: When SrcImage and AltImage are not loaded, check return of CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create ImagePattern and ImageLayoutProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step3. set image_ = nullptr, altImage_ = nullptr
     */
    imagePattern->image_ = nullptr;
    imagePattern->altImage_ = nullptr;
    /**
     * @tc.steps: step4. call CreateNodePaintMethod.
     * @tc.expected: step4. return nullptr
     */
    EXPECT_EQ(imagePattern->CreateNodePaintMethod(), nullptr);
    /**
     * @tc.steps: step5. set obscuredImage_ is not nullptr;
     */
    imagePattern->obscuredImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    /**
     * @tc.steps: step6. call CreateNodePaintMethod.
     * @tc.expected: step6. return is not nullptr
     */
    EXPECT_NE(imagePattern->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: ImagePatternCreateObscuredImageIfNeed001
 * @tc.desc: Check CreateObscuredImage method if will create ObscuredImage
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePatternCreateObscuredImageIfNeed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create ImagePattern and ImageLayoutProperty.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step3. set invalid selfIdealSize.
     */
    LayoutConstraintF layoutConstraint;
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    EXPECT_FALSE(layoutConstraint.selfIdealSize.IsValid());
    /**
     * @tc.steps: step4. check obscuredImage_.
     * @tc.expected: step4. obscuredImage is nullptr
     */
    imagePattern->CreateObscuredImage();
    EXPECT_EQ(imagePattern->obscuredImage_, nullptr);
    /**
     * @tc.steps: step5. set valid obscured.
     */
    std::vector<ObscuredReasons> reasons;
    reasons.emplace_back(static_cast<ObscuredReasons>(0));
    frameNode->GetRenderContext()->UpdateObscured(reasons);
    /**
     * @tc.steps: step6. check obscuredImage_.
     * @tc.expected: step6. obscuredImage_ is nullptr
     */
    imagePattern->CreateObscuredImage();
    EXPECT_EQ(imagePattern->obscuredImage_, nullptr);
    /**
     * @tc.steps: step7. set valid selfIdealSize.
     */
    layoutConstraint.selfIdealSize.width_ = 10.0;
    layoutConstraint.selfIdealSize.height_ = 10.0;
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    /**
     * @tc.steps: step8. check obscuredImage_.
     * @tc.expected: step8. obscuredImage_ is not nullptr
     */
    imagePattern->CreateObscuredImage();
    EXPECT_NE(imagePattern->obscuredImage_, nullptr);
    /**
     * @tc.steps: step9. set empty obscured.
     */
    imagePattern->CreateObscuredImage();
    reasons.clear();
    frameNode->GetRenderContext()->UpdateObscured(reasons);
    /**
     * @tc.steps: step10. check obscuredImage_.
     * @tc.expected: step10. obscuredImage_ is not nullptr
     */
    imagePattern->CreateObscuredImage();
    EXPECT_NE(imagePattern->obscuredImage_, nullptr);
}

/**
 * @tc.name: ImagePaintMethod002
 * @tc.desc: ImagePaintMethod can update radius correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    // update border radius
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(RADIUS_DEFAULT));
    frameNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(pattern->image_, true);
    /**
     * @tc.steps: step3. ImagePaintMethod GetContentDrawFunction.
     */
    auto renderProps = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProps, nullptr);
    renderProps->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    renderProps->UpdateNeedBorderRadius(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(WIDTH, HEIGHT));
    geometryNode->SetFrameOffset(OffsetF(WIDTH, HEIGHT));
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), geometryNode, renderProps);
    auto paintMethod = imagePaintMethod.GetContentDrawFunction(&paintWrapper);

    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);
    ASSERT_NE(paintMethod, nullptr);
    auto config = *imagePaintMethod.canvasImage_->paintConfig_;
    EXPECT_EQ(config.imageRepeat_, ImageRepeat::REPEAT_X);
    EXPECT_TRUE(config.borderRadiusXY_ != nullptr);
    EXPECT_EQ(config.borderRadiusXY_->at(0).GetX(), RADIUS_DEFAULT);

    /**
     * @tc.steps: step3. Update image radius.
     * radius should be normalized
     */
    borderRadius.SetRadius(Dimension(RADIUS_EXTREME));
    frameNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    paintMethod = imagePaintMethod.GetContentDrawFunction(&paintWrapper);
    config = *imagePaintMethod.canvasImage_->paintConfig_;
    EXPECT_NE(config.borderRadiusXY_->at(0).GetX(), RADIUS_EXTREME);
    EXPECT_EQ(config.borderRadiusXY_->at(0).GetX(), WIDTH / 2);
    EXPECT_EQ(config.borderRadiusXY_->at(0).GetY(), WIDTH / 2);
}

/**
 * @tc.name: ImagePaintMethod001
 * @tc.desc: ImagePaintMethod can get ContentDrawFunction and UpdatePaintConfig correctly.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImagePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    /**
     * @tc.steps: step2. create ImagePaintMethod.
     */
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, true);
    /**
     * @tc.steps: step3. ImagePaintMethod GetContentDrawFunction.
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
    EXPECT_EQ(config->imageFit_, IMAGE_FIT_DEFAULT);
    EXPECT_EQ(config->renderMode_, IMAGE_RENDERMODE_DEFAULT);
    EXPECT_EQ(config->imageInterpolation_, IMAGE_INTERPOLATION_DEFAULT);
    EXPECT_EQ(config->imageRepeat_, IMAGE_REPEAT_DEFAULT);
    EXPECT_EQ(config->flipHorizontally_, MATCHTEXTDIRECTION_DEFAULT);
    EXPECT_EQ(*config->colorFilter_, COLOR_FILTER_DEFAULT);
    EXPECT_EQ(config->obscuredReasons_, std::vector<ObscuredReasons>());

    /**
     * @tc.steps: step4. ImagePaintMethod GetOverlayDrawFunction
     */

    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<TextTheme>()));

    auto overlayPaintMethod = imagePaintMethod.GetOverlayDrawFunction(&paintWrapper);
    EXPECT_TRUE(overlayPaintMethod);
    EXPECT_TRUE(imagePaintMethod.selected_);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
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
HWTEST_F(ImageTestNg, ImageCreator001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create("", pixMap, BUNDLE_NAME, MODULE_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: ImageCreator002
 * @tc.desc: Verify that ImageCreator can parse json with no attributes set.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageCreator002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create("", pixMap, BUNDLE_NAME, MODULE_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo().value(), ImageSourceInfo(""));
    EXPECT_EQ(imageLayoutProperty->GetImageFit(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetAlt(), std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetImageSizeStyle(), nullptr);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetImagePaintStyle(), nullptr);
    EXPECT_EQ(imageRenderProperty->GetNeedBorderRadius(), std::nullopt);
}

/**
 * @tc.name: ImageCreator003
 * @tc.desc: Verify that ImageCreator can parse json with all attributes set.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageCreator003, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    image.SetImageFit(IMAGE_FIT_DEFAULT);
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
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfoValue(), ImageSourceInfo(IMAGE_SRC_URL));
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), IMAGE_FIT_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetAltValue(), ImageSourceInfo(ALT_SRC_URL));
    EXPECT_EQ(frameNode->GetPattern<ImagePattern>()->syncLoad_, false);
    EXPECT_EQ(frameNode->GetPattern<ImagePattern>()->copyOption_, COPYOPTIONS_DEFAULT);
    EXPECT_TRUE(imageLayoutProperty->GetImageSizeStyle() != nullptr);
    EXPECT_EQ(imageLayoutProperty->GetAutoResize().value(), AUTORESIZE_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetFitOriginalSize().value(), FIT_ORIGINAL_SIZE_DEFAULT);
    EXPECT_EQ(imageLayoutProperty->GetSourceSize().value(),
        SizeF(static_cast<float>(Dimension(IMAGE_SOURCESIZE_WIDTH).ConvertToPx()),
            static_cast<float>(Dimension(IMAGE_SOURCESIZE_HEIGHT).ConvertToPx())));

    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    ASSERT_NE(imageRenderProperty->GetImagePaintStyle(), nullptr);
    EXPECT_EQ(imageRenderProperty->GetImageRenderMode().value(), IMAGE_NO_RENDERMODE);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), IMAGE_NO_INTERPOLATION);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), IMAGE_NO_REPEAT);
    EXPECT_EQ(imageRenderProperty->GetMatchTextDirection().value(), MATCHTEXTDIRECTION_DEFAULT);
    EXPECT_TRUE(imageRenderProperty->GetNeedBorderRadiusValue());
}

/**
 * @tc.name: ImageEventTest001
 * @tc.desc: Test Image onComplete event.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageEventTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    LoadImageSuccessEvent curEvent(
        IMAGE_WIDTH_DEFAULT, IMAGE_HEIGHT_DEFAULT, IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, -1);
    auto onComplete = [&curEvent](const LoadImageSuccessEvent& info) { curEvent = info; };
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);
    LoadImageSuccessEvent loadImageSuccessEvent(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT, 1);
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
HWTEST_F(ImageTestNg, ImageEventTest002, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    LoadImageFailEvent curEvent(IMAGE_COMPONENTWIDTH_DEFAULT, IMAGE_COMPONENTHEIGHT_DEFAULT, "");
    auto onError = [&curEvent](const LoadImageFailEvent& info) { curEvent = info; };
    image.SetOnError(std::move(onError));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageEventHub>();
    ASSERT_NE(eventHub, nullptr);
    LoadImageFailEvent loadImageFailEvent(WIDTH, HEIGHT, "image load error!");
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
HWTEST_F(ImageTestNg, ImageSvgTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, pixMap, BUNDLE_NAME, MODULE_NAME);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    image.SetAlt(RESOURCE_URL);
    image.SetImageFill(Color::BLUE);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetForegroundColor().value(), Color::BLUE);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->loadingCtx_->GetSourceInfo().GetSrc(), IMAGE_SRC_URL);
    ASSERT_NE(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: ImageLayout001
 * @tc.desc: Verify that ImageComponent can resize with selfSize, whether has src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm3, nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(WIDTH, HEIGHT));
}

/**
 * @tc.name: ImageLayout002
 * @tc.desc: Verify that Image which has no SelfSize can resize with ContainerSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout002, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    LayoutConstraintF layoutConstraintSize;
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout003
 * @tc.desc: Verify that, when there is no srcImage, ImageComponent which has no SelfSize can resize with AltImageSize .
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout003, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm, nullptr);
    /**
    //     corresponding ets code:
    //         Image().Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    LayoutConstraintF layoutConstraintSize;
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size, std::nullopt);
    EXPECT_EQ(size.value(), SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout004
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout004, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm3, nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm4, nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size4, std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));
}

/**
 * @tc.name: ImageLayout005
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with AltImageSize and its aspectRatio.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout005, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));
}

/**
 * @tc.name: ImageLayout006
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent can resize with selfSize,
 *           whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout006, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm3, nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(WIDTH, HEIGHT));
}

/**
 * @tc.name: ImageLayout007
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent which has no size can resize with max
 *           LayoutConstraint, whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout007, TestSize.Level1)
{
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image().Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm3, nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    ASSERT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout008
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not, although fitOriginSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout008, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm3, nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size3, std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm4, nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size4, std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));
}

/**
 * @tc.name: ImageLayout009
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with ImageSize and its aspectRatio, although fitOriginalSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout009, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altloadingCtx, nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Widrh(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(WIDTH, WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(HEIGHT * aspectRatio, HEIGHT));
}

/**
 * @tc.name: ImageLayout010
 * @tc.desc: Verify that ImageComponent which has no SelfSize can resize with ImageSize, whether fitOriginalSize is set
 *           default. FitOriginalSize is false by default.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout010, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(loadingCtx, nullptr);
    LayoutWrapperNode layoutWrapper1(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm1, nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper1);
    ASSERT_NE(size1, std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));

    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapperNode layoutWrapper2(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    ASSERT_NE(imageLayoutAlgorithm2, nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper2);
    ASSERT_NE(size2, std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout011
 * @tc.desc: Verify that ImageComponent which has no SelfSize, and there has no srcImage or altImage, ImageComponent can
 *           not resize its size.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayout011, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH, HEIGHT));
    /**
    //     corresponding ets code:
    //         Image()
    */
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, nullptr);
    ASSERT_NE(imageLayoutAlgorithm, nullptr);
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_NE(size, std::nullopt);
}

/**
 * @tc.name: ImageLayoutFunction001
 * @tc.desc: Verify that ImageLayoutAlgorithm's Layout can carry out successfully.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, ImageLayoutFunction001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
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
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    imageLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(loadingCtx->imageFit_, ImageFit::COVER);
    EXPECT_EQ(loadingCtx->autoResize_, true);
    EXPECT_EQ(loadingCtx->dstSize_, SizeF(WIDTH, HEIGHT));
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test image drag with src change.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, Drag001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    frameNode->SetDraggable(true);
    frameNode->MarkModifyDone();
    auto pattern = frameNode->GetPattern<ImagePattern>();
    pattern->loadingCtx_->SuccessCallback(nullptr);

    // emulate drag event
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub->GetOnDragStart(), nullptr);
    auto extraParams =
        eventHub->GetDragExtraParams(std::string(), Point(RADIUS_DEFAULT, RADIUS_DEFAULT), DragEventType::START);
    auto dragDropInfo = (eventHub->GetOnDragStart())(nullptr, extraParams);

    // check dragInfo
    EXPECT_EQ(dragDropInfo.extraInfo, IMAGE_SRC_URL);

    // change src
    frameNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(ImageSourceInfo(ALT_SRC_URL));
    frameNode->MarkModifyDone();
    pattern->loadingCtx_->SuccessCallback(nullptr);

    auto newDragDropInfo = (eventHub->GetOnDragStart())(nullptr, extraParams);
    EXPECT_EQ(newDragDropInfo.extraInfo, ALT_SRC_URL);
}

/**
 * @tc.name: CopyOption001
 * @tc.desc: Test image copyOption.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, CopyOption001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    pattern->SetCopyOption(CopyOptions::InApp);
    frameNode->MarkModifyDone();
    EXPECT_EQ(pattern->copyOption_, CopyOptions::InApp);
    EXPECT_TRUE(pattern->clickEvent_ && pattern->longPressEvent_ && pattern->mouseEvent_);

    // emulate long press to open select overlay and click to close it
    EXPECT_FALSE(pattern->selectOverlay_);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    gestureHub->ActLongClick();
    EXPECT_TRUE(pattern->selectOverlay_);

    // close selectOverlay
    gestureHub->ActClick();
    EXPECT_FALSE(pattern->selectOverlay_);

    pattern->SetCopyOption(CopyOptions::None);
    frameNode->MarkModifyDone();
    EXPECT_FALSE(gestureHub->longPressEventActuator_->longPressEvent_);

    pattern->SetCopyOption(CopyOptions::Distributed);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(gestureHub->longPressEventActuator_->longPressEvent_);

    // should close selectOverlay when pattern is deleted
    gestureHub->ActLongClick();
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_FALSE(pattern->selectOverlay_);

    gestureHub->ActLongClick();
    EXPECT_TRUE(pattern->selectOverlay_);

    // shouldn't close selectOverlay when VisibleChange(true) triggers
    pattern->OnVisibleChange(true);
    EXPECT_TRUE(pattern->selectOverlay_);

    pattern->OnVisibleChange(false);
    EXPECT_FALSE(pattern->selectOverlay_);

    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->OnVisibleChange(true);
    EXPECT_FALSE(pattern->selectOverlay_);

    pattern->image_ = nullptr;
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->OnVisibleChange(true);
    EXPECT_FALSE(pattern->selectOverlay_);
}

/**
 * @tc.name: Resource001
 * @tc.desc: Test image reload Resource url when language changes.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, Resource001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);

    pattern->OnLanguageConfigurationUpdate();
    EXPECT_FALSE(pattern->loadingCtx_);
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode Func.
 */
HWTEST_F(ImageTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ImageTheme>()));
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->GetTheme<ImageTheme>()->draggable_ = false;
    frameNode->draggable_ = false;
    pattern->OnAttachToFrameNode();
    EXPECT_FALSE(frameNode->draggable_);

    pipeline->GetTheme<ImageTheme>()->draggable_ = false;
    frameNode->draggable_ = true;
    pattern->OnAttachToFrameNode();
    EXPECT_FALSE(frameNode->draggable_);

    pipeline->GetTheme<ImageTheme>()->draggable_ = true;
    frameNode->draggable_ = true;
    pattern->OnAttachToFrameNode();
    EXPECT_TRUE(frameNode->draggable_);

    pipeline->GetTheme<ImageTheme>()->draggable_ = true;
    frameNode->draggable_ = false;
    pattern->OnAttachToFrameNode();
    EXPECT_TRUE(frameNode->draggable_);
}

/**
 * @tc.name: InitCopy001
 * @tc.desc: Test InitCopy Func.
 */
HWTEST_F(ImageTestNg, InitCopy001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);

    auto callback1 = [](GestureEvent& info) {
        return ;
    };

    auto callback2 = [](MouseInfo& info) {
        return ;
    };

    auto callback3 = [](GestureEvent& info) {
        return ;
    };

    for (int status = 0; status < 8; ++status) {
        if (status >> 0 & 1) {
            pattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>(std::move(callback1));
        } else {
            pattern->longPressEvent_ = nullptr;
        }
        if (status >> 1 & 1) {
            pattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(callback2));
        } else {
            pattern->mouseEvent_ = nullptr;
        }
        if (status >> 2 & 1) {
            pattern->clickEvent_ = AceType::MakeRefPtr<ClickEvent>(std::move(callback3));
        } else {
            pattern->clickEvent_ = nullptr;
        }
        pattern->InitCopy();
        EXPECT_NE(pattern->longPressEvent_, nullptr);
        EXPECT_NE(pattern->mouseEvent_, nullptr);
        EXPECT_NE(pattern->clickEvent_, nullptr);
    }
}

/**
 * @tc.name: HandleCopy001
 * @tc.desc: Test HandleCopy Func.
 */
HWTEST_F(ImageTestNg, HandleCopy001, TestSize.Level1)
{
    auto frameNode = ImageTestNg::CreateImageNode(RESOURCE_URL, ALT_SRC_URL);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    frameNode->MarkModifyDone();
    EXPECT_TRUE(pattern->loadingCtx_);

    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
}

/**
 * @tc.name: GetMaxSize001
 * @tc.desc: Verify GetMaxSize Func.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, GetMaxSize001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, Dimension(0), IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    // 300 * 200
    ASSERT_NE(loadingCtx, nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    // 100 * 200
    ASSERT_NE(altloadingCtx, nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.width_ = std::nullopt;
    layoutConstraintSize.selfIdealSize.height_ = std::nullopt;

    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500)
    */
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    ASSERT_NE(imageLayoutAlgorithm, nullptr);
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(size, std::nullopt);

    loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    // 300 / 200 = 1.5
    std::vector<SizeF> cases = {
        {1, 1}, {1, Infinity<float>()},
        {Infinity<float>(), 1}, {Infinity<float>(), Infinity<float>()}
    };
    std::vector<SizeF> expectedRes {
        {1, 1}, {1, 2}, {0.5, 1}, {0, 0}
    };
    for (int i = 0; i < 4; ++i) {
        layoutConstraintSize.maxSize.SetSizeT(cases[i]);
        size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
        EXPECT_EQ(size.value(), expectedRes[i]);
    }
}

/**
 * @tc.name: MeasureContent001
 * @tc.desc: Verify MeasureContent Func.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestNg, MeasureContent001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper(nullptr, nullptr, imageLayoutProperty);

    std::vector<RefPtr<OHOS::Ace::NG::ImageLoadingContext>> loadingCtx = {
        nullptr,
        AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr)),
        AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, Dimension(-1), Dimension(-1)),
        LoadNotifier(nullptr, nullptr, nullptr))
    };

    std::vector<RefPtr<OHOS::Ace::NG::ImageLoadingContext>> altloadingCtx = {
        nullptr,
        AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr)),
        AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, Dimension(-1), Dimension(-1)),
        LoadNotifier(nullptr, nullptr, nullptr))
    };

    LayoutConstraintF layoutConstraintSize;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(
                loadingCtx[i], altloadingCtx[j]
            );
            auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
            
            int status = i * 3 + j;
            if (status == 0 || status == 2 || status == 6 || status == 8) {
                EXPECT_EQ(size, std::nullopt);
            } else {
                EXPECT_EQ(size.value(), SizeF(0, 0));
            }
        }
    }
}
} // namespace OHOS::Ace::NG

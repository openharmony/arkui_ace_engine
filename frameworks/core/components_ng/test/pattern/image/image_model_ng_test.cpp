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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double IMAGE_WIDTH_DEFAULT = -1.0;
constexpr double IMAGE_HEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTWIDTH_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTHEIGHT_DEFAULT = -1.0;
constexpr double IMAGE_COMPONENTSIZE_WIDTH = 400.0;
constexpr double IMAGE_COMPONENTSIZE_HEIGHT = 500.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 200.0;
constexpr ImageFit IMAGE_FIT_DEFAULT = ImageFit::COVER;
constexpr bool SYNCMODE_DEFAULT = false;
constexpr CopyOptions COPYOPTIONS_DEFAULT = CopyOptions::None;
constexpr bool AUTORESIZE_DEFAULT = true;
constexpr bool FIT_ORIGINAL_SIZE_DEFAULT = true;
constexpr ImageRepeat IMAGE_NO_REPEAT = ImageRepeat::NO_REPEAT;
constexpr ImageInterpolation IMAGE_NO_INTERPOLATION = ImageInterpolation::NONE;
constexpr ImageRenderMode IMAGE_NO_RENDERMODE = ImageRenderMode::ORIGINAL;
constexpr bool MATCHTEXTDIRECTION_DEFAULT = false;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.jpg";
const std::string ALT_SRC_URL = "file://data/data/com.example.test/res/exampleAlt.jpg";
const std::string SVG_SRC_URL = "file://data/data/com.example.test/res/example.svg";
const std::string SVG_ALT_URL = "file://data/data/com.example.test/res/exampleAlt.svg";
} // namespace

class ImageModelNgTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ImageModelNgTest::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ImageModelNgTest::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ImageCreator001
 * @tc.desc: Create Image.
 * @tc.type: FUNC
 */
HWTEST_F(ImageModelNgTest, ImageCreator001, TestSize.Level1)
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
HWTEST_F(ImageModelNgTest, ImageCreator002, TestSize.Level1)
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
HWTEST_F(ImageModelNgTest, ImageCreator003, TestSize.Level1)
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
HWTEST_F(ImageModelNgTest, ImageEventTest001, TestSize.Level1)
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
HWTEST_F(ImageModelNgTest, ImageEventTest002, TestSize.Level1)
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
HWTEST_F(ImageModelNgTest, ImageSvgTest001, TestSize.Level1)
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(SVG_SRC_URL, false, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    image.SetAlt(SVG_ALT_URL);
    image.SetImageFill(Color::BLUE);
    imageSourceInfo.SetFillColor(Color::BLUE);
    EXPECT_TRUE(imageLayoutProperty->GetImageSourceInfo() != std::nullopt);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo().value(), imageSourceInfo);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfo()->fillColor_.value(), Color::BLUE);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
    frameNode->MarkModifyDone();
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
    EXPECT_TRUE(imagePattern->loadingCtx_ != nullptr);
    EXPECT_EQ(imagePattern->loadingCtx_->GetSourceInfo().GetSrc(), SVG_SRC_URL);
    EXPECT_TRUE(imagePattern->altLoadingCtx_ != nullptr);
    EXPECT_EQ(imagePattern->altLoadingCtx_->GetSourceInfo().GetSrc(), SVG_ALT_URL);
}
} // namespace OHOS::Ace::NG

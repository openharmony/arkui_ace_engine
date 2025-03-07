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

namespace {} // namespace

class ImageTestThreeNg : public ImageBases {
public:
};

/**
 * @tc.name: ImagePixelMapListTest0024
 * @tc.desc: Test images size before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0024, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test images size
     * @tc.expected: 0
     */
    EXPECT_TRUE(imagePattern->images_.size() == 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test images size
     * @tc.expected: 10
     */
    EXPECT_TRUE(imagePattern->images_.size() == 10);
}

/**
 * @tc.name: ImagePixelMapListTest0025
 * @tc.desc: Test isAnimation before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0025, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isAnimation
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), false);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isAnimation
     * @tc.expected: true
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);
}

/**
 * @tc.name: ImagePixelMapListTest0026
 * @tc.desc: Test status before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0026, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test status
     * @tc.expected: IDLE
     */
    EXPECT_EQ(imagePattern->status_, Animator::Status::IDLE);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test status
     * @tc.expected: STATE_START
     */
    EXPECT_EQ(imagePattern->status_, static_cast<Animator::Status>(STATE_START));
}

/**
 * @tc.name: ImagePixelMapListTest0027
 * @tc.desc: Test durationTotal before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0027, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0028
 * @tc.desc: Test nowImageIndex before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0028, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0029
 * @tc.desc: Test isSrcUndefined before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0029, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);
}

/**
 * @tc.name: ImagePixelMapListTest0030
 * @tc.desc: Test ImageType before and after type switching, resource to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0030, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test ImageType
     * @tc.expected: BASE
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::BASE);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test ImageType
     * @tc.expected: ANIMATION
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::ANIMATED_DRAWABLE);
}

/**
 * @tc.name: ImagePixelMapListTest0031
 * @tc.desc: Test Duration before and after type switching, pixelMap list to undefined
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0031, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0032
 * @tc.desc: Test Iteration before and after type switching, pixelMap list to undefined
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0032, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0033
 * @tc.desc: Test durationTotal before and after type switching, pixelMap list to undefined
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0033, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0034
 * @tc.desc: Test nowImageIndex before and after type switching, pixelMap list to undefined
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0034, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    //切换Image数据源
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0035
 * @tc.desc: Test Test frameNode before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0035, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test imagenode
     * @tc.expected: true
     */
    EXPECT_EQ(frameNode->GetChildren().empty(), true);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test imagenode
     * @tc.expected: V2::IMAGE_ETS_TAG
     */
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ASSERT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: ImagePixelMapListTest0036
 * @tc.desc: Test Duration before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0036, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Duration
     * @tc.expected: DURATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetDuration(), DURATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0037
 * @tc.desc: Test Iteration before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0037, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test Iteration
     * @tc.expected: ITERATION_DEFAULT
     */
    EXPECT_EQ(imagePattern->animator_->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImagePixelMapListTest0038
 * @tc.desc: Test images size before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0038, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

        /**
     * @tc.steps: step1. Test images size
     * @tc.expected: 0
     */
    EXPECT_TRUE(imagePattern->images_.size() == 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test images size
     * @tc.expected: 10
     */
    EXPECT_TRUE(imagePattern->images_.size() == 10);
}

/**
 * @tc.name: ImagePixelMapListTest0039
 * @tc.desc: Test isAnimation before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0039, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isAnimation
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), false);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isAnimation
     * @tc.expected: true
     */
    EXPECT_EQ(imagePattern->GetIsAnimation(), true);
}

/**
 * @tc.name: ImagePixelMapListTest0040
 * @tc.desc: Test status before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0040, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test status
     * @tc.expected: IDLE
     */
    EXPECT_EQ(imagePattern->status_, Animator::Status::IDLE);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test status
     * @tc.expected: STATE_START
     */
    EXPECT_EQ(imagePattern->status_, static_cast<Animator::Status>(STATE_START));
}

/**
 * @tc.name: ImagePixelMapListTest0041
 * @tc.desc: Test durationTotal before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0041, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test durationTotal
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->durationTotal_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0042
 * @tc.desc: Test nowImageIndex before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0042, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test nowImageIndex
     * @tc.expected: 0
     */
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}

/**
 * @tc.name: ImagePixelMapListTest0043
 * @tc.desc: Test isSrcUndefined before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0043, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test isSrcUndefined
     * @tc.expected: false
     */
    EXPECT_EQ(imagePattern->isSrcUndefined_, false);
}

/**
 * @tc.name: ImagePixelMapListTest0044
 * @tc.desc: Test ImageType before and after type switching, undefined to pixelMap list
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePixelMapListTest0044, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>("");
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageModelNG.Create(imageInfoConfig, pixMap);
    imageModelNG.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step1. Test ImageType
     * @tc.expected: BASE
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::BASE);

    //切换Image数据源
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < 10; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageTestThreeNg::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. Test ImageType
     * @tc.expected: ANIMATION
     */
    EXPECT_EQ(imagePattern->imageType_, ImageType::ANIMATED_DRAWABLE);
}

/**
 * @tc.name: ImagePatternCreateCompleteCallBackInDataReady
 * @tc.desc: call CreateCompleteCallBackInDataReady.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternCreateCompleteCallBackInDataReady, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternSetOnFinishCallback, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternCheckHandles, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternCalAndUpdateSelectOverlay, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternGetParentGlobalOffset, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnAreaChangedInner, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternStartDecoding, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnRecycle, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnReuse, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternHandleCopy, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
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
HWTEST_F(ImageTestThreeNg, ImagePatternToJsonValue, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateFillColorIfForegroundColor, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternBetweenSelectedPosition, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternGetImageColorFilterStr, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
 * @tc.name: ImagePatternSetImageAnalyzerConfig
 * @tc.desc: call SetImageAnalyzerConfig.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternSetImageAnalyzerConfig, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternCreateAnalyzerOverlay, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
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
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateAnalyzerOverlayLayout, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternDestroyAnalyzerOverlay, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternReleaseImageAnalyzer, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateAnalyzerUIConfig, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternhasSceneChanged, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    bool b = imagePattern->hasSceneChanged();
    EXPECT_FALSE(b);
}

/**
 * @tc.name:  ImagePatternResetImage
 * @tc.desc: call ResetImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternResetImage, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternResetAltImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNodeWithDefaultProp(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
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
HWTEST_F(ImageTestThreeNg, ImagePatternResetAltImage002, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->ResetAltImage();
    EXPECT_EQ(imagePattern->altImage_, nullptr);
}

/**
 * @tc.name:  ImagePatternResetPictureSize
 * @tc.desc: call ResetPictureSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternResetPictureSize, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->ResetPictureSize();
    EXPECT_FALSE(imagePattern->hasSizeChanged);
}

/**
 * @tc.name:  ImagePatternSetColorFilter
 * @tc.desc: call SetColorFilter.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternSetColorFilter, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetColorFilter(frameNode);
    EXPECT_FALSE(frameNode->GetPaintProperty<ImageRenderProperty>()->HasColorFilter());
}

/**
 * @tc.name:  ImagePatternSetImageFit
 * @tc.desc: call SetImageFit.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternSetImageFit, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetImageFit(frameNode);
    EXPECT_FALSE(frameNode->GetPaintProperty<ImageRenderProperty>()->HasImageFit());
}

void ImagePatternMethods01()
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();

    imagePattern->TriggerFirstVisibleAreaChange();
    imagePattern->imageAnalyzerManager_ = nullptr;
    EXPECT_EQ(imagePattern->IsSupportImageAnalyzerFeature(), false);
    auto frameNodePtr = AceType::Claim(frameNode);
    imagePattern->AddImageLoadSuccessEvent(frameNodePtr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub->completeEvent_, nullptr);
    LoadImageSuccessEvent loadImageSuccessEvent(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT);
    eventHub->FireCompleteEvent(loadImageSuccessEvent);
    loadImageSuccessEvent.loadingStatus_ = -1;
    eventHub->FireCompleteEvent(loadImageSuccessEvent);

    RefPtr<PixelMap> pixelMap = nullptr;
    EXPECT_NE(ImagePattern::IsShowingSrc(frameNodePtr, pixelMap), false);
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->SetIsFormRender(true);

    imagePattern->UpdateFormDurationByRemainder();
    EXPECT_EQ(imagePattern->isFormAnimationEnd_, true);

    imagePattern->ResetFormAnimationFlag();
    EXPECT_EQ(imagePattern->formAnimationRemainder_, DURATION_DEFAULT);

    imagePattern->SetIteration(DURATION_DEFAULT);
    EXPECT_EQ(imagePattern->animator_->iteration_, ITERATION_DEFAULT);

    imagePattern->SetDuration(1);
    int testData = 0;
    std::function onProgress = [&testData](const uint32_t&, const uint32_t&) {
        testData = 1;
    };
    imagePattern->SetOnProgressCallback(std::move(onProgress));
    imagePattern->onProgressCallback_(uint32_t(0), uint32_t(1));
    EXPECT_EQ(testData, 1);

    imagePattern->EnableDrag();
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->defaultOnDragStart_(dragEvent, string(""));
    EXPECT_EQ(dragEvent->GetData(), nullptr);

    std::vector<float> matrix = {1.1f};
    ImageModelNG::SetColorFilterMatrix(frameNode, matrix);
    imagePattern->SetColorFilter(frameNodePtr);
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), matrix);

    ImageModelNG::SetImageFit(frameNode, ImageFit::COVER);
    imagePattern->SetImageFit(frameNodePtr);
    EXPECT_EQ(imageRenderProperty->GetImageFitValue(), ImageFit::COVER);
}

/**
 * @tc.name:  ImagePatternMethods
 * @tc.desc: call void methods.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternMethods, TestSize.Level1)
{
    ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ImagePatternMethods01();
}

/**
 * @tc.name: ImagePatternIsSupportImageAnalyzerFeature0045
 * @tc.desc: call IsSupportImageAnalyzerFeature.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternIsSupportImageAnalyzerFeature0045, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
 * @tc.name: ImagePatternResetFormAnimationStartTime0046
 * @tc.desc: call ResetFormAnimationStartTime.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternResetFormAnimationStartTime0046, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isFormAnimationStart_ = false;
    imagePattern->ResetFormAnimationStartTime();
    EXPECT_FALSE(imagePattern->isFormAnimationStart_);
}

/**
 * @tc.name: ImagePatternUpdateFormDurationByRemainder0047
 * @tc.desc: call UpdateFormDurationByRemainder.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateFormDurationByRemainder0047, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    RefPtr<PixelMap> pixelMap = nullptr;
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    imagePattern->UpdateFormDurationByRemainder();
    imagePattern->isFormAnimationStart_ = false;
    imagePattern->UpdateFormDurationByRemainder();
    EXPECT_NE(imagePattern->formAnimationRemainder_, 0);
}

/**
 * @tc.name:  ImagePatternhasSceneChanged0048
 * @tc.desc: call hasSceneChanged.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternhasSceneChanged0048, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnAreaChangedInner111, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternCreateNodePaintMethod0050, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnDirtyLayoutWrapperSwap0051, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    imagePattern->isLayouted_ = false;
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(imagePattern->isLayouted_);
    imagePattern->isLayouted_ = false;
    imagePattern->imageType_ = ImageType::BASE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(imagePattern->isLayouted_);
    imagePattern->isLayouted_ = true;
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(imagePattern->isLayouted_);
}
/**
 * @tc.name: ImagePatternOnImageModifyDone0052
 * @tc.desc: Test Image related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternOnImageModifyDone0052, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->imageType_ = ImageType::BASE;
    imagePattern->OnModifyDone();
    imagePattern->OnImageModifyDone();
    EXPECT_FALSE(imagePattern->isSelected_);
}

/**
 * @tc.name: ImagePatternControlAnimation0053
 * @tc.desc: Test Image related method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternControlAnimation0053, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->status_ = Animator::Status::IDLE;
    imagePattern->ControlAnimation(2);
    EXPECT_TRUE(imagePattern->isFormAnimationStart_);
    imagePattern->status_ = Animator::Status::PAUSED;
    imagePattern->ControlAnimation(2);
    EXPECT_TRUE(imagePattern->isFormAnimationStart_);
    imagePattern->status_ = Animator::Status::RUNNING;
    imagePattern->isFormAnimationEnd_ = true;
    imagePattern->ControlAnimation(2);
    EXPECT_FALSE(imagePattern->isFormAnimationEnd_);
}

/**
 * @tc.name: ImagePatternOnAreaChangedInner0054
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImagePatternOnAreaChangedInner0054, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternIsSupportImageAnalyzerFeature0055, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternSetImageAIOptions0056, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternEnableAnalyzer0057, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternGetImageColorFilterStr0058, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnLanguageConfigurationUpdate0059, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternOnAttachToFrameNode0060, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateDragEvent0061, TestSize.Level1)
{
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
HWTEST_F(ImageTestThreeNg, ImagePatternUpdateDragEvent0062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    imagePattern->UpdateDragEvent(dragEvent);
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ImageCreator0063
 * @tc.desc: call Creat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImageCreator0063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    auto imageType = ImageType::BASE;
    auto res = imagePattern->GetImageType();
    EXPECT_EQ(res, imageType);
    imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    imagePattern->hasSizeChanged = false;
    image.Create(imageInfoConfig, pixMap);
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: ImageCreator0064
 * @tc.desc: call Creat.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ImageCreator0064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    auto res = imagePattern->GetImageType();
    auto imageType = ImageType::ANIMATED_DRAWABLE;
    imagePattern->SetImageType(imageType);
    imagePattern->hasSizeChanged = true;
    image.Create(imageInfoConfig, pixMap);
    EXPECT_NE(res, imageType);
}

/**
 * @tc.name: ResetImage0065
 * @tc.desc: call ResetImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestThreeNg, ResetImage0065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    imagePattern->hasSizeChanged = false;
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
HWTEST_F(ImageTestThreeNg, ResetImage0066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = ImageTestThreeNg::CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL);
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
    imagePattern->hasSizeChanged = true;
    image.ResetImage();
    EXPECT_NE(res, imageType);
}
} // namespace OHOS::Ace::NG

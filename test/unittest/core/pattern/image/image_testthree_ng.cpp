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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    imageInfoConfig.src = PNG_IMAGE;
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
    EXPECT_EQ(imagePattern->imageType_, ImagePattern::ImageType::BASE);

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
    EXPECT_EQ(imagePattern->imageType_, ImagePattern::ImageType::ANIMATION);
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    imageInfoConfig.src = "";
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
    EXPECT_EQ(imagePattern->imageType_, ImagePattern::ImageType::BASE);

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
    EXPECT_EQ(imagePattern->imageType_, ImagePattern::ImageType::ANIMATION);
}

} // namespace OHOS::Ace::NG
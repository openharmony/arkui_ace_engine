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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float DEVICE_WIDTH = 480.f;
constexpr float DEVICE_HEIGHT = 800.f;
constexpr int32_t STATE_START = 1;
constexpr int32_t ITERATION_DEFAULT = 1;
constexpr bool ISREVERSE_DEFAULT = false;

constexpr Dimension IMAGE_WIDTH = 170.0_vp;
constexpr Dimension IMAGE_HEIGHT = 120.0_vp;
constexpr Dimension IMAGE_TOP = 0.0_vp;
constexpr Dimension IMAGE_LEFT = 0.0_vp;
constexpr double WIDTH = 400.0;
constexpr double HEIGHT = 500.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 200.0;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.jpg";

const std::string STATUS_IDLE_STR = "AnimationStatus.Initial";
const std::string FILLMODE_FORWARDS_STR = "FillMode.Forwards";
} // namespace

class ImageAnimatorPatternTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    static void SetWidth(const Dimension& width);
    static void SetHeight(const Dimension& height);
    void GetInstance();
    RefPtr<LayoutWrapperNode> RunMeasureAndLayout(float width = DEVICE_WIDTH, float height = DEVICE_HEIGHT);
    void CreateImageAnimator(int32_t number = 1);
    void CreatePixelMapAnimator(int32_t number = 1);
    RefPtr<PixelMap> CreatePixelMap(const std::string& src);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ImageAnimatorPattern> pattern_;
    RefPtr<ImageAnimatorEventHub> eventHub_;
    RefPtr<LayoutProperty> layoutProperty_;
};

RefPtr<PixelMap> ImageAnimatorPatternTestNg::CreatePixelMap(const std::string& src)
{
    auto voidChar = const_cast<char*>(src.c_str());
    void* voidPtr = static_cast<void*>(voidChar);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    return pixelMap;
}

void ImageAnimatorPatternTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void ImageAnimatorPatternTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ImageAnimatorPatternTestNg::SetUp() {}

void ImageAnimatorPatternTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
}

void ImageAnimatorPatternTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ImageAnimatorPatternTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void ImageAnimatorPatternTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ImageAnimatorPattern>();
    eventHub_ = frameNode_->GetOrCreateEventHub<ImageAnimatorEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
}

RefPtr<LayoutWrapperNode> ImageAnimatorPatternTestNg::RunMeasureAndLayout(float width, float height)
{
    RefPtr<LayoutWrapperNode> layoutWrapper = frameNode_->CreateLayoutWrapper(false, false);
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    LayoutConstraint.percentReference = { DEVICE_WIDTH, DEVICE_HEIGHT };
    if (NonNegative(width) && NonNegative(height)) {
        LayoutConstraint.selfIdealSize = { width, height };
    } else if (NonNegative(width)) {
        LayoutConstraint.selfIdealSize = { width, std::nullopt };
    } else if (NonNegative(height)) {
        LayoutConstraint.selfIdealSize = { std::nullopt, height };
    }
    LayoutConstraint.maxSize = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
    return layoutWrapper;
}

void ImageAnimatorPatternTestNg::CreateImageAnimator(int32_t number)
{
    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < number; index++) {
        ImageProperties imageProperties;
        imageProperties.src = IMAGE_SRC_URL;
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);
    GetInstance();
    RunMeasureAndLayout();
}

void ImageAnimatorPatternTestNg::CreatePixelMapAnimator(int32_t number)
{
    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < number; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);
    GetInstance();
    RunMeasureAndLayout();
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_CreatePictureAnimation
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, CreatePictureAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_TRUE(childNode != nullptr && childNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = childNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);

    auto imageAnimatorPattern_ = frameNode->GetPattern<ImageAnimatorPattern>();
    EXPECT_NE(imageAnimatorPattern_, nullptr);
    EXPECT_EQ(imageAnimatorPattern_->images_.size(), 0);
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_SetShowingIndex
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, SetShowingIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    CreateImageAnimator(10);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    pattern_->cacheImages_.front().isLoaded = true;
    auto newImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(newImageNode, nullptr);
    ImageAnimatorPattern::CacheImageStruct newCacheImageStruct(newImageNode);
    pattern_->cacheImages_.emplace_back(newCacheImageStruct);
    EXPECT_EQ(pattern_->cacheImages_.size(), 2);
    pattern_->SetShowingIndex(5);
    EXPECT_EQ(pattern_->images_.size(), 10);
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_SetShowingIndex
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, SetShowingIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    CreatePixelMapAnimator(10);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    int32_t index = 5;
    pattern_->SetShowingIndex(index);
    EXPECT_EQ(pattern_->images_.size(), 10);
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_FindCacheImageNode
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, FindCacheImageNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    CreatePixelMapAnimator(10);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    auto newImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(newImageNode, nullptr);
    auto childLayoutProperty_ = newImageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(childLayoutProperty_, nullptr);
    auto deformPixelMap = CreatePixelMap(IMAGE_SRC_URL);
    childLayoutProperty_->UpdateImageSourceInfo(ImageSourceInfo(deformPixelMap));
    EXPECT_EQ(childLayoutProperty_->HasImageSourceInfo(), true);
    ImageAnimatorPattern::CacheImageStruct newCacheImageStruct(newImageNode);
    pattern_->cacheImages_.emplace_back(newCacheImageStruct);
    pattern_->FindCacheImageNode(deformPixelMap);
    EXPECT_EQ(pattern_->cacheImages_.size(), 2);
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_AddImageLoadSuccessEvent
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, AddImageLoadSuccessEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    CreatePixelMapAnimator(10);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    auto newImageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(newImageNode, nullptr);
    auto childLayoutProperty_ = newImageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(childLayoutProperty_, nullptr);
    auto deformPixelMap = CreatePixelMap(IMAGE_SRC_URL);
    childLayoutProperty_->UpdateImageSourceInfo(ImageSourceInfo(deformPixelMap));
    EXPECT_EQ(childLayoutProperty_->HasImageSourceInfo(), true);
    ImageAnimatorPattern::CacheImageStruct newCacheImageStruct(newImageNode);
    pattern_->cacheImages_.emplace_back(newCacheImageStruct);
    LoadImageSuccessEvent loadImageSuccessEvent(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT, 1);
    LoadImageSuccessEvent loadImageSuccessEventError(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT, WIDTH, HEIGHT, 0);
    pattern_->AddImageLoadSuccessEvent(newImageNode);
    auto imageEventHub = newImageNode->GetOrCreateEventHub<NG::ImageEventHub>();
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent);
    imageEventHub->FireCompleteEvent(loadImageSuccessEventError);
    pattern_->nowImageIndex_ = 10;
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent);
    pattern_->nowImageIndex_ = 9;
    pattern_->images_[9].pixelMap = nullptr;
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent);
    pattern_->nowImageIndex_ = 1;
    imageEventHub->FireCompleteEvent(loadImageSuccessEvent);
    EXPECT_EQ(pattern_->cacheImages_.size(), 2);
}

/**
 * @tc.name: ImageAnimatorPatternTestNg_SetDuration
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorPatternTestNg, SetDuration, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimatorView and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */
    CreatePixelMapAnimator(10);
    /**
     * @tc.steps: step2. get childNode of frameNode and its imageLayoutProperty.
     * @tc.expected: step2. check whether childNode, imageLayoutProperty exists and tag of childNode is correct.
     */
    pattern_->durationTotal_ = 1;
    pattern_->SetDuration(0);
    EXPECT_EQ(pattern_->durationTotal_, 1);
}
} // namespace OHOS::Ace::NG

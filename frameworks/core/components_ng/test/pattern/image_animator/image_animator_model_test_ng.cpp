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

#include "core/animation/animator.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.cpp"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STATE_DEFAULT = 0;
constexpr int32_t STATE_START = 1;
constexpr int32_t STATE_PAUSED = 2;
constexpr int32_t DURATION_DEFAULT = 1000;
constexpr int32_t ITERATION_DEFAULT = 1;
constexpr int32_t FILLMODENG_DEFAULT = 1;
constexpr int32_t PREDECODE_DEFAULT = 0;
constexpr bool ISREVERSE_DEFAULT = false;
constexpr bool FIXEDSIZE_DEFAULT = true;

constexpr Dimension IMAGE_WIDTH = 170.0_vp;
constexpr Dimension IMAGE_HEIGHT = 120.0_vp;
constexpr Dimension IMAGE_TOP = 0.0_vp;
constexpr Dimension IMAGE_LEFT = 0.0_vp;
constexpr int32_t IMAGE_DURATION = 500;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.jpg";

const std::string STATUS_IDLE_STR = "AnimationStatus.Initial";
const std::string FILLMODE_FORWARDS_STR = "FillMode.Forwards";
} // namespace

class ImageAnimatorModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ImageAnimatorModelTestNg::SetUpTestCase() {}
void ImageAnimatorModelTestNg::TearDownTestCase() {}
void ImageAnimatorModelTestNg::SetUp() {}
void ImageAnimatorModelTestNg::TearDown() {}

/**
 * @tc.name: ImageAnimatorTest001
 * @tc.desc: Test Create of ImageAnimatorModelNG.
 * @tc.type: FUNC
 */

HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG and get frameNode.
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
    EXPECT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = childNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest002
 * @tc.desc: Set ImageAnimatorModelNG attributes into ImageAnimatorPattern and get them.
 * @tc.type: FUNC
 */

HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelTestNg.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set ImageAnimatorModelNG attributes into ImageAnimatorPattern.
     * @tc.expected: step2. related function is called.
     */
    ImageAnimatorModelNG.SetState(STATE_DEFAULT);
    ImageAnimatorModelNG.SetDuration(DURATION_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);
    ImageAnimatorModelNG.SetFillMode(FILLMODENG_DEFAULT);
    ImageAnimatorModelNG.SetPreDecode(PREDECODE_DEFAULT);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetFixedSize(FIXEDSIZE_DEFAULT);

    /**
     * @tc.steps: step3. get ImageAnimatorPattern from frameNode.
     * @tc.expected: step3. check whether frameNode and ImageAnimatorPattern exists.
     */

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);

    /**
     * @tc.steps: step4. get attributes from ImageAnimatorPattern by json.
     * @tc.expected: step4. check whether all attributes is correct.
     */

    auto jsonValue = JsonUtil::Create(true);
    imageAnimatorPattern->ToJsonValue(jsonValue);
    EXPECT_EQ(jsonValue->GetValue("state")->GetString().c_str(), STATUS_IDLE_STR);
    EXPECT_EQ(jsonValue->GetValue("duration")->GetString().c_str(), std::to_string(DURATION_DEFAULT));
    EXPECT_EQ(jsonValue->GetValue("iterations")->GetString().c_str(), std::to_string(ITERATION_DEFAULT));
    EXPECT_EQ(jsonValue->GetValue("fillMode")->GetString().c_str(), FILLMODE_FORWARDS_STR);
    EXPECT_EQ(jsonValue->GetValue("reverse")->GetString(), std::string(ISREVERSE_DEFAULT ? "true" : "false"));
    EXPECT_EQ(jsonValue->GetValue("fixedSize")->GetString(), std::string(FIXEDSIZE_DEFAULT ? "true" : "false"));
}

/**
 * @tc.name: ImageAnimatorTest003
 * @tc.desc: Test SetImages of ImageAnimatorModelNG.
 * @tc.type: FUNC
 */

HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelTestNg and get frameNode.
     * @tc.expected: step1. check frameNode exists and tag is correct.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's ImageAnimatorModelNG attributes into ImageProperties and set ImageProperties into
     * imageAnimatorView.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));

    /**
     * @tc.steps: step3. get ImageAnimatorPattern from frameNode.
     * @tc.expected: step3. check whether frameNode and ImageAnimatorPattern exists.
     */

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);

    /**
     * @tc.steps: step4. get image's attributes from ImageAnimatorPattern by json and splice json string with setting
     * values.
     * @tc.expected: step4. check whether two strings are equal.
     */

    auto jsonValue = JsonUtil::Create(true);
    imageAnimatorPattern->ToJsonValue(jsonValue);
    std::string imagesStr = jsonValue->GetValue("images")->GetString();
    auto imageArray = JsonUtil::CreateArray(true);
    auto imageItem = JsonUtil::Create(true);
    imageItem->Put("src", IMAGE_SRC_URL.c_str());
    imageItem->Put("left", IMAGE_LEFT.ToString().c_str());
    imageItem->Put("top", IMAGE_TOP.ToString().c_str());
    imageItem->Put("width", IMAGE_WIDTH.ToString().c_str());
    imageItem->Put("height", IMAGE_HEIGHT.ToString().c_str());
    imageItem->Put("duration", std::to_string(IMAGE_DURATION).c_str());
    imageArray->Put(imageItem);
    EXPECT_EQ(imagesStr, imageArray->ToString());
}

/**
 * @tc.name: ImageAnimatorTest004
 * @tc.desc: Test OnStart of ImageAnimatorModelNG and run Forward and Backward.
 * @tc.type: FUNC
 */

HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's duration by zero and imageAnimatorView's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_DEFAULT);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test SetOnStart on ImageAnimatorModelNg.
     * @tc.expected: step2. related function is called.
     */

    std::function<void()> OnStart;
    ImageAnimatorModelNG.SetOnStart(std::move(OnStart));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest005
 * @tc.desc: Test SetOnPause on ImageAnimatorModelNg.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and ImageAnimatorModelNG's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_PAUSED);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test SetOnPause on ImageAnimatorModelNg.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    std::function<void()> OnPause;
    ImageAnimatorModelNG.SetOnPause(std::move(OnPause));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest006
 * @tc.desc: Test SetOnCancel on ImageAnimatorModelNg.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and ImageAnimatorModelNG's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test SetOnCancel on ImageAnimatorModelNg.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    std::function<void()> OnCancel;
    ImageAnimatorModelNG.SetOnCancel(std::move(OnCancel));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest007
 * @tc.desc: Test SetOnFinish on ImageAnimatorModelNg.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and ImageAnimatorModelNG's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test SetOnFinish on ImageAnimatorModelNg.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    std::function<void()> OnFinish;
    ImageAnimatorModelNG.SetOnFinish(std::move(OnFinish));
    std::function<void()> OnStart;
    ImageAnimatorModelNG.SetOnStart(std::move(OnStart));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest008
 * @tc.desc: Test SetOnRepeat on ImageAnimatorModelNg.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorModelTestNg, ImageAnimatorTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and ImageAnimatorModelNG's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. Test SetOnRepeat.
     * @tc.expected: step3. related function is called .
     */

    std::function<void()> OnRepeat;
    ImageAnimatorModelNG.SetOnRepeat(std::move(OnRepeat));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
}
} // namespace OHOS::Ace::NG
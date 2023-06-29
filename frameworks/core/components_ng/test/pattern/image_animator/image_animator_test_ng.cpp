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
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"
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
constexpr int32_t STATE_STOPPED = 3;
constexpr int32_t DURATION_DEFAULT = 1000;
constexpr int32_t ITERATION_DEFAULT = 1;
constexpr int32_t FILLMODENG_DEFAULT = 1;
constexpr int32_t PREDECODE_DEFAULT = 0;
constexpr bool ISREVERSE_DEFAULT = false;
constexpr bool ISREVERSE_BACKWARD = true;
constexpr bool FIXEDSIZE_DEFAULT = true;
constexpr bool FIXEDSIZE_CHANGED = false;

constexpr Dimension IMAGE_WIDTH = 170.0_vp;
constexpr Dimension IMAGE_HEIGHT = 120.0_vp;
constexpr Dimension IMAGE_TOP = 0.0_vp;
constexpr Dimension IMAGE_LEFT = 0.0_vp;
constexpr int32_t IMAGE_DURATION = 500;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.jpg";

const std::string STATUS_IDLE_STR = "AnimationStatus.Initial";
const std::string FILLMODE_FORWARDS_STR = "FillMode.Forwards";
const constexpr float NORMALIZED_DURATION_MAX { 1.0f };
} // namespace

class ImageAnimatorTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ImageAnimatorTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ImageAnimatorTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ImageAnimatorTest001
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest001, TestSize.Level1)
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
}

/**
 * @tc.name: ImageAnimatorTest002
 * @tc.desc: Set ImageAnimator attributes into ImageAnimatorPattern and get them.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelTestNg.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set attributes into ImageAnimatorPattern.
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
 * @tc.desc: Set Image into ImageAnimator and get its attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelTestNg.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes into ImageProperties and set ImageProperties into imageAnimatorView.
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
 * @tc.desc: Set StartEvent into ImageAnimatorPattern and run Forward and Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
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
     * @tc.steps: step3. set startEvent into eventHub.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    bool startFlag = false;
    auto startEvent = [&startFlag]() { startFlag = !startFlag; };
    ImageAnimatorModelNG.SetOnStart(std::move(startEvent));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone to run Forward.
     * @tc.expected: step4. related function is called and check whether startFlag is true.
     */

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(startFlag);

    /**
     * @tc.steps: step5. change IsReverse and use OnModifyDone to run Backward.
     * @tc.expected: step5. related function is called and check whether startFlag is false.
     */

    ViewStackProcessor::GetInstance()->Push(element);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_BACKWARD);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(!startFlag);
}

/**
 * @tc.name: ImageAnimatorTest005
 * @tc.desc: Set PauseEvent into ImageAnimatorPattern and run it.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
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
     * @tc.steps: step3. set pauseEvent into eventHub.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    bool pauseFlag = false;
    auto pauseEvent = [&pauseFlag]() { pauseFlag = !pauseFlag; };
    ImageAnimatorModelNG.SetOnPause(std::move(pauseEvent));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone to run pauseEvent.
     * @tc.expected: step4. related function is called and check whether pauseFlag is true.
     */

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_TRUE(imageAnimatorPattern != nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(pauseFlag);
}

/**
 * @tc.name: ImageAnimatorTest006
 * @tc.desc: Set CancelEvent into ImageAnimatorPattern and run it.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
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
     * @tc.steps: step3. set cancelEvent into eventHub.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    bool cancelFlag = false;
    auto cancelEvent = [&cancelFlag]() { cancelFlag = !cancelFlag; };
    ImageAnimatorModelNG.SetOnCancel(std::move(cancelEvent));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone to set animator's status is RUNNING.
     * @tc.expected: step4. check whether animator's status is correct.
     */

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_EQ(imageAnimatorPattern->animator_->GetStatus(), static_cast<Animator::Status>(STATE_START));

    /**
     * @tc.steps: step5. change imageAnimatorView's status and use OnModifyDone to run cancelEvent.
     * @tc.expected: step5. check whether cancelFlag is true and imageLayoutProperty's url is correct.
     */

    ViewStackProcessor::GetInstance()->Push(element);
    ImageAnimatorModelNG.SetState(STATE_DEFAULT);
    ImageAnimatorModelNG.SetFixedSize(FIXEDSIZE_CHANGED);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(cancelFlag);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfoValue(), ImageSourceInfo(IMAGE_SRC_URL));
}

/**
 * @tc.name: ImageAnimatorTest007
 * @tc.desc: Set StopEvent into ImageAnimatorPattern and run it.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
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
     * @tc.steps: step3. set stoppedEvent and startEvent into eventHub.
     * @tc.expected: step3. related function is called and check whether eventHub is not null.
     */

    bool stoppedFlag = false;
    auto stoppedEvent = [&stoppedFlag]() { stoppedFlag = !stoppedFlag; };
    ImageAnimatorModelNG.SetOnFinish(std::move(stoppedEvent));
    bool startFlag = false;
    auto startEvent = [&startFlag]() { startFlag = !startFlag; };
    ImageAnimatorModelNG.SetOnStart(std::move(startEvent));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone to set animator's status is RUNNING.
     * @tc.expected: step4. check whether startFlag is true.
     */

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(startFlag);

    /**
     * @tc.steps: step5. change imageAnimatorView's status and use OnModifyDone to run stoppedlEvent.
     * @tc.expected: step5. check whether stoppedFlag is true.
     */

    ViewStackProcessor::GetInstance()->Push(element);
    ImageAnimatorModelNG.SetState(STATE_STOPPED);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(stoppedFlag);
}

/**
 * @tc.name: ImageAnimatorTest008
 * @tc.desc: Set RepeatEvent into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
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
     * @tc.steps: step3. set repeatEvent and repeatEvent into eventHub.
     * @tc.expected: step3. related function is called and check whether repeatFlag is true.
     */

    bool repeatFlag = false;
    auto repeatEvent = [&repeatFlag]() { repeatFlag = !repeatFlag; };
    ImageAnimatorModelNG.SetOnRepeat(std::move(repeatEvent));
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto repeatCallback = eventHub->GetRepeatEvent();
    EXPECT_NE(repeatCallback, nullptr);
    repeatCallback();
    EXPECT_TRUE(repeatFlag);
}

/**
 * @tc.name: ImageAnimatorTest009
 * @tc.desc: Set images with duration by zero into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest009, TestSize.Level1)
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
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    ImageAnimatorModelNG.SetImages(std::move(images));
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. get imageAnimatorPattern from frameNode.
     * @tc.expected: step3. check whether imageAnimatorPattern is not null.
     */

    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone when image's duration is zero.
     * @tc.expected: step4. PictureAnimation's duration is correct.
     */

    imageAnimatorPattern->AttachToFrameNode(frameNode);
    auto pictureAnimation = imageAnimatorPattern->CreatePictureAnimation(imageAnimatorPattern->images_.size());
    EXPECT_EQ(pictureAnimation->GetDuration(),
        NORMALIZED_DURATION_MAX / static_cast<float>(imageAnimatorPattern->images_.size()));
}

/**
 * @tc.name: ImageAnimatorTest010
 * @tc.desc: Add listener into animator and run it.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelTestNg.
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
    ImageAnimatorModelNG.SetState(STATE_START);
    ImageAnimatorModelNG.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);

    /**
     * @tc.steps: step3. use OnModifyDone to set animator's status is RUNNING and Add listener into animator.
     * @tc.expected: step3. check whether animator's status is correct and interpolators is not empty.
     */

    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_EQ(imageAnimatorPattern->animator_->GetStatus(), static_cast<Animator::Status>(STATE_START));
    EXPECT_TRUE(!imageAnimatorPattern->animator_->interpolators_.empty());
    /**
     * @tc.steps: step4. change fixedSize and use OnModifyDone to run listerner.
     * @tc.expected: step4. check whether ImageSourceInfoValue, MarginProperty, CalcLayoutConstraint, MeasureType is
     * correct.
     */

    ViewStackProcessor::GetInstance()->Push(element);
    ImageAnimatorModelNG.SetState(STATE_DEFAULT);
    ImageAnimatorModelNG.SetFixedSize(FIXEDSIZE_CHANGED);
    imageAnimatorPattern->OnModifyDone();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(imageFrameNode, nullptr);
    EXPECT_EQ(imageFrameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->GetImageSourceInfoValue(), ImageSourceInfo(IMAGE_SRC_URL));
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->left->ToString(), IMAGE_LEFT.ToString());
    EXPECT_EQ(imageLayoutProperty->GetMarginProperty()->top->ToString(), IMAGE_TOP.ToString());
    const auto& calcLayoutConstraint = imageLayoutProperty->GetCalcLayoutConstraint();
    EXPECT_NE(calcLayoutConstraint, nullptr);
    EXPECT_EQ(calcLayoutConstraint->selfIdealSize->Width()->ToString(), IMAGE_WIDTH.ToString());
    EXPECT_EQ(calcLayoutConstraint->selfIdealSize->Height()->ToString(), IMAGE_HEIGHT.ToString());
    EXPECT_EQ(imageLayoutProperty->GetMeasureType(), MeasureType::MATCH_CONTENT);
}
} // namespace OHOS::Ace::NG
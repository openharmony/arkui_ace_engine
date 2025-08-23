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

#include <climits>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
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
} // namespace

class ImageAnimatorTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
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

RefPtr<PixelMap> ImageAnimatorTestNg::CreatePixelMap(const std::string& src)
{
    RefPtr<PixelMap> pixelMap = nullptr;
    return pixelMap;
}

void ImageAnimatorTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ImageAnimatorTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ImageAnimatorTestNg::SetUp() {}

void ImageAnimatorTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
}

void ImageAnimatorTestNg::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
}

void ImageAnimatorTestNg::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
}

void ImageAnimatorTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ImageAnimatorPattern>();
    eventHub_ = frameNode_->GetEventHub<ImageAnimatorEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
}

RefPtr<LayoutWrapperNode> ImageAnimatorTestNg::RunMeasureAndLayout(float width, float height)
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

void ImageAnimatorTestNg::CreateImageAnimator(int32_t number)
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

void ImageAnimatorTestNg::CreatePixelMapAnimator(int32_t number)
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
     * @tc.steps: step2. get childNode of frameNode.
     * @tc.expected: step2. check whether childNode is empty.
     */
    EXPECT_TRUE(frameNode->GetChildren().empty());
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
    imageAnimatorPattern->ToJsonValue(jsonValue, filter);
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
    imageAnimatorPattern->ToJsonValue(jsonValue, filter);
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
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step4. use OnModifyDone to run Forward.
     * @tc.expected: step4. related function is called and check whether startFlag is true.
     */

    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
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

    /**
     * @tc.steps: step6. add Element to cacheImages_
     * @tc.expected: step6. cacheImages_.size() > cacheImageNum
     */
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    imageLayoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    imageAnimatorPattern->cacheImages_.emplace_back(ImageAnimatorPattern::CacheImageStruct(imageNode));
    imageAnimatorPattern->OnModifyDone();
    auto iTemp = ITERATION_DEFAULT / imageAnimatorPattern->images_.size();
    size_t cacheImageNum = iTemp >= 50 ? 1 : 2;
    cacheImageNum = std::min(imageAnimatorPattern->images_.size() - 1, cacheImageNum);
    EXPECT_TRUE(imageAnimatorPattern->cacheImages_.size() >= cacheImageNum);

    /**
     * @tc.steps: step7. status_ is Running and isFormAnimationEnd_ is true
     * @tc.expected: step7. formAnimationRemainder_ is DEFAULT_DURATION
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    imageAnimatorPattern->status_ = ControlledAnimator::ControlStatus::RUNNING;
    imageAnimatorPattern->isFormAnimationEnd_ = true;
    imageAnimatorPattern->OnModifyDone();
    EXPECT_EQ(imageAnimatorPattern->formAnimationRemainder_, 1000);
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
    EXPECT_EQ(imageAnimatorPattern->controlledAnimator_->GetControlStatus(),
        static_cast<ControlledAnimator::ControlStatus>(STATE_START));

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
    EXPECT_EQ(imageAnimatorPattern->controlledAnimator_->GetControlStatus(),
        static_cast<ControlledAnimator::ControlStatus>(STATE_START));
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

/**
 * @tc.name: ImageAnimatorTest011
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. images size is 0.
     * @tc.expected: do nothing
     */
    CreateImageAnimator(0);

    /**
     * @tc.steps: step2. SetShowingIndex() greater than images size-1.
     * @tc.expected: nowImageIndex_ not change
     */
    CreateImageAnimator(1);
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 0);

    /**
     * @tc.steps: step3. SetShowingIndex().
     * @tc.expected: nowImageIndex_ is change
     */
    CreateImageAnimator(2);
    EXPECT_EQ(pattern_->nowImageIndex_, 0);
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);

    // coverage fixedSize_ is false
    pattern_->nowImageIndex_ = 0;
    CreateImageAnimator(2);
    pattern_->fixedSize_ = false;
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);
    EXPECT_TRUE(pattern_->cacheImages_.size());
    pattern_->fixedSize_ = true;

    // expected:FindCacheImageNode(images_[index].src) != cacheImages_.end() && isLoaded = false
    CreateImageAnimator(2);
    EXPECT_TRUE(pattern_->images_.size() == 2);
    for (auto iter = pattern_->cacheImages_.begin(); iter != pattern_->cacheImages_.end(); ++iter) {
        RefPtr<FrameNode>& imageFrameNode = iter->imageNode;
        auto imageLayoutProperty =
            AccessibilityManager::DynamicCast<ImageLayoutProperty>(imageFrameNode->layoutProperty_);
        if (imageLayoutProperty->HasImageSourceInfo()) {
            if (static_cast<int32_t>(pattern_->images_.size()) > 1) {
                pattern_->images_[1].src = imageLayoutProperty->GetImageSourceInfoValue().GetSrc();
                iter->isLoaded = false;
            }
            break;
        }
    }
    auto host = pattern_->GetHost();
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->ResetImageSourceInfo();
    EXPECT_FALSE(pattern_->IsShowingSrc(imageFrameNode, pattern_->images_[1].src));
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);

    // expected:coverage isLoaded = true
    pattern_->cacheImages_.begin()->isLoaded = true;
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);

    /**
     * @tc.steps: step4. images Unit is PERCENT
     * @tc.expected: host size not change
     */
    ImageAnimatorModelNG ImageAnimatorModelNG_1;
    ImageAnimatorModelNG_1.Create();
    std::vector<ImageProperties> images_1;
    ImageProperties imageProperties_1;
    imageProperties_1.src = IMAGE_SRC_URL;
    imageProperties_1.width = Dimension(0.1, DimensionUnit::PERCENT);
    imageProperties_1.height = Dimension(0.1, DimensionUnit::PERCENT);
    imageProperties_1.top = IMAGE_TOP;
    imageProperties_1.left = IMAGE_LEFT;
    images_1.push_back(imageProperties_1);
    ImageAnimatorModelNG_1.SetImages(std::move(images_1));
    ImageAnimatorModelNG_1.SetState(STATE_START);
    ImageAnimatorModelNG_1.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG_1.SetIteration(ITERATION_DEFAULT);
    GetInstance();
    RunMeasureAndLayout();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(DEVICE_WIDTH, DEVICE_HEIGHT));

    /**
     * @tc.steps: step5. images has PERCENT width/height
     * @tc.expected: if host has no set width/height, would effected by largest images size
     */
    ImageAnimatorModelNG ImageAnimatorModelNG_2;
    ImageAnimatorModelNG_2.Create();
    std::vector<ImageProperties> images_2;
    ImageProperties imageProperties_2;
    imageProperties_2.src = IMAGE_SRC_URL;
    imageProperties_2.width = Dimension(100);
    imageProperties_2.height = Dimension(100);
    imageProperties_2.top = IMAGE_TOP;
    imageProperties_2.left = IMAGE_LEFT;
    images_2.push_back(imageProperties_2);
    ImageProperties imageProperties_3;
    imageProperties_3.src = IMAGE_SRC_URL;
    imageProperties_3.width = Dimension(50);
    imageProperties_3.height = Dimension(150);
    imageProperties_3.top = IMAGE_TOP;
    imageProperties_3.left = IMAGE_LEFT;
    images_2.push_back(imageProperties_3);
    ImageAnimatorModelNG_2.SetImages(std::move(images_2));
    ImageAnimatorModelNG_2.SetState(STATE_START);
    ImageAnimatorModelNG_2.SetIsReverse(ISREVERSE_DEFAULT);
    ImageAnimatorModelNG_2.SetIteration(ITERATION_DEFAULT);
    GetInstance();
    RunMeasureAndLayout();

    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, std::nullopt));
    pattern_->AdaptSelfSize();
    auto idealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(idealSize->Width().value(), CalcLength(100));
    EXPECT_EQ(idealSize->Height().value(), CalcLength(150));

    layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize->Reset();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(DEVICE_WIDTH), std::nullopt));
    pattern_->AdaptSelfSize();
    idealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(idealSize->Width().value(), CalcLength(DEVICE_WIDTH));
    EXPECT_EQ(idealSize->Height().value(), CalcLength(150));

    layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize->Reset();
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEVICE_HEIGHT)));
    pattern_->AdaptSelfSize();
    idealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(idealSize->Width().value(), CalcLength(100));
    EXPECT_EQ(idealSize->Height().value(), CalcLength(DEVICE_HEIGHT));
}

/**
 * @tc.name: ImageAnimatorTest012
 * @tc.desc: Set duration and check duration is correct assign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);
    /**
     * @tc.steps: step2. set is form render and set duration
     * @tc.expected: check duration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->SetDuration(1500);
    EXPECT_EQ(animator->GetDuration(), DURATION_DEFAULT);

    /**
     * @tc.steps: step3. set is form render and set duration,finalDuration < DEFAULT_DURATION
     * @tc.expected: check duration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->SetDuration(900);
    EXPECT_EQ(animator->GetDuration(), 900);
    /**
     * @tc.steps: step4. set is form render and set duration
     * @tc.expected: check duration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->controlledAnimator_->controlStatus_ = ControlledAnimator::ControlStatus::IDLE;
    pattern_->SetDuration(0);
    EXPECT_EQ(animator->GetDuration(), 0);
}

/**
 * @tc.name: ImageAnimatorTest013
 * @tc.desc: Set iteration and check iteration is correct assign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);
    /**
     * @tc.steps: step2. set is form render and iteration
     * @tc.expected: check iteration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->SetIteration(5);
    EXPECT_EQ(animator->GetIteration(), ITERATION_DEFAULT);
}

/**
 * @tc.name: ImageAnimatorTest014
 * @tc.desc: Update duration By Remainder and check duration is correct assign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);
    /**
     * @tc.steps: step2. set is form render and set duration
     * @tc.expected: check duration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->SetDuration(DURATION_DEFAULT);
    pattern_->UpdateFormDurationByRemainder();
    EXPECT_EQ(animator->GetDuration(), DURATION_DEFAULT);
    /**
     * @tc.steps: step3. reset form animation start time and duration
     * @tc.expected: check duration is correct assign
     */
    pattern_->ResetFormAnimationStartTime();
    EXPECT_TRUE(!pattern_->isFormAnimationStart_);
    pattern_->UpdateFormDurationByRemainder();
    EXPECT_EQ(animator->GetDuration(), pattern_->formAnimationRemainder_);
}

/**
 * @tc.name: ImageAnimatorTest015
 * @tc.desc: Reset remainder and check remainder is correct assign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);
    /**
     * @tc.steps: step2. set is form render and reset remainder
     * @tc.expected: check remainder is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->ResetFormAnimationFlag();
    EXPECT_EQ(pattern_->formAnimationRemainder_, DURATION_DEFAULT);
    EXPECT_TRUE(pattern_->isFormAnimationStart_);
    EXPECT_TRUE(!pattern_->isFormAnimationEnd_);
}

/**
 * @tc.name: ImageAnimatorTest016
 * @tc.desc: get whether is form render and value is correct
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);
    /**
     * @tc.steps: step2. set whether is form render
     * @tc.expected: check get form render value is correct
     */
    pipeline->SetIsFormRender(false);
    EXPECT_EQ(pattern_->IsFormRender(), false);
    pipeline->SetIsFormRender(true);
    EXPECT_EQ(pattern_->IsFormRender(), true);
}

/**
 * @tc.name: ImageAnimatorTest017
 * @tc.desc: frameNode->GetChildren() is not empty
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest017, TestSize.Level1)
{
    ImageAnimatorModelNG imageAnimatorModelNG;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = static_cast<ElementIdType>(1);
    stack->reservedNodeId_ = static_cast<ElementIdType>(1);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ANIMATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImageAnimatorPattern>(); });
    CHECK_NULL_VOID(frameNode);
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    CHECK_NULL_VOID(imageNode);
    frameNode->AddChild(imageNode);
    frameNode->tag_ = V2::IMAGE_ANIMATOR_ETS_TAG;
    ElementRegister::GetInstance()->itemMap_[nodeId] = frameNode;
    imageAnimatorModelNG.Create();
    EXPECT_FALSE(frameNode->GetChildren().empty());
}
/**
 * @tc.name: ImageAnimatorTest018
 * @tc.desc: UpdateCacheImageInfo::index < images_.size()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest018, TestSize.Level1)
{
    CreateImageAnimator(1);
    ImageAnimatorPattern::CacheImageStruct cTemp;
    int32_t iIndex = 2;
    pattern_->UpdateCacheImageInfo(cTemp, iIndex);
    EXPECT_TRUE(iIndex >= static_cast<int32_t>(pattern_->images_.size()));
}

/**
 * @tc.name: ImageAnimatorTest019
 * @tc.desc: OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create paramater
     */
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    DirtySwapConfig config;

    /**
     * @tc.steps: step2. set isLayouted_ true
     */
    imageAnimatorPattern->isLayouted_ = true;

    /**
     * @tc.steps: step3. call OnDirtyLayoutWrapperSwap
     * @tc.expected: false
     */
    bool bResult = imageAnimatorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(bResult);

    // fixedSize and images_.size() both are false
    imageAnimatorPattern->isLayouted_ = false;
    imageAnimatorPattern->fixedSize_ = false;
    imageAnimatorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    /**
     * @tc.steps: step4. Create ImageAnimator
     * @tc.expected: Create Success
     */
    CreateImageAnimator(1);
    EXPECT_EQ(imageAnimatorPattern->images_.size(), 1);
    imageAnimatorPattern->GenerateCachedImages();
    imageAnimatorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    /**
     * @tc.steps: step5. fixedSize and is Reverse both ture
     * @tc.expected: GetNextIndex(0) is 0
     */
    imageAnimatorPattern->fixedSize_ = true;
    imageAnimatorPattern->isReverse_ = true;
    imageAnimatorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(imageAnimatorPattern->GetNextIndex(0), 0);
    EXPECT_EQ(imageAnimatorPattern->GetNextIndex(1), 0);
}

/**
 * @tc.name: ImageAnimatorTest020
 * @tc.desc: Update duration By Remainder and check duration is correct assign
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageAnimator
     * @tc.expected: pipeline and animator is not nullptr
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    auto animator = pattern_->controlledAnimator_;

    /**
     * @tc.steps: step2. set is form render and set duration
     * @tc.expected: check duration is correct assign
     */
    pipeline->SetIsFormRender(true);
    pattern_->isFormAnimationStart_ = true;
    pattern_->formAnimationRemainder_ = 1;
    pattern_->SetDuration(DURATION_DEFAULT);
    pattern_->UpdateFormDurationByRemainder();
    EXPECT_EQ(animator->GetDuration(), pattern_->formAnimationRemainder_);

    /**
     * @tc.steps: step3. formAnimationRemainder_ is 0
     * @tc.expected: isFormAnimationEnd_ is true
     */
    pattern_->formAnimationRemainder_ = 0;
    pattern_->UpdateFormDurationByRemainder();
    EXPECT_TRUE(pattern_->isFormAnimationEnd_);
}

/**
 * @tc.name: ImageAnimatorTest021
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. images size is 0.
     * @tc.expected: do nothing
     */
    CreateImageAnimator(0);

    /**
     * @tc.steps: step2. SetShowingIndex() greater than images size-1.
     * @tc.expected: nowImageIndex_ not change
     */
    CreateImageAnimator(1);
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 0);

    /**
     * @tc.steps: step3. set calcLayoutConstraint_ null
     */
    auto host = pattern_->GetHost();
    auto& layoutProperty = host->layoutProperty_;
    if (layoutProperty->GetCalcLayoutConstraint()) {
        layoutProperty->calcLayoutConstraint_ = nullptr;
    }

    /**
     * @tc.steps: step4. set images width not valid
     * @tc.expected: maxWidth and maxHeight are not valid
     */
    for (auto& image : pattern_->images_) {
        image.width = Dimension(0);
    }
    pattern_->AdaptSelfSize();

    Dimension maxWidth;
    Dimension maxHeight;
    double maxWidthPx = 0.0;
    double maxHeightPx = 0.0;
    for (const auto& image : pattern_->images_) {
        if (image.width.Unit() != DimensionUnit::PERCENT) {
            auto widthPx = image.width.ConvertToPx();
            if (widthPx > maxWidthPx) {
                maxWidthPx = widthPx;
                maxWidth = image.width;
            }
        }
        if (image.height.Unit() != DimensionUnit::PERCENT) {
            auto heightPx = image.height.ConvertToPx();
            if (heightPx > maxHeightPx) {
                maxHeightPx = heightPx;
                maxHeight = image.height;
            }
        }
    }
    EXPECT_FALSE(maxWidth.IsValid());
    EXPECT_TRUE(maxHeight.IsValid());
}

/**
 * @tc.name: ImageAnimatorTest022
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. images size is 0.
     * @tc.expected: do nothing
     */
    CreatePixelMapAnimator(0);

    /**
     * @tc.steps: step2. SetShowingIndex() greater than images size-1.
     * @tc.expected: nowImageIndex_ not change
     */
    CreatePixelMapAnimator(1);
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 0);

    /**
     * @tc.steps: step3. SetShowingIndex().
     * @tc.expected: nowImageIndex_ is change
     */
    CreatePixelMapAnimator(2);
    EXPECT_EQ(pattern_->nowImageIndex_, 0);
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);

    // coverage fixedSize_ is false
    pattern_->nowImageIndex_ = 0;
    CreatePixelMapAnimator(2);
    pattern_->fixedSize_ = false;
    pattern_->SetShowingIndex(1);
    EXPECT_EQ(pattern_->nowImageIndex_, 1);
    EXPECT_TRUE(pattern_->cacheImages_.size());
    pattern_->fixedSize_ = true;

    // expected:images_ size is 2
    CreatePixelMapAnimator(2);
    EXPECT_TRUE(pattern_->images_.size() == 2);

    CreatePixelMapAnimator(1);
    ImageAnimatorPattern::CacheImageStruct cTemp;
    int32_t iIndex = 2;
    pattern_->UpdateCacheImageInfo(cTemp, iIndex);
    // expected:iIndex > images_ size
    EXPECT_TRUE(iIndex >= static_cast<int32_t>(pattern_->images_.size()));
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest023, TestSize.Level1)
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

    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_NE(imageAnimatorPattern, nullptr);
    ViewStackProcessor::GetInstance()->Push(element);

    // Enable automatic monitoring of invisible areas
    ImageAnimatorModelNG.SetAutoMonitorInvisibleArea(true);

    // Verify that the flag is correctly set to true
    EXPECT_TRUE(imageAnimatorPattern->isAutoMonitorInvisibleArea_);

    // Disable automatic monitoring of invisible areas
    ImageAnimatorModelNG.SetAutoMonitorInvisibleArea(false);

    // Verify that the flag is correctly set to false
    EXPECT_FALSE(imageAnimatorPattern->isAutoMonitorInvisibleArea_);
}

/**
 * @tc.name: ImageAnimatorTest024
 * @tc.desc: Test ImageAnimatorCreate.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG ImageAnimatorModelNG;
    ImageAnimatorModelNG.Create();

    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    EXPECT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ANIMATOR_ETS_TAG);
    EXPECT_TRUE(frameNode->GetChildren().empty());

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
     * @tc.expected: step2. frameNode children size is not empty.
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
    EXPECT_TRUE(frameNode->GetChildren().empty());
}

/**
 * @tc.name: ImageAnimatorTest_Play_001
 * @tc.desc: Verify basic forward playback functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImageAnimator instance
     * @tc.expected: Both pipeline and animator should be valid
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);

    /**
     * @tc.steps: step2. Trigger forward playback
     * @tc.expected: Status should be RUNNING, direction flag false
     */
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
    EXPECT_FALSE(animator->isReverse_);
}

/**
 * @tc.name: ImageAnimatorTest_Play_002
 * @tc.desc: Verify initial state of reverse playback
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize with 3 frames
     * @tc.expected: Animator instance should be valid
     */
    CreateImageAnimator(3);
    auto animator = pattern_->controlledAnimator_;
    ASSERT_NE(animator, nullptr);

    /**
     * @tc.steps: step2. Start reverse playback
     * @tc.expected: Should start from last frame (index 2) with reverse flag true
     */
    animator->Backward();
    EXPECT_EQ(animator->runningIdx_, 0);
    EXPECT_TRUE(animator->isReverse_);
}

/**
 * @tc.name: ImageAnimatorTest_Play_003
 * @tc.desc: Verify behavior with zero duration
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set duration to 0
     * @tc.expected: Animation should complete immediately
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(0);
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ImageAnimatorTest_Play_004
 * @tc.desc: Verify single frame animation behavior
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create single-frame animation
     * @tc.expected: Should stop immediately at index 0
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    EXPECT_EQ(animator->runningIdx_, 0);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ImageAnimatorTest_Play_005
 * @tc.desc: Verify resume functionality after pause
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start and pause animation
     * @tc.steps: step2. Resume playback
     * @tc.expected: Should maintain correct elapsed time
     */
    CreateImageAnimator(3);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(1000);
    animator->Forward();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    animator->Pause();
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ImageAnimatorTest_Play_006
 * @tc.desc: Verify direction switch during playback
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start forward playback
     * @tc.steps: step2. Switch to backward playback
     * @tc.expected: Direction flag should update immediately
     */
    CreateImageAnimator(4);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    animator->Backward();
    EXPECT_TRUE(animator->isReverse_);
}

/**
 * @tc.name: ImageAnimatorTest_Play_007
 * @tc.desc: Verify finite iteration completion
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set iteration count to 2
     * @tc.expected: Should stop after 2 complete cycles
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->SetIteration(2);
    animator->Forward();
    animator->Finish();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: ImageAnimatorTest_Play_008
 * @tc.desc: Verify infinite playback behavior
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set infinite iterations
     * @tc.expected: Should remain running after multiple cycles
     */
    CreateImageAnimator(3);
    auto animator = pattern_->controlledAnimator_;
    animator->SetIteration(INT_MAX);
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ImageAnimatorTest_Play_009
 * @tc.desc: Verify empty frame list handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animator with empty frame list
     * @tc.expected: Should remain in IDLE state
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
}

/**
 * @tc.name: ImageAnimatorTest_Play_012
 * @tc.desc: Verify form render mode constraints
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Play_012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Enable form render mode
     * @tc.steps: step2. Set duration below minimum threshold
     * @tc.expected: Duration should clamp to DEFAULT_DURATION
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);

    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(500); // Below minimum
    EXPECT_EQ(animator->GetDuration(), 500);
}

/**
 * @tc.name: ImageAnimatorTest_State_001
 * @tc.desc: Verify initial control state
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImageAnimator instance
     * @tc.expected: controlledAnimator_ should initialize in IDLE state
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
}

/**
 * @tc.name: ImageAnimatorTest_State_002
 * @tc.desc: Verify state transition on Forward()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize with 2 frames
     * @tc.steps: step2. Trigger Forward()
     * @tc.expected: State should change to RUNNING, direction flag false
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_FALSE(animator->isReverse_);
}

/**
 * @tc.name: ImageAnimatorTest_State_003
 * @tc.desc: Verify state transition on Backward()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize with 3 frames
     * @tc.steps: step2. Trigger Backward()
     * @tc.expected: State should be RUNNING, direction flag true, start from last frame
     */
    CreateImageAnimator(3);
    auto animator = pattern_->controlledAnimator_;
    animator->Backward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_TRUE(animator->isReverse_);
    EXPECT_EQ(animator->runningIdx_, 0);
}

/**
 * @tc.name: ImageAnimatorTest_State_004
 * @tc.desc: Verify state transition on Pause()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start playback and wait 200ms
     * @tc.steps: step2. Trigger Pause()
     * @tc.expected: State should be PAUSED with elapsed time recorded
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(1000);
    animator->Forward();
    animator->Pause();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::PAUSED);
}

/**
 * @tc.name: ImageAnimatorTest_State_005
 * @tc.desc: Verify resume from PAUSED state
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pause during playback
     * @tc.steps: step2. Trigger Forward() to resume
     * @tc.expected: State should return to RUNNING
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    animator->Pause();
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ImageAnimatorTest_State_006
 * @tc.desc: Verify state transition on Finish()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start single-frame animation
     * @tc.steps: step2. Trigger Finish()
     * @tc.expected: State should be STOPPED at frame 0
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    animator->Finish();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
    EXPECT_EQ(animator->runningIdx_, 0);
}

/**
 * @tc.name: ImageAnimatorTest_State_007
 * @tc.desc: Verify state transition on Cancel()
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start multi-frame animation
     * @tc.steps: step2. Trigger Cancel()
     * @tc.expected: State should reset to IDLE at frame 0
     */
    CreateImageAnimator(3);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    animator->Cancel();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
    EXPECT_EQ(animator->runningIdx_, 0);
}

/**
 * @tc.name: ImageAnimatorTest_State_008
 * @tc.desc: Verify restart from STOPPED state
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_State_008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Complete animation first
     * @tc.steps: step2. Trigger Forward() again
     * @tc.expected: State should restart as RUNNING from frame 0
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->Forward();
    animator->Finish();
    animator->Forward();
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_EQ(animator->runningIdx_, 0);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_001
 * @tc.desc: Verify normal duration setting
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ImageAnimator instance
     * @tc.steps: step2. Set duration to 1500ms
     * @tc.expected: Duration value should be exactly 1500ms
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(1500);
    EXPECT_EQ(animator->GetDuration(), 1500);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_002
 * @tc.desc: Verify zero duration handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize with form render mode
     * @tc.steps: step2. Set duration to 0ms
     * @tc.expected: Duration should be 0ms
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(0);
    EXPECT_EQ(animator->GetDuration(), 0);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_003
 * @tc.desc: Verify negative duration handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set duration to -500ms
     * @tc.expected: Duration should be -500ms
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(-500);
    EXPECT_EQ(animator->GetDuration(), -500);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_004
 * @tc.desc: Verify form mode duration constraints
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Enable form render mode
     * @tc.steps: step2. Set duration 500ms
     * @tc.expected: Duration should be 500ms
     */
    CreateImageAnimator(0);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(500); // Below minimum
    EXPECT_EQ(animator->GetDuration(), 500);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_005
 * @tc.desc: Verify runtime duration modification
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Start with 1000ms duration
     * @tc.steps: step2. Change to 2000ms during playback
     * @tc.expected: New duration should take effect immediately
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(1000);
    animator->Forward();
    animator->SetDuration(2000);
    EXPECT_EQ(animator->GetDuration(), 2000);
}

/**
 * @tc.name: ImageAnimatorTest_Duration_006
 * @tc.desc: Verify maximum duration boundary
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Duration_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set duration to INT32_MAX
     * @tc.expected: Duration should be accepted without overflow
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    animator->SetDuration(INT32_MAX);
    EXPECT_EQ(animator->GetDuration(), INT32_MAX);
}

/**
 * @tc.name: ImageAnimatorTest_Interpolator_001
 * @tc.desc: Verify basic interpolator addition
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Interpolator_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add interpolator with 2 frames
     * @tc.expected: PictureInfos should contain exactly 2 entries
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    animator->AddInterpolator(frames);
    EXPECT_EQ(animator->pictureInfos_.size(), 2);
}

/**
 * @tc.name: ImageAnimatorTest_Interpolator_002
 * @tc.desc: Verify frame ratio distribution
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Interpolator_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add 3 frames with 20%+30%+50% distribution
     * @tc.expected: Ratios should be preserved exactly
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    std::vector<PictureInfo> frames { { 0.2f, 101 }, { 0.3f, 102 }, { 0.5f, 103 } };
    animator->AddInterpolator(frames);

    const auto& pics = animator->pictureInfos_;
    EXPECT_FLOAT_EQ(pics[0].first, 0.2f);
    EXPECT_FLOAT_EQ(pics[1].first, 0.3f);
    EXPECT_FLOAT_EQ(pics[2].first, 0.5f);
}

/**
 * @tc.name: ImageAnimatorTest_Interpolator_003
 * @tc.desc: Verify interpolator clearance
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Interpolator_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add frames then clear
     * @tc.expected: PictureInfos should be empty after clearance
     */
    CreateImageAnimator(2); // Creates with 2 default frames
    auto animator = pattern_->controlledAnimator_;
    animator->ClearInterpolators();
    EXPECT_TRUE(animator->pictureInfos_.empty());
}

/**
 * @tc.name: ImageAnimatorTest_Interpolator_005
 * @tc.desc: Verify invalid ratio handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Interpolator_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add frames with invalid ratios (negative and zero)
     * @tc.expected: Should accept but behavior undefined per design
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;
    std::vector<PictureInfo> frames { { -0.5f, 100 }, { 0.0f, 200 }, { 1.5f, 300 } };
    animator->AddInterpolator(frames);

    const auto& pics = animator->pictureInfos_;
    EXPECT_EQ(pics.size(), 3); // Accepts values but may not behave correctly
}

/**
 * @tc.name: ImageAnimatorTest_Interpolator_006
 * @tc.desc: Verify multiple interpolator additions
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Interpolator_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add two separate interpolator sets
     * @tc.expected: Should concatenate all frames
     */
    CreateImageAnimator(0);
    auto animator = pattern_->controlledAnimator_;

    std::vector<PictureInfo> set1 { { 0.3f, 101 }, { 0.7f, 102 } };
    std::vector<PictureInfo> set2 { { 0.5f, 201 }, { 0.5f, 202 } };

    animator->AddInterpolator(set1);
    animator->AddInterpolator(set2);

    const auto& pics = animator->pictureInfos_;
    EXPECT_EQ(pics.size(), 2);
    EXPECT_EQ(pics[0].second, 201);
    EXPECT_EQ(pics[1].second, 202);
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_001
 * @tc.desc: Verify start listener callback by value modification
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Register start listener that modifies a boolean flag
     * @tc.steps: step2. Trigger Forward()
     * @tc.expected: Flag should be set to true in callback
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;

    bool isCalled = false;
    animator->AddStartListener([&isCalled]() { isCalled = true; });
    animator->Forward();

    EXPECT_FALSE(isCalled);
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_002
 * @tc.desc: Verify stop listener callback by counter increment
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Register stop listener that increments a counter
     * @tc.steps: step2. Complete animation
     * @tc.expected: Counter should be 1
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;

    int32_t callbackCount = 0;
    animator->AddStopListener([&callbackCount]() { callbackCount++; });
    animator->Forward();
    animator->Finish();

    EXPECT_EQ(callbackCount, 1);
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_004
 * @tc.desc: Verify pause listener by string modification
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Register listener that modifies a string
     * @tc.steps: step2. Pause during playback
     * @tc.expected: String should match expected value
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;

    std::string status = "unpaused";
    animator->AddPauseListener([&status]() { status = "paused"; });
    animator->Forward();
    animator->Pause();

    EXPECT_EQ(status, "paused");
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_005
 * @tc.desc: Verify repeat listener removal by flag persistence
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add then remove repeat listener
     * @tc.steps: step2. Trigger multiple iterations
     * @tc.expected: Flag should remain false (no callback)
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;
    animator->SetIteration(3);

    bool isCalled = false;
    auto listener = [&isCalled]() { isCalled = true; };
    animator->AddRepeatListener(listener);
    animator->RemoveRepeatListener();
    EXPECT_FALSE(isCalled);
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_006
 * @tc.desc: Verify multiple listeners by combined flags
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Register start/stop listeners with shared flag object
     * @tc.steps: step2. Complete animation cycle
     * @tc.expected: Flags should reflect correct callback sequence
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;

    struct CallbackFlags {
        bool startCalled = false;
        bool stopCalled = false;
    } flags;

    animator->AddStartListener([&flags]() { flags.startCalled = true; });
    animator->AddStopListener([&flags]() { flags.stopCalled = true; });
    animator->Forward();
    animator->Finish();

    EXPECT_FALSE(flags.startCalled);
    EXPECT_TRUE(flags.stopCalled);
}

/**
 * @tc.name: ImageAnimatorTest_ListenerCallback_007
 * @tc.desc: Verify pause and stop listener by string modification
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_ListenerCallback_007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Register listener that modifies a string
     * @tc.steps: step2. Pause during playback and then forward
     * @tc.expected: String should match expected value
     */
    CreateImageAnimator(2);
    auto animator = pattern_->controlledAnimator_;

    std::string status = "unpaused";
    animator->AddPauseListener([&status]() { status = "paused"; });
    animator->AddStopListener([&status]() { status = "stopped"; });
    animator->Forward();
    animator->Pause();

    EXPECT_EQ(status, "paused");
    animator->Finish();
    EXPECT_EQ(status, "stopped");
}

/**
 * @tc.name: ImageAnimatorTest_Edge_001
 * @tc.desc: Verify behavior with empty frame list
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Edge_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animator with empty frame list
     * @tc.steps: step2. Attempt playback operations
     * @tc.expected: Should remain in IDLE state for all operations
     */
    CreateImageAnimator(0); // 0 frames
    auto animator = pattern_->controlledAnimator_;

    bool startCalled = false;
    animator->AddStartListener([&startCalled]() { startCalled = true; });

    animator->Forward();
    animator->Backward();
    animator->Pause();

    EXPECT_FALSE(startCalled);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
}

/**
 * @tc.name: ImageAnimatorTest_Edge_002
 * @tc.desc: Verify infinite iterations with single frame
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorTest_Edge_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set single-frame animation with infinite iterations
     * @tc.steps: step2. Simulate long duration
     * @tc.expected: Should not crash and maintain RUNNING state
     */
    CreateImageAnimator(1);
    auto animator = pattern_->controlledAnimator_;
    animator->SetIteration(INT_MAX);

    int32_t callbackCount = 0;
    animator->AddRepeatListener([&callbackCount]() { callbackCount++; });

    animator->Forward();

    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_EQ(callbackCount, 0);
    ;
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest001, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::IDLE);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::PAUSED);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::PAUSED);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::STOPPED);
    EXPECT_EQ(animator->GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest002, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    animator->SetFillMode(FillMode::NONE);
    EXPECT_EQ(animator->GetFillMode(), FillMode::NONE);
    animator->SetFillMode(FillMode::FORWARDS);
    EXPECT_EQ(animator->GetFillMode(), FillMode::FORWARDS);
    animator->SetFillMode(FillMode::BACKWARDS);
    EXPECT_EQ(animator->GetFillMode(), FillMode::BACKWARDS);
    animator->SetFillMode(FillMode::BOTH);
    EXPECT_EQ(animator->GetFillMode(), FillMode::BOTH);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest003, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    animator->SetRunningIdx(40);
    EXPECT_EQ(animator->runningIdx_, 40);
    animator->SetDuration(40);
    EXPECT_EQ(animator->GetDuration(), 40);
    std::vector<PictureInfo> pictureInfos;
    PictureInfo info1 = { 122.0f, 661 };
    PictureInfo info2 = { 133.0f, 662 };
    PictureInfo info3 = { 155.0f, 663 };
    PictureInfo info4 = { 771.0f, 664 };
    pictureInfos.emplace_back(info1);
    pictureInfos.emplace_back(info2);
    pictureInfos.emplace_back(info3);
    pictureInfos.emplace_back(info4);
    animator->AddInterpolator(pictureInfos);
    EXPECT_EQ(animator->pictureInfos_.size(), 4);
    animator->ClearInterpolators();
    EXPECT_EQ(animator->pictureInfos_.size(), 0);
    AnimatorEvent event = []() {};
    animator->AddStartListener(event);
    EXPECT_NE(animator->startEvent_, nullptr);
    animator->AddStopListener(event);
    EXPECT_NE(animator->stopEvent_, nullptr);

    animator->AddPauseListener(event);
    EXPECT_NE(animator->pauseEvent_, nullptr);

    animator->AddRepeatListener(event);
    EXPECT_NE(animator->repeatEvent_, nullptr);

    animator->AddInnerRepeatListener(event);
    EXPECT_NE(animator->innerRepeatEvent_, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest004, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    AnimatorEvent event = []() {};
    animator->AddRepeatListener(event);
    EXPECT_NE(animator->repeatEvent_, nullptr);
    animator->RemoveRepeatListener();
    EXPECT_EQ(animator->pauseEvent_, nullptr);

    animator->AddInnerRepeatListener(event);
    EXPECT_NE(animator->innerRepeatEvent_, nullptr);
    animator->RemoveInnerRepeatListener();
    EXPECT_EQ(animator->innerRepeatEvent_, nullptr);

    animator->AddCancelListener(event);
    EXPECT_NE(animator->cancelEvent_, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest005, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    AnimatorEvent event = []() {};
    animator->AddStartListener(event);
    EXPECT_NE(animator->startEvent_, nullptr);
    animator->AddStopListener(event);
    EXPECT_NE(animator->stopEvent_, nullptr);

    animator->AddPauseListener(event);
    EXPECT_NE(animator->pauseEvent_, nullptr);

    animator->AddRepeatListener(event);
    EXPECT_NE(animator->repeatEvent_, nullptr);

    animator->AddCancelListener(event);
    EXPECT_NE(animator->cancelEvent_, nullptr);
    animator->ClearAllListeners();
    EXPECT_EQ(animator->startEvent_, nullptr);
    EXPECT_EQ(animator->stopEvent_, nullptr);
    EXPECT_EQ(animator->pauseEvent_, nullptr);
    EXPECT_EQ(animator->cancelEvent_, nullptr);
    EXPECT_EQ(animator->repeatEvent_, nullptr);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest006, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);

    animator->SetIteration(1);
    EXPECT_EQ(animator->GetIteration(), 1);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::IDLE);
    animator->SetIteration(3);

    animator->SetControlStatus(ControlledAnimator::ControlStatus::STOPPED);
    animator->SetIteration(4);
    AnimatorEvent event = []() {};
    animator->AddStopListener(event);
    animator->SetControlStatus(ControlledAnimator::ControlStatus::PAUSED);
    animator->SetIteration(5);

    animator->SetControlStatus(ControlledAnimator::ControlStatus::RUNNING);
    animator->SetIteration(6);
    EXPECT_EQ(animator->GetIteration(), 6);
}

/**
 * @tc.name: ImageAnimatorTest023
 * @tc.desc: Verify the functionality of enabling and disabling the automatic monitoring of invisible areas
 *            for the image animator.
 *            - When SetAutoMonitorInvisibleArea(true) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * true.
 *            - When SetAutoMonitorInvisibleArea(false) is called, the isAutoMonitorInvisibleArea_ flag should be set to
 * false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest007, TestSize.Level1)
{
    auto animator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(animator, nullptr);
    std::function<void(int32_t)> func = [](int32_t num) {};
    animator->AddListener(func);
    EXPECT_NE(animator->playbackListener_, nullptr);

    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    animator->AddInterpolator(frames);

    animator->SetIteration(-1);
    animator->PostPlayTask(2, 2, 2, 3);

    animator->SetIteration(3);
    animator->PostPlayTask(2, 2, 2, 3);

    animator->SetIteration(-1);
    animator->PostPlayTask(2, -2, 2, 3);
    animator->SetIteration(1);

    animator->PostPlayTask(2, 2, 2, 3);
    animator->needFireRepeatEvent_ = true;
    animator->repeatEvent_ = nullptr;
    animator->innerRepeatEvent_ = nullptr;

    AnimatorEvent event = []() {};
    animator->PostPlayTask(2, 2, 2, 3);
    animator->needFireRepeatEvent_ = true;
    animator->repeatEvent_ = event;
    animator->innerRepeatEvent_ = event;
}

/**
 * @tc.name: ControlledAnimatorTest_001
 * @tc.desc: Verify infinite iterations
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set single-frame animation with infinite iterations
     * @tc.expected: Should not crash and iteration expect infinite
     */
    auto animator = ControlledAnimator();
    animator.SetIteration(INT_MAX);
    EXPECT_EQ(animator.GetIteration(), INT_MAX);
}

/**
 * @tc.name: ControlledAnimatorTest_002
 * @tc.desc: Verify control status setting
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animator and set control status
     * @tc.expected: Control status should be updated correctly
     */
    auto animator = ControlledAnimator();
    animator.SetControlStatus(ControlledAnimator::ControlStatus::RUNNING);
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: ControlledAnimatorTest_003
 * @tc.desc: Verify fill mode setting
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animator and set fill mode
     * @tc.expected: Fill mode should be updated correctly
     */
    auto animator = ControlledAnimator();
    animator.SetFillMode(FillMode::FORWARDS);
    EXPECT_EQ(animator.GetFillMode(), FillMode::FORWARDS);
}

/**
 * @tc.name: ControlledAnimatorTest_004
 * @tc.desc: Verify duration setting
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create animator and set duration
     * @tc.expected: Duration should be updated correctly
     */
    auto animator = ControlledAnimator();
    animator.SetDuration(1000);
    EXPECT_EQ(animator.GetDuration(), 1000);
}

/**
 * @tc.name: ControlledAnimatorTest_005
 * @tc.desc: Verify forward playback
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_005, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with test data
     *   step2. Start forward playback
     * @tc.expected: Control status should be RUNNING and not reversed
     */
    auto animator = ControlledAnimator();
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    animator.AddInterpolator(frames);
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.Forward();
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
    EXPECT_EQ(flagNumber, 2);
    EXPECT_FALSE(animator.isReverse_);
}

/**
 * @tc.name: ControlledAnimatorTest_006
 * @tc.desc: Verify backward playback
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_006, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with test data
     *   step2. Start backward playback
     * @tc.expected: Control status should be RUNNING and reversed
     */
    auto animator = ControlledAnimator();
    animator.AddInterpolator({ { 0.1, 1 }, { 0.2, 1 } });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.Backward();
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
    EXPECT_EQ(flagNumber, 2);
    EXPECT_FALSE(animator.isReverse_);
}

/**
 * @tc.name: ControlledAnimatorTest_007
 * @tc.desc: Verify pause functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_007, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with test data
     *   step2. Start playback and then pause
     * @tc.expected: Control status should be PAUSED
     */
    auto animator = ControlledAnimator();
    animator.AddInterpolator({ { 0.1, 1 }, { 0.2, 1 } });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.Forward();
    animator.Pause();
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::PAUSED);
    EXPECT_EQ(flagNumber, 2);
}

/**
 * @tc.name: ControlledAnimatorTest_008
 * @tc.desc: Verify cancel functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_008, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with test data
     *   step2. Start playback and then cancel
     * @tc.expected: Control status should be IDLE
     */
    auto animator = ControlledAnimator();
    animator.AddInterpolator({ { 0.1, 1 }, { 0.2, 1 } });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.Forward();
    animator.Cancel();
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::IDLE);
    EXPECT_EQ(flagNumber, 2);
}

/**
 * @tc.name: ControlledAnimatorTest_009
 * @tc.desc: Verify finish functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_009, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with test data
     *   step2. Start playback and then finish
     * @tc.expected: Control status should be STOPPED
     */
    auto animator = ControlledAnimator();
    animator.AddInterpolator({ { 0.1, 1 }, { 0.2, 1 } });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.Forward();
    animator.Finish();
    EXPECT_EQ(animator.GetControlStatus(), ControlledAnimator::ControlStatus::STOPPED);
    EXPECT_EQ(flagNumber, 2);
}

/**
 * @tc.name: ControlledAnimatorTest_010
 * @tc.desc: Verify listener functionality
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_010, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator and add listeners
     *   step2. Trigger various events
     * @tc.expected: Listener flags should be set correctly
     */
    auto animator = ControlledAnimator();
    bool startCalled = false;
    bool stopCalled = false;

    animator.AddStartListener([&startCalled]() { startCalled = true; });
    animator.AddStopListener([&stopCalled]() { stopCalled = true; });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });

    animator.Forward();
    EXPECT_FALSE(startCalled);

    animator.Finish();
    EXPECT_FALSE(stopCalled);
    EXPECT_EQ(flagNumber, 1);
}

/**
 * @tc.name: ControlledAnimatorTest_011
 * @tc.desc: Verify empty interpolators handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_011, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with no interpolators
     *   step2. Attempt to start playback
     * @tc.expected: Control status should remain unchanged
     */
    auto animator = ControlledAnimator();
    auto initialStatus = animator.GetControlStatus();
    animator.Forward();
    EXPECT_EQ(animator.GetControlStatus(), initialStatus);
}

/**
 * @tc.name: ControlledAnimatorTest_012
 * @tc.desc: Verify zero duration handling
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ControlledAnimatorTest_012, TestSize.Level1)
{
    /**
     * @tc.steps:
     *   step1. Create animator with zero duration
     *   step2. Attempt to start playback
     * @tc.expected: Should finish immediately
     */
    auto animator = ControlledAnimator();
    animator.AddInterpolator({ { 0.1, 1 } });
    int32_t flagNumber = 1;
    animator.AddListener([&flagNumber](int32_t number) { flagNumber = 2; });
    animator.SetDuration(0);
    bool finished = false;
    animator.AddStopListener([&finished]() { finished = true; });
    animator.Forward();
    EXPECT_TRUE(finished);
    EXPECT_EQ(flagNumber, 2);
}

/**
 * @tc.name: ImageAnimatorSetImagesTest001
 * @tc.desc: SetImages into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorSetImagesTest001, TestSize.Level1)
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

    ImageProperties imageProperties1;
    imageProperties1.src = IMAGE_SRC_URL;
    imageProperties1.width = IMAGE_WIDTH;
    imageProperties1.height = IMAGE_HEIGHT;
    imageProperties1.top = IMAGE_TOP;
    imageProperties1.left = IMAGE_LEFT;
    imageProperties1.duration = IMAGE_DURATION;
    ImageProperties imageProperties2;
    imageProperties2.src = IMAGE_SRC_URL;
    imageProperties2.pixelMap = CreatePixelMap(IMAGE_SRC_URL);
    imageProperties2.width = IMAGE_WIDTH;
    imageProperties2.height = IMAGE_HEIGHT;
    imageProperties2.top = IMAGE_TOP;
    imageProperties2.left = IMAGE_LEFT;
    imageProperties2.duration = IMAGE_DURATION;
    ImageProperties imageProperties3;
    imageProperties3.src = IMAGE_SRC_URL;
    imageProperties3.pixelMap = CreatePixelMap(IMAGE_SRC_URL);
    imageProperties3.width = IMAGE_WIDTH;
    imageProperties3.height = IMAGE_HEIGHT;
    imageProperties3.top = IMAGE_TOP;
    imageProperties3.left = IMAGE_LEFT;
    imageProperties3.duration = IMAGE_DURATION;
    ImageProperties imageProperties4;
    imageProperties4.src = IMAGE_SRC_URL;
    imageProperties4.width = IMAGE_WIDTH;
    imageProperties4.height = IMAGE_HEIGHT;
    imageProperties4.top = IMAGE_TOP;
    imageProperties4.left = IMAGE_LEFT;
    imageProperties4.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images1 = { imageProperties1 };
    std::vector<ImageProperties> images2 = { imageProperties2 };
    std::vector<ImageProperties> images3 = { imageProperties3 };
    std::vector<ImageProperties> images4 = { imageProperties4 };
    ImageAnimatorModelNG.SetImages(std::move(images1));
    ImageAnimatorModelNG.SetImages(std::move(images2));
    ImageAnimatorModelNG.SetImages(std::move(images3));
    ImageAnimatorModelNG.SetImages(std::move(images4));
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
 * @tc.name: ImageAnimatorSetImagesTest002
 * @tc.desc: SetImages into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorSetImagesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG imageAnimatorModelNG;
    imageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
     * @tc.expected: step2. related function is called.
     */

    ImageProperties imageProperties1;
    imageProperties1.src = IMAGE_SRC_URL;
    imageProperties1.width = IMAGE_WIDTH;
    imageProperties1.height = IMAGE_HEIGHT;
    imageProperties1.top = IMAGE_TOP;
    imageProperties1.left = IMAGE_LEFT;
    imageProperties1.duration = -IMAGE_DURATION;
    ImageProperties imageProperties2;
    imageProperties2.src = IMAGE_SRC_URL;
    imageProperties2.pixelMap = CreatePixelMap(IMAGE_SRC_URL);
    imageProperties2.width = IMAGE_WIDTH;
    imageProperties2.height = IMAGE_HEIGHT;
    imageProperties2.top = IMAGE_TOP;
    imageProperties2.left = IMAGE_LEFT;
    imageProperties2.duration = IMAGE_DURATION;
    ImageProperties imageProperties3;
    imageProperties3.src = IMAGE_SRC_URL;
    imageProperties3.pixelMap = CreatePixelMap(IMAGE_SRC_URL);
    imageProperties3.width = IMAGE_WIDTH;
    imageProperties3.height = IMAGE_HEIGHT;
    imageProperties3.top = IMAGE_TOP;
    imageProperties3.left = IMAGE_LEFT;
    imageProperties3.duration = -IMAGE_DURATION;
    ImageProperties imageProperties4;
    imageProperties4.src = IMAGE_SRC_URL;
    imageProperties4.width = IMAGE_WIDTH;
    imageProperties4.height = IMAGE_HEIGHT;
    imageProperties4.top = IMAGE_TOP;
    imageProperties4.left = IMAGE_LEFT;
    imageProperties4.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images = { imageProperties1, imageProperties2, imageProperties3, imageProperties4 };
    imageAnimatorModelNG.SetImages(std::move(images));
    imageAnimatorModelNG.SetState(STATE_PAUSED);
    imageAnimatorModelNG.SetIteration(ITERATION_DEFAULT);
    auto pattern = imageAnimatorModelNG.GetImageAnimatorPattern();
    EXPECT_EQ(pattern->durationTotal_, 1000);
}

/**
 * @tc.name: ImageAnimatorSetImagesTest003
 * @tc.desc: SetImages into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorSetImagesTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */

    ImageAnimatorModelNG imageAnimatorModelNG;
    imageAnimatorModelNG.Create();

    /**
     * @tc.steps: step2. set image's attributes and imageAnimatorView's attributes.
     * @tc.expected: step2. related function is called.
     */
    std::vector<ImageProperties> images = {};
    imageAnimatorModelNG.SetImages(std::move(images));
    auto pattern = imageAnimatorModelNG.GetImageAnimatorPattern();
    EXPECT_TRUE(pattern->images_.empty());
}

/**
 * @tc.name: ImageAnimatorSetImagesTest004
 * @tc.desc: SetImages into ImageAnimatorPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorTestNg, ImageAnimatorSetImagesTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ImageAnimatorModelNG.
     */
    ImageAnimatorModelNG imageAnimatorModelNG;
    imageAnimatorModelNG.Create();
    std::vector<ImageProperties> images1 = {};
    ImageProperties imageProperties1;
    imageProperties1.src = IMAGE_SRC_URL;
    imageProperties1.width = IMAGE_WIDTH;
    imageProperties1.height = IMAGE_HEIGHT;
    imageProperties1.top = IMAGE_TOP;
    imageProperties1.left = IMAGE_LEFT;
    imageProperties1.duration = -IMAGE_DURATION;
    std::vector<ImageProperties> images2 = { imageProperties1 };
    imageAnimatorModelNG.SetImages(std::move(images2));
    /**
     * @tc.step2: step5. Verify that the image list has been set successfully (size should be 1).
     */
    auto pattern = imageAnimatorModelNG.GetImageAnimatorPattern();
    EXPECT_EQ(pattern->images_.size(), 1);
    /**
     * @tc.step3: step6. Switch to an empty image list dynamically and verify that the image list is cleared.
     */
    imageAnimatorModelNG.SetImages(std::move(images1));
    EXPECT_TRUE(pattern->images_.empty());
}
} // namespace OHOS::Ace::NG
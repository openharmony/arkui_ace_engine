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
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
} // namespace OHOS::Ace::NG
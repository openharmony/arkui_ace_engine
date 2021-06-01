/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/fake_asset_manager.h"
#include "adapter/ohos/osal/fake_task_executor.h"
#include "base/log/log.h"
#include "core/animation/card_transition_controller.h"
#include "core/animation/curve_animation.h"
#include "core/animation/keyframe_animation.h"
#include "core/components/box/box_component.h"
#include "core/components/test/json/json_frontend.h"
#include "core/components/test/unittest/mock/render_mock.h"
#include "core/components/test/unittest/mock/transform_mock.h"
#include "core/components/test/unittest/mock/tween_mock.h"
#include "core/components/test/unittest/mock/window_mock.h"
#include "core/components/tween/tween_component.h"
#include "core/components/tween/tween_element.h"
#include "core/mock/mock_resource_register.h"
#include "core/pipeline/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

CardTransitionController::CardTransitionController(const WeakPtr<PipelineContext>& context) {};

void CardTransitionController::RegisterTransitionListener() {};

RRect CardTransitionController::GetCardRect(const ComposeId& composeId) const
{
    return RRect();
}

namespace {

constexpr int32_t NANOSECOND_TO_MILLISECOND = 1000000;
constexpr int32_t FRAME_TIME_IN_MILLISECOND = 10;
constexpr int32_t TEST_SURFACE_WIDTH = 1080;
constexpr int32_t TEST_SURFACE_HEIGHT = 1920;
constexpr float ABS_ERROR = 0.1f;
using ConfigTweenComponent = std::function<void(const RefPtr<TweenComponent>&)>;
ConfigTweenComponent g_configTweenComponent;

void CreateScaleTweenKeyFrame(TweenOption& tweenOption, float begin, float end)
{
    auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, begin);
    auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, end);
    auto scale = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    scale->AddKeyframe(keyframe1);
    scale->AddKeyframe(keyframe2);
    tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
}

} // namespace

class TweenElementTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        GTEST_LOG_(INFO) << "TweenElementTest SetUpTestCase";
    }

    static void TearDownTestCase()
    {
        GTEST_LOG_(INFO) << "TweenElementTest TearDownTestCase";
    }

    void SetUp() override
    {
        MockRenderDisplay::SetMockHook(
            [this](const RefPtr<MockRenderDisplay>& displayRender) { displayRender_ = displayRender; });
        MockTweenComponent::SetMockHook(
            [this](const RefPtr<TweenElement>& tweenElement) { tweenElement_ = tweenElement; });
        MockRenderTransform::SetMockHook(
            [this](const RefPtr<MockRenderTransform>& transformRender) { transformRender_ = transformRender; });
    }

    void TearDown() override {}

    void CreateAndBuildTweenComponent()
    {
        std::unique_ptr<PlatformWindow> platformWindow = TweenTestUtils::CreatePlatformWindow();
        platformWindowRaw_ = reinterpret_cast<MockPlatformWindow*>(platformWindow.get());
        auto window = TweenTestUtils::CreateWindow(std::move(platformWindow));
        auto taskExecutor = AceType::MakeRefPtr<FakeTaskExecutor>();
        auto assetManager = Referenced::MakeRefPtr<FakeAssetManager>();
        auto resRegister = Referenced::MakeRefPtr<MockResourceRegister>();
        RefPtr<Frontend> frontend = Frontend::CreateDefault();
        context_ = AceType::MakeRefPtr<PipelineContext>(
            std::move(window), taskExecutor, assetManager, resRegister, frontend, 0);
        context_->SetTimeProvider(
            [this] { return this->platformWindowRaw_->GetCurrentTimestampNano() + NANOSECOND_TO_MILLISECOND * 10; });

        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
        boxComponent_->SetWidth(TEST_SURFACE_WIDTH);
        boxComponent_->SetHeight(TEST_SURFACE_HEIGHT);
        boxComponent_->SetColor(Color::WHITE);
        tweenComponent_ = AceType::MakeRefPtr<MockTweenComponent>("test_tween_id", "tween component", boxComponent_);
        if (g_configTweenComponent) {
            tweenComponent_->SetTweenOperation(TweenOperation::PLAY);
            g_configTweenComponent(tweenComponent_);
        }
        auto pageComponent = AceType::MakeRefPtr<PageComponent>(0, tweenComponent_);

        context_->SetupRootElement();
        context_->PushPage(pageComponent);
        context_->OnSurfaceChanged(TEST_SURFACE_WIDTH, TEST_SURFACE_HEIGHT);

        platformWindowRaw_->SetNanoFrameTime(NANOSECOND_TO_MILLISECOND * frameTimeMs_);
    }

protected:
    RefPtr<PipelineContext> context_;
    uint32_t frameTimeMs_ = FRAME_TIME_IN_MILLISECOND;
    MockPlatformWindow* platformWindowRaw_ = nullptr;
    RefPtr<MockRenderTransform> transformRender_;
    RefPtr<MockRenderDisplay> displayRender_;
    RefPtr<TweenElement> tweenElement_;
    RefPtr<TweenComponent> tweenComponent_;
    RefPtr<BoxComponent> boxComponent_;
};

/**
 * @tc.name: TweenScaleTest001
 * @tc.desc: test scale animation in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL3
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, TweenScaleTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest TweenScaleTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 1.0f, 4.0f);
        tweenOption.SetDuration(15);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation go
     * @tc.expected: step2. verify set curve taking effect
     */
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);

    /**
     * @tc.steps: step3. trigger last frame
     * @tc.expected: step3. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 4.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenBackgroundPositionTest001
 * @tc.desc: test background position animation in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DQ20H
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, TweenBackgroundPositionTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest TweenBackgroundPositionTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    BackgroundImagePosition backgroundImagePositionBegin =
        BackgroundImagePosition(BackgroundImagePositionType::PERCENT, 0, BackgroundImagePositionType::PX, 0);
    BackgroundImagePosition backgroundImagePositionEnd =
        BackgroundImagePosition(BackgroundImagePositionType::PERCENT, 100, BackgroundImagePositionType::PX, 50);
    g_configTweenComponent = [backgroundImagePositionBegin, backgroundImagePositionEnd](
                                 const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto backgroundPosition = AceType::MakeRefPtr<CurveAnimation<BackgroundImagePosition>>(
            backgroundImagePositionBegin, backgroundImagePositionEnd, Curves::LINEAR);
        tweenOption.SetBackgroundPositionAnimation(backgroundPosition);
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation go
     * @tc.expected: step2. verify set curve taking effect
     */
    platformWindowRaw_->TriggerOneFrame();
    auto box = AceType::DynamicCast<MockRenderBox>(tweenElement_->GetContentRender());
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_EQ(box->GetBackgroundPositionPublic(), (backgroundImagePositionEnd + backgroundImagePositionBegin) * 0.5);

    /**
     * @tc.steps: step3. trigger last frame
     * @tc.expected: step3. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_EQ(box->GetBackgroundPositionPublic(), backgroundImagePositionEnd);
}

/**
 * @tc.name: TweenElementPauseTest001
 * @tc.desc: test pause operation in tween with duration equals 0.
 * @tc.type: FUNC
 * @tc.require: AR000DSB28
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, PauseTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest PauseTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 1.0f, 4.0f);
        tweenOption.SetDuration(0);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
        tweenComponent->SetTweenOperation(TweenOperation::PAUSE);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCancelTest001
 * @tc.desc: test cancel operation in tween with duration equals 0.
 * @tc.type: FUNC
 * @tc.require: AR000DSB29
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, CancelTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CancelTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 0.5f, 4.0f);
        tweenOption.SetDuration(0);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
        tweenComponent->SetTweenOperation(TweenOperation::CANCEL);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementDurationTest001
 * @tc.desc: test negative duration value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, DurationTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest DurationTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(-4);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementDurationTest002
 * @tc.desc: test normal duration value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, DurationTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest DurationTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 1.0f, 5.0f);
        tweenOption.SetDuration(8);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementDelayTest001
 * @tc.desc: test negative delay value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, DelayTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest DelayTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetDelay(-1);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementDelayTest002
 * @tc.desc: test normal delay value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, DelayTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest DelayTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetDelay(12);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementRepeatTest001
 * @tc.desc: test repeatTimes value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, RepeatTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest RepeatTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetIteration(2);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NE(scale, 5.0f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementRepeatTest002
 * @tc.desc: test repeateTimes value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, RepeatTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest RepeatTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetIteration(-1);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NE(scale, 5.0f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NE(scale, 5.0f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NE(scale, 5.0f);
}

/**
 * @tc.name: TweenElementRepeatTest003
 * @tc.desc: test repeateTimes value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, RepeatTest003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest RepeatTest003";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetIteration(-3);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCurveTest001
 * @tc.desc: test curves value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, CurveTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CurveTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCurveTest002
 * @tc.desc: test curves value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, CurveTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CurveTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 1.0f, 5.0f);
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_LE(scale, 4.20797f);
    EXPECT_GE(scale, 4.20796f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCurveTest003
 * @tc.desc: test curves value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, CurveTest003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CurveTest003";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        CreateScaleTweenKeyFrame(tweenOption, 1.0f, 5.0f);
        tweenOption.SetDuration(20);
        tweenOption.SetCurve(Curves::EASE_IN);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_LE(scale, 2.26563f);
    EXPECT_GE(scale, 2.26562f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCurveTest004
 * @tc.desc: test curves value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, CurveTest004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CurveTest004";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetCurve(Curves::EASE_OUT);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_LE(scale, 3.73439f);
    EXPECT_GE(scale, 3.73437f);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementCurveTest005
 * @tc.desc: test curves value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL1
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, CurveTest005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest CurveTest005";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetCurve(Curves::EASE_IN_OUT);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest001
 * @tc.desc: test fillMode value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL2
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, FillModeTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetCurve(Curves::LINEAR);
        tweenOption.SetFillMode(FillMode::NONE);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    float scale = 0.0f;
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest002
 * @tc.desc: test fillMode value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DAUL2
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, FillModeTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, nullptr);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(8);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest003
 * @tc.desc: test fillMode value in tween, fillMode is backwards.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest003";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetDelay(10);
        tweenOption.SetFillMode(FillMode::BACKWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);

    // Return to the init value when the animation is over
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 0.5f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest004
 * @tc.desc: test fillMode value in tween, fillMode is both.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest004";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetDelay(10);
        tweenOption.SetFillMode(FillMode::BOTH);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, FLT_EPSILON);

    // Return to the end value when the animation is over
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest005
 * @tc.desc: test fillMode value in tween, fillMode is backwards, duration is 0.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest005";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(0);
        tweenOption.SetDelay(11);
        tweenOption.SetFillMode(FillMode::BACKWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // Return to the init value after delay time
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 0.5f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest006
 * @tc.desc: test fillMode value in tween, fillMode is both, duration is 0.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest006";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(0);
        tweenOption.SetDelay(11);
        tweenOption.SetFillMode(FillMode::BOTH);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // Return to the end value after delay time
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest007
 * @tc.desc: test fillMode value in tween, fillMode is backwards, repteat time is 2.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest007";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetDelay(10);
        tweenOption.SetIteration(2);
        tweenOption.SetFillMode(FillMode::BACKWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // first repeat time, back to begin value.
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // Return to the init value after repeat time.
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 0.5f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementFillModeTest008
 * @tc.desc: test fillMode value in tween, fillMode is both, repeat time is 2.
 * @tc.type: FUNC
 * @tc.require: AR000FL0VL
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, FillModeTest008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest FillModeTest008";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto scale = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        scale->SetInitValue(0.5f);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scale);
        tweenOption.SetDuration(20);
        tweenOption.SetDelay(10);
        tweenOption.SetIteration(2);
        tweenOption.SetFillMode(FillMode::BOTH);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the start value and end value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // In the start delay time, the animation is at the begin value
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // first repeat time, back to begin value
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 1.0f, FLT_EPSILON);

    // Return to the end value after repeat time
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, FLT_EPSILON);
}

/**
 * @tc.name: TweenElementKeyframeTest001
 * @tc.desc: test Keyframe value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, KeyframeTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest KeyframeTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        auto translateAnimation = AceType::MakeRefPtr<KeyframeAnimation<DimensionOffset>>();
        auto keyframe0 =
            AceType::MakeRefPtr<Keyframe<DimensionOffset>>(0.0f, DimensionOffset(Dimension(), Dimension()));
        auto keyframe1 = AceType::MakeRefPtr<Keyframe<DimensionOffset>>(
            0.5f, DimensionOffset(Dimension(40.0f, DimensionUnit::PX), Dimension(50.0f, DimensionUnit::PX)));
        auto keyframe2 = AceType::MakeRefPtr<Keyframe<DimensionOffset>>(
            1.0f, DimensionOffset(Dimension(100.0f, DimensionUnit::PX), Dimension(120.0f, DimensionUnit::PX)));
        translateAnimation->AddKeyframe(keyframe0);
        translateAnimation->AddKeyframe(keyframe1);
        translateAnimation->AddKeyframe(keyframe2);
        tweenOption.SetTranslateAnimations(AnimationType::TRANSLATE, translateAnimation);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    Dimension x;
    Dimension y;

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetTranslateSetting(x, y);
    EXPECT_NEAR(x.Value(), 0.0f, ABS_ERROR);
    EXPECT_NEAR(y.Value(), 0.0f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetTranslateSetting(x, y);
    EXPECT_NEAR(x.Value(), 40.0f, ABS_ERROR);
    EXPECT_NEAR(y.Value(), 50.0f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetTranslateSetting(x, y);
    EXPECT_NEAR(x.Value(), 100.0f, ABS_ERROR);
    EXPECT_NEAR(y.Value(), 120.0f, ABS_ERROR);
}

/**
 * @tc.name: TweenElementKeyframeTest002
 * @tc.desc: test Keyframe value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, KeyframeTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest KeyframeTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        tweenOption.SetDuration(40);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        auto scaleAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        auto keyframe0 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, 1.0f);
        auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.25f, 2.0f);
        auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(0.5f, 3.0f);
        auto keyframe3 = AceType::MakeRefPtr<Keyframe<float>>(0.75f, 4.0f);
        auto keyframe4 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, 5.0f);
        scaleAnimation->AddKeyframe(keyframe0);
        scaleAnimation->AddKeyframe(keyframe1);
        scaleAnimation->AddKeyframe(keyframe2);
        scaleAnimation->AddKeyframe(keyframe3);
        scaleAnimation->AddKeyframe(keyframe4);
        tweenOption.SetTransformFloatAnimation(AnimationType::SCALE, scaleAnimation);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    float scale = 0.0f;
    platformWindowRaw_->TriggerOneFrame();

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 2.0f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 3.0f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetScaleSetting(scale);
    EXPECT_NEAR(scale, 5.0f, ABS_ERROR);
}

/**
 * @tc.name: TweenElementKeyframeTest003
 * @tc.desc: test Keyframe value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: chenlien
 */
HWTEST_F(TweenElementTest, KeyframeTest003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest KeyframeTest003";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        tweenOption.SetDuration(40);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        auto rotateAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        auto keyframe0 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, 1.0f);
        auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.25f, 2.0f);
        auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(0.5f, 3.0f);
        auto keyframe3 = AceType::MakeRefPtr<Keyframe<float>>(0.75f, 4.0f);
        auto keyframe4 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, 5.0f);
        rotateAnimation->AddKeyframe(keyframe0);
        rotateAnimation->AddKeyframe(keyframe1);
        rotateAnimation->AddKeyframe(keyframe2);
        rotateAnimation->AddKeyframe(keyframe3);
        rotateAnimation->AddKeyframe(keyframe4);
        tweenOption.SetTransformFloatAnimation(AnimationType::ROTATE_X, rotateAnimation);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    float angle = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    platformWindowRaw_->TriggerOneFrame();

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetRotateSetting(angle, x, y, z);
    EXPECT_NEAR(x, 2.0, ABS_ERROR);
    EXPECT_NEAR(y, 0.0, ABS_ERROR);
    EXPECT_NEAR(z, 0.0, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetRotateSetting(angle, x, y, z);
    EXPECT_NEAR(x, 3.0, ABS_ERROR);
    EXPECT_NEAR(y, 0.0, ABS_ERROR);
    EXPECT_NEAR(z, 0.0, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    transformRender_->GetRotateSetting(angle, x, y, z);
    EXPECT_NEAR(x, 5.0, ABS_ERROR);
    EXPECT_NEAR(y, 0.0, ABS_ERROR);
    EXPECT_NEAR(z, 0.0, ABS_ERROR);
}

/**
 * @tc.name: TweenElementKeyframeTest004
 * @tc.desc: test Keyframe value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, KeyframeTest004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest KeyframeTest004";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        tweenOption.SetDuration(40);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        auto opacityAnimation = AceType::MakeRefPtr<KeyframeAnimation<float>>();
        auto keyframe0 = AceType::MakeRefPtr<Keyframe<float>>(0.0f, 1.0f);
        auto keyframe1 = AceType::MakeRefPtr<Keyframe<float>>(0.25f, 0.75f);
        auto keyframe2 = AceType::MakeRefPtr<Keyframe<float>>(0.5f, 0.5f);
        auto keyframe3 = AceType::MakeRefPtr<Keyframe<float>>(0.75f, 0.25f);
        auto keyframe4 = AceType::MakeRefPtr<Keyframe<float>>(1.0f, 0.0f);
        opacityAnimation->AddKeyframe(keyframe0);
        opacityAnimation->AddKeyframe(keyframe1);
        opacityAnimation->AddKeyframe(keyframe2);
        opacityAnimation->AddKeyframe(keyframe3);
        opacityAnimation->AddKeyframe(keyframe4);
        tweenOption.SetOpacityAnimation(opacityAnimation);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(displayRender_->GetOpacity(), 1.0f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(displayRender_->GetOpacity(), 0.75f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(displayRender_->GetOpacity(), 0.5f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(displayRender_->GetOpacity(), 0.25f, ABS_ERROR);

    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(displayRender_->GetOpacity(), 0.0f, ABS_ERROR);
}

/**
 * @tc.name: TweenElementKeyframeTest005
 * @tc.desc: test Keyframe value in tween.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, KeyframeTest005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest KeyframeTest005";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        auto colorAnimation = AceType::MakeRefPtr<KeyframeAnimation<Color>>();
        auto keyframe0 = AceType::MakeRefPtr<Keyframe<Color>>(0.0f, Color::WHITE);
        auto keyframe1 = AceType::MakeRefPtr<Keyframe<Color>>(0.5f, Color::BLACK);
        auto keyframe2 = AceType::MakeRefPtr<Keyframe<Color>>(1.0f, Color::BLUE);

        keyframe1->SetCurve(Curves::LINEAR);
        keyframe2->SetCurve(Curves::LINEAR);

        colorAnimation->AddKeyframe(keyframe0);
        colorAnimation->AddKeyframe(keyframe1);
        colorAnimation->AddKeyframe(keyframe2);

        colorAnimation->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
        tweenOption.SetColorAnimation(colorAnimation);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    auto box = AceType::DynamicCast<RenderBox>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_EQ(box->GetColor(), Color::WHITE);

    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_EQ(box->GetColor(), Color::BLUE);
}

/**
 * @tc.name: PropertyAnimationTest001
 * @tc.desc: verify float property animation
 * @tc.type: FUNC
 * @tc.require: AR000DQ20S
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, PropertyAnimationTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest PropertyAnimationTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto height = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_HEIGHT, height);
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    auto box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_NEAR(box->GetHeight(), 3.0f, DBL_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(box->GetHeight(), 5.0f, DBL_EPSILON);
}

/**
 * @tc.name: PropertyAnimationTest002
 * @tc.desc: verify color property animation
 * @tc.type: FUNC
 * @tc.require: AR000DQ20S
 * @tc.author: jiangdayuan
 */
HWTEST_F(TweenElementTest, PropertyAnimationTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest PropertyAnimationTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto color = AceType::MakeRefPtr<CurveAnimation<Color>>(Color::WHITE, Color::BLACK, Curves::LINEAR);
        color->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
        tweenOption.SetColorAnimation(color);
        tweenOption.SetDuration(20);
        tweenOption.SetFillMode(FillMode::FORWARDS);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    auto box = AceType::DynamicCast<RenderBox>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_EQ(box->GetColor(), Color::WHITE);

    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_EQ(box->GetColor(), Color::BLACK);
}

/**
 * @tc.name: TweenElementReplayTest001
 * @tc.desc: replay when previous is done.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, ReplayTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest ReplayTest001";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto width = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_WIDTH, width);
        tweenOption.SetDuration(20);
        tweenComponent->SetTweenOption(tweenOption);
        tweenComponent->SetTweenOperation(TweenOperation::PLAY);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    auto box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_NEAR(box->GetWidth(), 3.0, DBL_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(box->GetWidth(), TEST_SURFACE_WIDTH, DBL_EPSILON);

    /**
     * @tc.steps: step3. update it again to make it replay, and check
     * @tc.expected: step3. check the final value
     */
    tweenComponent_->SetTweenOperation(TweenOperation::PLAY);
    context_->ScheduleUpdate(tweenComponent_);
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_NEAR(box->GetWidth(), 3.0, DBL_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(box->GetWidth(), TEST_SURFACE_WIDTH, DBL_EPSILON);
}

/**
 * @tc.name: TweenElementReplayTest002
 * @tc.desc: replay when previous is playing.
 * @tc.type: FUNC
 * @tc.require: AR000DBULF
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, ReplayTest002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElementTest ReplayTest002";
    /**
     * @tc.steps: step1. init tween option and build tween component
     */
    g_configTweenComponent = [](const RefPtr<TweenComponent>& tweenComponent) {
        TweenOption tweenOption;
        auto width = AceType::MakeRefPtr<CurveAnimation<float>>(1.0f, 5.0f, Curves::LINEAR);
        tweenOption.SetPropertyAnimationFloat(PropertyAnimatableType::PROPERTY_WIDTH, width);
        tweenOption.SetDuration(20);
        tweenComponent->SetTweenOption(tweenOption);
    };
    CreateAndBuildTweenComponent();

    /**
     * @tc.steps: step2. trigger frames to let animation done
     * @tc.expected: step2. check the final value
     */
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    auto box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_NEAR(box->GetWidth(), 3.0, DBL_EPSILON);

    /**
     * @tc.steps: step3. make it replay before previous is done. and check
     * @tc.expected: step3. check the final value
     */
    tweenComponent_->SetTweenOperation(TweenOperation::PLAY);
    context_->ScheduleUpdate(tweenComponent_);
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    platformWindowRaw_->TriggerOneFrame();
    box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_TRUE(box);
    EXPECT_NEAR(box->GetWidth(), 3.0, DBL_EPSILON);
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(box->GetWidth(), TEST_SURFACE_WIDTH, DBL_EPSILON);
}

/**
 * @tc.name: TweenElementTimerUpdateTest001
 * @tc.desc: update element when times up.
 * @tc.type: FUNC
 * @tc.require: AR000DSB2A
 * @tc.author: zhouzebin
 */
HWTEST_F(TweenElementTest, TweenElementTimerUpdateTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "TweenElement TimerUpdateTest001";
    /**
     * @tc.steps: step1. build tween component
     */
    CreateAndBuildTweenComponent();
    platformWindowRaw_->TriggerOneFrame();
    /**
     * @tc.steps: step2. update box's width and trigger update
     * @tc.expected: step2. check the width updated
     */
    boxComponent_->SetWidth(5.0);
    context_->ScheduleUpdate(tweenComponent_);
    platformWindowRaw_->TriggerOneFrame();
    auto box = AceType::DynamicCast<RenderBoxBase>(tweenElement_->GetContentRender());
    EXPECT_NEAR(box->GetWidth(), 5.0, DBL_EPSILON);

    /**
     * @tc.steps: step3. update box's width and trigger update again
     * @tc.expected: step3. check the width updated
     */
    boxComponent_->SetWidth(15.0);
    context_->ScheduleUpdate(tweenComponent_);
    platformWindowRaw_->TriggerOneFrame();
    EXPECT_NEAR(box->GetWidth(), 15.0, DBL_EPSILON);
}

} // namespace OHOS::Ace

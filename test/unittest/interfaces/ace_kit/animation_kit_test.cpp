/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/animation/animation_utils.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class AnimationKitTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: StartAnimation_ShouldReturnAnimation_WhenOptionIsValid
 * @tc.desc: Test StartAnimation function when option is valid
 * @tc.type: Func
 */
HWTEST_F(AnimationKitTest, AnimationKitTest001, TestSize.Level1)
{
    AnimationOption option;
    Kit::AnimationCallback callback = []() { return; };
    Kit::AnimationCallback finishCallback = []() { return; };
    Kit::AnimationCallback repeatCallback = []() { return; };
    bool flushUITasks = true;

    auto animation = Kit::AnimationUtils::StartAnimation(option,
        callback, finishCallback, repeatCallback, flushUITasks);
    EXPECT_NE(animation, nullptr);
}

/**
 * @tc.name: StartAnimation_ShouldReturnNull_WhenOptionIsValid
 * @tc.desc: Test StartAnimation function when option is valid
 * @tc.type: Func
 */
HWTEST_F(AnimationKitTest, AnimationKitTest002, TestSize.Level1)
{
    AnimationOption option;
    Kit::AnimationCallback callback = []() { return; };
    Kit::AnimationCallback finishCallback = []() { return; };
    Kit::AnimationCallback repeatCallback = []() { return; };
    bool flushUITasks = false;

    auto animation = Kit::AnimationUtils::StartAnimation(option,
        callback, finishCallback, repeatCallback, flushUITasks);
    EXPECT_NE(animation, nullptr);
}

/**
 * @tc.name: StartAnimation_ShouldStopAnimation_WhenAnimationIsNotNull
 * @tc.desc: Test StopAnimation method when animation is not null
 * @tc.type: FUNC
 */
HWTEST_F(AnimationKitTest, AnimationKitTest003, TestSize.Level1)
{
    AnimationOption option;
    Kit::AnimationCallback callback = []() { return; };
    Kit::AnimationCallback finishCallback = []() { return; };
    Kit::AnimationCallback repeatCallback = []() { return; };
    bool flushUITasks = true;

    auto animation = Kit::AnimationUtils::StartAnimation(option,
        callback, finishCallback, repeatCallback, flushUITasks);

    Kit::AnimationUtils::StopAnimation(animation);
    EXPECT_NE(animation, nullptr);
}
} // namespace OHOS::Ace

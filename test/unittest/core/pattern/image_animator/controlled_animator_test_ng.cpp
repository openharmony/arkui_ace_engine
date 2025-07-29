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
#include "test/unittest/core/pattern/test_ng.h"
#include "ui/base/ace_type.h"

#include "core/components_ng/pattern/image_animator/controlled_animator.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ControlledAnimatorTestNg : public TestNG {
public:
    void SetUp() override {};
    void TearDown() override {};
};

/**
 * @tc.name: SetIteration001
 * @tc.desc: test SetIteration.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, SetIteration001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    int32_t iteration = 2;
    controlledAnimator->SetIteration(iteration);
    EXPECT_EQ(controlledAnimator->iteration_, 2);
}

/**
 * @tc.name: SetIteration002
 * @tc.desc: test SetIteration.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, SetIteration002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t iteration = 1;
    controlledAnimator->SetIteration(iteration);
    EXPECT_EQ(controlledAnimator->iteration_, 1);
}

/**
 * @tc.name: SetIteration003
 * @tc.desc: test iteration 2 for SetIteration to STOPPED
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, SetIteration003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t iteration = 2;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->SetIteration(iteration);
    EXPECT_EQ(controlledAnimator->controlStatus_, ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: SetIteration004
 * @tc.desc: test SetIteration.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, SetIteration004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t iteration = 2;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->stopEvent_ = []() {};
    controlledAnimator->SetIteration(iteration);
    EXPECT_EQ(controlledAnimator->controlStatus_, ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: PostPlayTask001
 * @tc.desc: test PostPlayTask.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, PostPlayTask001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t idx = 1;
    int32_t iteration = 2;
    int32_t idxOffset = 1;
    int32_t elapsedTime = 1;
    controlledAnimator->iteration_ = 1;
    controlledAnimator->PostPlayTask(idx, iteration, idxOffset, elapsedTime);
    EXPECT_NE(controlledAnimator->runningIdx_, idx);
}

/**
 * @tc.name: PostPlayTask002
 * @tc.desc: test PostPlayTask.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, PostPlayTask002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t idx = 1;
    int32_t iteration = 0;
    int32_t idxOffset = 1;
    int32_t elapsedTime = 1;
    controlledAnimator->iteration_ = 1;
    controlledAnimator->needFireRepeatEvent_ = false;

    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->PostPlayTask(idx, iteration, idxOffset, elapsedTime);
    EXPECT_EQ(controlledAnimator->runningIdx_, idx);
}

/**
 * @tc.name: PostPlayTask003
 * @tc.desc: test PostPlayTask.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, PostPlayTask003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t idx = 2;
    int32_t iteration = 0;
    int32_t idxOffset = 1;
    int32_t elapsedTime = 1;
    controlledAnimator->iteration_ = 1;
    controlledAnimator->needFireRepeatEvent_ = true;

    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->PostPlayTask(idx, iteration, idxOffset, elapsedTime);
    EXPECT_FALSE(controlledAnimator->needFireRepeatEvent_);
}

/**
 * @tc.name: PostPlayTask004
 * @tc.desc: test PostPlayTask.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, PostPlayTask004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    int32_t idx = 2;
    int32_t iteration = 0;
    int32_t idxOffset = 1;
    int32_t elapsedTime = 1;
    controlledAnimator->iteration_ = 1;
    controlledAnimator->needFireRepeatEvent_ = true;

    controlledAnimator->repeatEvent_ = []() {};
    controlledAnimator->innerRepeatEvent_ = []() {};

    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->PostPlayTask(idx, iteration, idxOffset, elapsedTime);
    EXPECT_FALSE(controlledAnimator->needFireRepeatEvent_);
}

/**
 * @tc.name: Forward001
 * @tc.desc: test Forward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Forward001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 1;

    controlledAnimator->Forward();
    EXPECT_FALSE(controlledAnimator->isReverse_);
}

/**
 * @tc.name: Forward002
 * @tc.desc: test Forward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Forward002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Forward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Forward003
 * @tc.desc: test Forward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Forward003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = false;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Forward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Forward004
 * @tc.desc: test Forward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Forward004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 0;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = false;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Forward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Forward005
 * @tc.desc: test Forward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Forward005, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 0;

    controlledAnimator->Forward();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: Backward001
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    controlledAnimator->isReverse_ = false;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 1;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->isReverse_);
}

/**
 * @tc.name: Backward002
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Backward003
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = false;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Backward004
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 0;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = false;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pictureInfos_.clear();
    controlledAnimator->duration_ = 1;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->isFirstRun_);
}

/**
 * @tc.name: Backward005
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward005, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 0;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: Backward005
 * @tc.desc: test Backward.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Backward006, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 1;
    controlledAnimator->isFirstRun_ = false;

    controlledAnimator->Backward();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::RUNNING);
}

/**
 * @tc.name: Cancel001
 * @tc.desc: test Cancel.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Cancel001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);

    controlledAnimator->Cancel();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::IDLE);
}

/**
 * @tc.name: Cancel002
 * @tc.desc: test Cancel.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Cancel002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 }, { 0.5f, 300 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->isReverse_ = true;

    controlledAnimator->cancelEvent_ = []() {};

    controlledAnimator->Cancel();
    EXPECT_EQ(controlledAnimator->runningIdx_, frames.size() - 1);
}

/**
 * @tc.name: Cancel003
 * @tc.desc: test Cancel.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Cancel003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    controlledAnimator->elapsedTime_ = 1;
    controlledAnimator->Cancel();
    EXPECT_NE(controlledAnimator->elapsedTime_, 0);
}

/**
 * @tc.name: Cancel004
 * @tc.desc: test Cancel.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Cancel004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::IDLE;
    controlledAnimator->elapsedTime_ = 1;
    controlledAnimator->Cancel();
    EXPECT_NE(controlledAnimator->elapsedTime_, 0);
}

/**
 * @tc.name: Cancel005
 * @tc.desc: test Cancel.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Cancel005, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 0;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::IDLE;
    controlledAnimator->elapsedTime_ = 1;
    controlledAnimator->Cancel();
    EXPECT_NE(controlledAnimator->elapsedTime_, 0);
}

/**
 * @tc.name: Pause001
 * @tc.desc: test Pause.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Pause001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);

    controlledAnimator->Pause();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::PAUSED);
}

/**
 * @tc.name: Pause002
 * @tc.desc: test Pause.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Pause002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->pauseEvent_ = []() {};

    controlledAnimator->Pause();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::PAUSED);
}

/**
 * @tc.name: Pause003
 * @tc.desc: test Pause.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Pause003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;

    controlledAnimator->isReverse_ = true;
    controlledAnimator->Pause();
    EXPECT_NE(controlledAnimator->elapsedTimeReversedStatus_, controlledAnimator->isReverse_);
}

/**
 * @tc.name: Pause004
 * @tc.desc: test Pause.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Pause004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;

    controlledAnimator->isReverse_ = true;
    controlledAnimator->Pause();
    EXPECT_NE(controlledAnimator->elapsedTimeReversedStatus_, controlledAnimator->isReverse_);
}

/**
 * @tc.name: Pause005
 * @tc.desc: test Pause.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Pause005, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 0;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::PAUSED;

    controlledAnimator->isReverse_ = true;
    controlledAnimator->Pause();
    EXPECT_NE(controlledAnimator->elapsedTimeReversedStatus_, controlledAnimator->isReverse_);
}

/**
 * @tc.name: CalFinishIdx001
 * @tc.desc: test CalFinishIdx.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, CalFinishIdx001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    bool checkWithFillMode = true;
    controlledAnimator->fillMode_ = FillMode::FORWARDS;
    controlledAnimator->isReverse_ = true;
    auto ret = controlledAnimator->CalFinishIdx(checkWithFillMode);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: CalFinishIdx002
 * @tc.desc: test CalFinishIdx.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, CalFinishIdx002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    bool checkWithFillMode = true;
    controlledAnimator->fillMode_ = FillMode::BOTH;
    controlledAnimator->isReverse_ = true;
    auto ret = controlledAnimator->CalFinishIdx(checkWithFillMode);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: CalFinishIdx003
 * @tc.desc: test CalFinishIdx.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, CalFinishIdx003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    bool checkWithFillMode = true;
    controlledAnimator->fillMode_ = FillMode::NONE;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    auto ret = controlledAnimator->CalFinishIdx(checkWithFillMode);
    EXPECT_EQ(ret, 1);
}

/**
 * @tc.name: CalFinishIdx004
 * @tc.desc: test CalFinishIdx.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, CalFinishIdx004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    bool checkWithFillMode = false;
    controlledAnimator->fillMode_ = FillMode::NONE;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    auto ret = controlledAnimator->CalFinishIdx(checkWithFillMode);
    EXPECT_EQ(ret, 1);
}

/**
 * @tc.name: MovePictureToRightPosition001
 * @tc.desc: test MovePictureToRightPosition.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, MovePictureToRightPosition001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->isReverse_ = true;
    controlledAnimator->MovePictureToRightPosition(false);
    EXPECT_EQ(controlledAnimator->runningIdx_, frames.size() - 1);
}

/**
 * @tc.name: MovePictureToRightPosition002
 * @tc.desc: test MovePictureToRightPosition.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, MovePictureToRightPosition002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    controlledAnimator->runningIdx_ = 1;
    controlledAnimator->isReverse_ = true;

    controlledAnimator->MovePictureToRightPosition(false);
    EXPECT_EQ(controlledAnimator->runningIdx_, frames.size() - 1);
}

/**
 * @tc.name: Finish001
 * @tc.desc: test Finish.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Finish001, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = true;
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 1;

    controlledAnimator->Finish();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::STOPPED);
}

/**
 * @tc.name: Finish002
 * @tc.desc: test Finish.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Finish002, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->needFireRepeatEvent_ = false;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;

    controlledAnimator->Finish();
    EXPECT_FALSE(controlledAnimator->needFireRepeatEvent_);
}

/**
 * @tc.name: Finish003
 * @tc.desc: test Finish.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Finish003, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->needFireRepeatEvent_ = false;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;

    controlledAnimator->Finish();
    EXPECT_FALSE(controlledAnimator->needFireRepeatEvent_);
}

/**
 * @tc.name: Finish004
 * @tc.desc: test Finish.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Finish004, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 0;
    controlledAnimator->needFireRepeatEvent_ = false;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::STOPPED;

    controlledAnimator->Finish();
    EXPECT_FALSE(controlledAnimator->needFireRepeatEvent_);
}

/**
 * @tc.name: Finish005
 * @tc.desc: test Finish.
 * @tc.type: FUNC
 */
HWTEST_F(ControlledAnimatorTestNg, Finish005, TestSize.Level1)
{
    auto controlledAnimator = AceType::MakeRefPtr<ControlledAnimator>();
    EXPECT_NE(controlledAnimator, nullptr);

    controlledAnimator->iteration_ = 1;
    controlledAnimator->controlStatus_ = ControlledAnimator::ControlStatus::RUNNING;
    controlledAnimator->isReverse_ = true;
    controlledAnimator->stopEvent_ = []() {};
    std::vector<PictureInfo> frames { { 0.5f, 100 }, { 0.5f, 200 } };
    controlledAnimator->AddInterpolator(frames);
    std::function<void(int32_t)> func = [](int32_t num) {};
    controlledAnimator->AddListener(func);
    controlledAnimator->duration_ = 1;

    controlledAnimator->Finish();
    EXPECT_TRUE(controlledAnimator->controlStatus_ == ControlledAnimator::ControlStatus::STOPPED);
}
} // namespace OHOS::Ace::NG
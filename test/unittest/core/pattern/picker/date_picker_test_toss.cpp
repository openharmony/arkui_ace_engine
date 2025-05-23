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

#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"

#define private public

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TestableTossAnimationController : public TossAnimationController {
public:
    void TestCreatePropertyCallback()
    {
        CreatePropertyCallback();
    }
};

class DummyDatePickerColumnPattern : public DatePickerColumnPattern {
public:
    DummyDatePickerColumnPattern()
        : touchBreakStatus_(false), mainVelocity_(0.f), offset_(0.f),
          tossStatus_(false), yOffset_(0.f) {}

    bool GetTouchBreakStatus() const { return touchBreakStatus_; }
    void SetTouchBreakStatus(bool status) { touchBreakStatus_ = status; }

    double GetMainVelocity() const { return mainVelocity_; }
    void SetMainVelocity(double velocity) { mainVelocity_ = velocity; }

    double GetOffset() const { return offset_; }
    void SetOffset(double offset) { offset_ = offset; }

    void SetTossStatus(bool status) { tossStatus_ = status; }
    bool GetTossStatus() const { return tossStatus_; }

    void SetYOffset(double offset) { yOffset_ = offset; }
    double GetYOffset() const { return yOffset_; }

private:
    bool touchBreakStatus_;
    double mainVelocity_;
    double offset_;
    bool tossStatus_;
    double yOffset_;
};

// Test fixture. Renamed to DatePickerTestThree to match the HWTEST_F macro.
class DatePickerTestToss : public testing::Test {
protected:
    void SetUp() override
    {
        column_ = AceType::MakeRefPtr<DummyDatePickerColumnPattern>();
        ASSERT_NE(column_, nullptr);
        controller_ = column_->GetToss();
        controller_->SetColumn(column_);
        ASSERT_NE(controller_, nullptr);
    }

    RefPtr<DummyDatePickerColumnPattern> column_;
    RefPtr<TossAnimationController> controller_;
};

/**
@tc.name: TossAnimationControllerSetStartTest
@tc.desc: Test SetStart method of TossAnimationController, ensuring yStart_ is set and yOffset remains unchanged.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerSetStartTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Verify that the controller is valid.
    @tc.steps: step2. Call SetStart and check that yStart_ is set to 100.f.
    @tc.steps: step3. Verify that Y offset remains unchanged.
    */
    ASSERT_NE(controller_, nullptr);
    controller_->SetStart(100.f);
    EXPECT_EQ(column_->GetYOffset(), 0.f);
    EXPECT_EQ(controller_->yStart_, 100.f);
}

/**
@tc.name: TossAnimationControllerSetEndTest
@tc.desc: Test SetEnd method of TossAnimationController ensuring yEnd_ is assigned.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerSetEndTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Verify that the controller is valid.
    @tc.steps: step2. Call SetEnd and check that yEnd_ is set to 200.f.
    */
    ASSERT_NE(controller_, nullptr);
    controller_->SetEnd(200.f);
    EXPECT_EQ(controller_->yEnd_, 200.f);
}

/**
@tc.name: TossAnimationControllerPlayValidVelocityTest
@tc.desc: Test Play method with a valid velocity for proper processing.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerPlayValidVelocityTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Set timeStart_ to 1.f and timeEnd_ to 4.f.
    @tc.steps: step2. Set a valid high velocity.
    @tc.steps: step3. Call Play and verify the speed is processed correctly.
    */
    ASSERT_NE(controller_, nullptr);
    controller_->timeEnd_ = 4.f;
    controller_->timeStart_ = 1.f;
    column_->SetMainVelocity(4500.f);
    controller_->SetColumn(column_);
    EXPECT_TRUE(controller_->Play());
    EXPECT_EQ(controller_->speed_, 4.5);
}

/**
@tc.name: TossAnimationControllerPlayInvalidVelocityTest
@tc.desc: Test Play method with an invalid velocity below threshold.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerPlayInvalidVelocityTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Verify both controller and column are valid.
    @tc.steps: step2. Set an invalid low velocity.
    @tc.steps: step3. Call Play and check that it returns false.
    */
    ASSERT_NE(controller_, nullptr);
    ASSERT_NE(column_, nullptr);
    column_->SetMainVelocity(200.f);
    EXPECT_FALSE(controller_->Play());
}

/**
@tc.name: TossAnimationControllerStartSpringMotionTest
@tc.desc: Test StartSpringMotion method updating toss status.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerStartSpringMotionTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Set a valid medium velocity.
    @tc.steps: step2. Invoke StartSpringMotion.
    @tc.steps: step3. Verify toss status is set appropriately.
    */
    ASSERT_NE(controller_, nullptr);
    ASSERT_NE(column_, nullptr);
    column_->SetMainVelocity(1500.f);
    controller_->StartSpringMotion();
    EXPECT_FALSE(column_->GetTossStatus());
}

/**
@tc.name: TossAnimationControllerUpdatePlayAnimationValueTest
@tc.desc: Test UpdatePlayAnimationValue with speed below and above VMAX.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerUpdatePlayAnimationValueTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Retrieve the tossAnimationController instance.
    @tc.steps: step2. Set speed to a value below VMAX and verify the curve and speed remain unchanged.
    @tc.steps: step3. Set speed above VMAX and confirm it is capped.
    */
    ASSERT_NE(column_, nullptr);
    auto ctrl = column_->tossAnimationController_;
    ASSERT_NE(ctrl, nullptr);

    ctrl->speed_ = 3.0;
    auto curve1 = ctrl->UpdatePlayAnimationValue();
    EXPECT_NE(curve1, nullptr);
    EXPECT_EQ(ctrl->speed_, 3.0);

    ctrl->speed_ = 6.0;
    auto curve2 = ctrl->UpdatePlayAnimationValue();
    EXPECT_NE(curve2, nullptr);
    EXPECT_EQ(ctrl->speed_, 5.0); // Speed capped at VMAX
}

/**
@tc.name: TossAnimationControllerGetCurrentTimeTest
@tc.desc: Test GetCurrentTime method ensuring time values are increasing.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerGetCurrentTimeTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Retrieve current time.
    @tc.steps: step2. Delay slightly and retrieve time again.
    @tc.steps: step3. Verify the second time is greater than the first.
    */
    ASSERT_NE(column_, nullptr);
    auto ctrl = column_->tossAnimationController_;
    ASSERT_NE(ctrl, nullptr);

    double time1 = ctrl->GetCurrentTime();
    EXPECT_GT(time1, 0.f);
    usleep(1000);
    double time2 = ctrl->GetCurrentTime();
    EXPECT_GT(time2, time1);
}

/**
@tc.name: TossAnimationControllerPlayEdgeCasesTest
@tc.desc: Test edge cases in Play method, including invalid time differences and very low velocity.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerPlayEdgeCasesTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Set an invalid time difference.
    @tc.steps: step2. Call Play and verify it fails.
    @tc.steps: step3. Set a very low velocity and check Play returns false.
    */
    ASSERT_NE(column_, nullptr);
    auto ctrl = column_->tossAnimationController_;
    ASSERT_NE(ctrl, nullptr);

    ctrl->timeEnd_ = ctrl->timeStart_;
    EXPECT_FALSE(ctrl->Play());

    column_->SetMainVelocity(100.f);
    EXPECT_FALSE(ctrl->Play());
}

/**
@tc.name: TossAnimationControllerStartSpringMotionNullTest
@tc.desc: Test StartSpringMotion method behavior when dependencies are null.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TossAnimationControllerStartSpringMotionNullTest, TestSize.Level1)
{
    /*
    @tc.steps: step1. Create a TossAnimationController with null column.
    @tc.steps: step2. Call StartSpringMotion and verify no crash occurs.
    @tc.steps: step3. Assign a valid column and call StartSpringMotion again.
    */
    auto ctrl = AceType::MakeRefPtr<TossAnimationController>();
    ctrl->StartSpringMotion();
    ctrl->SetColumn(column_);
    ctrl->StartSpringMotion();
}

} // namespace OHOS::Ace::NG
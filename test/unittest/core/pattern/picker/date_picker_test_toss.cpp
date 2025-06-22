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
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}

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
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    bool CompareOptionProperties(std::vector<PickerOptionProperty> option1, std::vector<PickerOptionProperty> option2)
    {
        int32_t size = option1.size();
        for (int32_t i = 0; i < size; i++) {
            if (option1[i].height != option2[i].height ||
                option1[i].fontheight != option2[i].fontheight ||
                option1[i].prevDistance != option2[i].prevDistance ||
                option1[i].nextDistance != option2[i].nextDistance) {
                return false;
            }
        }
        return true;
    }

protected:
    void SetUp() override
    {
        column_ = AceType::MakeRefPtr<DummyDatePickerColumnPattern>();
        ASSERT_NE(column_, nullptr);
        controller_ = column_->GetToss();
        controller_->SetColumn(column_);
        ASSERT_NE(controller_, nullptr);

        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            return GetTheme(type);
        });
        EXPECT_CALL(*themeManager, GetTheme(_, _))
            .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }

    void TearDown()
    {
        MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
        ViewStackProcessor::GetInstance()->ClearStack();
    }

    RefPtr<DummyDatePickerColumnPattern> column_;
    RefPtr<TossAnimationController> controller_;
};

void DatePickerTestToss::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestToss::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

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

/**
@tc.name: TestFlushCurrentOptionsNormalCase
@tc.desc: Test FlushCurrentOptions with normal parameters.
@tc.type: FUNC
*/
HWTEST_F(DatePickerTestToss, TestFlushCurrentOptionsNormalCase, TestSize.Level1)
{
    bool isDown = true;
    bool isUpateTextContentOnly = false;
    bool isUpdateAnimationProperties = true;
    bool isTossPlaying = false;
    /**
     * @tc.steps: step1. Create DatePicker and get columnPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(stackNode->GetChildAtIndex(1)->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    columnNode->MarkModifyDone();
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto initOptionProperties = columnPattern->optionProperties_;
    /*
    @tc.steps: step2. FlushCurrentOptions with parameters1.
    */
    columnPattern->FlushCurrentOptions(isDown, isUpateTextContentOnly, isUpdateAnimationProperties, isTossPlaying);
    auto optionProperties = columnPattern->optionProperties_;
    EXPECT_TRUE(CompareOptionProperties(initOptionProperties, optionProperties));

    /*
    @tc.steps: step3. FlushCurrentOptions with parameters2.
    */
    isDown = false;
    isUpateTextContentOnly = true;
    isUpdateAnimationProperties = false;
    isTossPlaying = true;
    columnPattern->FlushCurrentOptions(isDown, isUpateTextContentOnly, isUpdateAnimationProperties, isTossPlaying);
    optionProperties = columnPattern->optionProperties_;
    EXPECT_TRUE(CompareOptionProperties(initOptionProperties, optionProperties));

    /*
    @tc.steps: step4. FlushCurrentOptions with parameters3.
    */
    isDown = true;
    isUpateTextContentOnly = false;
    isUpdateAnimationProperties = false;
    isTossPlaying = false;
    columnPattern->FlushCurrentOptions(isDown, isUpateTextContentOnly, isUpdateAnimationProperties, isTossPlaying);
    optionProperties = columnPattern->optionProperties_;
    EXPECT_TRUE(CompareOptionProperties(initOptionProperties, optionProperties));
}

/**
 * @tc.name: DatePickerPatternDirty000
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestToss, DatePickerPatternDirty000, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto pickerProperty = columnNode->GetLayoutProperty<DataPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    DirtySwapConfig dirtySwapConfig;
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    /**
     * @tc.step: step2. call pattern's OnDirtyLayoutWrapperSwap method.
     * @tc.expected: the result of OnDirtyLayoutWrapperSwap is true.
     */
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = false;
    EXPECT_TRUE(pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    /**
     * @tc.step: step3. call pattern's OnDirtyLayoutWrapperSwap method.
     * @tc.expected: the result of OnDirtyLayoutWrapperSwap is false.
     */
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = true;
    EXPECT_FALSE(pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
}

/**
 * @tc.name: GetDisappearTextStyle001
 * @tc.desc: Test DatePickerModelNG GetDisappearTextStyle by frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestToss, GetDisappearTextStyle001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create DatePicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.step: step2. call SetDisappearTextStyle & getDisappearTextStyle.
     * @tc.expected: the result of fontStyle & textColor is equal to preset value.
     */
    NG::PickerTextStyle textStyle;
    textStyle.fontStyle = Ace::FontStyle::ITALIC;
    textStyle.textColor = Color::WHITE;
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
    auto curTextStyle = DatePickerModelNG::getDisappearTextStyle(frameNode);
    EXPECT_EQ(curTextStyle.fontStyle.value(), Ace::FontStyle::ITALIC);
    EXPECT_EQ(curTextStyle.textColor.value(), Color::WHITE);
}
} // namespace OHOS::Ace::NG
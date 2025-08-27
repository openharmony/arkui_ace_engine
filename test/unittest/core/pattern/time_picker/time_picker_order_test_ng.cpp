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

#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const std::string TIME_AMPM = "01";
const std::string AMPM_TIME = "10";
const PickerTime TIME_PICKED = PickerTime(14, 9, 10);
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
} // namespace

class TimePickerOrderTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void VerifyTimeOrder(const std::vector<std::string>& columnName);

    RefPtr<FrameNode> columnNode_;
    RefPtr<TimePickerColumnPattern> columnPattern_;
    std::string oldLanguage_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void TimePickerOrderTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void TimePickerOrderTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void TimePickerOrderTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    oldLanguage_ = AceApplicationInfo::GetInstance().GetLanguage();
}

void TimePickerOrderTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    AceApplicationInfo::GetInstance().language_ = oldLanguage_;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerOrderTestNg::VerifyTimeOrder(const std::vector<std::string>& columnName)
{
    // Helper function to verify TimePicker columns order
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto host = timePickerRowPattern->GetHost();
    auto children = host->GetChildren();
    int32_t index = 0;
    int32_t tested = 0;
    for (const auto& child : children) {
        auto stackNode = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(stackNode, nullptr);
        auto columnBlendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
        ASSERT_NE(columnBlendNode, nullptr);
        auto childNode = AceType::DynamicCast<FrameNode>(columnBlendNode->GetLastChild());
        ASSERT_NE(childNode, nullptr);
        EXPECT_EQ(childNode, allChildNode[columnName[index]]);
        ++index;
        ++tested;
    }
    EXPECT_EQ(tested, columnName.size());
}

/**
 * @tc.name: TimePickerOrder001
 * @tc.desc: Test the node sequence when system language is zh and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder001, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to zh and create timepicker.
     */
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and minuteNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder002
 * @tc.desc: Test the node sequence when system language is en and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder002, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to en and create timepicker.
     */
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder003
 * @tc.desc: Test the node sequence when system language is ur and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder003, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ur and create timepicker.
     */
    const std::string language = "ur";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and minuteNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder004
 * @tc.desc: Test the node sequence when system language is bo and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder004, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to bo and create timepicker.
     */
    const std::string language = "bo";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and minuteNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder005
 * @tc.desc: Test the node sequence when system language is fa and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder005, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to fa and create timepicker.
     */
    const std::string language = "fa";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder006
 * @tc.desc: Test the node sequence when system language is iw and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder006, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to iw and create timepicker.
     */
    const std::string language = "iw";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder007
 * @tc.desc: Test the node sequence when system language is he and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder007, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to he and create timepicker.
     */
    const std::string language = "he";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder008
 * @tc.desc: Test the node sequence when system language is ar and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder008, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to he and create timepicker.
     */
    const std::string language = "ar";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder009
 * @tc.desc: Test the node sequence when system language is zh and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder009, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to zh and create timepicker.
     */
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder010
 * @tc.desc: Test the node sequence when system language is en and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder010, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to en and create timepicker.
     */
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder011
 * @tc.desc: Test the node sequence when system language is ur and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder011, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ur and create timepicker.
     */
    const std::string language = "ur";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder012
 * @tc.desc: Test the node sequence when system language is bo and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder012, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to bo and create timepicker.
     */
    const std::string language = "bo";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder013
 * @tc.desc: Test the node sequence when system language is ar and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder013, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ar and create timepicker.
     */
    const std::string language = "ar";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder014
 * @tc.desc: Test the node sequence when system language is fa and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder014, TestSize.Level1)
{
    /**
     * @tc.step: step1. change language to fa and create timepicker.
     */
    const std::string language = "fa";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder015
 * @tc.desc: Test the node sequence when system language is iw and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder015, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to iw and create timepicker.
     */
    const std::string language = "iw";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder016
 * @tc.desc: Test the node sequence when system language is he and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder016, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to he and create timepicker.
     */
    const std::string language = "he";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second", "amPm"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder017
 * @tc.desc: Test the node sequence when system language is ug and has second.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder017, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ug and create timepicker.
     */
    const std::string language = "ug";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->language_ = language;
    timePickerRowPattern->UpdateAllChildNode();

    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and hourNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "second", "minute", "hour"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder018
 * @tc.desc: Test the node sequence when system language is ug and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder018, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ug and create timepicker.
     */
    const std::string language = "ug";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->language_ = language;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and hourNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "minute", "hour"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder019
 * @tc.desc: Test callback when language changed from zh to en
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder019, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to zh and create timepicker.
     */
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->language_ = "en";
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: hourNode is the first, and amPmNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder020
 * @tc.desc: Test callback when language changed from en to zh
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder020, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to en and create timepicker.
     */
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->language_ = "zh";
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and minuteNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "hour", "minute"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder021
 * @tc.desc: Test callback when language changed from zh to ug
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder021, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to zh and create timepicker.
     */
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = false;
    timePickerRowPattern->UpdateNodePositionForUg();
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: amPmNode is the first, and hourNode is the last.
     */
    std::vector<std::string> columnOrder = {"amPm", "minute", "hour"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder022
 * @tc.desc: Test the node sequence when system language is zh and time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder022, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to zh and create timepicker.
     */
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: hourNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder023
 * @tc.desc: Test the node sequence when system language is en and time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder023, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to en and create timepicker.
     */
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and second is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder024
 * @tc.desc: Test the node sequence when system language is ur and time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder024, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to ur and create timepicker.
     */
    const std::string language = "ur";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: hourNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder025
 * @tc.desc: Test the node sequence when system language is bo and time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder025, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to bo and create timepicker.
     */
    const std::string language = "bo";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = AMPM_TIME;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: hourNode is the first, and secondNode is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder026
 * @tc.desc: Test the node sequence when system language is fa and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder026, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to fa and create timepicker.
     */
    const std::string language = "fa";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and second is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder027
 * @tc.desc: Test the node sequence when system language is iw and time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder027, TestSize.Level1)
{
    /**
     * @tc.step: step1. set language to iw and create timepicker.
     */
    const std::string language = "iw";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->amPmTimeOrder_ = TIME_AMPM;
    timePickerRowPattern->UpdateAllChildNode();
    
    /**
     * @tc.step: step2. Check if the dateTimeOrder of all child nodes is corrected.
     * @tc.expected: Hour is the first, and second is the last.
     */
    std::vector<std::string> columnOrder = {"hour", "minute", "second"};
    VerifyTimeOrder(columnOrder);
}

/**
 * @tc.name: TimePickerOrder028
 * @tc.desc: Test TimePicker OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder028, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Set the initial language and city.
    */
    AceApplicationInfo::GetInstance().SetLocale("ar", "Egypt", "Arabic", "");

    /**
    * @tc.steps: steps2. Create TimePicker.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);

    /**
     * @tc.steps: steps3. Switch language and city.
     */
    AceApplicationInfo::GetInstance().SetLocale("ug", "Kashgar", "Uyghur", "");

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::AUTO);
}

/**
 * @tc.name: TimePickerOrder029
 * @tc.desc: Test TimePickerDialog OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerOrderTestNg, TimePickerOrder029, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set the initial language and city.
     */
    AceApplicationInfo::GetInstance().SetLocale("ar", "Egypt", "Arabic", "");

    /**
     * @tc.steps: steps2. Create TimePickerDialog.
     */
    DialogProperties dialogProperties;
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo buttonInfo;
    buttonInfo.fontWeight = FontWeight::W400;
    buttonInfos.push_back(buttonInfo);

    std::map<std::string, PickerTime> timePickerProperty;
    uint32_t hour = 3;
    uint32_t minute = 4;
    uint32_t second = 1;
    timePickerProperty["selected"] = PickerTime(hour, minute, second);
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    ASSERT_NE(customNode, nullptr);
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    ASSERT_NE(timePickerNode, nullptr);
    auto pickerProperty = timePickerNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);

    /**
     * @tc.steps: steps3. Switch language and city.
     */
    AceApplicationInfo::GetInstance().SetLocale("ug", "Kashgar", "Uyghur", "");

    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::AUTO);
}

} // namespace OHOS::Ace::NG
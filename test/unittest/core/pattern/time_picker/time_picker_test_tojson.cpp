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

#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
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

namespace OHOS::Ace::NG {
namespace {
const int SHOW_COUNT = 7;
InspectorFilter filter;

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
class TimePickerTestToJson : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTimePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<TimePickerColumnPattern> columnPattern_;
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

void TimePickerTestToJson::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerTestToJson::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerTestToJson::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerTestToJson::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerTestToJson::CreateTimePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetShowCount(SHOW_COUNT);
    columnPattern_->OnAttachToFrameNode();
    auto host = timePickerRowPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: TimePickerPatternToJsonValue001
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerRowPatternToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */

    PickerTime startTime = PickerTime(0, 1, 1);
    PickerTime endTime = PickerTime(22, 58, 58);
    bool isEnableHaptic = true;
    timePickerRowPattern->SetStartTime(startTime);
    timePickerRowPattern->SetEndTime(endTime);
    timePickerRowPattern->SetIsEnableHaptic(isEnableHaptic);

    /**
     * @tc.steps: step2. call tojsonvalue funtion.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_TRUE(json->GetBool("enableHapticFeedback"));
}

/**
 * @tc.name: TimePickerPatternToJsonValue002
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerRowPatternToJsonValue002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */

    PickerTime startTime = PickerTime(0, 0, 0);
    PickerTime endTime = PickerTime(23, 59, 59);
    bool isEnableHaptic = true;

    /**
     * @tc.steps: step2. call tojsonvalue funtion and judge default value.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetBool("enableHapticFeedback"), isEnableHaptic);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue001
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    bool hasSecond = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutProperty = pickerProperty->Clone();
    pickerProperty->GetOrCreateDisappearTextStyle();
    pickerProperty->GetOrCreateTextStyle();
    pickerProperty->GetOrCreateSelectedTextStyle();
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);
    EXPECT_FALSE(pickerProperty->HasIsUseMilitaryTime());
    EXPECT_FALSE(pickerProperty->HasLoop());
    EXPECT_FALSE(pickerProperty->HasIsEnableCascade());

    /**
     * @tc.step: step2. call ToJsonValue() and check default value.
     */
    EXPECT_EQ(json->GetString("useMilitaryTime"), "false");
    EXPECT_EQ(json->GetString("loop"), "true");
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    ASSERT_EQ(disappearTextStyle->GetString("color"), "#FF000000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "0.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Normal");

    auto textStyle = json->GetObject("textStyle");
    ASSERT_NE(textStyle, nullptr);
    ASSERT_EQ(textStyle->GetString("color"), "#FF000000");
    auto normalFont = textStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "0.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Normal");

    auto selectTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectTextStyle, nullptr);
    ASSERT_EQ(selectTextStyle->GetString("color"), "#FF000000");
    auto selectFont = textStyle->GetObject("font");
    ASSERT_NE(selectFont, nullptr);
    EXPECT_EQ(selectFont->GetString("size"), "0.00px");
    EXPECT_EQ(selectFont->GetString("weight"), "FontWeight.Normal");

    auto options = json->GetObject("dateTimeOptions");
    EXPECT_EQ(options->GetString("hour"), "numeric");
    EXPECT_EQ(
        options->GetString("minute"), TimeFormat::GetMinuteFormat(pickerProperty->GetPrefixMinuteValue(0)).c_str());
    if (pickerProperty->GetPrefixSecondValue(0) != static_cast<int32_t>(ZeroPrefixType::OFF)) {
        EXPECT_EQ(
            options->GetString("second"), TimeFormat::GetSecondFormat(pickerProperty->GetPrefixSecondValue(0)).c_str());
    }
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue002
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();

    /**
     * @tc.steps: step1. update enableCascade value and call ToJsonValue.
     * @tc.expected: as follows
     */
    bool isEnableCascade = false;
    timePickerModeNG->SetEnableCascade(isEnableCascade);

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be defaultDate false.
     */
    EXPECT_EQ(json->GetBool("enableCascade"), isEnableCascade);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue003
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();

    /**
     * @tc.steps: step1. update useMilitaryTime value and call ToJsonValue.
     * @tc.expected: as follows
     */
    bool isUseMilitaryTime = true;
    timePickerModeNG->SetHour24(isUseMilitaryTime);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be defaultDate true.
     */
    EXPECT_EQ(json->GetString("useMilitaryTime"), "true");
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue004
 * @tc.desc: Test TimePickerLayoutProperty SetNormalTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     *  @tc.step: step2 Set PickerTextStyle and call ToJsonValue()
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetNormalTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     *  @tc.step: step3 check value of PickerTextStyle
     */
    auto normalTextStyle = json->GetObject("textStyle");
    ASSERT_NE(normalTextStyle, nullptr);
    EXPECT_EQ(normalTextStyle->GetString("color"), "#FFFF0000");
    auto normalFont = normalTextStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "10.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check selectedTextStyle
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetTextStyle(), nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue005
 * @tc.desc: Test TimePickerLayoutProperty SetSelectTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     *  @tc.step: step2 Set PickerTextStyle and call ToJsonValue()
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetSelectedTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     *  @tc.step: step3 check value of selectedTextStyle
     */
    auto selectedTextStyle = json->GetObject("selectedTextStyle");
    ASSERT_NE(selectedTextStyle, nullptr);
    EXPECT_EQ(selectedTextStyle->GetString("color"), "#FFFF0000");
    auto selectedFont = selectedTextStyle->GetObject("font");
    ASSERT_NE(selectedFont, nullptr);
    EXPECT_EQ(selectedFont->GetString("size"), "10.00px");
    EXPECT_EQ(selectedFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check selectedTextStyle
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetSelectedTextStyle(), nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue006
 * @tc.desc: Test TimePickerLayoutProperty SetDisappearTextStyle and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     *  @tc.step: step2 Set SetDisappearTextStyle and call ToJsonValue()
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    timePickerModeNG->SetDisappearTextStyle(theme, data);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     *  @tc.step: step3 check property of disappearTextStyle
     */
    auto disappearTextStyle = json->GetObject("disappearTextStyle");
    ASSERT_NE(disappearTextStyle, nullptr);
    EXPECT_EQ(disappearTextStyle->GetString("color"), "#FFFF0000");
    auto disappearFont = disappearTextStyle->GetObject("font");
    ASSERT_NE(disappearFont, nullptr);
    EXPECT_EQ(disappearFont->GetString("size"), "10.00px");
    EXPECT_EQ(disappearFont->GetString("weight"), "FontWeight.Bold");

    /**
     * @tc.cases: case. cover call reset() and check disappearTextStyle Property.
     */
    pickerProperty->Reset();
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);
    EXPECT_EQ(pickerProperty->GetDisappearTextStyle(), nullptr);
    EXPECT_FALSE(pickerProperty->HasLoop());
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue007
 * @tc.desc: Test TimePickerLayoutProperty dateTimeOptions and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    bool hasSecond = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     *  @tc.step: step2 Set dateTimeOptions and call ToJsonValue()
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    bool isUseMilitaryTime = true;
    pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
    ASSERT_NE(pickerProperty, nullptr);
    int32_t typeHour = static_cast<int32_t>(ZeroPrefixType::AUTO);
    int32_t typeMinute = static_cast<int32_t>(ZeroPrefixType::HIDE);
    int32_t typeSecond = static_cast<int32_t>(ZeroPrefixType::SHOW);
    pickerProperty->UpdatePrefixHour(typeHour);
    pickerProperty->UpdatePrefixMinute(typeMinute);
    pickerProperty->UpdatePrefixSecond(typeSecond);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.cases: case. cover call isUseMilitaryTime is true and check dateTimeOptions Property.
     */
    auto timeOption = json->GetObject("dateTimeOptions");
    ASSERT_NE(timeOption, nullptr);
    EXPECT_EQ(timeOption->GetString("hour"), TimeFormat::GetHourFormat(typeHour, isUseMilitaryTime));
    EXPECT_EQ(timeOption->GetString("minute"), TimeFormat::GetMinuteFormat(typeMinute));
    EXPECT_EQ(timeOption->GetString("second"), TimeFormat::GetSecondFormat(typeSecond));

    /**
     * @tc.cases: case. cover call isUseMilitaryTime is false and check dateTimeOptions Property.
     */
    isUseMilitaryTime = false;
    pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
    auto json2 = JsonUtil::Create(true);
    ASSERT_NE(json2, nullptr);
    pickerProperty->ToJsonValue(json2, filter);

    auto timeOption2 = json2->GetObject("dateTimeOptions");
    ASSERT_NE(timeOption2, nullptr);
    EXPECT_EQ(timeOption2->GetString("hour"), TimeFormat::GetHourFormat(typeHour, isUseMilitaryTime));
    EXPECT_EQ(timeOption2->GetString("minute"), TimeFormat::GetMinuteFormat(typeMinute));
    EXPECT_EQ(timeOption2->GetString("second"), TimeFormat::GetSecondFormat(typeSecond));
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue008
 * @tc.desc: Test TimePickerLayoutProperty dateTimeOptions and call ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerTestToJson, TimePickerLayoutPropertyToJsonValue008, TestSize.Level1)
{
    /**
     * @tc.step: step1. initialize LayoutProperty and TimePickerModelNG.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    bool hasSecond = true;
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, hasSecond);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto timePickerModeNG = TimePickerModelNG::GetInstance();
    ASSERT_NE(timePickerModeNG, nullptr);

    /**
     *  @tc.step: step2 Set dateTimeOptions exception value and call ToJsonValue()
     */
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    bool isUseMilitaryTime = true;
    pickerProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
    ASSERT_NE(pickerProperty, nullptr);
    const int32_t typeHour = 6; // is not ZeroPrefixType
    const int32_t typeMinute = 6;
    const int32_t typeSecond = 6;
    pickerProperty->UpdatePrefixHour(typeHour);
    pickerProperty->UpdatePrefixMinute(typeMinute);
    pickerProperty->UpdatePrefixSecond(typeSecond);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pickerProperty->ToJsonValue(json, filter);

    /**
     * @tc.cases: case. cover call isUseMilitaryTime is true and check dateTimeOptions Property.
     */
    auto timeOption = json->GetObject("dateTimeOptions");
    ASSERT_NE(timeOption, nullptr);
    EXPECT_EQ(timeOption->GetString("hour"), "");
    EXPECT_EQ(timeOption->GetString("minute"), "");
    EXPECT_EQ(timeOption->GetString("second"), "");
}

} // namespace OHOS::Ace::NG

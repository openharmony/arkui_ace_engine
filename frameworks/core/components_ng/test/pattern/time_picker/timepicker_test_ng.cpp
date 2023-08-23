/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"
#include "core/components_ng/test/mock/pattern/picker/mock_picker_theme_manager.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double TOSS_DELTA = 20.0;
const int CURRENT_VALUE1 = 3;
const int CURRENT_VALUE2 = 10;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 5;
const int DEFAULT_INDEX = -1;
const std::string AM = "上午";
const std::string PM = "下午";
const std::string COLON = ":";
const std::string ZERO = "0";
const PickerTime TIME_PICKED = PickerTime(14, 9, 10);
const int32_t AM_PM_PICKED = 1;
const int32_t HOUR_PICKED = 1;
const int32_t HOUR24_PICKED = 14;
const int32_t MINUTE_PICKED = 9;
const int32_t SECOND_PICKED = 10;
const uint32_t MINUTE_59 = 59;
const std::vector<int> DEFAULT_VALUE = { 0, 1, 2, 3, 4 };
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
const double OFFSET_DISTANCE = 10.0;
const int32_t DEFAULT_FINGER_ID = 1;
const uint32_t INVALID_SHOW_COUNT = 1;
const uint32_t INDEX = 5;
const double SCALE = 1.0;
const double DEFAULT_JUMP_INTERVAL = 2.0;
const int32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
const float TEXT_HOUR24_HEIGHT_NUMBER = 9.0f;
const float EXTRA_WIDTH = 50.0f;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
const uint32_t DEFAULT_YEAR = 1;
const uint32_t DEFAULT_MONTH = 2;
const uint32_t DEFAULT_DAY = 5;
constexpr uint32_t AM_PM_HOUR_12 = 12;
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double TIME_PLUS = 1 * 100.0;
const SizeF TEST_FRAME_SIZE { 20, 50 };
} // namespace
class TimePickerPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
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

void TimePickerPatternTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void TimePickerPatternTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void TimePickerPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockPickerThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPatternTestNg::TearDown()
{
    MockPipelineBase::GetCurrent()->themeManager_ = nullptr;
}

/**
 * @tc.name: TimePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test TimePickerRowPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGCreateTimePicker001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto timePickerPattern = AceType::MakeRefPtr<TimePickerRowPattern>();
    timePickerPattern->AttachToFrameNode(frameNode);
    timePickerPattern->OnAttachToFrameNode();
    auto host = timePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_TRUE(pickerProperty->HasDisappearColor());
    EXPECT_TRUE(pickerProperty->HasDisappearWeight());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle001
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
    EXPECT_TRUE(pickerProperty->HasColor());
    EXPECT_TRUE(pickerProperty->HasWeight());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle002
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle003
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_TRUE(pickerProperty->HasSelectedWeight());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: TimePickerColumnPattern001
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->FlushCurrentOptions(true, true);
    minuteColumnPattern->FlushCurrentOptions(false, true);
}

/**
 * @tc.name: TimePickerColumnPattern002
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->FlushCurrentOptions(true, true);
    SystemProperties::SetDeviceType(DeviceType::UNKNOWN);
}

/**
 * @tc.name: TimePickerColumnPattern003
 * @tc.desc: Test TimePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->FlushCurrentOptions(true, true);
    minuteColumnPattern->FlushCurrentOptions(false, true);
    minuteColumnPattern->UpdateToss(TOSS_DELTA);
}

/**
 * @tc.name: TimePickerColumnPattern004
 * @tc.desc: Test TimePickerColumnPattern UpdateToss.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->UpdateToss(TOSS_DELTA);
}

/**
 * @tc.name: TimePickerColumnPattern005
 * @tc.desc: Test TimePickerColumnPattern UpdateToss.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern005, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    PickerTextStyle data;
    data.fontSize = Dimension(10);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    minuteColumnPattern->UpdateToss(0 - TOSS_DELTA);
    minuteColumnPattern->TossStoped();
}

/**
 * @tc.name: TimePickerDialogViewShow001
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewShow001, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto dialogNode =
        TimePickerDialogView::Show(dialogProperties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyToJsonValue001
 * @tc.desc: Test TimePickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto disappearFont = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(disappearFont);
    EXPECT_NE(disappearFont, nullptr);
}

/**
 * @tc.name: TimePickerLayoutPropertyReset001
 * @tc.desc: Test TimePickerLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyReset001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->Reset();
}

/**
 * @tc.name: TimePickerLayoutPropertyClone001
 * @tc.desc: Test TimePickerLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyClone001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_NE(pickerProperty->Clone(), nullptr);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), static_cast<int32_t>(DEFAULT_VALUE.size()));

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), 0);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg003
 * @tc.desc: Test the Index properties of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetShowCount(SHOW_COUNT);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    EXPECT_EQ(accessibilityProperty->GetCurrentIndex(), CURRENT_VALUE1);

    auto itemCount = accessibilityProperty->GetCollectionItemCounts();
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(),
        (itemCount + CURRENT_VALUE1 - SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);
    EXPECT_EQ(
        accessibilityProperty->GetEndIndex(), (itemCount + CURRENT_VALUE1 + SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);

    minuteColumnPattern->SetShowCount(itemCount + itemCount);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), itemCount - 1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);

    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), DEFAULT_INDEX);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg004
 * @tc.desc: Test the Text property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = 0;
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), "");

    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "08:00:00");

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "");
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg005
 * @tc.desc: Test the SupportAction property of TimePickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg005, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0;
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg006
 * @tc.desc: Test the Text property for of TimePickerRowPattern if it is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg006, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(accessibilityProperty->GetText(),
        ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    EXPECT_EQ(
        accessibilityProperty->GetText(), std::to_string(CURRENT_VALUE2) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg007
 * @tc.desc: Test the Text property of TimePickerRowPattern if it is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAccessibilityPropertyTestNg007, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto amPmColumn = allChildNode["amPm"];
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerColumnPattern006
 * @tc.desc: Test mouse event callback and touch event callback
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern006, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto parentNode = minuteColumn->GetParent();
    ASSERT_NE(parentNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    parentNode->children_.emplace_front(buttonNode);

    minuteColumnPattern->hoverColor_ = Color::BLACK;
    minuteColumnPattern->pressColor_ = Color::BLUE;

    minuteColumnPattern->InitMouseAndPressEvent();
    (*minuteColumnPattern->mouseEvent_)(true);
    EXPECT_TRUE(minuteColumnPattern->hoverd_);
    auto renderContext = buttonNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    (*minuteColumnPattern->mouseEvent_)(false);
    EXPECT_FALSE(minuteColumnPattern->hoverd_);
    renderContext = buttonNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);

    TouchEventInfo touchEventInfo("default");
    TouchLocationInfo touchLocationInfoDown(DEFAULT_FINGER_ID);
    touchLocationInfoDown.SetTouchType(TouchType::DOWN);
    const Offset offSet(OFFSET_X, OFFSET_Y);
    touchLocationInfoDown.SetLocalLocation(offSet);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoDown));

    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLUE);
    EXPECT_EQ(minuteColumnPattern->GetLocalDownDistance(), OFFSET_DISTANCE);

    TouchLocationInfo touchLocationInfoUp(DEFAULT_FINGER_ID);
    touchLocationInfoUp.SetTouchType(TouchType::UP);
    touchLocationInfoUp.SetLocalLocation(offSet);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoUp));

    minuteColumnPattern->hoverd_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    EXPECT_EQ(minuteColumnPattern->GetLocalDownDistance(), 0.0f);

    minuteColumnPattern->hoverd_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);

    TouchLocationInfo touchLocationInfoMove(DEFAULT_FINGER_ID);
    touchLocationInfoMove.SetTouchType(TouchType::MOVE);
    touchLocationInfoMove.SetLocalLocation(offSet);
    touchEventInfo.touches_.clear();
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfoMove));

    minuteColumnPattern->hoverd_ = true;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::BLACK);
    minuteColumnPattern->hoverd_ = false;
    (*minuteColumnPattern->touchListener_)(touchEventInfo);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
}

/**
 * @tc.name: TimePickerColumnPattern007
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern007, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto* stack = ViewStackProcessor::GetInstance();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto weakNode = AceType::WeakClaim(AceType::RawPtr(buttonNode));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        weakNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig dirtySwapConfig;
    EXPECT_FALSE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    dirtySwapConfig.frameSizeChange = true;
    EXPECT_TRUE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig));
    EXPECT_FALSE(minuteColumnPattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig));
}

/**
 * @tc.name: TimePickerColumnPattern008
 * @tc.desc: Test FlushCurrentOptions and UpdateTextPropertiesLinear function while the amount of child nodes
 * not equal to showOptionCount
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern008, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->SetShowCount(INVALID_SHOW_COUNT);
    auto showOptionCount = minuteColumnPattern->GetShowCount();
    auto child = minuteColumn->GetChildren();
    EXPECT_NE(showOptionCount, child.size());
    minuteColumnPattern->FlushCurrentOptions();
    minuteColumnPattern->UpdateTextPropertiesLinear(true, SCALE);
}

/**
 * @tc.name: TimePickerColumnPattern009
 * @tc.desc: Test TextPropertiesLinearAnimation function while indexes greater than the amount of animation properties
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern009, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    EXPECT_GE(INDEX, minuteColumnPattern->animationProperties_.size());
    minuteColumnPattern->TextPropertiesLinearAnimation(
        AceType::MakeRefPtr<TextLayoutProperty>(), INDEX, SHOW_COUNT, true, SCALE);
}

/**
 * @tc.name: TimePickerColumnPattern010
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern010, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    minuteColumnPattern->InitPanEvent(gestureHub);
    auto panEvent = minuteColumnPattern->panEvent_;

    // action start
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->GetToss()->yStart_, OFFSET_Y);
    EXPECT_EQ(minuteColumnPattern->yOffset_, OFFSET_Y);
    EXPECT_EQ(minuteColumnPattern->yLast_, OFFSET_Y);
    EXPECT_TRUE(minuteColumnPattern->pressed_);

    // action update
    auto options = minuteColumnPattern->GetOptions();
    auto totalOptionCount = options[minuteColumn];

    gestureEvent.SetInputEventType(InputEventType::AXIS);
    gestureEvent.SetSourceTool(SourceTool::MOUSE);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = minuteColumnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    auto currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + 1) % totalOptionCount);

    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = minuteColumnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + totalOptionCount - 1) % totalOptionCount);

    point.SetY(OFFSET_Y + 2);
    gestureEvent.SetGlobalPoint(point);
    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    minuteColumnPattern->SetCurrentIndex(totalOptionCount);
    minuteColumnPattern->SetShowCount(totalOptionCount * 2);
    panEvent->actionUpdate_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->GetToss()->yEnd_, OFFSET_Y + 2);
    EXPECT_FALSE(minuteColumnPattern->CanMove(true));

    minuteColumnPattern->SetCurrentIndex(totalOptionCount - 1);
    panEvent->actionUpdate_(gestureEvent);

    // action end
    minuteColumnPattern->scrollDelta_ = TOSS_DELTA;
    minuteColumnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(minuteColumnPattern->pressed_);
    EXPECT_EQ(minuteColumnPattern->yOffset_, 0.0);
    EXPECT_EQ(minuteColumnPattern->yLast_, 0.0);
    EXPECT_EQ(minuteColumnPattern->scrollDelta_, 0.0);

    minuteColumnPattern->scrollDelta_ = TOSS_DELTA;
    minuteColumnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    minuteColumnPattern->pressed_ = true;
    minuteColumnPattern->yOffset_ = OFFSET_Y;
    minuteColumnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_EQ(minuteColumnPattern->yOffset_, OFFSET_Y);
    EXPECT_EQ(minuteColumnPattern->yLast_, OFFSET_Y);
    EXPECT_TRUE(minuteColumnPattern->pressed_);

    // action cancel
    minuteColumnPattern->animationCreated_ = false;
    panEvent->actionCancel_();
    EXPECT_FALSE(minuteColumnPattern->pressed_);
    EXPECT_EQ(minuteColumnPattern->yOffset_, 0.0);
    EXPECT_EQ(minuteColumnPattern->yLast_, 0.0);
    EXPECT_EQ(minuteColumnPattern->scrollDelta_, 0.0);

    // action end for OnAccessibilityEvent
    minuteColumnPattern->SetShowCount(0);
    EXPECT_FALSE(minuteColumnPattern->NotLoopOptions());
    auto toss = minuteColumnPattern->GetToss();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    EXPECT_TRUE(toss->Play());
    gestureEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(minuteColumnPattern->pressed_);
}

/**
 * @tc.name: TimePickerColumnPattern011
 * @tc.desc: Test toController stopListener
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern011, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto options = minuteColumnPattern->GetOptions();
    auto totalOptionCount = options[minuteColumn];

    minuteColumnPattern->CreateAnimation();
    EXPECT_EQ(minuteColumnPattern->toController_->stopCallbacks_.size(), 1);
    minuteColumnPattern->scrollDelta_ = 0;
    minuteColumnPattern->toController_->NotifyStopListener();

    minuteColumnPattern->scrollDelta_ = TOSS_DELTA;
    auto preIndex = minuteColumnPattern->GetCurrentIndex();
    minuteColumnPattern->toController_->NotifyStopListener();
    auto currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + totalOptionCount - 1) % totalOptionCount);

    minuteColumnPattern->scrollDelta_ = -TOSS_DELTA;
    preIndex = minuteColumnPattern->GetCurrentIndex();
    minuteColumnPattern->toController_->NotifyStopListener();
    currentIndex = minuteColumnPattern->GetCurrentIndex();
    EXPECT_EQ(currentIndex, (preIndex + 1) % totalOptionCount);
}

/**
 * @tc.name: TimePickerColumnPattern012
 * @tc.desc: Test ScrollOption function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern012, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->jumpInterval_ = 0;
    minuteColumnPattern->ScrollOption(TOSS_DELTA);

    auto child = minuteColumn->GetChildren();
    auto iter = child.begin();
    auto textNode = AceType::DynamicCast<FrameNode>(*iter);
    ASSERT_TRUE(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_TRUE(textPattern);
    RefPtr<TextLayoutProperty> textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_TRUE(textLayoutProperty);

    minuteColumnPattern->jumpInterval_ = DEFAULT_JUMP_INTERVAL;
    minuteColumnPattern->ScrollOption(TOSS_DELTA);
    double scale = fabs(TOSS_DELTA) / (DEFAULT_JUMP_INTERVAL * 2);
    uint32_t showCount = minuteColumnPattern->GetShowCount();
    for (uint32_t index = 0; index < showCount; index++) {
        Dimension startFontSize = minuteColumnPattern->animationProperties_[index].fontSize;
        Dimension endFontSize = minuteColumnPattern->animationProperties_[index].downFontSize;
        Dimension updatedFontSize = textLayoutProperty->GetFontSizeValue(startFontSize);
        EXPECT_EQ(startFontSize + (endFontSize - startFontSize) * scale, updatedFontSize);
    }
}

/**
 * @tc.name: TimePickerColumnPattern013
 * @tc.desc: Test SetDividerHeight function
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern013, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto gradientHeight = theme->GetGradientHeight().Value();
    auto dividerSpacing = theme->GetDividerSpacing().Value();

    minuteColumnPattern->SetDividerHeight(OPTION_COUNT_PHONE_LANDSCAPE + 1);
    EXPECT_EQ(minuteColumnPattern->gradientHeight_, gradientHeight * TEXT_HEIGHT_NUMBER);
    EXPECT_EQ(
        minuteColumnPattern->dividerHeight_, minuteColumnPattern->gradientHeight_ + gradientHeight + dividerSpacing);
    EXPECT_EQ(minuteColumnPattern->dividerSpacingWidth_, dividerSpacing * TEXT_WEIGHT_NUMBER);

    minuteColumn->children_.pop_back();
    minuteColumn->children_.pop_back();
    minuteColumnPattern->SetDividerHeight(OPTION_COUNT_PHONE_LANDSCAPE + 1);
    EXPECT_EQ(minuteColumnPattern->gradientHeight_, gradientHeight - TEXT_HOUR24_HEIGHT_NUMBER);

    minuteColumnPattern->SetDividerHeight(OPTION_COUNT_PHONE_LANDSCAPE);
    EXPECT_EQ(minuteColumnPattern->gradientHeight_, gradientHeight - TEXT_HOUR24_HEIGHT_NUMBER);
}

/**
 * @tc.name: TimePickerColumnPattern014
 * @tc.desc: Test UpdateColumnChildPosition function abnormal situation
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern014, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->yOffset_ = OFFSET_Y;
    auto options = minuteColumnPattern->GetOptions();
    int totalOptionCount = static_cast<int>(options[minuteColumn]);
    minuteColumnPattern->SetCurrentIndex(totalOptionCount);
    minuteColumnPattern->SetShowCount(totalOptionCount * 2);
    minuteColumnPattern->UpdateColumnChildPosition(OFFSET_X);
    EXPECT_FALSE(minuteColumnPattern->CanMove(true));

    minuteColumnPattern->SetCurrentIndex(totalOptionCount - 2);
    minuteColumnPattern->UpdateColumnChildPosition(OFFSET_X);
    EXPECT_EQ(minuteColumnPattern->scrollDelta_, OFFSET_X - OFFSET_Y);
}

/**
 * @tc.name: TimePickerColumnPattern015
 * @tc.desc: Test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPattern015, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    minuteColumnPattern->InitOnKeyEvent(focusHub);

    KeyEvent keyEvent(KeyCode::KEY_DPAD_UP, KeyAction::UP);
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));
}

/**
 * @tc.name: TimePickerRowPattern001
 * @tc.desc: Test TimePickerRowPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig config;
    config.frameSizeChange = true;
    EXPECT_TRUE(timePickerRowPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    auto children = frameNode->GetChildren();
    auto height = theme->GetDividerSpacing();
    auto width = frameNode->GetGeometryNode()->GetFrameSize().Width() / static_cast<float>(children.size());
    auto defaultWidth = height.ConvertToPx() * 2;
    EXPECT_GT(width, defaultWidth);

    for (const auto& child : children) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        EXPECT_EQ(buttonLayoutProperty->GetMeasureType(), MeasureType::MATCH_PARENT_MAIN_AXIS);
        EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), ButtonType::NORMAL);
        auto calcSize = buttonLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value();
        EXPECT_EQ(calcSize.Width().value(), CalcLength(defaultWidth - PRESS_INTERVAL.ConvertToPx()));
        EXPECT_EQ(calcSize.Height().value(), CalcLength(height - PRESS_INTERVAL));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        EXPECT_EQ(buttonConfirmRenderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
    }
}

/**
 * @tc.name: TimePickerRowPattern002
 * @tc.desc: Test TimePickerRowPattern OnModifyDone while HasTitleNode
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    timePickerRowPattern->titleId_ = titleNodeId;
    auto* stack = ViewStackProcessor::GetInstance();
    auto textFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(textFrameNode);
    PickerDate pickerDate(DEFAULT_YEAR, DEFAULT_MONTH, DEFAULT_DAY);
    timePickerRowPattern->SetDialogTitleDate(pickerDate);

    timePickerRowPattern->OnModifyDone();
    auto textTitleNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
}

/**
 * @tc.name: TimePickerRowPattern003
 * @tc.desc: Test TimePickerRowPattern CreateAmPmNode while AmPmButtonIdeaSize > 0
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        buttonNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    }
    timePickerRowPattern->SetHour24(false);
    std::optional<int32_t> amPmId;
    timePickerRowPattern->amPmId_ = amPmId;

    timePickerRowPattern->CreateAmPmNode();
    EXPECT_GT(timePickerRowPattern->SetAmPmButtonIdeaSize(), 0);
}

/**
 * @tc.name: TimePickerRowPattern004
 * @tc.desc: Test TimePickerRowPattern GetCurrentTime using 12-hour system
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPmColumn = allChildNode["amPm"];
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmPickerColumnPattern, nullptr);
    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourPickerColumnPattern, nullptr);
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minutePickerColumnPattern, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), 0);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetMinute(), minutePickerColumnPattern->GetCurrentIndex());

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 2);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 - 1);

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 * 2 - 1);

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern005
 * @tc.desc: Test TimePickerRowPattern HandleColumnChange
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern005, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPmColumn = allChildNode["amPm"];
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmPickerColumnPattern, nullptr);
    amPmPickerColumnPattern->SetCurrentIndex(0);
    auto tag = allChildNode["hour"];
    ASSERT_NE(tag, nullptr);
    timePickerRowPattern->HandleColumnChange(tag, true, 11, true);
    std::vector<RefPtr<FrameNode>> tags;
    timePickerRowPattern->OnDataLinking(tag, true, 11, tags);
    EXPECT_EQ(tags.size(), 1);
}

/**
 * @tc.name: TimePickerRowPattern006
 * @tc.desc: Test TimePickerRowPattern HandleHourColumnBuilding while AM PM column is null
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern006, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    frameNode->GetChildren().front()->children_.clear();
    timePickerRowPattern->HandleHourColumnBuilding();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(allChildNode["amPm"], nullptr);
}

/**
 * @tc.name: TimePickerRowPattern007
 * @tc.desc: Test TimePickerRowPattern GetAllChildNode while using 24-hour system but has 3 child node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern007, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
    timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(frameNode->children_.size(), CHILD_WITH_AMPM_SIZE);
    EXPECT_TRUE(timePickerRowPattern->amPmId_.has_value());
}

/**
 * @tc.name: TimePickerRowPattern008
 * @tc.desc: Test TimePickerRowPattern HandleHour12Change
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern008, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::vector<RefPtr<FrameNode>> tags;
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPm = allChildNode["amPm"];
    ASSERT_NE(amPm, nullptr);
    auto amPmPickerColumnPattern = amPm->GetPattern<TimePickerColumnPattern>();

    amPmPickerColumnPattern->SetCurrentIndex(0);
    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 1);

    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 2);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 3);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 4);
}

/**
 * @tc.name: TimePickerRowPattern009
 * @tc.desc: Test TimePickerRowPattern GetAmPmHour
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern009, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(0), AM_PM_HOUR_12);
    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(AM_PM_HOUR_12), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern010
 * @tc.desc: Test TimePickerRowPattern GetAmPmFormatString and AddZeroPrefix
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern010, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->vecAmPm_.emplace_back("AM");
    timePickerRowPattern->vecAmPm_.emplace_back("PM");
    EXPECT_EQ(timePickerRowPattern->GetAmFormatString(), "AM");
    EXPECT_EQ(timePickerRowPattern->GetPmFormatString(), "PM");
    EXPECT_EQ(timePickerRowPattern->AddZeroPrefix("5"), "05");
}

/**
 * @tc.name: TimePickerRowPattern011
 * @tc.desc: Test TimePickerRowPattern InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern011, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    timePickerRowPattern->InitOnKeyEvent(focusHub);
    auto getInnerFocusRectFunc = focusHub->getInnerFocusRectFunc_;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UNKNOWN;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    keyEvent.action = KeyAction::DOWN;
    auto stackChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(timePickerRowPattern->focusKeyID_));
    ASSERT_NE(stackChild, nullptr);
    auto pickerChild = AceType::DynamicCast<FrameNode>(stackChild->GetLastChild());
    ASSERT_NE(pickerChild, nullptr);
    auto pattern = pickerChild->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(pattern, nullptr);
    timePickerRowPattern->options_[pickerChild].clear();
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    timePickerRowPattern->options_[pickerChild][0] = "AM";
    timePickerRowPattern->options_[pickerChild][1] = "PM";
    auto currentIndex = pattern->GetCurrentIndex();
    auto totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex - 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex + 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    keyEvent.code = KeyCode::KEY_MOVE_END;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount - 1));

    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 1);

    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 0);

    auto frameWidth = frameNode->GetGeometryNode()->GetFrameSize().Width();
    auto childSize = frameNode->GetChildren().size();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->dividerSpacing_ = Dimension(OFFSET_X);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    auto dividerSpacing = pickerTheme->GetDividerSpacing().ConvertToPx();
    auto pickerThemeWidth = dividerSpacing * 2;
    auto centerY =
        (frameNode->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / 2 + PRESS_INTERVAL.ConvertToPx();
    // default focusWidth < columnWidth, focusWidth = columnWidth
    RoundRect paintRect;
    getInnerFocusRectFunc(paintRect);
    auto rect = paintRect.GetRect();
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.GetY(), centerY);
    EXPECT_EQ(rect.Width(), pickerChild->GetGeometryNode()->GetFrameSize().Width());
    EXPECT_EQ(rect.Height(), dividerSpacing - PRESS_INTERVAL.ConvertToPx() * 2);

    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    // default focusWidth < columnWidth
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    RoundRect paintRect2;
    timePickerRowPattern->GetInnerFocusPaintRect(paintRect2);
    auto rect2 = paintRect2.GetRect();
    auto centerX = (frameWidth / childSize - pickerThemeWidth) / 2 +
                   pickerChild->GetGeometryNode()->GetFrameRect().Width() * timePickerRowPattern->focusKeyID_ +
                   PRESS_INTERVAL.ConvertToPx() * 2;
    EXPECT_EQ(rect2.GetX(), centerX);
    EXPECT_EQ(rect2.Width(), (dividerSpacing - PRESS_INTERVAL.ConvertToPx()) * 2);
}

/**
 * @tc.name: TimePickerRowPattern012
 * @tc.desc: Test TimePickerRowPattern OnKeyEvent and HandleDirectionKey false
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern012, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(timePickerRowPattern->OnKeyEvent(keyEvent));
    EXPECT_FALSE(timePickerRowPattern->HandleDirectionKey(KeyCode::KEY_DPAD_CENTER));
}

/**
 * @tc.name: TimePickerRowPattern013
 * @tc.desc: Test TimePickerRowPattern SetFocusDisable and SetFocusEnable
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPattern013, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto host = timePickerRowPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    timePickerRowPattern->SetFocusDisable();
    timePickerRowPattern->SetFocusEnable();
}

/**
 * @tc.name: TimePickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerFireChangeEventTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto changeEvent = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    TimePickerModelNG::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->FireChangeEvent(true);
}

/**
 * @tc.name: TimePickerHasSecond001
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR24_PICKED);

    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"];
    ASSERT_NE(secondColumn, nullptr);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(secondColumnPattern, nullptr);
    EXPECT_EQ(secondColumnPattern->GetCurrentIndex(), SECOND_PICKED);
}

/**
 * @tc.name: TimePickerHasSecond002
 * @tc.desc: Test TimePickerRowPattern SetHasSecond false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto amPmColumn = allChildNode["amPm"];
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmColumnPattern, nullptr);
    EXPECT_EQ(amPmColumnPattern->GetCurrentIndex(), AM_PM_PICKED);

    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR_PICKED);

    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"];
    ASSERT_EQ(secondColumn, nullptr);
}

/**
 * @tc.name: TimePickerHasSecond003
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true first then false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.steps: step1. create FrameNode and SetHasSecond(true).
     */
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    /**
     * @tc.steps: step2. check the secondColumn has been created.
     */
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto secondColumn = allChildNode["second"];
    ASSERT_NE(secondColumn, nullptr);
    /**
     * @tc.steps: step3. SetHasSecond(false) then check the secondColumn has been deleted.
     */
    timePickerRowPattern->SetHasSecond(false);
    frameNode->MarkModifyDone();
    allChildNode = timePickerRowPattern->GetAllChildNode();
    secondColumn = allChildNode["second"];
    ASSERT_EQ(secondColumn, nullptr);
}

/**
 * @tc.name: TimePickerWheelMode001
 * @tc.desc: Test TimePickerRowPattern SetWheelModeEnabled false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetWheelModeEnabled(), false);
}

/**
 * @tc.name: TimePickerWheelMode002
 * @tc.desc: Test TimePickerRowPattern default wheelmode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"];
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetWheelModeEnabled(), true);
}

/**
 * @tc.name: TimePickerWheelMode003
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode off.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: TimePickerWheelMode004
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode on.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_59);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TimePicker accessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create timePicker and initialize related properties.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);

    /**
     * @tc.steps: step2. Get timePickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get timePickerColumn accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When timePickerColumn can move, call the callback function in timePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When timePickerColumn can not move, call the callback function in timePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = INDEX;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetCurrentIndex(1);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: TimePickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    auto frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE);
}
} // namespace OHOS::Ace::NG

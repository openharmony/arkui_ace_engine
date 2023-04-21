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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
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
const std::string AM = "上午";
const std::string PM = "下午";
const std::string COLON = ":";
const std::string ZERO = "0";
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
} // namespace
class TimePickerPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
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
    auto themeManager = AceType::MakeRefPtr<MockPickerThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPatternTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[minuteColumnNode].emplace_back(std::to_string(Value));
    }
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), static_cast<int32_t>(DEFAULT_VALUE.size()));
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetShowCount(SHOW_COUNT);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    EXPECT_EQ(accessibilityProperty->GetCurrentIndex(), CURRENT_VALUE1);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), CURRENT_VALUE1 - SHOW_COUNT / MIDDLE_OF_COUNTS);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), CURRENT_VALUE1 + SHOW_COUNT / MIDDLE_OF_COUNTS);
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[minuteColumnNode].emplace_back(std::to_string(Value));
    }
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), std::to_string(DEFAULT_VALUE.at(CURRENT_VALUE1)));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg005
 * @tc.desc: Test the SupportAction property of DatePickerPattern
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"];
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[minuteColumnNode].emplace_back(std::to_string(Value));
    }
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto* stack = ViewStackProcessor::GetInstance();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto weakNode = AceType::WeakClaim(AceType::RawPtr(buttonNode));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
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
    auto totalOptionCount = options[minuteColumn].size();

    gestureEvent.SetInputEventType(InputEventType::AXIS);
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto options = minuteColumnPattern->GetOptions();
    auto totalOptionCount = options[minuteColumn].size();

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
    EXPECT_EQ(minuteColumnPattern->gradientHeight_, gradientHeight);
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    minuteColumnPattern->yOffset_ = OFFSET_Y;
    auto options = minuteColumnPattern->GetOptions();
    int totalOptionCount = static_cast<int>(options[minuteColumn].size());
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
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"];
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    minuteColumnPattern->InitOnKeyEvent(focusHub);
    auto onKeyEvent = focusHub->onKeyEventInternal_;

    KeyEvent keyEvent(KeyCode::KEY_DPAD_UP, KeyAction::UP);
    EXPECT_FALSE(onKeyEvent(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_TRUE(onKeyEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(onKeyEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(onKeyEvent(keyEvent));
}
} // namespace OHOS::Ace::NG

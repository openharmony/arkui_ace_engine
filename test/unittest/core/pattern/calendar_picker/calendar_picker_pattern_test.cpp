/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_event_hub.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_algorithm.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_property.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr Dimension TEST_SETTING_RADIUS = Dimension(10.0, DimensionUnit::VP);
} // namespace
class CalendarPickerPatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarPickerPatternTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == CalendarTheme::TypeId()) {
            return AceType::MakeRefPtr<CalendarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return AceType::MakeRefPtr<PickerTheme>();
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void CalendarPickerPatternTest::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

void CalendarPickerPatternTest::CreateCalendarPicker()
{
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    DimensionOffset offset;
    calendarPickerModel.SetEdgeAlign(CalendarEdgeAlign::EDGE_ALIGN_START, offset);

    PickerTextStyle textStyle;
    calendarPickerModel.SetTextStyle(textStyle);
    auto onChange = [](const std::string& /* info */) {};
    calendarPickerModel.SetOnChange(onChange);
    calendarPickerModel.SetChangeEvent(onChange);
}

RefPtr<FrameNode> CalendarPickerPatternTest::CalendarDialogShow(RefPtr<FrameNode> entryNode)
{
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(2000, 1, 1);
    settingData.selectedDate = selectedDate;
    settingData.dayRadius = TEST_SETTING_RADIUS;
    settingData.entryNode = entryNode;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = CalendarDialogView::Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    return dialogNode;
}

/**
 * @tc.name: CalendarPickerPatternTest015
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest015, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 800);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(799));
}

/**
 * @tc.name: CalendarPickerPatternTest016
 * @tc.desc: HandleMonthKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest016, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 10);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleMonthKeyEvent(10));

    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 3);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(3);
    EXPECT_TRUE(pickerPattern->isKeyWaiting_);

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 0);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleMonthKeyEvent(0));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 10);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(10);
    EXPECT_TRUE(pickerPattern->isKeyWaiting_);
}

/**
 * @tc.name: CalendarPickerPatternTest017
 * @tc.desc: HandleMonthKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest017, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 799);
    json->Put("month", 1);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(1);
}

/**
 * @tc.name: CalendarPickerPatternTest018
 * @tc.desc: HandleDayKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest018, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleDayKeyEvent(31));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 0);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleDayKeyEvent(0));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleDayKeyEvent(1);
}

/**
 * @tc.name: CalendarPickerPatternTest019
 * @tc.desc: HandleDayKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest019, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleDayKeyEvent(1);
}

/**
 * @tc.name: CalendarPickerPatternTest020
 * @tc.desc: HandleNumberKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest020, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_STAR;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventOne));

    KeyEvent keyEventTwo;
    keyEventTwo.code = KeyCode::KEY_NUMPAD_0;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventTwo));

    KeyEvent keyEventThree;
    keyEventThree.code = KeyCode::KEY_0;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventThree));
}

/**
 * @tc.name: CalendarPickerPatternTest021
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest021, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->taskCount_ = 2;
    pickerPattern->HandleTaskCallback();

    pickerPattern->taskCount_ = 0;
    pickerPattern->HandleTaskCallback();
    EXPECT_EQ(pickerPattern->taskCount_, 0);

    pickerPattern->taskCount_ = 1;
    pickerPattern->isKeyWaiting_ = true;
    auto json = JsonUtil::Create(true);
    json->Put("year", 1000);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleTaskCallback();
    EXPECT_FALSE(pickerPattern->isKeyWaiting_);

    pickerPattern->taskCount_ = 1;
    pickerPattern->isKeyWaiting_ = false;
    pickerPattern->HandleTaskCallback();
}

/**
 * @tc.name: CalendarPickerPatternTest022
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest022, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->taskCount_ = 1;
    pickerPattern->isKeyWaiting_ = true;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleTaskCallback();
    EXPECT_FALSE(pickerPattern->isKeyWaiting_);
}

/**
 * @tc.name: CalendarPickerPatternTest023
 * @tc.desc: HandleTextHoverEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest023, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    pickerPattern->HandleTextHoverEvent(true, 0);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    pickerPattern->HandleTextHoverEvent(true, 2);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    pickerPattern->HandleTextHoverEvent(true, 4);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    pickerPattern->HandleTextHoverEvent(false, 4);
}

/**
 * @tc.name: CalendarPickerPatternTest024
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest024, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 802);
    EXPECT_EQ(json->GetUInt("month"), 2);
    EXPECT_EQ(json->GetUInt("day"), 28);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 802);
    EXPECT_EQ(json->GetUInt("month"), 3);
    EXPECT_EQ(json->GetUInt("day"), 1);
}

/**
 * @tc.name: CalendarPickerPatternTest025
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest025, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 800);
    json->Put("month", 10);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 800);
    EXPECT_EQ(json->GetUInt("month"), 11);
    EXPECT_EQ(json->GetUInt("day"), 30);
}

/**
 * @tc.name: CalendarPickerPatternTest026
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest026, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 800);
    json->Put("month", 12);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 801);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest027
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest027, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 12);
    json->Put("day", 32);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 802);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 1);
}

/**
 * @tc.name: CalendarPickerPatternTest028
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest028, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    auto json = JsonUtil::Create(true);
    json->Put("year", 802);
    json->Put("month", 2);
    json->Put("day", 30);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 801);
    EXPECT_EQ(json->GetUInt("month"), 2);
    EXPECT_EQ(json->GetUInt("day"), 28);
}

/**
 * @tc.name: CalendarPickerPatternTest029
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest029, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 1);
    json->Put("day", 32);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 800);
    EXPECT_EQ(json->GetUInt("month"), 12);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest030
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest030, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 7);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 801);
    EXPECT_EQ(json->GetUInt("month"), 6);
    EXPECT_EQ(json->GetUInt("day"), 30);
}

/**
 * @tc.name: CalendarPickerPatternTest031
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest031, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 801);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest032
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest032, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 800);
    EXPECT_EQ(json->GetUInt("month"), 12);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest033
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest033, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 801);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest034
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest034, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_CENTER);
    pickerPattern->CalculateDialogOffset();
}

/**
 * @tc.name: CalendarPickerPatternTest035
 * @tc.desc: CalculateDialogOffset Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest035, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_END);
    pickerPattern->CalculateDialogOffset();
}

/**
 * @tc.name: CalendarPickerPatternTest037
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest037, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    auto json = JsonUtil::Create(true);
    json->Put("year", 5000);
    json->Put("month", 1);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 1);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest038
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest038, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 5000);
    json->Put("month", 12);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 1);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest039
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest039, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 5000);
    json->Put("month", 12);
    json->Put("day", 32);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleAddButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 1);
    EXPECT_EQ(json->GetUInt("month"), 1);
    EXPECT_EQ(json->GetUInt("day"), 1);
}

/**
 * @tc.name: CalendarPickerPatternTest040
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest040, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    auto json = JsonUtil::Create(true);
    json->Put("year", 1);
    json->Put("month", 2);
    json->Put("day", 30);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 5000);
    EXPECT_EQ(json->GetUInt("month"), 2);
    EXPECT_EQ(json->GetUInt("day"), 28);
}

/**
 * @tc.name: CalendarPickerPatternTest041
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest041, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    auto json = JsonUtil::Create(true);
    json->Put("year", 1);
    json->Put("month", 1);
    json->Put("day", 32);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 5000);
    EXPECT_EQ(json->GetUInt("month"), 12);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest042
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest042, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    auto json = JsonUtil::Create(true);
    json->Put("year", 1);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleSubButtonClick();
    json = JsonUtil::ParseJsonString(pickerPattern->GetEntryDateInfo());
    EXPECT_EQ(json->GetUInt("year"), 5000);
    EXPECT_EQ(json->GetUInt("month"), 12);
    EXPECT_EQ(json->GetUInt("day"), 31);
}

/**
 * @tc.name: CalendarPickerPatternTest043
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest043, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->onBlurInternal_, nullptr);

    focusHub->onBlurInternal_();
}

/**
 * @tc.name: CalendarPickerPatternTest044
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest044, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    KeyEvent event;
    EXPECT_FALSE(pickerPattern->HandleBlurEvent(event));
}

/**
 * @tc.name: CalendarPickerPatternTest045
 * @tc.desc: PostTaskToUI Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest045, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto context = frameNode->GetContextRefPtr();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    std::function<void()> task;
    pickerPattern->PostTaskToUI(task, "ArkUITask");
}

/**
 * @tc.name: CalendarPickerPatternTest046
 * @tc.desc: OnWindowSizeChanged Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest046, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    pickerPattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::RECOVER);
}
/**
 * @tc.name: CalendarPickerPatternTest047
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest047, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_TAB, pickerPattern->isFirtFocus_ = false;
    pickerPattern->SetDialogShow(false);
    EXPECT_FALSE(pickerPattern->HandleFocusEvent(keyEvent));
}

/**
 * @tc.name: CalendarPickerPatternTest048
 * @tc.desc: HandleButtonTouchEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest048, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    bool isPressed = true;
    pickerPattern->HandleButtonTouchEvent(isPressed, 0);
}

/**
 * @tc.name: CalendarPickerPatternTest049
 * @tc.desc: ShowDialog Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest049, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->SetDialogShow(true);
    pickerPattern->ShowDialog();
}

/**
 * @tc.name: CalendarPickerPatternTest050
 * @tc.desc: InitDateIndex Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest050, TestSize.Level0)
{
    const std::string language = "false";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->InitDateIndex();
    EXPECT_EQ(pickerPattern->yearIndex_, 0);
    EXPECT_EQ(pickerPattern->monthIndex_, 2);
    EXPECT_EQ(pickerPattern->dayIndex_, 4);
}

/**
 * @tc.name: CalendarPickerPatternTest051
 * @tc.desc: InitDateIndex Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest051, TestSize.Level0)
{
    const std::string language = "zh";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->InitDateIndex();

    EXPECT_EQ(pickerPattern->yearIndex_, 0);
    EXPECT_EQ(pickerPattern->monthIndex_, 2);
    EXPECT_EQ(pickerPattern->dayIndex_, 4);
}

/**
 * @tc.name: CalendarPickerPatternTest052
 * @tc.desc: InitDateIndex Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest052, TestSize.Level0)
{
    const std::string language = "ug";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->InitDateIndex();

    EXPECT_EQ(pickerPattern->yearIndex_, 4);
    EXPECT_EQ(pickerPattern->monthIndex_, 0);
    EXPECT_EQ(pickerPattern->dayIndex_, 2);
}

/**
 * @tc.name: CalendarPickerPatternTest053
 * @tc.desc: Test for SetStartDateWithNode and GetStartDateWithNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest053, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    uint32_t startYear = 2024;
    uint32_t startMonth = 1;
    uint32_t startDay = 8;
    CalendarPickerModelNG::SetStartDateWithNode(Referenced::RawPtr(frameNode), startYear, startMonth, startDay);
    auto startPickDate = CalendarPickerModelNG::GetStartDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(startPickDate.GetYear(), startYear);
    EXPECT_EQ(startPickDate.GetMonth(), startMonth);
    EXPECT_EQ(startPickDate.GetDay(), startDay);
   
    startDay = 40;
    CalendarPickerModelNG::SetStartDateWithNode(Referenced::RawPtr(frameNode), startYear, startMonth, startDay);
    startPickDate = CalendarPickerModelNG::GetStartDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(startPickDate.GetYear(), 0);
    EXPECT_EQ(startPickDate.GetMonth(), 0);
    EXPECT_EQ(startPickDate.GetDay(), 0);

    startDay = -1;
    CalendarPickerModelNG::SetStartDateWithNode(Referenced::RawPtr(frameNode), startYear, startMonth, startDay);
    startPickDate = CalendarPickerModelNG::GetStartDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(startPickDate.GetYear(), 0);
    EXPECT_EQ(startPickDate.GetMonth(), 0);
    EXPECT_EQ(startPickDate.GetDay(), 0);
}

/**
 * @tc.name: CalendarPickerPatternTest054
 * @tc.desc: Test for SetEndDateWithNode and GetEndDateWithNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest054, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    uint32_t startYear = 2024;
    uint32_t startMonth = 1;
    uint32_t startDay = 8;
    CalendarPickerModelNG::SetStartDateWithNode(Referenced::RawPtr(frameNode), startYear, startMonth, startDay);
    auto startPickDate = CalendarPickerModelNG::GetStartDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(startPickDate.GetYear(), startYear);
    EXPECT_EQ(startPickDate.GetMonth(), startMonth);
    EXPECT_EQ(startPickDate.GetDay(), startDay);
   
    uint32_t endYear = 2024;
    uint32_t endMonth = 1;
    uint32_t endDay = 7;
    CalendarPickerModelNG::SetEndDateWithNode(Referenced::RawPtr(frameNode), endYear, endMonth, endDay);
    auto endPickDate = CalendarPickerModelNG::GetEndDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(endPickDate.GetYear(), 0);
    EXPECT_EQ(endPickDate.GetMonth(), 0);
    EXPECT_EQ(endPickDate.GetDay(), 0);
    
    endDay = 9;
    CalendarPickerModelNG::SetEndDateWithNode(Referenced::RawPtr(frameNode), endYear, endMonth, endDay);
    endPickDate = CalendarPickerModelNG::GetEndDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(endPickDate.GetYear(), endYear);
    EXPECT_EQ(endPickDate.GetMonth(), endMonth);
    EXPECT_EQ(endPickDate.GetDay(), endDay);

    endDay = 40;
    CalendarPickerModelNG::SetEndDateWithNode(Referenced::RawPtr(frameNode), endYear, endMonth, endDay);
    endPickDate = CalendarPickerModelNG::GetEndDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(endPickDate.GetYear(), 0);
    EXPECT_EQ(endPickDate.GetMonth(), 0);
    EXPECT_EQ(endPickDate.GetDay(), 0);

    endDay = -1;
    CalendarPickerModelNG::SetEndDateWithNode(Referenced::RawPtr(frameNode), endYear, endMonth, endDay);
    endPickDate = CalendarPickerModelNG::GetEndDateWithNode(Referenced::RawPtr(frameNode));
    EXPECT_EQ(endPickDate.GetYear(), 0);
    EXPECT_EQ(endPickDate.GetMonth(), 0);
    EXPECT_EQ(endPickDate.GetDay(), 0);
}

/**
 * @tc.name: CalendarPickerPatternTest055
 * @tc.desc: Test for SetMarkToday and GetMarkToday
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest055, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.steps: step2. call SetMarkToday.
     * @tc.desc: set markToday.
     * @tc.expected: GetMarkToday equals markToday.
     */
    bool markToday = true;
    CalendarPickerModelNG::SetMarkToday(Referenced::RawPtr(frameNode), markToday);
    EXPECT_EQ(CalendarPickerModelNG::GetMarkToday(Referenced::RawPtr(frameNode)), markToday);
}

/**
 * @tc.name: CalendarPickerPatternTest056
 * @tc.desc: Test for SetDisabledDateRange and GetDisabledDateRange
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTest, CalendarPickerPatternTest056, TestSize.Level0)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.steps: step2. call SetDisabledDateRange.
     * @tc.desc: set disabledDateRange is empty.
     * @tc.expected: GetDisabledDateRange is empty.
     */
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    CalendarPickerModelNG::SetDisabledDateRange(Referenced::RawPtr(frameNode), disabledDateRange);
    EXPECT_EQ(CalendarPickerModelNG::GetDisabledDateRange(Referenced::RawPtr(frameNode)), "");
    /**
     * @tc.steps: step2. call SetDisabledDateRange.
     * @tc.desc: set disabledDateRange.
     * @tc.expected: GetDisabledDateRange equals disabledDateRange.
     */
    std::pair<PickerDate, PickerDate> pair;
    PickerDate defaultDate;
    pair.first = defaultDate;
    pair.second = defaultDate;
    disabledDateRange.emplace_back(pair);
    CalendarPickerModelNG::SetDisabledDateRange(Referenced::RawPtr(frameNode), disabledDateRange);
    std::string ret = std::to_string(pair.first.GetYear()) + "-" + std::to_string(pair.first.GetMonth()) + "-" +
                      std::to_string(pair.first.GetDay()) + "," + std::to_string(pair.second.GetYear()) + "-" +
                      std::to_string(pair.second.GetMonth()) + "-" + std::to_string(pair.second.GetDay());
    EXPECT_EQ(CalendarPickerModelNG::GetDisabledDateRange(Referenced::RawPtr(frameNode)), ret);
}
} // namespace OHOS::Ace::NG

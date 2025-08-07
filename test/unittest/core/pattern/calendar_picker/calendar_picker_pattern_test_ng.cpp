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

#include <cstddef>
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/base/mock_system_properties.h"

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

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr Dimension TEST_SETTING_RADIUS = Dimension(10.0, DimensionUnit::VP);
const std::string PICKER_DATE_JSON_STR = "{\"year\":2024,\"month\":1,\"day\":21}";
const std::string PICKER_DATE_JSON_STR2 = "{\"year\":2025,\"month\":2,\"day\":22}";
} // namespace
class CalendarPickerPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarPickerPatternTestNg::SetUpTestCase()
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

void CalendarPickerPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

void CalendarPickerPatternTestNg::CreateCalendarPicker()
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

RefPtr<FrameNode> CalendarPickerPatternTestNg::CalendarDialogShow(RefPtr<FrameNode> entryNode)
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
 * @tc.name: HandleHoverEvent001
 * @tc.desc: HandleHoverEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleHoverEvent001, TestSize.Level1)
{
    CreateCalendarPicker();
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto theme = pipelineContext->GetTheme<CalendarTheme>();
    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->yearIndex_));
    ASSERT_NE(yearNode, nullptr);
    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->monthIndex_));
    ASSERT_NE(monthNode, nullptr);
    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->dayIndex_));
    ASSERT_NE(dayNode, nullptr);
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(buttonFlexNode, nullptr);
    auto addBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(0));
    ASSERT_NE(addBtnNode, nullptr);
    auto subBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(1));
    ASSERT_NE(subBtnNode, nullptr);

    auto yearMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    yearMockRenderContext->rect_.SetRect(0, 0, 10, 10);
    yearNode->renderContext_ = yearMockRenderContext;
    auto monthMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    monthMockRenderContext->rect_.SetRect(0, 10, 10, 10);
    monthNode->renderContext_ = monthMockRenderContext;
    auto dayMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    dayMockRenderContext->rect_.SetRect(0, 20, 10, 10);
    dayNode->renderContext_ = dayMockRenderContext;
    auto addBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    addBtnMockRenderContext->rect_.SetRect(0, 30, 10, 10);
    addBtnNode->renderContext_ = addBtnMockRenderContext;
    auto subBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    subBtnMockRenderContext->rect_.SetRect(0, 40, 10, 10);
    subBtnNode->renderContext_ = subBtnMockRenderContext;

    Offset addBtnLocation(5, 35);
    pickerPattern->HandleHoverEvent(true, addBtnLocation);
    Offset subBtnLocation(5, 45);
    pickerPattern->HandleHoverEvent(true, subBtnLocation);
    Offset yeatLocation(5, 5);
    pickerPattern->HandleHoverEvent(true, yeatLocation);
    EXPECT_EQ(yearNode->GetRenderContext()->GetBackgroundColor(), theme->GetBackgroundHoverColor());
    Offset monthLocation(5, 15);
    pickerPattern->HandleHoverEvent(true, monthLocation);
    EXPECT_EQ(monthNode->GetRenderContext()->GetBackgroundColor(), theme->GetBackgroundHoverColor());
    Offset dayLocation(5, 25);
    pickerPattern->HandleHoverEvent(true, dayLocation);
    EXPECT_EQ(dayNode->GetRenderContext()->GetBackgroundColor(), theme->GetBackgroundHoverColor());
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: HandleTouchEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleTouchEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    auto element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto theme = pipelineContext->GetTheme<CalendarTheme>();
    ASSERT_NE(theme, nullptr);
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(buttonFlexNode, nullptr);
    auto addBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(0));
    ASSERT_NE(addBtnNode, nullptr);
    auto subBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(1));
    ASSERT_NE(subBtnNode, nullptr);

    auto addBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    addBtnMockRenderContext->rect_.SetRect(0, 0, 10, 10);
    addBtnNode->renderContext_ = addBtnMockRenderContext;
    auto subBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    subBtnMockRenderContext->rect_.SetRect(0, 10, 10, 10);
    subBtnNode->renderContext_ = subBtnMockRenderContext;

    Offset otherLocation(20, 30);
    pickerPattern->HandleTouchEvent(true, otherLocation);
    pickerPattern->HandleTouchEvent(false, otherLocation);

    Offset addBtnLocation(5, 5);
    pickerPattern->HandleTouchEvent(true, addBtnLocation);
    EXPECT_EQ(addBtnNode->GetRenderContext()->GetBackgroundColor(), theme->GetBackgroundHoverColor());

    Offset subBtnLocation(5, 15);
    pickerPattern->HandleTouchEvent(true, subBtnLocation);
    EXPECT_EQ(subBtnNode->GetRenderContext()->GetBackgroundColor(), theme->GetBackgroundHoverColor());
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: HandleClickEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleClickEvent001, TestSize.Level1)
{
    CreateCalendarPicker();
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto theme = pipelineContext->GetTheme<CalendarTheme>();
    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    auto yearNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->yearIndex_));
    auto monthNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->monthIndex_));
    auto dayNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(pickerPattern->dayIndex_));
    auto buttonFlexNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    auto addBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(0));
    auto subBtnNode = AceType::DynamicCast<FrameNode>(buttonFlexNode->GetChildAtIndex(1));

    auto yearMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    yearMockRenderContext->rect_.SetRect(0, 0, 10, 10);
    yearNode->renderContext_ = yearMockRenderContext;
    auto monthMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    monthMockRenderContext->rect_.SetRect(0, 10, 10, 10);
    monthNode->renderContext_ = monthMockRenderContext;
    auto dayMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    dayMockRenderContext->rect_.SetRect(0, 20, 10, 10);
    dayNode->renderContext_ = dayMockRenderContext;
    auto addBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    addBtnMockRenderContext->rect_.SetRect(0, 30, 10, 10);
    addBtnNode->renderContext_ = addBtnMockRenderContext;
    auto subBtnMockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    subBtnMockRenderContext->rect_.SetRect(0, 40, 10, 10);
    subBtnNode->renderContext_ = subBtnMockRenderContext;

    Offset otherLocation(20, 50);
    pickerPattern->SetDialogShow(true);
    pickerPattern->HandleClickEvent(otherLocation);
    pickerPattern->SetDialogShow(false);
    pickerPattern->HandleClickEvent(otherLocation);
    Offset addBtnLocation(5, 35);
    pickerPattern->HandleClickEvent(addBtnLocation);
    Offset subBtnLocation(5, 45);
    pickerPattern->HandleClickEvent(subBtnLocation);
    Offset yeatLocation(5, 5);
    pickerPattern->HandleClickEvent(yeatLocation);
    EXPECT_EQ(pickerPattern->selected_, CalendarPickerSelectedType::YEAR);
    Offset monthLocation(5, 15);
    pickerPattern->HandleClickEvent(monthLocation);
    EXPECT_EQ(pickerPattern->selected_, CalendarPickerSelectedType::MONTH);
    Offset dayLocation(5, 25);
    pickerPattern->HandleClickEvent(dayLocation);
    EXPECT_EQ(pickerPattern->selected_, CalendarPickerSelectedType::DAY);
}

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleKeyEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = false;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SHIFT_LEFT;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_SHIFT_LEFT;
    pickerPattern->isFirtFocus_ = false;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = false;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_SHIFT_LEFT;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(event);

    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_SHIFT_LEFT;
    pickerPattern->isFirtFocus_ = false;
    bool res = pickerPattern->HandleKeyEvent(event);

    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleFocusEvent001
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleFocusEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_UP;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = false;
    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = true;
    pickerPattern->selected_ = CalendarPickerSelectedType::SUBBTN;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = false;
    pickerPattern->selected_ = CalendarPickerSelectedType::SUBBTN;
    pickerPattern->HandleFocusEvent(event);

    event.code = KeyCode::KEY_DPAD_DOWN;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = false;
    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = true;
    pickerPattern->selected_ = CalendarPickerSelectedType::SUBBTN;
    pickerPattern->HandleFocusEvent(event);

    pickerPattern->isFirtFocus_ = false;
    pickerPattern->selected_ = CalendarPickerSelectedType::SUBBTN;
    bool res = pickerPattern->HandleFocusEvent(event);

    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleYearKeyWaitingEvent001
 * @tc.desc: HandleYearKeyWaitingEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleYearKeyWaitingEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    std::function<void()> task = []() {};

    std::function<void()> zeroStartTask = []() {};
    pickerPattern->yearPrefixZeroCount_ = 2;
    pickerPattern->yearEnterCount_ = 3;
    bool res = pickerPattern->HandleYearKeyWaitingEvent(0, task, zeroStartTask);
    EXPECT_TRUE(res);
    pickerPattern->yearPrefixZeroCount_ = 2;
    pickerPattern->yearEnterCount_ = 3;
    res = pickerPattern->HandleYearKeyWaitingEvent(-1, task, zeroStartTask);
    EXPECT_TRUE(res);
    pickerPattern->yearPrefixZeroCount_ = 3;
    pickerPattern->yearEnterCount_ = 4;
    res = pickerPattern->HandleYearKeyWaitingEvent(0, task, zeroStartTask);
    EXPECT_FALSE(res);
    pickerPattern->yearPrefixZeroCount_ = 3;
    pickerPattern->yearEnterCount_ = 4;
    res = pickerPattern->HandleYearKeyWaitingEvent(-1, task, zeroStartTask);
    EXPECT_TRUE(res);
    pickerPattern->yearPrefixZeroCount_ = 3;
    pickerPattern->yearEnterCount_ = 5;
    res = pickerPattern->HandleYearKeyWaitingEvent(-1, task, zeroStartTask);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleYearKeyEvent001
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleYearKeyEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->yearEnterCount_ = 5;
    bool res = pickerPattern->HandleYearKeyEvent(0);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: HandleMonthKeyEvent001
 * @tc.desc: HandleMonthKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleMonthKeyEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->isKeyWaiting_ = true;

    pickerPattern->monthPrefixZeroCount_ = 1;
    pickerPattern->HandleMonthKeyEvent(0);
    pickerPattern->monthPrefixZeroCount_ = 0;
    pickerPattern->HandleMonthKeyEvent(0);

    pickerPattern->monthPrefixZeroCount_ = 1;
    pickerPattern->HandleMonthKeyEvent(1);
    pickerPattern->monthPrefixZeroCount_ = 0;
    bool res = pickerPattern->HandleMonthKeyEvent(1);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: HandleDayKeyEvent001
 * @tc.desc: HandleDayKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, HandleDayKeyEvent001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->isKeyWaiting_ = true;

    pickerPattern->dayPrefixZeroCount_ = 1;
    pickerPattern->HandleDayKeyEvent(0);
    pickerPattern->dayPrefixZeroCount_ = 0;
    pickerPattern->HandleDayKeyEvent(0);

    pickerPattern->dayPrefixZeroCount_ = 1;
    pickerPattern->HandleDayKeyEvent(1);
    pickerPattern->dayPrefixZeroCount_ = 0;
    bool res = pickerPattern->HandleDayKeyEvent(1);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: CalculateDialogOffset001
 * @tc.desc: CalculateDialogOffset Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalculateDialogOffset001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto host = pickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_CENTER);
    OffsetF f = pickerPattern->CalculateDialogOffset();

    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_END);
    f = pickerPattern->CalculateDialogOffset();

    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto windowManager = pipelineContext->GetWindowManager();

    auto WindownMode = []() -> WindowMode { return WindowMode::WINDOW_MODE_FLOATING; };
    windowManager->SetWindowGetModeCallBack(WindownMode);
    pipelineContext->SetWindowModal(WindowModal::CONTAINER_MODAL);

    f = pickerPattern->CalculateDialogOffset();

    EXPECT_FALSE(f.GetX() > 0);
}

/**
 * @tc.name: CalendarDialogPatternTest029
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest029, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    const auto& calendarLayoutProperty = calendarNode->GetLayoutProperty();
    calendarLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    KeyEvent keyEventOne(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 1;
    result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogPatternTest030
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest030, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    const auto& calendarLayoutProperty = calendarNode->GetLayoutProperty();
    calendarLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    KeyEvent keyEventOne(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 1;
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogPatternTest031
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest31, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    const auto& calendarLayoutProperty = calendarNode->GetLayoutProperty();
    calendarLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    KeyEvent keyEventOne(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 1;
    result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogPatternTest032
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest032, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    const auto& calendarLayoutProperty = calendarNode->GetLayoutProperty();
    calendarLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    KeyEvent keyEventOne(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 1;
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogPatternTest034
 * @tc.desc: OnEnterKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest033, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    KeyEvent keyEventOne(KeyCode::KEY_NUMPAD_ENTER, KeyAction::DOWN);
    dialogPattern->OnEnterKeyEvent(keyEventOne);
    EXPECT_EQ(dialogNode->GetChildAtIndex(2), nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest034
 * @tc.desc: OnLanguageConfigurationUpdate Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest034, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    dialogPattern->OnLanguageConfigurationUpdate();
    EXPECT_NE(AceApplicationInfo::GetInstance().GetLanguage(), "zh");
    AceApplicationInfo::GetInstance().language_ = "zh";
    dialogPattern->OnLanguageConfigurationUpdate();
    auto pipelineContext = dialogPattern->GetContext();
    auto fontSizeScale = pipelineContext->GetFontScale();
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    EXPECT_FALSE(fontSizeScale < theme->GetCalendarPickerLargeScale());
}

/**
 * @tc.name: CalendarDialogPatternTest035
 * @tc.desc: HandleSurfaceChanged Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogPatternTest035, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    dialogPattern->HandleSurfaceChanged(1, 1, 2, 2);
    EXPECT_EQ(CalendarDialogView::previousOrientation_, SystemProperties::GetDeviceOrientation());
}

/**
 * @tc.name: GetChangeEvent001
 * @tc.desc: Get ChangeEvent Function Test for CalendarPickerDialog
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, GetChangeEvent001, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    CalendarSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto callback = CalendarDialogView::GetChangeEvent(settingData, nullptr, dialogEvent);
    ASSERT_NE(callback, nullptr);
    callback = CalendarDialogView::GetChangeEvent(settingData, frameNode, dialogEvent);
    ASSERT_NE(callback, nullptr);

    settingData.entryNode = frameNode;
    callback = CalendarDialogView::GetChangeEvent(settingData, nullptr, dialogEvent);
    ASSERT_EQ(callback, nullptr);
    callback = CalendarDialogView::GetChangeEvent(settingData, frameNode, dialogEvent);
    ASSERT_EQ(callback, nullptr);

    bool result = false;
    auto changeId = [&result](const std::string& info) {
        result = true;
    };
    dialogEvent["changeId"] = changeId;
    settingData.entryNode = nullptr;
    result = false;
    callback = CalendarDialogView::GetChangeEvent(settingData, nullptr, dialogEvent);
    ASSERT_NE(callback, nullptr);
    callback("");
    EXPECT_TRUE(result);

    result = false;
    callback = CalendarDialogView::GetChangeEvent(settingData, frameNode, dialogEvent);
    ASSERT_NE(callback, nullptr);
    callback("");
    EXPECT_TRUE(result);

    settingData.entryNode = frameNode;
    result = false;
    callback = CalendarDialogView::GetChangeEvent(settingData, nullptr, dialogEvent);
    ASSERT_NE(callback, nullptr);
    callback("");
    EXPECT_TRUE(result);

    result = false;
    callback = CalendarDialogView::GetChangeEvent(settingData, frameNode, dialogEvent);
    ASSERT_NE(callback, nullptr);
    callback("");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ReportChangeEvent001
 * @tc.desc: ReportChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, ReportChangeEvent001, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    auto calendarPickerNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(calendarPickerNode, nullptr);
    auto calendarPickerPattern = calendarPickerNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(calendarPickerPattern, nullptr);

    auto ret = calendarPickerPattern->ReportChangeEvent("CalendarPicker", "onChange",
        PICKER_DATE_JSON_STR);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ReportChangeEvent002
 * @tc.desc: ReportChangeEvent, GetReportChangeEventDate, CanReportChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, ReportChangeEvent002, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    ASSERT_NE(element, nullptr);
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    ASSERT_NE(dialogNode, nullptr);
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);
    auto ret = CalendarDialogView::ReportChangeEvent(calendarDialogNode, "CalendarPickerDialog", "onChange",
        PICKER_DATE_JSON_STR);
    EXPECT_TRUE(ret);

    auto dateJson = JsonUtil::ParseJsonString(PICKER_DATE_JSON_STR);
    ASSERT_NE(dateJson, nullptr);
    auto dateJson2 = JsonUtil::ParseJsonString(PICKER_DATE_JSON_STR2);
    ASSERT_NE(dateJson2, nullptr);

    PickerDate pickerDate;
    PickerDate reportedPickerDate;
    EXPECT_TRUE(CalendarDialogView::GetReportChangeEventDate(pickerDate, PICKER_DATE_JSON_STR));
    EXPECT_EQ(pickerDate.GetYear(), dateJson->GetUInt("year"));
    EXPECT_EQ(pickerDate.GetMonth(), dateJson->GetUInt("month"));
    EXPECT_EQ(pickerDate.GetDay(), dateJson->GetUInt("day"));
    EXPECT_TRUE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));
    EXPECT_FALSE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));

    EXPECT_TRUE(CalendarDialogView::GetReportChangeEventDate(pickerDate, PICKER_DATE_JSON_STR2));
    EXPECT_EQ(pickerDate.GetYear(), dateJson2->GetUInt("year"));
    EXPECT_EQ(pickerDate.GetMonth(), dateJson2->GetUInt("month"));
    EXPECT_EQ(pickerDate.GetDay(), dateJson2->GetUInt("day"));
    EXPECT_TRUE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));
    EXPECT_FALSE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));

    EXPECT_TRUE(CalendarDialogView::GetReportChangeEventDate(pickerDate, PICKER_DATE_JSON_STR));
    EXPECT_EQ(pickerDate.GetYear(), dateJson->GetUInt("year"));
    EXPECT_EQ(pickerDate.GetMonth(), dateJson->GetUInt("month"));
    EXPECT_EQ(pickerDate.GetDay(), dateJson->GetUInt("day"));
    EXPECT_TRUE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));
    EXPECT_FALSE(CalendarDialogView::CanReportChangeEvent(reportedPickerDate, pickerDate));
}

/**
 * @tc.name: CalendarDialogLayoutAlgorithmTest
 * @tc.desc: MeasureWithAssertions Funtion Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, CalendarDialogLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     * @tc.expected: step1. Create success.
     */
    CreateCalendarPicker();
    auto node = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(node->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(node));
    auto layoutWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(layoutWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetChildAtIndex(0));
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    ASSERT_NE(calendarNode, nullptr);
    EXPECT_EQ(calendarNode->GetTag(), V2::CALENDAR_ETS_TAG);

    /**
     * @tc.steps: step2. Create LayoutAlgorithm.
     * @tc.expected: step2. Create success.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNode =
        AceType::MakeRefPtr<LayoutWrapperNode>(dialogNode, geometryNode, dialogNode->GetLayoutProperty());
    auto layoutAlgorithm = AceType::DynamicCast<CalendarDialogLayoutAlgorithm>(dialogPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapperNode->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. Measure with assertions.
     * @tc.expected: step3. Measure success.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = OptionalSizeF(0.f, 0.f);
    layoutWrapperNode->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutAlgorithm->Measure(AceType::RawPtr(layoutWrapperNode));
    EXPECT_EQ(layoutWrapperNode->GetGeometryNode()->GetFrameSize().Width(), 0.f);
    EXPECT_EQ(layoutWrapperNode->GetGeometryNode()->GetFrameSize().Height(), 0.f);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Text OnColorConfigurationUpdate function when ConfigChangePerform is true.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     * @tc.expected: step1. Create success.
     */
    CreateCalendarPicker();
    auto node = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(node->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(node));
    ASSERT_NE(dialogNode, nullptr);
    auto layoutWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(layoutWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(layoutWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto swiperNode = dialogPattern->GetSwiperFrameNode();
    ASSERT_NE(swiperNode, nullptr);
    const auto& swiperNodeLayoutProperty = swiperNode->GetLayoutProperty();
    ASSERT_NE(swiperNodeLayoutProperty, nullptr);
    swiperNodeLayoutProperty->CleanDirty();

    /**
     * @tc.steps: step3. Call OnColorConfigurationUpdate function.
     */
    dialogPattern->OnColorConfigurationUpdate();
    auto layoutFlag = swiperNodeLayoutProperty->GetPropertyChangeFlag();
    EXPECT_EQ(layoutFlag, PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test CalendarPickerPattern OnColorConfigurationUpdate function when ConfigChangePerform is true.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerPatternTestNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     * @tc.expected: step1. Create success.
     */
    CreateCalendarPicker();
    auto element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto host = pickerPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto layoutProperty = host->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step3. Call OnColorConfigurationUpdate function.
     */
    pickerPattern->OnColorConfigurationUpdate();
    Color color = layoutProperty->GetColor().value();

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(calendarTheme);
    Color expectColor = calendarTheme->GetEntryFontColor();
    EXPECT_EQ(color, expectColor);
}

} // namespace OHOS::Ace::NG

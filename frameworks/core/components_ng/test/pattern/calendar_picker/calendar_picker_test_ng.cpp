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

#include "base/utils/utils.h"
#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TEST_SETTING_RADIUS = Dimension(10.0, DimensionUnit::VP);
constexpr int32_t YEAR_INDEX = 0;
constexpr int32_t MONTH_INDEX = 2;
} // namespace

class CalendarPickerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker(RefPtr<OHOS::Ace::MockThemeManager> themeManager);
    static RefPtr<FrameNode> CalendarDialogShow(
        RefPtr<OHOS::Ace::MockThemeManager> themeManager, RefPtr<FrameNode> entryNode);
};

void CalendarPickerTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void CalendarPickerTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void CalendarPickerTestNg::CreateCalendarPicker(RefPtr<OHOS::Ace::MockThemeManager> themeManager)
{
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    DimensionOffset offset;
    calendarPickerModel.SetEdgeAlign(CalendarEdgeAlign::EDGE_ALIGN_START, offset);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())); // SetTextStyle
    PickerTextStyle textStyle;
    calendarPickerModel.SetTextStyle(textStyle);
    auto onChange = [](const std::string& /* info */) {
    };
    calendarPickerModel.SetOnChange(onChange);
}

RefPtr<FrameNode> CalendarPickerTestNg::CalendarDialogShow(
    RefPtr<OHOS::Ace::MockThemeManager> themeManager, RefPtr<FrameNode> entryNode)
{
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()));

    CalendarDialogView calendarDialogView;
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
    auto dialogNode = calendarDialogView.Show(properties, settingData, dialogEvent, dialogCancelEvent);
    return dialogNode;
}

/**
 * @tc.name: CalendarModelNGTest001
 * @tc.desc: Create Calendar Picker.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step1. Create Calendar Picker
     * @tc.expected: step1. Create Calendar successfully
     */
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    RefPtr<CalendarTheme> theme = MockPipelineBase::GetCurrent()->GetTheme<CalendarTheme>();
    ASSERT_NE(theme, nullptr);

    auto& borderWidthProp = layoutProperty->GetBorderWidthProperty();
    ASSERT_NE(borderWidthProp, nullptr);
    EXPECT_EQ(
        borderWidthProp->leftDimen.value_or(Dimension(1.0)).ConvertToVp(), theme->GetEntryBorderWidth().ConvertToVp());

    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto borderColor = renderContext->GetBorderColor();
    EXPECT_EQ(borderColor->leftColor->ColorToString(), theme->GetEntryBorderColor().ColorToString());

    /**
     * @tc.steps: step2. Click Calendar Picker
     * @tc.expected: step2. Show Calendar Dialog
     */

    auto gesture = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));

    auto result = gesture->ActClick();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Handle KEY_TAB on Calendar Picker
     * @tc.expected: step3. Focus changed
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    auto eventHub = frameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    KeyEvent keyEventOne(KeyCode::KEY_TAB, KeyAction::DOWN);
    result = eventHub->ProcessOnKeyEventInternal(keyEventOne);

    /**
     * @tc.steps: step4. Hover Calendar Picker
     * @tc.expected: step4. onHoverEvent execute
     */
    pickerPattern->HandleTextHoverEvent(true, YEAR_INDEX);

    pickerPattern->HandleTextHoverEvent(true, MONTH_INDEX);
    auto contentNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(MONTH_INDEX));
    ASSERT_NE(textFrameNode, nullptr);
    auto textRenderContext = textFrameNode->GetRenderContext();
    ASSERT_NE(textRenderContext, nullptr);

    EXPECT_EQ(
        textRenderContext->GetBackgroundColorValue().ColorToString(), theme->GetBackgroundHoverColor().ColorToString());

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest001
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    KeyEvent keyEventOne(KeyCode::KEY_TAB, KeyAction::DOWN);
    auto result = pickerPattern->HandleFocusEvent(keyEventOne);
    EXPECT_FALSE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    KeyEvent keyEventTwo(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventTwo);
    EXPECT_TRUE(result);

    result = pickerPattern->HandleFocusEvent(keyEventTwo);
    EXPECT_TRUE(result);

    KeyEvent keyEventThree(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventThree);
    EXPECT_TRUE(result);

    result = pickerPattern->HandleFocusEvent(keyEventThree);
    EXPECT_TRUE(result);

    KeyEvent keyEventFour(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    KeyEvent keyEventFive(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventFour);
    EXPECT_TRUE(result);
    result = pickerPattern->HandleFocusEvent(keyEventFive);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    result = pickerPattern->HandleFocusEvent(keyEventFour);
    EXPECT_TRUE(result);
    result = pickerPattern->HandleFocusEvent(keyEventFive);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleFocusEvent(keyEventFour);
    EXPECT_TRUE(result);
    result = pickerPattern->HandleFocusEvent(keyEventFive);
    EXPECT_TRUE(result);

    KeyEvent keyEventSix(KeyCode::KEY_MOVE_HOME, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventSix);
    EXPECT_TRUE(result);

    KeyEvent keyEventSeven(KeyCode::KEY_MOVE_END, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventSeven);
    EXPECT_TRUE(result);

    KeyEvent keyEventEight(KeyCode::KEY_NUMPAD_ENTER, KeyAction::DOWN);
    result = pickerPattern->HandleFocusEvent(keyEventEight);
    EXPECT_FALSE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest002
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;

    KeyEvent keyEventOne(KeyCode::KEY_NUMPAD_1, KeyAction::DOWN);
    auto result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->isKeyWaiting_ = true;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest001
 * @tc.desc: Calendar Dialog Show.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(themeManager, AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->OnModifyDone();

    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    dialogPattern->touchListener_->GetTouchEventCallback()(info);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));

    auto gesture = calendarDialogNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    auto result = gesture->ActClick();
    EXPECT_TRUE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest002
 * @tc.desc: Create Calendar Dialog Without EntryNode.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    CalendarDialogView calendarDialogView;
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(2000, 1, 1);
    settingData.selectedDate = selectedDate;
    settingData.dayRadius = TEST_SETTING_RADIUS;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto dialogNode = calendarDialogView.Show(properties, settingData, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    dialogPattern->touchListener_->GetTouchEventCallback()(info);

    auto gesture = calendarDialogNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    gesture->ActClick();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest001
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(themeManager, AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));

    KeyEvent keyEventOne(KeyCode::KEY_TAB, KeyAction::DOWN);
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    KeyEvent keyEventTwo(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventTwo);
    EXPECT_TRUE(result);

    KeyEvent keyEventThree(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventThree);
    EXPECT_TRUE(result);

    KeyEvent keyEventFour(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventFour);
    EXPECT_TRUE(result);

    KeyEvent keyEventFive(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventFive);
    EXPECT_TRUE(result);

    KeyEvent keyEventSix(KeyCode::KEY_MOVE_HOME, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventSix);
    EXPECT_TRUE(result);

    KeyEvent keyEventSeven(KeyCode::KEY_MOVE_END, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventSeven);
    EXPECT_TRUE(result);

    KeyEvent keyEventEight(KeyCode::KEY_SPACE, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventEight);
    EXPECT_TRUE(result);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest002
 * @tc.desc: HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(themeManager, AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    KeyEvent keyEventOne(KeyCode::KEY_TAB, KeyAction::DOWN);
    auto result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    result = dialogPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    KeyEvent keyEventTwo(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventTwo);
    EXPECT_TRUE(result);

    KeyEvent keyEventThree(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventThree);
    EXPECT_TRUE(result);

    KeyEvent keyEventFour(KeyCode::KEY_MOVE_HOME, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventFour);
    EXPECT_TRUE(result);

    KeyEvent keyEventFive(KeyCode::KEY_MOVE_END, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventFive);
    EXPECT_TRUE(result);

    KeyEvent keyEventSix(KeyCode::KEY_SPACE, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventSix);
    EXPECT_TRUE(result);

    KeyEvent keyEventSeven(KeyCode::KEY_ENTER, KeyAction::DOWN);
    result = dialogPattern->HandleKeyEvent(keyEventSeven);
    EXPECT_FALSE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest003
 * @tc.desc: AddHotZoneRect Function Test.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(themeManager, AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->AddHotZoneRect();
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest004
 * @tc.desc: HandleEntryChange Function Test.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(themeManager, AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto json = JsonUtil::Create(true);
    json->Put("year", 1993);
    json->Put("month", 10);
    json->Put("day", 20);
    auto info = json->ToString();

    dialogPattern->HandleEntryChange(info);
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    ASSERT_NE(calendarNode, nullptr);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);
    auto newSelectedDay = calendarPattern->GetSelectedDay();
    EXPECT_EQ(newSelectedDay.GetYear(), 1993);
    EXPECT_EQ(newSelectedDay.GetMonth(), 10);
    EXPECT_EQ(newSelectedDay.GetDay(), 20);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}
} // namespace OHOS::Ace::NG

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
#include "base/test/mock/mock_task_executor.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_event_hub.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_algorithm.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_layout_property.h"

#include "core/components/calendar/calendar_theme.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/event/focus_hub.h"
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
#include "core/components_ng/pattern/text/text_layout_property.h"
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
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    DimensionOffset offset;
    calendarPickerModel.SetEdgeAlign(CalendarEdgeAlign::EDGE_ALIGN_START, offset);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())); // SetTextStyle
    PickerTextStyle textStyle;
    calendarPickerModel.SetTextStyle(textStyle);
    auto onChange = [](const std::string& /* info */) {
    };
    calendarPickerModel.SetOnChange(onChange);
    calendarPickerModel.SetChangeEvent(onChange);
}

RefPtr<FrameNode> CalendarPickerTestNg::CalendarDialogShow(
    RefPtr<OHOS::Ace::MockThemeManager> themeManager, RefPtr<FrameNode> entryNode)
{
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // show
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDialogNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));

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
    auto dialogNode = CalendarDialogView::Show(properties, settingData, dialogEvent, dialogCancelEvent);
    return dialogNode;
}

/**
 * @tc.name: CalendarModelNGTest001
 * @tc.desc: Create Calendar Picker Function Test
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
 * @tc.name: CalendarPickerModelNGTest002
 * @tc.desc: SetTextStyle Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())); // SetTextStyle
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(100);
    calendarPickerModel.SetTextStyle(textStyle);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerModelNGTest003
 * @tc.desc: SetTextStyle Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
            .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())); // SetTextStyle
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension();
    calendarPickerModel.SetTextStyle(textStyle);

    textStyle.fontSize = Dimension(100);
    calendarPickerModel.SetTextStyle(textStyle);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

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
    EXPECT_TRUE(result);

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
    EXPECT_TRUE(result);

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

    pickerPattern->isKeyWaiting_ = false;
    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->isKeyWaiting_ = false;
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
 * @tc.desc: Calendar Dialog Show Function Test
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
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
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
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));

    auto gesture = calendarDialogNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    auto result = gesture->ActClick();
    EXPECT_TRUE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest002
 * @tc.desc: Create Calendar Dialog Without EntryNode Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // show
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDialogNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDividerNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()));
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
 * @tc.name: CalendarDialogViewTest003
 * @tc.desc: SetDialogChange Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest003, TestSize.Level1)
{
    int32_t calendarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto calendarNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, calendarNodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    ASSERT_NE(calendarNode, nullptr);
    CalendarDialogView calendarDialogView;
    DialogEvent event;
    calendarDialogView.SetDialogChange(calendarNode, std::move(event));
}

/**
 * @tc.name: CalendarDialogViewTest004
 * @tc.desc: callback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // show
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDialogNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDividerNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()));
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
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    ASSERT_NE(calendarNode, nullptr);
    auto eventHub = calendarNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::string info = " ";
    eventHub->UpdateRequestDataEvent(info);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest005
 * @tc.desc: clickCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest005, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    int32_t calendarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto calendarNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, calendarNodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    ASSERT_NE(calendarNode, nullptr);
    DialogEvent event;
    auto buttonConfirmNode = CalendarDialogView::CreateConfirmNode(calendarNode, event);
    ASSERT_NE(buttonConfirmNode, nullptr);

    auto gesture = buttonConfirmNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->CheckClickActuator();
    gesture->ActClick();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest006
 * @tc.desc: OnSelectedChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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
    json->Put("year", 2001);
    json->Put("month", 2);
    json->Put("day", 20);
    auto info = json->ToString();
    CalendarDialogView calendarDialogView;
    auto changeEvent = [](const std::string& /* info */) {  };
    CalendarSettingData settingData;
    calendarDialogView.OnSelectedChangeEvent(1, info, changeEvent, settingData);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogViewTest007
 * @tc.desc: OnSelectedChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest007, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    const std::string callbackInfo;
    CalendarDialogView calendarDialogView;
    auto changeEvent = [](const std::string& /* info */) {  };
    CalendarSettingData settingData;
    calendarDialogView.OnSelectedChangeEvent(1, callbackInfo, changeEvent, settingData);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerEventHubTest001
 * @tc.desc: SetChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerEventHubTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto calendarpickerEventHub = frameNode->GetEventHub<CalendarPickerEventHub>();
    ASSERT_NE(calendarpickerEventHub, nullptr);
    std::string info = " ";
    calendarpickerEventHub->UpdateInputChangeEvent(info);
    calendarpickerEventHub->UpdateChangeEvent(info);
    calendarpickerEventHub->UpdateOnChangeEvent(info);
    calendarpickerEventHub->FireLayoutChangeEvent();

    auto changeEvent1 = [](const std::string& /* info */) {  };
    auto changeEvent2 = [](const std::string& /* info */) {  };
    auto changeEvent3 = [](const std::string& /* info */) {  };
    calendarpickerEventHub->SetInputChangeEvent(std::move(changeEvent1));
    calendarpickerEventHub->SetChangeEvent(std::move(changeEvent2));
    calendarpickerEventHub->SetOnChangeEvent(std::move(changeEvent3));

    calendarpickerEventHub->UpdateInputChangeEvent(info);
    calendarpickerEventHub->UpdateChangeEvent(info);
    calendarpickerEventHub->UpdateOnChangeEvent(info);
    calendarpickerEventHub->FireLayoutChangeEvent();

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
 * @tc.desc: HandleKeyEvent Function Test
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
    EXPECT_TRUE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest003
 * @tc.desc: AddHotZoneRect Function Test
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
 * @tc.desc: HandleEntryChange Function Test
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
    json->Put("year", 799);
    json->Put("month", 2);
    json->Put("day", 28);
    auto info = json->ToString();

    dialogPattern->HandleEntryChange(info);
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    ASSERT_NE(calendarNode, nullptr);
    auto calendarPattern = calendarNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);
    auto newSelectedDay = calendarPattern->GetSelectedDay();
    EXPECT_EQ(newSelectedDay.GetYear(), 799);
    EXPECT_EQ(newSelectedDay.GetMonth(), 2);
    EXPECT_EQ(newSelectedDay.GetDay(), 28);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest005
 * @tc.desc: IsAtomicNode Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest005, TestSize.Level1)
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

    auto result = dialogPattern->IsAtomicNode();
    EXPECT_TRUE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest006
 * @tc.desc: HandleEntryLayoutChange Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest006, TestSize.Level1)
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
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));;

    dialogPattern->HandleEntryLayoutChange();
    EXPECT_FALSE(dialogPattern->isFirstAddhotZoneRect_);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest007
 * @tc.desc: GetEntryNode & GetDialogOffset Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest007, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    dialogPattern->GetEntryNode();
    dialogPattern->GetDialogOffset();

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    EXPECT_TRUE(dialogPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest008
 * @tc.desc: onKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest008, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto eventHub = calendarDialogNode->GetOrCreateFocusHub();
    ASSERT_NE(eventHub, nullptr);

    KeyEvent keyEventOne(KeyCode::KEY_0, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventOne);

    KeyEvent keyEventOne1(KeyCode::KEY_TAB, KeyAction::DOWN);
    eventHub->ProcessOnKeyEventInternal(keyEventOne1);

    KeyEvent keyEventOne2(KeyCode::KEY_0, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventOne2);

    KeyEvent keyEventTwo(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = true;
    dialogPattern->isCalendarFirstFocused_ = false;
    dialogPattern->focusAreaID_ = 1;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    EXPECT_TRUE(dialogPattern->isCalendarFirstFocused_);

    KeyEvent keyEventTwo1(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = false;
    dialogPattern->isCalendarFirstFocused_ = false;
    dialogPattern->focusAreaID_ = 1;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo1);

    KeyEvent keyEventTwo2(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = true;
    dialogPattern->isCalendarFirstFocused_ = true;
    dialogPattern->focusAreaID_ = 1;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo2);

    KeyEvent keyEventTwo3(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = true;
    dialogPattern->isCalendarFirstFocused_ = false;
    dialogPattern->focusAreaID_ = 3;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo3);

    KeyEvent keyEventThree(KeyCode::KEY_TAB, KeyAction::DOWN);
    dialogPattern->isFocused_ = true;
    dialogPattern->isCalendarFirstFocused_ = true;
    dialogPattern->focusAreaID_ = 3;
    eventHub->ProcessOnKeyEventInternal(keyEventThree);
    EXPECT_TRUE(dialogPattern->HandleKeyEvent(keyEventThree));

    KeyEvent keyEventThree1(KeyCode::KEY_TAB, KeyAction::DOWN);
    dialogPattern->isFocused_ = false;
    dialogPattern->isCalendarFirstFocused_ = true;
    dialogPattern->focusAreaID_ = 3;
    eventHub->ProcessOnKeyEventInternal(keyEventThree1);

    KeyEvent keyEventFour(KeyCode::KEY_TAB, KeyAction::UP);
    dialogPattern->isFocused_ = false;
    eventHub->ProcessOnKeyEventInternal(keyEventFour);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest009
 * @tc.desc: getInnerPaintRectCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest009, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto eventHub = calendarDialogNode->GetOrCreateFocusHub();
    ASSERT_NE(eventHub, nullptr);

    PipelineContext::GetCurrentContext()->isFocusActive_ = true;
    eventHub->focusType_ = FocusType::NODE;
    eventHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    eventHub->PaintFocusState();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest010
 * @tc.desc: event Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest010, TestSize.Level1)
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
    auto contentNode =  AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    auto columnNode =  AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(columnNode, nullptr);

    auto operationsNode =  AceType::DynamicCast<FrameNode>(columnNode->GetLastChild());
    ASSERT_NE(operationsNode, nullptr);
    auto buttonConfirmNode =  AceType::DynamicCast<FrameNode>(operationsNode->GetLastChild());
    ASSERT_NE(buttonConfirmNode, nullptr);

    auto gesture = buttonConfirmNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->CheckClickActuator();
    gesture->ActClick();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest011
 * @tc.desc: InitOnTouchEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest011, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));
    dialogPattern->InitOnTouchEvent();

    TouchEventInfo info("test");
    TouchLocationInfo lInfo(1);
    lInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_front(lInfo);
    dialogPattern->isFocused_ = true;

    dialogPattern->touchListener_->callback_(info);
    EXPECT_TRUE(dialogPattern->isFocused_);

    lInfo.SetTouchType(TouchType::DOWN);
    info.touches_.emplace_front(lInfo);
    dialogPattern->touchListener_->callback_(info);
    EXPECT_FALSE(dialogPattern->isFocused_);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest012
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest012, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    KeyEvent keyEventOne(KeyCode::KEY_0, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 3;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventOne));

    KeyEvent keyEventLeftOne(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 2;
    dialogPattern->HandleKeyEvent(keyEventLeftOne);
    EXPECT_EQ(dialogPattern->focusAreaChildID_, 0);

    KeyEvent keyEventLeftTwo(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 3;
    dialogPattern->HandleKeyEvent(keyEventLeftTwo);
    EXPECT_EQ(dialogPattern->focusAreaChildID_, 2);

    KeyEvent keyEventLeftThree(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 2;
    dialogPattern->HandleKeyEvent(keyEventLeftThree);
    EXPECT_EQ(dialogPattern->focusAreaChildID_, 1);

    KeyEvent keyEventRightOne(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 1;
    dialogPattern->HandleKeyEvent(keyEventRightOne);
    EXPECT_EQ(dialogPattern->focusAreaChildID_, 3);

    KeyEvent keyEventEnter(KeyCode::KEY_ENTER, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 2;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventEnter));

    KeyEvent keyEventCall(KeyCode::KEY_CALL, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 0;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventCall));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest013
 * @tc.desc: HandleTabKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest013, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    KeyEvent keyEventLeft;
    keyEventLeft.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventLeft));
    keyEventLeft.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventLeft));

    KeyEvent keyEventRight;
    keyEventRight.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventRight));
    keyEventRight.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventRight));

    KeyEvent keyEventUp;
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));
    keyEventUp.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventUp));

    KeyEvent keyEventDown;
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));
    keyEventDown.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventDown));

    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_1;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(dialogPattern->HandleCalendarNodeKeyEvent(keyEvent));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest014
 * @tc.desc: HandleTabKeyEvent & UpdateSwiperNodeFocusedDay Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest014, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    dialogPattern->focusedDay_.day = 0;
    dialogPattern->FocusedLastFocusedDay();

    KeyEvent keyEventRight;
    keyEventRight.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventRight));
    keyEventRight.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventRight));
    dialogPattern->FocusedLastFocusedDay();

    KeyEvent keyEventIsPrev;
    keyEventIsPrev.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventIsPrev));
    keyEventIsPrev.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(dialogPattern->HandleCalendarNodeKeyEvent(keyEventIsPrev));
    dialogPattern->FocusedLastFocusedDay();

    CalendarDay focusedDayTrue;
    focusedDayTrue.day = 1;
    focusedDayTrue.month.year = 2000;
    focusedDayTrue.month.month = 1;
    dialogPattern->FocusedLastFocusedDay();
    dialogPattern->UpdateSwiperNodeFocusedDay(focusedDayTrue, true);

    CalendarDay focusedDay;
    focusedDay.day = 1;
    focusedDay.month.year = 2000;
    focusedDay.month.month = 2;
    dialogPattern->FocusedLastFocusedDay();
    dialogPattern->UpdateSwiperNodeFocusedDay(focusedDay, false);

    CalendarDay isPrev;
    isPrev.day = 1;
    isPrev.month.year = 1999;
    isPrev.month.month = 2;
    dialogPattern->FocusedLastFocusedDay();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest015
 * @tc.desc: PaintNonCurrentMonthFocusState Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest015, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    auto currentMonthData = dialogPattern->GetCalendarPattern()->GetCurrentMonthData();

    dialogPattern->PaintNonCurrentMonthFocusState(-1);
    dialogPattern->PaintNonCurrentMonthFocusState(-2);
    dialogPattern->PaintNonCurrentMonthFocusState(currentMonthData.days.size());
    dialogPattern->PaintNonCurrentMonthFocusState(currentMonthData.days.size() + 1);
    dialogPattern->PaintNonCurrentMonthFocusState(0);
    dialogPattern->PaintNonCurrentMonthFocusState(currentMonthData.days.size() - 1);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest016
 * @tc.desc: GetInnerFocusPaintRect Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest016, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    RoundRect paintRect;
    dialogPattern->focusAreaID_ = 1;
    dialogPattern->GetInnerFocusPaintRect(paintRect);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest017
 * @tc.desc: ChangeEntryState Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest017, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 0;
    dialogPattern->ChangeEntryState();

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 3;
    dialogPattern->ChangeEntryState();

    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 2;
    dialogPattern->ChangeEntryState();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest018
 * @tc.desc: HandleTitleArrowsClickEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest018, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // show
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDialogNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDividerNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()));
    CalendarDialogView calendarDialogView;
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(1, 1, 1);
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

    const RefPtr<FrameNode> buttonNode;
    auto currentMonthData = dialogPattern->GetCalendarPattern()->GetCurrentMonthData();
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 0);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 1);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 2);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 3);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 4);
}

/**
 * @tc.name: CalendarDialogPatternTest019
 * @tc.desc: OnDirtyLayoutWrapperSwap Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest019, TestSize.Level1)
{
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();

    dialogPattern->OnDirtyLayoutWrapperSwap(nullptr, true, true);
    dialogPattern->OnDirtyLayoutWrapperSwap(nullptr, true, true);
}

/**
 * @tc.name: CalendarDialogPatternTest020
 * @tc.desc: GetNextMonth Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest020, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    CalendarMonth calendarMax;
    calendarMax.year = 5000;
    calendarMax.month = 12;
    dialogPattern->GetNextMonth(calendarMax);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest021
 * @tc.desc: GetLastMonth Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest021, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

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

    CalendarMonth calendarMin;
    calendarMin.year = 1;
    calendarMin.month = 1;
    dialogPattern->GetLastMonth(calendarMin);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest022
 * @tc.desc: HandleTitleArrowsClickEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest022, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // show
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // SetCalendarPaintProperties
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateCalendarMonthNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>())) // CreateTitleImageNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDialogNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateButtonNode
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<DialogTheme>())) // CreateDividerNode
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<PickerTheme>()));
    CalendarDialogView calendarDialogView;
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(5000, 12, 31);
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

    const RefPtr<FrameNode> buttonNode;
    auto currentMonthData = dialogPattern->GetCalendarPattern()->GetCurrentMonthData();
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 0);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 1);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 2);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 3);
    dialogPattern->HandleTitleArrowsClickEvent(buttonNode, 4);
}

/**
 * @tc.name: CalendarDialogPatternTest023
 * @tc.desc: mouseCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest023, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetHoverState(true);
    auto inputHub = calendarDialogNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    ASSERT_NE(inputHub->mouseEventActuator_, nullptr);
    ASSERT_NE(inputHub->mouseEventActuator_->userCallback_, nullptr);
    ASSERT_NE(inputHub->mouseEventActuator_->userCallback_->onMouseCallback_, nullptr);

    MouseInfo info;
    inputHub->mouseEventActuator_->userCallback_->onMouseCallback_(info);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest024
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest024, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    ASSERT_NE(dialogPattern, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_->onHoverCallback_, nullptr);
    dialogPattern->hoverListener_->onHoverCallback_(false);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest025
 * @tc.desc: HandleEntryNodeHoverEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest025, TestSize.Level1)
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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    Offset globalLocation;
    dialogPattern->HandleEntryNodeHoverEvent(true, globalLocation);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest026
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest026, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto eventHub = calendarDialogNode->GetOrCreateFocusHub();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onBlurInternal_, nullptr);

    eventHub->onBlurInternal_();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarDialogPatternTest027
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest027, TestSize.Level1)
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

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<DialogTheme>()));

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    ASSERT_NE(dialogPattern, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_->onHoverCallback_, nullptr);
    dialogPattern->hoverListener_->onHoverCallback_(true);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutPropertyTest001
 * @tc.desc: Calendar Picker LayoutProperty  Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto clone = layoutProperty->Clone();

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json);
    layoutProperty->Reset();
    clone.Reset();

    ASSERT_NE(json, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutPropertyTest002
 * @tc.desc: CalendarPicker LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_START;
    layoutProperty->ToJsonValue(json);
    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_CENTER;
    layoutProperty->ToJsonValue(json);
    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_END;
    layoutProperty->ToJsonValue(json);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutAlgorithmTest001
 * @tc.desc: CalendarPicker LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutAlgorithmTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto layoutAlgorithmPattern = AceType::DynamicCast<CalendarPickerPattern>(frameNode->GetPattern());
    ASSERT_NE(layoutAlgorithmPattern, nullptr);
    auto calendarPickerLayoutAlgorithm = layoutAlgorithmPattern->CreateLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(calendarPickerLayoutAlgorithm));

    auto contentFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(contentFrameNode, nullptr);
    auto contentLayoutProperty = contentFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    RefPtr<GeometryNode> contentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> contentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        contentFrameNode, contentFrameNodeGeometryNode, contentFrameNode->GetLayoutProperty());
    ASSERT_NE(contentNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(contentNodeLayoutWrapper);

    auto flexFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    ASSERT_NE(flexFrameNode, nullptr);
    auto flexLayoutProperty = flexFrameNode->GetLayoutProperty<FlexLayoutProperty>();
    RefPtr<GeometryNode> flexFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> flexNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        flexFrameNode, flexFrameNodeGeometryNode, flexFrameNode->GetLayoutProperty());
    ASSERT_NE(flexNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(flexNodeLayoutWrapper);

    auto yearNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(0));
    auto yearContentLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> yearContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> yearContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        yearNode, yearContentFrameNodeGeometryNode, yearNode->GetLayoutProperty());
    ASSERT_NE(yearContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(yearContentNodeLayoutWrapper);

    auto textNode1 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(1));
    auto text1ContentLayoutProperty = textNode1->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text1ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text1ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode1, text1ContentFrameNodeGeometryNode, textNode1->GetLayoutProperty());
    ASSERT_NE(text1ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text1ContentNodeLayoutWrapper);

    auto monthNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(2));
    auto monthContentLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> monthContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> monthContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        monthNode, monthContentFrameNodeGeometryNode, monthNode->GetLayoutProperty());
    ASSERT_NE(monthContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(monthContentNodeLayoutWrapper);

    auto textNode2 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(3));
    auto text2ContentLayoutProperty = textNode2->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text2ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text2ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode2, text2ContentFrameNodeGeometryNode, textNode2->GetLayoutProperty());
    ASSERT_NE(text2ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text2ContentNodeLayoutWrapper);

    auto dayNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(4));
    auto dayContentLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> dayContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dayContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dayNode, dayContentFrameNodeGeometryNode, dayNode->GetLayoutProperty());
    ASSERT_NE(dayContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(dayContentNodeLayoutWrapper);

    auto buttonNode1 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(0));
    auto button1LayoutProperty = buttonNode1->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button1NodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        buttonNode1, button1NodeGeometryNode, buttonNode1->GetLayoutProperty());
    ASSERT_NE(button1NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button1NodeLayoutWrapper);

    auto buttonNode2 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(1));
    auto button2LayoutProperty = buttonNode2->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button2NodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        buttonNode2, button2NodeGeometryNode, buttonNode2->GetLayoutProperty());
    ASSERT_NE(button2NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button2NodeLayoutWrapper);

    auto imageNode1 = AceType::DynamicCast<FrameNode>(buttonNode1->GetOrCreateChildByIndex(0));
    auto image1LayoutProperty = imageNode1->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image1NodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        imageNode1, image1NodeGeometryNode, imageNode1->GetLayoutProperty());
    ASSERT_NE(image1NodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(image1NodeLayoutWrapper);

    auto imageNode2 = AceType::DynamicCast<FrameNode>(buttonNode2->GetOrCreateChildByIndex(0));
    auto image2LayoutProperty = imageNode2->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image2NodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        imageNode2, image2NodeGeometryNode, imageNode2->GetLayoutProperty());
    ASSERT_NE(image2NodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(image2NodeLayoutWrapper);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetWidth(10000);
    LayoutConstraintVaildSize.selfIdealSize.SetHeight(25000);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    calendarPickerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutAlgorithmTest002
 * @tc.desc: CalendarPicker Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutAlgorithmTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto searchPattern = AceType::DynamicCast<CalendarPickerPattern>(frameNode->GetPattern());
    ASSERT_NE(searchPattern, nullptr);
    auto searchLayoutAlgorithm = searchPattern->CreateLayoutAlgorithm();
    ASSERT_NE(searchLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(searchLayoutAlgorithm));

    auto contentFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(contentFrameNode, nullptr);
    auto contentLayoutProperty = contentFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    RefPtr<GeometryNode> contentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> contentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        contentFrameNode, contentFrameNodeGeometryNode, contentFrameNode->GetLayoutProperty());
    ASSERT_NE(contentNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(contentNodeLayoutWrapper);

    auto flexFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1));
    ASSERT_NE(flexFrameNode, nullptr);
    auto flexLayoutProperty = flexFrameNode->GetLayoutProperty<FlexLayoutProperty>();
    RefPtr<GeometryNode> flexFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> flexNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        flexFrameNode, flexFrameNodeGeometryNode, flexFrameNode->GetLayoutProperty());
    ASSERT_NE(flexNodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(flexNodeLayoutWrapper);

    auto yearNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(0));
    auto yearContentLayoutProperty = yearNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> yearContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> yearContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        yearNode, yearContentFrameNodeGeometryNode, yearNode->GetLayoutProperty());
    ASSERT_NE(yearContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(yearContentNodeLayoutWrapper);

    auto textNode1 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(1));
    auto text1ContentLayoutProperty = textNode1->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text1ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text1ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode1, text1ContentFrameNodeGeometryNode, textNode1->GetLayoutProperty());
    ASSERT_NE(text1ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text1ContentNodeLayoutWrapper);

    auto monthNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(2));
    auto monthContentLayoutProperty = monthNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> monthContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> monthContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        monthNode, monthContentFrameNodeGeometryNode, monthNode->GetLayoutProperty());
    ASSERT_NE(monthContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(monthContentNodeLayoutWrapper);

    auto textNode2 = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(3));
    auto text2ContentLayoutProperty = textNode2->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> text2ContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> text2ContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        textNode2, text2ContentFrameNodeGeometryNode, textNode2->GetLayoutProperty());
    ASSERT_NE(text2ContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(text2ContentNodeLayoutWrapper);

    auto dayNode = AceType::DynamicCast<FrameNode>(contentFrameNode->GetOrCreateChildByIndex(4));
    auto dayContentLayoutProperty = dayNode->GetLayoutProperty<TextLayoutProperty>();
    RefPtr<GeometryNode> dayContentFrameNodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dayContentNodeLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        dayNode, dayContentFrameNodeGeometryNode, dayNode->GetLayoutProperty());
    ASSERT_NE(dayContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(dayContentNodeLayoutWrapper);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    LayoutConstraintF LayoutConstraintVaildSize;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithmWrapper, nullptr);
    auto calendarPickerLayoutAlgorithm =
        AceType::DynamicCast<CalendarPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);
    calendarPickerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}
} // namespace OHOS::Ace::NG

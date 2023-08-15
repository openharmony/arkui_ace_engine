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

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_FALSE(result);

    pickerPattern->isKeyWaiting_ = true;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_FALSE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}
/**
 * @tc.name: CalendarPickerPatternTest003
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest003, TestSize.Level1)
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

    pickerPattern->HandleBlurEvent();
    EXPECT_EQ(pickerPattern->selected_, CalendarPickerSelectedType::OTHER);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest004
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest004, TestSize.Level1)
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

    pickerPattern->HandleTaskCallback();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest005
 * @tc.desc: HandleKeyEvent Number Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest005, TestSize.Level1)
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

    KeyEvent keyEventOne(KeyCode::KEY_1, KeyAction::DOWN);
    auto result = pickerPattern->HandleKeyEvent(keyEventOne);
    EXPECT_TRUE(result);

    KeyEvent keyEvenTwo(KeyCode::KEY_9, KeyAction::DOWN);
    result = pickerPattern->HandleKeyEvent(keyEvenTwo);
    EXPECT_TRUE(result);

    result = pickerPattern->HandleKeyEvent(keyEvenTwo);
    EXPECT_TRUE(result);

    result = pickerPattern->HandleKeyEvent(keyEvenTwo);
    EXPECT_TRUE(result);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest006
 * @tc.desc: IsDialogShow Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest006, TestSize.Level1)
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

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    layoutWrapper->skipMeasureContent_ = std::make_optional<bool>(true);
    pickerPattern->SetDialogShow(true);
    EXPECT_TRUE(pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));

    pickerPattern->SetDialogShow(false);
    EXPECT_TRUE(pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest007
 * @tc.desc: SetCalendarEdgeAlign Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest007, TestSize.Level1)
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

    auto result = pickerPattern->IsAtomicNode();
    EXPECT_TRUE(result);

    pickerPattern->SetCalendarEdgeAlign(CalendarEdgeAlign::EDGE_ALIGN_START);
    pickerPattern->GetCalendarEdgeAlign();

    DimensionOffset offset;
    pickerPattern->GetCalendarDialogOffset();
    pickerPattern->SetCalendarDialogOffset(offset);
    pickerPattern->GetCalendarDialogOffset();

    CalendarSettingData data;
    pickerPattern->GetCalendarData();
    pickerPattern->SetCalendarData(data);
    pickerPattern->GetCalendarData();

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    EXPECT_TRUE(pickerPattern->HasButtonFlexNode());
    EXPECT_TRUE(pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest008
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest008, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    ASSERT_NE(pickerPattern->hoverListener_, nullptr);
    ASSERT_NE(pickerPattern->hoverListener_->onHoverCallback_, nullptr);
    pickerPattern->hoverListener_->onHoverCallback_(true);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest010
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest010, TestSize.Level1)
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

    pickerPattern->SetDialogShow(true);
    pickerPattern->HandleBlurEvent();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest011
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest011, TestSize.Level1)
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
    KeyEvent keyEventOne(KeyCode::KEY_SPACE, KeyAction::UP);
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(keyEventOne);

    KeyEvent keyEventTwo(KeyCode::KEY_TAB, KeyAction::DOWN);
    pickerPattern->isFirtFocus_ = false;
    EXPECT_FALSE(pickerPattern->HandleKeyEvent(keyEventTwo));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest012
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest012, TestSize.Level1)
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
    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->SetDialogShow(true);
    EXPECT_TRUE(pickerPattern->HandleFocusEvent(keyEventOne));

    KeyEvent keyEventTwo;
    keyEventTwo.code = KeyCode::KEY_TAB,
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->SetDialogShow(false);
    EXPECT_TRUE(pickerPattern->HandleFocusEvent(keyEventTwo));

    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    KeyEvent keyEventThree;
    keyEventThree.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(pickerPattern->HandleFocusEvent(keyEventThree));

    pickerPattern->selected_ = CalendarPickerSelectedType::OTHER;
    KeyEvent keyEventFour;
    keyEventFour.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(pickerPattern->HandleFocusEvent(keyEventFour));

    KeyEvent keyEventFive;
    keyEventFive.code = KeyCode::KEY_ENTER;
    pickerPattern->SetDialogShow(false);
    pickerPattern->HandleFocusEvent(keyEventFive);
    pickerPattern->SetDialogShow(true);
    pickerPattern->HandleFocusEvent(keyEventFive);

    KeyEvent keyEventSix;
    keyEventSix.code = KeyCode::KEY_DEL;
    pickerPattern->HandleFocusEvent(keyEventSix);

    KeyEvent keyEventSeven;
    keyEventSeven.action = KeyAction::UP;
    pickerPattern->HandleFocusEvent(keyEventSeven);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest013
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest013, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(2000));

    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 10);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleYearKeyEvent(10);
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(10));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 0);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_FALSE(pickerPattern->HandleYearKeyEvent(0));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest014
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest014, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 999);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(999));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest015
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest015, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 800);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(799));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest016
 * @tc.desc: HandleMonthKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest016, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 10);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_FALSE(pickerPattern->HandleMonthKeyEvent(10));

    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 3);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(3);
    EXPECT_FALSE(pickerPattern->isKeyWaiting_);

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 0);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_FALSE(pickerPattern->HandleMonthKeyEvent(0));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 10);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(10);
    EXPECT_TRUE(pickerPattern->isKeyWaiting_);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest017
 * @tc.desc: HandleMonthKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest017, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 799);
    json->Put("month", 1);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleMonthKeyEvent(1);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest018
 * @tc.desc: HandleDayKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest018, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 31);
    pickerPattern->SetDate(json->ToString());
    EXPECT_FALSE(pickerPattern->HandleDayKeyEvent(31));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 0);
    pickerPattern->SetDate(json->ToString());
    EXPECT_FALSE(pickerPattern->HandleDayKeyEvent(0));

    pickerPattern->isKeyWaiting_ = false;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleDayKeyEvent(1);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest019
 * @tc.desc: HandleDayKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest019, TestSize.Level1)
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

    auto json = JsonUtil::Create(true);
    pickerPattern->isKeyWaiting_ = true;
    json->Put("year", 2000);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleDayKeyEvent(1);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest020
 * @tc.desc: HandleNumberKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest020, TestSize.Level1)
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

    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_STAR;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventOne));

    KeyEvent keyEventTwo;
    keyEventTwo.code = KeyCode::KEY_NUMPAD_0;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventTwo));

    KeyEvent keyEventThree;
    keyEventThree.code = KeyCode::KEY_0;
    EXPECT_FALSE(pickerPattern->HandleNumberKeyEvent(keyEventThree));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest021
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest021, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest022
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest022, TestSize.Level1)
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

    pickerPattern->taskCount_ = 1;
    pickerPattern->isKeyWaiting_ = true;
    auto json = JsonUtil::Create(true);
    json->Put("year", 801);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    pickerPattern->HandleTaskCallback();
    EXPECT_FALSE(pickerPattern->isKeyWaiting_);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest023
 * @tc.desc: HandleTextHoverEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest023, TestSize.Level1)
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
    pickerPattern->HandleTextHoverEvent(true, 0);

    pickerPattern->selected_ = CalendarPickerSelectedType::MONTH;
    pickerPattern->HandleTextHoverEvent(true, 2);

    pickerPattern->selected_ = CalendarPickerSelectedType::DAY;
    pickerPattern->HandleTextHoverEvent(true, 4);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    pickerPattern->HandleTextHoverEvent(false, 4);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest024
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest024, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest025
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest025, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest026
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest026, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest027
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest027, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest028
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest028, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest029
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest029, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest030
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest030, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest031
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest031, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest032
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest032, TestSize.Level1)
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
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest033
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest033, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest034
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest034, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_CENTER);
    pickerPattern->CalculateDialogOffset();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest035
 * @tc.desc: CalculateDialogOffset Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest035, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    CreateCalendarPicker(themeManager);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    layoutProperty->UpdateDialogAlignType(CalendarEdgeAlign::EDGE_ALIGN_END);
    pickerPattern->CalculateDialogOffset();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest036
 * @tc.desc: GetEntryDateInfo Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest036, TestSize.Level1)
{
    auto pickerPattern = AceType::MakeRefPtr<CalendarPickerPattern>();

    const std::string info = " ";
    pickerPattern->GetEntryDateInfo();
    pickerPattern->SetDate(info);
    pickerPattern->FlushTextStyle();
}

/**
 * @tc.name: CalendarPickerPatternTest037
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest037, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest038
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest038, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest039
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest039, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest040
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest040, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest041
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest041, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest042
 * @tc.desc: HandleSubButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest042, TestSize.Level1)
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

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest043
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest043, TestSize.Level1)
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

    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->onBlurInternal_, nullptr);

    focusHub->onBlurInternal_();

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest044
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest044, TestSize.Level1)
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

    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    KeyEvent event;
    EXPECT_FALSE(pickerPattern->HandleBlurEvent(event));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest045
 * @tc.desc: PostTaskToUI Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest045, TestSize.Level1)
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

    auto context = frameNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    std::function<void()> task;
    pickerPattern->PostTaskToUI(task);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest046
 * @tc.desc: OnWindowSizeChanged Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest046, TestSize.Level1)
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

    pickerPattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    pickerPattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::RECOVER);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}
/**
 * @tc.name: CalendarPickerPatternTest047
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest047, TestSize.Level1)
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
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_TAB,
    pickerPattern->isFirtFocus_ = false;
    pickerPattern->SetDialogShow(false);
    EXPECT_FALSE(pickerPattern->HandleFocusEvent(keyEvent));

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest048
 * @tc.desc: HandleButtonTouchEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest048, TestSize.Level1)
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
    bool isPressed = true;
    pickerPattern->HandleButtonTouchEvent(isPressed, 0);

    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: CalendarPickerPatternTest049
 * @tc.desc: ShowDialog Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest049, TestSize.Level1)
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
    pickerPattern->SetDialogShow(true);
    pickerPattern->ShowDialog();

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
 * @tc.desc: Create Calendar Dialog Without EntryNode.
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
    EXPECT_TRUE(result);

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

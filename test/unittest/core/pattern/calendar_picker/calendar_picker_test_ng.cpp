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
constexpr int32_t YEAR_INDEX = 0;
constexpr int32_t MONTH_INDEX = 2;
} // namespace
class CalendarPickerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarPickerTestNg::SetUpTestCase()
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

void CalendarPickerTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

void CalendarPickerTestNg::CreateCalendarPicker()
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

RefPtr<FrameNode> CalendarPickerTestNg::CalendarDialogShow(RefPtr<FrameNode> entryNode)
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
 * @tc.name: CalendarModelNGTest001
 * @tc.desc: Create Calendar Picker Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar Picker
     * @tc.expected: step1. Create Calendar successfully
     */
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
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

    auto result = gesture->ActClick();
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Handle KEY_TAB on Calendar Picker
     * @tc.expected: step3. Focus changed
     */
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
}

/**
 * @tc.name: CalendarPickerModelNGTest002
 * @tc.desc: SetTextStyle Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest002, TestSize.Level1)
{
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension(100);
    calendarPickerModel.SetTextStyle(textStyle);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
}

/**
 * @tc.name: CalendarPickerModelNGTest003
 * @tc.desc: SetTextStyle Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest003, TestSize.Level1)
{
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    PickerTextStyle textStyle;
    textStyle.fontSize = Dimension();
    calendarPickerModel.SetTextStyle(textStyle);

    textStyle.fontSize = Dimension(100);
    calendarPickerModel.SetTextStyle(textStyle);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
}

/**
 * @tc.name: CalendarPickerModelNGTest004
 * @tc.desc: Create Calendar Picker Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest004, TestSize.Level1)
{
    const std::string language = "false";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);

    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    json->Put("year", 2000);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());
    auto yearTextNode = calendarPickerModel.GetYearNode(AceType::RawPtr(frameNode));
    auto yearTextLayoutProperty = yearTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(yearTextLayoutProperty->GetContentValue(), u"2000");

    auto monthTextNode = calendarPickerModel.GetMonthNode(AceType::RawPtr(frameNode));
    auto monthTextLayoutProperty = monthTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(monthTextLayoutProperty->GetContentValue(), u"02");

    auto dayTextNode = calendarPickerModel.GetDayNode(AceType::RawPtr(frameNode));
    auto dayTextLayoutProperty = dayTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(dayTextLayoutProperty->GetContentValue(), u"29");
}

/**
 * @tc.name: CalendarPickerModelNGTest005
 * @tc.desc: Create Calendar Picker Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest005, TestSize.Level1)
{
    const std::string language = "zh";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);

    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    json->Put("year", 2000);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());

    auto yearTextNode = calendarPickerModel.GetYearNode(AceType::RawPtr(frameNode));
    auto yearTextLayoutProperty = yearTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(yearTextLayoutProperty->GetContentValue(), u"2000");

    auto monthTextNode = calendarPickerModel.GetMonthNode(AceType::RawPtr(frameNode));
    auto monthTextLayoutProperty = monthTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(monthTextLayoutProperty->GetContentValue(), u"02");

    auto dayTextNode = calendarPickerModel.GetDayNode(AceType::RawPtr(frameNode));
    auto dayTextLayoutProperty = dayTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(dayTextLayoutProperty->GetContentValue(), u"29");
}

/**
 * @tc.name: CalendarPickerModelNGTest006
 * @tc.desc: Create Calendar Picker Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest006, TestSize.Level1)
{
    const std::string language = "ug";
    const std::string countryOrRegion = "";
    const std::string script = "";
    const std::string keywordsAndValues = "";
    const std::string selected = "";
    Localization::GetInstance()->SetLocaleImpl(language, countryOrRegion, script, selected, keywordsAndValues);

    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;

    calendarPickerModel.Create(settingData);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto json = JsonUtil::Create(true);
    json->Put("year", 2000);
    json->Put("month", 2);
    json->Put("day", 29);
    pickerPattern->SetDate(json->ToString());

    auto yearTextNode = calendarPickerModel.GetYearNode(AceType::RawPtr(frameNode));
    auto yearTextLayoutProperty = yearTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(yearTextLayoutProperty->GetContentValue(), u"2000");

    auto monthTextNode = calendarPickerModel.GetMonthNode(AceType::RawPtr(frameNode));
    auto monthTextLayoutProperty = monthTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(monthTextLayoutProperty->GetContentValue(), u"02");

    auto dayTextNode = calendarPickerModel.GetDayNode(AceType::RawPtr(frameNode));
    auto dayTextLayoutProperty = dayTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(dayTextLayoutProperty->GetContentValue(), u"29");
}

/**
 * @tc.name: CalendarPickerPatternTest001
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

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
}

/**
 * @tc.name: CalendarPickerPatternTest002
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest002, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

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
}
/**
 * @tc.name: CalendarPickerPatternTest003
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest003, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->HandleBlurEvent();
    EXPECT_EQ(pickerPattern->selected_, CalendarPickerSelectedType::OTHER);
}

/**
 * @tc.name: CalendarPickerPatternTest004
 * @tc.desc: HandleTaskCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest004, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->HandleTaskCallback();
}

/**
 * @tc.name: CalendarPickerPatternTest005
 * @tc.desc: HandleKeyEvent Number Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest005, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

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
}

/**
 * @tc.name: CalendarPickerPatternTest006
 * @tc.desc: IsDialogShow Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest006, TestSize.Level1)
{
    CreateCalendarPicker();

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
}

/**
 * @tc.name: CalendarPickerPatternTest007
 * @tc.desc: SetCalendarEdgeAlign Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest007, TestSize.Level1)
{
    CreateCalendarPicker();

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
}

/**
 * @tc.name: CalendarPickerPatternTest008
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest008, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    ASSERT_NE(pickerPattern->hoverListener_, nullptr);
    ASSERT_NE(pickerPattern->hoverListener_->onHoverCallback_, nullptr);
    pickerPattern->hoverListener_->onHoverCallback_(true);
}

/**
 * @tc.name: CalendarPickerPatternTest010
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest010, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->SetDialogShow(true);
    pickerPattern->HandleBlurEvent();
}

/**
 * @tc.name: CalendarPickerPatternTest011
 * @tc.desc: HandleBlurEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest011, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    KeyEvent keyEventOne(KeyCode::KEY_SPACE, KeyAction::UP);
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->HandleKeyEvent(keyEventOne);

    KeyEvent keyEventTwo(KeyCode::KEY_TAB, KeyAction::DOWN);
    pickerPattern->isFirtFocus_ = false;
    EXPECT_FALSE(pickerPattern->HandleKeyEvent(keyEventTwo));
}

/**
 * @tc.name: CalendarPickerPatternTest012
 * @tc.desc: HandleFocusEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest012, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    pickerPattern->selected_ = CalendarPickerSelectedType::YEAR;
    KeyEvent keyEventOne;
    keyEventOne.code = KeyCode::KEY_TAB;
    pickerPattern->isFirtFocus_ = true;
    pickerPattern->SetDialogShow(true);
    EXPECT_TRUE(pickerPattern->HandleFocusEvent(keyEventOne));

    KeyEvent keyEventTwo;
    keyEventTwo.code = KeyCode::KEY_TAB, pickerPattern->isFirtFocus_ = true;
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
}

/**
 * @tc.name: CalendarPickerPatternTest013
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest013, TestSize.Level1)
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
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(0));
}

/**
 * @tc.name: CalendarPickerPatternTest014
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest014, TestSize.Level1)
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
    json->Put("year", 999);
    json->Put("month", 1);
    json->Put("day", 1);
    pickerPattern->SetDate(json->ToString());
    EXPECT_TRUE(pickerPattern->HandleYearKeyEvent(999));
}

/**
 * @tc.name: CalendarPickerPatternTest015
 * @tc.desc: HandleYearKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest015, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest016, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest017, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest018, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest019, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest020, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest021, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest022, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest023, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest024, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest025, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest026, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest027, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest028, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest029, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest030, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest031, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest032, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest033, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest034, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest035, TestSize.Level1)
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
 * @tc.name: CalendarPickerPatternTest036
 * @tc.desc: GetEntryDateInfo Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest036, TestSize.Level1)
{
    auto pickerPattern = AceType::MakeRefPtr<CalendarPickerPattern>();

    const std::string info = " ";
    auto oldInfo = pickerPattern->GetEntryDateInfo();
    pickerPattern->SetDate(info);
    pickerPattern->FlushTextStyle();
    auto newInfo = pickerPattern->GetEntryDateInfo();
    EXPECT_EQ(oldInfo, newInfo);
}

/**
 * @tc.name: CalendarPickerPatternTest037
 * @tc.desc: HandleAddButtonClick Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest037, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest038, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest039, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest040, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest041, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest042, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest043, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest044, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest045, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest046, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest047, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest048, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest049, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest050, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest051, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest052, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest053, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest054, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest055, TestSize.Level1)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest056, TestSize.Level1)
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

/**
 * @tc.name: CalendarDialogViewTest001
 * @tc.desc: Calendar Dialog Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    TouchEventInfo info("touch");
    TouchLocationInfo touchInfo1(1);
    touchInfo1.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchInfo1));
    dialogPattern->touchListener_->GetTouchEventCallback()(info);

    auto gesture = calendarDialogNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);

    auto result = gesture->ActClick();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogViewTest002
 * @tc.desc: Create Calendar Dialog Without EntryNode Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest002, TestSize.Level1)
{
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = calendarDialogView.Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = calendarDialogView.Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto calendarNode = dialogPattern->GetCalendarFrameNode();
    ASSERT_NE(calendarNode, nullptr);
    auto eventHub = calendarNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::string info = " ";
    eventHub->UpdateRequestDataEvent(info);
}

/**
 * @tc.name: CalendarDialogViewTest005
 * @tc.desc: clickCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest005, TestSize.Level1)
{
    int32_t calendarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto calendarNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, calendarNodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    ASSERT_NE(calendarNode, nullptr);
    DialogEvent event;
    std::vector<ButtonInfo> buttonInfos;
    auto buttonConfirmNode = CalendarDialogView::CreateConfirmNode(calendarNode, event, buttonInfos);
    ASSERT_NE(buttonConfirmNode, nullptr);

    auto gesture = buttonConfirmNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->CheckClickActuator();
    gesture->ActClick();
}

/**
 * @tc.name: CalendarDialogViewTest006
 * @tc.desc: OnSelectedChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest006, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto json = JsonUtil::Create(true);
    json->Put("year", 2001);
    json->Put("month", 2);
    json->Put("day", 20);
    auto info = json->ToString();
    CalendarDialogView calendarDialogView;
    auto changeEvent = [](const std::string& /* info */) {};
    CalendarSettingData settingData;
    calendarDialogView.OnSelectedChangeEvent(1, info, changeEvent, settingData);
}

/**
 * @tc.name: CalendarDialogViewTest007
 * @tc.desc: OnSelectedChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest007, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    const std::string callbackInfo;
    CalendarDialogView calendarDialogView;
    auto changeEvent = [](const std::string& /* info */) {};
    CalendarSettingData settingData;
    calendarDialogView.OnSelectedChangeEvent(1, callbackInfo, changeEvent, settingData);
}

/**
 * @tc.name: CalendarDialogViewTest008
 * @tc.desc: Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. mock PlatformVersion VERSION_ELEVEN.
     * @tc.expected: mock successfully.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step2. create dialogNodeProps.
     * @tc.expected: the dialogNodeProps created successfully.
     */
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = true;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(2000, 1, 1);
    settingData.selectedDate = selectedDate;
    settingData.dayRadius = TEST_SETTING_RADIUS;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    /**
     * @tc.steps: step3. execute CalendarDialogView::Show.
     * @tc.expected: show successfully.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = CalendarDialogView::Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    /**
     * @tc.steps: step4. get dialogNode's grandsonNode.
     * @tc.expected: getNode successfully.
     */
    auto contentNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    ASSERT_NE(theme, nullptr);
    /**
     * @tc.steps: step5. test dialogNode's RenderContext's BackBlurStyle value.
     * @tc.expected: equal static_cast<BlurStyle>(theme->GetCalendarPickerDialogBlurStyle()).
     */
    EXPECT_EQ(contentNode->GetRenderContext()->GetBackBlurStyle()->blurStyle,
        static_cast<BlurStyle>(theme->GetCalendarPickerDialogBlurStyle()));
}

/**
 * @tc.name: CalendarDialogViewTest009
 * @tc.desc: Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. mock PlatformVersion VERSION_ELEVEN.
     * @tc.expected: mock successfully.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step2. create dialogNodeProps.
     * @tc.expected: the dialogNodeProps created successfully.
     */
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = true;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    properties.backgroundBlurStyle = static_cast<int32_t>(BlurStyle::REGULAR);
    auto selectedDate = PickerDate(2000, 1, 1);
    settingData.selectedDate = selectedDate;
    settingData.dayRadius = TEST_SETTING_RADIUS;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    /**
     * @tc.steps: step3. execute CalendarDialogView::Show.
     * @tc.expected: show successfully.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = CalendarDialogView::Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    /**
     * @tc.steps: step4. get dialogNode's grandsonNode.
     * @tc.expected: getNode successfully.
     */
    auto contentNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(contentNode, nullptr);
    /**
     * @tc.steps: step5. test dialogNode's RenderContext's BackBlurStyle value.
     * @tc.expected: equal REGULAR.
     */
    EXPECT_EQ(contentNode->GetRenderContext()->GetBackBlurStyle()->blurStyle, BlurStyle::REGULAR);
}

/**
 * @tc.name: CalendarPickerEventHubTest001
 * @tc.desc: SetChangeEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerEventHubTest001, TestSize.Level1)
{
    CreateCalendarPicker();

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

    auto changeEvent1 = [](const std::string& /* info */) {};
    auto changeEvent2 = [](const std::string& /* info */) {};
    auto changeEvent3 = [](const std::string& /* info */) {};
    calendarpickerEventHub->SetInputChangeEvent(std::move(changeEvent1));
    calendarpickerEventHub->SetChangeEvent(std::move(changeEvent2));
    calendarpickerEventHub->SetOnChangeEvent(std::move(changeEvent3));

    calendarpickerEventHub->UpdateInputChangeEvent(info);
    calendarpickerEventHub->UpdateChangeEvent(info);
    calendarpickerEventHub->UpdateOnChangeEvent(info);
    calendarpickerEventHub->FireLayoutChangeEvent();
}

/**
 * @tc.name: CalendarDialogPatternTest001
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

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
}

/**
 * @tc.name: CalendarDialogPatternTest002
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest002, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

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
}

/**
 * @tc.name: CalendarDialogPatternTest003
 * @tc.desc: AddHotZoneRect Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest003, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->AddHotZoneRect();
}

/**
 * @tc.name: CalendarDialogPatternTest004
 * @tc.desc: HandleEntryChange Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest004, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
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
}

/**
 * @tc.name: CalendarDialogPatternTest005
 * @tc.desc: IsAtomicNode Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest005, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto result = dialogPattern->IsAtomicNode();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CalendarDialogPatternTest006
 * @tc.desc: HandleEntryLayoutChange Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest006, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->HandleEntryLayoutChange();
    EXPECT_FALSE(dialogPattern->isFirstAddhotZoneRect_);
}

/**
 * @tc.name: CalendarDialogPatternTest007
 * @tc.desc: GetEntryNode & GetDialogOffset Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest007, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->GetDialogOffset();

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    EXPECT_TRUE(dialogPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));
}

/**
 * @tc.name: CalendarDialogPatternTest008
 * @tc.desc: onKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest008, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

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
    dialogPattern->focusAreaID_ = 2;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    EXPECT_TRUE(dialogPattern->isCalendarFirstFocused_);

    KeyEvent keyEventTwo1(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = false;
    dialogPattern->isCalendarFirstFocused_ = false;
    dialogPattern->focusAreaID_ = 2;
    eventHub->ProcessOnKeyEventInternal(keyEventTwo1);

    KeyEvent keyEventTwo2(KeyCode::KEY_TAB, KeyAction::UP);
    eventHub->ProcessOnKeyEventInternal(keyEventTwo);
    dialogPattern->isFocused_ = true;
    dialogPattern->isCalendarFirstFocused_ = true;
    dialogPattern->focusAreaID_ = 2;
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
}

/**
 * @tc.name: CalendarDialogPatternTest009
 * @tc.desc: getInnerPaintRectCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest009, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto eventHub = calendarDialogNode->GetOrCreateFocusHub();
    ASSERT_NE(eventHub, nullptr);

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    eventHub->focusType_ = FocusType::NODE;
    eventHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    eventHub->PaintFocusState();
}

/**
 * @tc.name: CalendarDialogPatternTest010
 * @tc.desc: event Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest010, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(columnNode, nullptr);

    auto operationsNode = AceType::DynamicCast<FrameNode>(columnNode->GetLastChild());
    ASSERT_NE(operationsNode, nullptr);
    auto buttonConfirmNode = AceType::DynamicCast<FrameNode>(operationsNode->GetLastChild());
    ASSERT_NE(buttonConfirmNode, nullptr);

    auto gesture = buttonConfirmNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    gesture->CheckClickActuator();
    gesture->ActClick();
}

/**
 * @tc.name: CalendarDialogPatternTest011
 * @tc.desc: InitOnTouchEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest011, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
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
}

/**
 * @tc.name: CalendarDialogPatternTest012
 * @tc.desc: HandleKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest012, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    KeyEvent keyEventOne(KeyCode::KEY_0, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 3;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventOne));

    KeyEvent keyEventLeftOne(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 3;
    dialogPattern->focusAreaChildID_ = 2;
    dialogPattern->HandleKeyEvent(keyEventLeftOne);
    EXPECT_EQ(dialogPattern->focusAreaChildID_, 0);

    KeyEvent keyEventLeftTwo(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 3;
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
    dialogPattern->focusAreaID_ = 3;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventEnter));

    KeyEvent keyEventCall(KeyCode::KEY_CALL, KeyAction::DOWN);
    dialogPattern->focusAreaID_ = 0;
    EXPECT_FALSE(dialogPattern->HandleKeyEvent(keyEventCall));
}

/**
 * @tc.name: CalendarDialogPatternTest013
 * @tc.desc: HandleTabKeyEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest013, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
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
}

/**
 * @tc.name: CalendarDialogPatternTest014
 * @tc.desc: HandleTabKeyEvent & UpdateSwiperNodeFocusedDay Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest014, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
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
}

/**
 * @tc.name: CalendarDialogPatternTest015
 * @tc.desc: PaintNonCurrentMonthFocusState Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest015, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
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
}

/**
 * @tc.name: CalendarDialogPatternTest016
 * @tc.desc: GetInnerFocusPaintRect Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest016, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    RoundRect paintRect;
    dialogPattern->focusAreaID_ = 1;
    dialogPattern->GetInnerFocusPaintRect(paintRect);
}

/**
 * @tc.name: CalendarDialogPatternTest017
 * @tc.desc: ChangeEntryState Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest017, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 0;
    dialogPattern->ChangeEntryState();

    dialogPattern->focusAreaID_ = 0;
    dialogPattern->focusAreaChildID_ = 3;
    dialogPattern->ChangeEntryState();

    dialogPattern->focusAreaID_ = 2;
    dialogPattern->focusAreaChildID_ = 2;
    dialogPattern->ChangeEntryState();
}

/**
 * @tc.name: CalendarDialogPatternTest018
 * @tc.desc: HandleTitleArrowsClickEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest018, TestSize.Level1)
{
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = calendarDialogView.Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto currentMonthData = dialogPattern->GetCalendarPattern()->GetCurrentMonthData();
    dialogPattern->HandleTitleArrowsClickEvent(0);
    dialogPattern->HandleTitleArrowsClickEvent(1);
    dialogPattern->HandleTitleArrowsClickEvent(2);
    dialogPattern->HandleTitleArrowsClickEvent(3);
    dialogPattern->HandleTitleArrowsClickEvent(4);
}

/**
 * @tc.name: CalendarDialogPatternTest019
 * @tc.desc: OnDirtyLayoutWrapperSwap Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest019, TestSize.Level1)
{
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();

    EXPECT_TRUE(dialogPattern->OnDirtyLayoutWrapperSwap(nullptr, true, true));
    EXPECT_TRUE(dialogPattern->OnDirtyLayoutWrapperSwap(nullptr, true, true));
}

/**
 * @tc.name: CalendarDialogPatternTest020
 * @tc.desc: GetNextMonth Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest020, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    CalendarMonth calendarMax;
    calendarMax.year = 5000;
    calendarMax.month = 12;
    dialogPattern->GetNextMonth(calendarMax);
}

/**
 * @tc.name: CalendarDialogPatternTest021
 * @tc.desc: GetLastMonth Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest021, TestSize.Level1)
{
    CreateCalendarPicker();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    CalendarMonth calendarMin;
    calendarMin.year = 1;
    calendarMin.month = 1;
    dialogPattern->GetLastMonth(calendarMin);
}

/**
 * @tc.name: CalendarDialogPatternTest022
 * @tc.desc: HandleTitleArrowsClickEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest022, TestSize.Level1)
{
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = calendarDialogView.Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);
    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto currentMonthData = dialogPattern->GetCalendarPattern()->GetCurrentMonthData();
    dialogPattern->HandleTitleArrowsClickEvent(0);
    dialogPattern->HandleTitleArrowsClickEvent(1);
    dialogPattern->HandleTitleArrowsClickEvent(2);
    dialogPattern->HandleTitleArrowsClickEvent(3);
    dialogPattern->HandleTitleArrowsClickEvent(4);
}

/**
 * @tc.name: CalendarDialogPatternTest023
 * @tc.desc: mouseCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest023, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

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
}

/**
 * @tc.name: CalendarDialogPatternTest024
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest024, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    ASSERT_NE(dialogPattern, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_->onHoverCallback_, nullptr);
    dialogPattern->hoverListener_->onHoverCallback_(false);
}

/**
 * @tc.name: CalendarDialogPatternTest025
 * @tc.desc: HandleEntryNodeHoverEvent Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest025, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    Offset globalLocation;
    dialogPattern->HandleEntryNodeHoverEvent(true, globalLocation);
}

/**
 * @tc.name: CalendarDialogPatternTest026
 * @tc.desc: blurTask Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest026, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    auto eventHub = calendarDialogNode->GetOrCreateFocusHub();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->onBlurInternal_, nullptr);

    eventHub->onBlurInternal_();
}

/**
 * @tc.name: CalendarDialogPatternTest027
 * @tc.desc: hoverCallback Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest027, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);

    auto contentWrapper = dialogNode->GetChildAtIndex(0);
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);

    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);

    ASSERT_NE(dialogPattern, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_, nullptr);
    ASSERT_NE(dialogPattern->hoverListener_->onHoverCallback_, nullptr);
    dialogPattern->hoverListener_->onHoverCallback_(true);
}

/**
 * @tc.name: CalendarDialogPatternTest028
 * @tc.desc: UpdateDialogBackgroundColor Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateCalendarPicker.
     * @tc.expected: create successfully.
     */
    CreateCalendarPicker();

    /**
     * @tc.steps: step2. create dialogPattern.
     * @tc.expected: create successfully.
     */
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);
    auto dialogNode = CalendarDialogShow(AceType::DynamicCast<FrameNode>(element));
    EXPECT_EQ(dialogNode->GetTag(), V2::DIALOG_ETS_TAG);
    auto contentWrapper = AceType::DynamicCast<FrameNode>(dialogNode->GetChildAtIndex(0));
    ASSERT_NE(contentWrapper, nullptr);
    auto calendarDialogNode = AceType::DynamicCast<FrameNode>(contentWrapper->GetChildAtIndex(0));
    ASSERT_NE(calendarDialogNode, nullptr);
    auto dialogPattern = calendarDialogNode->GetPattern<CalendarDialogPattern>();
    /**
     * @tc.steps: step3. mock PlatformVersion VERSION_ELEVEN and CalendarTheme.
     * @tc.expected: mock successfully.
     */
    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    /**
     * @tc.steps: step4. execute UpdateDialogBackgroundColor.
     * @tc.expected: execute successfully.
     */
    dialogPattern->UpdateDialogBackgroundColor();
    /**
     * @tc.steps: step5. test calendarDialogNode's RenderContext's BackgroundColorValue value.
     * @tc.expected: equal TRANSPARENT.
     */
    EXPECT_EQ(contentWrapper->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).ColorToString(),
        Color::TRANSPARENT.ColorToString());
    /**
     * @tc.steps: step6. mock PlatformVersion VERSION_TEN.
     * @tc.expected: mock successfully.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    /**
     * @tc.steps: step7. test calendarDialogNode's RenderContext's BackgroundColorValue value.
     * @tc.expected: equal themeColor.
     */
    dialogPattern->UpdateDialogBackgroundColor();
    EXPECT_EQ(contentWrapper->GetRenderContext()->GetBackgroundColorValue(Color::TRANSPARENT).ColorToString(),
        theme->GetDialogBackgroundColor().ColorToString());
}

/**
 * @tc.name: CalendarPickerTextDirectionTest001
 * @tc.desc: CalendarPicker TextDirection Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerTextDirectionTest001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto contentFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    ASSERT_NE(contentFrameNode, nullptr);
    auto contentLayoutProperty = contentFrameNode->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(contentLayoutProperty, nullptr);
    EXPECT_EQ(contentLayoutProperty->GetLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: CalendarPickerLayoutPropertyTest001
 * @tc.desc: Calendar Picker LayoutProperty  Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest001, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto clone = layoutProperty->Clone();

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json, filter);
    layoutProperty->Reset();
    clone.Reset();

    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutPropertyTest002
 * @tc.desc: CalendarPicker LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest002, TestSize.Level1)
{
    CreateCalendarPicker();

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_START;
    layoutProperty->ToJsonValue(json, filter);
    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_CENTER;
    layoutProperty->ToJsonValue(json, filter);
    layoutProperty->propDialogAlignType_ = CalendarEdgeAlign::EDGE_ALIGN_END;
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: CalendarPickerLayoutAlgorithmTest001
 * @tc.desc: CalendarPicker LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutAlgorithmTest001, TestSize.Level1)
{
    CreateCalendarPicker();

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
    RefPtr<LayoutWrapperNode> dayContentNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dayNode, dayContentFrameNodeGeometryNode, dayNode->GetLayoutProperty());
    ASSERT_NE(dayContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(dayContentNodeLayoutWrapper);

    auto buttonNode1 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(0));
    auto button1LayoutProperty = buttonNode1->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button1NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(buttonNode1, button1NodeGeometryNode, buttonNode1->GetLayoutProperty());
    ASSERT_NE(button1NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button1NodeLayoutWrapper);

    auto buttonNode2 = AceType::DynamicCast<FrameNode>(flexFrameNode->GetOrCreateChildByIndex(1));
    auto button2LayoutProperty = buttonNode2->GetLayoutProperty<ButtonLayoutProperty>();
    RefPtr<GeometryNode> button2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> button2NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(buttonNode2, button2NodeGeometryNode, buttonNode2->GetLayoutProperty());
    ASSERT_NE(button2NodeLayoutWrapper, nullptr);
    flexNodeLayoutWrapper->AppendChild(button2NodeLayoutWrapper);

    auto imageNode1 = AceType::DynamicCast<FrameNode>(buttonNode1->GetOrCreateChildByIndex(0));
    auto image1LayoutProperty = imageNode1->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image1NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image1NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode1, image1NodeGeometryNode, imageNode1->GetLayoutProperty());
    ASSERT_NE(image1NodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(image1NodeLayoutWrapper);

    auto imageNode2 = AceType::DynamicCast<FrameNode>(buttonNode2->GetOrCreateChildByIndex(0));
    auto image2LayoutProperty = imageNode2->GetLayoutProperty<ImageLayoutProperty>();
    RefPtr<GeometryNode> image2NodeGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> image2NodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode2, image2NodeGeometryNode, imageNode2->GetLayoutProperty());
    ASSERT_NE(image2NodeLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(image2NodeLayoutWrapper);

    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetWidth(10000);
    LayoutConstraintVaildSize.selfIdealSize.SetHeight(25000);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    calendarPickerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: CalendarPickerLayoutAlgorithmTest002
 * @tc.desc: CalendarPicker Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutAlgorithmTest002, TestSize.Level1)
{
    CreateCalendarPicker();

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
    RefPtr<LayoutWrapperNode> dayContentNodeLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dayNode, dayContentFrameNodeGeometryNode, dayNode->GetLayoutProperty());
    ASSERT_NE(dayContentNodeLayoutWrapper, nullptr);
    contentNodeLayoutWrapper->AppendChild(dayContentNodeLayoutWrapper);

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
}
/**
 * @tc.name: CalendarPickerUpdateButtonStyles001
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerUpdateButtonStyles001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);

    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    ASSERT_NE(theme, nullptr);

    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto renderContext = buttonNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    CalendarDialogView::UpdateButtonStyles(buttonInfos, sizet, buttonLayoutProperty, renderContext);
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto testval = buttonLayoutProperty->GetFontWeightValue();

    EXPECT_EQ(testval, FontWeight::W100);
}
/**
 * @tc.name: CalendarDialogViewTest0050
 * @tc.desc: Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest0050, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto calendarTheme = AceType::MakeRefPtr<CalendarTheme>();
    ASSERT_NE(calendarTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(calendarTheme));
    CalendarDialogView calendarDialogView;
    CalendarSettingData settingData;
    DialogProperties properties;
    properties.alignment = DialogAlignment::BOTTOM;
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -1.0f));
    auto selectedDate = PickerDate(2000, 1, 1);
    settingData.selectedDate = selectedDate;
    settingData.dayRadius = TEST_SETTING_RADIUS;
    auto entryColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CalendarDialogPattern>());
    settingData.entryNode = AceType::WeakClaim(AceType::RawPtr(entryColumn));
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    buttonInfos.push_back(info1);

    auto dialogNode = calendarDialogView.Show(properties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CalendarDialogPattern>());
    calendarDialogView.OperationsToPattern(contentColumn, settingData, properties, buttonInfos);
    auto pattern = contentColumn->GetPattern<CalendarDialogPattern>();
    ASSERT_NE(pattern->entryNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: CalendarDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: CalendarDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: CalendarDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}
} // namespace OHOS::Ace::NG

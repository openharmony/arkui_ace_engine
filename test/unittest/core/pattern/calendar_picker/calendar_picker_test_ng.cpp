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
#include "core/components_ng/layout/layout_wrapper_node.h"
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest001, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest002, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest003, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest004, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest005, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerModelNGTest006, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest001, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest002, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest003, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest004, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest005, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest006, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest007, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest008, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest010, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest011, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest012, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest013, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerPatternTest014, TestSize.Level0)
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
 * @tc.name: CalendarDialogViewTest008
 * @tc.desc: Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest008, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewTest009, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerEventHubTest001, TestSize.Level0)
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
 * @tc.name: CalendarPickerTextDirectionTest001
 * @tc.desc: CalendarPicker TextDirection Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarPickerTextDirectionTest001, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest001, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerLayoutPropertyTest002, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarPickerUpdateButtonStyles001, TestSize.Level0)
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
 * @tc.name: CalendarDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus001, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus002, TestSize.Level0)
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
HWTEST_F(CalendarPickerTestNg, CalendarDialogViewUpdateButtonDefaultFocus003, TestSize.Level0)
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

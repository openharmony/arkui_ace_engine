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
} // namespace
class CalendarDialogPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarDialogPatternTestNg::SetUpTestCase()
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

void CalendarDialogPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

void CalendarDialogPatternTestNg::CreateCalendarPicker()
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

RefPtr<FrameNode> CalendarDialogPatternTestNg::CalendarDialogShow(RefPtr<FrameNode> entryNode)
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
 * @tc.name: CalendarDialogViewTest001
 * @tc.desc: Calendar Dialog Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest001, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest002, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest003, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest004, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest005, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest006, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest007, TestSize.Level0)
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
 * @tc.name: CalendarDialogPatternTest003
 * @tc.desc: AddHotZoneRect Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest003, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest004, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest005, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest006, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest007, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest008, TestSize.Level1)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest009, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest010, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest011, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest012, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest013, TestSize.Level1)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest014, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest015, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest016, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest017, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest018, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest019, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest020, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest021, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest022, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest023, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest024, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest025, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest026, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest027, TestSize.Level0)
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
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogPatternTest028, TestSize.Level0)
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
        theme->GetDialogBackgroundColor().ColorToString());
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
 * @tc.name: CalendarDialogViewTest0050
 * @tc.desc: Show Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogPatternTestNg, CalendarDialogViewTest0050, TestSize.Level0)
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
} // namespace OHOS::Ace::NG

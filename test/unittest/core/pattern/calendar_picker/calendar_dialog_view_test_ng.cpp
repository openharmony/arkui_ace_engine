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
#include "test/mock/core/common/mock_container.h"
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

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr Dimension TEST_SETTING_RADIUS = Dimension(10.0, DimensionUnit::VP);
} // namespace
class CalendarDialogViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarDialogViewTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
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

void CalendarDialogViewTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void CalendarDialogViewTestNg::CreateCalendarPicker()
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

RefPtr<FrameNode> CalendarDialogViewTestNg::CalendarDialogShow(RefPtr<FrameNode> entryNode)
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
 * @tc.name: DisableResetOptionButtonColor001
 * @tc.desc: DisableResetOptionButtonColor Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, DisableResetOptionButtonColor001, TestSize.Level1)
{
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    info1.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.fontWeight = FontWeight::W100;
    info2.fontColor = Color::BLACK;
    info2.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info2);
    ButtonInfo info3;
    info3.fontWeight = FontWeight::W100;
    info3.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info3.fontColor = Color::BLACK;
    info3.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info3);
    ButtonInfo info4;
    info4.fontWeight = FontWeight::W100;
    info4.role = ButtonRole::NORMAL;
    info4.fontColor = Color::BLACK;
    info4.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info4);
    /**
     * @tc.steps: step1. call DisableResetOptionButtonColor.
     * @tc.expected: set button font color flag.
     */
    int32_t cancelButtonFontColorIndex = 3;
    CalendarDialogView::DisableResetOptionButtonColor(dialogPattern, buttonInfos);
    EXPECT_FALSE(dialogPattern->updateColorFlags[cancelButtonFontColorIndex]);
}

/**
 * @tc.name: DisableResetOptionButtonColor002
 * @tc.desc: DisableResetOptionButtonColor Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, DisableResetOptionButtonColor002, TestSize.Level1)
{
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.fontWeight = FontWeight::W100;
    info2.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info2);
    ButtonInfo info3;
    info3.fontWeight = FontWeight::W100;
    info3.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info3.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info3);
    ButtonInfo info4;
    info4.fontWeight = FontWeight::W100;
    info4.role = ButtonRole::NORMAL;
    info4.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info4);
    /**
     * @tc.steps: step1. call DisableResetOptionButtonColor.
     * @tc.expected: set button font color flag.
     */
    int32_t cancelButtonFontColorIndex = 2;
    CalendarDialogView::DisableResetOptionButtonColor(dialogPattern, buttonInfos);
    EXPECT_FALSE(dialogPattern->updateColorFlags[cancelButtonFontColorIndex]);
}

/**
 * @tc.name: DisableResetOptionButtonColor003
 * @tc.desc: DisableResetOptionButtonColor Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, DisableResetOptionButtonColor003, TestSize.Level1)
{
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.fontWeight = FontWeight::W100;
    info2.fontColor = Color::BLACK;
    buttonInfos.push_back(info2);
    ButtonInfo info3;
    info3.fontWeight = FontWeight::W100;
    info3.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info3.fontColor = Color::BLACK;
    buttonInfos.push_back(info3);
    ButtonInfo info4;
    info4.fontWeight = FontWeight::W100;
    info4.role = ButtonRole::NORMAL;
    info4.fontColor = Color::BLACK;
    buttonInfos.push_back(info4);
    /**
     * @tc.steps: step1. call DisableResetOptionButtonColor.
     * @tc.expected: set button font color flag.
     */
    int32_t cancelButtonFontColorIndex = 1;
    CalendarDialogView::DisableResetOptionButtonColor(dialogPattern, buttonInfos);
    EXPECT_FALSE(dialogPattern->updateColorFlags[cancelButtonFontColorIndex]);
}

/**
 * @tc.name: SetTitleIdealSize001
 * @tc.desc: SetTitleIdealSize Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, SetTitleIdealSize001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(-99);
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
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(contentRow, nullptr);
    PipelineContext::GetCurrentContext();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    CalendarDialogView::UpdateOptionLayoutProps(contentRow, pipelineContext);
    auto monthFrameNode = FrameNode::GetOrCreateFrameNode(V2::CALENDAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(monthFrameNode, nullptr);
    CalendarSettingData settingData;
    AceApplicationInfo::GetInstance().language_ = "";
    CalendarDialogView::UpdatePaintProperties(monthFrameNode, settingData);
    pipeline->fontScale_ = -99;
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(titleRow, nullptr);
    auto layoutProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    CalendarDialogView::SetTitleIdealSize(theme, layoutProps);
    settingData.dayRadius = Dimension(10.0, DimensionUnit::VP);
    AceApplicationInfo::GetInstance().language_ = "zh";
    Dimension defaultDayRadius = theme->GetCalendarPickerDayLargeWidthOrHeight() / 2;
    settingData.dayRadius = defaultDayRadius;
    CalendarDialogView::UpdatePaintProperties(monthFrameNode, settingData);
    EXPECT_TRUE(pipeline->GetFontScale() < 0);
}

/**
 * @tc.name: SetCalendarIdealSize001
 * @tc.desc: SetCalendarIdealSize Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, SetCalendarIdealSize001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
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
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = -99;
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(titleRow, nullptr);
    auto layoutProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    CalendarDialogView::CreateDividerNode();
    CalendarDialogView::SetCalendarIdealSize(theme, layoutProps);
    CalendarSettingData settingData;
    auto monthFrameNode = FrameNode::GetOrCreateFrameNode(V2::CALENDAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(monthFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(monthFrameNode);
    AceApplicationInfo::GetInstance().language_ = "en";
    Dimension defaultDayRadius = theme->GetCalendarPickerDayLargeWidthOrHeight() / 2;
    settingData.dayRadius = defaultDayRadius;
    CalendarDialogView::SetCalendarPaintProperties(settingData);
    EXPECT_TRUE(pipeline->GetFontScale() < 0);
}

/**
 * @tc.name: CreateButtonNode001
 * @tc.desc: CreateButtonNode Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, CreateButtonNode001, TestSize.Level1)
{
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
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(titleRow, nullptr);
    auto layoutProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->AddChild(FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 4, AceType::MakeRefPtr<TextPattern>()));
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    pipeline->fontScale_ = 1000;
    CalendarDialogView::UpdateButtons(buttonNode, 1, buttonInfos);
    pipeline->fontScale_ = -99;
    CalendarDialogView::CreateButtonNode(true, buttonInfos);
    CalendarDialogView::UpdateButtons(buttonNode, 1, buttonInfos);
    EXPECT_TRUE(pipeline->GetFontScale() < 0);
}

/**
 * @tc.name: UpdateButtonLayoutProperty001
 * @tc.desc: UpdateButtonLayoutProperty Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateButtonLayoutProperty001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = -99;
    CalendarDialogView::UpdateButtonLayoutProperty(buttonNode, true, buttonInfos, pipeline);
    EXPECT_TRUE(pipeline->GetFontScale() < 0);
}

/**
 * @tc.name: UpdateButtonStyles001
 * @tc.desc: UpdateButtonStyles Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateButtonStyles001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    info1.fontFamily = { "unknown" };
    int calcvalue = 100;
    NG::BorderRadiusProperty radius;
    CalcDimension radiusCalc(calcvalue, static_cast<DimensionUnit>(1));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;
    info1.borderRadius = radius;
    info1.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto buttonLayoutProperty = AceType::MakeRefPtr<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto buttonRenderContext = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRenderContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    CalendarDialogView::UpdateButtonStyles(buttonInfos, 0, buttonLayoutProperty, buttonRenderContext);
    EXPECT_TRUE(buttonInfos[0].backgroundColor.has_value());
}

/**
 * @tc.name: UpdateButtonStyleAndRole001
 * @tc.desc: UpdateButtonStyleAndRole Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateButtonStyleAndRole001, TestSize.Level1)
{
    MockContainer::Current()->SetApiTargetVersion(99);
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W100;
    info1.role = ButtonRole::NORMAL;
    info1.buttonStyle = std::make_optional<ButtonStyleMode>(ButtonStyleMode::EMPHASIZE);
    info1.fontColor = Color::BLACK;
    info1.fontFamily = { "unknown" };
    int calcvalue = 100;
    NG::BorderRadiusProperty radius;
    CalcDimension radiusCalc(calcvalue, static_cast<DimensionUnit>(1));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;
    info1.borderRadius = radius;
    info1.backgroundColor = Color::BLACK;
    buttonInfos.push_back(info1);
    auto buttonLayoutProperty = AceType::MakeRefPtr<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    RefPtr<ButtonTheme> buttonTheme = nullptr;
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    auto buttonRenderContext = buttonNode->GetRenderContext();
    ASSERT_NE(buttonRenderContext, nullptr);
    CalendarDialogView::UpdateButtonStyleAndRole(
        buttonInfos, 10, buttonLayoutProperty, buttonRenderContext, buttonTheme);
    EXPECT_TRUE(buttonInfos[0].backgroundColor.has_value());
}

/**
 * @tc.name: UpdateButtonDefaultFocus001
 * @tc.desc: UpdateButtonDefaultFocus Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateButtonDefaultFocus001, TestSize.Level1)
{
    CreateCalendarPicker();
    auto dialogPattern = AceType::MakeRefPtr<CalendarDialogPattern>();
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.isPrimary = true;
    buttonInfos.push_back(info2);
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    buttonInfos.clear();
    info1.isPrimary = false;
    buttonInfos.push_back(info1);
    info2.isPrimary = true;
    buttonInfos.push_back(info2);
    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    buttonInfos.clear();
    info1.isPrimary = false;
    buttonInfos.push_back(info1);
    info2.isPrimary = false;
    buttonInfos.push_back(info2);
    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    buttonInfos.clear();
    info1.isPrimary = true;
    buttonInfos.push_back(info1);
    info2.isPrimary = false;
    buttonInfos.push_back(info2);
    CalendarDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_TRUE(focusHub->focusCallbackEvents_->isDefaultFocus_);
}

/**
 * @tc.name: UpdateDialogDefaultFocus001
 * @tc.desc: UpdateDialogDefaultFocus Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateDialogDefaultFocus001, TestSize.Level1)
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
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<CalendarDialogPattern>());
    ASSERT_NE(contentColumn, nullptr);
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(contentRow, nullptr);
    auto contentRowFocusHub = contentRow->GetOrCreateFocusHub();
    ASSERT_NE(contentRowFocusHub, nullptr);
    contentRowFocusHub->SetIsDefaultFocus(true);
    CalendarDialogView::UpdateDialogDefaultFocus(contentRow, contentColumn);
    EXPECT_TRUE(contentRowFocusHub->IsDefaultFocus());
}

/**
 * @tc.name: UpdateDefaultFocusByButtonInfo001
 * @tc.desc: UpdateDefaultFocusByButtonInfo Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarDialogViewTestNg, UpdateDefaultFocusByButtonInfo001, TestSize.Level1)
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
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(contentRow, nullptr);
    auto contentRowFocusHub = contentRow->GetOrCreateFocusHub();
    ASSERT_NE(contentRowFocusHub, nullptr);
    contentRowFocusHub->SetIsDefaultFocus(true);
    CalendarDialogView::UpdateDefaultFocusByButtonInfo(contentRow, contentRow, contentRow);
    EXPECT_TRUE(contentRowFocusHub->IsDefaultFocus());
}
} // namespace OHOS::Ace::NG

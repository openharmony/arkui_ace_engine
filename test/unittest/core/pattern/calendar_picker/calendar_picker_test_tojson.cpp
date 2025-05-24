/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
class CalendarPickerTestToJson : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void MockPipelineContextGetTheme();

protected:
    static void CreateCalendarPicker();
    static RefPtr<FrameNode> CalendarDialogShow(RefPtr<FrameNode> entryNode);
};

void CalendarPickerTestToJson::SetUpTestCase()
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

void CalendarPickerTestToJson::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

void CalendarPickerTestToJson::CreateCalendarPicker()
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

RefPtr<FrameNode> CalendarPickerTestToJson::CalendarDialogShow(RefPtr<FrameNode> entryNode)
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
 * @tc.name: CalendarPickerTestToJsonMarkToday
 * @tc.desc: Test CalendarPickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestToJson, CalendarPickerTestToJsonMarkToday, TestSize.Level1)
{
    CreateCalendarPicker();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.step: step1. Set MarkToday value.
     */
    bool isMarkToday = true;
    pickerPattern->SetMarkToday(isMarkToday);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be true.
     */
    EXPECT_EQ(json->GetString("markToday"), "true");
}

/**
 * @tc.name: CalendarPickerTestToJsonDisabledDateRange01
 * @tc.desc: Test CalendarPickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestToJson, CalendarPickerTestToJsonDisabledDateRange01, TestSize.Level1)
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
     * @tc.steps: step2. call SetDisabledDateRange.
     * @tc.desc: set disabledDateRange.
     * @tc.expected: GetDisabledDateRange equals disabledDateRange.
     */
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    pickerPattern->SetDisabledDateRange(disabledDateRange);
    EXPECT_EQ(CalendarPickerModelNG::GetDisabledDateRange(Referenced::RawPtr(frameNode)), "");

    /**
     * @tc.steps: step3. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be "".
     */
    EXPECT_EQ(json->GetString("disabledDateRange"), "");
}

/**
 * @tc.name: CalendarPickerTestToJsonDisabledDateRange02
 * @tc.desc: Test CalendarPickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestToJson, CalendarPickerTestToJsonDisabledDateRange02, TestSize.Level1)
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
     * @tc.steps: step2. call SetDisabledDateRange.
     * @tc.desc: set disabledDateRange.
     * @tc.expected: GetDisabledDateRange equals disabledDateRange.
     */
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    std::pair<PickerDate, PickerDate> pair;
    PickerDate defaultDate;
    pair.first = defaultDate;
    pair.second = defaultDate;
    disabledDateRange.emplace_back(pair);
    CalendarPickerModelNG::SetDisabledDateRange(Referenced::RawPtr(frameNode), disabledDateRange);
    std::string ret = std::to_string(pair.first.GetYear()) + "-" + std::to_string(pair.first.GetMonth()) + "-" +
                      std::to_string(pair.first.GetDay()) + "," + std::to_string(pair.second.GetYear()) + "-" +
                      std::to_string(pair.second.GetMonth()) + "-" + std::to_string(pair.second.GetDay());

    /**
     * @tc.steps: step3. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    pickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be defaultDate str.
     */
    std::string res;
    for (const auto& range : disabledDateRange) {
        res += range.first.ToString(false) + "," + range.second.ToString(false) + ",";
    }
    res.pop_back(); // remove ','
    EXPECT_EQ(json->GetString("disabledDateRange"), res);
}

/**
 * @tc.name: CalendarPickerTestToJsonTextStyle
 * @tc.desc: Test CalendarPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestToJson, CalendarPickerTestToJsonTextStyle, TestSize.Level1)
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
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetTextStyle.
     * @tc.desc: set pickerTextStyle.
     */
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    CalendarPickerModelNG::SetTextStyle(Referenced::RawPtr(frameNode), data);

    /**
     * @tc.steps: step3. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be data set.
     */
    auto textStyle = json->GetObject("textStyle");
    ASSERT_NE(textStyle, nullptr);
    EXPECT_EQ(textStyle->GetString("color"), "#FFFF0000");
    auto normalFont = textStyle->GetObject("font");
    ASSERT_NE(normalFont, nullptr);
    EXPECT_EQ(normalFont->GetString("size"), "10.00px");
    EXPECT_EQ(normalFont->GetString("weight"), "FontWeight.Bold");
}

/**
 * @tc.name: CalendarPickerTestToJsonEdgeAlign
 * @tc.desc: Test CalendarPickerLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerTestToJson, CalendarPickerTestToJsonEdgeAlign, TestSize.Level1)
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
    auto layoutProperty = frameNode->GetLayoutProperty<CalendarPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetTextStyle.
     * @tc.desc: set pickerTextStyle.
     */
    DimensionOffset offset(Dimension(2.0), Dimension(2.2));
    CalendarPickerModelNG::SetEdgeAlign(Referenced::RawPtr(frameNode), CalendarEdgeAlign::EDGE_ALIGN_START, offset);

    /**
     * @tc.steps: step3. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be data set.
     */
    auto edgeAlign = json->GetObject("edgeAlign");
    ASSERT_NE(edgeAlign, nullptr);
    EXPECT_EQ(edgeAlign->GetString("alignType"), "CalendarAlign.START");
    auto offsetData = edgeAlign->GetObject("offset");
    ASSERT_NE(offsetData, nullptr);
    EXPECT_EQ(offsetData->GetString("dx"),"2.00px");
    EXPECT_EQ(offsetData->GetString("dy"),"2.20px");
}
} // namespace OHOS::Ace::NG
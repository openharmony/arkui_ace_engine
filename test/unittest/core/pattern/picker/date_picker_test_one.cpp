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

#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double PATTERN_OFFSET = 1000;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t START_YEAR = 1980;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t CURRENT_DAY = 5;
} // namespace

class DatePickerTestOne : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void DatePickerTestOne::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestOne::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestOne::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return MockThemeDefault::GetPickerTheme();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestOne::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestOne::CreateDatePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    columnNode_ = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode_, nullptr);
    columnNode_->MarkModifyDone();
    columnPattern_ = columnNode_->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->OnAttachToFrameNode();
}

/**
 * @tc.name: BuildDialogAcceptAndCancelButtonForAging001
 * @tc.desc: Test DatePickerDialogView BuildDialogAcceptAndCancelButtonForAging.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, BuildDialogAcceptAndCancelButtonForAging001, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = false;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetCurrentIndex(0);
    columnPattern->UpdateToss(PATTERN_OFFSET);
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    timePickerNode->MountToParent(columnNode);
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnPattern, nullptr);
    DatePickerDialogView::BuildDialogAcceptAndCancelButtonForAging(buttonInfos, settingData,
        timePickerNode, dateNode, dateNode, dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
    ASSERT_TRUE(settingData.showTime);
}

/**
 * @tc.name: BuildDialogAcceptAndCancelButtonForAging002
 * @tc.desc: Test DatePickerDialogView BuildDialogAcceptAndCancelButtonForAging.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, BuildDialogAcceptAndCancelButtonForAging002, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = false;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetCurrentIndex(0);
    columnPattern->UpdateToss(PATTERN_OFFSET);

    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    timePickerNode->MountToParent(columnNode);

    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DatePickerDialogView::isShowTime_ = false;
    DatePickerDialogView::BuildDialogAcceptAndCancelButtonForAging(buttonInfos, settingData,
        timePickerNode, dateNode, dateNode, dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
    ASSERT_TRUE(settingData.showTime);
}

/**
 * @tc.name: NeedAdaptForAging001
 * @tc.desc: Test DatePickerDialogView NeedAdaptForAging
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, NeedAdaptForAging001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.0f;
    bool ret = DatePickerDialogView::NeedAdaptForAging();
    ASSERT_FALSE(ret);
}

/**
 * @tc.name: NeedAdaptForAging002
 * @tc.desc: Test DatePickerDialogView NeedAdaptForAging
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, NeedAdaptForAging002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;
    bool ret = DatePickerDialogView::NeedAdaptForAging();
    ASSERT_TRUE(ret);
}

/**
 * @tc.name: ConvertFontScaleValue003
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue003, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ((int)result.Value(), 40);
}

/**
 * @tc.name: ConvertFontScaleValue004
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue004, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_px;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ((int)result.Value(), 12);
}

/**
 * @tc.name: ConvertFontScaleValue005
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue005, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ((int)result.Value(), 40);
}

/**
 * @tc.name: ConvertFontScaleValue006
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue006, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_px;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ((int)result.Value(), 12);
}

/**
 * @tc.name: ConvertFontScaleValue007
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue007, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.0f;

    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: ConvertFontScaleValue008
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertFontScaleValue008, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.0f;

    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_px;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: ConvertTitleFontScaleValue001
 * @tc.desc: Test DatePickerDialogView ConvertTitleFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertTitleFontScaleValue001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 50.0_px;

    auto result = DatePickerDialogView::ConvertTitleFontScaleValue(fontSizeValue);
    EXPECT_EQ((int)result.Value(), 14);
}

/**
 * @tc.name: ConvertTitleFontScaleValue002
 * @tc.desc: Test DatePickerDialogView ConvertTitleFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ConvertTitleFontScaleValue002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 5.0f;

    Dimension fontSizeValue = 50.0_vp;

    auto result = DatePickerDialogView::ConvertTitleFontScaleValue(fontSizeValue);
    EXPECT_EQ((int)result.Value(), 72);
}

/**
 * @tc.name: CreateAndMountTimeNode001
 * @tc.desc: Test DatePickerDialogView CreateAndMountTimeNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateAndMountTimeNode001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 2.0f;

    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = false;

    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);

    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(pickerRow, nullptr);

    auto timeNode = DatePickerDialogView::CreateAndMountTimeNode(settingData, monthDaysNode, pickerRow);
    EXPECT_NE(timeNode, nullptr);
}

/**
 * @tc.name: CreateAndMountTimeNode002
 * @tc.desc: Test DatePickerDialogView CreateAndMountTimeNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateAndMountTimeNode002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 2.0f;

    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = true;

    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);

    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(pickerRow, nullptr);

    auto timeNode = DatePickerDialogView::CreateAndMountTimeNode(settingData, monthDaysNode, pickerRow);
    EXPECT_NE(timeNode, nullptr);
}
} // namespace OHOS::Ace::NG

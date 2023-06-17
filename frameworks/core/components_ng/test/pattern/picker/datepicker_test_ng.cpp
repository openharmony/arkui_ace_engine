/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/test/mock/pattern/picker/mock_picker_theme_manager.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double PATTERN_OFFSET = 1000;
constexpr double TEST_FONT_SIZE = 10;

constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t START_YEAR = 1980;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t CURRENT_DAY = 5;

const int YEARINDEX = 1;
const int BIG_SHOWCOUNT = 5;
const int SMALL_SHOWCOUNT = 3;
const int MIDDLE_OF_COUNTS = 2;
const vector<int> DEFAULT_DATE = { 1999, 9, 9 };
const std::string CONNECTER = "-";
const std::vector<int> DEFAULT_VALUE = { 1970, 1971, 1972 };
} // namespace

class DatePickerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
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

void DatePickerTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockPickerThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: DatePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test DatePickerPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGCreateDatePicker001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto buttonNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(0));
    auto renderContext = buttonNode->GetRenderContext();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(1));
    columnNode->MarkModifyDone();
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->FlushCurrentOptions();

    columnPattern->mouseEvent_->onHoverCallback_(true);
    EXPECT_TRUE(columnPattern->hoverd_);
    TouchLocationInfo touchLocationInfo(0);

    TouchEventInfo touchEventInfo1("");
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo1.AddTouchLocationInfo(std::move(touchLocationInfo));
    columnPattern->touchListener_->callback_(touchEventInfo1);
    EXPECT_EQ(columnPattern->pressColor_, renderContext->GetBackgroundColor());

    TouchEventInfo touchEventInfo2("");
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchEventInfo2.AddTouchLocationInfo(std::move(touchLocationInfo));
    columnPattern->touchListener_->callback_(touchEventInfo2);
    EXPECT_EQ(columnPattern->hoverColor_, renderContext->GetBackgroundColor());

    TouchEventInfo touchEventInfo3("");
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchEventInfo3.AddTouchLocationInfo(std::move(touchLocationInfo));
    columnPattern->touchListener_->callback_(touchEventInfo3);
    EXPECT_EQ(columnPattern->hoverColor_, renderContext->GetBackgroundColor());

    columnPattern->mouseEvent_->onHoverCallback_(false);
    EXPECT_FALSE(columnPattern->hoverd_);
    TouchEventInfo touchEventInfo4("");
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchEventInfo4.AddTouchLocationInfo(std::move(touchLocationInfo));
    columnPattern->touchListener_->callback_(touchEventInfo4);
    EXPECT_EQ(Color::TRANSPARENT, renderContext->GetBackgroundColor());

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_TRUE(datePickerPattern->HasYearNode());
    EXPECT_TRUE(datePickerPattern->HasMonthNode());
    EXPECT_TRUE(datePickerPattern->HasDayNode());
}

/**
 * @tc.name: DatePickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test DatePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_TRUE(pickerProperty->HasDisappearColor());
    EXPECT_TRUE(pickerProperty->HasDisappearWeight());
}

/**
 * @tc.name: DatePickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test DatePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(TEST_FONT_SIZE), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: DatePickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test DatePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: DatePickerModelNGSetNormalTextStyle001
 * @tc.desc: Test DatePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
    EXPECT_TRUE(pickerProperty->HasColor());
    EXPECT_TRUE(pickerProperty->HasWeight());
}

/**
 * @tc.name: DatePickerModelNGSetNormalTextStyle002
 * @tc.desc: Test DatePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetNormalTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: DatePickerModelNGSetNormalTextStyle003
 * @tc.desc: Test DatePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: DatePickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test DatePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_TRUE(pickerProperty->HasSelectedWeight());
}

/**
 * @tc.name: DatePickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test DatePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(TEST_FONT_SIZE), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: DatePickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test DatePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelNGSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: DatePickerDialogViewShow001
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow001, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: DatePickerDialogViewShow002
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow002, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR_BEFORE, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto titleNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild());
    auto titleEventHub = titleNode->GetOrCreateGestureEventHub();
    titleEventHub->ActClick();
    titleEventHub->ActClick();
    titleEventHub->ActClick();
    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManger = pipeline->GetOverlayManager();
    overlayManger->FireBackPressEvent();
    overlayManger->FireBackPressEvent();
}

/**
 * @tc.name: DatePickerDialogViewShow003
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow003, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = false;

    std::map<std::string, PickerDate> datePickerProperty;
    settingData.datePickerProperty = datePickerProperty;

    std::map<std::string, PickerTime> timePickerProperty;
    settingData.timePickerProperty = timePickerProperty;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManger = pipeline->GetOverlayManager();
    overlayManger->FireBackPressEvent();

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: DatePickerDialogViewShow004
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow004, TestSize.Level1)
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1));
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetCurrentIndex(0);
    columnPattern->UpdateColumnChildPosition(PATTERN_OFFSET);
}

/**
 * @tc.name: DatePickerDialogViewShow005
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow005, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR_BEFORE, 1, CURRENT_DAY);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, CURRENT_DAY, CURRENT_DAY);
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1));
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetCurrentIndex(0);
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: DatePickerDialogViewShow006
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow006, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1));
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetCurrentIndex(0);
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: DatePickerDialogViewShow007
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow007, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
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

    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1));
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    auto opt = columnPattern->GetOptions();
    columnPattern->SetCurrentIndex(opt[columnNode].size() - 1);
    columnPattern->HandleChangeCallback(false, true);
}

/**
 * @tc.name: DatePickerRowLayoutPropertyToJsonValue001
 * @tc.desc: Test DatePickerRowLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerRowLayoutPropertyToJsonValue001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto disappearFont = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(disappearFont);
    EXPECT_NE(disappearFont, nullptr);
}

/**
 * @tc.name: DatePickerRowLayoutPropertyReset001
 * @tc.desc: Test DatePickerRowLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerRowLayoutPropertyReset001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->Reset();
}

/**
 * @tc.name: DatePickerRowLayoutPropertyClone001
 * @tc.desc: Test DatePickerRowLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerRowLayoutPropertyClone001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_NE(pickerProperty->Clone(), nullptr);
}

/**
 * @tc.name: DatePickerPatternTest001
 * @tc.desc: Test SetShowLunar.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    DatePickerModelNG::GetInstance()->SetShowLunar(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->GetLunar());
}

/**
 * @tc.name: DatePickerPatternTest002
 * @tc.desc: Test SetStartDate, SetEndDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    DatePickerModelNG::GetInstance()->SetStartDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    DatePickerModelNG::GetInstance()->SetEndDate(PickerDate(END_YEAR, 1, 1));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(pickerProperty->GetStartDate()->year, datePickerPattern->GetStartDateLunar().year);
    EXPECT_EQ(pickerProperty->GetEndDate()->year, datePickerPattern->GetEndDateLunar().year);
    datePickerPattern->SetStartDate(PickerDate(0, 1, 1));
    datePickerPattern->SetEndDate(PickerDate(0, 1, 1));
    EXPECT_EQ(datePickerPattern->startDateSolar_.ToString(true),
                datePickerPattern->startDefaultDateSolar_.ToString(true));
    EXPECT_EQ(datePickerPattern->endDateSolar_.ToString(true), datePickerPattern->endDefaultDateSolar_.ToString(true));
}

/**
 * @tc.name: DatePickerPatternTest003
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    DatePickerModelNG::GetInstance()->SetSelectedDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedDate()->year, datePickerPattern->GetSelectDate().year);
    datePickerPattern->SetSelectDate(PickerDate(0, 1, 1));
    EXPECT_EQ(datePickerPattern->selectedDate_.ToString(true), PickerDate::Current().ToString(true));
}

/**
 * @tc.name: DatePickerPatternTest004
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);

    auto onChange = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    DatePickerModelNG::GetInstance()->SetOnChange(std::move(onChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->FireChangeEvent(true);
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);

    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    options[columnNode].clear();

    auto accessibilityProperty = columnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), static_cast<int32_t>(DEFAULT_VALUE.size()));

    options.erase(columnNode);
    columnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), 0);
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto columnNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    options[columnNode].clear();
    columnPattern->SetOptions(options);

    auto accessibilityProperty = columnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());

    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(-3);
    accessibilityProperty->SetSpecificSupportAction();
    EXPECT_FALSE(columnPattern->CanMove(true));
    EXPECT_FALSE(columnPattern->CanMove(false));
    EXPECT_TRUE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg003
 * @tc.desc: Test the Index properties of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg003, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);

    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    options[columnNode].clear();
    columnPattern->SetOptions(options);

    auto accessibilityProperty = columnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), DEFAULT_INDEX);

    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);
    columnPattern->SetShowCount(BIG_SHOWCOUNT);
    columnPattern->SetCurrentIndex(YEARINDEX);

    EXPECT_EQ(accessibilityProperty->GetCurrentIndex(), YEARINDEX);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), 0);
    auto itemCount = DEFAULT_VALUE.size();
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), itemCount - 1);

    columnPattern->SetShowCount(SMALL_SHOWCOUNT);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(),
        (itemCount + YEARINDEX - SMALL_SHOWCOUNT / MIDDLE_OF_COUNTS) % itemCount);
    EXPECT_EQ(
        accessibilityProperty->GetEndIndex(), (itemCount + YEARINDEX + SMALL_SHOWCOUNT / MIDDLE_OF_COUNTS) % itemCount);
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg004
 * @tc.desc: Test the Text property of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg004, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto yearColumnNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(yearColumnNode, nullptr);

    auto pickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto columnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetCurrentIndex(YEARINDEX);

    auto options = columnPattern->GetOptions();
    options[yearColumnNode].clear();
    columnPattern->SetOptions(options);
    auto accessibilityProperty = yearColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), "");

    for (auto& Value : DEFAULT_VALUE) {
        options[yearColumnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), std::to_string(DEFAULT_VALUE.at(YEARINDEX)));
    options[yearColumnNode].clear();
    columnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "");
    options.erase(yearColumnNode);
    columnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "");
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg005
 * @tc.desc: Test the SupportAction property of DatePickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg005, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto yearColumnNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(yearColumnNode, nullptr);

    auto pickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto columnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetCurrentIndex(YEARINDEX);

    auto options = columnPattern->GetOptions();
    options[yearColumnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[yearColumnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);

    auto accessibilityProperty = yearColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg006
 * @tc.desc: Test the Text property of DatePickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg006, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);

    auto datePickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetShowLunar(false);

    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    auto accessibilityProperty = pickerFrameNode->GetAccessibilityProperty<DatePickerAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));

    datePickerPattern->SetShowLunar(true);
    auto lunarDate = datePickerPattern->SolarToLunar(datePickerPattern->GetCurrentDate());
    EXPECT_EQ(accessibilityProperty->GetText(), std::to_string(lunarDate.year) + CONNECTER +
                                                    std::to_string(lunarDate.month) + CONNECTER +
                                                    std::to_string(lunarDate.day));
}

/**
 * @tc.name: DatePickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPaintTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto datePickerPaintMethod = AceType::MakeRefPtr<DatePickerPaintMethod>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = datePickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawLine(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(1);
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, Restore()).Times(1);
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: DatePickerPaintTest002
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPaintTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto datePickerPaintMethod = AceType::MakeRefPtr<DatePickerPaintMethod>();
    datePickerPaintMethod->SetEnabled(false);
    ASSERT_NE(datePickerPattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = datePickerPaintMethod->GetForegroundDrawFunction(paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawLine(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).Times(AtLeast(1));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: DatePickerPatternTest005
 * @tc.desc: Test PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest005, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    datePickerPattern->PaintFocusState();
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
}

/**
 * @tc.name: DatePickerPatternTest006
 * @tc.desc: Test OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest006, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case1. up KeyEvent.
     */
    KeyEvent keyEventUp(KeyCode::KEY_DPAD_UP, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventUp);
    auto propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case2. down KeyEvent.
     */
    KeyEvent keyEventDown(KeyCode::KEY_DPAD_DOWN, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventDown);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case3. UP KeyAction.
     */
    KeyEvent keyActionUp(KeyCode::KEY_DPAD_DOWN, KeyAction::UP);
    EXPECT_FALSE(datePickerPattern->OnKeyEvent(keyActionUp));
}

/**
 * @tc.name: DatePickerPatternTest007
 * @tc.desc: Test OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest007, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case1. left KeyEvent.
     */
    KeyEvent keyEventLeft(KeyCode::KEY_DPAD_LEFT, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventLeft);
    auto propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case2. right KeyEvent.
     */
    KeyEvent keyEventRight(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventRight);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case3. center KeyEvent.
     */
    KeyEvent keyEventCenter(KeyCode::KEY_DPAD_CENTER, KeyAction::DOWN);
    EXPECT_FALSE(datePickerPattern->OnKeyEvent(keyEventCenter));
}

/**
 * @tc.name: DatePickerPatternTest008
 * @tc.desc: Test methods GetYear, GetSolarMonth, GetSolarDay, GetLunarMonth, GetLunarDay.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest008, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: method GetYear.
     */
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetYear(1899));
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetYear(2101));
    EXPECT_EQ(datePickerPattern->years_[123], datePickerPattern->GetYear(2023));
    /**
     * @tc.cases: method GetSolarMonth.
     */
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetSolarMonth(0));
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetSolarMonth(13));
    EXPECT_EQ(datePickerPattern->solarMonths_[3], datePickerPattern->GetSolarMonth(4));
    /**
     * @tc.cases: method GetSolarDay.
     */
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetSolarDay(0));
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetSolarDay(32));
    EXPECT_EQ(datePickerPattern->solarDays_[15], datePickerPattern->GetSolarDay(16));
    /**
     * @tc.cases: method GetLunarMonth.
     */
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetLunarMonth(0, false));
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetLunarMonth(13, true));
    EXPECT_EQ(datePickerPattern->lunarMonths_[11], datePickerPattern->GetLunarMonth(12, false));
    /**
     * @tc.cases: method GetLunarDay.
     */
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetLunarDay(0));
    EXPECT_EQ(datePickerPattern->empty_, datePickerPattern->GetLunarDay(31));
    EXPECT_EQ(datePickerPattern->lunarDays_[14], datePickerPattern->GetLunarDay(15));
}

/**
 * @tc.name: DatePickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAlgorithmTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto yearId = datePickerPattern->GetYearId();
    auto yearColumnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, yearId);
    LayoutWrapper layoutWrapper =
        LayoutWrapper(yearColumnNode, yearColumnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapper> subTwoLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
    datePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
}

/**
 * @tc.name: DatePickerAlgorithmTest002
 * @tc.desc: Test Layout.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAlgorithmTest002, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto dataPickerLayoutProperty = AceType::MakeRefPtr<DataPickerLayoutProperty>();
    ASSERT_NE(dataPickerLayoutProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto yearId = datePickerPattern->GetYearId();
    auto yearColumnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, yearId);
    ASSERT_NE(yearColumnNode, nullptr);
    auto subNode = AceType::DynamicCast<FrameNode>(yearColumnNode->GetFirstChild());
    ASSERT_NE(subNode, nullptr);

    LayoutWrapper layoutWrapper =
        LayoutWrapper(yearColumnNode, yearColumnNode->GetGeometryNode(), dataPickerLayoutProperty);
    RefPtr<LayoutWrapper> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
    datePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
}

/**
 * @tc.name: DatePickerDialogViewShow008
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow008, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR_BEFORE, 1, CURRENT_DAY);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = false;
    settingData.useMilitary = false;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnDayNode columnPattern
     */
    auto columnDayNode = AceType::DynamicCast<FrameNode>(dateNode->GetLastChild()->GetLastChild());
    ASSERT_NE(columnDayNode, nullptr);
    auto columnPattern = columnDayNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->HandleChangeCallback(true, true);
    columnPattern->HandleChangeCallback(false, true);

    datePickerPattern->SetShowLunar(false);
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: DatePickerDialogViewShow009
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow009, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR_BEFORE, 1, CURRENT_DAY);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = false;
    settingData.useMilitary = false;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnMonthNode columnPattern
     */
    auto columnMonthNode = AceType::DynamicCast<FrameNode>(dateNode->GetChildAtIndex(1)->GetLastChild());
    ASSERT_NE(columnMonthNode, nullptr);
    auto columnPattern = columnMonthNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->HandleChangeCallback(true, true);
    columnPattern->HandleChangeCallback(false, true);

    datePickerPattern->SetShowLunar(false);
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: DatePickerDialogViewShow010
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow010, TestSize.Level1)
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
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR_BEFORE, 1, CURRENT_DAY);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = false;
    settingData.useMilitary = false;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto dialogNode = DatePickerDialogView::Show(dialogProperties, settingData, dialogEvent, dialogCancelEvent);

    auto midStackNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnYearNode columnPattern
     */
    auto columnYearNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetLastChild());
    ASSERT_NE(columnYearNode, nullptr);
    auto columnPattern = columnYearNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->HandleChangeCallback(true, true);
    columnPattern->HandleChangeCallback(false, true);

    datePickerPattern->SetShowLunar(false);
    columnPattern->HandleChangeCallback(true, true);
}

/**
 * @tc.name: DatePickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerFireChangeEventTest001, TestSize.Level1)
{
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);

    auto changeEvent = [](const BaseEventInfo* info) {
        EXPECT_EQ(info->GetType(), "DatePickerChangeEvent");
    };
    DatePickerModelNG::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->FireChangeEvent(true);
}
} // namespace OHOS::Ace::NG

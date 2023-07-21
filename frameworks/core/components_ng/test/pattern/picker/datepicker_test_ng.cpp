/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
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
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
constexpr double TOSS_DELTA = 20.0;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const double YOFFSET_START2 = 2000.0;
const double YOFFSET_END2 = 3000.0;
const double TIME_PLUS = 1 * 100.0;
const double TIME_PLUS_LARGE = 10 * 1000.0;
const SizeF TEST_FRAME_SIZE1 { 20, 50 };
const SizeF TEST_FRAME_SIZE2 { 0, 0 };
} // namespace

class DatePickerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
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

void DatePickerTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockPickerThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestNg::TearDown()
{
    MockPipelineBase::GetCurrent()->themeManager_ = nullptr;
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
    columnPattern->UpdateToss(PATTERN_OFFSET);
}

/**
 * @tc.name: DatePickerDialogViewShow003
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow003, TestSize.Level1)
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
    EXPECT_EQ(
        datePickerPattern->startDateSolar_.ToString(true), datePickerPattern->startDefaultDateSolar_.ToString(true));
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
    ASSERT_NE(datePickerPattern, nullptr);
    auto datePickerPaintMethod =
        AceType::MakeRefPtr<DatePickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(datePickerPattern)));
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
    auto datePickerPaintMethod =
        AceType::MakeRefPtr<DatePickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(datePickerPattern)));
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
    // default focusWidth < columnWidth, focusWidth = columnWidth
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->dividerSpacing_ = Dimension(50.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(pickerTheme));
    auto stackChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(datePickerPattern->focusKeyID_));
    ASSERT_NE(stackChild, nullptr);
    auto pickerChild = AceType::DynamicCast<FrameNode>(stackChild->GetLastChild());
    const float FRAME_WIDTH = 10.0f;
    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(PATTERN_OFFSET);
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(FRAME_WIDTH);
    RoundRect paintRect;
    datePickerPattern->GetInnerFocusPaintRect(paintRect);
    auto rect = paintRect.GetRect();
    EXPECT_EQ(rect.GetX(), 0);
    EXPECT_EQ(rect.Width(), pickerChild->GetGeometryNode()->GetFrameSize().Width());
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
     * @tc.cases: case3. home KeyEvent.
     */
    KeyEvent keyEventHome(KeyCode::KEY_MOVE_HOME, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventHome);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case4. end KeyEvent.
     */
    KeyEvent keyEventEnd(KeyCode::KEY_MOVE_END, KeyAction::DOWN);
    datePickerPattern->OnKeyEvent(keyEventEnd);
    propertyChangeFlag = pickerProperty->GetPropertyChangeFlag() | PROPERTY_UPDATE_RENDER;
    EXPECT_EQ(pickerProperty->GetPropertyChangeFlag(), propertyChangeFlag);
    /**
     * @tc.cases: case5. UP KeyAction.
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
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 2;
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
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(yearColumnNode, yearColumnNode->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);
    auto layoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    layoutConstraint.selfIdealSize.SetWidth(20);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    /**
     * @tc.step: step2. initialize DatePickerColumnLayoutAlgorithm and call Measure function.
     */
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
    for (int32_t i = 0; i < layoutWrapper.GetTotalChildCount(); i++) {
        datePickerColumnLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    }
    datePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);

    /**
     * test branch width.has_value()
     */
    layoutConstraint.parentIdealSize = OptionalSize<float>(300.0f, 200.0f);
    for (int32_t i = 0; i < layoutWrapper.GetTotalChildCount(); i++) {
        datePickerColumnLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    }
    datePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    auto frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE1);
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

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(yearColumnNode, yearColumnNode->GetGeometryNode(), dataPickerLayoutProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subNode, subNode->GetGeometryNode(), nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 1);
    DatePickerColumnLayoutAlgorithm datePickerColumnLayoutAlgorithm;
    for (int32_t i = 0; i < layoutWrapper.GetTotalChildCount(); i++) {
        datePickerColumnLayoutAlgorithm.currentOffset_.emplace_back(0.0f);
    }
    datePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    auto frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE2);
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

    auto changeEvent = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    DatePickerModelNG::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->FireChangeEvent(true);
}

/**
 * @tc.name: DatePickerColumnPatternTest001
 * @tc.desc: test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = columnNode->GetLayoutProperty<DataPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerColumnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    /**
     * @tc.step: step2. call columnpattern's OnDirtyLayoutWrapperSwap method.
     * @tc.expected: the result of OnDirtyLayoutWrapperSwap is true.
     */
    auto ret = pickerColumnPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DatePickerColumnPatternTest002
 * @tc.desc: test DatePickerColumnPattern FlushAnimationTextProperties
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto pickerColumnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(pickerColumnPattern, nullptr);
    /**
     * @tc.step: step2. call columnpattern's FlushAnimationTextProperties method.
     */
    pickerColumnPattern->FlushAnimationTextProperties(true);
    /**
     * test !animationProperties_.size() branch
     */
    pickerColumnPattern->animationProperties_.clear();
    pickerColumnPattern->FlushAnimationTextProperties(true);
}

/**
 * @tc.name: DatePickerColumnPatternTest003
 * @tc.desc: test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = columnNode->GetLayoutProperty<DataPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    /**
     * @tc.step: step2. call InitPanEvent method.
     */
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    /**
     * @tc.step: step3. call actionStart_ method.
     * @tc.expected: columnPattern->pressed_ is true.
     */
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    EXPECT_EQ(columnPattern->GetToss()->yStart_, OFFSET_Y);
    EXPECT_TRUE(columnPattern->pressed_);
    /**
     * @tc.step: step4. call actionUpdate_ method.
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = true;
    panEvent->actionEnd_(gestureEvent);

    columnPattern->pressed_ = true;
    columnPattern->yOffset_ = OFFSET_Y;
    columnPattern->yLast_ = OFFSET_Y;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    panEvent->actionEnd_(gestureEvent);
    /**
     * @tc.step: step5. call actionCancel_ method.
     * @tc.expected: columnPattern->pressed_ is false.
     */
    columnPattern->animationCreated_ = false;
    panEvent->actionCancel_();
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);
}

/**
 * @tc.name: DatePickerColumnPatternTest004
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = columnNode->GetLayoutProperty<DataPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    /**
     * @tc.step: step2. call InitPanEvent method.
     */
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    GestureEvent gestureEvent;
    Point point(OFFSET_X, OFFSET_Y);
    gestureEvent.SetGlobalPoint(point);
    panEvent->actionStart_(gestureEvent);
    /**
     * @tc.step: step3. call actionUpdate_ method.
     */
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    Offset deltaOffset(0.0, -1.0);
    gestureEvent.SetDelta(deltaOffset);
    auto preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);

    gestureEvent.SetInputEventType(InputEventType::MOUSE_BUTTON);
    deltaOffset.SetY(1.0);
    gestureEvent.SetDelta(deltaOffset);
    preIndex = columnPattern->GetCurrentIndex();
    panEvent->actionUpdate_(gestureEvent);
    /**
     * @tc.step: step4. call actionEnd_ method.
     * @tc.expected: columnPattern->pressed_ is false.
     */
    columnPattern->scrollDelta_ = TOSS_DELTA;
    columnPattern->animationCreated_ = false;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(columnPattern->pressed_);
    EXPECT_EQ(columnPattern->yOffset_, 0.0);
    EXPECT_EQ(columnPattern->yLast_, 0.0);
    EXPECT_EQ(columnPattern->scrollDelta_, 0.0);
}

/**
 * @tc.name: DatePickerColumnPatternTest005
 * @tc.desc: Test CreateAnimation callback.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->OnAttachToFrameNode();
    ASSERT_NE(columnPattern->toController_, nullptr);
    columnPattern->toController_->NotifyStopListener();
    /**
     * test fromBottomCurve_ callback
     */
    ASSERT_NE(columnPattern->fromBottomCurve_, nullptr);
    columnPattern->fromBottomCurve_->NotifyListener(0.1);
    /**
     * test fromTopCurve_ callback
     */
    ASSERT_NE(columnPattern->fromTopCurve_, nullptr);
    columnPattern->fromTopCurve_->NotifyListener(0.0);
}

/**
 * @tc.name: DatePickerColumnPatternTest006
 * @tc.desc: Test SetAccessibilityAction callback
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    columnPattern->SetAccessibilityAction();
    options[columnNode].clear();
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(1);
    EXPECT_EQ(columnPattern->GetCurrentIndex(), 1);

    columnPattern->OnAttachToFrameNode();
    EXPECT_TRUE(columnPattern->animationCreated_);
    auto accessibilityProperty = columnNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    /**
     * test actionScrollForwardImpl_ callback
     */
    ASSERT_NE(accessibilityProperty->actionScrollForwardImpl_, nullptr);
    accessibilityProperty->ActActionScrollForward();
}

/**
 * @tc.name: DatePickerColumnPatternTest007
 * @tc.desc: Test SetAccessibilityAction callback
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    columnPattern->SetAccessibilityAction();
    options[columnNode].clear();
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(1);
    EXPECT_EQ(columnPattern->GetCurrentIndex(), 1);
    columnPattern->OnAttachToFrameNode();
    EXPECT_TRUE(columnPattern->animationCreated_);
    auto accessibilityProperty = columnNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    /**
     * test actionScrollBackwardImpl_ callback
     */
    ASSERT_NE(accessibilityProperty->actionScrollBackwardImpl_, nullptr);
    accessibilityProperty->ActActionScrollBackward();
}

/**
 * @tc.name: DatePickerModelTest001
 * @tc.desc: Test SetBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create datepicker framenode.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(pickerFrameNode, nullptr);
    auto datePickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * @tc.step: step2. call SetBackgroundColor.
     * @tc.expected: datePickerPattern->backgroundColor_ is color.
     */
    Color color;
    DatePickerModelNG::GetInstance()->SetBackgroundColor(color);
    EXPECT_EQ(datePickerPattern->backgroundColor_, color);
}

/**
 * @tc.name: DatePickerPatternTest009
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest009, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild());
    auto pickerProperty = columnNode->GetLayoutProperty<DataPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, columnNode->GetGeometryNode(), pickerProperty);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.frameSizeChange = true;
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    /**
     * @tc.step: step2. call pattern's OnDirtyLayoutWrapperSwap method.
     * @tc.expected: the result of OnDirtyLayoutWrapperSwap is true.
     */
    auto ret = pickerPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DatePickerPatternTest010
 * @tc.desc: test ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest010, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto jsonValue = JsonUtil::Create(true);
    auto jsonValue2 = JsonUtil::Create(true);
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    rowLayoutProperty->UpdateLunar(false);
    /**
     * @tc.step: step2. call pattern's ToJsonValue method.
     * @tc.expected: jsonValue2->GetValue("constructor") is not nullptr.
     */
    pickerPattern->ToJsonValue(jsonValue);
    /**
     * cover branch LunarValue == true
     */
    rowLayoutProperty->UpdateLunar(true);
    pickerPattern->ToJsonValue(jsonValue2);
    ASSERT_NE(jsonValue2->GetValue("constructor"), nullptr);
}

/**
 * @tc.name: DatePickerPatternTest011
 * @tc.desc: test InitOnKeyEvent callback
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest011, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    focusHub->ProcessOnKeyEventInternal(keyEvent);
    /**
     * test callback getInnerFocusRectFunc_
     */
    RoundRect paintRect;
    focusHub->getInnerFocusRectFunc_(paintRect);
}

/**
 * @tc.name: DatePickerPatternTest012
 * @tc.desc: test some branches of OnDataLinking and HandleSolarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest012, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->showMonthDays_ = false;
    pickerPattern->SetShowLunar(false);
    std::vector<RefPtr<FrameNode>> tags;
    /**
     * @tc.step: step2. call OnDataLinking.
     * @tc.expected: tag is invalid.
     */
    pickerPattern->OnDataLinking(frameNode, false, 0, tags);
    /**
     * test HandleSolarDayChange
     */
    auto yearColumnNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(yearColumnNode, nullptr);
    auto monthColumnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1)->GetChildAtIndex(1));
    ASSERT_NE(monthColumnNode, nullptr);
    auto dayColumnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(2)->GetChildAtIndex(1));
    ASSERT_NE(yearColumnNode, nullptr);
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(yearColumnPattern, nullptr);
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(monthColumnPattern, nullptr);
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(dayColumnPattern, nullptr);
    /**
     * @tc.step: step3. set currentIndex = 12 and call HandleSolarDayChange.
     * @tc.expected: cover invalidate month branch.
     */
    monthColumnPattern->SetCurrentIndex(12);
    pickerPattern->HandleSolarDayChange(true, 0);
    yearColumnPattern->SetCurrentIndex(2101);
    pickerPattern->HandleSolarDayChange(true, 0);
    /**
     * test branch !yearDatePickerColumnPattern
     */
    auto allChildNode = pickerPattern->GetAllChildNode();
    auto yearNode = allChildNode["year"];
    yearNode->pattern_.Reset();
    pickerPattern->HandleSolarDayChange(false, 0);
}

/**
 * @tc.name: DatePickerPatternTest013
 * @tc.desc: test some branches of HandleLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest013, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto allChildNode = pickerPattern->GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    ASSERT_NE(monthNode, nullptr);
    auto yearDatePickerColumnPattern = yearNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(yearDatePickerColumnPattern, nullptr);
    auto monthDatePickerColumnPattern = monthNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(monthDatePickerColumnPattern, nullptr);

    monthDatePickerColumnPattern->SetCurrentIndex(1);
    pickerPattern->HandleReduceLunarDayChange(0);
    /**
     * @tc.step: step2. call HandleReduceLunarDayChange.
     * @tc.expected: hasLeapMonth is false.
     */
    yearDatePickerColumnPattern->SetCurrentIndex(323);
    monthDatePickerColumnPattern->SetCurrentIndex(1);
    pickerPattern->HandleReduceLunarDayChange(0);
    /**
     * @tc.step: step3. call HandleReduceLunarDayChange.
     * @tc.expected: lunarDate.isLeapMonth is true.
     */
    yearDatePickerColumnPattern->SetCurrentIndex(123);
    monthDatePickerColumnPattern->SetCurrentIndex(2);
    pickerPattern->HandleReduceLunarDayChange(0);
}

/**
 * @tc.name: DatePickerPatternTest014
 * @tc.desc: test LunarDateCompare
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest014, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    LunarDate lunarDateLeft, lunarDateRight;
    lunarDateLeft.year = 2013, lunarDateRight.year = 2000;
    lunarDateLeft.month = 5, lunarDateRight.month = 7;
    lunarDateLeft.day = 3, lunarDateRight.day = 2;
    lunarDateLeft.isLeapMonth = lunarDateRight.isLeapMonth = false;
    /**
     * @tc.step: step2. call LunarDateCompare(lunarDateLeft, lunarDateRight).
     * @tc.expected: the result of LunarDateCompare is 1.
     */
    auto ret = pickerPattern->LunarDateCompare(lunarDateLeft, lunarDateRight);
    EXPECT_EQ(ret, 1);
    /**
     * @tc.step: step3. call LunarDateCompare(lunarDateRight, lunarDateLeft).
     * @tc.expected: the result of LunarDateCompare is -1.
     */
    ret = pickerPattern->LunarDateCompare(lunarDateRight, lunarDateLeft);
    EXPECT_EQ(ret, -1);
    /**
     * @tc.step: step4. set lunarDateLeft.year = lunarDateRight.year and call LunarDateCompare.
     * @tc.expected: the result of LunarDateCompare is -1.
     */
    lunarDateLeft.year = lunarDateRight.year = 2000;
    ret = pickerPattern->LunarDateCompare(lunarDateLeft, lunarDateRight);
    EXPECT_EQ(ret, -1);
    /**
     * @tc.step: step5. set lunarDateLeft.month = lunarDateRight.month and call LunarDateCompare.
     * @tc.expected: the result of LunarDateCompare is 1.
     */
    lunarDateLeft.month = lunarDateRight.month = 7;
    ret = pickerPattern->LunarDateCompare(lunarDateLeft, lunarDateRight);
    EXPECT_EQ(ret, 1);
    /**
     * test branch left.day > right.day
     */
    lunarDateLeft.month = lunarDateRight.month = 7;
    ret = pickerPattern->LunarDateCompare(lunarDateRight, lunarDateLeft);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: DatePickerPatternTest015
 * @tc.desc: test AdjustSolarStartEndDate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest015, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    LunarDate startDate, endDate;
    startDate.year = 2013, endDate.year = 2000;
    startDate.month = 8, endDate.month = 3;
    startDate.day = 3, endDate.day = 2;
    startDate.isLeapMonth = endDate.isLeapMonth = false;

    auto dataPickerRowLayoutProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(dataPickerRowLayoutProperty, nullptr);
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    /**
     * test branch startDateSolar_.GetYear() > endDateSolar_.GetYear()
     */
    pickerPattern->AdjustSolarStartEndDate();
    /**
     * test branch startDateSolar_.GetMonth()>endDateSolar_.GetMonth()
     */
    startDate.year = endDate.year = 2000;
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    pickerPattern->AdjustSolarStartEndDate();
    /**
     * test branch startDateSolar_.GetDay() > endDateSolar_.GetDay()
     */
    startDate.month = endDate.month = 7;
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    pickerPattern->AdjustSolarStartEndDate();
}

/**
 * @tc.name: DatePickerPatternTest016
 * @tc.desc: test AdjustLunarStartEndDate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest016, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    LunarDate startDate, endDate;
    startDate.year = 2013, endDate.year = 2000;
    startDate.month = 8, endDate.month = 3;
    startDate.day = 3, endDate.day = 2;
    startDate.isLeapMonth = endDate.isLeapMonth = false;
    auto dataPickerRowLayoutProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(dataPickerRowLayoutProperty, nullptr);
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    /**
     * test branch GetStartDateLunar().year > GetEndDateLunar().year
     */
    pickerPattern->AdjustLunarStartEndDate();
    /**
     * test branch GetStartDateLunar().month > GetEndDateLunar().month
     */
    startDate.year = endDate.year = 2000;
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    pickerPattern->AdjustLunarStartEndDate();
    /**
     * test branch GetStartDateLunar().day > GetEndDateLunar().day
     */
    startDate.month = endDate.month = 7;
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);
    pickerPattern->AdjustLunarStartEndDate();
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: DatePicker Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePicker and initialize related properties.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Get datePickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    options[columnNode].clear();
    columnPattern->SetOptions(options);
    columnPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get datePickerColumn accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto accessibilityProperty = columnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When datePickerColumn can not move, call the callback function in datePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When datePickerColumn can move, call the callback function in datePickerColumn
     *                   accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    options[columnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    options = columnPattern->GetOptions();
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(1);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    options[columnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    options = columnPattern->GetOptions();
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(1);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: DatePickerEventActionsTest001
 * @tc.desc: Test pan event actions
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerEventActionsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datePickerColumn.
     */
    auto theme = MockPipelineBase::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModelNG::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(1));
    columnNode->MarkModifyDone();
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    auto panEvent = columnPattern->panEvent_;

    /**
     * @tc.steps: step2. call actionStart_ func.
     * @tc.expected: pressed_ is true.
     */
    GestureEvent gestureEvent;
    ASSERT_NE(panEvent->actionStart_, nullptr);
    panEvent->actionStart_(gestureEvent);
    EXPECT_TRUE(columnPattern->pressed_);

    /**
     * @tc.steps: step3. call actionEnd_ func.
     * @tc.expected: pressed_ is false.
     */
    ASSERT_NE(panEvent->actionEnd_, nullptr);
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(columnPattern->pressed_);

    /**
     * @tc.steps: step4. call actionEnd_ func in another condition.
     * @tc.expected: pressed_ is false.
     */
    auto toss = columnPattern->GetToss();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    EXPECT_TRUE(toss->Play());

    columnPattern->SetShowCount(0);
    auto options = columnPattern->GetOptions();
    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(std::to_string(Value));
    }
    columnPattern->SetOptions(options);
    EXPECT_FALSE(columnPattern->NotLoopOptions());

    columnPattern->pressed_ = true;
    panEvent->actionEnd_(gestureEvent);
    EXPECT_FALSE(columnPattern->pressed_);
}

/**
 * @tc.name: TossAnimationControllerTest001
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TossAnimationController instance.
     */
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is true.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
    auto column = AceType::MakeRefPtr<DatePickerColumnPattern>();
    toss->SetColumn(column);
}

/**
 * @tc.name: TossAnimationControllerTest002
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TossAnimationController instance.
     */
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    /**
     * @tc.steps: step2. call Play function.
     * @tc.expected: The return value is true.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
    toss->SetStart(YOFFSET_START2);
    toss->SetEnd(YOFFSET_END2);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START2);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END2);
    EXPECT_TRUE(ret);
    auto column = AceType::MakeRefPtr<DatePickerColumnPattern>();
    toss->SetColumn(column);
}

/**
 * @tc.name: TossAnimationControllerTest003
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest003, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() - TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest004
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest004, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_START1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_START1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TossAnimationControllerTest005
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest005, TestSize.Level1)
{
    RefPtr<TossAnimationController> toss = AceType::MakeRefPtr<TossAnimationController>();
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS_LARGE;
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG

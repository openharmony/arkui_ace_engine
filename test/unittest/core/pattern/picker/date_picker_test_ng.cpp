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


#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<DatePickerModel> DatePickerModel::datePickerInstance_ = nullptr;
std::unique_ptr<DatePickerDialogModel> DatePickerDialogModel::datePickerDialogInstance_ = nullptr;

DatePickerModel* DatePickerModel::GetInstance()
{
    if (!datePickerInstance_) {
        if (!datePickerInstance_) {
            datePickerInstance_.reset(new NG::DatePickerModelNG());
        }
    }
    return datePickerInstance_.get();
}

DatePickerDialogModel* DatePickerDialogModel::GetInstance()
{
    if (!datePickerDialogInstance_) {
        if (!datePickerDialogInstance_) {
            datePickerDialogInstance_.reset(new NG::DatePickerDialogModelNG());
        }
    }
    return datePickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double PATTERN_OFFSET = 1000;
constexpr double UP_FONT_SIZE = 5.0;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr double DOWN_FONT_SIZE = 20.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t START_YEAR = 1980;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t CURRENT_DAY = 5;
const int YEARINDEX = 1;
const int ENORMOUS_SHOWCOUNT = 7;
const int HUGE_SHOWCOUNT = 6;
const int BIG_SHOWCOUNT = 5;
const int MEDIUM_SHOWCOUNT = 4;
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
const std::string SELECTED_DATE_STRING = R"({"year":2000,"month":5,"day":6,"hour":1,"minute":1,"status":-1})";
constexpr double COLUMN_VELOCITY = 2000.0;
constexpr double COLUMN_WIDTH = 200.0;
constexpr double SECLECTED_TEXTNODE_HEIGHT = 84.0;
constexpr double OTHER_TEXTNODE_HEIGHT = 54.0;
const std::string AM = "上午";
const std::string PM = "下午";
const std::string COLON = ":";
const std::string ZERO = "0";
} // namespace

class DatePickerTestNg : public testing::Test {
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

void DatePickerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestNg::SetUp()
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

void DatePickerTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestNg::CreateDatePickerColumnNode()
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
 * @tc.name: DatePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test DatePickerPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelCreateDatePicker001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto buttonNode = AceType::DynamicCast<FrameNode>(stackNode->GetChildAtIndex(0));
    auto renderContext = buttonNode->GetRenderContext();
    auto columnNode = AceType::DynamicCast<FrameNode>(stackNode->GetChildAtIndex(1)->GetLastChild());
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

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_TRUE(datePickerPattern->HasYearNode());
    EXPECT_TRUE(datePickerPattern->HasMonthNode());
    EXPECT_TRUE(datePickerPattern->HasDayNode());
}

/**
 * @tc.name: DatePickerModelSetDisappearTextStyle001
 * @tc.desc: Test DatePickerModel SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_TRUE(pickerProperty->HasDisappearColor());
    EXPECT_TRUE(pickerProperty->HasDisappearWeight());
}

/**
 * @tc.name: DatePickerModelSetDisappearTextStyle002
 * @tc.desc: Test DatePickerModel SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetDisappearTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(TEST_FONT_SIZE), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: DatePickerModelSetDisappearTextStyle003
 * @tc.desc: Test DatePickerModel SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetDisappearTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: DatePickerModelSetDisappearTextStyle004
 * @tc.desc: Test DatePickerTestNg SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetDisappearTextStyle004, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(10);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = DatePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: DatePickerModelSetNormalTextStyle001
 * @tc.desc: Test DatePickerModel SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
    EXPECT_TRUE(pickerProperty->HasColor());
    EXPECT_TRUE(pickerProperty->HasWeight());
}

/**
 * @tc.name: DatePickerModelSetNormalTextStyle002
 * @tc.desc: Test DatePickerModel SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetNormalTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: DatePickerModelSetNormalTextStyle003
 * @tc.desc: Test DatePickerModel SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetNormalTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: DatePickerModelSetNormalTextStyle004
 * @tc.desc: Test DatePickerTestNg SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetNormalTextStyle004, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = DatePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: DatePickerModelSetSelectedTextStyle001
 * @tc.desc: Test DatePickerModel SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_TRUE(pickerProperty->HasSelectedColor());
    EXPECT_TRUE(pickerProperty->HasSelectedWeight());
}

/**
 * @tc.name: DatePickerModelSetSelectedTextStyle002
 * @tc.desc: Test DatePickerModel SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetSelectedTextStyle002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(TEST_FONT_SIZE);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(TEST_FONT_SIZE), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: DatePickerModelSetSelectedTextStyle003
 * @tc.desc: Test DatePickerModel SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetSelectedTextStyle003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: DatePickerModelSetSelectedTextStyle004
 * @tc.desc: Test DatePickerTestNg SetSeletedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerModelSetSelectedTextStyle004, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = DatePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
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

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto disappearFont = JsonUtil::Create(true);
    pickerProperty->ToJsonValue(disappearFont, filter);
    EXPECT_NE(disappearFont, nullptr);
}

/**
 * @tc.name: DatePickerRowLayoutPropertyReset001
 * @tc.desc: Test DatePickerRowLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerRowLayoutPropertyReset001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetShowLunar(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    DatePickerModel::GetInstance()->SetEndDate(PickerDate(END_YEAR, 1, 1));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(pickerProperty->GetStartDate()->year, datePickerPattern->GetStartDateLunar().year);
    EXPECT_EQ(pickerProperty->GetEndDate()->year, datePickerPattern->GetEndDateLunar().year);
}

/**
 * @tc.name: DatePickerPatternTest003
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto onChange = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    DatePickerModel::GetInstance()->SetOnChange(std::move(onChange));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->FireChangeEvent(true);
}

/**
 * @tc.name: DatePickerPatternTest019
 * @tc.desc: Test OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest019, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);

    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    ASSERT_NE(textCancelLayoutProperty, nullptr);
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    std::string nodeInfo = "";
    auto cancel = Localization::GetInstance()->GetEntryLetters("common.cancel");
    EXPECT_EQ(cancel, nodeInfo);
}

/**
 * @tc.name: DatePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerAccessibilityPropertyTestNg001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto blendNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode, nullptr);

    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto options = columnPattern->GetOptions();
    options[columnNode].clear();

    auto accessibilityProperty = columnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto blendNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto blendNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto blendNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto yearColumnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
        options[yearColumnNode].emplace_back(PickerDateF::CreateYear(Value));
    }
    columnPattern->SetOptions(options);
    DateTime date;
    date.year = DEFAULT_VALUE.at(YEARINDEX);
    EXPECT_EQ(accessibilityProperty->GetText(), Localization::GetInstance()->FormatDateTime(date, "y"));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto blendNode = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild()->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto yearColumnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(yearColumnNode, nullptr);

    auto pickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    auto columnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SetCurrentIndex(YEARINDEX);

    auto options = columnPattern->GetOptions();
    options[yearColumnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[yearColumnNode].emplace_back(PickerDateF::CreateYear(Value));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: DatePickerPaintTest002
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPaintTest002, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    canvasDrawFunction(rsCanvas);
}

/**
 * @tc.name: DatePickerPatternTest005
 * @tc.desc: Test PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest005, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->dividerSpacing_ = Dimension(50.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(pickerTheme));
    auto stackChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(datePickerPattern->focusKeyID_));
    ASSERT_NE(stackChild, nullptr);
    auto blendChild = AceType::DynamicCast<FrameNode>(stackChild->GetLastChild());
    ASSERT_NE(blendChild, nullptr);
    auto pickerChild = AceType::DynamicCast<FrameNode>(blendChild->GetLastChild());
    const float FRAME_WIDTH = 10.0f;
    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(PATTERN_OFFSET);
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(FRAME_WIDTH);
    RoundRect paintRect;
    datePickerPattern->GetInnerFocusPaintRect(paintRect);
    auto rect = paintRect.GetRect();
    Dimension offset = 2.0_vp;
    EXPECT_EQ(rect.GetX(), offset.ConvertToPx());
    EXPECT_EQ(rect.Width(), pickerChild->GetGeometryNode()->GetFrameSize().Width() - offset.ConvertToPx() * 2);
}

/**
 * @tc.name: DatePickerPatternTest006
 * @tc.desc: Test OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 2;
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto blendNode = AceType::DynamicCast<FrameNode>(yearColumnNode->GetParent());
    ASSERT_NE(blendNode, nullptr);
    auto layoutConstraint = blendNode->GetLayoutProperty()->CreateChildConstraint();
    layoutConstraint.selfIdealSize.SetWidth(20);
    blendNode->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    blendNode->GetLayoutProperty()->UpdateContentConstraint();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnDayNode columnPattern
     */
    auto blendDayNode = AceType::DynamicCast<FrameNode>(dateNode->GetLastChild()->GetLastChild());
    ASSERT_NE(blendDayNode, nullptr);
    auto columnDayNode = AceType::DynamicCast<FrameNode>(blendDayNode->GetLastChild());
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnMonthNode columnPattern
     */
    auto blendDayNode = AceType::DynamicCast<FrameNode>(dateNode->GetLastChild()->GetLastChild());
    ASSERT_NE(blendDayNode, nullptr);
    auto columnMonthNode = AceType::DynamicCast<FrameNode>(blendDayNode->GetLastChild());
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
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * columnYearNode columnPattern
     */
    auto blendYearNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetLastChild());
    ASSERT_NE(blendYearNode, nullptr);
    auto columnYearNode = AceType::DynamicCast<FrameNode>(blendYearNode->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto changeEvent = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    DatePickerModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
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
 * @tc.name: DatePickerColumnPatternTest006
 * @tc.desc: Test SetAccessibilityAction callback
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create datepicker framenode and columnpattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    auto datePickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    /**
     * @tc.step: step2. call SetBackgroundColor.
     * @tc.expected: datePickerPattern->backgroundColor_ is color.
     */
    Color color;
    DatePickerModel::GetInstance()->SetBackgroundColor(color);
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    pickerPattern->ToJsonValue(jsonValue, filter);
    /**
     * cover branch LunarValue == true
     */
    rowLayoutProperty->UpdateLunar(true);
    pickerPattern->ToJsonValue(jsonValue2, filter);
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    auto yearColumnNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
    ASSERT_NE(yearColumnNode, nullptr);
    auto monthColumnNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(1)->GetChildAtIndex(1)->GetLastChild());
    ASSERT_NE(monthColumnNode, nullptr);
    auto dayColumnNode =
        AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(2)->GetChildAtIndex(1)->GetLastChild());
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

    pickerPattern->isPicker_ = false;
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
 * @tc.name: DatePickerPatternTest017
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerTest017, TestSize.Level1)
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
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto pipeline = MockPipelineContext::GetCurrent();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->disappearOptionStyle_.textColor_ = Color::RED;
    pickerTheme->normalOptionStyle_.textColor_ = Color::RED;
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto dateNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto datePickerNode = DatePickerDialogView::CreateDateNode(
        dateNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(datePickerNode, nullptr);
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto monthDaysNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(
        monthDaysNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    datePickerNode->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    buttonTitleNode->MountToParent(contentColumn);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    datePickerPattern->SetContentRowNode(contentRow);
    contentRow->MountToParent(contentColumn);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
    auto context = datePickerNode->GetContext();
    ASSERT_NE(context, nullptr);
    datePickerPattern->OnColorConfigurationUpdate();
    auto pickerProperty = datePickerNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    EXPECT_EQ(pickerProperty->GetColor(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearColor(), Color::RED);
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    /**
     * @tc.steps: step2. Get datePickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto firstChild = AceType::DynamicCast<FrameNode>(pickerFrameNode->GetFirstChild());
    ASSERT_NE(firstChild, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(firstChild->GetChildAtIndex(1));
    ASSERT_NE(blendNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
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
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
    }
    options = columnPattern->GetOptions();
    columnPattern->SetOptions(options);
    columnPattern->SetCurrentIndex(1);
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    options[columnNode].clear();
    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
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
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
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
    EXPECT_FALSE(toss->Play());

    columnPattern->SetShowCount(0);
    auto options = columnPattern->GetOptions();
    for (auto& Value : DEFAULT_VALUE) {
        options[columnNode].emplace_back(PickerDateF::CreateYear(Value));
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
     * @tc.expected: The return value is false.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
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
     * @tc.expected: The return value is false.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(ret);
    auto column = AceType::MakeRefPtr<DatePickerColumnPattern>();
    toss->SetColumn(column);
    column->touchBreak_ = true;
    toss->SetStart(YOFFSET_START2);
    toss->SetEnd(YOFFSET_END2);
    toss->timeEnd_ = toss->GetCurrentTime() + TIME_PLUS;
    ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START2);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END2);
    EXPECT_FALSE(ret);
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

/**
 * @tc.name: TossAnimationControllerTest006
 * @tc.desc: Test TossAnimationController.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, TossAnimationControllerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DatePickerColumn.
     */
    CreateDatePickerColumnNode();

    /**
     * @tc.steps: step2. Set velocity and toss offset .
     */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    toss->timeEnd_ = toss->timeStart_ + TIME_PLUS;

    /**
     * @tc.step: step3. call toss::Play and check yStart_ and yEnd_.
     * @tc.expected: yStart_ and yEnd_ same as setting, return value is true.
     */
    auto ret = toss->Play();
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_TRUE(ret);
    toss->StopTossAnimation();
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: DatePickerDialogViewShow011
 * @tc.desc: Test GetSelectedObject.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DatePickerSettingData with showtime.
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    /**
     * @tc.steps: step2. Set DialogProperties.
     */
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.step: step3. call DatePickerDialogView::Show and find DatePickerPattern call GetSelectedObject.
     * @tc.expected: selectedDate same as setting.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->SetShowTimeFlag(true);
    pickerPattern->SetShowMonthDaysFlag(true);
    auto selectedDate = pickerPattern->GetSelectedObject(true);
    EXPECT_EQ(selectedDate, SELECTED_DATE_STRING);
}

/**
 * @tc.name: DateTimeAnimationControllerTest001
 * @tc.desc: Test DateTimeAnimationController PlayOldColumnOpacityInAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DateTimeAnimationControllerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DatePickerSettingData and create dateNode.
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    auto dateNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(dateNode, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);

    /**
     * @tc.steps: step2. PlayOldColumnOpacityInAnimation without datePicker.
     * @tc.expected: Opacity of render is set.
     */
    auto dateTimeAnimationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    dateTimeAnimationController->SetMonthDays(monthDaysNode);
    dateTimeAnimationController->SetTimePicker(timeNode);
    auto monthDays = dateTimeAnimationController->monthDays_.Upgrade();
    ASSERT_NE(monthDays, nullptr);
    auto monthDaysRender = monthDays->GetRenderContext();
    ASSERT_NE(monthDaysRender, nullptr);
    auto timePicker = dateTimeAnimationController->timePicker_.Upgrade();
    ASSERT_NE(timePicker, nullptr);
    auto timePickerRender = timePicker->GetRenderContext();
    ASSERT_NE(timePickerRender, nullptr);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);

    /**
     * @tc.steps: step3. Set datePicker.
     */
    auto tempChildren = dateNode->children_;
    dateNode->children_.clear();
    dateTimeAnimationController->SetDatePicker(dateNode);
    dateNode->children_ = tempChildren;
    dateTimeAnimationController->SetDatePicker(dateNode);
    auto datePicker = dateTimeAnimationController->datePicker_.Upgrade();
    ASSERT_NE(datePicker, nullptr);
    auto datePickerLayoutProperty = datePicker->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(datePickerLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. PlayOldColumnOpacityInAnimation with datePicker.
     * @tc.expected: datePicker's visibility is set visible.
     */
    monthDaysRender->UpdateOpacity(0.0f);
    timePickerRender->UpdateOpacity(0.0f);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);
    EXPECT_EQ(datePickerLayoutProperty->GetVisibilityValue(), VisibleType::VISIBLE);

    /**
     * @tc.steps: step5. PlayOldColumnOpacityInAnimation without datePicker layoutProperty.
     * @tc.expected: datePicker's visibility is not set.
     */
    datePicker->layoutProperty_ = nullptr;
    monthDaysRender->UpdateOpacity(0.0f);
    timePickerRender->UpdateOpacity(0.0f);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    EXPECT_FLOAT_EQ(monthDaysRender->GetOpacityValue(), 0);
    EXPECT_FLOAT_EQ(timePickerRender->GetOpacityValue(), 0);
}

/**
 * @tc.name: DateTimeAnimationControllerTest002
 * @tc.desc: Test DateTimeAnimationController PlayOldColumnOpacityInAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DateTimeAnimationControllerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DatePickerSettingData and create dateNode.
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    auto dateNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(dateNode, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);

    /**
     * @tc.steps: step2. StopOldColumnOpacityAnimation while oldColumnOpacityAnimation not set.
     */
    auto dateTimeAnimationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    dateTimeAnimationController->StopOldColumnOpacityInAnimation();
    dateTimeAnimationController->StopOldColumnOpacityOutAnimation();

    /**
     * @tc.steps: step3. StopOldColumnOpacityAnimation after oldColumnOpacityAnimation set.
     * @tc.expected: OldColumnOpacityAnimations is clear.
     */
    dateTimeAnimationController->SetMonthDays(monthDaysNode);
    dateTimeAnimationController->SetTimePicker(timeNode);
    dateTimeAnimationController->PlayOldColumnOpacityInAnimation();
    dateTimeAnimationController->PlayOldColumnOpacityOutAnimation();

    /**
     * @tc.steps: step4. Play animation.
     * @tc.expected: isInAnimationPlaying_ or isOutAnimationPlaying_ is set.
     */
    dateTimeAnimationController->SetDatePicker(dateNode);
    dateTimeAnimationController->created_ = false;
    dateTimeAnimationController->Play(true);
    EXPECT_TRUE(dateTimeAnimationController->created_);
    EXPECT_FALSE(dateTimeAnimationController->isInAnimationPlaying_);
    dateTimeAnimationController->isInAnimationPlaying_ = false;
    dateTimeAnimationController->Play(false);
    EXPECT_FALSE(dateTimeAnimationController->isOutAnimationPlaying_);
}

/**
 * @tc.name: DatePickerColumnPatternTest008
 * @tc.desc: Test DatePickerColumnPattern InitMouseAndPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. InitMouseAndPressEvent while mouseEvent_ or touchListener_ is null.
     * @tc.expected: Function called successfully.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(columnPattern_, nullptr);
    auto emptyMouseEventFunc = [](bool isHover) {};
    columnPattern_->mouseEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(emptyMouseEventFunc));
    columnPattern_->touchListener_ = nullptr;
    columnPattern_->InitMouseAndPressEvent();
    auto emptyTouchListenerFunc = [](const TouchEventInfo& info) {};
    columnPattern_->mouseEvent_ = nullptr;
    columnPattern_->touchListener_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(emptyTouchListenerFunc));
    columnPattern_->InitMouseAndPressEvent();

    /**
     * @tc.steps: step2. Get touchListener.
     */
    columnPattern_->mouseEvent_ = nullptr;
    columnPattern_->touchListener_ = nullptr;
    auto columnEventHub = columnNode_->GetEventHub<EventHub>();
    ASSERT_NE(columnEventHub, nullptr);
    auto columnGesture = columnEventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(columnGesture, nullptr);
    columnPattern_->InitMouseAndPressEvent();
    auto touchListener = columnGesture->touchEventActuator_->touchEvents_.back()->callback_;

    /**
     * @tc.steps: step3. Set TouchType DOWN and call callback.
     * @tc.expected: animationBreak_ and clickBreak_ are set false.
     */
    TouchEventInfo touchEventInfo("touch");
    TouchLocationInfo localLocationInfo(1);
    localLocationInfo.SetTouchType(TouchType::DOWN);
    std::list<TouchLocationInfo> touches;
    touches.emplace_back(localLocationInfo);
    touchEventInfo.touches_ = touches;
    touchListener(touchEventInfo);
    EXPECT_FALSE(columnPattern_->animationBreak_);
    EXPECT_FALSE(columnPattern_->clickBreak_);

    /**
     * @tc.steps: step4. Set tossStatus true and call callback.
     * @tc.expected: touchBreak_ animationBreak_ and clickBreak_ are set true.
     */
    columnPattern_->SetTossStatus(true);

    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    auto propertyCallback = [](float position) {};
    toss->property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    toss->end_ = OFFSET_Y;
    touchListener(touchEventInfo);
    EXPECT_TRUE(columnPattern_->touchBreak_);
    EXPECT_TRUE(columnPattern_->animationBreak_);
    EXPECT_TRUE(columnPattern_->clickBreak_);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, OFFSET_Y);

    /**
     * @tc.steps: step5. Set TouchType UP and call callback.
     * @tc.expected: touchBreak_ is set false.
     */
    localLocationInfo.SetTouchType(TouchType::UP);
    touches.clear();
    touches.emplace_back(localLocationInfo);
    touchEventInfo.touches_ = touches;
    columnPattern_->animationBreak_ = false;
    touchListener(touchEventInfo);
    EXPECT_FALSE(columnPattern_->touchBreak_);

    /**
     * @tc.steps: step5. Set animationBreak_ true and call callback.
     * @tc.expected: yOffset_ is set 0.
     */
    columnPattern_->animationBreak_ = true;
    touchListener(touchEventInfo);
    EXPECT_FLOAT_EQ(columnPattern_->yOffset_, 0.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest009
 * @tc.desc: Test DatePickerColumnPattern FlushAnimationTextProperties.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add random dateTextProperties to animationProperties_.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    DateTextProperties dateTextProperties;
    dateTextProperties.upFontSize = Dimension(UP_FONT_SIZE);
    dateTextProperties.fontSize = Dimension(TEST_FONT_SIZE);
    dateTextProperties.downFontSize = Dimension(DOWN_FONT_SIZE);
    dateTextProperties.upColor = Color::RED;
    dateTextProperties.currentColor = Color::BLUE;
    dateTextProperties.downColor = Color::GREEN;
    columnPattern_->animationProperties_.clear();
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);

    /**
     * @tc.steps: step2. Call AddAnimationTextProperties function.
     * @tc.expected: animationProperties_'s size is added to 2.
     */
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textLayoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE));
    columnPattern_->optionProperties_.clear();
    columnPattern_->AddAnimationTextProperties(0, textLayoutProperty);
    EXPECT_EQ(columnPattern_->animationProperties_.size(), 2);

    /**
     * @tc.steps: step3. Call FlushAnimationTextProperties function.
     * @tc.expected: animationProperties_'s properties is changed.
     */
    columnPattern_->FlushAnimationTextProperties(false);
    EXPECT_EQ(columnPattern_->animationProperties_[1].upFontSize, Dimension(UP_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].fontSize, Dimension(TEST_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].downFontSize, Dimension(DOWN_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[1].upColor, Color::RED);
    EXPECT_EQ(columnPattern_->animationProperties_[1].currentColor, Color::BLUE);
    EXPECT_EQ(columnPattern_->animationProperties_[1].downColor, Color::GREEN);
    EXPECT_EQ(columnPattern_->animationProperties_[0].upFontSize, Dimension());
    EXPECT_EQ(columnPattern_->animationProperties_[0].fontSize, Dimension(UP_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[0].downFontSize, Dimension(TEST_FONT_SIZE));
    EXPECT_EQ(columnPattern_->animationProperties_[0].upColor, Color());
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    EXPECT_EQ(
        columnPattern_->animationProperties_[0].currentColor, colorEvaluator->Evaluate(Color(), Color::BLUE, 0.5));
    EXPECT_EQ(columnPattern_->animationProperties_[0].downColor, Color::BLUE);
}

/**
 * @tc.name: DatePickerColumnPatternTest010
 * @tc.desc: Test DatePickerColumnPattern TextPropertiesLinearAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add random dateTextProperties to animationProperties_.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    DateTextProperties dateTextProperties;
    dateTextProperties.upFontSize = Dimension(UP_FONT_SIZE);
    dateTextProperties.fontSize = Dimension(TEST_FONT_SIZE);
    dateTextProperties.downFontSize = Dimension(DOWN_FONT_SIZE);
    dateTextProperties.upFontWeight = FontWeight::BOLD;
    dateTextProperties.fontWeight = FontWeight::BOLDER;
    dateTextProperties.downFontWeight = FontWeight::LIGHTER;
    dateTextProperties.upColor = Color::RED;
    dateTextProperties.currentColor = Color::BLUE;
    dateTextProperties.downColor = Color::GREEN;
    columnPattern_->animationProperties_.clear();
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);
    columnPattern_->animationProperties_.emplace_back(dateTextProperties);

    /**
     * @tc.steps: step2. Call TextPropertiesLinearAnimation while index is equal to midIndex.
     * @tc.expected: textLayoutProperty's properties is changed.
     */
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 2, 0, false, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 4, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 4, true, 1.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 2, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 2, true, 1.0f);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    Dimension updateSize = columnPattern_->LinearFontSize(
        Dimension(TEST_FONT_SIZE), Dimension(UP_FONT_SIZE), columnPattern_->distancePercent_);
    EXPECT_EQ(textLayoutProperty->GetFontSize().value(), updateSize);
    Color updateColor = AceType::MakeRefPtr<LinearEvaluator<Color>>()->Evaluate(
        Color::BLUE, Color::RED, static_cast<float>(columnPattern_->distancePercent_));
    EXPECT_EQ(textLayoutProperty->GetTextColor(), updateColor);

    /**
     * @tc.steps: step3. Call TextPropertiesLinearAnimation while index is one bigger than midIndex.
     * @tc.expected: textLayoutProperty's properties is changed.
     */
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 0, true, 0.0f);
    columnPattern_->TextPropertiesLinearAnimation(textLayoutProperty, 1, 0, true, 1.0f);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    updateSize = columnPattern_->LinearFontSize(
        Dimension(TEST_FONT_SIZE), Dimension(UP_FONT_SIZE), columnPattern_->distancePercent_);
    EXPECT_EQ(textLayoutProperty->GetFontSize().value(), updateSize);
    updateColor = AceType::MakeRefPtr<LinearEvaluator<Color>>()->Evaluate(
        Color::BLUE, Color::RED, static_cast<float>(columnPattern_->distancePercent_));
    EXPECT_EQ(textLayoutProperty->GetTextColor(), updateColor);
}

/**
 * @tc.name: DatePickerColumnPatternTest011
 * @tc.desc: Test DatePickerColumnPattern infrequent branches.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnNode_, nullptr);
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->UpdateTextPropertiesLinear(true, 2.0f);
    columnPattern_->showCount_ = 1;
    columnPattern_->UpdateTextPropertiesLinear(true, 0.5f);

    /**
     * @tc.steps: step2. Call HandleDragMove while inputEventType is AXIS and sourceTool is MOUSE.
     * @tc.expected: animationBreak_ is set false.
     */
    auto eventHub = columnNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    columnPattern_->InitPanEvent(gestureHub);
    auto actionEndTask = columnPattern_->panEvent_->actionEnd_;
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    actionEndTask(info);
    columnPattern_->HandleDragMove(info);
    EXPECT_FALSE(columnPattern_->animationBreak_);

    /**
     * @tc.steps: step3. Call HandleDragMove while inputEventType is AXIS and sourceTool is FINGER.
     * @tc.expected: yLast_ is changed.
     */
    info.SetSourceTool(SourceTool::FINGER);
    Point globalPoint(1.0f, 1.0f);
    info.SetGlobalPoint(globalPoint);
    info.SetOffsetX(1.0f);
    info.SetOffsetY(1.0f);
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->pressed_ = true;
    columnPattern_->HandleDragMove(info);
    EXPECT_FLOAT_EQ(columnPattern_->yLast_, 2.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest014
 * @tc.desc: Test DatePickerColumnPattern UpdateFinishToss.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto options = columnPattern_->GetOptions();
    auto pickerDates = options[columnNode_];
    pickerDates.clear();
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    options[columnNode_] = pickerDates;
    columnPattern_->options_ = options;

    /**
     * @tc.steps: step2. Call UpdateFinishToss while scroll can move.
     * @tc.expected: ScrollDelta_ is added.
     */
    columnPattern_->showCount_ = pickerDates.size() * 2;
    columnPattern_->SetCurrentIndex(5);
    columnPattern_->UpdateFinishToss(OFFSET_Y);
    EXPECT_FALSE(columnPattern_->CanMove(true));
    columnPattern_->SetCurrentIndex(1);
    EXPECT_TRUE(columnPattern_->CanMove(true));
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.prevDistance = 0.0f;
    datePickerOptionProperty.nextDistance = 1.0f;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->UpdateFinishToss(OFFSET_Y);
    EXPECT_EQ(columnPattern_->scrollDelta_, 1.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest015
 * @tc.desc: Test DatePickerColumnPattern CalcScrollIndex.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    /**
     * @tc.steps: step2. Call CalcScrollIndex with different parameters.
     * @tc.expected: Function return correct index.
     */
    EXPECT_EQ(
        columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, SMALL_SHOWCOUNT), MIDDLE_OF_COUNTS - 1);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, -SMALL_SHOWCOUNT),
        BIG_SHOWCOUNT - SMALL_SHOWCOUNT);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, false, 0), BIG_SHOWCOUNT);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(MIDDLE_OF_COUNTS, BIG_SHOWCOUNT, true, SMALL_SHOWCOUNT), 0);
    EXPECT_EQ(columnPattern_->CalcScrollIndex(0, BIG_SHOWCOUNT, true, SMALL_SHOWCOUNT), BIG_SHOWCOUNT);
}

/**
 * @tc.name: DatePickerColumnPatternTest016
 * @tc.desc: Test DatePickerColumnPattern GetShiftDistanceForLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and set pickerTheme.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->showOptionCount_ = -2;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));

    /**
     * @tc.steps: step2. Call GetShiftDistanceForLandscape in different situation.
     * @tc.expected: Function return correct distance.
     */
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::DOWN), 0.0f);
    pickerTheme->showOptionCount_ = 1;
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.height = DOWN_FONT_SIZE;
    datePickerOptionProperty.fontheight = TEST_FONT_SIZE;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::UP), -DOWN_FONT_SIZE);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(0, DatePickerScrollDirection::DOWN), 25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(1, DatePickerScrollDirection::DOWN), 25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(2, DatePickerScrollDirection::DOWN), DOWN_FONT_SIZE);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(2, DatePickerScrollDirection::UP), -25.0f);
    EXPECT_FLOAT_EQ(columnPattern_->GetShiftDistanceForLandscape(3, DatePickerScrollDirection::UP), 0.0f);
}

/**
 * @tc.name: DatePickerColumnPatternTest017
 * @tc.desc: Test DatePickerColumnPattern UpdateColumnChildPosition.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    auto options = columnPattern_->GetOptions();
    auto pickerDates = options[columnNode_];
    pickerDates.clear();
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    pickerDates.emplace_back(PickerDateF::CreateYear(START_YEAR));
    options[columnNode_] = pickerDates;
    columnPattern_->options_ = options;

    /**
     * @tc.steps: step2. Call UpdateColumnChildPosition in different situation.
     * @tc.expected: offsetCurSet_ and yOffset_ is set.
     */
    columnPattern_->SetCurrentIndex(5);
    columnPattern_->UpdateColumnChildPosition(OFFSET_Y);
    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.prevDistance = TEST_FONT_SIZE;
    datePickerOptionProperty.nextDistance = DOWN_FONT_SIZE;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->showCount_ = 0;
    columnPattern_->yLast_ = 0.0f;
    columnPattern_->yOffset_ = 0.0f;
    columnPattern_->UpdateColumnChildPosition(OFFSET_Y);
    EXPECT_FLOAT_EQ(columnPattern_->offsetCurSet_, OFFSET_Y);
    EXPECT_FLOAT_EQ(columnPattern_->yOffset_, OFFSET_Y);
}

/**
 * @tc.name: DatePickerColumnPatternTest020
 * @tc.desc: Test DatePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerColumnPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].height = SECLECTED_TEXTNODE_HEIGHT;
    columnPattern_->optionProperties_[midSize - 1].height = OTHER_TEXTNODE_HEIGHT;

    /**
     * @tc.steps: step2. Set height 50.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The middle textnode hot zone set is correct.
     */
    float height = 50.0f;
    columnPattern_->size_.SetWidth(COLUMN_WIDTH);
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    auto childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize));
    ASSERT_NE(childNode, nullptr);
    auto gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(), height);

    /**
     * @tc.steps: step3. Set height 100.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The candidate textnode hot zone set is correct.
     */
    height = 100.0f;
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize - 1));
    ASSERT_NE(childNode, nullptr);
    gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(), (height - SECLECTED_TEXTNODE_HEIGHT) / MIDDLE_OF_COUNTS);

    /**
     * @tc.steps: step4. Set height 200.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The disappear textnode hot zone set is correct.
     */
    height = 200.0f;
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize - MIDDLE_OF_COUNTS));
    ASSERT_NE(childNode, nullptr);
    gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(),
        (height - SECLECTED_TEXTNODE_HEIGHT - MIDDLE_OF_COUNTS * OTHER_TEXTNODE_HEIGHT) / MIDDLE_OF_COUNTS);
}
/**
 * @tc.name: DataPickerDialogViewUpdateButtonStyles001
 * @tc.desc: Test UpdateButtonStyle.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DataPickerDialogViewUpdateButtonStyles001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);

    size_t sizet = 0;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto layoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    
    auto renderContext = buttonNode->GetRenderContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto buttonTheme = AceType::MakeRefPtr<ButtonTheme>();
    ASSERT_NE(buttonTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(buttonTheme));
    DatePickerDialogView::UpdateButtonStyles(buttonInfos, sizet, layoutProperty, renderContext);
    auto testval = layoutProperty->GetFontWeightValue();
    EXPECT_EQ(testval, FontWeight::W400);
}
/**
 * @tc.name: DatePickerDialogViewShow0012
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0012, TestSize.Level1)
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

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level1)
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

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus004
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewUpdateButtonDefaultFocus004, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewUpdateButtonDefaultFocus005
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewUpdateButtonDefaultFocus005, TestSize.Level1)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_COMPONENT_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: steps1. setDefaultFocus is true and call UpdateButtonDefaultFocus;
     * @tc.expected: The texts of IsDefaultFocus is equal to true;
     */
    DatePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: DatePickerDialogViewShow0013
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0013, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(SMALL_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0014
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0014, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(SMALL_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0015
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0015, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(SMALL_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0016
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0016, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(SMALL_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0017
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0017, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0018
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0018, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0019
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0019, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0020
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0020, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0021
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0021, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0022
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0022, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0023
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0023, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0024
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0024, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0025
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0025, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0026
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0026, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0027
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0027, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0028
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0028, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0029
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0029, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0030
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0030, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0031
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0031, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0032
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0032, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0033
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0033, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0034
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0034, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0035
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0035, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0036
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0036, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0037
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0037, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0038
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0038, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0039
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0039, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0040
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0040, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0041
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0041, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0042
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0042, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0043
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0043, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0044
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0044, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0045
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0045, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(BIG_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0046
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0046, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(BIG_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0047
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0047, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(BIG_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0048
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0048, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(BIG_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0049
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewShow0049, TestSize.Level1)
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

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetCurrentIndex(0);
    columnPattern->UpdateToss(PATTERN_OFFSET);

    auto timePickerSwitchEvent =
        DatePickerDialogView::CreateAndSetTimePickerSwitchEvent(midStackNode, dateNode, columnNode);
    int32_t setApiVersion = 11;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto dialogViewNode =
        DatePickerDialogView::CreateNextPrevButtonNode(timePickerSwitchEvent, dateNode, buttonInfos, columnNode);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    dialogViewNode =
        DatePickerDialogView::CreateNextPrevButtonNode(timePickerSwitchEvent, dateNode, buttonInfos, columnNode);
}

/**
 * @tc.name: DatePickerPatternTest001
 * @tc.desc: Test OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerPatternTest111, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->OnModifyDone();

    datePickerPattern->isFiredDateChange_ = true;
    datePickerPattern->OnModifyDone();

    datePickerPattern->isFiredDateChange_ = false;
    datePickerPattern->showMonthDays_ = true;
    datePickerPattern->OnModifyDone();
}

/**
 * @tc.name: DatePickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontScaleValue001, TestSize.Level1)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: DatePickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test DatePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontScaleValue002, TestSize.Level1)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontSizeLimitTest001, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontSizeLimitTest002, TestSize.Level1)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontSizeLimitTest003, TestSize.Level1)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: DatePickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test DatePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewConvertFontSizeLimitTest004, TestSize.Level1)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = DatePickerDialogView::ConvertFontSizeLimit(fontSizeValue, fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewGetUserSettingLimitTest001, TestSize.Level1)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewGetUserSettingLimitTest002, TestSize.Level1)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewGetUserSettingLimitTest003, TestSize.Level1)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: DatePickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test DatePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNg, DatePickerDialogViewGetUserSettingLimitTest004, TestSize.Level1)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = DatePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

} // namespace OHOS::Ace::NG

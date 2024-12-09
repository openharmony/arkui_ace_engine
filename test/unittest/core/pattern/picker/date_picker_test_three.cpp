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

#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double PATTERN_OFFSET = 1000;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
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
const std::string SELECTED_DATE_STRING = R"({"year":2000,"month":5,"day":6,"hour":1,"minute":1,"status":-1})";
constexpr double COLUMN_VELOCITY = 2000.0;
const std::string AM = "上午";
const std::string PM = "下午";
const std::string COLON = ":";
const std::string ZERO = "0";
} // namespace

class DatePickerTestThree : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();
    DatePickerSettingData CreateDatePickerSettingData();

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

void DatePickerTestThree::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestThree::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestThree::SetUp()
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

void DatePickerTestThree::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestThree::CreateDatePickerColumnNode()
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

DatePickerSettingData DatePickerTestThree::CreateDatePickerSettingData()
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
    return settingData;
}

/**
 * @tc.name: DatePickerRowLayoutPropertyToJsonValue001
 * @tc.desc: Test DatePickerRowLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestThree, DatePickerRowLayoutPropertyToJsonValue001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerRowLayoutPropertyReset001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerRowLayoutPropertyClone001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest002, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest003, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest004, TestSize.Level1)
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
 * @tc.name: DatePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of DatePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg002, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg003, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg004, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg005, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAccessibilityPropertyTestNg006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);

    auto datePickerPattern = pickerFrameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    auto lunarDate = datePickerPattern->SolarToLunar(datePickerPattern->GetCurrentDate());
    datePickerPattern->LunarColumnsBuilding(lunarDate);
    std::string allColumnsText = "";
    for (const auto& child : pickerFrameNode->GetChildren()) {
        auto stackMonthDays = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(stackMonthDays, nullptr);
        auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
        ASSERT_NE(blendMonthDays, nullptr);
        auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
        ASSERT_NE(monthDaysColumnNode, nullptr);
        auto columnPattern = monthDaysColumnNode->GetPattern<DatePickerColumnPattern>();
        ASSERT_NE(columnPattern, nullptr);
        auto index = columnPattern->GetCurrentIndex();
        auto options = columnPattern->GetOptions();
        auto it = options.find(monthDaysColumnNode);
        if (it != options.end() && index >= 0 && index < it->second.size()) {
            auto date = it->second.at(index);
            allColumnsText.append(DatePickerPattern::GetFormatString(date));
        }
    }

    datePickerPattern->SetShowLunar(false);

    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    auto accessibilityProperty = pickerFrameNode->GetAccessibilityProperty<DatePickerAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));

    datePickerPattern->SetShowLunar(true);
    EXPECT_EQ(accessibilityProperty->GetText(), allColumnsText);
}

/**
 * @tc.name: DatePickerPaintTest001
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestThree, DatePickerPaintTest001, TestSize.Level1)
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
    std::unique_ptr<PaintWrapper> paintWrapper =
        std::make_unique<PaintWrapper>(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = datePickerPaintMethod->GetForegroundDrawFunction(paintWrapper.get());
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
HWTEST_F(DatePickerTestThree, DatePickerPaintTest002, TestSize.Level1)
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
    std::unique_ptr<PaintWrapper> paintWrapper =
        std::make_unique<PaintWrapper>(renderContext, geometryNode, pickerPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    auto canvasDrawFunction = datePickerPaintMethod->GetForegroundDrawFunction(paintWrapper.get());
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest005, TestSize.Level1)
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
    const float frameWidth = 10.0f;
    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(PATTERN_OFFSET);
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(frameWidth);
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest006, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest007, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest008, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAlgorithmTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerAlgorithmTest002, TestSize.Level1)
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
 * @tc.name: DatePickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestThree, DatePickerFireChangeEventTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest002, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest003, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest004, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest006, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerColumnPatternTest007, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerModelTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest009, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest010, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest011, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest012, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest013, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest014, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest015, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerPatternTest016, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerTest017, TestSize.Level1)
{
    DatePickerSettingData settingData = CreateDatePickerSettingData();
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
HWTEST_F(DatePickerTestThree, PerformActionTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, DatePickerEventActionsTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest001, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest002, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest003, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest004, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest005, TestSize.Level1)
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
HWTEST_F(DatePickerTestThree, TossAnimationControllerTest006, TestSize.Level1)
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

} // namespace OHOS::Ace::NG

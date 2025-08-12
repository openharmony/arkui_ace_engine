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


#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
const int YEARINDEX = 1;
const int MONTHINDEX = 5;
const int DAYINDEX = 12;
const std::string CONNECTER = "-";
const std::vector<int> DEFAULT_MONTH_DAY = { 1, 2, 3 };
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr uint8_t PIXEL_ROUND = 18;
const std::unordered_map<std::string, std::string> EXPECT_DATE_ORDER_MAP = {
    { "ug", "y-d-M" },
    { "ar", "y-M-d" },
    { "fa", "y-M-d" },
    { "ur", "y-M-d" },
    { "iw", "y-M-d" },
    { "he", "y-M-d" },
};

RefPtr<Theme> GetTheme(ThemeType type)
{
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
}
} // namespace

class DatePickerOrderTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    static void CreateDateColumn(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateYearColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);
    static RefPtr<FrameNode> CreateMonthColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);
    static RefPtr<FrameNode> CreateDayColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
    std::string oldLanguage_;
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

void DatePickerOrderTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerOrderTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerOrderTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    oldLanguage_ = AceApplicationInfo::GetInstance().GetLanguage();
}

void DatePickerOrderTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerOrderTest::CreateDateColumn(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode)
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    auto blendNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    layoutProperty->UpdateLayoutWeight(1);
    stackNode->MountToParent(dateNode);
    columnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
}

RefPtr<FrameNode> DatePickerOrderTest::CreateYearColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
{
    auto yearId = pattern->GetYearId();
    RefPtr<FrameNode> yearColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, yearId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(yearColumnNode, nullptr);
    bool hasYearNode = pattern->HasYearNode();
    if (!hasYearNode) {
        for (uint32_t index = 0; index < count; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(yearColumnNode);
        }
        yearColumnNode->MarkModifyDone();
        pattern->SetColumn(yearColumnNode);
    }
    return yearColumnNode;
}

RefPtr<FrameNode> DatePickerOrderTest::CreateMonthColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
{
    auto monthId = pattern->GetMonthId();
    RefPtr<FrameNode> monthColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, monthId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(monthColumnNode, nullptr);
    bool hasMonthNode = pattern->HasMonthNode();
    if (!hasMonthNode) {
        for (uint32_t index = 0; index < count; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(monthColumnNode);
        }
        monthColumnNode->MarkModifyDone();
        pattern->SetColumn(monthColumnNode);
    }
    return monthColumnNode;
}

RefPtr<FrameNode> DatePickerOrderTest::CreateDayColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
{
    auto dayId = pattern->GetDayId();
    RefPtr<FrameNode> dayColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, dayId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(dayColumnNode, nullptr);
    bool hasDayNode = pattern->HasDayNode();
    if (!hasDayNode) {
        for (uint32_t index = 0; index < count; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(dayColumnNode);
        }
        dayColumnNode->MarkModifyDone();
        pattern->SetColumn(dayColumnNode);
    }
    return dayColumnNode;
}

/**
 * @tc.name: DatePickerOrder001
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder001, TestSize.Level1)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    /**
     * @tc.steps: steps1. creat datePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.showTime = true;
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
    /**
     * columnMonthDayNode columnPattern
     */
    auto customNode = dialogNode->GetPattern<DialogPattern>()->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<FrameNode>(pickerRow->GetFirstChild());
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    auto stackMonthDaysNode = AceType::DynamicCast<FrameNode>(monthDaysNode->GetLastChild());
    auto blendMonthDaysNode = AceType::DynamicCast<FrameNode>(stackMonthDaysNode->GetLastChild());
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDaysNode->GetLastChild());
    auto monthDaysColumnPattern = monthDaysColumnNode->GetPattern<DatePickerColumnPattern>();
    monthDaysColumnPattern->SetCurrentIndex(YEARINDEX);
    auto options = monthDaysColumnPattern->GetOptions();
    options[monthDaysColumnNode].clear();
    monthDaysColumnPattern->SetOptions(options);
    auto textNode = AceType::DynamicCast<FrameNode>(monthDaysColumnNode->GetChildAtIndex(1));
    auto textPattern = textNode->GetPattern<TextPattern>();
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    for (auto& Value : DEFAULT_MONTH_DAY) {
        options[monthDaysColumnNode].emplace_back(PickerDateF::CreateMonthDay(Value, Value));
    }
    monthDaysColumnPattern->SetOptions(options);
    DateTime date;
    date.month = DEFAULT_MONTH_DAY.at(YEARINDEX);
    date.day = DEFAULT_MONTH_DAY.at(YEARINDEX);
    EXPECT_EQ(textLayoutProperty->GetContentValue(),
        StringUtils::Str8ToStr16(Localization::GetInstance()->FormatDateTime(date, "MMdd")));
}

/**
 * @tc.name: DatePickerOrder002
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder002, TestSize.Level1)
{
    const std::string language = "zh";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    /**
     * @tc.steps: steps1. creat datePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.showTime = true;
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
    /**
     * columnMonthDayNode columnPattern
     */
    auto customNode = dialogNode->GetPattern<DialogPattern>()->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<FrameNode>(pickerRow->GetFirstChild());
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    auto stackMonthDaysNode = AceType::DynamicCast<FrameNode>(monthDaysNode->GetLastChild());
    auto blendMonthDaysNode = AceType::DynamicCast<FrameNode>(stackMonthDaysNode->GetLastChild());
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDaysNode->GetLastChild());
    auto monthDaysColumnPattern = monthDaysColumnNode->GetPattern<DatePickerColumnPattern>();
    monthDaysColumnPattern->SetCurrentIndex(YEARINDEX);
    auto options = monthDaysColumnPattern->GetOptions();
    options[monthDaysColumnNode].clear();
    monthDaysColumnPattern->SetOptions(options);
    auto textNode = AceType::DynamicCast<FrameNode>(monthDaysColumnNode->GetChildAtIndex(1));
    auto textPattern = textNode->GetPattern<TextPattern>();
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    for (auto& Value : DEFAULT_MONTH_DAY) {
        options[monthDaysColumnNode].emplace_back(PickerDateF::CreateMonthDay(Value, Value));
    }
    monthDaysColumnPattern->SetOptions(options);
    DateTime date;
    date.month = DEFAULT_MONTH_DAY.at(YEARINDEX);
    date.day = DEFAULT_MONTH_DAY.at(YEARINDEX);
    EXPECT_EQ(textLayoutProperty->GetContentValue(),
        StringUtils::Str8ToStr16(Localization::GetInstance()->FormatDateTime(date, "MMdd")));
}

/**
 * @tc.name: DatePickerOrder003
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder003, TestSize.Level1)
{
    const std::string language = "ug";
    const std::string countryOrRegion = "CN";
    const std::string script = "Hans";
    const std::string keywordsAndValues = "";
    /**
     * @tc.steps: steps1. creat datePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.showTime = true;
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
    /**
     * columnMonthDayNode columnPattern
     */
    auto customNode = dialogNode->GetPattern<DialogPattern>()->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<FrameNode>(pickerRow->GetFirstChild());
    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);
    auto stackMonthDaysNode = AceType::DynamicCast<FrameNode>(monthDaysNode->GetLastChild());
    auto blendMonthDaysNode = AceType::DynamicCast<FrameNode>(stackMonthDaysNode->GetLastChild());
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDaysNode->GetLastChild());
    auto monthDaysColumnPattern = monthDaysColumnNode->GetPattern<DatePickerColumnPattern>();
    monthDaysColumnPattern->SetCurrentIndex(YEARINDEX);
    auto options = monthDaysColumnPattern->GetOptions();
    options[monthDaysColumnNode].clear();
    monthDaysColumnPattern->SetOptions(options);
    auto textNode = AceType::DynamicCast<FrameNode>(monthDaysColumnNode->GetChildAtIndex(1));
    auto textPattern = textNode->GetPattern<TextPattern>();
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    for (auto& Value : DEFAULT_MONTH_DAY) {
        options[monthDaysColumnNode].emplace_back(PickerDateF::CreateMonthDay(Value, Value));
    }
    monthDaysColumnPattern->SetOptions(options);
    DateTime date;
    date.month = DEFAULT_MONTH_DAY.at(YEARINDEX);
    date.day = DEFAULT_MONTH_DAY.at(YEARINDEX);
    EXPECT_EQ(textLayoutProperty->GetContentValue(),
        StringUtils::Str8ToStr16(Localization::GetInstance()->FormatDateTime(date, "MMdd")));
}

/**
 * @tc.name: DatePickerOrder004
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder004, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-d-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder005
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder005, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-M-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder006
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder006, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-d-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder007
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder007, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-y-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder008
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder008, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-M-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder009
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder009, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(dialogTheme->GetConfirmText());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-y-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder010
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder010, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-d-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + YEARINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder011
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder011, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-d-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + MONTHINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder012
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder012, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-y-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + DAYINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder013
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder013, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-y-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + YEARINDEX));
}

/**
 * @tc.name: DatePickerOrder014
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder014, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-y-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + MONTHINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder015
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder015, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("M-d-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + DAYINDEX));
}

/**
 * @tc.name: DatePickerOrder016
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder016, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-M-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + YEARINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder017
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder017, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-M-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + MONTHINDEX));
}

/**
 * @tc.name: DatePickerOrder018
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder018, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-M-y");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + DAYINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder019
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder019, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-y-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + YEARINDEX));
}

/**
 * @tc.name: DatePickerOrder020
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder020, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-y-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + MONTHINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder021
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder021, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("d-y-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + DAYINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder022
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder022, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-d-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + YEARINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder023
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder023, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-d-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + MONTHINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder024
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder024, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-d-M");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + DAYINDEX));
}

/**
 * @tc.name: DatePickerOrder025
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder025, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-M-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto yearColumnPattern = yearColumnNode->GetPattern<DatePickerColumnPattern>();
    yearColumnPattern->SetCurrentIndex(YEARINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear() + YEARINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder026
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder026, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-M-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto monthColumnPattern = monthColumnNode->GetPattern<DatePickerColumnPattern>();
    monthColumnPattern->SetCurrentIndex(MONTHINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth()) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay() + MONTHINDEX));
}

/**
 * @tc.name: DatePickerOrder027
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder027, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    datePickerPattern->SetDateOrder("y-M-d");
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->SetCancelNode(buttonCancelNode);
    datePickerPattern->OnLanguageConfigurationUpdate();
    auto dayColumnPattern = dayColumnNode->GetPattern<DatePickerColumnPattern>();
    dayColumnPattern->SetCurrentIndex(DAYINDEX);
    PickerDate pickerDate = datePickerPattern->startDateSolar_;
    EXPECT_EQ(datePickerPattern->GetText(), std::to_string(pickerDate.GetYear()) + CONNECTER +
                                                    std::to_string(pickerDate.GetMonth() + DAYINDEX) + CONNECTER +
                                                    std::to_string(pickerDate.GetDay()));
}

/**
 * @tc.name: DatePickerOrder028
 * @tc.desc: Test DatePickerOrder
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder028, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    datePickerPattern->HandleReduceLunarMonthDaysChange(0);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->HandleReduceLunarMonthDaysChange(0);

    auto stackYear = AccessibilityManager::DynamicCast<FrameNode>(datePickerNode->GetChildAtIndex(1));
    auto blendYear = AccessibilityManager::DynamicCast<FrameNode>(stackYear->GetLastChild());
    auto yearDaysNode = AccessibilityManager::DynamicCast<FrameNode>(blendYear->GetLastChild());
    yearDaysNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(2);
    datePickerPattern->HandleReduceLunarMonthDaysChange(0);

    auto stackMonthDays = AccessibilityManager::DynamicCast<FrameNode>(datePickerNode->GetChildAtIndex(0));
    auto blendMonthDays = AccessibilityManager::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    auto monthDaysNode = AccessibilityManager::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    monthDaysNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(1);
    datePickerPattern->HandleReduceLunarMonthDaysChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerOrder029
 * @tc.desc: Test HandleReduceLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder029, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    datePickerPattern->HandleReduceLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);

    auto allChildNode = datePickerPattern->GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(2);
    datePickerPattern->HandleReduceLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);

    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(1);
    datePickerPattern->HandleReduceLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerOrder030
 * @tc.desc: Test HandleReduceLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder030, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);

    auto allChildNode = datePickerPattern->GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(3);
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(5);
    datePickerPattern->HandleReduceLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerOrder031
 * @tc.desc: Test HandleReduceLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder031, TestSize.Level1)
{
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    datePickerNode->MountToParent(pickerStack);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    if (!hasYearNode) {
        CreateDateColumn(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateDateColumn(monthColumnNode, datePickerNode);
    }
    if (!hasDayNode) {
        CreateDateColumn(dayColumnNode, datePickerNode);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);

    auto allChildNode = datePickerPattern->GetAllChildNode();
    auto yearNode = allChildNode["year"];
    auto monthNode = allChildNode["month"];
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(3);
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(6);
    datePickerPattern->HandleReduceLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerOrder032
 * @tc.desc: Test DatePickerDialog OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder032, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set the initial language and city.
     */
    const std::string language = "ug";
    const std::string countryOrRegion = "Kashgar";
    const std::string script = "维吾尔";
    const std::string keywordsAndValues = "";

    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);

    /**
     * @tc.steps: steps2. Create DatePickerDialog.
     */
    DialogProperties dialogProperties;

    DatePickerSettingData settingData;
    settingData.lunarswitch = true;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo buttonInfo;
    buttonInfo.fontWeight = FontWeight::W400;
    buttonInfos.push_back(buttonInfo);

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto firstColumnNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(firstColumnNode, nullptr);

    auto secondColumnNode = AceType::DynamicCast<FrameNode>(firstColumnNode->GetFirstChild());
    ASSERT_NE(secondColumnNode, nullptr);

    auto midStackNode = AceType::DynamicCast<FrameNode>(secondColumnNode->GetChildAtIndex(1));
    ASSERT_NE(midStackNode, nullptr);

    auto datePickerNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);

    /**
     * @tc.steps: steps3. Switch language and city.
     * @tc.expected: The dateOrder_ changed, and isDateOrderChange_ equals true.
     */
    const std::string newLanguage = "fa";
    const std::string newCountryOrRegion = "Hamedan";
    const std::string newScript = "哈马丹";
    const std::string newKeywordsAndValues = "";
    AceApplicationInfo::GetInstance().SetLocale(newLanguage, newCountryOrRegion, newScript, newKeywordsAndValues);

    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(newLanguage)->second);
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, true);

    /**
     * @tc.steps: steps4. OnModifyDone update the properties and layout.
     * @tc.expected: The isDateOrderChange_ equals false.
     */
    datePickerPattern->OnModifyDone();
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, false);
}

/**
 * @tc.name: DatePickerOrder033
 * @tc.desc: Test DatePicker OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder033, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Set the initial language and city.
    */
    const std::string language = "ug";
    const std::string countryOrRegion = "Kashgar";
    const std::string script = "维吾尔";
    const std::string keywordsAndValues = "";

    AceApplicationInfo::GetInstance().SetLocale(language, countryOrRegion, script, keywordsAndValues);

    /**
    * @tc.steps: steps2. Create DatePicker.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    frameNode->MarkModifyDone();
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);

    /**
     * @tc.steps: steps3. Switch language and city.
     * @tc.expected: The dateOrder_ changed, and isDateOrderChange_ equals true.
     */
    const std::string newLanguage = "fa";
    const std::string newCountryOrRegion = "Hamedan";
    const std::string newScript = "哈马丹";
    const std::string newKeywordsAndValues = "";
    AceApplicationInfo::GetInstance().SetLocale(newLanguage, newCountryOrRegion, newScript, newKeywordsAndValues);

    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(newLanguage)->second);
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, true);

    /**
    * @tc.steps: steps4. OnModifyDone update the properties and layout.
    * @tc.expected: The isDateOrderChange_ equals false.
    */
    datePickerPattern->OnModifyDone();
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, false);
}

/**
 * @tc.name: DatePickerOrder034
 * @tc.desc: Test DatePicker OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder034, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Create DatePicker.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    frameNode->MarkModifyDone();

    /**
    * @tc.steps: steps2. Set the initial language and city.
    */
    const std::string language = "ar";
    AceApplicationInfo::GetInstance().SetLocale(language, "Egypt", "Arabic", "");

    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);
    EXPECT_EQ(datePickerPattern->isDirectionSetByAr, true);

    /**
     * @tc.steps: steps3. Switch language and city.
     * @tc.expected: The dateOrder_ changed, and isDateOrderChange_ equals true.
     */
    const std::string newLanguage = "ug";
    AceApplicationInfo::GetInstance().SetLocale(newLanguage, "Kashgar", "Uyghur", "");

    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(newLanguage)->second);
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, true);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::AUTO);
    EXPECT_EQ(datePickerPattern->isDirectionSetByAr, false);
    AceApplicationInfo::GetInstance().language_ = oldLanguage_;
}

/**
 * @tc.name: DatePickerOrder035
 * @tc.desc: Test DatePickerDialog OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder035, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create DatePickerDialog.
     */
    DialogProperties dialogProperties;

    DatePickerSettingData settingData;
    settingData.lunarswitch = true;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo buttonInfo;
    buttonInfo.fontWeight = FontWeight::W400;
    buttonInfos.push_back(buttonInfo);

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto firstColumnNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(firstColumnNode, nullptr);

    auto secondColumnNode = AceType::DynamicCast<FrameNode>(firstColumnNode->GetFirstChild());
    ASSERT_NE(secondColumnNode, nullptr);

    auto midStackNode = AceType::DynamicCast<FrameNode>(secondColumnNode->GetChildAtIndex(1));
    ASSERT_NE(midStackNode, nullptr);

    auto datePickerNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(datePickerNode, nullptr);

    /**
     * @tc.steps: steps2. Set the initial language and city.
     */
    const std::string language = "ar";
    AceApplicationInfo::GetInstance().SetLocale(language, "Egypt", "Arabic", "");

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);
    auto pickerProperty = datePickerNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);
    EXPECT_EQ(datePickerPattern->isDirectionSetByAr, true);

    /**
     * @tc.steps: steps3. Switch language and city.
     * @tc.expected: The dateOrder_ changed, and isDateOrderChange_ equals true.
     */
    const std::string newLanguage = "ug";
    AceApplicationInfo::GetInstance().SetLocale(newLanguage, "Kashgar", "Uyghur", "");

    datePickerPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(newLanguage)->second);
    EXPECT_EQ(datePickerPattern->isDateOrderChange_, true);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::AUTO);
    EXPECT_EQ(datePickerPattern->isDirectionSetByAr, false);
    AceApplicationInfo::GetInstance().language_ = oldLanguage_;
}

/**
 * @tc.name: DatePickerOrder036
 * @tc.desc: Test CreateDatePicker when the system language is set to ar.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder036, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Set the initial language and city.
    */
    const std::string language = "ar";
    AceApplicationInfo::GetInstance().SetLocale(language, "Egypt", "Arabic", "");

    /**
    * @tc.steps: steps2. Create DatePicker.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);
    AceApplicationInfo::GetInstance().language_ = oldLanguage_;
}

/**
 * @tc.name: DatePickerOrder037
 * @tc.desc: Test DatePickerDialogView Show when the system language is set to ar.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerOrderTest, DatePickerOrder037, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set the initial language and city.
     */
    const std::string language = "ar";
    AceApplicationInfo::GetInstance().SetLocale(language, "Egypt", "Arabic", "");

    /**
     * @tc.steps: steps2. Create DatePickerDialog.
     */
    DialogProperties dialogProperties;

    DatePickerSettingData settingData;
    settingData.lunarswitch = true;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo buttonInfo;
    buttonInfo.fontWeight = FontWeight::W400;
    buttonInfos.push_back(buttonInfo);

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;

    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    auto firstColumnNode = AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild());
    ASSERT_NE(firstColumnNode, nullptr);

    auto secondColumnNode = AceType::DynamicCast<FrameNode>(firstColumnNode->GetFirstChild());
    ASSERT_NE(secondColumnNode, nullptr);

    auto midStackNode = AceType::DynamicCast<FrameNode>(secondColumnNode->GetChildAtIndex(1));
    ASSERT_NE(midStackNode, nullptr);

    auto datePickerNode = AceType::DynamicCast<FrameNode>(midStackNode->GetFirstChild());
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    EXPECT_EQ(datePickerPattern->dateOrder_, EXPECT_DATE_ORDER_MAP.find(language)->second);
    auto pickerProperty = datePickerNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetLayoutDirection(), TextDirection::LTR);
    AceApplicationInfo::GetInstance().language_ = oldLanguage_;
}

} // namespace OHOS::Ace::NG

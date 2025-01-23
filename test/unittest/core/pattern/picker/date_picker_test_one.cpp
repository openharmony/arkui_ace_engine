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
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"

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
constexpr int32_t SELECTED_YEAR = 2000;
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
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
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
    DatePickerDialogView::BuildDialogAcceptAndCancelButtonForAging(buttonInfos, settingData, timePickerNode, dateNode,
        dateNode, dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
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
    DatePickerDialogView::BuildDialogAcceptAndCancelButtonForAging(buttonInfos, settingData, timePickerNode, dateNode,
        dateNode, dialogNode, contentColumn, dialogEvent, dialogCancelEvent);
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
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(3.2f);
    pipeline->fontScale_ = 5.0f;
    pipeline->rootHeight_ = 1000;
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
    /**
     * @tc.steps: step2. fontSizeValue's unit is VP and fontSizeValue is less than fontSizeLimit.
     * @tc.expected: call GetIsUserSetTextProperties and result expect equal fontSizeValue.
     */
    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    EXPECT_EQ(result.Value(), fontSizeValue.Value());
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
    pipeline->followSystem_ = true;
    pipeline->maxAppFontScale_ = 5.0f;
    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_px;
    /**
     * @tc.steps: step2. fontSizeValue's unit is NOT VP and isUserSetFont is true.
     * fontSizeValue is greater than fontSizeLimit.
     * @tc.expected: call GetIsUserSetTextProperties and result expect equal fontSizeLimit / fontSizeScale.
     */
    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, true);
    float fontSizeScale = pipeline->GetFontScale();
    auto fontSizeValueResult = fontSizeLimit / fontSizeScale;
    EXPECT_EQ(result.Value(), fontSizeValueResult.Value());
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
    /**
     * @tc.steps: step2. fontSizeValue's unit is VP and isUserSetFont is false.
     * @tc.expected: call GetIsUserSetTextProperties and result expect equal fontSizeValue.
     */
    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    EXPECT_EQ(result.Value(), fontSizeValue.Value());
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
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(2.0f);
    pipeline->rootWidth_ = 1000;
    Dimension fontSizeValue = 20.0_px;
    Dimension fontSizeLimit = 40.0_px;
    /**
     * @tc.steps: step2. fontSizeValue's unit is NOT VP and isUserSetFont is false.
     * fontSizeScale is greater than ThirdFontScale and call GetIsUserSetTextProperties
     * @tc.expected: result expect equal fontSizeValue - fontSizeLimit / fontSizeScale.
     */
    auto result = DatePickerDialogView::ConvertFontScaleValue(fontSizeValue, fontSizeLimit, false);
    float fontSizeScale = pipeline->GetMaxAppFontScale();
    auto fontSizeValueResult = fontSizeLimit / fontSizeScale;
    EXPECT_EQ((int)result.Value(), (fontSizeLimit - fontSizeValueResult).Value());
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
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(6.0f);
    pipeline->rootWidth_ = 1000;
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
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(3.2f);
    pipeline->rootWidth_ = 1000;
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

/**
 * @tc.name: SwitchContentRowButton002
 * @tc.desc: Test DatePickerDialogView SwitchContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SwitchContentRowButton002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;
    DatePickerSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    auto datePickerNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(datePickerNode, nullptr);
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    datePickerNode->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    ASSERT_NE(contentRow, nullptr);
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    ASSERT_NE(buttonTitleNode, nullptr);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    buttonTitleNode->MountToParent(contentColumn);
    datePickerPattern->SetContentRowNode(contentRow);
    contentRow->MountToParent(contentColumn);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
    auto context = datePickerNode->GetContext();
    ASSERT_NE(context, nullptr);
    DatePickerDialogView::SwitchContentRowButton(contentRow, true);
    auto nextButton = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(2));
    ASSERT_NE(nextButton, nullptr);
    auto nextButtonLayoutProperty = nextButton->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(nextButtonLayoutProperty, nullptr);
    nextButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(nextButtonLayoutProperty->propVisibility_, VisibleType::VISIBLE);
}
/**
 * @tc.name: SwitchContentRowButton003
 * @tc.desc: Test DatePickerDialogView SwitchContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SwitchContentRowButton003, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;
    DatePickerSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    auto datePickerNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(datePickerNode, nullptr);
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    datePickerNode->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    ASSERT_NE(contentRow, nullptr);
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    buttonTitleNode->MountToParent(contentColumn);
    datePickerPattern->SetContentRowNode(contentRow);
    contentRow->MountToParent(contentColumn);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
    auto context = datePickerNode->GetContext();
    ASSERT_NE(context, nullptr);
    DatePickerDialogView::switchFlag_ = true;
    DatePickerDialogView::SwitchContentRowButton(contentRow, true);
    auto confirmButton = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
    ASSERT_NE(confirmButton, nullptr);
    auto confirmLayoutProperty = confirmButton->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(confirmLayoutProperty, nullptr);
    confirmLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(confirmLayoutProperty->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: SwitchContentRowButton004
 * @tc.desc: Test DatePickerDialogView SwitchContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SwitchContentRowButton004, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;
    DatePickerSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    auto datePickerNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(datePickerNode, nullptr);
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(ElementRegister::GetInstance()->MakeUniqueId(),
        settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    datePickerNode->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    ASSERT_NE(contentRow, nullptr);
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    ASSERT_NE(buttonTitleNode, nullptr);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    buttonTitleNode->MountToParent(contentColumn);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    datePickerPattern->SetContentRowNode(contentRow);
    contentRow->MountToParent(contentColumn);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
    DatePickerDialogView::switchFlag_ = true;
    DatePickerDialogView::SwitchContentRowButton(contentRow, false);
    auto nextButton = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(2));
    ASSERT_NE(nextButton, nullptr);
    auto nextButtonLayoutProperty = nextButton->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(nextButtonLayoutProperty, nullptr);
    nextButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_EQ(nextButtonLayoutProperty->propVisibility_, VisibleType::VISIBLE);
}

/**
 * @tc.name: HideContentChildrenButton001
 * @tc.desc: Test DatePickerDialogView HideContentChildrenButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, HideContentChildrenButton001, TestSize.Level1)
{
    DatePickerSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    auto dateNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto datePickerNode = DatePickerDialogView::CreateDateNode(
        dateNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, false);
    ASSERT_NE(datePickerNode, nullptr);
    auto pickerStack = DatePickerDialogView::CreateStackNode();
    ASSERT_NE(pickerStack, nullptr);
    auto monthDaysNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto monthDaysNode = DatePickerDialogView::CreateDateNode(
        monthDaysNodeId, settingData.datePickerProperty, settingData.properties, settingData.isLunar, true);
    ASSERT_NE(monthDaysNode, nullptr);
    datePickerNode->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    ASSERT_NE(contentRow, nullptr);
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    ASSERT_NE(buttonTitleNode, nullptr);
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
    DatePickerDialogView::HideContentChildrenButton(contentRow);
    auto frameNodeChild = AceType::DynamicCast<NG::FrameNode>(contentRow->GetLastChild());
    ASSERT_NE(frameNodeChild, nullptr);
    auto layoutProperty = frameNodeChild->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: SwitchTimePickerPage001
 * @tc.desc: Test DatePickerDialogView SwitchTimePickerPage.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SwitchTimePickerPage001, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    ASSERT_NE(pickerStack, nullptr);
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    ASSERT_NE(dateNode, nullptr);
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    ASSERT_NE(pickerRow, nullptr);
    auto monthDaysNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(monthDaysNode, nullptr);
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    ASSERT_NE(timePickerNode, nullptr);
    auto contentRow = DatePickerDialogView::CreateButtonNodeForAging(
        settingData, timePickerNode, monthDaysNode, dateNode, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(contentRow, nullptr);
    auto temp = DatePickerDialogView::switchTimePickerFlag_;
    DatePickerDialogView::SwitchTimePickerPage(monthDaysNode, timePickerNode, contentRow);
    EXPECT_NE(DatePickerDialogView::switchTimePickerFlag_, temp);
}

/**
 * @tc.name: CreateLunarswitchNode001
 * @tc.desc: Test DatePickerDialogView CreateLunarswitchNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateLunarswitchNode001, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
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

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    ASSERT_NE(pickerStack, nullptr);
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    ASSERT_NE(dateNode, nullptr);
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    bool ret = false;
    auto changeEvent = [&ret](const bool check) { ret = check; };
    CheckboxSettingData checkboxData;
    DatePickerDialogView::CreateLunarswitchNode(
        contentColumn, dateNode, changeEvent, true, checkboxData);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CreateLunarswitchNode002
 * @tc.desc: Test DatePickerDialogView CreateLunarswitchNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateLunarswitchNode002, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    auto customNode = dialogPattern->GetCustomNode();
    ASSERT_NE(customNode, nullptr);
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    ASSERT_NE(pickerStack, nullptr);
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    ASSERT_NE(dateNode, nullptr);
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(contentColumn, nullptr);
    bool ret = false;
    auto changeEvent = [&ret](const bool check) { ret = check; };
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    CheckboxSettingData checkboxData;
    DatePickerDialogView::CreateLunarswitchNode(
        contentColumn, dateNode, changeEvent, true, checkboxData);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateCheckboxPaintProperty
 * @tc.desc: Test DatePickerDialogView UpdateCheckboxPaintProperty.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, UpdateCheckboxPaintProperty, TestSize.Level1)
{
    auto checkbox = FrameNode::CreateFrameNode(
        V2::CHECK_BOX_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<CheckBoxPattern>());
    CHECK_NULL_VOID(checkbox);
    auto checkboxPaintProps = checkbox->GetPaintProperty<CheckBoxPaintProperty>();
    CHECK_NULL_VOID(checkboxPaintProps);
    CheckboxSettingData checkboxData;
    checkboxData.selectedColor = Color::BLUE;
    checkboxData.unselectedColor = Color::BLUE;
    checkboxData.strokeColor = Color::BLUE;
    DatePickerDialogView::UpdateCheckboxPaintProperty(
        checkboxPaintProps, true, checkboxData);
    EXPECT_EQ(Color::BLUE, checkboxPaintProps->GetCheckBoxSelectedColor());
    EXPECT_EQ(Color::BLUE, checkboxPaintProps->GetCheckBoxUnSelectedColor());
    EXPECT_EQ(Color::BLUE, checkboxPaintProps->GetCheckBoxCheckMarkColor());
}

/**
 * @tc.name: SetTimeNodeColumnWeight001
 * @tc.desc: Test DatePickerDialogView SetTimeNodeColumnWeight.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SetTimeNodeColumnWeight001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;

    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);
    DatePickerDialogView::switchTimePickerFlag_ = false;
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    DatePickerDialogView::SetTimeNodeColumnWeight(timeNode, settingData);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(DatePickerDialogView::NeedAdaptForAging());
}

/**
 * @tc.name: SetTimeNodeColumnWeight002
 * @tc.desc: Test DatePickerDialogView SetTimeNodeColumnWeight.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SetTimeNodeColumnWeight002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;

    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);
    DatePickerDialogView::switchTimePickerFlag_ = true;
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    DatePickerDialogView::SetTimeNodeColumnWeight(timeNode, settingData);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(DatePickerDialogView::NeedAdaptForAging());
}

/**
 * @tc.name: SetTimeNodeColumnWeight003
 * @tc.desc: Test DatePickerDialogView SetTimeNodeColumnWeight.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SetTimeNodeColumnWeight003, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 2.0f;

    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = true;
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    DatePickerDialogView::SetTimeNodeColumnWeight(timeNode, settingData);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_TRUE(DatePickerDialogView::NeedAdaptForAging());
}

/**
 * @tc.name: SetTimeNodeColumnWeight004
 * @tc.desc: Test DatePickerDialogView SetTimeNodeColumnWeight.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, SetTimeNodeColumnWeight004, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 1.0f;

    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, CURRENT_DAY, CURRENT_DAY);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
    auto timeNode = DatePickerDialogView::CreateTimeNode(
        settingData.timePickerProperty, settingData.properties, settingData.useMilitary);
    ASSERT_NE(timeNode, nullptr);
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    EXPECT_EQ(MockContainer::Current()->GetApiTargetVersion(), settingApiVersion);
    DatePickerDialogView::SetTimeNodeColumnWeight(timeNode, settingData);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    EXPECT_EQ(MockContainer::Current()->GetApiTargetVersion(), backupApiVersion);
    EXPECT_FALSE(DatePickerDialogView::NeedAdaptForAging());
}

/**
 * @tc.name: CreateLunarSwitchTextNode001
 * @tc.desc: Test DatePickerDialogView CreateLunarSwitchTextNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateLunarSwitchTextNode001, TestSize.Level1)
{
    auto textNode = DatePickerDialogView::CreateLunarSwitchTextNode();
    EXPECT_NE(textNode, nullptr);
}

/**
 * @tc.name: UpdateButtonStyles001
 * @tc.desc: Test DatePickerDialogView UpdateButtonStyles.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, UpdateButtonStyles001, TestSize.Level1)
{
    int calcvalue = 100;
    NG::BorderRadiusProperty radius;
    CalcDimension radiusCalc(calcvalue, static_cast<DimensionUnit>(1));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;

    uint32_t color = 0;
    Color colorVal = Color(color);
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.fontStyle = Ace::FontStyle::ITALIC;
    info1.fontFamily = { "unknown" };
    info1.backgroundColor = colorVal;
    info1.borderRadius = radius;
    buttonInfos.push_back(info1);
    size_t sizet = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
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
    auto testval = layoutProperty->GetFontStyleValue();
    EXPECT_EQ(testval, Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: LinearFontSize001
 * @tc.desc: Test DatePickerColumnPattern LinearFontSize
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, LinearFontSize001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    Dimension startFontSize = 5.0_px;
    Dimension endFontSize = 10.0_px;
    double percent = 2.0f;

    auto result = columnPattern_->LinearFontSize(startFontSize, endFontSize, percent);
    EXPECT_EQ((int)result.Value(), 10);
}

/**
 * @tc.name: LinearFontSize002
 * @tc.desc: Test DatePickerColumnPattern LinearFontSize
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, LinearFontSize002, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    Dimension startFontSize = 5.0_px;
    Dimension endFontSize = 10.0_px;
    double percent = 0.2f;

    auto result = columnPattern_->LinearFontSize(startFontSize, endFontSize, percent);
    EXPECT_EQ((int)result.Value(), 6);
}

/**
 * @tc.name: ResetAlgorithmOffset001
 * @tc.desc: Test DatePickerColumnPattern ResetAlgorithmOffset
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ResetAlgorithmOffset001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->showCount_ = 2;
    columnPattern_->ResetAlgorithmOffset();
    EXPECT_EQ(columnPattern_->algorithmOffset_.size(), 2);
}

/**
 * @tc.name: ShiftOptionProp001
 * @tc.desc: Test DatePickerColumnPattern ShiftOptionProp
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, ShiftOptionProp001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    auto curNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(curNode, nullptr);
    auto curNodeLayoutProperty = curNode->GetLayoutProperty<TextLayoutProperty>();

    auto shiftNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(shiftNode, nullptr);
    auto shiftNodeLayoutProperty = shiftNode->GetLayoutProperty<TextLayoutProperty>();

    columnPattern_->ShiftOptionProp(curNode, shiftNode);
    ASSERT_NE(curNodeLayoutProperty, nullptr);
    ASSERT_NE(shiftNodeLayoutProperty, nullptr);
}

/**
 * @tc.name: PlayRestAnimation001
 * @tc.desc: Test DatePickerColumnPattern PlayRestAnimation
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, PlayRestAnimation001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    DatePickerOptionProperty datePickerOptionProperty;
    datePickerOptionProperty.prevDistance = 0.0f;
    datePickerOptionProperty.nextDistance = 1.0f;
    columnPattern_->optionProperties_.clear();
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);
    columnPattern_->optionProperties_.emplace_back(datePickerOptionProperty);

    columnPattern_->showCount_ = 2;
    columnPattern_->scrollDelta_ = 2.0f;
    columnPattern_->PlayRestAnimation();
    EXPECT_EQ(columnPattern_->scrollDelta_, 1.0f);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameOffset(OffsetF(10.0, 10.0));
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    config.frameSizeChange = false;
    config.frameOffsetChange = false;
    config.contentSizeChange = false;
    config.contentOffsetChange = false;

    columnPattern_->offset_ = { 0.0, 0.0 };
    columnPattern_->size_ = { 0.0, 0.0 };
    bool ret = columnPattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);

    struct DirtySwapConfig config;
    config.frameSizeChange = true;

    bool ret = columnPattern_->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameOffset(OffsetF(10.0, 10.0));
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    config.contentOffsetChange = true;

    columnPattern_->offset_ = { 0.0, 0.0 };
    columnPattern_->size_ = { 0.0, 0.0 };
    bool ret = columnPattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap004
 * @tc.desc: Test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, OnDirtyLayoutWrapperSwap004, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameOffset(OffsetF(10.0, 10.0));
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    config.frameOffsetChange = true;

    columnPattern_->offset_ = { 10.0, 10.0 };
    columnPattern_->size_ = { 0.0, 0.0 };
    bool ret = columnPattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap005
 * @tc.desc: Test DatePickerColumnPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, OnDirtyLayoutWrapperSwap005, TestSize.Level1)
{
    CreateDatePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(0));
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    firstGeometryNode->SetFrameOffset(OffsetF(10.0, 10.0));
    firstGeometryNode->SetFrameSize(SizeF(20.0, 20.0));
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);
    struct DirtySwapConfig config;
    config.contentSizeChange = true;

    columnPattern_->offset_ = { 10.0, 10.0 };
    columnPattern_->size_ = { 20.0, 20.0 };
    bool ret = columnPattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CreateLunarChangeEvent001
 * @tc.desc: Test DatePickerDialogView CreateLunarChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateLunarChangeEvent001, TestSize.Level1)
{
    DatePickerSettingData settingData;
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
    ASSERT_NE(midStackNode, nullptr);
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto layoutProp = datePickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    std::function<void(bool)> onCallback = DatePickerDialogView::CreateLunarChangeEvent(dateNode);
    ASSERT_NE(onCallback, nullptr);
    onCallback(true);
    EXPECT_TRUE(layoutProp->GetLunarValue());
}

/**
 * @tc.name: CreateAndMountMonthDaysNode001
 * @tc.desc: Test DatePickerDialogView CreateAndMountMonthDaysNode.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestOne, CreateAndMountMonthDaysNode001, TestSize.Level1)
{
    DatePickerSettingData settingData;
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
    ASSERT_NE(dateNode, nullptr);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    auto layoutProp = datePickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(pickerRow, nullptr);
    std::function<void(bool)> lunarChangeEvent = DatePickerDialogView::CreateLunarChangeEvent(dateNode);
    DatePickerDialogView::CreateAndMountMonthDaysNode(settingData, dateNode, pickerRow, std::move(lunarChangeEvent));
    ASSERT_NE(lunarChangeEvent, nullptr);
    lunarChangeEvent(true);
    EXPECT_TRUE(layoutProp->GetLunarValue());
}
} // namespace OHOS::Ace::NG

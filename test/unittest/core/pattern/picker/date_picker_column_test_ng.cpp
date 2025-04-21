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
#include "test/mock/core/common/mock_font_manager.h"
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
const std::string CONNECTER = "-";
const std::vector<int> DEFAULT_MONTH_DAY = { 1, 2, 3 };
const int MIDDLE_OF_COUNTS = 2;
constexpr double COLUMN_WIDTH = 200.0;
constexpr double SECLECTED_TEXTNODE_HEIGHT = 84.0;
constexpr double OTHER_TEXTNODE_HEIGHT = 54.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t MAX_DAY_INDEX = 31;
constexpr int32_t MAX_MONTH_INDEX = 11;
constexpr int32_t MAX_YEAR_INDEX = 200;
const int32_t API_VERSION_TWELVE = 12;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr uint8_t PIXEL_ROUND = 18;
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

class DatePickerColumnTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();
    static void CreateMonthOrDayColumnNode(
        const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode, Color buttonBackgroundColor);
    static void CreateYearColumnNode(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateYearColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);
    static RefPtr<FrameNode> CreateMonthColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);
    static RefPtr<FrameNode> CreateDayColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count);

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

void DatePickerColumnTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerColumnTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerColumnTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerColumnTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerColumnTest::CreateDatePickerColumnNode()
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

void DatePickerColumnTest::CreateMonthOrDayColumnNode(
    const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode, Color buttonBackgroundColor)
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
    buttonNode->GetRenderContext()->UpdateBackgroundColor(buttonBackgroundColor);
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    layoutProperty->UpdateLayoutWeight(1);
    stackNode->MountToParent(dateNode);
    columnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
}

void DatePickerColumnTest::CreateYearColumnNode(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode)
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

RefPtr<FrameNode> DatePickerColumnTest::CreateYearColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
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

RefPtr<FrameNode> DatePickerColumnTest::CreateMonthColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
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

RefPtr<FrameNode> DatePickerColumnTest::CreateDayColumnNode(RefPtr<DatePickerPattern>& pattern, uint32_t count)
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
 * @tc.name: DatePickerColumn001
 * @tc.desc: Test DatePickerColumnPattern OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerColumn001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
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

    /**
     * @tc.steps: step2. Set param and call OnAroundButtonClick.
     * @tc.expected: OnAroundButtonClick is executed correctly.
     */
    auto childNode = AccessibilityManager::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(0));
    auto childSize = static_cast<int32_t>(columnNode->GetChildren().size());
    RefPtr<DatePickerEventParam> param = AccessibilityManager::MakeRefPtr<DatePickerEventParam>();
    param->instance_ = childNode;
    param->itemIndex_ = 0;
    param->itemTotalCounts_ = childSize;
    columnPattern->OnAroundButtonClick(param);
    EXPECT_EQ(columnPattern->GetShowCount(), 7);
}

/**
 * @tc.name: DatePickerColumn002
 * @tc.desc: Test DatePickerColumnPattern OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerColumn002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
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

    /**
     * @tc.steps: step2. Set param and call OnAroundButtonClick.
     * @tc.expected: OnAroundButtonClick is executed correctly.
     */
    auto childNode = AccessibilityManager::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(0));
    auto childSize = static_cast<int32_t>(columnNode->GetChildren().size());
    RefPtr<DatePickerEventParam> param = AccessibilityManager::MakeRefPtr<DatePickerEventParam>();
    param->instance_ = childNode;
    param->itemIndex_ = 0;
    param->itemTotalCounts_ = childSize;
    columnPattern->SetclickBreak(true);
    columnPattern->OnAroundButtonClick(param);
    EXPECT_EQ(columnPattern->GetShowCount(), 7);
}

/**
 * @tc.name: DatePickerColumn003
 * @tc.desc: Test DatePickerColumnPattern OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerColumn003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
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

    /**
     * @tc.steps: step2. Set param and call OnAroundButtonClick.
     * @tc.expected: OnAroundButtonClick is executed correctly.
     */
    auto childNode = AccessibilityManager::DynamicCast<FrameNode>(columnNode->GetChildAtIndex(0));
    auto childSize = static_cast<int32_t>(columnNode->GetChildren().size());
    RefPtr<DatePickerEventParam> param = AccessibilityManager::MakeRefPtr<DatePickerEventParam>();
    param->instance_ = childNode;
    param->itemIndex_ = 0;
    param->itemTotalCounts_ = childSize;
    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.314f, 0.95f);
    option.SetCurve(motion);
    columnPattern->animation_ = AnimationUtils::StartAnimation(option, [&]() {});
    columnPattern->OnAroundButtonClick(param);
    EXPECT_EQ(columnPattern->GetShowCount(), 7);
}

/**
 * @tc.name: DatePickerColumn004
 * @tc.desc: Test DatePickerColumnPattern AddHotZoneRectToText.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerColumn004, TestSize.Level1)
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
     * @tc.steps: step2. Set height 400.0 for column and call AddHotZoneRectToText.
     * @tc.expected: The middle textnode hot zone set is correct.
     */
    float height = 400.0f;
    columnPattern_->size_.SetWidth(COLUMN_WIDTH);
    columnPattern_->size_.SetHeight(height);
    columnPattern_->AddHotZoneRectToText();
    auto childNode = AceType::DynamicCast<FrameNode>(columnNode_->GetChildAtIndex(midSize));
    ASSERT_NE(childNode, nullptr);
    auto gestureEventHub = childNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    auto responseRegion = gestureEventHub->GetResponseRegion().back();
    EXPECT_EQ(responseRegion.GetWidth().Value(), COLUMN_WIDTH);
    EXPECT_EQ(responseRegion.GetHeight().Value(), SECLECTED_TEXTNODE_HEIGHT);
}

/**
 * @tc.name: DatePickerColumn005
 * @tc.desc: Test DatePickerColumnPattern FlushCurrentOptions.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerColumn005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnNode and columnPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
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

    /**
     * @tc.steps: step2. Set datePickerPattern and call FlushCurrentOptions.
     * @tc.expected: FlushCurrentOptions is executed correctly.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    datePickerPattern->hasUserDefinedDisappearFontFamily_ = true;
    datePickerPattern->hasUserDefinedNormalFontFamily_ = true;
    datePickerPattern->hasUserDefinedSelectedFontFamily_ = true;
    columnPattern->FlushCurrentOptions();

    columnPattern->hasAppCustomFont_ = true;
    columnPattern->FlushCurrentOptions();

    datePickerPattern->hasUserDefinedDisappearFontFamily_ = false;
    datePickerPattern->hasUserDefinedNormalFontFamily_ = false;
    datePickerPattern->hasUserDefinedSelectedFontFamily_ = false;
    columnPattern->FlushCurrentOptions();
}

/**
 * @tc.name: DatePickerDialogView001
 * @tc.desc: Test DatePickerDialogView SwitchContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and pattern.
     */
    DatePickerSettingData settingData;
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

    /**
     * @tc.steps: step2. Set SwitchContentRowButton and call func.
     * @tc.expected: SwitchContentRowButton is executed correctly.
     */
    DatePickerDialogView::SwitchContentRowButton(contentRow, true);
    DatePickerDialogView::switchFlag_ = true;
    DatePickerDialogView::SwitchContentRowButton(contentRow, true);
    DatePickerDialogView::SwitchContentRowButton(contentRow, false);
    ASSERT_NE(contentRow, nullptr);
}

/**
 * @tc.name: DatePickerDialogView002
 * @tc.desc: Test DatePickerDialogView SwitchContentRowButton.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and pattern.
     */
    DatePickerSettingData settingData;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    auto pipeline = MockPipelineContext::GetCurrent();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
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

    /**
     * @tc.steps: step2. Set switchDatePickerFlag_ and call SwitchDatePickerPage.
     * @tc.expected: all branch of SwitchDatePickerPage is executed correctly.
     */
    DatePickerDialogView::SwitchDatePickerPage(datePickerNode, true);
    EXPECT_TRUE(DatePickerDialogView::switchDatePickerFlag_);

    DatePickerDialogView::switchDatePickerFlag_ = false;
    DatePickerDialogView::SwitchDatePickerPage(datePickerNode, false);
    EXPECT_TRUE(DatePickerDialogView::switchDatePickerFlag_);

    DatePickerDialogView::SwitchDatePickerPage(datePickerNode, true);
    EXPECT_TRUE(DatePickerDialogView::switchDatePickerFlag_);

    DatePickerDialogView::SwitchDatePickerPage(datePickerNode, false);
    EXPECT_FALSE(DatePickerDialogView::switchDatePickerFlag_);
}

/**
 * @tc.name: DatePickerDialogView003
 * @tc.desc: Test DatePickerDialogView CreateButtonNodeForAging.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
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
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
     * @tc.steps: step2.call CreateButtonNodeForAging.
     * @tc.expected:CreateButtonNodeForAging is executed correctly.
     */
    auto contentRow = DatePickerDialogView::CreateButtonNodeForAging(settingData, timePickerNode, monthDaysNode,
        dateNode, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(contentRow, nullptr);
}

/**
 * @tc.name: DatePickerDialogView004
 * @tc.desc: Test DatePickerDialogView CreateButtonNodeForAging.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    MockContainer::Current()->SetApiTargetVersion(API_VERSION_TWELVE);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    DatePickerSettingData settingData;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = true;
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
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
     * @tc.steps: step2.call CreateButtonNodeForAging.
     * @tc.expected:CreateButtonNodeForAging is executed correctly.
     */
    auto contentRow = DatePickerDialogView::CreateButtonNodeForAging(settingData, timePickerNode, monthDaysNode,
        dateNode, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(contentRow, nullptr);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogView005
 * @tc.desc: Test DatePickerDialogView CreateButtonNodeForAging.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
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
    auto dateNode = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(0));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));
    auto monthDaysNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    /**
     * @tc.steps: step2.call CreateButtonNodeForAging.
     * @tc.expected:CreateButtonNodeForAging is executed correctly.
     */
    DatePickerDialogView::switchTimePickerFlag_ = true;
    auto contentRow = DatePickerDialogView::CreateButtonNodeForAging(settingData, timePickerNode, monthDaysNode,
        dateNode, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(contentRow, nullptr);
}

/**
 * @tc.name: DatePickerDialogView006
 * @tc.desc: Test DatePickerDialogView SwitchPickerPage.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    DatePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.showTime = true;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

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
    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    monthDaysNode->MountToParent(pickerRow);
    auto timeNode = DatePickerDialogView::CreateTimeNode(settingData.timePickerProperty, settingData.properties, true);
    timeNode->MountToParent(pickerRow);
    pickerRow->MountToParent(pickerStack);
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
    RefPtr<DateTimeAnimationController> animationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    /**
     * @tc.steps: step2.call SwitchPickerPage.
     * @tc.expected:SwitchPickerPage is executed correctly.
     */
    DatePickerDialogView::SwitchPickerPage(pickerStack, contentColumn, animationController, true);
}

/**
 * @tc.name: DatePickerDialogView007
 * @tc.desc: Test DatePickerDialogView SwitchPickerPage.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerDialogView007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    DatePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.showTime = true;
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

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
    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    monthDaysNode->MountToParent(pickerRow);
    auto timeNode = DatePickerDialogView::CreateTimeNode(settingData.timePickerProperty, settingData.properties, true);
    timeNode->MountToParent(pickerRow);
    pickerRow->MountToParent(pickerStack);
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
    RefPtr<DateTimeAnimationController> animationController = AceType::MakeRefPtr<DateTimeAnimationController>();
    /**
     * @tc.steps: step2.call SwitchPickerPage.
     * @tc.expected:SwitchPickerPage is executed correctly.
     */
    DatePickerDialogView::switchFlag_ = true;
    DatePickerDialogView::SwitchPickerPage(pickerStack, contentColumn, animationController, true);
}

/**
 * @tc.name: DatePickerPatternTest001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.steps: step2.call OnModifyDone.
     * @tc.expected:all branch of OnModifyDone is executed correctly.
     */
    auto datePickerRowLayoutProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(datePickerRowLayoutProperty, nullptr);

    pickerPattern->isFiredDateChange_ = true;
    pickerPattern->isForceUpdate_ = false;
    pickerPattern->lunar_ = datePickerRowLayoutProperty->GetLunar().value_or(false);
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = false;
    pickerPattern->isForceUpdate_ = false;
    pickerPattern->lunar_ = datePickerRowLayoutProperty->GetLunar().value_or(false);
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = true;
    pickerPattern->isForceUpdate_ = true;
    pickerPattern->lunar_ = datePickerRowLayoutProperty->GetLunar().value_or(false);
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = true;
    pickerPattern->isForceUpdate_ = false;
    pickerPattern->lunar_ = !(datePickerRowLayoutProperty->GetLunar().value_or(false));
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = false;
    pickerPattern->isForceUpdate_ = true;
    pickerPattern->lunar_ = datePickerRowLayoutProperty->GetLunar().value_or(false);
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = false;
    pickerPattern->isForceUpdate_ = false;
    pickerPattern->lunar_ = !(datePickerRowLayoutProperty->GetLunar().value_or(false));
    pickerPattern->OnModifyDone();

    pickerPattern->isFiredDateChange_ = true;
    pickerPattern->isForceUpdate_ = true;
    pickerPattern->lunar_ = !(datePickerRowLayoutProperty->GetLunar().value_or(false));
    pickerPattern->OnModifyDone();

    auto eventHub = frameNode->GetEventHub<EventHub>();
    frameNode->focusHub_ = nullptr;
    pickerPattern->isFiredDateChange_ = false;
    pickerPattern->isForceUpdate_ = true;
    pickerPattern->lunar_ = !(datePickerRowLayoutProperty->GetLunar().value_or(false));
    pickerPattern->OnModifyDone();
}

/**
 * @tc.name: DatePickerPatternTest002
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    /**
     * @tc.steps: step2.call OnColorConfigurationUpdate.
     * @tc.expected:all branch of OnColorConfigurationUpdate is executed correctly.
     */
    pickerPattern->isPicker_ = true;
    pickerPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(frameNode->needCallChildrenUpdate_);
    pickerPattern->isPicker_ = false;
    pickerPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(frameNode->needCallChildrenUpdate_);
}

/**
 * @tc.name: DatePickerPatternTest003
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickeDialog.
     */
    DatePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

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
    auto pickerRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    monthDaysNode->MountToParent(pickerRow);
    pickerRow->MountToParent(pickerStack);
    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    /**
     * @tc.steps: step2.call OnColorConfigurationUpdate.
     * @tc.expected:all branch of OnColorConfigurationUpdate is executed correctly.
     */
    std::vector<ButtonInfo> buttonInfos;
    auto contentRow = DatePickerDialogView::CreateButtonNode(
        monthDaysNode, datePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    contentRow->AddChild(DatePickerDialogView::CreateDividerNode(datePickerNode), 1);
    auto buttonTitleNode = DatePickerDialogView::CreateTitleButtonNode(datePickerNode);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    buttonTitleNode->MountToParent(contentColumn);
    datePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    datePickerPattern->SetContentRowNode(contentRow);
    datePickerPattern->SetPickerTag(false);
    contentRow->MountToParent(contentColumn);
    datePickerPattern->OnColorConfigurationUpdate();
    ASSERT_NE(contentColumn, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest004
 * @tc.desc: Test HandleDirectionKey
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.cases: case1. KeyCode : KEY_DPAD_CENTER, focusKeyID_: 0.
     */
    pickerPattern->focusKeyID_ = 0;
    KeyCode code = KeyCode::KEY_DPAD_CENTER;
    auto ret = pickerPattern->HandleDirectionKey(code);
    EXPECT_FALSE(ret);
    /**
     * @tc.cases: case2. KeyCode : KEY_DPAD_LEFT, focusKeyID_: 1.
     */
    pickerPattern->focusKeyID_ = 2;
    code = KeyCode::KEY_DPAD_LEFT;
    auto retOne = pickerPattern->HandleDirectionKey(code);
    EXPECT_TRUE(retOne);
    /**
     * @tc.cases: case3. KeyCode : KEY_DPAD_RIGHT, focusKeyID_: 1.
     */
    code = KeyCode::KEY_DPAD_RIGHT;
    pickerPattern->showMonthDays_ = true;
    pickerPattern->focusKeyID_ = 1;
    auto retTwo = pickerPattern->HandleDirectionKey(code);
    EXPECT_FALSE(retTwo);
}

/**
 * @tc.name: DatePickerPatternTest005
 * @tc.desc: Test HandleAddLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    /**
     * @tc.cases: case1. index = 1.
     */
    datePickerPattern->HandleAddLunarDayChange(1);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case2. index = 0.
     */
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case3. index = 0, endDateLunar_ 1900 .
     */
    datePickerPattern->endDateLunar_.year = 1900;
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest006
 * @tc.desc: Test HandleAddLunarDayChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
    }
    /**
     * @tc.cases: case4. year: 1900, month: 2.
     */
    auto allChildNode = datePickerPattern->GetAllChildNode();
    auto monthNode = allChildNode["month"];
    auto yearNode = allChildNode["year"];
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(1);
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case5. year: 1973, month: 2.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(3);
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case6. year: 1974, month: 4.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(4);
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(4);
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case7. year: 1974, month: 3.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(4);
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(3);
    datePickerPattern->HandleAddLunarDayChange(0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest007
 * @tc.desc: Test HandleSolarMonthDaysChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    datePickerPattern->HandleSolarMonthDaysChange(true, 0);
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    /**
     * @tc.cases: case1~4. isAdd true/false, index 0/1.
     */
    datePickerPattern->HandleSolarMonthDaysChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleSolarMonthDaysChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleSolarMonthDaysChange(false, 1);
    EXPECT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleSolarMonthDaysChange(true, 1);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest008
 * @tc.desc: Test HandleLunarMonthDaysChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
    }
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    textCancelLayoutProperty->UpdateContent(dialogTheme->GetCancelText());
    textCancelNode->MountToParent(buttonCancelNode);
    /**
     * @tc.cases: case1~2. isAdd true/false, index 0.
     */
    datePickerPattern->HandleLunarMonthDaysChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    datePickerPattern->HandleLunarMonthDaysChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest009
 * @tc.desc: Test HandleSolarMonthChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
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
    auto dayNode = allChildNode["day"];
    /**
     * @tc.cases: case1. isAdd: true, date: 1970-1-1.
     */
    datePickerPattern->HandleSolarMonthChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case2. isAdd: true, date: 2170-1-1.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_YEAR_INDEX);
    datePickerPattern->HandleSolarMonthChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case3. isAdd: true, date: 2170-12-1.
     */
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_MONTH_INDEX);
    datePickerPattern->HandleSolarMonthChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest010
 * @tc.desc: Test HandleSolarMonthChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
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
    auto dayNode = allChildNode["day"];
    /**
     * @tc.cases: case4. isAdd: false, date: 1970-1-32.
     */
    dayNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_DAY_INDEX);
    datePickerPattern->HandleSolarMonthChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case5. isAdd: false, date: 1970-12-32.
     */
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_MONTH_INDEX);
    datePickerPattern->HandleSolarMonthChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case6. isAdd: false, date: 1971-12-32.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(1);
    datePickerPattern->HandleSolarMonthChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest011
 * @tc.desc: Test HandleLunarMonthChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
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
    auto dayNode = allChildNode["day"];
    /**
     * @tc.cases: case1. isAdd: true, index: 0, date: 1974-4-1.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(4);
    monthNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(5);
    datePickerPattern->HandleLunarMonthChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case2. isAdd: true, index: 0, date: 1970-4-1.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(0);
    dayNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_DAY_INDEX);
    datePickerPattern->HandleLunarMonthChange(true, 0);
    datePickerPattern->HandleLunarMonthChange(true, 1);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest012
 * @tc.desc: Test HandleLunarMonthChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
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
    auto dayNode = allChildNode["day"];
    /**
     * @tc.cases: case3. isAdd: false, index: 1, date: 1970-1-1.
     */
    datePickerPattern->HandleLunarMonthChange(false, 1);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case4. isAdd: false, index: 0, date: 1970-1-1.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(0);
    datePickerPattern->HandleLunarMonthChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case5. isAdd: false, index: 0, date: 2170-1-1.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_YEAR_INDEX);
    datePickerPattern->HandleLunarMonthChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest013
 * @tc.desc: Test HandleLunarYearChange
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
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
    if (!hasYearNode) {
        CreateYearColumnNode(yearColumnNode, datePickerNode);
    }
    if (!hasMonthNode) {
        CreateMonthOrDayColumnNode(monthColumnNode, datePickerNode, Color::BLUE);
    }
    if (!hasDayNode) {
        CreateMonthOrDayColumnNode(dayColumnNode, datePickerNode, Color::GRAY);
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
    auto dayNode = allChildNode["day"];
    /**
     * @tc.cases: case1. isAdd: true, date: 1970-1-1.
     */
    datePickerPattern->HandleLunarYearChange(true, 0);
    EXPECT_NE(datePickerPattern, nullptr);
    /**
     * @tc.cases: case2. isAdd: false, date: 1971-1-32.
     */
    yearNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(1);
    dayNode->GetPattern<DatePickerColumnPattern>()->SetCurrentIndex(MAX_DAY_INDEX);
    datePickerPattern->HandleLunarYearChange(false, 0);
    EXPECT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest014
 * @tc.desc: Test GetCurrentLunarDateByMonthDaysColumn
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest014, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    /**
     * @tc.cases: case1. pickerNode is completed.
     */
    uint32_t vulyear = 2024;
    pickerPattern->GetCurrentLunarDateByMonthDaysColumn(vulyear);
}

/**
 * @tc.name: DatePickerPatternTest015
 * @tc.desc: Test GetCurrentLunarDateByMonthDaysColumn
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
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
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    /**
     * @tc.cases: case2. pickerNode is not completed.
     */
    datePickerPattern->GetCurrentLunarDateByMonthDaysColumn(SELECTED_YEAR);
    ASSERT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest016
 * @tc.desc: Test LunarColumnsBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
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
    datePickerPattern->SetConfirmNode(buttonConfirmNode);
    /**
     * @tc.cases: case1. M-d-y.
     */
    LunarDate current;
    datePickerPattern->SetDateOrder("M-d-y");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, true);
    /**
     * @tc.cases: case2. y-d-M.
     */
    datePickerPattern->SetDateOrder("y-d-M");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, true);
}

/**
 * @tc.name: DatePickerPatternTest017
 * @tc.desc: Test LunarMonthDaysColumnBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto pickerTheme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
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
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = CreateYearColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> monthColumnNode = CreateMonthColumnNode(datePickerPattern, showCount);
    RefPtr<FrameNode> dayColumnNode = CreateDayColumnNode(datePickerPattern, showCount);
    /**
     * @tc.cases: case2. pickerNode is not completed.
     */
    auto lunarDate = datePickerPattern->GetCurrentLunarDateByMonthDaysColumn(SELECTED_YEAR);
    datePickerPattern->HandleAddLunarMonthDaysChange(0);
    datePickerPattern->LunarMonthDaysColumnBuilding(lunarDate);
    ASSERT_NE(datePickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest018
 * @tc.desc: Test LunarMonthDaysColumnBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    auto year = frameNode->GetChildAtIndex(1);
    ASSERT_NE(year, nullptr);
    auto stackYear = AceType::DynamicCast<FrameNode>(year);
    ASSERT_NE(stackYear, nullptr);
    auto blendYear = AceType::DynamicCast<FrameNode>(stackYear->GetLastChild());
    ASSERT_NE(blendYear, nullptr);
    auto yearDaysNode = AceType::DynamicCast<FrameNode>(blendYear->GetLastChild());
    ASSERT_NE(yearDaysNode, nullptr);
    auto yearDatePickerColumnPattern = yearDaysNode->GetPattern<DatePickerColumnPattern>();
    /**
     * @tc.cases: case1. pickerNode is completed.
     */
    yearDatePickerColumnPattern->SetCurrentIndex(0);
    pickerPattern->HandleAddLunarMonthDaysChange(0);
    pickerPattern->HandleAddLunarMonthDaysChange(1);
    auto lunarDate = pickerPattern->GetCurrentLunarDateByMonthDaysColumn(SELECTED_YEAR);
    pickerPattern->LunarMonthDaysColumnBuilding(lunarDate);
    ASSERT_NE(pickerPattern, nullptr);
}

/**
 * @tc.name: DatePickerPatternTest019
 * @tc.desc: Test LunarColumnsBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    DatePickerModel::GetInstance()->SetEndDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();

    LunarDate current;
    datePickerPattern->SetDateOrder("M-d-y");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, false);

    datePickerPattern->SetDateOrder("y-d-M");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, false);
}

/**
 * @tc.name: DatePickerPatternTest020
 * @tc.desc: Test LunarColumnsBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(PickerDate(START_YEAR_BEFORE, 1, 1));
    DatePickerModel::GetInstance()->SetEndDate(PickerDate(START_YEAR_BEFORE, 5, 1));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();

    LunarDate current;
    datePickerPattern->SetDateOrder("M-d-y");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, false);

    datePickerPattern->SetDateOrder("y-d-M");
    datePickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(datePickerPattern->lunar_, false);
}

/**
 * @tc.name: DatePickerPatternTest021
 * @tc.desc: Test LunarColumnsBuilding
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerColumnTest, DatePickerPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pickerPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(pickerPattern, nullptr);

    LunarDate startDate, endDate;
    startDate.year = 2300, endDate.year = 2300;
    startDate.month = 6, endDate.month = 12;
    startDate.day = 3, endDate.day = 2;
    startDate.isLeapMonth = endDate.isLeapMonth = true;

    auto dataPickerRowLayoutProperty = frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(dataPickerRowLayoutProperty, nullptr);
    dataPickerRowLayoutProperty->UpdateStartDate(startDate);
    dataPickerRowLayoutProperty->UpdateEndDate(endDate);

    LunarDate current;
    current.year = 2025;
    current.isLeapMonth = true;
    current.month = 6;
    pickerPattern->SetDateOrder("M-d-y");
    pickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(pickerPattern->lunar_, false);

    pickerPattern->SetDateOrder("y-d-M");
    pickerPattern->LunarColumnsBuilding(current);
    EXPECT_NE(pickerPattern->lunar_, false);
}
} // namespace OHOS::Ace::NG

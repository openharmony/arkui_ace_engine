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
#include "test/mock/core/common/mock_font_manager.h"
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
#include "core/common/font_manager.h"
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
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
const int32_t API_VERSION_TWELVE = 12;
} // namespace

class DatePickerColumnTest : public testing::Test {
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
} // namespace OHOS::Ace::NG
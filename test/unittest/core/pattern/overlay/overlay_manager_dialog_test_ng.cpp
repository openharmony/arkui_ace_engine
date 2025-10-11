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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/error/error_code.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/dump_log.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_method.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/napi/kits/promptaction/prompt_controller.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace
class OverlayManagerDialogTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    DatePickerSettingData GenDatePickerSettingData();
};

void OverlayManagerDialogTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DragBarTheme::TypeId()) {
            return AceType::MakeRefPtr<DragBarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return AceType::MakeRefPtr<PickerTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else if (type == ToastTheme::TypeId()) {
            return AceType::MakeRefPtr<ToastTheme>();
        } else if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void OverlayManagerDialogTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerDialogTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayManagerDialogTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayManagerDialogTestNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}
DatePickerSettingData OverlayManagerDialogTestNg::GenDatePickerSettingData()
{
    DatePickerSettingData datePickerSettingData;
    datePickerSettingData.isLunar = false;
    datePickerSettingData.showTime = false;
    datePickerSettingData.useMilitary = false;

    PickerTextProperties properties;
    properties.disappearTextStyle_.textColor = Color::RED;
    properties.disappearTextStyle_.fontSize = Dimension(0);
    properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.normalTextStyle_.textColor = Color::BLACK;
    properties.normalTextStyle_.fontSize = Dimension(10); // 10: refers to setting the font size
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(15); // 15:refers to setting the font size
    properties.selectedTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    datePickerSettingData.properties = properties;
    datePickerSettingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    datePickerSettingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    datePickerSettingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    datePickerSettingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    return datePickerSettingData;
}
/**
 * @tc.name: DialogTest001
 * @tc.desc: Test OverlayManager::ShowCustomDialog->CloseDialog->ShowDateDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. call DialogInMapHoldingFocus when dialogMap_ is not empty and focusHub is nullptr.
     * @tc.expected: return false
     */
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call CloseDialog when dialogMap_ is not empty.
     * @tc.expected: remove successfully
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call CloseDialog again when dialogMap_ is empty.
     * @tc.expected: function exits normally
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step5. call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
    */
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
}

/**
 * @tc.name: DialogTest002
 * @tc.desc: Test OverlayManager::ShowCustomDialog->CloseDialog->ShowDateDialog->ShowTimeDialog->RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. call DialogInMapHoldingFocus when dialogMap_ is not empty and focusHub is nullptr.
     * @tc.expected: return false
     */
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call CloseDialog when dialogMap_ is not empty.
     * @tc.expected: remove successfully
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step5. call CloseDialog again when dialogMap_ is empty.
     * @tc.expected: function exits normally
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step6. call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step7. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step8. call RemoveOverlay when dialogChildCount is 2
     * @tc.expected: remove lastChild successfully
     */
    EXPECT_TRUE(overlayManager->RemoveOverlay(false));
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
}

/**
 * @tc.name: DialogTest003
 * @tc.desc: Test OverlayManager::ShowCustomDialog->ShowTimeDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());

    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
}
/**
 * @tc.name: DialogTest004
 * @tc.desc: Test OverlayManager::ShowCustomDialog->ShowTextDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTextDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TextPickerSettingData textPickerSettingData;
    textPickerSettingData.properties = datePickerSettingData.properties;
    textPickerSettingData.options = {
        {{"jiangsu"}, {
            {{"suzhou"}, {
                {{"wujiang"}, {}},
                {{"kunshan"}, {}},
            }},
            {{"nanjing"}, {
                {{"xixia"}, {}},
            }}
        }}};
    overlayManager->ShowTextDialog(dialogProperties, textPickerSettingData, dialogEvent, dialogCancelEvent,
        dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
}
/**
 * @tc.name: DialogTest005
 * @tc.desc: Test OverlayManager::ShowCustomDialog->ShowTimeDialog->CloseDialog->ShowTextDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step4. call CloseDialog when dialogMap_ size is 1.
     * @tc.expected: remove successfully
     */
    overlayManager->CloseDialog(dialogNode);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step5. create textPickerSettingData and call ShowTextDialog.
     * @tc.expected: textDialogNode is created successfully
     */
    TextPickerSettingData textPickerSettingData;
    textPickerSettingData.properties = datePickerSettingData.properties;
    textPickerSettingData.options = {
        {{"jiangsu"}, {}}};
    overlayManager->ShowTextDialog(dialogProperties, textPickerSettingData, dialogEvent, dialogCancelEvent,
        dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
}
/**
 * @tc.name: DialogTest006
 * @tc.desc: Test OverlayManager::ShowDialog and RemoveOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node and prepare dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
    */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call RemoveOverlay when dialogMap_ is empty.
     * @tc.expected: remove successfully
     */
    overlayManager->RemoveOverlay(true);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step4. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step5. call RemoveOverlay when dialogMap_ is empty.
     * @tc.expected: remove successfully
     */
    overlayManager->RemoveOverlay(true);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step6. create textPickerSettingData and call ShowTextDialog.
     * @tc.expected: textDialogNode is created successfully
     */
    TextPickerSettingData textPickerSettingData;
    textPickerSettingData.properties = datePickerSettingData.properties;
    textPickerSettingData.options = {
        {{"jiangsu"}, {}}};
    overlayManager->ShowTextDialog(
        dialogProperties, textPickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step7. call RemoveOverlay when dialogMap_ is empty.
     * @tc.expected: remove successfully
     */
    overlayManager->RemoveOverlay(true);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}
/**
 * @tc.name: DialogTest007
 * @tc.desc: Test OverlayManager::ShowDialog->ShowDateDialog->Set symmetry transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto opacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto scaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    opacityTransition->SetNext(scaleTransition);
    dialogProperties.transitionEffect = opacityTransition;
    dialogProperties.isShowInSubWindow = true;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step4. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    ASSERT_NE(transitionEffect, nullptr);
    auto dialogScaleTransition = transitionEffect->GetNext();
    ASSERT_NE(dialogScaleTransition, nullptr);
}
/**
 * @tc.name: DialogTest008
 * @tc.desc: Test OverlayManager::ShowDialog->ShowTimeDialog->Set symmetry transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto opacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto scaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    opacityTransition->SetNext(scaleTransition);
    dialogProperties.transitionEffect = opacityTransition;
    dialogProperties.isShowInSubWindow = true;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step4. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    ASSERT_NE(transitionEffect, nullptr);
    auto dialogScaleTransition = transitionEffect->GetNext();
    ASSERT_NE(dialogScaleTransition, nullptr);
}

/**
 * @tc.name: DialogTest009
 * @tc.desc: Test OverlayManager::ShowDialog->ShowTimeDialog->ShowTextDialog->Set symmetry transition effect.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DialogTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto opacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto scaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    opacityTransition->SetNext(scaleTransition);
    dialogProperties.transitionEffect = opacityTransition;
    dialogProperties.isShowInSubWindow = true;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    auto datePickerSettingData = GenDatePickerSettingData();
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    dialogCancelEvent["cancelId"] = cancelFunc;

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 2);
    /**
     * @tc.steps: step4. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TextPickerSettingData textPickerSettingData;
    textPickerSettingData.properties = datePickerSettingData.properties;
    textPickerSettingData.options = {
        {{"jiangsu"}, {}}};
    overlayManager->ShowTextDialog(
        dialogProperties, textPickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 3);
    /**
     * @tc.steps: step5. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect = dialogPattern->GetDialogProperties().transitionEffect;
    ASSERT_NE(transitionEffect, nullptr);
    auto dialogScaleTransition = transitionEffect->GetNext();
    ASSERT_NE(dialogScaleTransition, nullptr);
}

/**
 * @tc.name: DismissDialogTest001
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create root node and dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    /**
     * @tc.steps: step2. Create overlayManager and call ShowDialog.
     */
    auto overlay = AceType::DynamicCast<FrameNode>(rootNode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps3: Set the onWillDismiss property.
     * @tc.expected:  return value are as expected.
     */
    std::function<void(int32_t, int32_t)> onWillDismiss1 = [](int32_t reason, int32_t instanceId) {};
    auto pattern = overlay->GetPattern();
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    dialogPattern->SetOnWillDismiss(onWillDismiss1);
    EXPECT_TRUE(dialogPattern->ShouldDismiss());
    /**
     * @tc.steps4: Call DismissDialog function.
     * @tc.expected: DismissDialog function is called.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest002
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create dialog node and root node.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    /**
     * @tc.steps: step2. create overlayManager and call ShowCustomDialog.
     * @tc.expected: dialogMap_ is not empty
     */
    overlayManager->ShowCustomDialog(dialogNode);
    overlayManager->BeforeShowDialog(dialogNode);
    EXPECT_FALSE(overlayManager->dialogMap_.empty());
    /**
     * @tc.steps: step3. call DialogInMapHoldingFocus when dialogMap_ is not empty and focusHub is nullptr.
     * @tc.expected: return false
     */
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call DismissDialog when dialogMap_ is not empty.
     * @tc.expected: remove successfully
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_TRUE(overlayManager->toastMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step4. call DismissDialog again when dialogMap_ is empty.
     * @tc.expected: function exits normally
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest003
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogParam;
    dialogParam.isShowInSubWindow = true;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: dialogNode is created successfully
     */
    auto dialogNode = overlayManager->ShowDialog(dialogParam, nullptr, true);
    EXPECT_NE(dialogNode, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. create focusHub and call DialogInMapHoldingFocus when dialogMap_ is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialogNode->GetEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    dialogNode->eventHub_ = eventHub;
    EXPECT_TRUE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DismissDialogTest004
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;

    auto datePickerSettingData = GenDatePickerSettingData();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest005
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = false;

    auto datePickerSettingData = GenDatePickerSettingData();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDateDialog.
     * @tc.expected: dateDialogNode is created successfully
     */
    overlayManager->ShowDateDialog(
        dialogProperties, datePickerSettingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest006
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;

    auto datePickerSettingData = GenDatePickerSettingData();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    /**
     * @tc.steps: step2. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest007
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = false;

    auto datePickerSettingData = GenDatePickerSettingData();

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    auto lifeCycleFunc = []() {};
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["didDisappearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willAppearId"] = lifeCycleFunc;
    dialogLifeCycleEvent["willDisappearId"] = lifeCycleFunc;
    /**
     * @tc.steps: step2. create timePickerSettingData and call ShowTimeDialog.
     * @tc.expected: timeDialogNode is created successfully
     */
    TimePickerSettingData timePickerSettingData;
    timePickerSettingData.properties = datePickerSettingData.properties;
    timePickerSettingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    overlayManager->ShowTimeDialog(dialogProperties, timePickerSettingData, timePickerProperty, dialogEvent,
        dialogCancelEvent, dialogLifeCycleEvent);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest008
 * @tc.desc: Test OverlayManager::OpenCustomDialog->CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;
    auto contentNodeNew = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParamNew;
    dialogParamNew.contentNode = contentNodeNew;

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);
    auto openCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackSnd);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step4. call DismissDialog for contentNodeNew.
     * @tc.expected: remove  successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}

/**
 * @tc.name: DismissDialogTest009
 * @tc.desc: Test DismissDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and prepare dialogProperties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    DialogProperties dialogParam;
    dialogParam.isShowInSubWindow = false;
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: dialogNode is created successfully
     */
    auto dialogNode = overlayManager->ShowDialog(dialogParam, nullptr, true);
    EXPECT_NE(dialogNode, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. create focusHub and call DialogInMapHoldingFocus when dialogMap_ is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialogNode->GetEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    dialogNode->eventHub_ = eventHub;
    EXPECT_TRUE(overlayManager->DialogInMapHoldingFocus());
    /**
     * @tc.steps: step3. call DismissDialog.
     * @tc.expected: remove successfully.
     */
    ViewAbstract::DismissDialog();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DismissDialogTest010
 * @tc.desc: Test OverlayManager::OpenCustomDialog->Dialog Controller::CloseDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerDialogTestNg, DismissDialogTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    /**
     * @tc.steps: step2. create dialog content node.
     */
    auto contentNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParam;
    dialogParam.contentNode = contentNode;
    auto contentNodeNew = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    DialogProperties dialogParamNew;
    dialogParamNew.contentNode = contentNodeNew;

    /**
     * @tc.steps: step3. call OpenCustomDialog for contentNode.
     * @tc.expected: OpenCustomDialog succeed and dialog of contentNode is in the dialogMap_.
     */
    auto openCallbackFst = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackFst);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    auto dialogNode = overlayManager->GetDialogNodeWithExistContent(contentNode);
    EXPECT_NE(dialogNode, nullptr);
    auto openCallbackSnd = [](int32_t errorCode) {
        EXPECT_EQ(errorCode, ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    };
    overlayManager->OpenCustomDialog(dialogParam, openCallbackSnd);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step4. call CloseDialog for contentNodeNew.
     * @tc.expected: remove  successfully.
     */
    Napi::PromptDialogController* controller = new Napi::PromptDialogController();
    controller->SetNode(dialogNode);
    controller->Close();
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
}
} // namespace OHOS::Ace::NG

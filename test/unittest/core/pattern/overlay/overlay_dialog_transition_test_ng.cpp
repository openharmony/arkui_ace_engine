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
const std::string LONGEST_CONTENT = "新建文件夹";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const std::string CONTENT = "content";
const std::string TITLE = "title";
const std::string SUB_TITLE = "subtitle";
const std::string CHECKBOX_CONTENT = "checkboxContent";
constexpr int32_t FONT_SIZE_10 = 10;
constexpr int32_t FONT_SIZE_15 = 15;
} // namespace
class OverlayDialogTransitionTestNg : public testing::Test {
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

void OverlayDialogTransitionTestNg::SetUpTestCase()
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
void OverlayDialogTransitionTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayDialogTransitionTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

void OverlayDialogTransitionTestNg::CreateSheetStyle(SheetStyle& sheetStyle)
{
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
}

void OverlayDialogTransitionTestNg::CreateSheetBuilder()
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
DatePickerSettingData OverlayDialogTransitionTestNg::GenDatePickerSettingData()
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
    properties.normalTextStyle_.fontSize = Dimension(FONT_SIZE_10);
    properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    properties.selectedTextStyle_.textColor = Color::RED;
    properties.selectedTextStyle_.fontSize = Dimension(FONT_SIZE_15);
    properties.selectedTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    datePickerSettingData.properties = properties;
    datePickerSettingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    datePickerSettingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    datePickerSettingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    datePickerSettingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    return datePickerSettingData;
}

/**
 * @tc.name: DialogTransitionTest001
 * @tc.desc: Test transitionEffect value is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.type = DialogType::ACTION_SHEET;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);
}

/**
 * @tc.name: DialogTransitionTest002
 * @tc.desc: Test appearTransition value is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.type = DialogType::ACTION_SHEET;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step3. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);
}

/**
 * @tc.name: DialogTransitionTest003
 * @tc.desc: Test disappearTransition value is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.type = DialogType::ACTION_SHEET;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);
}
/**
 * @tc.name: DialogTransitionTest004
 * @tc.desc: Test OverlayManager::ShowDialog->Set the type of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.type = DialogType::ACTION_SHEET;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step3. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step3. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    auto properties = static_cast<DialogProperties>(dialogPattern->GetDialogProperties());
    auto type = properties.type;
    EXPECT_EQ(type, DialogType::ACTION_SHEET);
}

/**
 * @tc.name: DialogTransitionTest005
 * @tc.desc: Test OverlayManager::ShowDialog->Set the title of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.title = TITLE;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step3. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step3. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    auto properties = static_cast<DialogProperties>(dialogPattern->GetDialogProperties());
    auto title = properties.title;
    ASSERT_NE(title, "");
}

/**
 * @tc.name: DialogTransitionTest006
 * @tc.desc: Test OverlayManager::ShowDialog->Set the content of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.content = CONTENT;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    auto properties = static_cast<DialogProperties>(dialogPattern->GetDialogProperties());
    auto content = properties.content;
    ASSERT_NE(content, "");
}

/**
 * @tc.name: DialogTransitionTest007
 * @tc.desc: Test OverlayManager::ShowDialog->Set the subtitle of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.subtitle = SUB_TITLE;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step3. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step3. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    auto properties = static_cast<DialogProperties>(dialogPattern->GetDialogProperties());
    auto subtitle = properties.subtitle;
    ASSERT_NE(subtitle, "");
}

/**
 * @tc.name: DialogTransitionTest008
 * @tc.desc: Test OverlayManager::ShowDialog->Set the checkboxContent of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    dialogProperties.checkboxContent = CHECKBOX_CONTENT;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    auto properties = static_cast<DialogProperties>(dialogPattern->GetDialogProperties());
    auto checkboxContent = properties.checkboxContent;
    ASSERT_NE(checkboxContent, "");
}


/**
 * @tc.name: DialogTransitionTest009
 * @tc.desc: Test OverlayManager::ShowDialog->Set the dialog Id of the dialog box
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step6. test OverlayManager.GetDialog function.
     * @tc.expected: overlayManager.dialog.id equal to GetDialog(dialogId).id.
     */
    int32_t dialogId = dialog->GetId();
    auto dialogNode = overlayManager->GetDialog(dialogId);
    CHECK_NULL_VOID(dialogNode);
    EXPECT_EQ(dialogId, dialogNode->GetId());
}

/**
 * @tc.name: DialogTransitionTest010
 * @tc.desc: Test focusHub is not empty
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step3. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step3. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step6. Test focusHub is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialog->GetOrCreateEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
}

/**
 * @tc.name: DialogTransitionTest011
 * @tc.desc: Test focus event
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step6. create focusHub and call DialogInMapHoldingFocus when dialogMap_ is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialog->GetOrCreateEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    dialog->eventHub_ = eventHub;
    EXPECT_TRUE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DialogTransitionTest012
 * @tc.desc: Test remove subwindow
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);

    ASSERT_NE(transitionEffect, nullptr);
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step4. call RemoveOverlayInSubwindow.
     * @tc.expected: remove successfully.
     */
    EXPECT_TRUE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DialogTransitionTest013
 * @tc.desc: Test remove subwindow and the dialog Id
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    dialogProperties.isShowInSubWindow = true;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);

    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step6. test OverlayManager.GetDialog function.
     * @tc.expected: overlayManager.dialog.id equal to GetDialog(dialogId).id.
     */
    int32_t dialogId = dialog->GetId();
    auto dialogNode = overlayManager->GetDialog(dialogId);
    CHECK_NULL_VOID(dialogNode);
    EXPECT_EQ(dialogId, dialogNode->GetId());

    /**
     * @tc.steps: step7. call RemoveOverlayInSubwindow.
     * @tc.expected: remove successfully.
     */
    EXPECT_TRUE(overlayManager->RemoveOverlayInSubwindow());
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
}

/**
 * @tc.name: DialogTransitionTest014
 * @tc.desc: Test the dialog Id and focus event
 * @tc.type: FUNC
 */
HWTEST_F(OverlayDialogTransitionTestNg, DialogTransitionTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and dialogProperties.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    DialogProperties dialogProperties;
    double opacity = 1.0;
    auto appearOpacityTransition = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(opacity);
    NG::ScaleOptions scale(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct);
    auto disappearScaleTransition = AceType::MakeRefPtr<NG::ChainedScaleEffect>(scale);
    dialogProperties.transitionEffect = AceType::MakeRefPtr<NG::ChainedAsymmetricEffect>(appearOpacityTransition,
        disappearScaleTransition);

    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    ASSERT_NE(dialog, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 1);
    /**
     * @tc.steps: step3. get transitionEffect from dialog.
     * @tc.expected: transitionEffect value is not nullptr.
     */
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    auto transitionEffect =
        AceType::DynamicCast<NG::ChainedAsymmetricEffect>(dialogPattern->GetDialogProperties().transitionEffect);
    ASSERT_NE(transitionEffect, nullptr);

    /**
     * @tc.steps: step4. get appearTransition from dialog.
     * @tc.expected: appearTransition value is not nullptr.
     */
    auto appearTransition = transitionEffect->GetAppearEffect();
    ASSERT_NE(appearTransition, nullptr);

    /**
     * @tc.steps: step5. get disappearTransition from dialog.
     * @tc.expected: disappearTransition value is not nullptr.
     */
    auto disappearTransition = transitionEffect->GetDisappearEffect();
    ASSERT_NE(disappearTransition, nullptr);

    /**
     * @tc.steps: step6. test OverlayManager.GetDialog function.
     * @tc.expected: overlayManager.dialog.id equal to GetDialog(dialogId).id.
     */
    int32_t dialogId = dialog->GetId();
    auto dialogNode = overlayManager->GetDialog(dialogId);
    CHECK_NULL_VOID(dialogNode);
    EXPECT_EQ(dialogId, dialogNode->GetId());

    /**
     * @tc.steps: step7. create focusHub and call DialogInMapHoldingFocus when dialogMap_ is not empty.
     * @tc.expected: return true
     */
    auto eventHub = dialogNode->GetOrCreateEventHub<DialogEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    dialogNode->eventHub_ = eventHub;
    EXPECT_TRUE(overlayManager->DialogInMapHoldingFocus());
}
} // namespace OHOS::Ace::NG

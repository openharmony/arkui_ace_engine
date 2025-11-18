/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/image/image_base.h"
#include "ui/base/ace_type.h"

#include "base/utils/singleton.h"
#include "core/common/display_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/constants.h"

#define private public
#define protected public
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const double DIMENSIONVALUE = 1.0;
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const CalcDimension WIDTHDIMENSION = CalcDimension(DIMENSIONVALUE);
const CalcDimension HEIGHTDIMENSION = CalcDimension(DIMENSIONVALUE);
const NG::BorderWidthProperty BORDERWIDTH = { .leftDimen = Dimension(DIMENSIONVALUE) };
const BorderColorProperty BORDERCOLOR = { .bottomColor = Color::WHITE };
const NG::BorderRadiusProperty BORDERRADIUS = BorderRadiusProperty(Dimension(DIMENSIONVALUE));
const RectF CONTROL_RECT = RectF(0.0f, 0.0f, 100.0f, 100.0f);
} // namespace

class DialogPatternAdditionalTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogPatternAdditionalTwoTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DialogPatternAdditionalTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DialogPatternAdditionalTwoTestNgGetContentRect
 * @tc.desc: Test DialogPattern GetContentRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternAdditionalTwoTestNgGetContentRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogProperties_.customStyle = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_EQ(pattern->GetContentRect(frameNode), frameNode->GetGeometryNode()->GetFrameRect());

    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    pattern->customNode_ = dialogNode;
    auto customNode = pattern->customNode_.Upgrade();
    EXPECT_NE(pattern->customNode_.Upgrade(), nullptr);
    auto customContent = AccessibilityManagerNG::DynamicCast<FrameNode>(customNode);
    EXPECT_NE(customContent, nullptr);
    EXPECT_EQ(pattern->GetContentRect(frameNode), frameNode->GetGeometryNode()->GetFrameRect());
}

/**
 * @tc.name: DialogPatternAdditionalTwoTestNgInitHostWindowRect
 * @tc.desc: Test DialogPattern InitHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternAdditionalTwoTestNgInitHostWindowRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogProperties_.isShowInSubWindow = true;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_FALSE(!pattern->dialogProperties_.isShowInSubWindow);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    EXPECT_FALSE(container->IsSubContainer());
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(container->IsUIExtensionWindow());
    pattern->InitHostWindowRect();
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());
    pattern->InitHostWindowRect();
}

/**
 * @tc.name: DialogPatternAdditionalTwoTestNgIsShowInFreeMultiWindow
 * @tc.desc: Test DialogPattern IsShowInFreeMultiWindow
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternAdditionalTwoTestNgIsShowInFreeMultiWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    MockContainer::container_ = nullptr;
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_EQ(container, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());

    MockContainer::SetUp();
    container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());

    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_EQ(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());

    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    AceEngine::Get().AddContainer(currentId, container);
    subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_NE(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet001
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogModelTestNgShowActionSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    theme->expandDisplay_ = true;
    container->isSubContainer_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    container->isSubContainer_ = true;
    actionSheetModelNg.ShowActionSheet(props);
    theme->expandDisplay_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    props.isShowInSubWindow = false;
    actionSheetModelNg.ShowActionSheet(props);
    container->isSubContainer_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet002
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogModelTestNgShowActionSheet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
        .dialogLevelMode = LevelMode::EMBEDDED,
        .dialogLevelUniqueId = 0,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto containerId = Container::CurrentId();
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    mockSubwindow->isRosenWindowCreate_ = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    EXPECT_CALL(*mockSubwindow, ShowDialogNG(_, _)).WillRepeatedly(Return(dialog));
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).WillRepeatedly(Return(containerId));
    SubwindowManager::GetInstance()->AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, mockSubwindow);
    actionSheetModelNg.ShowActionSheet(props);
    container->isUIExtensionWindow_ = true;
    actionSheetModelNg.ShowActionSheet(props);
    props.isModal = false;
    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: GetWindowButtonRect
 * @tc.desc: Test GetWindowButtonRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, GetWindowButtonRect, TestSize.Level1)
{
    /**
    * @tc.steps: step0. create dialog node.
    * @tc.expected: the dialog node created successfully.
    */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    auto pattern = dialog->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipelineContext = dialog->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto avoidInfoMgr = pipelineContext->GetAvoidInfoManager();
    ASSERT_NE(avoidInfoMgr, nullptr);
    avoidInfoMgr->avoidInfo_.needAvoid = false;
    avoidInfoMgr->avoidInfo_.controlBottonsRect = CONTROL_RECT;
    RectF floatButtons;
    pattern->GetWindowButtonRect(floatButtons);
    EXPECT_EQ(floatButtons, RectF());
    avoidInfoMgr->avoidInfo_.needAvoid = true;
    pattern->GetWindowButtonRect(floatButtons);
    EXPECT_EQ(floatButtons, CONTROL_RECT);
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet003
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogModelTestNgShowActionSheet003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
        .dialogLevelMode = LevelMode::EMBEDDED,
        .dialogLevelUniqueId = 0,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);

    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->onMainTree_ = true;
    ElementRegister::GetInstance()->AddReferenced(props.dialogLevelUniqueId, contentNode);
    auto currentNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(props.dialogLevelUniqueId);
    ASSERT_NE(currentNode, nullptr);
    auto getOverlayManager = DialogManager::FindPageNodeOverlay(currentNode);
    ASSERT_NE(getOverlayManager, nullptr);

    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
    ElementRegister::GetInstance()->Clear();
}

/**
 * @tc.name: DialogPatternAdditionalTwoTestNgUpdateButtonsProperty
 * @tc.desc: Test DialogPattern UpdateButtonsProperty
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternAdditionalTwoTestNgUpdateButtonsProperty, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->buttonContainer_ = nullptr;
    RefPtr<FrameNode> menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(menuNode, nullptr);
    pattern->menuNode_ = menuNode;
    RefPtr<FrameNode> childNodeOne =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeOne, nullptr);
    RefPtr<FrameNode> childNodeTwo =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeTwo, nullptr);
    RefPtr<FrameNode> childNodeThree =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 5, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeThree, nullptr);
    childNodeOne->MountToParent(menuNode);
    childNodeTwo->MountToParent(menuNode);
    childNodeThree->MountToParent(menuNode);
    RefPtr<FrameNode> childNodeFour =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 6, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeFour, nullptr);
    childNodeFour->MountToParent(childNodeThree);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->UpdateButtonsProperty();
    EXPECT_EQ(pattern->isFirstDefaultFocus_, true);
}

/**
 * @tc.name: DialogPatternAdditionalTwoTestNgIsShowInFloatingWindow
 * @tc.desc: Test DialogPattern IsShowInFloatingWindow
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternAdditionalTwoTestNgIsShowInFloatingWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    MockContainer::container_ = nullptr;
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_EQ(container, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    MockContainer::SetUp();
    container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());
    container->UpdateCurrent(11);

    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_EQ(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    AceEngine::Get().AddContainer(currentId, container);
    subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_NE(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    container->ResetContainer();
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
}

/**
 * @tc.name: DialogPatternTestSetDialogAccessibilityHoverConsume
 * @tc.desc: Test SetDialogAccessibilityHoverConsume
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, DialogPatternTestSetDialogAccessibilityHoverConsume, TestSize.Level1)
{
    /**
     * @tc.steps: step0. create dialog node.
     * @tc.expected: the dialog node created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialog, nullptr);
    DialogView::SetDialogAccessibilityHoverConsume(dialog);
    auto dialogAccessibilityProperty = dialog->GetAccessibilityProperty<DialogAccessibilityProperty>();
    ASSERT_NE(dialogAccessibilityProperty, nullptr);
}

/**
 * @tc.name: DialogPatternTestSetDialogAccessibilityHoverConsume
 * @tc.desc: Test OnWindowShow
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTwoTestNg, OnWindowShow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set refreshOnWindowShow to true and invoke function.
     * @tc.expected: RefreshOnWindowShow is false.
     */
    pattern->refreshOnWindowShow_ = true;
    pattern->OnWindowShow();
    EXPECT_FALSE(pattern->refreshOnWindowShow_);
    
    pattern->refreshOnWindowShow_ = false;
    pattern->OnWindowShow();
    EXPECT_FALSE(pattern->refreshOnWindowShow_);
}
} // namespace OHOS::Ace::NG
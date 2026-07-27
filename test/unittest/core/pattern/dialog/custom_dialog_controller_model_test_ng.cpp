/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/common/resource/resource_object.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dialog/custom_dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
void ReloadResources(DialogProperties& dialogProperties);
namespace {
constexpr int32_t TEST_DIALOG_NODE_ID = 100;
} // namespace

class CustomDialogControllerModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CustomDialogControllerModelTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == DialogTheme::TypeId()) {
                return AceType::MakeRefPtr<DialogTheme>();
            } else {
                return nullptr;
            }
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    AceEngine::Get().AddContainer(Container::CurrentId(), MockContainer::Current());
}

void CustomDialogControllerModelTestNg::TearDownTestCase()
{
    AceEngine::Get().RemoveContainer(Container::CurrentId());
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void CustomDialogControllerModelTestNg::SetUp() {}

void CustomDialogControllerModelTestNg::TearDown()
{
    MockContainer::Current()->ResetContainer();
    auto executor = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->taskExecutor_ = executor;
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    AceEngine::Get().RemoveContainer(0);
    AceEngine::Get().AddContainer(0, MockContainer::Current());
}

/**
 * @tc.name: ReloadResources001
 * @tc.desc: Test ReloadResources when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ReloadResources001, TestSize.Level1)
{
    auto savedFlag = g_isConfigChangePerform;
    g_isConfigChangePerform = false;

    DialogProperties props;
    props.maskColorResObj = AceType::MakeRefPtr<ResourceObject>();
    ReloadResources(props);

    EXPECT_FALSE(g_isConfigChangePerform);
    g_isConfigChangePerform = savedFlag;
}

/**
 * @tc.name: ReloadResources002
 * @tc.desc: Test ReloadResources when ConfigChangePerform is true and all resource objects are set
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ReloadResources002, TestSize.Level1)
{
    auto savedFlag = g_isConfigChangePerform;
    g_isConfigChangePerform = true;

    DialogProperties props;
    props.maskColorResObj = AceType::MakeRefPtr<ResourceObject>();
    props.backgroundColorResObj = AceType::MakeRefPtr<ResourceObject>();
    props.blurStyleOption = BlurStyleOption();
    props.effectOption = EffectOption();
    props.borderColor = NG::BorderColorProperty();
    props.shadow = Shadow();

    ReloadResources(props);

    EXPECT_TRUE(g_isConfigChangePerform);
    g_isConfigChangePerform = savedFlag;
}

/**
 * @tc.name: ReloadResources003
 * @tc.desc: Test ReloadResources when ConfigChangePerform is true but no resource objects are set
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ReloadResources003, TestSize.Level1)
{
    auto savedFlag = g_isConfigChangePerform;
    g_isConfigChangePerform = true;

    DialogProperties props;
    ReloadResources(props);

    EXPECT_TRUE(g_isConfigChangePerform);
    g_isConfigChangePerform = savedFlag;
}

/**
 * @tc.name: ReloadResources004
 * @tc.desc: Test ReloadResources with partial resource objects set
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ReloadResources004, TestSize.Level1)
{
    auto savedFlag = g_isConfigChangePerform;
    g_isConfigChangePerform = true;

    DialogProperties props;
    props.maskColorResObj = AceType::MakeRefPtr<ResourceObject>();
    props.blurStyleOption = BlurStyleOption();
    props.shadow = Shadow();

    ReloadResources(props);

    EXPECT_TRUE(g_isConfigChangePerform);
    g_isConfigChangePerform = savedFlag;
}

/**
 * @tc.name: SetOpenDialog001
 * @tc.desc: Test SetOpenDialog when container is null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog001, TestSize.Level1)
{
    auto savedContainer = MockContainer::container_;
    MockContainer::container_ = nullptr;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    WeakPtr<AceType> controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
    MockContainer::container_ = savedContainer;
}

/**
 * @tc.name: SetOpenDialog002
 * @tc.desc: Test SetOpenDialog when executor is null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog002, TestSize.Level1)
{
    auto savedExecutor = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->taskExecutor_ = nullptr;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    WeakPtr<AceType> controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
    MockContainer::Current()->taskExecutor_ = savedExecutor;
}

/**
 * @tc.name: SetOpenDialog003
 * @tc.desc: Test SetOpenDialog with valid controller and isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog003, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);
}

/**
 * @tc.name: SetOpenDialog004
 * @tc.desc: Test SetOpenDialog with valid controller and isShowInSubWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog004, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = true;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
}

/**
 * @tc.name: SetOpenDialog005
 * @tc.desc: Test SetOpenDialog with isSubContainer=true and isShowInSubWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog005, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    MockContainer::Current()->isSubContainer_ = true;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = true;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
}

/**
 * @tc.name: SetOpenDialog006
 * @tc.desc: Test SetOpenDialog with isSubContainer=true and isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog006, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    MockContainer::Current()->isSubContainer_ = true;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
}

/**
 * @tc.name: SetOpenDialog007
 * @tc.desc: Test SetOpenDialog with dialogLevelMode=EMBEDDED
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog007, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    props.dialogLevelMode = LevelMode::EMBEDDED;
    props.dialogLevelUniqueId = -1;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);
}

/**
 * @tc.name: SetOpenDialog008
 * @tc.desc: Test SetOpenDialog with null controller (ParseOpenDialogTask controller null branch)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialog008, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    WeakPtr<AceType> controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    std::function<void()> buildFunc;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;
    bool hasBind = false;

    controllerModel.SetOpenDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        std::move(buildFunc), dialogComponent, customDialog, dialogOperation, hasBind);

    EXPECT_FALSE(hasBind);
}

/**
 * @tc.name: SetOpenDialogInTask001
 * @tc.desc: Test SetOpenDialogInTask with null overlayManager
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask001, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    RefPtr<OverlayManager> overlayManager = nullptr;
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask002
 * @tc.desc: Test SetOpenDialogInTask with null container
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask002, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = nullptr;
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask003
 * @tc.desc: Test SetOpenDialogInTask with null controller
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask003, TestSize.Level1)
{
    WeakPtr<AceType> controller;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask004
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=true (SubwindowManager returns null)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask004, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = true;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask005
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=false (overlayManager->ShowDialog)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask005, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = false;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_NE(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask006
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=true, isModal=true, isSceneBoardDialog=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask006, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = false;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask007
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=true, isModal=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask007, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = false;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask008
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=true, isModal=true, isSceneBoardDialog=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask008, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = true;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask009
 * @tc.desc: Test SetOpenDialogInTask with isShowInSubWindow=true, isModal=true, isSceneBoardDialog=false,
 *           IsUIExtensionWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask009, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    MockContainer::Current()->SetIsUIExtensionWindow(true);
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = false;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    EXPECT_EQ(dialog, nullptr);
}

/**
 * @tc.name: SetOpenDialogInTask010
 * @tc.desc: Test SetOpenDialogInTask onStatusChanged callback with isShownStatus=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask010, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = false;
    bool isShown = true;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    ASSERT_NE(props.onStatusChanged, nullptr);
    props.onStatusChanged(false);
    EXPECT_FALSE(isShown);
}

/**
 * @tc.name: SetOpenDialogInTask011
 * @tc.desc: Test SetOpenDialogInTask onStatusChanged callback with isShownStatus=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogInTask011, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    RefPtr<Container> container = MockContainer::Current();
    RefPtr<NG::FrameNode> dialog;
    DialogProperties props;
    props.isShowInSubWindow = false;
    bool isShown = false;

    CustomDialogControllerModelNG::SetOpenDialogInTask(
        overlayManager, container, controller, dialog, props, nullptr, isShown);

    ASSERT_NE(props.onStatusChanged, nullptr);
    props.onStatusChanged(true);
    EXPECT_FALSE(isShown);
}

/**
 * @tc.name: SetOpenDialogWithNode004
 * @tc.desc: Test SetOpenDialogWithNode with isShowInSubWindow=true, isModal=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode004, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = false;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode005
 * @tc.desc: Test SetOpenDialogWithNode with IsUIExtensionWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode005, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    MockContainer::Current()->SetIsUIExtensionWindow(true);
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = false;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode006
 * @tc.desc: Test SetOpenDialogWithNode with isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode006, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode007
 * @tc.desc: Test SetOpenDialogWithNode with IsSubContainer=true, isShowInSubWindow=false
 *           ParentContainerId returns -1, GetContainer(-1) returns null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode007, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    MockContainer::Current()->isSubContainer_ = true;
    DialogProperties props;
    props.isShowInSubWindow = false;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode008
 * @tc.desc: Test SetOpenDialogWithNode with IsSubContainer=true, isShowInSubWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode008, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    MockContainer::Current()->isSubContainer_ = true;
    DialogProperties props;
    props.isShowInSubWindow = true;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode009
 * @tc.desc: Test SetOpenDialogWithNode with dialogLevelMode=EMBEDDED and isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode009, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    props.dialogLevelMode = LevelMode::EMBEDDED;
    props.dialogLevelUniqueId = -1;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: SetOpenDialogWithNode010
 * @tc.desc: Test SetOpenDialogWithNode with isShowInSubWindow=true, isModal=true,
 *           isSceneBoardDialog=false, IsUIExtensionWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetOpenDialogWithNode010, TestSize.Level1)
{
    CustomDialogControllerModelNG controllerModel;
    MockContainer::Current()->SetIsUIExtensionWindow(false);
    DialogProperties props;
    props.isShowInSubWindow = true;
    props.isModal = true;
    props.isSceneBoardDialog = false;

    auto result = controllerModel.SetOpenDialogWithNode(props, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SetCloseDialog001
 * @tc.desc: Test SetCloseDialog when container is null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog001, TestSize.Level1)
{
    auto savedContainer = MockContainer::container_;
    MockContainer::container_ = nullptr;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    WeakPtr<AceType> controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);

    MockContainer::container_ = savedContainer;
}

/**
 * @tc.name: SetCloseDialog002
 * @tc.desc: Test SetCloseDialog with isSubContainer=true and isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog002, TestSize.Level1)
{
    MockContainer::Current()->isSubContainer_ = true;

    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog003
 * @tc.desc: Test SetCloseDialog with valid controller and non-empty dialogs, isShowInSubWindow=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog003, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, TEST_DIALOG_NODE_ID, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog004
 * @tc.desc: Test SetCloseDialog with isShowInSubWindow=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog004, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, TEST_DIALOG_NODE_ID, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = true;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog005
 * @tc.desc: Test SetCloseDialog with empty dialogs
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog005, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog006
 * @tc.desc: Test SetCloseDialog with a dialog that is removing
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog006, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, TEST_DIALOG_NODE_ID, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->isRemoving_ = true;

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog007
 * @tc.desc: Test SetCloseDialog with null controller (ParseCloseDialogTask controller null)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog007, TestSize.Level1)
{
    WeakPtr<AceType> controller;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, TEST_DIALOG_NODE_ID, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog008
 * @tc.desc: Test SetCloseDialog with dialogLevelMode=EMBEDDED
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog008, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, TEST_DIALOG_NODE_ID,
            AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    props.dialogLevelMode = LevelMode::EMBEDDED;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialog009
 * @tc.desc: Test SetCloseDialog with non-FrameNode in dialogs (DynamicCast fails)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialog009, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;

    auto nonDialogNode = AceType::MakeRefPtr<Pattern>();

    CustomDialogControllerModelNG controllerModel;
    DialogProperties props;
    props.isShowInSubWindow = false;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(nonDialogNode));
    bool pending = false;
    bool isShown = false;
    std::function<void()> cancelTask;
    RefPtr<AceType> dialogComponent;
    RefPtr<AceType> customDialog;
    std::list<DialogOperation> dialogOperation;

    controllerModel.SetCloseDialog(props, controller, dialogs, pending, isShown, std::move(cancelTask),
        dialogComponent, customDialog, dialogOperation);
}

/**
 * @tc.name: SetCloseDialogForNDK001
 * @tc.desc: Test SetCloseDialogForNDK with null dialogNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialogForNDK001, TestSize.Level1)
{
    CustomDialogControllerModelNG::SetCloseDialogForNDK(nullptr);
}

/**
 * @tc.name: SetCloseDialogForNDK002
 * @tc.desc: Test SetCloseDialogForNDK when Container::Current() is null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialogForNDK002, TestSize.Level1)
{
    auto savedContainer = MockContainer::container_;
    MockContainer::container_ = nullptr;

    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG::SetCloseDialogForNDK(dialogNode.rawPtr_);

    MockContainer::container_ = savedContainer;
}

/**
 * @tc.name: SetCloseDialogForNDK003
 * @tc.desc: Test SetCloseDialogForNDK when Container::Current() is not null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, SetCloseDialogForNDK003, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG::SetCloseDialogForNDK(dialogNode.rawPtr_);
}

/**
 * @tc.name: GetState001
 * @tc.desc: Test GetState with hasBind=true and dialog null (dialogs empty)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState001, TestSize.Level1)
{
    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool hasBind = true;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::DISAPPEARED);
}

/**
 * @tc.name: GetState002
 * @tc.desc: Test GetState with hasBind=false and dialogs empty
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState002, TestSize.Level1)
{
    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    bool hasBind = false;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::UNINITIALIZED);
}

/**
 * @tc.name: GetState003
 * @tc.desc: Test GetState with hasBind=true and dialog not null but dialogPattern null
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState003, TestSize.Level1)
{
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(dialogNode, nullptr);

    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool hasBind = true;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::INITIALIZED);
}

/**
 * @tc.name: GetState004
 * @tc.desc: Test GetState with non-FrameNode in dialogs (DynamicCast fails, pop_back)
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState004, TestSize.Level1)
{
    auto nonDialogNode = AceType::MakeRefPtr<Pattern>();

    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(nonDialogNode));
    bool hasBind = false;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::UNINITIALIZED);
}

/**
 * @tc.name: GetState005
 * @tc.desc: Test GetState with non-FrameNode followed by valid dialog
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState005, TestSize.Level1)
{
    auto nonDialogNode = AceType::MakeRefPtr<Pattern>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetState(PromptActionCommonState::APPEARED);

    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(nonDialogNode));
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool hasBind = true;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::APPEARED);
}

/**
 * @tc.name: GetState006
 * @tc.desc: Test GetState with valid dialog and hasBind=true
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState006, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetState(PromptActionCommonState::APPEARING);

    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool hasBind = true;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::APPEARING);
}

/**
 * @tc.name: GetState007
 * @tc.desc: Test GetState with valid dialog and hasBind=false
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetState007, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetState(PromptActionCommonState::DISAPPEARED);

    CustomDialogControllerModelNG controller;
    std::vector<WeakPtr<AceType>> dialogs;
    dialogs.emplace_back(WeakPtr<AceType>(dialogNode));
    bool hasBind = false;

    auto state = controller.GetState(dialogs, hasBind);
    EXPECT_EQ(state, PromptActionCommonState::DISAPPEARED);
}

/**
 * @tc.name: GetStateWithNode001
 * @tc.desc: Test GetStateWithNode with null dialogNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetStateWithNode001, TestSize.Level1)
{
    auto state = CustomDialogControllerModelNG::GetStateWithNode(nullptr);
    EXPECT_EQ(state, PromptActionCommonState::INITIALIZED);
}

/**
 * @tc.name: GetStateWithNode002
 * @tc.desc: Test GetStateWithNode with dialogNode that has no DialogPattern
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetStateWithNode002, TestSize.Level1)
{
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(dialogNode, nullptr);

    auto state = CustomDialogControllerModelNG::GetStateWithNode(dialogNode.rawPtr_);
    EXPECT_EQ(state, PromptActionCommonState::INITIALIZED);
}

/**
 * @tc.name: GetStateWithNode003
 * @tc.desc: Test GetStateWithNode with valid dialogNode that has DialogPattern
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, GetStateWithNode003, TestSize.Level1)
{
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    auto dialogNode =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->SetState(PromptActionCommonState::APPEARED);

    auto state = CustomDialogControllerModelNG::GetStateWithNode(dialogNode.rawPtr_);
    EXPECT_EQ(state, PromptActionCommonState::APPEARED);
}

/**
 * @tc.name: ParseCloseDialogTask001
 * @tc.desc: Test ParseCloseDialogTask with null overlayManager
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ParseCloseDialogTask001, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    DialogProperties props;
    std::vector<WeakPtr<AceType>> dialogs;
    RefPtr<OverlayManager> overlayManager = nullptr;

    CustomDialogControllerModelNG controllerModel;
    auto task = controllerModel.ParseCloseDialogTask(controller, props, dialogs, overlayManager);
    ASSERT_NE(task, nullptr);
    task();
}

/**
 * @tc.name: ParseCloseDialogTask002
 * @tc.desc: Test ParseCloseDialogTask with null controller
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ParseCloseDialogTask002, TestSize.Level1)
{
    WeakPtr<AceType> controller;
    DialogProperties props;
    std::vector<WeakPtr<AceType>> dialogs;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();

    CustomDialogControllerModelNG controllerModel;
    auto task = controllerModel.ParseCloseDialogTask(controller, props, dialogs, overlayManager);
    ASSERT_NE(task, nullptr);
    task();
}

/**
 * @tc.name: ParseCloseDialogTask003
 * @tc.desc: Test ParseCloseDialogTask with empty dialogs
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerModelTestNg, ParseCloseDialogTask003, TestSize.Level1)
{
    auto controllerNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<AceType> controller = controllerNode;
    DialogProperties props;
    std::vector<WeakPtr<AceType>> dialogs;
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();

    CustomDialogControllerModelNG controllerModel;
    auto task = controllerModel.ParseCloseDialogTask(controller, props, dialogs, overlayManager);
    ASSERT_NE(task, nullptr);
    task();
}
} // namespace OHOS::Ace::NG

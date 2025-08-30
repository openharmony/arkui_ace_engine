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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_resource_register.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/common/asset/mock_asset.h"

#include "common/include/window_session_property.h"
#include "session_manager/include/scene_session_manager.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string ABILITY_NAME = "MainAbility";
const std::string BUNDLE_NAME = "com.example.helloworld";
const std::string MODULE_NAME = "entry";
const uint32_t WAIT_SYNC_IN_NS = 200000;
} // namespace

class WindowSceneTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    static sptr<Rosen::SceneSessionManager> ssm_;

    RefPtr<WindowScene> CreateWindowSceneForStartingWindowTest(Rosen::SessionInfo& sessionInfo);
};

sptr<Rosen::SceneSessionManager> WindowSceneTest::ssm_ = nullptr;

void WindowSceneTest::SetUpTestSuite()
{
    ssm_ = &Rosen::SceneSessionManager::GetInstance();
    ASSERT_NE(ssm_, nullptr);
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void WindowSceneTest::TearDownTestSuite()
{
    ssm_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void WindowSceneTest::SetUp()
{
    ssm_->sceneSessionMap_.clear();
}

void WindowSceneTest::TearDown()
{
    usleep(WAIT_SYNC_IN_NS);
    ssm_->sceneSessionMap_.clear();
}

RefPtr<WindowScene> WindowSceneTest::CreateWindowSceneForStartingWindowTest(Rosen::SessionInfo& sessionInfo)
{
    auto session = ssm_->RequestSceneSession(sessionInfo);
    CHECK_EQUAL_RETURN(session, nullptr, nullptr);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    CHECK_EQUAL_RETURN(windowScene, nullptr, nullptr);

    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    CHECK_EQUAL_RETURN(session->surfaceNode_, nullptr, nullptr);
    session->surfaceNode_->bufferAvailable_ = true;

    auto startingWindowNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->startingWindow_ = AceType::RawPtr(startingWindowNode);
    CHECK_EQUAL_RETURN(windowScene->startingWindow_, nullptr, nullptr);
    windowScene->startingWindow_->renderContext_ = AceType::MakeRefPtr<RosenRenderContext>();
    CHECK_EQUAL_RETURN(windowScene->startingWindow_->renderContext_, nullptr, nullptr);
    return windowScene;
}

/**
 * @tc.name: WindowSceneTest01
 * @tc.desc: Create WindowNode with invalid persistentId
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, WindowSceneTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create WindowNode.
     */
    int32_t persistentId = 0;
    WindowSceneModel::Create(persistentId);
    /**
     * @tc.steps: step2. Get and check WindowNode.
     */
    auto windowNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(windowNode, nullptr);
}

/**
 * @tc.name: WindowSceneTest02
 * @tc.desc: Create WindowScene with valid persistentId
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, WindowSceneTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Request scene session.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    /**
     * @tc.steps: step2. Create WindowNode with persistentId.
     */
    int32_t persistentId = session->GetPersistentId();
    WindowSceneModel::Create(persistentId);
    /**
     * @tc.steps: step3. Get and check WindowNode.
     */
    auto windowNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(windowNode, nullptr);
}

/**
 * @tc.name: BufferAvailableCallback01
 * @tc.desc: Buffer aviliable callback when enable app remove starting window and app not ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, BufferAvailableCallback01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = true;
    windowScene->session_->appBufferReady_ = false;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    EXPECT_NE(windowScene->startingWindow_, nullptr);
    windowScene->BufferAvailableCallback();
    EXPECT_EQ(windowScene->session_->surfaceNode_->bufferAvailable_, true);
}

/**
 * @tc.name: BufferAvailableCallback02
 * @tc.desc: Buffer aviliable callback when enable app remove starting window and app ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, BufferAvailableCallback02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = true;
    windowScene->session_->appBufferReady_ = true;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->BufferAvailableCallback();
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: BufferAvailableCallback03
 * @tc.desc: Buffer aviliable callback when not enable app remove starting window and app ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, BufferAvailableCallback03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->appBufferReady_ = true;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->BufferAvailableCallback();
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: BufferAvailableCallback04
 * @tc.desc: Buffer aviliable callback when not enable app remove starting window and app not ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, BufferAvailableCallback04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->appBufferReady_ = false;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->BufferAvailableCallback();
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: AddPersistentImage
 * @tc.desc: add persistent image
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, AddPersistentImage, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->appBufferReady_ = false;
    windowScene->session_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test add persistent image return false.
     */
    auto result = windowScene->AddPersistentImage(windowScene->session_->surfaceNode_, windowScene->GetHost());
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: AddBackgroundColorDelayed
 * @tc.desc: add background color delayed
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, AddBackgroundColorDelayed, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->appBufferReady_ = false;
    windowScene->session_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test add snapshot background color delayed.
     */
    windowScene->session_->SetExitSplitOnBackground(false);
    windowScene->AddBackgroundColorDelayed();
    EXPECT_EQ(windowScene->needAddBackgroundColor_, true);

    windowScene->session_->SetExitSplitOnBackground(true);
    windowScene->AddBackgroundColorDelayed();
    EXPECT_EQ(windowScene->needAddBackgroundColor_, true);
}

/**
 * @tc.name: OnAppRemoveStartingWindow01
 * @tc.desc: App ready callback when enable app remove starting window and rs not ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAppRemoveStartingWindow01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = true;
    windowScene->session_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->OnAppRemoveStartingWindow();
    EXPECT_EQ(windowScene->session_->appBufferReady_, true);
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_NE(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: OnAppRemoveStartingWindow02
 * @tc.desc: App ready callback when enable app remove starting window and rs ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAppRemoveStartingWindow02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = true;
    windowScene->session_->surfaceNode_->bufferAvailable_ = true;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->OnAppRemoveStartingWindow();
    EXPECT_EQ(windowScene->session_->appBufferReady_, true);
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: OnAppRemoveStartingWindow03
 * @tc.desc: App ready callback when not enable app remove starting window and rs ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAppRemoveStartingWindow03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->surfaceNode_->bufferAvailable_ = true;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->OnAppRemoveStartingWindow();
    EXPECT_EQ(windowScene->session_->appBufferReady_, false);
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_NE(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: OnAppRemoveStartingWindow04
 * @tc.desc: App ready callback when not enable app remove starting window and rs not ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAppRemoveStartingWindow04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->session_->enableRemoveStartingWindow_ = false;
    windowScene->session_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test and check starting window.
     */
    windowScene->OnAppRemoveStartingWindow();
    EXPECT_EQ(windowScene->session_->appBufferReady_, false);
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_NE(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: OnPreLoadStartingWindowFinished
 * @tc.desc: preload starting window finished
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnPreLoadStartingWindowFinished, TestSize.Level1)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    windowScene->OnPreLoadStartingWindowFinished();
    usleep(WAIT_SYNC_IN_NS);
    ASSERT_NE(windowScene->startingWindow_, nullptr);
}

/**
 * @tc.name: OnUpdateSnapshotWindow
 * @tc.desc: update snapshot window
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnUpdateSnapshotWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    /**
     * @tc.steps: step2. Test and check snapshot window.
     */
    windowScene->OnUpdateSnapshotWindow();
    EXPECT_EQ(windowScene->session_->GetSnapshot(), nullptr);
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->snapshotWindow_, nullptr);
}

/**
 * @tc.name: OnAddRemoveSnapshot
 * @tc.desc: add and remove snapshot
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAddRemoveSnapshot, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    /**
     * @tc.steps: step2. Test and check
     */
    windowScene->OnAddSnapshot();
    windowScene->OnRemoveSnapshot();
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->session_->GetSnapshot(), nullptr);
}

/**
 * @tc.name: IsMainSessionRecent
 * @tc.desc: check main session recent
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, IsMainSessionRecent, TestSize.Level0)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    Rosen::SessionInfo subSessionInfo = {
        .abilityName_ = "SUB_ABILITY_NAME",
        .bundleName_ = "SUB_BUNDLE_NAME",
        .moduleName_ = "SUB_MODULE_NAME",
    };
    auto subSession = ssm_->RequestSceneSession(subSessionInfo);
    ASSERT_NE(subSession, nullptr);
    auto subWindowScene = AceType::MakeRefPtr<WindowScene>(subSession);
    ASSERT_NE(subWindowScene, nullptr);
    auto subFrameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), subWindowScene);
    subWindowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(subFrameNode));
    ASSERT_NE(subWindowScene->GetHost(), nullptr);
    windowScene->AddChild(windowScene->GetHost(), subFrameNode, "subWindow");

    auto ret = subWindowScene->IsMainSessionRecent();
    EXPECT_EQ(ret, false);

    session->SetShowRecent(true);
    ret = subWindowScene->IsMainSessionRecent();
    EXPECT_EQ(ret, true);

    auto startingWindowNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->startingWindow_ = AceType::RawPtr(startingWindowNode);
    ASSERT_NE(windowScene->startingWindow_, nullptr);
    ret = subWindowScene->IsMainSessionRecent();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: HideStartingWindow
 * @tc.desc: HideStartingWindow
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, HideStartingWindowInvisible, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
        .startWindowType_ = Rosen::StartWindowType::RETAIN_AND_INVISIBLE,
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);

    /**
     * @tc.steps: step2. Set hiding.
     */
    windowScene->CreateStartingWindow();

    /**
     * @tc.steps: step3. Test and check
     */
    ASSERT_EQ(windowScene->session_->GetHidingStartingWindow(), true);
}

/**
 * @tc.name: HideStartingWindow
 * @tc.desc: HideStartingWindow
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, HideStartingWindowDefalut, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
        .startWindowType_ = Rosen::StartWindowType::DEFAULT,
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);

    /**
     * @tc.steps: step2. Set default.
     */
    windowScene->CreateStartingWindow();

    /**
     * @tc.steps: step3. Test and check
     */
    ASSERT_EQ(windowScene->session_->GetHidingStartingWindow(), false);
}

/**
 * @tc.name: SetSubSessionVisible
 * @tc.desc: set sub session visible
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, SetSubSessionVisible, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    /**
     * @tc.steps: step2. Set sub session.
     */
    Rosen::SessionInfo subSessionInfo = {
        .abilityName_ = "SUB_ABILITY_NAME",
        .bundleName_ = "SUB_BUNDLE_NAME",
        .moduleName_ = "SUB_MODULE_NAME",
    };
    auto subSession = ssm_->RequestSceneSession(subSessionInfo);
    ASSERT_NE(subSession, nullptr);
    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    subSession->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    ASSERT_NE(subSession->surfaceNode_, nullptr);
    subSession->surfaceNode_->SetVisible(false);
    windowScene->weakSubSessions_.push_back(subSession);
    /**
     * @tc.steps: step3. Test and check
     */
    windowScene->SetSubSessionVisible();
    ASSERT_EQ(subSession->surfaceNode_->GetStagingProperties().GetVisible(), true);
}

/**
 * @tc.name: OnLayoutFinished
 * @tc.desc: OnLayoutFinished Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnLayoutFinished, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    auto windowScene = CreateWindowSceneForStartingWindowTest(sessionInfo);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    windowScene->session_->SetShowRecent(true);
    windowScene->OnLayoutFinished();
    EXPECT_EQ(windowScene->session_->GetShowRecent(), true);
}

/**
 * @tc.name: CreateSnapshotWindow
 * @tc.desc: CreateSnapshotWindow Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, CreateSnapshotWindow, TestSize.Level0)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    session->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr("bundleName", 1);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);
    windowScene->isBlankForSnapshot_ = true;
    windowScene->CreateSnapshotWindow();
    auto key = Rosen::defaultStatus;
    session->scenePersistence_->SetHasSnapshot(true, key);
    windowScene->CreateSnapshotWindow();

    session->scenePersistence_->isSavingSnapshot_[key.first][key.second] = true;
    session->freeMultiWindow_.store(true);
    windowScene->CreateSnapshotWindow();
    EXPECT_EQ(windowScene->isBlankForSnapshot_, false);
}

/**
 * @tc.name: OnAttachToFrameNode
 * @tc.desc: OnAttachToFrameNode Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAttachToFrameNode, TestSize.Level0)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    session->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr("bundleName", 1);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    session->state_ = Rosen::SessionState::STATE_DISCONNECT;
    session->SetShowRecent(true);
    auto key = Rosen::defaultStatus;
    session->scenePersistence_->isSavingSnapshot_[key.first][key.second] = true;
    windowScene->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(session->GetShowRecent(), true);
}

/**
 * @tc.name: OnBoundsChanged
 * @tc.desc: OnBoundsChanged Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnBoundsChanged, TestSize.Level0)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    session->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr("bundleName", 1);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene);
    windowScene->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ASSERT_NE(windowScene->GetHost(), nullptr);

    Rosen::Vector4f bounds {1.0, 1.0, 1.0, 1.0};
    session->SetShowRecent(true);
    windowScene->OnBoundsChanged(bounds);
    EXPECT_EQ(session->GetShowRecent(), true);
    session->SetShowRecent(false);
    windowScene->OnBoundsChanged(bounds);
    EXPECT_EQ(session->GetShowRecent(), false);
}

/**
 * @tc.name: TransformOrientationForMatchSnapshot
 * @tc.desc: TransformOrientationForMatchSnapshot Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, TransformOrientationForMatchSnapshot, TestSize.Level1)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    session->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr("bundleName", 1);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);

    uint32_t lastRotation = 2;
    uint32_t windowRotation = 0;
    auto ret = windowScene->TransformOrientationForMatchSnapshot(lastRotation, windowRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    auto ret1 = windowScene->TransformOrientation(lastRotation, windowRotation, 0);
    EXPECT_EQ(ret1, 0);
}

/**
 * @tc.name: TransformOrientationForDisMatchSnapshot
 * @tc.desc: TransformOrientationForDisMatchSnapshot Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, TransformOrientationForDisMatchSnapshot, TestSize.Level1)
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = "ABILITY_NAME",
        .bundleName_ = "BUNDLE_NAME",
        .moduleName_ = "MODULE_NAME",
    };
    auto session = ssm_->RequestSceneSession(sessionInfo);
    ASSERT_NE(session, nullptr);
    session->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr("bundleName", 1);
    auto windowScene = AceType::MakeRefPtr<WindowScene>(session);
    ASSERT_NE(windowScene, nullptr);

    uint32_t lastRotation = 3;
    uint32_t windowRotation = 0;
    uint32_t snapshotRotation = 0;
    auto ret = windowScene->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::LEFT);

    windowRotation = 1;
    ret = windowScene->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::RIGHT);

    lastRotation = 2;
    ret = windowScene->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    lastRotation = 0;
    ret = windowScene->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    windowRotation = 2;
    snapshotRotation = 2;
    ret = windowScene->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);
}
} // namespace OHOS::Ace::NG
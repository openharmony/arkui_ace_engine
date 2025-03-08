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

    RefPtr<WindowScene> CreateWindowSceneForStartingWindowTest();
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

RefPtr<WindowScene> WindowSceneTest::CreateWindowSceneForStartingWindowTest()
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
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
HWTEST_F(WindowSceneTest, WindowSceneTest01, TestSize.Level1)
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
HWTEST_F(WindowSceneTest, WindowSceneTest02, TestSize.Level1)
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
HWTEST_F(WindowSceneTest, BufferAvailableCallback01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
 * @tc.name: OnAppRemoveStartingWindow01
 * @tc.desc: App ready callback when enable app remove starting window and rs not ready
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAppRemoveStartingWindow01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
    auto windowScene = CreateWindowSceneForStartingWindowTest();
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
 * @tc.name: OnAddRemoveSnapshot
 * @tc.desc: add and remove snapshot
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneTest, OnAddRemoveSnapshot, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create windowScene.
     */
    auto windowScene = CreateWindowSceneForStartingWindowTest();
    ASSERT_NE(windowScene, nullptr);
    /**
     * @tc.steps: step2. Test and check
     */
    windowScene->OnAddSnapshot();
    windowScene->OnRemoveSnapshot();
    usleep(WAIT_SYNC_IN_NS);
    EXPECT_EQ(windowScene->session_->GetSnapshot(), nullptr);
}
} // namespace OHOS::Ace::NG
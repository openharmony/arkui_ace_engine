/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "key_event.h"
#include "pointer_event.h"
#include "session_manager/include/scene_session_manager.h"
#include "ui/rs_surface_node.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_extension.h"
#include "core/components_ng/pattern/window_scene/scene/window_node.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "test/mock/core/common/mock_container.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.helloworld";
const std::string ABILITY_NAME = "MainAbility";
const int32_t NODE_ID = 1000;
} // namespace

class WindowPatternTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: WindowPatternTest001
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    auto model = WindowSceneModel();
    uint64_t persistentId = 0;
    model.Create(persistentId);

    auto windowSceneNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(windowSceneNode, nullptr);
}

/**
 * @tc.name: WindowPatternTest002
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: WindowPatternTest003
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    EXPECT_NE(session->surfaceNode_, nullptr);

    auto pattern = frameNode->GetPattern<WindowScene>();
    pattern->OnConnect();
    pattern->BufferAvailableCallback();
    pattern->OnForeground();
    pattern->OnBackground();
}

/**
 * @tc.name: WindowPatternTest004
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();

    /**
     * @tc.steps: step2. Set session state to STATE_DISCONNECT.
     */
    session->state_ = Rosen::SessionState::STATE_DISCONNECT;
    model.Create(persistentId);
    auto frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set session state to STATE_ACTIVE.
     */
    session->state_ = Rosen::SessionState::STATE_ACTIVE;
    model.Create(persistentId);
    frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set session state to STATE_BACKGROUND.
     */
    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    EXPECT_NE(session->surfaceNode_, nullptr);
    session->state_ = Rosen::SessionState::STATE_BACKGROUND;
    model.Create(persistentId);
    frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: WindowPatternTest005
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    EXPECT_NE(session->surfaceNode_, nullptr);

    TouchRestrict touchRestrict;
    TouchTestResult testResult;
    auto result = frameNode->TouchTest(PointF(), PointF(), touchRestrict, testResult, 1);
    EXPECT_EQ(static_cast<int>(HitTestResult::BUBBLING), static_cast<int>(result));
}

/**
 * @tc.name: WindowPatternTest006
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode =
        AceType::DynamicCast<WindowNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WindowScene>();
    ASSERT_NE(pattern, nullptr);

    auto dirty = AceType::MakeRefPtr<LayoutWrapper>(nullptr, AceType::MakeRefPtr<GeometryNode>(), nullptr);
    DirtySwapConfig config;
    config.frameSizeChange = false;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(dirty, config), false);

    config.frameSizeChange = true;
    EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(dirty, config), false);

    auto pointerEvent = MMI::PointerEvent::Create();
    pattern->DispatchPointerEvent(pointerEvent);

    auto keyEvent = MMI::KeyEvent::Create();
    pattern->DispatchKeyEvent(keyEvent);
}

/**
 * @tc.name: WindowPatternTest007
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowExtension.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);

    auto pattern = AceType::MakeRefPtr<WindowExtension>(BUNDLE_NAME, ABILITY_NAME);
    ASSERT_NE(pattern, nullptr);

    pattern->OnConnect();
    pattern->OnWindowShow();
    pattern->OnWindowHide();
}

/**
 * @tc.name: WindowPatternTest008
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowExtension.
     */
    MockPipelineBase::SetUp();
    MockContainer::SetUp();
    MockContainer::container_->pipelineContext_ = MockPipelineBase::pipeline_;
    auto container = Container::Current();
    EXPECT_NE(container, nullptr);
    auto context = container->GetPipelineContext();
    EXPECT_NE(context, nullptr);

    auto pattern = AceType::MakeRefPtr<WindowExtension>(BUNDLE_NAME, ABILITY_NAME);
    ASSERT_NE(pattern, nullptr);

    pattern->OnAttachToFrameNode();
    pattern->InitContent();
    pattern->CreateSnapshotNode();
    pattern->CreateStartingNode();
}

/**
 * @tc.name: WindowPatternTest009
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get or create WindowExtension.
     * @tc.expect: Get or create WindowExtension success.
     */
    auto frameNode1 = WindowNode::GetOrCreateWindowNode("WindowNode", NODE_ID,
        []() { return AceType::MakeRefPtr<WindowExtension>(BUNDLE_NAME, ABILITY_NAME); });
    EXPECT_NE(frameNode1, nullptr);

    /**
     * @tc.steps: step2. Get or create WindowExtension.
     * @tc.expect: frameNode1 equal frameNode2.
     */
    auto frameNode2 = WindowNode::GetOrCreateWindowNode("WindowNode", NODE_ID,
        []() { return AceType::MakeRefPtr<WindowExtension>(BUNDLE_NAME, ABILITY_NAME); });
    EXPECT_EQ(frameNode1, frameNode2);

    /**
     * @tc.steps: step3. Get or create WindowExtension.
     * @tc.expect: frameNode2 does not equal frameNode3.
     */
    auto frameNode3 = WindowNode::GetOrCreateWindowNode("WindowNode2", NODE_ID,
        []() { return AceType::MakeRefPtr<WindowExtension>(BUNDLE_NAME, ABILITY_NAME); });
    EXPECT_NE(frameNode2, frameNode3);
}

/**
 * @tc.name: WindowPatternTest010
 * @tc.desc: WindowPattern test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, WindowPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WindowSceneModel.
     */
    auto model = WindowSceneModel();

    Rosen::SessionInfo sessionInfo = {
        .bundleName_ = BUNDLE_NAME,
        .abilityName_ = ABILITY_NAME,
        .isSystem_ = true
    };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    uint64_t persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode =
        AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<SystemWindowScene>();
    ASSERT_NE(pattern, nullptr);
}
} // namespace OHOS::Ace::NG

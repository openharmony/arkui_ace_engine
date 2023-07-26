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
#include "test/mock/core/common/mock_container.h"
#include "ui/rs_surface_node.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/window_scene/root/root_scene_model.h"
#include "core/components_ng/pattern/window_scene/root/root_scene_node.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene.h"
#include "core/components_ng/pattern/window_scene/scene/window_scene_model.h"
#include "core/components_ng/pattern/window_scene/screen/screen_model.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.helloworld";
const std::string ABILITY_NAME = "MainAbility";
} // namespace

class WindowPatternTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: ScreenPatternTest001
 * @tc.desc: Screen test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, ScreenPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScreenModel.
     */
    auto model = ScreenModel();
    uint64_t screenId = 0;
    model.Create(screenId);

    auto screenNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_EQ(screenNode, nullptr);
}

/**
 * @tc.name: RootSceneTest001
 * @tc.desc: RootScene test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, RootSceneTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RootSceneModel.
     */
    auto model = RootSceneModel();
    model.Create();

    /**
     * @tc.steps: step2. Create RootScene.
     */
    auto rootSceneNode = AceType::DynamicCast<RootSceneNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(rootSceneNode, nullptr);
    auto isAtomic = rootSceneNode->IsAtomicNode();
    EXPECT_EQ(isAtomic, false);
}

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
    int32_t persistentId = 0;
    model.Create(persistentId);

    auto windowSceneNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
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

    Rosen::SessionInfo sessionInfo = { .bundleName_ = BUNDLE_NAME, .abilityName_ = ABILITY_NAME };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    auto persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
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

    Rosen::SessionInfo sessionInfo = { .bundleName_ = BUNDLE_NAME, .abilityName_ = ABILITY_NAME };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    auto persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(frameNode, nullptr);

    Rosen::RSSurfaceNodeConfig config = { .SurfaceNodeName = "SurfaceNode" };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    EXPECT_NE(session->surfaceNode_, nullptr);
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

    Rosen::SessionInfo sessionInfo = { .bundleName_ = BUNDLE_NAME, .abilityName_ = ABILITY_NAME };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    auto persistentId = session->GetPersistentId();

    /**
     * @tc.steps: step2. Set session state to STATE_DISCONNECT.
     */
    session->state_ = Rosen::SessionState::STATE_DISCONNECT;
    model.Create(persistentId);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set session state to STATE_ACTIVE.
     */
    session->state_ = Rosen::SessionState::STATE_ACTIVE;
    model.Create(persistentId);
    frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step3. Set session state to STATE_BACKGROUND.
     */
    Rosen::RSSurfaceNodeConfig config = { .SurfaceNodeName = "SurfaceNode" };
    session->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    EXPECT_NE(session->surfaceNode_, nullptr);
    session->state_ = Rosen::SessionState::STATE_BACKGROUND;
    model.Create(persistentId);
    frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(frameNode, nullptr);
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

    Rosen::SessionInfo sessionInfo = { .bundleName_ = BUNDLE_NAME, .abilityName_ = ABILITY_NAME };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    auto persistentId = session->GetPersistentId();
    model.Create(persistentId);
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

    Rosen::SessionInfo sessionInfo = { .bundleName_ = BUNDLE_NAME, .abilityName_ = ABILITY_NAME, .isSystem_ = true };
    auto session = Rosen::SceneSessionManager::GetInstance().RequestSceneSession(sessionInfo);
    auto persistentId = session->GetPersistentId();
    model.Create(persistentId);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_NE(frameNode, nullptr);
}
} // namespace OHOS::Ace::NG

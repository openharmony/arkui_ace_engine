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
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
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

class WindowPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    static sptr<Rosen::SceneSessionManager> ssm_;
    sptr<Rosen::SceneSession> sceneSession_;
    RefPtr<FrameNode> frameNode_;
    RefPtr<WindowScene> windowScene_;

    void CreateWindowSceneWindowPatternTest();
};

sptr<Rosen::SceneSessionManager> WindowPatternTest::ssm_ = nullptr;

void WindowPatternTest::SetUpTestSuite()
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

void WindowPatternTest::TearDownTestSuite()
{
    ssm_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void WindowPatternTest::SetUp()
{
    ssm_->sceneSessionMap_.clear();
    CreateWindowSceneWindowPatternTest();
}

void WindowPatternTest::TearDown()
{
    usleep(WAIT_SYNC_IN_NS);
    ssm_->sceneSessionMap_.clear();
}

void WindowPatternTest::CreateWindowSceneWindowPatternTest()
{
    Rosen::SessionInfo sessionInfo = {
        .abilityName_ = ABILITY_NAME,
        .bundleName_ = BUNDLE_NAME,
        .moduleName_ = MODULE_NAME,
    };
    sceneSession_ = sptr<Rosen::SceneSession>::MakeSptr(sessionInfo, nullptr);
    sceneSession_->scenePersistence_ = sptr<Rosen::ScenePersistence>::MakeSptr(
        BUNDLE_NAME, sceneSession_->persistentId_);
    windowScene_ = AceType::MakeRefPtr<WindowScene>(sceneSession_);
    ASSERT_NE(windowScene_, nullptr);

    frameNode_ = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), windowScene_);
    windowScene_->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode_));
    ASSERT_NE(windowScene_->GetHost(), nullptr);

    Rosen::RSSurfaceNodeConfig config = {
        .SurfaceNodeName = "SurfaceNode"
    };
    sceneSession_->surfaceNode_ = Rosen::RSSurfaceNode::Create(config);
    ASSERT_NE(sceneSession_->surfaceNode_, nullptr);
    sceneSession_->surfaceNode_->bufferAvailable_ = true;
}

/**
 * @tc.name: AddPersistentImage
 * @tc.desc: add persistent image
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, AddPersistentImage, TestSize.Level1)
{
    ASSERT_NE(windowScene_, nullptr);
    ASSERT_NE(windowScene_->GetHost(), nullptr);
    sceneSession_->enableRemoveStartingWindow_ = false;
    sceneSession_->appBufferReady_ = false;
    sceneSession_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test add persistent image return false.
     */
    auto result = windowScene_->AddPersistentImage(sceneSession_->surfaceNode_, windowScene_->GetHost());
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: AddBackgroundColorDelayed
 * @tc.desc: add background color delayed
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, AddBackgroundColorDelayed, TestSize.Level1)
{
    ASSERT_NE(windowScene_, nullptr);
    ASSERT_NE(windowScene_->GetHost(), nullptr);
    sceneSession_->enableRemoveStartingWindow_ = false;
    sceneSession_->appBufferReady_ = false;
    sceneSession_->surfaceNode_->bufferAvailable_ = false;
    /**
     * @tc.steps: step2. Test add snapshot background color delayed.
     */
    sceneSession_->SetExitSplitOnBackground(false);
    windowScene_->AddBackgroundColorDelayed();
    EXPECT_EQ(windowScene_->needAddBackgroundColor_, true);

    sceneSession_->SetExitSplitOnBackground(true);
    windowScene_->AddBackgroundColorDelayed();
    EXPECT_EQ(windowScene_->needAddBackgroundColor_, true);
}

/**
 * @tc.name: CreateSnapshotWindow
 * @tc.desc: CreateSnapshotWindow Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, CreateSnapshotWindow, TestSize.Level0)
{
    ASSERT_NE(windowScene_, nullptr);
    ASSERT_NE(windowScene_->GetHost(), nullptr);
    windowScene_->isBlankForSnapshot_ = true;
    windowScene_->CreateSnapshotWindow();
    auto key = Rosen::defaultStatus;
    sceneSession_->scenePersistence_->SetHasSnapshot(true, key);
    windowScene_->CreateSnapshotWindow();

    sceneSession_->scenePersistence_->isSavingSnapshot_[key] = true;
    sceneSession_->freeMultiWindow_.store(true);
    windowScene_->CreateSnapshotWindow();
    EXPECT_EQ(windowScene_->isBlankForSnapshot_, false);
}

/**
 * @tc.name: OnAttachToFrameNode
 * @tc.desc: OnAttachToFrameNode Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, OnAttachToFrameNode, TestSize.Level0)
{
    ASSERT_NE(windowScene_, nullptr);
    ASSERT_NE(windowScene_->GetHost(), nullptr);

    sceneSession_->state_ = Rosen::SessionState::STATE_DISCONNECT;
    sceneSession_->SetShowRecent(true);
    auto key = Rosen::defaultStatus;
    sceneSession_->scenePersistence_->isSavingSnapshot_[key] = true;
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(sceneSession_->GetShowRecent(), true);

    sceneSession_->state_ = Rosen::SessionState::STATE_BACKGROUND;
    sceneSession_->SetShowRecent(false);
    sceneSession_->isAppLockControl_.store(false);
    sceneSession_->scenePersistence_->hasSnapshot_[key] = true;
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);

    sceneSession_->SetShowRecent(false);
    sceneSession_->isAppLockControl_.store(true);
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);

    sceneSession_->SetShowRecent(true);
    sceneSession_->isAppLockControl_.store(false);
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);

    sceneSession_->SetShowRecent(true);
    sceneSession_->isAppLockControl_.store(true);
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);

    sceneSession_->state_ = Rosen::SessionState::STATE_ACTIVE;
    sceneSession_->SetShowRecent(false);
    sceneSession_->isAppLockControl_.store(false);
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);

    sceneSession_->isAppLockControl_.store(true);
    windowScene_->WindowPattern::OnAttachToFrameNode();
    EXPECT_EQ(windowScene_->attachToFrameNodeFlag_, true);
}

/**
 * @tc.name: TransformOrientationForMatchSnapshot
 * @tc.desc: TransformOrientationForMatchSnapshot Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, TransformOrientationForMatchSnapshot, TestSize.Level1)
{
    ASSERT_NE(windowScene_, nullptr);

    uint32_t lastRotation = 2;
    uint32_t windowRotation = 0;
    auto ret = windowScene_->TransformOrientationForMatchSnapshot(lastRotation, windowRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    auto ret1 = windowScene_->TransformOrientation(lastRotation, windowRotation, 0);
    EXPECT_EQ(ret1, 0);
}

/**
 * @tc.name: TransformOrientationForDisMatchSnapshot
 * @tc.desc: TransformOrientationForDisMatchSnapshot Test
 * @tc.type: FUNC
 */
HWTEST_F(WindowPatternTest, TransformOrientationForDisMatchSnapshot, TestSize.Level1)
{
    ASSERT_NE(windowScene_, nullptr);

    uint32_t lastRotation = 3;
    uint32_t windowRotation = 0;
    uint32_t snapshotRotation = 0;
    auto ret = windowScene_->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::LEFT);

    windowRotation = 1;
    ret = windowScene_->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::RIGHT);

    lastRotation = 2;
    ret = windowScene_->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    lastRotation = 0;
    ret = windowScene_->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);

    windowRotation = 2;
    snapshotRotation = 2;
    ret = windowScene_->TransformOrientationForDisMatchSnapshot(lastRotation, windowRotation, snapshotRotation);
    EXPECT_EQ(ret, ImageRotateOrientation::UP);
}
} // namespace OHOS::Ace::NG
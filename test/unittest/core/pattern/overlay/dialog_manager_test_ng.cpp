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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "core/common/ace_engine.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"


using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class DialogManagerTestNg : public testing::Test {
    public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void DialogManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DialogManagerTest001
 * @tc.desc: Test FindPageNodeOverlay
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest001, TestSize.Level1)
{
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 101, dialogPattern);
    auto dialogNodeOnTree = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, 102, dialogPattern);
    DialogManager dialogManager;
    auto ret = dialogManager.FindPageNodeOverlay(nullptr);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.FindPageNodeOverlay(dialogNode);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.FindPageNodeOverlay(dialogNodeOnTree);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: DialogManagerTest002
 * @tc.desc: Test GetEmbeddedOverlay
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest002, TestSize.Level1)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 101, dialogPattern);
    auto dialogNodeOnTree = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, 102, dialogPattern);
    DialogManager dialogManager;
    auto ret = dialogManager.GetEmbeddedOverlay(1, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(101, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(102, context);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlay(-1, context);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: DialogManagerTest003
 * @tc.desc: Test GetEmbeddedOverlayWithNode&GetDialogNodeByContentNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest003, TestSize.Level1)
{
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 201, AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG, 301, AceType::MakeRefPtr<StagePattern>());
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 401, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto pageDialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 501, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    auto navigationNode = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 601, AceType::MakeRefPtr<NavDestinationPattern>());
    auto navDialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 701, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    auto columnNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, 801, AceType::MakeRefPtr<OHOS::Ace::NG::LinearLayoutPattern>(true));
    stageNode->MountToParent(rootNode);
    pageNode->MountToParent(stageNode);
    navigationNode->MountToParent(pageNode);
    pageDialogNode->MountToParent(pageNode);
    navDialogNode->MountToParent(navigationNode);
    columnNode->MountToParent(navDialogNode);
    DialogManager dialogManager;
    auto ret = dialogManager.GetEmbeddedOverlayWithNode(pageDialogNode);
    EXPECT_EQ(ret, nullptr);
    ret = dialogManager.GetEmbeddedOverlayWithNode(navDialogNode);
    EXPECT_EQ(ret, nullptr);
    dialogManager.GetDialogNodeByContentNode(columnNode);
}

/**
 * @tc.name: DialogManagerTest004
 * @tc.desc: Test GetMainPipelineContext
 * @tc.type: FUNC
 */
HWTEST_F(DialogManagerTestNg, DialogManagerTest004, TestSize.Level1)
{
    auto context = DialogManager::GetMainPipelineContext(nullptr);
    EXPECT_EQ(context, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);
    node->instanceId_ = 999;
    context = DialogManager::GetMainPipelineContext(node);
    EXPECT_EQ(context, nullptr);
    auto container = Container::Current();
    node->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    context = DialogManager::GetMainPipelineContext(node);
    ASSERT_NE(context, nullptr);
}
} // namespace OHOS::Ace::NG
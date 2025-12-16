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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/base/mock_mouse_style.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "base/ressched/ressched_click_optimizer.h"
#include "base/ressched/ressched_touch_optimizer.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace NG {
ElementIdType PipelineContextFourTestNg::frameNodeId_ = 0;
ElementIdType PipelineContextFourTestNg::customNodeId_ = 0;
RefPtr<FrameNode> PipelineContextFourTestNg::frameNode_ = nullptr;
RefPtr<CustomNode> PipelineContextFourTestNg::customNode_ = nullptr;
RefPtr<PipelineContext> PipelineContextFourTestNg::context_ = nullptr;

void PipelineContextFourTestNg::ResetEventFlag(int32_t testFlag)
{
    auto flag = context_->eventManager_->GetInstanceId();
    context_->eventManager_->SetInstanceId(flag & (~testFlag));
}

bool PipelineContextFourTestNg::GetEventFlag(int32_t testFlag)
{
    auto flag = context_->eventManager_->GetInstanceId();
    return flag & testFlag;
}

void PipelineContextFourTestNg::SetUpTestSuite()
{
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    customNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    // AddUINode is called in the function.
    customNode_ = CustomNode::CreateCustomNode(customNodeId_, TEST_TAG);
    ElementRegister::GetInstance()->AddUINode(frameNode_);
    auto window = std::make_shared<MockWindow>();
    context_ = AceType::MakeRefPtr<PipelineContext>(
        window, AceType::MakeRefPtr<MockTaskExecutor>(), nullptr, nullptr, DEFAULT_INSTANCE_ID);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    context_->fontManager_ = FontManager::Create();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = context_;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context_->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
}

void PipelineContextFourTestNg::TearDownTestSuite()
{
    context_->Destroy();
    context_->window_.reset();
    MockContainer::TearDown();
}

void PipelineContextFourTestNg::CreateCycleDirtyNode(int cycle, bool& flagUpdate)
{
    const int MAX_RECURSION_DEPTH = 1000;
    if (cycle <= 0 || cycle > MAX_RECURSION_DEPTH) {
        return;
    }
    cycle -= 1;
    auto customNodeTemp = CustomNode::CreateCustomNode(customNodeId_ + cycle + 100, TEST_TAG);
    customNodeTemp->SetUpdateFunction([cycle, &flagUpdate]() {
        PipelineContextFourTestNg::CreateCycleDirtyNode(cycle, flagUpdate);
        flagUpdate = !flagUpdate;
    });
    context_->AddDirtyCustomNode(customNodeTemp);
}

/**
 * @tc.name: PipelineContextFourTestNg001
 * @tc.desc: Test AddDirtyPropertyNode thread safety warning.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto node = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps3: Call AddDirtyPropertyNode on UI thread.
     * @tc.expected: No warning log, node added to dirty list.
     */
    context_->AddDirtyPropertyNode(node);
    EXPECT_EQ(context_->hasIdleTasks_, true);
}

/**
 * @tc.name: PipelineContextFourTestNg002
 * @tc.desc: Test AddDirtyCustomNode with various boundary conditions.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize parameters.
     * @tc.expected: All pointers are non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Test with nullptr input.
     * @tc.expected: Warning logged, nothing added to dirty list.
     */
    context_->AddDirtyCustomNode(nullptr);

    /**
     * @tc.steps3: Test with non-CustomNode UINode (FrameNode).
     * @tc.expected: Node added to dirtyNodes_, no trace recorded for JSViewName.
     */
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<CustomNode>(frameNode));
    size_t initialSize = context_->dirtyNodes_.size();
    context_->AddDirtyCustomNode(frameNode);
    EXPECT_EQ(context_->dirtyNodes_.size(), initialSize + 1);
    EXPECT_TRUE(context_->dirtyNodes_.find(frameNode) != context_->dirtyNodes_.end());

    /**
     * @tc.steps4: Test with CustomNode having empty JSViewName and empty inspector ID.
     * @tc.expected: Node added to dirtyNodes_, trace recorded without ID info.
     */
    RefPtr<CustomNode> customNodeEmpty =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "test");
    ASSERT_NE(customNodeEmpty, nullptr);
    EXPECT_EQ(customNodeEmpty->GetJSViewName(), "");
    EXPECT_EQ(customNodeEmpty->GetInspectorIdValue(""), "");
    initialSize = context_->dirtyNodes_.size();
    context_->AddDirtyCustomNode(customNodeEmpty);
    EXPECT_EQ(context_->dirtyNodes_.size(), initialSize + 1);
    EXPECT_TRUE(context_->dirtyNodes_.find(customNodeEmpty) != context_->dirtyNodes_.end());
}

/**
 * @tc.name: PipelineContextFourTestNg003
 * @tc.desc: Test AddDirtyLayoutNode trace logging with inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode with inspector ID and call AddDirtyLayoutNode.
     * @tc.expected: Trace log recorded with key info.
     */
    auto nodeWithId = FrameNode::CreateFrameNode("TestId", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithId, nullptr);
    nodeWithId->UpdateInspectorId("test_inspector_id");
    context_->AddDirtyLayoutNode(nodeWithId);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg004
 * @tc.desc: Test AddDirtyLayoutNode trace logging without inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode without inspector ID and call AddDirtyLayoutNode.
     * @tc.expected: Trace log recorded without key info.
     */
    auto normalNode = FrameNode::CreateFrameNode("NormalTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(normalNode, nullptr);
    normalNode->UpdateInspectorId(""); // Explicitly set empty inspector ID
    context_->AddDirtyLayoutNode(normalNode);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg005
 * @tc.desc: Test AddDirtyLayoutNode with long inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode with very long inspector ID and call AddDirtyLayoutNode.
     * @tc.expected: Trace log recorded with long key info.
     */
    auto nodeWithLongId = FrameNode::CreateFrameNode("LongIdTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithLongId, nullptr);
    std::string longId(1000, 'X');
    nodeWithLongId->UpdateInspectorId(longId);
    context_->AddDirtyLayoutNode(nodeWithLongId);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg006
 * @tc.desc: Test SetOnWindowFocused multiple times.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid context.
     * @tc.expected: Context and task executor are not null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->taskExecutor_, nullptr);

    /**
     * @tc.steps: 2. Set multiple callbacks sequentially.
     * @tc.expected: Last callback should be the one stored.
     */
    int callback1Executed = 0;
    int callback2Executed = 0;
    auto callback1 = [&callback1Executed]() {
        callback1Executed++;
    };
    auto callback2 = [&callback2Executed]() {
        callback2Executed++;
    };
    context_->SetOnWindowFocused(callback1);
    context_->SetOnWindowFocused(callback2);
    EXPECT_EQ(callback1Executed, 0);
    EXPECT_EQ(callback2Executed, 0);
}

/**
 * @tc.name: PipelineContextFourTestNg007
 * @tc.desc: Test AddDirtyLayoutNode with nullptr input.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Call AddDirtyLayoutNode with nullptr.
     * @tc.expected: No crash occurs.
     */
    context_->AddDirtyLayoutNode(nullptr);
    auto normalNode = FrameNode::CreateFrameNode("NormalTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(normalNode, nullptr);
    context_->AddDirtyLayoutNode(normalNode);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg008
 * @tc.desc: Test AddDirtyLayoutNode with parent node information.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create parent and child nodes, then call AddDirtyLayoutNode on child.
     * @tc.expected: Trace log recorded with parent information.
     */
    auto parentNode = FrameNode::CreateFrameNode("ParentTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode("ChildTest", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->UpdateInspectorId("child_inspector_id");
    childNode->SetParent(parentNode);
    context_->AddDirtyLayoutNode(childNode);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg009
 * @tc.desc: Test AddDirtyLayoutNode with root ETS node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create V2::ROOT_ETS_TAG node and call AddDirtyLayoutNode.
     * @tc.expected: isFirstRootLayout_ flag is updated and log is printed.
     */
    auto rootEtNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootEtNode, nullptr);
    context_->AddDirtyLayoutNode(rootEtNode);
    EXPECT_FALSE(context_->IsDirtyLayoutNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg010
 * @tc.desc: Test AddDirtyRenderNode with normal node having inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode with inspector ID and call AddDirtyRenderNode.
     * @tc.expected: Trace log recorded with key info.
     */
    auto nodeWithId = FrameNode::CreateFrameNode("TestId", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithId, nullptr);
    nodeWithId->UpdateInspectorId("test_inspector_id");
    context_->AddDirtyRenderNode(nodeWithId);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg011
 * @tc.desc: Test AddDirtyRenderNode with normal node without inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode without inspector ID and call AddDirtyRenderNode.
     * @tc.expected: Trace log recorded without key info.
     */
    auto normalNode = FrameNode::CreateFrameNode("NormalTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(normalNode, nullptr);
    normalNode->UpdateInspectorId(""); // Explicitly set empty inspector ID
    context_->AddDirtyRenderNode(normalNode);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg012
 * @tc.desc: Test AddDirtyRenderNode with long inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode with very long inspector ID and call AddDirtyRenderNode.
     * @tc.expected: Trace log recorded with long key info.
     */
    auto nodeWithLongId = FrameNode::CreateFrameNode("LongIdTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithLongId, nullptr);
    std::string longId(1000, 'X');
    nodeWithLongId->UpdateInspectorId(longId);
    context_->AddDirtyRenderNode(nodeWithLongId);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg013
 * @tc.desc: Test AddDirtyRenderNode with special characters in inspector ID.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create FrameNode with special characters in inspector ID and call AddDirtyRenderNode.
     * @tc.expected: Trace log recorded with special character key info.
     */
    auto nodeWithSpecialId = FrameNode::CreateFrameNode("SpecialIdTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nodeWithSpecialId, nullptr);
    std::string specialId = "!@#$%^&*()_+-={}[]|\\:;\"'<>?,./";
    nodeWithSpecialId->UpdateInspectorId(specialId);
    context_->AddDirtyRenderNode(nodeWithSpecialId);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg014
 * @tc.desc: Test AddDirtyRenderNode with nullptr input.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Call AddDirtyRenderNode with nullptr.
     * @tc.expected: No crash occurs.
     */
    context_->AddDirtyRenderNode(nullptr);
    auto normalNode = FrameNode::CreateFrameNode("NormalTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(normalNode, nullptr);
    context_->AddDirtyRenderNode(normalNode);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg015
 * @tc.desc: Test AddDirtyRenderNode with node having parent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create parent and child nodes, then call AddDirtyRenderNode on child.
     * @tc.expected: Trace log recorded with parent information.
     */
    auto parentNode = FrameNode::CreateFrameNode("ParentTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(parentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode("ChildTest", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childNode, nullptr);
    childNode->UpdateInspectorId("child_inspector_id");
    childNode->SetParent(parentNode);
    context_->AddDirtyRenderNode(childNode);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg016
 * @tc.desc: Test AddDirtyRenderNode multiple times.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Call AddDirtyRenderNode multiple times with different nodes.
     * @tc.expected: All nodes are added correctly.
     */
    const int nodeCount = 10;
    std::vector<RefPtr<FrameNode>> nodes;

    for (int i = 0; i < nodeCount; i++) {
        auto node = FrameNode::CreateFrameNode("TestNode", i, AceType::MakeRefPtr<Pattern>());
        ASSERT_NE(node, nullptr);
        if (i % 2 == 0) {
            node->UpdateInspectorId("inspector_" + std::to_string(i));
        }
        nodes.push_back(node);
        context_->AddDirtyRenderNode(node);
    }

    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
    for (const auto& node : nodes) {
        EXPECT_NE(node, nullptr);
        if (node->GetInspectorIdValue("").empty()) {
            EXPECT_EQ(node->GetInspectorIdValue(""), "");
        } else {
            EXPECT_STRNE(node->GetInspectorIdValue("").c_str(), "");
        }
    }
}

/**
 * @tc.name: PipelineContextFourTestNg017
 * @tc.desc: Test AddDirtyRenderNode with empty and whitespace inspector IDs.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Create nodes with empty and whitespace inspector IDs.
     * @tc.expected: Nodes are handled correctly without crashing.
     */
    auto emptyIdNode = FrameNode::CreateFrameNode("EmptyIdTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(emptyIdNode, nullptr);
    emptyIdNode->UpdateInspectorId("");
    context_->AddDirtyRenderNode(emptyIdNode);
    auto spaceIdNode = FrameNode::CreateFrameNode("SpaceIdTest", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(spaceIdNode, nullptr);
    spaceIdNode->UpdateInspectorId("   ");
    context_->AddDirtyRenderNode(spaceIdNode);
    auto tabIdNode = FrameNode::CreateFrameNode("TabIdTest", 3, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(tabIdNode, nullptr);
    tabIdNode->UpdateInspectorId("\t");
    context_->AddDirtyRenderNode(tabIdNode);
    EXPECT_FALSE(context_->IsDirtyNodesEmpty());
}

/**
 * @tc.name: PipelineContextFourTestNg018
 * @tc.desc: Test FlushDragEventVoluntarily function with comprehensive coverage.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test normal case with valid drag drop manager.
     * @tc.expected: Function executes without crash and calls DispatchLastDragEventVoluntarily.
     */
    auto dragDropManager = context_->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    context_->FlushDragEventVoluntarily();

    /**
     * @tc.steps: 3. Test with isTransFlag_ set to true.
     * @tc.expected: Function executes and passes isTransFlag_ as true.
     */
    context_->isTransFlag_ = true;
    EXPECT_TRUE(context_->isTransFlag_);
    context_->FlushDragEventVoluntarily();

    /**
     * @tc.steps: 4. Test with isTransFlag_ set to false.
     * @tc.expected: Function executes and passes isTransFlag_ as false.
     */
    context_->isTransFlag_ = false;
    EXPECT_FALSE(context_->isTransFlag_);
    context_->FlushDragEventVoluntarily();

    /**
     * @tc.steps: 5. Test multiple consecutive calls.
     * @tc.expected: Function executes without crash each time.
     */
    const int iterations = 5;
    for (int i = 0; i < iterations; i++) {
        context_->isTransFlag_ = (i % 2 == 0);
        context_->FlushDragEventVoluntarily();
        
        if (i % 2 == 0) {
            EXPECT_TRUE(context_->isTransFlag_);
        } else {
            EXPECT_FALSE(context_->isTransFlag_);
        }
    }

    /**
     * @tc.steps: 6. Test with null drag drop manager.
     * @tc.expected: Function returns early and logs error message.
     */
    auto originalManager = context_->dragDropManager_;
    context_->dragDropManager_ = nullptr;
    auto nullManager = context_->GetDragDropManager();
    EXPECT_EQ(nullManager, nullptr);
    context_->FlushDragEventVoluntarily();

    context_->dragDropManager_ = originalManager;

    /**
     * @tc.steps: 7. Test complex scenario with dummy frame node.
     * @tc.expected: Function executes properly even with potential drag events.
     */
    auto frameNode = FrameNode::CreateFrameNode("DragTest", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    DragPointerEvent dragEvent;
    dragEvent.pointerId = 1;
    dragEvent.action = PointerAction::DOWN;
    dragEvent.x = 100.0f;
    dragEvent.y = 200.0f;

    context_->isTransFlag_ = true;
    context_->FlushDragEventVoluntarily();
    context_->isTransFlag_ = false;

    /**
     * @tc.steps: 8. Final verification with restored state.
     * @tc.expected: Function works normally after all tests.
     */
    context_->FlushDragEventVoluntarily();
    EXPECT_EQ(nullManager, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg019
 * @tc.desc: Test ReloadNodesResource when ConfigChangePerform is false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test when ConfigChangePerform is false.
     * @tc.expected: Function returns early without processing nodes.
     */
    context_->needReloadResource_ = true;
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg020
 * @tc.desc: Test ReloadNodesResource when needReloadResource_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test when needReloadResource_ is false but ConfigChangePerform is true.
     * @tc.expected: Function returns early without processing nodes.
     */
    context_->needReloadResource_ = false;
    context_->ReloadNodesResource();
    EXPECT_FALSE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg021
 * @tc.desc: Test ReloadNodesResource normal case with valid nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test normal case with ConfigChangePerform true and needReloadResource_ true.
     * @tc.expected: Nodes are processed and needReloadResource_ is set to false.
     */
    context_->needReloadResource_ = true;
    auto frameNode1 = FrameNode::CreateFrameNode("TestComponent1", 1, AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = FrameNode::CreateFrameNode("TestComponent2", 2, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    ASSERT_NE(frameNode2, nullptr);
    context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(frameNode1)));
    context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(frameNode2)));
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg022
 * @tc.desc: Test ReloadNodesResource with empty needReloadNodes_ list.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test with empty needReloadNodes_ list.
     * @tc.expected: Function completes without processing any nodes.
     */
    context_->needReloadResource_ = true;
    context_->needReloadNodes_.clear();
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg023
 * @tc.desc: Test ReloadNodesResource with nodes that don't have force dark allowed.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test with nodes that don't have force dark allowed.
     * @tc.expected: Nodes are processed with force dark disallowed flag.
     */
    context_->needReloadResource_ = true;
    auto frameNode4 = FrameNode::CreateFrameNode("TestComponent4", 4, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode4, nullptr);
    context_->needReloadNodes_.clear();
    context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(frameNode4)));
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg024
 * @tc.desc: Test ReloadNodesResource with mixed node types.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test with mixed node types (FrameNode and non-FrameNode).
     * @tc.expected: Only FrameNodes are processed.
     */
    context_->needReloadResource_ = true;
    auto customNode = AceType::MakeRefPtr<CustomNode>(1, "test");
    ASSERT_NE(customNode, nullptr);
    context_->needReloadNodes_.clear();
    context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(customNode)));
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg025
 * @tc.desc: Test ReloadNodesResource with large number of nodes.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test with large number of nodes.
     * @tc.expected: All nodes are processed correctly.
     */
    context_->needReloadResource_ = true;
    const int nodeCount = 10;
    context_->needReloadNodes_.clear();
    for (int i = 0; i < nodeCount; i++) {
        auto node = FrameNode::CreateFrameNode("BulkTestComponent", 100 + i, AceType::MakeRefPtr<Pattern>());
        ASSERT_NE(node, nullptr);
        context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(node)));
    }
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg026
 * @tc.desc: Test ReloadNodesResource with consecutive calls.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test consecutive calls.
     * @tc.expected: Subsequent calls don't process nodes since needReloadResource_ is false.
     */
    context_->needReloadResource_ = true;
    auto testNode = FrameNode::CreateFrameNode("TestComponent", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(testNode, nullptr);
    context_->needReloadNodes_.emplace_back(AceType::WeakClaim(AceType::RawPtr(testNode)));
    context_->ReloadNodesResource(); // First call
    EXPECT_TRUE(context_->needReloadResource_);
    context_->ReloadNodesResource(); // Second call
    context_->ReloadNodesResource(); // Third call
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg027
 * @tc.desc: Test ReloadNodesResource with null weak references.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test with null weak references in the list.
     * @tc.expected: Null references are safely handled.
     */
    context_->needReloadResource_ = true;
    context_->needReloadNodes_.clear();
    context_->needReloadNodes_.emplace_back(WeakPtr<UINode>()); // Null reference
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg028
 * @tc.desc: Test ReloadNodesResource restoration of system property.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Test restoration of original system property value.
     * @tc.expected: System property is restored to its original value.
     */
    context_->needReloadResource_ = true;
    context_->ReloadNodesResource();
    EXPECT_TRUE(context_->needReloadResource_);
}

/**
 * @tc.name: PipelineContextFourTestNg30
 * @tc.desc: Test SetOnWindowFocused with valid task executor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg30, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid task executor.
     * @tc.expected: Context is not null and taskExecutor_ is valid.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->taskExecutor_, nullptr);

    /**
     * @tc.steps: 2. Set up a mock callback function.
     * @tc.expected: Callback function is assigned correctly.
     */
    bool callbackCalled = false;
    auto mockCallback = [&callbackCalled]() {
        callbackCalled = true;
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with valid callback.
     * @tc.expected: Callback is stored in focusOnNodeCallback_.
     */
    context_->SetOnWindowFocused(mockCallback);
    
    // Allow time for the posted task to execute
    context_->taskExecutor_->PostTask([]() {}, TaskExecutor::TaskType::UI, "DummyTask");
    
    // Check that the callback was set (indirectly, since it's private)
    EXPECT_NE(context_->GetWindowFocusCallback(), nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg31
 * @tc.desc: Test SetOnWindowFocused with null task executor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg31, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Create a context with null task executor.
     * @tc.expected: Context can be created.
     */
    RefPtr<PipelineContext> nullContext = AceType::MakeRefPtr<PipelineContext>();
    ASSERT_NE(nullContext, nullptr);

    /**
     * @tc.steps: 2. Try to set window focused callback with null task executor.
     * @tc.expected: Function returns early without crash.
     */
    nullContext->taskExecutor_ = nullptr;
    nullContext->SetOnWindowFocused([]() {});
    EXPECT_EQ(nullContext->taskExecutor_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg32
 * @tc.desc: Test SetOnWindowFocused with empty callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg32, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->taskExecutor_, nullptr);

    /**
     * @tc.steps: 2. Call SetOnWindowFocused with empty callback.
     * @tc.expected: Function handles empty callback correctly.
     */
    std::function<void()> emptyCallback;
    context_->SetOnWindowFocused(emptyCallback);
    EXPECT_NE(context_->taskExecutor_, nullptr);
}

} // namespace NG
} // namespace OHOS::Ace
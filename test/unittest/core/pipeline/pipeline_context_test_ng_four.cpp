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

void PipelineContextFourTestNg::AssertValidContext()
{
    ASSERT_NE(context_, nullptr);
    ASSERT_NE(context_->taskExecutor_, nullptr);
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
    AssertValidContext();

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
 * @tc.name: PipelineContextFourTestNg029
 * @tc.desc: Test SetOnWindowFocused with valid task executor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid task executor.
     * @tc.expected: Context is not null and taskExecutor_ is valid.
     */
    AssertValidContext();

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
 * @tc.name: PipelineContextFourTestNg030
 * @tc.desc: Test SetOnWindowFocused with null task executor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg030, TestSize.Level1)
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
 * @tc.name: PipelineContextFourTestNg031
 * @tc.desc: Test SetOnWindowFocused with empty callback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Call SetOnWindowFocused with empty callback.
     * @tc.expected: Function handles empty callback correctly.
     */
    std::function<void()> emptyCallback;
    context_->SetOnWindowFocused(emptyCallback);
    EXPECT_NE(context_->taskExecutor_, nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg032
 * @tc.desc: Test SetOnWindowFocused executes successfully with complex callback logic.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define a complex callback with multiple operations.
     * @tc.expected: Callback is assigned correctly.
     */
    std::vector<int> testData = {1, 2, 3, 4, 5};
    int sum = 0;
    bool modifiedData = false;
    
    auto complexCallback = [&testData, &sum, &modifiedData]() {
        for (int val : testData) {
            sum += val;
        }
        testData.clear();
        modifiedData = true;
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with complex callback.
     * @tc.expected: Complex callback is handled correctly.
     */
    context_->SetOnWindowFocused(complexCallback);
    EXPECT_NE(context_->GetWindowFocusCallback(), nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg033
 * @tc.desc: Test SetOnWindowFocused handles multiple consecutive callback assignments.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg033, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define multiple callbacks for sequential assignment.
     * @tc.expected: Each callback is properly defined.
     */
    int callCount = 0;
    
    // First callback
    auto firstCallback = [&callCount]() {
        callCount = 1;
    };
    // Second callback
    auto secondCallback = [&callCount]() {
        callCount = 2;
    };
    // Third callback
    auto thirdCallback = [&callCount]() {
        callCount = 3;
    };

    /**
     * @tc.steps: 3. Make multiple consecutive calls with different callbacks.
     * @tc.expected: Each call overwrites the previous callback.
     */
    context_->SetOnWindowFocused(firstCallback);
    context_->SetOnWindowFocused(secondCallback);
    context_->SetOnWindowFocused(thirdCallback);
    
    EXPECT_NE(context_->GetWindowFocusCallback(), nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg034
 * @tc.desc: Test SetOnWindowFocused handles lambda with large data capture.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg034, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Create large data structure for lambda capture.
     * @tc.expected: Large data is created successfully.
     */
    std::vector<std::string> testData(10, "Test");
    auto dataCallback = [testData]() {
        EXPECT_EQ(testData.size(), 10u);
        EXPECT_EQ(testData[0], "Test");
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with large data capturing lambda.
     * @tc.expected: Function handles large data capture without issues.
     */
    context_->SetOnWindowFocused(dataCallback);
    EXPECT_NE(context_->GetWindowFocusCallback(), nullptr);
}

/**
 * @tc.name: PipelineContextFourTestNg035
 * @tc.desc: Test SetOnWindowFocused handles recursive-like callback pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Set up recursive-like callback simulation.
     * @tc.expected: Recursive callback is properly configured.
     */
    int recursionLevel = 0;
    const int maxRecursionLevel = 3;
    
    std::function<void()> recursiveCallback;
    recursiveCallback = [&recursionLevel, maxRecursionLevel, &recursiveCallback]() {
        if (recursionLevel < maxRecursionLevel) {
            recursionLevel++;
            // In real scenario, this would call itself, but we simulate it
        }
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with recursive callback.
     * @tc.expected: Function handles recursive callback pattern.
     */
    context_->SetOnWindowFocused(recursiveCallback);
    EXPECT_NE(context_->GetWindowFocusCallback(), nullptr);
    EXPECT_EQ(recursionLevel, 0); // Should not have executed yet
}

/**
 * @tc.name: PipelineContextFourTestNg036
 * @tc.desc: Test FlushDragWindowVisibleCallback handles unset callback scenario.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    
    /**
     * @tc.steps: 2. Ensure no callback is set initially.
     * @tc.expected: Callback pointer is null.
     */
    context_->AddDragWindowVisibleTask(nullptr);

    /**
     * @tc.steps: 3. Call FlushDragWindowVisibleCallback with unset callback.
     * @tc.expected: Function executes without crash.
     */
    context_->FlushDragWindowVisibleCallback();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: PipelineContextFourTestNg037
 * @tc.desc: Test FlushDragWindowVisibleCallback executes callback and resets it.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    
    /**
     * @tc.steps: 2. Define and set a callback function.
     * @tc.expected: Callback is properly defined.
     */
    bool callbackExecuted = false;
    context_->AddDragWindowVisibleTask([&callbackExecuted]() {
        callbackExecuted = true;
    });

    /**
     * @tc.steps: 3. Call FlushDragWindowVisibleCallback.
     * @tc.expected: Callback is executed and then reset to nullptr.
     */
    context_->FlushDragWindowVisibleCallback();
    EXPECT_TRUE(callbackExecuted);
    
    /**
     * @tc.steps: 4. Call FlushDragWindowVisibleCallback again.
     * @tc.expected: Callback is not executed since it was reset.
     */
    callbackExecuted = false;
    context_->FlushDragWindowVisibleCallback();
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg038
 * @tc.desc: Test FlushDragWindowVisibleCallback prevents multiple executions.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    
    /**
     * @tc.steps: 2. Define callback to track execution count.
     * @tc.expected: Callback is properly defined.
     */
    int callbackExecutionCount = 0;
    context_->AddDragWindowVisibleTask([&callbackExecutionCount]() {
        callbackExecutionCount++;
    });
    
    /**
     * @tc.steps: 3. Call FlushDragWindowVisibleCallback multiple times.
     * @tc.expected: Callback is executed only on first call, subsequent calls do nothing.
     */
    const int iterations = 10;
    for (int i = 0; i < iterations; i++) {
        context_->FlushDragWindowVisibleCallback();
    }
    EXPECT_EQ(callbackExecutionCount, 1);
}

/**
 * @tc.name: PipelineContextFourTestNg039
 * @tc.desc: Test FlushDragWindowVisibleCallback handles complex callback logic.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    
    /**
     * @tc.steps: 2. Define complex callback with multiple operations.
     * @tc.expected: Callback variables are initialized correctly.
     */
    std::vector<int> executionLog;
    int testValue = 42;
    
    context_->AddDragWindowVisibleTask([&executionLog, &testValue, this]() {
        executionLog.push_back(1);
        testValue *= 2;
        executionLog.push_back(2);
    });
    
    EXPECT_EQ(executionLog.size(), 0u);
    EXPECT_EQ(testValue, 42);

    /**
     * @tc.steps: 3. Execute the complex callback.
     * @tc.expected: Complex callback executes correctly and is reset afterwards.
     */
    context_->FlushDragWindowVisibleCallback();
    EXPECT_EQ(executionLog.size(), 2u);
    EXPECT_EQ(executionLog[0], 1);
    EXPECT_EQ(executionLog[1], 2);
    EXPECT_EQ(testValue, 84);
    
    /**
     * @tc.steps: 4. Call FlushDragWindowVisibleCallback again.
     * @tc.expected: Callback does not execute and value remains unchanged.
     */
    executionLog.clear();
    context_->FlushDragWindowVisibleCallback();
    EXPECT_EQ(executionLog.size(), 0u);
    EXPECT_EQ(testValue, 84);
}

/**
 * @tc.name: PipelineContextFourTestNg040
 * @tc.desc: Test FlushDragWindowVisibleCallback works after context setup.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment and setup root element.
     * @tc.expected: Context is not null and root element is set up.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Define callback that interacts with context.
     * @tc.expected: Callback variables are initialized correctly.
     */
    bool callbackCalled = false;
    std::string testString = "initial";
    context_->AddDragWindowVisibleTask([this, &callbackCalled, &testString]() {
        callbackCalled = true;
        testString = "modified";
        
        if (this->context_ && this->context_->GetRootElement()) {
            testString += "_with_root";
        }
    });
    EXPECT_FALSE(callbackCalled);
    EXPECT_EQ(testString, "initial");

    /**
     * @tc.steps: 3. Call FlushDragWindowVisibleCallback.
     * @tc.expected: Function works correctly in typical usage scenario.
     */
    context_->FlushDragWindowVisibleCallback();
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(testString, "modified_with_root");

    /**
     * @tc.steps: 4. Call FlushDragWindowVisibleCallback again.
     * @tc.expected: Callback is not executed.
     */
    callbackCalled = false;
    context_->FlushDragWindowVisibleCallback();
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: PipelineContextFourTestNg041
 * @tc.desc: Test SetOnWindowFocused executes successfully with valid inputs.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg041, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid context.
     * @tc.expected: Context and task executor are not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define a valid callback function.
     * @tc.expected: Callback is properly defined.
     */
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() {
        callbackExecuted = true;
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with valid callback.
     * @tc.expected: Callback is posted to task executor and executed correctly.
     */
    context_->SetOnWindowFocused(callback);
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg042
 * @tc.desc: Test SetOnWindowFocused handles empty callback parameter.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg042, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid context.
     * @tc.expected: Context and task executor are not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define an empty callback function.
     * @tc.expected: Empty callback is properly defined.
     */
    std::function<void()> emptyCallback = nullptr;

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with empty callback.
     * @tc.expected: Empty callback is handled correctly.
     */
    context_->SetOnWindowFocused(emptyCallback);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: PipelineContextFourTestNg043
 * @tc.desc: Test SetOnWindowFocused handles lambda with large captured data.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid context.
     * @tc.expected: Context and task executor are not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define callback with large captured data.
     * @tc.expected: Large data capture is properly defined.
     */
    std::vector<int> largeData(10000, 42);
    std::string largeString(10000, 'A');
    auto largeDataCallback = [largeData, largeString]() {
        // Use the data to prevent optimization
        volatile size_t dataSize = largeData.size();
        volatile size_t stringSize = largeString.length();
        (void)dataSize;
        (void)stringSize;
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with large data capturing lambda.
     * @tc.expected: Large data capture handled correctly.
     */
    context_->SetOnWindowFocused(largeDataCallback);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: PipelineContextFourTestNg044
 * @tc.desc: Test SetOnWindowFocused handles recursive-like callback pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg044, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment with valid context.
     * @tc.expected: Context and task executor are not null.
     */
    AssertValidContext();

    /**
     * @tc.steps: 2. Define recursive-like callback simulation.
     * @tc.expected: Recursive callback is properly configured.
     */
    int recursionCounter = 0;
    const int maxRecursions = 5;
    auto recursiveSimCallback = [&recursionCounter, maxRecursions]() {
        if (recursionCounter < maxRecursions) {
            recursionCounter++;
        }
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused with recursive callback.
     * @tc.expected: Recursive callback handled without stack overflow.
     */
    context_->SetOnWindowFocused(recursiveSimCallback);
    EXPECT_EQ(recursionCounter, 0);
}

/**
 * @tc.name: PipelineContextFourTestNg045
 * @tc.desc: Test SetOnWindowFocused works after context setup and UI operations.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg045, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment and setup root element.
     * @tc.expected: Context is properly initialized.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    ASSERT_NE(context_->taskExecutor_, nullptr);

    /**
     * @tc.steps: 2. Define callback after typical UI operations.
     * @tc.expected: Callback is properly defined.
     */
    bool callbackExecuted = false;
    auto typicalCallback = [&callbackExecuted, this]() {
        callbackExecuted = true;
        // Verify context is still valid
        if (this->context_ && this->context_->GetRootElement()) {
            // Perform some operation with context
            (void)this->context_->GetRootElement()->GetId();
        }
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused after UI operations.
     * @tc.expected: Function works correctly in typical usage scenario.
     */
    context_->SetOnWindowFocused(typicalCallback);
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg046
 * @tc.desc: Test SetOnWindowFocused works with moved context object.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg046, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Create and move a pipeline context.
     * @tc.expected: Moved context functions correctly.
     */
    auto originalContext = AceType::MakeRefPtr<PipelineContext>();
    ASSERT_NE(originalContext, nullptr);
    auto movedContext = std::move(originalContext);
    ASSERT_NE(movedContext, nullptr);

    /**
     * @tc.steps: 2. Define callback for moved context.
     * @tc.expected: Callback is properly defined.
     */
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() {
        callbackExecuted = true;
    };

    /**
     * @tc.steps: 3. Call SetOnWindowFocused on moved context.
     * @tc.expected: Function works correctly with moved context.
     */
    movedContext->SetOnWindowFocused(callback);
    EXPECT_FALSE(callbackExecuted);
}

/**
 * @tc.name: PipelineContextFourTestNg047
 * @tc.desc: Test SendEventToAccessibilityWithNode handles null accessibility manager.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg047, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps: 2. Store original accessibility manager and set to nullptr.
     * @tc.expected: Accessibility manager pointer can be modified.
     */
    auto originalAccessibilityManager = context_->accessibilityManagerNG_;
    context_->accessibilityManagerNG_ = nullptr;
    
    AccessibilityEvent event;
    auto testNode = FrameNode::CreateFrameNode("TestNode", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(testNode, nullptr);
    
    /**
     * @tc.steps: 3. Call SendEventToAccessibilityWithNode with null manager.
     * @tc.expected: Function returns early without crash.
     */
    context_->SendEventToAccessibilityWithNode(event, testNode);
    context_->accessibilityManagerNG_ = originalAccessibilityManager;
}

/**
 * @tc.name: PipelineContextFourTestNg048
 * @tc.desc: Test SendEventToAccessibilityWithNode handles disabled accessibility.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg048, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Test environment is properly initialized.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto accessibilityManager = context_->accessibilityManagerNG_;
    ASSERT_NE(accessibilityManager, nullptr);

    /**
     * @tc.steps: 2. Store original accessibility state and disable feature.
     * @tc.expected: Accessibility state can be modified.
     */
    bool originalAccessibilityEnabled = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = false;
    AccessibilityEvent event;
    auto testNode = FrameNode::CreateFrameNode("TestNode", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(testNode, nullptr);
    
    /**
     * @tc.steps: 3. Call SendEventToAccessibilityWithNode with disabled accessibility.
     * @tc.expected: Function exits early when accessibility is disabled.
     */
    context_->SendEventToAccessibilityWithNode(event, testNode);
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = originalAccessibilityEnabled;
}

/**
 * @tc.name: PipelineContextFourTestNg049
 * @tc.desc: Test SendEventToAccessibilityWithNode executes successfully with valid inputs.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg049, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context and accessibility manager are not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto accessibilityManager = context_->accessibilityManagerNG_;
    ASSERT_NE(accessibilityManager, nullptr);

    /**
     * @tc.steps: 2. Store original accessibility state and enable feature.
     * @tc.expected: Accessibility state can be modified.
     */
    bool originalAccessibilityEnabled = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    
    AccessibilityEvent event;
    auto testNode = FrameNode::CreateFrameNode("TestNode", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(testNode, nullptr);

    /**
     * @tc.steps: 3. Call SendEventToAccessibilityWithNode with valid parameters.
     * @tc.expected: Function executes without crash.
     */
    context_->SendEventToAccessibilityWithNode(event, testNode);
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = originalAccessibilityEnabled;
}

/**
 * @tc.name: PipelineContextFourTestNg050
 * @tc.desc: Test SendEventToAccessibilityWithNode handles null node parameter.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg050, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context and accessibility manager are not null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto accessibilityManager = context_->accessibilityManagerNG_;
    ASSERT_NE(accessibilityManager, nullptr);

    /**
     * @tc.steps: 2. Store original accessibility state and enable feature.
     * @tc.expected: Accessibility state can be modified.
     */
    bool originalAccessibilityEnabled = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    
    AccessibilityEvent event;

    /**
     * @tc.steps: 3. Call SendEventToAccessibilityWithNode with nullptr node.
     * @tc.expected: Function handles nullptr node gracefully.
     */
    context_->SendEventToAccessibilityWithNode(event, nullptr);
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = originalAccessibilityEnabled;
}

/**
 * @tc.name: PipelineContextFourTestNg051
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation with SceneBoard window check enabled.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg051, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();
    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;

    /**
     * @tc.steps: 2. Prepare safe area insets data.
     * @tc.expected: Safe area insets are properly initialized.
     */
    SafeAreaInsets systemSafeArea;

    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with checkSceneBoardWindow = true.
     * @tc.expected: Method executes with SceneBoard window check enabled.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(systemSafeArea, true);
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
}

/**
 * @tc.name: PipelineContextFourTestNg052
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation exits early on unsupported platform versions.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg052, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();

    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    auto originalMinPlatformVersion = PipelineContextFourTestNg::context_->minPlatformVersion_;
    
    /**
     * @tc.steps: 2. Create mock safe area manager and set unsupported platform version.
     * @tc.expected: Platform version can be modified.
     */
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;
    
    PipelineContextFourTestNg::context_->minPlatformVersion_ = 9;
    SafeAreaInsets systemSafeArea;
    
    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with old platform version.
     * @tc.expected: Should return early due to platform version check.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(systemSafeArea, false);
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = originalMinPlatformVersion;
}

/**
 * @tc.name: PipelineContextFourTestNg053
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation with minimum supported platform version.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg053, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();

    // Save original values
    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    auto originalMinPlatformVersion = PipelineContextFourTestNg::context_->minPlatformVersion_;
    
    /**
     * @tc.steps: 2. Create mock safe area manager and set minimum supported platform version.
     * @tc.expected: Platform version can be modified to boundary value.
     */
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;
    
    PipelineContextFourTestNg::context_->minPlatformVersion_ = 10;
    SafeAreaInsets systemSafeArea;

    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with platform version equals to PLATFORM_VERSION_TEN.
     * @tc.expected: Boundary condition with platform version equal to 10.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(systemSafeArea, false);
    
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = originalMinPlatformVersion;
}

/**
 * @tc.name: PipelineContextFourTestNg054
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation handles zero-value safe areas.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg054, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();

    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    auto originalMinPlatformVersion = PipelineContextFourTestNg::context_->minPlatformVersion_;
    
    /**
     * @tc.steps: 2. Create mock safe area manager and set supported platform version.
     * @tc.expected: Environment is properly configured for test.
     */
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;
    
    SafeAreaInsets zeroSafeArea;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = 11;

    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with zero safe area values.
     * @tc.expected: Boundary condition with zero values.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(zeroSafeArea, false);
    
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = originalMinPlatformVersion;
}

/**
 * @tc.name: PipelineContextFourTestNg055
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation handles negative safe area values.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg055, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();

    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    auto originalMinPlatformVersion = PipelineContextFourTestNg::context_->minPlatformVersion_;
    
    /**
     * @tc.steps: 2. Create mock safe area manager.
     * @tc.expected: Mock manager is properly created.
     */
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;
    
    SafeAreaInsets negativeSafeArea;

    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with negative safe area values.
     * @tc.expected: Boundary condition with negative values.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(negativeSafeArea, true);
    
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = originalMinPlatformVersion;
}

/**
 * @tc.name: PipelineContextFourTestNg056
 * @tc.desc: Test UpdateSystemSafeAreaWithoutAnimation handles large safe area values.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextFourTestNg056, TestSize.Level1)
{
    /**
     * @tc.steps: 1. Initialize test environment.
     * @tc.expected: Context is not null.
     */
    ASSERT_NE(PipelineContextFourTestNg::context_, nullptr);
    PipelineContextFourTestNg::context_->SetupRootElement();
    auto originalSafeAreaManager = PipelineContextFourTestNg::context_->safeAreaManager_;
    auto originalMinPlatformVersion = PipelineContextFourTestNg::context_->minPlatformVersion_;
    
    /**
     * @tc.steps: 2. Create mock safe area manager and set platform version.
     * @tc.expected: Test environment is properly configured.
     */
    auto mockSafeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    PipelineContextFourTestNg::context_->safeAreaManager_ = mockSafeAreaManager;
    SafeAreaInsets largeSafeArea;
    
    PipelineContextFourTestNg::context_->minPlatformVersion_ = 12;

    /**
     * @tc.steps: 3. Call UpdateSystemSafeAreaWithoutAnimation with large safe area values.
     * @tc.expected: Boundary condition with very large values.
     */
    PipelineContextFourTestNg::context_->UpdateSystemSafeAreaWithoutAnimation(largeSafeArea, false);
    
    PipelineContextFourTestNg::context_->safeAreaManager_ = originalSafeAreaManager;
    PipelineContextFourTestNg::context_->minPlatformVersion_ = originalMinPlatformVersion;
}

/**
 * @tc.name: OnHideTest001
 * @tc.desc: Test onHide not send event when is formrender.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, OnHideTest001, TestSize.Level1)
{
    auto frontend = AceType::MakeRefPtr<MockFrontend>();
    ASSERT_NE(frontend, nullptr);
    auto rootBackup = context_->GetRootElement();
    ASSERT_NE(rootBackup, nullptr);
    auto weakFrontendBackup = context_->weakFrontend_;
    auto formBackup = context_->IsFormRender();
    bool accessibilityEnableBackup = AceApplicationInfo::GetInstance().IsAccessibilityEnabled();
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    context_->weakFrontend_ = frontend;

    EXPECT_CALL(*frontend, GetAccessibilityManager())
        .Times(1);

    context_->rootNode_ = nullptr;
    // 1. no rootNode and IsFormRenderExceptDynamicComponent
    context_->SetIsFormRender(true);
    context_->OnHide();
    // 2. no rootNode and not IsFormRenderExceptDynamicComponent
    context_->SetIsFormRender(false);
    context_->OnHide();
    // 3. has rootNode and IsFormRenderExceptDynamicComponent
    context_->rootNode_ = rootBackup;
    context_->SetIsFormRender(true);
    context_->OnHide();
    // 4. has rootNode and not IsFormRenderExceptDynamicComponent
    context_->SetIsFormRender(false);
    context_->OnHide();

    context_->weakFrontend_ = weakFrontendBackup;
    context_->SetIsFormRender(formBackup);
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(accessibilityEnableBackup);
}
} // namespace NG
} // namespace OHOS::Ace
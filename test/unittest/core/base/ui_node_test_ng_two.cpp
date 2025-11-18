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
#include <ostream>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "core/common/builder_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/unittest/core/base/ui_node_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class UINodeTestNgTwo : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void UINodeTestNgTwo::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void UINodeTestNgTwo::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetPerformanceCheckData003
 * @tc.desc: Test ui node method GetCurrentCustomNodeInfo
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, GetPerformanceCheckData003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto childTwo = FrameNode::CreateFrameNode("childTwo", childTwoId, AceType::MakeRefPtr<Pattern>(), true);
    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    childTwo->tag_ = V2::COMMON_VIEW_ETS_TAG;
    childTwo->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);
    parent->AddChild(childTwo);

    /**
     * @tc.steps: step2.  construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);

    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);

    /**
     * @tc.steps: step3. change child tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    child->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_FALSE(parent->isBuildByJS_);
}

/**
 * @tc.name: UpdateConfigurationUpdate001
 * @tc.desc: Test ui node method UpdateConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UpdateConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    parent->tag_ = V2::COMMON_VIEW_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();

    /**
     * @tc.steps: step2.  construct parameter configurationChange and call UpdateConfigurationUpdate
     * @tc.expected: cover branch needCallChildrenUpdate_ is true
     */
    ConfigurationChange configurationChange;
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_TRUE(parent->needCallChildrenUpdate_);

    /**
     * @tc.steps: step3. create child frame node and call UpdateConfigurationUpdate
     * @tc.expected: cover branch children is not empty
     */
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto childTwo = FrameNode::CreateFrameNode("childTwo", childTwoId, AceType::MakeRefPtr<Pattern>(), true);
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    childTwo->tag_ = V2::COMMON_VIEW_ETS_TAG;
    childTwo->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_TRUE(parent->needCallChildrenUpdate_);

    /**
     * @tc.steps: step4. set needCallChildrenUpdate_ and call UpdateConfigurationUpdate
     * @tc.expected: cover branch needCallChildrenUpdate_ is false
     */
    parent->SetNeedCallChildrenUpdate(false);
    parent->UINode::UpdateConfigurationUpdate(configurationChange);
    EXPECT_FALSE(parent->needCallChildrenUpdate_);
}

/**
 * @tc.name: DumpTreeById001
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, DumpTreeById001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);
    /**
     * @tc.steps: step2. call DumpTreeById
     * @tc.expected: cover branch GetDumpFile is nullptr and result is false
     */
    bool result = parent->UINode::DumpTreeById(0, "");
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. set DumpFile and call DumpTreeById
     * @tc.expected: cover branch GetDumpFile is not nullptr and result is true
     */
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));

    result = parent->UINode::DumpTreeById(0, "");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DumpTreeById002
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, DumpTreeById002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));

    /**
     * @tc.steps: step2. construt parameter and call DumpTreeById
     * @tc.expected: result is false
     */
    bool result = parent->UINode::DumpTreeById(0, "DumpTreeById002");
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. change parameter and call DumpTreeById
     * @tc.expected: result is false
     */
    result = parent->UINode::DumpTreeById(1, "");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: UINodeTestNgTwo045
 * @tc.desc: IsContextTransparent()、GetPageNodeCountAndDepth()
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call IsContextTransparent
     * @tc.expected: result is True
     */
    parent->AddChild(child);
    EXPECT_TRUE(parent->UINode::IsContextTransparent());
    int32_t count = 0;
    int32_t depth = 0;

    parent->GetPageNodeCountAndDepth(&count, &depth);
    EXPECT_EQ(parent->depth_, Infinity<int32_t>());
    EXPECT_EQ(parent->depth_, Infinity<int32_t>());

    auto child1 = FrameNode::CreateFrameNode(
        "child1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode(
        "child2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    child2->tag_ = V2::JS_VIEW_ETS_TAG;
    child1->AddChild(child2);
    child1->AddChild(ONE);
    std::list<int32_t> removedElmtId;
    parent->UINode::CollectRemovedChildren(child1->GetChildren(), removedElmtId, true);
    parent->UINode::GetFrameChildByIndexWithoutExpanded(0);
    parent->UINode::SetJSViewActive(false);
    parent->UINode::RenderCustomChild(0);
    std::vector<RefPtr<UINode>> res;
    parent->DFSAllChild(child1, res);
    EXPECT_EQ(res.size(), 2);
}

/**
 * @tc.name: UINodeTestNgTwo046
 * @tc.desc: IsContextTransparent()、GetPageNodeCountAndDepth()
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step2. call IsContextTransparent
     * @tc.expected: result is True
     */
    parent->AddChild(child);
    parent->AddChild(ONE);

    auto child1 = FrameNode::CreateFrameNode(
        "child1", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode(
        "child2", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    child2->tag_ = V2::JS_VIEW_ETS_TAG;
    child1->AddChild(child2);
    std::list<int32_t> removedElmtId;
    EXPECT_TRUE(parent->UINode::GetContextWithCheck());
    EXPECT_EQ(parent->UINode::GetFrameNodeIndex(child, true), 0);
    EXPECT_EQ(parent->UINode::GetFrameNodeIndex(child1, false), -1);
}

/**
 * @tc.name: UINodeTestNgTwo047
 * @tc.desc: Test ui node method AddChildBefore
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild,child not exsit and siblingNode exsit
     * @tc.expected: children_.size = 3
     */
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->Clean();
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->AddChild(TWO, 1, false);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode2, testNode);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step2. AddChild, both child and siblingNode not exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    const int32_t testId3 = 23;
    auto testNode3 = TestNode::CreateTestNode(testId3);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode3, testNode2);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step3. AddChild,  child  exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChild(testNode3, 1, false);
    ONE->AddChildBefore(testNode, testNode3);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo048
 * @tc.desc: Test ui node method AddChildAfter
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AddChild,child exsit
     * @tc.expected: children_.size = 3
     */
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->Clean();
    EXPECT_EQ(ONE->children_.size(), 0);
    ONE->AddChild(TWO, 1, false);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildAfter(testNode2, testNode);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step3. AddChild, both child and siblingNode not exsit
     * @tc.expected: children_.size = 3
     */
    ONE->AddChild(TWO, 1, false);
    const int32_t testId3 = 23;
    auto testNode3 = TestNode::CreateTestNode(testId3);
    ONE->AddChild(testNode, 1, false);
    ONE->AddChildBefore(testNode3, testNode2);
    EXPECT_EQ(ONE->children_.size(), 3);
    ONE->Clean();

    /**
     * @tc.steps: step2. AddChild, addModalUiextension is false and modalUiextensionCount_ > 0
     * @tc.expected: children_.size = 0
     */
    ONE->UpdateModalUiextensionCount(true);
    ONE->AddChild(TWO, 1, false, false, false);
    ONE->RemoveImmediately();
    EXPECT_EQ(ONE->children_.size(), 1);
}

/**
 * @tc.name: UINodeTestNgTwo050
 * @tc.desc: Test ui node method GetContextWithCheck
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add child and GetContextWithCheck
     * @tc.expected: ret != nullptr
     */
    ONE->AddChild(TWO, 1, false);
    PipelineContext* ret = ONE->GetContextWithCheck();
    ASSERT_TRUE(ret != nullptr);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo051
 * @tc.desc: Test ui node method CurrentFrameCount/GenerateAccessibilityId
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. add child and excute CurrentFrameCount
     * @tc.expected: count == 0
     */
    ONE->AddChild(TWO, 1, false);
    int32_t count = ONE->CurrentFrameCount();
    ASSERT_TRUE(count == 1);
    int64_t idCurrent = ONE->GenerateAccessibilityId();
    int64_t id = ONE->GenerateAccessibilityId();
    ASSERT_TRUE(id == idCurrent + 1);
    ONE->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo052
 * @tc.desc: Test ui node method of AttachContext
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a uinode
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ASSERT_NE(testNode, nullptr);
    testNode->AddChild(TWO, 1, false);
    /**
     * @tc.steps: step2. attach context
     */
    testNode->AttachContext(AceType::RawPtr(context), true);
    EXPECT_EQ(testNode->context_, AceType::RawPtr(context));
    /**
     * @tc.steps: step3. detach context
     */
    testNode->DetachContext(true);
    EXPECT_EQ(testNode->context_, nullptr);
}

/**
 * @tc.name: UINodeTestNgTwo053
 * @tc.desc: Test ui node method GetBestBreakPoint1
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetChildAtIndex and retParent nullptr  0000
     * @tc.expected: GetChildAtIndex and retParent nullptr
     */
    ZERO->parent_ = nullptr;
    RefPtr<UINode> retParent = ZERO->GetParent();
    RefPtr<UINode> retChildAtIndex = ZERO->GetChildAtIndex(-1);
    ZERO->GetBestBreakPoint(retChildAtIndex, retParent);
    EXPECT_EQ(retParent, nullptr);
    EXPECT_EQ(retChildAtIndex, nullptr);

    /**
     * @tc.steps: step2. GetChildAtIndex and retParent not nullptr 1100
     * @tc.expected: retParent2 nullptr and retChildAtIndex2 point to ZERO
     */
    ZERO->parent_ = nullptr;
    auto testNode25 = TestNode::CreateTestNode(25);
    ZERO->AddChild(testNode25, 1, false);
    RefPtr<UINode> retChildAtIndex2 = ZERO->GetChildAtIndex(0);
    RefPtr<UINode> retParent2 = ZERO;
    testNode25->GetBestBreakPoint(retChildAtIndex2, retParent2);
    EXPECT_EQ(retParent2, 0);
    EXPECT_EQ(retChildAtIndex2->GetTag(), ZERO->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step3. GetChildAtIndex and retParent not nullptr,child IsDisappearing is true 1010
     * @tc.expected: retParent3  and retChildAtIndex3 point to ZERO
     */
    ASSERT_TRUE(ZERO->children_.size() == 0);
    ZERO->parent_ = nullptr;
    ZERO->AddChild(ONE, 1, false);
    ZERO->AddDisappearingChild(ONE, 0);
    RefPtr<UINode> retChildAtIndex3 = ZERO->GetChildAtIndex(0);
    RefPtr<UINode> retParent3 = ONE->GetParent();
    ONE->GetBestBreakPoint(retChildAtIndex3, retParent3);
    EXPECT_EQ(retParent3, 1);
    EXPECT_EQ(retChildAtIndex3->GetTag(), ONE->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step4. GetChildAtIndex and retParent not nullptr, child testNode IsDisappearing is true 1110
     * @tc.expected: retParent4 point to ZERO and retChildAtIndex4 point to testNode
     */
    ZERO->parent_ = nullptr;
    auto testNode = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode, 1, false);
    testNode->AddChild(TWO, 1, false);
    ZERO->AddDisappearingChild(testNode, 0);
    RefPtr<UINode> retChildAtIndex4 = testNode->GetChildAtIndex(0);
    RefPtr<UINode> retParent4 = testNode;
    TWO->GetBestBreakPoint(retChildAtIndex4, retParent4);
    EXPECT_EQ(retParent4->GetTag(), ZERO->GetTag());
    EXPECT_EQ(retChildAtIndex4->GetTag(), testNode->GetTag());
    ZERO->Clean();

    /**
     * @tc.steps: step5. GetChildAtIndex and retParent not nullptr,all child  Disappearing  true 1011
     * @tc.expected: retParent5  and retChildAtIndex5 do not change
     */
    ZERO->parent_ = nullptr;
    auto testNode1 = TestNode::CreateTestNode(TEST_ID_ONE);
    ZERO->AddChild(testNode1, 1, false);
    testNode1->AddChild(TWO, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->AddDisappearingChild(TWO, 0);
    RefPtr<UINode> retChildAtIndex5 = testNode1->GetChildAtIndex(0);
    RefPtr<UINode> retParent5 = testNode1;
    TWO->GetBestBreakPoint(retChildAtIndex5, retParent5);
    EXPECT_EQ(retParent5->GetTag(), testNode1->GetTag());
    EXPECT_EQ(retChildAtIndex5->GetTag(), TWO->GetTag());
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo054
 * @tc.desc: Test ui node method GetBestBreakPoint2
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. GetChildAtIndex and retParent not nullptr,all child  Disappearing  true 1111
     * @tc.expected: retParent point to  testNode3 and retChildAtIndex point to  testNode4
     */
    ZERO->parent_ = nullptr;
    auto testNode3 = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode4 = TestNode::CreateTestNode(TEST_ID_TWO);
    auto testNode5 = TestNode::CreateTestNode(23);
    ZERO->AddChild(testNode3, 1, false);
    testNode3->AddChild(testNode4, 1, false);
    testNode4->AddChild(testNode5, 1, false);
    ZERO->AddDisappearingChild(testNode3, 0);
    testNode3->AddDisappearingChild(testNode4, 0);
    RefPtr<UINode> retChildAtIndex = testNode4->GetChildAtIndex(0);
    RefPtr<UINode> retParent = testNode4;
    testNode4->GetBestBreakPoint(retChildAtIndex, retParent);
    EXPECT_EQ(retParent->GetTag(), testNode3->GetTag());
    EXPECT_EQ(retChildAtIndex->GetTag(), testNode4->GetTag());
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo055
 * @tc.desc: Test ui node method RemoveFromParentCleanly
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. child isDisappearing_ is false, not in ModifyChildren
     * @tc.expected: testNode3 has been deleted
     */
    ZERO->parent_ = nullptr;
    auto testNode1 = TestNode::CreateTestNode(TEST_ID_ONE);
    auto testNode2 = TestNode::CreateTestNode(TEST_ID_TWO);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    testNode1->AddChild(testNode2, 1, false);
    testNode2->AddChild(testNode3, 1, false);
    testNode3->RemoveFromParentCleanly(testNode3, testNode2);
    EXPECT_EQ(testNode2->children_.size(), 0);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode2->AddChild(testNode3, 1, false);
    testNode4->RemoveFromParentCleanly(testNode4, testNode2);
    EXPECT_EQ(testNode2->children_.size(), 1);
    ZERO->Clean();

    /**
     * @tc.steps: step2. child isDisappearing_ is true
     * @tc.expected: child isDisappearing_ is false
     */
    ZERO->parent_ = nullptr;
    auto testNode5 = TestNode::CreateTestNode(25);
    auto testNode6 = TestNode::CreateTestNode(26);
    const RefPtr<FrameNode> testNode7 =
        FrameNode::CreateFrameNode("testNode7", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode5, 1, false);
    testNode5->AddChild(testNode6, 1, false);
    testNode6->AddChild(testNode7, 1, false);
    testNode6->AddDisappearingChild(testNode7, 0);
    testNode7->RemoveFromParentCleanly(testNode7, testNode6);
    EXPECT_EQ(testNode7->isDisappearing_, false);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo057
 * @tc.desc: Test ui node method DumpViewDataPageNodes
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a uinode and add child,skipSubAutoFillContainer is false
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(nullptr, 1, false);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    testNode1->DumpViewDataPageNodes(viewDataWrap, false);
    ZERO->Clean();

    /**
     * @tc.steps: step2. construct a uinode and add child,skipSubAutoFillContainer is true
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNodePage = FrameNode::CreateFrameNode("page", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode3->AddChild(testNode4, 1, false);
    testNode3->AddChild(nullptr, 1, false);
    testNode3->AddChild(testNodePage, 1, false);
    auto viewDataWrap2 = ViewDataWrap::CreateViewDataWrap();
    testNode3->DumpViewDataPageNodes(viewDataWrap2, true);
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode2"));
}

/**
 * @tc.name: UINodeTestNgTwo058
 * @tc.desc: Test ui node method DumpTree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with Disappearing child and OverlayNode child
     * @tc.expected: expect no exception
     */
    ZERO->parent_ = nullptr;
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 1, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    ZERO->AddChild(testNode2, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->SetOverlayNode(testNode3);
    testNode1->AddDisappearingChild(testNode4, 0);
    testNode1->DumpTree(0);
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode1"));
}

/**
 * @tc.name: UINodeTestNgTwo059
 * @tc.desc: Test ui node method DumpTreeById
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with Disappearing child
     * @tc.expected: expect no exception
     */
    ZERO->parent_ = nullptr;
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    ZERO->AddChild(testNode1, 1, false);
    ZERO->AddChild(testNode2, 1, false);
    ZERO->AddDisappearingChild(testNode1, 0);
    testNode1->AddChild(testNode3, 0);
    testNode1->AddDisappearingChild(testNode4, 0);
    testNode1->DumpTreeById(0, "3");
    testNode1->DumpTreeById(0, "4");
    ZERO->Clean();
    EXPECT_TRUE(DumpLog::GetInstance().result_.find("testNode1"));
}

/**
 * @tc.name: UINodeTestNgTwo060
 * @tc.desc: Test ui node method AdjustLayoutWrapperTree
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode with child
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    RefPtr<LayoutWrapperNode> retLayoutWrapper = testNode1->UINode::CreateLayoutWrapper(true, true);
    testNode1->UINode::AdjustLayoutWrapperTree(retLayoutWrapper, false, false);
    EXPECT_EQ(testNode1->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNgTwo061
 * @tc.desc: Test ui node method CreateExportTextureInfoIfNeeded
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FrameNode
     * @tc.expected: expect no exception
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->UINode::CreateExportTextureInfoIfNeeded();
    EXPECT_EQ(testNode1->GetExportTextureInfo() != nullptr, true);
    testNode1->UINode::CreateExportTextureInfoIfNeeded();
    EXPECT_EQ(testNode1->GetExportTextureInfo() != nullptr, true);
}

/**
 * @tc.name: UINodeTestNgTwo062
 * @tc.desc: Test ui node method SetJSViewActive
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    auto child = CustomNode::CreateCustomNode(childId, "child");
    auto childTwo = CustomNode::CreateCustomNode(childTwoId, "child_two");
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->UINode::SetJSViewActive(true, true);
    child->SetIsV2(true);
    parent->UINode::SetJSViewActive(true, true);
    EXPECT_TRUE(child->GetJsActive());
}

/**
 * @tc.name: UINodeTestNgTwo063
 * @tc.desc: Test ui node method OnRecycle/OnReuse/PaintDebugBoundaryTreeAll/IsContextTransparent
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode1->OnRecycle();
    testNode1->OnReuse();
    testNode1->PaintDebugBoundaryTreeAll(true);
    bool ret = testNode1->IsContextTransparent();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: UINodeTestNgTwo064
 * @tc.desc: Test ui node method DFSAllChild
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node without child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    std::vector<RefPtr<UINode>> ret;
    testNode1->DFSAllChild(testNode1, ret);
    EXPECT_EQ(ret.size(), 1);
    ret.clear();

    /**
     * @tc.steps: step2. create node with child
     */
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode1->DFSAllChild(testNode1, ret);
    EXPECT_EQ(ret.size(), 3);
    ret.clear();
}

/**
 * @tc.name: UINodeTestNgTwo065
 * @tc.desc: Test ui node method GetPageNodeCountAndDepth
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    int32_t* count = new int32_t(0);
    int32_t* depth = new int32_t(0);
    testNode1->GetPageNodeCountAndDepth(count, depth);
    EXPECT_EQ(*count, 4);
    delete count;
    delete depth;
}

/**
 * @tc.name: UINodeTestNgTwo066
 * @tc.desc: Test ui node method CollectRemovedChildren/UpdateNodeStatus
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);
    testNode2->SetIsRootBuilderNode(true);
    std::list<int32_t> removedElmtId;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId, true);
    EXPECT_EQ(removedElmtId.size(), 2);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId, true);
    EXPECT_EQ(removedElmtId.size(), 3);
}

/**
 * @tc.name: UINodeTestNgTwo067
 * @tc.desc: Test ui node method GetFrameChildByIndexWithoutExpanded
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode with child
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    auto testNode2 = TestNode::CreateTestNode(22);
    auto testNode3 = TestNode::CreateTestNode(23);
    auto testNode4 = TestNode::CreateTestNode(24);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    RefPtr<UINode> ret = testNode1->GetFrameChildByIndexWithoutExpanded(4);
    EXPECT_EQ(ret == nullptr, true);
}

/**
 * @tc.name: UINodeTestNgTwo068
 * @tc.desc: Test ui node method Build
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create custome node,SetIsV2 false,isLazyForEachNode true
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childTwoId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = CustomNode::CreateCustomNode(parentId, "parent");
    auto child = CustomNode::CreateCustomNode(childId, "child");
    auto childTwo = CustomNode::CreateCustomNode(childTwoId, "child_two");
    auto childThree = TestNode::CreateTestNode(24);
    ExtraInfo extraInfo;
    extraInfo.page = "1";
    childTwo->SetExtraInfo(extraInfo);
    parent->AddChild(child);
    parent->AddChild(childTwo);
    parent->AddChild(childThree);
    std::shared_ptr<std::list<ExtraInfo>> extraInfos;
    parent->UINode::Build(extraInfos);
    extraInfos = std::make_shared<std::list<ExtraInfo>>();
    parent->UINode::Build(extraInfos);
    EXPECT_EQ(parent->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNgTwo069
 * @tc.desc: Test ui node method GenerateOneDepthVisibleFrameWithTransition/GenerateOneDepthVisibleFrameWithOffset
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node,AddChild,AddDisappearingChild
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    OffsetT<float> offset;
    std::list<RefPtr<FrameNode>> visibleList;
    testNode1->GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
    testNode1->AddDisappearingChild(testNode2, 1);
    testNode1->AddDisappearingChild(testNode3, 2);
    testNode1->AddDisappearingChild(testNode4, 3);
    testNode1->AddDisappearingChild(testNode5, 4);
    testNode1->GenerateOneDepthVisibleFrameWithTransition(visibleList);
    testNode1->GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
    EXPECT_EQ(testNode1->GetChildren().size(), 3);
}

/**
 * @tc.name: UINodeTestNgTwo070
 * @tc.desc: Test ui node method TouchTest/MouseTest
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node and construct params
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    PointT<float> globalPoint;
    PointT<float> parentLocalPoint;
    PointT<float> parentRevertPoint;
    TouchRestrict touchRestrict;
    MouseTestResult onMouseResult;
    MouseTestResult onHoverResult;
    RefPtr<FrameNode> hoverNode;
    HitTestResult ret =
        testNode1->UINode::MouseTest(globalPoint, parentLocalPoint, onMouseResult, onHoverResult, hoverNode);
    EXPECT_EQ(ret == HitTestResult::BUBBLING, true);
    AxisTestResult onAxisResult;
    HitTestResult ret2 =
        testNode1->UINode::AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
    EXPECT_EQ(ret2 == HitTestResult::OUT_OF_REGION, true);
}

/**
 * @tc.name: UINodeTestNgTwo071
 * @tc.desc: Test ui node method SetAccessibilityNodeVirtual
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node and construct params
     */
    auto testNode1 = TestNode::CreateTestNode(21);
    auto child = TestNode::CreateTestNode(22);
    testNode1->SetAccessibilityNodeVirtual();
    EXPECT_EQ(testNode1->IsAccessibilityVirtualNode(), true);
    testNode1->SetAccessibilityVirtualNodeParent(child);
    auto weakResult = testNode1->GetVirtualNodeParent();
    auto result = weakResult.Upgrade();
    ASSERT_NE(result, nullptr);
}

/**
 * @tc.name: UINodeTestNgTwo072
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode node and construct params
     */
    ZERO->hostPageId_ = 0;
    ZERO->SetInDestroying();
    EXPECT_NE(ZERO->OnRemoveFromParent(false), false);
    ZERO->SetDestroying(false);
    ZERO->Clean();
}

/**
 * @tc.name: UINodeTestNgTwo073
 * @tc.desc: Test ui node method
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UINodeTestNgTwo073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), false);

    child->tag_ = V2::IMAGE_ETS_TAG;
    parent->AddChild(child);
    std::list<RefPtr<UINode>> nodes;

    /**
     * @tc.steps: step2. call GetFirstBuilderNode
     * @tc.expected: child isRootBuilderNode_ is true, nodes size is 1
     */
    child->SetIsRootBuilderNode(true);
    BuilderUtils::GetFirstBuilderNode(parent, nodes);
    EXPECT_EQ(nodes.size(), SIZE_ONE);

    child->SetIsRootBuilderNode(false);
    auto son = FrameNode::CreateFrameNode(
        "son", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), false);
    child->AddChild(son);
    son->SetIsRootBuilderNode(true);
    child->tag_ = V2::NODE_CONTAINER_ETS_TAG;
    nodes.clear();
    BuilderUtils::GetFirstBuilderNode(parent, nodes);
    EXPECT_EQ(nodes.size(), SIZE_ZERO);
    child->tag_ = V2::JS_NODE_SLOT_ETS_TAG;
    BuilderUtils::GetFirstBuilderNode(parent, nodes);
    EXPECT_EQ(nodes.size(), SIZE_ZERO);

    child->tag_ = V2::IMAGE_ETS_TAG;
    BuilderUtils::GetFirstBuilderNode(parent, nodes);
    EXPECT_EQ(nodes.size(), SIZE_ONE);
}

/**
 * @tc.name: GetPerformanceCheckData004
 * @tc.desc: Test ui node method GetPerformanceCheckData
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, GetPerformanceCheckData004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and childframe node
     */
    auto parentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childIdId2 = ElementRegister::GetInstance()->MakeUniqueId();
    auto parent = FrameNode::CreateFrameNode("parent", parentId, AceType::MakeRefPtr<Pattern>(), true);
    auto child = FrameNode::CreateFrameNode("child", childId, AceType::MakeRefPtr<Pattern>(), true);
    auto child2 = FrameNode::CreateFrameNode("child2", childIdId2, AceType::MakeRefPtr<Pattern>(), true);

    parent->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    parent->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    parent->AddChild(child);

    /**
     * @tc.steps: step2.  construct parameter performanceCheckNodeMap and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    PerformanceCheckNodeMap nodeMap;
    PerformanceCheckNode performanceCheckNode = PerformanceCheckNode();
    nodeMap.emplace(nodeId, performanceCheckNode);
    child->UINode::GetPerformanceCheckData(nodeMap);
    child2->tag_ = V2::COMMON_VIEW_ETS_TAG;
    child2->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->AddChild(child2, 1, false);
    auto childId4 = ElementRegister::GetInstance()->MakeUniqueId();
    auto child4 = FrameNode::CreateFrameNode("child4", childId4, AceType::MakeRefPtr<Pattern>(), true);
    child4->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    child4->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child->AddChild(child4, 1, false);
    // grandChildren exist
    auto childIdId3 = ElementRegister::GetInstance()->MakeUniqueId();
    auto child3 = FrameNode::CreateFrameNode("child3", childIdId3, AceType::MakeRefPtr<Pattern>(), true);
    child3->nodeInfo_ = std::make_unique<PerformanceCheckNode>();
    child2->AddChild(child3);
    child->UINode::GetPerformanceCheckData(nodeMap);

    /**
     * @tc.steps: step3. change child tag_ and call GetPerformanceCheckData
     * @tc.expected: isBuildByJS_ is false
     */
    child->tag_ = V2::JS_FOR_EACH_ETS_TAG;
    child->UINode::GetPerformanceCheckData(nodeMap);
    EXPECT_EQ(child->nodeInfo_->nodeTag, "ForEach");
}

/**
 * @tc.name: CollectCleanedChildren
 * @tc.desc: Test ui node method CollectCleanedChildren
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, CollectCleanedChildren, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API13.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);

    /**
     * @tc.steps: step2. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step3. add child
     */
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);

    /**
     * @tc.steps: step4. test CollectCleanedChildren.
     */
    testNode2->isDisappearing_ = true;
    std::list<int32_t> removedElmtId2;
    std::list<int32_t> reservedElmtIds;
    testNode1->CollectCleanedChildren(testNode1->GetChildren(), removedElmtId2, reservedElmtIds, true);
    EXPECT_EQ(removedElmtId2.size(), 4);
    testNode2->CollectCleanedChildren(testNode2->GetChildren(), removedElmtId2, reservedElmtIds, false);
    EXPECT_EQ(removedElmtId2.size(), 5);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: CollectRemovedChildren001
 * @tc.desc: Test ui node method CollectRemovedChildren
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, CollectRemovedChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API12.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step2. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step3. add child
     */
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);

    /**
     * @tc.steps: step4. test CollectRemovedChildren.
     */
    testNode2->isDisappearing_ = true;
    std::list<int32_t> removedElmtId1;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId1, true);
    EXPECT_EQ(removedElmtId1.size(), 2);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId1, true);
    EXPECT_EQ(removedElmtId1.size(), 3);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: CollectRemovedChildren002
 * @tc.desc: Test ui node method CollectRemovedChildren
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, CollectRemovedChildren002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API13.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);

    /**
     * @tc.steps: step2. create FrameNode with child
     */
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode("testNode1", 1, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode("testNode2", 2, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode("testNode3", 3, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode("testNode4", 4, AceType::MakeRefPtr<Pattern>(), true);
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode("testNode5", 5, AceType::MakeRefPtr<Pattern>(), true);

    /**
     * @tc.steps: step3. add child
     */
    testNode1->AddChild(testNode2, 1, false);
    testNode1->AddChild(testNode3, 1, false);
    testNode1->AddChild(testNode4, 1, false);
    testNode2->AddChild(testNode5, 1, false);

    /**
     * @tc.steps: step4. test CollectRemovedChildren.
     */
    testNode2->isDisappearing_ = true;
    std::list<int32_t> removedElmtId2;
    testNode1->CollectRemovedChildren(testNode1->GetChildren(), removedElmtId2, true);
    EXPECT_EQ(removedElmtId2.size(), 4);
    testNode2->CollectRemovedChildren(testNode2->GetChildren(), removedElmtId2, false);
    EXPECT_EQ(removedElmtId2.size(), 5);

    /**
     * @tc.steps: step5. revert to the origin API.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: IsAutoFillContainerNode001
 * @tc.desc: Test ui node method IsAutoFillContainerNode
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, IsAutoFillContainerNode001, TestSize.Level1)
{
    const RefPtr<FrameNode> testNode1 =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode1->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode2 =
        FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode2->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode3 =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode3->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode4 =
        FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, 4, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode4->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode5 =
        FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG, 5, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode5->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode6 =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, 6, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_TRUE(testNode6->IsAutoFillContainerNode());
    const RefPtr<FrameNode> testNode7 =
        FrameNode::CreateFrameNode("OTHER_TAG", 7, AceType::MakeRefPtr<Pattern>(), false);
    EXPECT_FALSE(testNode7->IsAutoFillContainerNode());
}

/**
 * @tc.name: AddFunc_API01
 * @tc.desc: CanAddChildWhenTopNodeIsModalUec
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, AddFunc_API01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare the environment variables for the function.
     */
    const RefPtr<FrameNode> testNode =
        FrameNode::CreateFrameNode("testNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    testNode->AddChild(TWO, 1, false);
    testNode->AddChild(THREE, 1, false);
    std::list<RefPtr<UINode>>::iterator itr = testNode->children_.end();
    testNode->CanAddChildWhenTopNodeIsModalUec(itr);

    /**
     * @tc.steps: step2. change function parameters.
     */
    itr = testNode->children_.begin();
    testNode->CanAddChildWhenTopNodeIsModalUec(itr);
    itr = testNode->children_.begin();
    itr++;
    TWO->isAllowAddChildBelowModalUec_ = false;
    TWO->tag_ = V2::MODAL_PAGE_TAG;
    THREE->isAllowAddChildBelowModalUec_ = false;
    THREE->tag_ = V2::MODAL_PAGE_TAG;

    /**
     * @tc.steps: step3. test CanAddChildWhenTopNodeIsModalUec.
     */
    bool res = testNode->CanAddChildWhenTopNodeIsModalUec(itr);
    EXPECT_EQ(res, true);
}

/**
 * @tc.name: UpdateBuilderNodeColorMode001
 * @tc.desc: Test UpdateBuilderNodeColorMode
 * @tc.type: FUNC
 */
HWTEST_F(UINodeTestNgTwo, UpdateBuilderNodeColorMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare the environment variables for the function.
     */
    auto parentNode = FrameNode::CreateFrameNode("parentNode", 10000, AceType::MakeRefPtr<Pattern>());
    auto childNode = FrameNode::CreateFrameNode("parentNode", 10000, AceType::MakeRefPtr<Pattern>());
    parentNode->AddChild(childNode);
    parentNode->onMainTree_ = false;
    parentNode->nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    parentNode->SetDarkMode(true);
    childNode->SetDarkMode(false);
    g_isConfigChangePerform = true;

    /**
     * @tc.steps: step2. parentNode AttachToMainTree
     * @tc.expected: parentNode->CheckIsDarkMode() equles childNode->CheckIsDarkMode()
     */
    PipelineContext* context = parentNode->GetContextWithCheck();
    parentNode->AttachToMainTree(true, context);
    EXPECT_EQ(parentNode->CheckIsDarkMode(), childNode->CheckIsDarkMode());
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/pattern.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_layout_algorithm.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node_pattern.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#include "core/components_ng/pattern/custom_frame_node/custom_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/custom_frame_node/custom_accessibility_provider.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string CHILD_NODE = "ChildNode";
} // namespace

class CustomFrameNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateNode();
};

void CustomFrameNodeTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void CustomFrameNodeTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CustomFrameNodeTestNg::CreateNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
}

/**
 * @tc.name: CustomFrameNodeFrameNodeCreator001
 * @tc.desc: Test the create of CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeFrameNodeCreator001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
}

/**
 * @tc.name: CustomFrameNodeRenderNodeModifierCreate001
 * @tc.desc: Test creation of renderNodeModifier_ in CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeRenderNodeModifierCreate001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
    RefPtr<FrameNode> childNode_0 = FrameNode::CreateFrameNode(CHILD_NODE, 0, AceType::MakeRefPtr<Pattern>());
    auto pattern = customFrameNode->GetPattern<CustomFrameNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1.Create RenderNodeModifier by CreateNodePaintMethod.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr, it created by fire CreateNodePaintMethod function.
     */
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);

    /**
     * @tc.steps: step2. Create RenderNodeModifier by SetDrawCallback.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr.
     */
    pattern->renderNodeModifier_ = nullptr;
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->SetDrawCallback(nullptr);
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);
}

/**
 * @tc.name: CustomFrameNodeRenderNodeInvalidate001
 * @tc.desc: Test Invalidate function in CustomFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, CustomFrameNodeRenderNodeInvalidate001, TestSize.Level1)
{
    RefPtr<FrameNode> customFrameNode = CreateNode();
    ASSERT_NE(customFrameNode, nullptr);
    RefPtr<FrameNode> childNode_0 = FrameNode::CreateFrameNode(CHILD_NODE, 0, AceType::MakeRefPtr<Pattern>());
    auto pattern = customFrameNode->GetPattern<CustomFrameNodePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. Call Invalidate without renderNodeModifier_.
     * @tc.expected: Process success without crash.
     */
    ASSERT_EQ(pattern->renderNodeModifier_, nullptr);
    pattern->Invalidate();

    /**
     * @tc.steps: step2.Create RenderNodeModifier by CreateNodePaintMethod.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr, it created by fire CreateNodePaintMethod function.
     */
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->renderNodeModifier_, nullptr);

    /**
     * @tc.steps: step3. Create RenderNodeModifier by SetDrawCallback.
     * @tc.expected: renderNodeModifier_ in pattern is nullptr.
     */
    ASSERT_EQ(pattern->renderNodeModifier_->renderNodeFlag_->Get(), 0);
    pattern->Invalidate();
    ASSERT_EQ(pattern->renderNodeModifier_->renderNodeFlag_->Get(), 1);
}

/**
 * @tc.name: OnRegisterTest
 * @tc.desc: Test OnRegister Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnRegisterTest001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityChildTreeCallback
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_NE(pattern, nullptr);
    int accessibilityId = 2;
    auto customAccessibilityChildTreeCallback =
        std::make_shared<CustomAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(customAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnRegister Func when nativeProvider->IsRegister() is false
     * @tc.expected: ret = false and xComponentAccessibilityChildTreeCallback->isReg_ = false
     */
    uint32_t windowId = 1;
    int32_t treeId = 2;
    bool ret = customAccessibilityChildTreeCallback->OnRegister(windowId, treeId);
    EXPECT_FALSE(ret);
    EXPECT_FALSE(customAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: OnDeregisterTest
 * @tc.desc: Test OnDeregister Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnDeregisterTest002, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityChildTreeCallback
     * @tc.expected: Create Custom and CustomAccessibilityChildTreeCallback Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_NE(pattern, nullptr);
    int accessibilityId = 2;
    auto customAccessibilityChildTreeCallback =
        std::make_shared<CustomAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(customAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDeregister Func
     * @tc.expected: ret = false and customAccessibilityChildTreeCallback->isReg_ = false
     */
    bool ret = customAccessibilityChildTreeCallback->OnDeregister();
    EXPECT_TRUE(ret);
    EXPECT_FALSE(customAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: OnSetChildTreeTest
 * @tc.desc: Test OnSetChildTree Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnSetChildTreeTest001, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityChildTreeCallback
     * @tc.expected: Create Custom and CustomAccessibilityChildTreeCallback Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto customAccessibilityChildTreeCallback =
        std::make_shared<CustomAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(customAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDeregister Func
     * @tc.expected: ret = true
     */
    int32_t childWindowId = 1;
    int32_t childTreeId = 2;
    bool ret = customAccessibilityChildTreeCallback->OnSetChildTree(childWindowId, childTreeId);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: OnClearRegisterFlagTest
 * @tc.desc: Test OnClearRegisterFlag Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnClearRegisterFlagTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityChildTreeCallback
     * @tc.expected: Create Custom and CustomAccessibilityChildTreeCallback Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto customAccessibilityChildTreeCallback =
        std::make_shared<CustomAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(customAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnClearRegisterFlag Func
     * @tc.expected: isReg_ = false;
     */
    customAccessibilityChildTreeCallback->OnClearRegisterFlag();
    EXPECT_FALSE(customAccessibilityChildTreeCallback->isReg_);
}

/**
 * @tc.name: OnAccessibilityChildTreeDeregisterTest001
 * @tc.desc: Test InitNativeNodeCallbacks Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnAccessibilityChildTreeDeregisterTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    /**
     * @tc.steps2: GetNativeProvider is null ptr
     * @tc.expected: OnAccessibilityChildTreeDeregister return false
     */
    auto result = pattern->OnAccessibilityChildTreeDeregister(AceType::RawPtr(testNode));
    ASSERT_FALSE(result);
    result = pattern->OnAccessibilityChildTreeDeregister();
    ASSERT_FALSE(result);
}

/**
 * @tc.name: FindAccessibilityNodeInfosByIdTest
 * @tc.desc: Test FindAccessibilityNodeInfosById Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, FindAccessibilityNodeInfosByIdTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call FindAccessibilityNodeInfosById Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    int32_t mode = 2;
    int32_t requestId = 3;
    std::vector<ArkUI_AccessibilityElementInfo> infos;
    int32_t ret = customAccessibilityProvider->FindAccessibilityNodeInfosById(elementId, mode, requestId, infos);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: FindAccessibilityNodeInfosByTextTest
 * @tc.desc: Test FindAccessibilityNodeInfosByText Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, FindAccessibilityNodeInfosByTextTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call FindAccessibilityNodeInfosByText Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    string text = "2";
    int32_t requestId = 3;
    std::vector<ArkUI_AccessibilityElementInfo> infos;
    int32_t ret = customAccessibilityProvider->FindAccessibilityNodeInfosByText(elementId, text, requestId, infos);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: FindFocusedAccessibilityNodeTest
 * @tc.desc: Test FindFocusedAccessibilityNode Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, FindFocusedAccessibilityNodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call FindFocusedAccessibilityNode Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    int32_t focusType = 2;
    int32_t requestId = 3;
    ArkUI_AccessibilityElementInfo info;
    int32_t ret = customAccessibilityProvider->FindFocusedAccessibilityNode(elementId, focusType, requestId, info);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: FindNextFocusAccessibilityNodeTest
 * @tc.desc: Test FindNextFocusAccessibilityNode Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, FindNextFocusAccessibilityNodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call FindNextFocusAccessibilityNode Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    int32_t direction = 2;
    int32_t requestId = 3;
    ArkUI_AccessibilityElementInfo info;
    int32_t ret =
        customAccessibilityProvider->FindNextFocusAccessibilityNode(elementId, direction, requestId, info);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: ExecuteAccessibilityActionTest
 * @tc.desc: Test ExecuteAccessibilityAction Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, ExecuteAccessibilityActionTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call ExecuteAccessibilityAction Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    int32_t action = 2;
    int32_t requestId = 3;
    std::map<std::string, std::string> actionArguments;
    int32_t ret =
        customAccessibilityProvider->ExecuteAccessibilityAction(elementId, action, requestId, actionArguments);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: ClearFocusedAccessibilityNodeTest
 * @tc.desc: Test ClearFocusedAccessibilityNode Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, ClearFocusedAccessibilityNodeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call ClearFocusedAccessibilityNode Func
     * @tc.expected: ret = 0
     */
    int32_t ret = customAccessibilityProvider->ClearFocusedAccessibilityNode();
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GetAccessibilityNodeCursorPositionTest
 * @tc.desc: Test GetAccessibilityNodeCursorPosition Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, GetAccessibilityNodeCursorPositionTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call GetAccessibilityNodeCursorPosition Func
     * @tc.expected: ret = 0
     */
    int64_t elementId = 1;
    int32_t requestId = 2;
    int32_t cursorPosition = 3;
    int32_t ret =
        customAccessibilityProvider->GetAccessibilityNodeCursorPosition(elementId, requestId, cursorPosition);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: SendAccessibilityAsyncEventTest1
 * @tc.desc: Test SendAccessibilityAsyncEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, SendAccessibilityAsyncEventTest1, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call SendAccessibilityAsyncEvent Func when callback is not null and thirdAccessibilityManager_ is not
     * null
     * @tc.expected: ret = 0
     */
    ArkUI_AccessibilityEventInfo accessibilityEvent;
    auto thirdAccessibilityManager = std::make_shared<ThirdAccessibilityManager>();
    customAccessibilityProvider->thirdAccessibilityManager_ = thirdAccessibilityManager;
    auto callback = [](int32_t errorCode) {};
    int32_t ret = customAccessibilityProvider->SendAccessibilityAsyncEvent(accessibilityEvent, callback);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: SendAccessibilityAsyncEventTest2
 * @tc.desc: Test SendAccessibilityAsyncEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, SendAccessibilityAsyncEventTest2, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call SendAccessibilityAsyncEvent Func when callback is null and thirdAccessibilityManager_ is not null
     * @tc.expected: ret = 0
     */
    ArkUI_AccessibilityEventInfo accessibilityEvent;
    auto thirdAccessibilityManager = std::make_shared<ThirdAccessibilityManager>();
    customAccessibilityProvider->thirdAccessibilityManager_ = thirdAccessibilityManager;
    int32_t ret = customAccessibilityProvider->SendAccessibilityAsyncEvent(accessibilityEvent, nullptr);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: SendAccessibilityAsyncEventTest3
 * @tc.desc: Test SendAccessibilityAsyncEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, SendAccessibilityAsyncEventTest3, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);

    /**
     * @tc.step2: Call SendAccessibilityAsyncEvent Func when callback is not null and thirdAccessibilityManager_ is null
     * @tc.expected: ret = -1
     */
    ArkUI_AccessibilityEventInfo accessibilityEvent;
    customAccessibilityProvider->thirdAccessibilityManager_ = std::shared_ptr<ThirdAccessibilityManager>();
    auto callback = [](int32_t errorCode) {};
    int32_t ret = customAccessibilityProvider->SendAccessibilityAsyncEvent(accessibilityEvent, callback);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: OnDetachContextTest
 * @tc.desc: Test OnDetachContext Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnDetachContextTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom
     * @tc.expected: Create Custom Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    PipelineContext* context = testNode->GetContext();
    ASSERT_TRUE(context);
    /**
     * @tc.step2: Call OnDetachContext Func
     * @tc.expected: onWindowStateChangedCallbacks_ can not find nodeId by the frameNode
     */
    pattern->OnDetachContext(context);
    EXPECT_EQ(context->onWindowStateChangedCallbacks_.find(testNode->GetId()),
        context->onWindowStateChangedCallbacks_.end());
}

/**
 * @tc.name: InitializeAccessibility
 * @tc.desc: Test InitializeAccessibility Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, InitializeAccessibilityTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom
     * @tc.expected: Create Custom Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    PipelineContext* context = testNode->GetContext();
    ASSERT_TRUE(context);
    /**
     * @tc.step2: Call InitializeAccessibility Func
     */
    pattern->InitializeAccessibility(context);
    auto nprovider = pattern->GetNativeAccessibilityProvider();
    ASSERT_TRUE(nprovider);
}

/**
 * @tc.name: OnDumpChildInfoTest
 * @tc.desc: Test OnDumpChildInfo Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, OnDumpChildInfoTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityChildTreeCallback
     * @tc.expected: Create Custom and CustomAccessibilityChildTreeCallback Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    int accessibilityId = 2;
    auto customAccessibilityChildTreeCallback =
        std::make_shared<CustomAccessibilityChildTreeCallback>(pattern, accessibilityId);
    ASSERT_TRUE(customAccessibilityChildTreeCallback);
    /**
     * @tc.step2: Call OnDumpChildInfo Func
     * @tc.expected: ret = false
     */
    std::vector<std::string> g_params;
    std::vector<std::string> info;
    bool ret = customAccessibilityChildTreeCallback->OnDumpChildInfo(g_params, info);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SendThirdAccessibilityProviderTest
 * @tc.desc: Test SendThirdAccessibilityProvider Func
 * @tc.type: FUNC
 */
HWTEST_F(CustomFrameNodeTestNg, SendThirdAccessibilityProviderTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create Custom and CustomAccessibilityProvider
     * @tc.expected: Create Custom and CustomAccessibilityProvider Successfully
     */
    auto testNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<CustomPattern>(), true);
    ASSERT_NE(testNode, nullptr);
    auto pattern = testNode->GetPattern<CustomPattern>();
    ASSERT_TRUE(pattern);
    auto customAccessibilityProvider = std::make_shared<CustomAccessibilityProvider>(pattern);
    ASSERT_TRUE(customAccessibilityProvider);
    /**
     * @tc.step2: Call SendThirdAccessibilityProvider Func
     * @tc.expected: customAccessibilityProvider->thirdAccessibilityManager_ is not null
     */
    auto thirdAccessibilityManager = std::make_shared<ThirdAccessibilityManager>();
    customAccessibilityProvider->SendThirdAccessibilityProvider(thirdAccessibilityManager);
    EXPECT_TRUE(customAccessibilityProvider->thirdAccessibilityManager_.lock());
}
} // namespace OHOS::Ace::NG

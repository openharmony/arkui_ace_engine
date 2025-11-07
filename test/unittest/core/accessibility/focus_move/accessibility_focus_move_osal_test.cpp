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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "accessibility_system_ability_client.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_accessibility_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_ng.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal_third.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_third_node_utils.h"
#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"
#include "core/pipeline_ng/pipeline_context.h"

#include "test/unittest/core/accessibility/js_accessibility_manager_test.h"
#include "test/unittest/core/accessibility/js_third_provider_interaction_operation_test.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
constexpr float TEST_FRAME_NODE_WIDTH = 10.0f;
constexpr float TEST_FRAME_NODE_HEIGHT = 10.0f;

class MockRenderContextTest : public NG::RenderContext {
public:
    NG::RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<NG::RectF> retf;
};

RefPtr<NG::FrameNode> CreatFrameNode()
{
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->SetActive(true, false);
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto rect = std::make_shared<NG::RectF>(0.0, 0.0, TEST_FRAME_NODE_WIDTH, TEST_FRAME_NODE_HEIGHT);
    renderContext->retf = rect;
    frameNode->renderContext_ = renderContext;
    return frameNode;
}

void CreatNextPrevFrameNode(
    RefPtr<Framework::JsAccessibilityManager>& jsAccessibilityManager,
    int32_t instanceId,
    RefPtr<NG::FrameNode>& currentFrameNode,
    RefPtr<NG::FrameNode>& nextFrameNode,
    RefPtr<NG::FrameNode>& prevFrameNode)
{
    ASSERT_NE(jsAccessibilityManager, nullptr);
    currentFrameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentFrameNode, nullptr);

    nextFrameNode = NG::FrameNode::CreateFrameNode("nextFrameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(nextFrameNode, nullptr);
    std::string nextKey = "next_key";
    nextFrameNode->UpdateInspectorId(nextKey);
    prevFrameNode = NG::FrameNode::CreateFrameNode("prevFrameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(prevFrameNode, nullptr);
    std::string currentKey = "current_key";
    currentFrameNode->UpdateInspectorId(currentKey);
    auto accessibilityProperty = currentFrameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityNextFocusInspectorKey(nextKey);
    jsAccessibilityManager->UpdateAccessibilityNextFocusIdMap(
        instanceId, currentKey, prevFrameNode->GetAccessibilityId());
}

} // namespace

class AccessibilityFocusMoveTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityFocusMoveTest::SetUpTestCase()
{
    NG::MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityFocusMoveTest::TearDownTestCase()
{
    NG::MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

class MockFocusStrategyOsal : public FocusStrategyOsal {
    DECLARE_ACE_TYPE(MockFocusStrategyOsal, AceType);
public:
    explicit MockFocusStrategyOsal(const RefPtr<JsAccessibilityManager>& jsAccessibilityManager)
        : FocusStrategyOsal(jsAccessibilityManager) {}
    ~MockFocusStrategyOsal() override = default;

    void InvailidElementInfo(Accessibility::AccessibilityElementInfo& info) override {}
    bool UpdateOriginNodeInfo(int64_t elementId) override { return updateOriginNodeInfoResult_; }
    std::shared_ptr<FocusRulesCheckNode> GetCurrentCheckNode() override { return currentCheckNode_; }
    void UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode) override {}
    std::shared_ptr<FocusRulesCheckNode> ChangeToRoot() override { return rootCheckNode_; }
    bool ChangeToEmbed(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override
    {
        return changeToEmbedResult_;
    }
    bool UpdateElementInfo(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override
    {
        return updateElementInfoResult_;
    }
public:
    bool updateOriginNodeInfoResult_ = true;
    std::shared_ptr<FocusRulesCheckNode> currentCheckNode_;
    bool updateNextFocusResult_ = true;
    std::shared_ptr<FocusRulesCheckNode> rootCheckNode_;
    bool changeToEmbedResult_ = true;
    bool updateElementInfoResult_ = true;
};

/**
 * @tc.name: AccessibilityNodeUtilsTest001
 * @tc.desc: GetPropText
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, AccessibilityNodeUtilsTest001, TestSize.Level1)
{
    int32_t nodeId = 1;
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    std::string testStr = "hello";
    std::string strStar(testStr.size(), '*');
    accessibilityNode->SetText(testStr);
    auto checkNode = std::make_shared<AccessibilityNodeRulesCheckNode>(
        accessibilityNode, static_cast<int64_t>(accessibilityNode->GetNodeId()));
    ASSERT_NE(checkNode, nullptr);
    Accessibility::PropValue value;
    auto result = checkNode->GetPropText(value);
    ASSERT_TRUE(result);
    ASSERT_EQ(value.valueStr, testStr);
    accessibilityNode->SetIsPassword(true);
    result = checkNode->GetPropText(value);
    ASSERT_TRUE(result);
    ASSERT_EQ(value.valueStr, strStar);
}

/**
 * @tc.name: AccessibilityNodeUtilsTest002
 * @tc.desc: GetPropActionNames
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, AccessibilityNodeUtilsTest002, TestSize.Level1)
{
    int32_t nodeId = 1;
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    auto checkNode = std::make_shared<AccessibilityNodeRulesCheckNode>(
        accessibilityNode, static_cast<int64_t>(accessibilityNode->GetNodeId()));
    ASSERT_NE(checkNode, nullptr);
    accessibilityNode->AddSupportAction(AceAction::ACTION_FOCUS);
    Accessibility::PropValue value;
    auto result = checkNode->GetPropActionNames(value);
    EXPECT_EQ(result, true);
    auto findRet = value.valueArray.find("clearFocus");
    EXPECT_TRUE(findRet == value.valueArray.end());
    findRet = value.valueArray.find("focus");
    EXPECT_TRUE(findRet != value.valueArray.end());
}

/**
 * @tc.name: AccessibilityNodeUtilsTest003
 * @tc.desc: GetPropHintText
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, AccessibilityNodeUtilsTest003, TestSize.Level1)
{
    int32_t nodeId = 1;
    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, "test");
    ASSERT_NE(accessibilityNode, nullptr);
    std::string testStr = "hello";
    accessibilityNode->SetHintText(testStr);
    auto checkNode = std::make_shared<AccessibilityNodeRulesCheckNode>(
        accessibilityNode, static_cast<int64_t>(accessibilityNode->GetNodeId()));
    ASSERT_NE(checkNode, nullptr);
    Accessibility::PropValue value;
    auto result = checkNode->GetPropHintText(value);
    ASSERT_TRUE(result);
    ASSERT_EQ(value.valueType, Accessibility::ValueType::STRING);
    ASSERT_EQ(value.valueStr, testStr);
}

/**
 * @tc.name: FocusStrategyOsalNGTest001
 * @tc.desc: SetNextFocusIdToElementInfo  SetPrevFocusIdToElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalNGTest001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    ASSERT_NE(ngPipeline, nullptr);
    auto rootNode = ngPipeline->GetRootElement();
    auto instanceId = context->GetInstanceId();
    ASSERT_NE(rootNode, nullptr);

    RefPtr<NG::FrameNode> currentFrameNode;
    RefPtr<NG::FrameNode> nextFrameNode;
    RefPtr<NG::FrameNode> prevFrameNode;
    CreatNextPrevFrameNode(jsAccessibilityManager, instanceId, currentFrameNode, nextFrameNode, prevFrameNode);
    ASSERT_NE(currentFrameNode, nullptr);
    ASSERT_NE(nextFrameNode, nullptr);
    ASSERT_NE(prevFrameNode, nullptr);
    rootNode->AddChild(currentFrameNode);
    rootNode->AddChild(nextFrameNode);
    rootNode->AddChild(prevFrameNode);

    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, context);
    strategy.UpdateOriginNodeInfo(currentFrameNode->GetAccessibilityId());
    auto checkNode = strategy.GetCurrentCheckNode();
    strategy.UpdateNextFocus(checkNode);
    Accessibility::AccessibilityElementInfo nodeInfo;
    strategy.UpdateElementInfo(checkNode, nodeInfo);
    ASSERT_NE(strategy.rootNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.baseNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.baseNextNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.basePrevNode_.Upgrade(), nullptr);
    EXPECT_EQ(nodeInfo.GetAccessibilityNextFocusId(), nextFrameNode->GetAccessibilityId());
    EXPECT_EQ(nodeInfo.GetAccessibilityPreviousFocusId(), prevFrameNode->GetAccessibilityId());
    rootNode->RemoveChild(currentFrameNode);
    rootNode->RemoveChild(nextFrameNode);
    rootNode->RemoveChild(prevFrameNode);
}
/**
 * @tc.name: FocusStrategyOsalNGTest002
 * @tc.desc: SetNextFocusIdToElementInfo  SetPrevFocusIdToElementInfo with tree Id
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalNGTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    ASSERT_NE(ngPipeline, nullptr);
    auto rootNode = ngPipeline->GetRootElement();
    auto instanceId = context->GetInstanceId();
    ASSERT_NE(rootNode, nullptr);

    RefPtr<NG::FrameNode> currentFrameNode;
    RefPtr<NG::FrameNode> nextFrameNode;
    RefPtr<NG::FrameNode> prevFrameNode;
    CreatNextPrevFrameNode(jsAccessibilityManager, instanceId, currentFrameNode, nextFrameNode, prevFrameNode);
    ASSERT_NE(currentFrameNode, nullptr);
    ASSERT_NE(nextFrameNode, nullptr);
    ASSERT_NE(prevFrameNode, nullptr);
    rootNode->AddChild(currentFrameNode);
    rootNode->AddChild(nextFrameNode);
    rootNode->AddChild(prevFrameNode);
    int32_t treeId = 1;
    jsAccessibilityManager->treeId_ = treeId;

    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, context);
    strategy.UpdateOriginNodeInfo(currentFrameNode->GetAccessibilityId());
    auto checkNode = strategy.GetCurrentCheckNode();
    strategy.UpdateNextFocus(checkNode);
    Accessibility::AccessibilityElementInfo nodeInfo;
    strategy.UpdateElementInfo(checkNode, nodeInfo);
    ASSERT_NE(strategy.rootNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.baseNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.baseNextNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.basePrevNode_.Upgrade(), nullptr);
    auto nextId = nextFrameNode->GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, nextId);
    auto prevId = prevFrameNode->GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(treeId, prevId);
    EXPECT_EQ(nodeInfo.GetAccessibilityNextFocusId(), nextId);
    EXPECT_EQ(nodeInfo.GetAccessibilityPreviousFocusId(), prevId);
    rootNode->RemoveChild(currentFrameNode);
    rootNode->RemoveChild(nextFrameNode);
    rootNode->RemoveChild(prevFrameNode);
}

/**
 * @tc.name: FocusStrategyOsalNGTest003
 * @tc.desc: SetNextFocusIdToElementInfo  SetPrevFocusIdToElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalNGTest003, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    ASSERT_NE(ngPipeline, nullptr);
    auto rootNode = ngPipeline->GetRootElement();
    auto instanceId = context->GetInstanceId();
    ASSERT_NE(rootNode, nullptr);

    RefPtr<NG::FrameNode> finalFrameNode;
    RefPtr<NG::FrameNode> nextFrameNode;
    RefPtr<NG::FrameNode> prevFrameNode;
    CreatNextPrevFrameNode(jsAccessibilityManager, instanceId, finalFrameNode, nextFrameNode, prevFrameNode);
    ASSERT_NE(finalFrameNode, nullptr);
    ASSERT_NE(nextFrameNode, nullptr);
    ASSERT_NE(prevFrameNode, nullptr);
    rootNode->AddChild(finalFrameNode);
    rootNode->AddChild(nextFrameNode);
    rootNode->AddChild(prevFrameNode);

    auto currentFrameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentFrameNode, nullptr);
    rootNode->AddChild(currentFrameNode);
    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, context);
    strategy.UpdateOriginNodeInfo(currentFrameNode->GetAccessibilityId());
    auto checkNode = strategy.GetCurrentCheckNode();
    strategy.UpdateNextFocus(checkNode);
    ASSERT_NE(strategy.rootNode_.Upgrade(), nullptr);
    ASSERT_NE(strategy.baseNode_.Upgrade(), nullptr);
    ASSERT_EQ(strategy.baseNextNode_.Upgrade(), nullptr);
    ASSERT_EQ(strategy.basePrevNode_.Upgrade(), nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    auto finalNode = std::make_shared<FrameNodeRulesCheckNode>(finalFrameNode, finalFrameNode->GetAccessibilityId());
    strategy.UpdateElementInfo(finalNode, nodeInfo);
    EXPECT_EQ(nodeInfo.GetAccessibilityNextFocusId(), nextFrameNode->GetAccessibilityId());
    EXPECT_EQ(nodeInfo.GetAccessibilityPreviousFocusId(), prevFrameNode->GetAccessibilityId());
    rootNode->RemoveChild(currentFrameNode);
    rootNode->RemoveChild(finalFrameNode);
    rootNode->RemoveChild(nextFrameNode);
    rootNode->RemoveChild(prevFrameNode);
}

/**
 * @tc.name: FocusStrategyOsalNGTest004
 * @tc.desc: ChangeToEmbed
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalNGTest004, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    FocusStrategyOsalNG strategy(jsAccessibilityManager, context, context);
    auto currentFrameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentFrameNode, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    auto checkNode =
        std::make_shared<FrameNodeRulesCheckNode>(currentFrameNode, currentFrameNode->GetAccessibilityId());
    auto result = strategy.ChangeToEmbed(checkNode, nodeInfo);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: FocusStrategyOsalThirdTest001
 * @tc.desc: ChangeToRoot
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalThirdTest001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    ASSERT_NE(ohAccessibilityProvider, nullptr);
    NodeConfig config;
    FocusStrategyOsalThird strategy(jsAccessibilityManager, ohAccessibilityProvider, config);
    auto rootNode = strategy.ChangeToRoot();
    EXPECT_NE(rootNode, nullptr);
}

/**
 * @tc.name: FocusStrategyOsalThirdTest002
 * @tc.desc: ChangeToRoot
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalThirdTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    ASSERT_NE(ohAccessibilityProvider, nullptr);
    ohAccessibilityProvider->SetInjectResult(-1);
    NodeConfig config;
    FocusStrategyOsalThird strategy(jsAccessibilityManager, ohAccessibilityProvider, config);
    auto rootNode = strategy.ChangeToRoot();
    EXPECT_EQ(rootNode, nullptr);
}

/**
 * @tc.name: ThirdRulesCheckNodeTest001
 * @tc.desc: GetPropActionNames
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, ThirdRulesCheckNodeTest001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    ASSERT_NE(ohAccessibilityProvider, nullptr);
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    int32_t elementId = 1;
    nodeInfo->SetElementId(elementId);
    ArkUI_AccessibleAction tempAction { ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS, "test"};
    nodeInfo->AddOperationAction(tempAction);
    auto checkNode = std::make_shared<ThirdRulesCheckNode>(nodeInfo, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode, nullptr);
    
    Accessibility::PropValue value;
    auto result = checkNode->GetPropActionNames(value);
    EXPECT_EQ(result, true);
    auto findRet = value.valueArray.find("clearAccessibilityFocus");
    EXPECT_TRUE(findRet == value.valueArray.end());
    findRet = value.valueArray.find("accessibilityFocus");
    EXPECT_TRUE(findRet != value.valueArray.end());
}

/**
 * @tc.name: ThirdRulesCheckNodeTest002
 * @tc.desc: GetAceChildren
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, ThirdRulesCheckNodeTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    ASSERT_NE(ohAccessibilityProvider, nullptr);
    auto nodeInfo = std::make_shared<ArkUI_AccessibilityElementInfo>();
    int32_t elementId = 1;
    nodeInfo->SetElementId(elementId);
    nodeInfo->AddChildNodeId(-1);
    nodeInfo->AddChildNodeId(Accessibility::AccessibilityElementInfo::ROOT_PARENT_ID);
    nodeInfo->AddChildNodeId(MAX_TEST_ELEMENT_COUNT);
    nodeInfo->AddChildNodeId(0);
    auto checkNode = std::make_shared<ThirdRulesCheckNode>(nodeInfo, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode, nullptr);

    auto children = checkNode->GetAceChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: ThirdRulesCheckNodeTest003
 * @tc.desc: GetAceParent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, ThirdRulesCheckNodeTest003, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto ohAccessibilityProvider
        = AceType::MakeRefPtr<MockOhAccessibilityProvider>();
    ASSERT_NE(ohAccessibilityProvider, nullptr);
    int32_t elementId = 1;
    auto nodeInfo1 = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo1->SetElementId(elementId);
    nodeInfo1->SetParentId(-1);
    auto checkNode1 = std::make_shared<ThirdRulesCheckNode>(nodeInfo1, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode1, nullptr);
    auto parent = checkNode1->GetAceParent();
    EXPECT_EQ(parent, nullptr);

    auto nodeInfo2 = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo2->SetElementId(elementId);
    nodeInfo2->SetParentId(Accessibility::AccessibilityElementInfo::ROOT_PARENT_ID);
    auto checkNode2 = std::make_shared<ThirdRulesCheckNode>(nodeInfo2, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode2, nullptr);
    parent = checkNode2->GetAceParent();
    EXPECT_EQ(parent, nullptr);

    auto nodeInfo3 = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo3->SetElementId(elementId);
    nodeInfo3->SetParentId(MAX_TEST_ELEMENT_COUNT);
    auto checkNode3 = std::make_shared<ThirdRulesCheckNode>(nodeInfo3, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode3, nullptr);
    parent = checkNode3->GetAceParent();
    EXPECT_EQ(parent, nullptr);

    auto nodeInfo4 = std::make_shared<ArkUI_AccessibilityElementInfo>();
    nodeInfo4->SetElementId(elementId);
    nodeInfo4->SetParentId(0);
    auto checkNode4 = std::make_shared<ThirdRulesCheckNode>(nodeInfo4, elementId, ohAccessibilityProvider);
    ASSERT_NE(checkNode4, nullptr);
    parent = checkNode4->GetAceParent();
    EXPECT_NE(parent, nullptr);
}

/**
 * @tc.name: FocusStrategyOsalTest001
 * @tc.desc: IsProcessGetScrollAncestor
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalTest001, TestSize.Level1)
{
    std::map<FocusMoveDirection, bool> IsProcessGetScrollAncestorTest = {
        { FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR, true },
        { FocusMoveDirection::GET_BACKWARD_SCROLL_ANCESTOR, true },
        { FocusMoveDirection::GET_SCROLLABLE_ANCESTOR, true },
        { FocusMoveDirection::DIRECTION_INVALID, false },
    };
    Accessibility::AccessibilityFocusMoveParam param;
    for (auto& testMap : IsProcessGetScrollAncestorTest) {
        param.direction = testMap.first;
        auto result = FocusStrategyOsal::IsProcessGetScrollAncestor(param);
        ASSERT_EQ(result, testMap.second);
    }
}

/**
 * @tc.name: FocusStrategyOsalTest002
 * @tc.desc: ProcessGetScrollAncestor
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    bool result = false;
    Accessibility::AccessibilityFocusMoveParam param;

    int64_t elementId = 0;
    std::list<Accessibility::AccessibilityElementInfo> infos;
    param.direction = FocusMoveDirection::GET_BACKWARD_SCROLL_ANCESTOR;
    strategy.ProcessGetScrollAncestor(elementId, param, infos);
    ASSERT_EQ(infos.empty(), true);
    param.direction = FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR;
    strategy.ProcessGetScrollAncestor(elementId, param, infos);
    ASSERT_EQ(infos.empty(), true);
    param.direction = FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR;
    strategy.ProcessGetScrollAncestor(elementId, param, infos);
    ASSERT_EQ(infos.empty(), true);
}

/**
 * @tc.name: FocusStrategyOsalTest003
 * @tc.desc: GetAceCondition
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalTest003, TestSize.Level1)
{
    std::map<DetailCondition, AceFocusMoveDetailCondition> GetAceConditionTest = {
        { DetailCondition::BYPASS_SELF, {.bypassSelf = true, .bypassDescendants = false} },
        { DetailCondition::BYPASS_SELF_DESCENDANTS, {.bypassSelf = true, .bypassDescendants = true} },
        { DetailCondition::CHECK_SELF, {.bypassSelf = false, .bypassDescendants = false} },
        { DetailCondition::CHECK_SELF_BYPASS_DESCENDANTS, {.bypassSelf = false, .bypassDescendants = true} },
    };

    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;

    for (auto& testMap : GetAceConditionTest) {
        param.condition = testMap.first;
        auto result = strategy.GetAceCondition(param);
        ASSERT_EQ(result.bypassSelf, testMap.second.bypassSelf);
        ASSERT_EQ(result.bypassDescendants, testMap.second.bypassDescendants);
    }
}

/**
 * @tc.name: FocusStrategyOsalHandleFocusMoveSearchResultTest001
 * @tc.desc: HandleFocusMoveSearchResult
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalHandleFocusMoveSearchResultTest001, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    // aceResult FIND_SUCCESS
    auto targetNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    AceFocusMoveResult aceResult = AceFocusMoveResult::FIND_SUCCESS;
    auto finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_SUCCESS);
    // aceResult FIND_FAIL
    aceResult = AceFocusMoveResult::FIND_FAIL;
    finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL);

    // aceResult FIND_SUCCESS, UpdateElementInfo fail
    aceResult = AceFocusMoveResult::FIND_SUCCESS;
    strategy.updateElementInfoResult_ = false;
    finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL);

    // aceResult FIND_FAIL, finalNode nullptr
    std::shared_ptr<FocusRulesCheckNode> targetNode1;
    aceResult = AceFocusMoveResult::FIND_FAIL;
    strategy.updateElementInfoResult_ = false;
    finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode1, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL);
}

/**
 * @tc.name: FocusStrategyOsalHandleFocusMoveSearchResultTest002
 * @tc.desc: HandleFocusMoveSearchResult
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalHandleFocusMoveSearchResultTest002, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    // aceResult FIND_CHILDTREE
    auto targetNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    AceFocusMoveResult aceResult = AceFocusMoveResult::FIND_CHILDTREE;
    param.direction = FocusMoveDirection::BACKWARD;
    auto finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::DOUBLE_CHECK_CHILD_PROPERTY_AND_GET_LAST);
}

/**
 * @tc.name: FocusStrategyOsalHandleFocusMoveSearchResultTest003
 * @tc.desc: HandleFocusMoveSearchResult
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalHandleFocusMoveSearchResultTest003, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    // aceResult FIND_FAIL_IN_CHILDTREE, direction  BACKWARD
    auto targetNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    AceFocusMoveResult aceResult = AceFocusMoveResult::FIND_FAIL_IN_CHILDTREE;
    param.direction = FocusMoveDirection::BACKWARD;
    auto finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL_IN_CHILDTREE);
}

/**
 * @tc.name: FocusStrategyOsalHandleFocusMoveSearchResultTest004
 * @tc.desc: HandleFocusMoveSearchResult
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalHandleFocusMoveSearchResultTest004, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    auto targetNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    // aceResult FIND_EMBED_TARGET, ChangeToEmbed successs
    AceFocusMoveResult aceResult = AceFocusMoveResult::FIND_EMBED_TARGET;
    strategy.changeToEmbedResult_ = true;
    auto finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_NEXT);

    // aceResult FIND_EMBED_TARGET, ChangeToEmbed fail
    aceResult = AceFocusMoveResult::FIND_EMBED_TARGET;
    strategy.changeToEmbedResult_ = false;
    finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL);
}

/**
 * @tc.name: FocusStrategyOsalHandleFocusMoveSearchResultTest005
 * @tc.desc: HandleFocusMoveSearchResult
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalHandleFocusMoveSearchResultTest005, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    // aceResult FIND_FAIL_IN_SCROLL
    auto targetNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    AceFocusMoveResult aceResult = AceFocusMoveResult::FIND_FAIL_IN_SCROLL;
    auto finalResult = strategy.HandleFocusMoveSearchResult(param, targetNode, aceResult, info);
    ASSERT_EQ(finalResult, FocusMoveResultType::SEARCH_FAIL_IN_SCROLL);
}

/**
 * @tc.name: FocusStrategyOsalTest004
 * @tc.desc: ExecuteFocusMoveSearch
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusStrategyOsalTest004, TestSize.Level1)
{
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    MockFocusStrategyOsal strategy(jsAccessibilityManager);
        int64_t elementId = 0;
    Accessibility::AccessibilityFocusMoveParam param;
    Accessibility::AccessibilityElementInfo info;
    param.direction = FocusMoveDirection::BACKWARD;
    auto finalResult = strategy.ExecuteFocusMoveSearch(elementId, param, info);
    param.direction = FocusMoveDirection::FORWARD;
    finalResult = strategy.ExecuteFocusMoveSearch(elementId, param, info);
    param.direction = FocusMoveDirection::FIND_LAST;
    finalResult = strategy.ExecuteFocusMoveSearch(elementId, param, info);
    param.direction = FocusMoveDirection::DIRECTION_INVALID;
    finalResult = strategy.ExecuteFocusMoveSearch(elementId, param, info);
    ASSERT_EQ(finalResult.resultType, FocusMoveResultType::NOT_SUPPORT);
}

/**
 * @tc.name: DetectParentRulesCheckNodeTest001
 * @tc.desc: ExecuteFocusMoveSearch
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, DetectParentRulesCheckNodeTest001, TestSize.Level1)
{
    auto baseNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(baseNode, nullptr);
    AccessibilityElementInfo nodeInfo;
    AccessibleAction action(ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS, "ace");
    AccessibleAction action1(ActionType::ACCESSIBILITY_ACTION_INVALID, "ace");
    nodeInfo.AddAction(action);
    nodeInfo.AddAction(action1);
    auto checkNode = std::make_shared<DetectParentRulesCheckNode>(nodeInfo, baseNode);

    Accessibility::PropValue value;
    auto result = checkNode->GetPropActionNames(value);
    EXPECT_EQ(result, true);
    auto findRet = value.valueArray.find("clearAccessibilityFocus");
    EXPECT_TRUE(findRet == value.valueArray.end());
    findRet = value.valueArray.find("accessibilityFocus");
    EXPECT_TRUE(findRet != value.valueArray.end());
}

/**
 * @tc.name: FocusMoveSearchWithCondition001
 * @tc.desc: ExecuteFocusMoveSearch
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusMoveSearchWithCondition001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->SetPipelineContext(context);
    MockAccessibilityElementOperatorCallback operatorCallback;

    //  GetPipelineByWindowId fail
    auto windowId = context->GetWindowId();
    auto elementId = 0;
    Accessibility::AccessibilityFocusMoveParam param;
    int32_t requestId = 1;
    Accessibility::AccessibilityElementInfo info;
    info.SetAccessibilityId(elementId);
    jsAccessibilityManager->FocusMoveSearchWithCondition(info, param, requestId, operatorCallback, windowId + 1);
    EXPECT_EQ(operatorCallback.mockResult_.resultType, FocusMoveResultType::SEARCH_FAIL);
}

/**
 * @tc.name: FocusMoveSearchWithCondition002
 * @tc.desc: IsProcessGetScrollAncestor
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusMoveSearchWithCondition002, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->SetPipelineContext(context);
    MockAccessibilityElementOperatorCallback operatorCallback;

    //  ProcessGetScrollAncestor no infos
    auto windowId = context->GetWindowId();
    jsAccessibilityManager->SetWindowId(windowId);
    auto elementId = 0;
    Accessibility::AccessibilityElementInfo info;
    info.SetAccessibilityId(elementId);
    Accessibility::AccessibilityFocusMoveParam param;
    int32_t requestId = 1;
    param.direction = FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR;
    jsAccessibilityManager->FocusMoveSearchWithCondition(info, param, requestId, operatorCallback, windowId);
    EXPECT_EQ(operatorCallback.mockResult_.resultType, FocusMoveResultType::SEARCH_FAIL);
}

/**
 * @tc.name: FocusMoveSearchWithCondition003
 * @tc.desc: IsProcessGetScrollAncestor
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusMoveSearchWithCondition003, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->SetPipelineContext(context);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    ASSERT_NE(ngPipeline, nullptr);
    auto rootNode = ngPipeline->GetRootElement();
    ASSERT_NE(rootNode, nullptr);

    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    rootNode->AddChild(frameNode);
    frameNode->MountToParent(rootNode);
    // parent is fowardScrollAncestor
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetSpecificSupportActionCallback(
        [accessibilityPtr = AceType::WeakClaim(AceType::RawPtr(accessibilityProperty))]() {
        const auto& accessibilityProperty = accessibilityPtr.Upgrade();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    });

    //  ProcessGetScrollAncestor have infos
    MockAccessibilityElementOperatorCallback operatorCallback;
    auto windowId = context->GetWindowId();
    jsAccessibilityManager->SetWindowId(windowId);
    auto elementId = frameNode1->GetAccessibilityId();
    Accessibility::AccessibilityElementInfo info;
    info.SetAccessibilityId(elementId);
    Accessibility::AccessibilityFocusMoveParam param;
    int32_t requestId = 1;
    param.direction = FocusMoveDirection::GET_FORWARD_SCROLL_ANCESTOR;
    jsAccessibilityManager->FocusMoveSearchWithCondition(info, param, requestId, operatorCallback, windowId);
    EXPECT_EQ(operatorCallback.mockResult_.resultType, FocusMoveResultType::SEARCH_SUCCESS);
    rootNode->RemoveChild(frameNode);
}

/**
 * @tc.name: FocusMoveSearchWithCondition004
 * @tc.desc: IsProcessGetScrollAncestor
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusMoveTest, FocusMoveSearchWithCondition004, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    jsAccessibilityManager->SetPipelineContext(context);
    MockAccessibilityElementOperatorCallback operatorCallback;

    //  ExecuteFocusMoveSearch no infos
    auto windowId = context->GetWindowId();
    jsAccessibilityManager->SetWindowId(windowId);
    auto elementId = 0;
    Accessibility::AccessibilityFocusMoveParam param;
    int32_t requestId = 1;
    param.direction = FocusMoveDirection::FORWARD;
    Accessibility::AccessibilityElementInfo info;
    info.SetAccessibilityId(elementId);
    jsAccessibilityManager->FocusMoveSearchWithCondition(info, param, requestId, operatorCallback, windowId);
    EXPECT_EQ(operatorCallback.mockResult_.resultType, FocusMoveResultType::SEARCH_FAIL);
}

} // namespace OHOS::Ace::NG
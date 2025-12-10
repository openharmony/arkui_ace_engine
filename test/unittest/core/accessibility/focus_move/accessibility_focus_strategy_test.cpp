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
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "core/pipeline_ng/pipeline_context.h"

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

class MockAccessibilityFocusStrategy : public AccessibilityFocusStrategy {
public:
    bool CanAccessibilityFocus(const std::shared_ptr<FocusRulesCheckNode>& currentNode) override
    {
        CHECK_NULL_RETURN(currentNode, false);
        if ((mockCanFocusId_ != -1) && (currentNode->GetAccessibilityId() == mockCanFocusId_)) {
            return true;
        }
        return mockCanFocus_;
    }
    bool IsRootType(const std::shared_ptr<FocusRulesCheckNode>& currentNode) override
    {
        return false;
    }

    bool mockCanFocusId_ = -1;
    bool mockCanFocus_ = false;
};
class MockFocusRulesCheckNode : public FocusRulesCheckNode {
public:
    explicit MockFocusRulesCheckNode(int64_t accessibilityId)
        : FocusRulesCheckNode(accessibilityId) {}
    ~MockFocusRulesCheckNode() override = default;

    bool GetPropText(Accessibility::PropValue& value) override
    {
        return false;
    }

    bool GetPropHintText(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropDesc(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropAccessibilityText(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropType(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropAccessibilityLevel(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropAccessibilityGroup(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropIsEnable(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropChildrenCount(Accessibility::PropValue& value) override
    {
        return false;
    }
    bool GetPropActionNames(Accessibility::PropValue& value) override
    {
        value.valueType = Accessibility::ValueType::ARRAY;
        value.valueArray.insert(mockValueArray_.begin(), mockValueArray_.end());
        return true;
    }
    std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> GetChildren() override
    {
        std::vector<std::shared_ptr<Accessibility::ReadableRulesNode>> checkNodeChildren;
        return checkNodeChildren;
    }

    std::shared_ptr<Accessibility::ReadableRulesNode> GetParent() override
    {
        return nullptr;
    }

    std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren() override
    {
        std::vector<std::shared_ptr<FocusRulesCheckNode>> checkNodeChildren;
        return checkNodeChildren;
    }

    std::shared_ptr<FocusRulesCheckNode> GetAceParent() override
    {
        if (mockParentNode_) {
            return mockParentNode_;
        }
        return nullptr;
    }

    bool IsModal() override
    {
        return true;
    }

    bool IsInChildTree() override
    {
        return false;
    }

    std::shared_ptr<FocusRulesCheckNode> GetUserNextFocusNode() override
    {
        if (mockNextNode_) {
            return mockNextNode_;
        }
        return nullptr;
    }

    std::shared_ptr<FocusRulesCheckNode> GetUserPrevFocusNode() override
    {
        return nullptr;
    }
    bool IsAccessibiltyVisible() override
    {
        return false;
    }

    bool IsChildTreeContainer() override
    {
        return mockChildTreeContainer;
    }

    bool IsEmbededTarget() override
    {
        return mockIsEmbededTarget_;
    }
    std::set<std::string> mockValueArray_;
    std::shared_ptr<FocusRulesCheckNode> mockNextNode_;
    std::shared_ptr<FocusRulesCheckNode> mockParentNode_;
    bool mockChildTreeContainer = false;
    bool mockIsEmbededTarget_ = false;
private:
};
} // namespace

class AccessibilityFocusStrategyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityFocusStrategyTest::SetUpTestCase()
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

void AccessibilityFocusStrategyTest::TearDownTestCase()
{
    NG::MockPipelineContext::TearDown();
    MockContainer::TearDown();
}


/**
 * @tc.name: FindLastNodeWithoutCheck001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindLastNodeWithoutCheck001, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetActive(true, false);
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    AccessibilityFocusStrategy focusStrategy;
    // 1. get self when has no children
    focusStrategy.FindLastNodeWithoutCheck(condition, checkNode, targetNode);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(frameNode->GetAccessibilityId(), targetNode->GetAccessibilityId());
    // 2. get child when has  children
    auto frameNode1 = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode1, nullptr);
    frameNode1->SetActive(true, false);
    frameNode->AddChild(frameNode1);
    targetNode = nullptr;
    auto result = focusStrategy.FindLastNodeWithoutCheck(condition, checkNode, targetNode);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(frameNode1->GetAccessibilityId(), targetNode->GetAccessibilityId());
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    // 3. childe is childtree container
    auto accessibilityProperty1 = frameNode1->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    accessibilityProperty1->SetChildTreeId(1);
    result = focusStrategy.FindLastNodeWithoutCheck(condition, checkNode, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
}

/**
 * @tc.name: FindForwardScrollAncestor001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindForwardScrollAncestor001, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    AccessibilityFocusStrategy focusStrategy;
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode1, frameNode1->GetAccessibilityId());
    // 1. no fowardScrollAncestor
    auto result = focusStrategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    EXPECT_EQ(targetNodes.size(), 0);
    // 2. parent is fowardScrollAncestor
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetSpecificSupportActionCallback(
        [accessibilityPtr = AceType::WeakClaim(AceType::RawPtr(accessibilityProperty))]() {
        const auto& accessibilityProperty = accessibilityPtr.Upgrade();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    });
    
    result = focusStrategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    ASSERT_EQ(targetNodes.size(), 1);
    auto targetNode = targetNodes.front();
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(frameNode->GetAccessibilityId(), targetNode->GetAccessibilityId());
}

/**
 * @tc.name: FindForwardScrollAncestor001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindForwardScrollAncestor002, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    AccessibilityFocusStrategy focusStrategy;
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode1, frameNode1->GetAccessibilityId());
    // 1. parent is fowardScrollAncestor but not visiable
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetSpecificSupportActionCallback(
        [accessibilityPtr = AceType::WeakClaim(AceType::RawPtr(accessibilityProperty))]() {
        const auto& accessibilityProperty = accessibilityPtr.Upgrade();
        CHECK_NULL_VOID(accessibilityProperty);
        accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    });
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    ASSERT_NE(renderContext, nullptr);
    auto rect = std::make_shared<NG::RectF>(0.0, 0.0, 0, 0);
    renderContext->retf = rect;
    frameNode->renderContext_ = renderContext;
    auto result = focusStrategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    EXPECT_EQ(targetNodes.size(), 0);
}

/**
 * @tc.name: FindForwardScrollAncestor001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindForwardScrollAncestor003, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    AccessibilityFocusStrategy focusStrategy;
    std::list<std::shared_ptr<FocusRulesCheckNode>> targetNodes;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode1, frameNode1->GetAccessibilityId());
    // 1. parent can not GetPropActionName
    frameNode->GetOrCreateAccessibilityProperty() = nullptr;
    auto result = focusStrategy.FindForwardScrollAncestor(condition, checkNode, targetNodes);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    EXPECT_EQ(targetNodes.size(), 0);
}

/**
 * @tc.name: FindForwardScrollAncestor001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, CanAccessibilityFocus001, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);

    AccessibilityFocusStrategy focusStrategy;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    // 1. node is visible
    auto result = focusStrategy.CanAccessibilityFocus(checkNode);
    EXPECT_EQ(result, false);
    // 2. node is not visible
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    ASSERT_NE(renderContext, nullptr);
    auto rect = std::make_shared<NG::RectF>(0.0, 0.0, 0, 0);
    renderContext->retf = rect;
    frameNode->renderContext_ = renderContext;
    result = focusStrategy.CanAccessibilityFocus(checkNode);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: GetPropActionNames001
 * @tc.desc: GetPropActionNames click info
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, GetPropActionNames001, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    // 1. focushub but not focusable
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    Accessibility::PropValue value;
    auto result = checkNode->GetPropActionNames(value);
    EXPECT_EQ(result, true);
    auto findRet = value.valueArray.find("clearFocus");
    EXPECT_TRUE(findRet == value.valueArray.end());
    findRet = value.valueArray.find("focus");
    EXPECT_TRUE(findRet == value.valueArray.end());
    // 2. focushub , focusable , current focus is false
    focusHub->SetParentFocusable(true);
    focusHub->SetFocusable(true);
    focusHub->SetFocusType(NG::FocusType::NODE);
    focusHub->SetCurrentFocus(false);
    ASSERT_EQ(focusHub->IsFocusable(), true);
    ASSERT_EQ(focusHub->IsCurrentFocus(), false);
    Accessibility::PropValue value1;
    result = checkNode->GetPropActionNames(value1);
    EXPECT_EQ(result, true);
    findRet = value1.valueArray.find("clearFocus");
    EXPECT_TRUE(findRet == value1.valueArray.end());
    findRet = value1.valueArray.find("focus");
    EXPECT_TRUE(findRet != value1.valueArray.end());

    // 3. focushub , focusable , current focus is true
    focusHub->SetCurrentFocus(true);
    ASSERT_EQ(focusHub->IsCurrentFocus(), true);
    Accessibility::PropValue value2;
    result = checkNode->GetPropActionNames(value2);
    EXPECT_EQ(result, true);
    findRet = value2.valueArray.find("clearFocus");
    EXPECT_TRUE(findRet != value2.valueArray.end());
    findRet = value2.valueArray.find("focus");
    EXPECT_TRUE(findRet == value2.valueArray.end());
}

/**
 * @tc.name: GetPropActionNames001
 * @tc.desc: GetPropActionNames click info
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, GetPropActionNames002, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    // 1. eventhub but not clickable not longclick able
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    Accessibility::PropValue value;
    auto result = checkNode->GetPropActionNames(value);
    EXPECT_EQ(result, true);
    auto findRet = value.valueArray.find("click");
    EXPECT_TRUE(findRet == value.valueArray.end());
    findRet = value.valueArray.find("longClick");
    EXPECT_TRUE(findRet == value.valueArray.end());
    // 2. eventhub but  clickable and  longclick able
    auto clickCallback = [](GestureEvent& info) {
    };
    auto clickEvent = AceType::MakeRefPtr<NG::ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);
    auto longPressTask = [](GestureEvent& info) {
    };
    auto longPressEventTest = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(longPressTask));
    gestureEventHub->SetLongPressEvent(longPressEventTest);
    ASSERT_EQ(gestureEventHub->IsAccessibilityClickable(), true);
    ASSERT_EQ(gestureEventHub->IsAccessibilityLongClickable(), true);
    Accessibility::PropValue value1;
    result = checkNode->GetPropActionNames(value1);
    EXPECT_EQ(result, true);
    findRet = value1.valueArray.find("click");
    EXPECT_TRUE(findRet != value1.valueArray.end());
    findRet = value1.valueArray.find("longClick");
    EXPECT_TRUE(findRet != value1.valueArray.end());
}

/**
 * @tc.name: GetAceParent001
 * @tc.desc: get parent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, GetAceParent001, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    auto stage = NG::FrameNode::CreateFrameNode("stage", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(stage, nullptr);
    auto page = NG::FrameNode::CreateFrameNode("page", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(page, nullptr);
    auto root = NG::FrameNode::CreateFrameNode("root", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(root, nullptr);

    // bypass page and stage
    page->AddChild(frameNode);
    frameNode->MountToParent(page);
    stage->AddChild(page);
    page->MountToParent(stage);
    root->AddChild(stage);
    stage->MountToParent(root);
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    auto targetNode = checkNode->GetAceParent();
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(root->GetAccessibilityId(), targetNode->GetAccessibilityId());
}

/**
 * @tc.name: FindNextReadableNodeBySelfAndSameLevel001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindNextReadableNodeBySelfAndSameLevel001, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    MockAccessibilityFocusStrategy focusStrategy;
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = false, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode1, frameNode1->GetAccessibilityId());

    // check current and current is focus
    focusStrategy.mockCanFocus_ = true;
    auto result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());

    // check current and current is not focus , but IsChildTreeContainer
    focusStrategy.mockCanFocus_ = false;
    auto accessibilityProperty = frameNode1->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetChildTreeId(1);
    result = focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());

    // not current and current is  focus , but IsChildTreeContainer
    condition.bypassSelf = true;
    focusStrategy.mockCanFocus_ = true;
    accessibilityProperty->SetChildTreeId(1);
    result = focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());

    // not current and current is not focus , but IsChildTreeContainer
    condition.bypassSelf = true;
    focusStrategy.mockCanFocus_ = false;
    accessibilityProperty->SetChildTreeId(1);
    result = focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());
}

/**
 * @tc.name: FindNextReadableNodeBySelfAndSameLevel002
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindNextReadableNodeBySelfAndSameLevel002, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    MockAccessibilityFocusStrategy focusStrategy;
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode1, frameNode1->GetAccessibilityId());
    auto frameNode2 = CreatFrameNode();
    auto checkNode2 = std::make_shared<FrameNodeRulesCheckNode>(frameNode2, frameNode2->GetAccessibilityId());
    sameLevelNodes.emplace_back(checkNode);
    sameLevelNodes.emplace_back(checkNode2);

    // not check current and current is not ChildTreeContainer, samelevel brother is unfocusable and ChildTreeContainer
    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    accessibilityProperty2->SetChildTreeId(1);
    auto result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode2->GetAccessibilityId());

    // not check current and current is not ChildTreeContainer, samelevel brother is unfocusable and ChildTreeContainer
    // same level cannot find already checked
    sameLevelNodes.clear();
    sameLevelNodes.emplace_back(checkNode2);
    accessibilityProperty2->SetChildTreeId(1);
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: FindNextReadableNodeBySelfAndSameLevel003
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindNextReadableNodeBySelfAndSameLevel003, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    MockAccessibilityFocusStrategy focusStrategy;
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());

    // not check current and current is not ChildTreeContainer
    // children. empty,  bypass descendants， !NoNeedSearchild
    condition.bypassDescendants = true;
    focusStrategy.mockCanFocus_ = true;
    auto result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
    // children. empty,  not bypass descendants， !NoNeedSearchild
    condition.bypassDescendants = false;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    // children. empty,  bypass descendants， NoNeedSearchild
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);

    condition.bypassDescendants = true;
    focusStrategy.mockCanFocus_ = true;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
    // children. empty,  not bypass descendants， NoNeedSearchild
    condition.bypassDescendants = false;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
}

/**
 * @tc.name: FindNextReadableNodeBySelfAndSameLevel004
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindNextReadableNodeBySelfAndSameLevel004, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    MockAccessibilityFocusStrategy focusStrategy;
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());

    // not check current and current is not ChildTreeContainer
    // children not empty,  bypass descendants， !NoNeedSearchild, expect not find node
    condition.bypassDescendants = true;
    focusStrategy.mockCanFocus_ = true;
    auto result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
    // children not empty,  not bypass descendants， !NoNeedSearchild, expect not find node
    condition.bypassDescendants = false;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());
    targetNode.reset();
    // children not empty,  bypass descendants， NoNeedSearchild, expect not find node
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    condition.bypassDescendants = true;
    focusStrategy.mockCanFocus_ = true;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
    // children not empty,  not bypass descendants， NoNeedSearchild, expect not find node
    condition.bypassDescendants = false;
    result =
        focusStrategy.FindNextReadableNodeBySelfAndSameLevel(condition, checkNode, sameLevelNodes, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    ASSERT_EQ(targetNode, nullptr);
}

/**
 * @tc.name: FindPrevReadableNodeByChildAndSelf001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindPrevReadableNodeByChildAndSelf001, TestSize.Level1)
{
    auto frameNode = CreatFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = CreatFrameNode();
    ASSERT_NE(frameNode1, nullptr);
    frameNode->AddChild(frameNode1);
    frameNode1->MountToParent(frameNode);
    MockAccessibilityFocusStrategy focusStrategy;
    std::vector<std::shared_ptr<FocusRulesCheckNode>> sameLevelNodes;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition = {.bypassSelf = true, .bypassDescendants = false};
    auto checkNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    focusStrategy.mockCanFocus_ = true;
    // NoNeedSearchChild, only search and get self
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityLevel(NG::AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    auto result =
        focusStrategy.FindPrevReadableNodeByChildAndSelf(checkNode, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode->GetAccessibilityId());

    // need searchchild, can search child node
    targetNode.reset();
    accessibilityProperty->SetAccessibilityLevel(NG::AccessibilityProperty::Level::YES_STR);
    result =
        focusStrategy.FindPrevReadableNodeByChildAndSelf(checkNode, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    ASSERT_NE(targetNode, nullptr);
    EXPECT_EQ(targetNode->GetAccessibilityId(), frameNode1->GetAccessibilityId());
}

/**
 * @tc.name: AccessibilityPropertyTest020
 * @tc.desc: Test the method SetIsAccessibilityModal.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsAccessibilityModalTest001, TestSize.Level1)
{
    NG::AccessibilityProperty accessibilityProperty;
    EXPECT_FALSE(accessibilityProperty.overlayProperty_.has_value());
    // default value is true
    EXPECT_TRUE(accessibilityProperty.IsAccessibilityModal());
    accessibilityProperty.SetIsAccessibilityModal(false);
    EXPECT_FALSE(accessibilityProperty.IsAccessibilityModal());
    accessibilityProperty.SetIsAccessibilityModal(true);
    EXPECT_TRUE(accessibilityProperty.IsAccessibilityModal());
}

/**
 * @tc.name: FindPrevReadableNode001
 * @tc.desc: Test the method FindPrevReadableNode.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindPrevReadableNode001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    std::shared_ptr<FocusRulesCheckNode> checkNode1;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition;
    auto result = focusStrategy.FindPrevReadableNode(condition, checkNode1, targetNode);
    // checknode null，returns fail
    ASSERT_EQ(result, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: CheckParentEarlyStopTest001
 * @tc.desc: Test the method CheckParentEarlyStop.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, CheckParentEarlyStopTest001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    std::shared_ptr<MockFocusRulesCheckNode> parentNode1;
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition;
    // 1. parentNode nullptr, returns success
    auto result = focusStrategy.CheckParentEarlyStop(parentNode1, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    // 2. parentNode not nullptr, returns success
    std::shared_ptr<MockFocusRulesCheckNode> parentNode2 = std::make_shared<MockFocusRulesCheckNode>(0);
    result = focusStrategy.CheckParentEarlyStop(parentNode2, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_SUCCESS);
    // 3. parentNode IsChildTreeContainer, returns FIND_CHILDTREE
    parentNode2->mockChildTreeContainer = true;
    result = focusStrategy.CheckParentEarlyStop(parentNode2, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_CHILDTREE);
    // 4. parentNode IsSupportScrollBackward, returns FIND_FAIL_IN_SCROLL
    parentNode2->mockChildTreeContainer = false;
    parentNode2->mockValueArray_.insert("scrollBackward");
    result = focusStrategy.CheckParentEarlyStop(parentNode2, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_FAIL_IN_SCROLL);
}

/**
 * @tc.name: FindPrevReadableNodeToHigherLevel001
 * @tc.desc: Test the method CheckParentEarlyStop.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, FindPrevReadableNodeToHigherLevel001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    std::shared_ptr<MockFocusRulesCheckNode> parentNode = std::make_shared<MockFocusRulesCheckNode>(0);
    std::shared_ptr<MockFocusRulesCheckNode> currentNode = std::make_shared<MockFocusRulesCheckNode>(1);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    AceFocusMoveDetailCondition condition;
    ASSERT_NE(currentNode, nullptr);
    currentNode->mockParentNode_ = parentNode;
    // no focusable, need return FIND_FAIL
    auto result = focusStrategy.FindPrevReadableNodeToHigherLevel(currentNode, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_FAIL);
    // parent is embeded, need return FIND_EMBED_TARGET
    std::shared_ptr<MockFocusRulesCheckNode> parentNode1 = std::make_shared<MockFocusRulesCheckNode>(2);
    parentNode1->mockIsEmbededTarget_ = true;
    currentNode->mockParentNode_ = parentNode1;
    result = focusStrategy.FindPrevReadableNodeToHigherLevel(currentNode, targetNode);
    ASSERT_EQ(result, AceFocusMoveResult::FIND_EMBED_TARGET);
}

/**
 * @tc.name: IsFindNextReadableNode001
 * @tc.desc: Test the method IsFindNextReadableNode.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindNextReadableNode001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto currentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    auto parentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto NextResult = focusStrategy.IsFindNextReadableNode(currentNode, parentNode, targetNode);
    EXPECT_EQ(NextResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindNextReadableNode002
 * @tc.desc: Test the method IsFindNextReadableNode.
 * brotherIt != end && ++brotherIt == end.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindNextReadableNode002, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);

    auto currentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    auto frameNode2 = NG::FrameNode::CreateFrameNode("framenode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode2, nullptr);

    auto parentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode2, frameNode->GetAccessibilityId());
    ASSERT_NE(parentNode, nullptr);
    frameNode2->AddChild(frameNode);
    std::shared_ptr<FocusRulesCheckNode> targetNode;

    auto NextResult = focusStrategy.IsFindNextReadableNode(currentNode, parentNode, targetNode);
    EXPECT_EQ(NextResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindNextReadableNode003
 * @tc.desc: Test the method IsFindNextReadableNode.
 * brotherIt != end && ++brotherIt != end.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindNextReadableNode003, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);
    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());

    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    parentNode->AddChild(currentNode2);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto NextResult = focusStrategy.IsFindNextReadableNode(current1, parent, targetNode);
    EXPECT_EQ(NextResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindNextReadableNode004
 * @tc.desc: Test the method IsFindNextReadableNode.
 * (brotherIt != end) && (++brotherIt != end) && (IsHeaderFooterInScroll = true) && (IsAccessibiltyVisible = false).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindNextReadableNode004, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);

    //IsHeaderFooterInScroll = true
    auto accessibilityProperty = currentNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetIsHeaderOrFooter(true);

    //IsAccessibiltyVisible = false
    currentNode1->SetAccessibilityVisible(false);

    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());
    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    parentNode->AddChild(currentNode2);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto NextResult = focusStrategy.IsFindNextReadableNode(current1, parent, targetNode);
    EXPECT_EQ(NextResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindNextReadableNode005
 * @tc.desc: Test the method IsFindNextReadableNode.
 * (brotherIt != end) && (++brotherIt != end) && (IsHeaderFooterInScroll = false).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindNextReadableNode005, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);

    //IsHeaderFooterInScroll = false
    auto accessibilityProperty = currentNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetIsHeaderOrFooter(false);

    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());
    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    parentNode->AddChild(currentNode2);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto NextResult = focusStrategy.IsFindNextReadableNode(current1, parent, targetNode);
    EXPECT_EQ(NextResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindPrevReadableNode001
 * @tc.desc: Test the method IsFindPrevReadableNode.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindPrevReadableNode001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    auto currentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    auto parentNode = std::make_shared<FrameNodeRulesCheckNode>(frameNode, frameNode->GetAccessibilityId());
    std::shared_ptr<FocusRulesCheckNode> targetNode;

    auto prevResult = focusStrategy.IsFindPrevReadableNode(currentNode, parentNode, targetNode);
    EXPECT_EQ(prevResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindPrevReadableNode002
 * @tc.desc: Test the method IsFindPrevReadableNode.
 * (currentIt != end) && (++currentIt == rbegin).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindPrevReadableNode002, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);
    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());

    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto prevResult = focusStrategy.IsFindPrevReadableNode(current1, parent, targetNode);
    EXPECT_EQ(prevResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: IsFindPrevReadableNode003
 * @tc.desc: Test the method IsFindPrevReadableNode.
 * (currentIt != end) && (++currentIt != rbegin) && (IsHeaderFooterInScroll = true) && (IsAccessibiltyVisible = false).
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, IsFindPrevReadableNode003, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);
    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());

    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    //IsHeaderFooterInScroll = true
    auto accessibilityProperty = currentNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetIsHeaderOrFooter(true);

    //IsAccessibiltyVisible = false
    currentNode1->SetAccessibilityVisible(false);

    parentNode->AddChild(currentNode2);
    parentNode->AddChild(currentNode1);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto prevResult = focusStrategy.IsFindPrevReadableNode(current1, parent, targetNode);
    EXPECT_EQ(prevResult, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: CanScroll001
 * @tc.desc: Test the method CanScroll.
 * parentCanScroll == true.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, CanScroll001, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);

    auto accessibilityProperty = currentNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetIsHeaderOrFooter(true);
    currentNode1->SetAccessibilityVisible(true);
    EXPECT_TRUE(accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_BOTTOM);
    EXPECT_TRUE(accessibilityProperty->GetScrollableStatus() != NG::ScrollableStatus::AT_BOTH_TOP_BOTTOM);

    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());
    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    parentNode->AddChild(currentNode2);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto result = focusStrategy.IsFindNextReadableNode(current1, parent, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
}

/**
 * @tc.name: CanScroll002
 * @tc.desc: Test the method CanScroll.
 * parentCanScroll == false.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityFocusStrategyTest, CanScroll002, TestSize.Level1)
{
    MockAccessibilityFocusStrategy focusStrategy;
    auto currentNode1 = NG::FrameNode::CreateFrameNode("currentNode1", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode1, nullptr);
    auto current1 = std::make_shared<FrameNodeRulesCheckNode>(currentNode1, currentNode1->GetAccessibilityId());

    auto currentNode2 = NG::FrameNode::CreateFrameNode("currentNode2", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(currentNode2, nullptr);

    //IsHeaderFooterInScroll = true
    auto accessibilityProperty = currentNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetIsHeaderOrFooter(true);

    //IsAccessibiltyVisible = true
    currentNode1->SetAccessibilityVisible(true);

    //parentCanScroll == false
    EXPECT_FALSE(accessibilityProperty->GetScrollableStatus() == NG::ScrollableStatus::AT_BOTTOM);

    auto current2 = std::make_shared<FrameNodeRulesCheckNode>(currentNode2, currentNode2->GetAccessibilityId());
    auto parentNode = NG::FrameNode::CreateFrameNode("parentNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(parentNode, nullptr);
    auto parent = std::make_shared<FrameNodeRulesCheckNode>(parentNode, parentNode->GetAccessibilityId());

    parentNode->AddChild(currentNode1);
    parentNode->AddChild(currentNode2);
    std::shared_ptr<FocusRulesCheckNode> targetNode;
    auto result = focusStrategy.IsFindNextReadableNode(current1, parent, targetNode);
    EXPECT_EQ(result, AceFocusMoveResult::FIND_FAIL);
}

} // namespace OHOS::Ace::NG
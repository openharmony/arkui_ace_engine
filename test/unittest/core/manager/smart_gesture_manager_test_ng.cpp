/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <limits>

#include "gtest/gtest.h"

#include "core/components_ng/event/event_hub.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"
#undef private
#undef protected
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/event_manager.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/smart_gesture_property.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t TEST_INSTANCE_ID = 100;
constexpr char TEST_NODE_TAG[] = "test";
constexpr double TEST_SCROLL_DISTANCE = 96.0;
constexpr float TEST_NODE_SIZE = 100.0f;

class TestScrollablePattern : public Pattern {
    DECLARE_ACE_TYPE(TestScrollablePattern, Pattern);

public:
    bool IsScrollAble(SmartGestureDirection direction = SmartGestureDirection::FORWARD) const override
    {
        return true;
    }

    void PerformScroll(const ScrollingConfig& config) override
    {
        lastConfig_ = config;
        ++performScrollCount_;
    }

    bool ScrollToNode(const RefPtr<FrameNode>& focusFrameNode) override
    {
        ++scrollToNodeCount_;
        return scrollToNodeResult_;
    }

    int32_t GetPerformScrollCount() const
    {
        return performScrollCount_;
    }

    const std::optional<ScrollingConfig>& GetLastConfig() const
    {
        return lastConfig_;
    }

    int32_t GetScrollToNodeCount() const
    {
        return scrollToNodeCount_;
    }

    void SetScrollToNodeResult(bool result)
    {
        scrollToNodeResult_ = result;
    }

private:
    int32_t performScrollCount_ = 0;
    std::optional<ScrollingConfig> lastConfig_;
    int32_t scrollToNodeCount_ = 0;
    bool scrollToNodeResult_ = false;
};

RefPtr<FrameNode> CreateNode(const RefPtr<Pattern>& pattern)
{
    return FrameNode::CreateFrameNode(TEST_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
}

RefPtr<FrameNode> CreatePrimaryActionNode(bool enabled = true)
{
    auto node = CreateNode(AceType::MakeRefPtr<Pattern>());
    SmartGestureShortcutConfig config { SmartGestureShortcutAction::PRIMARY, enabled, false };
    node->GetOrCreateSmartGestureProperty()->SetSmartGestureShortcut(config);
    return node;
}

RefPtr<FrameNode> CreatePrimaryActionNodeWithPattern(const RefPtr<Pattern>& pattern, bool enabled = true)
{
    auto node = CreateNode(pattern);
    SmartGestureShortcutConfig config { SmartGestureShortcutAction::PRIMARY, enabled, false };
    node->GetOrCreateSmartGestureProperty()->SetSmartGestureShortcut(config);
    return node;
}

void MakeNodeActiveAndVisible(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    node->onMainTree_ = true;
    node->GetGeometryNode()->SetFrameSize(SizeF(TEST_NODE_SIZE, TEST_NODE_SIZE));
    MockPipelineContext::GetCurrent()->onShow_ = true;
}

void MakeNodeClickable(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
}

ScrollingConfig CreateDistanceScrollingConfig()
{
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    return config;
}
} // namespace

class SmartGestureManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        MockPipelineContext::GetCurrent()->SetInstanceId(TEST_INSTANCE_ID);
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        auto context = MockPipelineContext::GetCurrent();
        ASSERT_NE(context, nullptr);
        auto eventManager = context->GetEventManager();
        ASSERT_NE(eventManager, nullptr);
        eventManager->ResetSmartGestureManager();
        manager_ = eventManager->GetOrCreateSmartGestureManager();
        ASSERT_NE(manager_, nullptr);
        manager_->productGestureEnabled_ = true;
        manager_->SetSmartTapAndSlideGesturesEnabled(true);
        manager_->SetMonitor(SmartGestureManager::SmartGestureMonitor());
    }

    RefPtr<SmartGestureManager> manager_;
};

/**
 * @tc.name: SmartGestureManagerHandleTrigger001
 * @tc.desc: HandleTrigger returns false when default proposal is none action and no monitor is registered.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerHandleTrigger001, TestSize.Level1)
{
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::TAP, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: SmartGestureManagerHandleTrigger002
 * @tc.desc: HandleTrigger returns false when every registered monitor rejects the default proposal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerHandleTrigger002, TestSize.Level1)
{
    manager_->SetMonitor([](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = false;
        return resolution;
    });
    KeyEvent event(KeyCode::KEY_WRIST_TURN, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::WRIST_BACK, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: SmartGestureManagerHandleTrigger003
 * @tc.desc: HandleTrigger returns false when monitor consumes and overrides with none action proposal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerHandleTrigger003, TestSize.Level1)
{
    manager_->SetMonitor([](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        resolution.hasSelectedProposal = true;
        resolution.selectedProposal =
            SmartGestureProposal(SmartGestureProposalType::NONE_ACTION, proposal.operateIntention);
        return resolution;
    });
    KeyEvent event(KeyCode::KEY_WRIST_TURN, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::WRIST_BACK, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: SmartGestureManagerResolveProposal001
 * @tc.desc: ResolveProposal keeps the default proposal when monitor consumes without selected proposal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerResolveProposal001, TestSize.Level1)
{
    manager_->SetMonitor([](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        resolution.hasSelectedProposal = false;
        return resolution;
    });
    SmartGestureProposal defaultProposal(
        SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);

    auto proposal = manager_->ResolveProposal(defaultProposal);

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::BACK_PRESS);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::BACK_PRESS);
}

/**
 * @tc.name: SmartGestureManagerResolveProposal002
 * @tc.desc: ResolveProposal rejects monitor result when selected proposal flag has no proposal value.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerResolveProposal002, TestSize.Level1)
{
    manager_->SetMonitor([](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        resolution.hasSelectedProposal = true;
        return resolution;
    });
    SmartGestureProposal defaultProposal(
        SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);

    auto proposal = manager_->ResolveProposal(defaultProposal);

    EXPECT_FALSE(proposal.has_value());
}

/**
 * @tc.name: SmartGestureManagerBuildSlideForwardProposal001
 * @tc.desc: BuildSlideForwardProposal wraps to first clickable node when selected node is the last visible node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerBuildSlideForwardProposal001, TestSize.Level1)
{
    const auto firstNode = CreatePrimaryActionNode();
    firstNode->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    const auto secondNode = CreatePrimaryActionNode();
    secondNode->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    auto proposal = manager_->BuildSlideForwardProposal(visibleNodes, secondNode, {});

    EXPECT_EQ(proposal.type, SmartGestureProposalType::SELECT);
    EXPECT_EQ(proposal.operateIntention, SmartGestureOperateIntention::SLIDE_FORWARD);
    EXPECT_EQ(proposal.GetTargetNode(), firstNode);
}

/**
 * @tc.name: SmartGestureManagerBuildSlideForwardProposal002
 * @tc.desc: BuildSlideForwardProposal uses center-hit proposal when no visible primary node exists.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerBuildSlideForwardProposal002, TestSize.Level1)
{
    const auto scrollableNode = CreateNode(AceType::MakeRefPtr<TestScrollablePattern>());
    const std::vector<RefPtr<FrameNode>> centerHitPath { scrollableNode };

    auto proposal = manager_->BuildSlideForwardProposal({}, nullptr, centerHitPath);

    EXPECT_EQ(proposal.type, SmartGestureProposalType::NONE_ACTION);
    EXPECT_EQ(proposal.operateIntention, SmartGestureOperateIntention::SLIDE_FORWARD);
}

/**
 * @tc.name: SmartGestureManagerExecuteProposal001
 * @tc.desc: ExecuteProposal returns true and calls PerformScroll for a scroll proposal with config.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerExecuteProposal001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TestScrollablePattern>();
    const auto scrollableNode = CreateNode(pattern);
    SmartGestureProposal proposal(SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD,
        scrollableNode, CreateDistanceScrollingConfig());
    KeyEvent event(KeyCode::KEY_TAB, KeyAction::DOWN);

    auto result = manager_->ExecuteProposal(proposal, event);

    ASSERT_TRUE(result);
    EXPECT_EQ(pattern->GetPerformScrollCount(), 1);
    ASSERT_TRUE(pattern->GetLastConfig().has_value());
    ASSERT_TRUE(pattern->GetLastConfig()->distance.has_value());
    EXPECT_DOUBLE_EQ(pattern->GetLastConfig()->distance.value(), TEST_SCROLL_DISTANCE);
}

/**
 * @tc.name: SmartGestureManagerExecuteProposal002
 * @tc.desc: ExecuteProposal returns true for back press proposal even when no UIContent is attached.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerExecuteProposal002, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);
    KeyEvent event(KeyCode::KEY_WRIST_TURN, KeyAction::DOWN);

    auto result = manager_->ExecuteProposal(proposal, event);

    EXPECT_TRUE(result);
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_EmptyRegistry
 * @tc.desc: BuildVisiblePrimaryActionNodes returns empty vector when primaryActionRegistry_ is empty.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_EmptyRegistry, TestSize.Level1)
{
    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_NullContext
 * @tc.desc: BuildVisiblePrimaryActionNodes returns empty vector when pipeline context is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_NullContext, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);
    manager_->context_ = nullptr;

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_ExpiredWeakPtr
 * @tc.desc: BuildVisiblePrimaryActionNodes cleans up expired weak pointers and returns empty vector.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_ExpiredWeakPtr, TestSize.Level1)
{
    {
        auto expiredNode = CreatePrimaryActionNode();
        manager_->AddPrimaryActionNode(expiredNode);
    }

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(manager_->primaryActionRegistry_.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InactiveNode_NoSmartGestureProperty
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes without SmartGestureProperty.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InactiveNodeNoProperty, TestSize.Level1)
{
    auto node = CreateNode(AceType::MakeRefPtr<Pattern>());
    node->onMainTree_ = true;
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InactiveNode_NotEnabled
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes whose SmartGestureProperty has primary action disabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InactiveNodeNotEnabled, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode(false);
    node->onMainTree_ = true;
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InactiveNode_ContextMismatch
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes whose pipeline context does not match.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InactiveNodeContextMismatch, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);
    node->context_ = nullptr;

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InactiveNode_EventHubDisabled
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes whose event hub is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InactiveNodeEventHubDisabled, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    node->GetEventHub<NG::EventHub>()->SetEnabled(false);
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InactiveNodeNotOnMainTree
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes that are not on the main tree.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InactiveNodeNotOnMainTree, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InvisibleNode_NoGeometry
 * @tc.desc: BuildVisiblePrimaryActionNodes skips nodes whose visible rect is empty because geometry is not set.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InvisibleNodeNoGeometry, TestSize.Level1)
{
    auto parent = CreateNode(AceType::MakeRefPtr<Pattern>());
    auto node = CreatePrimaryActionNode();
    parent->AddChild(node);
    parent->onMainTree_ = true;
    node->onMainTree_ = true;
    MockPipelineContext::GetCurrent()->onShow_ = true;
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_OrderStored
 * @tc.desc: BuildVisiblePrimaryActionNodes stores order correctly in the merged registry entry.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_OrderStored, TestSize.Level1)
{
    auto firstNode = CreatePrimaryActionNode();
    auto secondNode = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(firstNode);
    manager_->AddPrimaryActionNode(secondNode);

    EXPECT_EQ(manager_->primaryActionRegistry_[firstNode->GetId()].order, 0u);
    EXPECT_EQ(manager_->primaryActionRegistry_[secondNode->GetId()].order, 1u);
}

/**
 * @tc.name: HandleTrigger_ProductGestureDisabled
 * @tc.desc: HandleTrigger returns false when product gesture is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_ProductGestureDisabled, TestSize.Level1)
{
    manager_->productGestureEnabled_ = false;
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::TAP, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleTrigger_SmartTapSlideDisabledForTap
 * @tc.desc: HandleTrigger returns false when smartTapAndSlideGesturesEnabled_ is false for TAP trigger.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_SmartTapSlideDisabledForTap, TestSize.Level1)
{
    manager_->SetSmartTapAndSlideGesturesEnabled(false);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::TAP, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleTrigger_SmartTapSlideDisabledForSlide
 * @tc.desc: HandleTrigger returns false when smartTapAndSlideGesturesEnabled_ is false for SLIDE_FORWARD.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_SmartTapSlideDisabledForSlide, TestSize.Level1)
{
    manager_->SetSmartTapAndSlideGesturesEnabled(false);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::SLIDE_FORWARD, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleTrigger_NoArgOverload
 * @tc.desc: HandleTrigger no-argument overload delegates to the key event overload.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_NoArgOverload, TestSize.Level1)
{
    auto result = manager_->HandleTrigger(SmartGestureTrigger::TAP);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ResolveProposal_MonitorOverride
 * @tc.desc: ResolveProposal returns the monitor's selected proposal when it overrides with a valid proposal.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ResolveProposal_MonitorOverride, TestSize.Level1)
{
    SmartGestureProposal overrideProposal(
        SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);
    manager_->SetMonitor([&overrideProposal](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        resolution.hasSelectedProposal = true;
        resolution.selectedProposal = overrideProposal;
        return resolution;
    });
    SmartGestureProposal defaultProposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);

    auto proposal = manager_->ResolveProposal(defaultProposal);

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::BACK_PRESS);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::BACK_PRESS);
}

/**
 * @tc.name: ResolveProposal_InvalidDefaultProposal
 * @tc.desc: ResolveProposal returns nullopt when the default proposal fails validation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ResolveProposal_InvalidDefaultProposal, TestSize.Level1)
{
    SmartGestureProposal defaultProposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, nullptr);

    auto proposal = manager_->ResolveProposal(defaultProposal);

    EXPECT_FALSE(proposal.has_value());
}

/**
 * @tc.name: ResolveProposal_MonitorOverrideInvalid
 * @tc.desc: ResolveProposal returns nullopt when the monitor's override proposal fails validation.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ResolveProposal_MonitorOverrideInvalid, TestSize.Level1)
{
    manager_->SetMonitor([](const SmartGestureProposal& proposal) {
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        resolution.hasSelectedProposal = true;
        resolution.selectedProposal =
            SmartGestureProposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, nullptr);
        return resolution;
    });
    SmartGestureProposal defaultProposal(
        SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);

    auto proposal = manager_->ResolveProposal(defaultProposal);

    EXPECT_FALSE(proposal.has_value());
}

/**
 * @tc.name: ExecuteProposal_NoneAction
 * @tc.desc: ExecuteProposal returns false for NONE_ACTION type.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteProposal_NoneAction, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->ExecuteProposal(proposal, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ExecuteSelectProposal_ActiveClickableNode
 * @tc.desc: ExecuteSelectProposal updates selected node when target node is active and clickable.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteSelectProposal_ActiveClickableNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->ExecuteSelectProposal(node);

    ASSERT_TRUE(result);
    ASSERT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: ExecuteSelectProposal_NotClickable
 * @tc.desc: ExecuteSelectProposal returns false and does not select node when target node is not clickable.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteSelectProposal_NotClickable, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->ExecuteSelectProposal(node);

    EXPECT_FALSE(result);
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: ExecuteSelectProposal_InactiveNode
 * @tc.desc: ExecuteSelectProposal returns false and does not select node when target node is not active.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteSelectProposal_InactiveNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode(false);
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->ExecuteSelectProposal(node);

    EXPECT_FALSE(result);
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: ExecuteClickProposal_NullSelectedNode
 * @tc.desc: ExecuteClickProposal establishes selection when no node is currently selected.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteClickProposal_NullSelectedNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    manager_->AddPrimaryActionNode(node);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->ExecuteClickProposal(node, event);

    EXPECT_TRUE(result);
    EXPECT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: ExecuteClickProposal_DifferentSelectedNode
 * @tc.desc: ExecuteClickProposal returns false when a different node is already selected.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteClickProposal_DifferentSelectedNode, TestSize.Level1)
{
    auto existingSelected = CreatePrimaryActionNode();
    existingSelected->onMainTree_ = true;
    existingSelected->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    manager_->AddPrimaryActionNode(existingSelected);
    manager_->selectedNode_ = existingSelected;

    auto targetNode = CreatePrimaryActionNode();
    targetNode->onMainTree_ = true;
    targetNode->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    manager_->AddPrimaryActionNode(targetNode);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);
    auto result = manager_->ExecuteClickProposal(targetNode, event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SyncPrimaryActionNode_AddWhenEnabled
 * @tc.desc: SyncPrimaryActionNode adds node to registry when SmartGestureProperty has primary action enabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SyncPrimaryActionNode_AddWhenEnabled, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->SyncPrimaryActionNode(node);
    ASSERT_EQ(manager_->primaryActionRegistry_.size(), 1u);
    EXPECT_NE(manager_->primaryActionRegistry_.find(node->GetId()), manager_->primaryActionRegistry_.end());
}

/**
 * @tc.name: SyncPrimaryActionNode_RemoveWhenDisabled
 * @tc.desc: SyncPrimaryActionNode removes node from registry when SmartGestureProperty does not enable primary action.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SyncPrimaryActionNode_RemoveWhenDisabled, TestSize.Level1)
{
    auto node = CreateNode(AceType::MakeRefPtr<Pattern>());
    manager_->AddPrimaryActionNode(node);
    manager_->SyncPrimaryActionNode(node);
    EXPECT_TRUE(manager_->primaryActionRegistry_.empty());
}

/**
 * @tc.name: RemovePrimaryActionNode_ClearsSelected
 * @tc.desc: RemovePrimaryActionNode clears the selected node when it matches the removed node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RemovePrimaryActionNode_ClearsSelected, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    manager_->RemovePrimaryActionNode(node->GetId());
    EXPECT_TRUE(manager_->primaryActionRegistry_.empty());
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RemovePrimaryActionNode_SelectedNotCleared
 * @tc.desc: RemovePrimaryActionNode does not clear selected node when it does not match the removed node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RemovePrimaryActionNode_SelectedNotCleared, TestSize.Level1)
{
    auto selectedNode = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(selectedNode);
    manager_->selectedNode_ = selectedNode;

    auto otherNode = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(otherNode);
    manager_->RemovePrimaryActionNode(otherNode->GetId());

    EXPECT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), selectedNode->GetId());
}

/**
 * @tc.name: RefreshSelectedNodeState_ClearsInvalid
 * @tc.desc: RefreshSelectedNodeState clears selected node when it is no longer valid.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RefreshSelectedNodeState_ClearsInvalid, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    node->onMainTree_ = false;
    manager_->RefreshSelectedNodeState();

    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: ValidateProposal_ClickWithNullNode
 * @tc.desc: ValidateProposal returns false for CLICK type when the target node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ClickWithNullNode, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithNegativeCount
 * @tc.desc: ValidateProposal returns false for SCROLL type when scrolling count is negative.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithNegativeCount, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.count = -1;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);

    auto result = manager_->ValidateProposal(proposal);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithNegativeDistance
 * @tc.desc: ValidateProposal returns false for SCROLL type when scrolling distance is negative.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithNegativeDistance, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = -1.0;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);

    auto result = manager_->ValidateProposal(proposal);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithInfiniteDistance
 * @tc.desc: ValidateProposal returns false for SCROLL type when scrolling distance is infinite.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithInfiniteDistance, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = std::numeric_limits<double>::infinity();
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);

    auto result = manager_->ValidateProposal(proposal);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithNanDistance
 * @tc.desc: ValidateProposal returns false for SCROLL type when scrolling distance is NaN.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithNanDistance, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = std::numeric_limits<double>::quiet_NaN();
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);

    auto result = manager_->ValidateProposal(proposal);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithZeroCountAndDistance
 * @tc.desc: ValidateProposal returns true for SCROLL type when count and distance are zero.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithZeroCountAndDistance, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.count = 0;
    config.distance = 0.0;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClearSelected
 * @tc.desc: ClearSelected resets the selected node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ClearSelected, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    manager_->ClearSelected();
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: BuildCenterHitPath_NullContext
 * @tc.desc: BuildCenterHitPath returns empty vector when pipeline context is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildCenterHitPath_NullContext, TestSize.Level1)
{
    manager_->context_ = nullptr;
    auto result = manager_->BuildCenterHitPath();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildCenterHitPath_EmptyRootRect
 * @tc.desc: BuildCenterHitPath returns empty vector when root node has no geometry rect.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildCenterHitPath_EmptyRootRect, TestSize.Level1)
{
    auto result = manager_->BuildCenterHitPath();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildSelectedAncestorPath_NullNode
 * @tc.desc: BuildSelectedAncestorPath returns empty vector when input node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSelectedAncestorPath_NullNode, TestSize.Level1)
{
    auto result = manager_->BuildSelectedAncestorPath(nullptr);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: BuildSelectedAncestorPath_NoAncestor
 * @tc.desc: BuildSelectedAncestorPath returns empty vector when node has no scrollable ancestor.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSelectedAncestorPath_NoAncestor, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    auto result = manager_->BuildSelectedAncestorPath(node);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_NonScrollableParent
 * @tc.desc: RevealSelectedNodeIfNeeded does nothing when node parent is not scrollable.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_NonScrollableParent, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    manager_->RevealSelectedNodeIfNeeded(node);
    EXPECT_FALSE(node->IsActive());
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_ScrollableParentSuccess
 * @tc.desc: RevealSelectedNodeIfNeeded calls ScrollToNode when parent has a scrollable pattern.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_ScrollableParentSuccess, TestSize.Level1)
{
    auto scrollablePattern = AceType::MakeRefPtr<TestScrollablePattern>();
    scrollablePattern->SetScrollToNodeResult(true);
    auto parent = CreateNode(scrollablePattern);
    auto node = CreatePrimaryActionNode();
    parent->AddChild(node);
    MakeNodeActiveAndVisible(parent);
    MakeNodeActiveAndVisible(node);
    manager_->RevealSelectedNodeIfNeeded(node);
    EXPECT_GT(scrollablePattern->GetScrollToNodeCount(), 0);
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_ListItemTagNode
 * @tc.desc: RevealSelectedNodeIfNeeded calls ScrollToNode on the scrollable parent when node is a ListItem.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_ListItemTagNode, TestSize.Level1)
{
    auto listItemNode = FrameNode::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto scrollablePattern = AceType::MakeRefPtr<TestScrollablePattern>();
    auto parent = CreateNode(scrollablePattern);
    parent->AddChild(listItemNode);
    MakeNodeActiveAndVisible(parent);
    MakeNodeActiveAndVisible(listItemNode);
    manager_->RevealSelectedNodeIfNeeded(listItemNode);
    EXPECT_EQ(scrollablePattern->GetScrollToNodeCount(), 1);
}

/**
 * @tc.name: PaintSelectedNode_NullNode
 * @tc.desc: PaintSelectedNode does not update selectedPaintedNode when node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_NullNode, TestSize.Level1)
{
    manager_->PaintSelectedNode(nullptr);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PaintSelectedNode_NullRenderContext
 * @tc.desc: PaintSelectedNode does not update selectedPaintedNode when node's renderContext is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_NullRenderContext, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    node->renderContext_ = nullptr;
    manager_->PaintSelectedNode(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PaintSelectedNode_NullAppTheme
 * @tc.desc: PaintSelectedNode does not update selectedPaintedNode when theme manager returns null AppTheme.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_NullAppTheme, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    manager_->PaintSelectedNode(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PaintSelectedNode_FocusHubPath
 * @tc.desc: PaintSelectedNode sets focus emphasis on focusHub path when node has a valid focusHub.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_FocusHubPath, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    auto context = MockPipelineContext::GetCurrent();
    auto mockThemeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*mockThemeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));
    context->themeManager_ = mockThemeManager;
    manager_->PaintSelectedNode(node);
    EXPECT_NE(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PaintSelectedNode_RenderContextDirectPath
 * @tc.desc: PaintSelectedNode sets emphasis directly on renderContext when node has no focusHub.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_RenderContextDirectPath, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    node->focusHub_ = nullptr;
    auto context = MockPipelineContext::GetCurrent();
    auto mockThemeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*mockThemeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));
    context->themeManager_ = mockThemeManager;
    manager_->PaintSelectedNode(node);
    EXPECT_NE(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: DispatchSmartGestureClick_SelectThenClick
 * @tc.desc: ExecuteClickProposal selects node and triggers click callback when node matches selectedNode.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, DispatchSmartGestureClick_SelectThenClick, TestSize.Level1)
{
    bool clickCalled = false;
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([&clickCalled](GestureEvent&) { clickCalled = true; });
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->ExecuteClickProposal(node, event);

    EXPECT_TRUE(result);
    EXPECT_TRUE(clickCalled);
}

/**
 * @tc.name: DispatchSmartGestureClick_NullGeometryNode
 * @tc.desc: ExecuteClickProposal returns false when node's geometryNode is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, DispatchSmartGestureClick_NullGeometryNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    node->geometryNode_ = nullptr;
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->ExecuteClickProposal(node, event);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: RequestSelected_NullContext
 * @tc.desc: RequestSelected does not select any node when pipeline context is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RequestSelected_NullContext, TestSize.Level1)
{
    manager_->context_ = nullptr;
    manager_->RequestSelected("test_id");
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RequestSelected_NodeNotFound
 * @tc.desc: RequestSelected does not select any node when inspectorId is not found in registry.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RequestSelected_NodeNotFound, TestSize.Level1)
{
    manager_->RequestSelected("nonexistent_id");
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RequestSelected_NodeNotActive
 * @tc.desc: RequestSelected does not select node when primary action is not enabled on it.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RequestSelected_NodeNotActive, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode(false);
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    node->UpdateInspectorId("test_not_active");
    manager_->RequestSelected("test_not_active");
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RequestSelected_NodeNotClickable
 * @tc.desc: RequestSelected does not select node when it has no clickable event hub.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RequestSelected_NodeNotClickable, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    node->UpdateInspectorId("test_not_clickable");
    manager_->AddPrimaryActionNode(node);
    manager_->RequestSelected("test_not_clickable");
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RequestSelected_Valid
 * @tc.desc: RequestSelected selects node when it is active, clickable, and found by inspectorId.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RequestSelected_Valid, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    node->UpdateInspectorId("test_valid_id");
    manager_->AddPrimaryActionNode(node);

    manager_->RequestSelected("test_valid_id");

    EXPECT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: UpdateSelectedNodePaintIfNeeded_NullNode
 * @tc.desc: UpdateSelectedNodePaintIfNeeded does not clear selectedNode when input node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, UpdateSelectedNodePaintIfNeeded_NullNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->selectedNode_ = node;
    manager_->UpdateSelectedNodePaintIfNeeded(nullptr);
    EXPECT_NE(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: UpdateSelectedNodePaintIfNeeded_NullSelectedNode
 * @tc.desc: UpdateSelectedNodePaintIfNeeded does nothing when selectedNode weak ptr is already null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, UpdateSelectedNodePaintIfNeeded_NullSelectedNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->UpdateSelectedNodePaintIfNeeded(node);
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: UpdateSelectedNodePaintIfNeeded_DifferentNode
 * @tc.desc: UpdateSelectedNodePaintIfNeeded clears painted node when input differs from selectedNode.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, UpdateSelectedNodePaintIfNeeded_DifferentNode, TestSize.Level1)
{
    auto selectedNode = CreatePrimaryActionNode();
    auto otherNode = CreatePrimaryActionNode();
    manager_->selectedNode_ = selectedNode;
    manager_->UpdateSelectedNodePaintIfNeeded(otherNode);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), selectedNode->GetId());
}

/**
 * @tc.name: UpdateSelectedNodePaintIfNeeded_SameNode
 * @tc.desc: UpdateSelectedNodePaintIfNeeded paints node when input matches selectedNode and node is valid.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, UpdateSelectedNodePaintIfNeeded_SameNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    manager_->selectedNode_ = node;
    SmartGestureShortcutConfig selectableConfig { SmartGestureShortcutAction::PRIMARY, true, true };
    node->GetOrCreateSmartGestureProperty()->SetSmartGestureShortcut(selectableConfig);
    manager_->UpdateSelectedNodePaintIfNeeded(node);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: ValidateProposal_NoneAction
 * @tc.desc: ValidateProposal returns true for NONE_ACTION proposal type.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_NoneAction, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::NONE_ACTION, SmartGestureOperateIntention::TAP);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ValidateProposal_BackPress
 * @tc.desc: ValidateProposal returns true for BACK_PRESS proposal type.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_BackPress, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::BACK_PRESS, SmartGestureOperateIntention::BACK_PRESS);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ValidateProposal_SelectWithNullNode
 * @tc.desc: ValidateProposal returns false for SELECT type when target node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_SelectWithNullNode, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ClickWithValidNode
 * @tc.desc: ValidateProposal returns true for CLICK type with a valid, active, clickable node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ClickWithValidNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, node);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_SelectWithValidNode
 * @tc.desc: ValidateProposal returns true for SELECT type with a valid, active, clickable node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_SelectWithValidNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, node);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateProposal_ScrollWithValidConfig
 * @tc.desc: ValidateProposal returns true for SCROLL type with valid scrolling config and scrollable pattern.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ScrollWithValidConfig, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTargetNode_NullNode
 * @tc.desc: ValidateTargetNode returns false when input node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_NullNode, TestSize.Level1)
{
    auto result = manager_->ValidateTargetNode(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTargetNode_NullContext
 * @tc.desc: ValidateTargetNode returns false when pipeline context does not match node's context.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_NullContext, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->context_ = nullptr;
    auto result = manager_->ValidateTargetNode(node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTargetNode_NotOnMainTree
 * @tc.desc: ValidateTargetNode returns false when node is not on the main tree.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_NotOnMainTree, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    auto result = manager_->ValidateTargetNode(node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTargetNode_NotVisible
 * @tc.desc: ValidateTargetNode returns false when node has no visible rect.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_NotVisible, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    auto result = manager_->ValidateTargetNode(node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTargetNode_ValidNode
 * @tc.desc: ValidateTargetNode returns true when node is active, on main tree, and visible.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_ValidNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    manager_->AddPrimaryActionNode(node);
    auto result = manager_->ValidateTargetNode(node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateClickProposal_NullNode
 * @tc.desc: ValidateClickProposal returns false when proposal target node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateClickProposal_NullNode, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP);
    auto result = manager_->ValidateClickProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateClickProposal_NotActive
 * @tc.desc: ValidateClickProposal returns false when node's primary action is not enabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateClickProposal_NotActive, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode(false);
    MakeNodeActiveAndVisible(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, node);
    auto result = manager_->ValidateClickProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateClickProposal_NotClickable
 * @tc.desc: ValidateClickProposal returns false when node has no clickable event hub.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateClickProposal_NotClickable, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, node);
    auto result = manager_->ValidateClickProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateClickProposal_Valid
 * @tc.desc: ValidateClickProposal returns true when node is active, clickable, and on main tree.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateClickProposal_Valid, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, node);
    auto result = manager_->ValidateClickProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateSelectProposal_NullNode
 * @tc.desc: ValidateSelectProposal returns false when proposal target node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateSelectProposal_NullNode, TestSize.Level1)
{
    SmartGestureProposal proposal(SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD);
    auto result = manager_->ValidateSelectProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateSelectProposal_NotActive
 * @tc.desc: ValidateSelectProposal returns false when node's primary action is not enabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateSelectProposal_NotActive, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode(false);
    MakeNodeActiveAndVisible(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, node);
    auto result = manager_->ValidateSelectProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateSelectProposal_NotClickable
 * @tc.desc: ValidateSelectProposal returns false when node has no clickable event hub.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateSelectProposal_NotClickable, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, node);
    auto result = manager_->ValidateSelectProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateSelectProposal_Valid
 * @tc.desc: ValidateSelectProposal returns true when node is active, clickable, and on main tree.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateSelectProposal_Valid, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, node);
    auto result = manager_->ValidateSelectProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_NullNode
 * @tc.desc: ValidateScrollProposal returns false when proposal target node is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_NullNode, TestSize.Level1)
{
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, nullptr, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_NoScrollingConfig
 * @tc.desc: ValidateScrollProposal returns false when proposal has no scrollingConfig.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_NoScrollingConfig, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_EmptyScrollingConfig
 * @tc.desc: ValidateScrollProposal returns false when scrollingConfig has zero count and distance.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_EmptyScrollingConfig, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_NoPattern
 * @tc.desc: ValidateScrollProposal returns false when node has no scrollable pattern.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_NoPattern, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_NotScrollablePattern
 * @tc.desc: ValidateScrollProposal returns false when node's pattern is not a ScrollablePattern.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_NotScrollablePattern, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<Pattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_ValidWithCount
 * @tc.desc: ValidateScrollProposal returns true when scrollingConfig has valid count.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_ValidWithCount, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.count = 3;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_ValidWithDistance
 * @tc.desc: ValidateScrollProposal returns true when scrollingConfig has valid distance.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_ValidWithDistance, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateScrollProposal_ValidWithBoth
 * @tc.desc: ValidateScrollProposal returns true when scrollingConfig has both valid count and distance.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateScrollProposal_ValidWithBoth, TestSize.Level1)
{
    auto node = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeActiveAndVisible(node);
    ScrollingConfig config;
    config.count = 3;
    config.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal proposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, node, config);
    auto result = manager_->ValidateScrollProposal(proposal);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG

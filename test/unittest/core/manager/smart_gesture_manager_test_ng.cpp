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
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
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

class TestUINode : public UINode {
    DECLARE_ACE_TYPE(TestUINode, UINode);

public:
    explicit TestUINode(int32_t nodeId) : UINode("TestUINode", nodeId) {}
    ~TestUINode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }
};

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

class TestConfigurableScrollablePattern : public TestScrollablePattern {
    DECLARE_ACE_TYPE(TestConfigurableScrollablePattern, TestScrollablePattern);

public:
    std::optional<ScrollingConfig> GetDefaultScrollingConfig(
        SmartGestureDirection direction = SmartGestureDirection::FORWARD) const override
    {
        return defaultConfig_;
    }

    void SetDefaultScrollingConfig(const ScrollingConfig& config)
    {
        defaultConfig_ = config;
    }

private:
    std::optional<ScrollingConfig> defaultConfig_;
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

    void MakeNodeFullyActiveAndVisible(
        const RefPtr<FrameNode>& node, const RectF& rect = RectF(0.0f, 0.0f, TEST_NODE_SIZE, TEST_NODE_SIZE))
    {
        ASSERT_NE(node, nullptr);
        node->onMainTree_ = true;
        node->SetActive(true);
        node->GetGeometryNode()->SetFrameOffset(rect.GetOffset());
        node->GetGeometryNode()->SetFrameSize(rect.GetSize());
        auto renderContext = AceType::DynamicCast<MockRenderContext>(node->GetRenderContext());
        ASSERT_NE(renderContext, nullptr);
        renderContext->SetPaintRectWithTransform(rect);

        auto parent = node->GetParentFrameNode();
        if (!parent) {
            parent = CreateNode(AceType::MakeRefPtr<Pattern>());
            parent->AddChild(node);
            visibleParents_.emplace_back(parent);
        }
        parent->onMainTree_ = true;
        parent->SetActive(true);
        parent->GetGeometryNode()->SetFrameSize(SizeF(TEST_NODE_SIZE * 10.0f, TEST_NODE_SIZE * 10.0f));
        auto parentRenderContext = AceType::DynamicCast<MockRenderContext>(parent->GetRenderContext());
        ASSERT_NE(parentRenderContext, nullptr);
        parentRenderContext->SetPaintRectWithTransform(
            RectF(0.0f, 0.0f, TEST_NODE_SIZE * 10.0f, TEST_NODE_SIZE * 10.0f));
        MockPipelineContext::GetCurrent()->onShow_ = true;
    }

    RefPtr<SmartGestureManager> manager_;
    std::vector<RefPtr<FrameNode>> visibleParents_;
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
 * @tc.name: RefreshSelectedNodeState_ClearsInvisibleActiveNode
 * @tc.desc: RefreshSelectedNodeState checks visibility after the selected node passes its active-state checks.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RefreshSelectedNodeState_ClearsInvisibleActiveNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    manager_->selectedNode_ = node;

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
 * @tc.name: BuildCenterHitPath_NullRootNode
 * @tc.desc: BuildCenterHitPath returns empty vector when the pipeline has no root node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildCenterHitPath_NullRootNode, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto rootNode = context->rootNode_;
    context->rootNode_.Reset();

    auto result = manager_->BuildCenterHitPath();

    EXPECT_TRUE(result.empty());
    context->rootNode_ = rootNode;
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
 * @tc.name: PaintSelectedNode_FocusHubFallsBack
 * @tc.desc: PaintSelectedNode falls back from a present focus hub when the focus hub cannot paint.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PaintSelectedNode_FocusHubFallsBack, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeActiveAndVisible(node);
    ASSERT_NE(node->GetOrCreateFocusHub(), nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto themeManager = context->themeManager_;
    auto mockThemeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*mockThemeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(nullptr));
    context->themeManager_ = mockThemeManager;

    manager_->PaintSelectedNode(node);

    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
    context->themeManager_ = themeManager;
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

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_VisibleNodesSorted
 * @tc.desc: BuildVisiblePrimaryActionNodes keeps visible nodes and orders layers and registration ties.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_VisibleNodesSorted, TestSize.Level1)
{
    auto rightTopNode = CreatePrimaryActionNode();
    auto leftTopNode = CreatePrimaryActionNode();
    auto firstBottomNode = CreatePrimaryActionNode();
    auto secondBottomNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(rightTopNode, RectF(100.0f, 0.0f, 20.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(leftTopNode, RectF(0.0f, 0.0f, 20.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(firstBottomNode, RectF(0.0f, 50.0f, 20.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(secondBottomNode, RectF(0.0f, 50.0f, 20.0f, 20.0f));
    manager_->AddPrimaryActionNode(rightTopNode);
    manager_->AddPrimaryActionNode(leftTopNode);
    manager_->AddPrimaryActionNode(firstBottomNode);
    manager_->AddPrimaryActionNode(secondBottomNode);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], leftTopNode);
    EXPECT_EQ(result[1], rightTopNode);
    EXPECT_EQ(result[2], firstBottomNode);
    EXPECT_EQ(result[3], secondBottomNode);
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_DistanceAndHorizontalTieBreakers
 * @tc.desc: Nodes in one layer use center distance and absolute horizontal distance as ordering tie-breakers.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_DistanceAndHorizontalTieBreakers, TestSize.Level1)
{
    auto baseNode = CreatePrimaryActionNode();
    auto horizontalNode = CreatePrimaryActionNode();
    auto verticalNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(baseNode, RectF(0.0f, 0.0f, 200.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(horizontalNode, RectF(100.5f, 9.5f, 1.0f, 1.0f));
    MakeNodeFullyActiveAndVisible(verticalNode, RectF(99.5f, 10.5f, 1.0f, 1.0f));
    manager_->AddPrimaryActionNode(baseNode);
    manager_->AddPrimaryActionNode(horizontalNode);
    manager_->AddPrimaryActionNode(verticalNode);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], baseNode);
    EXPECT_EQ(result[1], verticalNode);
    EXPECT_EQ(result[2], horizontalNode);
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_VerticalDistanceTieBreaker
 * @tc.desc: Near-equal center distances and horizontal offsets fall through to the vertical-distance tie-breaker.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_VerticalDistanceTieBreaker, TestSize.Level1)
{
    auto baseNode = CreatePrimaryActionNode();
    auto horizontalNode = CreatePrimaryActionNode();
    auto slightlyVerticalNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(baseNode, RectF(0.0f, 0.0f, 200.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(horizontalNode, RectF(100.5f, 9.5f, 1.0f, 1.0f));
    MakeNodeFullyActiveAndVisible(slightlyVerticalNode, RectF(98.5f, 9.502f, 1.0f, 1.0f));
    manager_->AddPrimaryActionNode(baseNode);
    manager_->AddPrimaryActionNode(horizontalNode);
    manager_->AddPrimaryActionNode(slightlyVerticalNode);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], baseNode);
    EXPECT_EQ(result[1], horizontalNode);
    EXPECT_EQ(result[2], slightlyVerticalNode);
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_LeftAndTopTieBreakers
 * @tc.desc: Identical centers fall through to left-edge and top-edge ordering tie-breakers.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_LeftAndTopTieBreakers, TestSize.Level1)
{
    auto wideNode = CreatePrimaryActionNode();
    auto narrowNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(wideNode, RectF(10.0f, 20.0f, 40.0f, 20.0f));
    MakeNodeFullyActiveAndVisible(narrowNode, RectF(20.0f, 20.0f, 20.0f, 20.0f));
    manager_->AddPrimaryActionNode(wideNode);
    manager_->AddPrimaryActionNode(narrowNode);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], wideNode);
    EXPECT_EQ(result[1], narrowNode);

    manager_->primaryActionRegistry_.clear();
    auto tallNode = CreatePrimaryActionNode();
    auto shortNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(tallNode, RectF(20.0f, 10.0f, 20.0f, 40.0f));
    MakeNodeFullyActiveAndVisible(shortNode, RectF(20.0f, 20.0f, 20.0f, 20.0f));
    manager_->AddPrimaryActionNode(tallNode);
    manager_->AddPrimaryActionNode(shortNode);

    result = manager_->BuildVisiblePrimaryActionNodes();

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], tallNode);
    EXPECT_EQ(result[1], shortNode);
}

/**
 * @tc.name: AddPrimaryActionNode_ReaddSelectedNode
 * @tc.desc: Re-adding a selected node preserves its registration order and refreshes selected paint.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, AddPrimaryActionNode_ReaddSelectedNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    manager_->AddPrimaryActionNode(node);
    auto originalOrder = manager_->primaryActionRegistry_[node->GetId()].order;
    manager_->selectedNode_ = node;

    manager_->AddPrimaryActionNode(node);

    EXPECT_EQ(manager_->primaryActionRegistry_.size(), 1u);
    EXPECT_EQ(manager_->primaryActionRegistry_[node->GetId()].order, originalOrder);
    EXPECT_EQ(manager_->nextPrimaryActionOrder_, 1u);
}

/**
 * @tc.name: AddPrimaryActionNode_DifferentSelectedNode
 * @tc.desc: Adding a node different from the current selection does not synchronize selected paint.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, AddPrimaryActionNode_DifferentSelectedNode, TestSize.Level1)
{
    auto selectedNode = CreatePrimaryActionNode();
    auto addedNode = CreatePrimaryActionNode();
    manager_->selectedNode_ = selectedNode;

    manager_->AddPrimaryActionNode(addedNode);

    ASSERT_EQ(manager_->primaryActionRegistry_.size(), 1u);
    EXPECT_NE(manager_->primaryActionRegistry_.find(addedNode->GetId()), manager_->primaryActionRegistry_.end());
    EXPECT_EQ(manager_->selectedNode_.Upgrade(), selectedNode);
}

/**
 * @tc.name: BuildSlideForwardProposal_NextVisibleNode
 * @tc.desc: BuildSlideForwardProposal selects the next clickable node after the current selection.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSlideForwardProposal_NextVisibleNode, TestSize.Level1)
{
    auto firstNode = CreatePrimaryActionNode();
    auto secondNode = CreatePrimaryActionNode();
    MakeNodeClickable(firstNode);
    MakeNodeClickable(secondNode);

    auto proposal = manager_->BuildSlideForwardProposal({ firstNode, secondNode }, firstNode, {});

    EXPECT_EQ(proposal.type, SmartGestureProposalType::SELECT);
    EXPECT_EQ(proposal.GetTargetNode(), secondNode);
}

/**
 * @tc.name: BuildSlideForwardProposal_SelectedAncestorScroll
 * @tc.desc: BuildSlideForwardProposal scrolls a selected node's scrollable ancestor before wrapping selection.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSlideForwardProposal_SelectedAncestorScroll, TestSize.Level1)
{
    auto scrollablePattern = AceType::MakeRefPtr<TestConfigurableScrollablePattern>();
    scrollablePattern->SetDefaultScrollingConfig(CreateDistanceScrollingConfig());
    auto scrollableParent = CreateNode(scrollablePattern);
    auto selectedNode = CreatePrimaryActionNode();
    MakeNodeClickable(selectedNode);
    scrollableParent->AddChild(selectedNode);

    auto proposal = manager_->BuildSlideForwardProposal({ selectedNode }, selectedNode, {});

    EXPECT_EQ(proposal.type, SmartGestureProposalType::SCROLL);
    EXPECT_EQ(proposal.GetTargetNode(), scrollableParent);
    ASSERT_TRUE(proposal.scrollingConfig.has_value());
}

/**
 * @tc.name: BuildSlideForwardProposal_NoClickableVisibleNode
 * @tc.desc: BuildSlideForwardProposal returns none action when visible nodes contain no clickable target.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSlideForwardProposal_NoClickableVisibleNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();

    auto proposal = manager_->BuildSlideForwardProposal({ node }, node, {});

    EXPECT_EQ(proposal.type, SmartGestureProposalType::NONE_ACTION);
}

/**
 * @tc.name: BuildSlideForwardProposal_CenterHitScroll
 * @tc.desc: BuildSlideForwardProposal returns a scroll proposal from the center-hit path when no primary node exists.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSlideForwardProposal_CenterHitScroll, TestSize.Level1)
{
    auto scrollablePattern = AceType::MakeRefPtr<TestConfigurableScrollablePattern>();
    scrollablePattern->SetDefaultScrollingConfig(CreateDistanceScrollingConfig());
    auto scrollableNode = CreateNode(scrollablePattern);

    auto proposal = manager_->BuildSlideForwardProposal({}, nullptr, { scrollableNode });

    EXPECT_EQ(proposal.type, SmartGestureProposalType::SCROLL);
    EXPECT_EQ(proposal.GetTargetNode(), scrollableNode);
}

/**
 * @tc.name: HandleTrigger_TapSelectsVisibleNode
 * @tc.desc: HandleTrigger executes the default select proposal for a visible clickable primary node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_TapSelectsVisibleNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::TAP, event);

    EXPECT_TRUE(result);
    ASSERT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: HandleTrigger_WristBackIgnoresTapSlideSwitch
 * @tc.desc: WRIST_BACK remains enabled when tap and slide smart gestures are disabled.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_WristBackIgnoresTapSlideSwitch, TestSize.Level1)
{
    manager_->SetSmartTapAndSlideGesturesEnabled(false);
    KeyEvent event(KeyCode::KEY_WRIST_TURN, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::WRIST_BACK, event);

    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleTrigger_SlideSelectsVisibleNode
 * @tc.desc: SLIDE_FORWARD builds the center path and selects the first visible clickable node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_SlideSelectsVisibleNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(node);
    MakeNodeClickable(node);
    manager_->AddPrimaryActionNode(node);
    KeyEvent event(KeyCode::KEY_TAB, KeyAction::DOWN);

    auto result = manager_->HandleTrigger(SmartGestureTrigger::SLIDE_FORWARD, event);

    EXPECT_TRUE(result);
    ASSERT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: BuildSelectedAncestorPath_MultipleAncestors
 * @tc.desc: BuildSelectedAncestorPath returns every frame ancestor from nearest to farthest.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildSelectedAncestorPath_MultipleAncestors, TestSize.Level1)
{
    auto grandParent = CreateNode(AceType::MakeRefPtr<Pattern>());
    auto parent = CreateNode(AceType::MakeRefPtr<Pattern>());
    auto node = CreatePrimaryActionNode();
    grandParent->AddChild(parent);
    parent->AddChild(node);

    auto result = manager_->BuildSelectedAncestorPath(node);

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], parent);
    EXPECT_EQ(result[1], grandParent);
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_ContinuesToScrollableGrandparent
 * @tc.desc: RevealSelectedNodeIfNeeded continues after a parent declines ScrollToNode.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_ContinuesToScrollableGrandparent, TestSize.Level1)
{
    auto grandParentPattern = AceType::MakeRefPtr<TestScrollablePattern>();
    grandParentPattern->SetScrollToNodeResult(true);
    auto parentPattern = AceType::MakeRefPtr<TestScrollablePattern>();
    parentPattern->SetScrollToNodeResult(false);
    auto grandParent = CreateNode(grandParentPattern);
    auto parent = CreateNode(parentPattern);
    auto node = CreatePrimaryActionNode();
    grandParent->AddChild(parent);
    parent->AddChild(node);

    manager_->RevealSelectedNodeIfNeeded(node);

    EXPECT_EQ(parentPattern->GetScrollToNodeCount(), 1);
    EXPECT_EQ(grandParentPattern->GetScrollToNodeCount(), 1);
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_SkipsNonFrameParent
 * @tc.desc: RevealSelectedNodeIfNeeded skips a non-FrameNode parent and continues to a scrollable ancestor.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_SkipsNonFrameParent, TestSize.Level1)
{
    auto scrollablePattern = AceType::MakeRefPtr<TestScrollablePattern>();
    scrollablePattern->SetScrollToNodeResult(true);
    auto scrollableAncestor = CreateNode(scrollablePattern);
    auto nonFrameParent = AceType::MakeRefPtr<TestUINode>(ElementRegister::GetInstance()->MakeUniqueId());
    auto node = CreatePrimaryActionNode();
    scrollableAncestor->AddChild(nonFrameParent);
    nonFrameParent->AddChild(node);

    manager_->RevealSelectedNodeIfNeeded(node);

    EXPECT_EQ(scrollablePattern->GetScrollToNodeCount(), 1);
}

/**
 * @tc.name: RevealSelectedNodeIfNeeded_OtherListItemTags
 * @tc.desc: ListItemGroup and ArcListItem nodes are used as reveal anchors.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RevealSelectedNodeIfNeeded_OtherListItemTags, TestSize.Level1)
{
    const std::vector<std::string> tags { V2::LIST_ITEM_GROUP_ETS_TAG, V2::ARC_LIST_ITEM_ETS_TAG };
    for (const auto& tag : tags) {
        auto pattern = AceType::MakeRefPtr<TestScrollablePattern>();
        auto parent = CreateNode(pattern);
        auto item = FrameNode::CreateFrameNode(
            tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        parent->AddChild(item);

        manager_->RevealSelectedNodeIfNeeded(item);

        EXPECT_EQ(pattern->GetScrollToNodeCount(), 1);
    }
}

/**
 * @tc.name: ClearSelectedNodePaint_AllGuardsAndSuccess
 * @tc.desc: ClearSelectedNodePaint covers null, mismatch, null render context, and successful clear paths.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ClearSelectedNodePaint_AllGuardsAndSuccess, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    auto otherNode = CreatePrimaryActionNode();
    manager_->ClearSelectedNodePaint(nullptr);
    manager_->ClearSelectedNodePaint(node);

    manager_->selectedPaintedNode_ = otherNode;
    manager_->ClearSelectedNodePaint(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), otherNode);

    auto renderContext = node->renderContext_;
    manager_->selectedPaintedNode_ = node;
    node->renderContext_ = nullptr;
    manager_->ClearSelectedNodePaint(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), node);

    node->renderContext_ = renderContext;
    manager_->ClearSelectedNodePaint(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RefreshSelectedNodeState_KeepsValidNode
 * @tc.desc: RefreshSelectedNodeState preserves an active and visible selected node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RefreshSelectedNodeState_KeepsValidNode, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(node);
    manager_->selectedNode_ = node;

    manager_->RefreshSelectedNodeState();

    ASSERT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), node->GetId());
}

/**
 * @tc.name: Proposal_InvalidEnumValue
 * @tc.desc: Proposal validation and execution reject unknown proposal enum values.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, Proposal_InvalidEnumValue, TestSize.Level1)
{
    SmartGestureProposal proposal(static_cast<SmartGestureProposalType>(-1), SmartGestureOperateIntention::TAP);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);

    EXPECT_FALSE(manager_->ValidateProposal(proposal));
    EXPECT_FALSE(manager_->ExecuteProposal(proposal, event));
}

/**
 * @tc.name: ExecuteProposal_SelectAndClickCases
 * @tc.desc: ExecuteProposal dispatches SELECT and CLICK switch cases.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteProposal_SelectAndClickCases, TestSize.Level1)
{
    bool clickCalled = false;
    auto node = CreatePrimaryActionNode();
    node->onMainTree_ = true;
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([&clickCalled](GestureEvent&) { clickCalled = true; });
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);
    SmartGestureProposal selectProposal(SmartGestureProposalType::SELECT, SmartGestureOperateIntention::TAP, node);
    SmartGestureProposal clickProposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, node);

    EXPECT_TRUE(manager_->ExecuteProposal(selectProposal, event));
    EXPECT_TRUE(manager_->ExecuteProposal(clickProposal, event));
    EXPECT_TRUE(clickCalled);
}

/**
 * @tc.name: ExecuteSelectAndClickProposal_GuardBranches
 * @tc.desc: Execute select and click proposals reject null, inactive, and non-clickable nodes.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteSelectAndClickProposal_GuardBranches, TestSize.Level1)
{
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_FALSE(manager_->ExecuteSelectProposal(nullptr));
    EXPECT_FALSE(manager_->ExecuteClickProposal(nullptr, event));

    auto inactiveNode = CreatePrimaryActionNode(false);
    inactiveNode->onMainTree_ = true;
    MakeNodeClickable(inactiveNode);
    EXPECT_FALSE(manager_->ExecuteClickProposal(inactiveNode, event));

    auto nonClickableNode = CreatePrimaryActionNode();
    nonClickableNode->onMainTree_ = true;
    EXPECT_FALSE(manager_->ExecuteClickProposal(nonClickableNode, event));

    auto noEventHubNode = CreatePrimaryActionNode();
    noEventHubNode->onMainTree_ = true;
    noEventHubNode->eventHub_ = nullptr;
    EXPECT_FALSE(manager_->ExecuteSelectProposal(noEventHubNode));
}

/**
 * @tc.name: ExecuteBackPressProposal_NullContext
 * @tc.desc: ExecuteBackPressProposal returns before querying UIContent when the pipeline context expired.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ExecuteBackPressProposal_NullContext, TestSize.Level1)
{
    manager_->context_ = nullptr;
    manager_->ExecuteBackPressProposal();
    EXPECT_EQ(manager_->GetPipelineContext(), nullptr);
}

/**
 * @tc.name: PrimaryActionStateHelpers_AllBranches
 * @tc.desc: Primary action helper methods cover null, context, event hub, property, visibility, and selectability
 * branches.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, PrimaryActionStateHelpers_AllBranches, TestSize.Level1)
{
    EXPECT_FALSE(manager_->IsPrimaryActionNodeActive(nullptr));
    EXPECT_FALSE(manager_->IsPrimaryActionNodeVisible(nullptr));
    EXPECT_FALSE(manager_->IsPrimaryActionNodeSelectable(nullptr));

    auto noPropertyNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    noPropertyNode->onMainTree_ = true;
    EXPECT_FALSE(manager_->IsPrimaryActionNodeActive(noPropertyNode));
    EXPECT_FALSE(manager_->IsPrimaryActionNodeSelectable(noPropertyNode));

    auto enabledNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(enabledNode);
    enabledNode->eventHub_ = nullptr;
    EXPECT_TRUE(manager_->IsPrimaryActionNodeActive(enabledNode));
    EXPECT_TRUE(manager_->IsPrimaryActionNodeVisible(enabledNode));
    EXPECT_FALSE(manager_->IsPrimaryActionNodeSelectable(enabledNode));

    SmartGestureShortcutConfig selectableConfig { SmartGestureShortcutAction::PRIMARY, true, true };
    enabledNode->GetOrCreateSmartGestureProperty()->SetSmartGestureShortcut(selectableConfig);
    EXPECT_TRUE(manager_->IsPrimaryActionNodeSelectable(enabledNode));

    manager_->context_ = nullptr;
    EXPECT_FALSE(manager_->IsPrimaryActionNodeActive(enabledNode));
    EXPECT_FALSE(manager_->IsPrimaryActionNodeVisible(enabledNode));
}

/**
 * @tc.name: HandleTrigger_InvalidTriggerFallback
 * @tc.desc: An unknown trigger exits without a monitor and uses a none-action fallback with a monitor.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, HandleTrigger_InvalidTriggerFallback, TestSize.Level1)
{
    auto invalidTrigger = static_cast<SmartGestureTrigger>(-1);
    KeyEvent event(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_FALSE(manager_->HandleTrigger(invalidTrigger, event));

    bool monitorCalled = false;
    manager_->SetMonitor([&monitorCalled](const SmartGestureProposal& proposal) {
        monitorCalled = true;
        EXPECT_EQ(proposal.type, SmartGestureProposalType::NONE_ACTION);
        EXPECT_EQ(proposal.operateIntention, SmartGestureOperateIntention::TAP);
        SmartGestureHandlingResolution resolution;
        resolution.isConsumed = true;
        return resolution;
    });

    EXPECT_FALSE(manager_->HandleTrigger(invalidTrigger, event));
    EXPECT_TRUE(monitorCalled);
}

/**
 * @tc.name: BuildVisiblePrimaryActionNodes_InvalidVisibleRect
 * @tc.desc: BuildVisiblePrimaryActionNodes skips a node whose visible rectangle is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, BuildVisiblePrimaryActionNodes_InvalidVisibleRect, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(node, RectF(0.0f, 0.0f, -1.0f, TEST_NODE_SIZE));
    manager_->AddPrimaryActionNode(node);

    auto result = manager_->BuildVisiblePrimaryActionNodes();

    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: RegistryAndSelectedNode_NullAndReplacementBranches
 * @tc.desc: Registry methods accept null defensively and UpdateSelectedNode replaces a previous selection.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, RegistryAndSelectedNode_NullAndReplacementBranches, TestSize.Level1)
{
    manager_->SyncPrimaryActionNode(nullptr);
    manager_->AddPrimaryActionNode(nullptr);
    EXPECT_TRUE(manager_->primaryActionRegistry_.empty());

    auto firstNode = CreatePrimaryActionNode();
    auto secondNode = CreatePrimaryActionNode();
    manager_->UpdateSelectedNode(firstNode);
    ASSERT_EQ(manager_->selectedNode_.Upgrade(), firstNode);

    manager_->UpdateSelectedNode(secondNode);

    ASSERT_NE(manager_->selectedNode_.Upgrade(), nullptr);
    EXPECT_EQ(manager_->selectedNode_.Upgrade()->GetId(), secondNode->GetId());
}

/**
 * @tc.name: SelectedNodePaint_NullContextAndSelectableBranches
 * @tc.desc: Selected paint helpers cover null input, missing context, selectable, and non-selectable paths.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SelectedNodePaint_NullContextAndSelectableBranches, TestSize.Level1)
{
    manager_->SyncSelectedNodePaint(nullptr);

    auto node = CreatePrimaryActionNode();
    node->focusHub_ = nullptr;
    auto context = manager_->context_;
    manager_->context_ = nullptr;
    manager_->PaintSelectedNode(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
    manager_->context_ = context;

    manager_->selectedPaintedNode_ = node;
    manager_->SyncSelectedNodePaint(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);

    SmartGestureShortcutConfig selectableConfig { SmartGestureShortcutAction::PRIMARY, true, true };
    node->GetOrCreateSmartGestureProperty()->SetSmartGestureShortcut(selectableConfig);
    manager_->context_ = nullptr;
    manager_->SyncSelectedNodePaint(node);
    EXPECT_EQ(manager_->selectedPaintedNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: ValidateTargetNode_ContextMismatch
 * @tc.desc: ValidateTargetNode rejects a node attached to a different pipeline context.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateTargetNode_ContextMismatch, TestSize.Level1)
{
    auto node = CreatePrimaryActionNode();
    node->context_ = nullptr;

    EXPECT_FALSE(manager_->ValidateTargetNode(node));
}

/**
 * @tc.name: ValidateProposal_ReachableTrueBranches
 * @tc.desc: Validate target, click, select, and scroll proposals with independently prepared visible nodes.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, ValidateProposal_ReachableTrueBranches, TestSize.Level1)
{
    auto actionNode = CreatePrimaryActionNode();
    MakeNodeFullyActiveAndVisible(actionNode);
    MakeNodeClickable(actionNode);
    SmartGestureProposal clickProposal(SmartGestureProposalType::CLICK, SmartGestureOperateIntention::TAP, actionNode);
    SmartGestureProposal selectProposal(
        SmartGestureProposalType::SELECT, SmartGestureOperateIntention::SLIDE_FORWARD, actionNode);

    EXPECT_TRUE(manager_->ValidateTargetNode(actionNode));
    EXPECT_TRUE(manager_->ValidateClickProposal(clickProposal));
    EXPECT_TRUE(manager_->ValidateSelectProposal(selectProposal));
    EXPECT_TRUE(manager_->ValidateProposal(clickProposal));
    EXPECT_TRUE(manager_->ValidateProposal(selectProposal));

    auto scrollNode = CreatePrimaryActionNodeWithPattern(AceType::MakeRefPtr<TestScrollablePattern>());
    MakeNodeFullyActiveAndVisible(scrollNode);

    ScrollingConfig zeroConfig;
    zeroConfig.count = 0;
    zeroConfig.distance = 0.0;
    SmartGestureProposal zeroProposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, scrollNode, zeroConfig);
    EXPECT_TRUE(manager_->ValidateProposal(zeroProposal));

    ScrollingConfig countConfig;
    countConfig.count = 3;
    SmartGestureProposal countProposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, scrollNode, countConfig);
    EXPECT_TRUE(manager_->ValidateScrollProposal(countProposal));

    ScrollingConfig distanceConfig;
    distanceConfig.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal distanceProposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, scrollNode, distanceConfig);
    EXPECT_TRUE(manager_->ValidateScrollProposal(distanceProposal));

    ScrollingConfig fullConfig;
    fullConfig.count = 3;
    fullConfig.distance = TEST_SCROLL_DISTANCE;
    SmartGestureProposal fullProposal(
        SmartGestureProposalType::SCROLL, SmartGestureOperateIntention::SLIDE_FORWARD, scrollNode, fullConfig);
    EXPECT_TRUE(manager_->ValidateScrollProposal(fullProposal));
}

} // namespace OHOS::Ace::NG

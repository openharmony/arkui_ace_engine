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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/manager/smart_gesture/smart_gesture_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#undef private
#undef protected
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/event_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t TEST_INSTANCE_ID = 100;
constexpr char TEST_NODE_TAG[] = "test";
constexpr double TEST_SCROLL_DISTANCE = 96.0;

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

    int32_t GetPerformScrollCount() const
    {
        return performScrollCount_;
    }

    const std::optional<ScrollingConfig>& GetLastConfig() const
    {
        return lastConfig_;
    }

private:
    int32_t performScrollCount_ = 0;
    std::optional<ScrollingConfig> lastConfig_;
};

RefPtr<FrameNode> CreateNode(const RefPtr<Pattern>& pattern)
{
    return FrameNode::CreateFrameNode(TEST_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
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
 * @tc.desc: BuildSlideForwardProposal wraps to first visible node when selected node is the last visible node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureManagerTestNg, SmartGestureManagerBuildSlideForwardProposal001, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
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
} // namespace OHOS::Ace::NG

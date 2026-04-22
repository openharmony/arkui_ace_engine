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

#include <optional>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/manager/smart_gesture/smart_gesture_decider.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/base/element_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr char TEST_NODE_TAG[] = "test";
constexpr int32_t TEST_SCROLL_COUNT = 3;

class TestScrollablePattern : public Pattern {
    DECLARE_ACE_TYPE(TestScrollablePattern, Pattern);

public:
    TestScrollablePattern(bool scrollable, std::optional<ScrollingConfig> config)
        : scrollable_(scrollable), config_(std::move(config))
    {}

    bool IsScrollAble(SmartGestureDirection direction = SmartGestureDirection::FORWARD) const override
    {
        return scrollable_;
    }

    std::optional<ScrollingConfig> GetDefaultScrollingConfig(
        SmartGestureDirection direction = SmartGestureDirection::FORWARD) const override
    {
        return config_;
    }

private:
    bool scrollable_ = false;
    std::optional<ScrollingConfig> config_;
};

ScrollingConfig CreateScrollingConfig()
{
    ScrollingConfig config;
    config.count = TEST_SCROLL_COUNT;
    return config;
}

RefPtr<FrameNode> CreateNode(const RefPtr<Pattern>& pattern)
{
    return FrameNode::CreateFrameNode(TEST_NODE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
}

RefPtr<FrameNode> CreateClickableNode()
{
    auto node = CreateNode(AceType::MakeRefPtr<Pattern>());
    node->GetOrCreateGestureEventHub()->SetCommonClickEvent([](GestureEvent&) {});
    return node;
}

RefPtr<FrameNode> CreateScrollableNode(bool scrollable, std::optional<ScrollingConfig> config)
{
    return CreateNode(AceType::MakeRefPtr<TestScrollablePattern>(scrollable, std::move(config)));
}
} // namespace

class SmartGestureDeciderTestNg : public testing::Test {};

/**
 * @tc.name: SmartGestureDeciderGetFirstVisiblePrimaryNode001
 * @tc.desc: GetFirstVisiblePrimaryNode returns nullptr for an empty visible list.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetFirstVisiblePrimaryNode001, TestSize.Level1)
{
    const std::vector<RefPtr<FrameNode>> visibleNodes;

    EXPECT_EQ(SmartGestureDecider::GetFirstVisiblePrimaryNode(visibleNodes), nullptr);
}

/**
 * @tc.name: SmartGestureDeciderGetFirstVisiblePrimaryNode002
 * @tc.desc: GetFirstVisiblePrimaryNode returns the first node in a non-empty visible list.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetFirstVisiblePrimaryNode002, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    EXPECT_EQ(SmartGestureDecider::GetFirstVisiblePrimaryNode(visibleNodes), firstNode);
}

/**
 * @tc.name: SmartGestureDeciderGetNextVisiblePrimaryNode001
 * @tc.desc: GetNextVisiblePrimaryNode returns the first node when no node is selected.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetNextVisiblePrimaryNode001, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    EXPECT_EQ(SmartGestureDecider::GetNextVisiblePrimaryNode(visibleNodes, nullptr), firstNode);
}

/**
 * @tc.name: SmartGestureDeciderGetNextVisiblePrimaryNode002
 * @tc.desc: GetNextVisiblePrimaryNode returns the next node after the selected node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetNextVisiblePrimaryNode002, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto thirdNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode, thirdNode };

    EXPECT_EQ(SmartGestureDecider::GetNextVisiblePrimaryNode(visibleNodes, secondNode), thirdNode);
}

/**
 * @tc.name: SmartGestureDeciderGetNextVisiblePrimaryNode003
 * @tc.desc: GetNextVisiblePrimaryNode falls back to the first node when selection is not visible.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetNextVisiblePrimaryNode003, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto selectedNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    EXPECT_EQ(SmartGestureDecider::GetNextVisiblePrimaryNode(visibleNodes, selectedNode), firstNode);
}

/**
 * @tc.name: SmartGestureDeciderGetNextVisiblePrimaryNode004
 * @tc.desc: GetNextVisiblePrimaryNode returns nullptr when the selected node is the last visible node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderGetNextVisiblePrimaryNode004, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    EXPECT_EQ(SmartGestureDecider::GetNextVisiblePrimaryNode(visibleNodes, secondNode), nullptr);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal001
 * @tc.desc: BuildDefaultProposal returns click for tap on a clickable selected node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal001, TestSize.Level1)
{
    const auto clickableNode = CreateClickableNode();
    const std::vector<RefPtr<FrameNode>> visibleNodes { clickableNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(
        SmartGestureTrigger::TAP, visibleNodes, clickableNode, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::CLICK);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::TAP);
    EXPECT_EQ(proposal->GetTargetNode(), clickableNode);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal004
 * @tc.desc: BuildDefaultProposal returns none action for tap when no visible node exists.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal004, TestSize.Level1)
{
    auto proposal = SmartGestureDecider::BuildDefaultProposal(SmartGestureTrigger::TAP, {}, nullptr, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::NONE_ACTION);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::TAP);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal002
 * @tc.desc: BuildDefaultProposal selects the first visible node for tap without a selection.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal002, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(SmartGestureTrigger::TAP, visibleNodes, nullptr, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::SELECT);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::TAP);
    EXPECT_EQ(proposal->GetTargetNode(), firstNode);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal005
 * @tc.desc: BuildDefaultProposal returns none action for tap when the selected node is not clickable.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal005, TestSize.Level1)
{
    const auto selectedNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { selectedNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(
        SmartGestureTrigger::TAP, visibleNodes, selectedNode, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::NONE_ACTION);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::TAP);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal008
 * @tc.desc: BuildDefaultProposal returns none action when slide forward has no next visible node.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal008, TestSize.Level1)
{
    const auto onlyNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { onlyNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(
        SmartGestureTrigger::SLIDE_FORWARD, visibleNodes, onlyNode, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::NONE_ACTION);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::SLIDE_FORWARD);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal006
 * @tc.desc: BuildDefaultProposal selects the next visible node for slide forward.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal006, TestSize.Level1)
{
    const auto firstNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto secondNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const std::vector<RefPtr<FrameNode>> visibleNodes { firstNode, secondNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(
        SmartGestureTrigger::SLIDE_FORWARD, visibleNodes, firstNode, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::SELECT);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::SLIDE_FORWARD);
    EXPECT_EQ(proposal->GetTargetNode(), secondNode);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal007
 * @tc.desc: BuildDefaultProposal falls back to center-hit scroll proposal for slide forward.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal007, TestSize.Level1)
{
    const auto scrollableNode = CreateScrollableNode(true, CreateScrollingConfig());
    const std::vector<RefPtr<FrameNode>> centerHitPath { scrollableNode };

    auto proposal = SmartGestureDecider::BuildDefaultProposal(
        SmartGestureTrigger::SLIDE_FORWARD, {}, nullptr, centerHitPath);

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::SCROLL);
    EXPECT_EQ(proposal->GetTargetNode(), scrollableNode);
}

/**
 * @tc.name: SmartGestureDeciderBuildCenterHitProposal001
 * @tc.desc: BuildCenterHitProposal skips invalid nodes and returns the first scrollable hit.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildCenterHitProposal001, TestSize.Level1)
{
    const auto nonScrollableNode = CreateNode(AceType::MakeRefPtr<Pattern>());
    const auto scrollableNode = CreateScrollableNode(true, CreateScrollingConfig());
    const std::vector<RefPtr<FrameNode>> centerHitPath { nullptr, nonScrollableNode, scrollableNode };

    auto proposal = SmartGestureDecider::BuildCenterHitProposal(centerHitPath);

    ASSERT_TRUE(proposal.has_value());
    ASSERT_TRUE(proposal->scrollingConfig.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::SCROLL);
    EXPECT_EQ(proposal->GetTargetNode(), scrollableNode);
    EXPECT_EQ(proposal->scrollingConfig->count.value(), TEST_SCROLL_COUNT);
}

/**
 * @tc.name: SmartGestureDeciderBuildCenterHitProposal002
 * @tc.desc: BuildCenterHitProposal returns none action when no hit node exposes a usable scroll config.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildCenterHitProposal002, TestSize.Level1)
{
    ScrollingConfig emptyConfig;
    const auto invalidScrollableNode = CreateScrollableNode(true, emptyConfig);
    const std::vector<RefPtr<FrameNode>> centerHitPath { invalidScrollableNode };

    auto proposal = SmartGestureDecider::BuildCenterHitProposal(centerHitPath);

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::NONE_ACTION);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::SLIDE_FORWARD);
}

/**
 * @tc.name: SmartGestureDeciderBuildDefaultProposal003
 * @tc.desc: BuildDefaultProposal returns back press for wrist back.
 * @tc.type: FUNC
 */
HWTEST_F(SmartGestureDeciderTestNg, SmartGestureDeciderBuildDefaultProposal003, TestSize.Level1)
{
    auto proposal = SmartGestureDecider::BuildDefaultProposal(SmartGestureTrigger::WRIST_BACK, {}, nullptr, {});

    ASSERT_TRUE(proposal.has_value());
    EXPECT_EQ(proposal->type, SmartGestureProposalType::BACK_PRESS);
    EXPECT_EQ(proposal->operateIntention, SmartGestureOperateIntention::BACK_PRESS);
    EXPECT_EQ(proposal->GetTargetNode(), nullptr);
}
} // namespace OHOS::Ace::NG

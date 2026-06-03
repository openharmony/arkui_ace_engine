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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/accessibility/accessibility_manager.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

class JsAccessibilityManagerDetachFocusTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<Framework::JsAccessibilityManager> manager_;
};

void JsAccessibilityManagerDetachFocusTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void JsAccessibilityManagerDetachFocusTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void JsAccessibilityManagerDetachFocusTest::SetUp()
{
    manager_ = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(manager_, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    manager_->SetPipelineContext(context);
    manager_->Register(true);
}

void JsAccessibilityManagerDetachFocusTest::TearDown()
{
    manager_ = nullptr;
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest001
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns true for PAGE_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest001, TestSize.Level1)
{
    EXPECT_TRUE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::PAGE_CHANGE));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest002
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns true for CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest002, TestSize.Level1)
{
    EXPECT_TRUE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::CHANGE));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest003
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns true for PAGE_OPEN
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest003, TestSize.Level1)
{
    EXPECT_TRUE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::PAGE_OPEN));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest004
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns true for PAGE_CLOSE
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest004, TestSize.Level1)
{
    EXPECT_TRUE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::PAGE_CLOSE));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest005
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns false for SCROLLING_EVENT when no focus node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest005, TestSize.Level1)
{
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::SCROLLING_EVENT));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest006
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns false for SCROLL_END when no focus node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest006, TestSize.Level1)
{
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::SCROLL_END));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest007
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns false for SCROLL_START when no focus node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest007, TestSize.Level1)
{
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::SCROLL_START));
}

/**
 * @tc.name: IsDetachFocusCacheClearEventTest008
 * @tc.desc: Test IsDetachFocusCacheClearEvent returns false for non-clear events
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, IsDetachFocusCacheClearEventTest008, TestSize.Level1)
{
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::CLICK));
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::LONG_PRESS));
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::FOCUS));
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::TEXT_CHANGE));
    EXPECT_FALSE(manager_->IsDetachFocusCacheClearEvent(AccessibilityEventType::ACCESSIBILITY_FOCUSED));
}

/**
 * @tc.name: ClearDetachFocusFallbackCacheTest001
 * @tc.desc: Test ClearDetachFocusFallbackCache removes existing cache entry
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, ClearDetachFocusFallbackCacheTest001, TestSize.Level1)
{
    int32_t instanceId = 100;
    int64_t focusNodeId = 50;
    std::vector<int64_t> ids = { 1, 2, 3 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids);

    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_EQ(result.candidateIds.size(), 3U);

    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids);
    manager_->ClearDetachFocusFallbackCache(instanceId);
    result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: ClearDetachFocusFallbackCacheTest002
 * @tc.desc: Test ClearDetachFocusFallbackCache on non-existent instanceId does not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, ClearDetachFocusFallbackCacheTest002, TestSize.Level1)
{
    int32_t instanceId = 999;
    manager_->ClearDetachFocusFallbackCache(instanceId);
    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: CacheDetachFocusFallbackCandidatesTest001
 * @tc.desc: Test CacheDetachFocusFallbackCandidates stores candidates correctly
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, CacheDetachFocusFallbackCandidatesTest001, TestSize.Level1)
{
    int32_t instanceId = 200;
    int64_t focusNodeId = 55;
    std::vector<int64_t> ids = { 10, 20, 30 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids);

    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    ASSERT_EQ(result.candidateIds.size(), 3U);
    EXPECT_EQ(result.focusNodeId, focusNodeId);
    EXPECT_EQ(result.candidateIds[0], 10);
    EXPECT_EQ(result.candidateIds[1], 20);
    EXPECT_EQ(result.candidateIds[2], 30);
}

/**
 * @tc.name: CacheDetachFocusFallbackCandidatesTest002
 * @tc.desc: Test CacheDetachFocusFallbackCandidates with empty vector clears cache
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, CacheDetachFocusFallbackCandidatesTest002, TestSize.Level1)
{
    int32_t instanceId = 201;
    int64_t focusNodeId = 55;
    std::vector<int64_t> ids = { 10, 20, 30 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids);

    std::vector<int64_t> emptyIds;
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, emptyIds);

    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: CacheDetachFocusFallbackCandidatesTest003
 * @tc.desc: Test CacheDetachFocusFallbackCandidates overwrites existing cache
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, CacheDetachFocusFallbackCandidatesTest003, TestSize.Level1)
{
    int32_t instanceId = 202;
    int64_t focusNodeId = 55;
    std::vector<int64_t> ids1 = { 1, 2, 3 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids1);

    std::vector<int64_t> ids2 = { 4, 5 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids2);

    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    ASSERT_EQ(result.candidateIds.size(), 2U);
    EXPECT_EQ(result.candidateIds[0], 4);
    EXPECT_EQ(result.candidateIds[1], 5);
}

/**
 * @tc.name: GetAndClearDetachFocusFallbackCandidatesTest001
 * @tc.desc: Test GetAndClear returns empty for non-existent instanceId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, GetAndClearDetachFocusFallbackCandidatesTest001, TestSize.Level1)
{
    int32_t instanceId = 300;
    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: GetAndClearDetachFocusFallbackCandidatesTest002
 * @tc.desc: Test GetAndClear clears cache after retrieval
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, GetAndClearDetachFocusFallbackCandidatesTest002, TestSize.Level1)
{
    int32_t instanceId = 301;
    int64_t focusNodeId = 60;
    std::vector<int64_t> ids = { 100, 200 };
    manager_->CacheDetachFocusFallbackCandidates(instanceId, focusNodeId, ids);

    auto result1 = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    ASSERT_EQ(result1.candidateIds.size(), 2U);

    auto result2 = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result2.candidateIds.empty());
}

/**
 * @tc.name: GetAndClearDetachFocusFallbackCandidatesTest003
 * @tc.desc: Test GetAndClear for different instanceIds are isolated
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, GetAndClearDetachFocusFallbackCandidatesTest003, TestSize.Level1)
{
    int32_t id1 = 400;
    int32_t id2 = 401;
    int64_t focusNodeId = 70;
    std::vector<int64_t> ids1 = { 1 };
    std::vector<int64_t> ids2 = { 2, 3 };
    manager_->CacheDetachFocusFallbackCandidates(id1, focusNodeId, ids1);
    manager_->CacheDetachFocusFallbackCandidates(id2, focusNodeId, ids2);

    auto result1 = manager_->GetAndClearDetachFocusFallbackCandidates(id1);
    ASSERT_EQ(result1.candidateIds.size(), 1U);
    EXPECT_EQ(result1.candidateIds[0], 1);

    auto result2 = manager_->GetAndClearDetachFocusFallbackCandidates(id2);
    ASSERT_EQ(result2.candidateIds.size(), 2U);
    EXPECT_EQ(result2.candidateIds[0], 2);
    EXPECT_EQ(result2.candidateIds[1], 3);
}

/**
 * @tc.name: SendRequestFocusToCandidateTest001
 * @tc.desc: Test SendRequestFocusToCandidate returns false for null node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, SendRequestFocusToCandidateTest001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> nullNode = nullptr;
    EXPECT_FALSE(manager_->SendRequestFocusToCandidate(nullNode));
}

/**
 * @tc.name: SendRequestFocusToCandidateTest002
 * @tc.desc: Test SendRequestFocusToCandidate returns false for node with negative elementId
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, SendRequestFocusToCandidateTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(manager_->SendRequestFocusToCandidate(frameNode));
}

/**
 * @tc.name: FindCandidateByFocusMoveTest001
 * @tc.desc: Test FindCandidateByFocusMove returns nullptr for null node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, FindCandidateByFocusMoveTest001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> nullNode = nullptr;
    auto result = manager_->FindCandidateByFocusMove(nullNode, FocusMoveDirection::FORWARD);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: QueryDetachFocusFallbackCandidatesTest001
 * @tc.desc: Test QueryDetachFocusFallbackCandidates returns empty for null focusNode
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, QueryDetachFocusFallbackCandidatesTest001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    RefPtr<NG::FrameNode> nullNode = nullptr;
    auto result = manager_->QueryDetachFocusFallbackCandidates(nullNode, context, 3);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: QueryDetachFocusFallbackCandidatesTest002
 * @tc.desc: Test QueryDetachFocusFallbackCandidates returns empty for null context
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, QueryDetachFocusFallbackCandidatesTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 100, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NG::PipelineContext> nullContext = nullptr;
    auto result = manager_->QueryDetachFocusFallbackCandidates(frameNode, nullContext, 3);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: HandleDetachFocusFallbackCallbackTest001
 * @tc.desc: Test HandleDetachFocusFallbackCallback with empty cache does not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, HandleDetachFocusFallbackCallbackTest001, TestSize.Level1)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(true));

    int32_t instanceId = 500;
    manager_->HandleDetachFocusFallbackCallback(instanceId);
    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: NotifyAccessibilityFocusDetachOrInvisibleTest001
 * @tc.desc: Test NotifyAccessibilityFocusDetachOrInvisible with null node does not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, NotifyAccessibilityFocusDetachOrInvisibleTest001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> nullNode = nullptr;
    manager_->currentFocusNodeId_ = 99999;
    manager_->NotifyAccessibilityFocusDetachOrInvisible(nullNode);
    EXPECT_EQ(manager_->currentFocusNodeId_, 99999);
}

/**
 * @tc.name: OnAccessbibilityDetachFromMainTreeTest001
 * @tc.desc: Test OnAccessbibilityDetachFromMainTree with null node does not crash
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, OnAccessbibilityDetachFromMainTreeTest001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> nullNode = nullptr;
    manager_->currentFocusNodeId_ = 99999;
    manager_->OnAccessbibilityDetachFromMainTree(nullNode);
    EXPECT_EQ(manager_->currentFocusNodeId_, 99999);
}

/**
 * @tc.name: OnAccessbibilityDetachFromMainTreeTest002
 * @tc.desc: Test OnAccessbibilityDetachFromMainTree with non-focused node returns early
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, OnAccessbibilityDetachFromMainTreeTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 600, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    manager_->currentFocusNodeId_ = 99999;
    manager_->OnAccessbibilityDetachFromMainTree(frameNode);
    EXPECT_EQ(manager_->currentFocusNodeId_, 99999);
}

/**
 * @tc.name: OnAccessbibilityDetachFromMainTreeTest003
 * @tc.desc: Test OnAccessbibilityDetachFromMainTree clears focus state on matched node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, OnAccessbibilityDetachFromMainTreeTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 700, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    int64_t nodeId = frameNode->GetAccessibilityId();
    manager_->currentFocusNodeId_ = nodeId;
    manager_->OnAccessbibilityDetachFromMainTree(frameNode);
    EXPECT_EQ(manager_->currentFocusNodeId_, -1);
    EXPECT_EQ(manager_->currentFocusVirtualNodeParentId_, -1);
}

/**
 * @tc.name: FireAccessibilityEventCallbackDetachFocusTest001
 * @tc.desc: Test FireAccessibilityEventCallback handles ON_SEND_DETACH_FOCUS_FALLBACK
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, FireAccessibilityEventCallbackDetachFocusTest001, TestSize.Level1)
{
    int32_t instanceId = 800;
    manager_->CacheDetachFocusFallbackCandidates(instanceId, 100, { 1, 2, 3 });
    manager_->FireAccessibilityEventCallback(
        static_cast<uint32_t>(AccessibilityCallbackEventId::ON_SEND_DETACH_FOCUS_FALLBACK),
        static_cast<int64_t>(instanceId));
    auto result = manager_->GetAndClearDetachFocusFallbackCandidates(instanceId);
    EXPECT_TRUE(result.candidateIds.empty());
}

/**
 * @tc.name: CacheClearRaceTest001
 * @tc.desc: Test cache operations for multiple instanceIds are independent
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, CacheClearRaceTest001, TestSize.Level1)
{
    int32_t id1 = 900;
    int32_t id2 = 901;
    int32_t id3 = 902;
    int64_t focusNodeId = 80;
    std::vector<int64_t> ids1 = { 1, 2 };
    std::vector<int64_t> ids2 = { 3, 4, 5 };
    std::vector<int64_t> ids3 = { 6 };

    manager_->CacheDetachFocusFallbackCandidates(id1, focusNodeId, ids1);
    manager_->CacheDetachFocusFallbackCandidates(id2, focusNodeId, ids2);
    manager_->CacheDetachFocusFallbackCandidates(id3, focusNodeId, ids3);

    manager_->ClearDetachFocusFallbackCache(id2);

    auto result1 = manager_->GetAndClearDetachFocusFallbackCandidates(id1);
    EXPECT_EQ(result1.candidateIds.size(), 2U);

    auto result2 = manager_->GetAndClearDetachFocusFallbackCandidates(id2);
    EXPECT_TRUE(result2.candidateIds.empty());

    auto result3 = manager_->GetAndClearDetachFocusFallbackCandidates(id3);
    EXPECT_EQ(result3.candidateIds.size(), 1U);
}

/**
 * @tc.name: SendRequestFocusToCandidateTest003
 * @tc.desc: Test SendRequestFocusToCandidate with valid node
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityManagerDetachFocusTest, SendRequestFocusToCandidateTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 950, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    bool result = manager_->SendRequestFocusToCandidate(frameNode);
    EXPECT_TRUE(result);
}

} // namespace OHOS::Ace::NG

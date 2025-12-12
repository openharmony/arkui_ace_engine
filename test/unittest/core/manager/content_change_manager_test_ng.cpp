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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INITIAL_NODE_SIZE = 5;
constexpr int32_t INITIAL_NODE_SIZE_PLUS_ONE = INITIAL_NODE_SIZE + 1;

RefPtr<ContentChangeManager> GetContentChangeManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetContentChangeManager() : nullptr;
}

void SetOnContentChangeNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        for (int32_t i = 0; i < INITIAL_NODE_SIZE; i++) {
            auto node = FrameNode::CreateFrameNode("frameNode", i, AceType::MakeRefPtr<Pattern>(), true);
            auto weak = AceType::WeakClaim(AceType::RawPtr(node));
            contentChangeMgr->onContentChangeNodes_.emplace(weak);
        }
    }
}

void ResetOnContentChangeNodes()
{
    auto contentChangeMgr = GetContentChangeManager();
    if (contentChangeMgr) {
        contentChangeMgr->onContentChangeNodes_.clear();
    }
}
} // namespace

class ContentChangeManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ContentChangeManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ContentChangeManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ContentChangeManagerTest001
 * @tc.desc: Test StartContentChangeReport, StopContentChangeReport
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test add one node
     */
    SetOnContentChangeNodes();
    auto node = FrameNode::CreateFrameNode("frameNode", INITIAL_NODE_SIZE, AceType::MakeRefPtr<Pattern>(), true);
    auto weak = AceType::WeakClaim(AceType::RawPtr(node));
    contentChangeMgr->onContentChangeNodes_.emplace(weak);
    weak.Reset();
    auto size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step3. test StartContentChangeReport
     */
    ContentChangeConfig config;
    contentChangeMgr->StartContentChangeReport(config);
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());

    /**
     * @tc.steps: step4. test StopContentChangeReport
     */
    contentChangeMgr->StopContentChangeReport();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());

    /**
     * @tc.steps: step5. reset
     */
    ResetOnContentChangeNodes();
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: ContentChangeManagerTest002
 * @tc.desc: Test AddOnContentChangeNode, RemoveOnContentChangeNode
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTestNg, ContentChangeManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get content change manager
     */
    auto contentChangeMgr = GetContentChangeManager();
    ASSERT_NE(contentChangeMgr, nullptr);

    /**
     * @tc.steps: step2. test AddOnContentChangeNode
     */
    SetOnContentChangeNodes();
    auto node = FrameNode::CreateFrameNode("frameNode", INITIAL_NODE_SIZE, AceType::MakeRefPtr<Pattern>(), true);
    auto weak = AceType::WeakClaim(AceType::RawPtr(node));
    contentChangeMgr->AddOnContentChangeNode(weak);
    auto size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step3. test RemoveOnContentChangeNode
     */
    contentChangeMgr->RemoveOnContentChangeNode(weak);
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE);

    /**
     * @tc.steps: step4. When IsContentChangeDetectEnable, test AddOnContentChangeNode
     */
    ContentChangeConfig config;
    contentChangeMgr->currentContentChangeConfig_ = config;
    EXPECT_TRUE(contentChangeMgr->IsContentChangeDetectEnable());
    contentChangeMgr->AddOnContentChangeNode(weak);
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, INITIAL_NODE_SIZE_PLUS_ONE);

    /**
     * @tc.steps: step5. reset
     */
    ResetOnContentChangeNodes();
    size = static_cast<int32_t>(contentChangeMgr->onContentChangeNodes_.size());
    EXPECT_EQ(size, 0);
    contentChangeMgr->currentContentChangeConfig_.reset();
    EXPECT_FALSE(contentChangeMgr->IsContentChangeDetectEnable());
}
} // namespace OHOS::Ace::NG

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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/syntax/static/detached_free_root_node.h"
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#include "core/pipeline/base/element_register.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr char TAG_HOST[] = "a11yVirtualHost";
constexpr char TAG_VIRTUAL[] = "a11yVirtualInner";
constexpr int32_t TEST_INSTANCE_ID = 0;
} // namespace

class AccessibilityVirtualNodeStaticTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityVirtualNodeStaticTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityVirtualNodeStaticTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// Build the real proxy -> freeRoot -> inner structure that the static frontend buildFunc returns.
static RefPtr<UINode> BuildProxyWrappedVirtualNode(int32_t& innerIdTracker)
{
    auto inner = FrameNode::CreateFrameNode(
        TAG_VIRTUAL, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    innerIdTracker = inner->GetId();

    auto freeRoot = AceType::MakeRefPtr<DetachedFreeRootNode>(
        ElementRegister::GetInstance()->MakeUniqueId());
    freeRoot->AddChild(inner);

    auto proxy = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(TEST_INSTANCE_ID);
    proxy->AddChild(freeRoot);
    return proxy;
}

static RefPtr<FrameNode> CreateHostNode(bool onMainTree, bool isFree)
{
    auto host = FrameNode::CreateFrameNode(
        TAG_HOST, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    host->onMainTree_ = onMainTree;
    host->SetIsFree(isFree);
    return host;
}

// ==================== SetAccessibilityVirtualNode (Static) ====================

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic001
 * @tc.desc: Null frameNode should be ignored safely; buildFunc is not invoked.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. pass null frameNode
     * @tc.expected: no crash, buildFunc not invoked
     */
    int32_t mark = 0;
    auto buildFunc = [&mark]() -> RefPtr<UINode> {
        mark = 1;
        return nullptr;
    };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(nullptr, std::move(buildFunc));
    EXPECT_EQ(mark, 0);
}

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic002
 * @tc.desc: When buildFunc returns nullptr and host is on main tree, the host node clears
 *           accessibility virtual node flag and saves nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a host node already on main tree, buildFunc returns nullptr
     * @tc.expected: HasAccessibilityVirtualNode == false, saved virtual node == nullptr
     */
    auto host = CreateHostNode(true /*onMainTree*/, false /*isFree*/);
    ASSERT_NE(host, nullptr);

    int32_t invoked = 0;
    auto buildFunc = [&invoked]() -> RefPtr<UINode> {
        invoked = 1;
        return nullptr;
    };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(AceType::RawPtr(host), std::move(buildFunc));

    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_FALSE(property->HasAccessibilityVirtualNode());
    EXPECT_EQ(property->GetAccessibilityVirtualNode(), nullptr);
    EXPECT_EQ(invoked, 1);
}

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic003
 * @tc.desc: When buildFunc returns a plain FrameNode (not wrapped by proxy) and host is on
 *           main tree, virtual node should be installed directly with all accessibility flags.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. host is on main tree, buildFunc returns a plain FrameNode
     * @tc.expected: HasAccessibilityVirtualNode == true, virtual node flags are set on inner
     */
    auto host = CreateHostNode(true /*onMainTree*/, false /*isFree*/);
    ASSERT_NE(host, nullptr);

    RefPtr<FrameNode> inner;
    auto buildFunc = [&inner]() -> RefPtr<UINode> {
        inner = FrameNode::CreateFrameNode(
            TAG_VIRTUAL, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
        return inner;
    };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(AceType::RawPtr(host), std::move(buildFunc));

    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->HasAccessibilityVirtualNode());
    EXPECT_EQ(property->GetAccessibilityVirtualNode(), inner);
    ASSERT_NE(inner, nullptr);
    EXPECT_TRUE(inner->IsAccessibilityVirtualNode());
    EXPECT_TRUE(inner->IsFirstVirtualNode());
    auto parent = inner->GetVirtualNodeParent().Upgrade();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->GetId(), host->GetId());
}

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic004
 * @tc.desc: Regression for Sta virtual node creation failure: when buildFunc returns
 *           DetachedFreeRootProxyNode -> DetachedFreeRootNode -> inner, the inner FrameNode
 *           must be unwrapped and installed as the accessibility virtual node; the proxy and
 *           freeRoot must no longer wrap inner.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. host is on main tree, buildFunc returns proxy -> freeRoot -> inner
     * @tc.expected: virtual node saved on host equals inner; inner has accessibility flags set;
     *               proxy/freeRoot no longer wrap inner
     */
    auto host = CreateHostNode(true /*onMainTree*/, false /*isFree*/);
    ASSERT_NE(host, nullptr);

    int32_t innerId = -1;
    auto buildFunc = [&innerId]() -> RefPtr<UINode> { return BuildProxyWrappedVirtualNode(innerId); };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(AceType::RawPtr(host), std::move(buildFunc));

    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->HasAccessibilityVirtualNode());

    auto saved = property->GetAccessibilityVirtualNode();
    ASSERT_NE(saved, nullptr);
    EXPECT_EQ(saved->GetId(), innerId);

    auto savedFrame = AceType::DynamicCast<FrameNode>(saved);
    ASSERT_NE(savedFrame, nullptr);
    EXPECT_TRUE(savedFrame->IsAccessibilityVirtualNode());
    EXPECT_TRUE(savedFrame->IsFirstVirtualNode());
    auto parent = savedFrame->GetVirtualNodeParent().Upgrade();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->GetId(), host->GetId());
}

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic005
 * @tc.desc: Deferred execution path: when host is free (worker-thread built) and not on main
 *           tree, FREE_NODE_CHECK diverts to the MultiThread variant which queues the task via
 *           PostAfterAttachMainTreeTask; the task executes once the host attaches to main tree.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. host is free and NOT on main tree, call SetAccessibilityVirtualNode
     * @tc.expected: task is queued into afterAttachMainTreeTasks_; nothing is installed yet
     */
    auto host = CreateHostNode(false /*onMainTree*/, true /*isFree*/);
    ASSERT_NE(host, nullptr);

    int32_t innerId = -1;
    auto buildFunc = [&innerId]() -> RefPtr<UINode> { return BuildProxyWrappedVirtualNode(innerId); };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(AceType::RawPtr(host), std::move(buildFunc));

    EXPECT_FALSE(host->afterAttachMainTreeTasks_.empty());
    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_FALSE(property->HasAccessibilityVirtualNode());

    /**
     * @tc.steps: step2. simulate attach to main tree -> ExecuteAfterAttachMainTreeTasks
     * @tc.expected: virtual node is now installed on host; queue is drained
     */
    host->onMainTree_ = true;
    host->ExecuteAfterAttachMainTreeTasks();

    EXPECT_TRUE(property->HasAccessibilityVirtualNode());
    auto saved = property->GetAccessibilityVirtualNode();
    ASSERT_NE(saved, nullptr);
    EXPECT_EQ(saved->GetId(), innerId);
    EXPECT_TRUE(host->afterAttachMainTreeTasks_.empty());
}

/**
 * @tc.name: SetAccessibilityVirtualNodeStatic006
 * @tc.desc: Deferred execution path with a plain (non-proxy-wrapped) FrameNode queued via the
 *           MultiThread path; verifies inner accessibility flags are correctly propagated after
 *           the deferred task runs.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityVirtualNodeStaticTest, SetAccessibilityVirtualNodeStatic006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. host is free and not on main tree; buildFunc returns plain FrameNode
     * @tc.expected: after attach + ExecuteAfterAttachMainTreeTasks, virtual node flags are set
     */
    auto host = CreateHostNode(false /*onMainTree*/, true /*isFree*/);
    ASSERT_NE(host, nullptr);

    RefPtr<FrameNode> inner;
    auto buildFunc = [&inner]() -> RefPtr<UINode> {
        inner = FrameNode::CreateFrameNode(
            TAG_VIRTUAL, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
        return inner;
    };
    ViewAbstractModelStatic model;
    model.SetAccessibilityVirtualNode(AceType::RawPtr(host), std::move(buildFunc));

    EXPECT_FALSE(host->afterAttachMainTreeTasks_.empty());

    host->onMainTree_ = true;
    host->ExecuteAfterAttachMainTreeTasks();

    ASSERT_NE(inner, nullptr);
    EXPECT_TRUE(inner->IsAccessibilityVirtualNode());
    EXPECT_TRUE(inner->IsFirstVirtualNode());
    auto parent = inner->GetVirtualNodeParent().Upgrade();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->GetId(), host->GetId());

    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->HasAccessibilityVirtualNode());
    EXPECT_EQ(property->GetAccessibilityVirtualNode(), inner);
}
} // namespace OHOS::Ace::NG

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

#include <string>
#include <utility>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class SpyNavigationStack : public NavigationStack {
    DECLARE_ACE_TYPE(SpyNavigationStack, NavigationStack);

public:
    /**
     * @tc.steps: Override Pop/Push/Remove* callbacks in spy stack.
     * @tc.expected: Test can assert base routing behavior without real JS stack integration.
     */
    void Pop() override
    {
        popCalls_++;
    }

    void Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo) override
    {
        pushByRouteCalls_.emplace_back(name);
        lastRouteInfo_ = routeInfo;
    }

    void Push(const std::string& name, int32_t index) override
    {
        pushByIndexCalls_.emplace_back(std::make_pair(name, index));
    }

    void RemoveName(const std::string& name) override
    {
        removeNameCalls_++;
        removedName_ = name;
    }

    void RemoveIndex(int32_t index) override
    {
        removedIndexes_.emplace_back(index);
    }

    void Clear() override
    {
        clearCalls_++;
        NavigationStack::Clear();
    }

    int32_t popCalls_ = 0;
    int32_t removeNameCalls_ = 0;
    int32_t clearCalls_ = 0;
    std::string removedName_;
    std::vector<std::string> pushByRouteCalls_;
    std::vector<std::pair<std::string, int32_t>> pushByIndexCalls_;
    std::vector<int32_t> removedIndexes_;
    RefPtr<RouteInfo> lastRouteInfo_;
};

class TestRouteInfo : public RouteInfo {
    DECLARE_ACE_TYPE(TestRouteInfo, RouteInfo);

public:
    /**
     * @tc.steps: Provide lightweight RouteInfo stub with deterministic name.
     * @tc.expected: Add(..., routeInfo) path can be verified through Push(name, routeInfo) arguments.
     */
    explicit TestRouteInfo(std::string name) : name_(std::move(name)) {}
    ~TestRouteInfo() override = default;

    std::string GetName() override
    {
        return name_;
    }

private:
    std::string name_;
};

RefPtr<FrameNode> CreateTestNode(const std::string& tag)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
}

RefPtr<NavDestinationGroupNode> CreateNavDestinationNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
}
} // namespace

class NavigationStackTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: NavigationStackRemove001
 * @tc.desc: Verify Remove() on empty stack.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackRemove001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    ASSERT_NE(stack, nullptr);

    stack->Remove();
    /**
     * @tc.steps: Call Remove() on an empty stack.
     * @tc.expected: No native item is removed and Pop callback is not triggered.
     */
    EXPECT_EQ(stack->Size(), 0);
    EXPECT_EQ(stack->popCalls_, 0);
}

/**
 * @tc.name: NavigationStackRemove002
 * @tc.desc: Verify Remove() pops native stack and calls Pop callback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackRemove002, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    ASSERT_NE(nodeA, nullptr);
    ASSERT_NE(nodeB, nullptr);

    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });
    stack->Remove();

    /**
     * @tc.steps: Call Remove() on a non-empty stack.
     * @tc.expected: One entry is popped from native list and Pop callback is triggered once.
     */
    EXPECT_EQ(stack->Size(), 1);
    EXPECT_EQ(stack->Get(), nodeA);
    EXPECT_EQ(stack->popCalls_, 1);
}

/**
 * @tc.name: NavigationStackRemove003
 * @tc.desc: Verify Remove(name) removes all matched entries and triggers RemoveName.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackRemove003, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA1 = CreateTestNode("nodeA1");
    auto nodeB = CreateTestNode("nodeB");
    auto nodeA2 = CreateTestNode("nodeA2");

    stack->SetNavPathList({ { "A", nodeA1 }, { "B", nodeB }, { "A", nodeA2 } });
    stack->Remove("A");

    /**
     * @tc.steps: Remove entries by duplicated name.
     * @tc.expected: All matching names are removed and RemoveName(name) is triggered.
     */
    ASSERT_EQ(stack->Size(), 1);
    EXPECT_EQ(stack->Get(), nodeB);
    EXPECT_EQ(stack->removeNameCalls_, 1);
    EXPECT_EQ(stack->removedName_, "A");
}

/**
 * @tc.name: NavigationStackRemove004
 * @tc.desc: Verify Remove(name, node) removes target node and triggers RemoveIndex.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackRemove004, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    auto nodeC = CreateTestNode("nodeC");

    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB }, { "C", nodeC } });
    stack->Remove("B", nodeB);

    /**
     * @tc.steps: Remove exact entry by name + node pointer.
     * @tc.expected: RemoveIndex receives the exact matched index.
     */
    EXPECT_EQ(stack->Size(), 2);
    ASSERT_EQ(stack->removedIndexes_.size(), 1);
    EXPECT_EQ(stack->removedIndexes_[0], 1);
}

/**
 * @tc.name: NavigationStackAdd001
 * @tc.desc: Verify PUSH mode for new destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAdd001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto routeInfo = AceType::MakeRefPtr<TestRouteInfo>("A");

    stack->Add("A", nodeA, NavRouteMode::PUSH, routeInfo);

    /**
     * @tc.steps: Add a new destination with PUSH mode.
     * @tc.expected: Node is appended and Push(name, routeInfo) is called.
     */
    EXPECT_EQ(stack->Size(), 1);
    EXPECT_EQ(stack->Get(), nodeA);
    ASSERT_EQ(stack->pushByRouteCalls_.size(), 1);
    EXPECT_EQ(stack->pushByRouteCalls_[0], "A");
    EXPECT_TRUE(stack->pushByIndexCalls_.empty());
}

/**
 * @tc.name: NavigationStackAdd002
 * @tc.desc: Verify PUSH mode for existing destination triggers RemoveIndex + Push(name,index).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAdd002, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto routeInfo = AceType::MakeRefPtr<TestRouteInfo>("A");

    stack->SetNavPathList({ { "A", nodeA } });
    stack->Add("A", nodeA, NavRouteMode::PUSH, routeInfo);

    /**
     * @tc.steps: Add duplicated destination with PUSH mode.
     * @tc.expected: RemoveIndex(oldIndex) and Push(name, oldIndex) are triggered.
     * @tc.expected: Base NavigationStack keeps old native entry then appends new one (size becomes 2).
     */
    EXPECT_EQ(stack->Size(), 2);
    EXPECT_EQ(stack->Get(), nodeA);
    ASSERT_EQ(stack->removedIndexes_.size(), 1);
    EXPECT_EQ(stack->removedIndexes_[0], 0);
    ASSERT_EQ(stack->pushByIndexCalls_.size(), 1);
    EXPECT_EQ(stack->pushByIndexCalls_[0].first, "A");
    EXPECT_EQ(stack->pushByIndexCalls_[0].second, 0);
}

/**
 * @tc.name: NavigationStackAdd003
 * @tc.desc: Verify PUSH_WITH_RECREATE mode for existing destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAdd003, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");

    stack->SetNavPathList({ { "A", nodeA } });
    stack->Add("A", nodeA, NavRouteMode::PUSH_WITH_RECREATE, nullptr);

    /**
     * @tc.steps: Add duplicated destination with PUSH_WITH_RECREATE mode.
     * @tc.expected: Duplicate path triggers RemoveIndex(oldIndex) and Push(name, oldIndex).
     */
    EXPECT_EQ(stack->Size(), 2);
    EXPECT_EQ(stack->Get(), nodeA);
    ASSERT_EQ(stack->removedIndexes_.size(), 1);
    EXPECT_EQ(stack->removedIndexes_[0], 0);
    ASSERT_EQ(stack->pushByIndexCalls_.size(), 1);
    EXPECT_EQ(stack->pushByIndexCalls_[0].second, 0);
}

/**
 * @tc.name: NavigationStackAdd004
 * @tc.desc: Verify REPLACE mode on empty stack behaves like Add.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAdd004, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");

    stack->Add("A", nodeA, NavRouteMode::REPLACE, nullptr);

    /**
     * @tc.steps: Execute REPLACE on empty stack.
     * @tc.expected: Behavior degrades to Add path and does not trigger Pop.
     */
    EXPECT_EQ(stack->Size(), 1);
    EXPECT_EQ(stack->Get(), nodeA);
    EXPECT_EQ(stack->popCalls_, 0);
    ASSERT_EQ(stack->pushByRouteCalls_.size(), 1);
    EXPECT_EQ(stack->pushByRouteCalls_[0], "A");
}

/**
 * @tc.name: NavigationStackAdd005
 * @tc.desc: Verify REPLACE mode on non-empty stack pops previous top.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAdd005, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    auto nodeC = CreateTestNode("nodeC");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });

    stack->Add("C", nodeC, NavRouteMode::REPLACE, nullptr);

    /**
     * @tc.steps: Execute REPLACE on non-empty stack.
     * @tc.expected: Old top is popped and new destination is pushed to top.
     */
    EXPECT_EQ(stack->Size(), 2);
    EXPECT_EQ(stack->Get(), nodeC);
    EXPECT_EQ(stack->popCalls_, 1);
    ASSERT_EQ(stack->pushByRouteCalls_.size(), 1);
    EXPECT_EQ(stack->pushByRouteCalls_[0], "C");
}

/**
 * @tc.name: NavigationStackQuery001
 * @tc.desc: Verify query functions Get/GetPre/FindIndex/GetAllPathName/GetAllPathIndex.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackQuery001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    auto nodeC = CreateTestNode("nodeC");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB }, { "C", nodeC } });

    /**
     * @tc.steps: Query stack by top/index/name and previous-node helpers.
     * @tc.expected: Returned node/index/name mappings are consistent.
     */
    EXPECT_EQ(stack->Get(), nodeC);
    EXPECT_EQ(stack->Get(-1), nullptr);
    EXPECT_EQ(stack->Get(99), nullptr);
    EXPECT_EQ(stack->Get(1), nodeB);
    EXPECT_EQ(stack->GetPre("C", nodeC), nodeB);
    EXPECT_EQ(stack->GetPre("A", nodeA), nullptr);
    EXPECT_EQ(stack->FindIndex("B", nodeB, true), 1);
    EXPECT_EQ(stack->GetNavDesNameByIndex(1), "B");
    EXPECT_EQ(stack->GetNavDesNameByIndex(8), "");

    RefPtr<UINode> outNode;
    int32_t outIndex = -1;
    EXPECT_TRUE(stack->Get("A", outNode, outIndex));
    EXPECT_EQ(outNode, nodeA);
    EXPECT_EQ(outIndex, 0);

    auto names = stack->GetAllPathName();
    auto indexes = stack->GetAllPathIndex();
    ASSERT_EQ(names.size(), 3);
    ASSERT_EQ(indexes.size(), 3);
    EXPECT_EQ(names[0], "A");
    EXPECT_EQ(indexes[2], 2);
}

/**
 * @tc.name: NavigationStackAll001
 * @tc.desc: Verify RemoveAll and Clear.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackAll001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    stack->SetNavPathList({ { "A", nodeA } });

    stack->RemoveAll();
    /**
     * @tc.steps: Call RemoveAll() on non-empty stack.
     * @tc.expected: Native stack is cleared and Clear callback is triggered.
     */
    EXPECT_EQ(stack->Size(), 0);
    EXPECT_EQ(stack->clearCalls_, 1);
}

/**
 * @tc.name: NavigationStackCache001
 * @tc.desc: Verify AddCacheNode and RemoveCacheNode(handle) updates cache node flag.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCache001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto navDest = CreateNavDestinationNode();
    ASSERT_NE(navDest, nullptr);
    EXPECT_FALSE(navDest->IsCacheNode());

    stack->AddCacheNode("pageA", navDest);
    EXPECT_TRUE(navDest->IsCacheNode());
    ASSERT_EQ(stack->GetAllCacheNodes().size(), 1);

    stack->RemoveCacheNode(navDest->GetId());
    EXPECT_FALSE(navDest->IsCacheNode());
    /**
     * @tc.steps: Add then remove cache entry by handle.
     * @tc.expected: Cache list and destination cache flag stay synchronized.
     */
    EXPECT_TRUE(stack->GetAllCacheNodes().empty());
}

/**
 * @tc.name: NavigationStackCache002
 * @tc.desc: Verify cache reorder/get/remove helpers.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCache002, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->AddCacheNode("A", nodeA);
    stack->AddCacheNode("B", nodeB);

    stack->ReOrderCache("B", nodeB);
    auto allCache = stack->GetAllCacheNodes();
    ASSERT_EQ(allCache.size(), 2);
    EXPECT_EQ(allCache[0].first, "B");
    EXPECT_EQ(stack->GetFromCacheNode("A"), nodeA);
    EXPECT_EQ(stack->GetFromCacheNode("B"), nodeB);

    auto byHandle = stack->GetFromCacheNode(nodeA->GetId());
    ASSERT_NE(byHandle, std::nullopt);
    EXPECT_EQ(byHandle->first, "A");
    EXPECT_EQ(byHandle->second, nodeA);

    stack->RemoveCacheNode(allCache, "A", nodeA);
    /**
     * @tc.steps: Reorder, query, and erase cache via helper APIs.
     * @tc.expected: Cache helper APIs perform targeted reorder/lookup/erase correctly.
     */
    ASSERT_EQ(allCache.size(), 1);
    EXPECT_EQ(allCache[0].first, "B");
}

/**
 * @tc.name: NavigationStackCompat001
 * @tc.desc: Verify SavePreNavList snapshots pre-list and force-set flag.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    ASSERT_NE(nodeA, nullptr);
    stack->GetPreNavPathList() = { { "A", nodeA } };
    stack->SetIsCurForceSetList(true);

    stack->SavePreNavList();

    /**
     * @tc.steps: Prepare pre-nav list and force-set flag, then call SavePreNavList().
     * @tc.expected: Previous-list snapshot keeps name/node mapping and stores current force-set flag.
     */
    EXPECT_TRUE(stack->GetIsPreForceSetList());
    auto& prev = stack->GetAllNavDestinationNodesPrev();
    ASSERT_EQ(prev.size(), 1);
    EXPECT_EQ(prev[0].first, "A");
    EXPECT_EQ(prev[0].second.Upgrade(), nodeA);
}

/**
 * @tc.name: NavigationStackCompat002
 * @tc.desc: Verify GetTopNavPath/GetPreTopNavPath behaviors on empty and non-empty lists.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat002, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    EXPECT_EQ(stack->GetTopNavPath(), std::nullopt);
    EXPECT_EQ(stack->GetPreTopNavPath(), std::nullopt);

    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });
    stack->GetPreNavPathList() = { { "A", nodeA } };

    /**
     * @tc.steps: Query top path from empty lists, then from populated current/pre lists.
     * @tc.expected: Empty returns nullopt; non-empty returns last entry of each list.
     */
    auto top = stack->GetTopNavPath();
    auto preTop = stack->GetPreTopNavPath();
    ASSERT_NE(top, std::nullopt);
    ASSERT_NE(preTop, std::nullopt);
    EXPECT_EQ(top->first, "B");
    EXPECT_EQ(preTop->first, "A");
}

/**
 * @tc.name: NavigationStackCompat003
 * @tc.desc: Verify RemoveStack only clears current navPathList.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat003, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });
    stack->GetPreNavPathList() = { { "A", nodeA } };

    stack->RemoveStack();

    /**
     * @tc.steps: Populate current/pre lists, then call RemoveStack().
     * @tc.expected: Current list is cleared while pre list keeps existing data.
     */
    EXPECT_EQ(stack->Size(), 0);
    EXPECT_EQ(stack->PreSize(), 1);
}

/**
 * @tc.name: NavigationStackCompat004
 * @tc.desc: Verify UpdateRecoveryList/ClearRecoveryList persistence behavior.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat004, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });

    stack->UpdateRecoveryList();
    auto recovery = stack->GetRecoveryList();
    ASSERT_EQ(recovery.size(), 2);
    EXPECT_EQ(recovery[0].first, "A");
    EXPECT_EQ(recovery[1].first, "B");

    stack->ClearRecoveryList();

    /**
     * @tc.steps: Snapshot current list to recovery list, then clear recovery list.
     * @tc.expected: Recovery list first mirrors current entries and then becomes empty after clear.
     */
    EXPECT_TRUE(stack->GetRecoveryList().empty());
}

/**
 * @tc.name: NavigationStackCompat005
 * @tc.desc: Verify GetFromCacheNode(handle) returns nullopt for unmatched handle.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat005, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    stack->AddCacheNode("A", nodeA);

    auto byMissHandle = stack->GetFromCacheNode(nodeA->GetId() + 1);

    /**
     * @tc.steps: Add one cache entry and query cache by a non-existent handle.
     * @tc.expected: Query result is nullopt and does not affect existing cache entries.
     */
    EXPECT_EQ(byMissHandle, std::nullopt);
    EXPECT_EQ(stack->GetAllCacheNodes().size(), 1);
}

/**
 * @tc.name: NavigationStackCompat006
 * @tc.desc: Verify RemoveInNavPathList return value and erase behavior.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat006, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });

    auto notFound = stack->RemoveInNavPathList("C", nodeA);
    ASSERT_EQ(notFound, -1);
    ASSERT_EQ(stack->Size(), 2);

    auto removed = stack->RemoveInNavPathList("A", nodeA);

    /**
     * @tc.steps: Remove with unmatched key first, then remove with exact matched key+node.
     * @tc.expected: Unmatched call returns -1 without erase; matched call returns index and erases entry.
     */
    EXPECT_EQ(removed, 0);
    EXPECT_EQ(stack->Size(), 1);
    EXPECT_EQ(stack->Get(), nodeB);
}

/**
 * @tc.name: NavigationStackCompat007
 * @tc.desc: Verify base CreateNodeByIndex/CreateNodeByRouteInfo default behavior.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat007, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    RefPtr<UINode> outNode;
    auto created = stack->CreateNodeByIndex(0, WeakPtr<UINode>(), outNode);
    auto routeCreated = stack->CreateNodeByRouteInfo(nullptr, WeakPtr<UINode>());

    /**
     * @tc.steps: Invoke base node-creation extension points without mock override.
     * @tc.expected: Base class keeps compatibility default: CreateNodeByIndex=false, CreateNodeByRouteInfo=nullptr.
     */
    EXPECT_FALSE(created);
    EXPECT_EQ(outNode, nullptr);
    EXPECT_EQ(routeCreated, nullptr);
}

/**
 * @tc.name: NavigationStackCompat008
 * @tc.desc: Verify IsEmpty compatibility behavior in base class.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat008, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    stack->SetNavPathList({ { "A", nodeA } });

    /**
     * @tc.steps: Check IsEmpty() on base stack with existing entries.
     * @tc.expected: Base class returns default false for compatibility with extended implementations.
     */
    EXPECT_FALSE(stack->IsEmpty());
}

/**
 * @tc.name: NavigationStackCompat009
 * @tc.desc: Verify Clear() clears both nav path list and cache list.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat009, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA } });
    stack->AddCacheNode("B", nodeB);
    ASSERT_EQ(stack->Size(), 1);
    ASSERT_EQ(stack->GetAllCacheNodes().size(), 1);

    stack->Clear();

    /**
     * @tc.steps: Prepare current path + cache entries, then call Clear().
     * @tc.expected: Clear() empties both native nav list and cache list.
     */
    EXPECT_EQ(stack->Size(), 0);
    EXPECT_TRUE(stack->GetAllCacheNodes().empty());
}

/**
 * @tc.name: NavigationStackCompat010
 * @tc.desc: Verify recovery list remains as snapshot after nav list mutation.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationStackTestNg, NavigationStackCompat010, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<SpyNavigationStack>();
    auto nodeA = CreateTestNode("nodeA");
    auto nodeB = CreateTestNode("nodeB");
    stack->SetNavPathList({ { "A", nodeA }, { "B", nodeB } });
    stack->UpdateRecoveryList();
    auto recovery = stack->GetRecoveryList();
    ASSERT_EQ(recovery.size(), 2);

    stack->RemoveStack();
    ASSERT_EQ(stack->Size(), 0);

    /**
     * @tc.steps: Take recovery snapshot, then mutate current nav list by RemoveStack().
     * @tc.expected: Recovery list keeps snapshot content until ClearRecoveryList() is called.
     */
    EXPECT_EQ(stack->GetRecoveryList().size(), 2);
    stack->ClearRecoveryList();
    EXPECT_TRUE(stack->GetRecoveryList().empty());
}

} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_node.h"
#include "core/components_ng/syntax/repeat_model_ng.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG = "node";
const std::list<std::string> FOR_REPEAT_IDS = { "0", "1", "2", "3", "4", "5" };
constexpr int32_t NODE_ID = 1;
constexpr int32_t COUNT_1 = 1;
constexpr int32_t COUNT_3 = 3;
} // namespace

using CacheItem = RepeatVirtualScrollCaches::CacheItem;

class RepeatVirtualTestNg2 : public testing::Test {
public:

    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }

    RefPtr<RepeatVirtualScrollNode> GetOrCreateRepeatNode(bool createItems);

    RefPtr<FrameNode> CreateNode(const std::string& tag, int32_t elmtId)
    {
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, elmtId, pattern);
        pattern->AttachToFrameNode(frameNode);
        ViewStackProcessor::GetInstance()->Push(frameNode);
        return frameNode;
    }

    // create ListItemNode with 2 Text Node inside
    RefPtr<FrameNode> CreateListItemNode(int32_t elmtId)
    {
        auto tag = "TEXT_ETS_TAG";

        auto* stack = ViewStackProcessor::GetInstance();
        auto liFrameNode = FrameNode::GetOrCreateFrameNode(V2::LIST_ITEM_ETS_TAG, elmtId,
            []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE); });

        auto textNode = CreateNode(V2::TEXT_ETS_TAG, 100*elmtId);

        auto pattern = AceType::MakeRefPtr<Pattern>();
        const uint32_t uniqNumMultiplier1 = 200;
        auto textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier1*elmtId, pattern);
        pattern->AttachToFrameNode(textFrameNode);
        liFrameNode->AddChild(textFrameNode);

        pattern = AceType::MakeRefPtr<Pattern>();
        const uint32_t uniqNumMultiplier2 = 100;
        textFrameNode = AceType::MakeRefPtr<FrameNode>(tag, uniqNumMultiplier2*elmtId, pattern);
        pattern->AttachToFrameNode(textFrameNode);
        liFrameNode->AddChild(textFrameNode);
        stack->Push(liFrameNode);
        return liFrameNode;
    }

    const std::function<void(uint32_t)> onCreateNode = [this](uint32_t forIndex) {
        CreateListItemNode(forIndex);
    };
};
/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onCreateNode = [](uint32_t forIndex) {
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onUpdateNode = [](const std::string& fromKey, uint32_t forIndex) {
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> keys;
    for (uint32_t i = from; i <= to; ++i) {
        keys.push_back("Key" + std::to_string(i));
    }
    return keys;
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> types;
    for (uint32_t i = from; i <= to; ++i) {
        types.push_back("Type" + std::to_string(i));
    }

    return types;
};
/**
 * Function needed by RepeatVirtualScrollNode constructor
 */
auto g_onSetActiveRange = [](int32_t from, int32_t to) {
};

/**
 * Map needed by RepeatVirtualScrollCaches constructor
 */
const std::map<std::string, std::pair<bool, uint32_t>> cacheCountL24ttype = {
    {"element1", { true, 1 }},
    {"element2", { true, 2 }},
    {"element3", { true, 3 }},
    {"element4", { true, 4 }},
    {"element5", { true, 5 }}
};

/**
 * Map needed by RepeatVirtualScrollNode constructor
 */
const std::map<std::string, std::pair<bool, uint32_t>> templateCachedCountMap = {
    // { template, { cachedCountSpecified, cacheCount } }
    {"elmt1", { true, 1 } },
    {"elmt2", { true, 2 } }
};

RefPtr<RepeatVirtualScrollNode> RepeatVirtualTestNg2::GetOrCreateRepeatNode(bool createItems)
{
    RefPtr<RepeatVirtualScrollNode> node;
    if (createItems) {
        node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(NODE_ID, COUNT_3, templateCachedCountMap, onCreateNode,
            g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range, g_onSetActiveRange);
    } else {
        node = RepeatVirtualScrollNode::GetOrCreateRepeatNode(NODE_ID, COUNT_1, templateCachedCountMap, g_onCreateNode,
            g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range, g_onSetActiveRange);
    }
    return node;
}

/**
 * @tc.name: RepeatNodeCacheTest046
 * @tc.desc: Test AddKeyToL1 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest046, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", nodeId, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key046", node } };
    caches.node4key_ = { { "Key046", cacheItem } };
    caches.node4key4ttype_ = { { "template046", nodeKey } };
    caches.ttype4index_ = { { 0, "template046" } };
    caches.index4ttype_ = { { "template046", 0 } };
    caches.reusedNodeIds_.clear();
    caches.AddKeyToL1("Key046", true);
    EXPECT_EQ(caches.reusedNodeIds_.size(), 1);
    auto id = caches.reusedNodeIds_.begin();
    EXPECT_EQ(*id, node->GetId());

    caches.AddKeyToL1("Key046", true);
    EXPECT_EQ(caches.reusedNodeIds_.size(), 1);
    EXPECT_EQ(*id, node->GetId());
}

/**
 * @tc.name: RepeatNodeCacheTest047
 * @tc.desc: Test UpdateFromL2 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest047, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    caches.ttype4index_.clear();
    auto retNode = caches.UpdateFromL2(0);
    ASSERT_EQ(retNode, nullptr);

    caches.ttype4index_ = { { 0, "template047" } };
    retNode = caches.UpdateFromL2(0);
    ASSERT_EQ(retNode, nullptr);

    retNode = caches.UpdateFromL2(0);
    ASSERT_EQ(retNode, nullptr);

    caches.key4index_ = { { 0, "Key047" } };
    retNode = caches.UpdateFromL2(0);
    ASSERT_EQ(retNode, nullptr);

    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key047", node } };
    CacheItem cacheItem;
    cacheItem.item = node;
    caches.node4key_ = { { "Key047", cacheItem } };
    caches.node4key4ttype_ = { { "template047", nodeKey } };
    retNode = caches.UpdateFromL2(0);
    ASSERT_NE(retNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest048
 * @tc.desc: Test CreateNewNode function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest048, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    auto retNode = caches.CreateNewNode(0);
    ASSERT_EQ(retNode, nullptr);
    caches.key4index_ = { { 0, "Key048" } };
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key048", node } };
    CacheItem cacheItem;
    cacheItem.item = node;
    caches.node4key_ = { { "Key048", cacheItem } };
    retNode = caches.CreateNewNode(0);
    ASSERT_NE(retNode, nullptr);
    caches.node4key_.clear();
    retNode = caches.CreateNewNode(0);
    ASSERT_EQ(retNode, nullptr);

    caches.ttype4index_ = { { 0, "template048" } };
    retNode = caches.CreateNewNode(0);
    ASSERT_EQ(retNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest050
 * @tc.desc: Test RebuildL1 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest050, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    caches.activeNodeKeysInL1_ = { "Key0" };

    std::function<bool(int32_t, const RefPtr<UINode>&)> callback = [](int32_t a, const RefPtr<UINode>& b) {
        return true;
    };
    auto ret = caches.RebuildL1(callback);
    EXPECT_FALSE(ret);

    caches.activeNodeKeysInL1_ = { "Key050" };
    caches.index4Key_ = { { "Key050", 0 } };
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", nodeId, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    caches.node4key_ = { { "Key050", cacheItem } };
    ret = caches.RebuildL1(callback);
    EXPECT_FALSE(ret);
    EXPECT_EQ(caches.activeNodeKeysInL1_.size(), 1);

    std::function<bool(int32_t, const RefPtr<UINode>&)> callback2 = [](int32_t a, const RefPtr<UINode>& b) {
        return false;
    };
    ret = caches.RebuildL1(callback2);
    EXPECT_TRUE(ret);
    EXPECT_EQ(caches.activeNodeKeysInL1_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest051
 * @tc.desc: Test SetLastActiveRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest051, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    std::pair<uint32_t, uint32_t> range = { 10, 30 };
    caches.lastActiveRanges_[0] = range;
    EXPECT_EQ(caches.lastActiveRanges_[0], range);
    caches.cacheCountL24ttype_ = { { "Key051", { true, 0 } } };
    caches.SetLastActiveRange(20, 25);
    EXPECT_EQ(caches.lastActiveRanges_[1], range);
    std::pair<uint32_t, uint32_t> range2 = { 20, 25 };
    EXPECT_EQ(caches.lastActiveRanges_[0], range2);

    caches.cacheCountL24ttype_ = { { "Key051", { false, 0 } } };
    caches.SetLastActiveRange(20, 25);
    std::map<std::string, std::pair<bool, uint32_t>> cacheCout = { { "Key051", { false, 6 } } };
    EXPECT_EQ(caches.cacheCountL24ttype_, cacheCout);
}

/**
 * @tc.name: RepeatNodeCacheTest052
 * @tc.desc: Test SetLastActiveRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest052, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto ret = caches.Purge();
    EXPECT_FALSE(ret);
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key052", node } };
    caches.node4key4ttype_ = { { "template052", nodeKey } };
    ret = caches.Purge();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: RepeatNodeCacheTest053
 * @tc.desc: Test DoSetActiveChildRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest053, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(true);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_.clear();
    repeatNode->children_.push_back(childNode);
    EXPECT_EQ(repeatNode->children_.size(), 1);

    caches.index4Key_ = { { "Key053", 0 } };
    caches.activeNodeKeysInL1_ = { "Key053" };
    repeatNode->caches_ = caches;
    repeatNode->DoSetActiveChildRange(0, 1, 0, 0);
    EXPECT_EQ(repeatNode->children_.size(), 0);

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key053", node } };
    caches.node4key_ = { { "Key053", cacheItem } };
    repeatNode->caches_ = caches;
    repeatNode->DoSetActiveChildRange(0, 1, 0, 0);
    EXPECT_EQ(repeatNode->children_.size(), 0);

    repeatNode->children_.clear();
    repeatNode->children_.push_back(childNode);
    repeatNode->SetIsLoop(false);
    repeatNode->DoSetActiveChildRange(3, 5, 2, 1);
    EXPECT_EQ(repeatNode->children_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest054
 * @tc.desc: Test DoSetActiveChildRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest054, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(true);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    repeatNode->caches_ = caches;
    repeatNode->caches_.AddKeyToL1("Key054");
    repeatNode->caches_.AddKeyToL1("Key2");
    repeatNode->caches_.AddKeyToL1("Key3");
    std::set<int32_t> activeItems;

    const int largeValue = 100;
    for (int i = 0; i < largeValue; i++) {
        activeItems.insert(i);
    }
    std::set<int32_t> cachedItems;
    cachedItems.insert(1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);

    repeatNode->caches_.index4Key_ = { { "Key054", 0 } };
    repeatNode->caches_.activeNodeKeysInL1_ = { "Key054" };
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 0);

    repeatNode->caches_.activeNodeKeysInL1_ = { "Key054" };
    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_ = { childNode };
    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 0);
    EXPECT_EQ(repeatNode->children_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest055
 * @tc.desc: Test DoSetActiveChildRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest055, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(true);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key055", node } };
    caches.node4key_ = { { "Key055", cacheItem } };
    caches.index4Key_ = { { "Key055", 0 } };
    caches.activeNodeKeysInL1_ = { "Key055" };
    repeatNode->caches_ = caches;
    repeatNode->children_ = { node };
    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    node->children_ = { childNode };

    std::set<int32_t> activeItems;
    const int largeValue = 100;
    for (int i = 3; i < largeValue; i++) {
        activeItems.insert(i);
    }

    std::set<int32_t> cachedItems;
    cachedItems.insert(1);

    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);
    EXPECT_EQ(repeatNode->children_.size(), 1);

    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);
    EXPECT_EQ(repeatNode->children_.size(), 1);
}

/**
 * @tc.name: RepeatNodeCacheTest056
 * @tc.desc: Test DoSetActiveChildRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest056, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(true);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key056", node } };
    caches.node4key_ = { { "Key056", cacheItem } };
    caches.index4Key_ = { { "Key056", 0 } };
    caches.activeNodeKeysInL1_ = { "Key056" };
    repeatNode->caches_ = caches;
    repeatNode->children_ = { node };
    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    node->children_ = { childNode };

    std::set<int32_t> activeItems;
    const int largeValue = 100;
    for (int i = 0; i < largeValue; i++) {
        activeItems.insert(i);
    }

    std::set<int32_t> cachedItems = { 1 };

    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);
    EXPECT_EQ(repeatNode->children_.size(), 1);

    activeItems.clear();
    for (int i = 3; i < largeValue; i++) {
        activeItems.insert(i);
    }

    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 0);
    EXPECT_EQ(repeatNode->children_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest057
 * @tc.desc: Test for GetOrCreateRepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest057, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();

    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(repeatNode, nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = repeatNode->GetOrCreateRepeatNode(nodeId);
    ASSERT_NE(node, nullptr);

    auto existNode = repeatNode->GetOrCreateRepeatNode(nodeId);
    ASSERT_NE(existNode, nullptr);
    EXPECT_EQ(existNode->GetId(), nodeId);
}

/**
 * @tc.name: RepeatNodeCacheTest058
 * @tc.desc: Test for FinishRepeatRender
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest058, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();

    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(repeatNode, nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);

    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_ = { childNode };
    EXPECT_GT(repeatNode->children_.size(), 0);

    std::list<std::string> ids2 = FOR_REPEAT_IDS;
    repeatNode->SetIds(std::move(ids2));
    repeatNode->CreateTempItems();
    EXPECT_GT(repeatNode->tempChildrenOfRepeat_.size(), 0);

    std::list<int32_t> arr;
    arr.push_back(0);
    repeatNode->FinishRepeatRender(arr);
    EXPECT_EQ(repeatNode->tempChildren_.size(), 0);
    EXPECT_EQ(repeatNode->tempChildrenOfRepeat_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest059
 * @tc.desc: Test for FinishRepeatRender
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest059, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();

    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(repeatNode, nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);

    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->SetParent(node);
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_ = { childNode };
    EXPECT_GT(repeatNode->children_.size(), 0);

    std::list<std::string> ids2 = FOR_REPEAT_IDS;
    repeatNode->SetIds(std::move(ids2));
    repeatNode->CreateTempItems();
    EXPECT_GT(repeatNode->tempChildrenOfRepeat_.size(), 0);

    std::list<int32_t> arr;
    arr.push_back(0);
    repeatNode->FinishRepeatRender(arr);
    EXPECT_EQ(repeatNode->tempChildren_.size(), 0);
    EXPECT_EQ(repeatNode->tempChildrenOfRepeat_.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest060
 * @tc.desc: Test for MoveChild
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest060, TestSize.Level1)
{
    RepeatModelNG repeatModel;
    repeatModel.StartRender();
    auto repeatNode = AceType::DynamicCast<RepeatNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(repeatNode, nullptr);
    EXPECT_EQ(repeatNode->GetTag(), V2::JS_REPEAT_ETS_TAG);

    auto node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->SetParent(node);
    auto childNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_ = { childNode };
    EXPECT_GT(repeatNode->children_.size(), 0);
    EXPECT_EQ(repeatNode->tempChildrenOfRepeat_.size(), 0);

    std::list<std::string> ids2 = FOR_REPEAT_IDS;
    repeatNode->SetIds(std::move(ids2));
    repeatNode->CreateTempItems();
    EXPECT_GT(repeatNode->tempChildrenOfRepeat_.size(), 0);

    repeatNode->MoveChild(0);
}

/**
 * @tc.name: RepeatNodeCacheTest061
 * @tc.desc: Test for GetFrameChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtualTestNg2, RepeatNodeCacheTest061, TestSize.Level1)
{
    auto onGetTypes4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
        std::list<std::string> types;
        for (uint32_t i = from; i <= to; ++i) {
            types.push_back("elmt1");
        }
        return types;
    };
    // enable reuse
    RefPtr<RepeatVirtualScrollNode> repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID, COUNT_3, templateCachedCountMap, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, onGetTypes4Range,
        g_onSetActiveRange, true);
    ASSERT_NE(repeatNode, nullptr);
    repeatNode->GetFrameChildByIndex(0, true, false, true);
    repeatNode->GetFrameChildByIndex(1, true, false, true);
    repeatNode->DoSetActiveChildRange(0, 0, 0, 0);
    auto node = repeatNode->GetFrameChildByIndex(2, true, false, true);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetId(), 1);
    // diable reuse
    repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
        NODE_ID + 1, COUNT_3, templateCachedCountMap, onCreateNode, g_onUpdateNode, g_onGetKeys4Range, onGetTypes4Range,
        g_onSetActiveRange, false);
    ASSERT_NE(repeatNode, nullptr);
    repeatNode->GetFrameChildByIndex(0, true, false, true);
    repeatNode->GetFrameChildByIndex(1, true, false, true);
    repeatNode->DoSetActiveChildRange(0, 0, 0, 0);
    node = repeatNode->GetFrameChildByIndex(2, true, false, true);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetId(), 2);
}
}
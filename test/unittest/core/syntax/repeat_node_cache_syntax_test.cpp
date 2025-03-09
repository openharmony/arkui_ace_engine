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

class RepeatNodeCacheSyntaxTest : public testing::Test {
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
 * Function needed by RepeatVirtualScrollCaches constructor is special test case
 */
auto g_onGetKeys4RangeMaxTo5 = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> keys;
    for (uint32_t i = from; i <= to && i<=5; ++i) {
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

RefPtr<RepeatVirtualScrollNode> RepeatNodeCacheSyntaxTest::GetOrCreateRepeatNode(bool createItems)
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
 * @tc.name: RepeatNodeCacheTest001
 * @tc.desc: Test GetKey4Index without fetch.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest001, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to get key for index 2.
     * @tc.expected: Because second parameter is false
     * FetchMoreKeysTTypes will not be called and std::nullopt is returned
     */
    std::optional<std::string> key = caches.GetKey4Index(2, false);
    EXPECT_EQ(key, std::nullopt);
}

/**
 * @tc.name: RepeatNodeCacheTest002
 * @tc.desc: Test GetKey4Index with fetch.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest002, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

     /**
     * @tc.steps: step1. Try to get key for index 2.
     * @tc.expected: Because second parameter is true FetchMoreKeysTTypes will be called and Key2 string is returned
     */
    std::optional<std::string> key = caches.GetKey4Index(2, true);

    /**
     * @tc.steps: step2. Try to create node for index 2.
     * @tc.expected: Because viewStack->Finish() will eventually return nullptr node will also be nullptr
     */
    RefPtr<UINode> node = caches.CreateNewNode(2);
    EXPECT_EQ(node, nullptr);
    EXPECT_EQ(key, "Key2");
}

/**
 * @tc.name: RepeatNodeCacheTest003
 * @tc.desc: Test UpdateFromL2
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest003, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to get UINode from index 2
     * @tc.expected: Because there are no items in L2 nullptr is expected
     */
    RefPtr<UINode> node = caches.UpdateFromL2(2);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest004
 * @tc.desc: Test GetDistanceFromRange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest004, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Get distance from active range of index 2
     * @tc.expected: Because active range index is 0 it expected that number 2 is returned.
     */
    int32_t dist = caches.GetDistanceFromRange(2);
    EXPECT_EQ(dist, 2);
}

/**
 * @tc.name: RepeatNodeCacheTest005
 * @tc.desc: Test creation of GetOrCreateRepeatNode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          nodeId,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    EXPECT_NE(repeatNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest006
 * @tc.desc: Test FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest006, TestSize.Level1)
{
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    /**
     * @tc.steps: step2. Update total count to 2
     * @tc.expected: Object internal frame count is increased to 2
     */
    repeatNode->UpdateTotalCount(2);

    /**
     * @tc.steps: step3. Get frame count
     * @tc.expected: Object internal frame count should be 2
     */
    uint32_t frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, 2);
}

/**
 * @tc.name: RepeatNodeCacheTest007
 * @tc.desc: Test GetChildren
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest007, TestSize.Level1)
{
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    /**
     * @tc.steps: step2. Get children count
     * @tc.expected: Returns number of children. Should be 0
     */
    std::list<RefPtr<UINode>> nodes = repeatNode->GetChildren();
    EXPECT_EQ(nodes.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest008
 * @tc.desc: Test Multiple functions when onCreate lambda really creates node.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest008, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype, onCreateNode,
                                     g_onUpdateNode, g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    std::optional<std::string> key1 = caches.GetKey4Index(1, true);
    EXPECT_EQ(key1, "Key1");
    std::optional<std::string> key2 = caches.GetKey4Index(2, true);
    EXPECT_EQ(key2, "Key2");
    std::optional<std::string> key3 = caches.GetKey4Index(3, true);
    EXPECT_EQ(key3, "Key3");

    RefPtr<UINode> node1 = caches.CreateNewNode(1);
    EXPECT_NE(node1, nullptr);
    RefPtr<UINode> node2 = caches.CreateNewNode(2);
    EXPECT_NE(node2, nullptr);
    RefPtr<UINode> node3 = caches.CreateNewNode(3);
    EXPECT_NE(node3, nullptr);

    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1, 3, templateCachedCountMap, onCreateNode,
                          g_onUpdateNode, g_onGetKeys4Range,
                          g_onGetTypes4Range, g_onSetActiveRange);

    repeatNode->caches_ = caches;
    /**
     * @tc.steps: step1. Add keys to cache
     * @tc.expected: Items in cache size should be 3
     */
    repeatNode->caches_.FetchMoreKeysTTypes(1, 3);
    repeatNode->caches_.AddKeyToL1("Key1");
    repeatNode->caches_.AddKeyToL1("Key2");
    repeatNode->caches_.AddKeyToL1("Key3");
    EXPECT_EQ(repeatNode->caches_.activeNodeKeysInL1_.size(), 3);

    /**
     * @tc.steps: step2. Dump information
     * @tc.expected: Dumping output string should have ListItem(3) substring
     */
    std::string l1Dump = repeatNode->caches_.DumpL1();
    const std::string expectedSubStringL1And4TType = "ListItem";
    EXPECT_NE(l1Dump.find(expectedSubStringL1And4TType), std::string::npos);
    std::string dmp4KeyType = repeatNode->caches_.DumpUINode4Key4TType();
    EXPECT_NE(dmp4KeyType.find(expectedSubStringL1And4TType), std::string::npos);

    /**
     * @tc.steps: step3. Find unused keys
     * @tc.expected: Number of unused keys should be 0
     */
    std::set<std::pair<bool, std::string>> keys;
    caches.FindUnusedKeys(keys);
    EXPECT_EQ(keys.size(), 0);

    caches.UINodeHasBeenUpdated("Type1", "Key1", "Key2");
    repeatNode->DoSetActiveChildRange(1, 3, 1, 2);
    repeatNode->caches_.index4Key_.clear();
    repeatNode->DropFromL1("Key1");
    repeatNode->caches_.GetL1KeyToUpdate("Key1");
    repeatNode->caches_.InvalidateKeyAndTTypeCaches();
    repeatNode->UpdateRenderState(true);
    repeatNode->UpdateRenderState(false);
    repeatNode->RecycleItems(0, 100);

    /**
     * @tc.steps: step4. Get GetFrameNode
     * @tc.expected: Returns valid frame node
     */
    auto frameNode = repeatNode->GetFrameNode(1);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest009
 * @tc.desc: Test FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest009, TestSize.Level1)
{
    const uint32_t totalCount = 10;
    const uint32_t updatedCount = 5;
    /**
     * @tc.steps: step1. Create node object with totalCount = 10
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          totalCount,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    /**
     * @tc.steps: step2. Ask frame count
     * @tc.expected: Should be totalCount
     */
    uint32_t frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, totalCount);

    /**
     * @tc.steps: step3. Update total count to the new value
     * @tc.expected: Should be updatedCount
     */
    repeatNode->UpdateTotalCount(updatedCount);
    frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, updatedCount);
}

/**
 * @tc.name: RepeatNodeCacheTest010
 * @tc.desc: Test GetL1KeyToUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest010, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    caches.FetchMoreKeysTTypes(1, 3);
    /**
     * @tc.steps: step1. Try to get L1 key to update
     * @tc.expected: Because there are no L1 key for Type1
     * std::nullopt is returned
     */
    std::optional<std::string> key = caches.GetL1KeyToUpdate("Type1");
    EXPECT_EQ(key, std::nullopt);
}

/**
 * @tc.name: RepeatNodeCacheTest011
 * @tc.desc: Test UiNodeHasBeenUpdated
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest011, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to get UI node by calling UINodeHasBeenUpdated
     * @tc.expected: Because there are no nodes nullptr is returned
     */
    RefPtr<UINode> node = caches.UINodeHasBeenUpdated("Type1", "Key0", "Key1");
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest012
 * @tc.desc: Test FindUnusedKeys
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest012, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to get set of unused keys
     * @tc.expected: Because there are no keys 0 is returned
     */
    std::set<std::pair<bool, std::string>> keys;
    caches.FindUnusedKeys(keys);
    EXPECT_EQ(keys.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest013
 * @tc.desc: Test DumpL1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest013, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpL1
     * @tc.expected: Because there are no items. Its expected that there is
     * total number=0 substring in return value
     */
    std::string l1Dump = caches.DumpL1();
    const std::string expectedSubString = "total number=0";
    EXPECT_NE(l1Dump.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest014
 * @tc.desc: Test DumpL2
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest014, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpL2
     * @tc.expected: Because there are no items. Its expected that there is size=0 substring in return value
     */
    std::string l2Dump = caches.DumpL2();
    const std::string expectedSubString = "size=0";
    EXPECT_NE(l2Dump.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest015
 * @tc.desc: Test DumpKey4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest015, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpKey4Index
     * @tc.expected: Because there are no items. Its expected that there is size=0 substring in return value
     */
    std::string key4IndexDump = caches.DumpKey4Index();
    const std::string expectedSubString = "size=0";
    EXPECT_NE(key4IndexDump.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest016
 * @tc.desc: Test DumpTType4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest016, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpTType4Index
     * @tc.expected: Because there are no items. Its expected that there is size=0 substring in return value
     */
    std::string tTypeIndex = caches.DumpTType4Index();
    const std::string expectedSubString = "size=0";
    EXPECT_NE(tTypeIndex.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest017
 * @tc.desc: Test DumpUINode4Key
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest017, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpUINode4Key
     * @tc.expected: Because there are no items. Its expected that there is size=0 substring in return value
     */
    std::string uiNode4Key = caches.DumpUINode4Key();
    const std::string expectedSubString = "size=0";
    EXPECT_NE(uiNode4Key.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest018
 * @tc.desc: Test DumpUINode4Key4TType
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest018, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);


    /**
     * @tc.steps: step1. Try to call DumpUINode4Key4TType
     * @tc.expected: Because there are no items. Its expected that there is size=0 substring in return value
     */
    std::string uiNode4Key4TType = caches.DumpUINode4Key4TType();
    const std::string expectedSubString = "size=0";
    EXPECT_NE(uiNode4Key4TType.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest019
 * @tc.desc: Test DumpUINodeWithKey
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest019, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpUINodeWithKey
     * @tc.expected: Because there are no items. Its expected that there is "no UINode" substring in return value
     */
    std::string uiNodeWithKey = caches.DumpUINodeWithKey("Key1");
    const std::string expectedSubString = "no UINode";
    EXPECT_NE(uiNodeWithKey.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest020
 * @tc.desc: Test DumpUINode
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest020, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call DumpUINode
     * @tc.expected: Because input argument is nullptr its expected that there is nullptr in return value
     */
    std::string uiNode = caches.DumpUINode(nullptr);
    const std::string expectedSubString = "nullptr";
    EXPECT_NE(uiNode.find(expectedSubString), std::string::npos);
}

/**
 * @tc.name: RepeatNodeCacheTest021
 * @tc.desc: Test OnConfigurationUpdate function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest021, TestSize.Level1)
{
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    ConfigurationChange cfgChange;
    cfgChange.colorModeUpdate = true;
    /**
     * @tc.steps: step1. Try to call GetOrCreateRepeatNode.
     * @tc.expected: Instead of creating current node is returned,
     */
    auto repeatNode2 = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    EXPECT_EQ(repeatNode, repeatNode2);
    /**
     * @tc.steps: step3. Try to call OnConfigurationChange.
     * @tc.expected: No code crash happens
     */
    repeatNode->OnConfigurationUpdate(cfgChange);
}

/**
 * @tc.name: RepeatNodeCacheTest022
 * @tc.desc: Test FetchMoreKeysTTypes with invalid values.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest022, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to call FetchMoreKeysTTypes so that "from" is bigger than "to"
     * @tc.expected: False is expected to be returned
     */
    bool status = caches.FetchMoreKeysTTypes(2, 1);
    EXPECT_EQ(status, false);
}

/**
 * @tc.name: RepeatNodeCacheTest023
 * @tc.desc: Test FetchMoreKeysTTypes with special MaxTo5 lambda.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create caches object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     g_onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4RangeMaxTo5,
                                     g_onGetTypes4Range);

     /**
     * @tc.steps: step2. Try to call FetchMoreKeysTTypes so that internally "keys"
     * *are smaller than "types" due to g_onGetKeys4RangeMaxTo5
     * @tc.expected: False is expected to be returned
     */
    bool status = caches.FetchMoreKeysTTypes(1, 10);
    EXPECT_EQ(status, false);
}

/**
 * @tc.name: RepeatNodeCacheTest024
 * @tc.desc: Test GetKey4Index with fetch and creating new node.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest024, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    /**
     * @tc.steps: step1. Try to get key for index 2.
     * @tc.expected: Because second parameter is true FetchMoreKeysTTypes will be internally
     * called and Key2 string is returned
     */
    std::optional<std::string> key = caches.GetKey4Index(2, true);
    EXPECT_EQ(key, "Key2");
    /**
     * @tc.steps: step2. Try to create node for index 2.
     * @tc.expected: Because onCreateNode lambda used that really creates node 1 is expected.
     */
    RefPtr<UINode> node = caches.CreateNewNode(2);
    EXPECT_NE(node, nullptr);

    RefPtr<UINode> uinode = caches.DropFromL1("Key2");
    EXPECT_NE(uinode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest025
 * @tc.desc: Test GetDistanceFromRange
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest025, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    int32_t dist = caches.GetDistanceFromRange(UINT32_MAX);
    EXPECT_EQ(dist, UINT32_MAX);

    caches.lastActiveRanges_[0].first = 10;
    caches.lastActiveRanges_[0].second = 30;
    caches.lastActiveRanges_[1].first = 20;
    dist = caches.GetDistanceFromRange(9);
    EXPECT_EQ(dist, 0);

    dist = caches.GetDistanceFromRange(11);
    EXPECT_EQ(dist, 0);

    caches.lastActiveRanges_[0].first = 10;
    caches.lastActiveRanges_[0].second = 30;
    caches.lastActiveRanges_[1].second = 20;
    dist = caches.GetDistanceFromRange(29);
    EXPECT_EQ(dist, 0);

    dist = caches.GetDistanceFromRange(31);
    EXPECT_EQ(dist, 0);
}

/**
 * @tc.name: RepeatNodeCacheTest026
 * @tc.desc: Test GetCachedNode4Key4Ttype
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);

    auto ret = caches.GetCachedNode4Key4Ttype(std::nullopt, std::nullopt);
    EXPECT_EQ(ret, nullptr);
    ret = caches.GetCachedNode4Key4Ttype(std::string("a"), std::nullopt);
    EXPECT_EQ(ret, nullptr);
    ret = caches.GetCachedNode4Key4Ttype(std::nullopt, std::string("a"));
    EXPECT_EQ(ret, nullptr);
    ret = caches.GetCachedNode4Key4Ttype(std::string("a"), std::string("a"));
    EXPECT_EQ(ret, nullptr);

    // std::unordered_map<std::string, std::unordered_map<std::string, RefPtr<UINode>>> node4key4ttype_;
    caches.node4key4ttype_.insert({ std::string("a"), { { std::string("a"), nullptr } } });
    ret = caches.GetCachedNode4Key4Ttype(std::string("a"), std::string("a"));
    EXPECT_EQ(ret, nullptr);
    ret = caches.GetCachedNode4Key4Ttype(std::string("b"), std::string("a"));
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest027
 * @tc.desc: Test GetCachedNode4Key
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);

    auto ret = caches.GetCachedNode4Key(std::nullopt);
    EXPECT_FALSE(ret.has_value());
}

/**
 * @tc.name: RepeatNodeCacheTest028
 * @tc.desc: Test GetTType4Index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);
    std::string val("0");
    caches.ttype4index_.insert({ 0, val });
    auto ret = caches.GetTType4Index(0);
    EXPECT_TRUE(ret.has_value());
}

/**
 * @tc.name: RepeatNodeCacheTest029
 * @tc.desc: Test GetIndex4Key
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);

    std::string key("key");
    caches.index4Key_.insert({ key, 0 });
    auto ret = caches.GetIndex4Key(key);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: RepeatNodeCacheTest030
 * @tc.desc: Test FindUnusedKeys
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);

    std::string key("key");
    caches.node4key_.insert({ key, CacheItem() });
    std::set<std::pair<bool, std::string>> result;
    caches.FindUnusedKeys(result);
    EXPECT_EQ(result.size(), 1);

    result.clear();
    caches.index4Key_.insert({ key, 0 });
    caches.FindUnusedKeys(result);
    EXPECT_EQ(result.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest031
 * @tc.desc: Test UINodeHasBeenUpdated
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
     * @tc.expected: Object is created correctly
     */
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4RangeMaxTo5, g_onGetTypes4Range);

    std::string key("key");
    std::string key2("key2");
    caches.node4key4ttype_.insert({ key, { { key2, nullptr } } });
    auto ret = caches.UINodeHasBeenUpdated(key, std::string("a"), std::string("a"));
    EXPECT_EQ(ret, nullptr);
    ret = caches.UINodeHasBeenUpdated(key, key2, std::string("a"));
    EXPECT_EQ(ret, nullptr);

    caches.node4key_.insert({ key2, CacheItem() });
    ret = caches.UINodeHasBeenUpdated(key, key2, std::string("a"));
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest032
 * @tc.desc: Test GetL1KeyToUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest032, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    std::string key("key");
    std::string key1("key1");
    caches.activeNodeKeysInL1_.insert(key);
    std::optional<std::string> ret = caches.GetL1KeyToUpdate(key1);
    EXPECT_EQ(ret, std::nullopt);

    caches.index4Key_.insert({ key, 0 });
    ret = caches.GetL1KeyToUpdate(key1);
    EXPECT_EQ(ret, std::nullopt);

    caches.index4Key_.clear();
    caches.node4key4ttype_.insert({ key1, {} });
    ret = caches.GetL1KeyToUpdate(key1);
    EXPECT_EQ(ret, std::nullopt);

    caches.node4key4ttype_.clear();
    caches.node4key4ttype_.insert({ key1, { { key, nullptr } } });
    ret = caches.GetL1KeyToUpdate(key1);
    EXPECT_NE(ret, std::nullopt);
}

/**
 * @tc.name: RepeatNodeCacheTest033
 * @tc.desc: Test GetL2KeyToUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest033, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto ret = caches.GetL2KeyToUpdate(std::nullopt);
    EXPECT_EQ(ret, std::nullopt);

    std::string key("key");
    ret = caches.GetL2KeyToUpdate(key);
    EXPECT_EQ(ret, std::nullopt);

    caches.node4key4ttype_.insert({ key, { { key, nullptr } } });
    ret = caches.GetL2KeyToUpdate(key);
    EXPECT_NE(ret, std::nullopt);

    caches.node4key4ttype_.clear();
    caches.node4key4ttype_.insert({ key, { { key, nullptr } } });
    ret = caches.GetL2KeyToUpdate(key);
    EXPECT_NE(ret, std::nullopt);

    std::unordered_map<std::string, RefPtr<UINode>> nodeKey;
    caches.node4key4ttype_ = { { "template1", nodeKey } };
    ret = caches.GetL2KeyToUpdate(key);
    EXPECT_EQ(ret, std::nullopt);
}

/**
 * @tc.name: RepeatNodeCacheTest034
 * @tc.desc: Test GetFrameNodeIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest034, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto ret = caches.GetFrameNodeIndex(nullptr);
    EXPECT_EQ(ret, -1);

    std::string key("key");
    caches.activeNodeKeysInL1_.insert(key);
    ret = caches.GetFrameNodeIndex(nullptr);
    EXPECT_EQ(ret, -1);

    caches.node4key_.insert({ key, CacheItem() });
    caches.activeNodeKeysInL1_.insert(key);
    ret = caches.GetFrameNodeIndex(nullptr);
    EXPECT_EQ(ret, -1);

    caches.activeNodeKeysInL1_ = { "Key1", "Key2" };
    caches.key4index_ = { { 0, "Key1" }, { 1, "Key2" } };
    caches.ttype4index_ = { { 0, "template1" }, { 1, "template2" } };
    caches.index4ttype_ = { { "template1", 0 }, { "template2", 1 } };

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { {"Key1", node} };
    caches.node4key_ = { {"Key1", cacheItem} };
    caches.node4key4ttype_ = { {"template1", nodeKey} };
    ret = caches.GetFrameNodeIndex(node);
    EXPECT_EQ(ret, -1);

    caches.index4Key_ = { {"Key1", 2} };
    ret = caches.GetFrameNodeIndex(node);
    EXPECT_EQ(ret, 2);
}

/**
 * @tc.name: RepeatNodeCacheTest035
 * @tc.desc: Test Multiple functions
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest035, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(cacheCountL24ttype,
                                     onCreateNode,
                                     g_onUpdateNode,
                                     g_onGetKeys4Range,
                                     g_onGetTypes4Range);

    std::optional<std::string> key1 = caches.GetKey4Index(1, true);
    EXPECT_EQ(key1, "Key1");
    std::optional<std::string> key2 = caches.GetKey4Index(2, true);
    EXPECT_EQ(key2, "Key2");
    std::optional<std::string> key3 = caches.GetKey4Index(3, true);
    EXPECT_EQ(key3, "Key3");
    RefPtr<UINode> node1 = caches.CreateNewNode(1);
    EXPECT_NE(node1, nullptr);
    RefPtr<UINode> node2 = caches.CreateNewNode(2);
    EXPECT_NE(node2, nullptr);
    RefPtr<UINode> node3 = caches.CreateNewNode(3);
    EXPECT_NE(node3, nullptr);

    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          3,
                          templateCachedCountMap,
                          onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    // Set caches to repeat.
    repeatNode->caches_ = caches;
    repeatNode->caches_.FetchMoreKeysTTypes(1, 3);
    repeatNode->caches_.AddKeyToL1("Key1");
    repeatNode->caches_.AddKeyToL1("Key2");
    repeatNode->caches_.AddKeyToL1("Key3");

    std::set<int32_t> activeItems;
    const int largeValue = 100;
    for (int i = 0; i < largeValue; i++) {
        activeItems.insert(i);
    }
    std::set<int32_t> cachedItems;
    cachedItems.insert(1);

    /**
     * @tc.steps: step2. Perform two DoSetActiveChildRange calls
     * First with valid value 1 and second too large value
     * @tc.expected: Functions do not return any value
     */
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, largeValue+1);
}

/**
 * @tc.name: RepeatNodeCacheTest036
 * @tc.desc: Call functions that are currently empty implementations
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest036, TestSize.Level1)
{
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          3,
                          templateCachedCountMap,
                          onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange);

    EXPECT_NE(repeatNode, nullptr);

    auto onMoveLambda = [](int32_t start, int32_t end) {
    };
    /**
     * @tc.steps: step1. Call functions with no implementation yet in repeat_virtual_scroll_node.cpp
     * @tc.expected: Not crash happens
     */
    repeatNode->SetOnMove(std::move(onMoveLambda));
    repeatNode->MoveData(0, 100);
    auto frameNode = repeatNode->GetFrameNode(1);
    repeatNode->InitDragManager(frameNode);
    repeatNode->InitAllChildrenDragManager(true);
}

/**
 * @tc.name: RepeatNodeCacheTest037
 * @tc.desc: Test CheckNode4IndexInL1 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest037, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(true);
    ASSERT_NE(repeatNode, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    auto ret = repeatNode->CheckNode4IndexInL1(3, 2, 4, 1, 1, frameNode);
    EXPECT_TRUE(frameNode->isActive_);
    EXPECT_TRUE(ret);

    repeatNode->SetIsLoop(true);
    ret = repeatNode->CheckNode4IndexInL1(3, 5, 2, 1, 1, frameNode);
    EXPECT_FALSE(frameNode->isActive_);
    EXPECT_TRUE(ret);

    repeatNode->SetIsLoop(false);
    ret = repeatNode->CheckNode4IndexInL1(3, 5, 2, 1, 1, frameNode);
    EXPECT_FALSE(frameNode->isActive_);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: RepeatNodeCacheTest038
 * @tc.desc: Test for DropFromL1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest038, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);

    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_.clear();
    repeatNode->children_.push_back(childNode);
    EXPECT_EQ(repeatNode->children_.size(), 1);
    repeatNode->DropFromL1("Key038");
    EXPECT_EQ(repeatNode->children_.size(), 1);
}

/**
 * @tc.name: RepeatNodeCacheTest039
 * @tc.desc: Test for UpdateRenderState
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest039, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);
    auto childNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->children_.clear();
    repeatNode->children_.push_back(childNode);
    EXPECT_EQ(repeatNode->children_.size(), 1);

    auto frameNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    repeatNode->SetParent(frameNode);
    repeatNode->UpdateRenderState(true);
    EXPECT_EQ(repeatNode->children_.size(), 0);

    repeatNode->children_.push_back(childNode);
    repeatNode->UpdateRenderState(false);
    EXPECT_EQ(repeatNode->children_.size(), 1);
}

/**
 * @tc.name: RepeatNodeCacheTest040
 * @tc.desc: Test for GetFrameChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest040, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);
    auto childNode = repeatNode->GetFrameChildByIndex(0, false, false, false);
    EXPECT_EQ(childNode, nullptr);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    caches.key4index_.insert(pair<int, string>(0, "Key1"));
    CacheItem cacheItem;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = AceType::MakeRefPtr<FrameNode>("node", nodeId, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;

    RefPtr<UINode> uiNode = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key1", uiNode } };
    caches.node4key_ = { { "Key1", cacheItem } };
    caches.node4key4ttype_ = { { "template1", nodeKey } };
    repeatNode->caches_ = caches;

    childNode = repeatNode->GetFrameChildByIndex(1, false, false, false);
    EXPECT_EQ(childNode, nullptr);

    childNode = repeatNode->GetFrameChildByIndex(1, true, false, false);
    EXPECT_EQ(childNode, nullptr);

    childNode = repeatNode->GetFrameChildByIndex(0, true, false, false);
    repeatNode->isActive_ = true;
    EXPECT_EQ(childNode, nullptr);

    nodeKey = { { "Key1", node } };
    caches.index4ttype_ = { { "template1", 0 } };
    caches.ttype4index_ = { { 0, "template1" } };
    caches.node4key4ttype_ = { { "template1", nodeKey } };
    caches.activeNodeKeysInL1_ = { "Key1" };
    repeatNode->caches_ = caches;
    childNode = repeatNode->GetFrameChildByIndex(0, false, false, true);
    ASSERT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetId(), nodeId);
}

/**
 * @tc.name: RepeatNodeCacheTest041
 * @tc.desc: Test for GetFrameChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest041, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);
    auto childNode = repeatNode->GetFrameChildByIndex(0, false, false, false);
    EXPECT_EQ(childNode, nullptr);

    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);
    caches.key4index_.insert(pair<int, string>(0, "Key041"));
    CacheItem cacheItem;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = AceType::MakeRefPtr<FrameNode>("node", nodeId, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key041", node } };
    caches.node4key_ = { { "Key041", cacheItem } };

    auto ttype = g_onGetTypes4Range(0, 0).front();
    caches.node4key4ttype_ = { { ttype, nodeKey } };
    caches.ttype4index_ = { { 0, ttype } };
    caches.index4ttype_ = { { ttype, 0 } };
    repeatNode->caches_ = caches;
    repeatNode->onMainTree_ = true;

    std::function<void(int32_t, int32_t)> onMoveEvent_ = [](int32_t a, int32_t b) {};
    repeatNode->onMoveEvent_ = onMoveEvent_;
    childNode = repeatNode->GetFrameChildByIndex(0, false, false, true);
    ASSERT_NE(childNode, nullptr);
    EXPECT_EQ(childNode->GetId(), nodeId);
}

/**
 * @tc.name: RepeatNodeCacheTest042
 * @tc.desc: Test for GetChildren
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest042, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);
    repeatNode->caches_.activeNodeKeysInL1_ = { { "Key042", "Key2", "Key3" } };

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key042", node } };
    repeatNode->caches_.index4Key_ = { { "Key042", 0 } };
    repeatNode->caches_.node4key_ = { { "Key042", cacheItem } };
    auto children = repeatNode->GetChildren();
    EXPECT_EQ(children.size(), 1);

    repeatNode->children_ = { node };
    children = repeatNode->GetChildren();
    EXPECT_EQ(children.size(), 1);
}

/**
 * @tc.name: RepeatNodeCacheTest043
 * @tc.desc: Test UpdateChildrenFreezeState function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest043, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);
    ASSERT_NE(repeatNode, nullptr);
    repeatNode->caches_.activeNodeKeysInL1_ = { { "Key043", "Key2", "Key3" } };

    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key043", node } };
    repeatNode->caches_.node4key_ = { { "Key043", cacheItem } };
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->SetOpenInvisibleFreeze(true);
    repeatNode->UpdateChildrenFreezeState(true);
    for (auto iter = repeatNode->caches_.node4key_.begin(); iter != repeatNode->caches_.node4key_.end(); ++iter) {
        auto item = iter->second.item;
        ASSERT_NE(item, nullptr);
        EXPECT_TRUE(item->isFreeze_);
    }

    repeatNode->UpdateChildrenFreezeState(false);
    for (auto iter = repeatNode->caches_.node4key_.begin(); iter != repeatNode->caches_.node4key_.end(); ++iter) {
        auto item = iter->second.item;
        ASSERT_NE(item, nullptr);
        EXPECT_FALSE(item->isFreeze_);
    }
}

/**
 * @tc.name: RepeatNodeCacheTest044
 * @tc.desc: Test OnConfigurationUpdate function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest044, TestSize.Level1)
{
    auto repeatNode = GetOrCreateRepeatNode(false);

    CacheItem cacheItem;
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(frameNode->pattern_, nullptr);

    cacheItem.item = frameNode;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key044", frameNode } };
    repeatNode->caches_.node4key_ = { { "Key044", cacheItem } };

    ConfigurationChange cfgChange;
    cfgChange.colorModeUpdate = true;
    repeatNode->OnConfigurationUpdate(cfgChange);
}

/**
 * @tc.name: RepeatNodeCacheTest045
 * @tc.desc: Test HasOverlapWithLastActiveRange function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest045, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    caches.lastActiveRanges_[0].first = 10;
    caches.lastActiveRanges_[0].second = 30;
    auto ret = caches.HasOverlapWithLastActiveRange(10, 20);
    EXPECT_TRUE(ret);

    caches.lastActiveRanges_[0].first = 20;
    caches.lastActiveRanges_[0].second = 10;
    ret = caches.HasOverlapWithLastActiveRange(10, 20);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: RepeatNodeCacheTest046
 * @tc.desc: Test AddKeyToL1 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest046, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest047, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest048, TestSize.Level1)
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
 * @tc.name: RepeatNodeCacheTest049
 * @tc.desc: Test RecycleItemsByIndex function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest049, TestSize.Level1)
{
    RepeatVirtualScrollCaches caches(
        cacheCountL24ttype, g_onCreateNode, g_onUpdateNode, g_onGetKeys4Range, g_onGetTypes4Range);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    CacheItem cacheItem;
    auto node = AceType::MakeRefPtr<FrameNode>("node", nodeId, AceType::MakeRefPtr<Pattern>());
    cacheItem.item = node;
    std::unordered_map<std::string, RefPtr<UINode>> nodeKey = { { "Key049", node } };
    caches.key4index_ = { { nodeId, "Key049" } };
    caches.node4key_ = { { "Key049", cacheItem } };
    caches.reusedNodeIds_.clear();
    caches.AddKeyToL1("Key049", true);
    EXPECT_EQ(caches.reusedNodeIds_.size(), 1);
    auto id = caches.reusedNodeIds_.begin();
    EXPECT_EQ(*id, node->GetId());
    caches.RecycleItemsByIndex(nodeId);
    EXPECT_EQ(caches.reusedNodeIds_.size(), 1);
}

/**
 * @tc.name: RepeatNodeCacheTest050
 * @tc.desc: Test RebuildL1 function
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest050, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest051, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest052, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest053, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest054, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest055, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest056, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest057, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest058, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest059, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest060, TestSize.Level1)
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
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest061, TestSize.Level1)
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
} // namespace OHOS::Ace::NG

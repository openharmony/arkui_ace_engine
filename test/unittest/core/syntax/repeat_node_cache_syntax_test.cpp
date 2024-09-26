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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_caches.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RepeatNodeCacheSyntaxTest : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void RepeatNodeCacheSyntaxTest::SetUp()
{
}

void RepeatNodeCacheSyntaxTest::TearDown()
{
}

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
    {"element2", { true, 2 } },
    {"element3", { true, 3 }},
    {"element4", { true, 4 }},
    {"element5", { true, 5 }}
};

/**
 * Map needed by RepeatVirtualScrollNode constructor
 */
const std::map<std::string, std::pair<bool, uint32_t>> templateCachedCountMap = {
    // { template, { cachedCountSpecified, cacheCount } }
    {"elmt1", { true, 1} },
    {"elmt2", { true, 2} }
};

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
                          g_onSetActiveRange
                    );
    stack->Push(repeatNode);
    stack->PopContainer();
    EXPECT_NE(repeatNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest006
 * @tc.desc: Test FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange
                    );

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
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange
                    );

    /**
     * @tc.steps: step2. Get children count
     * @tc.expected: Returns number of children. Should be 0
     */
    std::list<RefPtr<UINode>> nodes = repeatNode->GetChildren();
    EXPECT_EQ(nodes.size(), 0);
}

/**
 * @tc.name: RepeatNodeCacheTest008
 * @tc.desc: Test Multiple functions
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange
                    );


    std::set<int32_t> activeItems;
    const int largeValue = 10000;
    for (int i = 0; i < largeValue; i++) {
        activeItems.insert(i);
    }
    std::set<int32_t> cachedItems;
    cachedItems.insert(1);
    cachedItems.insert(2);

    /**
     * @tc.steps: step2. Call some common functions
     * @tc.expected: Following functions are run without crash
     */
    repeatNode->DoSetActiveChildRange(1, 2, 1, 1);
    repeatNode->DoSetActiveChildRange(activeItems, cachedItems, 1);
    repeatNode->DropFromL1("Key1");
    repeatNode->UpdateRenderState(true);
    repeatNode->RecycleItems(0, 100);
    repeatNode->MoveData(0, 100);

     /**
     * @tc.steps: step3. Try to create node for index 2.
     * @tc.expected: Because viewStack->Finish() will eventually return nullptr node will also be nullptr
     */
    RefPtr<UINode> node = repeatNode->CreateOrUpdateFrameChild4Index(1, "Key1");
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest009
 * @tc.desc: Test FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest009, TestSize.Level1)
{
    const uint32_t totalCount = 10;
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
                          g_onSetActiveRange
                    );

    /**
     * @tc.steps: step2. Ask frame count
     * @tc.expected: Should be totalCount
     */
    uint32_t frameCount = repeatNode->FrameCount();
    EXPECT_EQ(frameCount, totalCount);
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
     * @tc.expected: Because there are no items. Its expected that there is total number=0 substring in return value
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
    /**
     * @tc.steps: step1. Create node object
     * @tc.expected: Object is not nullptr.
     */
    auto repeatNode = RepeatVirtualScrollNode::GetOrCreateRepeatNode(
                          1,
                          1,
                          templateCachedCountMap,
                          g_onCreateNode,
                          g_onUpdateNode,
                          g_onGetKeys4Range,
                          g_onGetTypes4Range,
                          g_onSetActiveRange
                    );

    ConfigurationChange cfgChange;
    cfgChange.colorModeUpdate = true;

    /**
     * @tc.steps: step3. Try to call OnConfigurationChange.
     * @tc.expected: No code crash happens
     */
    repeatNode->OnConfigurationUpdate(cfgChange);
    EXPECT_NE(repeatNode, nullptr);
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
     * @tc.steps: step1. Create cached object with Keys function that limits keys to 5 (for unit testing)
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
} // namespace OHOS::Ace::NG

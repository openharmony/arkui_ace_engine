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

    RefPtr<FrameNode> CreateNode(const std::string& tag);
};

void RepeatNodeCacheSyntaxTest::SetUp()
{
    MockPipelineContext::SetUp();
}

void RepeatNodeCacheSyntaxTest::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> RepeatNodeCacheSyntaxTest::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onCreateNode = [](uint32_t forIndex) {
    std::cout << "onCreateNode for index: " << forIndex << std::endl;
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onUpdateNode = [](const std::string& fromKey, uint32_t forIndex) {
    std::cout << "onUpdateNode fromKey " << fromKey << " forIndex=" << forIndex << std::endl;
};

/**
 * Function needed by RepeatVirtualScrollCaches constructor
 */
auto g_onGetKeys4Range = [](uint32_t from, uint32_t to) -> std::list<std::string> {
    std::list<std::string> keys;
    for (uint32_t i = from; i <= to; ++i) {
        keys.push_back("Key" + std::to_string(i));
    }
    std::cout << "onGetKeys4Range from " << from << " to " << to << " returns [";
    std::copy(keys.begin(), keys.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "]" << std::endl;
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
    std::cout << "g_onGetTypes4Range from " << from << " to " << to << " returns [";
    std::copy(types.begin(), types.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << "]" << std::endl;
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
    // { template, { cachedCountSpecified, cacheCount } }
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
    std::cout<<"RepeatNodeCacheTest001"<<std::endl;

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

    if (key.has_value()) {
        std::cout << "Key: " << key.value() << std::endl;
    } else {
        std::cout << "No key available for the given index." << std::endl;
    }

    EXPECT_EQ(key, std::nullopt);
}

/**
 * @tc.name: RepeatNodeCacheTest002
 * @tc.desc: Test GetKey4Index with fetch.
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest002, TestSize.Level1)
{
    std::cout<<"RepeatNodeCacheTest002"<<std::endl;

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

    if (key.has_value()) {
        std::cout << "Key: " << key.value() << std::endl;
    } else {
        std::cout << "No key available for the given index." << std::endl;
    }

    /**
     * @tc.steps: step2. Try to create node for index 2.
     * @tc.expected: Because viewStack->Finish() will eventually return nullptr nore will also be nullptr
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
    std::cout<<"RepeatNodeCacheTest003"<<std::endl;

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
    std::cout<<"RepeatNodeCacheTest004"<<std::endl;

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
    std::cout<<"RepeatNodeCacheTest005"<<std::endl;

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

    EXPECT_NE(repeatNode, nullptr);
}

/**
 * @tc.name: RepeatNodeCacheTest006
 * @tc.desc: Test FrameCount
 * @tc.type: FUNC
 */
HWTEST_F(RepeatNodeCacheSyntaxTest, RepeatNodeCacheTest006, TestSize.Level1)
{
    std::cout<<"RepeatNodeCacheTest006"<<std::endl;

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
    std::cout<<"RepeatNodeCacheTest007"<<std::endl;

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
    std::cout<<"RepeatNodeCacheTest008"<<std::endl;

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
     * @tc.steps: step2. Call some common functions to make sure no crash happenes
     * @tc.expected: Following functions are run without crash
     */
    repeatNode->DoSetActiveChildRange(1, 2, 1, 1);
    repeatNode->DropFromL1("Key1");
    repeatNode->UpdateRenderState(true);
    repeatNode->RecycleItems(0, 100);

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
    std::cout<<"RepeatNodeCacheTest009"<<std::endl;
    const uint32_t totalCount = 10;
    /**
     * @tc.steps: step1. Create node object
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

} // namespace OHOS::Ace::NG


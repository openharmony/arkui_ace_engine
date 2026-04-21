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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_caches.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_INDEX_1 = 0;
constexpr int32_t TEST_INDEX_2 = 1;
constexpr int32_t TEST_INDEX_3 = 2;
constexpr int32_t TEST_INDEX_5 = 5;
constexpr uint32_t TEST_RID_1 = 100;
constexpr uint32_t TEST_RID_2 = 200;
constexpr int32_t TEST_NODE_ID = 1;
constexpr int32_t TEST_MOVE_INDEX_1 = 1;
constexpr int32_t TEST_MOVE_INDEX_2 = 2;
constexpr int32_t TEST_MOVE_INDEX_3 = 3;
} // namespace

class RepeatVirtual2CachesTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    std::unique_ptr<RepeatVirtualScroll2Caches> CreateCachesWithMockCallback();
};

void RepeatVirtual2CachesTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RepeatVirtual2CachesTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void RepeatVirtual2CachesTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void RepeatVirtual2CachesTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

std::unique_ptr<RepeatVirtualScroll2Caches> RepeatVirtual2CachesTestNg::CreateCachesWithMockCallback()
{
    auto onGetRid4Index = [](IndexType index, bool) -> std::pair<RIDType, uint32_t> {
        return { TEST_RID_1, OnGetRid4IndexResult::NO_NODE };
    };
    return std::make_unique<RepeatVirtualScroll2Caches>(onGetRid4Index);
}

/**
 * @tc.name: ConstructorTest001
 * @tc.desc: Constructor initializes caches with callback
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConstructorTest001, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    EXPECT_TRUE(caches != nullptr);
}

/**
 * @tc.name: GetFrameChildTest002
 * @tc.desc: GetFrameChild returns NO_NODE when needBuild is false and no L1 cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetFrameChildTest002, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetFrameChild(TEST_INDEX_1, false);
    EXPECT_EQ(result.first, OnGetRid4IndexResult::NO_NODE);
    EXPECT_TRUE(result.second == nullptr);
}

/**
 * @tc.name: RemoveNodeTest003
 * @tc.desc: RemoveNode removes node from cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, RemoveNodeTest003, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->RemoveNode(TEST_RID_1);
    SUCCEED();
}

/**
 * @tc.name: SetInvalidTest004
 * @tc.desc: SetInvalid drops RID from L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, SetInvalidTest004, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->SetInvalid(TEST_RID_1);
    SUCCEED();
}

/**
 * @tc.name: DropFromL1ByRidTest005
 * @tc.desc: DropFromL1ByRid removes RID from L1 cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DropFromL1ByRidTest005, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->DropFromL1ByRid(TEST_RID_1);
    SUCCEED();
}

/**
 * @tc.name: DropFromL1ByIndexTest006
 * @tc.desc: DropFromL1ByIndex removes index from L1 cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DropFromL1ByIndexTest006, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->DropFromL1ByIndex(TEST_INDEX_1);
    SUCCEED();
}

/**
 * @tc.name: GetL1Index4RidTest007
 * @tc.desc: GetL1Index4Rid returns nullopt when RID not in L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetL1Index4RidTest007, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetL1Index4Rid(TEST_RID_1);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetL1Index4RIDTest008
 * @tc.desc: GetL1Index4RID returns nullopt when RID not in L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetL1Index4RIDTest008, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetL1Index4RID(TEST_RID_1);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetL1Index4NodeTest009
 * @tc.desc: GetL1Index4Node returns nullopt when frameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetL1Index4NodeTest009, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    RefPtr<FrameNode> nullNode = nullptr;
    auto result = caches->GetL1Index4Node(nullNode);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: UpdateL1Rid4IndexTest010
 * @tc.desc: UpdateL1Rid4Index updates L1 cache mapping
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, UpdateL1Rid4IndexTest010, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    std::map<int32_t, uint32_t> l1Rd4Index;
    l1Rd4Index[TEST_INDEX_1] = TEST_RID_1;
    l1Rd4Index[TEST_INDEX_2] = TEST_RID_2;
    caches->UpdateL1Rid4Index(l1Rd4Index);
    EXPECT_EQ(caches->l1Rid4Index_.size(), static_cast<size_t>(2));
}

/**
 * @tc.name: GetCacheItem4RIDTest011
 * @tc.desc: GetCacheItem4RID returns nullopt when RID not in cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetCacheItem4RIDTest011, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetCacheItem4RID(TEST_RID_1);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetRID4IndexTest012
 * @tc.desc: GetRID4Index returns nullopt when index not in L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetRID4IndexTest012, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetRID4Index(TEST_INDEX_1);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetL1CacheItem4IndexTest013
 * @tc.desc: GetL1CacheItem4Index returns nullopt when index not in L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, GetL1CacheItem4IndexTest013, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->GetL1CacheItem4Index(TEST_INDEX_1);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: RebuildL1Test014
 * @tc.desc: RebuildL1 returns false when L1 is empty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, RebuildL1Test014, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto cbFunc = [](IndexType, RepeatVirtualScroll2Caches::CacheItem&) -> bool { return true; };
    bool result = caches->RebuildL1(cbFunc);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ForEachL1NodeTest015
 * @tc.desc: ForEachL1Node does nothing when L1 is empty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ForEachL1NodeTest015, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    int32_t callCount = 0;
    auto cbFunc = [&callCount](IndexType, RIDType, const RefPtr<UINode>&) { callCount++; };
    caches->ForEachL1Node(cbFunc);
    EXPECT_EQ(callCount, 0);
}

/**
 * @tc.name: ForEachL1NodeWithOnMoveTest016
 * @tc.desc: ForEachL1NodeWithOnMove does nothing when L1 is empty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ForEachL1NodeWithOnMoveTest016, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    int32_t callCount = 0;
    auto cbFunc = [&callCount](const RefPtr<UINode>&) { callCount++; };
    caches->ForEachL1NodeWithOnMove(cbFunc);
    EXPECT_EQ(callCount, 0);
}

/**
 * @tc.name: ForEachCacheItemTest017
 * @tc.desc: ForEachCacheItem does nothing when cache is empty
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ForEachCacheItemTest017, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    int32_t callCount = 0;
    auto cbFunc = [&callCount](RIDType, const RepeatVirtualScroll2Caches::CacheItem&) { callCount++; };
    caches->ForEachCacheItem(cbFunc);
    EXPECT_EQ(callCount, 0);
}

/**
 * @tc.name: UpdateMoveFromToTest018
 * @tc.desc: UpdateMoveFromTo sets moveFromTo when not exists
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, UpdateMoveFromToTest018, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_2);
    EXPECT_TRUE(caches->IsMoveFromToExist());
}

/**
 * @tc.name: UpdateMoveFromToTest019
 * @tc.desc: UpdateMoveFromTo updates existing moveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, UpdateMoveFromToTest019, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_2);
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_3);
    EXPECT_TRUE(caches->IsMoveFromToExist());
}

/**
 * @tc.name: UpdateMoveFromToTest020
 * @tc.desc: UpdateMoveFromTo resets when from equals to
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, UpdateMoveFromToTest020, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_2);
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_1);
    EXPECT_FALSE(caches->IsMoveFromToExist());
}

/**
 * @tc.name: ResetMoveFromToTest021
 * @tc.desc: ResetMoveFromTo clears moveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ResetMoveFromToTest021, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_2);
    EXPECT_TRUE(caches->IsMoveFromToExist());
    caches->ResetMoveFromTo();
    EXPECT_FALSE(caches->IsMoveFromToExist());
}

/**
 * @tc.name: ConvertFromToIndexTest022
 * @tc.desc: ConvertFromToIndex returns same index when no moveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexTest022, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->ConvertFromToIndex(TEST_INDEX_1);
    EXPECT_EQ(result, TEST_INDEX_1);
}

/**
 * @tc.name: ConvertFromToIndexTest023
 * @tc.desc: ConvertFromToIndex converts index when moveFromTo exists
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexTest023, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_5);
    auto result = caches->ConvertFromToIndex(TEST_INDEX_5);
    EXPECT_EQ(result, TEST_INDEX_1);
}

/**
 * @tc.name: ConvertFromToIndexRevertTest024
 * @tc.desc: ConvertFromToIndexRevert returns same index when no moveFromTo
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexRevertTest024, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->ConvertFromToIndexRevert(TEST_INDEX_1);
    EXPECT_EQ(result, TEST_INDEX_1);
}

/**
 * @tc.name: ConvertFromToIndexRevertTest025
 * @tc.desc: ConvertFromToIndexRevert reverts converted index
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexRevertTest025, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_INDEX_1, TEST_INDEX_5);
    auto result = caches->ConvertFromToIndexRevert(TEST_INDEX_1);
    EXPECT_EQ(result, TEST_INDEX_5);
}

/**
 * @tc.name: DumpUINodeTest026
 * @tc.desc: DumpUINode returns correct string for nullptr
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DumpUINodeTest026, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    RefPtr<UINode> nullNode = nullptr;
    auto result = caches->DumpUINode(nullNode);
    EXPECT_EQ(result, "UINode: nullptr");
}

/**
 * @tc.name: DumpCacheItemTest027
 * @tc.desc: DumpCacheItem handles nullptr node
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DumpCacheItemTest027, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    RefPtr<UINode> nullNode = nullptr;
    auto cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(nullNode, false);
    auto result = caches->DumpCacheItem(cacheItem);
    EXPECT_EQ(result, "UINode nullptr");
}

/**
 * @tc.name: DumpUINodeCacheTest028
 * @tc.desc: DumpUINodeCache returns string for empty cache
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DumpUINodeCacheTest028, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->DumpUINodeCache();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: DumpL1Rid4IndexTest029
 * @tc.desc: DumpL1Rid4Index returns string for empty L1
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, DumpL1Rid4IndexTest029, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    auto result = caches->DumpL1Rid4Index();
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: IsMoveFromToExistTest030
 * @tc.desc: IsMoveFromToExist returns false initially
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, IsMoveFromToExistTest030, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    EXPECT_FALSE(caches->IsMoveFromToExist());
}

/**
 * @tc.name: CacheItemMakeCacheItemTest031
 * @tc.desc: RepeatVirtualScroll2CacheItem MakeCacheItem creates cache item
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, CacheItemMakeCacheItemTest031, TestSize.Level1)
{
    RefPtr<UINode> node = FrameNode::CreateFrameNode("test", TEST_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(node, true);
    EXPECT_TRUE(cacheItem != nullptr);
    EXPECT_TRUE(cacheItem->isL1_);
    EXPECT_FALSE(cacheItem->isActive_);
    EXPECT_FALSE(cacheItem->isOnRenderTree_);
}

/**
 * @tc.name: UpdateIsL1Test032
 * @tc.desc: UpdateIsL1 updates isL1 flag
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, UpdateIsL1Test032, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    RefPtr<UINode> node = FrameNode::CreateFrameNode("test", TEST_NODE_ID, AceType::MakeRefPtr<Pattern>());
    auto cacheItem = RepeatVirtualScroll2CacheItem::MakeCacheItem(node, false);
    caches->UpdateIsL1(cacheItem, true, false);
    EXPECT_TRUE(cacheItem->isL1_);
}

/**
 * @tc.name: ConvertFromToIndexTest033
 * @tc.desc: ConvertFromToIndex handles forward move range
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexTest033, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_MOVE_INDEX_1, TEST_MOVE_INDEX_3);
    EXPECT_EQ(caches->ConvertFromToIndex(TEST_MOVE_INDEX_1), TEST_MOVE_INDEX_2);
    EXPECT_EQ(caches->ConvertFromToIndex(TEST_MOVE_INDEX_2), TEST_MOVE_INDEX_3);
}

/**
 * @tc.name: ConvertFromToIndexTest034
 * @tc.desc: ConvertFromToIndex handles backward move range
 * @tc.type: FUNC
 */
HWTEST_F(RepeatVirtual2CachesTestNg, ConvertFromToIndexTest034, TestSize.Level1)
{
    auto caches = CreateCachesWithMockCallback();
    caches->UpdateMoveFromTo(TEST_MOVE_INDEX_3, TEST_MOVE_INDEX_1);
    EXPECT_EQ(caches->ConvertFromToIndex(TEST_MOVE_INDEX_3), TEST_MOVE_INDEX_2);
    EXPECT_EQ(caches->ConvertFromToIndex(TEST_MOVE_INDEX_2), TEST_MOVE_INDEX_1);
}

} // namespace OHOS::Ace::NG

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

#include <gtest/gtest.h>

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/rich_editor/lru_cache.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr size_t CACHE_CAPACITY_SMALL = 3;
constexpr size_t CACHE_CAPACITY_MEDIUM = 5;
constexpr int32_t KEY_FIRST = 1;
constexpr int32_t KEY_SECOND = 2;
constexpr int32_t KEY_THIRD = 3;
constexpr int32_t KEY_FOURTH = 4;
constexpr int32_t KEY_FIFTH = 5;
const std::string VALUE_ALPHA = "alpha";
const std::string VALUE_BETA = "beta";
const std::string VALUE_GAMMA = "gamma";
const std::string VALUE_DELTA = "delta";
const std::string VALUE_UPDATED = "updated";
} // namespace

class LRUMapTestNg : public testing::Test {
public:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: LRUMapPutAndGet001
 * @tc.desc: Test LRUMap Put and Get basic operations
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapPutAndGet001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    auto it = cache->Get(KEY_FIRST);
    EXPECT_NE(it, cache->End());
    EXPECT_EQ(it->second, VALUE_ALPHA);
}

/**
 * @tc.name: LRUMapGetNonExistent001
 * @tc.desc: Test LRUMap Get returns End for non-existent key
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapGetNonExistent001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    auto it = cache->Get(KEY_FIRST);
    EXPECT_EQ(it, cache->End());
    EXPECT_EQ(cache->Size(), static_cast<size_t>(0));
}

/**
 * @tc.name: LRUMapUpdateExisting001
 * @tc.desc: Test LRUMap Put updates value for existing key and keeps size as 1
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapUpdateExisting001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_FIRST, VALUE_UPDATED);
    auto it = cache->Get(KEY_FIRST);
    EXPECT_NE(it, cache->End());
    EXPECT_EQ(it->second, VALUE_UPDATED);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(1));
}

/**
 * @tc.name: LRUMapEvictionPolicy001
 * @tc.desc: Test LRUMap evicts least recently used item when capacity exceeded
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapEvictionPolicy001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>(CACHE_CAPACITY_SMALL);
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    cache->Put(KEY_THIRD, VALUE_GAMMA);
    // Cache is full, adding KEY_FOURTH should evict KEY_FIRST (LRU)
    cache->Put(KEY_FOURTH, VALUE_DELTA);
    EXPECT_EQ(cache->Get(KEY_FIRST), cache->End());
    EXPECT_NE(cache->Get(KEY_SECOND), cache->End());
    EXPECT_NE(cache->Get(KEY_THIRD), cache->End());
    EXPECT_NE(cache->Get(KEY_FOURTH), cache->End());
    EXPECT_EQ(cache->Size(), CACHE_CAPACITY_SMALL);
}

/**
 * @tc.name: LRUMapAccessUpdatesOrder001
 * @tc.desc: Test LRUMap Get promotes accessed item, preventing it from being evicted first
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapAccessUpdatesOrder001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>(CACHE_CAPACITY_SMALL);
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    cache->Put(KEY_THIRD, VALUE_GAMMA);
    // Access KEY_FIRST to move it to most recently used
    cache->Get(KEY_FIRST);
    // Adding KEY_FOURTH should evict KEY_SECOND (now LRU)
    cache->Put(KEY_FOURTH, VALUE_DELTA);
    EXPECT_NE(cache->Get(KEY_FIRST), cache->End());
    EXPECT_EQ(cache->Get(KEY_SECOND), cache->End());
    EXPECT_NE(cache->Get(KEY_THIRD), cache->End());
    EXPECT_NE(cache->Get(KEY_FOURTH), cache->End());
}

/**
 * @tc.name: LRUMapErase001
 * @tc.desc: Test LRUMap Erase removes specified key
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapErase001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    cache->Erase(KEY_FIRST);
    EXPECT_EQ(cache->Get(KEY_FIRST), cache->End());
    EXPECT_NE(cache->Get(KEY_SECOND), cache->End());
    EXPECT_EQ(cache->Size(), static_cast<size_t>(1));
}

/**
 * @tc.name: LRUMapEraseNonExistent001
 * @tc.desc: Test LRUMap Erase on non-existent key does not affect other entries
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapEraseNonExistent001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Erase(KEY_SECOND);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(1));
    EXPECT_NE(cache->Get(KEY_FIRST), cache->End());
}

/**
 * @tc.name: LRUMapClear001
 * @tc.desc: Test LRUMap Clear removes all entries
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapClear001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    cache->Clear();
    EXPECT_EQ(cache->Size(), static_cast<size_t>(0));
    EXPECT_EQ(cache->Get(KEY_FIRST), cache->End());
    EXPECT_EQ(cache->Get(KEY_SECOND), cache->End());
}

/**
 * @tc.name: LRUMapSizeTracking001
 * @tc.desc: Test LRUMap Size accurately tracks Put, Erase operations
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapSizeTracking001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    EXPECT_EQ(cache->Size(), static_cast<size_t>(0));
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(1));
    cache->Put(KEY_SECOND, VALUE_BETA);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(2));
    // Update existing key should not change size
    cache->Put(KEY_FIRST, VALUE_UPDATED);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(2));
    cache->Erase(KEY_FIRST);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(1));
}

/**
 * @tc.name: LRUMapSetCapacityShrink001
 * @tc.desc: Test LRUMap SetCapacity evicts oldest entries when shrinking below current size
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapSetCapacityShrink001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    cache->Put(KEY_THIRD, VALUE_GAMMA);
    cache->Put(KEY_FOURTH, VALUE_DELTA);
    ASSERT_EQ(cache->Size(), static_cast<size_t>(4));
    // Shrink capacity to 2, should evict 2 oldest items
    cache->SetCapacity(2);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(2));
    // Most recently added items should remain
    EXPECT_NE(cache->Get(KEY_THIRD), cache->End());
    EXPECT_NE(cache->Get(KEY_FOURTH), cache->End());
}

/**
 * @tc.name: LRUMapSetCapacityExpand001
 * @tc.desc: Test LRUMap SetCapacity with larger capacity preserves all entries
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapSetCapacityExpand001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>(CACHE_CAPACITY_SMALL);
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    cache->Put(KEY_SECOND, VALUE_BETA);
    // Expand capacity
    cache->SetCapacity(CACHE_CAPACITY_MEDIUM);
    cache->Put(KEY_THIRD, VALUE_GAMMA);
    cache->Put(KEY_FOURTH, VALUE_DELTA);
    cache->Put(KEY_FIFTH, VALUE_ALPHA);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(5));
    EXPECT_NE(cache->Get(KEY_FIRST), cache->End());
    EXPECT_NE(cache->Get(KEY_FIFTH), cache->End());
}

/**
 * @tc.name: LRUMapDefaultCapacityNoEviction001
 * @tc.desc: Test LRUMap with default capacity (SIZE_MAX) never evicts entries
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapDefaultCapacityNoEviction001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>();
    for (int32_t i = 0; i < 100; ++i) {
        cache->Put(i, "value" + std::to_string(i));
    }
    EXPECT_EQ(cache->Size(), static_cast<size_t>(100));
    EXPECT_NE(cache->Get(0), cache->End());
    EXPECT_NE(cache->Get(99), cache->End());
}

/**
 * @tc.name: LRUMapInitialCapacityConstructor001
 * @tc.desc: Test LRUMap constructor with initial capacity
 * @tc.type: FUNC
 */
HWTEST_F(LRUMapTestNg, LRUMapInitialCapacityConstructor001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<int, std::string>>(CACHE_CAPACITY_SMALL);
    EXPECT_EQ(cache->Size(), static_cast<size_t>(0));
    cache->Put(KEY_FIRST, VALUE_ALPHA);
    EXPECT_NE(cache->Get(KEY_FIRST), cache->End());
}
} // namespace OHOS::Ace::NG

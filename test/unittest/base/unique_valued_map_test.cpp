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

#include "gtest/gtest.h"

#include "base/utils/unique_valued_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class UniqueValuedMapTest : public testing::Test {
protected:
    UniqueValuedMap<int, std::string> map;
};

HWTEST_F(UniqueValuedMapTest, PutAndGet, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "two");

    EXPECT_EQ(map.Get(1).value(), "one");
    EXPECT_EQ(map.Get(2).value(), "two");
    EXPECT_EQ(map.Get(3), std::nullopt);
}

HWTEST_F(UniqueValuedMapTest, OverwriteKey, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(1, "uno");

    EXPECT_EQ(map.Get(1).value(), "uno");
    EXPECT_EQ(map.ContainsValue("one"), false);
}

HWTEST_F(UniqueValuedMapTest, OverwriteValue, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "one");

    EXPECT_EQ(map.Get(2).value(), "one");
    EXPECT_EQ(map.ContainsKey(1), false);
}

HWTEST_F(UniqueValuedMapTest, RemoveByKey, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "two");

    map.Remove(1);

    EXPECT_EQ(map.Get(1), std::nullopt);
    EXPECT_EQ(map.ContainsValue("one"), false);
    EXPECT_EQ(map.Get(2).value(), "two");
}

HWTEST_F(UniqueValuedMapTest, RemoveByValue, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "two");

    map.RemoveValue("one");

    EXPECT_EQ(map.Get(1), std::nullopt);
    EXPECT_EQ(map.ContainsKey(1), false);
    EXPECT_EQ(map.Get(2).value(), "two");
}

HWTEST_F(UniqueValuedMapTest, ContainsKeyAndValue, TestSize.Level1)
{
    map.Put(1, "one");

    EXPECT_TRUE(map.ContainsKey(1));
    EXPECT_TRUE(map.ContainsValue("one"));
    EXPECT_FALSE(map.ContainsKey(2));
    EXPECT_FALSE(map.ContainsValue("two"));
}

HWTEST_F(UniqueValuedMapTest, Clear, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "two");

    map.Clear();

    EXPECT_EQ(map.Size(), 0);
    EXPECT_FALSE(map.ContainsKey(1));
    EXPECT_FALSE(map.ContainsValue("one"));
}

HWTEST_F(UniqueValuedMapTest, Size, TestSize.Level1)
{
    EXPECT_EQ(map.Size(), 0);

    map.Put(1, "one");
    EXPECT_EQ(map.Size(), 1);

    map.Put(2, "two");
    EXPECT_EQ(map.Size(), 2);

    map.Remove(1);
    EXPECT_EQ(map.Size(), 1);
}

/**
 * @tc.name: RemoveIfFunction
 * @tc.desc: Test the RemoveIf functionality of UniqueValuedMap
 * @tc.type: FUNC
 */
HWTEST_F(UniqueValuedMapTest, RemoveIfFunction, TestSize.Level1)
{
    map.Put(1, "one");
    map.Put(2, "two");
    map.Put(3, "three");
    map.Put(4, "four");

    // Remove elements where key is even
    map.RemoveIf([](const int& key, const std::string&) {
        return key % 2 == 0;
    });

    EXPECT_EQ(map.Size(), 2);
    EXPECT_TRUE(map.ContainsKey(1));
    EXPECT_TRUE(map.ContainsKey(3));
    EXPECT_FALSE(map.ContainsKey(2));
    EXPECT_FALSE(map.ContainsKey(4));
    EXPECT_TRUE(map.ContainsValue("one"));
    EXPECT_TRUE(map.ContainsValue("three"));
    EXPECT_FALSE(map.ContainsValue("two"));
    EXPECT_FALSE(map.ContainsValue("four"));

    // Remove elements where value contains 'e'
    map.RemoveIf([](const int&, const std::string& value) {
        return value.find('e') != std::string::npos;
    });

    EXPECT_EQ(map.Size(), 0);
    EXPECT_FALSE(map.ContainsKey(1));
    EXPECT_FALSE(map.ContainsKey(3));
    EXPECT_FALSE(map.ContainsValue("one"));
    EXPECT_FALSE(map.ContainsValue("three"));

    // Test with empty predicate
    map.Put(1, "one");
    map.RemoveIf(nullptr);
    EXPECT_EQ(map.Size(), 1);
    EXPECT_TRUE(map.ContainsKey(1));
    EXPECT_TRUE(map.ContainsValue("one"));
}

HWTEST_F(UniqueValuedMapTest, SwapFunction, TestSize.Level1)
{
    // Swap two existing keys
    map.Put(1, "one");
    map.Put(2, "two");
    map.Swap(1, 2);
    auto v1 = map.Get(1);
    auto v2 = map.Get(2);
    ASSERT_TRUE(v1.has_value());
    ASSERT_TRUE(v2.has_value());
    EXPECT_EQ(v1.value(), "two");
    EXPECT_EQ(v2.value(), "one");
    auto k1 = map.GetKey("one");
    auto k2 = map.GetKey("two");
    ASSERT_TRUE(k1.has_value());
    ASSERT_TRUE(k2.has_value());
    EXPECT_EQ(k1.value(), 2);
    EXPECT_EQ(k2.value(), 1);

    // Swap back
    map.Swap(1, 2);
    v1 = map.Get(1);
    v2 = map.Get(2);
    ASSERT_TRUE(v1.has_value());
    ASSERT_TRUE(v2.has_value());
    EXPECT_EQ(v1.value(), "one");
    EXPECT_EQ(v2.value(), "two");

    // Swap with self (should be no-op)
    map.Swap(1, 1);
    v1 = map.Get(1);
    v2 = map.Get(2);
    ASSERT_TRUE(v1.has_value());
    ASSERT_TRUE(v2.has_value());
    EXPECT_EQ(v1.value(), "one");
    EXPECT_EQ(v2.value(), "two");

    // Swap with non-existent key (should be no-op)
    map.Swap(1, 3);
    v1 = map.Get(1);
    v2 = map.Get(2);
    auto v3 = map.Get(3);
    ASSERT_TRUE(v1.has_value());
    ASSERT_TRUE(v2.has_value());
    EXPECT_EQ(v1.value(), "one");
    EXPECT_EQ(v2.value(), "two");
    EXPECT_EQ(v3, std::nullopt);

    // Swap when both keys do not exist (should be no-op)
    map.Swap(4, 5); // 4 and 5 are not present
    EXPECT_EQ(map.Get(4), std::nullopt);
    EXPECT_EQ(map.Get(5), std::nullopt);

    // Swap when values are the same
    map.Put(3, "two"); // This will remove key 2
    map.Put(2, "three");
    map.Swap(2, 3);
    auto v2b = map.Get(2);
    auto v3b = map.Get(3);
    ASSERT_TRUE(v2b.has_value());
    ASSERT_TRUE(v3b.has_value());
    EXPECT_EQ(v2b.value(), "two");
    EXPECT_EQ(v3b.value(), "three");
    auto k2b = map.GetKey("two");
    auto k3b = map.GetKey("three");
    ASSERT_TRUE(k2b.has_value());
    ASSERT_TRUE(k3b.has_value());
    EXPECT_EQ(k2b.value(), 2);
    EXPECT_EQ(k3b.value(), 3);
}
} // namespace OHOS::Ace

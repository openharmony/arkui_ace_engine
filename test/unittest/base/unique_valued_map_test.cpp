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
} // namespace OHOS::Ace

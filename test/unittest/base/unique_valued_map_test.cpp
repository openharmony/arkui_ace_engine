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

#include "frameworks/base/utils/unique_valued_map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class UniqueValuedMapTest : public testing::Test {
protected:
    UniqueValuedMap<int, std::string> map;
};

HWTEST_F(UniqueValuedMapTest, PutAndGet, TestSize.Level1)
{
    map.put(1, "one");
    map.put(2, "two");

    EXPECT_EQ(map.get(1).value(), "one");
    EXPECT_EQ(map.get(2).value(), "two");
    EXPECT_EQ(map.get(3), std::nullopt);
}

HWTEST_F(UniqueValuedMapTest, OverwriteKey, TestSize.Level1)
{
    map.put(1, "one");
    map.put(1, "uno");

    EXPECT_EQ(map.get(1).value(), "uno");
    EXPECT_EQ(map.containsValue("one"), false);
}

HWTEST_F(UniqueValuedMapTest, OverwriteValue, TestSize.Level1)
{
    map.put(1, "one");
    map.put(2, "one");

    EXPECT_EQ(map.get(2).value(), "one");
    EXPECT_EQ(map.containsKey(1), false);
}

HWTEST_F(UniqueValuedMapTest, RemoveByKey, TestSize.Level1)
{
    map.put(1, "one");
    map.put(2, "two");

    map.remove(1);

    EXPECT_EQ(map.get(1), std::nullopt);
    EXPECT_EQ(map.containsValue("one"), false);
    EXPECT_EQ(map.get(2).value(), "two");
}

HWTEST_F(UniqueValuedMapTest, RemoveByValue, TestSize.Level1)
{
    map.put(1, "one");
    map.put(2, "two");

    map.removeValue("one");

    EXPECT_EQ(map.get(1), std::nullopt);
    EXPECT_EQ(map.containsKey(1), false);
    EXPECT_EQ(map.get(2).value(), "two");
}

HWTEST_F(UniqueValuedMapTest, ContainsKeyAndValue, TestSize.Level1)
{
    map.put(1, "one");

    EXPECT_TRUE(map.containsKey(1));
    EXPECT_TRUE(map.containsValue("one"));
    EXPECT_FALSE(map.containsKey(2));
    EXPECT_FALSE(map.containsValue("two"));
}

HWTEST_F(UniqueValuedMapTest, Clear, TestSize.Level1)
{
    map.put(1, "one");
    map.put(2, "two");

    map.clear();

    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.containsKey(1));
    EXPECT_FALSE(map.containsValue("one"));
}

HWTEST_F(UniqueValuedMapTest, Size, TestSize.Level1)
{
    EXPECT_EQ(map.size(), 0);

    map.put(1, "one");
    EXPECT_EQ(map.size(), 1);

    map.put(2, "two");
    EXPECT_EQ(map.size(), 2);

    map.remove(1);
    EXPECT_EQ(map.size(), 1);
}
} // namespace OHOS::Ace

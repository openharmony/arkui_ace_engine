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

#include <cstdint>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <stdlib.h>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/container/list.h"
#include "base/container/map.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class SafeContainerTest : public testing::Test {};

/**
 * @tc.name: SafeListTest001
 * @tc.desc: Test SafeList construction and basic iterator operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest001, TestSize.Level1)
{
    SafeList<int> emptyContainer;
    EXPECT_EQ(emptyContainer.begin(), emptyContainer.end());
    SafeList<int> list = { 1, 2, 3 };
    auto endIt = list.end();
    --endIt;
    EXPECT_EQ(*endIt, 3);
    auto it1 = list.begin();
    auto it2 = it1;
    EXPECT_EQ(it1, it2);
    EXPECT_EQ(*it1, *it2);
}

/**
 * @tc.name: SafeListTest002
 * @tc.desc: Test SafeList emplace_back and push_back
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest002, TestSize.Level1)
{
    SafeList<int> list = { 1, 2, 3 };
    auto originalEnd = --list.end();
    list.emplace_back(4);
    EXPECT_EQ(*originalEnd, 3);
    EXPECT_EQ(list.back(), 4);
    list.push_back(5);
    EXPECT_EQ(list.back(), 5);
}

/**
 * @tc.name: SafeListTest003
 * @tc.desc: Test SafeList iterator boundary and movement
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest003, TestSize.Level1)
{
    SafeList<int> list = { 1, 2, 3 };
    auto endIt = list.end();
    ++endIt;
    EXPECT_EQ(*endIt, 1);
    --endIt;
    EXPECT_EQ(endIt, list.end());
    --endIt;
    EXPECT_EQ(*endIt, 3);
    ++endIt;
    EXPECT_EQ(endIt, list.end());
}

/**
 * @tc.name: SafeListTest004
 * @tc.desc: Test SafeList element modification and assignment
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest004, TestSize.Level1)
{
    SafeList<int> list = { 1, 2, 3 };
    auto it = list.begin();
    *it = 10;
    EXPECT_EQ(*list.begin(), 10);
    auto originalIt = it;
    ++it;
    EXPECT_NE(originalIt, it);
}

/**
 * @tc.name: SafeListTest005
 * @tc.desc: Test SafeList reverse iterators
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest005, TestSize.Level1)
{
    SafeList<int> list = { 1, 2, 3, 4, 5 };
    std::vector<int> reversed;
    for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
        reversed.push_back(*rit);
    }
    EXPECT_EQ(reversed, (std::vector<int> { 5, 4, 3, 2, 1 }));
    auto rit = list.rbegin();
    EXPECT_EQ(*rit, 5);
    ++rit;
    EXPECT_EQ(*rit, 4);
}

/**
 * @tc.name: SafeListTest006
 * @tc.desc: Test SafeList modification operations (insert/erase)
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest006, TestSize.Level1)
{
    SafeList<int> list = { 1, 2, 3 };
    auto it = list.insert(list.begin(), 0);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(*it, 0);
    it = list.erase(it);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(*it, 1);
}

/**
 * @tc.name: SafeListTest007
 * @tc.desc: Test SafeList sort and unique operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest007, TestSize.Level1)
{
    SafeList<int> list = { 3, 1, 5, 1, 4 };
    list.sort();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 5);
    list.unique();
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(*(++list.begin()), 3);
}

/**
 * @tc.name: SafeListTest008
 * @tc.desc: Test SafeList merge and splice operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest008, TestSize.Level1)
{
    SafeList<int> list1 = { 1, 3, 5 };
    SafeList<int> list2 = { 2, 4, 6 };
    list1.merge(list2);
    EXPECT_EQ(list1.size(), 6);
    EXPECT_EQ(list1.back(), 6);
    EXPECT_TRUE(list2.empty());
    SafeList<int> list3 = { 7, 8 };
    list1.splice(list1.end(), list3);
    EXPECT_EQ(list1.back(), 8);
}

/**
 * @tc.name: SafeListTest009
 * @tc.desc: Test SafeList special operations (swap/resize)
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest009, TestSize.Level1)
{
    SafeList<int> list1 = { 1, 2, 3 };
    SafeList<int> list2 = { 4, 5 };
    list1.swap(list2);
    EXPECT_EQ(list1.front(), 4);
    EXPECT_EQ(list2.front(), 1);
    list1.resize(5);
    EXPECT_EQ(list1.size(), 5);
    EXPECT_EQ(list1.back(), 0);
}

/**
 * @tc.name: SafeListTest010
 * @tc.desc: Test SafeList complex type operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest010, TestSize.Level1)
{
    struct Point {
        int x, y;
        bool operator<(const Point& other) const
        {
            return x < other.x;
        }
    };

    SafeList<Point> points { { 2, 3 }, { 1, 2 }, { 3, 4 } };
    points.sort();
    EXPECT_EQ(points.front().x, 1);
    points.insert(points.end(), { 4, 5 });
    EXPECT_EQ(points.back().x, 4);
}

/**
 * @tc.name: SafeListTest011
 * @tc.desc: Test SafeList push_front pop_front pop_back 
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeListTest011, TestSize.Level1)
{
    SafeList<int> list { 1, 2, 3 };
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    list.push_front(4);
    EXPECT_EQ(list.front(), 4);
    int temp = 5;
    list.push_front(temp);
    EXPECT_EQ(list.front(), 5);
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    list.push_back(5);
    EXPECT_EQ(list.back(), 5);
}

/**
 * @tc.name: SafeMapTest001
 * @tc.desc: Test basic map operations and element access
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest001, TestSize.Level1)
{
    SafeMap<int, std::string> m;
    m[1] = "one";
    EXPECT_EQ(m[1], "one");
    m[1] = "new_one";
    EXPECT_EQ(m[1], "new_one");
    m.try_emplace(4, "four");
    EXPECT_EQ(m.at(4), "four");
    auto it = m.begin();
    it->second = "modified";
    EXPECT_EQ(m[1], "modified");
}

/**
 * @tc.name: SafeMapTest002
 * @tc.desc: Test map insertion methods
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest002, TestSize.Level1)
{
    SafeMap<int, std::string> m;
    auto [it1, inserted1] = m.try_emplace(1, "one");
    EXPECT_TRUE(inserted1);
    auto [it2, inserted2] = m.try_emplace(1, "duplicate");
    EXPECT_FALSE(inserted2);
    auto hint = m.find(1);
    m.insert(hint, { 2, "two" });
    EXPECT_EQ(m[2], "two");
    std::vector<std::pair<int, std::string>> data { { 3, "three" }, { 4, "four" } };
    m.insert(data.begin(), data.end());
    EXPECT_EQ(m.size(), 4);
}

/**
 * @tc.name: SafeMapTest003
 * @tc.desc: Test map erase operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest003, TestSize.Level1)
{
    SafeMap<int, std::string> m { { 1, "one" }, { 2, "two" }, { 3, "three" } };
    auto it = m.find(2);
    m.erase(it);
    EXPECT_EQ(m.size(), 2);
    size_t removed = m.erase(3);
    EXPECT_EQ(removed, 1);
    m.erase(m.begin(), m.end());
    EXPECT_TRUE(m.empty());
}

/**
 * @tc.name: SafeMapTest004
 * @tc.desc: Test map iteration and traversal
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest004, TestSize.Level1)
{
    SafeMap<int, std::string> m { { 1, "one" }, { 2, "two" }, { 3, "three" } };
    std::vector<int> keys;
    for (auto& pair : m) {
        keys.push_back(pair.first);
    }
    EXPECT_EQ(keys, (std::vector<int> { 1, 2, 3 }));
    std::vector<int> reverse_keys;
    for (auto rit = m.rbegin(); rit != m.rend(); ++rit) {
        reverse_keys.push_back(rit->first);
    }
    EXPECT_EQ(reverse_keys, (std::vector<int> { 3, 2, 1 }));
}

/**
 * @tc.name: SafeMapTest005
 * @tc.desc: Test map merge and swap operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest005, TestSize.Level1)
{
    SafeMap<int, std::string> m1 { { 1, "one" }, { 3, "three" } };
    SafeMap<int, std::string> m2 { { 2, "two" }, { 3, "new_three" } };
    m1.merge(m2);
    EXPECT_EQ(m1.size(), 3);
    EXPECT_EQ(m1[3], "three");
    m1.swap(m2);
    EXPECT_EQ(m2.size(), 3);
    EXPECT_EQ(m1.size(), 1);
}

/**
 * @tc.name: SafeMapTest006
 * @tc.desc: Test map special operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest006, TestSize.Level1)
{
    SafeMap<int, std::string> m { { 1, "one" }, { 2, "two" } };
    auto lb_it = m.lower_bound(1);
    EXPECT_EQ(lb_it->first, 1);
    auto ub_it = m.upper_bound(1);
    EXPECT_EQ(ub_it->first, 2);
    auto node = m.extract(1);
    EXPECT_TRUE(node);
    EXPECT_EQ(node.key(), 1);
}

/**
 * @tc.name: SafeMapTest007
 * @tc.desc: Test map copy/move operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest007, TestSize.Level1)
{
    SafeMap<int, std::string> original { { 1, "one" }, { 2, "two" } };
    SafeMap<int, std::string> copy(original);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[1], "one");
    SafeMap<int, std::string> moved(std::move(original));
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(moved.size(), 2);
}

/**
 * @tc.name: SafeMapTest008
 * @tc.desc: Test map capacity methods
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest008, TestSize.Level1)
{
    SafeMap<int, std::string> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
    m.emplace(1, "one");
    EXPECT_FALSE(m.empty());
    EXPECT_EQ(m.size(), 1);
}

/**
 * @tc.name: SafeMapTest009
 * @tc.desc: Test map lookup operations
 * @tc.type: FUNC
 */
HWTEST_F(SafeContainerTest, SafeMapTest009, TestSize.Level1)
{
    SafeMap<int, std::string> m { { 1, "one" }, { 2, "two" } };
    EXPECT_EQ(m.count(1), 1);
    EXPECT_EQ(m.count(3), 0);
    auto it1 = m.find(3);
    EXPECT_EQ(it1, m.end());
    auto it2 = m.find(2);
    EXPECT_NE(it2, m.end());
}
} // namespace OHOS::Ace
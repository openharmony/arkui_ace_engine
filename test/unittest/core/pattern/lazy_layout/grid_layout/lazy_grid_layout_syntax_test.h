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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_LAZY_FOR_EACH_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_LAZY_FOR_EACH_TEST_H

#include "test/unittest/core/pattern/lazy_layout/grid_layout/lazy_grid_layout_test.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class LazyGridLayoutSyntaxTest : public LazyGridLayoutTest {
public:
    static void SetUpTestSuite()
    {
        LazyGridLayoutTest::SetUpTestSuite();
    }

    static void TearDownTestSuite()
    {
        LazyGridLayoutTest::TearDownTestSuite();
    }

    void SetUp() override
    {
        LazyGridLayoutTest::SetUp();
    }

    void TearDown() override
    {
        LazyGridLayoutTest::TearDown();
    }

    void CreateRepeatVirtualScrollNode(
        int32_t itemNumber, const std::function<std::pair<uint32_t, uint32_t>(int32_t, bool)>& createFunc);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_LAZY_FOR_EACH_TEST_H

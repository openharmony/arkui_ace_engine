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

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "frameworks/core/components_ng/syntax/arkoala_lazy_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ArkoalaLazyNodeTest : public TestNG {};

TEST_F(ArkoalaLazyNodeTest, ArkoalaLazyNodeTest001)
{
    auto lazyNode = AceType::MakeRefPtr<ArkoalaLazyNode>(-1);
    EXPECT_EQ(lazyNode->GetTag(), V2::JS_LAZY_FOR_EACH_ETS_TAG);
    lazyNode->SetCallbacks([](int32_t idx) { return ColumnModelNG::CreateFrameNode(-1); },
        [](int32_t start, int32_t end) {
            EXPECT_EQ(start, 8);
            EXPECT_EQ(end, 8);
        });
    lazyNode->SetTotalCount(10);

    EXPECT_EQ(lazyNode->FrameCount(), 10);
    EXPECT_FALSE(lazyNode->GetFrameNode(9));
    EXPECT_FALSE(lazyNode->GetFrameChildByIndex(9, false, false, false));
    EXPECT_TRUE(lazyNode->GetFrameChildByIndex(9, true, false, true));
    auto child = lazyNode->GetFrameNode(9);
    EXPECT_TRUE(child);
    EXPECT_TRUE(child->IsActive());

    EXPECT_TRUE(lazyNode->GetFrameChildByIndex(8, true, false, true));
    lazyNode->DoSetActiveChildRange(8, 8, 0, 0, false);
    EXPECT_FALSE(lazyNode->GetFrameNode(9));
    EXPECT_TRUE(lazyNode->GetFrameNode(8)->IsActive());
}
} // namespace OHOS::Ace::NG
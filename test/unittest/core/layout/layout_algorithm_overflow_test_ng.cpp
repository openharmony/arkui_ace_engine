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
#include "test/unittest/core/layout/layout_property_test_ng.h"
#include "frameworks/core/components_ng/layout/layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "base/memory/ace_type.h"

#define protected public
#define private public

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class LayoutAlgorithmOverflowTestNg : public TestNG {};

/**
 * @tc.name: LayoutAlgorithmShouldDoOverflowWorkTest
 * @tc.desc: Test ShouldDoOverflowWork method
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmShouldDoOverflowWorkTest, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    bool result = layoutAlgorithm->ShouldDoOverflowWork();
    // The actual result depends on the global configuration
    EXPECT_TRUE(result); // Placeholder to ensure test compiles and runs
}

/**
 * @tc.name: LayoutAlgorithmIsContentOverflowTest
 * @tc.desc: Test IsContentOverflow method
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmOverflowTestNg, LayoutAlgorithmIsContentOverflowTest, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode("test", 10, AceType::MakeRefPtr<Pattern>());
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);

    OverflowCollector collector(false);

    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();

    // Test with null layout wrapper
    bool result = layoutAlgorithm->IsContentOverflow(nullptr, collector);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/pattern.h"
#undef protected
#undef private

#include "test/unittest/core/pattern/dynamiclayout/mock_layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "LazyDynamicLayout";
}

class LazyDynamicLayoutPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: LazyDynamicLayoutPattern_CreateLayoutAlgorithm_001
 * @tc.desc: Test CreateLayoutAlgorithm with CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_CreateLayoutAlgorithm_001, TestSize.Level1)
{
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    LazyDynamicLayoutPattern pattern(customParams);

    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto lazyDynamicLayoutAlgorithm = AceType::DynamicCast<LazyDynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(lazyDynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: LazyDynamicLayoutPattern_CreateLayoutAlgorithm_002
 * @tc.desc: Test CreateLayoutAlgorithm without CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_CreateLayoutAlgorithm_002, TestSize.Level1)
{
    LazyDynamicLayoutPattern pattern;

    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto lazyDynamicLayoutAlgorithm = AceType::DynamicCast<LazyDynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(lazyDynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: LazyDynamicLayoutPattern_IsAtomicNode_001
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_IsAtomicNode_001, TestSize.Level1)
{
    LazyDynamicLayoutPattern pattern;
    EXPECT_FALSE(pattern.IsAtomicNode());
}
} // namespace OHOS::Ace::NG
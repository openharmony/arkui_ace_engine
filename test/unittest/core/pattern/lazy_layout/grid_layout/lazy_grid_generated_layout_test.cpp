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
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/base/frame_node.h"
#undef protected
#undef private

#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "LazyGrid";
}

class LazyGridGeneratedLayoutTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    }

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }
};

/**
 * @tc.name: LazyGridLayoutPattern_SetDynamicLayoutOptions_001
 * @tc.desc: Test SetDynamicLayoutOptions with true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutPattern_SetDynamicLayoutOptions_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options to true
     */
    pattern->SetDynamicLayoutOptions(true);

    /**
     * @tc.steps: step3. Verify IsDynamicLayout returns true
     * @tc.expected: Should return true
     */
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_SetDynamicLayoutOptions_002
 * @tc.desc: Test SetDynamicLayoutOptions with false
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutPattern_SetDynamicLayoutOptions_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options to false
     */
    pattern->SetDynamicLayoutOptions(false);

    /**
     * @tc.steps: step3. Verify IsDynamicLayout returns false
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_IsDynamicLayout_Default_001
 * @tc.desc: Test IsDynamicLayout default value
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutPattern_IsDynamicLayout_Default_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern without setting options
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Verify IsDynamicLayout returns false by default
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutPattern_CreateLayoutAlgorithm_WithDynamicLayout_001
 * @tc.desc: Test CreateLayoutAlgorithm when isDynamicLayout is true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutPattern_CreateLayoutAlgorithm_WithDynamicLayout_001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern and set dynamic layout
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    pattern->SetDynamicLayoutOptions(true);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm
     */
    auto algorithm = pattern->CreateLayoutAlgorithm();

    /**
     * @tc.steps: step3. Verify algorithm is created and has dynamic layout flag
     * @tc.expected: Should return valid LazyGridLayoutAlgorithm with isDynamicLayout=true
     */
    ASSERT_NE(algorithm, nullptr);
    auto gridAlgorithm = AceType::DynamicCast<LazyGridLayoutAlgorithm>(algorithm);
    ASSERT_NE(gridAlgorithm, nullptr);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_001
 * @tc.desc: Test SetDynamicLayout with true
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout to true
     */
    algorithm->SetDynamicLayout(true);

    /**
     * @tc.steps: step3. Verify flag is set
     * @tc.expected: isDynamicLayout_ should be true
     */
    EXPECT_TRUE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_002
 * @tc.desc: Test SetDynamicLayout with false
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout to false
     */
    algorithm->SetDynamicLayout(false);

    /**
     * @tc.steps: step3. Verify flag is set
     * @tc.expected: isDynamicLayout_ should be false
     */
    EXPECT_FALSE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_SetDynamicLayout_Default_001
 * @tc.desc: Test SetDynamicLayout default value
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutAlgorithm_SetDynamicLayout_Default_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm without setting dynamic layout
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Verify default isDynamicLayout is false
     * @tc.expected: isDynamicLayout_ should be false by default
     */
    EXPECT_FALSE(algorithm->isDynamicLayout_);
}

/**
 * @tc.name: LazyGridLayoutPattern_MultipleSetDynamicLayoutOptions_001
 * @tc.desc: Test SetDynamicLayoutOptions called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutPattern_MultipleSetDynamicLayoutOptions_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();

    /**
     * @tc.steps: step2. Set dynamic layout options multiple times
     */
    pattern->SetDynamicLayoutOptions(true);
    EXPECT_TRUE(pattern->IsDynamicLayout());

    pattern->SetDynamicLayoutOptions(false);
    EXPECT_FALSE(pattern->IsDynamicLayout());

    pattern->SetDynamicLayoutOptions(true);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: LazyGridLayoutAlgorithm_MultipleSetDynamicLayout_001
 * @tc.desc: Test SetDynamicLayout called multiple times
 * @tc.type: FUNC
 */
HWTEST_F(LazyGridGeneratedLayoutTest, LazyGridLayoutAlgorithm_MultipleSetDynamicLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LazyGridLayoutAlgorithm
     */
    auto layoutInfo = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    auto algorithm = AceType::MakeRefPtr<LazyGridLayoutAlgorithm>(layoutInfo);

    /**
     * @tc.steps: step2. Set dynamic layout multiple times
     */
    algorithm->SetDynamicLayout(true);
    EXPECT_TRUE(algorithm->isDynamicLayout_);

    algorithm->SetDynamicLayout(false);
    EXPECT_FALSE(algorithm->isDynamicLayout_);

    algorithm->SetDynamicLayout(true);
    EXPECT_TRUE(algorithm->isDynamicLayout_);
}

} // namespace OHOS::Ace::NG

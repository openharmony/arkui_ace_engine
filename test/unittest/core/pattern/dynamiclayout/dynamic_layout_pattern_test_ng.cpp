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
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/pattern.h"
#undef protected
#undef private

#include "test/unittest/core/pattern/dynamiclayout/mock_layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG = "DynamicLayout";
}

class DynamicLayoutPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: DynamicLayoutPattern_CreateLayoutAlgorithm_001
 * @tc.desc: Test CreateLayoutAlgorithm with CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_CreateLayoutAlgorithm_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutPattern with CustomLayoutAlgorithmParam
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    DynamicLayoutPattern pattern(customParams);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm
     * @tc.expected: Return non-null DynamicLayoutAlgorithm
     */
    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto dynamicLayoutAlgorithm = AceType::DynamicCast<DynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(dynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: DynamicLayoutPattern_CreateLayoutAlgorithm_002
 * @tc.desc: Test CreateLayoutAlgorithm without CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_CreateLayoutAlgorithm_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutPattern without parameters
     */
    DynamicLayoutPattern pattern;

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm
     * @tc.expected: Return non-null DynamicLayoutAlgorithm with null params
     */
    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto dynamicLayoutAlgorithm = AceType::DynamicCast<DynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(dynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: DynamicLayoutPattern_IsAtomicNode_001
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_IsAtomicNode_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutPattern
     */
    DynamicLayoutPattern pattern;

    /**
     * @tc.steps: step2. Call IsAtomicNode
     * @tc.expected: Return false (DynamicLayout is a container, not atomic)
     */
    EXPECT_FALSE(pattern.IsAtomicNode());
}

/**
 * @tc.name: DynamicLayoutPattern_IsAtomicNode_002
 * @tc.desc: Test IsAtomicNode with CustomLayoutAlgorithmParam returns false
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_IsAtomicNode_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutPattern with CustomLayoutAlgorithmParam
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    DynamicLayoutPattern pattern(customParams);

    /**
     * @tc.steps: step2. Call IsAtomicNode
     * @tc.expected: Return false (DynamicLayout is always a container)
     */
    EXPECT_FALSE(pattern.IsAtomicNode());
}

/**
 * @tc.name: DynamicLayoutAlgorithm_Measure_001
 * @tc.desc: Test DynamicLayoutAlgorithm Measure with valid onMeasureSize callback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutAlgorithm_Measure_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam with onMeasureSize callback
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;
    customParams->SetOnMeasureSize([&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    });

    /**
     * @tc.steps: step2. Create DynamicLayoutAlgorithm with custom params
     */
    DynamicLayoutAlgorithm algorithm(customParams);

    /**
     * @tc.steps: step3. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step4. Call Measure
     * @tc.expected: onMeasureSize callback should be executed
     */
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: DynamicLayoutAlgorithm_Measure_002
 * @tc.desc: Test DynamicLayoutAlgorithm Measure without onMeasureSize callback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutAlgorithm_Measure_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam without callbacks
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Create DynamicLayoutAlgorithm with custom params
     */
    DynamicLayoutAlgorithm algorithm(customParams);

    /**
     * @tc.steps: step3. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step4. Call Measure
     * @tc.expected: Should not crash even without callback
     */
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: DynamicLayoutAlgorithm_Layout_001
 * @tc.desc: Test DynamicLayoutAlgorithm Layout with valid onPlaceChildren callback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutAlgorithm_Layout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam with onPlaceChildren callback
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;
    customParams->SetOnPlaceChildren([&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    });

    /**
     * @tc.steps: step2. Create DynamicLayoutAlgorithm with custom params
     */
    DynamicLayoutAlgorithm algorithm(customParams);

    /**
     * @tc.steps: step3. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step4. Call Layout
     * @tc.expected: onPlaceChildren callback should be executed
     */
    algorithm.Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: DynamicLayoutAlgorithm_Layout_002
 * @tc.desc: Test DynamicLayoutAlgorithm Layout without onPlaceChildren callback
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutAlgorithm_Layout_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam without callbacks
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Create DynamicLayoutAlgorithm with custom params
     */
    DynamicLayoutAlgorithm algorithm(customParams);

    /**
     * @tc.steps: step3. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step4. Call Layout
     * @tc.expected: Should not crash even without callback
     */
    algorithm.Layout(AceType::RawPtr(layoutWrapper));
}

/**
 * @tc.name: DynamicLayoutPattern_DefaultConstructor_001
 * @tc.desc: Test DynamicLayoutPattern default constructor initializes correctly
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_DefaultConstructor_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutPattern with default constructor
     * @tc.expected: Pattern should be created successfully
     */
    DynamicLayoutPattern pattern;
    auto algorithm = pattern.CreateLayoutAlgorithm();
    EXPECT_NE(algorithm, nullptr);
    EXPECT_FALSE(pattern.IsAtomicNode());
}

/**
 * @tc.name: DynamicLayoutPattern_ParamConstructor_001
 * @tc.desc: Test DynamicLayoutPattern parameterized constructor
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutPatternTestNg, DynamicLayoutPattern_ParamConstructor_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Create DynamicLayoutPattern with parameterized constructor
     * @tc.expected: Pattern should store custom params
     */
    DynamicLayoutPattern pattern(customParams);
    auto algorithm = pattern.CreateLayoutAlgorithm();
    EXPECT_NE(algorithm, nullptr);
    auto dynamicLayoutAlgorithm = AceType::DynamicCast<DynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(dynamicLayoutAlgorithm, nullptr);
}

} // namespace OHOS::Ace::NG

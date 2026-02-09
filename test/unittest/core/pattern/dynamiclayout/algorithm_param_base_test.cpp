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
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h"
#undef protected
#undef private

#include "test/unittest/core/pattern/dynamiclayout/mock_layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG = "DynamicLayout";
constexpr float TEST_SPACE_VALUE = 10.0f;
constexpr bool TEST_IS_REVERSE = true;
}

class AlgorithmParamBaseTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: AlgorithmParamBase_GetDynamicLayoutType_001
 * @tc.desc: Test GetDynamicLayoutType returns default DEFAULT_LAYOUT
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, AlgorithmParamBase_GetDynamicLayoutType_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AlgorithmParamBase
     */
    AlgorithmParamBase param;

    /**
     * @tc.steps: step2. Call GetDynamicLayoutType
     * @tc.expected: Should return DEFAULT_LAYOUT
     */
    EXPECT_EQ(param.GetDynamicLayoutType(), DynamicLayoutType::DEFAULT_LAYOUT);
}

/**
 * @tc.name: AlgorithmParamBase_SetDynamicLayoutType_001
 * @tc.desc: Test SetDynamicLayoutType with various types
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, AlgorithmParamBase_SetDynamicLayoutType_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AlgorithmParamBase
     */
    AlgorithmParamBase param;

    /**
     * @tc.steps: step2. Set different layout types
     * @tc.expected: GetDynamicLayoutType should return the set value
     */
    param.SetDynamicLayoutType(DynamicLayoutType::COLUMN_LAYOUT);
    EXPECT_EQ(param.GetDynamicLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);

    param.SetDynamicLayoutType(DynamicLayoutType::ROW_LAYOUT);
    EXPECT_EQ(param.GetDynamicLayoutType(), DynamicLayoutType::ROW_LAYOUT);

    param.SetDynamicLayoutType(DynamicLayoutType::STACK_LAYOUT);
    EXPECT_EQ(param.GetDynamicLayoutType(), DynamicLayoutType::STACK_LAYOUT);

    param.SetDynamicLayoutType(DynamicLayoutType::CUSTOM_LAYOUT);
    EXPECT_EQ(param.GetDynamicLayoutType(), DynamicLayoutType::CUSTOM_LAYOUT);
}

/**
 * @tc.name: LinearLayoutAlgorithmParam_Constructor_IsVertical_001
 * @tc.desc: Test LinearLayoutAlgorithmParam constructor with isVertical=true
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, LinearLayoutAlgorithmParam_Constructor_IsVertical_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam with isVertical=true
     */
    auto param = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);

    /**
     * @tc.steps: step2. Verify layout type is COLUMN_LAYOUT
     * @tc.expected: Should return COLUMN_LAYOUT
     */
    EXPECT_EQ(param->GetDynamicLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);
}

/**
 * @tc.name: LinearLayoutAlgorithmParam_Constructor_IsVertical_002
 * @tc.desc: Test LinearLayoutAlgorithmParam constructor with isVertical=false
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, LinearLayoutAlgorithmParam_Constructor_IsVertical_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam with isVertical=false
     */
    auto param = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(false);

    /**
     * @tc.steps: step2. Verify layout type is ROW_LAYOUT
     * @tc.expected: Should return ROW_LAYOUT
     */
    EXPECT_EQ(param->GetDynamicLayoutType(), DynamicLayoutType::ROW_LAYOUT);
}

/**
 * @tc.name: LinearLayoutAlgorithmParam_Constructor_Full_001
 * @tc.desc: Test LinearLayoutAlgorithmParam constructor with full parameters
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, LinearLayoutAlgorithmParam_Constructor_Full_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam with space and alignments
     */
    CalcDimension space(TEST_SPACE_VALUE, DimensionUnit::VP);
    auto param = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(
        space, FlexAlign::CENTER, FlexAlign::FLEX_END);

    /**
     * @tc.steps: step2. Verify properties are set correctly
     * @tc.expected: Getters should return the set values
     */
    EXPECT_EQ(param->GetSpace().Value(), TEST_SPACE_VALUE);
    EXPECT_EQ(param->GetMainAxisAlign(), FlexAlign::CENTER);
    EXPECT_EQ(param->GetCrossAxisAlign(), FlexAlign::FLEX_END);
}

/**
 * @tc.name: LinearLayoutAlgorithmParam_SetAndGet_001
 * @tc.desc: Test SetSpace, SetMainAxisAlign, SetCrossAxisAlign, SetIsReverse
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, LinearLayoutAlgorithmParam_SetAndGet_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam
     */
    auto param = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);

    /**
     * @tc.steps: step2. Set properties
     */
    CalcDimension space(TEST_SPACE_VALUE, DimensionUnit::VP);
    param->SetSpace(space);
    param->SetMainAxisAlign(FlexAlign::FLEX_END);
    param->SetCrossAxisAlign(FlexAlign::FLEX_START);
    param->SetIsReverse(TEST_IS_REVERSE);

    /**
     * @tc.steps: step3. Verify properties are set correctly
     * @tc.expected: Getters should return the set values
     */
    EXPECT_EQ(param->GetSpace().Value(), TEST_SPACE_VALUE);
    EXPECT_EQ(param->GetMainAxisAlign(), FlexAlign::FLEX_END);
    EXPECT_EQ(param->GetCrossAxisAlign(), FlexAlign::FLEX_START);
    EXPECT_EQ(param->IsReverse(), TEST_IS_REVERSE);
}

/**
 * @tc.name: StackLayoutAlgorithmParam_DefaultConstructor_001
 * @tc.desc: Test StackLayoutAlgorithmParam default constructor
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, StackLayoutAlgorithmParam_DefaultConstructor_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StackLayoutAlgorithmParam with default constructor
     */
    auto param = AceType::MakeRefPtr<StackLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Verify default values
     * @tc.expected: Should have STACK_LAYOUT type and CENTER alignment
     */
    EXPECT_EQ(param->GetDynamicLayoutType(), DynamicLayoutType::STACK_LAYOUT);
    EXPECT_EQ(param->GetAlignContent(), Alignment::CENTER);
}

/**
 * @tc.name: StackLayoutAlgorithmParam_Constructor_Alignment_001
 * @tc.desc: Test StackLayoutAlgorithmParam constructor with alignment
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, StackLayoutAlgorithmParam_Constructor_Alignment_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StackLayoutAlgorithmParam with TOP_LEFT alignment
     */
    auto param = AceType::MakeRefPtr<StackLayoutAlgorithmParam>(Alignment::TOP_LEFT);

    /**
     * @tc.steps: step2. Verify alignment is set
     * @tc.expected: Should return TOP_LEFT alignment
     */
    EXPECT_EQ(param->GetDynamicLayoutType(), DynamicLayoutType::STACK_LAYOUT);
    EXPECT_EQ(param->GetAlignContent(), Alignment::TOP_LEFT);
}

/**
 * @tc.name: StackLayoutAlgorithmParam_SetAlignContent_001
 * @tc.desc: Test SetAlignContent
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, StackLayoutAlgorithmParam_SetAlignContent_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create StackLayoutAlgorithmParam
     */
    auto param = AceType::MakeRefPtr<StackLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Set different alignments
     * @tc.expected: GetAlignContent should return the set value
     */
    param->SetAlignContent(Alignment::TOP_RIGHT);
    EXPECT_EQ(param->GetAlignContent(), Alignment::TOP_RIGHT);

    param->SetAlignContent(Alignment::BOTTOM_LEFT);
    EXPECT_EQ(param->GetAlignContent(), Alignment::BOTTOM_LEFT);

    param->SetAlignContent(Alignment::BOTTOM_RIGHT);
    EXPECT_EQ(param->GetAlignContent(), Alignment::BOTTOM_RIGHT);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_DefaultConstructor_001
 * @tc.desc: Test CustomLayoutAlgorithmParam default constructor
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_DefaultConstructor_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam with default constructor
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Verify default layout type
     * @tc.expected: Should have CUSTOM_LAYOUT type
     */
    EXPECT_EQ(param->GetDynamicLayoutType(), DynamicLayoutType::CUSTOM_LAYOUT);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_FireOnMeasureSize_001
 * @tc.desc: Test FireOnMeasureSize with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_FireOnMeasureSize_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam with onMeasureSize callback
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;
    param->SetOnMeasureSize([&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    });

    /**
     * @tc.steps: step2. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step3. Call FireOnMeasureSize
     * @tc.expected: Should return true and execute callback
     */
    auto result = param->FireOnMeasureSize(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_FireOnMeasureSize_002
 * @tc.desc: Test FireOnMeasureSize without callback
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_FireOnMeasureSize_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam without callback
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step3. Call FireOnMeasureSize
     * @tc.expected: Should return false and not crash
     */
    auto result = param->FireOnMeasureSize(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_FireOnPlaceChildren_001
 * @tc.desc: Test FireOnPlaceChildren with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_FireOnPlaceChildren_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam with onPlaceChildren callback
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;
    param->SetOnPlaceChildren([&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    });

    /**
     * @tc.steps: step2. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step3. Call FireOnPlaceChildren
     * @tc.expected: Should return true and execute callback
     */
    auto result = param->FireOnPlaceChildren(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_FireOnPlaceChildren_002
 * @tc.desc: Test FireOnPlaceChildren without callback
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_FireOnPlaceChildren_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam without callback
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Create MockLayoutWrapper
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    /**
     * @tc.steps: step3. Call FireOnPlaceChildren
     * @tc.expected: Should return false and not crash
     */
    auto result = param->FireOnPlaceChildren(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_SetOnMeasureSize_Move_001
 * @tc.desc: Test SetOnMeasureSize with move semantics
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_SetOnMeasureSize_Move_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;

    /**
     * @tc.steps: step2. SetOnMeasureSize with std::move
     */
    DynamicLayoutAlgorithmFunc callback = [&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    };
    param->SetOnMeasureSize(std::move(callback));

    /**
     * @tc.steps: step3. Create MockLayoutWrapper and call FireOnMeasureSize
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    auto result = param->FireOnMeasureSize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. Verify callback executed
     * @tc.expected: Should return true and execute callback
     */
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: CustomLayoutAlgorithmParam_SetOnPlaceChildren_Move_001
 * @tc.desc: Test SetOnPlaceChildren with move semantics
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, CustomLayoutAlgorithmParam_SetOnPlaceChildren_Move_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomLayoutAlgorithmParam
     */
    auto param = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool callbackExecuted = false;

    /**
     * @tc.steps: step2. SetOnPlaceChildren with std::move
     */
    DynamicLayoutAlgorithmFunc callback = [&callbackExecuted](LayoutWrapper* layoutWrapper) {
        callbackExecuted = true;
    };
    param->SetOnPlaceChildren(std::move(callback));

    /**
     * @tc.steps: step3. Create MockLayoutWrapper and call FireOnPlaceChildren
     */
    auto pattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    WeakPtr<FrameNode> hostNode(frameNode);
    auto layoutWrapper = AceType::MakeRefPtr<MockLayoutWrapper>(hostNode);

    auto result = param->FireOnPlaceChildren(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. Verify callback executed
     * @tc.expected: Should return true and execute callback
     */
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: LinearLayoutAlgorithmParam_IsReverse_Default_001
 * @tc.desc: Test IsReverse default value is false
 * @tc.type: FUNC
 */
HWTEST_F(AlgorithmParamBaseTest, LinearLayoutAlgorithmParam_IsReverse_Default_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LinearLayoutAlgorithmParam
     */
    auto param = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);

    /**
     * @tc.steps: step2. Verify default IsReverse is false
     * @tc.expected: Should return false
     */
    EXPECT_FALSE(param->IsReverse());
}

} // namespace OHOS::Ace::NG

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
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_model_static.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "LazyDynamicLayoutModelStatic";
constexpr int32_t TEST_NODE_ID = 1001;
constexpr float TEST_ADJUSTED_OFFSET = 50.0f;
}

class LazyDynamicLayoutModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: LazyDynamicLayoutModelStatic_CreateFrameNode_001
 * @tc.desc: Test CreateFrameNode creates valid FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_CreateFrameNode_001, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), "LazyDynamicLayout");
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_CreateFrameNode_002
 * @tc.desc: Test CreateFrameNode with different node IDs
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_CreateFrameNode_002, TestSize.Level1)
{
    constexpr int32_t nodeId1 = 100;
    constexpr int32_t nodeId2 = 200;
    
    auto frameNode1 = LazyDynamicLayoutModelStatic::CreateFrameNode(nodeId1);
    auto frameNode2 = LazyDynamicLayoutModelStatic::CreateFrameNode(nodeId2);
    
    ASSERT_NE(frameNode1, nullptr);
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_NE(frameNode1, frameNode2);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetParams_001
 * @tc.desc: Test SetParams with valid params
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetParams_001, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    customParams->SetAxis(Axis::FREE);
    
    LazyDynamicLayoutModelStatic::SetParams(AceType::RawPtr(frameNode), customParams);
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto retrievedParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(retrievedParams, nullptr);
    EXPECT_EQ(retrievedParams->GetAxis(), Axis::FREE);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetParams_002
 * @tc.desc: Test SetParams with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetParams_002, TestSize.Level1)
{
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    FrameNode* nullFrameNode = nullptr;
    
    LazyDynamicLayoutModelStatic::SetParams(nullFrameNode, customParams);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetParams_003
 * @tc.desc: Test SetParams with null params
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetParams_003, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    RefPtr<LazyCustomLayoutAlgorithmParam> nullParams = nullptr;
    LazyDynamicLayoutModelStatic::SetParams(AceType::RawPtr(frameNode), nullParams);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetAdjustedOffset_001
 * @tc.desc: Test SetAdjustedOffset with valid offset
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetAdjustedOffset_001, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    LazyDynamicLayoutModelStatic::SetAdjustedOffset(AceType::RawPtr(frameNode), TEST_ADJUSTED_OFFSET);
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(customParams, nullptr);
    EXPECT_FLOAT_EQ(customParams->GetAdjustedOffset(), TEST_ADJUSTED_OFFSET);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetAdjustedOffset_002
 * @tc.desc: Test SetAdjustedOffset with negative offset
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetAdjustedOffset_002, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    constexpr float negativeOffset = -100.0f;
    LazyDynamicLayoutModelStatic::SetAdjustedOffset(AceType::RawPtr(frameNode), negativeOffset);
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(customParams, nullptr);
    EXPECT_FLOAT_EQ(customParams->GetAdjustedOffset(), negativeOffset);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetAdjustedOffset_003
 * @tc.desc: Test SetAdjustedOffset with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetAdjustedOffset_003, TestSize.Level1)
{
    FrameNode* nullFrameNode = nullptr;
    LazyDynamicLayoutModelStatic::SetAdjustedOffset(nullFrameNode, TEST_ADJUSTED_OFFSET);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetInActiveChildren_001
 * @tc.desc: Test SetInActiveChildren with valid children list
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetInActiveChildren_001, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    std::vector<int32_t> inActiveChildren = {1, 2, 3, 4, 5};
    LazyDynamicLayoutModelStatic::SetInActiveChildren(AceType::RawPtr(frameNode), inActiveChildren);
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(customParams, nullptr);
    auto retrievedChildren = customParams->GetInActiveChildren();
    EXPECT_EQ(retrievedChildren.size(), inActiveChildren.size());
    for (size_t i = 0; i < inActiveChildren.size(); ++i) {
        EXPECT_EQ(retrievedChildren[i], inActiveChildren[i]);
    }
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetInActiveChildren_002
 * @tc.desc: Test SetInActiveChildren with empty children list
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetInActiveChildren_002, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    std::vector<int32_t> emptyChildren;
    LazyDynamicLayoutModelStatic::SetInActiveChildren(AceType::RawPtr(frameNode), emptyChildren);
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(customParams, nullptr);
    auto retrievedChildren = customParams->GetInActiveChildren();
    EXPECT_EQ(retrievedChildren.size(), 0);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetInActiveChildren_003
 * @tc.desc: Test SetInActiveChildren with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg, LazyDynamicLayoutModelStatic_SetInActiveChildren_003, TestSize.Level1)
{
    FrameNode* nullFrameNode = nullptr;
    std::vector<int32_t> inActiveChildren = {1, 2, 3};
    LazyDynamicLayoutModelStatic::SetInActiveChildren(nullFrameNode, inActiveChildren);
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetOnVisibleIndexesChange_001
 * @tc.desc: Test SetOnVisibleIndexesChange with valid callback
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg,
    LazyDynamicLayoutModelStatic_SetOnVisibleIndexesChange_001, TestSize.Level1)
{
    auto frameNode = LazyDynamicLayoutModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(frameNode, nullptr);
    
    std::vector<int32_t> testIndexes = {10, 20, 30};
    bool callbackCalled = false;
    OnVisibleIndexesChangeEvent callback = [&callbackCalled, &testIndexes](const std::vector<int32_t>& indexes) {
        callbackCalled = true;
        EXPECT_EQ(indexes.size(), testIndexes.size());
    };
    
    LazyDynamicLayoutModelStatic::SetOnVisibleIndexesChange(AceType::RawPtr(frameNode), std::move(callback));
    
    auto pattern = frameNode->GetPattern<LazyDynamicLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customParams = pattern->GetCustomLayoutAlgorithmParam();
    ASSERT_NE(customParams, nullptr);
    
    auto retrievedCallback = customParams->GetOnVisibleIndexesChange();
    if (retrievedCallback) {
        retrievedCallback(testIndexes);
        EXPECT_TRUE(callbackCalled);
    }
}

/**
 * @tc.name: LazyDynamicLayoutModelStatic_SetOnVisibleIndexesChange_002
 * @tc.desc: Test SetOnVisibleIndexesChange with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutModelStaticTestNg,
    LazyDynamicLayoutModelStatic_SetOnVisibleIndexesChange_002, TestSize.Level1)
{
    FrameNode* nullFrameNode = nullptr;
    OnVisibleIndexesChangeEvent callback = [](const std::vector<int32_t>& indexes) {};
    LazyDynamicLayoutModelStatic::SetOnVisibleIndexesChange(nullFrameNode, std::move(callback));
}

} // namespace OHOS::Ace::NG
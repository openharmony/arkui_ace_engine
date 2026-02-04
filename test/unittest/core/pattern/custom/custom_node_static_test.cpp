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

#include <functional>
#include <utility>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/custom/custom_node_static.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t TEST_NODE_ID = 1001;
const std::string TEST_JS_VIEW_NAME("TestJsViewName");
} // namespace

class CustomNodeStaticTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;
};

inline void CustomNodeStaticTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

inline void CustomNodeStaticTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CustomNodeStaticTest001
 * @tc.desc: Test ConstructCustomNode with NodeKoalaInfo
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo with callbacks
     * @tc.expected: NodeKoalaInfo is created
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return "dump"; };

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     * @tc.expected: CustomNode is created successfully
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);
    EXPECT_EQ(customNode->GetTag(), V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(customNode->GetId(), TEST_NODE_ID);
}

/**
 * @tc.name: CustomNodeStaticTest002
 * @tc.desc: Test ConstructCustomNode with onMeasureSize non-null, others null
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare onMeasureSize callback
     * @tc.expected: Callback is created
     */
    std::function<void(NG::LayoutWrapper*)> onMeasureSize = [](NG::LayoutWrapper*) {};

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode with onMeasureSize non-null, others null
     * @tc.expected: Should enter if (onMeasureSize) branch, CustomMeasureLayoutNode is created
     */
    auto node = CustomNodeStatic::ConstructCustomNode(
        TEST_NODE_ID, std::move(onMeasureSize), nullptr, nullptr);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
}

/**
 * @tc.name: CustomNodeStaticTest003
 * @tc.desc: Test ConstructCustomNode with onPlaceChildren non-null, others null
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare onPlaceChildren callback
     * @tc.expected: Callback is created
     */
    std::function<void(NG::LayoutWrapper*)> onPlaceChildren = [](NG::LayoutWrapper*) {};

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode with onPlaceChildren non-null, others null
     * @tc.expected: Should enter if (onPlaceChildren) branch, CustomMeasureLayoutNode is created
     */
    auto node = CustomNodeStatic::ConstructCustomNode(
        TEST_NODE_ID, nullptr, std::move(onPlaceChildren), nullptr);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
}

/**
 * @tc.name: CustomNodeStaticTest004
 * @tc.desc: Test ConstructCustomNode with updateParamFunc non-null, others null
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare updateParamFunc callback
     * @tc.expected: Callback is created
     */
    std::function<void(NG::LayoutWrapper*)> updateParamFunc = [](NG::LayoutWrapper*) {};

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode with updateParamFunc non-null, others null
     * @tc.expected: Should enter if (updateParamFunc) branch, CustomMeasureLayoutNode is created
     */
    auto node = CustomNodeStatic::ConstructCustomNode(
        TEST_NODE_ID, nullptr, nullptr, std::move(updateParamFunc));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
}

/**
 * @tc.name: CustomNodeStaticTest005
 * @tc.desc: Test ConstructCustomNode with all three callbacks null
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke ConstructCustomNode with all callbacks null
     * @tc.expected: Should enter all else branches, CustomMeasureLayoutNode is created
     */
    auto node = CustomNodeStatic::ConstructCustomNode(
        TEST_NODE_ID, nullptr, nullptr, nullptr);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::JS_VIEW_ETS_TAG);
    EXPECT_EQ(node->GetId(), TEST_NODE_ID);
}

} // namespace OHOS::Ace::NG

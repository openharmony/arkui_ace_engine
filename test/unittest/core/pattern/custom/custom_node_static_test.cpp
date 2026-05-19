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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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

/**
 * @tc.name: CustomNodeStaticTest006
 * @tc.desc: Test DidDefaultMeasure with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke DidDefaultMeasure with null frameNode
     * @tc.expected: Should return SizeF(0, 0)
     */
    RefPtr<CustomMeasureLayoutNode> nullFrameNode = nullptr;
    auto result = CustomNodeStatic::DidDefaultMeasure(nullFrameNode);
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 0.0f);
}

/**
 * @tc.name: CustomNodeStaticTest007
 * @tc.desc: Test DidDefaultMeasure with valid frameNode but no children
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CustomMeasureLayoutNode without children
     * @tc.expected: FrameNode is created successfully
     */
    auto frameNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID, "");
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get initial geometry node frame size
     * @tc.expected: Initial frame size is (0, 0)
     */
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto initialSize = geometryNode->GetFrameSize();
    EXPECT_EQ(initialSize.Width(), 0.0f);
    EXPECT_EQ(initialSize.Height(), 0.0f);

    /**
     * @tc.steps: step3. Invoke DidDefaultMeasure
     * @tc.expected: Should complete measurement and return valid frame size
     */
    auto result = CustomNodeStatic::DidDefaultMeasure(frameNode);
    EXPECT_GE(result.Width(), 0.0f);
    EXPECT_GE(result.Height(), 0.0f);
}

/**
 * @tc.name: CustomNodeStaticTest008
 * @tc.desc: Test ConstructCustomNode with onDumpInfoFunc callback set
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo with onDumpInfoFunc callback
     * @tc.expected: NodeKoalaInfo is created
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return ""; };
    std::vector<std::string> capturedParams;
    info.onDumpInfoFunc = [&capturedParams](const std::vector<std::string>& params) {
        capturedParams.assign(params.begin(), params.end());
    };

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     * @tc.expected: CustomNode is created successfully with onDumpInfoFunc set
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step3. Fire the onDumpInfoFunc callback
     * @tc.expected: Callback receives the expected parameters
     */
    std::vector<std::string> testParams = { "-dumpAll", "-r" };
    customNode->FireOnDumpInfoFunc(testParams);
    EXPECT_EQ(capturedParams.size(), 2);
    EXPECT_EQ(capturedParams[0], "-dumpAll");
    EXPECT_EQ(capturedParams[1], "-r");
}

/**
 * @tc.name: CustomNodeStaticTest009
 * @tc.desc: Test ConstructCustomNode without onDumpInfoFunc (default null)
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo without onDumpInfoFunc
     * @tc.expected: NodeKoalaInfo is created with onDumpInfoFunc as default (null)
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return ""; };
    // onDumpInfoFunc is left as default (null)

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     * @tc.expected: CustomNode is created successfully
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step3. Fire the onDumpInfoFunc callback when it is null
     * @tc.expected: No crash occurs, callback is not invoked
     */
    std::vector<std::string> testParams = { "-viewHierarchy" };
    customNode->FireOnDumpInfoFunc(testParams);
}

/**
 * @tc.name: CustomNodeStaticTest010
 * @tc.desc: Test ConstructCustomNode with onDumpInfoFunc receiving empty params
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo with onDumpInfoFunc callback
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return ""; };
    std::vector<std::string> capturedParams;
    info.onDumpInfoFunc = [&capturedParams](const std::vector<std::string>& params) {
        capturedParams.assign(params.begin(), params.end());
    };

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     * @tc.expected: CustomNode is created successfully
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step3. Fire with empty params
     * @tc.expected: Callback receives empty vector
     */
    std::vector<std::string> emptyParams;
    customNode->FireOnDumpInfoFunc(emptyParams);
    EXPECT_TRUE(capturedParams.empty());
}

/**
 * @tc.name: CustomNodeStaticTest011
 * @tc.desc: Test onDumpInfoFunc with multiple sequential FireOnDumpInfoFunc calls
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo with onDumpInfoFunc that records call count
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return ""; };
    int callCount = 0;
    info.onDumpInfoFunc = [&callCount](const std::vector<std::string>& params) { callCount++; };

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step3. Fire the callback multiple times
     * @tc.expected: Callback is invoked each time
     */
    customNode->FireOnDumpInfoFunc({ "-dumpAll" });
    EXPECT_EQ(callCount, 1);
    customNode->FireOnDumpInfoFunc({ "-stateVariables", "-viewId=123" });
    EXPECT_EQ(callCount, 2);
    customNode->FireOnDumpInfoFunc({ "-inactiveComponents", "-r" });
    EXPECT_EQ(callCount, 3);
}

/**
 * @tc.name: CustomNodeStaticTest012
 * @tc.desc: Test onDumpInfoFunc with DFX-style commands
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeStaticTestNg, CustomNodeStaticTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NodeKoalaInfo with onDumpInfoFunc that captures all params
     */
    NodeKoalaInfo info;
    info.jsViewName = TEST_JS_VIEW_NAME;
    info.onPageShowFunc = []() {};
    info.onPageHideFunc = []() {};
    info.onBackPressedFunc = []() -> bool { return true; };
    info.pageTransitionFunc = []() {};
    info.onCleanupFunc = []() {};
    info.onDumpInspectorFunc = []() -> std::string { return ""; };
    std::vector<std::string> capturedParams;
    info.onDumpInfoFunc = [&capturedParams](const std::vector<std::string>& params) {
        capturedParams.assign(params.begin(), params.end());
    };

    /**
     * @tc.steps: step2. Invoke ConstructCustomNode
     */
    auto customNode = CustomNodeStatic::ConstructCustomNode(TEST_NODE_ID, std::move(info));
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step3. Fire with RecyclePool command (as used in CustomNode::DumpInfo)
     * @tc.expected: Callback receives "RecyclePool"
     */
    customNode->FireOnDumpInfoFunc({ "RecyclePool" });
    EXPECT_EQ(capturedParams.size(), 1);
    EXPECT_EQ(capturedParams[0], "RecyclePool");

    /**
     * @tc.steps: step4. Fire with viewId-based command
     * @tc.expected: Callback receives viewId command
     */
    std::vector<std::string> viewIdParams = { "-dumpAll", "-viewId=100", "-r" };
    customNode->FireOnDumpInfoFunc(viewIdParams);
    EXPECT_EQ(capturedParams.size(), 3);
    EXPECT_EQ(capturedParams[0], "-dumpAll");
    EXPECT_EQ(capturedParams[1], "-viewId=100");
    EXPECT_EQ(capturedParams[2], "-r");
}

} // namespace OHOS::Ace::NG

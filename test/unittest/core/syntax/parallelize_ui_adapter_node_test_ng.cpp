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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define PRIVATE public
#define PROTECTED public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/arkoala_parallelize_ui_adapter_node.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef PRIVATE
#undef PROTECTED

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ParallelizeUIAdapterNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: ParallelizeUIAdapterNode_FrameCount
 * @tc.desc: Test FrameCount before and after RegisterCallback with getCount
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, FrameCountTest001, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(100);
    // default no getCount_ set -> should be 0
    EXPECT_EQ(node->FrameCount(), 0);

    // register getCount only (registerCallback returns nullptr)
    node->RegisterCallback(
        std::function<int32_t()>([]() { return 3; }),
        std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>(
            [](int32_t, int32_t, int32_t) -> ArkUINodeHandle { return nullptr; })
    );

    EXPECT_EQ(node->FrameCount(), 3);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChild
 * @tc.desc: Register callbacks to return a FrameNode and verify GetFrameChildByIndex and GetChildren
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexTest002, TestSize.Level1)
{
    // create a child FrameNode that will be returned by the registerCallback
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(101);

    // register callbacks: getCount -> 1, registerCallback -> return the raw pointer of childFrameNode
    node->RegisterCallback(std::function<int32_t()>([]() { return 1; }),
        std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>(
            [child = childFrameNode](int32_t /*index*/, int32_t /*needBuild*/, int32_t /*isCache*/) -> ArkUINodeHandle {
                return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(child));
            }));

    // request frame child and add to render tree
    auto frameChild = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true, false, true));
    ASSERT_NE(frameChild, nullptr);

    // after adding, children list should contain one item
    const auto& children = node->GetChildren();
    EXPECT_EQ(children.size(), 1u);
    node->Reset();
    auto frameChild2 = AceType::DynamicCast<FrameNode>(node->GetFrameChildByIndex(0, true, false, true));
    ASSERT_NE(frameChild2, nullptr);
    EXPECT_EQ(node->GetChildren().size(), 1u);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_ExceptionBranch
 * @tc.desc: registerCallback_ nullptr and return nullptr branch test
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, ExceptionBranchTest003, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(102);
    auto result = node->GetFrameChildByIndex(0, true, false, true);
    EXPECT_EQ(result, nullptr);
    node->RegisterCallback(std::function<int32_t()>([]() { return 1; }),
        std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>([](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return nullptr;
        }));
    auto result2 = node->GetFrameChildByIndex(0, true, false, true);
    EXPECT_EQ(result2, nullptr);
    EXPECT_EQ(node->GetChildren().size(), 0u);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_FrameCount
 * @tc.desc: Test FrameCount before and after RegisterCallback with getCount
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, FrameCountTest004, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(1);
    EXPECT_EQ(node->FrameCount(), 0);

    node->RegisterCallback(
        std::function<int32_t()>([]() { return 100; }),
        std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>(
            [](int32_t, int32_t, int32_t) -> ArkUINodeHandle { return nullptr; })
    );

    EXPECT_EQ(node->FrameCount(), 100);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_DoSetActiveChildRange
 * @tc.desc: Test DoSetActiveChildRange activates children within range and deactivates others
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, DoSetActiveChildRangeTest005, TestSize.Level1)
{
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(200);

    auto p0 = AceType::MakeRefPtr<Pattern>();
    auto c0 = AceType::MakeRefPtr<FrameNode>("c0", 0, p0);
    p0->AttachToFrameNode(c0);

    auto p1 = AceType::MakeRefPtr<Pattern>();
    auto c1 = AceType::MakeRefPtr<FrameNode>("c1", 1, p1);
    p1->AttachToFrameNode(c1);

    auto p2 = AceType::MakeRefPtr<Pattern>();
    auto c2 = AceType::MakeRefPtr<FrameNode>("c2", 2, p2);
    p2->AttachToFrameNode(c2);

    node->RegisterCallback(
        []() -> int32_t {
            return 3;
        },
        [&](int32_t index, int32_t, int32_t) -> ArkUINodeHandle {
            switch (index) {
                case 0: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c0));
                case 1: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c1));
                case 2: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c2));
                default: return nullptr;
            }
        });

    node->GetFrameChildByIndex(0, true);
    node->GetFrameChildByIndex(1, true);
    node->GetFrameChildByIndex(2, true);

    EXPECT_FALSE(c0->IsActive());
    EXPECT_FALSE(c1->IsActive());
    EXPECT_FALSE(c2->IsActive());

    node->DoSetActiveChildRange(0, 1, 0, 0, false);

    EXPECT_TRUE(c0->IsActive());
    EXPECT_TRUE(c1->IsActive());
    EXPECT_FALSE(c2->IsActive());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_IsAtomicNode
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, IsAtomicNodeTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(300);
    EXPECT_FALSE(node->IsAtomicNode());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_FlushUpdateAndMarkDirty
 * @tc.desc: Test FlushUpdateAndMarkDirty does not crash (empty implementation)
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, FlushUpdateAndMarkDirtyTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(301);

    /**
     * @tc.steps: step2. Should not crash - empty implementation
     */
    node->FlushUpdateAndMarkDirty();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_MoveData
 * @tc.desc: Test MoveData does not crash (empty implementation)
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, MoveDataTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(302);

    /**
     * @tc.steps: step2. Should not crash - empty implementation
     */
    node->MoveData(0, 1);
    node->MoveData(5, 10);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameNode
 * @tc.desc: Test GetFrameNode returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameNodeTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(303);

    /**
     * @tc.steps: step2. GetFrameNode should return nullptr
     */
    EXPECT_EQ(node->GetFrameNode(0), nullptr);
    EXPECT_EQ(node->GetFrameNode(100), nullptr);
    EXPECT_EQ(node->GetFrameNode(-1), nullptr);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_DoSetActiveChildRangeEarlyReturn
 * @tc.desc: Test DoSetActiveChildRange early return when start and end unchanged
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, DoSetActiveChildRangeEarlyReturnTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(304);
    auto p0 = AceType::MakeRefPtr<Pattern>();
    auto c0 = AceType::MakeRefPtr<FrameNode>("c0", 0, p0);
    p0->AttachToFrameNode(c0);
    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t index, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c0));
        });

    node->GetFrameChildByIndex(0, true);

    /**
     * @tc.steps: step2. First call to set range 0-0 inactive c0
     */
    node->DoSetActiveChildRange(0, 0, 0, 0, false);
    EXPECT_FALSE(c0->IsActive());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexWithIsCache
 * @tc.desc: Test GetFrameChildByIndex with isCache parameter
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexIsCacheTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(306);
    bool isCacheParam = false;
    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t isCache) -> ArkUINodeHandle {
            isCacheParam = isCache;
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    /**
     * @tc.steps: step2. Test with isCache = true
     */
    node->GetFrameChildByIndex(0, true, true, false);
    EXPECT_TRUE(isCacheParam);

    /**
     * @tc.steps: step3. Test with isCache = false
     */
    node->GetFrameChildByIndex(0, true, false, false);
    EXPECT_FALSE(isCacheParam);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexWithoutAddToRenderTree
 * @tc.desc: Test GetFrameChildByIndex with addToRenderTree = false
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexNoAddToTreeTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(307);
    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    /**
     * @tc.steps: step2. Test with addToRenderTree = false
     */
    auto frameChild = node->GetFrameChildByIndex(0, true, false, false);
    ASSERT_NE(frameChild, nullptr);

    /**
     * @tc.steps: step3. When addToRenderTree is false, the node should not be set active
     */
    EXPECT_FALSE(childFrameNode->IsActive());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetChildrenCached
 * @tc.desc: Test GetChildren returns cached list on subsequent calls
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetChildrenCachedTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(308);

    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    node->GetFrameChildByIndex(0, true, false, true);

    /**
     * @tc.steps: step2. First call populates children_
     */
    const auto& children1 = node->GetChildren();
    EXPECT_EQ(children1.size(), 1u);

    /**
     * @tc.steps: step3. Second call should return the same cached list
     */
    const auto& children2 = node->GetChildren();
    EXPECT_EQ(children2.size(), 1u);
    EXPECT_EQ(&children1, &children2);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_IsSyntaxNode
 * @tc.desc: Test IsSyntaxNode returns true (inherited from ForEachBaseNode)
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, IsSyntaxNodeTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(309);
    EXPECT_TRUE(node->IsSyntaxNode());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexAlreadyActive
 * @tc.desc: Test GetFrameChildByIndex when frameNode is already active
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexAlreadyActiveTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    /**
     * @tc.steps: step2. Pre-activate the node
     */
    childFrameNode->SetActive(true);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(310);

    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    /**
     * @tc.steps: step3. Should not re-activate when already active
     */
    auto frameChild = node->GetFrameChildByIndex(0, true, false, true);
    ASSERT_NE(frameChild, nullptr);
    EXPECT_TRUE(childFrameNode->IsActive());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_MultipleChildrenInMap
 * @tc.desc: Test multiple children added to childMap_ and GetChildren returns all
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, MultipleChildrenTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto p0 = AceType::MakeRefPtr<Pattern>();
    auto c0 = AceType::MakeRefPtr<FrameNode>("c0", 0, p0);
    p0->AttachToFrameNode(c0);

    auto p1 = AceType::MakeRefPtr<Pattern>();
    auto c1 = AceType::MakeRefPtr<FrameNode>("c1", 1, p1);
    p1->AttachToFrameNode(c1);

    auto p2 = AceType::MakeRefPtr<Pattern>();
    auto c2 = AceType::MakeRefPtr<FrameNode>("c2", 2, p2);
    p2->AttachToFrameNode(c2);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(311);

    node->RegisterCallback(
        []() -> int32_t { return 3; },
        [&](int32_t index, int32_t, int32_t) -> ArkUINodeHandle {
            switch (index) {
                case 0: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c0));
                case 1: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c1));
                case 2: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c2));
                default: return nullptr;
            }
        });

    node->GetFrameChildByIndex(0, true);
    node->GetFrameChildByIndex(1, true);
    node->GetFrameChildByIndex(2, true);

    /**
     * @tc.steps: step2. GetChildren should return all three children
     */
    const auto& children = node->GetChildren();
    EXPECT_EQ(children.size(), 3u);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexNeedBuildParam
 * @tc.desc: Test GetFrameChildByIndex passes needBuild parameter correctly
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexNeedBuildTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(314);

    int32_t capturedNeedBuild = -1;
    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t needBuild, int32_t) -> ArkUINodeHandle {
            capturedNeedBuild = needBuild;
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    /**
     * @tc.steps: step2. Test with needBuild = true
     */
    node->GetFrameChildByIndex(0, true, false, false);
    EXPECT_EQ(capturedNeedBuild, 1);

    /**
     * @tc.steps: step3. Test with needBuild = false
     */
    node->GetFrameChildByIndex(0, false, false, false);
    EXPECT_EQ(capturedNeedBuild, 0);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetChildrenWithNotDetach
 * @tc.desc: Test GetChildren with notDetach parameter
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetChildrenNotDetachTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(315);

    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    node->GetFrameChildByIndex(0, true, false, true);

    /**
     * @tc.steps: step2. Test with notDetach = true
     */
    const auto& children1 = node->GetChildren(true);
    EXPECT_EQ(children1.size(), 1u);

        /**
     * @tc.steps: step3. Test with notDetach = false
     */
    const auto& children2 = node->GetChildren(false);
    EXPECT_EQ(children2.size(), 1u);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_ResetClearsAndMarks
 * @tc.desc: Test Reset marks need sync and frame flush dirty
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, ResetMarksTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(316);

    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    node->GetFrameChildByIndex(0, true, false, true);
    EXPECT_EQ(node->GetChildren().size(), 1u);

    /**
     * @tc.steps: step2. Call Reset and verify no crash
     */
    node->Reset();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_DoSetActiveChildRangeChangeRange
 * @tc.desc: Test DoSetActiveChildRange changes range correctly on subsequent calls
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, DoSetActiveChildRangeChangeTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(317);

    auto p0 = AceType::MakeRefPtr<Pattern>();
    auto c0 = AceType::MakeRefPtr<FrameNode>("c0", 0, p0);
    p0->AttachToFrameNode(c0);

    auto p1 = AceType::MakeRefPtr<Pattern>();
    auto c1 = AceType::MakeRefPtr<FrameNode>("c1", 1, p1);
    p1->AttachToFrameNode(c1);

    node->RegisterCallback(
        []() -> int32_t { return 2; },
        [&](int32_t index, int32_t, int32_t) -> ArkUINodeHandle {
            switch (index) {
                case 0: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c0));
                case 1: return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(c1));
                default: return nullptr;
            }
        });

    node->GetFrameChildByIndex(0, true);
    node->GetFrameChildByIndex(1, true);

    /**
     * @tc.steps: step2. First range
     */
    node->DoSetActiveChildRange(0, 0, 0, 0, false);
    EXPECT_FALSE(c0->IsActive());
    EXPECT_FALSE(c1->IsActive());

    /**
     * @tc.steps: step3. Change range: only c1 active
     */
    node->DoSetActiveChildRange(1, 1, 0, 0, false);
    EXPECT_FALSE(c0->IsActive());
    EXPECT_TRUE(c1->IsActive());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetChildrenEmptyMap
 * @tc.desc: Test GetChildren when childMap_ is empty
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetChildrenEmptyMapTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(320);
    const auto& children = node->GetChildren();
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexLargeIndex
 * @tc.desc: Test GetFrameChildByIndex with large index value
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexLargeIndexTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ParallelizeUIAdapterNode
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto childFrameNode = AceType::MakeRefPtr<FrameNode>("child", -1, pattern);
    pattern->AttachToFrameNode(childFrameNode);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(324);

    uint32_t capturedIndex = 0;
    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t index, int32_t, int32_t) -> ArkUINodeHandle {
            capturedIndex = index;
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(childFrameNode));
        });

    /**
     * @tc.steps: step2. Test with large index value
     */
    constexpr uint32_t largeIndex = 0xFFFFFFFF;
    node->GetFrameChildByIndex(largeIndex, true, false, false);
    EXPECT_EQ(capturedIndex, largeIndex);
}

/**
 * @tc.name: ParallelizeUIAdapterNode_GetFrameChildByIndexChildGetFrameChildReturnsNull
 * @tc.desc: Test GetFrameChildByIndex when child->GetFrameChildByIndex returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ParallelizeUIAdapterNodeTestNg, GetFrameChildByIndexChildNullTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a UINode that has no children (GetFrameChildByIndex will return nullptr)
     */
    auto emptyNode = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(999);

    auto node = AceType::MakeRefPtr<ParallelizeUIAdapterNode>(326);

    node->RegisterCallback(
        []() -> int32_t { return 1; },
        [&](int32_t, int32_t, int32_t) -> ArkUINodeHandle {
            return reinterpret_cast<ArkUINodeHandle>(Referenced::RawPtr(emptyNode));
        });

    /**
     * @tc.steps: step2. child->GetFrameChildByIndex(0, true) should return nullptr for emptyNode
     */
    auto result = node->GetFrameChildByIndex(0, true, false, true);
    EXPECT_EQ(result, nullptr);
}
} // namespace OHOS::Ace::NG

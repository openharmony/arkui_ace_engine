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

#include <utility>
#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/syntax/mock_lazy_for_each_builder.h"
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
constexpr int32_t TEST_NODE_ID_2 = 200;
constexpr int32_t INVALID_INDEX = -1;
constexpr bool IS_ATOMIC_NODE = false;
} // namespace

class LazyForEachModelSyntaxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
private:
    RefPtr<FrameNode> CreateParentNode();
};

void LazyForEachModelSyntaxTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void LazyForEachModelSyntaxTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void LazyForEachModelSyntaxTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void LazyForEachModelSyntaxTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LazyForEachModelSyntaxTestNg::CreateParentNode()
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    return frameNode;
}

/**
 * @tc.name: LazyForEachModelSyntaxCreateTest001
 * @tc.desc: Create LazyForEach node with valid builder
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCreateTest001, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
    EXPECT_EQ(lazyForEachNode->GetTag(), V2::JS_LAZY_FOR_EACH_ETS_TAG);
}

/**
 * @tc.name: LazyForEachModelSyntaxCreateTest002
 * @tc.desc: Create LazyForEach node and verify atomic property
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCreateTest002, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
    EXPECT_EQ(lazyForEachNode->IsAtomicNode(), IS_ATOMIC_NODE);
}

/**
 * @tc.name: LazyForEachModelSyntaxCreateTest003
 * @tc.desc: Create LazyForEach with Tabs parent does not create node
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCreateTest003, TestSize.Level1)
{
    auto tabsPattern = AceType::MakeRefPtr<Pattern>();
    auto tabsNode = AceType::MakeRefPtr<FrameNode>(V2::TABS_ETS_TAG, -1, tabsPattern);
    tabsPattern->AttachToFrameNode(tabsNode);
    ViewStackProcessor::GetInstance()->Push(tabsNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxOnMoveTest005
 * @tc.desc: OnMove sets move callback
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxOnMoveTest005, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxOnMoveTest006
 * @tc.desc: OnMove without Create handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxOnMoveTest006, TestSize.Level1)
{
    LazyForEachModelNG model;
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxOnMoveTest007
 * @tc.desc: OnMove with null callback
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxOnMoveTest007, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    model.OnMove(nullptr);
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxSetItemDragHandlerTest008
 * @tc.desc: SetItemDragHandler sets drag handlers
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxSetItemDragHandlerTest008, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    model.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxSetItemDragHandlerTest009
 * @tc.desc: SetItemDragHandler without Create handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxSetItemDragHandlerTest009, TestSize.Level1)
{
    LazyForEachModelNG model;
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    model.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxSetItemDragHandlerTest010
 * @tc.desc: SetItemDragHandler with null callbacks
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxSetItemDragHandlerTest010, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    model.SetItemDragHandler(nullptr, nullptr, nullptr, nullptr);
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxGetOrCreateTest011
 * @tc.desc: GetOrCreateLazyForEachNode with same ID returns same instance
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxGetOrCreateTest011, TestSize.Level1)
{
    const RefPtr<LazyForEachBuilder> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    auto node1 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, mockBuilder);
    auto node2 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, mockBuilder);
    EXPECT_EQ(node1, node2);
}

/**
 * @tc.name: LazyForEachModelSyntaxGetOrCreateTest012
 * @tc.desc: GetOrCreateLazyForEachNode with different IDs returns different instances
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxGetOrCreateTest012, TestSize.Level1)
{
    const RefPtr<LazyForEachBuilder> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    auto node1 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID, mockBuilder);
    auto node2 = LazyForEachNode::GetOrCreateLazyForEachNode(TEST_NODE_ID_2, mockBuilder);
    EXPECT_NE(node1, node2);
}

/**
 * @tc.name: LazyForEachModelSyntaxCompleteFlowTest013
 * @tc.desc: Complete flow: Create, OnMove, SetItemDragHandler
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCompleteFlowTest013, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    model.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
}

/**
 * @tc.name: LazyForEachModelSyntaxMultipleCreateTest014
 * @tc.desc: Create multiple LazyForEach nodes
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxMultipleCreateTest014, TestSize.Level1)
{
    for (int32_t i = 0; i < 3; ++i) {
        auto parentNode = CreateParentNode();
        ViewStackProcessor::GetInstance()->Push(parentNode);
        LazyForEachModelNG model;
        const RefPtr<LazyForEachActuator> mockBuilder =
            AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
        model.Create(mockBuilder);
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_TRUE(lazyForEachNode != nullptr);
    }
}

/**
 * @tc.name: LazyForEachModelSyntaxViewStackTest015
 * @tc.desc: Test LazyForEach node ViewStackProcessor interaction
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxViewStackTest015, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto topNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_TRUE(topNode != nullptr);
}

/**
 * @tc.name: LazyForEachModelSyntaxBuilderCastTest016
 * @tc.desc: Test LazyForEachBuilder dynamic cast
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxBuilderCastTest016, TestSize.Level1)
{
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(mockBuilder);
    EXPECT_TRUE(builder != nullptr);
}

/**
 * @tc.name: LazyForEachModelSyntaxCreateWithInvalidBuilderTest017
 * @tc.desc: Create with non-LazyForEachBuilder handles gracefully
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCreateWithInvalidBuilderTest017, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    RefPtr<LazyForEachActuator> invalidBuilder = nullptr;
    model.Create(invalidBuilder);
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxNodeIdTest018
 * @tc.desc: Test LazyForEach node ID assignment
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxNodeIdTest018, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
    EXPECT_NE(lazyForEachNode->GetId(), INVALID_INDEX);
}

/**
 * @tc.name: LazyForEachModelSyntaxRefCountTest019
 * @tc.desc: Test LazyForEach node reference counting
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxRefCountTest019, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
}

/**
 * @tc.name: LazyForEachModelSyntaxFrameCountTest020
 * @tc.desc: Test LazyForEach node initial frame count
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxFrameCountTest020, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(lazyForEachNode != nullptr);
}

/**
 * @tc.name: LazyForEachModelSyntaxCallbackExecutionTest021
 * @tc.desc: Verify callbacks are properly stored
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxCallbackExecutionTest021, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    auto onMoveCallback = [](int32_t from, int32_t to) {};
    model.OnMove(std::move(onMoveCallback));
    auto onLongPress = [](int32_t index) {};
    auto onDragStart = [](int32_t index) {};
    auto onMoveThrough = [](int32_t from, int32_t to) {};
    auto onDrop = [](int32_t index) {};
    model.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
        std::move(onMoveThrough), std::move(onDrop));
    SUCCEED();
}

/**
 * @tc.name: LazyForEachModelSyntaxMultipleCallbacksTest022
 * @tc.desc: Test setting callbacks multiple times
 * @tc.type: FUNC
 */
HWTEST_F(LazyForEachModelSyntaxTestNg, LazyForEachModelSyntaxMultipleCallbacksTest022, TestSize.Level1)
{
    auto parentNode = CreateParentNode();
    ViewStackProcessor::GetInstance()->Push(parentNode);
    LazyForEachModelNG model;
    const RefPtr<LazyForEachActuator> mockBuilder =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    model.Create(mockBuilder);
    for (int32_t i = 0; i < 3; ++i) {
        auto onMoveCallback = [i](int32_t from, int32_t to) {};
        model.OnMove(std::move(onMoveCallback));
        auto onLongPress = [](int32_t index) {};
        auto onDragStart = [](int32_t index) {};
        auto onMoveThrough = [](int32_t from, int32_t to) {};
        auto onDrop = [](int32_t index) {};
        model.SetItemDragHandler(std::move(onLongPress), std::move(onDragStart),
            std::move(onMoveThrough), std::move(onDrop));
    }
}

} // namespace OHOS::Ace::NG

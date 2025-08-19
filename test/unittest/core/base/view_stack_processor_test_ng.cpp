/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr char TAG_ROOT[] = "root";
constexpr char TAG_CHILD[] = "child";
const auto MOCK_PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto MOCK_PATTERN_CHILD = AceType::MakeRefPtr<Pattern>();
const auto PATTERN_ROOT = AceType::MakeRefPtr<Pattern>();
const auto FRAME_NODE_ROOT = FrameNode::CreateFrameNode(TAG_ROOT, 1, MOCK_PATTERN_ROOT, true);
const auto FRAME_NODE_CHILD = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
}; // namespace

class ViewStackProcessorTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: ViewStackProcessorTestNg001
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push isCustomView = false
     * @tc.expected: removeSilently_ is false
     */
    bool customViews[2] = { true, false };
    for (int i = 0; i < 2; ++i) {
        ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT, customViews[i]);
        auto node = ViewStackProcessor::GetInstance()->Finish();
        EXPECT_FALSE(node->removeSilently_);
    }
}

/**
 * @tc.name: ViewStackProcessorTestNg002
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push childFrameNode
     * @tc.expected: mainFrameNode's tag is child
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->ImplicitPopBeforeContinue();
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    /**
     * @tc.steps: step2. ImplicitPopBeforeContinue
     * @tc.expected: mainFrameNode's tag is child
     */
    ViewStackProcessor::GetInstance()->ImplicitPopBeforeContinue();
    auto topFrameNodeTwo = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(strcmp(topFrameNodeTwo->GetTag().c_str(), TAG_CHILD), 0);
}

/**
 * @tc.name: ViewStackProcessorTestNg003
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. ImplicitPopBeforeContinue
     * @tc.expected: frameNode's isMeasureBoundary_ is false
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    FRAME_NODE_ROOT->onMainTree_ = true;
    ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    ViewStackProcessor::GetInstance()->FlushRerenderTask();
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->FlushRerenderTask();
    ViewStackProcessor::GetInstance()->FlushRerenderTask();
    EXPECT_FALSE(FRAME_NODE_ROOT->isMeasureBoundary_);
}

/**
 * @tc.name: ViewStackProcessorTestNg004
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push key one and two
     * @tc.expected: GetKey is "one_two"
     */
    const std::string keyOne("one");
    const std::string keyTwo("two");
    ViewStackProcessor::GetInstance()->PushKey(keyOne);
    ViewStackProcessor::GetInstance()->PushKey(keyTwo);
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), "one_two"), 0);
    /**
     * @tc.steps: step2. pop key one and two
     * @tc.expected: GetKey is ""
     */
    ViewStackProcessor::GetInstance()->PopKey();
    ViewStackProcessor::GetInstance()->PopKey();
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), ""), 0);
    ViewStackProcessor::GetInstance()->ProcessViewId("three");
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), ""), 0);
    /**
     * @tc.steps: step3. push a empty key and do pop key
     * @tc.expected: GetKey is ""
     */
    ViewStackProcessor::GetInstance()->PushKey("");
    ViewStackProcessor::GetInstance()->PopKey();
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), ""), 0);
    /**
     * @tc.steps: step4. create ScopedViewStackProcessor
     * @tc.expected: not nullptr
     */
    auto scoped = std::make_shared<ScopedViewStackProcessor>();
    EXPECT_NE(scoped->instance_, nullptr);
    scoped = nullptr;
}

/**
 * @tc.name: ViewStackProcessorTestNg005
 * @tc.desc: Test the SetVisualState and GetVisualState in view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get instance and set different states and show result
     * @tc.expected: GetVisualState value meeting expectations.
     */
    auto instance = ViewStackProcessor::GetInstance();
    instance->SetVisualState(VisualState::DISABLED);
    EXPECT_EQ(instance->GetVisualState(), 4);
    instance->SetVisualState(VisualState::FOCUSED);
    EXPECT_EQ(instance->GetVisualState(), 2);
    instance->SetVisualState(VisualState::PRESSED);
    EXPECT_EQ(instance->GetVisualState(), 1);
    instance->SetVisualState(VisualState::NORMAL);
    EXPECT_EQ(instance->GetVisualState(), 0);
    instance->SetVisualState(VisualState::HOVER);
    EXPECT_EQ(instance->GetVisualState(), 0);
    /**
     * @tc.steps: step2. clear visual state
     * @tc.expected: IsCurrentVisualStateProcess meeting expectations.
     */
    EXPECT_FALSE(instance->IsCurrentVisualStateProcess());
    instance->ClearVisualState();
    EXPECT_TRUE(instance->IsCurrentVisualStateProcess());
}

/**
 * @tc.name: ViewStackProcessorTestNg006
 * @tc.desc: Test the Push and PopContainer in view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get instance and try PopContainer
     * @tc.expected: actually nothing happened because elementsStack no value.
     */
    auto instance = ViewStackProcessor::GetInstance();
    instance->PopContainer();
    EXPECT_EQ(instance->elementsStack_.size(), 0);
    /**
     * @tc.steps: step2. Create some node
     */
    auto pipe = MockPipelineContext::GetCurrent();
    const auto root = FrameNode::CreateFrameNode(TAG_CHILD, 0, AceType::MakeRefPtr<RootPattern>(), true);
    const auto child = FrameNode::CreateFrameNode(TAG_CHILD, 3, AceType::MakeRefPtr<RootPattern>(), true);
    const auto child2 = FrameNode::CreateFrameNode(TAG_CHILD, 4, AceType::MakeRefPtr<Pattern>(), true);
    root->context_ = AceType::RawPtr(pipe);
    child->context_ = AceType::RawPtr(pipe);
    child2->context_ = AceType::RawPtr(pipe);
    /**
     * @tc.steps: step3. Push root into container
     * @tc.expected: Pop failed elementsStack_ size still 1.
     */
    instance->Push(root);
    instance->PopContainer();
    EXPECT_EQ(instance->elementsStack_.size(), 1);
    /**
     * @tc.steps: step4. pop root and put FRAME_NODE_ROOT into container
     * @tc.expected: Pop failed elementsStack_ size still 1.
     */
    FRAME_NODE_ROOT->context_ = AceType::RawPtr(pipe);
    instance->elementsStack_.pop();
    instance->Push(FRAME_NODE_ROOT);
    instance->PopContainer();
    EXPECT_EQ(instance->elementsStack_.size(), 1);
    /**
     * @tc.steps: step5. push child2 and child into instance
     * @tc.expected: Pop success elementsStack_ size residue 1.
     */
    instance->Push(child2);
    instance->Push(child);
    instance->ImplicitPopBeforeContinue();
    EXPECT_EQ(instance->elementsStack_.size(), 2);
    instance->PopContainer();
    EXPECT_EQ(instance->elementsStack_.size(), 1);
    /**
     * @tc.steps: step6. push child2 again
     * @tc.expected: Pop success elementsStack_ size residue 1.
     */
    instance->Push(child2);
    instance->PopContainer();
    EXPECT_EQ(instance->elementsStack_.size(), 1);
}

/**
 * @tc.name: ViewStackProcessorTestNg007
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. clear PrebuildCompCmds.
     */
    auto& prebuildComponentCmds = ViewStackProcessor::GetInstance()->GetPrebuildComponentCmds();
    while (!prebuildComponentCmds.empty()) {
        prebuildComponentCmds.pop();
    }
    /**
     * @tc.steps: step2. PushPrebuildCompCmd.
     * @tc.expected: PrebuildCompCmds is not empty.
     */
    ViewStackProcessor::GetInstance()->PushPrebuildCompCmd();
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->GetPrebuildComponentCmds().empty());
    /**
     * @tc.steps: step3. pop PrebuildCompCmd.
     * @tc.expected: PrebuildCompCmds is empty.
     */
    if (!prebuildComponentCmds.empty()) {
        prebuildComponentCmds.pop();
    }
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetPrebuildComponentCmds().empty());
}
} // namespace OHOS::Ace::NG

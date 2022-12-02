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
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
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
     * @tc.expected: step1. removeSilently_ is false
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
     * @tc.expected: step1. mainFrameNode's tag is child
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->ImplicitPopBeforeContinue();
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    /**
     * @tc.steps: step2. ImplicitPopBeforeContinue
     * @tc.expected: step2. mainFrameNode's tag is child
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
     * @tc.expected: step1. frameNode's isMeasureBoundary_ is false
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
    FRAME_NODE_ROOT->onMainTree_ = true;
    ViewStackProcessor::GetInstance()->FlushImplicitAnimation();
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
     * @tc.steps: step1. PopContainer
     * @tc.expected: step1. stack top tag is root
     */
    auto groupPattern = AceType::MakeRefPtr<RootPattern>();
    auto groupNode = AceType::MakeRefPtr<GroupNode>("group", 3, groupPattern);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(groupNode);
    ViewStackProcessor::GetInstance()->PopContainer();
    auto topFrameNode = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(strcmp(topFrameNode->GetTag().c_str(), TAG_ROOT), 0);
    /**
     * @tc.steps: step2. PopContainer
     * @tc.expected: step2. stack top tag is root
     */
    ViewStackProcessor::GetInstance()->Push(groupNode);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewStackProcessor::GetInstance()->PopContainer();
    auto final = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(strcmp(final->GetTag().c_str(), "group"), 0);
}

/**
 * @tc.name: ViewStackProcessorTestNg005
 * @tc.desc: Test the operation of view stack processor
 * @tc.type: FUNC
 */
HWTEST_F(ViewStackProcessorTestNg, ViewStackProcessorTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. push key one and two
     * @tc.expected: step1. GetKey is "one_two"
     */
    const std::string keyOne("one");
    const std::string keyTwo("two");
    ViewStackProcessor::GetInstance()->PushKey(keyOne);
    ViewStackProcessor::GetInstance()->PushKey(keyTwo);
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), "one_two"), 0);
    /**
     * @tc.steps: step2. pop key one and two
     * @tc.expected: step2. GetKey is ""
     */
    ViewStackProcessor::GetInstance()->PopKey();
    ViewStackProcessor::GetInstance()->PopKey();
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), ""), 0);
    ViewStackProcessor::GetInstance()->ProcessViewId("three");
    EXPECT_EQ(strcmp(ViewStackProcessor::GetInstance()->GetKey().c_str(), ""), 0);
    /**
     * @tc.steps: step3. create ScopedViewStackProcessor
     * @tc.expected: step3. not nullptr
     */
    auto scoped = std::make_shared<ScopedViewStackProcessor>();
    EXPECT_NE(scoped->instance_, nullptr);
    scoped = nullptr;
}
} // namespace OHOS::Ace::NG
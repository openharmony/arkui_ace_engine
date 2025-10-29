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

#include "test/unittest/core/syntax/lazy_for_each_utils_test_ng.h"

namespace OHOS::Ace::NG {

void LazyForEachUtilsTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void LazyForEachUtilsTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> LazyForEachUtilsTestNg::CreateNode(const std::string& tag)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(tag, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    return frameNode;
}

void LazyForEachUtilsTestNg::UpdateItems(
    const RefPtr<LazyForEachNode>& lazyForEachNode, const RefPtr<LazyForEachActuator>& mockLazyForEachActuator)
{
    /**
     * @tc.steps: step1. Add child found in generatedItem_.
     */
    auto ids = LAZY_FOR_EACH_NODE_IDS;
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    for (auto iter : LAZY_FOR_EACH_NODE_IDS_INT) {
        builder->GetChildByIndex(iter.value_or(0), true);
    }
}

RefPtr<LazyForEachNode> LazyForEachUtilsTestNg::CreateLazyForEachNode()
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create LazyForEachNode and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>();
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. Add children items to lazyForEachNode.
     */
    UpdateItems(lazyForEachNode, mockLazyForEachActuator);
    return lazyForEachNode;
}

RefPtr<LazyForEachBuilder> LazyForEachUtilsTestNg::CreateLazyForEachBuilder(bool deleteExpiringItemImmediately = false)
{
    /**
     * @tc.steps: step1. Create Text and push it to view stack processor.
     * @tc.expected: Make Text as LazyForEach parent.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    if (!pattern) {
        return nullptr;
    }
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, pattern);
    if (!frameNode) {
        return nullptr;
    }
    pattern->AttachToFrameNode(frameNode);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    /**
     * @tc.steps: step2. Invoke lazyForEach Create function.
     * @tc.expected: Create lazyForEachBuilder and can be pop from ViewStackProcessor.
     */
    LazyForEachModelNG lazyForEach;
    const RefPtr<LazyForEachActuator> mockLazyForEachActuator =
        AceType::MakeRefPtr<OHOS::Ace::Framework::MockLazyForEachBuilder>(deleteExpiringItemImmediately);
    if (!mockLazyForEachActuator) {
        return nullptr;
    }
    lazyForEach.Create(mockLazyForEachActuator);
    auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(ViewStackProcessor::GetInstance()->Finish());
    auto lazyForEachBuilder = AceType::DynamicCast<LazyForEachBuilder>(mockLazyForEachActuator);
    /**
     * @tc.steps: step3. Add children items to lazyForEachNode.
     */
    UpdateItems(lazyForEachNode, mockLazyForEachActuator);
    return lazyForEachBuilder;
}
} // namespace OHOS::Ace::NG
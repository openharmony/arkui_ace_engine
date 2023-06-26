/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#define private public

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/remote_window/remote_window_pattern.h"
#include "core/components_ng/pattern/remote_window/remote_window_model_ng.h"
#include "core/components_ng/pattern/remote_window/remote_window_layout_algorithm.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float IDEAL_WIDTH = 300.0f;
const float IDEAL_HEIGHT = 300.0f;
const SizeF IDEAL_SIZE(IDEAL_WIDTH, IDEAL_HEIGHT);

const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);

class RemoteWindowTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RemoteWindowTestNg::SetUpTestCase()
{
}
void RemoteWindowTestNg::TearDownTestCase()
{
}
void RemoteWindowTestNg::SetUp() {}
void RemoteWindowTestNg::TearDown() {}

/**
 * @tc.name: RemoteWindowPatternTest001
 * @tc.desc: Test IsMeasureBoundary and IsAtomicNode.
 * @tc.type: FUNC
 */
HWTEST_F(RemoteWindowTestNg, RemoteWindowPatternTest001, TestSize.Level1)
{
    auto remoteWindowPattern = AceType::MakeRefPtr<RemoteWindowPattern>();
    EXPECT_TRUE(remoteWindowPattern->IsMeasureBoundary());
    EXPECT_TRUE(remoteWindowPattern->IsAtomicNode());
}

/**
 * @tc.name: RemoteWindowPatternTest002
 * @tc.desc: Test RemoteWindowPattern::OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(RemoteWindowTestNg, RemoteWindowPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize RemoteWindowPattern
     * @tc.expected: All pointer is non-null
     */
    auto pattern = AceType::MakeRefPtr<RemoteWindowPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);

    /**
     * @tc.steps: step2. Get host and check AttachToFrameNode run right
     * @tc.expected: Check measure type is MeasureType::MATCH_PARENT set by AttachToFrameNode
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    EXPECT_EQ(host->GetLayoutProperty()->GetMeasureType(), MeasureType::MATCH_PARENT);
}

/**
 * @tc.name: RemoteWindowModelNgTest001
 * @tc.desc: Test RemoteWindowModelNg::Create
 * @tc.type: FUNC
 */
HWTEST_F(RemoteWindowTestNg, RemoteWindowModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. clear stack
     */
    auto stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();

    /**
     * @tc.steps: step2. run RemoteWindowModelNg::Create
     */
    std::unique_ptr<RemoteWindowModel> instance = nullptr;
    instance.reset(new NG::RemoteWindowModelNG());
    std::shared_ptr<OHOS::Rosen::RSNode> rsNode = nullptr;
    instance->Create(rsNode);
    
    /**
     * @tc.expected: check tag of RemoteWindowModelNg
     */
    auto frameNode = stack->GetMainFrameNode();
    EXPECT_EQ(frameNode->GetTag(), V2::REMOTE_WINDOW_ETS_TAG);
}

/**
 * @tc.name: RemoteWindowLayoutAlgorithmTest001
 * @tc.desc: Test RemoteWindowLayoutAlgorithm::MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(RemoteWindowTestNg, RemoteWindowLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    auto pattern = AceType::MakeRefPtr<RemoteWindowPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, frameNode->geometryNode_, frameNode->GetLayoutProperty());
    auto layoutAlgorithm = AceType::MakeRefPtr<RemoteWindowLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step2. Call the function MeasureContent without the max size.
     * @tc.expected: The return value is equal to MAX_SIZE.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), MAX_SIZE);
    
    /**
     * @tc.steps: step3. Call the function MeasureContent with the ideal size.
     * @tc.expected: The return value is equal to IDEAL_SIZE.
     */
    layoutConstraint.selfIdealSize.SetSize(IDEAL_SIZE);
    canvasSize = layoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper);
    EXPECT_EQ(canvasSize.value_or(SizeF(0.0f, 0.0f)), IDEAL_SIZE);
}
}
} // namespace OHOS::Ace::NG


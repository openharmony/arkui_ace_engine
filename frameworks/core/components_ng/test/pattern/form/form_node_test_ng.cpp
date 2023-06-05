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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
FormModelNG formModelNG;
constexpr int32_t NODE_ID_OF_FORM_NODE = 123456;
constexpr int32_t NODE_ID_OF_PARENT_NODE = 654321;
} // namespace

struct TestProperty {};

class FormNodeTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateFromNode();
};

void FormNodeTestNg::SetUp()
{
    MockPipelineBase::SetUp();
}
void FormNodeTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: formModelNG
 * @tc.desc: Test function in form_model_ng when RequestFormInfo has not been setted
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTestNg, formModelNG, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a form node by GetOrCreateFormNode.
     * @tc.expected: Create node success.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    stack->Push(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    ASSERT_NE(property, nullptr);

    /**
     * @tc.steps: step2. Test function in form_model_ng when RequestFormInfo has not been setted.
     */
    formModelNG.SetDimension(0);
    formModelNG.AllowUpdate(true);
    formModelNG.SetModuleName("");
    formModelNG.SetVisible(VisibleType::INVISIBLE);
    ASSERT_EQ(property->HasRequestFormInfo(), false);

    /**
     * @tc.steps: step3. Test SetVisibility in form_model_ng when isLoaded is false  and visible is
     *                   VisibleType::VISIBLE.
     */
    auto formPattern = frameNode->GetPattern<FormPattern>();
    CHECK_NULL_VOID(formPattern);
    formPattern->isLoaded_ = false;
    formModelNG.SetVisibility(VisibleType::VISIBLE);
    ASSERT_EQ(property->GetVisibility(), VisibleType::INVISIBLE);

    /**
     * @tc.steps: step4. Test SetVisibility in form_model_ng when isLoaded is false  and visible is
     *                   VisibleType::INVISIBLE.
     */
    formPattern->isLoaded_ = true;
    formModelNG.SetVisibility(VisibleType::GONE);
    ASSERT_EQ(property->GetVisibility(), VisibleType::GONE);
}

/**
 * @tc.name: GetOrCreateFormNode001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormNodeTestNg, GetOrCreateFormNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a form node by GetOrCreateFormNode.
     * @tc.expected: Create node success.
     */
    auto frameNode = FormNode::GetOrCreateFormNode(
        "FormComponent", NODE_ID_OF_FORM_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get a form node by GetOrCreateFormNode with same nodeId.
     * @tc.expected: Get same node success.
     */
    auto sameFormNode = FormNode::GetOrCreateFormNode(
        "FormComponent", NODE_ID_OF_FORM_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    EXPECT_EQ(frameNode == sameFormNode, true);

    /**
     * @tc.steps: step3. Remove a form node by GetOrCreateFormNode with different tag when parent is nullptr.
     * @tc.expected: Get a different node success.
     */
    auto diffFormNode = FormNode::GetOrCreateFormNode(
        "FormComponent1", NODE_ID_OF_FORM_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    EXPECT_NE(frameNode == diffFormNode, true);

    /**
     * @tc.steps: step4. Remove a form node by GetOrCreateFormNode with different tag.
     * @tc.expected: Get a different node success and remove the node from parent.
     */
    auto parentFormNode = FormNode::GetOrCreateFormNode(
        "FormComponent", NODE_ID_OF_PARENT_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    ASSERT_NE(parentFormNode, nullptr);
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", NODE_ID_OF_FORM_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    formNode->SetParent(parentFormNode);
    parentFormNode->AddChild(formNode);
    ASSERT_EQ(parentFormNode->GetFirstChild(), formNode);
    diffFormNode = FormNode::GetOrCreateFormNode(
        "FormComponent1", NODE_ID_OF_FORM_NODE, []() { return AceType::MakeRefPtr<FormPattern>(); });
    EXPECT_NE(formNode == diffFormNode, true);
    ASSERT_EQ(AceType::TypeName(diffFormNode->pattern_), "FormPattern");
    ASSERT_EQ(parentFormNode->GetFirstChild(), nullptr);

    /**
     * @tc.steps: step5. Remove a form node by GetOrCreateFormNode without  patternCreator.
     * @tc.expected: Get a different node success.
     */
    formNode = FormNode::GetOrCreateFormNode("FormComponent", NODE_ID_OF_FORM_NODE, nullptr);
    auto pattrn = formNode->pattern_;
    ASSERT_EQ(AceType::TypeName(pattrn), "Pattern");
}
} // namespace OHOS::Ace::NG

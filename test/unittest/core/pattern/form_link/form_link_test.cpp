/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "frameworks/core/components_ng/pattern/form_link/form_link_model_ng.h"
#include "frameworks/core/components_ng/base/view_abstract.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#define private public
#include "frameworks/core/components_ng/pattern/form_link/form_link_pattern.h"
#undef private
#include "frameworks/core/components_ng/base/frame_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class FormLinkTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void FormLinkTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void FormLinkTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}


/**
 * @tc.name: FormLinkPatternTest001
 * @tc.desc: Test FormLinkPatternTest in Form Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(FormLinkTest, FormLinkPatternTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::FORM_LINK_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::FORM_LINK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FormLinkPattern>(); });
    auto pattern = frameNode->GetPattern<FormLinkPattern>();
    auto ret = std::make_shared<int64_t>(1);
    pattern->OnAttachToFrameNode();
    ASSERT_EQ(*ret, 1);
    pattern->OnAreaChangedInner();
    ASSERT_EQ(*ret, 1);
}
} // namespace OHOS::Ace::NG
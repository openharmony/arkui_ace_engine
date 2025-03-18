/*
 * SPDX-License-Identifier: Apache-2.0
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

#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/event/focus_core/focus_request_test.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/focus_state.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

const std::vector<FocusRequestTestCase> FOCUS_TEST_REQUEST_CASES = {
    // case1
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, true, true, true, "NODEA", { true, false }),
    // case2
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, true, true, true, "NODEB", { false, true }),
    // case3
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, true, false, true, "NODEA", { true, false }),
    // case4
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, true, false, true, "NODEB", { false, true }),
    // case5
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, false, true, true, "NODEA", { false, true }),
    // case6
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, false, true, true, "NODEB", { false, true }),
    // case7
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, false, false, true, "NODEA", { false, true }),
    // case8
    FocusRequestTestCase(FocusRequestFocusAble { true, true }, false, false, true, "NODEB", { false, true }),
    // case9
    FocusRequestTestCase(FocusRequestFocusAble { true, false }, true, false, true, "NODEA", { true, false }),
    // case10
    FocusRequestTestCase(FocusRequestFocusAble { true, false }, true, false, true, "NODEB", { false, false }),
    // case11
    FocusRequestTestCase(FocusRequestFocusAble { true, false }, true, false, true, "NODEA", { true, false }),
    // case12
    FocusRequestTestCase(FocusRequestFocusAble { true, false }, true, false, true, "NODEB", { false, false }),
};

void FocusRequestTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusRequestTestNG SetUpTestCase";
}

void FocusRequestTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusRequestTestNG TearDownTestCase";
}

testing::AssertionResult FocusRequestTestNG::IsRequestFocusStateEqual(
    int32_t caseNum, const std::vector<bool>& actualState, const std::vector<bool>& expectState)
{
    auto length = actualState.size();
    for (int32_t i = 0; i < length; i++) {
        if (actualState[i] != expectState[i]) {
            return testing::AssertionFailure()
                   << "TestCaseNum: " << caseNum << ", NodeId: " << i << ", actual state: " << actualState[i]
                   << ", expect state: " << expectState[i];
        }
    }
    return testing::AssertionSuccess();
}
RefPtr<FrameNode> FocusRequestTestNG::CreatNode(bool isFocusable)
{
    auto node = CreateNodeWithFocusPattern("node", FocusType::NODE, isFocusable);
    EXPECT_NE(node, nullptr);
    node->UpdateInspectorId("NODE");
    return node;
}
void FocusRequestTestNG::SetDependence(bool isDependenceSelf, const RefPtr<FocusHub>& focusHub)
{
    if (isDependenceSelf) {
        focusHub->SetFocusDependence(FocusDependence::SELF);
    } else {
        focusHub->SetFocusDependence(FocusDependence::AUTO);
    }
}
void FocusRequestTestNG::SetWindowSwiping(bool isWindowSwiping)
{
    if (isWindowSwiping) {
        auto context = PipelineBase::GetCurrentContext();
        context->RequestFrame();
    }
}
void FocusRequestTestNG::SetFcousCurrents(const RefPtr<FocusHub>& focusHub, const RefPtr<FrameNode>& node)
{
    auto pipeline = AceType::MakeRefPtr<MockPipelineContext>();
    focusHub->RequestFocus();
    pipeline->dirtyFocusNode_ = AceType::WeakClaim(AceType::RawPtr(node));
    pipeline->dirtyRequestFocusNode_ = AceType::WeakClaim(AceType::RawPtr(node));
    pipeline->FlushFocus();
}
void FocusRequestTestNG::InitFocusRequest()
{
    int32_t caseNum = 1;
    for (const auto& testCase : FOCUS_TEST_REQUEST_CASES) {
        auto rootNode = CreateRootNode();
        EXPECT_NE(rootNode, nullptr);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);

        auto nodeA = CreatNode(testCase.isFocusable.isAFocusable);
        auto focusHubA = nodeA->GetOrCreateFocusHub();
        EXPECT_NE(focusHubA, nullptr);

        auto nodeB = CreatNode(testCase.isFocusable.isBFocusable);
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        EXPECT_NE(focusHubB, nullptr);

        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);

        SetDependence(testCase.isADependenceSelf, focusHubA);
        SetWindowSwiping(testCase.isWindowSwiping);
        nodeA->onMainTree_ = testCase.isAOnMainTree;
        nodeB->onMainTree_ = testCase.isAOnMainTree;

        if (testCase.isFocusable.isAFocusable) {
            if ((!testCase.isFocusable.isBFocusable && testCase.inspectorId == "NODEA") ||
                (testCase.isADependenceSelf && testCase.inspectorId == "NODEA")) {
                SetFcousCurrents(focusHubA, nodeA);
            }
            if ((!testCase.isADependenceSelf && testCase.inspectorId == "NODEA") ||
                (testCase.isFocusable.isBFocusable && testCase.inspectorId == "NODEB")) {
                SetFcousCurrents(focusHubB, nodeB);
            }
        }

        std::vector<bool> results = { focusHubA->IsCurrentFocus(), focusHubB->IsCurrentFocus() };
        EXPECT_TRUE(IsRequestFocusStateEqual(caseNum, results, testCase.expectResults));
        caseNum++;
    }
}

HWTEST_F(FocusRequestTestNG, FocusRequestTest001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    InitFocusRequest();
}
} // namespace OHOS::Ace::NG
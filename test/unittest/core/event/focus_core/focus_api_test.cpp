/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/unittest/core/event/focus_core/focus_api_test.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

struct FocusApiTestRequestImmediatelyByIdCase {
    bool isAFocusable;
    bool isBFocusable;
    bool isADependenceSelf;
    bool isAOnMainTree;
    std::string inspectorId;
    std::vector<bool> expectResults;
    FocusApiTestRequestImmediatelyByIdCase(
        bool isAFocusable, bool isBFocusable, bool isADependenceSelf, bool isAOnMainTree,
        std::string inspectorId, const std::vector<bool>& expectResults) : isAFocusable(isAFocusable),
        isBFocusable(isBFocusable), isADependenceSelf(isADependenceSelf),
        isAOnMainTree(isAOnMainTree), inspectorId(inspectorId), expectResults(expectResults) {}
};

const std::vector<FocusApiTestRequestImmediatelyByIdCase>
    FOCUS_API_TEST_REQUESTIMMEDIATELYBYID_CASES = {
    // case1
    FocusApiTestRequestImmediatelyByIdCase(true, true, true, true, "NODEA", {true, false}),
    // case2
    FocusApiTestRequestImmediatelyByIdCase(true, true, true, true, "NODEB", {true, true}),
    // case3
    FocusApiTestRequestImmediatelyByIdCase(true, true, true, false, "NODEA", {false, false}),
    // case4
    FocusApiTestRequestImmediatelyByIdCase(true, true, true, false, "NODEB", {false, false}),
    // case5
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, true, "NODEA", {true, true}),
    // case6
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, true, "NODEB", {true, true}),
    // case7
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, false, "NODEA", {false, false}),
    // case8
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, false, "NODEB", {false, false}),
    // case9
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, false, "NODEA", {false, false}),
    // case10
    FocusApiTestRequestImmediatelyByIdCase(true, true, false, false, "NODEB", {false, false}),
};

void FocusApiTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusApiTestNG SetUpTestCase";
}

void FocusApiTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusApiTestNG TearDownTestCase";
}

testing::AssertionResult FocusApiTestNG::IsRequestImmediatelyByIdStateEqual(int32_t caseNum,
    const std::vector<bool>& actualState, const std::vector<bool>& expectState)
{
    auto length = actualState.size();
    for (int32_t i = 0; i < length; ++i) {
        if (actualState[i] != expectState[i]) {
            return testing::AssertionFailure() << "TestCaseNum: " << caseNum << ", NodeId: " <<
                i << ", actual state: " << actualState[i] << ", expect state: " << expectState[i];
        }
    }
    return testing::AssertionSuccess();
}

/**
 * @tc.name: FocusApiTestRequestImmediatelyById001
 * @tc.desc: RequestImmediatelyById
 * @tc.type: FUNC
 */
HWTEST_F(FocusApiTestNG, FocusApiTestRequestImmediatelyById001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : FOCUS_API_TEST_REQUESTIMMEDIATELYBYID_CASES) {

        /**
        * @tc.steps: step1. Create rootNode and focusHub.
        * @tc.expected: rootNode and focusHub not null.
        */
        auto rootNode = CreateRootNode();
        EXPECT_NE(rootNode, nullptr);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);

        /**
        * @tc.steps: step2. Create scope nodeA and focusHub.
        * @tc.expected: nodeA and focusHub not null.
        */
        auto nodeA = CreateNodeWithFocusPattern("nodeA", FocusType::SCOPE, testCase.isAFocusable);
        EXPECT_NE(nodeA, nullptr);
        nodeA->UpdateInspectorId("NODEA");
        auto focusHubA = nodeA->GetOrCreateFocusHub();
        EXPECT_NE(focusHubA, nullptr);

        /**
        * @tc.steps: step3. Create node nodeB and focusHub.
        * @tc.expected: nodeB and focusHub not null.
        */
        auto nodeB = CreateNodeWithFocusPattern("nodeB", FocusType::NODE, testCase.isBFocusable);
        EXPECT_NE(nodeB, nullptr);
        nodeB->UpdateInspectorId("NODEB");
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        EXPECT_NE(focusHubB, nullptr);

        /**
        * @tc.steps: step4. Add nodeA as child of rootNode, add nodeB as child of nodeA.
        */
        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);

        /**
        * @tc.steps: step5. Set FocusDependence::SELF to nodeA by input.
        */
        if (testCase.isADependenceSelf) {
            focusHubA->SetFocusDependence(FocusDependence::SELF);
        }

        /**
        * @tc.steps: step6. Set isOnMainTree of nodeA and nodeB by input.
        */
        nodeA->onMainTree_ = testCase.isAOnMainTree;
        nodeB->onMainTree_ = testCase.isAOnMainTree;

        /**
        * @tc.steps: step7. RequestFocusImmediatelyById.
        * @tc.expected: results are same as expectResults.
        */
        rootNodeFocusHub->RequestFocusImmediatelyById(testCase.inspectorId, true);
        std::vector<bool> results = {focusHubA->IsCurrentFocus(), focusHubB->IsCurrentFocus()};
        EXPECT_TRUE(IsRequestImmediatelyByIdStateEqual(caseNum, results,
            testCase.expectResults));
        ++caseNum;
    }
}
} // namespace OHOS::Ace::NG

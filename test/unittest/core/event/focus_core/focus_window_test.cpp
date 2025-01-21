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
#include "test/unittest/core/event/focus_core/focus_window_test.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

struct WindowFocusCase {
    bool isBLastFocusView;
    // 0 for null, 1 for root, 2 for B, 3 for C
    int32_t isNodeCurrentFocus;
    bool isBDependenceSelf;
    bool isBFocusable;
    bool isCFocusable;
    std::string expectResults;
    WindowFocusCase(
        bool isBLastFocusView, int32_t isNodeCurrentFocus, bool isBDependenceSelf, bool isBFocusable,
        bool isCFocusable, const std::string& expectResults) : isBLastFocusView(isBLastFocusView),
        isNodeCurrentFocus(isNodeCurrentFocus), isBDependenceSelf(isBDependenceSelf),
        isBFocusable(isBFocusable), isCFocusable(isCFocusable), expectResults(expectResults) {}
};

const std::vector<WindowFocusCase>
    WINDOW_FOCUS_CASES = {};

void FocusWindowTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusWindowTestNG SetUpTestCase";
}

void FocusWindowTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusWindowTestNG TearDownTestCase";
}

testing::AssertionResult FocusWindowTestNG::IsWindowFocusStateEqual(int32_t caseNum,
    std::string& expectState)
{
    if (!focusManager_) {
        return testing::AssertionFailure() << "TestCaseNum: " << caseNum <<
            "focusManager is null";
    }
    auto focusNode = focusManager_->switchingFocus_;
    if (!focusNode) {
        return testing::AssertionFailure() << "TestCaseNum: " << caseNum <<
            "focus node is null";
    }
    auto actualState = focusNode->GetFrameNode()->GetInspectorId().value_or("NULL");
    if (actualState != expectState) {
        return testing::AssertionFailure() << "TestCaseNum: " << caseNum <<
            ", actual state: " << actualState << ", expect state: " << expectState;
    }
    return testing::AssertionSuccess();
}

/**
 * @tc.name: FocusWindowTestNG001
 * @tc.desc: FocusWindowTestNG
 * @tc.type: FUNC
 */
HWTEST_F(FocusWindowTestNG, FocusWindowTestNG001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : WINDOW_FOCUS_CASES) {

        /**
        * @tc.steps: step1. Create rootNode and focusHub.
        * @tc.expected: rootNode and focusHub not null.
        */
        auto rootNode = CreateRootNode();
        EXPECT_NE(rootNode, nullptr);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);
        rootNode->UpdateInspectorId("ROOTNODE");

        /**
        * @tc.steps: step2. Create FocusView nodeB.
        * @tc.expected: nodeB and focusHubB not null.
        */
        std::list<int32_t> emptyList;
        auto nodeB = CreateFocusViewWithFocusPattern("nodeB", emptyList, FocusType::SCOPE, testCase.isBFocusable);
        EXPECT_NE(nodeB, nullptr);
        nodeB->UpdateInspectorId("NODEB");
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        EXPECT_NE(focusHubB, nullptr);
        auto focusViewB = nodeB->GetPattern<FocusView>();
        EXPECT_NE(focusViewB, nullptr);

        /**
        * @tc.steps: step3. Create nodeC.
        * @tc.expected: nodeC and focusHubC not null.
        */
        auto nodeC = CreateNodeWithFocusPattern("nodeC", FocusType::NODE, testCase.isCFocusable);
        EXPECT_NE(nodeC, nullptr);
        nodeC->UpdateInspectorId("NODEC");
        auto focusHubC = nodeC->GetOrCreateFocusHub();
        EXPECT_NE(focusHubC, nullptr);

        /**
        * @tc.steps: step4. Add nodeB as child of rootNode, add nodeC as child of nodeB.
        */
        rootNode->AddChild(nodeB);
        nodeB->AddChild(nodeC);

        /**
        * @tc.steps: step4. Set lastFocusView to nodeB or null.
        */
        if (testCase.isBLastFocusView) {
            focusManager_->lastFocusView_ = AceType::WeakClaim(AceType::RawPtr(focusViewB));
        } else {
            focusManager_->lastFocusView_ = nullptr;
        }
        
        /**
        * @tc.steps: step4. Set FocusDependence::SELF to nodeB and rootNode by input.
        */
        if (testCase.isNodeCurrentFocus == 1) {
            rootNodeFocusHub->SetFocusDependence(FocusDependence::SELF);
            rootNodeFocusHub->RequestFocusImmediatelyInner();
        } else if (testCase.isNodeCurrentFocus == 2) {
            focusHubB->SetFocusDependence(FocusDependence::SELF);
            focusHubB->RequestFocusImmediatelyInner();
        } else if (testCase.isNodeCurrentFocus == 3) {
            focusHubC->RequestFocusImmediatelyInner();
        }

        /**
        * @tc.steps: step5. Set FocusDependence::SELF to nodeB by input.
        */
        if (testCase.isBDependenceSelf) {
            focusHubB->SetFocusDependence(FocusDependence::SELF);
        }

        /**
        * @tc.steps: step6. Set Window Focus.
        * @tc.expected: results are same as expectResults.
        */
        auto context = PipelineContext::GetCurrentContext();
        EXPECT_NE(context, nullptr);
        context->WindowFocus(true);
        auto expectResults = testCase.expectResults;
        EXPECT_TRUE(IsWindowFocusStateEqual(caseNum, expectResults));
        ++caseNum;
    }
}
} // namespace OHOS::Ace::NG

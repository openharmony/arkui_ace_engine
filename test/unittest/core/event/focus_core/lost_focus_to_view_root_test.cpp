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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/event/focus_core/lost_focus_to_view_root_test.h"
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
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

struct LostFocusToViewRootCase {
    std::string checkPoint;   //  not report  A or null
    std::string getFocusNode; // A  B or  null
    std::string expectResults;
    LostFocusToViewRootCase(
        const std::string& checkPoint, const std::string& getFocusNode, const std::string& expectResults)
        : checkPoint(checkPoint), getFocusNode(getFocusNode), expectResults(expectResults)
    {}
};

const std::vector<LostFocusToViewRootCase> LOST_FOCUS_TO_VIEW_ROOT_CASES = { LostFocusToViewRootCase(
    "不上报", "A", "A") };

void LostFocusToViewRootTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "LostFocusToViewRootTestNG SetUpTestCase";
}

void LostFocusToViewRootTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "LostFocusToViewRootTestNG TearDownTestCase";
}

HWTEST_F(LostFocusToViewRootTestNG, LostFocusToViewRootTestNG001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LOST_FOCUS_TO_VIEW_ROOT_CASES) {
        // create root node
        auto rootNode = CreateRootNode();
        CHECK_NULL_VOID(rootNode);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);
        CHECK_NULL_VOID(rootNodeFocusHub);

        // create node A
        auto nodeA = CreateNodeWithFocusPattern("nodeA", FocusType::NODE, true);
        CHECK_NULL_VOID(nodeA);
        nodeA->UpdateInspectorId("A");
        auto nodeAFocusHub = nodeA->GetOrCreateFocusHub();
        CHECK_NULL_VOID(nodeAFocusHub);

        // create node B
        auto nodeB = CreateNodeWithFocusPattern("nodeB", FocusType::NODE, true);
        CHECK_NULL_VOID(nodeB);
        nodeB->UpdateInspectorId("B");
        auto nodeBFocusHub = nodeB->GetOrCreateFocusHub();
        CHECK_NULL_VOID(nodeBFocusHub);

        // create node tree
        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);

        // Request focus according to the test case
        if (testCase.getFocusNode == "A") {
            if (nodeAFocusHub) {
                nodeAFocusHub->RequestFocusImmediately();
            }
        } else if (testCase.getFocusNode == "B") {
            if (nodeBFocusHub) {
                nodeBFocusHub->RequestFocusImmediately();
            }
        }

        // Simulate losing focus to the view root node
        if (rootNodeFocusHub) {
            rootNodeFocusHub->LostFocusToViewRoot();
        }

        // get current focus node
        std::string actualState = "NULL";
        if (focusManager_) {
            auto currentFocusNode = focusManager_->GetCurrentFocus();
            if (currentFocusNode) {
                auto inspectorId = currentFocusNode->GetFrameNode()->GetInspectorId();
                actualState = inspectorId.has_value() ? inspectorId.value() : "NULL";
            }
        }

        // Verify result
        EXPECT_EQ(actualState, testCase.expectResults)
            << "TestCaseNum: " << caseNum << ", actual state: " << actualState
            << ", expect state: " << testCase.expectResults;

        ++caseNum;
    }
}
} // namespace OHOS::Ace::NG

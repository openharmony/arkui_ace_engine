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
#include "test/unittest/core/event/focus_core/focus_test_base.h"
#include "test/unittest/core/event/focus_core/linear_focus_test.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/flex/flex_element.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
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
#include "core/event/focus_axis_event.h"
#include "core/event/key_event.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

void LinearFocusingTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "LinearFocusingTestNG SetUpTestCase";
}

void LinearFocusingTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "GoFocusTestNG TearDownTestCase";
}

void LinearFocusingTestNG::CreateAndInitNodes(RefPtr<FrameNode>& rootNode, RefPtr<FocusHub>& rootNodeFocusHub,
    RefPtr<FrameNode>& nodeA, RefPtr<FocusHub>& focusHubA, RefPtr<FrameNode>& nodeB, RefPtr<FocusHub>& focusHubB,
    RefPtr<FrameNode>& nodeC, RefPtr<FocusHub>& focusHubC, RefPtr<FrameNode>& nodeD, RefPtr<FocusHub>& focusHubD,
    RefPtr<FrameNode>& nodeE, RefPtr<FocusHub>& focusHubE, RefPtr<FrameNode>& nodeF, RefPtr<FocusHub>& focusHubF)
{
    rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);
    rootNode->UpdateInspectorId("ROOTNODE");

    nodeA = CreateNodeWithFocusPattern("nodeA", FocusType::NODE, true);
    EXPECT_NE(nodeA, nullptr);
    nodeA->UpdateInspectorId("A");
    focusHubA = nodeA->GetOrCreateFocusHub();
    EXPECT_NE(focusHubA, nullptr);

    nodeB = CreateNodeWithFocusPattern("nodeB", FocusType::NODE, true);
    EXPECT_NE(nodeB, nullptr);
    nodeB->UpdateInspectorId("B");
    focusHubB = nodeB->GetOrCreateFocusHub();
    EXPECT_NE(focusHubB, nullptr);

    nodeC = CreateNodeWithFocusPattern("nodeC", FocusType::NODE, true);
    EXPECT_NE(nodeC, nullptr);
    nodeC->UpdateInspectorId("C");
    focusHubC = nodeC->GetOrCreateFocusHub();
    EXPECT_NE(focusHubC, nullptr);

    nodeD = CreateNodeWithFocusPattern("nodeD", FocusType::NODE, true);
    EXPECT_NE(nodeD, nullptr);
    nodeD->UpdateInspectorId("D");
    focusHubD = nodeD->GetOrCreateFocusHub();
    EXPECT_NE(focusHubD, nullptr);

    nodeE = CreateNodeWithFocusPattern("nodeE", FocusType::NODE, true);
    EXPECT_NE(nodeE, nullptr);
    nodeE->UpdateInspectorId("E");
    focusHubE = nodeE->GetOrCreateFocusHub();
    EXPECT_NE(focusHubE, nullptr);

    nodeF = CreateNodeWithFocusPattern("nodeF", FocusType::NODE, true);
    EXPECT_NE(nodeF, nullptr);
    nodeF->UpdateInspectorId("F");
    focusHubF = nodeF->GetOrCreateFocusHub();
    EXPECT_NE(focusHubF, nullptr);

    rootNode->AddChild(nodeA);
    nodeA->AddChild(nodeB);
    nodeA->AddChild(nodeC);
    nodeA->AddChild(nodeD);
    nodeC->AddChild(nodeE);
    nodeC->AddChild(nodeF);
}

void LinearFocusingTestNG::HandleFocusAndExecuteTest(int32_t caseNum, const LinearFocusingDirectCase& testCase,
    RefPtr<FocusHub> focusHubB, RefPtr<FocusHub> focusHubC, RefPtr<FocusHub> focusHubD, RefPtr<FocusHub> focusHubE,
    RefPtr<FocusHub> focusHubF)
{
    if (testCase.goFocusStartPoint == "B") {
        LinearFocusingTestNG::Test02Focus(caseNum, testCase, focusHubB);
    }
    if (testCase.goFocusStartPoint == "C") {
        if (testCase.isChildNodeGetFocus) {
            focusHubE->SetFocusable(true);
            focusHubF->SetFocusable(true);
        } else {
            focusHubE->SetFocusable(false);
            focusHubF->SetFocusable(false);
        }
        LinearFocusingTestNG::Test02Focus(caseNum, testCase, focusHubC);
    }
    if (testCase.goFocusStartPoint == "D") {
        LinearFocusingTestNG::Test02Focus(caseNum, testCase, focusHubD);
    }
}

void LinearFocusingTestNG::HomeOrTabFocus(int caseNum, const LinearFocusingCase& testCase, RefPtr<FocusHub> focusHub)
{
    focusHub->SetCurrentFocus(true);
    if (testCase.isGoFocusActivityStatus) {
        focusHub->isFocusActiveWhenFocused_ = true;
    }
    if (testCase.goFocusStartPoint == "D") {
        if (testCase.inputValue == "上键走焦") {
            focusHub->RequestNextFocus(FocusStep::UP);
        } else if (testCase.inputValue == "下键走焦") {
            focusHub->RequestNextFocus(FocusStep::DOWN);
        } else if (testCase.inputValue == "左键走焦") {
            focusHub->RequestNextFocus(FocusStep::LEFT);
        } else if (testCase.inputValue == "右键走焦") {
            focusHub->RequestNextFocus(FocusStep::RIGHT);
        }
    } else if (testCase.goFocusStartPoint == "A") {
        if (testCase.inputValue == "Tab走焦") {
            focusHub->RequestNextFocus(FocusStep::TAB);
            EXPECT_EQ(focusHub->IsCurrentFocus(), true)
                << "TestCaseNum: " << caseNum << ", inputvalue: " << testCase.inputValue;
        } else if (testCase.inputValue == "Shift+Tab走焦") {
            focusHub->RequestNextFocus(FocusStep::SHIFT_TAB);
        }
    } else if (testCase.goFocusStartPoint == "B") {
        if (testCase.inputValue == "Tab走焦") {
            focusHub->RequestNextFocus(FocusStep::TAB);
        } else if (testCase.inputValue == "Shift+Tab走焦") {
            focusHub->RequestNextFocus(FocusStep::SHIFT_TAB);
        }
    }
    HomeOrTabFocusExpect(caseNum, testCase, focusHub);
}

void LinearFocusingTestNG::HomeOrTabFocusExpect(
    int caseNum, const LinearFocusingCase& testCase, RefPtr<FocusHub> focusHub)
{
    if (testCase.expectResults == "A") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual A STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "B") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual B STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "C") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual C STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "D") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual D STATSU: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "E") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual E STATSU: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "F") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual F STATSU: " << focusHub->IsCurrentFocus();
    }
}

void LinearFocusingTestNG::Test02Focus(int caseNum, const LinearFocusingDirectCase& testCase, RefPtr<FocusHub> focusHub)
{
    focusHub->SetCurrentFocus(true);
    if (testCase.isGoFocusActivityStatus) {
        focusHub->isFocusActiveWhenFocused_ = true;
    }

    if (testCase.isparentCanDealCurrentOperation) {
        focusHub->SetParentFocusable(true);
    }

    if (testCase.isBrotherNodeGetFocus) {
        focusHub->focusable_ = true;
    }
    if (testCase.inputValue == "上键走焦") {
        focusHub->RequestNextFocus(FocusStep::UP);
    } else if (testCase.inputValue == "下键走焦") {
        focusHub->RequestNextFocus(FocusStep::DOWN);
    } else if (testCase.inputValue == "左键走焦") {
        focusHub->RequestNextFocus(FocusStep::LEFT);
    } else if (testCase.inputValue == "右键走焦") {
        focusHub->RequestNextFocus(FocusStep::RIGHT);
    }
    Test02FocusExpect(caseNum, testCase, focusHub);
}
void LinearFocusingTestNG::Test02FocusExpect(
    int caseNum, const LinearFocusingDirectCase& testCase, RefPtr<FocusHub> focusHub)
{
    if (testCase.expectResults == "A") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual A STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "B") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual B STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "C") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual C STATUS: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "D") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual D STATSU: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "E") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual E STATSU: " << focusHub->IsCurrentFocus();
    } else if (testCase.expectResults == "F") {
        EXPECT_EQ(focusHub->IsCurrentFocus(), true)
            << "TestCaseNum: " << caseNum << ", actual F STATSU: " << focusHub->IsCurrentFocus();
    }
}

void LinearFocusingTestNG::CreatNodeHandleLeftRightFocus(int caseNum, const LinearFocusingHomeCase& testCase)
{
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);
    rootNode->UpdateInspectorId("ROOTNODE");

    /**
     * @tc.steps: step2. Create FocusView nodeB.
     * @tc.expected: nodeB and focusHubB not null.
     */
    auto nodeA = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(nodeA, nullptr);
    nodeA->UpdateInspectorId("A");
    auto focusHubA = nodeA->GetOrCreateFocusHub();
    EXPECT_NE(focusHubA, nullptr);
    /**
     * @tc.steps: step3. Create FocusView nodeB.
     * @tc.expected: nodeB and focusHubB not null.
     */
    auto nodeB = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(nodeB, nullptr);
    nodeB->UpdateInspectorId("B");
    auto focusHubB = nodeB->GetOrCreateFocusHub();
    EXPECT_NE(focusHubB, nullptr);

    /**
     * @tc.steps: step4. Create FocusView nodec.
     * @tc.expected: nodeB and focusHubB not null.
     */
    auto nodeC = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(nodeC, nullptr);
    nodeC->UpdateInspectorId("C");
    auto focusHubC = nodeC->GetOrCreateFocusHub();
    EXPECT_NE(focusHubC, nullptr);

    /**
     * @tc.steps: step5. Create nodeC.
     * @tc.expected: nodeC and focusHubC not null.
     */
    auto nodeD = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_NE(nodeD, nullptr);
    nodeD->UpdateInspectorId("D");
    auto focusHubD = nodeC->GetOrCreateFocusHub();
    EXPECT_NE(focusHubD, nullptr);
    /**
     * @tc.steps: step6. Add nodes
     */
    rootNode->AddChild(nodeA);
    nodeA->AddChild(nodeB);
    nodeA->AddChild(nodeC);
    nodeA->AddChild(nodeD);

    if (testCase.isGoFocusActivityStatus) {
        focusHubC->isFocusActiveWhenFocused_ = true;
    }
    if (!testCase.goFocusStartPoint.empty()) {
        focusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubC));
    }

    if (testCase.inputValue == "HOME键走焦") {
        focusHubC->RequestNextFocus(FocusStep::LEFT_END) || focusHubC->RequestNextFocus(FocusStep::UP_END);
    } else if (testCase.inputValue == "END键走焦") {
        focusHubC->RequestNextFocus(FocusStep::RIGHT_END) || focusHubC->RequestNextFocus(FocusStep::DOWN_END);
    }

    auto lastFocusNode = focusHubC->GetLastWeakFocusNode().Upgrade();
    std::string actualNode = lastFocusNode ? lastFocusNode->GetFrameNode()->GetInspectorId().value_or("") : "";

    EXPECT_EQ(actualNode, testCase.expectResults)
        << "TestCaseNum: " << caseNum << ", actual node: " << actualNode << ", expect node: " << testCase.expectResults;
}

void LinearFocusingTestNG::CreatNodeHandleUpDownFocus(int caseNum, const LinearFocusingHomeCase& testCase)
{
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);
    rootNode->UpdateInspectorId("ROOTNODE");
    auto nodeA = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(nodeA, nullptr);
    nodeA->UpdateInspectorId("A");
    auto focusHubA = nodeA->GetOrCreateFocusHub();
    EXPECT_NE(focusHubA, nullptr);

    /**
     * @tc.steps: step3. Create FocusView nodeB.
     * @tc.expected: nodeB and focusHubB not null.
     */
    auto nodeB = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(nodeB, nullptr);
    nodeB->UpdateInspectorId("B");
    auto focusHubB = nodeB->GetOrCreateFocusHub();
    EXPECT_NE(focusHubB, nullptr);

    /**
     * @tc.steps: step4. Create FocusView nodec.
     * @tc.expected: nodeB and focusHubB not null.
     */
    auto nodeC = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(nodeC, nullptr);
    nodeC->UpdateInspectorId("C");
    auto focusHubC = nodeC->GetOrCreateFocusHub();
    EXPECT_NE(focusHubC, nullptr);

    /**
     * @tc.steps: step5. Create nodeC.
     * @tc.expected: nodeC and focusHubC not null.
     */
    auto nodeD = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_NE(nodeD, nullptr);
    nodeD->UpdateInspectorId("D");
    auto focusHubD = nodeC->GetOrCreateFocusHub();
    EXPECT_NE(focusHubD, nullptr);
    /**
     * @tc.steps: step6. Add nodes
     */
    rootNode->AddChild(nodeA);
    nodeA->AddChild(nodeB);
    nodeA->AddChild(nodeC);
    nodeA->AddChild(nodeD);

    if (testCase.isGoFocusActivityStatus) {
        focusHubC->isFocusActiveWhenFocused_ = true;
    }

    if (!testCase.goFocusStartPoint.empty()) {
        focusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubC));
    }
    if (testCase.inputValue == "HOME键走焦") {
        focusHubC->RequestNextFocus(FocusStep::LEFT_END) || focusHubC->RequestNextFocus(FocusStep::UP_END);
    } else if (testCase.inputValue == "END键走焦") {
        focusHubC->RequestNextFocus(FocusStep::RIGHT_END) || focusHubC->RequestNextFocus(FocusStep::DOWN_END);
    }
    auto lastFocusNode = focusHubC->GetLastWeakFocusNode().Upgrade();
    std::string actualNode = lastFocusNode ? lastFocusNode->GetFrameNode()->GetInspectorId().value_or("") : "";
    EXPECT_EQ(actualNode, testCase.expectResults)
        << "TestCaseNum: " << caseNum << ", actual node: " << actualNode << ", expect node: " << testCase.expectResults;
}

HWTEST_F(LinearFocusingTestNG, LinearFocusingTestNG001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LINEAR_FOCUSING_CASES) {
        RefPtr<FrameNode> rootNode;
        RefPtr<FocusHub> rootNodeFocusHub;
        RefPtr<FrameNode> nodeA, nodeB, nodeC, nodeD, nodeE, nodeF;
        RefPtr<FocusHub> focusHubA, focusHubB, focusHubC, focusHubD, focusHubE, focusHubF;
        CreateAndInitNodes(rootNode, rootNodeFocusHub, nodeA, focusHubA, nodeB, focusHubB, nodeC, focusHubC, nodeD,
            focusHubD, nodeE, focusHubE, nodeF, focusHubF);

        if (!testCase.goFocusStartPoint.empty()) {
            if (testCase.isConfigurationTabindexNode) {
                OHOS::Ace::KeyEvent keyEvent;
                keyEvent.action = KeyAction::DOWN;
                keyEvent.code = KeyCode::KEY_TAB;
                focusHubA->HandleFocusByTabIndex(keyEvent);
            }
            if (testCase.isBrotherNodeGetFocus)
                focusHubC->focusable_ = true;
            if (testCase.isChildNodeGetFocus)
                focusHubE->SetFocusable(true);
            else
                focusHubE->SetFocusable(false);

            RefPtr<FocusHub> startHub;
            if (testCase.goFocusStartPoint == "A")
                startHub = focusHubA;
            else if (testCase.goFocusStartPoint == "B")
                startHub = focusHubB;
            else if (testCase.goFocusStartPoint == "D")
                startHub = focusHubD;

            LinearFocusingTestNG::HomeOrTabFocus(caseNum, testCase, startHub);
        }
        ++caseNum;
    }
}

HWTEST_F(LinearFocusingTestNG, LinearFocusingTestNG002, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LINEAR_FOCUSING_DIRECT_CASES) {
        RefPtr<FrameNode> rootNode;
        RefPtr<FocusHub> rootNodeFocusHub;
        RefPtr<FrameNode> nodeA, nodeB, nodeC, nodeD, nodeE, nodeF;
        RefPtr<FocusHub> focusHubA, focusHubB, focusHubC, focusHubD, focusHubE, focusHubF;

        CreateAndInitNodes(rootNode, rootNodeFocusHub, nodeA, focusHubA, nodeB, focusHubB, nodeC, focusHubC, nodeD,
            focusHubD, nodeE, focusHubE, nodeF, focusHubF);

        HandleFocusAndExecuteTest(caseNum, testCase, focusHubB, focusHubC, focusHubD, focusHubE, focusHubF);

        ++caseNum;
    }
}

HWTEST_F(LinearFocusingTestNG, LinearFocusingTestNG003, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LINEAR_FOCUSING_HOME_CASES) {
        if (testCase.isparentNodeHandleLeftRightFocus) {
            CreatNodeHandleLeftRightFocus(caseNum, testCase);
        } else {
            CreatNodeHandleUpDownFocus(caseNum, testCase);
        }
        ++caseNum;
    }
}

} // namespace OHOS::Ace::NG

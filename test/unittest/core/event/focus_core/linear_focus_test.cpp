/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

struct LinearFocusingCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isConfigurationTabindexNode;
    bool isBrotherNodeGetFocus;
    bool isChildNodeGetFocus;
    std::string inputValue;    // input value
    std::string expectResults; // expect value
    LinearFocusingCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isConfigurationTabindexNode, bool isBrotherNodeGetFocus, bool isChildNodeGetFocus,
        const std::string& inputValue, const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isConfigurationTabindexNode(isConfigurationTabindexNode), isBrotherNodeGetFocus(isBrotherNodeGetFocus),
          isChildNodeGetFocus(isChildNodeGetFocus), inputValue(inputValue), expectResults(expectResults)
    {}
};
struct LinearFocusingDirectCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isparentCanDealCurrentOperation;
    bool isBrotherNodeGetFocus;
    bool isChildNodeGetFocus;
    std::string inputValue;    // input value
    std::string expectResults; // expect value
    LinearFocusingDirectCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isparentCanDealCurrentOperation, bool isBrotherNodeGetFocus, bool isChildNodeGetFocus,
        const std::string& inputValue, const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isparentCanDealCurrentOperation(isparentCanDealCurrentOperation),
          isBrotherNodeGetFocus(isBrotherNodeGetFocus), isChildNodeGetFocus(isChildNodeGetFocus),
          inputValue(inputValue), expectResults(expectResults)
    {}
};

struct LinearFocusingHomeCase {
    std::string goFocusStartPoint;
    bool isGoFocusActivityStatus;
    bool isparentNodeHandleLeftRightFocus;
    bool isparentNodeHandleUpOrDownFocus;
    std::string inputValue;    // input value
    std::string expectResults; // expect value
    LinearFocusingHomeCase(const std::string& goFocusStartPoint, bool isGoFocusActivityStatus,
        bool isparentNodeHandleLeftRightFocus, bool isparentNodeHandleUpOrDownFocus, const std::string& inputValue,
        const std::string& expectResults)
        : goFocusStartPoint(goFocusStartPoint), isGoFocusActivityStatus(isGoFocusActivityStatus),
          isparentNodeHandleLeftRightFocus(isparentNodeHandleLeftRightFocus),
          isparentNodeHandleUpOrDownFocus(isparentNodeHandleUpOrDownFocus), inputValue(inputValue),
          expectResults(expectResults)
    {}
};

const std::vector<LinearFocusingCase> LINEAR_FOCUSING_CASES = { LinearFocusingCase(
    { "A", true, false, false, false, "Tab走焦", "A" }) };

const std::vector<LinearFocusingDirectCase> LINEAR_FOCUSING_DIRECT_CASES = { LinearFocusingDirectCase(
    { "B", false, false, false, false, "上键走焦", "B" }) };

const std::vector<LinearFocusingHomeCase> LINEAR_FOCUSING_HOME_CASES = { LinearFocusingHomeCase(
    { "C", false, false, false, "HOME键走焦", "C" }) };

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

HWTEST_F(LinearFocusingTestNG, LinearFocusingTestNG001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LINEAR_FOCUSING_CASES) {
        // creat root node
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
        auto nodeA = CreateNodeWithFocusPattern("nodeA", FocusType::NODE, true);
        EXPECT_NE(nodeA, nullptr);
        nodeA->UpdateInspectorId("A");
        auto focusHubA = nodeA->GetOrCreateFocusHub();
        EXPECT_NE(focusHubA, nullptr);

        /**
         * @tc.steps: step3. Create FocusView nodeB.
         * @tc.expected: nodeB and focusHubB not null.
         */
        auto nodeB = CreateNodeWithFocusPattern("nodeB", FocusType::NODE, true);
        EXPECT_NE(nodeB, nullptr);
        nodeB->UpdateInspectorId("B");
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        EXPECT_NE(focusHubB, nullptr);

        /**
         * @tc.steps: step4. Create FocusView nodec.
         * @tc.expected: nodeB and focusHubB not null.
         */
        auto nodeC = CreateNodeWithFocusPattern("nodeC", FocusType::NODE, true);
        EXPECT_NE(nodeC, nullptr);
        nodeC->UpdateInspectorId("C");
        auto focusHubC = nodeC->GetOrCreateFocusHub();
        EXPECT_NE(focusHubC, nullptr);

        /**
         * @tc.steps: step5. Create nodeD.
         * @tc.expected: nodeD and focusHubD not null.
         */
        auto nodeD = CreateNodeWithFocusPattern("nodeD", FocusType::NODE, true);
        EXPECT_NE(nodeD, nullptr);
        nodeD->UpdateInspectorId("D");
        auto focusHubD = nodeD->GetOrCreateFocusHub();
        EXPECT_NE(focusHubD, nullptr);

        /**
         * @tc.steps: step6. Create nodeE.
         * @tc.expected: nodeE and focusHubE not null.
         */
        auto nodeE = CreateNodeWithFocusPattern("nodeE", FocusType::NODE, true);
        EXPECT_NE(nodeE, nullptr);
        nodeD->UpdateInspectorId("E");
        auto focusHubE = nodeE->GetOrCreateFocusHub();
        EXPECT_NE(focusHubE, nullptr);

        /**
         * @tc.steps: step7. Create nodeF.
         * @tc.expected: nodeF and focusHubF not null.
         */
        auto nodeF = CreateNodeWithFocusPattern("nodeF", FocusType::NODE, true);
        EXPECT_NE(nodeF, nullptr);
        nodeF->UpdateInspectorId("F");
        auto focusHubF = nodeF->GetOrCreateFocusHub();
        EXPECT_NE(focusHubF, nullptr);

        /**
         * @tc.steps: step8. Add nodes
         */
        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);
        nodeA->AddChild(nodeC);
        nodeA->AddChild(nodeD);
        nodeC->AddChild(nodeE);
        nodeC->AddChild(nodeF);

        if (!testCase.goFocusStartPoint.empty()) {
            // tab
            if (testCase.isConfigurationTabindexNode) {
                OHOS::Ace::KeyEvent keyEvent;
                keyEvent.action = KeyAction::DOWN;
                keyEvent.code = KeyCode::KEY_TAB;
                focusHubA->HandleFocusByTabIndex(keyEvent);
            }
            // is brother node can get focus
            if (testCase.isBrotherNodeGetFocus) {
                focusHubC->focusable_ = true;
            }
            // is child node can get focus
            if (testCase.isChildNodeGetFocus) {
                focusHubE->SetFocusable(true);
            } else {
                focusHubE->SetFocusable(false);
            }
            if (testCase.goFocusStartPoint == "A") {
                focusHubA->SetCurrentFocus(true);
                // set activity status
                if (testCase.isGoFocusActivityStatus) {
                    focusHubA->isFocusActiveWhenFocused_ = true;
                }
                //  set focusstep
                if (testCase.inputValue == "Tab走焦") {
                    focusHubA->RequestNextFocus(FocusStep::TAB);
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", inputvalue: " << testCase.inputValue;
                } else if (testCase.inputValue == "Shift+Tab走焦") {
                    focusHubA->RequestNextFocus(FocusStep::SHIFT_TAB);
                }

                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubF->IsCurrentFocus();
                }
            }
            if (testCase.goFocusStartPoint == "B") {
                focusHubB->SetCurrentFocus(true);
                // set activity status
                if (testCase.isGoFocusActivityStatus) {
                    focusHubB->isFocusActiveWhenFocused_ = true;
                }
                //  set focusstep
                if (testCase.inputValue == "Tab走焦") {
                    focusHubB->RequestNextFocus(FocusStep::TAB);
                } else if (testCase.inputValue == "Shift+Tab走焦") {
                    focusHubB->RequestNextFocus(FocusStep::SHIFT_TAB);
                }

                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubF->IsCurrentFocus();
                }
            }
            if (testCase.goFocusStartPoint == "D") {
                focusHubD->SetCurrentFocus(true);
                // set activity status
                if (testCase.isGoFocusActivityStatus) {
                    focusHubD->isFocusActiveWhenFocused_ = true;
                }
                //  set focusstep
                if (testCase.inputValue == "Tab走焦") {
                    focusHubD->RequestNextFocus(FocusStep::TAB);
                } else if (testCase.inputValue == "Shift+Tab走焦") {
                    focusHubD->RequestNextFocus(FocusStep::SHIFT_TAB);
                }

                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual node: " << focusHubF->IsCurrentFocus();
                }
            }
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
         * @tc.steps: step2. Create FocusView nodeA.
         * @tc.expected: nodeA and focusHubB not null.
         */
        auto nodeA = CreateNodeWithFocusPattern("nodeA", FocusType::NODE, true);
        EXPECT_NE(nodeA, nullptr);
        nodeA->UpdateInspectorId("A");
        auto focusHubA = nodeA->GetOrCreateFocusHub();
        EXPECT_NE(focusHubA, nullptr);

        /**
         * @tc.steps: step3. Create FocusView nodeB.
         * @tc.expected: nodeB and focusHubB not null.
         */
        auto nodeB = CreateNodeWithFocusPattern("nodeB", FocusType::NODE, true);
        EXPECT_NE(nodeB, nullptr);
        nodeB->UpdateInspectorId("B");
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        EXPECT_NE(focusHubB, nullptr);

        /**
         * @tc.steps: step4. Create FocusView nodec.
         * @tc.expected: nodeB and focusHubB not null.
         */
        auto nodeC = CreateNodeWithFocusPattern("nodeC", FocusType::NODE, true);
        EXPECT_NE(nodeC, nullptr);
        nodeC->UpdateInspectorId("C");
        auto focusHubC = nodeC->GetOrCreateFocusHub();
        EXPECT_NE(focusHubC, nullptr);

        /**
         * @tc.steps: step5. Create nodeD.
         * @tc.expected: nodeD and focusHubD not null.
         */
        auto nodeD = CreateNodeWithFocusPattern("nodeD", FocusType::NODE, true);
        EXPECT_NE(nodeD, nullptr);
        nodeD->UpdateInspectorId("D");
        auto focusHubD = nodeD->GetOrCreateFocusHub();
        EXPECT_NE(focusHubD, nullptr);

        /**
         * @tc.steps: step6. Create nodeE.
         * @tc.expected: nodeE and focusHubE not null.
         */
        auto nodeE = CreateNodeWithFocusPattern("nodeE", FocusType::NODE, true);
        EXPECT_NE(nodeE, nullptr);
        nodeD->UpdateInspectorId("E");
        auto focusHubE = nodeE->GetOrCreateFocusHub();
        EXPECT_NE(focusHubE, nullptr);

        /**
         * @tc.steps: step7. Create nodeC.
         * @tc.expected: nodeC and focusHubF not null.
         */
        auto nodeF = CreateNodeWithFocusPattern("nodeF", FocusType::NODE, true);
        EXPECT_NE(nodeF, nullptr);
        nodeF->UpdateInspectorId("F");
        auto focusHubF = nodeF->GetOrCreateFocusHub();
        EXPECT_NE(focusHubF, nullptr);

        /**
         * @tc.steps: step8. Add nodes
         */
        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);
        nodeA->AddChild(nodeC);
        nodeA->AddChild(nodeD);
        nodeC->AddChild(nodeE);
        nodeC->AddChild(nodeF);

        // set start node
        if (!testCase.goFocusStartPoint.empty()) {
            focusHubB->SetCurrentFocus(true);
            if (testCase.goFocusStartPoint == "B") {
                if (testCase.isGoFocusActivityStatus) {
                    focusHubB->isFocusActiveWhenFocused_ = true;
                }

                // set father node can deal operation
                if (testCase.isparentCanDealCurrentOperation) {
                    focusHubB->SetParentFocusable(true);
                }

                // is brother node can get focus
                if (testCase.isBrotherNodeGetFocus) {
                    focusHubB->focusable_ = true;
                }

                //  set focusstep
                if (testCase.inputValue == "上键走焦") {
                    // run focus
                    focusHubB->RequestNextFocus(FocusStep::UP);

                } else if (testCase.inputValue == "下键走焦") {
                    focusHubB->RequestNextFocus(FocusStep::DOWN);
                } else if (testCase.inputValue == "左键走焦") {
                    focusHubB->RequestNextFocus(FocusStep::LEFT);
                } else if (testCase.inputValue == "右键走焦") {
                    focusHubB->RequestNextFocus(FocusStep::RIGHT);
                }
                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual A STATUS: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual B STATUS: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual C STATUS: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual D STATSU: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual E STATSU: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual F STATSU: " << focusHubF->IsCurrentFocus();
                }
            }
            if (testCase.goFocusStartPoint == "C") {
                focusHubC->SetCurrentFocus(true);
                if (testCase.isGoFocusActivityStatus) {
                    focusHubC->isFocusActiveWhenFocused_ = true;
                }

                // set father node can deal operation
                if (testCase.isparentCanDealCurrentOperation) {
                    focusHubC->SetParentFocusable(true);
                }

                // is brother node can get focus
                if (testCase.isBrotherNodeGetFocus) {
                    focusHubC->focusable_ = true;
                }

                // is child node can get focus
                if (testCase.isChildNodeGetFocus) {
                    focusHubE->SetFocusable(true);
                    focusHubF->SetFocusable(true);
                } else {
                    focusHubE->SetFocusable(false);
                    focusHubF->SetFocusable(false);
                }
                //  set focusstep
                if (testCase.inputValue == "上键走焦") {
                    // run focus
                    focusHubC->RequestNextFocus(FocusStep::UP);
                } else if (testCase.inputValue == "下键走焦") {
                    focusHubC->RequestNextFocus(FocusStep::DOWN);
                } else if (testCase.inputValue == "左键走焦") {
                    focusHubC->RequestNextFocus(FocusStep::LEFT);
                } else if (testCase.inputValue == "右键走焦") {
                    focusHubC->RequestNextFocus(FocusStep::RIGHT);
                }
                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual A STATUS: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual B STATUS: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual C STATUS: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual D STATSU: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual E STATSU: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual F STATSU: " << focusHubF->IsCurrentFocus();
                }
            }
            if (testCase.goFocusStartPoint == "D") {
                focusHubD->SetCurrentFocus(true);
                if (testCase.isGoFocusActivityStatus) {
                    focusHubD->isFocusActiveWhenFocused_ = true;
                }

                // set father node can deal operation
                if (testCase.isparentCanDealCurrentOperation) {
                    focusHubD->SetParentFocusable(true);
                }

                // is brother node can get focus
                if (testCase.isBrotherNodeGetFocus) {
                    focusHubD->focusable_ = true;
                }
                //  set focusstep
                if (testCase.inputValue == "上键走焦") {
                    // run focus
                    focusHubD->RequestNextFocus(FocusStep::UP);
                } else if (testCase.inputValue == "下键走焦") {
                    focusHubD->RequestNextFocus(FocusStep::DOWN);
                } else if (testCase.inputValue == "左键走焦") {
                    focusHubD->RequestNextFocus(FocusStep::LEFT);
                } else if (testCase.inputValue == "右键走焦") {
                    focusHubD->RequestNextFocus(FocusStep::RIGHT);
                }
                if (testCase.expectResults == "A") {
                    EXPECT_EQ(focusHubA->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual A STATUS: " << focusHubA->IsCurrentFocus();
                } else if (testCase.expectResults == "B") {
                    EXPECT_EQ(focusHubB->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual B STATUS: " << focusHubB->IsCurrentFocus();
                } else if (testCase.expectResults == "C") {
                    EXPECT_EQ(focusHubC->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual C STATUS: " << focusHubC->IsCurrentFocus();
                } else if (testCase.expectResults == "D") {
                    EXPECT_EQ(focusHubD->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual D STATSU: " << focusHubD->IsCurrentFocus();
                } else if (testCase.expectResults == "E") {
                    EXPECT_EQ(focusHubE->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual E STATSU: " << focusHubE->IsCurrentFocus();
                } else if (testCase.expectResults == "F") {
                    EXPECT_EQ(focusHubF->IsCurrentFocus(), true)
                        << "TestCaseNum: " << caseNum << ", actual F STATSU: " << focusHubF->IsCurrentFocus();
                }
            }
        }
        // NEXT ONE
        ++caseNum;
    }
}

HWTEST_F(LinearFocusingTestNG, LinearFocusingTestNG003, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : LINEAR_FOCUSING_HOME_CASES) {
        // creat root node
        auto rootNode = CreateRootNode();
        EXPECT_NE(rootNode, nullptr);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);
        rootNode->UpdateInspectorId("ROOTNODE");

        /**
         * @tc.steps: step2. Create FocusView nodeB.
         * @tc.expected: nodeB and focusHubB not null.
         */
        if (testCase.isparentNodeHandleLeftRightFocus) {
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

            // set activity status
            if (testCase.isGoFocusActivityStatus) {
                focusHubC->isFocusActiveWhenFocused_ = true;
            }
            // set start node
            if (!testCase.goFocusStartPoint.empty()) {
                focusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubC));
            }

            //  set focusstep
            if (testCase.inputValue == "HOME键走焦") {
                focusHubC->RequestNextFocus(FocusStep::LEFT_END) || focusHubC->RequestNextFocus(FocusStep::UP_END);
            } else if (testCase.inputValue == "END键走焦") {
                focusHubC->RequestNextFocus(FocusStep::RIGHT_END) || focusHubC->RequestNextFocus(FocusStep::DOWN_END);
            }

            // auto lastFocusNode = focusManager_->GetCurrentFocus();
            auto lastFocusNode = focusHubC->GetLastWeakFocusNode().Upgrade();
            std::string actualNode = lastFocusNode ? lastFocusNode->GetFrameNode()->GetInspectorId().value_or("") : "";

            // expect result
            EXPECT_EQ(actualNode, testCase.expectResults)
                << "TestCaseNum: " << caseNum << ", actual node: " << actualNode
                << ", expect node: " << testCase.expectResults;
        } else {
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
            // set activity status
            if (testCase.isGoFocusActivityStatus) {
                focusHubC->isFocusActiveWhenFocused_ = true;
            }
            // set start node
            if (!testCase.goFocusStartPoint.empty()) {
                focusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubC));
                // focusHubC->SetCurrentFocus(true);
            }

            //  set focusstep
            if (testCase.inputValue == "HOME键走焦") {
                focusHubC->RequestNextFocus(FocusStep::LEFT_END) || focusHubC->RequestNextFocus(FocusStep::UP_END);
            } else if (testCase.inputValue == "END键走焦") {
                focusHubC->RequestNextFocus(FocusStep::RIGHT_END) || focusHubC->RequestNextFocus(FocusStep::DOWN_END);
            }
            auto lastFocusNode = focusHubC->GetLastWeakFocusNode().Upgrade();
            std::string actualNode = lastFocusNode ? lastFocusNode->GetFrameNode()->GetInspectorId().value_or("") : "";
            EXPECT_EQ(actualNode, testCase.expectResults)
                << "TestCaseNum: " << caseNum << ", actual node: " << actualNode
                << ", expect node: " << testCase.expectResults;
        }
        ++caseNum;
    }
}

} // namespace OHOS::Ace::NG

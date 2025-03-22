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
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/event/focus_core/passive_last_focus_test.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/manager/focus/focus_manager.h"
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
struct FocusPassiveNode {
    RefPtr<FrameNode> nodeA;
    RefPtr<FrameNode> nodeB;
    RefPtr<FrameNode> nodeC;
    RefPtr<FrameNode> nodeD;
    RefPtr<FrameNode> nodeE;
    RefPtr<FrameNode> nodeF;
    RefPtr<FrameNode> nodeG;
    RefPtr<FocusHub> focusHubA;
    RefPtr<FocusHub> focusHubB;
    RefPtr<FocusHub> focusHubC;
    RefPtr<FocusHub> focusHubD;
    RefPtr<FocusHub> focusHubE;
    RefPtr<FocusHub> focusHubF;
    RefPtr<FocusHub> focusHubG;
};
FocusPassiveNode g_focusNode;
FocusPassiveNode g_focusHub;
struct FocusPassiveTestCase {
    bool isTabFocusNode;
    bool isShiftTabFocusNode;
    FocusPassiveCase focusCurrentNodeId;
    std::vector<bool> expectResults;
    FocusPassiveTestCase(bool isTabFocusNode, bool isShiftTabFocusNode, FocusPassiveCase focusCurrentNodeId,
        const std::vector<bool>& expectResults)
        : isTabFocusNode(isTabFocusNode), isShiftTabFocusNode(isShiftTabFocusNode),
          focusCurrentNodeId(focusCurrentNodeId), expectResults(expectResults)
    {}
};

const std::vector<FocusPassiveTestCase> FOCUS_Passive_CASES = {
    // case1
    FocusPassiveTestCase(true, false, FocusPassiveCase::DFOCUSNODEID, { true, true }),
    // case2
    FocusPassiveTestCase(false, true, FocusPassiveCase::GFOCUSNODEID, { true, true }),
    // case3
    FocusPassiveTestCase(false, false, FocusPassiveCase::DFOCUSNODEID, { true, true }),
    // case4
    FocusPassiveTestCase(false, false, FocusPassiveCase::BFOCUSNODEID, { true, true }),
    // case5
    FocusPassiveTestCase(false, false, FocusPassiveCase::CFOCUSNODEID, { true, true }),
};

void FocusPassiveTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusPassiveTestNG SetUpTestCase";
}

void FocusPassiveTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusPassiveTestNG TearDownTestCase";
}
void FocusPassiveTestNG::SetFocusNode(RefPtr<FrameNode>& node, RefPtr<FocusHub>& focusHub)
{
    node = CreateNodeWithFocusPattern("node", FocusType::NODE, true);
    EXPECT_NE(node, nullptr);
    node->UpdateInspectorId("NODE");
    focusHub = node->GetOrCreateFocusHub();
    EXPECT_NE(focusHub, nullptr);
}
void FocusPassiveTestNG::SetFocusAbleNode(const RefPtr<FocusHub>& focusHub1, const RefPtr<FocusHub>& focusHub2)
{
    focusHub1->SetFocusable(true);
    focusHub2->SetFocusable(true);
}
void FocusPassiveTestNG::SetFocusRemoveSelf(const RefPtr<FocusHub>& focusHub1, const RefPtr<FocusHub>& focusHub2,
    const RefPtr<FocusHub>& focusHub, RefPtr<FrameNode>& node)
{
    const auto& focusManager = focusManager_->GetFocusManager(node);
    focusManager->SetLastFocusStateNode(focusHub);
    focusHub1->RemoveSelf();
    auto nextFocushub = focusManager->GetLastFocusStateNode();
    EXPECT_EQ(nextFocushub->currentFocus_, focusHub2->currentFocus_);
}
void FocusPassiveTestNG::InitFocusPassive()
{
    for (const auto& testCase : FOCUS_Passive_CASES) {
        SetFocusNode(g_focusNode.nodeA, g_focusHub.focusHubA);
        SetFocusNode(g_focusNode.nodeB, g_focusHub.focusHubB);
        SetFocusNode(g_focusNode.nodeC, g_focusHub.focusHubC);
        SetFocusNode(g_focusNode.nodeD, g_focusHub.focusHubD);
        SetFocusNode(g_focusNode.nodeE, g_focusHub.focusHubE);
        SetFocusNode(g_focusNode.nodeF, g_focusHub.focusHubF);
        SetFocusNode(g_focusNode.nodeG, g_focusHub.focusHubG);

        g_focusNode.nodeA->AddChild(g_focusNode.nodeB);
        g_focusNode.nodeA->AddChild(g_focusNode.nodeC);
        g_focusNode.nodeB->AddChild(g_focusNode.nodeD);
        g_focusNode.nodeB->AddChild(g_focusNode.nodeE);
        g_focusNode.nodeC->AddChild(g_focusNode.nodeF);
        g_focusNode.nodeC->AddChild(g_focusNode.nodeG);

        if (testCase.isTabFocusNode) {
            SetFocusAbleNode(g_focusHub.focusHubE, g_focusHub.focusHubG);
        }

        if (testCase.isShiftTabFocusNode) {
            SetFocusAbleNode(g_focusHub.focusHubF, g_focusHub.focusHubD);
        }

        if (!testCase.isTabFocusNode && !testCase.isShiftTabFocusNode &&
            testCase.focusCurrentNodeId == FocusPassiveCase::DFOCUSNODEID) {
            SetFocusAbleNode(g_focusHub.focusHubC, g_focusHub.focusHubE);
        }
        switch (testCase.focusCurrentNodeId) {
            case FocusPassiveCase::BFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubB, g_focusHub.focusHubC, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            case FocusPassiveCase::CFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubC, g_focusHub.focusHubB, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            case FocusPassiveCase::DFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubD, g_focusHub.focusHubE, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            case FocusPassiveCase::EFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubE, g_focusHub.focusHubD, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            case FocusPassiveCase::FFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubF, g_focusHub.focusHubG, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            case FocusPassiveCase::GFOCUSNODEID:
                SetFocusRemoveSelf(g_focusHub.focusHubG, g_focusHub.focusHubF, g_focusHub.focusHubA, g_focusNode.nodeA);
                break;
            default:
                break;
        }
    }
}

HWTEST_F(FocusPassiveTestNG, FocusPassiveTest001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    InitFocusPassive();
}
} // namespace OHOS::Ace::NG
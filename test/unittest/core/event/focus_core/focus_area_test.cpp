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
#include "test/unittest/core/event/focus_core/focus_area_test.h"
#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_box.h"
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
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
int32_t childSize = 4;
const std::vector<FocusAreaTestCase> FOCUS_AREA_CASES = {
    // case1
    FocusAreaTestCase(true, false, FocusStep::TAB,
        FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 120.0f, 180.0f, 130.0f }),
    // case2
    FocusAreaTestCase(
        true, true, FocusStep::TAB, FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 80.0f, 180.0f, 130.0f }),
    // case3
    FocusAreaTestCase(
        true, true, FocusStep::TAB, FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 80.0f, 200.0f, 60.0f }),
    // case4
    FocusAreaTestCase(
        true, false, FocusStep::UP, FocusAreaNodeOffset { 110.0f, 160.0f, 230.0f, 0.0f, 0.0f, 0.0f, 230.0f, 80.0f }),
    // case5
    FocusAreaTestCase(
        true, true, FocusStep::UP, FocusAreaNodeOffset { 110.0f, 160.0f, 230.0f, 0.0f, 0.0f, 0.0f, 180.0f, 80.0f }),
    // case6
    FocusAreaTestCase(
        true, true, FocusStep::UP, FocusAreaNodeOffset { 110.0f, 160.0f, 190.0f, 40.0f, 0.0f, 0.0f, 160.0f, 60.0f }),
    // case7
    FocusAreaTestCase(
        true, false, FocusStep::DOWN, FocusAreaNodeOffset { 110.0f, 160.0f, 230.0f, 0.0f, 0.0f, 0.0f, 230.0f, 80.0f }),
    // case8
    FocusAreaTestCase(
        true, true, FocusStep::DOWN, FocusAreaNodeOffset { 110.0f, 160.0f, 230.0f, 0.0f, 0.0f, 0.0f, 180.0f, 80.0f }),
    // case9
    FocusAreaTestCase(
        true, true, FocusStep::DOWN, FocusAreaNodeOffset { 110.0f, 160.0f, 160.0f, 60.0f, 0.0f, 0.0f, 190.0f, 40.0f }),
    // case10
    FocusAreaTestCase(
        true, false, FocusStep::LEFT, FocusAreaNodeOffset { 210.0f, 60.0f, 0.0f, 180.0f, 0.0f, 0.0f, 110.0f, 0.0f }),
    // case11
    FocusAreaTestCase(
        true, true, FocusStep::LEFT, FocusAreaNodeOffset { 210.0f, 60.0f, 0.0f, 180.0f, 0.0f, 0.0f, 110.0f, 40.0f }),
    // case12
    FocusAreaTestCase(
        true, true, FocusStep::LEFT, FocusAreaNodeOffset { 210.0f, 60.0f, 0.0f, 180.0f, 0.0f, 30.0f, 110.0f, 40.0f }),
    // case13
    FocusAreaTestCase(true, false, FocusStep::RIGHT,
        FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 120.0f, 180.0f, 130.0f }),
    // case14
    FocusAreaTestCase(true, true, FocusStep::RIGHT,
        FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 80.0f, 180.0f, 130.0f }),
    // case15
    FocusAreaTestCase(
        true, true, FocusStep::RIGHT, FocusAreaNodeOffset { 10.0f, 60.0f, 120.0f, 0.0f, 120.0f, 80.0f, 200.0f, 60.0f }),
};

void FocusAreaTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusAreaTestNG SetUpTestCase";
}

void FocusAreaTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusAreaTestNG TearDownTestCase";
}
RefPtr<FrameNode> FocusAreaTestNG::CreatNode(float nodex, float nodey)
{
    auto node = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    node->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    node->geometryNode_->SetFrameOffset(OffsetF(nodex, nodey));
    EXPECT_NE(node, nullptr);
    return node;
}
RefPtr<FrameNode> FocusAreaTestNG::CreatRootNode()
{
    auto rootNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    return rootNode;
}
void FocusAreaTestNG::InitFocusareaTest()
{
    for (const auto& testCase : FOCUS_AREA_CASES) {
        auto rootNode = CreatRootNode();
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        rootNodeFocusHub->focusAlgorithm_.scopeType = ScopeType::PROJECT_AREA;
        auto nodeA = FocusAreaTestNG::CreatNode(testCase.nodeOffset.nodeAx, testCase.nodeOffset.nodeAy);
        auto nodeB = FocusAreaTestNG::CreatNode(testCase.nodeOffset.nodeBx, testCase.nodeOffset.nodeBy);
        auto nodeC = FocusAreaTestNG::CreatNode(testCase.nodeOffset.nodeCx, testCase.nodeOffset.nodeCy);
        auto nodeD = FocusAreaTestNG::CreatNode(testCase.nodeOffset.nodeDx, testCase.nodeOffset.nodeDy);

        auto focusHubA = nodeA->GetOrCreateFocusHub();
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        auto focusHubC = nodeC->GetOrCreateFocusHub();
        auto focusHubD = nodeD->GetOrCreateFocusHub();
        rootNode->AddChild(nodeA);
        rootNode->AddChild(nodeB);
        rootNode->AddChild(nodeC);
        rootNode->AddChild(nodeD);
        std::list<RefPtr<FocusHub>> children;
        rootNodeFocusHub->FlushChildrenFocusHub(children);
        EXPECT_EQ(children.size(), childSize);
        if (!testCase.isFocusBrotherNode) {
            auto nextnode = focusHubA->GetNearestNodeByProjectArea(children, testCase.StepMethod);
            CHECK_NULL_VOID(nextnode);
            nextnode->TryRequestFocus(nextnode, RectF(), testCase.StepMethod);
            EXPECT_TRUE(focusHubA->IsCurrentFocus());
        }
        if ((testCase.isFocusBrotherNode && testCase.StepMethod == FocusStep::TAB) ||
            (testCase.isFocusBrotherNode && testCase.StepMethod == FocusStep::RIGHT)) {
            auto nextnode = focusHubA->GetNearestNodeByProjectArea(children, testCase.StepMethod);
            CHECK_NULL_VOID(nextnode);
            nextnode->TryRequestFocus(nextnode, RectF(), testCase.StepMethod);
            EXPECT_TRUE(focusHubC->IsCurrentFocus());
        }
        if ((testCase.isFocusBrotherNode && testCase.StepMethod == FocusStep::UP) ||
            (testCase.isFocusBrotherNode && testCase.StepMethod == FocusStep::LEFT)) {
            auto nextnode = focusHubA->GetNearestNodeByProjectArea(children, testCase.StepMethod);
            CHECK_NULL_VOID(nextnode);
            nextnode->TryRequestFocus(nextnode, RectF(), testCase.StepMethod);
            EXPECT_TRUE(focusHubD->IsCurrentFocus());
        }
        if (testCase.isFocusBrotherNode && testCase.StepMethod == FocusStep::DOWN) {
            auto nextnode = focusHubA->GetNearestNodeByProjectArea(children, testCase.StepMethod);
            CHECK_NULL_VOID(nextnode);
            nextnode->TryRequestFocus(nextnode, RectF(), testCase.StepMethod);
            EXPECT_TRUE(focusHubB->IsCurrentFocus());
        }
    }
}
HWTEST_F(FocusAreaTestNG, FocusAreaTest001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    InitFocusareaTest();
}
} // namespace OHOS::Ace::NG
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
#include "test/unittest/core/event/focus_core/focus_creatbox_test.h"
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
NG::FocusBoxStyle styleType;

const std::vector<FocusCreatBoxTestCase> FOCUS_Creat_Box_CASES = {
    // case1
    FocusCreatBoxTestCase(FocusBoxPolyMorPhismStyle { true, true, true },
        FocusBoxStyleType { FocusStyleType::NONE, FocusStyleType::NONE, FocusStyleType::NONE },
        FocusBoxDependence { true, true }),
    // case2
    FocusCreatBoxTestCase(FocusBoxPolyMorPhismStyle { true, true, true },
        FocusBoxStyleType { FocusStyleType::NONE, FocusStyleType::NONE, FocusStyleType::NONE },
        FocusBoxDependence { true, false }),
    // case3
    FocusCreatBoxTestCase(FocusBoxPolyMorPhismStyle { true, true, true },
        FocusBoxStyleType { FocusStyleType::NONE, FocusStyleType::NONE, FocusStyleType::NONE },
        FocusBoxDependence { false, true }),
    // case4
    FocusCreatBoxTestCase(FocusBoxPolyMorPhismStyle { true, true, true },
        FocusBoxStyleType { FocusStyleType::NONE, FocusStyleType::NONE, FocusStyleType::NONE },
        FocusBoxDependence { false, false }),
};

void FocusCreatBoxTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusCreatBoxTestNG SetUpTestCase";
}

void FocusCreatBoxTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusCreatBoxTestNG TearDownTestCase";
}
RefPtr<FrameNode> FocusCreatBoxTestNG::CreatNode()
{
    auto node = CreateNodeWithFocusPattern("node", FocusType::NODE, true);
    EXPECT_NE(node, nullptr);
    node->UpdateInspectorId("NODE");
    return node;
}
void FocusCreatBoxTestNG::FocusPolyMorPhismStyle(bool testCase, const RefPtr<FocusHub>& focusHub)
{
    styleType.strokeColor = Color::RED;
    if (testCase) {
        focusHub->GetFocusBox().SetStyle(styleType);
        auto style = focusHub->GetFocusBox().GetStyle().value();
        EXPECT_EQ(style.strokeColor, Color::RED);
    }
}
void FocusCreatBoxTestNG::SetDependence(bool testCase, const RefPtr<FocusHub>& focusHub)
{
    if (testCase) {
        focusHub->SetFocusDependence(FocusDependence::SELF);
    } else {
        focusHub->SetFocusDependence(FocusDependence::AUTO);
    }
}
void FocusCreatBoxTestNG::InitFocusCreatBox()
{
    for (const auto& testCase : FOCUS_Creat_Box_CASES) {
        auto rootNode = CreateRootNode();
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);

        auto nodeA = CreatNode();
        auto focusHubA = nodeA->GetOrCreateFocusHub();
        focusHubA->SetFocusStyleType(testCase.focusStyleType.focusAStyleType);

        auto nodeB = CreatNode();
        auto focusHubB = nodeB->GetOrCreateFocusHub();
        focusHubB->SetFocusStyleType(testCase.focusStyleType.focusBStyleType);

        auto nodeC = CreatNode();
        auto focusHubC = nodeC->GetOrCreateFocusHub();
        focusHubC->SetFocusStyleType(testCase.focusStyleType.focusCStyleType);

        FocusPolyMorPhismStyle(testCase.style.isAFocusBoxStyle, focusHubA);
        FocusPolyMorPhismStyle(testCase.style.isBFocusBoxStyle, focusHubB);
        FocusPolyMorPhismStyle(testCase.style.isCFocusBoxStyle, focusHubC);

        rootNode->AddChild(nodeA);
        nodeA->AddChild(nodeB);
        nodeB->AddChild(nodeC);

        SetDependence(testCase.isDependence.isADependence, focusHubA);
        SetDependence(testCase.isDependence.isBDependence, focusHubB);

        focusHubA->RequestFocusImmediately();
        focusHubB->RequestFocusImmediately();
        focusHubC->RequestFocusImmediately();
        if ((testCase.isDependence.isADependence && testCase.isDependence.isBDependence) ||
            (testCase.isDependence.isADependence && !testCase.isDependence.isBDependence)) {
            rootNodeFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubA));
            auto res = rootNodeFocusHub->PaintAllFocusState();
            EXPECT_TRUE(res);
            EXPECT_EQ(focusManager_->GetLastFocusStateNode(), focusHubA);
        }
        if (!testCase.isDependence.isADependence && testCase.isDependence.isBDependence) {
            rootNodeFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubA));
            focusHubA->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubB));
            auto res = rootNodeFocusHub->PaintAllFocusState();
            EXPECT_TRUE(res);
            ASSERT_EQ(focusManager_->GetLastFocusStateNode(), focusHubB);
        }
        if (!testCase.isDependence.isADependence && !testCase.isDependence.isBDependence) {
            rootNodeFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubA));
            focusHubA->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubB));
            focusHubB->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHubC));
            auto res = rootNodeFocusHub->PaintAllFocusState();
            EXPECT_TRUE(res);
            EXPECT_EQ(focusManager_->GetLastFocusStateNode(), focusHubC);
        }
    }
}

HWTEST_F(FocusCreatBoxTestNG, FocusCreatBoxTestNG001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    InitFocusCreatBox();
}
} // namespace OHOS::Ace::NG

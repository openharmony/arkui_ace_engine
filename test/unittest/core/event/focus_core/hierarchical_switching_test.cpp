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
#include "hierarchical_switching_test.h"
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/event/focus_core/hierarchical_switching_test.h"
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

struct FocusHierarchicalPageTestCase {
    bool isDefaultFocus;
    bool isDefaultFocusAble;
    bool isCFirstFocus;
    bool isCAlreadyFocus;
    FocusHierarchicalCase nodeId;
    bool isDependenceC;
    bool isDesiredNodes;
    FocusHierarchicalPageTestCase(bool isDefaultFocus, bool isDefaultFocusAble, bool isCFirstFocus,
        bool isCAlreadyFocus, FocusHierarchicalCase nodeId, bool isDependenceC, bool isDesiredNodes)
        : isDefaultFocus(isDefaultFocus), isDefaultFocusAble(isDefaultFocusAble), isCFirstFocus(isCFirstFocus),
          isCAlreadyFocus(isCAlreadyFocus), nodeId(nodeId), isDependenceC(isDependenceC), isDesiredNodes(isDesiredNodes)
    {}
};

const std::vector<FocusHierarchicalPageTestCase> FOCUS_HIERARCHICAL_PAGE_CASES = {
    // case1
    FocusHierarchicalPageTestCase(true, true, true, false, FocusHierarchicalCase::NONE, true, false),
    // case2
    FocusHierarchicalPageTestCase(true, true, true, false, FocusHierarchicalCase::NONE, false, false),
    // case3
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEC, true, false),
    // case4
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEC, false, false),
    // case5
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEE, true, false),
    // case6
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEE, false, false),

};

void FocusHierarchicalPageTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusHierarchicalPageTestNG SetUpTestCase";
}

void FocusHierarchicalPageTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusHierarchicalPageTestNG TearDownTestCase";
}
void SetDefaultFocus(
    bool isDefaultFocus, bool isDefaultFocusAble, const RefPtr<FocusHub>& focusHub1, const RefPtr<FocusHub>& focusHub2)
{
    if (isDefaultFocus) {
        focusHub1->SetDefaultFocusNode(focusHub2);
        if (isDefaultFocusAble) {
            focusHub2->SetFocusable(true);
        }
    }
}
void IsCAlreadyFocus(bool isCAlreadyFocus, const RefPtr<FocusHub>& focusHub)
{
    if (isCAlreadyFocus) {
        focusHub->SetCurrentFocus(true);
        EXPECT_TRUE(focusHub->IsCurrentFocus());
    }
}
void IsDependence(bool isDependence, const RefPtr<FocusHub>& focusHub)
{
    if (isDependence) {
        focusHub->SetFocusDependence(FocusDependence::SELF);
    }
    focusHub->SetFocusDependence(FocusDependence::AUTO);
}

void VerifyFocus(const RefPtr<FocusHub>& focusHub1, const RefPtr<FocusHub>& focusHub3, bool isDependence,
    const RefPtr<FrameNode>& node)
{
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto focusView = node->GetPattern<FocusView>();
    focusManager->FocusViewShow(focusView);
    focusView->RequestDefaultFocus();
    if (isDependence) {
        EXPECT_TRUE(focusHub1->IsCurrentFocus());
    }
    EXPECT_TRUE(focusHub3->IsCurrentFocus());
}

HWTEST_F(FocusHierarchicalPageTestNG, FocusHierarchicalPageTestNG001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : FOCUS_HIERARCHICAL_PAGE_CASES) {
        auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
        auto rootFocusHub = rootNode->GetOrCreateFocusHub();

        auto pagePatternC = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
        auto pageNodeC = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePatternC);
        auto pageFocusHubC = pageNodeC->GetOrCreateFocusHub();

        auto columnPatternC = AceType::MakeRefPtr<LinearLayoutPattern>(true);
        auto columnNodeC = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPatternC);
        auto columnFocusHubC = columnNodeC->GetOrCreateFocusHub();

        auto buttonPatternE = AceType::MakeRefPtr<ButtonPattern>();
        auto buttonNodeE = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPatternE);
        auto buttonFocusHubE = buttonNodeE->GetOrCreateFocusHub();

        rootNode->AddChild(pageNodeC);
        pageNodeC->AddChild(columnNodeC);
        pageNodeC->AddChild(buttonNodeE);
        SetDefaultFocus(testCase.isDefaultFocus, testCase.isDefaultFocusAble, columnFocusHubC, buttonFocusHubE);
        IsCAlreadyFocus(testCase.isCAlreadyFocus, pageFocusHubC);
        IsDependence(testCase.isDependenceC, pageFocusHubC);
        if (testCase.isDefaultFocusAble) {
            if (!testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NODEE) {
                pageFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHubC));
                columnFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHubE));
                VerifyFocus(pageFocusHubC, buttonFocusHubE, testCase.isDependenceC, pageNodeC);
            }
            if (!testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NODEC) {
                pageFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHubC));
                VerifyFocus(pageFocusHubC, buttonFocusHubE, testCase.isDependenceC, pageNodeC);
            }
            if (!testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NONE) {
                VerifyFocus(pageFocusHubC, buttonFocusHubE, testCase.isDependenceC, pageNodeC);
            }
        }
        pageFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHubC));
        columnFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHubE));
        auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
        auto focusView = pageNodeC->GetPattern<FocusView>();
        focusManager->FocusViewShow(focusView);
        focusView->RequestDefaultFocus();
        EXPECT_TRUE(pageFocusHubC->IsCurrentFocus());
    }
}

} // namespace OHOS::Ace::NG
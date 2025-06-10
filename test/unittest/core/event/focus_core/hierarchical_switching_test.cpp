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
#include "test/unittest/core/event/focus_core/hierarchical_switching_test.h"
#include "test/unittest/core/pattern/test_ng.h"

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
    FocusHierarchicalPageTestCase(bool isDefaultFocus, bool isDefaultFocusAble, bool isCFirstFocus,
        bool isCAlreadyFocus, FocusHierarchicalCase nodeId, bool isDependenceC)
        : isDefaultFocus(isDefaultFocus), isDefaultFocusAble(isDefaultFocusAble), isCFirstFocus(isCFirstFocus),
          isCAlreadyFocus(isCAlreadyFocus), nodeId(nodeId), isDependenceC(isDependenceC)
    {}
};

const std::vector<FocusHierarchicalPageTestCase> FOCUS_HIERARCHICAL_PAGE_CASES = {
    // case1
    FocusHierarchicalPageTestCase(true, true, true, false, FocusHierarchicalCase::NONE, true),
    // case2
    FocusHierarchicalPageTestCase(true, true, true, false, FocusHierarchicalCase::NONE, false),
    // case3
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEC, true),
    // case4
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEC, false),
    // case5
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEE, true),
    // case6
    FocusHierarchicalPageTestCase(true, true, false, true, FocusHierarchicalCase::NODEE, false),

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
void SetDefaultFocus(bool isDefaultFocus, bool isDefaultFocusAble, RefPtr<FocusHub>& focusHub)
{
    if (isDefaultFocus && isDefaultFocusAble) {
        focusHub->SetIsDefaultFocus(true);
        EXPECT_TRUE(focusHub->IsDefaultFocus());
    }
}
void IsCAlreadyFocus(bool isCAlreadyFocus, const RefPtr<FocusHub>& focusHub)
{
    if (!isCAlreadyFocus) {
        focusHub->SetCurrentFocus(true);
        EXPECT_TRUE(focusHub->IsCurrentFocus());
    }
}
void IsCFirstFocus(bool isCFirstFocus, const RefPtr<FocusHub>& focusHub)
{
    if (isCFirstFocus) {
        focusHub->SetCurrentFocus(true);
        EXPECT_TRUE(focusHub->IsCurrentFocus());
    }
}
void IsDependence(bool isDependence, const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetFocusDependence(isDependence ? FocusDependence::SELF : FocusDependence::AUTO);
}

/**
 * @tc.name: JudgMentDefaultFocus
 * @tc.desc: judg Dependence RequestDefaultFocus.
 * @tc.type: FUNC
 */
void JudgMentDefaultFocus(
    bool isDependenceC, RefPtr<FocusHub>& focusHub1, RefPtr<FocusHub>& focusHub2, RefPtr<FocusView>& focusView)
{
    if (isDependenceC) {
        focusView->RequestDefaultFocus();
        EXPECT_TRUE(focusHub1->IsCurrentFocus());
    }
    focusView->RequestDefaultFocus();
    EXPECT_TRUE(focusHub2->IsCurrentFocus());
}
HWTEST_F(FocusHierarchicalPageTestNG, FocusHierarchicalPageTestNG001, TestSize.Level1)
{
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : FOCUS_HIERARCHICAL_PAGE_CASES) {
        /**
         * @tc.steps: step2. Create scope root and focusHub.
         * @tc.expected: root and focusHub not null.
         */
        auto rootNode = CreateRootNode();
        EXPECT_NE(rootNode, nullptr);
        auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
        EXPECT_NE(rootNodeFocusHub, nullptr);

        /**
         * @tc.steps: step2. Create scope page and focusHub and focusview.
         * @tc.expected: page and focusHub and focusview not null.
         */
        std::list<int32_t> emptyList;
        auto pageNodeC = CreateFocusViewWithFocusPattern("pageNodeC", emptyList, FocusType::SCOPE, true);
        EXPECT_NE(pageNodeC, nullptr);
        pageNodeC->UpdateInspectorId("PAGENODEC");
        auto pageFocusHubC = pageNodeC->GetOrCreateFocusHub();
        EXPECT_NE(pageFocusHubC, nullptr);
        auto focusView = pageNodeC->GetPattern<FocusView>();
        EXPECT_NE(focusView, nullptr);

        /**
         * @tc.steps: step2. Create scope columnnode and focusHub.
         * @tc.expected: columnnode and focusHub not null.
         */
        auto columnPatternC = AceType::MakeRefPtr<LinearLayoutPattern>(true);
        EXPECT_NE(columnPatternC, nullptr);
        auto columnNodeC = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPatternC);
        EXPECT_NE(columnNodeC, nullptr);
        auto columnFocusHubC = columnNodeC->GetOrCreateFocusHub();
        EXPECT_NE(columnFocusHubC, nullptr);

        /**
         * @tc.steps: step2. Create scope buttonnode and focusHub.
         * @tc.expected: buttonnode and focusHub not null.
         */
        auto buttonNodeE = CreateNodeWithFocusPattern("buttonNodeE", FocusType::NODE, true);
        EXPECT_NE(buttonNodeE, nullptr);
        buttonNodeE->UpdateInspectorId("BUTTONNODEE");
        auto buttonFocusHubE = buttonNodeE->GetOrCreateFocusHub();
        EXPECT_NE(buttonFocusHubE, nullptr);

        rootNode->AddChild(pageNodeC);
        pageNodeC->AddChild(columnNodeC);
        columnNodeC->AddChild(buttonNodeE);

        /**
         * @tc.steps: step2. set isdefaultfocus.
         */
        SetDefaultFocus(testCase.isDefaultFocus, testCase.isDefaultFocusAble, buttonFocusHubE);
        /**
         * @tc.steps: step2. judge pagenode is firstfocus.
         */
        IsCFirstFocus(testCase.isCFirstFocus, pageFocusHubC);
        /**
         * @tc.steps: step2. judge pagenode is alreadyfocus.
         */
        IsCAlreadyFocus(testCase.isCAlreadyFocus, pageFocusHubC);
        /**
         * @tc.steps: step2. set pagenode dependence.
         */
        IsDependence(testCase.isDependenceC, pageFocusHubC);
        /**
         * @tc.steps: step2. create pipeline and focusManager.
         * @tc.expected: pipeline and focusManager not null.
         */
        auto pipeline = pageNodeC->GetContextRefPtr();
        EXPECT_NE(pipeline, nullptr);
        auto focusManager = pipeline->GetFocusManager();
        EXPECT_NE(focusManager, nullptr);
        /**
         * @tc.steps: step2. show focusview.
         */
        focusManager->FocusViewShow(focusView);
        if (testCase.isDefaultFocusAble) {
            if (!testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NODEE) {
                pageFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHubC));
                columnFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHubE));
                JudgMentDefaultFocus(testCase.isDependenceC, pageFocusHubC, buttonFocusHubE, focusView);
            }
            if (!testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NODEC) {
                pageFocusHubC->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHubC));
                JudgMentDefaultFocus(testCase.isDependenceC, pageFocusHubC, buttonFocusHubE, focusView);
            }
            if (testCase.isCFirstFocus && testCase.nodeId == FocusHierarchicalCase::NONE) {
                JudgMentDefaultFocus(testCase.isDependenceC, pageFocusHubC, buttonFocusHubE, focusView);
            }
        }
        focusManager->FocusViewShow(focusView);
        focusView->RequestDefaultFocus();
        EXPECT_TRUE(pageFocusHubC->IsCurrentFocus());
    }
}
HWTEST_F(FocusHierarchicalPageTestNG, FocusSwiperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create scope swiperNode and focusHub.
     * @tc.expected: swiperNode and focusHub not null.
     */
    auto swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    auto swiperNode = FrameNodeOnTree::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    EXPECT_NE(swiperNode, nullptr);
    auto swiperFocusHub = swiperNode->GetOrCreateFocusHub();
    EXPECT_NE(swiperFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create scope navigationNode and focusHub.
     * @tc.expected: navigationNode and focusHub not null.
     */
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto navigationNode = FrameNodeOnTree::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, -1, navigationPattern);
    EXPECT_NE(navigationNode, nullptr);
    auto navigationFocusHub = navigationNode->GetOrCreateFocusHub();
    EXPECT_NE(navigationFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create scope menuNode and focusHub.
     * @tc.expected: menuNode and focusHub not null.
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::MENU);
    auto menuNode = FrameNodeOnTree::CreateFrameNode(V2::MENU_ETS_TAG, -1, menuPattern);
    EXPECT_NE(menuNode, nullptr);
    auto menuFocusHub = menuNode->GetOrCreateFocusHub();
    EXPECT_NE(menuFocusHub, nullptr);
    rootNode->AddChild(swiperNode);
    swiperNode->AddChild(navigationNode);
    navigationNode->AddChild(menuNode);

    /**
     * @tc.steps: step2. set Focus Chain.
     */
    swiperFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(navigationFocusHub));
    navigationFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(menuFocusHub));

    /**
     * @tc.steps: step2. create pipeline and focusManager.
     * @tc.expected: pipeline and focusManager not null.
     */
    auto pipeline = swiperNode->GetContextRefPtr();
    EXPECT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto focusView = menuNode->GetPattern<FocusView>();
    EXPECT_NE(focusView, nullptr);
    focusManager->FocusViewShow(focusView);
    swiperFocusHub->SetParentFocusable(false);
    EXPECT_FALSE(focusView->GetIsViewHasShow());
}
HWTEST_F(FocusHierarchicalPageTestNG, FocusViewWindowFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();
    ASSERT_NE(rootFocusHub, nullptr);
    rootFocusHub->SetFocusType(FocusType::SCOPE);
    rootNode->UpdateInspectorId("ROOTNODE");

    /**
     * @tc.steps: step2. Create page node and focusHub.
     * @tc.expected: pageNode and focusHub not null.
     */
    auto pageNode = CreateNodeWithFocusPattern("nodeC", FocusType::SCOPE, true);
    ASSERT_NE(pageNode, nullptr);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    ASSERT_NE(pageFocusHub, nullptr);
    pageNode->UpdateInspectorId("PAGENODE");

    /**
     * @tc.steps: step2. Create focusViewNode and focusView and focusHub.
     * @tc.expected: focusViewNode and focusView and focusHub not null.
     */
    std::list<int32_t> emptyList;
    auto focusViewNode = CreateFocusViewWithFocusPattern("focusViewNode", emptyList, FocusType::NODE, true);
    ASSERT_NE(focusViewNode, nullptr);
    focusViewNode->UpdateInspectorId("FOCUSVIEW");
    auto focusViewFocusHub = focusViewNode->GetOrCreateFocusHub();
    ASSERT_NE(focusViewFocusHub, nullptr);
    auto focusView = focusViewNode->GetPattern<FocusView>();
    ASSERT_NE(focusView, nullptr);

    rootNode->AddChild(pageNode);
    pageNode->AddChild(focusViewNode);

    /**
     * @tc.steps: step2. Create pipeline and focusManager.
     * @tc.expected: focusViewNode and focusView and focusHub not null.
     */
    auto pipeline = pageNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.expected: focusViewNode CurrentFocus
     */
    pageFocusHub->RequestFocusImmediately();
    focusManager->FocusViewShow(focusView);
    pipeline->WindowFocus(true);
    EXPECT_TRUE(focusViewFocusHub->IsCurrentFocus());
}
HWTEST_F(FocusHierarchicalPageTestNG, FocusLostFocusToViewRootTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create pageNode and focusview and focusHub.
     * @tc.expected: pageNode and focusview and focusHub not null.
     */
    std::list<int32_t> emptyList;
    auto pageNode = CreateFocusViewWithFocusPattern("pageNode", emptyList, FocusType::SCOPE, true);
    EXPECT_NE(pageNode, nullptr);
    pageNode->UpdateInspectorId("PAGENODE");
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    EXPECT_NE(pageFocusHub, nullptr);
    auto focusView = pageNode->GetPattern<FocusView>();
    EXPECT_NE(focusView, nullptr);

    /**
     * @tc.steps: step2. Create columnNode1  and focusHub.
     * @tc.expected: columnNode1 and focusHub not null.
     */
    auto columnNode1 = CreateNodeWithFocusPattern("buttonNode1", FocusType::NODE, true);
    EXPECT_NE(columnNode1, nullptr);
    columnNode1->UpdateInspectorId("BUTTONNODE1");
    auto columnFocusHub1 = columnNode1->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub1, nullptr);

    /**
     * @tc.steps: step2. Create buttonNode1 and focusHub.
     * @tc.expected: buttonNode1 and focusHub not null.
     */
    auto buttonNode1 = CreateNodeWithFocusPattern("buttonNode1", FocusType::NODE, true);
    EXPECT_NE(buttonNode1, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE1");
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub1, nullptr);

    /**
     * @tc.steps: step2. add node tree.
     */
    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode1);
    columnNode1->AddChild(buttonNode1);

    /**
     * @tc.steps: step2. add lastWeakFocusNode_.
     * @tc.expected: root and focusHub not null.
     */
    pageFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHub1));
    columnFocusHub1->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHub1));

    /**
     * @tc.steps: step2. Create pipeline and focusManager.
     * @tc.expected: root and focusHub not null.
     */
    auto pipeline = pageNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->lastFocusView_ = AceType::WeakClaim(AceType::RawPtr(focusView));

    /**
     * @tc.steps: step2. lostfocus and anewfoucs focus on root.
     * @tc.expected: root and focusHub not null.
     */
    focusManager->FocusViewShow(focusView);
    buttonFocusHub1->RequestFocusImmediately();
    buttonFocusHub1->LostFocusToViewRoot();
    focusManager->FocusViewHide(focusView);
    focusManager->FocusViewShow(focusView);
    pipeline->FlushFocusView();
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
}
HWTEST_F(FocusHierarchicalPageTestNG, FocusGetfocusleafTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create pageNode and focusHub and focusview.
     * @tc.expected: pageNode and focusHub and foucsview not null.
     */
    std::list<int32_t> emptyList;
    auto pageNode = CreateFocusViewWithFocusPattern("pageNode", emptyList, FocusType::SCOPE, true);
    EXPECT_NE(pageNode, nullptr);
    pageNode->UpdateInspectorId("PAGENODE");
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->SetFocusDependence(FocusDependence::AUTO);
    EXPECT_NE(pageFocusHub, nullptr);
    auto focusView = pageNode->GetPattern<FocusView>();
    EXPECT_NE(focusView, nullptr);

    /**
     * @tc.steps: step2. Create columnNode1 and focusHub.
     * @tc.expected: columnNode1 and focusHub not null.
     */
    auto columnNode1 = CreateNodeWithFocusPattern("columnNode1", FocusType::SCOPE, true);
    EXPECT_NE(columnNode1, nullptr);
    columnNode1->UpdateInspectorId("columnNode1");
    auto columnFocusHub1 = columnNode1->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub1, nullptr);
    columnFocusHub1->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create columnNode2 and focusHub.
     * @tc.expected: columnNode2 and focusHub not null.
     */
    auto columnNode2 = CreateNodeWithFocusPattern("columnNode2", FocusType::NODE, true);
    EXPECT_NE(columnNode2, nullptr);
    columnNode2->UpdateInspectorId("columnNode2");
    auto columnFocusHub2 = columnNode2->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub2, nullptr);
    columnFocusHub2->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create buttonNode1 and focusHub.
     * @tc.expected: buttonNode1 and focusHub not null.
     */
    auto buttonNode1 = CreateNodeWithFocusPattern("buttonNode1", FocusType::NODE, true);
    EXPECT_NE(buttonNode1, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE1");
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub1, nullptr);

    /**
     * @tc.steps: step2. Create buttonNode2 and focusHub.
     * @tc.expected: buttonNode2 and focusHub not null.
     */
    auto buttonNode2 = CreateNodeWithFocusPattern("buttonNode2", FocusType::NODE, true);
    EXPECT_NE(buttonNode2, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE2");
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub2, nullptr);

    /**
     * @tc.steps: step2. add node tree.
     * @tc.expected: buttonNode2 and focusHub not null.
     */
    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode1);
    columnNode1->AddChild(columnNode2);
    columnNode2->AddChild(buttonNode1);
    columnNode2->AddChild(buttonNode2);

    
    pageFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHub1));
    columnFocusHub1->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHub2));
    columnFocusHub2->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHub1));

    /**
     * @tc.steps: step2. Create pipeline and focusManager.
     * @tc.expected: root and focusHub not null.
     */
    auto pipeline = pageNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Follow the memory to find focus.
     * @tc.expected: focusHub EQ buttonFocusHub1.
     */
    focusManager->FocusViewShow(focusView);
    buttonFocusHub1->RequestFocusImmediately();
    buttonFocusHub1->LostFocusToViewRoot();
    focusManager->FocusViewHide(focusView);
    focusManager->FocusViewShow(focusView);
    auto focusHub = pageFocusHub->GetFocusLeaf();
    EXPECT_EQ(focusHub->GetFrameId(), buttonFocusHub1->GetFrameId());
}
HWTEST_F(FocusHierarchicalPageTestNG, TabFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create pageNode and focusview and focusHub.
     * @tc.expected: pageNode and focusview and focusHub not null.
     */
    std::list<int32_t> emptyList;
    auto pageNode = CreateFocusViewWithFocusPattern("pageNode", emptyList, FocusType::SCOPE, true);
    EXPECT_NE(pageNode, nullptr);
    pageNode->UpdateInspectorId("PAGENODE");
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->SetFocusDependence(FocusDependence::AUTO);
    EXPECT_NE(pageFocusHub, nullptr);
    auto focusView = pageNode->GetPattern<FocusView>();
    EXPECT_NE(focusView, nullptr);

    /**
     * @tc.steps: step2. Create columnNode1 and focusHub.
     * @tc.expected: columnNode1 and focusHub not null.
     */
    auto columnNode1 = CreateNodeWithFocusPattern("columnNode1", FocusType::SCOPE, true);
    EXPECT_NE(columnNode1, nullptr);
    columnNode1->UpdateInspectorId("columnNode1");
    auto columnFocusHub1 = columnNode1->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub1, nullptr);
    columnFocusHub1->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create columnNode2 and focusHub.
     * @tc.expected: columnNode2 and focusHub not null.
     */
    auto columnNode2 = CreateNodeWithFocusPattern("columnNode2", FocusType::NODE, true);
    EXPECT_NE(columnNode2, nullptr);
    columnNode2->UpdateInspectorId("columnNode2");
    auto columnFocusHub2 = columnNode2->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub2, nullptr);
    columnFocusHub2->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create buttonNode1 and focusHub.
     * @tc.expected: buttonNode1 and focusHub not null.
     */
    auto buttonNode1 = CreateNodeWithFocusPattern("buttonNode1", FocusType::NODE, true);
    EXPECT_NE(buttonNode1, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE1");
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub1, nullptr);

    /**
     * @tc.steps: step2. Create buttonNode2 and focusHub.
     * @tc.expected: buttonNode2 and focusHub not null.
     */
    auto buttonNode2 = CreateNodeWithFocusPattern("buttonNode2", FocusType::NODE, true);
    EXPECT_NE(buttonNode2, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE2");
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub2, nullptr);

    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode1);
    columnNode1->AddChild(columnNode2);
    columnNode2->AddChild(buttonNode1);
    columnNode2->AddChild(buttonNode2);

    pageFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHub1));
    columnFocusHub1->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(columnFocusHub2));
    columnFocusHub2->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHub2));

    /**
     * @tc.steps: step2. Create pipeline and focusManager.
     * @tc.expected: pipeline and focusManager not null.
     */
    auto pipeline = pageNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Out of focus and then regain focus as TAB buttonFocusHub2.
     * @tc.expected: Press tab foucs is buttonFocusHub2.
     */
    focusManager->FocusViewShow(focusView);
    buttonFocusHub2->RequestFocusImmediately();
    buttonFocusHub2->LostFocusToViewRoot();
    focusManager->FocusViewHide(focusView);
    focusManager->FocusViewShow(focusView);
    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    event.action = KeyAction::DOWN;
    event.pressedCodes = {KeyCode::KEY_TAB};
    focusManager->isFocusActive_ = true;
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = false;
    event.eventType = UIInputEventType::KEY;
    focusManager->keyProcessingMode_ = KeyProcessingMode::ANCESTOR_EVENT;
    auto res = pageFocusHub->HandleEvent(event);
    EXPECT_TRUE(res);
    EXPECT_TRUE(buttonFocusHub2->IsCurrentFocus());
}
HWTEST_F(FocusHierarchicalPageTestNG, TabOnFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Create scope root and focusHub.
     * @tc.expected: root and focusHub not null.
     */
    auto rootNode = CreateRootNode();
    EXPECT_NE(rootNode, nullptr);
    auto rootNodeFocusHub = rootNode->GetOrCreateFocusHub();
    EXPECT_NE(rootNodeFocusHub, nullptr);

    /**
     * @tc.steps: step2. Create pageNode and focusView and focusHub.
     * @tc.expected: pageNode and focusView and focusHub not null.
     */
    std::list<int32_t> emptyList;
    auto pageNode = CreateFocusViewWithFocusPattern("pageNode", emptyList, FocusType::SCOPE, true);
    EXPECT_NE(pageNode, nullptr);
    pageNode->UpdateInspectorId("PAGENODE");
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->SetFocusDependence(FocusDependence::AUTO);
    EXPECT_NE(pageFocusHub, nullptr);
    auto focusView = pageNode->GetPattern<FocusView>();
    EXPECT_NE(focusView, nullptr);

    /**
     * @tc.steps: step2. Create columnNode1 and focusHub.
     * @tc.expected: columnNode1 and focusHub not null.
     */
    auto columnNode1 = CreateNodeWithFocusPattern("columnNode1", FocusType::SCOPE, false);
    EXPECT_NE(columnNode1, nullptr);
    columnNode1->UpdateInspectorId("columnNode1");
    auto columnFocusHub1 = columnNode1->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub1, nullptr);
    columnFocusHub1->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create columnNode2 and focusHub.
     * @tc.expected: columnNode2 and focusHub not null.
     */
    auto columnNode2 = CreateNodeWithFocusPattern("columnNode2", FocusType::NODE, false);
    EXPECT_NE(columnNode2, nullptr);
    columnNode2->UpdateInspectorId("columnNode2");
    auto columnFocusHub2 = columnNode2->GetOrCreateFocusHub();
    EXPECT_NE(columnFocusHub2, nullptr);
    columnFocusHub2->SetFocusDependence(FocusDependence::AUTO);

    /**
     * @tc.steps: step2. Create buttonNode1 and focusHub.
     * @tc.expected: buttonNode1 and focusHub not null.
     */
    auto buttonNode1 = CreateNodeWithFocusPattern("buttonNode1", FocusType::NODE, false);
    EXPECT_NE(buttonNode1, nullptr);
    buttonNode1->UpdateInspectorId("BUTTONNODE1");
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub1, nullptr);

    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode1);
    columnNode1->AddChild(columnNode2);
    columnNode2->AddChild(buttonNode1);

    /**
     * @tc.steps: step2. Create pipeline and focusManager.
     * @tc.expected: pipeline and focusManager not null.
     */
    auto pipeline = pageNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Create Register the callback function.
     * @tc.steps: step2. Pressing tab does not trigger a callback.
     * @tc.expected: focusCount add 1.
     */
    int32_t focusCount = 0;
    pageFocusHub->SetOnFocusCallback(([&focusCount]() {
        focusCount++;
    }));
    pageFocusHub->RequestFocusImmediately();
    EXPECT_EQ(focusCount, 1);
    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    event.action = KeyAction::DOWN;
    event.pressedCodes = {KeyCode::KEY_TAB};
    focusManager->isFocusActive_ = true;
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = false;
    event.eventType = UIInputEventType::KEY;
    focusManager->keyProcessingMode_ = KeyProcessingMode::ANCESTOR_EVENT;
    auto res = pageFocusHub->HandleEvent(event);
    EXPECT_TRUE(res);
    EXPECT_EQ(focusCount, 1);
}
} // namespace OHOS::Ace::NG

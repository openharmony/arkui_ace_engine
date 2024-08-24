/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class FocusViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FocusViewTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FocusViewTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: FocusViewTest001
 * @tc.desc: FocusViewShow / FocusViewClose / GetCurrentFocusView() / GetEntryFocusView()
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct all kinds of FocusView.
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto bubblePattern = AceType::MakeRefPtr<BubblePattern>();
    auto bubbleNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, bubblePattern);
    auto bubbleFocusHub = bubbleNode->GetOrCreateFocusHub();
    rootNode->AddChild(bubbleNode);

    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, -1, dialogPattern);
    auto dialogFocusHub = dialogNode->GetOrCreateFocusHub();
    rootNode->AddChild(dialogNode);

    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::MENU);
    auto menuNode = FrameNodeOnTree::CreateFrameNode(V2::MENU_ETS_TAG, -1, menuPattern);
    auto menuFocusHub = menuNode->GetOrCreateFocusHub();
    rootNode->AddChild(menuNode);

    auto modalPattern = AceType::MakeRefPtr<ModalPresentationPattern>(-1, ModalTransition::DEFAULT, nullptr);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPattern);
    auto modalFocusHub = modalNode->GetOrCreateFocusHub();
    rootNode->AddChild(modalNode);

    auto sheetPattern = AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr);
    auto sheetNode = FrameNodeOnTree::CreateFrameNode(V2::SHEET_PAGE_TAG, -1, sheetPattern);
    auto sheetFocusHub = sheetNode->GetOrCreateFocusHub();
    rootNode->AddChild(sheetNode);

    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto navigationNode = FrameNodeOnTree::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, -1, navigationPattern);
    auto navigationFocusHub = navigationNode->GetOrCreateFocusHub();

    auto navbarPattern = AceType::MakeRefPtr<NavBarPattern>();
    auto navbarNode = FrameNodeOnTree::CreateFrameNode(V2::NAVBAR_ETS_TAG, -1, navbarPattern);
    auto navbarFocusHub = navbarNode->GetOrCreateFocusHub();

    auto navdestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>(nullptr);
    auto navdestinationNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, navdestinationPattern);
    auto navdestinationFocusHub = navdestinationNode->GetOrCreateFocusHub();

    pageNode->AddChild(navigationNode);
    navigationNode->AddChild(navbarNode);
    navigationNode->AddChild(navdestinationNode);

    /**
     * @tc.steps: step2. GetCurrentFocusView expect equal with the view showed.
     */
    pagePattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), pagePattern);
    EXPECT_EQ(pagePattern->GetEntryFocusView(), pagePattern);

    bubblePattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), bubblePattern);
    EXPECT_EQ(bubblePattern->GetEntryFocusView(), bubblePattern);

    dialogPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), dialogPattern);
    EXPECT_EQ(dialogPattern->GetEntryFocusView(), dialogPattern);

    menuPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), menuPattern);
    EXPECT_EQ(menuPattern->GetEntryFocusView(), menuPattern);

    modalPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), modalPattern);
    EXPECT_EQ(modalPattern->GetEntryFocusView(), modalPattern);

    sheetPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), sheetPattern);
    EXPECT_EQ(sheetPattern->GetEntryFocusView(), sheetPattern);

    navbarPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), navbarPattern);
    EXPECT_EQ(navbarPattern->GetEntryFocusView(), pagePattern);

    navdestinationPattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), navdestinationPattern);
    EXPECT_EQ(navdestinationPattern->GetEntryFocusView(), pagePattern);

    /**
     * @tc.steps: step2. GetCurrentFocusView expect equal with the last view after FocusViewClose.
     */
    navdestinationPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), navbarPattern);
    EXPECT_EQ(navbarPattern->GetEntryFocusView(), pagePattern);

    navbarPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), sheetPattern);
    EXPECT_EQ(sheetPattern->GetEntryFocusView(), sheetPattern);

    sheetPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), modalPattern);
    EXPECT_EQ(modalPattern->GetEntryFocusView(), modalPattern);

    modalPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), menuPattern);
    EXPECT_EQ(menuPattern->GetEntryFocusView(), menuPattern);

    menuPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), dialogPattern);
    EXPECT_EQ(dialogPattern->GetEntryFocusView(), dialogPattern);

    dialogPattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), bubblePattern);
    EXPECT_EQ(bubblePattern->GetEntryFocusView(), bubblePattern);

    bubblePattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), pagePattern);
    EXPECT_EQ(pagePattern->GetEntryFocusView(), pagePattern);

    pagePattern->FocusViewClose();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), nullptr);
}

/**
 * @tc.name: FocusViewTest002
 * @tc.desc: Page first call FocusViewShow without defaultFocus
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: columnFocusHub
     */
    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern->isViewHasFocused_ is false.
     */
    pagePattern->FocusViewShow();
    EXPECT_FALSE(pagePattern->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected: Page / Column get focused.
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern->isViewHasFocused_);
    EXPECT_TRUE(pagePattern->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern->neverShown_);
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub2->IsCurrentFocus());
}

/**
 * @tc.name: FocusViewTest003
 * @tc.desc: Page first call FocusViewShow with defaultFocus
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();
    buttonFocusHub2->SetIsDefaultFocus(true);

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: columnFocusHub
     */
    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern->isViewHasFocused_ is false.
     */
    pagePattern->FocusViewShow();
    EXPECT_FALSE(pagePattern->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected: Page / Column / Button2(defaultFocus) get focused.
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern->isViewHasFocused_);
    EXPECT_FALSE(pagePattern->isViewRootScopeFocused_);
    EXPECT_FALSE(pagePattern->neverShown_);
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_TRUE(buttonFocusHub2->IsCurrentFocus());
}

/**
 * @tc.name: FocusViewTest004
 * @tc.desc: Page call FocusViewShow with SetIsViewRootScopeFocused(false)
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: columnFocusHub
     */
    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern->isViewHasFocused_ is false.
     */
    pagePattern->SetIsViewRootScopeFocused(false);
    pagePattern->FocusViewShow();
    EXPECT_FALSE(pagePattern->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected: Page / Column / Button1 get focused.
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern->isViewHasFocused_);
    EXPECT_FALSE(pagePattern->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern->neverShown_);
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_TRUE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub2->IsCurrentFocus());
}

/**
 * @tc.name: FocusViewTest005
 * @tc.desc: Page1 FocusViewShow / Page2 FocusViewShow
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page1
     *   - Column1
     *     - Button11
     *     - Button12
     * - Page2
     *   - Column2
     *     - Button21
     *     - Button22
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageFocusHub1 = pageNode1->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode1);

    auto columnPattern1 = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode1 = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern1);
    auto columnFocusHub1 = columnNode1->GetOrCreateFocusHub();

    auto buttonPattern11 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode11 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern11);
    auto buttonFocusHub11 = buttonNode11->GetOrCreateFocusHub();

    auto buttonPattern12 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode12 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern12);
    auto buttonFocusHub12 = buttonNode12->GetOrCreateFocusHub();

    pageNode1->AddChild(columnNode1);
    columnNode1->AddChild(buttonNode11);
    columnNode1->AddChild(buttonNode12);

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto pageFocusHub2 = pageNode2->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode2);

    auto columnPattern2 = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode2 = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern2);
    auto columnFocusHub2 = columnNode2->GetOrCreateFocusHub();

    auto buttonPattern21 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode21 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern21);
    auto buttonFocusHub21 = buttonNode21->GetOrCreateFocusHub();

    auto buttonPattern22 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode22 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern22);
    auto buttonFocusHub22 = buttonNode22->GetOrCreateFocusHub();

    pageNode2->AddChild(columnNode2);
    columnNode2->AddChild(buttonNode21);
    columnNode2->AddChild(buttonNode22);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: pagePattern1 -> columnFocusHub1 / pagePattern2 -> columnFocusHub2
     */
    EXPECT_EQ(pagePattern1->GetViewRootScope(), columnFocusHub1);
    EXPECT_EQ(pagePattern2->GetViewRootScope(), columnFocusHub2);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern1->isViewHasFocused_ is false.
     */
    pagePattern1->FocusViewShow();
    EXPECT_FALSE(pagePattern1->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected:
     * - Page1 *
     *   - Column1 *
     *     - Button11
     *     - Button12
     * - Page2
     *   - Column2
     *     - Button21
     *     - Button22
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern1->isViewHasFocused_);
    EXPECT_TRUE(pagePattern1->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern1->neverShown_);
    EXPECT_TRUE(pageFocusHub1->IsCurrentFocus());
    EXPECT_TRUE(pagePattern1->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub11->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub12->IsCurrentFocus());

    EXPECT_FALSE(pagePattern2->isViewHasFocused_);
    EXPECT_TRUE(pagePattern2->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern2->neverShown_);
    EXPECT_FALSE(pageFocusHub2->IsCurrentFocus());
    EXPECT_FALSE(pagePattern2->IsRootScopeCurrentFocus());
    EXPECT_FALSE(columnFocusHub2->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub21->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub22->IsCurrentFocus());

    /**
     * @tc.steps: step5. Page execute FocusViewShow()
     * expected: pagePattern2->isViewHasFocused_ is false.
     */
    pagePattern2->FocusViewShow();
    EXPECT_FALSE(pagePattern2->isViewHasFocused_);

    /**
     * @tc.steps: step6. FlushFocusView()
     * expected:
     * - Page1
     *   - Column1
     *     - Button11
     *     - Button12
     * - Page2 *
     *   - Column2 *
     *     - Button21
     *     - Button22
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern1->isViewHasFocused_);
    EXPECT_TRUE(pagePattern1->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern1->neverShown_);
    EXPECT_FALSE(pageFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(pagePattern1->IsRootScopeCurrentFocus());
    EXPECT_FALSE(columnFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub11->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub12->IsCurrentFocus());

    EXPECT_TRUE(pagePattern2->isViewHasFocused_);
    EXPECT_TRUE(pagePattern2->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern2->neverShown_);
    EXPECT_TRUE(pageFocusHub2->IsCurrentFocus());
    EXPECT_TRUE(pagePattern2->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub2->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub21->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub22->IsCurrentFocus());

    /**
     * @tc.steps: step7. Page2 execute FocusViewClose()
     * expected: pagePattern1->isViewHasFocused_ is false.
     */
    pagePattern2->FocusViewClose();

    /**
     * @tc.steps: step8. FlushFocusView()
     * expected:
     * - Page1 *
     *   - Column1 *
     *     - Button11
     *     - Button12
     * - Page2
     *   - Column2
     *     - Button21
     *     - Button22
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern1->isViewHasFocused_);
    EXPECT_TRUE(pagePattern1->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern1->neverShown_);
    EXPECT_TRUE(pageFocusHub1->IsCurrentFocus());
    EXPECT_TRUE(pagePattern1->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub11->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub12->IsCurrentFocus());

    EXPECT_TRUE(pagePattern2->isViewHasFocused_);
    EXPECT_TRUE(pagePattern2->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern2->neverShown_);
    EXPECT_FALSE(pageFocusHub2->IsCurrentFocus());
    EXPECT_FALSE(pagePattern2->IsRootScopeCurrentFocus());
    EXPECT_FALSE(columnFocusHub2->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub21->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub22->IsCurrentFocus());
}

/**
 * @tc.name: FocusViewTest006
 * @tc.desc: TriggerFocusMove without tabIndex
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: columnFocusHub
     */
    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern->isViewHasFocused_ is false.
     */
    pagePattern->FocusViewShow();
    EXPECT_FALSE(pagePattern->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected: Page / Column get focused.
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern->isViewHasFocused_);
    EXPECT_TRUE(pagePattern->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern->neverShown_);
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub2->IsCurrentFocus());

    /**
     * @tc.steps: step5. TriggerFocusMove()
     * expected: Page / Column / Button1 get focused.
     */
    pagePattern->TriggerFocusMove();
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_TRUE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub2->IsCurrentFocus());
}

/**
 * @tc.name: FocusViewTest007
 * @tc.desc: TriggerFocusMove with tabIndex
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusViewTestNg, FocusViewTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();
    buttonFocusHub2->SetTabIndex(1);

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    /**
     * @tc.steps: step2. Get pagePattern's ViewRootScope
     * expected: columnFocusHub
     */
    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);

    /**
     * @tc.steps: step3. Page execute FocusViewShow()
     * expected: pagePattern->isViewHasFocused_ is false.
     */
    pagePattern->FocusViewShow();
    EXPECT_FALSE(pagePattern->isViewHasFocused_);

    /**
     * @tc.steps: step4. FlushFocusView()
     * expected: Page / Column get focused.
     */
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_TRUE(pagePattern->isViewHasFocused_);
    EXPECT_TRUE(pagePattern->isViewRootScopeFocused_);
    EXPECT_TRUE(pagePattern->neverShown_);
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub2->IsCurrentFocus());

    /**
     * @tc.steps: step5. TriggerFocusMove()
     * expected: Page / Column / Button2 get focused.
     */
    pagePattern->TriggerFocusMove();
    EXPECT_TRUE(pageFocusHub->IsCurrentFocus());
    EXPECT_TRUE(pagePattern->IsRootScopeCurrentFocus());
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub1->IsCurrentFocus());
    EXPECT_TRUE(buttonFocusHub2->IsCurrentFocus());
}
} // namespace OHOS::Ace::NG

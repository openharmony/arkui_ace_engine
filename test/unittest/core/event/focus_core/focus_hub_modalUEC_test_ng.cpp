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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ModalFocusHubTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ModalFocusHubTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ModalFocusHubTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ModalFocusHubTest001
 * @tc.desc: Test ModalCheckBeforeRequestFocus returns true when modal stack is empty
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Verify modal stack is empty
     */
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());

    /**
     * @tc.steps: step3. Get FocusHub and call ModalCheckBeforeRequestFocus
     * expected: result is true when modal stack is empty
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto canRequest = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

/**
 * @tc.name: ModalFocusHubTest002
 * @tc.desc: Test ModalCheckBeforeRequestFocus returns true when current node is in modal stack
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree with modal view
     * - Root
     *   - Page
     *     - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Get button's FocusHub and call ModalCheckBeforeRequestFocus
     * expected: result is true (button is child of modal view)
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto canRequest = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

/**
 * @tc.name: ModalFocusHubTest003
 * @tc.desc: Test ModalCheckBeforeRequestFocus returns true for nested child view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup nested component tree
     * - Root
     *   - Page
     *     - Column
     *       - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Get button's FocusHub (nested child) and call check
     * expected: result is true for nested child
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto canRequest = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

/**
 * @tc.name: ModalFocusHubTest004
 * @tc.desc: Test ModalCheckBeforeRequestFocus returns false for unrelated node
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup two separate pages
     * - Root
     *   - Page1
     *   - Page2
     *     - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);
    pageNode2->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern1 to modal stack
     */
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);

    /**
     * @tc.steps: step3. Get button's FocusHub (child of pageNode2, not pagePattern1)
     * expected: result is true for unrelated node
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto canRequest = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

/**
 * @tc.name: ModalFocusHubTest005
 * @tc.desc: Test ModalCheckBeforeRequestFocus with multi-level nesting
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup deeply nested tree
     * - Root
     *   - Page
     *     - Column1
     *       - Column2
     *         - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto columnPattern1 = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode1 = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern1);
    auto columnPattern2 = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode2 = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern2);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(columnNode1);
    columnNode1->AddChild(columnNode2);
    columnNode2->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Get deeply nested button's FocusHub and call check
     * expected: result is true for deeply nested child
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto canRequest = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

/**
 * @tc.name: ModalFocusHubTest006
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC returns false for non-UIExtension
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup button node (non-UIExtension)
     * - Root
     *   - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Get button's FocusHub and call RequestFocusImmediatelyFromModalUEC
     * expected: result is false for non-UIExtension component
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ModalFocusHubTest007
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC returns false for non-modal UIExtension
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup non-modal UIExtension
     * - Root
     *   - UIExtension (isModal=false)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(false);
    auto nonModalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    rootNode->AddChild(nonModalNode);

    /**
     * @tc.steps: step2. Get UIExtension's FocusHub and call RequestFocusImmediatelyFromModalUEC
     * expected: result is false for non-modal UIExtension
     */
    auto focusHub = nonModalNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ModalFocusHubTest007B
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC returns false when isModalFixFocus is false
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest007B, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension without fix focus
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true, isModalFixFocus=false)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern);
    rootNode->AddChild(modalPageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(true);
    modalPattern->SetIsModalFixFocus(false);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    /**
     * @tc.steps: step2. Get UIExtension's FocusHub and call RequestFocusImmediatelyFromModalUEC
     * expected: result is true (isModalFixFocus is false)
     */
    auto focusHub = modalNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ModalFocusHubTest008
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC is intercepted when modal stack is valid
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup two modal UIExtensions
     * - Root
     *   - ModalPage1 (MODAL_PAGE_TAG)
     *     - UIExtension1 (isModal=true)
     *   - ModalPage2 (MODAL_PAGE_TAG)
     *     - UIExtension2 (isModal=true)
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern1 = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPagePattern2 = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode1 = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern1);
    auto modalPageNode2 = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern2);
    rootNode->AddChild(modalPageNode1);
    rootNode->AddChild(modalPageNode2);

    auto modalPattern1 = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern1->SetModalFlag(true);
    modalPattern1->SetIsModalFixFocus(true);
    auto modalPattern2 = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern2->SetModalFlag(true);
    modalPattern2->SetIsModalFixFocus(true);
    auto modalNode1 = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern1);
    auto modalNode2 = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern2);
    modalPageNode1->AddChild(modalNode1);
    modalPageNode2->AddChild(modalNode2);

    /**
     * @tc.steps: step2. Add modalPagePattern1 to modal stack (simulating existing modal window)
     */
    auto modalPageWeakPtr1 = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr1);

    /**
     * @tc.steps: step3. Try to request focus for second modal UIExtension
     * expected: result is false (intercepted by existing modal stack)
     */
    auto focusHub2 = modalNode2->GetFocusHub();
    ASSERT_NE(focusHub2, nullptr);
    auto result = focusHub2->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ModalFocusHubTest009
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC succeeds for modal UIExtension
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern);
    rootNode->AddChild(modalPageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    /**
     * @tc.steps: step2. Verify modal stack is empty (no existing modal window)
     */
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());

    /**
     * @tc.steps: step3. Get modal UIExtension's FocusHub and call RequestFocusImmediatelyFromModalUEC
     * expected: focus request succeeds (actual result depends on RequestFocusImmediatelyInner)
     */
    auto focusHub = modalNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ModalFocusHubTest010
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC verifies focus state
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern);
    rootNode->AddChild(modalPageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    /**
     * @tc.steps: step2. Get modal UIExtension's FocusHub
     */
    auto focusHub = modalNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Call RequestFocusImmediatelyFromModalUEC with DEFAULT reason
     * expected: method is called with correct parameters
     */
    auto result = focusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ModalFocusHubTest011
 * @tc.desc: Test RequestFocusImmediately is intercepted by modal check
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree with modal view
     * - Root
     *   - Page1
     *   - Page2
     *     - Button
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);
    pageNode2->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern1 to modal stack
     */
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);

    /**
     * @tc.steps: step3. Try to request focus for button (unrelated to modal view)
     * expected: request is intercepted by modal check
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->RequestFocusImmediately(FocusReason::DEFAULT);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ModalFocusHubTest012
 * @tc.desc: Test RequestFocusImmediately proceeds when modal check passes
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page
     *     - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Verify modal stack is empty
     */
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());

    /**
     * @tc.steps: step3. Get button's FocusHub and call RequestFocusImmediately
     * expected: request proceeds (modal check returns true)
     */
    auto focusHub = buttonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately(FocusReason::DEFAULT);
}

/**
 * @tc.name: ModalFocusHubTest013
 * @tc.desc: Test LostFocusToViewRoot is intercepted when modal stack is valid
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree with modal view
     * - Root
     *   - Page
     *     - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add pagePattern to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Set current focus view to pagePattern using FocusViewShow
     */
    pagePattern->FocusViewShow();
    EXPECT_EQ(FocusView::GetCurrentFocusView(), pagePattern);

    /**
     * @tc.steps: step4. Call LostFocusToViewRoot
     * expected: LostFocusToViewRoot is intercepted (viewRootScope not changed)
     */
    auto viewRootScopeBefore = pagePattern->GetViewRootScope();
    FocusHub::LostFocusToViewRoot();
    auto viewRootScopeAfter = pagePattern->GetViewRootScope();
    EXPECT_EQ(viewRootScopeAfter, viewRootScopeBefore);
}

/**
 * @tc.name: ModalFocusHubTest015
 * @tc.desc: Test focus is locked on modal UIExtension, other components cannot steal focus
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree with modal UIExtension
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - ModalUIExtension (isModal=true, isModalFixFocus=true)
     *   - Page (PAGE_ETS_TAG)
     *     - Button
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    // Create modal UIExtension
    auto modalPagePattern = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern);
    rootNode->AddChild(modalPageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(true);
    modalPattern->SetIsModalFixFocus(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    // Create button on separate page (not child of modal)
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    rootNode->AddChild(pageNode);
    pageNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Modal UIExtension requests focus and succeeds
     */
    auto modalFocusHub = modalNode->GetFocusHub();
    ASSERT_NE(modalFocusHub, nullptr);
    modalFocusHub->RequestFocusImmediatelyFromModalUEC(FocusReason::DEFAULT);

    /**
     * @tc.steps: step3. Add modalPagePattern to modal stack
     */
    auto modalPageWeakPtr = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr);

    /**
     * @tc.steps: step4. Set current focus to modal UIExtension
     */
    focusManager->currentFocus_ = modalFocusHub;

    /**
     * @tc.steps: step5. Button (unrelated component) tries to request focus
     * expected: request is intercepted, button cannot steal focus from modal UIExtension
     */
    auto buttonFocusHub = buttonNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);
    auto buttonResult = buttonFocusHub->RequestFocusImmediately(FocusReason::DEFAULT);
    EXPECT_FALSE(buttonResult);

    /**
     * @tc.steps: step6. Verify focus is still on modal UIExtension
     */
    EXPECT_EQ(focusManager->currentFocus_, modalFocusHub);
    EXPECT_TRUE(modalFocusHub->IsCurrentFocus());
    EXPECT_FALSE(buttonFocusHub->IsCurrentFocus());
}

/**
 * @tc.name: ModalFocusHubTest016
 * @tc.desc: Test child components inside modal UIExtension can request focus normally
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusHubTestNg, ModalFocusHubTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - OuterRoot
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - ModalUIExtension (isModal=true, isModalFixFocus=true)
     *       - InnerRoot (inside UIExtension)
     *         - Page (PAGE_ETS_TAG)
     *           - Button (child inside modal UIExtension)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto outerRootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern);
    outerRootNode->AddChild(modalPageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(true);
    modalPattern->SetIsModalFixFocus(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    // Inside UIExtension: create Root - Page - Button structure
    auto innerRootPattern = AceType::MakeRefPtr<RootPattern>();
    auto innerRootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, innerRootPattern);
    modalNode->AddChild(innerRootNode);

    auto innerPagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto innerPageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, innerPagePattern);
    innerRootNode->AddChild(innerPageNode);

    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern);
    innerPageNode->AddChild(buttonNode);

    /**
     * @tc.steps: step2. Add modalPagePattern to modal stack
     */
    auto modalPageWeakPtr = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr);

    /**
     * @tc.steps: step3. Set current focus to modal UIExtension
     */
    auto modalFocusHub = modalNode->GetFocusHub();
    ASSERT_NE(modalFocusHub, nullptr);
    focusManager->currentFocus_ = modalFocusHub;

    /**
     * @tc.steps: step4. Button (inside modal UIExtension's child tree) requests focus
     * expected: request is allowed (Button is descendant of modal view)
     */
    auto buttonFocusHub = buttonNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);
    auto canRequest = buttonFocusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(canRequest);
}

} // namespace OHOS::Ace::NG

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
namespace {
constexpr int32_t SIZE_1 = 1;
constexpr int32_t SIZE_2 = 2;
} // namespace

class ModalFocusManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ModalFocusManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ModalFocusManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ModalFocusManagerTest001
 * @tc.desc: Test IsModalFocusViewStackValid returns false when stack is empty
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with empty modal stack
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call IsModalFocusViewStackValid
     * expected: result is false for empty stack
     */
    auto isValid = focusManager->IsModalFocusViewStackValid();
    EXPECT_FALSE(isValid);
}

/**
 * @tc.name: ModalFocusManagerTest002
 * @tc.desc: Test IsModalFocusViewStackValid returns true when stack has valid object
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Add valid focus view to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Call IsModalFocusViewStackValid
     * expected: result is true when stack has valid object
     */
    auto isValid = focusManager->IsModalFocusViewStackValid();
    EXPECT_TRUE(isValid);
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), SIZE_1);
}

/**
 * @tc.name: ModalFocusManagerTest003
 * @tc.desc: Test IsModalFocusViewStackValid returns false when stack only has invalid pointers
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Add invalid weak pointer to modal stack
     */
    WeakPtr<FocusView> invalidWeakPtr = nullptr;
    focusManager->modalFocusViewStack_.emplace_back(invalidWeakPtr);

    /**
     * @tc.steps: step3. Call IsModalFocusViewStackValid
     * expected: result is false when stack only has invalid pointers
     */
    auto isValid = focusManager->IsModalFocusViewStackValid();
    EXPECT_FALSE(isValid);
}

/**
 * @tc.name: ModalFocusManagerTest004
 * @tc.desc: Test IsModalFocusViewStackValid returns true when stack has partial valid objects
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup components
     * - Root
     *   - Page1
     *   - Page2
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);

    /**
     * @tc.steps: step2. Add mix of valid and invalid pointers to modal stack
     */
    WeakPtr<FocusView> invalidWeakPtr = nullptr;
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    auto pageWeakPtr2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern2));

    focusManager->modalFocusViewStack_.emplace_back(invalidWeakPtr);
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);
    focusManager->modalFocusViewStack_.emplace_back(invalidWeakPtr);
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr2);

    /**
     * @tc.steps: step3. Call IsModalFocusViewStackValid
     * expected: result is true when stack has at least one valid object
     */
    auto isValid = focusManager->IsModalFocusViewStackValid();
    EXPECT_TRUE(isValid);
}

/**
 * @tc.name: ModalFocusManagerTest005
 * @tc.desc: Test GetValidModalFocusView returns nullptr when stack is empty
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with empty modal stack
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call GetValidModalFocusView
     * expected: result is nullptr for empty stack
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_EQ(validView, nullptr);
}

/**
 * @tc.name: ModalFocusManagerTest006
 * @tc.desc: Test GetValidModalFocusView returns valid view from top of stack
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Add focus view to modal stack
     */
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);

    /**
     * @tc.steps: step3. Call GetValidModalFocusView
     * expected: result is the valid view from stack
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_NE(validView, nullptr);
    EXPECT_EQ(validView, pagePattern);
}

/**
 * @tc.name: ModalFocusManagerTest007
 * @tc.desc: Test GetValidModalFocusView skips invalid pointers and returns valid view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Add mix of invalid and valid pointers to modal stack
     */
    WeakPtr<FocusView> invalidWeakPtr1 = nullptr;
    auto pageWeakPtr = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern));
    WeakPtr<FocusView> invalidWeakPtr2 = nullptr;

    focusManager->modalFocusViewStack_.emplace_back(invalidWeakPtr1);
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr);
    focusManager->modalFocusViewStack_.emplace_back(invalidWeakPtr2);

    /**
     * @tc.steps: step3. Call GetValidModalFocusView
     * expected: result skips invalid pointers and returns valid view
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_NE(validView, nullptr);
    EXPECT_EQ(validView, pagePattern);
}

/**
 * @tc.name: ModalFocusManagerTest008
 * @tc.desc: Test ArrangeModalFocusViewStack does not add non-UIExtension component
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree with button
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
     * @tc.steps: step2. Set current focus to button (non-UIExtension component)
     */
    auto buttonFocusHub = buttonNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);
    focusManager->currentFocus_ = buttonFocusHub;

    /**
     * @tc.steps: step3. Call ArrangeModalFocusViewStack
     * expected: modal stack is not modified
     */
    auto initialStackSize = focusManager->modalFocusViewStack_.size();
    focusManager->ArrangeModalFocusViewStack();
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), initialStackSize);
}

/**
 * @tc.name: ModalFocusManagerTest009
 * @tc.desc: Test ArrangeModalFocusViewStack does not add non-modal UIExtension
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup non-modal UIExtension
     * - Root
     *   - Page (PAGE_ETS_TAG)
     *     - UIExtension (isModal=false, isModalFixFocus=false)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    auto modalPattern = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern->SetModalFlag(false);
    auto nonModalNode = FrameNodeOnTree::CreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    pageNode->AddChild(nonModalNode);

    /**
     * @tc.steps: step2. Set current focus to non-modal UIExtension
     */
    auto nonModalFocusHub = nonModalNode->GetFocusHub();
    ASSERT_NE(nonModalFocusHub, nullptr);
    focusManager->currentFocus_ = nonModalFocusHub;

    /**
     * @tc.steps: step3. Call ArrangeModalFocusViewStack
     * expected: modal stack is not modified (isModal is false)
     */
    auto initialStackSize = focusManager->modalFocusViewStack_.size();
    focusManager->ArrangeModalFocusViewStack();
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), initialStackSize);
}

/**
 * @tc.name: ModalFocusManagerTest009B
 * @tc.desc: Test ArrangeModalFocusViewStack does not add modal UIExtension when isModalFixFocus is false
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest009B, TestSize.Level1)
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
     * @tc.steps: step2. Set current focus to modal UIExtension
     */
    auto modalFocusHub = modalNode->GetFocusHub();
    ASSERT_NE(modalFocusHub, nullptr);
    focusManager->currentFocus_ = modalFocusHub;

    /**
     * @tc.steps: step3. Call ArrangeModalFocusViewStack
     * expected: modal stack is not modified (isModalFixFocus is false)
     */
    auto initialStackSize = focusManager->modalFocusViewStack_.size();
    focusManager->ArrangeModalFocusViewStack();
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), initialStackSize);
}

/**
 * @tc.name: ModalFocusManagerTest010
 * @tc.desc: Test ArrangeModalFocusViewStack adds modal UIExtension to stack
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true, isModalFixFocus=true)
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
    modalPattern->SetIsModalFixFocus(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    /**
     * @tc.steps: step2. Set current focus to modal UIExtension
     */
    auto modalFocusHub = modalNode->GetFocusHub();
    ASSERT_NE(modalFocusHub, nullptr);
    focusManager->currentFocus_ = modalFocusHub;

    /**
     * @tc.steps: step3. Call ArrangeModalFocusViewStack
     * expected: modal UIExtension is added to stack
     */
    auto initialStackSize = focusManager->modalFocusViewStack_.size();
    focusManager->ArrangeModalFocusViewStack();
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), initialStackSize + SIZE_1);

    /**
     * @tc.steps: step4. Verify the added view is valid
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_NE(validView, nullptr);
}

/**
 * @tc.name: ModalFocusManagerTest011
 * @tc.desc: Test ArrangeModalFocusViewStack moves duplicate modal view to top of stack
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true, isModalFixFocus=true)
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
    modalPattern->SetIsModalFixFocus(true);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern);
    modalPageNode->AddChild(modalNode);

    /**
     * @tc.steps: step2. Manually add modalPagePattern to modal stack
     */
    auto modalPageWeakPtr = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr);

    /**
     * @tc.steps: step3. Set current focus to modal UIExtension and call ArrangeModalFocusViewStack
     * expected: view is moved to top of stack (not duplicated)
     */
    auto modalFocusHub = modalNode->GetFocusHub();
    ASSERT_NE(modalFocusHub, nullptr);
    focusManager->currentFocus_ = modalFocusHub;
    focusManager->ArrangeModalFocusViewStack();
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), SIZE_1);

    /**
     * @tc.steps: step4. Verify top of stack is the same view
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_EQ(validView, modalPagePattern);
}

/**
 * @tc.name: ModalFocusManagerTest012
 * @tc.desc: Test ArrangeModalFocusViewStack handles multiple modal views correctly
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup multiple modal UIExtensions
     * - Root
     *   - Page1
     *     - UIExtension1 (isModal=true)
     *   - Page2
     *     - UIExtension2 (isModal=true)
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    auto modalPagePattern1 = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode1 = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern1);

    auto modalPagePattern2 = AceType::MakeRefPtr<ModalPresentationPattern>(
        -1, ModalTransition::DEFAULT, nullptr);
    auto modalPageNode2 = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPagePattern2);
    rootNode->AddChild(modalPageNode1);
    rootNode->AddChild(modalPageNode2);

    auto modalPattern1 = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern1->SetModalFlag(true);
    modalPattern1->SetIsModalFixFocus(true);
    auto modalNode1 = FrameNodeOnTree::CreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern1);
    modalPageNode1->AddChild(modalNode1);

    auto modalPattern2 = AceType::MakeRefPtr<UIExtensionPattern>();
    modalPattern2->SetModalFlag(true);
    modalPattern2->SetIsModalFixFocus(true);
    auto modalNode2 = FrameNodeOnTree::CreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_TAG, -1, modalPattern2);
    modalPageNode2->AddChild(modalNode2);

    /**
     * @tc.steps: step2. Set focus to first modal UIExtension
     */
    auto modalFocusHub1 = modalNode1->GetFocusHub();
    ASSERT_NE(modalFocusHub1, nullptr);
    focusManager->currentFocus_ = modalFocusHub1;
    focusManager->ArrangeModalFocusViewStack();

    /**
     * @tc.steps: step3. Set focus to second modal UIExtension
     */
    auto modalFocusHub2 = modalNode2->GetFocusHub();
    ASSERT_NE(modalFocusHub2, nullptr);
    focusManager->currentFocus_ = modalFocusHub2;
    focusManager->ArrangeModalFocusViewStack();

    /**
     * @tc.steps: step4. Verify both modal views are in stack and top is second
     */
    EXPECT_EQ(focusManager->modalFocusViewStack_.size(), SIZE_2);
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_EQ(validView, modalPagePattern2);
}

/**
 * @tc.name: ModalFocusManagerTest013
 * @tc.desc: Test FocusViewShow is intercepted when modal stack is valid for non-child view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page1
     *   - Page2
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);

    /**
     * @tc.steps: step2. Add pagePattern1 to modal stack
     */
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);
    focusManager->lastFocusView_ = pageWeakPtr1;

    /**
     * @tc.steps: step3. Call FocusViewShow for pagePattern2 (non-child view)
     * expected: FocusViewShow is intercepted (lastFocusView not changed)
     */
    auto lastFocusViewBefore = focusManager->lastFocusView_.Upgrade();
    focusManager->FocusViewShow(pagePattern2);
    auto lastFocusViewAfter = focusManager->lastFocusView_.Upgrade();
    EXPECT_EQ(lastFocusViewAfter, lastFocusViewBefore);
}

/**
 * @tc.name: ModalFocusManagerTest014
 * @tc.desc: Test FocusViewShow allows child view when modal stack is valid
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension with internal child structure
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true)
     *       - InnerRoot (inside UIExtension)
     *         - Page (PAGE_ETS_TAG)
     *           - Button (child inside modal UIExtension)
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
     * @tc.steps: step3. Call FocusViewHide for modalNode (child of modalPagePattern)
     * expected: FocusViewHide is intercepted (stack not modified)
     */
    auto viewStackSizeBefore = focusManager->focusViewStack_.size();
    auto lastFocusViewBefore = focusManager->lastFocusView_.Upgrade();
    focusManager->FocusViewShow(innerPagePattern);
    auto viewStackSizeAfter = focusManager->focusViewStack_.size();
    auto lastFocusViewAfter = focusManager->lastFocusView_.Upgrade();
    EXPECT_EQ(viewStackSizeAfter, viewStackSizeBefore);
    EXPECT_EQ(lastFocusViewAfter, lastFocusViewBefore);
}

/**
 * @tc.name: ModalFocusManagerTest015
 * @tc.desc: Test FocusViewShow works normally when modal stack is empty
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup component tree
     * - Root
     *   - Page
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Verify modal stack is empty
     */
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());

    /**
     * @tc.steps: step3. Call FocusViewShow for pagePattern
     * expected: FocusViewShow works normally
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), pagePattern);
    EXPECT_EQ(focusManager->GetWeakFocusViewList().size(), SIZE_1);
}

/**
 * @tc.name: ModalFocusManagerTest016
 * @tc.desc: Test FocusViewHide is intercepted when hiding modal view itself
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest016, TestSize.Level1)
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
     * @tc.steps: step2. Add modalPagePattern to modal stack and show it
     */
    auto modalPageWeakPtr = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr);
    modalPagePattern->FocusViewShow();

    /**
     * @tc.steps: step3. Call FocusViewHide for the modal view in stack
     * expected: FocusViewHide is intercepted (stack not modified)
     */
    auto viewStackSizeBefore = focusManager->focusViewStack_.size();
    focusManager->FocusViewHide(modalPagePattern);
    auto viewStackSizeAfter = focusManager->focusViewStack_.size();
    EXPECT_EQ(viewStackSizeAfter, viewStackSizeBefore);
}

/**
 * @tc.name: ModalFocusManagerTest017
 * @tc.desc: Test FocusViewHide is intercepted when hiding child of modal view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup modal UIExtension with internal child structure
     * - Root
     *   - ModalPage (MODAL_PAGE_TAG)
     *     - UIExtension (isModal=true)
     *       - InnerRoot (inside UIExtension)
     *         - Page (PAGE_ETS_TAG)
     *           - Button (child inside modal UIExtension)
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
     * @tc.steps: step3. Call FocusViewHide for modalNode (child of modalPagePattern)
     * expected: FocusViewHide is intercepted (stack not modified)
     */
    auto viewStackSizeBefore = focusManager->focusViewStack_.size();
    focusManager->FocusViewHide(innerPagePattern);
    auto viewStackSizeAfter = focusManager->focusViewStack_.size();
    EXPECT_EQ(viewStackSizeAfter, viewStackSizeBefore);
}

/**
 * @tc.name: ModalFocusManagerTest018
 * @tc.desc: Test FocusViewHide works normally for non-child view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup two separate pages
     * - Root
     *   - Page1
     *   - Page2
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);

    /**
     * @tc.steps: step2. Add pagePattern1 to modal stack and show pagePattern2
     */
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);
    focusManager->FocusViewShow(pagePattern2);

    /**
     * @tc.steps: step3. Call FocusViewHide for pagePattern2 (non-child of modal stack view)
     * expected: FocusViewHide works normally (stack)
     */
    auto viewStackSizeBefore = focusManager->focusViewStack_.size();
    focusManager->FocusViewHide(pagePattern2);
    auto viewStackSizeAfter = focusManager->focusViewStack_.size();
    EXPECT_EQ(viewStackSizeAfter, viewStackSizeBefore);
}

/**
 * @tc.name: ModalFocusManagerTest019
 * @tc.desc: Test FocusViewClose removes modal view from stack
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest019, TestSize.Level1)
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
     * @tc.steps: step2. Add modalPagePattern to modal stack
     */
    auto modalPageWeakPtr = AceType::WeakClaim<ModalPresentationPattern>(AceType::RawPtr(modalPagePattern));
    focusManager->modalFocusViewStack_.emplace_back(modalPageWeakPtr);
    auto modalStackSizeBefore = focusManager->modalFocusViewStack_.size();
    EXPECT_EQ(modalStackSizeBefore, SIZE_1);

    /**
     * @tc.steps: step3. Call FocusViewClose for modalPagePattern
     * expected: modal view is removed from stack
     */
    focusManager->FocusViewClose(modalPagePattern);
    auto modalStackSizeAfter = focusManager->modalFocusViewStack_.size();
    EXPECT_EQ(modalStackSizeAfter, modalStackSizeBefore - SIZE_1);
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());
}

/**
 * @tc.name: ModalFocusManagerTest021
 * @tc.desc: Test FocusViewClose does not affect modal stack when closing non-modal view
 * @tc.type: FUNC
 * @tc.author: YourName
 */
HWTEST_F(ModalFocusManagerTestNg, ModalFocusManagerTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and setup two pages
     * - Root
     *   - Page1
     *   - Page2
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    ASSERT_NE(focusManager, nullptr);

    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pageNode2 = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);

    /**
     * @tc.steps: step2. Add pagePattern1 to modal stack
     */
    auto pageWeakPtr1 = AceType::WeakClaim<PagePattern>(AceType::RawPtr(pagePattern1));
    focusManager->modalFocusViewStack_.emplace_back(pageWeakPtr1);
    auto modalStackSizeBefore = focusManager->modalFocusViewStack_.size();

    /**
     * @tc.steps: step3. Call FocusViewClose for pagePattern2 (non-modal view)
     * expected: modal stack is not modified
     */
    focusManager->FocusViewClose(pagePattern2);
    auto modalStackSizeAfter = focusManager->modalFocusViewStack_.size();
    EXPECT_EQ(modalStackSizeAfter, modalStackSizeBefore);

    /**
     * @tc.steps: step4. Verify pagePattern1 is still in modal stack
     */
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_EQ(validView, pagePattern1);
}

} // namespace OHOS::Ace::NG

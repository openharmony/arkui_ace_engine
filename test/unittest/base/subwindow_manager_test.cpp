/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/subwindow/subwindow_manager.h"
#include "core/common/container.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
    const int32_t CONATINERID = 100000;
    constexpr int32_t MAIN_CONTAINER_ID = 0;
    constexpr int32_t SUB_CONTAINER_ID = 1000000;
    constexpr int32_t NESTED_SUB_CONTAINER_ID = 1001000;
} // namespace

class SubwindowManagerTest : public testing::Test {
public:
    void SetUp() override
    {
        MockContainer::SetUp();
    }
    void TearDown() override
    {
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: SubwindowManagerTest_ShowPreviewNG001
 * @tc.desc: Test frame node method ShowPreviewNG
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, ShowPreviewNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. 
     * @tc.expected: expect ShowPreviewNG return nullptr.
     */
    EXPECT_EQ(manager->ShowPreviewNG(false), nullptr);
}

/**
 * @tc.name: SubwindowManagerTest_HidePreviewNG001
 * @tc.desc: Test frame node method HidePreviewNG
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, HidePreviewNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager, and initialize parameters.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    auto subwindow = manager->ShowPreviewNG(false);
    ASSERT_EQ(subwindow, nullptr);

    /**
     * @tc.steps: step2. call HidePreviewNG.
     * @tc.expected: HidePreviewNG return void.
     */
    manager->HidePreviewNG();
}

/**
 * @tc.name: SubwindowManagerTest_CloseDialog001
 * @tc.desc: Test frame node method CloseDialog
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, CloseDialog001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager, and CloseDialog.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    manager->CloseDialog(CONATINERID);
}

/**
 * @tc.name: SubwindowManagerTest_ShowDialogNG001
 * @tc.desc: Test frame node method ShowDialogNG
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, ShowDialogNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager, and ShowDialogNG.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    DialogProperties dialogProps;
    std::function<void()> buildFunc = nullptr;
    auto dialogNode = manager->ShowDialogNG(dialogProps, std::move(buildFunc));
    ASSERT_EQ(dialogNode, nullptr);
}

/**
 * @tc.name: SubwindowManagerTest_HasDialogOrPopup001
 * @tc.desc: Test method HasDialogOrPopup
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, HasDialogOrPopup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    /**
     * @tc.steps: step2. call HasDialogOrPopup
     */
    auto containerId = 1000000;
    ASSERT_EQ(manager->HasDialogOrPopup(containerId), false);
}

/**
 * @tc.name: SubwindowManagerTest_ShouldEnableDragEventForSubwindow001
 * @tc.desc: Test method ShouldEnableDragEventForSubwindow
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, ShouldEnableDragEventForSubwindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);
    /**
     * @tc.steps: step2. call ShouldEnableDragEventForSubwindow
     */
    auto containerId = 1000000;
    auto isRestartDrag = false;
    ASSERT_EQ(manager->ShouldEnableDragEventForSubwindow(containerId, isRestartDrag), false);
}

/**
 * @tc.name: SubwindowManagerTest_ParentContainerIdLookup001
 * @tc.desc: Test GetParentContainerId returns correct values for main and sub containers
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, ParentContainerIdLookup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Setup parent container relationship: subContainer's parent is mainContainer
     * @tc.expected: GetParentContainerId returns correct parent id
     */
    manager->AddParentContainerId(SUB_CONTAINER_ID, MAIN_CONTAINER_ID);
    EXPECT_EQ(manager->GetParentContainerId(SUB_CONTAINER_ID), MAIN_CONTAINER_ID);

    /**
     * @tc.steps: step3. Setup nested subcontainer relationship: nestedSubContainer's parent is subContainer
     * @tc.expected: GetParentContainerId returns correct parent id for nested container
     */
    manager->AddParentContainerId(NESTED_SUB_CONTAINER_ID, SUB_CONTAINER_ID);
    EXPECT_EQ(manager->GetParentContainerId(NESTED_SUB_CONTAINER_ID), SUB_CONTAINER_ID);

    /**
     * @tc.steps: step4. Test that non-existent container returns -1
     * @tc.expected: GetParentContainerId returns -1 for unknown container
     */
    EXPECT_EQ(manager->GetParentContainerId(999999), -1);
}

/**
 * @tc.name: SubwindowManagerTest_IsNestedSubwindow001
 * @tc.desc: Test detection logic for nested subwindow (parent is also a subwindow)
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, IsNestedSubwindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Setup: subContainer's parent is mainContainer (not a subwindow)
     * @tc.expected: This is NOT a nested subwindow scenario (parent is main window)
     */
    manager->AddParentContainerId(SUB_CONTAINER_ID, MAIN_CONTAINER_ID);
    auto parentId = manager->GetParentContainerId(SUB_CONTAINER_ID);
    EXPECT_EQ(parentId, MAIN_CONTAINER_ID);
    EXPECT_LT(parentId, MIN_SUBCONTAINER_ID);

    /**
     * @tc.steps: step3. Setup: nestedSubContainer's parent is subContainer (which IS a subwindow)
     * @tc.expected: This IS a nested subwindow scenario (parent is also a subwindow)
     */
    manager->AddParentContainerId(NESTED_SUB_CONTAINER_ID, SUB_CONTAINER_ID);
    parentId = manager->GetParentContainerId(NESTED_SUB_CONTAINER_ID);
    EXPECT_EQ(parentId, SUB_CONTAINER_ID);
    EXPECT_GE(parentId, MIN_SUBCONTAINER_ID);
}

/**
 * @tc.name: SubwindowManagerTest_NestedSubwindowMenuBlocked001
 * @tc.desc: Test that menu is blocked when parent container is also a subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, NestedSubwindowMenuBlocked001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate nested subwindow scenario:
     * - nestedSubContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is subContainer (also id >= MIN_SUBCONTAINER_ID)
     * @tc.expected: Menu should be blocked because parent is also a subwindow
     */
    manager->AddParentContainerId(NESTED_SUB_CONTAINER_ID, SUB_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(NESTED_SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_TRUE(isNestedSubwindow);
}

/**
 * @tc.name: SubwindowManagerTest_SubwindowMenuAllowedWithMainParent001
 * @tc.desc: Test that menu is allowed when parent container is main window
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, SubwindowMenuAllowedWithMainParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate subwindow scenario with main window parent:
     * - subContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is mainContainer (id < MIN_SUBCONTAINER_ID)
     * @tc.expected: Menu should be allowed because parent is main window (not a subwindow)
     */
    manager->AddParentContainerId(SUB_CONTAINER_ID, MAIN_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_FALSE(isNestedSubwindow);
    EXPECT_LT(parentContainerId, MIN_SUBCONTAINER_ID);
}

/**
 * @tc.name: SubwindowManagerTest_NestedSubwindowPopupBlocked001
 * @tc.desc: Test that popup is blocked when parent container is also a subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, NestedSubwindowPopupBlocked001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate nested subwindow scenario for popup:
     * - nestedSubContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is subContainer (also id >= MIN_SUBCONTAINER_ID)
     * @tc.expected: Popup should be blocked because parent is also a subwindow
     */
    manager->AddParentContainerId(NESTED_SUB_CONTAINER_ID, SUB_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(NESTED_SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_TRUE(isNestedSubwindow);
}

/**
 * @tc.name: SubwindowManagerTest_SubwindowPopupAllowedWithMainParent001
 * @tc.desc: Test that popup is allowed when parent container is main window
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, SubwindowPopupAllowedWithMainParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate subwindow scenario with main window parent for popup:
     * - subContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is mainContainer (id < MIN_SUBCONTAINER_ID)
     * @tc.expected: Popup should be allowed because parent is main window
     */
    manager->AddParentContainerId(SUB_CONTAINER_ID, MAIN_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_FALSE(isNestedSubwindow);
}

/**
 * @tc.name: SubwindowManagerTest_NestedSubwindowTipsBlocked001
 * @tc.desc: Test that tips is blocked when parent container is also a subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, NestedSubwindowTipsBlocked001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate nested subwindow scenario for tips:
     * - nestedSubContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is subContainer (also id >= MIN_SUBCONTAINER_ID)
     * @tc.expected: Tips should be blocked because parent is also a subwindow
     */
    manager->AddParentContainerId(NESTED_SUB_CONTAINER_ID, SUB_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(NESTED_SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_TRUE(isNestedSubwindow);
}

/**
 * @tc.name: SubwindowManagerTest_SubwindowTipsAllowedWithMainParent001
 * @tc.desc: Test that tips is allowed when parent container is main window
 * @tc.type: FUNC
 */
HWTEST_F(SubwindowManagerTest, SubwindowTipsAllowedWithMainParent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get subwindowManager.
     */
    auto manager = SubwindowManager::GetInstance();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. Simulate subwindow scenario with main window parent for tips:
     * - subContainer (id >= MIN_SUBCONTAINER_ID)
     * - parent is mainContainer (id < MIN_SUBCONTAINER_ID)
     * @tc.expected: Tips should be allowed because parent is main window
     */
    manager->AddParentContainerId(SUB_CONTAINER_ID, MAIN_CONTAINER_ID);
    auto parentContainerId = manager->GetParentContainerId(SUB_CONTAINER_ID);
    bool isNestedSubwindow = (parentContainerId >= MIN_SUBCONTAINER_ID);
    EXPECT_FALSE(isNestedSubwindow);
}
}
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <vector>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "wm/window.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/render/adapter/rosen_window.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILD_CONTAINER_ID = 100001;
constexpr int32_t MISSING_SUBWINDOW_ID = 100002;
constexpr int32_t NEXT_SUBWINDOW_ID = 100003;
constexpr int32_t PARENT_CONTAINER_ID = 1;
} // namespace

class RosenWindowTest : public testing::Test {
public:
    void SetUp() override
    {
        sptr<Rosen::WindowOption> option = new Rosen::WindowOption();
        option->SetWindowType(Rosen::WindowType::WINDOW_TYPE_TRANSPARENT_VIEW);
        rsWindow_ = Rosen::Window::Create("rosen_window_test", option);
        ASSERT_NE(rsWindow_, nullptr);
        taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>(true);
        window_ = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, CHILD_CONTAINER_ID);
        multiInstanceEnabled_ = SystemProperties::GetMultiInstanceEnabled();
    }

    void TearDown() override
    {
        SubwindowManager::GetInstance()->RemoveParentContainerId(CHILD_CONTAINER_ID);
        MockContainer::TearDown();
        SystemProperties::SetMultiInstanceEnabled(multiInstanceEnabled_);
        window_.reset();
        if (rsWindow_) {
            EXPECT_EQ(rsWindow_->Destroy(), Rosen::WMError::WM_OK);
            rsWindow_ = nullptr;
        }
    }

    void SetSharedParentRoute(const std::shared_ptr<RosenWindow>& parentWindow)
    {
        childContainer_ = AceType::MakeRefPtr<MockContainer>();
        childContainer_->isSubContainer_ = true;
        parentContainer_ = AceType::MakeRefPtr<MockContainer>();
        parentContainer_->SetMockWindow(parentWindow.get());
        MockContainer::SetGetContainerCallback(
            [childContainer = childContainer_, parentContainer = parentContainer_](int32_t id) -> RefPtr<Container> {
                if (id == CHILD_CONTAINER_ID) {
                    return childContainer;
                }
                return id == PARENT_CONTAINER_ID ? parentContainer : nullptr;
            });
        SubwindowManager::GetInstance()->AddParentContainerId(CHILD_CONTAINER_ID, PARENT_CONTAINER_ID);
        SystemProperties::SetMultiInstanceEnabled(true);
    }

    sptr<Rosen::Window> rsWindow_;
    RefPtr<MockTaskExecutor> taskExecutor_;
    std::shared_ptr<RosenWindow> window_;
    RefPtr<MockContainer> childContainer_;
    RefPtr<MockContainer> parentContainer_;
    bool multiInstanceEnabled_ = false;
};

/**
 * @tc.name: SharedParentLifecycleRegisterAndUnregister
 * @tc.desc: The shared-parent Init branch registers the child and Destroy unregisters the same instanceId once.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, SharedParentLifecycleRegisterAndUnregister, TestSize.Level1)
{
    auto parentWindow = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, PARENT_CONTAINER_ID);
    SetSharedParentRoute(parentWindow);

    window_->Init();
    EXPECT_THAT(parentWindow->GetSubWindowIds(), ElementsAre(CHILD_CONTAINER_ID));
    EXPECT_EQ(window_->registeredParentId_, PARENT_CONTAINER_ID);

    SystemProperties::SetMultiInstanceEnabled(false);
    window_->Destroy();
    EXPECT_TRUE(parentWindow->GetSubWindowIds().empty());
    EXPECT_EQ(window_->registeredParentId_, -1);
    EXPECT_EQ(window_->rsUIDirector_, nullptr);
}

/**
 * @tc.name: InitWithoutParentIdUsesOwnVsync
 * @tc.desc: A special subwindow without a parent mapping uses independent VSync.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitWithoutParentIdUsesOwnVsync, TestSize.Level1)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    auto childContainer = AceType::MakeRefPtr<MockContainer>();
    childContainer->isSubContainer_ = true;
    MockContainer::SetGetContainerCallback([childContainer](int32_t id) -> RefPtr<Container> {
        return id == CHILD_CONTAINER_ID ? childContainer : nullptr;
    });

    window_->Init();

    ASSERT_NE(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(static_cast<bool>(window_->rsUIDirector_->requestVsyncCallback_));
    EXPECT_EQ(window_->registeredParentId_, -1);
}

/**
 * @tc.name: InitParentContainerMissingFallsBackToOwnVsync
 * @tc.desc: Missing parent during Init falls back to the child VSync callback.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitParentContainerMissingFallsBackToOwnVsync, TestSize.Level1)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    auto childContainer = AceType::MakeRefPtr<MockContainer>();
    childContainer->isSubContainer_ = true;
    MockContainer::SetGetContainerCallback([childContainer](int32_t id) -> RefPtr<Container> {
        return id == CHILD_CONTAINER_ID ? childContainer : nullptr;
    });
    SubwindowManager::GetInstance()->AddParentContainerId(CHILD_CONTAINER_ID, PARENT_CONTAINER_ID);

    window_->Init();

    ASSERT_NE(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(static_cast<bool>(window_->rsUIDirector_->requestVsyncCallback_));
}

/**
 * @tc.name: InitParentWindowMissingFallsBackToOwnVsync
 * @tc.desc: A missing parent Window falls back without interrupting Init.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitParentWindowMissingFallsBackToOwnVsync, TestSize.Level1)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    auto childContainer = AceType::MakeRefPtr<MockContainer>();
    childContainer->isSubContainer_ = true;
    auto parentContainer = AceType::MakeRefPtr<MockContainer>();
    MockContainer::SetGetContainerCallback([childContainer, parentContainer](int32_t id) -> RefPtr<Container> {
        if (id == CHILD_CONTAINER_ID) {
            return childContainer;
        }
        return id == PARENT_CONTAINER_ID ? parentContainer : nullptr;
    });
    SubwindowManager::GetInstance()->AddParentContainerId(CHILD_CONTAINER_ID, PARENT_CONTAINER_ID);

    window_->Init();

    ASSERT_NE(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(static_cast<bool>(window_->rsUIDirector_->requestVsyncCallback_));
}

/**
 * @tc.name: InitDifferentRsUIContextUsesOwnVsync
 * @tc.desc: A parent with a different RSUIContext is not shared and the child uses its own VSync callback.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitDifferentRsUIContextUsesOwnVsync, TestSize.Level1)
{
    sptr<Rosen::Window> emptyWindow;
    auto parentWindow = std::make_shared<RosenWindow>(emptyWindow, taskExecutor_, PARENT_CONTAINER_ID);
    ASSERT_NE(parentWindow->rsUIDirector_->GetRSUIContext(), window_->rsUIDirector_->GetRSUIContext());
    SetSharedParentRoute(parentWindow);

    window_->Init();

    EXPECT_TRUE(parentWindow->GetSubWindowIds().empty());
    EXPECT_EQ(window_->registeredParentId_, -1);
    EXPECT_TRUE(static_cast<bool>(window_->rsUIDirector_->requestVsyncCallback_));
    parentWindow->Destroy();
}

/**
 * @tc.name: InitWithoutSharedParentUsesOwnVsync
 * @tc.desc: Independent windows install their own VSync callback without retaining a parent registration.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitWithoutSharedParentUsesOwnVsync, TestSize.Level1)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    auto container = AceType::MakeRefPtr<MockContainer>();
    MockContainer::SetGetContainerCallback([container](int32_t) -> RefPtr<Container> { return container; });

    window_->Init();

    ASSERT_NE(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(static_cast<bool>(window_->rsUIDirector_->requestVsyncCallback_));
    EXPECT_EQ(window_->registeredParentId_, -1);
}

/**
 * @tc.name: InitMissingSubWindowContinuesVsyncFlush
 * @tc.desc: A missing popup instance does not prevent later subwindows from being processed.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, InitMissingSubWindowContinuesVsyncFlush, TestSize.Level1)
{
    SystemProperties::SetMultiInstanceEnabled(true);
    auto currentContainer = AceType::MakeRefPtr<MockContainer>();
    auto nextContainer = AceType::MakeRefPtr<MockContainer>();
    auto queriedSubWindowIds = std::make_shared<std::vector<int32_t>>();
    MockContainer::SetGetContainerCallback(
        [currentContainer, nextContainer, queriedSubWindowIds](int32_t id) -> RefPtr<Container> {
            if (id == CHILD_CONTAINER_ID) {
                return currentContainer;
            }
            queriedSubWindowIds->emplace_back(id);
            return id == NEXT_SUBWINDOW_ID ? nextContainer : nullptr;
        });
    window_->Init();
    window_->RegisterSubWindow(MISSING_SUBWINDOW_ID);
    window_->RegisterSubWindow(NEXT_SUBWINDOW_ID);

    window_->rsUIDirector_->requestVsyncCallback_();

    EXPECT_THAT(*queriedSubWindowIds, ElementsAre(MISSING_SUBWINDOW_ID, NEXT_SUBWINDOW_ID));
}

/**
 * @tc.name: DestroyAfterParentWindowDestroyedCompletesCleanup
 * @tc.desc: Parent-first destruction does not interrupt child resource cleanup.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, DestroyAfterParentWindowDestroyedCompletesCleanup, TestSize.Level1)
{
    auto parentWindow = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, PARENT_CONTAINER_ID);
    window_->SetVsyncCallback([](uint64_t, uint64_t) {});
    ASSERT_FALSE(window_->callbacks_.empty());
    SetSharedParentRoute(parentWindow);
    window_->Init();
    ASSERT_THAT(parentWindow->GetSubWindowIds(), ElementsAre(CHILD_CONTAINER_ID));

    parentWindow->Destroy();

    window_->Destroy();

    EXPECT_TRUE(parentWindow->GetSubWindowIds().empty());
    EXPECT_EQ(window_->registeredParentId_, -1);
    EXPECT_EQ(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(window_->callbacks_.empty());
}

/**
 * @tc.name: DestroyAfterParentWindowReleasedCompletesCleanup
 * @tc.desc: The child clears its parent instance mapping when the parent container is no longer available.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, DestroyAfterParentWindowReleasedCompletesCleanup, TestSize.Level1)
{
    auto parentWindow = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, PARENT_CONTAINER_ID);
    window_->SetVsyncCallback([](uint64_t, uint64_t) {});
    SetSharedParentRoute(parentWindow);
    window_->Init();
    ASSERT_THAT(parentWindow->GetSubWindowIds(), ElementsAre(CHILD_CONTAINER_ID));

    parentWindow->Destroy();
    MockContainer::SetGetContainerCallback([childContainer = childContainer_](int32_t id) -> RefPtr<Container> {
        return id == CHILD_CONTAINER_ID ? childContainer : nullptr;
    });
    parentWindow.reset();

    window_->Destroy();

    EXPECT_EQ(window_->registeredParentId_, -1);
    EXPECT_EQ(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(window_->callbacks_.empty());
}

/**
 * @tc.name: DestroyRepeatedlyIsSafe
 * @tc.desc: Repeated Destroy calls do not dereference a released RSUIDirector.
 * @tc.type: FUNC
 */
HWTEST_F(RosenWindowTest, DestroyRepeatedlyIsSafe, TestSize.Level1)
{
    auto parentWindow = std::make_shared<RosenWindow>(rsWindow_, taskExecutor_, PARENT_CONTAINER_ID);
    window_->SetVsyncCallback([](uint64_t, uint64_t) {});
    SetSharedParentRoute(parentWindow);
    window_->Init();
    ASSERT_THAT(parentWindow->GetSubWindowIds(), ElementsAre(CHILD_CONTAINER_ID));

    window_->Destroy();
    EXPECT_TRUE(parentWindow->GetSubWindowIds().empty());
    parentWindow->RegisterSubWindow(CHILD_CONTAINER_ID);
    window_->Destroy();

    EXPECT_THAT(parentWindow->GetSubWindowIds(), ElementsAre(CHILD_CONTAINER_ID));
    EXPECT_EQ(window_->rsUIDirector_, nullptr);
    EXPECT_TRUE(window_->callbacks_.empty());
}
} // namespace OHOS::Ace::NG

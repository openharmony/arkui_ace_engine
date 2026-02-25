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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/utils/system_properties.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/common/force_split/force_split_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<ForceSplitManager> GetForceSplitManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetForceSplitManager() : nullptr;
}
} // namespace

class ForceSplitManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ForceSplitManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ForceSplitManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateIsInForceSplitMode001
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = false;
    manager->UpdateIsInForceSplitMode();
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
}

/**
 * @tc.name: UpdateIsInForceSplitMode002
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => false
 *                   if (isForceSplitEnable_) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);

    EXPECT_CALL(*container, IsMainWindow).Times(::testing::AtLeast(1)).WillRepeatedly(Return(true));
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto backupCallback = std::move(windowManager->windowGetModeCallback_);
    windowManager->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_UNDEFINED; };
    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = true;
    manager->UpdateIsInForceSplitMode();
    EXPECT_TRUE(context->IsCurrentInForceSplitMode());
    windowManager->windowGetModeCallback_ = std::move(backupCallback);
}

/**
 * @tc.name: UpdateIsInForceSplitMode003
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => false
 *                   if (isForceSplitEnable_) { => false
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode003, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = false;
    manager->UpdateIsInForceSplitMode();
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
}

/**
 * @tc.name: UpdateIsInForceSplitModeWithSplitScreen001
 * @tc.desc: Test force split mode when already in split screen mode (primary)
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitModeWithSplitScreen001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);

    // Setup: in split screen primary mode, should not enable force split
    EXPECT_CALL(*container, IsMainWindow).Times(
        ::testing::AtLeast(1)).WillRepeatedly(Return(true));
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    windowManager->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; };
    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = true;
    manager->UpdateIsInForceSplitMode();
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
}

/**
 * @tc.name: IsForceSplitEnable001
 * @tc.desc: Branch: isRouter=true, returns isForceSplitEnable_ && isRouter_
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitEnable001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isRouter_ = true;
    manager->disableNavForceSplitInternal_ = true;
    EXPECT_TRUE(manager->IsForceSplitEnable(true));

    manager->isForceSplitEnable_ = false;
    EXPECT_FALSE(manager->IsForceSplitEnable(true));
}

/**
 * @tc.name: IsForceSplitEnable002
 * @tc.desc: Branch: isRouter=false, returns isForceSplitEnable_ && !isRouter_ && !disableNavForceSplitInternal_
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitEnable002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isRouter_ = false;
    manager->disableNavForceSplitInternal_ = false;
    EXPECT_TRUE(manager->IsForceSplitEnable(false));

    manager->disableNavForceSplitInternal_ = true;
    EXPECT_FALSE(manager->IsForceSplitEnable(false));
}

/**
 * @tc.name: GetDisableNavForceSplitInternal001
 * @tc.desc: Test GetDisableNavForceSplitInternal returns correct value
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, GetDisableNavForceSplitInternal001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->disableNavForceSplitInternal_ = false;
    EXPECT_FALSE(manager->GetDisableNavForceSplitInternal());

    manager->disableNavForceSplitInternal_ = true;
    EXPECT_TRUE(manager->GetDisableNavForceSplitInternal());
}

/**
 * @tc.name: SetNavigationForceSplitEnableInternal001
 * @tc.desc: Branch: isForceSplitSupported_=false, early return
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetNavigationForceSplitEnableInternal001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = false;
    manager->disableNavForceSplitInternal_ = false;
    manager->SetNavigationForceSplitEnableInternal(true);
    EXPECT_FALSE(manager->GetDisableNavForceSplitInternal());
}

/**
 * @tc.name: SetNavigationForceSplitEnableInternal002
 * @tc.desc: Branch: isRouter_=true, early return
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetNavigationForceSplitEnableInternal002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isRouter_ = true;
    manager->disableNavForceSplitInternal_ = false;
    manager->SetNavigationForceSplitEnableInternal(true);
    EXPECT_FALSE(manager->GetDisableNavForceSplitInternal());
}

/**
 * @tc.name: SetNavigationForceSplitEnableInternal003
 * @tc.desc: Branch: disableNavForceSplitInternal_ != enableSplit, early return (no change)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetNavigationForceSplitEnableInternal003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isRouter_ = false;
    manager->disableNavForceSplitInternal_ = true;
    manager->SetNavigationForceSplitEnableInternal(true);
    EXPECT_FALSE(manager->GetDisableNavForceSplitInternal());
}

/**
 * @tc.name: SetNavigationForceSplitEnableInternal004
 * @tc.desc: Branch: Set enableSplit=false toggles disableNavForceSplitInternal_ to true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetNavigationForceSplitEnableInternal004, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isRouter_ = false;
    manager->disableNavForceSplitInternal_ = false;
    manager->SetPipelineContext(context);

    manager->SetNavigationForceSplitEnableInternal(false);
    EXPECT_TRUE(manager->GetDisableNavForceSplitInternal());
}

/**
 * @tc.name: SetForceSplitEnable001
 * @tc.desc: Branch: if (needUpdateViewport) { => false
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // Test with needUpdateViewport=false
    manager->SetForceSplitEnable(true, false);
    EXPECT_TRUE(manager->isForceSplitSupported_);
    EXPECT_TRUE(manager->isForceSplitEnable_);

    manager->SetForceSplitEnable(false, false);
    EXPECT_FALSE(manager->isForceSplitEnable_);
}

/**
 * @tc.name: SetForceSplitEnable002
 * @tc.desc: Branch: if (needUpdateViewport) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetForceSplitEnable(true, true);
    EXPECT_TRUE(manager->isForceSplitSupported_);
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.value());
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());

    // Reset for next test
    manager->delayedIsForceSplitEnable_ = std::nullopt;
    manager->surfaceChangeCallbackId_ = std::nullopt;

    manager->SetForceSplitEnable(false, true);
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.value());
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());
}

/**
 * @tc.name: RegisterSurfaceChangeCallbackIfNeeded001
 * @tc.desc: Test RegisterSurfaceChangeCallbackIfNeeded when callback already registered
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, RegisterSurfaceChangeCallbackIfNeeded001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context->surfaceChangedCallbackMap_.clear();
    manager->surfaceChangeCallbackId_ = std::nullopt;
    manager->RegisterSurfaceChangeCallbackIfNeeded();
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());
    EXPECT_EQ(context->surfaceChangedCallbackMap_.size(), 1);

    // Try to register again - should not register duplicate
    int32_t originalId = manager->surfaceChangeCallbackId_.value();
    manager->RegisterSurfaceChangeCallbackIfNeeded();
    ASSERT_TRUE(manager->surfaceChangeCallbackId_.has_value());
    EXPECT_EQ(manager->surfaceChangeCallbackId_.value(), originalId);
    EXPECT_EQ(context->surfaceChangedCallbackMap_.size(), 1);
}

/**
 * @tc.name: ChangeForceSplitModeIfNeeded001
 * @tc.desc: Test ChangeForceSplitModeIfNeeded when delayedIsForceSplitEnable_ has value
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, ChangeForceSplitModeIfNeeded001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // Set delayed force split enable
    manager->delayedIsForceSplitEnable_ = true;
    // Change force split mode
    manager->ChangeForceSplitModeIfNeeded();

    // Verify that delayed flag is cleared
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
}

/**
 * @tc.name: ChangeForceSplitModeIfNeeded002
 * @tc.desc: Test ChangeForceSplitModeIfNeeded when delayedIsForceSplitEnable_ has no value
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, ChangeForceSplitModeIfNeeded002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // Ensure delayed flag is not set
    manager->delayedIsForceSplitEnable_ = std::nullopt;

    // Change force split mode - should do nothing
    manager->ChangeForceSplitModeIfNeeded();

    // Verify that delayed flag remains null
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
}
} // namespace OHOS::Ace::NG

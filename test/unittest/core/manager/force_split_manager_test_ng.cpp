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
#include "core/components_ng/manager/force_split/force_split_manager.h"

#include "base/utils/system_properties.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/common/force_split/force_split_utils.h"

#include "core/components_ng/manager/navigation/navigation_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<ForceSplitManager> GetForceSplitManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetForceSplitManager() : nullptr;
}

void ResetForceSplitBehaviorConfig(const RefPtr<ForceSplitManager>& manager)
{
    if (!manager) {
        return;
    }
    manager->behaviorMode_ = ForceSplitBehaviorMode::NAVIGATION;
    manager->pagePairs_.clear();
    manager->transPages_.clear();
    manager->fullScreenPages_.clear();
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
    //expect false
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
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
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
    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, false);
    EXPECT_TRUE(manager->isForceSplitSupported_);
    EXPECT_TRUE(manager->isForceSplitEnable_);
    EXPECT_EQ(manager->mode_, ForceSplitMode::WIDE_SPLIT);

    manager->SetForceSplitEnable(false, ForceSplitMode::NOT_SPLIT, false);
    EXPECT_FALSE(manager->isForceSplitEnable_);
    EXPECT_EQ(manager->mode_, ForceSplitMode::NOT_SPLIT);
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

    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, true);
    EXPECT_TRUE(manager->isForceSplitSupported_);
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.value());
    EXPECT_TRUE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::WIDE_SPLIT);
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());

    // Reset for next test
    manager->delayedIsForceSplitEnable_ = std::nullopt;
    manager->delayedMode_ = std::nullopt;
    manager->surfaceChangeCallbackId_ = std::nullopt;

    manager->SetForceSplitEnable(false, ForceSplitMode::NOT_SPLIT, true);
    EXPECT_TRUE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.value());
    EXPECT_TRUE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::NOT_SPLIT);
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());
}

/**
 * @tc.name: SetForceSplitEnable003
 * @tc.desc: Branch: if (needUpdateViewport) { => false
 *                   if (delayedIsForceSplitEnable_.has_value()) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable003, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->delayedIsForceSplitEnable_ = true;
    manager->SetForceSplitEnable(false, ForceSplitMode::WIDE_SPLIT, false);
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
}

/**
 * @tc.name: SetForceSplitEnable004
 * @tc.desc: Test SetForceSplitEnable with mode override
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // Set with delay mode
    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, true);
    EXPECT_TRUE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::WIDE_SPLIT);

    // Override with new mode
    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, false);
    EXPECT_FALSE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->mode_, ForceSplitMode::SQUARE_SPLIT);
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
    manager->delayedMode_ = ForceSplitMode::WIDE_SPLIT;
    // Change force split mode
    manager->ChangeForceSplitModeIfNeeded();

    // Verify that delayed flag is cleared
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedMode_.has_value());
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

/**
 * @tc.name: IsTopFullScreenPage001
 * @tc.desc: Branch: isRouter_ = true, early return
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsTopFullScreenPage001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // isRouter_ = true
    manager->isRouter_ = true;

    //expect false
    EXPECT_FALSE(manager->IsTopFullScreenPage());
}

/**
 * @tc.name: IsTopFullScreenPage002
 * @tc.desc: Branch: isRouter_ = false, existForceSplitNav.first = false early return
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsTopFullScreenPage002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // isRouter_ = false
    manager->isRouter_ = false;

    auto navMgr = context->GetNavigationManager();
    ASSERT_NE(navMgr, nullptr);
    //existForceSplitNav.first = false
    navMgr->SetExistForceSplitNav(false, 20);

    //expect false
    EXPECT_FALSE(manager->IsTopFullScreenPage());
}

/**
 * @tc.name: AddForceSplitRatioListener001
 * @tc.desc: Test AddForceSplitRatioListener adds listener successfully
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, AddForceSplitRatioListener001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    int32_t nodeId = 100;
    bool listenerCalled = false;
    std::function<void(float)> listener = [&listenerCalled](float ratio) {
        listenerCalled = true;
    };

    manager->AddForceSplitRatioListener(nodeId, std::move(listener));
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId) != manager->forceSplitRatioListeners_.end());
}

/**
 * @tc.name: RemoveForceSplitRatioListener001
 * @tc.desc: Test RemoveForceSplitRatioListener removes listener successfully
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, RemoveForceSplitRatioListener001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    int32_t nodeId = 100;
    std::function<void(float)> listener = [](float ratio) {};

    manager->AddForceSplitRatioListener(nodeId, std::move(listener));
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId) != manager->forceSplitRatioListeners_.end());

    manager->RemoveForceSplitRatioListener(nodeId);
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId) == manager->forceSplitRatioListeners_.end());
}

/**
 * @tc.name: RemoveForceSplitRatioListener002
 * @tc.desc: Test RemoveForceSplitRatioListener with non-existent listener
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, RemoveForceSplitRatioListener002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    int32_t nodeId = 999;
    // Should not crash when removing non-existent listener
    manager->RemoveForceSplitRatioListener(nodeId);
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId) == manager->forceSplitRatioListeners_.end());
}

/**
 * @tc.name: UpdateForceSplitRatio001
 * @tc.desc: Test UpdateForceSplitRatio updates split ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->SetWideSplitRatio(0.6f);

    // Update force split ratio
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.6f);
}

/**
 * @tc.name: UpdateForceSplitRatio002
 * @tc.desc: Test UpdateForceSplitRatio with NOT_SPLIT mode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::NOT_SPLIT;
    manager->splitRatio_ = 0.7f;

    // Update force split ratio with NOT_SPLIT mode should set to default
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.5f);
}

/**
 * @tc.name: UpdateForceSplitRatio003
 * @tc.desc: Test UpdateForceSplitRatio with SQUARE_SPLIT mode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->SetSquareSplitRatio(0.55f);

    // Update force split ratio
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.55f);
}

/**
 * @tc.name: UpdateForceSplitRatio004
 * @tc.desc: Test UpdateForceSplitRatio with same ratio (no update)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->SetWideSplitRatio(0.6f);
    manager->UpdateForceSplitRatio();

    float oldRatio = manager->GetSplitRatio();
    // Call again with same ratio
    manager->UpdateForceSplitRatio();
    // Ratio should remain the same
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), oldRatio);
}

/**
 * @tc.name: CalcCurrentSplitRatio001
 * @tc.desc: Test CalcCurrentSplitRatio with NOT_SPLIT mode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::NOT_SPLIT;
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.5f);
}

/**
 * @tc.name: CalcCurrentSplitRatio002
 * @tc.desc: Test CalcCurrentSplitRatio with WIDE_SPLIT mode and ratio set
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->SetWideSplitRatio(0.6f);
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.6f);
}

/**
 * @tc.name: CalcCurrentSplitRatio003
 * @tc.desc: Test CalcCurrentSplitRatio with WIDE_SPLIT mode and no ratio set
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->wideSplitRatio_ = std::nullopt;
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.5f);
}

/**
 * @tc.name: CalcCurrentSplitRatio004
 * @tc.desc: Test CalcCurrentSplitRatio with SQUARE_SPLIT mode and ratio set
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->SetSquareSplitRatio(0.55f);
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.55f);
}

/**
 * @tc.name: CalcCurrentSplitRatio005
 * @tc.desc: Test CalcCurrentSplitRatio with SQUARE_SPLIT mode and no ratio set
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio005, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->squareSplitRatio_ = std::nullopt;
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.5f);
}

/**
 * @tc.name: IsPagePair001
 * @tc.desc: Test IsPagePair with missing from page, specific target page, and wildcard target page
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsPagePair001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    ResetForceSplitBehaviorConfig(manager);

    EXPECT_FALSE(manager->IsPagePair("home", "detail"));

    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "home", { "detail", "goods" } },
        { "list", {} },
    };
    manager->SetPagePairs(std::move(pagePairs));

    EXPECT_TRUE(manager->IsPagePair("home", "detail"));
    EXPECT_TRUE(manager->IsPagePair("home", "goods"));
    EXPECT_FALSE(manager->IsPagePair("home", "dialog"));
    EXPECT_TRUE(manager->IsPagePair("list", "anyTarget"));
    EXPECT_FALSE(manager->IsPagePair("unknown", "detail"));
}

/**
 * @tc.name: IsTransPage001
 * @tc.desc: Test IsTransPage returns whether the page is configured as transPage
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsTransPage001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    ResetForceSplitBehaviorConfig(manager);

    EXPECT_FALSE(manager->IsTransPage("dialog"));

    std::unordered_set<std::string> transPages = { "dialog", "transparent" };
    manager->SetTransPages(std::move(transPages));
    EXPECT_TRUE(manager->IsTransPage("dialog"));
    EXPECT_TRUE(manager->IsTransPage("transparent"));
    EXPECT_FALSE(manager->IsTransPage("detail"));
}

/**
 * @tc.name: CanPushPageToPrimary001
 * @tc.desc: Test CanPushPageToPrimary for navigation mode and displace mode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CanPushPageToPrimary001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    ResetForceSplitBehaviorConfig(manager);

    manager->SetBehaviorMode(ForceSplitBehaviorMode::NAVIGATION);
    EXPECT_FALSE(manager->CanPushPageToPrimary());

    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "home", { "detail" } },
    };
    manager->SetPagePairs(std::move(pagePairs));
    EXPECT_TRUE(manager->CanPushPageToPrimary());

    manager->pagePairs_.clear();
    manager->SetBehaviorMode(ForceSplitBehaviorMode::DISPLACE);
    EXPECT_TRUE(manager->CanPushPageToPrimary());
}

/**
 * @tc.name: IsTransitionShouldMovePageToPrimary001
 * @tc.desc: Test navigation mode transition check uses pagePairs and fullScreenPages
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsTransitionShouldMovePageToPrimary001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    ResetForceSplitBehaviorConfig(manager);

    manager->SetBehaviorMode(ForceSplitBehaviorMode::NAVIGATION);
    std::unordered_map<std::string, std::unordered_set<std::string>> pagePairs = {
        { "home", { "detail" } },
        { "list", {} },
    };
    manager->SetPagePairs(std::move(pagePairs));

    EXPECT_TRUE(manager->IsTransitionShouldMovePageToPrimary("home", "detail"));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("home", "dialog"));
    EXPECT_TRUE(manager->IsTransitionShouldMovePageToPrimary("list", "anyTarget"));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("unknown", "detail"));

    std::unordered_set<std::string> fullScreenPages = { "fullScreen" };
    manager->SetFullScreenPages(std::move(fullScreenPages));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("fullScreen", "detail"));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("home", "fullScreen"));
}

/**
 * @tc.name: IsTransitionShouldMovePageToPrimary002
 * @tc.desc: Test displace mode transition check excludes fullScreenPages and transPages
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsTransitionShouldMovePageToPrimary002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    ResetForceSplitBehaviorConfig(manager);

    manager->SetBehaviorMode(ForceSplitBehaviorMode::DISPLACE);
    EXPECT_TRUE(manager->IsTransitionShouldMovePageToPrimary("home", "detail"));

    std::unordered_set<std::string> transPages = { "dialog", "transparent" };
    manager->SetTransPages(std::move(transPages));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("dialog", "detail"));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("home", "transparent"));

    std::unordered_set<std::string> fullScreenPages = { "fullScreen" };
    manager->SetFullScreenPages(std::move(fullScreenPages));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("fullScreen", "detail"));
    EXPECT_FALSE(manager->IsTransitionShouldMovePageToPrimary("home", "fullScreen"));
}

/**
 * @tc.name: ForceSplitManagerConstructor001
 * @tc.desc: Test ForceSplitManager constructor initializes default values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitManagerConstructor001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<ForceSplitManager>();
    ASSERT_NE(manager, nullptr);
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.5f);
    EXPECT_EQ(manager->mode_, ForceSplitMode::NOT_SPLIT);
}

/**
 * @tc.name: ForceSplitManagerConstructor002
 * @tc.desc: Test ForceSplitManager constructor initializes ratio to defaultSplitRatio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitManagerConstructor002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<ForceSplitManager>();
    ASSERT_NE(manager, nullptr);
    constexpr float defaultSplitRatio = 0.5f;
    EXPECT_FLOAT_EQ(manager->splitRatio_, defaultSplitRatio);
}

/**
 * @tc.name: ForceSplitManagerConstructor003
 * @tc.desc: Test ForceSplitManager constructor initializes mode to NOT_SPLIT
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitManagerConstructor003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<ForceSplitManager>();
    ASSERT_NE(manager, nullptr);
    EXPECT_EQ(manager->mode_, ForceSplitMode::NOT_SPLIT);
}

/**
 * @tc.name: ForceSplitManagerConstructor004
 * @tc.desc: Test ForceSplitManager constructor initializes optional values to nullopt
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitManagerConstructor004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<ForceSplitManager>();
    ASSERT_NE(manager, nullptr);
    EXPECT_FALSE(manager->wideSplitRatio_.has_value());
    EXPECT_FALSE(manager->squareSplitRatio_.has_value());
    EXPECT_FALSE(manager->delayedMode_.has_value());
}

/**
 * @tc.name: SetForceSplitEnable005
 * @tc.desc: Test SetForceSplitEnable with different mode transitions
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable005, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, false);
    EXPECT_EQ(manager->mode_, ForceSplitMode::WIDE_SPLIT);

    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, false);
    EXPECT_EQ(manager->mode_, ForceSplitMode::SQUARE_SPLIT);

    manager->SetForceSplitEnable(true, ForceSplitMode::NOT_SPLIT, false);
    EXPECT_EQ(manager->mode_, ForceSplitMode::NOT_SPLIT);
}

/**
 * @tc.name: SetForceSplitEnable006
 * @tc.desc: Test SetForceSplitEnable with needUpdateViewport=true stores delayedMode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable006, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, true);
    EXPECT_TRUE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::WIDE_SPLIT);
    EXPECT_TRUE(manager->surfaceChangeCallbackId_.has_value());

    manager->delayedMode_ = std::nullopt;
    manager->delayedIsForceSplitEnable_ = std::nullopt;
    manager->surfaceChangeCallbackId_ = std::nullopt;

    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, true);
    EXPECT_TRUE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::SQUARE_SPLIT);
}

/**
 * @tc.name: SetForceSplitEnable007
 * @tc.desc: Test SetForceSplitEnable clears previous delayedMode when needUpdateViewport=false
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable007, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->delayedMode_ = ForceSplitMode::WIDE_SPLIT;
    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, false);
    EXPECT_FALSE(manager->delayedMode_.has_value());
    EXPECT_EQ(manager->mode_, ForceSplitMode::SQUARE_SPLIT);
}

/**
 * @tc.name: SetForceSplitEnable008
 * @tc.desc: Test SetForceSplitEnable with multiple rapid calls (override scenario)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable008, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, true);
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::WIDE_SPLIT);

    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, true);
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::SQUARE_SPLIT);

    manager->SetForceSplitEnable(false, ForceSplitMode::NOT_SPLIT, true);
    EXPECT_EQ(manager->delayedMode_.value(), ForceSplitMode::NOT_SPLIT);
}

/**
 * @tc.name: SetForceSplitEnable009
 * @tc.desc: Test SetForceSplitEnable sets isForceSplitSupported_ to true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable009, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = false;
    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, false);
    EXPECT_TRUE(manager->isForceSplitSupported_);
}

/**
 * @tc.name: SetForceSplitEnable010
 * @tc.desc: Test SetForceSplitEnable updates ratio when mode changes
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitEnable010, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetWideSplitRatio(0.6f);
    manager->SetSquareSplitRatio(0.55f);

    manager->SetForceSplitEnable(true, ForceSplitMode::WIDE_SPLIT, false);
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.6f);

    manager->SetForceSplitEnable(true, ForceSplitMode::SQUARE_SPLIT, false);
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.55f);
}

/**
 * @tc.name: SetWideSplitRatio001
 * @tc.desc: Test SetWideSplitRatio sets ratio correctly
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetWideSplitRatio001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetWideSplitRatio(0.6f);
    EXPECT_TRUE(manager->wideSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->wideSplitRatio_.value(), 0.6f);
}

/**
 * @tc.name: SetWideSplitRatio002
 * @tc.desc: Test SetWideSplitRatio with nullopt clears ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetWideSplitRatio002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetWideSplitRatio(0.6f);
    EXPECT_TRUE(manager->wideSplitRatio_.has_value());

    manager->SetWideSplitRatio(std::nullopt);
    EXPECT_FALSE(manager->wideSplitRatio_.has_value());
}

/**
 * @tc.name: SetWideSplitRatio003
 * @tc.desc: Test SetWideSplitRatio with boundary value 1/3
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetWideSplitRatio003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float minSplitRatio = 1.0f / 3.0f;
    manager->SetWideSplitRatio(minSplitRatio);
    EXPECT_TRUE(manager->wideSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->wideSplitRatio_.value(), minSplitRatio);
}

/**
 * @tc.name: SetWideSplitRatio004
 * @tc.desc: Test SetWideSplitRatio with boundary value 2/3
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetWideSplitRatio004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float maxSplitRatio = 2.0f / 3.0f;
    manager->SetWideSplitRatio(maxSplitRatio);
    EXPECT_TRUE(manager->wideSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->wideSplitRatio_.value(), maxSplitRatio);
}

/**
 * @tc.name: SetSquareSplitRatio001
 * @tc.desc: Test SetSquareSplitRatio sets ratio correctly
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSquareSplitRatio001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetSquareSplitRatio(0.55f);
    EXPECT_TRUE(manager->squareSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->squareSplitRatio_.value(), 0.55f);
}

/**
 * @tc.name: SetSquareSplitRatio002
 * @tc.desc: Test SetSquareSplitRatio with nullopt clears ratio
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSquareSplitRatio002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetSquareSplitRatio(0.55f);
    EXPECT_TRUE(manager->squareSplitRatio_.has_value());

    manager->SetSquareSplitRatio(std::nullopt);
    EXPECT_FALSE(manager->squareSplitRatio_.has_value());
}

/**
 * @tc.name: SetSquareSplitRatio003
 * @tc.desc: Test SetSquareSplitRatio with boundary value 1/3
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSquareSplitRatio003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float minSplitRatio = 1.0f / 3.0f;
    manager->SetSquareSplitRatio(minSplitRatio);
    EXPECT_TRUE(manager->squareSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->squareSplitRatio_.value(), minSplitRatio);
}

/**
 * @tc.name: SetSquareSplitRatio004
 * @tc.desc: Test SetSquareSplitRatio with boundary value 2/3
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSquareSplitRatio004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float maxSplitRatio = 2.0f / 3.0f;
    manager->SetSquareSplitRatio(maxSplitRatio);
    EXPECT_TRUE(manager->squareSplitRatio_.has_value());
    EXPECT_FLOAT_EQ(manager->squareSplitRatio_.value(), maxSplitRatio);
}

/**
 * @tc.name: GetSplitRatio001
 * @tc.desc: Test GetSplitRatio after mode changes
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, GetSplitRatio001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetWideSplitRatio(0.6f);
    manager->SetSquareSplitRatio(0.55f);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.6f);

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.55f);

    manager->mode_ = ForceSplitMode::NOT_SPLIT;
    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), 0.5f);
}

/**
 * @tc.name: AddForceSplitRatioListener002
 * @tc.desc: Test AddForceSplitRatioListener with multiple listeners
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, AddForceSplitRatioListener002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId1 = 100;
    constexpr int32_t nodeId2 = 200;
    constexpr int32_t nodeId3 = 300;

    std::function<void(float)> listener1 = [](float ratio) {};
    std::function<void(float)> listener2 = [](float ratio) {};
    std::function<void(float)> listener3 = [](float ratio) {};

    manager->AddForceSplitRatioListener(nodeId1, std::move(listener1));
    manager->AddForceSplitRatioListener(nodeId2, std::move(listener2));
    manager->AddForceSplitRatioListener(nodeId3, std::move(listener3));

    EXPECT_EQ(manager->forceSplitRatioListeners_.size(), 3);
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId1) != manager->forceSplitRatioListeners_.end());
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId2) != manager->forceSplitRatioListeners_.end());
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId3) != manager->forceSplitRatioListeners_.end());
}

/**
 * @tc.name: RemoveForceSplitRatioListener003
 * @tc.desc: Test RemoveForceSplitRatioListener removes specific listener from multiple
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, RemoveForceSplitRatioListener003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId1 = 100;
    constexpr int32_t nodeId2 = 200;
    constexpr int32_t nodeId3 = 300;

    std::function<void(float)> listener1 = [](float ratio) {};
    std::function<void(float)> listener2 = [](float ratio) {};
    std::function<void(float)> listener3 = [](float ratio) {};

    manager->AddForceSplitRatioListener(nodeId1, std::move(listener1));
    manager->AddForceSplitRatioListener(nodeId2, std::move(listener2));
    manager->AddForceSplitRatioListener(nodeId3, std::move(listener3));
    EXPECT_EQ(manager->forceSplitRatioListeners_.size(), 3);

    manager->RemoveForceSplitRatioListener(nodeId2);
    EXPECT_EQ(manager->forceSplitRatioListeners_.size(), 2);
    EXPECT_TRUE(manager->forceSplitRatioListeners_.find(nodeId2) == manager->forceSplitRatioListeners_.end());
}

/**
 * @tc.name: UpdateForceSplitRatio005
 * @tc.desc: Test UpdateForceSplitRatio triggers OnForceSplitRatioUpdate when ratio changes
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio005, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->splitRatio_ = 0.5f;
    manager->SetWideSplitRatio(0.6f);
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;

    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->splitRatio_, 0.6f);
}

/**
 * @tc.name: UpdateForceSplitRatio006
 * @tc.desc: Test UpdateForceSplitRatio does not trigger when ratio unchanged
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio006, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->splitRatio_ = 0.6f;
    manager->SetWideSplitRatio(0.6f);
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;

    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->splitRatio_, 0.6f);
}

/**
 * @tc.name: UpdateForceSplitRatio007
 * @tc.desc: Test UpdateForceSplitRatio with ratio just above default
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio007, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float expectedRatio = 0.51f;
    manager->SetWideSplitRatio(expectedRatio);
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;

    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), expectedRatio);
}

/**
 * @tc.name: UpdateForceSplitRatio008
 * @tc.desc: Test UpdateForceSplitRatio with ratio just below default
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateForceSplitRatio008, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float expectedRatio = 0.49f;
    manager->SetWideSplitRatio(expectedRatio);
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;

    manager->UpdateForceSplitRatio();
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), expectedRatio);
}

/**
 * @tc.name: CalcCurrentSplitRatio006
 * @tc.desc: Test CalcCurrentSplitRatio with WIDE_SPLIT and wideSplitRatio at boundary
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio006, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float minSplitRatio = 1.0f / 3.0f;
    constexpr float maxSplitRatio = 2.0f / 3.0f;

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->SetWideSplitRatio(minSplitRatio);
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, minSplitRatio);

    manager->SetWideSplitRatio(maxSplitRatio);
    ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, maxSplitRatio);
}

/**
 * @tc.name: CalcCurrentSplitRatio007
 * @tc.desc: Test CalcCurrentSplitRatio with SQUARE_SPLIT and squareSplitRatio at boundary
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio007, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr float minSplitRatio = 1.0f / 3.0f;
    constexpr float maxSplitRatio = 2.0f / 3.0f;

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->SetSquareSplitRatio(minSplitRatio);
    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, minSplitRatio);

    manager->SetSquareSplitRatio(maxSplitRatio);
    ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, maxSplitRatio);
}

/**
 * @tc.name: CalcCurrentSplitRatio008
 * @tc.desc: Test CalcCurrentSplitRatio with invalid mode (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio008, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->mode_ = ForceSplitMode::NOT_SPLIT;
    manager->SetWideSplitRatio(0.6f);
    manager->SetSquareSplitRatio(0.55f);

    float ratio = manager->CalcCurrentSplitRatio();
    EXPECT_FLOAT_EQ(ratio, 0.5f);
}

/**
 * @tc.name: CalcCurrentSplitRatio009
 * @tc.desc: Test CalcCurrentSplitRatio returns correct ratio for all three modes
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, CalcCurrentSplitRatio009, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetWideSplitRatio(0.6f);
    manager->SetSquareSplitRatio(0.55f);

    manager->mode_ = ForceSplitMode::NOT_SPLIT;
    EXPECT_FLOAT_EQ(manager->CalcCurrentSplitRatio(), 0.5f);

    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    EXPECT_FLOAT_EQ(manager->CalcCurrentSplitRatio(), 0.6f);

    manager->mode_ = ForceSplitMode::SQUARE_SPLIT;
    EXPECT_FLOAT_EQ(manager->CalcCurrentSplitRatio(), 0.55f);
}

/**
 * @tc.name: ChangeForceSplitModeIfNeeded003
 * @tc.desc: Test ChangeForceSplitModeIfNeeded with different delayedMode values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ChangeForceSplitModeIfNeeded003, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->delayedIsForceSplitEnable_ = true;
    manager->delayedMode_ = ForceSplitMode::SQUARE_SPLIT;
    manager->ChangeForceSplitModeIfNeeded();
    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedMode_.has_value());
}

/**
 * @tc.name: ChangeForceSplitModeIfNeeded004
 * @tc.desc: Test ChangeForceSplitModeIfNeeded when both delayed flags are set
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ChangeForceSplitModeIfNeeded004, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->delayedIsForceSplitEnable_ = true;
    manager->delayedMode_ = ForceSplitMode::WIDE_SPLIT;
    manager->ChangeForceSplitModeIfNeeded();

    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedMode_.has_value());
}

/**
 * @tc.name: ChangeForceSplitModeIfNeeded005
 * @tc.desc: Test ChangeForceSplitModeIfNeeded with isForceSplitEnable_=false
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ChangeForceSplitModeIfNeeded005, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->delayedIsForceSplitEnable_ = false;
    manager->delayedMode_ = ForceSplitMode::NOT_SPLIT;
    manager->ChangeForceSplitModeIfNeeded();

    EXPECT_FALSE(manager->delayedIsForceSplitEnable_.has_value());
    EXPECT_FALSE(manager->delayedMode_.has_value());
}

/**
 * @tc.name: OnForceSplitEnableChange001
 * @tc.desc: Test OnForceSplitEnableChange calls UpdateIsInForceSplitMode
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, OnForceSplitEnableChange001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isForceSplitSupported_ = true;
    manager->OnForceSplitEnableChange();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnForceSplitEnableChange002
 * @tc.desc: Test OnForceSplitEnableChange when force split is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, OnForceSplitEnableChange002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = false;
    manager->isForceSplitSupported_ = true;
    manager->OnForceSplitEnableChange();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetForceSplitSupported001
 * @tc.desc: Test SetForceSplitSupported sets isForceSplitSupported_
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetForceSplitSupported001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->hasSetForceSplitConfig_ = false;
    manager->SetForceSplitSupported(true);
    EXPECT_TRUE(manager->isForceSplitSupported_);
    EXPECT_TRUE(manager->hasSetForceSplitConfig_);

    manager->SetForceSplitSupported(false);
    EXPECT_FALSE(manager->isForceSplitSupported_);
}

/**
 * @tc.name: IsForceSplitSupported001
 * @tc.desc: Test IsForceSplitSupported with different isRouter values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitSupported001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isRouter_ = true;

    EXPECT_TRUE(manager->IsForceSplitSupported(true));
    EXPECT_FALSE(manager->IsForceSplitSupported(false));

    manager->isRouter_ = false;
    EXPECT_FALSE(manager->IsForceSplitSupported(true));
    EXPECT_TRUE(manager->IsForceSplitSupported(false));
}

/**
 * @tc.name: IsForceSplitEnable003
 * @tc.desc: Test IsForceSplitEnable with all conditions true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitEnable003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isRouter_ = false;
    manager->disableNavForceSplitInternal_ = false;
    EXPECT_TRUE(manager->IsForceSplitEnable(false));
}

/**
 * @tc.name: IsForceSplitEnable004
 * @tc.desc: Test IsForceSplitEnable with disableNavForceSplitInternal_ true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitEnable004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isRouter_ = false;
    manager->disableNavForceSplitInternal_ = true;
    EXPECT_FALSE(manager->IsForceSplitEnable(false));
}

/**
 * @tc.name: IsForceSplitEnable005
 * @tc.desc: Test IsForceSplitEnable with isRouter_=true
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsForceSplitEnable005, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitEnable_ = true;
    manager->isRouter_ = true;
    manager->disableNavForceSplitInternal_ = false;
    EXPECT_TRUE(manager->IsForceSplitEnable(true));
}

/**
 * @tc.name: SetIsRouter001
 * @tc.desc: Test SetIsRouter sets isRouter_ correctly
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetIsRouter001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetIsRouter(true);
    EXPECT_TRUE(manager->isRouter_);

    manager->SetIsRouter(false);
    EXPECT_FALSE(manager->isRouter_);
}

/**
 * @tc.name: IsRouterForceSplit001
 * @tc.desc: Test IsRouterForceSplit returns isRouter_
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, IsRouterForceSplit001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetIsRouter(true);
    EXPECT_TRUE(manager->IsRouterForceSplit());

    manager->SetIsRouter(false);
    EXPECT_FALSE(manager->IsRouterForceSplit());
}

/**
 * @tc.name: SetSplitDividerColor001
 * @tc.desc: Test SetSplitDividerColor sets colors correctly
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSplitDividerColor001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    Color lightColor = Color::RED;
    Color darkColor = Color::BLUE;

    manager->SetSplitDividerColor(lightColor, darkColor);
    auto colors = manager->GetSplitDividerColor();

    EXPECT_TRUE(colors.first.has_value());
    EXPECT_TRUE(colors.second.has_value());
    EXPECT_EQ(colors.first.value(), lightColor);
    EXPECT_EQ(colors.second.value(), darkColor);
}

/**
 * @tc.name: SetSplitDividerColor002
 * @tc.desc: Test SetSplitDividerColor with nullopt values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSplitDividerColor002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->SetSplitDividerColor(std::nullopt, std::nullopt);
    auto colors = manager->GetSplitDividerColor();

    EXPECT_FALSE(colors.first.has_value());
    EXPECT_FALSE(colors.second.has_value());
}

/**
 * @tc.name: SetSplitDividerColor003
 * @tc.desc: Test SetSplitDividerColor with only light color
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSplitDividerColor003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    Color lightColor = Color::RED;

    manager->SetSplitDividerColor(lightColor, std::nullopt);
    auto colors = manager->GetSplitDividerColor();

    EXPECT_TRUE(colors.first.has_value());
    EXPECT_FALSE(colors.second.has_value());
    EXPECT_EQ(colors.first.value(), lightColor);
}

/**
 * @tc.name: SetSplitDividerColor004
 * @tc.desc: Test SetSplitDividerColor with only dark color
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, SetSplitDividerColor004, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    Color darkColor = Color::BLUE;

    manager->SetSplitDividerColor(std::nullopt, darkColor);
    auto colors = manager->GetSplitDividerColor();

    EXPECT_FALSE(colors.first.has_value());
    EXPECT_TRUE(colors.second.has_value());
    EXPECT_EQ(colors.second.value(), darkColor);
}

/**
 * @tc.name: GetSplitDividerColor001
 * @tc.desc: Test GetSplitDividerColor returns correct pair
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, GetSplitDividerColor001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    Color lightColor = Color::RED;
    Color darkColor = Color::BLUE;

    manager->splitDividerColorLight_ = lightColor;
    manager->splitDividerColorDark_ = darkColor;

    auto colors = manager->GetSplitDividerColor();
    EXPECT_EQ(colors.first.value(), lightColor);
    EXPECT_EQ(colors.second.value(), darkColor);
}

/**
 * @tc.name: NotifyForceSplitStateChange001
 * @tc.desc: Test NotifyForceSplitStateChange calls registered listeners
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, NotifyForceSplitStateChange001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId = 100;
    bool listenerCalled = false;
    std::function<void()> listener = [&listenerCalled]() { listenerCalled = true; };

    manager->AddForceSplitStateListener(nodeId, std::move(listener));
    manager->NotifyForceSplitStateChange();
    EXPECT_TRUE(listenerCalled);
}

/**
 * @tc.name: NotifyForceSplitStateChange002
 * @tc.desc: Test NotifyForceSplitStateChange with no listeners
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, NotifyForceSplitStateChange002, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    manager->forceSplitListeners_.clear();
    manager->NotifyForceSplitStateChange();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: NotifyForceSplitStateChange003
 * @tc.desc: Test NotifyForceSplitStateChange with multiple listeners
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, NotifyForceSplitStateChange003, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId1 = 100;
    constexpr int32_t nodeId2 = 200;
    int32_t callCount = 0;

    std::function<void()> listener1 = [&callCount]() { callCount++; };
    std::function<void()> listener2 = [&callCount]() { callCount++; };

    manager->AddForceSplitStateListener(nodeId1, std::move(listener1));
    manager->AddForceSplitStateListener(nodeId2, std::move(listener2));
    manager->NotifyForceSplitStateChange();
    EXPECT_EQ(callCount, 2);
}

/**
 * @tc.name: AddForceSplitStateListener001
 * @tc.desc: Test AddForceSplitStateListener adds listener
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, AddForceSplitStateListener001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId = 100;
    std::function<void()> listener = []() {};

    manager->AddForceSplitStateListener(nodeId, std::move(listener));
    EXPECT_TRUE(manager->forceSplitListeners_.find(nodeId) != manager->forceSplitListeners_.end());
}

/**
 * @tc.name: RemoveForceSplitStateListener001
 * @tc.desc: Test RemoveForceSplitStateListener removes listener
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, RemoveForceSplitStateListener001, TestSize.Level1)
{
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    constexpr int32_t nodeId = 100;
    std::function<void()> listener = []() {};

    manager->AddForceSplitStateListener(nodeId, std::move(listener));
    manager->RemoveForceSplitStateListener(nodeId);
    EXPECT_TRUE(manager->forceSplitListeners_.find(nodeId) == manager->forceSplitListeners_.end());
}

/**
 * @tc.name: ForceSplitModeEnum001
 * @tc.desc: Test ForceSplitMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitModeEnum001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(ForceSplitMode::NOT_SPLIT), 0);
    EXPECT_EQ(static_cast<int32_t>(ForceSplitMode::WIDE_SPLIT), 1);
    EXPECT_EQ(static_cast<int32_t>(ForceSplitMode::SQUARE_SPLIT), 2);
}

/**
 * @tc.name: ForceSplitModeEnum002
 * @tc.desc: Test ForceSplitMode enum comparison
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitModeEnum002, TestSize.Level1)
{
    auto mode1 = ForceSplitMode::NOT_SPLIT;
    auto mode2 = ForceSplitMode::WIDE_SPLIT;
    auto mode3 = ForceSplitMode::SQUARE_SPLIT;

    EXPECT_NE(mode1, mode2);
    EXPECT_NE(mode2, mode3);
    EXPECT_NE(mode1, mode3);
}

/**
 * @tc.name: ForceSplitModeEnum003
 * @tc.desc: Test ForceSplitMode enum ordering
 * @tc.type: FUNC
 */
HWTEST_F(ForceSplitManagerTestNg, ForceSplitModeEnum003, TestSize.Level1)
{
    EXPECT_LT(static_cast<int32_t>(ForceSplitMode::NOT_SPLIT), static_cast<int32_t>(ForceSplitMode::WIDE_SPLIT));
    EXPECT_LT(static_cast<int32_t>(ForceSplitMode::WIDE_SPLIT), static_cast<int32_t>(ForceSplitMode::SQUARE_SPLIT));
}

} // namespace OHOS::Ace::NG

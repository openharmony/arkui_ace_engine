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

#include "test/unittest/core/manager/safe_area_manager_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
// ADR-7: enum type skeleton is empty; tests construct values via static_cast to represent
// enumerators that upstream strategy SRs will append.
constexpr auto STRATEGY_A = static_cast<ImmersiveStrategy>(0);
constexpr auto STRATEGY_B = static_cast<ImmersiveStrategy>(1);
} // namespace

/**
 * @tc.name: ImmersiveStrategyApplyAndQueryTest
 * @tc.desc: ApplyDefaultImmersiveStrategy records strategy; IsImmersiveStrategySet returns membership.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ImmersiveStrategyApplyAndQueryTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset();
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ STRATEGY_A });
    EXPECT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_B));
}

/**
 * @tc.name: ImmersiveStrategyMultipleTest
 * @tc.desc: Apply multiple strategies; both queryable.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ImmersiveStrategyMultipleTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset();
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ STRATEGY_A, STRATEGY_B });
    EXPECT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    EXPECT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_B));
}

/**
 * @tc.name: ImmersiveStrategyReplaceTest
 * @tc.desc: Apply is replace semantics (INV-1): later call overrides previous set.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ImmersiveStrategyReplaceTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset();
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ STRATEGY_A });
    ASSERT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ STRATEGY_B });
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    EXPECT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_B));
}

/**
 * @tc.name: ImmersiveStrategyEmptyClearsTest
 * @tc.desc: Empty array clears all applied strategies (AC-1.3).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ImmersiveStrategyEmptyClearsTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset();
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ STRATEGY_A, STRATEGY_B });
    ASSERT_TRUE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    safeAreaManager_->ApplyDefaultImmersiveStrategy({});
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_B));
}

/**
 * @tc.name: ImmersiveStrategyInitialEmptyTest
 * @tc.desc: Initial state: no strategy is set (AC-2.2).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ImmersiveStrategyInitialEmptyTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset();
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_A));
    EXPECT_FALSE(safeAreaManager_->IsImmersiveStrategySet(STRATEGY_B));
}

/**
 * @tc.name: ShouldAvoidCutoutNulloptPlusStrategyTest
 * @tc.desc: useCutout_ nullopt (switch not set) + AVOID_CUTOUT strategy -> avoid (AC-1.1).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ShouldAvoidCutoutNulloptPlusStrategyTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_.reset(); // switch not set
    EXPECT_FALSE(safeAreaManager_->GetUseCutout());
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ ImmersiveStrategy::AVOID_CUTOUT });
    EXPECT_TRUE(safeAreaManager_->GetUseCutout());
}

/**
 * @tc.name: ShouldAvoidCutoutSwitchTrueTest
 * @tc.desc: useCutout_ true (switch on) -> avoid regardless of strategy (AC-1.2).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ShouldAvoidCutoutSwitchTrueTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_ = true;
    EXPECT_TRUE(safeAreaManager_->GetUseCutout());
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ ImmersiveStrategy::AVOID_CUTOUT });
    EXPECT_TRUE(safeAreaManager_->GetUseCutout()); // switch wins, enum masked
}

/**
 * @tc.name: ShouldAvoidCutoutSwitchFalseNoEffectTest
 * @tc.desc: useCutout_ false (explicit) + AVOID_CUTOUT -> not avoid (AC-1.3).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, ShouldAvoidCutoutSwitchFalseNoEffectTest, TestSize.Level0)
{
    safeAreaManager_->useCutout_ = false;
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ ImmersiveStrategy::AVOID_CUTOUT });
    EXPECT_FALSE(safeAreaManager_->GetUseCutout()); // explicit false, enum has no effect
}

/**
 * @tc.name: AvoidFloatNavDelegateEnableTest
 * @tc.desc: AVOID_FLOAT_NAV in set -> delegate called with enable=true (AC-2.1).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, AvoidFloatNavDelegateEnableTest, TestSize.Level0)
{
    bool enableValue = false;
    safeAreaManager_->SetFloatNavPullDelegate([&enableValue](bool enable) { enableValue = enable; });
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ ImmersiveStrategy::AVOID_FLOAT_NAV });
    EXPECT_TRUE(enableValue);
}

/**
 * @tc.name: AvoidFloatNavDelegateDisableTest
 * @tc.desc: AVOID_FLOAT_NAV not in set -> delegate called with enable=false (AC-2.2).
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, AvoidFloatNavDelegateDisableTest, TestSize.Level0)
{
    bool enableValue = true;
    safeAreaManager_->SetFloatNavPullDelegate([&enableValue](bool enable) { enableValue = enable; });
    safeAreaManager_->ApplyDefaultImmersiveStrategy({ ImmersiveStrategy::AVOID_CUTOUT });
    EXPECT_FALSE(enableValue);
}
} // namespace OHOS::Ace::NG

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
#include <memory>
#include <unordered_set>
#include "core/common/container.h"
#include "immersive_strategy_ani_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/interfaces/ani/ani_api.h"
#include "frameworks/core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
namespace {
const std::unordered_set<int32_t> VALID_IMMERSIVE_STRATEGY_VALUES = {
    static_cast<int32_t>(ImmersiveStrategy::AVOID_CUTOUT),
    static_cast<int32_t>(ImmersiveStrategy::AVOID_FLOAT_NAV),
};
} // namespace

void ApplyDefaultImmersiveStrategy(const int32_t* types, int32_t count)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    // C8 gate: only effective before the first layout flow is entered.
    if (!ngPipeline || !ngPipeline->IsFirstRootLayout()) {
        return;
    }
    std::unordered_set<ImmersiveStrategy> strategies;
    if (types != nullptr && count > 0) {
        for (int32_t i = 0; i < count; i++) {
            if (VALID_IMMERSIVE_STRATEGY_VALUES.find(types[i]) != VALID_IMMERSIVE_STRATEGY_VALUES.end()) {
                strategies.insert(static_cast<ImmersiveStrategy>(types[i]));
            }
        }
    }
    ngPipeline->ApplyDefaultImmersiveStrategy(strategies);
}

const ArkUIAniImmersiveStrategyModifier* GetImmersiveStrategyAniModifier()
{
    static const ArkUIAniImmersiveStrategyModifier impl = {
        .applyDefaultImmersiveStrategy = OHOS::Ace::NG::ApplyDefaultImmersiveStrategy
    };
    return &impl;
}
} // namespace OHOS::Ace::NG

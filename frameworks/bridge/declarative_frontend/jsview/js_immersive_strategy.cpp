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

#include "frameworks/bridge/declarative_frontend/jsview/js_immersive_strategy.h"

#include <unordered_set>

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
const std::unordered_set<int32_t> VALID_IMMERSIVE_STRATEGY_VALUES = {
    static_cast<int32_t>(ImmersiveStrategy::AVOID_CUTOUT),
    static_cast<int32_t>(ImmersiveStrategy::AVOID_FLOAT_NAV),
};

void AddValidStrategy(std::unordered_set<ImmersiveStrategy>& types, int32_t value)
{
    if (VALID_IMMERSIVE_STRATEGY_VALUES.find(value) != VALID_IMMERSIVE_STRATEGY_VALUES.end()) {
        types.insert(static_cast<ImmersiveStrategy>(value));
    }
}
} // namespace

void JSImmersiveStrategy::ApplyDefaultImmersiveStrategy(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    // C8 gate: apply is only effective before the first layout flow is entered.
    if (!ngPipeline || !ngPipeline->IsFirstRootLayout()) {
        return;
    }
    std::unordered_set<ImmersiveStrategy> types;
    if (info.Length() >= 1 && info[0]->IsArray()) {
        auto array = JSRef<JSArray>::Cast(info[0]);
        for (size_t i = 0; i < array->Length(); i++) {
            auto elem = array->GetValueAt(i);
            if (elem->IsNumber()) {
                AddValidStrategy(types, elem->ToNumber<int32_t>());
            }
        }
    } else {
        for (size_t i = 0; i < info.Length(); i++) {
            if (info[i]->IsNumber()) {
                AddValidStrategy(types, info[i]->ToNumber<int32_t>());
            }
        }
    }
    ngPipeline->ApplyDefaultImmersiveStrategy(types);
}

void JSImmersiveStrategy::JSBind(BindingTarget globalObj)
{
    JSClass<JSImmersiveStrategy>::Declare("__ImmersiveStrategy__");
    JSClass<JSImmersiveStrategy>::StaticMethod(
        "applyDefaultImmersiveStrategy", &JSImmersiveStrategy::ApplyDefaultImmersiveStrategy);
    JSClass<JSImmersiveStrategy>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework

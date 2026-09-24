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

#include "load.h"
#include "log/log.h"
#include <memory>
#include <vector>
#include "immersive_strategy_module.h"

namespace OHOS::Ace::Ani {
namespace {
bool TryGetStrategyInt(ani_env* env, ani_array typesArray, ani_size index, int32_t& out)
{
    ani_ref ref;
    ani_status status = env->Object_CallMethodByName_Ref(
        typesArray, "$_get", "i:Y", &ref, static_cast<ani_int>(index));
    if (status != ANI_OK) {
        return false;
    }
    ani_int intValue = 0;
    status = env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(ref), &intValue);
    if (status != ANI_OK) {
        ani_double doubleValue = 0;
        status = env->Object_CallMethodByName_Double(
            static_cast<ani_object>(ref), "toDouble", ":d", &doubleValue);
        if (status != ANI_OK) {
            return false;
        }
        intValue = static_cast<ani_int>(doubleValue);
    }
    out = static_cast<int32_t>(intValue);
    return true;
}
}

void ApplyDefaultImmersiveStrategy(ani_env* env, [[maybe_unused]] ani_object obj, ani_array typesArray)
{
    const auto* modifier = GetNodeAniModifier();
    if (!env || !modifier) {
        return;
    }
    auto immersiveStrategyAniModifier = modifier->getImmersiveStrategyAniModifier();
    CHECK_NULL_VOID(immersiveStrategyAniModifier);

    std::vector<int32_t> types;
    if (typesArray != nullptr) {
        ani_size length = 0;
        if (env->Array_GetLength(typesArray, &length) != ANI_OK) {
            HILOGE("ApplyDefaultImmersiveStrategy Array_GetLength failed");
            return;
        }
        for (ani_size i = 0; i < length; i++) {
            int32_t value = 0;
            if (TryGetStrategyInt(env, typesArray, i, value)) {
                types.push_back(value);
            }
        }
    }
    immersiveStrategyAniModifier->applyDefaultImmersiveStrategy(
        types.data(), static_cast<int32_t>(types.size()));
}

} // namespace OHOS::Ace::Ani

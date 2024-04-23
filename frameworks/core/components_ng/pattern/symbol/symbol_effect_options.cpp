/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/symbol/symbol_effect_options.h"

namespace OHOS::Ace::NG {

SymbolEffectOptions::SymbolEffectOptions(SymbolEffectType effectType)
{
    effectType_ = effectType;
}

bool SymbolEffectOptions::operator==(const SymbolEffectOptions& other) const
{
    if (effectType_ != other.GetEffectType()) {
        return false;
    }
    if (scopeType_ != other.GetScopeType()) {
        return false;
    }
    if (commonSubType_ != other.GetCommonSubType()) {
        return false;
    }
    if (fillStyle_ != other.GetFillStyle()) {
        return false;
    }
    if (repeatCount_ != other.GetRepeatCount()) {
        return false;
    }
    if (isActive_ != other.GetIsActive()) {
        return false;
    }
    if (isActive_ != other.GetIsTxtActive()) {
        return false;
    }
    if (isActive_ != other.GetTriggerNum()) {
        return false;
    }
    return true;
}

bool SymbolEffectOptions::operator!=(const SymbolEffectOptions& other) const
{
    return !(operator==(other));
}

} // namespace OHOS::Ace::NG

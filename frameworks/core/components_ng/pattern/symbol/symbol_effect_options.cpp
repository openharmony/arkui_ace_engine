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
    return effectType_ == other.effectType_ && scopeType_ == other.scopeType_ &&
           commonSubType_ == other.commonSubType_ && fillStyle_ == other.fillStyle_ &&
           repeatCount_ == other.repeatCount_ && isActive_ == other.isActive_ && isTxtActive_ == other.isTxtActive_ &&
           triggerNum_ == other.triggerNum_;
}

bool SymbolEffectOptions::operator!=(const SymbolEffectOptions& other) const
{
    return !(operator==(other));
}

std::string SymbolEffectOptions::ToString() const
{
    auto json = JsonUtil::Create(true);
    json->Put("effectType", static_cast<int32_t>(effectType_));
    json->Put("scopeType", static_cast<int32_t>(scopeType_.value_or(ScopeType::LAYER)));
    json->Put("commonSubType", static_cast<int32_t>(commonSubType_.value_or(CommonSubType::DOWN)));
    json->Put("fillStyle", static_cast<int32_t>(fillStyle_.value_or(FillStyle::CUMULATIVE)));
    json->Put("isTxtActive", isTxtActive_);
    if (triggerNum_.has_value()) {
        json->Put("triggerNum", triggerNum_.value());
    }
    if (isTriggerNumChanged_.has_value()) {
        json->Put("isTriggerNumChanged", isTriggerNumChanged_.value());
    }
    if (isActive_.has_value()) {
        json->Put("isActive", isActive_.value());
    }
    return json->ToString();
}

} // namespace OHOS::Ace::NG

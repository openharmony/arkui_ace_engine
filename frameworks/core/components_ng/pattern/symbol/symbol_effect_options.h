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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_EFFECT_OPTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_EFFECT_OPTIONS_H

#include <optional>
#include <string>

#include "base/json/json_util.h"
#include "core/components_ng/pattern/symbol/constants.h"

namespace OHOS::Ace::NG {
class SymbolEffectOptions {
public:
    explicit SymbolEffectOptions(SymbolEffectType effectType);

    SymbolEffectOptions(SymbolEffectType effectType, ScopeType scopeType)
        : effectType_(effectType), scopeType_(scopeType)
    {}

    SymbolEffectOptions(SymbolEffectType effectType, ScopeType scopeType, CommonSubType commonSubType)
        : effectType_(effectType), scopeType_(scopeType), commonSubType_(commonSubType)
    {}

    SymbolEffectOptions(SymbolEffectType effectType, FillStyle fillStyle)
        : effectType_(effectType), fillStyle_(fillStyle)
    {}

    SymbolEffectOptions() = default;
    ~SymbolEffectOptions() = default;

    void SetEffectType(SymbolEffectType effectType)
    {
        effectType_ = effectType;
    }

    void SetScopeType(ScopeType scopeType)
    {
        scopeType_ = scopeType;
    }

    void SetCommonSubType(CommonSubType commonSubType)
    {
        commonSubType_ = commonSubType;
    }

    void SetFillStyle(FillStyle fillStyle)
    {
        fillStyle_ = fillStyle;
    }

    void SetRepeatCount(int32_t repeatCount)
    {
        repeatCount_ = repeatCount;
    }

    void SetIsActive(bool isActive)
    {
        isActive_ = isActive;
    }

    SymbolEffectType GetEffectType() const
    {
        return effectType_;
    }

    std::optional<ScopeType> GetScopeType() const
    {
        return scopeType_;
    }

    std::optional<CommonSubType> GetCommonSubType() const
    {
        return commonSubType_;
    }

    std::optional<FillStyle> GetFillStyle() const
    {
        return fillStyle_;
    }

    int32_t GetRepeatCount() const
    {
        return repeatCount_;
    }

    bool GetIsActive() const
    {
        return isActive_;
    }

    bool operator==(const SymbolEffectOptions& info) const;
    bool operator!=(const SymbolEffectOptions& info) const;

    std::string ToString() const
    {
        auto json = JsonUtil::Create(true);
        json->Put("effectType", static_cast<int32_t>(effectType_));
        json->Put("scopeType", static_cast<int32_t>(scopeType_.value_or(ScopeType::LAYER)));
        json->Put("commonSubType", static_cast<int32_t>(commonSubType_.value_or(CommonSubType::DOWN)));
        json->Put("fillStyle", static_cast<int32_t>(fillStyle_.value_or(FillStyle::CUMULATIVE)));
        json->Put("repeatCount", repeatCount_);
        json->Put("isActive", isActive_);
        return json->ToString();
    }

private:
    SymbolEffectType effectType_ = SymbolEffectType::NONE;
    std::optional<ScopeType> scopeType_;
    std::optional<CommonSubType> commonSubType_;
    std::optional<FillStyle> fillStyle_;
    int32_t repeatCount_ = 1;
    bool isActive_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_SOURCE_INFO_H

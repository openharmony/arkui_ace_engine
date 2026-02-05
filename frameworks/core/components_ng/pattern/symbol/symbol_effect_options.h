/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
class ACE_FORCE_EXPORT SymbolEffectOptions {
public:
    explicit SymbolEffectOptions(SymbolEffectType effectType);

    SymbolEffectOptions(SymbolEffectType effectType, Ace::ScopeType scopeType);

    SymbolEffectOptions(SymbolEffectType effectType, Ace::ScopeType scopeType, CommonSubType commonSubType);

    SymbolEffectOptions(SymbolEffectType effectType, FillStyle fillStyle);

    SymbolEffectOptions();
    ~SymbolEffectOptions();

    void SetEffectType(SymbolEffectType effectType);

    void SetScopeType(Ace::ScopeType scopeType);

    void SetCommonSubType(CommonSubType commonSubType);

    void SetFillStyle(FillStyle fillStyle);

    void SetRepeatCount(int32_t repeatCount);

    void SetIsActive(std::optional<bool> isActive);

    void Reset();

    void SetTriggerNum(int32_t triggerNum);

    void UpdateFlags(const SymbolEffectOptions& lastOptions);

    void SetIsTxtActive(bool isTxtActive);

    void SetIsTxtActiveSource(int16_t isTxtActiveSource);

    const SymbolEffectType& GetEffectType() const;

    const std::optional<Ace::ScopeType>& GetScopeType() const;

    const std::optional<CommonSubType>& GetCommonSubType() const;

    const std::optional<FillStyle>& GetFillStyle() const;

    int32_t GetRepeatCount() const;

    const std::optional<bool>& GetIsActive() const;

    bool GetIsTxtActive() const;

    const std::optional<bool>& IsTriggerChanged() const;

    const std::optional<int32_t>& GetTriggerNum() const;

    bool operator==(const SymbolEffectOptions& info) const;
    bool operator!=(const SymbolEffectOptions& info) const;

    std::string ToString() const;

private:
    SymbolEffectType effectType_ = SymbolEffectType::NONE;
    std::optional<Ace::ScopeType> scopeType_;
    std::optional<CommonSubType> commonSubType_;
    std::optional<FillStyle> fillStyle_;
    std::optional<bool> isActive_;
    std::optional<int32_t> triggerNum_;
    std::optional<bool> isTriggerNumChanged_;
    bool isTxtActive_ = false;
    int16_t isTxtActiveSource_ = -1; // -1:未设置开关   0:isActive   1:用户js接口的Trigger
    int32_t repeatCount_ = 1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SYMBOL_SYMBOL_SOURCE_INFO_H

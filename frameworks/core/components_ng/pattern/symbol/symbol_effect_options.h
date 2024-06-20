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

    void SetIsActive(std::optional<bool> isActive)
    {
        isActive_ = isActive;
    }

    void Reset()
    {
        if (isTxtActiveSource_ == 1) {
            isTxtActive_ = false;
        }
    }

    void SetTriggerNum(int32_t triggerNum)
    {
        triggerNum_ = triggerNum;
    }

    void UpdateFlags(const SymbolEffectOptions& lastOptions)
    {
        bool isCurTriggerSetted = triggerNum_.has_value();
        bool isTriggerHasSetted = lastOptions.GetTriggerNum().has_value();
        bool isCurActiveSetted = isActive_.has_value();

        if (isCurTriggerSetted) {
            // 本次设置了triggerValue, 比较两次的TriggerNum值
            isTxtActiveSource_ = 1;
            if (!isTriggerHasSetted) {
                // 上次无值
                if (triggerNum_ == -1) {
                    isTxtActive_ = false;
                } else {
                    isTxtActive_ = true;
                }
            } else {
                // 上次有值
                int32_t lastTriggerNum = lastOptions.GetTriggerNum().value();
                int32_t curTriggerNum = triggerNum_.value();
                isTxtActive_ = curTriggerNum != lastTriggerNum;
            }
        } else if (isTriggerHasSetted) {
            // 历史设置过triggerValue,本次没设置triggerValue（两个接口混用,isActive写在下面场景）
            isTxtActiveSource_ = 1;
            isTxtActive_ = lastOptions.GetIsTxtActive();
            triggerNum_ = lastOptions.GetTriggerNum().value();
        } else if (isCurActiveSetted) {
            // 只设isActive => isActive
            isTxtActiveSource_ = 0;
            isTxtActive_ = isActive_.value();
        } else {
            // isActive && triggerValue都未设置 => false
            isTxtActiveSource_ = -1;
            isTxtActive_ = false;
        }
    }

    void SetIsTxtActive(bool isTxtActive)
    {
        isTxtActive_ = isTxtActive;
    }

    void SetIsTxtActiveSource(int16_t isTxtActiveSource)
    {
        isTxtActiveSource_ = isTxtActiveSource;
    }

    const SymbolEffectType& GetEffectType() const
    {
        return effectType_;
    }

    const std::optional<ScopeType>& GetScopeType() const
    {
        return scopeType_;
    }

    const std::optional<CommonSubType>& GetCommonSubType() const
    {
        return commonSubType_;
    }

    const std::optional<FillStyle>& GetFillStyle() const
    {
        return fillStyle_;
    }

    int32_t GetRepeatCount() const
    {
        return repeatCount_;
    }

    const std::optional<bool>& GetIsActive() const
    {
        return isActive_;
    }

    bool GetIsTxtActive() const
    {
        return isTxtActive_;
    }

    const std::optional<bool>& IsTriggerChanged() const
    {
        return isTriggerNumChanged_;
    }

    const std::optional<int32_t>& GetTriggerNum() const
    {
        return triggerNum_;
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

private:
    SymbolEffectType effectType_ = SymbolEffectType::NONE;
    std::optional<ScopeType> scopeType_;
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

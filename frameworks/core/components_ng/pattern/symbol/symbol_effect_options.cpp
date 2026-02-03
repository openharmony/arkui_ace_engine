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

#include "core/components_ng/pattern/symbol/symbol_effect_options.h"

namespace OHOS::Ace::NG {

SymbolEffectOptions::SymbolEffectOptions() = default;

SymbolEffectOptions::~SymbolEffectOptions() = default;

SymbolEffectOptions::SymbolEffectOptions(SymbolEffectType effectType)
    : effectType_(effectType)
{}

SymbolEffectOptions::SymbolEffectOptions(SymbolEffectType effectType, Ace::ScopeType scopeType)
    : effectType_(effectType), scopeType_(scopeType)
{}

SymbolEffectOptions::SymbolEffectOptions(
    SymbolEffectType effectType,
    Ace::ScopeType scopeType,
    CommonSubType commonSubType)
    : effectType_(effectType), scopeType_(scopeType), commonSubType_(commonSubType)
{}

SymbolEffectOptions::SymbolEffectOptions(SymbolEffectType effectType, FillStyle fillStyle)
    : effectType_(effectType), fillStyle_(fillStyle)
{}

void SymbolEffectOptions::SetEffectType(SymbolEffectType effectType)
{
    effectType_ = effectType;
}

void SymbolEffectOptions::SetScopeType(Ace::ScopeType scopeType)
{
    scopeType_ = scopeType;
}

void SymbolEffectOptions::SetCommonSubType(CommonSubType commonSubType)
{
    commonSubType_ = commonSubType;
}

void SymbolEffectOptions::SetFillStyle(FillStyle fillStyle)
{
    fillStyle_ = fillStyle;
}

void SymbolEffectOptions::SetRepeatCount(int32_t repeatCount)
{
    repeatCount_ = repeatCount;
}

void SymbolEffectOptions::SetIsActive(std::optional<bool> isActive)
{
    isActive_ = isActive;
}

void SymbolEffectOptions::Reset()
{
    if (isTxtActiveSource_ == 1) {
        isTxtActive_ = false;
    }
}

void SymbolEffectOptions::SetTriggerNum(int32_t triggerNum)
{
    triggerNum_ = triggerNum;
}

void SymbolEffectOptions::UpdateFlags(const SymbolEffectOptions& lastOptions)
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

void SymbolEffectOptions::SetIsTxtActive(bool isTxtActive)
{
    isTxtActive_ = isTxtActive;
}

void SymbolEffectOptions::SetIsTxtActiveSource(int16_t isTxtActiveSource)
{
    isTxtActiveSource_ = isTxtActiveSource;
}

const SymbolEffectType& SymbolEffectOptions::GetEffectType() const
{
    return effectType_;
}

const std::optional<Ace::ScopeType>& SymbolEffectOptions::GetScopeType() const
{
    return scopeType_;
}

const std::optional<CommonSubType>& SymbolEffectOptions::GetCommonSubType() const
{
    return commonSubType_;
}

const std::optional<FillStyle>& SymbolEffectOptions::GetFillStyle() const
{
    return fillStyle_;
}

int32_t SymbolEffectOptions::GetRepeatCount() const
{
    return repeatCount_;
}

const std::optional<bool>& SymbolEffectOptions::GetIsActive() const
{
    return isActive_;
}

bool SymbolEffectOptions::GetIsTxtActive() const
{
    return isTxtActive_;
}

const std::optional<bool>& SymbolEffectOptions::IsTriggerChanged() const
{
    return isTriggerNumChanged_;
}

const std::optional<int32_t>& SymbolEffectOptions::GetTriggerNum() const
{
    return triggerNum_;
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

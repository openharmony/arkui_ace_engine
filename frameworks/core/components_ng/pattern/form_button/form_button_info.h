/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_INFO_H

#include "base/geometry/ng/rect_t.h"
#include "base/json/json_util.h"

namespace OHOS::Ace::NG {
class FormButtonInfo final {
public:
    FormButtonInfo() = default;
    ~FormButtonInfo() = default;

    void SetAction(const std::string& action)
    {
        action_ = action;
    }

    std::string GetAction() const
    {
        return action_;
    }

    void SetBundleName(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    std::string GetBundleName() const
    {
        return bundleName_;
    }

    void SetAbilityName(const std::string& abilityName)
    {
        abilityName_ = abilityName;
    }

    std::string GetAbilityName() const
    {
        return abilityName_;
    }

    std::string GetModuleName() const
    {
        return moduleName_;
    }

    void SetModuleName(const std::string& moduleName)
    {
        moduleName_ = moduleName;
    }

    int32_t GetDimension() const
    {
        return dimension_;
    }

    void SetDimension(const int32_t& dimension)
    {
        dimension_ = dimension;
    }

    std::string GetCardName() const
    {
        return cardName_;
    }

    void SetCardName(const std::string& cardName)
    {
        cardName_ = cardName;
    }

    void SetFomButtonRect(const RectF& rect)
    {
        formButtonRect_ = rect;
    }

    std::string ToString()
    {
        auto json = JsonUtil::Create(true);
        json->Put("action", action_.c_str());
        json->Put("formButtonRect", formButtonRect_.ToString().c_str());
        return json->ToString();
    }

private:
    RectF formButtonRect_;
    std::string action_;
    std::string bundleName_;
    std::string abilityName_;
    std::string moduleName_;
    std::string cardName_;
    int32_t dimension_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_INFO_H
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_PATTERN_H

#include "core/components_ng/pattern/form_button/form_button_info.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::NG {

class FormButtonPattern : public StackPattern {
    DECLARE_ACE_TYPE(FormButtonPattern, Pattern);

public:
    FormButtonPattern();
    ~FormButtonPattern() override;

    void SetAction(const std::string& action)
    {
        formButtonInfo_.SetAction(action);
    }

    std::string GetAction() const
    {
        return formButtonInfo_.GetAction();
    }

    void SetBundleName(const std::string& bundleName)
    {
        formButtonInfo_.SetBundleName(bundleName);
    }

    std::string GetBundleName() const
    {
        return formButtonInfo_.GetBundleName();
    }

    void SetAbilityName(const std::string& abilityName)
    {
        formButtonInfo_.SetAbilityName(abilityName);
    }

    std::string GetAbilityName() const
    {
        return formButtonInfo_.GetAbilityName();
    }
    std::string GetModuleName() const
    {
        return formButtonInfo_.GetModuleName();
    }

    void SetModuleName(const std::string& moduleName)
    {
        formButtonInfo_.SetModuleName(moduleName);
    }

    int32_t GetDimension() const
    {
        return formButtonInfo_.GetDimension();
    }

    void SetDimension(const int32_t& dimension)
    {
        formButtonInfo_.SetDimension(dimension);
    }

    std::string GetCardName() const
    {
        return formButtonInfo_.GetCardName();
    }

    void SetCardName(const std::string& cardName)
    {
        formButtonInfo_.SetCardName(cardName);
    }

private:
    void OnAttachToFrameNode() override;
    void InitClickEvent();

    FormButtonInfo formButtonInfo_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_BUTTON_PATTERN_H
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkbox/toggle_checkbox_accessibility_property.h"

namespace OHOS::Ace::NG {

class ToggleCheckBoxPattern : public CheckBoxPattern {
    DECLARE_ACE_TYPE(ToggleCheckBoxPattern, CheckBoxPattern);

public:
    ToggleCheckBoxPattern() = default;
    ~ToggleCheckBoxPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ToggleCheckBoxAccessibilityProperty>();
    }

    static bool ParseCommand(const std::string& command, bool& isOn)
    {
        auto json = JsonUtil::ParseJsonString(command);
        CHECK_NE_RETURN(json->IsObject(), true, false);
        auto cmdType = json->GetString("cmd");
        CHECK_NE_RETURN(cmdType, "SetToggleIsOn", false);
        auto paramJson = json->GetValue("params");
        CHECK_NE_RETURN(paramJson->IsObject(), true, false);
        auto isOnJson = paramJson->GetValue("isOn");
        CHECK_NE_RETURN(isOnJson->IsBool(), true, false);
        isOn = isOnJson->GetBool();
        return true;
    }

    int32_t OnInjectionEvent(const std::string& command) override
    {
        bool isOn = false;
        auto ret = ParseCommand(command, isOn);
        CHECK_EQUAL_RETURN(ret, false, RET_FAILED);
        SetCheckBoxSelect(isOn);
        return RET_SUCCESS;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ToggleCheckBoxPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H

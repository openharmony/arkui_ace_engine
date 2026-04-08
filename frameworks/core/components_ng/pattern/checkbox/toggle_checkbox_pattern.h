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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkbox/toggle_checkbox_accessibility_property.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
namespace {
const std::string INJECTION_CMD_FORMAT_ERROR = "Invalid injection command format.";
const std::string COMPONENT_IN_READONLY = "The component is in read-only state.";
} // namespace

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

    bool ParseCommand(const std::string& command, bool& isOn)
    {
        auto jsonObj = JsonUtil::ParseJsonString(command);
        if (!jsonObj->IsValid() || !jsonObj->IsObject()) {
            ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
            return false;
        }
        auto cmdObj = jsonObj->GetValue("cmd");
        if (!cmdObj->IsValid() || !cmdObj->IsString()) {
            ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
            return false;
        }
        auto cmdType = cmdObj->GetString();
        if (cmdType != "onToggleChange") {
            ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
            return false;
        }
        auto paramJson = jsonObj->GetValue("params");
        if (!paramJson->IsValid() || !paramJson->IsObject()) {
            ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
            return false;
        }
        auto isOnJson = paramJson->GetValue("isOn");
        if (!isOnJson->IsValid() || !isOnJson->IsBool()) {
            ReportInjectionResult(false, INJECTION_CMD_FORMAT_ERROR);
            return false;
        }
        isOn = isOnJson->GetBool();
        return true;
    }

    int32_t OnInjectionEvent(const std::string& command) override
    {
        bool isOn = false;
        auto ret = ParseCommand(command, isOn);
        CHECK_EQUAL_RETURN(ret, false, RET_FAILED);
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, RET_FAILED);
        if (!eventHub->IsEnabled()) {
            ReportInjectionResult(false, COMPONENT_IN_READONLY);
            return RET_FAILED;
        }
        SetCheckBoxSelect(isOn);
        ReportInjectionResult(true, "");
        return RET_SUCCESS;
    }

    bool ReportInjectionResult(bool isSuccess, const std::string& reason)
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto nodeId = host->GetId();
        CHECK_NULL_RETURN(nodeId, false);
        auto result = JsonUtil::Create();
        CHECK_NULL_RETURN(result, false);
        result->Put("nodeId", nodeId);
        result->Put("event", "onToggleChange");
        result->Put("result", isSuccess ? "success" : "failed");
        result->Put("reason", reason.c_str());
        UiSessionManager::GetInstance()->ReportComponentChangeEvent(
            "ToggleResult", result->ToString(), ComponentEventType::COMPONENT_EVENT_SELECT);
        return true;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ToggleCheckBoxPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_TOGGLE_CHECKBOX_PATTERN_H

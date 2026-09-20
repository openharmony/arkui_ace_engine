/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/form_utils_impl.h"

#include "form_mgr.h"
#include "form_constants.h"

#include "insight_intent/insight_intent_execute_param.h"
#include "want_params.h"
#include "want_params_wrapper.h"

#include "bool_wrapper.h"
#include "int_wrapper.h"
#include "string_wrapper.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/log.h"

namespace OHOS::Ace {
namespace {
    constexpr int32_t ERR_OK = 0;

    // postCardAction 可选透传意图目标三元组（bundleName/moduleName/abilityName），
    // 塞入 want element（FMS/AMS 的 GenerateFromWant 从 element 解析三元组）；
    // 全缺省时不设置 element，任一字段缺失由 FMS 按 FormRecord 逐项补齐。
    void SetIntentTargetElement(const std::unique_ptr<JsonValue>& eventAction, AAFwk::Want& want)
    {
        const auto bundleName = eventAction->GetValue("bundleName")->GetString();
        const auto moduleName = eventAction->GetValue("moduleName")->GetString();
        const auto abilityName = eventAction->GetValue("abilityName")->GetString();
        if (bundleName.empty() && moduleName.empty() && abilityName.empty()) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_FORM,
            "InsightIntentEvent passthrough target, bundleName: %{public}s, moduleName: %{public}s, "
            "abilityName: %{public}s", bundleName.c_str(), moduleName.c_str(), abilityName.c_str());
        AppExecFwk::ElementName element;
        element.SetBundleName(bundleName);
        element.SetModuleName(moduleName);
        element.SetAbilityName(abilityName);
        want.SetElement(element);
    }

    // postCardAction 可选透传 executeMode（取值见 AppExecFwk::ExecuteMode，0-3），
    // 作为 params 内保留键（与 intentParams 并列）解析；缺省回退前台执行，
    // 传入非法值（非数字/超范围）返回 false 由调用方拒绝。
    bool GetIntentExecuteMode(const std::unique_ptr<JsonValue>& params, int32_t& executeMode)
    {
        executeMode = static_cast<int32_t>(AppExecFwk::ExecuteMode::UI_ABILITY_FOREGROUND);
        if (!params->IsValid()) {
            return true;
        }
        auto executeModeJson = params->GetValue("executeMode");
        if (!executeModeJson->IsValid()) {
            return true;
        }
        if (!executeModeJson->IsNumber()) {
            TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent executeMode is not a number");
            return false;
        }
        executeMode = executeModeJson->GetInt();
        if (executeMode < static_cast<int32_t>(AppExecFwk::ExecuteMode::UI_ABILITY_FOREGROUND)
            || executeMode > static_cast<int32_t>(AppExecFwk::ExecuteMode::SERVICE_EXTENSION_ABILITY)) {
            TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent executeMode out of range: %{public}d", executeMode);
            return false;
        }
        return true;
    }

    // 将单个 intentParams 子项按类型写入 WantParams：
    // string/number/bool 直接映射；null/object/array 降级为空字符串
    // （GetString 对 object/array 返回 ""），object/array 加告警暴露数据丢失。
    void SetWantParamByType(const std::unique_ptr<JsonValue>& child, AAFwk::WantParams& wantParams)
    {
        auto key = child->GetKey();
        // WantParams::SetParam 仅接受 IInterface 派生类型，需用 AAFwk 包装类 Box() 转换。
        if (child->IsString()) {
            wantParams.SetParam(key, AAFwk::String::Box(child->GetString()));
        } else if (child->IsNumber()) {
            wantParams.SetParam(key, AAFwk::Integer::Box(child->GetInt()));
        } else if (child->IsBool()) {
            wantParams.SetParam(key, AAFwk::Boolean::Box(child->GetBool()));
        } else {
            if (child->IsObject() || child->IsArray()) {
                TAG_LOGW(AceLogTag::ACE_FORM,
                    "InsightIntentEvent intentParams contains object/array value, "
                    "downgrade to empty string, key: %{public}s", key.c_str());
            }
            wantParams.SetParam(key, AAFwk::String::Box(child->GetString()));
        }
    }

    // 遍历 params.intentParams（业务意图参数信封），将各键值按类型写入 wantParams；
    // params 或 intentParams 缺失时保持 wantParams 为空。
    void ParseIntentParams(const std::unique_ptr<JsonValue>& params, AAFwk::WantParams& wantParams)
    {
        if (!params->IsValid()) {
            return;
        }
        auto intentParams = params->GetValue("intentParams");
        if (!intentParams->IsValid()) {
            return;
        }
        auto child = intentParams->GetChild();
        while (child->IsValid()) {
            SetWantParamByType(child, wantParams);
            child = child->GetNext();
        }
    }

    void ParseRouterEventParams(const std::unique_ptr<JsonValue>& params, AAFwk::Want& want)
    {
        if (params->IsValid()) {
            auto child = params->GetChild();
            while (child->IsValid()) {
                auto key = child->GetKey();
                if (child->IsNull()) {
                    want.SetParam(key, std::string());
                } else if (child->IsString()) {
                    want.SetParam(key, child->GetString());
                } else if (child->IsNumber()) {
                    want.SetParam(key, child->GetInt());
                } else {
                    want.SetParam(key, std::string());
                }
                child = child->GetNext();
            }
        }
        want.SetParam("params", params->ToString());
    }

    bool SetRouterEventElement(
        const std::unique_ptr<JsonValue>& eventAction, const std::string& defaultBundleName, AAFwk::Want& want)
    {
        auto uri = eventAction->GetValue("uri");
        if (uri->IsValid()) {
            want.SetUri(uri->GetString());
        }
        auto bundle = eventAction->GetValue("bundleName")->GetString();
        auto ability = eventAction->GetValue("abilityName")->GetString();
        if (!ability.empty()) {
            if (bundle.empty()) {
                bundle = defaultBundleName;
            }
            want.SetElementName(bundle, ability);
        } else if (uri->IsValid()) {
            if (!bundle.empty()) {
                want.SetElementName(bundle, std::string());
            }
        } else {
            return false;
        }
        return true;
    }
}
int32_t FormUtilsImpl::RouterEvent(
    const int64_t formId, const std::string& action, const int32_t containerId, const std::string& defaultBundleName)
{
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto ace_container = AceType::DynamicCast<Platform::AceContainer>(container);
    auto token_ = ace_container->GetToken();
    CHECK_NULL_RETURN(token_, -1);
    AAFwk::Want want;
    auto eventAction = JsonUtil::ParseJsonString(action);
    ParseRouterEventParams(eventAction->GetValue("params"), want);
    AddWantFreeInstallFlagForRouterEvent(eventAction->GetValue("flag"), want);
    auto enableRouteSecondPage = eventAction->GetValue("enableRouteSecondePage");
    bool isRouteSecondPageEnabled = enableRouteSecondPage->IsValid()
        && enableRouteSecondPage->IsBool() && enableRouteSecondPage->GetBool();
    want.SetParam(AppExecFwk::Constants::PARAM_ENABLE_ROUTE_SECOND_PAGE, isRouteSecondPageEnabled);
    if (!SetRouterEventElement(eventAction, defaultBundleName, want)) {
        return -1;
    }

    return AppExecFwk::FormMgr::GetInstance().RouterEvent(formId, want, token_);
}

void FormUtilsImpl::AddWantFreeInstallFlagForRouterEvent(const std::unique_ptr<JsonValue> &flag, AAFwk::Want &want)
{
    if (flag->IsValid()) {
        auto inputFlag = flag->GetUInt();
        if (inputFlag & Want::FLAG_INSTALL_ON_DEMAND) {
            want.AddFlags(Want::FLAG_INSTALL_ON_DEMAND);
        }
    }
}

int32_t FormUtilsImpl::RequestPublishFormEvent(const AAFwk::Want& want,
    const std::string& formBindingDataStr, int64_t& formId, std::string &errMsg)
{
    std::unique_ptr<AppExecFwk::FormProviderData> formBindingData = std::make_unique<AppExecFwk::FormProviderData>();
    bool withFormBindingData = false;
    if (!formBindingDataStr.empty()) {
        withFormBindingData = true;
        formBindingData->SetDataString(const_cast<std::string&>(formBindingDataStr));
        formBindingData->ParseImagesData();
    }
    std::vector<AppExecFwk::FormDataProxy> formDataProxies;
    int32_t ret = AppExecFwk::FormMgr::GetInstance().RequestPublishFormWithSnapshot(const_cast<Want&>(want),
        withFormBindingData, formBindingData, formId, formDataProxies);
    int32_t externalErrorCode = ret;
    if (ret != ERR_OK) {
        OHOS::AppExecFwk::FormMgr::GetInstance().GetExternalError(ret, externalErrorCode, errMsg);
    }
    
    return externalErrorCode;
}

int32_t FormUtilsImpl::BackgroundEvent(const int64_t formId, const std::string& action, const int32_t containerId,
    const std::string& defaultBundleName, bool isManuallyClick)
{
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, -1);
    auto token = aceContainer->GetToken();
    CHECK_NULL_RETURN(token, -1);
    AAFwk::Want want;
    auto eventAction = JsonUtil::ParseJsonString(action);
    auto bundleName = eventAction->GetValue("bundleName");
    auto abilityName = eventAction->GetValue("abilityName");
    auto params = eventAction->GetValue("params");
    auto bundle = bundleName->GetString();
    auto ability = abilityName->GetString();
    if (ability.empty()) {
        return -1;
    }
    if (bundle.empty()) {
        bundle = defaultBundleName;
    }
    want.SetElementName(bundle, ability);
    if (params->IsValid()) {
        auto child = params->GetChild();
        while (child->IsValid()) {
            auto key = child->GetKey();
            if (child->IsNull()) {
                want.SetParam(key, std::string());
            } else if (child->IsString()) {
                want.SetParam(key, child->GetString());
            } else if (child->IsNumber()) {
                want.SetParam(key, child->GetInt());
            } else {
                want.SetParam(key, std::string());
            }
            child = child->GetNext();
        }
    }
    want.SetParam("params", params->ToString());
    want.SetParam(OHOS::AppExecFwk::Constants::PARAM_FORM_MANUAL_CLICK_KEY, isManuallyClick);
    return AppExecFwk::FormMgr::GetInstance().BackgroundEvent(formId, want, token);
}

int32_t FormUtilsImpl::InsightIntentEvent(
    const int64_t formId, const std::string& action, const int32_t containerId)
{
    TAG_LOGI(AceLogTag::ACE_FORM,
        "InsightIntentEvent enter, formId: %{public}" PRId64 ", containerId: %{public}d", formId, containerId);
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    if (aceContainer == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent aceContainer is null");
        return -1;
    }
    // 权限校验已在宿主侧 OnInsightIntentActionEvent 完成，此处不重复。
    auto token = aceContainer->GetToken();
    if (token == nullptr) {
        TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent token is null");
        return -1;
    }

    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent action is not valid json");
        return -1;
    }
    auto intentNameJson = eventAction->GetValue("intentName");
    const auto intentName = intentNameJson->GetString();
    if (intentName.empty()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "InsightIntentEvent intentName is empty");
        return -1;
    }
    // params 为透传信封：内含 intentParams（业务意图参数）与保留键 executeMode，
    // 业务参数整体隔离在子对象中，与保留键无同名冲突；
    // executeMode 缺省回退前台执行，非法值整体拒绝。
    auto params = eventAction->GetValue("params");
    int32_t executeMode = 0;
    if (!GetIntentExecuteMode(params, executeMode)) {
        return -1;
    }

    AAFwk::WantParams wantParams;
    ParseIntentParams(params, wantParams);

    AAFwk::Want want;
    AAFwk::WantParams executeWantParams;
    executeWantParams.SetParam(
        AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_NAME, AAFwk::String::Box(intentName));
    // intentId 由 AMS 侧按名称查表覆盖，此处占位 "0"（GenerateFromWant 要求可解析为 uint64，不能为空）。
    executeWantParams.SetParam(
        AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_ID, AAFwk::String::Box("0"));
    executeWantParams.SetParam(AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_MODE,
        AAFwk::Integer::Box(executeMode));
    executeWantParams.SetParam(AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_PARAM,
        AAFwk::WantParamWrapper::Box(wantParams));
    want.SetParams(executeWantParams);
    // postCardAction 显式传入的目标三元组优先，缺失字段由 FMS 按 FormRecord 补齐。
    SetIntentTargetElement(eventAction, want);
    TAG_LOGI(AceLogTag::ACE_FORM, "InsightIntentEvent send IPC, intentName: %{public}s", intentName.c_str());
    auto ret = AppExecFwk::FormMgr::GetInstance().InsightIntentEvent(formId, want, token);
    TAG_LOGI(AceLogTag::ACE_FORM, "InsightIntentEvent IPC result: %{public}d", ret);
    return ret;
}
} // namespace OHOS::Ace

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

#include "insight_intent/insight_intent_execute_param.h"
#include "want_params.h"
#include "want_params_wrapper.h"

#include "bool_wrapper.h"
#include "int_wrapper.h"
#include "string_wrapper.h"

#include "adapter/ohos/entrance/ace_container.h"

namespace OHOS::Ace {
namespace {
    constexpr int32_t ERR_OK = 0;
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
    auto uri = eventAction->GetValue("uri");
    auto params = eventAction->GetValue("params");
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
    AddWantFreeInstallFlagForRouterEvent(eventAction->GetValue("flag"), want);
    auto abilityName = eventAction->GetValue("abilityName");
    auto bundleName = eventAction->GetValue("bundleName");
    auto bundle = bundleName->GetString();
    auto ability = abilityName->GetString();
    if (uri->IsValid()) {
        want.SetUri(uri->GetString());
    }
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
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, -1);
    // 权限校验已在宿主侧 OnInsightIntentActionEvent 完成，此处不重复。
    auto token = aceContainer->GetToken();
    CHECK_NULL_RETURN(token, -1);

    auto eventAction = JsonUtil::ParseJsonString(action);
    auto intentNameJson = eventAction->GetValue("intentName");
    const auto intentName = intentNameJson->GetString();
    if (intentName.empty()) {
        return -1;
    }

    AAFwk::WantParams wantParams;
    auto intentParams = eventAction->GetValue("intentParams");
    if (intentParams->IsValid()) {
        auto child = intentParams->GetChild();
        while (child->IsValid()) {
            auto key = child->GetKey();
            // WantParams::SetParam 仅接受 IInterface 派生类型，需用 AAFwk 包装类 Box() 转换。
            if (child->IsString()) {
                wantParams.SetParam(key, AAFwk::String::Box(child->GetString()));
            } else if (child->IsNumber()) {
                wantParams.SetParam(key, AAFwk::Integer::Box(child->GetInt()));
            } else if (child->IsBool()) {
                wantParams.SetParam(key, AAFwk::Boolean::Box(child->GetBool()));
            } else {
                wantParams.SetParam(key, AAFwk::String::Box(child->GetString()));
            }
            child = child->GetNext();
        }
    }

    AAFwk::Want want;
    AAFwk::WantParams executeWantParams;
    executeWantParams.SetParam(
        AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_NAME, AAFwk::String::Box(intentName));
    // intentId 由 AMS 侧按名称查表覆盖，此处占位 "0"（GenerateFromWant 要求可解析为 uint64，不能为空）。
    executeWantParams.SetParam(
        AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_ID, AAFwk::String::Box("0"));
    // 卡片点击拉起前台 UIAbility，实际支持的 executeMode 由 AMS 校验。
    executeWantParams.SetParam(AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_MODE,
        AAFwk::Integer::Box(static_cast<int32_t>(AppExecFwk::ExecuteMode::UI_ABILITY_FOREGROUND)));
    executeWantParams.SetParam(AppExecFwk::INSIGHT_INTENT_EXECUTE_PARAM_PARAM,
        AAFwk::WantParamWrapper::Box(wantParams));
    want.SetParams(executeWantParams);
    return AppExecFwk::FormMgr::GetInstance().InsightIntentEvent(formId, want, token);
}
} // namespace OHOS::Ace

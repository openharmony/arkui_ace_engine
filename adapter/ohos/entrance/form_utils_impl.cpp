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

#include "want_params.h"

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
    const int64_t formId, const std::string& action, const int32_t containerId, const std::string& defaultBundleName)
{
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, -1);
    // 系统应用门禁已落位：宿主侧 OnInsightIntentActionEvent 内 FormMgr::IsSystemAppForm
    // 判 provider bundleName（先例 RegisterFont 字体门禁），此处不重复校验。
    auto token = aceContainer->GetToken();
    CHECK_NULL_RETURN(token, -1);

    auto eventAction = JsonUtil::ParseJsonString(action);
    auto intentNameJson = eventAction->GetValue("intentName");
    auto intentName = intentNameJson->GetString();
    if (intentName.empty()) {
        return -1;
    }

    // intentParams: JSON -> AAFwk::WantParams（对照 RouterEvent 的 params 转换循环）
    AAFwk::WantParams wantParams;
    auto intentParams = eventAction->GetValue("intentParams");
    if (intentParams->IsValid()) {
        auto child = intentParams->GetChild();
        while (child->IsValid()) {
            auto key = child->GetKey();
            // WantParams::SetParam 仅接受 IInterface 派生类型（Want 才有原始类型重载），
            // 需用 AAFwk 包装类 Box() 转换，先例：js_plugin_want.cpp / ace_ability.cpp。
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

    // TODO: 以下依赖 form_fwk 侧接口定稿（InsightIntentExecuteParam / InsightIntentHostClient
    // / ExecuteIntentWithSpecalTokenId 均不在本仓库），补齐 include 后替换占位实现：
    // 1. InsightIntentExecuteParam 字段名待接口负责人确认（推测含 intentName）；
    // 2. uint64_t key 语义待确认。注意：aceContainer->GetToken() 返回 sptr<IRemoteObject>（IPC
    //    token 对象，参照 RouterEvent 传 token 的旧模式），无法直接转为 uint64 数值。类型核对：
    //    formId 为 int64_t、containerId 为 int32_t（宽度/符号不吻合），精确匹配 uint64_t 的
    //    是 FullTokenID —— 参照 js_plugin_component.cpp 先例 IPCSkeleton::GetSelfTokenID()，
    //    与函数名 WithSpecalTokenId 吻合，待接口负责人确认；
    // 3. InsightIntentHostClient 已确认为外部提供，ace_engine 不实现回调，直接获取实例传入
    //    （具体获取方式待头文件定稿：GetInstance() 单例模式，参照 FormHostClient）。
    // InsightIntentExecuteParam param;
    // param.intentName = intentName;
    // return XxxMgr::GetInstance().ExecuteIntentWithSpecalTokenId(
    //     key, InsightIntentHostClient::GetInstance(), param, wantParams);
    return -1;
}
} // namespace OHOS::Ace

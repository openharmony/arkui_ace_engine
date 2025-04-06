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
    auto abilityName = eventAction->GetValue("abilityName");
    if (uri->IsValid() && !abilityName->IsValid()) {
        auto uriStr = uri->GetString();
        want.SetUri(uriStr);
        auto bundleName = eventAction->GetValue("bundleName");
        auto bundle = bundleName->GetString();
        if (!bundle.empty()) {
            want.SetElementName(bundle, std::string());
        }
    } else {
        auto bundleName = eventAction->GetValue("bundleName");
        auto bundle = bundleName->GetString();
        auto ability = abilityName->GetString();
        if (ability.empty()) {
            return -1;
        }
        if (bundle.empty()) {
            bundle = defaultBundleName;
        }
        want.SetElementName(bundle, ability);
    }

    return AppExecFwk::FormMgr::GetInstance().RouterEvent(formId, want, token_);
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
    if (ret != ERR_OK) {
        errMsg = OHOS::AppExecFwk::FormMgr::GetInstance().GetErrorMessage(ret);
    }
    
    return ret;
}

int32_t FormUtilsImpl::BackgroundEvent(
    const int64_t formId, const std::string& action, const int32_t containerId, const std::string& defaultBundleName)
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
    return AppExecFwk::FormMgr::GetInstance().BackgroundEvent(formId, want, token);
}
} // namespace OHOS::Ace

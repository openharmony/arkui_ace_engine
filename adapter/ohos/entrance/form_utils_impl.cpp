/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "want.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/utils/utils.h"
#include "core/common/container_scope.h"
#include "core/common/form_manager.h"
#include "frameworks/base/json/json_util.h"

namespace OHOS::Ace {
int32_t FormUtilsImpl::RouterEvent(
    const int64_t formId, const std::string& action, const int32_t containerId, const std::string& defaultBundleName)
{
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto ace_container = AceType::DynamicCast<Platform::AceContainer>(container);
    auto token_ = ace_container->GetToken();
    CHECK_NULL_RETURN_NOLOG(token_, -1);
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
    if (uri->IsValid()) {
        auto uriStr = uri->GetString();
        want.SetUri(uriStr);
    } else {
        auto bundleName = eventAction->GetValue("bundleName");
        auto abilityName = eventAction->GetValue("abilityName");
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

int32_t FormUtilsImpl::BackgroundEvent(
    const int64_t formId, const std::string& action, const int32_t containerId, const std::string& defaultBundleName)
{
    ContainerScope scope(containerId);
    auto container = Container::Current();
    auto aceContainer = AceType::DynamicCast<Platform::AceContainer>(container);
    CHECK_NULL_RETURN_NOLOG(aceContainer, -1);
    auto token = aceContainer->GetToken();
    CHECK_NULL_RETURN_NOLOG(token, -1);
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
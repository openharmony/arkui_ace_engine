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

#include "want_wrap_ohos.h"

#include "napi_common_want.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
RefPtr<WantParamsWrap> WantParamsWrap::CreateWantWrap(napi_env env, napi_value value)
{
    return AceType::MakeRefPtr<WantParamsWrapOhos>(env, value);
}
WantParamsWrapOhos::WantParamsWrapOhos(napi_env env, napi_value value)
{
    AppExecFwk::UnwrapWantParams(env, value, params_);
}

napi_value WantWrap::ConvertToNativeValue(const OHOS::AAFwk::Want& want, napi_env env)
{
    return OHOS::AppExecFwk::WrapWant(env, want);
}

napi_value WantWrap::ConvertParamsToNativeValue(const OHOS::AAFwk::WantParams& wantParams, napi_env env)
{
    return OHOS::AppExecFwk::WrapWantParams(env, wantParams);
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(napi_env env, napi_value value)
{
    if (env == nullptr || value == nullptr) {
        LOGW("engine or value is nullptr when CreateWantWrap.");
        return nullptr;
    }

    return AceType::MakeRefPtr<WantWrapOhos>(env, value);
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(const std::string& bundleName, const std::string& abilityName)
{
    return AceType::MakeRefPtr<WantWrapOhos>(bundleName, abilityName);
}

WantWrapOhos::WantWrapOhos(const AAFwk::Want& want) : want_(want) {}

WantWrapOhos::WantWrapOhos(napi_env env, napi_value value)
{
    OHOS::AppExecFwk::UnwrapWant(env, value, want_);
}

WantWrapOhos::WantWrapOhos(const std::string& bundleName, const std::string& abilityName)
{
    want_.SetElementName(bundleName, abilityName);
}

void WantWrapOhos::SetWantParamsFromWantWrap(void* want)
{
    auto destWant = reinterpret_cast<AAFwk::Want*>(want);
    CHECK_NULL_VOID(destWant);
    auto params = want_.GetParams();
    destWant->SetParams(params);
}

void WantWrapOhos::SetWantParam(const std::map<std::string, std::string>& params)
{
    for (const auto& param : params) {
        want_.SetParam(param.first, param.second);
    }
}

std::string WantWrapOhos::ToString() const
{
    return want_.ToString();
}
} // namespace OHOS::Ace

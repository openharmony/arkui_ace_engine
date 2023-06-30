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

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "napi_common_want.h"

namespace OHOS::Ace {
NativeValue* WantWrap::ConvertToNativeValue(const OHOS::AAFwk::Want& want, NativeEngine* engine)
{
    return reinterpret_cast<NativeValue*>(OHOS::AppExecFwk::WrapWant(reinterpret_cast<napi_env>(engine), want));
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(void* nativeEngine, void* nativeValue)
{
    NativeEngine* engine = reinterpret_cast<NativeEngine*>(nativeEngine);
    NativeValue* value = reinterpret_cast<NativeValue*>(nativeValue);
    if (engine == nullptr || value == nullptr) {
        LOGW("engine or value is nullptr when CreateWantWrap.");
        return nullptr;
    }

    return AceType::MakeRefPtr<WantWrapOhos>(engine, value);
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(const std::string& bundleName, const std::string& abilityName)
{
    return AceType::MakeRefPtr<WantWrapOhos>(bundleName, abilityName);
}

WantWrapOhos::WantWrapOhos(NativeEngine* engine, NativeValue* value)
{
    OHOS::AppExecFwk::UnwrapWant(reinterpret_cast<napi_env>(engine),
                                 reinterpret_cast<napi_value>(value),
                                 want_);
}

WantWrapOhos::WantWrapOhos(const std::string& bundleName, const std::string& abilityName)
{
    want_.SetElementName(bundleName, abilityName);
}

void WantWrapOhos::SetWantParamsFromWantWrap(void* want)
{
    auto destWant = reinterpret_cast<AAFwk::Want*>(want);
    CHECK_NULL_VOID_NOLOG(destWant);
    auto params = want_.GetParams();
    destWant->SetParams(params);
}

std::string WantWrapOhos::ToString() const
{
    return want_.ToString();
}
} // namespace OHOS::Ace

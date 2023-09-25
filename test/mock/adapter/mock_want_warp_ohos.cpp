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

#include "adapter/ohos/osal/want_wrap_ohos.h"

namespace OHOS::Ace {
napi_value WantWrap::ConvertToNativeValue(const OHOS::AAFwk::Want& want, NativeEngine* engine)
{
    napi_value result = nullptr;
    return result;
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(napi_env env, napi_value value)
{
    return nullptr;
}

RefPtr<WantWrap> WantWrap::CreateWantWrap(const std::string& bundleName, const std::string& abilityName)
{
    return nullptr;
}

WantWrapOhos::WantWrapOhos(napi_env env, napi_value value)
{
}

WantWrapOhos::WantWrapOhos(const std::string& bundleName, const std::string& abilityName)
{
}

void WantWrapOhos::SetWantParamsFromWantWrap(void* want)
{
}

std::string WantWrapOhos::ToString() const
{
    return std::string();
}
} // namespace OHOS::Ace

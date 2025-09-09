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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_WANT_WRAP_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_WANT_WRAP_OHOS_H

#include <string>

#include "napi/native_api.h"
#include "native_engine/native_engine.h"
#include "want.h"

#include "base/want/want_wrap.h"

namespace OHOS::Ace {
class WantParamsWrapOhos : public WantParamsWrap {
    DECLARE_ACE_TYPE(WantParamsWrapOhos, WantParamsWrap);

public:
    WantParamsWrapOhos(napi_env env, napi_value value);
    ~WantParamsWrapOhos() = default;
    const AAFwk::WantParams& GetWantParams() const
    {
        return params_;
    }

private:
    AAFwk::WantParams params_;
};

class WantWrapOhos : public WantWrap {
    DECLARE_ACE_TYPE(WantWrapOhos, WantWrap);

public:
    explicit WantWrapOhos(const AAFwk::Want& want);
    WantWrapOhos(napi_env env, napi_value value);
    WantWrapOhos(const std::string& bundleName, const std::string& abilityName);
    ~WantWrapOhos() = default;
    void SetWantParamsFromWantWrap(void* want) override;
    std::string ToString() const override;
    void SetWantParam(const std::map<std::string, std::string>& params) override;

    const AAFwk::Want& GetWant() const override
    {
        return want_;
    }

private:
    AAFwk::Want want_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_WANT_WRAP_OHOS_H

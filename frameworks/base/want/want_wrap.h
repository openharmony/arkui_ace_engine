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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H

#include <map>

#include "base/memory/ace_type.h"

typedef struct napi_value__* napi_value;
typedef struct napi_env__* napi_env;
namespace OHOS::AAFwk {
class Want;
class WantParams;
} // namespace OHOS::AAFwk

namespace OHOS::Ace {
class WantParamsWrap : public AceType {
    DECLARE_ACE_TYPE(WantParamsWrap, AceType);

public:
    static RefPtr<WantParamsWrap> CreateWantWrap(napi_env env, napi_value value);
};

class ACE_EXPORT WantWrap : public AceType {
    DECLARE_ACE_TYPE(WantWrap, AceType);

public:
    static napi_value ConvertToNativeValue(const OHOS::AAFwk::Want& want, napi_env env);
    static napi_value ConvertParamsToNativeValue(const OHOS::AAFwk::WantParams& wantParams, napi_env env);
    static RefPtr<WantWrap> CreateWantWrap(napi_env env, napi_value value);
    static RefPtr<WantWrap> CreateWantWrap(const std::string& bundleName, const std::string& abilityName);

    virtual void SetWantParamsFromWantWrap(void* want) = 0;
    virtual void SetWantParam(const std::map<std::string, std::string>& params) = 0;
    virtual std::string ToString() const = 0;
    virtual const OHOS::AAFwk::Want& GetWant() const = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_WANT_WRAP_H

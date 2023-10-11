/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H
#define FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H

#include <chrono>
#include <cmath>
#include <cstdint>
#include <regex>
#include <vector>

#include "native_engine/native_value.h"

#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace::Napi {

struct ResourceInfo {
    int32_t resId = 0;
    int32_t type = 0;
    std::vector<std::string> params;
    std::optional<std::string> bundleName = std::nullopt;
    std::optional<std::string> moduleName = std::nullopt;
};

size_t GetParamLen(napi_env env, napi_value param);
bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType);

void NapiThrow(napi_env env, const std::string& message, int32_t errCode);

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info);

bool ParseString(const ResourceInfo& info, std::string& result);

std::string ErrorToMessage(int32_t code);

} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_NAPI_KITS_UTILS_H

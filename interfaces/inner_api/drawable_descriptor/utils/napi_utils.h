/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_BASE_NAPI_UTILS_H
#define FOUNDATION_ACE_INTERFACE_BASE_NAPI_UTILS_H

#include <cstdint>
#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/resource.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class NapiUtils {
public:
    static Resource ParseJsResource(napi_env env, napi_value value);
    static std::string ParseJsString(napi_env env, napi_value value);
    static napi_valuetype ParseJsType(napi_env env, napi_value value);
    static int32_t ParseJsInt(napi_env env, napi_value value);
    static napi_value GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    static bool IsArray(napi_env env, napi_value value);
    static bool ParseJsBool(napi_env env, napi_value value);
    static napi_value CreateString(napi_env env, const char* str);
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_BASE_NAPI_UTILS_H
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_COMPONENTEXT_EXT_COMMON_EXT_NAPI_UTILS_H
#define FOUNDATION_ACE_COMPONENTEXT_EXT_COMMON_EXT_NAPI_UTILS_H

#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "ui/base/macros.h"
#include "frameworks/core/components/common/properties/color.h"
#include "frameworks/core/components/theme/theme_constants.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT NapiAsyncEvent {
public:
    NapiAsyncEvent(napi_env env, napi_value callback);
    ~NapiAsyncEvent();
    napi_value Call(int32_t argc, napi_value* argv);
    napi_env GetEnv();

private:
    napi_env env_;
    napi_ref ref_;
};

class ACE_FORCE_EXPORT ExtNapiUtils {
public:
    static napi_value CreateInt32(napi_env env, int32_t code);
    static napi_value CreateObject(napi_env env);
    static napi_value CreateDouble(napi_env env, double value);
    static napi_value CreateFunction(napi_env env,
                                        const char* utf8name, size_t length,
                                        napi_callback cb,
                                        void* data);
    static int32_t GetCInt32(napi_env env, napi_value value);
    static int64_t GetCInt64(napi_env env, napi_value value);
    static napi_value CreateNull(napi_env env);
    static bool GetBool(napi_env env, napi_value value);
    static napi_valuetype GetValueType(napi_env env, napi_value value);
    static std::string GetStringFromValueUtf8(napi_env env, napi_value value);
    static bool CheckTypeForNapiValue(napi_env env, napi_value param, napi_valuetype expectType);
    static void SetNamedProperty(napi_env env, napi_value object, const std::string& propertyName, napi_value value);
    static bool ParseColorFromResource(napi_env env, napi_value value, Color& result);
    static bool ParseColor(napi_env env, napi_value value, Color& result);
    static napi_value GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    static bool IsArray(napi_env env, napi_value value);
    static napi_value CreateUndefined(napi_env env);
    static RefPtr<ThemeConstants> GetThemeConstants(napi_env env, napi_value value);
    static std::unique_ptr<JsonValue> PutJsonValue(napi_env env, napi_value value, std::string& key);
    static bool ParseLengthMetrics(napi_env env, napi_value param, CalcDimension& result);
    static bool ParseColorMetrics(napi_env env, napi_value param, Color& result);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_COMPONENTEXT_EXT_COMMON_EXT_NAPI_UTILS_H
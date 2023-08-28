/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAPI_COMMON_UTILS_COMMON_NAPI_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAPI_COMMON_UTILS_COMMON_NAPI_UTILS_H

#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme_constants.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT NapiAsyncEvnet {
public:
    NapiAsyncEvnet(napi_env env, napi_value callback);
    ~NapiAsyncEvnet();
    napi_value Call(int32_t argc, napi_value* argv);
    napi_env GetEnv();

private:
    napi_env env_;
    napi_ref ref_;
};

class ACE_FORCE_EXPORT CommonNapiUtils {
public:
    static napi_value CreateInt32(napi_env env, int32_t code);
    static int32_t GetCInt32(napi_value value, napi_env env);
    static int64_t GetCInt64(napi_value value, napi_env env);
    static napi_value CreateBoolean(napi_env env, bool value);
    static bool GetBool(napi_env env, napi_value value);
    static napi_value CreateDouble(napi_env env, double value);
    static double GetDouble(napi_env env, napi_value value);
    static size_t GetCString(napi_value value, napi_env env, char* buf, size_t size);
    static napi_value CreateStringUtf8(napi_env env, const std::string& str);
    static std::string GetStringFromValueUtf8(napi_env env, napi_value value);
    static napi_value CreateNull(napi_env env);
    static napi_value CreateUndefined(napi_env env);
    static napi_valuetype GetValueType(napi_env env, napi_value value);
    static napi_value CreateObject(napi_env env);
    static void DefineProperties(
        napi_env env, napi_value object, const std::initializer_list<napi_property_descriptor>& properties);
    static void DefineClass(napi_env env, napi_value exports,
        const std::initializer_list<napi_property_descriptor>& properties, const std::string& className);
    static void SetNamedProperty(napi_env env, napi_value object, const std::string& propertyName, napi_value value);
    static napi_value GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    static bool HasNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    static bool GetPropertyNames(napi_env env, napi_value object, std::vector<std::string>& nameList);
    static bool IsArray(napi_env env, napi_value value);
    static void SetSelementToArray(napi_env env, napi_value array, int index, napi_value value);
    static napi_value CreateArray(napi_env env);
    static bool ParseColorFromResource(napi_env env, napi_value value, Color& result);
    static bool ParseColor(napi_env env, napi_value value, Color& result);
    static std::unique_ptr<JsonValue> PutJsonValue(napi_env env, napi_value value, std::string& key);
    static RefPtr<ThemeConstants> GetThemeConstants(napi_env env, napi_value value);
    static bool GetDimensionResult(napi_env env, napi_value value, CalcDimension& result);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAPI_COMMON_UTILS_COMMON_NAPI_UTILS_H

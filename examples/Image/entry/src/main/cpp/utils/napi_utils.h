/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef CAPI_NAPI_UTILS_H
#define CAPI_NAPI_UTILS_H

#include <string>
#include "napi/native_api.h"

namespace Self::UI {
size_t GetParamLen(napi_env env, napi_value param);
bool NapiStringToString(napi_env env, napi_value value, std::string &retStr);
float GetFloatProperty(napi_env env, napi_value obj, const char *propName, float defaultValue = 0.0f);
bool HasProperty(napi_env env, napi_value obj, const char *propName);
std::vector<float> ParseFloatArray(napi_env env, napi_value arrayValue);
std::vector<int> ParseIntArray(napi_env env, napi_value arrayValue);
} // namespace Self::UI

#endif // CAPI_NAPI_UTILS_H
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_ETS_ANI_UTILS_ANI_UTILS_H
#define INTERFACES_ETS_ANI_UTILS_ANI_UTILS_H

#include <ani.h>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace OHOS::Ace::AniUtils {

// Create ANI objects
ani_object CreateANIIntObject(ani_env* env, int32_t intValue);
ani_object CreateANILongObject(ani_env* env, int64_t longValue);
ani_object CreateANIDoubleObject(ani_env* env, double doubleValue);

// Check object type
bool IsUndefinedObject(ani_env* env, ani_ref objectRef);
bool IsClassObject(ani_env* env, ani_object object, const char* classDescriptor);
bool IsArrayObject(ani_env* env, ani_object object);
bool IsArrayObject(ani_env* env, ani_ref ref);
bool IsEnum(ani_env* env, ani_object object, const char* enumDescriptor);

// Get bool parameter
bool GetBoolParam(ani_env* env, ani_ref ref, bool& result);
bool GetBoolParam(ani_env* env, ani_object object, const char* name, bool& result);

// Get int32 parameter
bool GetInt32Param(ani_env* env, ani_ref ref, int32_t& result);
bool GetInt32Param(ani_env* env, ani_object object, const char* name, int32_t& result);

// Get int64 parameter
bool GetInt64Param(ani_env* env, ani_ref ref, int64_t& result);
bool GetInt64Param(ani_env* env, ani_object object, const char* name, int64_t& result);

// Get double parameter
bool GetDoubleParam(ani_env* env, ani_ref ref, double& result);
bool GetDoubleParam(ani_env* env, ani_object object, const char* name, double& result);
bool GetDoubleParamOpt(ani_env* env, ani_object object, const char* name, std::optional<double>& result);

// String utilities
std::string ANIStringToStdString(ani_env* env, ani_string aniStr);
bool GetStringParam(ani_env* env, ani_ref ref, std::string& result);
bool GetStringParam(ani_env* env, ani_object object, const char* name, std::string& result);
bool GetStringParamOpt(ani_env* env, ani_object object, const char* name, std::optional<std::string>& result);
bool GetStringArrayParam(ani_env* env, ani_object object, const char* name, std::vector<std::string>& result);

// Get enum int value
bool GetEnumInt(ani_env* env, ani_object resultObj, const char* enumDescriptor, int32_t& result);
bool GetEnumInt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor, int32_t& result);
bool GetEnumIntOpt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor,
    std::optional<int32_t>& result);

// Get enum string value
bool GetEnumString(ani_env* env, ani_object resultObj, const char* enumDescriptor, std::string& result);
bool GetEnumString(ani_env* env, ani_object object, const char* name, const char* enumDescriptor, std::string& result);
bool GetEnumStringOpt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor,
    std::optional<std::string>& result);

// Get function parameter
bool GetFunctionParam(ani_env* env, ani_ref ref, std::function<void()>& result);
bool GetFunctionParam(ani_env* env, ani_object object, const char* name, std::function<void()>& result);

// Throw error
std::string ErrorToMessage(int32_t code);
std::string GetErrorMsg(int32_t errorCode);
ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code);
void AniThrow(ani_env* env, const std::string& errMsg, int32_t code);

} // namespace OHOS::Ace::AniUtils

#endif // INTERFACES_ETS_ANI_UTILS_ANI_UTILS_H

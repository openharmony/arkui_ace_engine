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

#ifndef INTERFACES_ETS_ANI_PROMPTACTION_SRC_DRAWABLE_DESCRIPTOR_UTILS_H
#define INTERFACES_ETS_ANI_PROMPTACTION_SRC_DRAWABLE_DESCRIPTOR_UTILS_H

#include <ani.h>

#include "core/common/resource/resource_wrapper.h"
namespace OHOS::Ace::Ani {

#define ANI_CALL(env, call, onFail...) \
    if (env) {                         \
        if (((env)->call) != ANI_OK) { \
            onFail;                    \
        }                              \
    } else {                           \
        onFail;                        \
    }

struct DrawableAsyncContext {
    ani_vm* vm = nullptr;
    ani_resolver deferred = nullptr;
    int32_t instanceId = -1;
};

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};

struct ResourceObjectInfo {
    int32_t resId = 0;
    int32_t type = 0;
    std::vector<ResourceObjectParams> params;
    std::optional<std::string> bundleName = std::nullopt;
    std::optional<std::string> moduleName = std::nullopt;
};

enum class ResourceStruct { CONSTANT, DYNAMIC_V1, DYNAMIC_V2 };
constexpr const int32_t NUMBER_ZERO = 0;
constexpr const int32_t NUMBER_ONE = 1;
constexpr const int32_t NUMBER_TWO = 2;
constexpr size_t MAX_TYPENAME_LEN = 255;
constexpr int32_t SPECIFIED_CAPACITY = 16;

// Get ANI base params
bool IsClassObject(ani_env* env, ani_object object, const char* classDescriptor);
bool IsUndefinedObject(ani_env* env, ani_ref objectRef);
bool IsArrayObject(ani_env* env, ani_object object);
bool IsArrayObject(ani_env* env, ani_ref ref);
bool IsStringObject(ani_env* env, ani_ref objectRef);
bool IsNumberObject(ani_env* env, ani_ref objectRef);
bool GetStringParam(ani_env* env, ani_ref ref, std::string& result);
bool GetStringParam(ani_env* env, ani_object object, const char* name, std::string& result);
bool GetStringParamOpt(ani_env* env, ani_object object, const char* name, std::optional<std::string>& result);
bool GetInt32Param(ani_env* env, ani_ref ref, int32_t& result);
bool GetInt32Param(ani_env* env, ani_object object, const char* name, int32_t& result);
bool GetBoolParam(ani_env* env, ani_ref ref, bool& result);
bool GetBoolParam(ani_env* env, ani_object object, const char* name, bool& result);
bool GetArrayIntParam(ani_env* env, ani_ref ref, std::vector<int32_t>& result);
bool GetArrayIntParam(ani_env* env, ani_object object, const char* name, std::vector<int32_t>& result);
std::string ANIStringToStdString(ani_env* env, ani_string aniStr);
ani_object CreateANIDoubleObject(ani_env* env, double doubleValue);
void ProcessResourceType(ani_env* env, ani_object value, ani_ref paramsRef, size_t length, std::string resName);
void ModifyResourceParam(ani_env* env, ani_object object, const ResourceType& resType, const std::string& resName);
void PrefixEmptyBundleName(ani_env* env, ani_object object);
ResourceStruct CheckResourceStruct(ani_env* env, ani_object object);
void CompleteResourceParamV1(ani_env* env, ani_object object);
void CompleteResourceParamV2(ani_env* env, ani_object object);
void CompleteResourceParam(ani_env* env, ani_object object);
bool ConvertResourceType(const std::string& typeName, ResourceType& resType);
bool GetDollarResource(
    ani_env* env, ani_object object, ResourceType& resType, std::string& resName, std::string& moduleName);
bool GetResourceParam(ani_env* env, ani_object object, ResourceObjectInfo& result);
bool GetResourceObjectParams(
    ani_env* env, ani_object object, const char* name, std::vector<ResourceObjectParams>& result);
// Get drawable params
ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code);
} // namespace OHOS::Ace::Ani
#endif // INTERFACES_ETS_ANI_PROMPTACTION_SRC_DRAWABLE_DESCRIPTOR_UTILS_H

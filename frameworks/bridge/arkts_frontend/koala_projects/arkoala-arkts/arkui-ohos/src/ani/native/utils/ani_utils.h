/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_UTILS
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_UTILS

#include "ani.h"
#include <string>
#include "./../log/log.h"
#include "ui/base/macros.h"
#include "base/error/error_code.h"
#include "base/utils/utils.h"

#define ANI_CALL(env, call, onFail...)                                                                 \
    if (env) {                                                                                         \
        const char* aniErr[] = {                                                                       \
            "ANI_OK",                                                                                  \
            "ANI_ERROR",                                                                               \
            "ANI_INVALID_ARGS",                                                                        \
            "ANI_INVALID_TYPE",                                                                        \
            "ANI_INVALID_DESCRIPTOR",                                                                  \
            "ANI_INCORRECT_REF",                                                                       \
            "ANI_PENDING_ERROR",                                                                       \
            "ANI_NOT_FOUND",                                                                           \
            "ANI_ALREADY_BINDED",                                                                      \
            "ANI_OUT_OF_REF",                                                                          \
            "ANI_OUT_OF_MEMORY",                                                                       \
            "ANI_OUT_OF_RANGE",                                                                        \
            "ANI_BUFFER_TO_SMALL",                                                                     \
            "ANI_INVALID_VERSION",                                                                     \
            "ANI_AMBIGUOUS",                                                                           \
        };                                                                                             \
        ani_status ret;                                                                                \
        if ((ret = (env)->call) != ANI_OK) {                                                           \
            HILOGE("ani call %{public}s failed: %{public}d, %{public}s", #call, ret,                   \
                static_cast<size_t>(ret) < std::extent_v<decltype(aniErr)> ? aniErr[ret] : "ANI_???"); \
            if (ret == ANI_PENDING_ERROR) {                                                            \
                Ani::AniUtils::ClearAniPendingError(env);                                              \
            }                                                                                          \
            onFail;                                                                                    \
        }                                                                                              \
    } else {                                                                                           \
        onFail;                                                                                        \
    }

namespace OHOS::Ace::Ani {
class AniUtils {
public:
    static ani_object CreateDouble(ani_env *env, double value);
    static ani_object CreateLong(ani_env *env, ani_long value);
    static ani_object CreateInt32(ani_env *env, int32_t value);
    static bool CheckType(ani_env *env, ani_object obj, const std::string& type);
    static bool GetIntByName(ani_env *env, ani_object param, const char *name, int &value);
    static bool GetBoolOrUndefined(ani_env *env, ani_object param, const char *name);
    static std::string ANIStringToStdString(ani_env* env, ani_string ani_str);
    static bool IsString(ani_env* env, ani_object obj);
    static bool IsNumber(ani_env* env, ani_object obj);
    static bool IsFunction(ani_env* env, ani_object obj);
    static bool IsUndefined(ani_env* env, ani_object obj);
    static ani_object GetUndefined(ani_env* env);
    static std::optional<ani_string> StdStringToANIString(ani_env *env, std::string str);
    static bool GetStringByName(
        ani_env *env, ani_object param, const char *name, std::string &value);
    static ani_ref CreateBusinessError(ani_env* env, const char *msg, ani_int code);
    static void AniThrow(ani_env* env, const char *errMsg, int32_t code);
    static bool IsClassObject(ani_env *env, ani_ref object_ref, const char *class_descriptor);
    static bool GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue);
    static bool GetEnumItem(
        [[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem);
    // Get double value from ani_ref.
    // The return value means the parse result. True means success.
    // If the ref is undefined, it will return false.
    static bool GetOptionalDouble(ani_env* env, ani_ref value, double& result);
    // If the ref is undefined, it will return false.
    static bool GetOptionalInt(ani_env* env, ani_ref value, int32_t& result);
    /**
     * Get std/core/Double.
     */
    static ani_object CreateDoubleObject(ani_env* env, double value);
    /**
     * Get std/core/Double by float.
     */
    static ani_object FloatToNumberObject(ani_env* env, const float& value);
    /**
     * Create std/core/Boolean.
     */
    static int32_t CreateAniBoolean(ani_env* env, bool value, ani_object& result);

    /**
     * Get AbcRuntimeLinkder to load application class.
     */
    static int32_t GetNearestNonBootRuntimeLinker(ani_env*, ani_ref& result);

    /**
     * Clear ani pending error.
     */
    static void ClearAniPendingError(ani_env* env);

    /**
     * Get ani env from ani vm.
     */
    static ani_env* GetAniEnv(ani_vm* vm);
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_UTILS
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
#include "base/error/error_code.h"
#include "base/utils/utils.h"
namespace OHOS::Ace::Ani {
class AniUtils {
public:
    static ani_object CreateDouble(ani_env *env, double value);
    static ani_object CreateLong(ani_env *env, ani_long value);
    static bool CheckType(ani_env *env, ani_object obj, const std::string& type);
    static bool GetIntByName(ani_env *env, ani_object param, const char *name, int &value);
    static bool GetBoolOrUndefined(ani_env *env, ani_object param, const char *name);
    static std::string ANIStringToStdString(ani_env* env, ani_string ani_str);
    static bool IsString(ani_env* env, ani_object obj);
    static bool IsNumber(ani_env* env, ani_object obj);
    static bool IsUndefined(ani_env* env, ani_object obj);
    static ani_object GetUndefined(ani_env* env);
    static std::optional<ani_string> StdStringToANIString(ani_env *env, std::string str);
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
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_ANI_UTILS
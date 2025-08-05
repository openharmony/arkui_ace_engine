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

#include "ani_utils.h"

#include <string>

namespace OHOS::Ace::Ani {
ani_object AniUtils::CreateDouble(ani_env *env, double value)
{
    CHECK_NULL_RETURN(env, nullptr);
    static const char *className = "Lstd/core/Double;";
    ani_class persion_cls;
    if (ANI_OK != env->FindClass(className, &persion_cls)) {
        return nullptr;
    }
    ani_method infoCtor;
    if (ANI_OK != env->Class_FindMethod(persion_cls, "<ctor>", "D:V", &infoCtor)) {
        return nullptr;
    }
    ani_object personInfoObj;
    if (ANI_OK != env->Object_New(persion_cls, infoCtor, &personInfoObj, ani_double(value))) {
        return nullptr;
    }
    return personInfoObj;
}

ani_object AniUtils::CreateLong(ani_env *env, ani_long value)
{
    CHECK_NULL_RETURN(env, nullptr);
    static const char *className = "Lstd/core/Long;";
    ani_class long_cls;
    if (ANI_OK != env->FindClass(className, &long_cls)) {
        return nullptr;
    }
    ani_method longCtor;
    if (ANI_OK != env->Class_FindMethod(long_cls, "<ctor>", "J:V", &longCtor)) {
        return nullptr;
    }
    ani_object longObj;
    if (ANI_OK != env->Object_New(long_cls, longCtor, &longObj, value)) {
        return nullptr;
    }
    return longObj;
}

bool AniUtils::CheckType(ani_env *env, ani_object obj, const std::string& type)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    ani_status status = ANI_OK;
    if ((status = env->Reference_IsUndefined(obj, &isUndefined)) != ANI_OK) {
        return false;
    }
    if (isUndefined) {
        return false;
    }

    ani_class cls;
    status = env->FindClass(type.c_str(), &cls);
    if (status != ANI_OK) {
        return false;
    }

    ani_boolean isType;
    env->Object_InstanceOf(obj, cls, &isType);
    if (!isType) {
        return false;
    }

    return true;
}

bool AniUtils::GetIntByName(ani_env *env, ani_object param, const char *name, int &value)
{
    CHECK_NULL_RETURN(env, false);
    ani_int res;
    ani_status status = env->Object_GetFieldByName_Int(param, name, &res);
    if (status != ANI_OK) {
        return false;
    }

    value = static_cast<int>(res);
    return true;
}

bool AniUtils::GetBoolOrUndefined(ani_env *env, ani_object param, const char *name)
{
    CHECK_NULL_RETURN(env, false);
    ani_status status = ANI_ERROR;
    ani_boolean res;
    if ((status = env->Object_GetFieldByName_Boolean(param, name, &res)) != ANI_OK) {
        return false;
    }

    return res;
}

std::string AniUtils::ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    CHECK_NULL_RETURN(env, "");
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);

    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

bool AniUtils::IsString(ani_env* env, ani_object obj)
{
    CHECK_NULL_RETURN(env, false);
    ani_class stringClass;
    env->FindClass("Lstd/core/String;", &stringClass);

    ani_boolean isString;
    env->Object_InstanceOf(obj, stringClass, &isString);
    return isString;
}

bool AniUtils::IsNumber(ani_env* env, ani_object obj)
{
    CHECK_NULL_RETURN(env, false);
    ani_class numberClass;
    env->FindClass("Lstd/core/Double;", &numberClass);

    ani_boolean isNumber;
    env->Object_InstanceOf(obj, numberClass, &isNumber);
    return isNumber;
}

bool AniUtils::IsUndefined(ani_env* env, ani_object obj)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    env->Reference_IsUndefined(obj, &isUndefined);
    return isUndefined;
}

ani_object AniUtils::GetUndefined(ani_env* env)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return nullptr;
    }
    return static_cast<ani_object>(undefinedRef);
}

std::optional<ani_string> AniUtils::StdStringToANIString(ani_env *env, std::string str)
{
    ani_string result_string{};
    CHECK_NULL_RETURN(env, result_string);
    if (env->String_NewUTF8(str.c_str(), str.size(), &result_string) != ANI_OK) {
        return {};
    }
    return result_string;
}

ani_object WrapBusinessError(ani_env* env, const char *msg, ani_int code)
{
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = ANI_ERROR;
    if (env == nullptr) {
        return nullptr;
    }

    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg, strlen(msg), &aniMsg)) != ANI_OK) {
        return nullptr;
    }

    ani_ref undefRef;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        return nullptr;
    }

    if ((status = env->FindClass("Lescompat/Error;", &cls)) != ANI_OK) {
        return nullptr;
    }

    if ((status = env->Class_FindMethod(cls, "<ctor>", "DLstd/core/String;Lescompat/ErrorOptions;:V", &method)) !=
        ANI_OK) {
        return nullptr;
    }
    ani_double dCode(code);
    if ((status = env->Object_New(cls, method, &obj, dCode, aniMsg, undefRef)) != ANI_OK) {
        return nullptr;
    }
    
    return obj;
}

ani_ref AniUtils::CreateBusinessError(ani_env* env, const char *msg, ani_int code)
{
    ani_class cls;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("L@ohos/base/BusinessError;", &cls)) != ANI_OK) {
        return nullptr;
    }
    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", "DLescompat/Error;:V", &ctor)) != ANI_OK) {
        return nullptr;
    }
    ani_object error = WrapBusinessError(env, msg, code);
    if (error == nullptr) {
        return nullptr;
    }
    ani_object obj = nullptr;
    ani_double dCode(code);
    if ((status = env->Object_New(cls, ctor, &obj, dCode, error)) != ANI_OK) {
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(obj);
}

void AniUtils::AniThrow(ani_env* env, const char *errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = CreateBusinessError(env, errMsg, code);
    if (errObj == nullptr) {
        HILOGE("Get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(static_cast<ani_error>(errObj))) {
        HILOGE("Throw ani error object failed!");
        return;
    }
}

bool AniUtils::IsClassObject(ani_env *env, ani_ref object_ref, const char *class_descriptor)
{
    CHECK_NULL_RETURN(env, false);
    ani_class objectClass;
    ani_status status = env->FindClass(class_descriptor, &objectClass);
    if (status != ANI_OK) {
        HILOGW("Find %{public}s class failed. status = %{public}d", class_descriptor, status);
        return false;
    }

    ani_boolean isInstance;
    status = env->Object_InstanceOf(static_cast<ani_object>(object_ref), objectClass, &isInstance);
    if (status != ANI_OK) {
        HILOGW("Object is not %{public}s instance. status = %{public}d", class_descriptor, status);
        return false;
    }
    return static_cast<bool>(isInstance);
}

bool AniUtils::GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue)
{
    CHECK_NULL_RETURN(env, false);
    auto status = ANI_OK;
    ani_long value;
    if ((status = env->Object_CallMethodByName_Long(object, "unboxed", ":J", &value)) != ANI_OK) {
        return false;
    }
    longValue = value;
    return true;
}

bool AniUtils::GetEnumItem([[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem)
{
    CHECK_NULL_RETURN(env, false);
    ani_enum enumType;
    ani_status status = ANI_OK;
    if ((status = env->FindEnum(enumName, &enumType)) != ANI_OK) {
        HILOGE("Find %{public}s fail. status = %{public}d", enumName, status);
        return false;
    }
    if ((status = env->Enum_GetEnumItemByIndex(enumType, index, &enumItem)) != ANI_OK) {
        HILOGE("Get %{public}s Enum fail. status = %{public}d", enumName, status);
        return false;
    }
    return true;
}

bool AniUtils::GetOptionalDouble(ani_env* env, ani_ref value, double& result)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    if (env->Reference_IsUndefined(value, &isUndefined) != ANI_OK) {
        return false;
    }
    ani_double aniResult;
    if (env->Object_CallMethodByName_Double(static_cast<ani_object>(value), "unboxed", ":d", &aniResult) != ANI_OK) {
        return false;
    }
    result = static_cast<double>(aniResult);
    return true;
}
}
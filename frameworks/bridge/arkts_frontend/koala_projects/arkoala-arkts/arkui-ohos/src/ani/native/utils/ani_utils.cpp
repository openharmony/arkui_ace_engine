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

bool AniUtils::CheckType(ani_env *env, ani_object obj, const std::string& type)
{
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
    ani_status status = ANI_ERROR;
    ani_boolean res;
    if ((status = env->Object_GetFieldByName_Boolean(param, name, &res)) != ANI_OK) {
        return false;
    }

    return res;
}

std::string AniUtils::ANIStringToStdString(ani_env* env, ani_string ani_str)
{
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
    ani_class stringClass;
    env->FindClass("Lstd/core/String;", &stringClass);

    ani_boolean isString;
    env->Object_InstanceOf(obj, stringClass, &isString);
    return isString;
}

bool AniUtils::IsNumber(ani_env* env, ani_object obj)
{
    ani_class numberClass;
    env->FindClass("Lstd/core/Double;", &numberClass);

    ani_boolean isNumber;
    env->Object_InstanceOf(obj, numberClass, &isNumber);
    return isNumber;
}

bool AniUtils::IsUndefined(ani_env* env, ani_object obj)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(obj, &isUndefined);
    return isUndefined;
}

ani_object AniUtils::GetUndefined(ani_env* env)
{
    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return nullptr;
    }
    return static_cast<ani_object>(undefinedRef);
}

std::optional<ani_string> AniUtils::StdStringToANIString(ani_env *env, std::string str)
{
    ani_string result_string{};
    if (env->String_NewUTF8(str.c_str(), str.size(), &result_string) != ANI_OK) {
        return {};
    }
    return result_string;
}
}
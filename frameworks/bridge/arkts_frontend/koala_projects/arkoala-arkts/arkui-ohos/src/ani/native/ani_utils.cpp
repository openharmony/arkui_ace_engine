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

#include "base/log/log_wrapper.h"

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
        LOGE("Reference_IsUndefined failed when CheckType, status: %{public}d", status);
        return false;
    }
    if (isUndefined) {
        LOGE("Obj is Undefined when CheckType");
        return false;
    }

    ani_class cls;
    status = env->FindClass(type.c_str(), &cls);
    if (status != ANI_OK) {
        LOGE("FindClass failed when CheckType, status: %{public}d, type: %{public}s",
            status, type.c_str());
        return false;
    }

    ani_boolean isType;
    env->Object_InstanceOf(obj, cls, &isType);
    if (!isType) {
        LOGE("obj InstanceOf failed when CheckType, type: %{public}s", type.c_str());
        return false;
    }

    return true;
}

bool AniUtils::GetIntByName(ani_env *env, ani_object param, const char *name, int &value)
{
    ani_int res;
    ani_status status = env->Object_GetFieldByName_Int(param, name, &res);
    if (status != ANI_OK) {
        LOGE("GetFieldByName_Int failed, name: %{public}s", name);
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
        LOGE("GetFieldByName_Boolean failed, status: %{public}d, name: %{public}s",
            status, name);
        return false;
    }

    return res;
}
}
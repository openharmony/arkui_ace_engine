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

#include <cstddef>
#include <regex>

#include <ani_signature_builder.h>

#include "ani_utils.h"

namespace OHOS::Ace {
namespace {
    const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
    constexpr int32_t DEFAULT_SCOPE = 60;
}

AniAsyncEvent::AniAsyncEvent(ani_env* env, ani_ref ref)
{
    env_ = env;
    env->GlobalReference_Create(ref, &ref_);
}

AniAsyncEvent::~AniAsyncEvent()
{
    env_->GlobalReference_Delete(ref_);
}

ani_status AniAsyncEvent::Call(ani_size argc, ani_ref *argv)
{
    auto status = env_->CreateLocalScope(DEFAULT_SCOPE);
    if (status != ANI_OK) {
        return status;
    }

    ani_ref result {};
    status = env_->FunctionalObject_Call(static_cast<ani_fn_object>(ref_), argc, argv, &result);
    if (status != ANI_OK) {

    }

    env_->DestroyLocalScope();
    return status;
}

ani_env* AniAsyncEvent::GetEnv()
{
    return env_;
}

bool AniUtils::GetIsUndefinedObject(ani_env *env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(objectRef, &isUndefined)) {
        return true;
    }
    return (bool)isUndefined;
}

bool AniUtils::GetIsEnum(ani_env *env, ani_ref objectRef, const char* enumName)
{
    ani_enum enumAni;
    if (ANI_OK != env->FindEnum(enumName, &enumAni)) {
        return false;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(objectRef), enumAni, &isEnum)) {
        return false;
    }
    return (bool)isEnum;
}

ani_status AniUtils::GetInt32(ani_env *env, ani_int arg, int32_t &value)
{
    value = static_cast<int32_t>(arg);
    return ANI_OK;
}

std::string AniUtils::AniStringToStdString(ani_env *env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();
    ani_size bytesWritten = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytesWritten);
    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

bool AniUtils::ParseOptionalBool(ani_env *env, ani_object object, std::optional<bool> &result)
{
    if (GetIsUndefinedObject(env, object)) {
        result.reset();
        return true;
    }
    bool boolValue;
    if (ANI_OK != GetBool(env, object, boolValue)) {
        return false;
    }
    result = boolValue;
    return true;
}

ani_status AniUtils::GetBool(ani_env *env, ani_boolean arg, bool &value)
{
    value = (arg == ANI_TRUE);
    return ANI_OK;
}

ani_status AniUtils::GetBool(ani_env *env, ani_object arg, bool &value)
{
    if (GetIsUndefinedObject(env, arg)) {
        return ANI_ERROR;
    }

    ani_class cls {};
    static const std::string className = "std.core.Boolean";
    ani_status status = env->FindClass(className.c_str(), &cls);
    if (ANI_OK != status) {
        return status;
    }

    ani_method method {};
    status = env->Class_FindMethod(cls, "valueOf", nullptr, &method);
    if (ANI_OK != status) {
        return status;
    }
    
    ani_boolean result = 0;
    status = env->Object_CallMethod_Boolean(arg, method, &result);
    if (ANI_OK != status) {
        return status;
    }
    return GetBool(env, result, value);
}
}
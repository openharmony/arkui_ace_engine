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
#include "ani.h"
#include "ani_plugin_component_util.h"
#include "core/common/container.h"
 
ACEAsyncJSCallbackInfo* AceCreateAsyncJSCallbackInfo(ani_env* env)
{
    auto containerId = OHOS::Ace::Container::CurrentId();
    ACEAsyncJSCallbackInfo* asyncCallbackInfo = new ACEAsyncJSCallbackInfo {
        .cbInfo = {
            .env = env,
            .callback = nullptr,
            .containerId = containerId,
        },
        .ability = nullptr,
    };
    return asyncCallbackInfo;
}
 
void AceFreeAsyncJSCallbackInfo(ACEAsyncJSCallbackInfo** asyncCallbackInfo)
{
    if (asyncCallbackInfo == nullptr) {
        return;
    }
    if (*asyncCallbackInfo == nullptr) {
        return;
    }

    if ((*asyncCallbackInfo)->cbInfo.callback != nullptr && (*asyncCallbackInfo)->cbInfo.env != nullptr) {
        (*asyncCallbackInfo)->cbInfo.callback = nullptr;
        (*asyncCallbackInfo)->cbInfo.env = nullptr;
    }

    delete (*asyncCallbackInfo);
    *asyncCallbackInfo = nullptr;
}

bool AceIsSameFuncFromANI(ACECallbackInfo& left, ACECallbackInfo& right)
{
    if (left.env == nullptr && right.env == nullptr) {
        return true;
    }
    if (left.env != right.env || left.containerId != right.containerId) {
        return false;
    }
    if (left.callback == nullptr && right.callback == nullptr) {
        return true;
    }
    ani_boolean rs;
    left.env->Reference_StrictEquals(left.callback, right.callback, &rs);
    return rs == ANI_TRUE;
}

ani_ref CreateInt(ani_env* env, ani_int value)
{
    ani_class cls;
    env->FindClass("Lstd/core/Int;", &cls);
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", "I:V", &ctor);
    ani_object rs;
    env->Object_New(cls, ctor, &rs, value);
    return rs;
}

ani_string AceWrapStringToAni(ani_env* env, std::string str)
{
    ani_string aniStr;
    ani_status status = env->String_NewUTF8(str.c_str(), str.size(), &aniStr);
    if (ANI_OK != status) {
        LOGE("Can not convert string to ani_string.");
        return nullptr;
    }
    return aniStr;
}

ani_ref AceWrapStringToObject(ani_env* env, const std::string str)
{
    ani_ref undefinedResult;
    env->GetUndefined(&undefinedResult);
    ani_class cls = nullptr;
    if (ANI_OK != env->FindClass("L@ohos/app/ability/Want/RecordSerializeTool;", &cls)) {
        LOGE("plugin-ani FindClass RecordSerializeTool failed");
        return undefinedResult;
    }
    if (cls == nullptr) {
        LOGE("plugin-ani RecordSerializeTool class null");
        return undefinedResult;
    }
    ani_static_method parseMethod = nullptr;
    if (ANI_OK != env->Class_FindStaticMethod(cls, "parseNoThrow", nullptr, &parseMethod)) {
        LOGE("plugin-ani failed to get parseNoThrow method");
        return undefinedResult;
    }
    ani_ref kvObjectAniString;
    if (ANI_OK != env->Class_CallStaticMethod_Ref(cls, parseMethod, &kvObjectAniString, AceWrapStringToAni(env, str))) {
        LOGE("plugin-ani failed to call parseNoThrow method");
        return undefinedResult;
    }
    ani_boolean isUndefined = true;
    if (ANI_OK != env->Reference_IsUndefined(kvObjectAniString, &isUndefined) || isUndefined) {
        LOGE("plugin-ani parseNoThrow is null");
        return undefinedResult;
    }
    return kvObjectAniString;
}

std::string AniStringToNativeString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);
   
    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);
    
    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

ani_status GetAniKVObjectPropertyByName(ani_env* env, ani_object parameters, std::string propertyName,
    std::string &propertyValue)
{
    ani_ref kvObj;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(parameters, propertyName.c_str(), &kvObj)) {
        LOGE("plugin-ani GetAniKVObjectPropertyByName %{public}s error", propertyName.c_str());
        return ANI_ERROR;
    }
    ani_boolean isUndefined = true;
    if (ANI_OK != env->Reference_IsUndefined(kvObj, &isUndefined) || isUndefined) {
        LOGE("plugin-ani GetAniKVObjectPropertyByName %{public}s is null", propertyName.c_str());
        return ANI_ERROR;
    }
    ani_class cls = nullptr;
    if (ANI_OK != env->FindClass("L@ohos/app/ability/Want/RecordSerializeTool;", &cls)) {
        LOGE("plugin-ani FindClass RecordSerializeTool failed");
        return ANI_ERROR;
    }
    if (cls == nullptr) {
        LOGE("plugin-ani RecordSerializeTool class null");
        return ANI_ERROR;
    }
    ani_static_method stringifyMethod = nullptr;
    if (ANI_OK != env->Class_FindStaticMethod(cls, "stringifyNoThrow", nullptr, &stringifyMethod)) {
        LOGE("plugin-ani failed to get stringifyNoThrow method");
        return ANI_ERROR;
    }
    ani_ref kvObjectAniString;
    if (ANI_OK != env->Class_CallStaticMethod_Ref(cls, stringifyMethod, &kvObjectAniString, kvObj)) {
        LOGE("plugin-ani failed to call stringifyNoThrow method");
        return ANI_ERROR;
    }
    if (ANI_OK != env->Reference_IsUndefined(kvObjectAniString, &isUndefined) || isUndefined) {
        LOGE("plugin-ani GetAniKVObjectPropertyByName %{public}s is null", propertyName.c_str());
        return ANI_ERROR;
    }
    propertyValue = AniStringToNativeString(env, reinterpret_cast<ani_string>(kvObjectAniString));
    return ANI_OK;
}

ani_status GetAniStringPropertyByName(ani_env* env, ani_object parameters, std::string propertyName,
    std::string &propertyValue)
{
    ani_ref valueAni;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(parameters, propertyName.c_str(), &valueAni)) {
        LOGE("plugin-ani GetPropertyByName %{public}s error", propertyName.c_str());
        return ANI_ERROR;
    }
    ani_boolean isUndefined = true;
    if (ANI_OK != env->Reference_IsUndefined(valueAni, &isUndefined) || isUndefined) {
        LOGE("plugin-ani GetPropertyByName %{public}s is null", propertyName.c_str());
        return ANI_ERROR;
    }
    propertyValue = AniStringToNativeString(env, reinterpret_cast<ani_string>(valueAni));
    return ANI_OK;
}
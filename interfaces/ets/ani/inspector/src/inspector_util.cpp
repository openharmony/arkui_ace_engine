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
#include "inspector_util.h"
#include "base/log/log_wrapper.h"
#include "frameworks/base/error/error_code.h"
 
namespace OHOS::Ace {
void AniThrow(ani_env *env, const std::string &errMsg, int32_t errorCode)
{
    ani_class errCls;
    if (ANI_OK != env->FindClass("@ohos.base.BusinessError", &errCls)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "FindClass BusinessError failed.");
        return;
    }
    ani_method errCtor {};
    if (ANI_OK != env->Class_FindMethod(errCls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &errCtor)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "FindMethod escompat.Error failed.");
        return;
    }
    ani_string resultString {};
    if (ANI_OK != env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &resultString)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Covert string to ani string failed.");
        return;
    }
    ani_ref undefinedRef {};
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Get undefined failed.");
        return;
    }
    ani_object errObj {};
    if (ANI_OK != env->Object_New(errCls, errCtor, &errObj, resultString, undefinedRef)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Create ani error object failed.");
        return;
    }
    if (ANI_OK != env->Object_SetFieldByName_Int(errObj, "code", static_cast<ani_int>(errorCode))) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Set error code failed.");
        return;
    }
    if (ANI_OK != env->Object_SetFieldByName_Ref(errObj, "message", resultString)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Set error message failed.");
        return;
    }
    if (ANI_OK != env->ThrowError(static_cast<ani_error>(errObj))) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Throw ani error object failed.");
        return;
    }
}
 
ani_status ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str, std::string& str)
{
    ani_size strSize;
    ani_status status = env->String_GetUTF8Size(ani_str, &strSize);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani String_GetUTF8Size failed %{public}d.", status);
        return status;
    }
   
    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();
 
    ani_size bytes_written = 0;
    status = env->String_GetUTF8(ani_str, utf8Buffer, buffer.size(), &bytes_written);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani String_GetUTF8 failed %{public}d.", status);
        return status;
    }
    
    utf8Buffer[bytes_written] = '\0';
    str = std::string(utf8Buffer);
    return status;
}
 
NG::InspectorFilter GetInspectorFilter(ani_env *env, const ani_array& filters, bool& isLayoutInspector)
{
    NG::InspectorFilter inspectorFilter;
    ani_size size;
    if (filters != nullptr && !IsUndefinedRef(env, filters) && ANI_OK == env->Array_GetLength(filters, &size)) {
        for (ani_size i = 0; i < size; i++) {
            ani_ref string_ref;
            if (ANI_OK != env->Array_Get(filters, i, &string_ref)) {
                TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "Array_Get FAILED index:%{public}zu", i);
                continue;
            }
            std::string filterItem;
            if (ANI_OK != ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(string_ref), filterItem)) {
                TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "ANIStringToStdString FAILED index:%{public}zu", i);
                continue;
            }
            if (filterItem == "isLayoutInspector") {
                isLayoutInspector = true;
                continue;
            }
            inspectorFilter.AddFilterAttr(filterItem);
        }
    }
    return inspectorFilter;
}

bool IsUndefinedRef(ani_env *env, ani_ref object_ref)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(object_ref, &isUndefined)) {
        return false;
    }
    return isUndefined == ANI_TRUE;
}
} // namespace OHOS::Ace
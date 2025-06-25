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
#include "ani_utils.h"
#include "drag_controller_utils.h"

namespace OHOS::Ace::NG {
ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class errClass;
    if (ANI_OK != env->FindClass("L@ohos/base/BusinessError;", &errClass)) {
        LOGE("AceLogTag::ACE_DRAG, find class failed");
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(errClass, "<ctor>", ":V", &ctor)) {
        LOGE("AceLogTag::ACE_DRAG, Cannot find constructor for class.");
        return nullptr;
    }
    ani_string errMessage;
    if (ANI_OK != env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage)) {
        LOGE("AceLogTag::ACE_DRAG, Convert string to ani string failed.");
        return nullptr;
    }
    ani_object errObj;
    if (ANI_OK != env->Object_New(errClass, ctor, &errObj)) {
        LOGE("AceLogTag::ACE_DRAG, Cannot create ani error object.");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetFieldByName_Double(errObj, "code", static_cast<ani_double>(code))) {
        LOGE("AceLogTag::ACE_DRAG, set error code failed");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(errObj, "message", errMessage)) {
        LOGE("AceLogTag::ACE_DRAG, set error message failed");
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}

void AniThrow(ani_env* env, const std::string& errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = GetErrorObject(env, errMsg, code);
    if (errObj == nullptr) {
        LOGE("AceLogTag::ACE_DRAG, get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(errObj)) {
        LOGE("AceLogTag::ACE_DRAG, throw ani error object failed!");
        return;
    }
}

bool IsUndefinedObject(ani_env* env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(objectRef, &isUndefined)) {
        return false;
    }
    return static_cast<bool>(isUndefined);
}

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
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

bool IsFunctionObject(ani_env* env, ani_ref obj)
{
    ani_class funcClass;
    ani_status status = ANI_OK;
    if ((status = env->FindClass("Lstd/core/Function0;", &funcClass)) != ANI_OK) {
        return false;
    }
    ani_boolean result;
    if ((status = env->Object_InstanceOf(static_cast<ani_object>(obj), funcClass, &result)) != ANI_OK) {
        return false;
    }
    return static_cast<bool>(result);
}

bool IsBigIntObject(ani_env* env, ani_ref obj)
{
    ani_class bigIntClass;
    ani_status status = ANI_OK;
    if ((ANI_OK != env->FindClass("Lescompat/BigInt;", &bigIntClass)) != ANI_OK) {
        return false;
    }
    ani_boolean result;
    if ((status = env->Object_InstanceOf(static_cast<ani_object>(obj), bigIntClass, &result)) != ANI_OK) {
        return false;
    }
    return result;
}

bool IsFunctionObjectWith2Param(ani_env* env, ani_ref obj)
{
    ani_class funcClass;
    env->FindClass("Lstd/core/Function2;", &funcClass);
    ani_boolean result;
    env->Object_InstanceOf(static_cast<ani_object>(obj), funcClass, &result);
    return static_cast<bool>(result);
}

bool IsNumberObject(ani_env* env, ani_ref obj)
{
    ani_class numberClass;
    env->FindClass("Lstd/core/Numeric;", &numberClass);
    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(obj), numberClass, &isNumber);
    return static_cast<bool>(isNumber);
}

bool IsInt32Object(ani_env* env, ani_ref obj)
{
    ani_class numberClass;
    env->FindClass("Lstd/core/Int;", &numberClass);
    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(obj), numberClass, &isNumber);
    return static_cast<bool>(isNumber);
}

bool IsStringObject(ani_env* env, ani_ref obj)
{
    ani_class stringClass;
    env->FindClass("Lstd/core/String;", &stringClass);
    ani_boolean isString;
    env->Object_InstanceOf(static_cast<ani_object>(obj), stringClass, &isString);
    return static_cast<bool>(isString);
}

bool IsArrayObject(ani_env* env, ani_ref obj)
{
    ani_class arrayClass;
    env->FindClass("Lescompat/Array;", &arrayClass);
    ani_boolean isArray;
    env->Object_InstanceOf(static_cast<ani_object>(obj), arrayClass, &isArray);
    return static_cast<bool>(isArray);
}

bool IsBooleanObject(ani_env* env, ani_ref obj)
{
    ani_class booleanClass;
    env->FindClass("Lstd/core/Boolean;", &booleanClass);
    ani_boolean isBoolean;
    env->Object_InstanceOf(static_cast<ani_object>(obj), booleanClass, &isBoolean);
    return static_cast<bool>(isBoolean);
}

bool GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue)
{
    auto status = ANI_OK;
    ani_long value;
    if ((status = env->Object_CallMethodByName_Long(object, "unboxed", ":J", &value)) != ANI_OK) {
        return false;
    }
    longValue = value;
    return true;
}

bool GetEnumItem([[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem)
{
    ani_enum enumType;
    auto status = ANI_OK;
    static const char* namespaceName = "L@ohos/arkui/dragController/dragController;";
    ani_namespace nns;
    if ((status = env->FindNamespace(namespaceName, &nns)) != ANI_OK) {
        LOGE("AceLogTag::ACE_DRAG, find dragController namespace fail. statsu = %{public}d", status);
        return false;
    }
    if ((status = env->Namespace_FindEnum(nns, enumName, &enumType)) != ANI_OK) {
        LOGE("AceLogTag::ACE_DRAG, find DragStatus Enum fail. statsu = %{public}d", status);
        return false;
    }
    if ((status = env->Enum_GetEnumItemByIndex(enumType, index, &enumItem)) != ANI_OK) {
        LOGE("AceLogTag::ACE_DRAG, get DragStatus Enum fail. statsu = %{public}d", status);
        return false;
    }
    return true;
}

bool IsDragPreviewModeEnum(ani_env *env, ani_ref obj)
{
    static const char *namespaceName = "L@ohos/arkui/dragController/dragController;";
    ani_namespace nns;
    if (ANI_OK != env->FindNamespace(namespaceName, &nns)) {
        LOGE("AceLogTag::ACE_DRAG, find dragController namespace fail.");
        return false;
    }
    static const char *className = "LDragPreviewMode;";
    ani_enum enumType;
    if (ANI_OK != env->Namespace_FindEnum(nns, className, &enumType)) {
        LOGE("AceLogTag::ACE_DRAG, find DragPreviewMode calss fail.");
        return false;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(obj), enumType, &isEnum)) {
        LOGE("AceLogTag::ACE_DRAG, object is not DragPreviewMode instance.");
        return false;
    }
    return static_cast<bool>(isEnum);
}
} // namespace OHOS::Ace::NG
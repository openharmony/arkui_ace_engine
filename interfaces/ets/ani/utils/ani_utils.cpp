/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <unordered_map>

#include "ani_utils.h"

#include "bridge/common/utils/utils.h"
#include "frameworks/base/error/error_code.h"

namespace OHOS::Ace::AniUtils {

static const std::unordered_map<int32_t, std::string> ERROR_CODE_TO_MSG {
    { ERROR_CODE_PERMISSION_DENIED, "Permission denied. " },
    { ERROR_CODE_PARAM_INVALID, "Parameter error. " },
    { ERROR_CODE_SYSTEMCAP_ERROR, "Capability not supported. " },
    { ERROR_CODE_INTERNAL_ERROR, "Internal error. " },
    { ERROR_CODE_URI_ERROR, "Uri error. " },
    { ERROR_CODE_PAGE_STACK_FULL, "Page stack error. " },
    { ERROR_CODE_URI_ERROR_LITE, "Uri error. " },
    { ERROR_CODE_DIALOG_CONTENT_ERROR, "Dialog content error. " },
    { ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST, "Dialog content already exist. " },
    { ERROR_CODE_DIALOG_CONTENT_NOT_FOUND, "Dialog content not found. " },
    { ERROR_CODE_OVERLAY_CANNOT_OPEN_DUE_TO_SYSTEM_WINDOW,
        "The overlay cannot be opened due to the system pop-up window." },
    { ERROR_CODE_TOAST_NOT_FOUND, "Toast not found. " }
};

ani_object CreateANIIntObject(ani_env* env, int32_t intValue)
{
    ani_class intCls {};
    env->FindClass("std.core.Int", &intCls);
    ani_method ctor {};
    env->Class_FindMethod(intCls, "<ctor>", "i:", &ctor);
    ani_object result {};
    ani_int aniInt = static_cast<ani_int>(intValue);
    ani_status status = env->Object_New(intCls, ctor, &result, aniInt);
    if (status != ANI_OK) {
        ani_ref undefinedRef;
        env->GetUndefined(&undefinedRef);
        return static_cast<ani_object>(undefinedRef);
    }
    return result;
}

ani_object CreateANILongObject(ani_env* env, int64_t longValue)
{
    ani_class longCls {};
    env->FindClass("std.core.Long", &longCls);
    ani_method ctor {};
    env->Class_FindMethod(longCls, "<ctor>", "l:", &ctor);
    ani_object result {};
    ani_long aniLong = static_cast<ani_long>(longValue);
    ani_status status = env->Object_New(longCls, ctor, &result, aniLong);
    if (status != ANI_OK) {
        ani_ref undefinedRef;
        env->GetUndefined(&undefinedRef);
        return static_cast<ani_object>(undefinedRef);
    }
    return result;
}

ani_object CreateANIDoubleObject(ani_env* env, double doubleValue)
{
    ani_class doubleCls {};
    env->FindClass("std.core.Double", &doubleCls);
    ani_method ctor {};
    env->Class_FindMethod(doubleCls, "<ctor>", "d:", &ctor);
    ani_object result {};
    ani_double aniDouble = static_cast<ani_double>(doubleValue);
    ani_status status = env->Object_New(doubleCls, ctor, &result, aniDouble);
    if (status != ANI_OK) {
        ani_ref undefinedRef;
        env->GetUndefined(&undefinedRef);
        return static_cast<ani_object>(undefinedRef);
    }
    return result;
}

bool IsUndefinedObject(ani_env* env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    ani_status status = env->Reference_IsUndefined(objectRef, &isUndefined);
    if (status != ANI_OK) {
        return false;
    }
    return static_cast<bool>(isUndefined);
}

bool IsClassObject(ani_env* env, ani_object object, const char* classDescriptor)
{
    ani_class objectClass;
    ani_status status = env->FindClass(classDescriptor, &objectClass);
    if (status != ANI_OK) {
        return false;
    }

    ani_boolean isInstance;
    status = env->Object_InstanceOf(object, objectClass, &isInstance);
    if (status != ANI_OK) {
        return false;
    }
    return static_cast<bool>(isInstance);
}

bool IsArrayObject(ani_env* env, ani_object object)
{
    return IsClassObject(env, object, "std.core.Array");
}

bool IsArrayObject(ani_env* env, ani_ref ref)
{
    ani_object object = static_cast<ani_object>(ref);
    return IsArrayObject(env, object);
}

bool IsEnum(ani_env* env, ani_object object, const char* enumDescriptor)
{
    ani_enum valueEnum;
    ani_status status = env->FindEnum(enumDescriptor, &valueEnum);
    if (status != ANI_OK) {
        return false;
    }

    ani_boolean isEnum;
    status = env->Object_InstanceOf(object, valueEnum, &isEnum);
    if (status != ANI_OK) {
        return false;
    }
    return static_cast<bool>(isEnum);
}

bool GetBoolParam(ani_env* env, ani_ref ref, bool& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "std.core.Boolean")) {
        return false;
    }

    ani_boolean resultValue;
    ani_status status = env->Object_CallMethodByName_Boolean(object, "toBoolean", ":z", &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<bool>(resultValue);
    return true;
}

bool GetBoolParam(ani_env* env, ani_object object, const char* name, bool& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetBoolParam(env, resultRef, result);
}

bool GetInt32Param(ani_env* env, ani_ref ref, int32_t& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "std.core.Int")) {
        return false;
    }

    ani_int resultValue;
    ani_status status = env->Object_CallMethodByName_Int(object, "toInt", ":i", &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<int32_t>(resultValue);
    return true;
}

bool GetInt32Param(ani_env* env, ani_object object, const char* name, int32_t& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetInt32Param(env, resultRef, result);
}

bool GetInt64Param(ani_env* env, ani_ref ref, int64_t& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "std.core.Long")) {
        return false;
    }

    ani_long resultValue;
    ani_status status = env->Object_CallMethodByName_Long(object, "toLong", ":l", &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<int64_t>(resultValue);
    return true;
}

bool GetInt64Param(ani_env* env, ani_object object, const char* name, int64_t& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetInt64Param(env, resultRef, result);
}

bool GetDoubleParam(ani_env* env, ani_ref ref, double& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "std.core.Double")) {
        return false;
    }

    ani_double resultValue;
    ani_status status = env->Object_CallMethodByName_Double(object, "toDouble", ":d", &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<double>(resultValue);
    return true;
}

bool GetDoubleParam(ani_env* env, ani_object object, const char* name, double& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetDoubleParam(env, resultRef, result);
}

bool GetDoubleParamOpt(ani_env* env, ani_object object, const char* name, std::optional<double>& result)
{
    double resultValue;
    if (!GetDoubleParam(env, object, name, resultValue)) {
        return false;
    }
    result = std::make_optional<double>(resultValue);
    return true;
}

std::string ANIStringToStdString(ani_env* env, ani_string aniStr)
{
    ani_size strSize;
    env->String_GetUTF8Size(aniStr, &strSize);

    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();

    ani_size bytesWritten = 0;
    env->String_GetUTF8(aniStr, utf8Buffer, strSize + 1, &bytesWritten);

    utf8Buffer[bytesWritten] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

bool GetStringParam(ani_env* env, ani_ref ref, std::string& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "std.core.String")) {
        return false;
    }
    result = ANIStringToStdString(env, static_cast<ani_string>(object));
    return true;
}

bool GetStringParam(ani_env* env, ani_object object, const char* name, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetStringParam(env, resultRef, result);
}

bool GetStringParamOpt(ani_env* env, ani_object object, const char* name, std::optional<std::string>& result)
{
    std::string resultStr;
    if (!GetStringParam(env, object, name, resultStr)) {
        return false;
    }
    result = std::make_optional<std::string>(resultStr);
    return true;
}

bool GetStringArrayParam(ani_env* env, ani_object object, const char* name, std::vector<std::string>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef) || !IsArrayObject(env, resultRef)) {
        return false;
    }

    ani_size length;
    ani_array resultObj = static_cast<ani_array>(resultRef);
    status = env->Array_GetLength(resultObj, &length);
    if (status != ANI_OK) {
        return false;
    }

    std::vector<std::string> stringArray;
    for (int32_t i = 0; i < int32_t(length); i++) {
        ani_ref itemRef;
        status = env->Array_Get(resultObj, static_cast<ani_size>(i), &itemRef);
        if (status != ANI_OK) {
            continue;
        }
        stringArray.emplace_back(ANIStringToStdString(env, static_cast<ani_string>(itemRef)));
    }
    result = stringArray;
    return true;
}

bool GetEnumInt(ani_env* env, ani_object resultObj, const char* enumDescriptor, int32_t& result)
{
    if (!IsEnum(env, resultObj, enumDescriptor)) {
        return false;
    }

    ani_int resultInt;
    ani_status status = env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(resultObj), &resultInt);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<int32_t>(resultInt);
    return true;
}

bool GetEnumInt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor, int32_t& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }
    ani_object resultObj = static_cast<ani_object>(resultRef);
    return GetEnumInt(env, resultObj, enumDescriptor, result);
}

bool GetEnumIntOpt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor,
    std::optional<int32_t>& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, name, enumDescriptor, resultInt)) {
        return false;
    }
    result = std::make_optional<int32_t>(resultInt);
    return true;
}

bool GetEnumString(ani_env* env, ani_object resultObj, const char* enumDescriptor, std::string& result)
{
    if (!IsEnum(env, resultObj, enumDescriptor)) {
        return false;
    }

    ani_string resultStr;
    ani_status status = env->EnumItem_GetValue_String(static_cast<ani_enum_item>(resultObj), &resultStr);
    if (status != ANI_OK) {
        return false;
    }
    result = ANIStringToStdString(env, resultStr);
    return true;
}

bool GetEnumString(ani_env* env, ani_object object, const char* name, const char* enumDescriptor, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }
    ani_object resultObj = static_cast<ani_object>(resultRef);
    return GetEnumString(env, resultObj, enumDescriptor, result);
}

bool GetEnumStringOpt(ani_env* env, ani_object object, const char* name, const char* enumDescriptor,
    std::optional<std::string>& result)
{
    std::string resultStr;
    if (!GetEnumString(env, object, name, enumDescriptor, resultStr)) {
        return false;
    }
    result = std::make_optional<std::string>(resultStr);
    return true;
}

bool GetFunctionParam(ani_env* env, ani_ref ref, std::function<void()>& result)
{
    ani_ref globalRef;
    ani_status status = env->GlobalReference_Create(ref, &globalRef);
    if (status != ANI_OK) {
        return false;
    }

    ani_vm* vm = nullptr;
    status = env->GetVM(&vm);
    if (status != ANI_OK || vm == nullptr) {
        return false;
    }

    result = [vm, globalRef]() {
        if (!globalRef) {
            return;
        }

        ani_env* env = nullptr;
        ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
        if (status != ANI_OK || env == nullptr) {
            return;
        }

        ani_fn_object func = static_cast<ani_fn_object>(globalRef);
        std::vector<ani_ref> args;
        ani_ref fnReturnVal {};
        status = env->FunctionalObject_Call(func, args.size(), args.data(), &fnReturnVal);
        env->GlobalReference_Delete(globalRef);
    };

    return true;
}

bool GetFunctionParam(ani_env* env, ani_object object, const char* name, std::function<void()>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }
    return GetFunctionParam(env, resultRef, result);
}

std::string ErrorToMessage(int32_t code)
{
    auto iter = ERROR_CODE_TO_MSG.find(code);
    return (iter != ERROR_CODE_TO_MSG.end()) ? iter->second : "";
}

std::string GetErrorMsg(int32_t errorCode)
{
    std::string strMsg;
    if (errorCode == ERROR_CODE_DIALOG_CONTENT_ERROR) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ERROR) + "The ComponentContent is incorrect.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) +
            "The ComponentContent has already been opened.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) + "The ComponentContent cannot be found.";
    } else {
        strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Build custom dialog failed.";
    }
    return strMsg;
}

ani_error GetErrorObject(ani_env *env, const std::string &errMsg, int32_t code)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class errClass;
    ani_status status = env->FindClass("@ohos.base.BusinessError", &errClass);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "find class failed. status: %{public}d", status);
        return nullptr;
    }
    ani_method ctor;
    status = env->Class_FindMethod(errClass, "<ctor>", ":", &ctor);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "cannot find constructor for class. status: %{public}d", status);
        return nullptr;
    }
    ani_string errMessage;
    status = env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "convert string to ani string failed. status: %{public}d", status);
        return nullptr;
    }
    ani_object errObj;
    status = env->Object_New(errClass, ctor, &errObj);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "cannot create ani error object. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Int(errObj, "code", static_cast<ani_int>(code));
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "set error code failed. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Ref(errObj, "message", errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "set error message failed. status: %{public}d", status);
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}

void AniThrow(ani_env *env, const std::string &errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = GetErrorObject(env, errMsg, code);
    if (errObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(errObj)) {
        TAG_LOGE(AceLogTag::ACE_OVERLAY, "throw ani error object failed!");
        return;
    }
}

} // namespace OHOS::Ace::AniUtils

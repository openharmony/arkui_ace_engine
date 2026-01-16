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

#include "drawableDescriptor_utils.h"

#include "core/common/container.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Ani {
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr int32_t DOLLAR_TOKENS_SIZE = 3;
constexpr int32_t MAYBE_MODULE_NAME_SIZE = 3;
const std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);

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

bool IsStringObject(ani_env* env, ani_ref objectRef)
{
    ani_class stringClass;
    if (ANI_OK != env->FindClass("std.core.String", &stringClass)) {
        return false;
    }
    ani_boolean isString;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(objectRef), stringClass, &isString)) {
        return false;
    }
    return static_cast<bool>(isString);
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
    ani_status status = env->Object_CallMethodByName_Int(object, "toInt", nullptr, &resultValue);
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

bool GetStringParamOpt(ani_env* env, ani_object object, const char* name, std::optional<std::string>& result)
{
    std::string resultStr;
    if (!GetStringParam(env, object, name, resultStr)) {
        return false;
    }
    result = std::make_optional<std::string>(resultStr);
    return true;
}

bool IsUndefinedObject(ani_env* env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    ani_status status = env->Reference_IsUndefined(objectRef, &isUndefined);
    if (status != ANI_OK) {
        return false;
    }
    return (bool)isUndefined;
}

bool IsNumberObject(ani_env* env, ani_ref objectRef)
{
    ani_class numberClass;
    if (ANI_OK != env->FindClass("std.core.Numeric", &numberClass)) {
        return false;
    }
    ani_boolean isNumber;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(objectRef), numberClass, &isNumber)) {
        return false;
    }
    return static_cast<bool>(isNumber);
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
    ani_status status = env->Object_CallMethodByName_Boolean(object, "toBoolean", nullptr, &resultValue);
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

bool GetArrayIntParam(ani_env* env, ani_ref ref, std::vector<int32_t>& result)
{
    if (IsUndefinedObject(env, ref) || !IsArrayObject(env, ref)) {
        return false;
    }

    ani_size length;
    ani_array arrayObj = static_cast<ani_array>(ref);
    ani_status status = env->Array_GetLength(arrayObj, &length);
    if (status != ANI_OK) {
        return false;
    }
    for (size_t i = 0; i < length; i++) {
        ani_ref itemRef;
        status = env->Object_CallMethodByName_Ref(
            static_cast<ani_object>(arrayObj), "$_get", "i:Y", &itemRef, (ani_int)i);
        if (status != ANI_OK) {
            return false;
        }

        ani_object itemObj = static_cast<ani_object>(itemRef);
        if (!IsClassObject(env, itemObj, "std.core.Int")) {
            return false;
        }

        ani_int itemValue;
        status = env->Object_CallMethodByName_Int(itemObj, "toInt", ":i", &itemValue);
        if (status != ANI_OK) {
            return false;
        }
        result.push_back(static_cast<int32_t>(itemValue));
    }
    return true;
}

bool GetArrayIntParam(ani_env* env, ani_object object, const char* name, std::vector<int32_t>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetArrayIntParam(env, resultRef, result);
}

bool ConvertResourceType(const std::string& typeName, ResourceType& resType)
{
    static const std::unordered_map<std::string, ResourceType> resTypeMap {
        { "color", ResourceType::COLOR },
        { "media", ResourceType::MEDIA },
        { "float", ResourceType::FLOAT },
        { "string", ResourceType::STRING },
        { "plural", ResourceType::PLURAL },
        { "pattern", ResourceType::PATTERN },
        { "boolean", ResourceType::BOOLEAN },
        { "integer", ResourceType::INTEGER },
        { "strarray", ResourceType::STRARRAY },
        { "intarray", ResourceType::INTARRAY },
    };
    auto iter = resTypeMap.find(typeName);
    if (iter == resTypeMap.end()) {
        return false;
    }

    resType = iter->second;
    return true;
}

bool GetDollarResource(ani_env* env, ani_ref ref, ResourceType& resType, std::string& resName, std::string& moduleName)
{
    std::string resPath;
    if (!GetStringParam(env, ref, resPath)) {
        return false;
    }

    // $r format like app.xxx.xxx, has 3 paragraph
    std::vector<std::string> tokens;
    OHOS::Ace::StringUtils::StringSplitter(resPath, '.', tokens);
    if (static_cast<int32_t>(tokens.size()) != DOLLAR_TOKENS_SIZE) {
        return false;
    }

    // [*] or app/hsp at least has 3 chars
    std::string maybeModuleName = tokens[0];
    if (maybeModuleName.size() < MAYBE_MODULE_NAME_SIZE) {
        return false;
    }

    char begin = *maybeModuleName.begin();
    char end = maybeModuleName.at(maybeModuleName.size() - 1);
    bool headCheckPass = false;
    if (begin == '[' && end == ']') {
        moduleName = maybeModuleName.substr(NUMBER_ONE, maybeModuleName.size() - NUMBER_TWO);
        headCheckPass = true;
    }
    if (std::find(RESOURCE_HEADS.begin(), RESOURCE_HEADS.end(), tokens[0]) == RESOURCE_HEADS.end() && !headCheckPass) {
        return false;
    }

    if (!ConvertResourceType(tokens[1], resType)) {
        return false;
    }
    resName = resPath;
    return true;
}

void ProcessResourceType(ani_env* env, ani_object value, ani_ref paramsRef, ani_size length, std::string resName)
{
    ani_object paramsObj = static_cast<ani_object>(paramsRef);
    ani_status status;
    std::vector<std::string> stringArray;
    for (int i = 0; i < int(length); i++) {
        ani_ref itemRef;
        status = env->Object_CallMethodByName_Ref(paramsObj, "$_get", "i:Y", &itemRef, (ani_int)i);
        if (status != ANI_OK) {
            continue;
        }
        auto itemStr = ANIStringToStdString(env, static_cast<ani_string>(itemRef));
        stringArray.emplace_back(itemStr);
    }

    ani_class stringCls = nullptr;
    status = env->FindClass("std.core.String", &stringCls);
    if (status != ANI_OK) {
        return;
    }

    ani_ref undefinedRef = nullptr;
    status = env->GetUndefined(&undefinedRef);
    if (status != ANI_OK) {
        return;
    }

    int32_t index = 0;
    ani_string firstStr;
    status = env->String_NewUTF8(resName.c_str(), resName.size(), &firstStr);
    if (status != ANI_OK) {
        status = env->Object_CallMethodByName_Void(paramsObj, "$_set", "iY:", index, firstStr);
        if (status != ANI_OK) {
            return;
        }
    }
    index++;

    for (auto string : stringArray) {
        ani_string aniStr;
        status = env->String_NewUTF8(string.c_str(), string.size(), &aniStr);
        if (status != ANI_OK) {
            break;
        }

        status = env->Object_CallMethodByName_Void(paramsObj, "$_set", "iY:", index, aniStr);
        if (status != ANI_OK) {
            break;
        }
        index++;
    }
}

void ModifyResourceParam(ani_env* env, ani_object object, const ResourceType& resType, const std::string& resName)
{
    // raw input : {"id":"app.xxx.xxx","params":[],"moduleName":"xxx","bundleName":"xxx"}
    // modified output : {"id":-1, "params":["app.xxx.xxx"],"type":xxxx,"moduleName":"xxx","bundleName":"xxx"}
    ani_ref paramsRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "params", &paramsRef);
    if (status != ANI_OK) {
        return;
    }

    if (IsUndefinedObject(env, paramsRef) || !IsArrayObject(env, paramsRef)) {
        return;
    }

    ani_double length;
    status = env->Object_GetPropertyByName_Double(static_cast<ani_object>(paramsRef), "length", &length);
    if (status != ANI_OK) {
        return;
    }

    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        ProcessResourceType(env, object, paramsRef, static_cast<size_t>(length), resName);
        return;
    }

    ani_string paramsStr;
    env->String_NewUTF8(resName.c_str(), resName.size(), &paramsStr);
    status = env->Object_SetPropertyByName_Ref(object, "params", static_cast<ani_ref>(paramsStr));
}

void CompleteResourceParamV1(ani_env* env, ani_object object)
{
    ani_ref idRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "id", &idRef);
    if (status != ANI_OK) {
        return;
    }

    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!GetDollarResource(env, idRef, resType, resName, moduleName)) {
        return;
    }

    ModifyResourceParam(env, object, resType, resName);
    ani_long aniId = static_cast<ani_long>(static_cast<int64_t>(UNKNOWN_RESOURCE_ID));
    status = env->Object_SetPropertyByName_Long(object, "id", aniId);
    if (status != ANI_OK) {
        return;
    }

    ani_int aniType = static_cast<ani_int>(static_cast<int32_t>(resType));
    status = env->Object_SetPropertyByName_Int(object, "type", aniType);
    if (status != ANI_OK) {
        return;
    }

    ani_ref bundleNameRef;
    status = env->Object_GetPropertyByName_Ref(object, "bundleName", &bundleNameRef);
    if (status != ANI_OK) {
        ani_string defautBundleName;
        env->String_NewUTF8("", 0, &defautBundleName);
        env->Object_SetPropertyByName_Ref(object, "bundleName", static_cast<ani_ref>(defautBundleName));
        return;
    }

    ani_ref moduleNameRef;
    status = env->Object_GetPropertyByName_Ref(object, "moduleName", &moduleNameRef);
    if (status != ANI_OK) {
        ani_string defautModuleName;
        env->String_NewUTF8("", 0, &defautModuleName);
        env->Object_SetPropertyByName_Ref(object, "moduleName", static_cast<ani_ref>(defautModuleName));
        return;
    }
}

void CompleteResourceParamV2(ani_env* env, ani_object object)
{
    ani_ref paramsRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "params", &paramsRef);
    if (status != ANI_OK) {
        return;
    }

    if (IsUndefinedObject(env, paramsRef)) {
        return;
    }

    ani_object paramsObj = static_cast<ani_object>(paramsRef);
    ani_double length;
    status = env->Object_GetPropertyByName_Double(paramsObj, "length", &length);
    if (status != ANI_OK) {
        return;
    }

    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!GetDollarResource(env, paramsRef, resType, resName, moduleName)) {
        return;
    }

    ani_int aniType = static_cast<ani_int>(static_cast<int32_t>(resType));
    status = env->Object_SetPropertyByName_Int(object, "type", aniType);
    if (status != ANI_OK) {
        return;
    }

    if (!moduleName.empty()) {
        ani_string moduleNameStr;
        env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &moduleNameStr);
        status = env->Object_SetPropertyByName_Ref(object, "moduleName", static_cast<ani_ref>(moduleNameStr));
        return;
    }
}

ResourceStruct CheckResourceStruct(ani_env* env, ani_object object)
{
    ani_long aniId;
    ani_status status = env->Object_GetPropertyByName_Long(object, "id", &aniId);
    if (status != ANI_OK) {
        ani_ref idRef;
        status = env->Object_GetPropertyByName_Ref(object, "id", &idRef);
        if (status != ANI_OK) {
            return ResourceStruct::CONSTANT;
        }
        return ResourceStruct::DYNAMIC_V1;
    }

    int32_t idInt = static_cast<int32_t>(aniId);
    if (idInt == UNKNOWN_RESOURCE_ID) {
        return ResourceStruct::DYNAMIC_V2;
    }
    return ResourceStruct::CONSTANT;
}

void CompleteResourceParam(ani_env* env, ani_object object)
{
    PrefixEmptyBundleName(env, object);
    ResourceStruct resourceStruct = CheckResourceStruct(env, object);
    switch (resourceStruct) {
        case ResourceStruct::CONSTANT:
            return;
        case ResourceStruct::DYNAMIC_V1:
            CompleteResourceParamV1(env, object);
            return;
        case ResourceStruct::DYNAMIC_V2:
            CompleteResourceParamV2(env, object);
            return;
        default:
            return;
    }
}

bool GetResourceObjectParams(
    ani_env* env, ani_object object, const char* name, std::vector<ResourceObjectParams>& result)
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

    std::vector<ResourceObjectParams> resourceObjectParamsArray;
    for (int i = 0; i < static_cast<int>(length); i++) {
        ani_ref itemRef;
        status = env->Array_Get(resultObj, (ani_size)i, &itemRef);
        if (status != ANI_OK) {
            continue;
        }
        ResourceObjectParams resObjParams { .value = ANIStringToStdString(env, static_cast<ani_string>(itemRef)) };
        if (IsStringObject(env, itemRef)) {
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (IsNumberObject(env, itemRef)) {
            if (std::regex_match(ANIStringToStdString(env, static_cast<ani_string>(itemRef)), FLOAT_PATTERN)) {
                resObjParams.type = ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.type = ResourceObjectParamType::INT;
            }
        }

        resourceObjectParamsArray.emplace_back(resObjParams);
    }
    result = resourceObjectParamsArray;
    return true;
}

void PrefixEmptyBundleName(ani_env* env, ani_object object)
{
    ani_ref bundleNameRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "bundleName", &bundleNameRef);
    if (status != ANI_OK) {
        return;
    }

    auto bundleName = ANIStringToStdString(env, static_cast<ani_string>(bundleNameRef));
    if (bundleName.empty()) {
        auto container = OHOS::Ace::Container::CurrentSafely();
        CHECK_NULL_VOID(container);
        bundleName = container->GetBundleName();

        ani_string bundleNameStr;
        status = env->String_NewUTF8(bundleName.c_str(), bundleName.size(), &bundleNameStr);
        if (status != ANI_OK) {
            return;
        }
        status = env->Object_SetPropertyByName_Ref(object, "bundleName", static_cast<ani_ref>(bundleNameStr));
    }
}

bool GetResourceParam(ani_env* env, ani_object object, ResourceObjectInfo& result)
{
    if (!IsClassObject(env, object, "global.resource.Resource")) {
        return false;
    }

    CompleteResourceParam(env, object);
    ani_long aniId;
    ani_status status = env->Object_GetPropertyByName_Long(object, "id", &aniId);
    if (status == ANI_OK) {
        result.resId = static_cast<int32_t>(aniId);
    }
    GetStringParamOpt(env, object, "bundleName", result.bundleName);
    GetStringParamOpt(env, object, "moduleName", result.moduleName);
    GetInt32Param(env, object, "type", result.type);
    GetResourceObjectParams(env, object, "params", result.params);
    return true;
}

ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class errClass;
    ani_status status = env->FindClass("@ohos.base.BusinessError", &errClass);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "find class failed. status: %{public}d", status);
        return nullptr;
    }
    ani_method ctor;
    status = env->Class_FindMethod(errClass, "<ctor>", ":", &ctor);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "cannot find constructor for class. status: %{public}d", status);
        return nullptr;
    }
    ani_string errMessage;
    status = env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "convert string to ani string failed. status: %{public}d", status);
        return nullptr;
    }
    ani_object errObj;
    status = env->Object_New(errClass, ctor, &errObj);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "cannot create ani error object. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Int(errObj, "code", static_cast<ani_int>(code));
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "set error code failed. status: %{public}d", status);
        return nullptr;
    }
    status = env->Object_SetPropertyByName_Ref(errObj, "message", errMessage);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "set error message failed. status: %{public}d", status);
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}
} // namespace OHOS::Ace::Ani
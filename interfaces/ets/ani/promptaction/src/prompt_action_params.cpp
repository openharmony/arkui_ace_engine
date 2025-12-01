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

#include "prompt_action_params.h"

#include "core/pipeline/pipeline_base.h"

std::unordered_map<int, OHOS::Ace::BlurStyle> blurStyleMap = {
    { PromptActionBlurStyle::THIN, OHOS::Ace::BlurStyle::THIN },
    { PromptActionBlurStyle::REGULAR, OHOS::Ace::BlurStyle::REGULAR },
    { PromptActionBlurStyle::THICK, OHOS::Ace::BlurStyle::THICK },
    { PromptActionBlurStyle::BACKGROUND_THIN, OHOS::Ace::BlurStyle::BACKGROUND_THIN },
    { PromptActionBlurStyle::BACKGROUND_REGULAR, OHOS::Ace::BlurStyle::BACKGROUND_REGULAR },
    { PromptActionBlurStyle::BACKGROUND_THICK, OHOS::Ace::BlurStyle::BACKGROUND_THICK },
    { PromptActionBlurStyle::BACKGROUND_ULTRA_THICK, OHOS::Ace::BlurStyle::BACKGROUND_ULTRA_THICK },
    { PromptActionBlurStyle::NONE, OHOS::Ace::BlurStyle::NO_MATERIAL },
    { PromptActionBlurStyle::COMPONENT_ULTRA_THIN, OHOS::Ace::BlurStyle::COMPONENT_ULTRA_THIN },
    { PromptActionBlurStyle::COMPONENT_THIN, OHOS::Ace::BlurStyle::COMPONENT_THIN },
    { PromptActionBlurStyle::COMPONENT_REGULAR, OHOS::Ace::BlurStyle::COMPONENT_REGULAR },
    { PromptActionBlurStyle::COMPONENT_THICK, OHOS::Ace::BlurStyle::COMPONENT_THICK },
    { PromptActionBlurStyle::COMPONENT_ULTRA_THICK, OHOS::Ace::BlurStyle::COMPONENT_ULTRA_THICK },
};

std::unordered_map<int, uint32_t> colorMap = {
    {PromptActionColor::PROMPT_ACTION_COLOR_WHITE, 0xffffff | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_BLACK, 0x000000 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_BLUE, 0x0000ff | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_BROWN, 0xa52a2a | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_GRAY, 0x808080 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_GREEN, 0x008000 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_GREY, 0x808080 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_ORANGE, 0xffa500 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_PINK, 0xffc0cb | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_RED, 0xff0000 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_YELLOW, 0xffff00 | 0xFF000000},
    {PromptActionColor::PROMPT_ACTION_COLOR_TRANSPARENT, 0x00000000},
};

ani_object CreateANIIntObject(ani_env *env, int32_t intValue)
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

ani_object CreateANILongObject(ani_env *env, int64_t longValue)
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

ani_object CreateANIDoubleObject(ani_env *env, double doubleValue)
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

bool IsUndefinedObject(ani_env *env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    ani_status status = env->Reference_IsUndefined(objectRef, &isUndefined);
    if (status != ANI_OK) {
        return false;
    }
    return (bool)isUndefined;
}

bool IsClassObject(ani_env *env, ani_object object, const char *class_descriptor)
{
    ani_class objectClass;
    ani_status status = env->FindClass(class_descriptor, &objectClass);
    if (status != ANI_OK) {
        return false;
    }

    ani_boolean isInstance;
    status = env->Object_InstanceOf(object, objectClass, &isInstance);
    if (status != ANI_OK) {
        return false;
    }
    return (bool)isInstance;
}

bool IsArrayObject(ani_env *env, ani_object object)
{
    return IsClassObject(env, object, "std.core.Array");
}

bool IsArrayObject(ani_env *env, ani_ref ref)
{
    ani_object object = static_cast<ani_object>(ref);
    return IsArrayObject(env, object);
}

bool IsEnum(ani_env *env, ani_object object, const char *enum_descriptor)
{
    ani_enum valueEnum;
    ani_status status = env->FindEnum(enum_descriptor, &valueEnum);
    if (status != ANI_OK) {
        return false;
    }

    ani_boolean isEnum;
    status = env->Object_InstanceOf(object, valueEnum, &isEnum);
    if (status != ANI_OK) {
        return false;
    }
    return (bool)isEnum;
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

bool GetBoolParam(ani_env* env, ani_object object, const char *name, bool& result)
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
    ani_status status = env->Object_CallMethodByName_Int(object, "toInt", nullptr, &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<int32_t>(resultValue);
    return true;
}

bool GetInt32Param(ani_env* env, ani_object object, const char *name, int32_t& result)
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
    ani_status status = env->Object_CallMethodByName_Long(object, "toLong", nullptr, &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<int64_t>(resultValue);
    return true;
}

bool GetInt64Param(ani_env* env, ani_object object, const char *name, int64_t& result)
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
    ani_status status = env->Object_CallMethodByName_Double(object, "toDouble", nullptr, &resultValue);
    if (status != ANI_OK) {
        return false;
    }
    result = static_cast<double>(resultValue);
    return true;
}

bool GetDoubleParam(ani_env* env, ani_object object, const char *name, double& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetDoubleParam(env, resultRef, result);
}

bool GetDoubleParamOpt(ani_env *env, ani_object object, const char *name, std::optional<double>& result)
{
    double resultValue;
    if (!GetDoubleParam(env, object, name, resultValue)) {
        return false;
    }
    result = std::make_optional<double>(resultValue);
    return true;
}

std::string ANIStringToStdString(ani_env *env, ani_string ani_str)
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

bool GetStringParam(ani_env *env, ani_ref ref, std::string& result)
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

bool GetStringParam(ani_env *env, ani_object object, const char *name, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetStringParam(env, resultRef, result);
}

bool GetStringParamOpt(ani_env *env, ani_object object, const char *name, std::optional<std::string>& result)
{
    std::string resultStr;
    if (!GetStringParam(env, object, name, resultStr)) {
        return false;
    }
    result = std::make_optional<std::string>(resultStr);
    return true;
}

bool GetStringArrayParam(ani_env *env, ani_object object, const char *name, std::vector<std::string>& result)
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
    for (int i = 0; i < int(length); i++) {
        ani_ref itemRef;
        status = env->Array_Get(resultObj, (ani_size)i, &itemRef);
        if (status != ANI_OK) {
            continue;
        }
        stringArray.emplace_back(ANIStringToStdString(env, static_cast<ani_string>(itemRef)));
    }
    result = stringArray;
    return true;
}

bool GetEnumInt(ani_env* env, ani_object resultObj, const char *enum_descriptor, int32_t& result)
{
    if (!IsEnum(env, resultObj, enum_descriptor)) {
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

bool GetEnumInt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor, int32_t& result)
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
    return GetEnumInt(env, resultObj, enum_descriptor, result);
}

bool GetEnumIntOpt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor,
    std::optional<int32_t>& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, name, enum_descriptor, resultInt)) {
        return false;
    }
    result = std::make_optional<int32_t>(resultInt);
    return true;
}

bool GetEnumString(ani_env* env, ani_object resultObj, const char *enum_descriptor, std::string& result)
{
    if (!IsEnum(env, resultObj, enum_descriptor)) {
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

bool GetEnumString(ani_env* env, ani_object object, const char *name, const char *enum_descriptor, std::string& result)
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
    return GetEnumString(env, resultObj, enum_descriptor, result);
}

bool GetEnumStringOpt(ani_env* env, ani_object object, const char *name, const char *enum_descriptor,
    std::optional<std::string>& result)
{
    std::string resultStr;
    if (!GetEnumString(env, object, name, enum_descriptor, resultStr)) {
        return false;
    }
    result = std::make_optional<std::string>(resultStr);
    return true;
}

bool GetFunctionParam(ani_env *env, ani_ref ref, std::function<void()>& result)
{
    ani_ref globalRef;
    ani_status status = env->GlobalReference_Create(ref, &globalRef);
    if (status != ANI_OK) {
        return false;
    }

    ani_vm *vm = nullptr;
    status = env->GetVM(&vm);
    if (status != ANI_OK || vm == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetVM fail. status: %{public}d", status);
        return false;
    }

    result = [vm, globalRef]() {
        if (!globalRef) {
            return;
        }

        ani_env* env = nullptr;
        ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
        if (status != ANI_OK || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetEnv fail. status: %{public}d", status);
            return;
        }

        ani_fn_object func = static_cast<ani_fn_object>(globalRef);
        std::vector<ani_ref> args;
        ani_ref fnReturnVal {};
        status = env->FunctionalObject_Call(func, args.size(), args.data(), &fnReturnVal);
        env->GlobalReference_Delete(globalRef);
        if (status != ANI_OK) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] FunctionalObject_Call fail. status: %{public}d", status);
        }
    };
    return true;
}

bool GetFunctionParam(ani_env *env, ani_object object, const char *name, std::function<void()>& result)
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

void PrefixEmptyBundleName(ani_env *env, ani_object object)
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

ResourceStruct CheckResourceStruct(ani_env *env, ani_object object)
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

bool GetDollarResource(ani_env *env, ani_ref ref, ResourceType& resType, std::string& resName, std::string& moduleName)
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

void ProcessResourceType(ani_env *env, ani_object value, ani_ref paramsRef, ani_size length, std::string resName)
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

void ModifyResourceParam(ani_env *env, ani_object object, const ResourceType& resType, const std::string& resName)
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

void CompleteResourceParamV1(ani_env *env, ani_object object)
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

void CompleteResourceParamV2(ani_env *env, ani_object object)
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

void CompleteResourceParam(ani_env *env, ani_object object)
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

bool GetResourceParam(ani_env *env, ani_object object, ResourceInfo& result)
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
    GetStringArrayParam(env, object, "params", result.params);
    return true;
}

OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(
    const std::optional<std::string>& bundleName, const std::optional<std::string>& moduleName)
{
    auto container = OHOS::Ace::Container::Current();
    if (!container) {
        return nullptr;
    }

    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return nullptr;
    }

    auto themeManager = pipelineContext->GetThemeManager();
    if (!themeManager) {
        return nullptr;
    }

    if (bundleName.has_value() && moduleName.has_value()) {
        return themeManager->GetThemeConstants(bundleName.value_or(""), moduleName.value_or(""));
    }
    return themeManager->GetThemeConstants();
}

OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& result)
{
    OHOS::Ace::RefPtr<OHOS::Ace::ResourceAdapter> resourceAdapter = nullptr;
    OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> themeConstants = nullptr;
    if (OHOS::Ace::SystemProperties::GetResourceDecoupling()) {
        if (result.bundleName.has_value() && result.moduleName.has_value()) {
            auto bundleName = result.bundleName.value_or("");
            auto moduleName = result.moduleName.value_or("");
            auto resourceObject = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::ResourceObject>(
                bundleName, moduleName, OHOS::Ace::Container::CurrentIdSafely());
            resourceAdapter = OHOS::Ace::ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        } else {
            resourceAdapter = OHOS::Ace::ResourceManager::GetInstance().GetResourceAdapter(
                OHOS::Ace::Container::CurrentIdSafely());
        }
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(result.bundleName, result.moduleName);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

void ReplaceHolder(std::string& originStr, const std::vector<std::string>& params, uint32_t containCount)
{
    auto size = static_cast<uint32_t>(params.size());
    if (containCount == size) {
        return;
    }

    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matches;
    bool shortHolderType = false;
    bool firstMatch = true;
    uint32_t searchTime = 0;
    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (static_cast<uint32_t>(shortHolderType) ^ (static_cast<uint32_t>(pos.length() == 0))) {
                LOGE("wrong place holder,stop parse string");
                return;
            }
        }

        std::string replaceContentStr;
        std::string::size_type index = 0;
        if (shortHolderType) {
            index = static_cast<std::string::size_type>(searchTime + containCount);
        } else {
            int32_t indexTmp = OHOS::Ace::StringUtils::StringToInt(pos) + static_cast<int32_t>(containCount) - 1;
            if (indexTmp >= 0) {
                index = static_cast<std::string::size_type>(indexTmp);
            } else {
                LOGE("indexTmp err:%{public}d", indexTmp);
            }
        }

        if (static_cast<uint32_t>(index) < size) {
            replaceContentStr = params[index];
        } else {
            LOGE("index = %{public}d size = %{public}d", static_cast<uint32_t>(index), size);
        }
        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

std::string DimensionToString(OHOS::Ace::Dimension dimension)
{
    static const int32_t unitsNum = 6;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto" };
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == OHOS::Ace::DimensionUnit::NONE) {
        return OHOS::Ace::StringUtils::DoubleToString(value).append("none");
    }

    if (units[static_cast<int>(unit)] == units[percentIndex]) {
        return OHOS::Ace::StringUtils::DoubleToString(value * percentUnit).append(units[static_cast<int>(unit)]);
    }
    return OHOS::Ace::StringUtils::DoubleToString(value).append(units[static_cast<int>(unit)]);
}

bool ResourceToString(const ResourceInfo resourceInfo, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (resourceInfo.type == static_cast<int>(ResourceType::PLURAL)) {
        std::string pluralResults;
        if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
            auto count = OHOS::Ace::StringUtils::StringToInt(resourceInfo.params[1]);
            pluralResults = resourceWrapper->GetPluralStringByName(resourceInfo.params[0], count);
            ReplaceHolder(pluralResults, resourceInfo.params, PLURAL_HOLDER_INDEX);
        } else {
            auto count = OHOS::Ace::StringUtils::StringToInt(resourceInfo.params[0]);
            pluralResults = resourceWrapper->GetPluralString(resourceInfo.resId, count);
            ReplaceHolder(pluralResults, resourceInfo.params, 1);
        }
        result = pluralResults;
        return true;
    }

    if (resourceInfo.type == static_cast<int>(ResourceType::RAWFILE)) {
        auto fileName = resourceInfo.params[0];
        result = resourceWrapper->GetRawfile(fileName);
        return true;
    }

    if (resourceInfo.type == static_cast<int>(ResourceType::FLOAT)) {
        if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
            result = DimensionToString(resourceWrapper->GetDimensionByName(resourceInfo.params[0]));
        } else {
            result = DimensionToString(resourceWrapper->GetDimension(resourceInfo.resId));
        }
        return true;
    }

    if (resourceInfo.type == static_cast<int>(ResourceType::STRING)) {
        std::string originStr;
        if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
            originStr = resourceWrapper->GetStringByName(resourceInfo.params[0]);
            ReplaceHolder(originStr, resourceInfo.params, 1);
        } else {
            originStr = resourceWrapper->GetString(resourceInfo.resId);
            ReplaceHolder(originStr, resourceInfo.params, 0);
        }
        result = originStr;
        return true;
    }

    if (resourceInfo.type == static_cast<int>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resourceInfo.resId).ColorToString();
        return true;
    }

    if (resourceInfo.type == static_cast<int>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resourceInfo.resId));
        return true;
    }
    return false;
}

bool GetResourceStrParam(ani_env *env, ani_ref ref, std::string& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    ani_class resultClass;
    ani_status status = env->FindClass("global.resource.Resource", &resultClass);
    if (status != ANI_OK) {
        return false;
    }

    ani_object object = static_cast<ani_object>(ref);
    ani_boolean isInstance = false;
    status = env->Object_InstanceOf(object, resultClass, &isInstance);
    if (status != ANI_OK) {
        return false;
    }

    if (GetStringParam(env, ref, result)) {
        return true;
    }

    ResourceInfo resourceInfo;
    if (!GetResourceParam(env, object, resourceInfo)) {
        return false;
    }

    if (ResourceToString(resourceInfo, result)) {
        return true;
    }
    return false;
}

bool GetResourceStrParam(ani_env *env, ani_object object, const char *name, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetResourceStrParam(env, resultRef, result);
}

bool GetLengthParam(ani_env *env, ani_ref ref, OHOS::Ace::CalcDimension& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    double resultDouble;
    if (GetDoubleParam(env, ref, resultDouble)) {
        result.SetUnit(OHOS::Ace::DimensionUnit::VP);
        result.SetValue(resultDouble);
        return true;
    }

    std::string resultStr;
    if (GetResourceStrParam(env, ref, resultStr)) {
        result = OHOS::Ace::StringUtils::StringToCalcDimension(resultStr, false, OHOS::Ace::DimensionUnit::VP);
        return true;
    }
    return false;
}

bool GetLengthParam(ani_env *env, ani_object object, const char *name, OHOS::Ace::CalcDimension& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetLengthParam(env, resultRef, result);
}

bool GetColorParam(ani_env* env, ani_object object, std::string& result)
{
    if (!GetEnumString(env, object, "arkui.component.enums.Color", result)) {
        return false;
    }
    return true;
}

bool GetResourceColorParam(ani_env *env, ani_ref ref, OHOS::Ace::Color& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    std::string resultStr;
    if (GetStringParam(env, ref, resultStr)) {
        OHOS::Ace::Color::ParseColorString(resultStr, result);
        return true;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (GetColorParam(env, object, resultStr)) {
        OHOS::Ace::Color::ParseColorString(resultStr, result);
        return true;
    }

    double resultDouble;
    if (GetDoubleParam(env, ref, resultDouble)) {
        result = static_cast<OHOS::Ace::Color>(resultDouble);
        return true;
    }

    if (GetResourceStrParam(env, ref, resultStr)) {
        if (resultStr.size() == 0) {
            return false;
        }
        OHOS::Ace::Color::ParseColorString(resultStr, result);
        return true;
    }
    return false;
}

bool GetResourceColorParam(ani_env* env, ani_object object, const char *name, OHOS::Ace::Color& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetResourceColorParam(env, resultRef, result);
}

bool GetResourceColorParamOpt(ani_env* env, ani_object object, const char *name,
    std::optional<OHOS::Ace::Color>& result)
{
    OHOS::Ace::Color resultColor;
    if (!GetResourceColorParam(env, object, name, resultColor)) {
        return false;
    }
    result = std::make_optional<OHOS::Ace::Color>(resultColor);
    return true;
}

bool GetShadowStyleParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& shadow)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "arkui.component.common.ShadowStyle", resultInt)) {
        return false;
    }

    OHOS::Ace::ShadowStyle shadowStyle = static_cast<OHOS::Ace::ShadowStyle>(resultInt);
    if (shadowStyle == OHOS::Ace::ShadowStyle::None) {
        return true;
    }

    auto container = OHOS::Ace::Container::CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto shadowTheme = pipelineContext->GetTheme<OHOS::Ace::ShadowTheme>();
    if (!shadowTheme) {
        return false;
    }

    auto colorMode = container->GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

bool GetRadiusNumberToDouble(ani_env *env, ani_object object, double& result)
{
    if (!IsClassObject(env, object, "std.core.Numeric")) {
        return false;
    }

    double resultValue = 0.0;
    if (!GetDoubleParam(env, object, resultValue)) {
        return false;
    }

    if (OHOS::Ace::LessNotEqual(resultValue, 0.0)) {
        resultValue = 0.0;
    }
    result = resultValue;
    return true;
}

bool ResourceToDimension(const ResourceInfo resource, OHOS::Ace::CalcDimension& result)
{
    auto resourceWrapper = CreateResourceWrapper(resource);
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (resource.type == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resource.resId);
        return OHOS::Ace::StringUtils::StringToCalcDimensionNG(value, result, false);
    }

    if (resource.type == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resource.resId));
        OHOS::Ace::StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (resource.type == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resource.resId);
        return true;
    }
    return false;
}

bool GetRadiusResourceToDouble(ani_env *env, ani_object object, double& result)
{
    double radiusValue = 0.0;
    ResourceInfo resourceInfo;
    if (!GetResourceParam(env, object, resourceInfo)) {
        return false;
    }

    OHOS::Ace::CalcDimension radius;
    if (ResourceToDimension(resourceInfo, radius)) {
        radiusValue = OHOS::Ace::LessNotEqual(radius.Value(), 0.0) ? 0.0 : radius.Value();
    }
    result = radiusValue;
    return true;
}

bool GetShadowOptionsRadiusParam(ani_env *env, ani_object object, double& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "radius", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (GetRadiusNumberToDouble(env, resultObj, result)) {
        return true;
    }
    return GetRadiusResourceToDouble(env, resultObj, result);
}

bool GetShadowOptionsType(ani_env *env, ani_object object, int32_t& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "type", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    int32_t resultInt;
    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (!GetEnumInt(env, resultObj, "arkui.component.common.ShadowType", resultInt)) {
        return false;
    }

    if (resultInt != static_cast<int32_t>(OHOS::Ace::ShadowType::BLUR)) {
        resultInt = static_cast<int32_t>(OHOS::Ace::ShadowType::COLOR);
    }
    result = std::clamp(resultInt, static_cast<int32_t>(OHOS::Ace::ShadowType::COLOR),
        static_cast<int32_t>(OHOS::Ace::ShadowType::BLUR));
    return true;
}

bool GetShadowColorStrategy(ani_env *env, ani_object object, OHOS::Ace::ShadowColorStrategy& result)
{
    std::string resultStr;
    if (!GetEnumString(env, object, "arkui.component.enums.ColoringStrategy", resultStr)) {
        return false;
    }

    if (resultStr.empty()) {
        return false;
    }

    if (resultStr == "average") {
        result = OHOS::Ace::ShadowColorStrategy::AVERAGE;
        return true;
    }

    if (resultStr == "primary") {
        result = OHOS::Ace::ShadowColorStrategy::PRIMARY;
        return true;
    }
    return false;
}

bool GetShadowColorStrategy(ani_env *env, ani_ref ref, OHOS::Ace::ShadowColorStrategy& result)
{
    ani_object object = static_cast<ani_object>(ref);
    return GetShadowColorStrategy(env, object, result);
}

bool GetShadowOptionsColor(ani_env *env, ani_object object, OHOS::Ace::Shadow& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "color", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    OHOS::Ace::ShadowColorStrategy shadowColorStrategy;
    if (GetShadowColorStrategy(env, resultRef, shadowColorStrategy)) {
        result.SetShadowColorStrategy(shadowColorStrategy);
        return true;
    }

    OHOS::Ace::Color color;
    if (GetResourceColorParam(env, resultRef, color)) {
        result.SetColor(color);
    }
    return true;
}

bool GetShadowOptionsOffset(ani_env *env, ani_ref ref, double& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    if (GetDoubleParam(env, ref, result)) {
        return true;
    }

    ani_object object = static_cast<ani_object>(ref);
    if (!IsClassObject(env, object, "global.resource.Resource")) {
        return false;
    }

    ResourceInfo resourceInfo;
    if (!GetResourceParam(env, object, resourceInfo)) {
        return false;
    }

    bool isRtl = OHOS::Ace::AceApplicationInfo::GetInstance().IsRightToLeft();
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    auto offsetValue = resourceWrapper->GetDimension(resourceInfo.resId);
    result = isRtl ? offsetValue.Value() * (-1) : offsetValue.Value();
    return true;
}

bool GetShadowOptionsOffset(ani_env *env, ani_object object, const char *name, double& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetShadowOptionsOffset(env, resultRef, result);
}

bool GetShadowOptionsParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& result)
{
    double blurRadius = 0.0;
    GetShadowOptionsRadiusParam(env, object, blurRadius);
    result.SetBlurRadius(blurRadius);

    int32_t shadowType = static_cast<int32_t>(OHOS::Ace::ShadowType::COLOR);
    if (GetShadowOptionsType(env, object, shadowType)) {
        result.SetShadowType(static_cast<OHOS::Ace::ShadowType>(shadowType));
    }
    GetShadowOptionsColor(env, object, result);

    double offsetX = 0.0;
    if (GetShadowOptionsOffset(env, object, "offsetX", offsetX)) {
        result.SetOffsetX(offsetX);
    }

    double offsetY = 0.0;
    if (GetShadowOptionsOffset(env, object, "offsetY", offsetY)) {
        result.SetOffsetY(offsetY);
    }

    bool isFilled = false;
    if (GetBoolParam(env, object, "fill", isFilled)) {
        result.SetIsFilled(isFilled);
    }
    return true;
}

bool GetShadowParam(ani_env *env, ani_object object, OHOS::Ace::Shadow& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "shadow", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (GetShadowStyleParam(env, resultObj, result)) {
        return true;
    }
    return GetShadowOptionsParam(env, resultObj, result);
}

bool GetShadowParamOpt(ani_env *env, ani_object object, std::optional<OHOS::Ace::Shadow>& result)
{
    OHOS::Ace::Shadow shadow;
    if (!GetShadowParam(env, object, shadow)) {
        return false;
    }
    result = std::make_optional<OHOS::Ace::Shadow>(shadow);
    return true;
}

bool ResourceIntegerToString(const ResourceInfo& resourceInfo, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (resourceInfo.type != static_cast<int>(ResourceType::INTEGER)) {
        return true;
    }

    if (resourceInfo.resId == UNKNOWN_RESOURCE_ID) {
        result = std::to_string(resourceWrapper->GetIntByName(resourceInfo.params[0]));
    } else {
        result = std::to_string(resourceWrapper->GetInt(resourceInfo.resId));
    }
    return true;
}

bool GetDimensionParam(ani_env* env, ani_ref ref, OHOS::Ace::CalcDimension& result)
{
    if (IsUndefinedObject(env, ref)) {
        return false;
    }

    double resultDouble;
    if (GetDoubleParam(env, ref, resultDouble)) {
        OHOS::Ace::CalcDimension dimension(resultDouble, OHOS::Ace::DimensionUnit::VP);
        result = dimension;
        return true;
    }

    std::string resultStr;
    if (GetStringParam(env, ref, resultStr)) {
        if (OHOS::Ace::StringUtils::StringToCalcDimensionNG(resultStr, result, false, OHOS::Ace::DimensionUnit::VP)) {
            return true;
        }
    }

    ani_object object = static_cast<ani_object>(ref);
    ResourceInfo resourceInfo;
    if (!GetResourceParam(env, object, resourceInfo)) {
        return false;
    }

    std::string resourceStr;
    if (!ResourceToString(resourceInfo, resourceStr)) {
        return false;
    }

    if (!ResourceIntegerToString(resourceInfo, resourceStr)) {
        return false;
    }
    result = OHOS::Ace::StringUtils::StringToDimensionWithUnit(resourceStr, OHOS::Ace::DimensionUnit::VP);
    return true;
}

bool GetDimensionParam(ani_env* env, ani_object object, const char *name, OHOS::Ace::CalcDimension& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }
    return GetDimensionParam(env, resultRef, result);
}

bool GetDimensionParamOpt(ani_env* env, ani_object object, const char *name,
    std::optional<OHOS::Ace::CalcDimension>& result)
{
    OHOS::Ace::CalcDimension dimension;
    if (!GetDimensionParam(env, object, name, dimension)) {
        return false;
    }
    result = std::make_optional<OHOS::Ace::CalcDimension>(dimension);
    return true;
}

void CheckDimension(OHOS::Ace::CalcDimension value)
{
    if (value.IsNegative()) {
        value.Reset();
    }
}

bool GetBackgroundBlurStyleParam(ani_env* env, ani_object object, int32_t& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "backgroundBlurStyle", "arkui.component.common.BlurStyle", resultInt)) {
        return false;
    }

    auto iter = blurStyleMap.find(resultInt);
    if (iter != blurStyleMap.end()) {
        result = static_cast<int32_t>(iter->second);
        return true;
    }
    return false;
}

bool GetBackgroundBlurStyleParamOpt(ani_env* env, ani_object object, std::optional<int32_t>& result)
{
    int32_t style;
    if (!GetBackgroundBlurStyleParam(env, object, style)) {
        return false;
    }
    result = std::make_optional<int32_t>(style);
    return true;
}

bool GetHoverModeAreaParam(ani_env* env, ani_object object, OHOS::Ace::HoverModeAreaType& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "hoverModeArea", "arkui.component.common.HoverModeAreaType", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::HoverModeAreaType>(resultInt);
    return true;
}

bool GetHoverModeAreaParamOpt(ani_env* env, ani_object object, std::optional<OHOS::Ace::HoverModeAreaType>& result)
{
    OHOS::Ace::HoverModeAreaType hoverModeArea;
    if (!GetHoverModeAreaParam(env, object, hoverModeArea)) {
        return false;
    }
    result = std::make_optional<OHOS::Ace::HoverModeAreaType>(hoverModeArea);
    return true;
}

bool GetOffsetParam(ani_env *env, ani_object object, OHOS::Ace::DimensionOffset& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "offset", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::CalcDimension dx;
    GetLengthParam(env, resultObj, "dx", dx);
    OHOS::Ace::CalcDimension dy;
    GetLengthParam(env, resultObj, "dy", dy);
    result = OHOS::Ace::DimensionOffset { dx, dy };
    return true;
}

bool GetOffsetParamOpt(ani_env *env, ani_object object, std::optional<OHOS::Ace::DimensionOffset>& result)
{
    OHOS::Ace::DimensionOffset offset;
    if (!GetOffsetParam(env, object, offset)) {
        return false;
    }
    result = std::make_optional<OHOS::Ace::DimensionOffset>(offset);
    return true;
}

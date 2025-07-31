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
#include "core/common/ace_engine.h"
#include "drag_controller_utils.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Ani {
std::unordered_map<int, uint32_t> colorMap = {
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_WHITE, 0xffffff | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_BLACK, 0x000000 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_BLUE, 0x0000ff | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_BROWN, 0xa52a2a | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_GRAY, 0x808080 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_GREEN, 0x008000 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_GREY, 0x808080 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_ORANGE, 0xffa500 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_PINK, 0xffc0cb | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_RED, 0xff0000 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_YELLOW, 0xffff00 | 0xFF000000},
    {DragForegroundColor::DRAG_FOREGROUND_COLOR_TRANSPARENT, 0x00000000},
};

ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_class errClass;
    if (ANI_OK != env->FindClass("@ohos.base.BusinessError", &errClass)) {
        LOGE("AceDrag, find class failed");
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(errClass, "<ctor>", ":", &ctor)) {
        LOGE("AceDrag, Cannot find constructor for class.");
        return nullptr;
    }
    ani_string errMessage;
    if (ANI_OK != env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &errMessage)) {
        LOGE("AceDrag, Convert string to ani string failed.");
        return nullptr;
    }
    ani_object errObj;
    if (ANI_OK != env->Object_New(errClass, ctor, &errObj)) {
        LOGE("AceDrag, Cannot create ani error object.");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetFieldByName_Double(errObj, "code", static_cast<ani_double>(code))) {
        LOGE("AceDrag, set error code failed");
        return nullptr;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(errObj, "message", errMessage)) {
        LOGE("AceDrag, set error message failed");
        return nullptr;
    }
    return static_cast<ani_error>(errObj);
}

void AniThrow(ani_env* env, const std::string& errMsg, int32_t code)
{
    CHECK_NULL_VOID(env);
    auto errObj = GetErrorObject(env, errMsg, code);
    if (errObj == nullptr) {
        LOGE("AceDrag, get error object failed!");
        return;
    }
    if (ANI_OK != env->ThrowError(errObj)) {
        LOGE("AceDrag, throw ani error object failed!");
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
    if ((status = env->FindClass("std.core.Function0", &funcClass)) != ANI_OK) {
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
    if ((ANI_OK != env->FindClass("escompat.BigInt", &bigIntClass)) != ANI_OK) {
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
    env->FindClass("std.core.Function2", &funcClass);
    ani_boolean result;
    env->Object_InstanceOf(static_cast<ani_object>(obj), funcClass, &result);
    return static_cast<bool>(result);
}

bool IsNumberObject(ani_env* env, ani_ref obj)
{
    ani_class numberClass;
    env->FindClass("std.core.Numeric", &numberClass);
    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(obj), numberClass, &isNumber);
    return static_cast<bool>(isNumber);
}

bool IsInt32Object(ani_env* env, ani_ref obj)
{
    ani_class numberClass;
    env->FindClass("std.core.Int", &numberClass);
    ani_boolean isNumber;
    env->Object_InstanceOf(static_cast<ani_object>(obj), numberClass, &isNumber);
    return static_cast<bool>(isNumber);
}

bool IsStringObject(ani_env* env, ani_ref obj)
{
    ani_class stringClass;
    env->FindClass("std.core.String", &stringClass);
    ani_boolean isString;
    env->Object_InstanceOf(static_cast<ani_object>(obj), stringClass, &isString);
    return static_cast<bool>(isString);
}

bool IsArrayObject(ani_env* env, ani_ref obj)
{
    ani_class arrayClass;
    env->FindClass("escompat.Array", &arrayClass);
    ani_boolean isArray;
    env->Object_InstanceOf(static_cast<ani_object>(obj), arrayClass, &isArray);
    return static_cast<bool>(isArray);
}

bool IsBooleanObject(ani_env* env, ani_ref obj)
{
    ani_class booleanClass;
    env->FindClass("std.core.Boolean", &booleanClass);
    ani_boolean isBoolean;
    env->Object_InstanceOf(static_cast<ani_object>(obj), booleanClass, &isBoolean);
    return static_cast<bool>(isBoolean);
}

bool GetBigIntValue(ani_env* env, ani_object object, int64_t& longValue)
{
    auto status = ANI_OK;
    ani_long value;
    if ((status = env->Object_CallMethodByName_Long(object, "unboxed", ":l", &value)) != ANI_OK) {
        return false;
    }
    longValue = value;
    return true;
}

bool GetEnumItem([[maybe_unused]] ani_env* env, ani_size index, const char* enumName, ani_enum_item& enumItem)
{
    ani_enum enumType;
    auto status = ANI_OK;
    static const std::string fullEnumName = std::string("@ohos.arkui.dragController.dragController.").append(enumName);
    if ((status = env->FindEnum(fullEnumName.c_str(), &enumType)) != ANI_OK) {
        LOGE("AceDrag, find %{public}s fail. statsu = %{public}d", enumName, status);
        return false;
    }
    if ((status = env->Enum_GetEnumItemByIndex(enumType, index, &enumItem)) != ANI_OK) {
        LOGE("AceDrag, get %{public}s Enum fail. status = %{public}d", enumName, status);
        return false;
    }
    return true;
}

bool IsDragPreviewModeEnum(ani_env *env, ani_ref obj)
{
    static const char *className = "@ohos.arkui.dragController.dragController.DragPreviewMode";
    ani_enum enumType;
    if (ANI_OK != env->FindEnum(className, &enumType)) {
        LOGE("AceDrag, find DragPreviewMode calss fail.");
        return false;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(obj), enumType, &isEnum)) {
        LOGE("AceDrag, object is not DragPreviewMode instance.");
        return false;
    }
    return static_cast<bool>(isEnum);
}

bool IsResourceObject(ani_env *env, ani_ref object_ref)
{
    static const char *enumName = "@ohos.arkui.dragController.dragController.Resource";
    ani_enum enumType;
    if (ANI_OK != env->FindEnum(enumName, &enumType)) {
        LOGW("AceDrag, find Resource calss fail");
        return false;
    }
    ani_boolean isResource;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), enumType, &isResource)) {
        LOGW("AceDrag, object is not Resource instance.");
        return false;
    }
    return static_cast<bool>(isResource);
}

void PreFixEmptyBundleName(ani_env *env, ani_object value)
{
    ani_ref bundleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "bundleName", &bundleName_ref)) {
        return;
    }
    auto bundleName = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(bundleName_ref));
    if (bundleName.empty()) {
        auto container = OHOS::Ace::Container::CurrentSafely();
        CHECK_NULL_VOID(container);
        bundleName = container->GetBundleName();
        ani_string ani_bundleName{};
        if (ANI_OK != env->String_NewUTF8(bundleName.c_str(), bundleName.size(), &ani_bundleName)) {
            return;
        }
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "bundleName", static_cast<ani_ref>(ani_bundleName))) {
            return;
        }
    }
}

ResourceStruct CheckResourceStruct(ani_env *env, ani_object value)
{
    ani_double id;
    if (ANI_OK != env->Object_GetPropertyByName_Double(value, "id", &id)) {
        ani_ref id_ref;
        if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "id", &id_ref)) {
            return ResourceStruct::CONSTANT;
        }
        return ResourceStruct::DYNAMIC_V1;
    } else {
        if (static_cast<int32_t>(id) == UNKNOWN_RESOURCE_ID) {
            return ResourceStruct::DYNAMIC_V2;
        }
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
    auto it = resTypeMap.find(typeName);
    if (it == resTypeMap.end()) {
        return false;
    }
    resType = it->second;
    return true;
}

bool ParseDollarResource(
    ani_env *env, ani_object params_ref, ResourceType& resType, std::string& resName, std::string& moduleName)
{
    if (!IsStringObject(env, params_ref)) {
        return false;
    }
    auto resPath = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(params_ref));

    std::vector<std::string> tokens;
    OHOS::Ace::StringUtils::StringSplitter(resPath, '.', tokens);
    // $r format like app.xxx.xxx, has 3 paragraph
    if (static_cast<int32_t>(tokens.size()) != 3) {
        return false;
    }
    std::string maybeModuleName = tokens[0];
    // [*] or app/hsp at least has 3 chars
    if (maybeModuleName.size() < 3) {
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

void processResourceType(ani_env *env, ani_object value, ani_ref params_ref, size_t length, std::string resName)
{
    std::vector<std::string> vectorStr;
    for (size_t i = 0; i < length; i++) {
        ani_ref stringEntryRef;
        if (ANI_OK != env->Object_CallMethodByName_Ref(static_cast<ani_object>(params_ref),
            "$_get", "i:C{std.core.Object}", &stringEntryRef, (ani_int)i)) {
            break;
        }
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(stringEntryRef));
        vectorStr.emplace_back(stringContent);
    }
    ani_class stringCls = nullptr;
    if (ANI_OK != env->FindClass("std.core.String", &stringCls)) {
        return;
    }
    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return;
    }
    int32_t index = 0;
    ani_string ani_first_str;
    if (ANI_OK != env->String_NewUTF8(resName.c_str(), resName.size(), &ani_first_str)) {
        return;
    } else {
        if (ANI_OK != env->Object_CallMethodByName_Void(static_cast<ani_object>(params_ref),
            "$_set", "iC{std.core.Object}:", index, ani_first_str)) {
            return;
        }
    }
    index++;
    for (const auto& string : vectorStr) {
        ani_string ani_str;
        if (ANI_OK != env->String_NewUTF8(string.c_str(), string.size(), &ani_str)) {
            break;
        }
        if (ANI_OK != env->Object_CallMethodByName_Void(static_cast<ani_object>(params_ref),
            "$_set", "iC{std.core.Object}:", index, ani_str)) {
            break;
        }
        index++;
    }
}

void ModifyResourceParam(ani_env *env, ani_object value, const ResourceType& resType, const std::string& resName)
{
    // raw input : {"id":"app.xxx.xxx","params":[],"moduleName":"xxx","bundleName":"xxx"}
    // modified output : {"id":-1, "params":["app.xxx.xxx"],"type":xxxx,"moduleName":"xxx","bundleName":"xxx"}
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "params", &params_ref)) {
        return;
    }
    if (IsUndefinedObject(env, params_ref)) {
        return;
    }
    if (!IsArrayObject(env, params_ref)) {
        return;
    }
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(params_ref), "length", &length)) {
        return;
    }
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        processResourceType(env, value, params_ref, static_cast<size_t>(length), resName);
    } else {
        ani_string ani_res{};
        if (ANI_OK != env->String_NewUTF8(resName.c_str(), resName.size(), &ani_res)) {
            return;
        }
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "params", static_cast<ani_ref>(ani_res))) {
            return;
        }
    }
}

void CompleteResourceParamV1(ani_env *env, ani_object value)
{
    ani_ref id_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "id", &id_ref)) {
        return;
    }
    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!ParseDollarResource(env, static_cast<ani_object>(id_ref), resType, resName, moduleName)) {
        return;
    }
    ModifyResourceParam(env, value, resType, resName);
    ani_int ani_id = static_cast<ani_int>(UNKNOWN_RESOURCE_ID);
    if (ANI_OK != env->Object_SetPropertyByName_Int(value, "id", static_cast<ani_int>(ani_id))) {
        return;
    }
    int32_t aniType = static_cast<int32_t>(resType);
    if (ANI_OK != env->Object_SetPropertyByName_Int(value, "type", static_cast<ani_int>(aniType))) {
        return;
    }
    ani_ref bundleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "bundleName", &bundleName_ref)) {
        std::string bundleNameStr = "";
        ani_string defaut_bundleName{};
        if (ANI_OK != env->String_NewUTF8(bundleNameStr.c_str(), bundleNameStr.size(), &defaut_bundleName)) {
            return;
        }
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "bundleName",
            static_cast<ani_ref>(defaut_bundleName))) {
            return;
        }
        return;
    }
    ani_ref moduleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "moduleName", &moduleName_ref)) {
        std::string moduleNameStr = "";
        ani_string defaut_moduleName{};
        if (ANI_OK != env->String_NewUTF8(moduleNameStr.c_str(), moduleNameStr.size(), &defaut_moduleName)) {
            return;
        }
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "moduleName",
            static_cast<ani_ref>(defaut_moduleName))) {
            return;
        }
        return;
    }
}

void CompleteResourceParamV2(ani_env *env, ani_object value)
{
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "params", &params_ref)) {
        return;
    }
    if (IsUndefinedObject(env, params_ref)) {
        return;
    }
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(params_ref), "length", &length)) {
        return;
    }
    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!ParseDollarResource(env, static_cast<ani_object>(params_ref), resType, resName, moduleName)) {
        return;
    }
    int32_t aniType = static_cast<int32_t>(resType);
    
    if (ANI_OK != env->Object_SetPropertyByName_Int(value, "type", static_cast<ani_int>(aniType))) {
        return;
    }
    if (!moduleName.empty()) {
        ani_string ani_moduleName{};
        if (ANI_OK != env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &ani_moduleName)) {
            return;
        }
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "moduleName", static_cast<ani_ref>(ani_moduleName))) {
            return;
        }
    }
}

void CompleteResourceParam(ani_env *env, ani_object value)
{
    PreFixEmptyBundleName(env, value);
    ResourceStruct resourceStruct = CheckResourceStruct(env, value);
    switch (resourceStruct) {
        case ResourceStruct::CONSTANT:
            return;
        case ResourceStruct::DYNAMIC_V1:
            CompleteResourceParamV1(env, value);
            return;
        case ResourceStruct::DYNAMIC_V2:
            CompleteResourceParamV2(env, value);
            return;
        default:
            return;
    }
}

bool ParseResourceParamId(ani_env *env, ani_object objects, ResourceInfo& info)
{
    ani_double id_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Double(objects, "id", &id_ref)) {
        return false;
    }
    info.resId = static_cast<int32_t>(id_ref);
    return true;
}

bool ParseResourceParamBundleName(ani_env *env, ani_object objects, ResourceInfo& info)
{
    ani_ref bundleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "bundleName", &bundleName_ref)) {
        return false;
    }
    auto bundleName_str = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(bundleName_ref));
    info.bundleName = bundleName_str;
    return true;
}

bool ParseResourceParamModuleName(ani_env *env, ani_object objects, ResourceInfo& info)
{
    ani_ref moduleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "moduleName", &moduleName_ref)) {
        return false;
    }
    auto moduleName_str = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(moduleName_ref));
    info.moduleName = moduleName_str;
    return true;
}

bool ParseResourceParamType(ani_env *env, ani_object objects, ResourceInfo& info)
{
    ani_ref type_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "type", &type_ref)) {
        return false;
    }
    if (IsUndefinedObject(env, type_ref)) {
        return true;
    }
    ani_double type;
    if (ANI_OK !=env->Object_CallMethodByName_Double(
        static_cast<ani_object>(type_ref), "doubleValue", nullptr, &type)) {
        return false;
    }
    info.type = static_cast<int32_t>(type);
    return true;
}

bool ParseResourceParamName(ani_env *env, ani_object objects, ResourceInfo& info)
{
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "params", &params_ref)) {
        return false;
    }
    if (IsUndefinedObject(env, params_ref)) {
        return true;
    }
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(params_ref), "length", &length)) {
        return false;
    }
    std::vector<std::string> strings;
    for (int i = 0; i < int(length); i++) {
        ani_ref stringEntryRef;
        if (ANI_OK != env->Object_CallMethodByName_Ref(static_cast<ani_object>(params_ref),
            "$_get", "i:C{std.core.Object}", &stringEntryRef, (ani_int)i)) {
            return false;
        }
        strings.emplace_back(ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(stringEntryRef)));
    }
    info.params = strings;
    return true;
}

bool ParseResourceParam(ani_env *env, ani_object objects, ResourceInfo& info)
{
    if (IsUndefinedObject(env, objects)) {
        return false;
    }
    CompleteResourceParam(env, objects);
    if (!ParseResourceParamId(env, objects, info)) {
        return false;
    }
    if (!ParseResourceParamBundleName(env, objects, info)) {
        return false;
    }
    if (!ParseResourceParamModuleName(env, objects, info)) {
        return false;
    }
    if (!ParseResourceParamType(env, objects, info)) {
        return false;
    }
    if (!ParseResourceParamName(env, objects, info)) {
        return false;
    }
    return true;
}

bool IsColorEnum(ani_env *env, ani_ref objectRef)
{
    ani_status status = ANI_OK;
    ani_enum enumType;
    if ((status = env->FindEnum("arkui.component.enums.Color", &enumType)) != ANI_OK) {
        LOGW("AceDrag, find Color enum failed, status:%{public}d", status);
        return false;
    }
    ani_boolean isEnum = ANI_FALSE;
    if ((status = env->Object_InstanceOf(static_cast<ani_object>(objectRef), enumType, &isEnum)) != ANI_OK) {
        LOGW("AceDrag, object is not Color instance, status:%{public}d", status);
        return false;
    }
    return static_cast<bool>(isEnum);
}

bool ParseColorMapToColor(DragForegroundColor colorEnum, OHOS::Ace::Color& color)
{
    OHOS::Ace::Color colorTemp;
    auto it = colorMap.find(colorEnum);
    if (it != colorMap.end()) {
        colorTemp = OHOS::Ace::Color(it->second);
        color = colorTemp;
        return true;
    }
    return false;
}

bool ParseResourceColor(ani_env *env, ani_ref resourceColorRef, OHOS::Ace::Color& resourceColor)
{
    ResourceInfo resourceInfo;
    std::string resourceColorStr;
    if (!ParseResourceParam(env, static_cast<ani_object>(resourceColorRef), resourceInfo)) {
        return false;
    }
    if (!ParseString(resourceInfo, resourceColorStr)) {
        return false;
    }
    if (resourceColorStr.size() == 0) {
        return false;
    }
    resourceColor = OHOS::Ace::Color::FromString(resourceColorStr);
    return true;
}

bool ParseAniColor(ani_env *env, ani_ref resourceColorRef, OHOS::Ace::Color& resourceColor)
{
    if (IsStringObject(env, resourceColorRef)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(resourceColorRef));
        resourceColor = OHOS::Ace::Color::FromString(stringContent);
        return true;
    }
    if (IsColorEnum(env, resourceColorRef)) {
        ani_int colorObj;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(resourceColorRef), &colorObj)) {
            return false;
        }
        OHOS::Ace::Color resourceColorValue;
        ParseColorMapToColor(static_cast<DragForegroundColor>(colorObj), resourceColorValue);
        resourceColor = resourceColorValue;
        return true;
    }
    if (IsNumberObject(env, resourceColorRef)) {
        ani_double resourceColorValue;
        if (ANI_OK !=env->Object_CallMethodByName_Double(
            static_cast<ani_object>(resourceColorRef), "unboxed", ":d", &resourceColorValue)) {
            return false;
        }
        resourceColor = static_cast<OHOS::Ace::Color>(resourceColorValue);
        return true;
    }
    if (IsResourceObject(env, resourceColorRef)) {
        return ParseResourceColor(env, resourceColorRef, resourceColor);
    }
    return false;
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
        LOGE("themeManager is null!");
        return nullptr;
    }
    if (bundleName.has_value() && moduleName.has_value()) {
        return themeManager->GetThemeConstants(bundleName.value_or(""), moduleName.value_or(""));
    }
    return themeManager->GetThemeConstants();
}

OHOS::Ace::RefPtr<OHOS::Ace::ResourceWrapper> CreateResourceWrapper(const ResourceInfo& info)
{
    auto bundleName = info.bundleName;
    auto moduleName = info.moduleName;

    OHOS::Ace::RefPtr<OHOS::Ace::ResourceAdapter> resourceAdapter = nullptr;
    OHOS::Ace::RefPtr<OHOS::Ace::ThemeConstants> themeConstants = nullptr;
    if (OHOS::Ace::SystemProperties::GetResourceDecoupling()) {
        if (bundleName.has_value() && moduleName.has_value()) {
            auto resourceObject = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::ResourceObject>(
                            bundleName.value_or(""), moduleName.value_or(""), OHOS::Ace::Container::CurrentIdSafely());
            resourceAdapter = OHOS::Ace::ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        } else {
            resourceAdapter = OHOS::Ace::ResourceManager::GetInstance().GetResourceAdapter(
                OHOS::Ace::Container::CurrentIdSafely());
        }
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(info.bundleName, info.moduleName);
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

bool ParseString(const ResourceInfo& info, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(info);
    CHECK_NULL_RETURN(resourceWrapper, false);
    if (info.type == static_cast<int>(ResourceType::PLURAL)) {
        std::string pluralResults;
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            auto count = OHOS::Ace::StringUtils::StringToInt(info.params[1]);
            pluralResults = resourceWrapper->GetPluralStringByName(info.params[0], count);
            ReplaceHolder(pluralResults, info.params, 2); // plural holder in index 2
        } else {
            auto count = OHOS::Ace::StringUtils::StringToInt(info.params[0]);
            pluralResults = resourceWrapper->GetPluralString(info.resId, count);
            ReplaceHolder(pluralResults, info.params, 1);
        }
        result = pluralResults;
        return true;
    } else if (info.type == static_cast<int>(ResourceType::RAWFILE)) {
        auto fileName = info.params[0];
        result = resourceWrapper->GetRawfile(fileName);
        return true;
    } else if (info.type == static_cast<int>(ResourceType::FLOAT)) {
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            result = DimensionToString(resourceWrapper->GetDimensionByName(info.params[0]));
        } else {
            result = DimensionToString(resourceWrapper->GetDimension(info.resId));
        }
        return true;
    } else if (info.type == static_cast<int>(ResourceType::STRING)) {
        std::string originStr;
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            originStr = resourceWrapper->GetStringByName(info.params[0]);
            ReplaceHolder(originStr, info.params, 1);
        } else {
            originStr = resourceWrapper->GetString(info.resId);
            ReplaceHolder(originStr, info.params, 0);
        }
        result = originStr;
        return true;
    } else if (info.type == static_cast<int>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(info.resId).ColorToString();
        return true;
    } else if (info.type == static_cast<int>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(info.resId));
        return true;
    }
    return false;
}

void ParseCurveInfo(const std::string& curveString, std::string& curveTypeString, std::vector<float>& curveValue)
{
    if (curveString.back() != ')') {
        return;
    }
    std::string::size_type leftEmbracePosition = curveString.find_last_of('(');
    if (leftEmbracePosition == std::string::npos) {
        return;
    }
    curveTypeString = curveString.substr(0, leftEmbracePosition);
    auto params = curveString.substr(leftEmbracePosition + 1, curveString.length() - leftEmbracePosition - 2);
    if (curveTypeString.empty() || params.empty()) {
        return;
    }
    std::vector<std::string> paramsVector;
    StringUtils::StringSplitter(params, ',', paramsVector);
    for (auto& param : paramsVector) {
        OHOS::Ace::Framework::RemoveHeadTailSpace(param);
        if (param == "true" || param == "start") {
            param = "1.000000";
        }
        if (param == "false" || param == "end") {
            param = "0.000000";
        }
        errno = 0;
        char* end = nullptr;
        float value = strtof(param.c_str(), &end);
        if (end == param.c_str() || errno == ERANGE) {
            LOGW("AceDrag, %{public}s can not be converted to float or is out of range.", param.c_str());
        }
        curveValue.emplace_back(value);
    }
}

void ParseCurve(ani_env* env, ani_object object, std::string& curveTypeString, std::vector<float>& curveValue)
{
    CHECK_NULL_VOID(env);
    if (IsUndefinedObject(env, object))  {
        LOGE("AceDrag, the type of curve is incorrect.");
        return;
    }
    if (!IsStringObject(env, object)) {
        ani_ref curveObject;
        env->Object_GetPropertyByName_Ref(object, "__curveString", &curveObject);
        object = static_cast<ani_object>(curveObject);
    }
    auto resultStr = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(object));
    ani_size stringLen = 0U;
    auto status = env->String_GetUTF8Size(static_cast<ani_string>(object), &stringLen);
    constexpr int32_t ANI_BUF_LENGTH = 256;
    if (stringLen < 0 || stringLen >= ANI_BUF_LENGTH || status != ANI_OK) {
        LOGE("AceDrag, string length error.");
        return;
    }

    RefPtr<Curve> curve;
    const std::string domAnimationDefaultCurveString = "ease-in-out";
    if (resultStr.empty()) {
        curve = OHOS::Ace::Framework::CreateCurve(domAnimationDefaultCurveString);
    } else {
        curve = OHOS::Ace::Framework::CreateCurve(resultStr);
    }
    CHECK_NULL_VOID(curve);
    std::string curveString = curve->ToString();
    ParseCurveInfo(curveString, curveTypeString, curveValue);
}
} // namespace OHOS::Ace::NG

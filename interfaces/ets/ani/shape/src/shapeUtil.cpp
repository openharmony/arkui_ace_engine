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

#include "shapeUtil.h"

#include "core/pipeline/pipeline_base.h"

std::unordered_map<int, uint32_t> colorMap = {
    { ResColor::RES_COLOR_WHITE, 0xffffff | 0xFF000000 },
    { ResColor::RES_COLOR_BLACK, 0x000000 | 0xFF000000 },
    { ResColor::RES_COLOR_BLUE, 0x0000ff | 0xFF000000 },
    { ResColor::RES_COLOR_BROWN, 0xa52a2a | 0xFF000000 },
    { ResColor::RES_COLOR_GRAY, 0x808080 | 0xFF000000 },
    { ResColor::RES_COLOR_GREEN, 0x008000 | 0xFF000000 },
    { ResColor::RES_COLOR_GREY, 0x808080 | 0xFF000000 },
    { ResColor::RES_COLOR_ORANGE, 0xffa500 | 0xFF000000 },
    { ResColor::RES_COLOR_PINK, 0xffc0cb | 0xFF000000 },
    { ResColor::RES_COLOR_RED, 0xff0000 | 0xFF000000 },
    { ResColor::RES_COLOR_YELLOW, 0xffff00 | 0xFF000000 },
    { ResColor::RES_COLOR_TRANSPARENT, 0x00000000 },
};

bool GetIsStringObject(ani_env* env, ani_ref object_ref)
{
    ani_class stringClass;
    if (ANI_OK != env->FindClass("std.core.String", &stringClass)) {
        return false;
    }
    ani_boolean isString;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), stringClass, &isString)) {
        return false;
    }
    return (bool)isString;
}
bool GetIsNumberObject(ani_env* env, ani_ref object_ref)
{
    ani_class numberClass;
    if (ANI_OK != env->FindClass("std.core.Numeric", &numberClass)) {
        return false;
    }
    ani_boolean isNumber;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), numberClass, &isNumber)) {
        return false;
    }
    return (bool)isNumber;
}

bool GetIsIntObject(ani_env* env, ani_ref object_ref)
{
    ani_class intClass;
    if (ANI_OK != env->FindClass("std.core.Int", &intClass)) {
        return false;
    }
    ani_boolean result;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), intClass, &result)) {
        return false;
    }
    return static_cast<bool>(result);
}

bool GetIsUndefinedObject(ani_env* env, ani_ref object_ref)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(object_ref, &isUndefined)) {
        return false;
    }
    return (bool)isUndefined;
}

bool GetIsResourceObject(ani_env* env, ani_ref object_ref)
{
    ani_class resourceClass;
    if (ANI_OK != env->FindClass("std.core.Object", &resourceClass)) {
        return false;
    }
    ani_boolean isResource = false;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), resourceClass, &isResource)) {
        return false;
    }
    return bool(isResource);
}

bool GetIsArrayObject(ani_env* env, ani_ref object_ref)
{
    ani_class arrayClass;
    if (ANI_OK != env->FindClass("std.core.Array", &arrayClass)) {
        return false;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(object_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    ani_boolean isArray;
    if (env->Object_InstanceOf(static_cast<ani_object>(object_ref), arrayClass, &isArray)) {
        return false;
    }
    return (bool)isArray;
}

void processResourceType(ani_env* env, ani_object value, ani_ref params_ref, size_t length, std::string resName)
{
    std::vector<std::string> strings;
    for (int i = 0; i < int(length); i++) {
        ani_ref stringEntryRef;
        if (ANI_OK != env->Object_CallMethodByName_Ref(static_cast<ani_object>(params_ref), 
                                                       "$_get",
                                                       "i:Y",
                                                       &stringEntryRef, 
                                                       (ani_int)i)) {
            break;
        }
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(stringEntryRef));
        strings.emplace_back(stringContent);
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
    if (ANI_OK == env->String_NewUTF8(resName.c_str(), resName.size(), &ani_first_str)) {
        if (ANI_OK != env->Object_CallMethodByName_Void(static_cast<ani_object>(params_ref),
                                                        "$_set", 
                                                        "iY:",
                                                        index, 
                                                        ani_first_str)) {
            return;
        }
    }
    index++;
    for (auto string : strings) {
        ani_string ani_str;
        if (ANI_OK != env->String_NewUTF8(string.c_str(), string.size(), &ani_str)) {
            break;
        }
        if (ANI_OK != env->Object_CallMethodByName_Void(static_cast<ani_object>(params_ref), 
                                                        "$_set", 
                                                        "iY:",
                                                        index, 
                                                        ani_str)) {
            break;
        }
        index++;
    }
}

void ModifyResourceParam(ani_env* env, ani_object value, const ResourceType& resType, const std::string& resName)
{
    // raw input : {"id":"app.xxx.xxx","params":[],"moduleName":"xxx","bundleName":"xxx"}
    // modified output : {"id":-1, "params":["app.xxx.xxx"],"type":xxxx,"moduleName":"xxx","bundleName":"xxx"}
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "params", &params_ref)) {
        return;
    }
    if (GetIsUndefinedObject(env, params_ref)) {
        return;
    }
    if (!GetIsArrayObject(env, params_ref)) {
        return;
    }
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(params_ref), "length", &length)) {
        return;
    }
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        processResourceType(env, value, params_ref, static_cast<size_t>(length), resName);
    } else {
        ani_string ani_res {};
        env->String_NewUTF8(resName.c_str(), resName.size(), &ani_res);
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "params", static_cast<ani_ref>(ani_res))) {
            return;
        }
    }
}

void CompleteResourceParamV1(ani_env* env, ani_object value)
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
        ani_string defaut_bundleName {};
        env->String_NewUTF8(bundleNameStr.c_str(), bundleNameStr.size(), &defaut_bundleName);
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "bundleName", static_cast<ani_ref>(defaut_bundleName))) {
            return;
        }
        return;
    }
    ani_ref moduleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "moduleName", &moduleName_ref)) {
        std::string moduleNameStr = "";
        ani_string defaut_moduleName {};
        env->String_NewUTF8(moduleNameStr.c_str(), moduleNameStr.size(), &defaut_moduleName);
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "moduleName", static_cast<ani_ref>(defaut_moduleName))) {
            return;
        }
        return;
    }
}
void CompleteResourceParamV2(ani_env* env, ani_object value)
{
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "params", &params_ref)) {
        return;
    }
    if (GetIsUndefinedObject(env, params_ref)) {
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
        ani_string ani_moduleName {};
        env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &ani_moduleName);
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "moduleName", static_cast<ani_ref>(ani_moduleName))) {
            return;
        }
    }
}
bool ParseDollarResource(
    ani_env* env, ani_object params_ref, ResourceType& resType, std::string& resName, std::string& moduleName)
{
    if (!GetIsStringObject(env, params_ref)) {
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

ResourceStruct CheckResourceStruct(ani_env* env, ani_object value)
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

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
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

bool IsInstanceOfCls(ani_env* env, [[maybe_unused]] ani_object object, const char* className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_boolean isInstance;
    if (env->Object_InstanceOf(object, cls, &isInstance)) {
        return false;
    }
    return (bool)isInstance;
}

bool ParseStringNumberUndefinedObject(ani_env* env, ani_ref property_ref, OHOS::Ace::DimensionUnit defaultUnit,
    std::optional<OHOS::Ace::CalcDimension>& result)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(property_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return true;
    }
    if (GetIsStringObject(env, property_ref)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(property_ref));
        result = OHOS::Ace::StringUtils::StringToCalcDimension(stringContent, false, defaultUnit);
        return true;
    }
    if (GetIsNumberObject(env, property_ref)) {
        ani_double numberValue;
        if (ANI_OK != env->Object_CallMethodByName_Double(static_cast<ani_object>(property_ref), 
                                                          "toDouble", 
                                                          ":d", 
                                                          &numberValue)) {
            return false;
        }
        result = OHOS::Ace::CalcDimension(OHOS::Ace::Dimension(static_cast<double>(numberValue), defaultUnit));
        return true;
    }
    return false;
}

bool ParseStringNumberUndefinedOption(ani_env* env, ani_object options, std::optional<OHOS::Ace::CalcDimension>& result,
    const char* property, const char* className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    if (!IsInstanceOfCls(env, options, className)) {
        return false;
    }
    ani_ref property_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, property, &property_ref)) {
        return false;
    }
    return ParseStringNumberUndefinedObject(env, property_ref, OHOS::Ace::DimensionUnit::VP, result);
}

void PreFixEmptyBundleName(ani_env* env, ani_object value)
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
        ani_string ani_bundleName {};
        bundleName = "app";
        env->String_NewUTF8(bundleName.c_str(), bundleName.size(), &ani_bundleName);
        if (ANI_OK != env->Object_SetPropertyByName_Ref(value, "bundleName", static_cast<ani_ref>(ani_bundleName))) {
            return;
        }
    }
}

void CompleteResourceParam(ani_env* env, ani_object value)
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

bool ParseResourceParamId(ani_env* env, ani_object objects, ResourceInfo& info)
{
    ani_double id_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Double(objects, "id", &id_ref)) {
        return false;
    }
    info.resId = static_cast<int32_t>(id_ref);
    return true;
}
bool ParseResourceParamBundleName(ani_env* env, ani_object objects, ResourceInfo& info)
{
    ani_ref bundleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "bundleName", &bundleName_ref)) {
        return false;
    }
    auto bundleName_str = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(bundleName_ref));
    info.bundleName = bundleName_str;
    return true;
}
bool ParseResourceParamModuleName(ani_env* env, ani_object objects, ResourceInfo& info)
{
    ani_ref moduleName_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "moduleName", &moduleName_ref)) {
        return false;
    }
    auto moduleName_str = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(moduleName_ref));
    info.moduleName = moduleName_str;
    return true;
}
bool ParseResourceParamType(ani_env* env, ani_object objects, ResourceInfo& info)
{
    ani_ref type_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "type", &type_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, type_ref)) {
        return false;
    }
    ani_double type;
    if (ANI_OK != env->Object_CallMethodByName_Double(static_cast<ani_object>(type_ref), "toDouble", ":d", &type)) {
        return false;
    }
    info.type = static_cast<int32_t>(type);
    return true;
}
bool ParseResourceParamName(ani_env* env, ani_object objects, ResourceInfo& info)
{
    ani_ref params_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(objects, "params", &params_ref)) {
        return false;
    }
    if (GetIsUndefinedObject(env, params_ref)) {
        return false;
    }
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(params_ref), "length", &length)) {
        return false;
    }
    std::vector<std::string> strings;
    for (int i = 0; i < int(length); i++) {
        ani_ref stringEntryRef;
        if (ANI_OK != env->Object_CallMethodByName_Ref(static_cast<ani_object>(params_ref), 
                                                       "$_get",
                                                       "i:Y",
                                                       &stringEntryRef, 
                                                       (ani_int)i)) {
            return false;
        }
        strings.emplace_back(ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(stringEntryRef)));
    }
    info.params = strings;
    for (const auto& s : strings) {
        std::cout << "ParseResourceParamName Array String Content:" << s.c_str() << std::endl;
    }
    return true;
}

bool ParseResourceParam(ani_env* env, ani_object objects, ResourceInfo& info)
{
    CompleteResourceParam(env, objects);

    ParseResourceParamId(env, objects, info);
    ParseResourceParamBundleName(env, objects, info);
    ParseResourceParamModuleName(env, objects, info);
    ParseResourceParamType(env, objects, info);
    ParseResourceParamName(env, objects, info);
    return true;
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
            resourceAdapter =
                OHOS::Ace::ResourceManager::GetInstance().GetResourceAdapter(OHOS::Ace::Container::CurrentIdSafely());
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

bool ParseLengthToDimension(
    ani_env* env, ani_ref source_ref, OHOS::Ace::DimensionUnit defaultUnit, OHOS::Ace::CalcDimension& result)
{
    if (GetIsStringObject(env, source_ref)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(source_ref));
        result = OHOS::Ace::StringUtils::StringToCalcDimension(stringContent, false, defaultUnit);
        return true;
    }
    if (GetIsNumberObject(env, source_ref)) {
        ani_double numberValue;
        if (ANI_OK !=env->Object_CallMethodByName_Double(static_cast<ani_object>(source_ref), 
                                                         "toDouble", 
                                                         ":d", 
                                                         &numberValue)) {
            return false;
        }
        result.SetUnit(defaultUnit);
        result.SetValue(static_cast<double>(numberValue));
        return true;
    }
    if (GetIsResourceObject(env, source_ref)) {
        ResourceInfo recv;
        std::string parameterStr;
        if (!ParseResourceParam(env, static_cast<ani_object>(source_ref), recv)) {
            return false;
        }
        if (!ParseString(recv, parameterStr)) {
            return false;
        }
        result = OHOS::Ace::StringUtils::StringToDimensionWithUnit(parameterStr, defaultUnit);
        return true;
    }
    return true;
}

bool ParseLength(ani_env* env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_ref aniOption,
    OHOS::Ace::CalcDimension& lengthInput)
{
    if (GetIsUndefinedObject(env, aniOption)) {
        return false;
    }
    if (!ParseLengthToDimension(env, aniOption, OHOS::Ace::DimensionUnit::VP, lengthInput)) {
        return false;
    }
    if (OHOS::Ace::LessNotEqual(lengthInput.Value(), 0.0)) {
        return false;
    }
    return true;
}

bool ParseOption(
    ani_env* env, ani_object options, OHOS::Ace::CalcDimension& input, const char* property, const char* className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_ref property_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, property, &property_ref)) {
        return false;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(property_ref, &isUndefined)) {
        return false;
    }
    if (isUndefined) {
        return false;
    }
    if (!ParseLength(env, options, property_ref, input)) {
        return false;
    }
    return true;
}

bool GetIsColorEnum(ani_env* env, ani_ref object_ref)
{
    ani_enum colorEnum;
    if (ANI_OK != env->FindEnum("arkui.component.enums.Color", &colorEnum)) {
        return false;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(object_ref), colorEnum, &isEnum)) {
        return false;
    }
    return (bool)isEnum;
}

bool ParseColorMapToColor(ResColor colorenum, OHOS::Ace::Color& Color)
{
    OHOS::Ace::Color colorProp;
    auto it = colorMap.find(colorenum);
    if (it != colorMap.end()) {
        colorProp = OHOS::Ace::Color(it->second);
        Color = colorProp;
        return true;
    }
    return false;
}

bool ParseResourceColor(ani_env* env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor)
{
    ResourceInfo resourceInfo;
    std::string resourceColorStr;
    if (!ParseResourceParam(env, static_cast<ani_object>(resourceColor_ref), resourceInfo)) {
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

bool ParseAniColor(ani_env* env, ani_ref resourceColor_ref, OHOS::Ace::Color& resourceColor)
{
    if (GetIsStringObject(env, resourceColor_ref)) {
        auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(resourceColor_ref));
        resourceColor = OHOS::Ace::Color::FromString(stringContent);
        return true;
    }
    if (GetIsColorEnum(env, resourceColor_ref)) {
        ani_string Color_int;
        if (ANI_OK != env->EnumItem_GetValue_String(static_cast<ani_enum_item>(resourceColor_ref), &Color_int)) {
            return false;
        }
        OHOS::Ace::Color resourceColorValue;
        std::string color = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(Color_int));
        if (OHOS::Ace::Color::ParseColorString(color, resourceColorValue)) {
            resourceColor = resourceColorValue;
        }
        return true;
    }
    if (GetIsIntObject(env, resourceColor_ref)) {
        ani_int resourceColorValue;
        if (ANI_OK != env->Object_CallMethodByName_Int(
                          static_cast<ani_object>(resourceColor_ref), "toInt", ":i", &resourceColorValue)) {
            return false;
        }
        resourceColor = static_cast<OHOS::Ace::Color>(resourceColorValue);
        return true;
    }
    if (GetIsResourceObject(env, resourceColor_ref)) {
        bool ret = ParseResourceColor(env, resourceColor_ref, resourceColor);
        return ret;
    }
    return true;
}

std::string ParseCommands(ani_env* env, ani_object aniOption)
{
    std::string commands = "";
    if (GetIsUndefinedObject(env, aniOption)) {
        return commands;
    }
    ani_ref property_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(aniOption, "commands", &property_ref)) {
        return commands;
    }
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(property_ref, &isUndefined)) {
        return commands;
    }
    if (!GetIsStringObject(env, property_ref)) {
        return commands;
    }
    commands = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(property_ref));
    return commands;
}

void SetRadiusValue(
    const OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect>& shapeRect, const OHOS::Ace::CalcDimension& radius, int32_t index)
{
    CHECK_NULL_VOID(shapeRect);
    auto newRadius = OHOS::Ace::Radius(OHOS::Ace::Dimension(radius), OHOS::Ace::Dimension(radius));
    switch (index) {
        case TOP_LEFT_RADIUS:
            shapeRect->SetTopLeftRadius(newRadius);
            break;
        case TOP_RIGHT_RADIUS:
            shapeRect->SetTopRightRadius(newRadius);
            break;
        case BOTTOM_RIGHT_RADIUS:
            shapeRect->SetBottomRightRadius(newRadius);
            break;
        case BOTTOM_LEFT_RADIUS:
            shapeRect->SetBottomLeftRadius(newRadius);
            break;
        default:
            break;
    }
}

void ParseArray([[maybe_unused]] ani_env* env, 
                const OHOS::Ace::RefPtr<OHOS::Ace::ShapeRect>& shapeRect,
                ani_object options)
{
    ani_double length;
    if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(options), "length", &length)) {
        return;
    }
    for (int i = 0; i < static_cast<int32_t>(length); i++) {
        ani_ref pointRef;
        if (ANI_OK != env->Object_CallMethodByName_Ref(static_cast<ani_object>(options), 
                                                       "$_get", 
                                                       "i:Y",
                                                       &pointRef, 
                                                       (ani_int)i)) {
            break;
        }
        OHOS::Ace::CalcDimension result;
        if (GetIsStringObject(env, pointRef)) {
            auto stringContent = ANIUtils_ANIStringToStdString(env, static_cast<ani_string>(pointRef));
            result = OHOS::Ace::StringUtils::StringToCalcDimension(stringContent, false, OHOS::Ace::DimensionUnit::VP);
        } else if (GetIsNumberObject(env, pointRef)) {
            ani_double numberValue;
            if (ANI_OK != env->Object_CallMethodByName_Double(static_cast<ani_object>(pointRef), 
                                                              "toDouble", 
                                                              ":d", 
                                                              &numberValue)) {
                return;
            }
            result.SetUnit(OHOS::Ace::DimensionUnit::VP);
            result.SetValue(static_cast<double>(numberValue));
        }
        SetRadiusValue(shapeRect, result, i);
    }
}
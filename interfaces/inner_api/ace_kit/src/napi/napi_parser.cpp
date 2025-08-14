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

#include "napi/napi_parser.h"

#include <optional>
#include <regex>

#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/components/theme/resource_adapter.h"
#ifdef PREVIEW
#include "native_engine/native_engine.h"
#ifdef WINDOWS_PLATFORM
#undef TRANSPARENT
#undef ERROR
#undef ALTERNATE
#endif
#endif
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "interfaces/inner_api/ace_kit/src/view/scroller_impl.h"

namespace OHOS::Ace::Kit {

namespace {
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
constexpr int32_t UNKNOWN_RESOURCE_ID = -1;
constexpr char BUNDLE_NAME[] = "bundleName";
std::vector<std::string> RESOURCE_HEADS = { "app", "sys" };
} // namespace

struct ResourceInfo {
    int32_t resId = 0;
    int32_t type = 0;
    std::vector<std::string> params;
    std::optional<std::string> bundleName = std::nullopt;
    std::optional<std::string> moduleName = std::nullopt;
};

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000
};

enum class ResourceStruct { CONSTANT, DYNAMIC_V1, DYNAMIC_V2 };

bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType);

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info);

napi_valuetype GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
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
            if (static_cast<uint32_t>(shortHolderType) ^ static_cast<uint32_t>(pos.length() == 0)) {
                LOGE("wrong place holder,stop parse string");
                return;
            }
        }

        std::string replaceContentStr;
        std::string::size_type index = 0;
        if (shortHolderType) {
            index = static_cast<std::string::size_type>(searchTime + containCount);
        } else {
            int32_t indexTmp = StringUtils::StringToInt(pos) + static_cast<int32_t>(containCount) - 1;
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

size_t GetParamLen(napi_env env, napi_value param)
{
    size_t buffSize = 0;
    napi_status status = napi_get_value_string_utf8(env, param, nullptr, 0, &buffSize);
    if (status != napi_ok || buffSize == 0) {
        return 0;
    }
    return buffSize;
}

bool NapiStringToString(napi_env env, napi_value value, std::string& retStr)
{
    size_t ret = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        return false;
    }
    if (GetParamLen(env, value) == 0) {
        return false;
    }
    size_t valueLen = GetParamLen(env, value) + 1;
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(valueLen);
    napi_get_value_string_utf8(env, value, buffer.get(), valueLen, &ret);
    retStr = buffer.get();
    return true;
}

static uint32_t CompleteColorAlphaIfIncomplete(uint32_t origin)
{
    constexpr uint32_t colorAlphaOffset = 24;
    constexpr uint32_t colorAlphaDefaultValue = 0xFF000000;
    uint32_t result = origin;
    if ((origin >> colorAlphaOffset) == 0) {
        result = origin | colorAlphaDefaultValue;
    }
    return result;
}

napi_value CreateNapiString(napi_env env, const std::string& rawStr)
{
    napi_value retVal = nullptr;
    napi_create_string_utf8(env, rawStr.c_str(), rawStr.length(), &retVal);
    return retVal;
}

RefPtr<ResourceAdapter> CreateResourceWrapper(const ResourceInfo& info)
{
    auto bundleName = info.bundleName;
    auto moduleName = info.moduleName;

    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    if (bundleName.has_value() && moduleName.has_value()) {
        auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
            bundleName.value_or(""), moduleName.value_or(""), Container::CurrentIdSafely());
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    } else {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
    }
    return resourceAdapter;
}

bool ParseIntegerToString(const ResourceInfo& info, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(info);
    if (resourceWrapper == nullptr) {
        return false;
    }
    if (info.type == static_cast<int>(ResourceType::INTEGER)) {
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            result = std::to_string(resourceWrapper->GetIntByName(info.params[0]));
        } else {
            result = std::to_string(resourceWrapper->GetInt(info.resId));
        }
        return true;
    }
    return true;
}

std::string DimensionToString(Dimension dimension)
{
    static const int32_t unitsNum = 6;
    static const int32_t percentIndex = 3;
    static const int32_t percentUnit = 100;
    static std::array<std::string, unitsNum> units = { "px", "vp", "fp", "%", "lpx", "auto" };
    auto unit = dimension.Unit();
    auto value = dimension.Value();
    if (unit == DimensionUnit::NONE) {
        return StringUtils::DoubleToString(value).append("none");
    }
    if (units[static_cast<int>(unit)] == units[percentIndex]) {
        return StringUtils::DoubleToString(value * percentUnit).append(units[static_cast<int>(unit)]);
    }
    return StringUtils::DoubleToString(value).append(units[static_cast<int>(unit)]);
}

bool ParseString(const ResourceInfo& info, std::string& result)
{
    auto resourceWrapper = CreateResourceWrapper(info);
    if (resourceWrapper == nullptr) {
        return false;
    }
    if (info.type == static_cast<int>(ResourceType::PLURAL)) {
        std::string pluralResults;
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            auto count = StringUtils::StringToInt(info.params[1]);
            pluralResults = resourceWrapper->GetPluralStringByName(info.params[0], count);
            ReplaceHolder(pluralResults, info.params, 2); // plural holder in index 2
        } else {
            pluralResults = resourceWrapper->GetPluralString(info.resId, StringUtils::StringToInt(info.params[0]));
            ReplaceHolder(pluralResults, info.params, 1);
        }
        result = pluralResults;
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::RAWFILE)) {
        result = resourceWrapper->GetRawfile(info.params[0]);
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::FLOAT)) {
        if (info.resId == UNKNOWN_RESOURCE_ID) {
            result = DimensionToString(resourceWrapper->GetDimensionByName(info.params[0]));
        } else {
            result = DimensionToString(resourceWrapper->GetDimension(info.resId));
        }
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::STRING)) {
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
    }
    if (info.type == static_cast<int>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(info.resId).ColorToString();
        return true;
    }
    if (info.type == static_cast<int>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(info.resId));
        return true;
    }
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

bool ParseDollarResource(
    napi_env env, napi_value value, ResourceType& resType, std::string& resName, std::string& moduleName)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_string) {
        return false;
    }
    std::string resPath;
    if (!GetNapiString(env, value, resPath, valueType)) {
        return false;
    }
    std::vector<std::string> tokens;
    StringUtils::StringSplitter(resPath, '.', tokens);
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
        // moduleName not include 2 brackets
        moduleName = maybeModuleName.substr(1, maybeModuleName.size() - 2);
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

void PreFixEmptyBundleName(napi_env env, napi_value value)
{
    napi_value bundleNameNApi = nullptr;
    if (napi_get_named_property(env, value, BUNDLE_NAME, &bundleNameNApi) != napi_ok) {
        return;
    }
    std::string bundleName;
    NapiStringToString(env, bundleNameNApi, bundleName);
    if (bundleName.empty()) {
        auto container = Container::CurrentSafely();
        CHECK_NULL_VOID(container);
        bundleName = container->GetBundleName();
        bundleNameNApi = CreateNapiString(env, bundleName);
        napi_set_named_property(env, value, BUNDLE_NAME, bundleNameNApi);
    }
}

ResourceStruct CheckResourceStruct(napi_env env, napi_value value)
{
    napi_value idNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_object) {
        return ResourceStruct::CONSTANT;
    }
    if (napi_get_named_property(env, value, "id", &idNApi) != napi_ok) {
        return ResourceStruct::CONSTANT;
    }
    napi_typeof(env, idNApi, &valueType);
    if (valueType == napi_string) {
        return ResourceStruct::DYNAMIC_V1;
    }
    if (valueType == napi_number) {
        int32_t id = 0;
        napi_get_value_int32(env, idNApi, &id);
        if (id == UNKNOWN_RESOURCE_ID) {
            return ResourceStruct::DYNAMIC_V2;
        }
    }
    return ResourceStruct::CONSTANT;
}

std::optional<std::string> GetStringFromValueUtf8(napi_env env, napi_value value)
{
    if (GetValueType(env, value) != napi_string) {
        return std::nullopt;
    }

    size_t paramLen = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &paramLen);
    if (paramLen == 0 || status != napi_ok) {
        return std::nullopt;
    }
    std::unique_ptr<char[]> params = std::make_unique<char[]>(paramLen + 1);
    status = napi_get_value_string_utf8(env, value, params.get(), paramLen + 1, &paramLen);
    if (status != napi_ok) {
        return std::nullopt;
    }
    return std::optional<std::string>(params.get());
}

bool GetNapiString(napi_env env, napi_value value, std::string& retStr, napi_valuetype& valueType)
{
    if (NapiStringToString(env, value, retStr)) {
        return true;
    }
    napi_typeof(env, value, &valueType);
    if (valueType == napi_object) {
        ResourceInfo recv;
        if (ParseResourceParam(env, value, recv)) {
            ParseString(recv, retStr);
            return true;
        }
    }
    return false;
}

void ModifyResourceParam(napi_env env, napi_value value, const ResourceType& resType, const std::string& resName)
{
    // raw input : {"id":"app.xxx.xxx","params":[],"moduleName":"xxx","bundleName":"xxx"}
    // modified output : {"id":-1, "params":["app.xxx.xxx"],"type":xxxx,"moduleName":"xxx","bundleName":"xxx"}
    napi_value paramsNApi = nullptr;
    napi_get_named_property(env, value, "params", &paramsNApi);
    bool isArray = false;
    if (napi_is_array(env, paramsNApi, &isArray) != napi_ok) {
        return;
    }
    if (!isArray) {
        return;
    }
    uint32_t paramCount = 0;
    bool hasProperty = false;
    napi_get_array_length(env, paramsNApi, &paramCount);
    napi_value typeKeyNApi = CreateNapiString(env, "type");
    napi_value resNameNApi = CreateNapiString(env, resName);
    if (resType == ResourceType::PLURAL || resType == ResourceType::STRING) {
        std::vector<napi_value> tmpParams;
        for (uint32_t i = 0; i < paramCount; i++) {
            napi_value param = nullptr;
            napi_get_element(env, paramsNApi, i, &param);
            tmpParams.insert(tmpParams.end(), param);
        }
        napi_set_element(env, paramsNApi, 0, resNameNApi);
        uint32_t paramIndex = 1;
        napi_has_property(env, value, typeKeyNApi, &hasProperty);
        if (hasProperty) {
            napi_value firstParam = nullptr;
            napi_get_property(env, value, typeKeyNApi, &firstParam);
            napi_set_element(env, paramsNApi, paramIndex, firstParam);
            paramIndex++;
        }
        for (auto tmpParam : tmpParams) {
            napi_set_element(env, paramsNApi, paramIndex, tmpParam);
            paramIndex++;
        }
    } else {
        napi_set_element(env, paramsNApi, 0, resNameNApi);
    }
}

void CompleteResourceParamV1(napi_env env, napi_value value)
{
    napi_value idNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_object) {
        return;
    }
    if (napi_get_named_property(env, value, "id", &idNApi) != napi_ok) {
        return;
    }
    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!ParseDollarResource(env, idNApi, resType, resName, moduleName)) {
        return;
    }
    bool hasProperty = false;
    napi_value typeIdNApi = nullptr;
    napi_value resourceIdNApi = nullptr;
    napi_value typeKeyNApi = CreateNapiString(env, "type");
    napi_value defaultNameNApi = CreateNapiString(env, "");
    napi_value bundleNameKeyNApi = CreateNapiString(env, "bundleName");
    napi_value moduleNameKeyNApi = CreateNapiString(env, "moduleName");
    napi_create_int32(env, UNKNOWN_RESOURCE_ID, &resourceIdNApi);
    napi_create_int32(env, static_cast<uint32_t>(resType), &typeIdNApi);
    ModifyResourceParam(env, value, resType, resName);
    napi_set_property(env, value, typeKeyNApi, typeIdNApi);
    napi_set_property(env, value, CreateNapiString(env, "id"), resourceIdNApi);
    napi_has_property(env, value, bundleNameKeyNApi, &hasProperty);
    if (!hasProperty) {
        napi_set_property(env, value, bundleNameKeyNApi, defaultNameNApi);
    }
    napi_has_property(env, value, moduleNameKeyNApi, &hasProperty);
    if (!hasProperty) {
        napi_set_property(env, value, moduleNameKeyNApi, defaultNameNApi);
    }
}

void CompleteResourceParamV2(napi_env env, napi_value value)
{
    napi_value paramsNApi = nullptr;
    if (napi_get_named_property(env, value, "params", &paramsNApi) != napi_ok) {
        return;
    }
    bool isArray = false;
    napi_is_array(env, paramsNApi, &isArray);
    if (!isArray) {
        return;
    }
    uint32_t paramCount = 0;
    napi_get_array_length(env, paramsNApi, &paramCount);
    if (paramCount <= 0) {
        return;
    }
    napi_value resNameNApi = nullptr;
    napi_get_element(env, paramsNApi, 0, &resNameNApi);
    std::string resName;
    std::string moduleName;
    ResourceType resType;
    if (!ParseDollarResource(env, resNameNApi, resType, resName, moduleName)) {
        return;
    }
    napi_value typeIdNApi = nullptr;
    napi_value typeKeyNApi = CreateNapiString(env, "type");
    napi_create_int32(env, static_cast<uint32_t>(resType), &typeIdNApi);
    napi_set_property(env, value, typeKeyNApi, typeIdNApi);
    if (!moduleName.empty()) {
        napi_value moduleNameNApi = CreateNapiString(env, moduleName);
        napi_value moduleNameKeyNApi = CreateNapiString(env, "moduleName");
        napi_set_property(env, value, moduleNameKeyNApi, moduleNameNApi);
    }
}

void CompleteResourceParam(napi_env env, napi_value value)
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

bool ParseResourceParam(napi_env env, napi_value value, ResourceInfo& info)
{
    CompleteResourceParam(env, value);
    napi_value idNApi = nullptr;
    napi_value typeNApi = nullptr;
    napi_value paramsNApi = nullptr;
    napi_value bundleNameNApi = nullptr;
    napi_value moduleNameNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, value, "id", &idNApi);
        napi_get_named_property(env, value, "type", &typeNApi);
        napi_get_named_property(env, value, "params", &paramsNApi);
        napi_get_named_property(env, value, "bundleName", &bundleNameNApi);
        napi_get_named_property(env, value, "moduleName", &moduleNameNApi);
    } else {
        return false;
    }

    napi_typeof(env, idNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, idNApi, &info.resId);
    }

    napi_typeof(env, typeNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, typeNApi, &info.type);
    }

    bool isArray = false;
    if (napi_is_array(env, paramsNApi, &isArray) != napi_ok) {
        return false;
    }

    if (!isArray) {
        return false;
    }

    uint32_t arrayLength = 0;
    napi_get_array_length(env, paramsNApi, &arrayLength);

    for (uint32_t i = 0; i < arrayLength; i++) {
        size_t ret = 0;
        napi_value indexValue = nullptr;
        napi_get_element(env, paramsNApi, i, &indexValue);
        napi_typeof(env, indexValue, &valueType);
        if (valueType == napi_string) {
            size_t strLen = GetParamLen(env, indexValue) + 1;
            std::unique_ptr<char[]> indexStr = std::make_unique<char[]>(strLen);
            napi_get_value_string_utf8(env, indexValue, indexStr.get(), strLen, &ret);
            info.params.emplace_back(indexStr.get());
        } else if (valueType == napi_number) {
            int32_t num;
            napi_get_value_int32(env, indexValue, &num);
            info.params.emplace_back(std::to_string(num));
        }
    }

    napi_typeof(env, bundleNameNApi, &valueType);
    if (valueType == napi_string) {
        size_t ret = 0;
        size_t strLen = GetParamLen(env, bundleNameNApi) + 1;
        std::unique_ptr<char[]> bundleNameStr = std::make_unique<char[]>(strLen);
        napi_get_value_string_utf8(env, bundleNameNApi, bundleNameStr.get(), strLen, &ret);
        info.bundleName = bundleNameStr.get();
    }

    napi_typeof(env, moduleNameNApi, &valueType);
    if (valueType == napi_string) {
        size_t ret = 0;
        size_t strLen = GetParamLen(env, moduleNameNApi) + 1;
        std::unique_ptr<char[]> moduleNameStr = std::make_unique<char[]>(strLen);
        napi_get_value_string_utf8(env, moduleNameNApi, moduleNameStr.get(), strLen, &ret);
        info.moduleName = moduleNameStr.get();
    }

    return true;
}

bool ParseColorFromResourceObject(napi_env env, napi_value value, Color& colorResult)
{
    ResourceInfo resourceInfo;
    if (!ParseResourceParam(env, value, resourceInfo)) {
        return false;
    }
    auto resourceWrapper = CreateResourceWrapper(resourceInfo);
    if (resourceWrapper == nullptr) {
        return false;
    }
    if (resourceInfo.type == static_cast<int32_t>(ResourceType::STRING)) {
        auto colorString = resourceWrapper->GetString(resourceInfo.type);
        return Color::ParseColorString(colorString, colorResult);
    }
    if (resourceInfo.type == static_cast<int32_t>(ResourceType::INTEGER)) {
        auto colorInt = resourceWrapper->GetInt(resourceInfo.type);
        colorResult = Color(CompleteColorAlphaIfIncomplete(colorInt));
        return true;
    }
    colorResult = resourceWrapper->GetColor(resourceInfo.resId);
    return true;
}

bool ParseColor(napi_env env, napi_value value, Color& result)
{
    napi_valuetype valueType = GetValueType(env, value);
    if (valueType != napi_number && valueType != napi_string && valueType != napi_object) {
        return false;
    }
    if (valueType == napi_number) {
        int32_t colorId = 0;
        napi_get_value_int32(env, value, &colorId);
        result = Color(CompleteColorAlphaIfIncomplete(static_cast<uint32_t>(colorId)));
        return true;
    }
    if (valueType == napi_string) {
        std::optional<std::string> colorString = GetStringFromValueUtf8(env, value);
        if (!colorString.has_value()) {
            return false;
        }
        return Color::ParseColorString(colorString.value(), result);
    }

    return ParseColorFromResourceObject(env, value, result);
}

bool ACE_FORCE_EXPORT ParseDimension(
    napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit, bool isSupportPercent)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType == napi_number) {
        double value = 0;
        napi_get_value_double(env, napiValue, &value);

        result.SetUnit(defaultUnit);
        result.SetValue(value);
        return true;
    } else if (valueType == napi_string) {
        std::string valueString;
        if (!GetNapiString(env, napiValue, valueString, valueType)) {
            return false;
        }
        if (valueString.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(valueString, result, false, defaultUnit);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        std::string parameterStr;
        if (!ParseResourceParam(env, napiValue, recv)) {
            return false;
        }
        if (!ParseString(recv, parameterStr)) {
            return false;
        }
        if (!ParseIntegerToString(recv, parameterStr)) {
            return false;
        }
        result = StringUtils::StringToDimensionWithUnit(parameterStr, defaultUnit);
        return true;
    }
    return false;
}

RefPtr<Scroller> ACE_FORCE_EXPORT ParseScroller(napi_env env, napi_value value)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (valueType != napi_object) {
        return nullptr;
    }
    auto vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    panda::Local<panda::ObjectRef> scrollerObject((uintptr_t)value);
    if (scrollerObject->GetNativePointerFieldCount(vm) == 0) {
        return nullptr;
    }
    Framework::JSScroller* scroller = (Framework::JSScroller*)scrollerObject->GetNativePointerField(vm, 0);
    return AceType::MakeRefPtr<ScrollerImpl>(AceType::Claim(scroller));
}

} // namespace OHOS::Ace::Kit

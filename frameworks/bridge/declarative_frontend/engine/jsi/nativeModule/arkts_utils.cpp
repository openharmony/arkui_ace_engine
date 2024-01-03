/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

#include "frameworks/core/components/declaration/common/declaration.h"
#include "frameworks/core/common/resource/resource_manager.h"
#include "frameworks/base/utils/system_properties.h"
#include "frameworks/core/common/resource/resource_wrapper.h"
#include "frameworks/core/common/resource/resource_object.h"
#include "frameworks/core/components/theme/theme_constants.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "frameworks/core/common/card_scope.h"

namespace OHOS::Ace::NG {
const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
const std::string DEFAULT_STR = "-1";
constexpr  int32_t REPLACEHOLDER_INDEX = 2;
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

uint32_t ArkTSUtils::ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

bool ArkTSUtils::ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    if (value->IsNumber()) {
        result = Color(value->Uint32Value(vm));
        return true;
    }
    if (value->IsString()) {
        return Color::ParseColorString(value->ToString(vm)->ToString(), result);
    }
    if (value->IsObject()) {
        auto obj = value->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsColorFromResource(vm, value, result);
    }
    return false;
}

bool ArkTSUtils::ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result)
{
    if (value->IsNumber()) {
        result = Color(ColorAlphaAdapt(value->Uint32Value(vm)));
        return true;
    }
    if (value->IsString()) {
        return Color::ParseColorString(value->ToString(vm)->ToString(), result);
    }
    if (value->IsObject()) {
        return ParseJsColorFromResource(vm, value, result);
    }
    return false;
}

std::string ToString(const EcmaVM* vm,  Local<JSValueRef>& jsVal)
{
    panda::LocalScope scope(vm);
    if (jsVal->IsObject()) {
        return panda::JSON::Stringify(vm, jsVal)->ToString(vm)->ToString();
    }
    return jsVal->ToString(vm)->ToString();
}

RefPtr<ResourceObject> GetResourceObject(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    auto id = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"))->Int32Value(vm);
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"))->Int32Value(vm);
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));

    std::string bundleName;
    std::string moduleName;
    auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
    auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
    if (bundle->IsString() && module->IsString()) {
        bundleName = bundle->ToString(vm)->ToString();
        moduleName = module->ToString(vm)->ToString();
    }

    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    std::vector<ResourceObjectParams> resObjParamsList;
    auto size = static_cast<int32_t>(params->Length(vm));
    for (int32_t i = 0; i < size; i++) {
        auto item = panda::ArrayRef::GetValueAt(vm, params, i);

        std::string valueString = ToString(vm, item).c_str();

        ResourceObjectParams resObjParams { .value = valueString };
        if (item->IsString()) {
            resObjParams.type = ResourceObjectParamType::STRING;
        } else if (item->IsNumber()) {
            if (std::regex_match(item->ToString(vm)->ToString(), FLOAT_PATTERN)) {
                resObjParams.type = OHOS::Ace::ResourceObjectParamType::FLOAT;
            } else {
                resObjParams.type = OHOS::Ace::ResourceObjectParamType::INT;
            }
        }
        resObjParamsList.push_back(resObjParams);
    }
    auto resourceObject = AceType::MakeRefPtr<ResourceObject>(id, type, resObjParamsList, bundleName, moduleName);
    return resourceObject;
}

RefPtr<OHOS::Ace::ThemeConstants> GetThemeConstants(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    std::string bundleName;
    std::string moduleName;
    if (!jsObj->IsUndefined()) {
        auto obj = jsObj->ToObject(vm);
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString() && module->IsString()) {
            bundleName = bundle->ToString(vm)->ToString();
            moduleName = module->ToString(vm)->ToString();
        }
    }

    auto cardId = CardScope::CurrentId();
    if (cardId != OHOS::Ace::INVALID_CARD_ID) {
        auto container = Container::Current();
        auto weak = container->GetCardPipeline(cardId);
        auto cardPipelineContext = weak.Upgrade();
        CHECK_NULL_RETURN(cardPipelineContext, nullptr);
        auto cardThemeManager = cardPipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(cardThemeManager, nullptr);
        return cardThemeManager->GetThemeConstants(bundleName, moduleName);
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

RefPtr<ResourceWrapper> CreateResourceWrapper(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    RefPtr<ResourceObject>& resourceObject)
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = GetThemeConstants(vm, jsObj);
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

bool IsGetResourceByName(const EcmaVM* vm, const Local<JSValueRef>& jsObj)
{
    auto obj = jsObj->ToObject(vm);
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!args->IsArray(vm)) {
        return false;
    }
    auto bundleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
    auto moduleName = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
    if (!bundleName->IsString() || !moduleName->IsString()) {
        return false;
    }
    if (!bundleName->ToString(vm)->ToString().empty() || !moduleName->ToString(vm)->ToString().empty()) {
        return false;
    }
    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    if (params->Length(vm) == 0) {
        return false;
    }
    return true;
}


bool ArkTSUtils::ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result)
{
    auto obj = jsObj ->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(vm, jsObj);
    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetColorByName(param->ToString(vm)->ToString());
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        return Color::ParseColorString(value, result);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = resourceWrapper->GetInt(resId->Int32Value(vm));
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::COLOR)) {
        result = resourceWrapper->GetColor(resId->ToNumber(vm)->Value());
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result)
{
    auto obj = jsObj->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(vm, jsObj);

    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetDimensionByName(param->ToString(vm)->ToString());
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        result = StringUtils::StringToCalcDimension(value, false, dimensionUnit);
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->Int32Value(vm)));
        result = StringUtils::StringToDimensionWithUnit(value, dimensionUnit);
        return true;
    }
    result = resourceWrapper->GetDimension(resId->Int32Value(vm));
    return true;
}

bool ArkTSUtils::ParseJsDimensionFromResourceNG(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result)
{
    auto obj = jsObj->ToObject(vm);
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(vm, jsObj);

    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result = resourceWrapper->GetDimensionByName(param->ToString(vm)->ToString());
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        return StringUtils::StringToCalcDimensionNG(value, result, false, dimensionUnit);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(resId->Int32Value(vm)));
        StringUtils::StringToDimensionWithUnitNG(value, result, dimensionUnit);
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(resId->Int32Value(vm));
        return true;
    }

    return false;
}

bool ArkTSUtils::ParseStringArray(const EcmaVM* vm, const Local<JSValueRef>& arg,
    std::string* array, int32_t defaultLength)
{
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(array, false);
    if (defaultLength <= 0) {
        return false;
    }
    auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, arg);
    int32_t length = static_cast<int32_t>(handle->Length(vm));
    if (length != defaultLength) {
        return false;
    }
    for (int32_t i = 0; i < length; i++) {
        auto value = handle->GetValueAt(vm, arg, i);
        if (!ParseJsMedia(vm, value, *(array + i))) {
            *(array + i) = "";
        }
    }
    return true;
}

bool ArkTSUtils::ParseJsDimensionVp(
    const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(vm, value, result, DimensionUnit::VP, true, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, uint32_t &result)
{
    if (value->IsNumber()) {
        result = value->Uint32Value(vm);
        return true;
    }
    // resource ignore by design
    return false;
}

bool GetResourceIdAndType(const EcmaVM* vm, const Local<panda::ObjectRef>& jsObj, int32_t& resId, int32_t& resType)
{
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (!id->IsNumber() || !type->IsNumber()) {
        return false;
    }

    resId = id->Int32Value(vm);
    resType = type->Int32Value(vm);
    return true;
}

bool ArkTSUtils::ParseResourceToDouble(const EcmaVM* vm, const Local<JSValueRef>& jsValue, double& result)
{
    auto jsObj = jsValue->ToObject(vm);
    int32_t resId;
    int32_t resType;
    if (jsObj->IsNull() || !GetResourceIdAndType(vm, jsObj, resId, resType)) {
        return false;
    }
    auto resourceObject = GetResourceObject(vm, jsObj);
    auto resourceWrapper = CreateResourceWrapper(vm, jsObj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }
    if (resId == -1) {
        if (!IsGetResourceByName(vm, jsObj)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        if (resType == static_cast<int32_t>(ResourceType::STRING)) {
            auto numberString = resourceWrapper->GetStringByName(param->ToString(vm)->ToString());
            return StringUtils::StringToDouble(numberString, result);
        }
        if (resType == static_cast<int32_t>(ResourceType::INTEGER)) {
            result = resourceWrapper->GetIntByName(param->ToString(vm)->ToString());
            return true;
        }
        if (resType == static_cast<int32_t>(ResourceType::FLOAT)) {
            result = resourceWrapper->GetDoubleByName(param->ToString(vm)->ToString());
            return true;
        }
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto numberString = resourceWrapper->GetString(resId);
        return StringUtils::StringToDouble(numberString, result);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        result = resourceWrapper->GetInt(resId);
        return true;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDouble(resId);
        return true;
    }
    return false;
}

bool ArkTSUtils::ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result)
{
    if (value->IsNumber()) {
        result = value->ToNumber(vm)->Value();
        return true;
    }
    if (value->IsString()) {
        return StringUtils::StringToDouble(value->ToString(vm)->ToString(), result);
    }
    if (value->IsObject()) {
        return ParseResourceToDouble(vm, value, result);
    }
    return false;
}

bool ArkTSUtils::ParseAllBorder(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result)
{
    if (ParseJsDimensionVp(vm, args, result)) {
        if (result.IsNegative()) {
            result.Reset();
        }

        if (result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
        return true;
    } else {
        return false;
    }
}

bool ArkTSUtils::ParseAllRadius(const EcmaVM* vm, const Local<JSValueRef>& args, CalcDimension& result)
{
    if (ParseJsDimensionVp(vm, args, result)) {
        if (result.IsNegative()) {
            result.Reset();
        }
        return true;
    } else {
        return false;
    }
}

bool ArkTSUtils::ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString(vm)->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(), result, false, defaultUnit);
    }
    if (jsValue->IsObject()) {
        return ParseJsDimensionFromResourceNG(vm, jsValue, defaultUnit, result);
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent, bool enableCheckInvalidvalue)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto stringValue = jsValue->ToString(vm)->ToString();
        if (stringValue.back() == '%' && !isSupportPercent) {
            return false;
        }
        if (enableCheckInvalidvalue && stringValue.find("calc") == std::string::npos) {
            errno = 0;
            char* pEnd = nullptr;
            std::string str = jsValue->ToString(vm)->ToString();
            std::strtod(str.c_str(), &pEnd);
            if (pEnd == str.c_str() || errno == ERANGE) {
                return false;
            }
        }
        result = StringUtils::StringToCalcDimension(jsValue->ToString(vm)->ToString(), false, defaultUnit);
        return true;
    }
    if (jsValue->IsObject()) {
        return ParseJsDimensionFromResource(vm, jsValue, defaultUnit, result);
    }
    return false;
}

bool ArkTSUtils::ParseJsDimensionFp(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    bool isSupportPercent, bool enableCheckInvalidvalue)
{
    return ArkTSUtils::ParseJsDimension(
        vm, jsValue, result, DimensionUnit::FP, isSupportPercent, enableCheckInvalidvalue);
}

bool ArkTSUtils::ParseJsFontFamiliesToString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    if (jsValue->IsNull() || jsValue->IsUndefined()) {
        return false;
    }

    if (jsValue->IsString() && jsValue->ToString(vm)->ToString().empty()) {
        return false;
    }

    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(vm, jsValue, fontFamilies)) {
        return false;
    }
    if (fontFamilies.size() > 0) {
        result = "";
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            result += fontFamilies.at(i);
            if (&fontFamilies.at(i) != &fontFamilies.back()) {
                result += ",";
            }
        }
        return true;
    }

    return true;
}

bool ArkTSUtils::ParseJsFontFamilies(
    const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result)
{
    result.clear();
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = Framework::ConvertStrToFontFamilies(jsValue->ToString(vm)->ToString());
        return true;
    }
    if (jsValue->IsObject()) {
        auto obj = jsValue->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsFontFamiliesFromResource(vm, jsValue, result);
    }
    return true;
}

bool ArkTSUtils::ParseJsFontFamiliesFromResource(
    const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result)
{
    auto jsObj = jsValue->ToObject(vm);
    auto resId = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNumber()) {
        return false;
    }

    auto resourceObject = GetResourceObject(vm, jsValue);
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    auto resIdNum = resId->Int32Value(vm);
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, jsValue)) {
            return false;
        }
        auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
        if (!args->IsArray(vm)) {
            return false;
        }
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
        auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
        result.emplace_back(resourceWrapper->GetStringByName(param->ToString(vm)->ToString()));
        return true;
    }
    result.emplace_back(resourceWrapper->GetString(resId->Uint32Value(vm)));
    return true;
}

bool ArkTSUtils::ParseJsMedia(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result)
{
    if (!jsValue->IsObject() && !jsValue->IsString()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = jsValue->ToString(vm)->ToString();
        return true;
    }
    if (jsValue->IsObject()) {
        auto obj = jsValue->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsMediaFromResource(vm, jsValue, result);
    }
    return false;
}

bool ArkTSUtils::ParseJsMediaFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result)
{
    auto jsObj = jsValue->ToObject(vm);
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto resId = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    if (!resId->IsNull() && !type->IsNull() && type->IsNumber() && resId->IsNumber()) {
        auto resourceObject = GetResourceObject(vm, jsValue);
        auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
        if (!resourceWrapper) {
            return false;
        }

        if (resourceObject->GetType() == static_cast<int32_t>(ResourceType::RAWFILE)) {
            auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
            if (!args->IsArray(vm)) {
                return false;
            }
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
            auto fileName = panda::ArrayRef::GetValueAt(vm, params, 0);
            if (!fileName->IsString()) {
                return false;
            }
            result = resourceWrapper->GetRawfile(fileName->ToString(vm)->ToString());
            return true;
        }
        auto resIdNum = resId->Int32Value(vm);
        if (resIdNum == -1) {
            if (!IsGetResourceByName(vm, jsValue)) {
                return false;
            }
            auto args = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
            if (!args->IsArray(vm)) {
                return false;
            }
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
            auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
            if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::MEDIA)) {
                result = resourceWrapper->GetMediaPathByName(param->ToString(vm)->ToString());
                return true;
            }
            return false;
        }
        if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::MEDIA)) {
            result = resourceWrapper->GetMediaPath(resId->Uint32Value(vm));
            return true;
        }
        return false;
    }
    return false;
}

void ArkTSUtils::GetStringFromJS(const EcmaVM *vm, const Local<JSValueRef> &value, std::string& result)
{
    result = DEFAULT_STR;
    if (!value->IsNull() && value->IsString()) {
        result = value->ToString(vm)->ToString();
    }
    if (value->IsObject()) {
        ParseJsStringFromResource(vm, value, result);
    }
}

bool ArkTSUtils::ParseJsIntegerArray(const EcmaVM* vm, Local<JSValueRef> values, std::vector<uint32_t>& result)
{
    if (!values->IsArray(vm) && !values->IsObject()) {
        return false;
    }

    Local<panda::ArrayRef> valueArray = static_cast<Local<panda::ArrayRef>>(values);
    for (size_t i = 0; i < valueArray->Length(vm); i++) {
        Local<JSValueRef> value = valueArray->GetValueAt(vm, values, i);
        if (value->IsNumber()) {
            result.emplace_back(value->Uint32Value(vm));
        } else if (value->IsObject()) {
            uint32_t singleResInt;
            if (ParseJsInteger(vm, value, singleResInt)) {
                result.emplace_back(singleResInt);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

bool ArkTSUtils::ParseJsString(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    if (!jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }
    if (jsValue->IsString()) {
        result = jsValue->ToString(vm)->ToString();
        return true;
    }
    if (jsValue->IsObject()) {
        return ArkTSUtils::ParseJsStringFromResource(vm, jsValue, result);
    }
    return false;
}

std::string GetReplaceContentStr(
    const EcmaVM* vm, int32_t pos, const std::string& type, Local<panda::ArrayRef> params, int32_t containCount)
{
    int32_t index = pos + containCount;
    if (index < 0) {
        return std::string();
    }
    auto item = panda::ArrayRef::GetValueAt(vm, params, static_cast<uint32_t>(index));
    if (type == "d") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber(vm)->Value());
        }
    } else if (type == "s") {
        if (item->IsString()) {
            return item->ToString(vm)->ToString();
        }
    } else if (type == "f") {
        if (item->IsNumber()) {
            return std::to_string(item->ToNumber(vm)->Value());
        }
    }
    return std::string();
}

void ReplaceHolder(const EcmaVM* vm, std::string& originStr, const Local<panda::ArrayRef>& params, int32_t containCount)
{
    auto size = static_cast<int32_t>(params->Length(vm));
    if (containCount == size) {
        return;
    }
    std::string::const_iterator start = originStr.begin();
    std::string::const_iterator end = originStr.end();
    std::smatch matches;
    bool shortHolderType = false;
    bool firstMatch = true;
    int searchTime = 0;
    while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
        std::string pos = matches[2];
        std::string type = matches[4];
        if (firstMatch) {
            firstMatch = false;
            shortHolderType = pos.length() == 0;
        } else {
            if (static_cast<uint32_t>(shortHolderType) ^ static_cast<uint32_t>(pos.length() == 0)) {
                return;
            }
        }

        std::string replaceContentStr;
        if (shortHolderType) {
            replaceContentStr = GetReplaceContentStr(vm, searchTime, type, params, containCount);
        } else {
            replaceContentStr = GetReplaceContentStr(vm, StringUtils::StringToInt(pos) - 1, type, params, containCount);
        }

        originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
        start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
        end = originStr.end();
        searchTime++;
    }
}

bool FillResultForResIdNumIsNegative(const EcmaVM* vm, const Local<JSValueRef>& type, const Local<JSValueRef>& params,
    std::string& result, const RefPtr<ResourceWrapper>& resourceWrapper)
{
    auto param = panda::ArrayRef::GetValueAt(vm, params, 0);
    if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetStringByName(param->ToString(vm)->ToString());
        ReplaceHolder(vm, originStr, params, 0);
        result = originStr;
    } else if (type->Uint32Value(vm) == static_cast<uint32_t>(ResourceType::PLURAL)) {
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, 1);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralStringByName(param->ToString(vm)->ToString(), count);
        ReplaceHolder(vm, pluralStr, params, REPLACEHOLDER_INDEX);
        result = pluralStr;
    } else {
        return false;
    }
    return true;
}

bool ArkTSUtils::ParseJsStringFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& result)
{
    auto obj = jsValue->ToObject(vm);
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    auto args = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "params"));
    if (!type->IsNumber() || !resId->IsNumber() || !args->IsArray(vm)) {
        return false;
    }

    auto resourceObject = GetResourceObject(vm, obj);
    auto resourceWrapper = CreateResourceWrapper(vm, obj, resourceObject);
    if (!resourceWrapper) {
        return false;
    }

    Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(args);
    auto resIdNum = resourceObject->GetId();
    if (resIdNum == -1) {
        if (!IsGetResourceByName(vm, obj)) {
            return false;
        }
        return FillResultForResIdNumIsNegative(vm, type, params, result, resourceWrapper);
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto originStr = resourceWrapper->GetString(resId->Uint32Value(vm));
        ReplaceHolder(vm, originStr, params, 0);
        result = originStr;
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::PLURAL)) {
        auto countJsVal = panda::ArrayRef::GetValueAt(vm, params, 0);
        int count = 0;
        if (!countJsVal->IsNumber()) {
            return false;
        }
        count = countJsVal->ToNumber(vm)->Value();
        auto pluralStr = resourceWrapper->GetPluralString(resId->ToNumber(vm)->Value(), count);
        ReplaceHolder(vm, pluralStr, params, 1);
        result = pluralStr;
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = std::to_string(resourceWrapper->GetDouble(resId->Uint32Value(vm)));
    } else if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::INTEGER)) {
        result = std::to_string(resourceWrapper->GetInt(resId->Uint32Value(vm)));
    } else {
        return false;
    }
    return true;
}

bool ArkTSUtils::ParseJsResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result)
{
    if (!jsValue->IsObject()) {
        return false;
    }
    auto jsObj = jsValue->ToObject(vm);
    auto resourceObject = GetResourceObject(vm, jsValue);
    auto resourceWrapper = CreateResourceWrapper(vm, jsValue, resourceObject);
    CHECK_NULL_RETURN(resourceWrapper, false);
    
    auto type = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    auto id = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
    uint32_t resourceType = 0;
    if (type->IsNull() || !type->IsNumber() || id->IsNull() || !id->IsNumber()) {
        return false;
    } else {
        resourceType = type->Uint32Value(vm);
    }
    if (resourceType == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(id->Uint32Value(vm));
        return StringUtils::StringToCalcDimensionNG(value, result, false);
    }
    if (resourceType == static_cast<uint32_t>(ResourceType::INTEGER)) {
        auto value = std::to_string(resourceWrapper->GetInt(id->Uint32Value(vm)));
        StringUtils::StringToDimensionWithUnitNG(value, result);
        return true;
    }

    if (resourceType == static_cast<uint32_t>(ResourceType::FLOAT)) {
        result = resourceWrapper->GetDimension(id->Uint32Value(vm));
        return true;
    }
    return false;
}

void ArkTSUtils::GetJsMediaBundleInfo(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& bundleName, std::string& moduleName)
{
    if (!jsValue->IsObject() || jsValue->IsString()) {
        return;
    }
    auto jsObj = jsValue->ToObject(vm);
    if (!jsObj->IsUndefined()) {
        auto bundle = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString() && module->IsString()) {
            bundleName = bundle->ToString(vm)->ToString();
            moduleName = module->ToString(vm)->ToString();
        }
    }
}

bool ArkTSUtils::GetJsPasswordIcon(const EcmaVM *vm, const Local<JSValueRef> &jsOnIconSrc,
    const Local<JSValueRef> &jsOffIconSrc, PasswordIcon& result)
{
    result.showResult = "";
    result.hideResult = "";
    result.showBundleName = "";
    result.hideBundleName = "";
    result.showModuleName = "";
    result.hideModuleName = "";

    if (!jsOnIconSrc->IsString() && !jsOnIconSrc->IsObject()
        && !jsOffIconSrc->IsString() && !jsOffIconSrc->IsObject()) {
        return false;
    }

    if (jsOnIconSrc->IsString()) {
        result.showResult = jsOnIconSrc->ToString(vm)->ToString();
    }

    if (jsOnIconSrc->IsObject()) {
        auto obj = jsOnIconSrc->ToObject(vm);
        std::string bundleName;
        std::string moduleName;
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString() && module->IsString()) {
            result.showBundleName = bundle->ToString(vm)->ToString();
            result.showModuleName = module->ToString(vm)->ToString();
        }
        ParseJsMedia(vm, jsOnIconSrc, result.showResult);
    }

    if (jsOffIconSrc->IsString()) {
        result.hideResult = jsOffIconSrc->ToString(vm)->ToString();
    }

    if (jsOffIconSrc->IsObject()) {
        auto obj = jsOffIconSrc->ToObject(vm);
        std::string bundleName;
        std::string moduleName;
        auto bundle = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "bundleName"));
        auto module = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "moduleName"));
        if (bundle->IsString() && module->IsString()) {
            result.hideBundleName = bundle->ToString(vm)->ToString();
            result.hideModuleName = module->ToString(vm)->ToString();
        }
        ParseJsMedia(vm, jsOffIconSrc, result.hideResult);
    }
    return true;
}
} // namespace OHOS::Ace::NG

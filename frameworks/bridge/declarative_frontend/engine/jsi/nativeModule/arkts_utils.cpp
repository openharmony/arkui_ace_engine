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
const std::regex FLOAT_PATTERN(R"(-?(0|[1-9]\d*)(\.\d+))", std::regex::icase);
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
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

uint32_t ColorAlphaAdapt(uint32_t origin)
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
        auto obj = value->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsColorFromResource(vm, value, result);
    }
    return false;
}

bool ArkTSUtils::ParseJsDimension(const EcmaVM* vm, const Local<JSValueRef>& value,
    DimensionUnit dimensionUnit, CalcDimension& result, bool isSupportPercent = true)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), dimensionUnit);
        return true;
    }
    if (value->IsString()) {
        auto stringValue = value->ToString(vm)->ToString();
        if (stringValue.back() == '%' && !isSupportPercent) {
            return false;
        }
        result = StringUtils::StringToCalcDimension(stringValue, false, dimensionUnit);
        return true;
    }
    if (value->IsObject()) {
        auto obj = value->ToObject(vm);
        auto resId = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "id"));
        if (!resId->IsNumber()) {
            return false;
        }
        return ParseJsDimensionFromResource(vm, value, dimensionUnit, result);
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
    result = resourceWrapper->GetColor(resId->Int32Value(vm));
    return true;
}


bool ArkTSUtils::ParseJsDimensionFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj,
    DimensionUnit dimensionUnit, CalcDimension& result, bool isSupportPercent)
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
        result = resourceWrapper->GetDimensionByName(param->ToString(vm)->ToString());
        return true;
    }
    auto type = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "type"));
    if (type->IsNull() || !type->IsNumber()) {
        return false;
    }
    if (resourceObject->GetType() == static_cast<uint32_t>(ResourceType::STRING)) {
        auto value = resourceWrapper->GetString(resId->Int32Value(vm));
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
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


bool ArkTSUtils::ParseStringArray(const EcmaVM *vm, const Local<JSValueRef> &arg, char **array, int32_t defaultLength)
{
    CHECK_NULL_RETURN(vm, false);
    CHECK_NULL_RETURN(array, false);
    if (defaultLength <= 0) {
        return false;
    }
    auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, arg);
    int32_t length = handle->Length(vm);
    if (length != defaultLength) {
        return false;
    }
    for (int32_t i = 0; i < length; i++) {
        auto value = handle->GetValueAt(vm, arg, i);
        if (value->IsString()) {
            *(array + i) = const_cast<char *>(value->ToString(vm)->ToString().c_str());
        } else {
            *(array + i) = nullptr;
        }
    }
    return true;
}


bool ArkTSUtils::ParseJsDimensionVp(const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension &result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    // resouce ignore by design
    return false;
}

bool ArkTSUtils::ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    // resouce ignore by design
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
    // resouce ignore by design
    return false;
}

void ArkTSUtils::ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result)
{
    if (ParseJsDimensionVp(vm, args, result) && result.IsNonNegative()) {
        if (result.Unit() == DimensionUnit::PERCENT) {
            result.Reset();
        }
    }
}

bool ArkTSUtils::ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
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
    // resouce ignore by design
    return false;
}

bool ArkTSUtils::ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    bool isSupportPercent)
{
    return ArkTSUtils::ParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}

bool ArkTSUtils::ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
    DimensionUnit defaultUnit)
{
    if (!jsValue->IsNumber() && !jsValue->IsString() && !jsValue->IsObject()) {
        return false;
    }

    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        result = StringUtils::StringToCalcDimension(jsValue->ToString(vm)->ToString(), false, defaultUnit);
        return true;
    }
    return true;
}

bool ArkTSUtils::ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result)
{
    return ArkTSUtils::ParseJsDimension(vm, jsValue, result, DimensionUnit::FP);
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
    return true;
}
} // namespace OHOS::Ace::NG